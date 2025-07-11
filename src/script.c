/*!
 * \file script.c
 * \brief Basic Postscript support for libembroidery.
 *
 * Libembroidery 1.0.0-alpha
 * https://www.libembroidery.org
 *
 * A library for reading, writing, altering and otherwise
 * processing machine embroidery files and designs.
 *
 * Also, the core library supporting the Embroidermodder Project's
 * family of machine embroidery interfaces.
 *
 * -----------------------------------------------------------------------------
 *
 * Copyright 2018-2025 The Embroidermodder Team
 * Licensed under the terms of the zlib license.
 *
 * -----------------------------------------------------------------------------
 *
 * In order to support postscript and allow for certain path operations we need
 * a minimal scripting environment. This needs to be kept fairly simple, as
 * it will be a more bug prone way to work than in straightforward C.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#include "embroidery.h"
#include "../extern/mpc/mpc.h"

void embPattern_addArc(EmbPattern *pattern, EmbArc arc);
int process_stack_head(EmbStack *stack);

static EmbPattern *focussed_pattern = NULL;

const char *index_th_name[] = {
    "first",
    "second",
    "third",
    "fourth",
    "fifth",
    "sixth",
    "seventh"
};

/*!
 * Internally, we use fixed-point arithmetic because it can be made more
 * consistent.
 *
 * The maximum integer value is 32767, so with a place value of 0.1 the
 * maximum distance is 3276.7 mm which is around 3 metres. In longer
 * calculations this means that we can have stacked errors that cause issues.
 *
 * However, since 2 byte, fixed-point real types are appropriate for most
 * scenarios: if this is a issue for a specific calculation then we recommend
 * that authors scale up then scale down what they're working on. If it
 * continues to be an issue please describe your use case, along with a
 * description of your art, to us at the issues page on:
 *     https://github.com/embroidermodder/libembroidery
 */
#define DEFAULT_PLACE_VALUE        (0.1)

/* INTERNAL POSTSCRIPT-COMPATIBLE INTERPRETER
 * ------------------------------------------
 *
 * Eventually we want all dependencies of libembroidery to be only c standard
 * libraries and we also need the interpreter to integrate well with our
 * own virtual machine. So this experiment is to establish that this works.
 *
 * I am using the PostScript Reference Manual for a description of how the
 * langauge works. It is being held in an environment where it cannot
 * effect the disk directly and can only edit a pattern loaded into memory.
 * This should reduce the potential damage of a malicious postscript file,
 * because it will only have access to the files that we explicitly give it
 * access to (assuming there are no memory leaks).
 */

/* PostScript data types */
#define STRING_TYPE                    0
#define ARRAY_TYPE                     1
#define REAL_TYPE                      2
#define INT_TYPE                       3
#define BOOL_TYPE                      4
#define NAME_TYPE                      5
#define DICTIONARY_TYPE                6

/*! Postscript data types */
static char postscript_data_type[][20] = {
    "string",
    "array",
    "real",
    "int",
    "bool",
    "name",
    "dictionary"
};

/* Attributes */
#define LITERAL_ATTR                   0
#define EXEC_ATTR                      1

/* PostScript's built-in identifiers
 * (See the in_built_functions string table below.)
 */
/* 3.6.1 Stack */
#define PS_FUNC_DUP                    0
#define PS_FUNC_EXCH                   1
#define PS_FUNC_POP                    2
#define PS_FUNC_COPY                   3
#define PS_FUNC_ROLL                   4
#define PS_FUNC_INDEX                  5
#define PS_FUNC_MARK                   6
#define PS_FUNC_CLEAR                  7
#define PS_FUNC_COUNT                  8
#define PS_FUNC_COUNTTOMARK            9
/* 3.6.2 Mathematical */
#define PS_FUNC_ADD                   10
#define PS_FUNC_SUB                   11
#define PS_FUNC_MUL                   12
#define PS_FUNC_DIV                   13
#define PS_FUNC_IDIV                  14
#define PS_FUNC_MOD                   15
#define PS_FUNC_ABS                   16
#define PS_FUNC_NEG                   17
#define PS_FUNC_CEILING               18
#define PS_FUNC_FLOOR                 19
#define PS_FUNC_ROUND                 20
#define PS_FUNC_TRUNCATE              21
#define PS_FUNC_SQRT                  22
#define PS_FUNC_EXP                   23
#define PS_FUNC_LN                    24
#define PS_FUNC_LOG                   25
#define PS_FUNC_sin                   26
#define PS_FUNC_cos                   27
#define PS_FUNC_atan                  28
#define PS_FUNC_rand                  29
#define PS_FUNC_srand                 30
#define PS_FUNC_rrand                 31
/* 3.6.3 Array, Dictionary, String */
#define PS_FUNC_get                   32
#define PS_FUNC_put                   33
#define PS_FUNC_copy                  34
#define PS_FUNC_length                35
#define PS_FUNC_getinterval           36
#define PS_FUNC_putinterval           37
/* Array-specific */
#define PS_FUNC_aload                 38
#define PS_FUNC_astore                39
#define PS_FUNC_OPEN_SQ               40
#define PS_FUNC_CLOSE_SQ              41
#define PS_FUNC_setpacking            42
#define PS_FUNC_currentpacking        43
/* Dictionary-specific */
#define PS_FUNC_begin                 44
#define PS_FUNC_end                   45
#define PS_FUNC_def                   46
#define PS_FUNC_store                 47
#define PS_FUNC_load                  48
#define PS_FUNC_where                 49
#define PS_FUNC_countdictstack        50
#define PS_FUNC_cleardictstack        51
#define PS_FUNC_dictstack             52
#define PS_FUNC_known                 53
#define PS_FUNC_maxlength             54
#define PS_FUNC_undef                 55 /* Level 2 */
#define PS_FUNC_left_arrow            56 /* Level 2 */
#define PS_FUNC_right_arrow           57 /* Level 2 */
/* String-specific */
#define PS_FUNC_search                58
#define PS_FUNC_anchorsearch          59
#define PS_FUNC_token                 60
/* 3.6.4 Boolean */
#define PS_FUNC_eq                    61
#define PS_FUNC_ne                    62
#define PS_FUNC_gt                    63
#define PS_FUNC_ge                    64
#define PS_FUNC_le                    65
#define PS_FUNC_lt                    66
#define PS_FUNC_and                   67
#define PS_FUNC_or                    68
#define PS_FUNC_xor                   69
#define PS_FUNC_true                  70
#define PS_FUNC_false                 71
#define PS_FUNC_not                   72
/* 3.6.5 Control */
#define PS_FUNC_if                    73
#define PS_FUNC_ifelse                74
#define PS_FUNC_exec                  75
#define PS_FUNC_for                   76
#define PS_FUNC_repeat                77
#define PS_FUNC_loop                  78
#define PS_FUNC_forall                79
#define PS_FUNC_exit                  80
#define PS_FUNC_countexecstack        81
#define PS_FUNC_execstack             82
#define PS_FUNC_stop                  83
/* 3.6.6 Type */
#define PS_FUNC_type                  84
#define PS_FUNC_xcheck                85
#define PS_FUNC_rcheck                86
#define PS_FUNC_wcheck                87
#define PS_FUNC_cvlit                 88
#define PS_FUNC_cvx                   89
#define PS_FUNC_readonly              90
#define PS_FUNC_executeonly           91
#define PS_FUNC_noaccess              92
#define PS_FUNC_cvi                   93
#define PS_FUNC_cvr                   94
#define PS_FUNC_cvn                   95
#define PS_FUNC_cvs                   96
#define PS_FUNC_cvrs                  97
/* 3.7.1 Memory */
#define PS_FUNC_array                 98
#define PS_FUNC_packedarray           99
#define PS_FUNC_dict                 100
#define PS_FUNC_string               101
#define PS_FUNC_gstate               102
/* 3.7.2 VM */
#define PS_FUNC_save                 103
#define PS_FUNC_restore              104
#define PS_FUNC_userdict             105
#define PS_FUNC_gcheck               106

int emb_repl(void);
void execute_postscript(EmbStack *stack, char line[200]);
void analyse_stack(EmbStack *stack);

/* The PostScript Reference Manual (second edition) lists these commands and
 * specifically requests that authors credit them as the copyright holder
 * in order to protect their ownership of the language and de-facto interpreter.
 *
 * We reproduce it here in order to make our own filters and graphics features
 * compatible with those found in graphic design for modern printers and
 * scanners.
 *
 * The in_built_functions string table here is credited to:
 *     Adobe Systems Incorporated "The PostScript(R) Reference Manual" (1990)
 *     (Second Edition) Addison Wesley
 */
static char in_built_functions[][20] = {
    /* 3.6.1 Stack */
    "dup",
    "exch",
    "pop",
    "copy",
    "roll",
    "index",
    "mark",
    "clear",
    "count",
    "counttomark",
    /* 3.6.2 Mathematical */
    "add",
    "sub",
    "mul",
    "div",
    "idiv",
    "mod",
    "abs",
    "neg",
    "ceiling",
    "floor",
    "round",
    "truncate",
    "sqrt",
    "exp",
    "ln",
    "log",
    "sin",
    "cos",
    "atan",
    "rand",
    "srand",
    "rrand",
    /* 3.6.3 Array, Dictionary, String */
    "get",
    "put",
    "copy",
    "length",
    "getinterval",
    "putinterval",
    /* Array-specific */
    "aload",
    "astore",
    "[",
    "]",
    "setpacking",
    "currentpacking",
    /* Dictionary-specific */
    "begin",
    "end",
    "def",
    "store",
    "load",
    "where",
    "countdictstack",
    "cleardictstack",
    "dictstack",
    "known",
    "maxlength",
    "undef", /* Level 2 */
    "<<", /* Level 2 */
    ">>", /* Level 2 */
    /* String-specific */
    "search",
    "anchorsearch",
    "token",
    /* 3.6.4 Boolean */
    "eq",
    "ne",
    "gt",
    "ge",
    "le",
    "lt",
    "and",
    "or",
    "xor",
    "true",
    "false",
    "not",
    /* 3.6.5 Control */
    "if",
    "ifelse",
    "exec",
    "for",
    "repeat",
    "loop",
    "forall",
    "exit",
    "countexecstack",
    "execstack",
    "stop",
    /* 3.6.6 Type */
    "type",
    "xcheck",
    "rcheck",
    "wcheck",
    "cvlit",
    "cvx",
    "readonly",
    "executeonly",
    "noaccess",
    "cvi",
    "cvr",
    "cvn",
    "cvs",
    "cvrs",
    /* 3.7.1 Memory */
    "array",
    "packedarray",
    "dict",
    "string",
    "gstate",
    /* 3.7.2 VM */
    "save",
    "restore",
    "userdict",
    "gcheck",
    ""
};

/*! The default internal scripting of programs that use libembroidery is our
 * internal scheme dialect that we will attempt to keep in line with R5RS.
 * Ideally, the .arguments term would match the specification somehow so
 * argument checking on ... TODO
 */
const CommandData builtins_data[] = {
    {
        .command="+",
        .arguments="nn" /* Can work work with either number type, so we need
                         * to allow different arguments to pass.
                         */
    }
};

const ScriptValue script_true = {
    .r = 0.0F,
    .i = 1,
    .b = true,
    .s = "",
    .label = "true",
    .type = SCRIPT_BOOL
};

const ScriptValue script_false = {
    .r = 0.0F,
    .i = 0,
    .b = false,
    .s = "",
    .label = "false",
    .type = SCRIPT_BOOL
};

const ScriptValue script_null = {
    .r = 0.0F,
    .i = 0,
    .b = false,
    .s = "",
    .label = "false",
    .type = SCRIPT_NULL
};

/* . */
ScriptValue
script_bool(unsigned char b)
{
    ScriptValue value;
    value.type = SCRIPT_BOOL;
    value.b = b;
    return value;
}

/* . */
ScriptValue
script_int(int i)
{
    ScriptValue value;
    value.type = SCRIPT_INT;
    value.i = i;
    return value;
}

/* . */
ScriptValue
script_real(EmbReal r)
{
    ScriptValue value;
    value.type = SCRIPT_REAL;
    value.r = r;
    return value;
}

/* . */
ScriptValue
script_string(char *s)
{
    ScriptValue value;
    value.type = SCRIPT_STRING;
    strncpy(value.s, s, MAX_STRING_LENGTH-1);
    return value;
}

/* . */
ScriptValue
script_vector(EmbVector v)
{
    ScriptValue value;
    value.type = SCRIPT_VECTOR;
    value.v = v;
    return value;
}

ScriptEnv *
create_script_env(void)
{
    ScriptEnv *context = (ScriptEnv*)malloc(sizeof(ScriptEnv));
    context->argumentCount = 0;
    context->script_true = script_true;
    context->script_false = script_false;
    context->script_null = script_null;
    context->state = emb_create_root();
    context->n_commands = 0;
    context->command_mem = 100;
    context->command_list = (CommandData*)malloc(context->command_mem*sizeof(CommandData));
    strncpy(context->curcmd, "null", MAX_STRING_LENGTH-1);
    return context;
}

/* . */
void
free_script_env(ScriptEnv* context)
{
    free(context->command_list);
    free(context);
}

/* . */
void
script_add_command(ScriptEnv *context, CommandData *cmd)
{
    if (context->n_commands > context->command_mem - 2) {
        context->command_mem += 100;
        context->command_list = (CommandData*)realloc(context->command_list,
            context->command_mem*sizeof(CommandData));
    }
    memcpy(context->command_list + context->n_commands, cmd, sizeof(CommandData));
    context->n_commands++;
}

/* Using stdarg we can pack arguments into the context using the above functions.
 *
 * https://pubs.opengroup.org/onlinepubs/009695399/basedefs/stdarg.h.html
 */
ScriptEnv *
pack(ScriptEnv *context, const char *fmt, ...)
{
    va_list a;
    int argno;
    context->argumentCount = 0;
    va_start(a, fmt);
    for (argno = 0; fmt[argno]; argno++) {
        switch (fmt[argno]) {
        case 's': {
            const char *s = va_arg(a, const char *);
            strncpy(context->argument[context->argumentCount].s, s, MAX_STRING_LENGTH);
            context->argument[context->argumentCount].type = SCRIPT_STRING;
            break;
        }
        case 'i': {
            int i = va_arg(a, int);
            context->argument[context->argumentCount].i = i;
            context->argument[context->argumentCount].type = SCRIPT_INT;
            break;
        }
        case 'r': {
            EmbReal r = va_arg(a, double);
            context->argument[context->argumentCount].r = r;
            context->argument[context->argumentCount].type = SCRIPT_REAL;
            break;
        }
        default:
            break;
        }
        context->argumentCount++;
    }
    va_end(a);
    return context;
}

/* Using a similar approach to pack we can now create a caller that also packs
 * the arguments.
 */
ScriptValue
call(ScriptEnv *context, const char *cmd)
{
    int id = -1, i;
    for (i=0; i<context->n_commands; i++) {
        if (!strcmp(context->command_list[i].command, cmd)) {
            id = i;
            break;
        }
    }
    if (id < 0) {
        debug_message("ERROR: failed to find function %s", cmd);
        return script_false;
    }
    if (!argument_checks(context, cmd, context->command_list[id].arguments)) {
        debug_message("ERROR: Failed argument checks for %s.", cmd);
        return script_false;
    }
    strncpy(context->curcmd, cmd, MAX_STRING_LENGTH-1);
    Command *command = context->command_list[id].action;
    return command(context);
}

/* TODO: remove args command, use the command_data table
 */
int
argument_checks(ScriptEnv *context, const char *function, const char *args)
{
    char s[200];
    int i;
    if (context->argumentCount != strlen(args)) {
        sprintf(s, "%s() requires %d arguments.", function, context->argumentCount);
        puts(s);
        return 0;
    }
    for (i=0; args[i]; i++) {
        if (args[i] == 'r') {
            if (context->argument[i].type != SCRIPT_REAL) {
                sprintf(s,
                    "TYPE_ERROR, %s(): %s argument is not a real number.",
                    function, index_th_name[i]);
                puts(s);
                return 0;
            }
            float variable = context->argument[i].r;
            if (isnan(variable)) {
                sprintf(s,
                    "TYPE_ERROR, %s(): %s argument is not a real number.",
                    function, index_th_name[i]);
                puts(s);
                return 0;
            }
        }
        if (args[i] == 'i') {
            if (context->argument[i].type != SCRIPT_INT) {
                sprintf(s,
                    "TYPE_ERROR, %s(): %s argument is not an integer.",
                    function, index_th_name[i]);
                puts(s);
                return 0;
            }
        }
        if (args[i] == 'b') {
            if (context->argument[i].type != SCRIPT_BOOL) {
                sprintf(s,
                    "TYPE_ERROR, %s(): %s argument is not a boolean.",
                    function, index_th_name[i]);
                puts(s);
                return 0;
            }
        }
        if (args[i] == 's') {
            if (context->argument[i].type != SCRIPT_STRING) {
                sprintf(s,
                    "TYPE_ERROR, %s(): %s argument is not a string.",
                    function, index_th_name[i]);
                puts(s);
                return 0;
            }
        }
    }
    return 1;
}

/*!  . */
ScriptValue
plus_command(ScriptEnv *context)
{
    return script_null;
}

/*!  . */
ScriptValue
minus_command(ScriptEnv *context)
{
    return script_null;
}

/*!  . */
ScriptValue
lambda_command(ScriptEnv *context)
{
    return script_null;
}

/*!  . */
ScriptValue
if_command(ScriptEnv *context)
{
    return script_null;
}

/*!  . */
ScriptValue
and_command(ScriptEnv *context)
{
    return script_null;
}

/*!  . */
ScriptValue
cond_command(ScriptEnv *context)
{
    return script_null;
}

/* .
 */
void
analyse_stack(EmbStack *stack)
{
    int i;
    for (i=0; i<stack->position; i++) {
        EmbStackElement element = stack->stack[i];
        printf("%d ", i);
        if ((element.data_type >= 0) && (element.data_type <= DICTIONARY_TYPE)) {
            printf("%s", postscript_data_type[element.data_type]);
        }
        else {
            printf("unknown");
        }
        printf(" ");
        if (element.attribute) {
            printf("exec index %d", element.i);
        }
        else {
            printf("literal");
        }
        printf(" %s\n", element.s);
    }
}

/* .
 */
int
stack_push(EmbStack *stack, char *token)
{
    int i, j;
    int all_digits = 1;
    int decimal_place_present = 0;
    if (token[0] == 0) {
        return -1;
    }
    strncpy(stack->stack[stack->position].s, token, 200);
    stack->position++;    
    EmbStackElement *element = stack->stack + stack->position - 1;
    i = 0;
    j = 0;
    for (j=0; in_built_functions[j][0]; j++) {
        if (!strcmp(in_built_functions[j], token)) {
            element->data_type = NAME_TYPE;
            element->attribute = EXEC_ATTR;
            element->i = j;
            return NAME_TYPE;
        }
    }

    element->attribute = LITERAL_ATTR;

    if (token[0] == '-') {
        i++;
    }
    if (token[0] == '"') {
        element->data_type = STRING_TYPE;
        return STRING_TYPE;
    }
    for (; token[i] && (i < 200); i++) {
        if ((token[i] < '0') || (token[i] > '9')) {
            all_digits = 0;
        }
        if (token[i] == '.') {
            decimal_place_present++;
        }
    }
    if (all_digits) {
        if (decimal_place_present == 0) {
            element->data_type = INT_TYPE;
            return INT_TYPE;
        }
        if (decimal_place_present == 1) {
            element->data_type = REAL_TYPE;
            return REAL_TYPE;
        }
        /* Multiple decimal points in one float error. */
        stack->position--;
        return -2;
    }
    /* ERROR CODE */
    stack->position--;
    return -1;
}

/* .
 */
EmbStackElement
stack_pop(EmbStack *stack)
{
    EmbStackElement e;
    memcpy(&e, stack->stack + stack->position - 1, sizeof(EmbStackElement));
    stack->position--;
    return e;
}

/* .
 */
int
queue_token(EmbStack *stack, char token[200])
{
    int error_code = stack_push(stack, token);
    if (error_code < 0) {
        printf("Failed to queue token %s\n", token);
        return 0;
    }
    process_stack_head(stack);
    return 1;
}

/* .
 */
void
queue_token_list(EmbStack *stack, char line[200])
{
    char current_token[200];
    int i, j;
    j = 0;
    for (i=0; line[i]; i++) {
        if (line[i] == ' ') {
            current_token[j] = 0;
            queue_token(stack, current_token);
            j = 0;
        }
        else {
            current_token[j] = line[i];
            j++;
        }
    }
    if (line[0] != 0) {
        current_token[j] = 0;
        queue_token(stack, current_token);
    }
}

/* .
 */
int
token_is_int(EmbStackElement arg)
{
    if (arg.attribute) {
        return 0;
    }
    return (arg.data_type == INT_TYPE);
}

/* Tests if char * matches a fixed string, often from compiled-in program
 * data.
 */
bool
string_equal(char *a, const char *b)
{
    return (strncmp(a, b, MAX_STRING_LENGTH) == 0);
}


/* . */
int
parse_floats(const char *line, float result[], int n)
{
    char substring[MAX_STRING_LENGTH];
    const char *c;
    int i = 0;
    int pos = 0;
    for (c=line; *c; c++) {
        substring[pos] = *c;
        if (*c == ',' || *c == ' ') {
            substring[pos] = 0;
            result[i] = atof(substring);
            pos = 0;
            i++;
            if (i > n-1) {
                return -1;
            }
        }
        else {
            pos++;
        }
    }
    substring[pos] = 0;
    result[i] = atof(substring);
    return i+1;
}

int
parse_vector(const char *line, EmbVector *v)
{
    float v_[2];
    if (parse_floats(line, v_, 2) == 2) {
        return 0;
    }
    v->x = v_[0];
    v->y = v_[1];
    return 1;
}

/* . */
bool
valid_rgb(float r, float g, float b)
{
    if (isnan(r)) {
        return false;
    }
    if (isnan(g)) {
        return false;
    }
    if (isnan(b)) {
        return false;
    }
    if (r < 0 || r > 255) {
        return false;
    }
    if (g < 0 || g > 255) {
        return false;
    }
    if (b < 0 || b > 255) {
        return false;
    }
    return true;
}

/* This version of string_array_length does not protect against the END_SYMBOL
 * missing, because it is only to be used for compiled in constant tables.
 *
 * For string tables edited during run time, the END_SYMBOL is checked for during loops.
 */
int
table_length(char *s[])
{
    int i;
    for (i=0; i<1000; i++) {
        if (s[i][0] == END_SYMBOL[0]) {
            if (!strncmp(s[i], END_SYMBOL, MAX_STRING_LENGTH)) {
                break;
            }
        }
    }
    if (i == 1000) {
        puts("ERROR: Table is missing END_SYMBOL.");
        return 1000;
    }
    return i;
}

/* . */
unsigned char *
load_file(char *fname)
{
    FILE *f = fopen(fname, "r");
    if (!f) {
        printf("ERROR: Failed to open \"%s\".\n", fname);
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    size_t length = ftell(f);
    unsigned char *data = malloc(length+1);
    fseek(f, 0, SEEK_SET);
    if (!read_n_bytes(f, data, length)) {
        fclose(f);
        return NULL;
    }
    fclose(f);
    return data;
}


/* . */
bool
int32_underflow(int64_t a, int64_t b)
{
    int64_t c;
    assert(LLONG_MAX>INT_MAX);
    c = (int64_t)a-b;
    if (c < INT_MIN || c > INT_MAX) {
        return true;
    }
    return false;
}

/* . */
bool
int32_overflow(int64_t a, int64_t b)
{
    int64_t c;
    assert(LLONG_MAX>INT_MAX);
    c = (int64_t)a+b;
    if (c < INT_MIN || c > INT_MAX) {
        return true;
    }
    return false;
}

/* . */
int
round_to_multiple(bool roundUp, int numToRound, int multiple)
{
    if (multiple == 0) {
        return numToRound;
    }
    int remainder = numToRound % multiple;
    if (remainder == 0) {
        return numToRound;
    }

    if (numToRound < 0 && roundUp) {
        return numToRound - remainder;
    }
    if (roundUp) {
        return numToRound + multiple - remainder;
    }
    /* else round down */
    if (numToRound < 0 && !roundUp) {
        return numToRound - multiple - remainder;
    }
    return numToRound - remainder;
}

/* Formats each message with a timestamp. */
void
debug_message(const char *msg, ...)
{
    char buffer[MAX_STRING_LENGTH], fname[MAX_STRING_LENGTH];
    time_t t;
    struct tm* tm_info;
    sprintf(fname, "debug.log");
    FILE *f = fopen(fname, "a");
    if (!f) {
        printf("Failed to write to debug.log.");
        return;
    }
    t = time(NULL);
    tm_info = localtime(&t);
    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    fprintf(f, "%s ", buffer);

    va_list args;
    va_start(args, msg);
    vfprintf(f, msg, args);
    va_end(args);

    fprintf(f, "\n");
    fclose(f);
}

/* . */
bool
valid_file_format(char *fileName)
{
    if (emb_identify_format(fileName) >= 0) {
        return true;
    }
    return false;
}

/* . */
int
get_id(char *data[], char *label)
{
    int id;
    int n = table_length(data);
    for (id=0; id<n; id++) {
        if (string_equal(data[id], label)) {
            return id;
        }
    }
    return -1;
}

static int
emb_int_from_bytes(const char *program, int i)
{
    return 256*program[i] + program[i+1];
}

static EmbReal
emb_real_from_bytes(const char *program, int i)
{
    return DEFAULT_PLACE_VALUE * emb_int_from_bytes(program, i);
}

static EmbVector
emb_vector_from_bytes(const char *program, int i)
{
    EmbVector v;
    v.x = emb_real_from_bytes(program, i);
    v.y = emb_real_from_bytes(program, i+2);
    return v;
}

/* . */
int
get_int_tokens(EmbStack *stack, EmbStackElement *args, int n_tokens)
{
    int i;
    if (stack->position < n_tokens) {
        return 0;
    }

    for (i = 0; i < n_tokens; i++) {
        args[i] = stack->stack[stack->position-(2+i)];
        if (!token_is_int(args[i])) {
            return 0;
        }
    }

    stack_pop(stack);
    for (i = n_tokens-1; i >= 0; i++) {
        args[i] = stack_pop(stack);
    }
    return 1;
}

/* .
 */
int
process_stack_head(EmbStack *stack)
{
    EmbString token;
    EmbStackElement element = stack->stack[stack->position-1];
    EmbStackElement args[10];
    if (!element.attribute) {
        return 1;
    }
    switch (element.i) {
    /* 3.6.1 Stack */
    case PS_FUNC_DUP: {
        if (!get_int_tokens(stack, args, 1)) {
            break;
        }
        stack_push(stack, args[0].s);
        stack_push(stack, args[0].s);
        break;
    }
    case PS_FUNC_EXCH: {
        break;
    }
    case PS_FUNC_POP: {
        stack_pop(stack);
        break;
    }
    case PS_FUNC_COPY: {
        break;
    }
    case PS_FUNC_ROLL: {
        break;
    }
    case PS_FUNC_INDEX: {
        break;
    }
    case PS_FUNC_MARK: {
        break;
    }
    case PS_FUNC_CLEAR: {
        break;
    }
    case PS_FUNC_COUNT: {
        break;
    }
    case PS_FUNC_COUNTTOMARK: {
        break;
    }
    /* 3.6.2 Mathematical */
    case PS_FUNC_ADD: {
        if (!get_int_tokens(stack, args, 2)) {
            break;
        }
        sprintf(token, "%d", atoi(args[0].s) + atoi(args[1].s));
        stack_push(stack, token);
        break;
    }
    case PS_FUNC_SUB: {
        if (!get_int_tokens(stack, args, 2)) {
            break;
        }
        sprintf(token, "%d", atoi(args[0].s) - atoi(args[1].s));
        stack_push(stack, token);
        break;
    }
    case PS_FUNC_MUL: {
        if (!get_int_tokens(stack, args, 2)) {
            break;
        }
        sprintf(token, "%d", atoi(args[0].s) * atoi(args[1].s));
        stack_push(stack, token);
        break;
    }
    case PS_FUNC_DIV: {
        if (!get_int_tokens(stack, args, 2)) {
            break;
        }
        sprintf(token, "%f", atof(args[0].s) / atof(args[1].s));
        stack_push(stack, token);
        break;
    }
    case PS_FUNC_IDIV: {
        if (!get_int_tokens(stack, args, 2)) {
            break;
        }
        sprintf(token, "%d", atoi(args[0].s) / atoi(args[1].s));
        stack_push(stack, token);
        break;
    }
    case PS_FUNC_MOD: {
        if (!get_int_tokens(stack, args, 2)) {
            break;
        }
        sprintf(token, "%d", atoi(args[0].s) % atoi(args[1].s));
        stack_push(stack, token);
        break;
    }
    case PS_FUNC_ABS: {
        if (!get_int_tokens(stack, args, 1)) {
            break;
        }
        sprintf(token, "%d", abs(atoi(args[0].s)));
        stack_push(stack, token);
        break;
    }
    case PS_FUNC_NEG: {
        if (!get_int_tokens(stack, args, 1)) {
            break;
        }
        sprintf(token, "%d", -atoi(args[0].s));
        stack_push(stack, token);
        break;
    }
    case PS_FUNC_CEILING: {
        break;
    }
    case PS_FUNC_FLOOR: {
        break;
    }
    case PS_FUNC_ROUND: {
        break;
    }
    case PS_FUNC_TRUNCATE: {
        break;
    }
    case PS_FUNC_SQRT: {
        if (!get_int_tokens(stack, args, 1)) {
            break;
        }
        sprintf(token, "%f", sqrt(atof(args[0].s)));
        stack_push(stack, token);
        break;
    }
    case PS_FUNC_EXP: {
        if (!get_int_tokens(stack, args, 1)) {
            break;
        }
        sprintf(token, "%f", exp(atof(args[0].s)));
        stack_push(stack, token);
        break;
    }
    case PS_FUNC_LN: {
        break;
    }
    case PS_FUNC_LOG: {
        break;
    }
    case PS_FUNC_sin: {
        if (!get_int_tokens(stack, args, 1)) {
            break;
        }
        sprintf(token, "%f", sin(atof(args[0].s)));
        stack_push(stack, token);
        break;
    }
    case PS_FUNC_cos: {
        if (!get_int_tokens(stack, args, 1)) {
            break;
        }
        sprintf(token, "%f", cos(atof(args[0].s)));
        stack_push(stack, token);
        break;
    }
    case PS_FUNC_atan: {
        if (!get_int_tokens(stack, args, 1)) {
            break;
        }
        sprintf(token, "%f", atan(atof(args[0].s)));
        stack_push(stack, token);
        break;
    }
    case PS_FUNC_rand: {
        if (!get_int_tokens(stack, args, 1)) {
            break;
        }
        sprintf(token, "%d", rand());
        stack_push(stack, token);
        break;
    }
    case PS_FUNC_srand: {
        if (!get_int_tokens(stack, args, 1)) {
            break;
        }
        srand(atoi(args[0].s));
        break;
    }
    case PS_FUNC_rrand: {
        break;
    }
    /* 3.6.3 Array, Dictionary, String */
    case PS_FUNC_get: {
        break;
    }
    case PS_FUNC_put: {
        break;
    }
    case PS_FUNC_copy: {
        break;
    }
    case PS_FUNC_length: {
        break;
    }
    case PS_FUNC_getinterval: {
        break;
    }
    case PS_FUNC_putinterval: {
        break;
    }
    /*     Array-specific */
    case PS_FUNC_aload: {
        break;
    }
    case PS_FUNC_astore: {
        break;
    }
    case PS_FUNC_OPEN_SQ: {
        break;
    }
    case PS_FUNC_CLOSE_SQ: {
        break;
    }
    case PS_FUNC_setpacking: {
        break;
    }
    case PS_FUNC_currentpacking: {
        break;
    }
    /*     Dictionary-specific */
    case PS_FUNC_begin: {
        break;
    }
    case PS_FUNC_end: {
        break;
    }
    case PS_FUNC_def: {
        break;
    }
    case PS_FUNC_store: {
        break;
    }
    case PS_FUNC_load: {
        break;
    }
    case PS_FUNC_where: {
        break;
    }
    case PS_FUNC_countdictstack: {
        break;
    }
    case PS_FUNC_cleardictstack: {
        break;
    }
    case PS_FUNC_dictstack: {
        break;
    }
    case PS_FUNC_known: {
        break;
    }
    case PS_FUNC_maxlength: {
        break;
    }
    case PS_FUNC_undef: {
        break;
    }
    case PS_FUNC_left_arrow: {
        break;
    }
    case PS_FUNC_right_arrow: {
        break;
    }
    /*     String-specific */
    case PS_FUNC_search: {
        break;
    }
    case PS_FUNC_anchorsearch: {
        break;
    }
    case PS_FUNC_token: {
        break;
    }
    /* 3.6.4 Boolean */
    case PS_FUNC_eq: {
        if (!get_int_tokens(stack, args, 2)) {
            break;
        }
        break;
    }
    case PS_FUNC_ne: {
        if (!get_int_tokens(stack, args, 2)) {
            break;
        }
        break;
    }
    case PS_FUNC_gt: {
        if (!get_int_tokens(stack, args, 2)) {
            break;
        }
        break;
    }
    case PS_FUNC_ge: {
        if (!get_int_tokens(stack, args, 2)) {
            break;
        }
        break;
    }
    case PS_FUNC_le: {
        if (!get_int_tokens(stack, args, 2)) {
            break;
        }
        break;
    }
    case PS_FUNC_lt: {
        if (!get_int_tokens(stack, args, 2)) {
            break;
        }
        break;
    }
    case PS_FUNC_and: {
        if (!get_int_tokens(stack, args, 2)) {
            break;
        }
        break;
    }
    case PS_FUNC_or: {
        if (!get_int_tokens(stack, args, 2)) {
            break;
        }
        break;
    }
    case PS_FUNC_xor: {
        if (!get_int_tokens(stack, args, 2)) {
            break;
        }
        break;
    }
    case PS_FUNC_true: {
        break;
    }
    case PS_FUNC_false: {
        break;
    }
    case PS_FUNC_not: {
        break;
    }
    /* 3.6.5 Control */
    case PS_FUNC_if: {
        break;
    }
    case PS_FUNC_ifelse: {
        break;
    }
    case PS_FUNC_exec: {
        break;
    }
    case PS_FUNC_for: {
        break;
    }
    case PS_FUNC_repeat: {
        break;
    }
    case PS_FUNC_loop: {
        break;
    }
    case PS_FUNC_forall: {
        break;
    }
    case PS_FUNC_exit: {
        break;
    }
    case PS_FUNC_countexecstack: {
        break;
    }
    case PS_FUNC_execstack: {
        break;
    }
    case PS_FUNC_stop: {
        break;
    }
    /* 3.6.6 Type */
    case PS_FUNC_type: {
        break;
    }
    case PS_FUNC_xcheck: {
        break;
    }
    case PS_FUNC_rcheck: {
        break;
    }
    case PS_FUNC_wcheck: {
        break;
    }
    case PS_FUNC_cvlit: {
        break;
    }
    case PS_FUNC_cvx: {
        break;
    }
    case PS_FUNC_readonly: {
        break;
    }
    case PS_FUNC_executeonly: {
        break;
    }
    case PS_FUNC_noaccess: {
        break;
    }
    case PS_FUNC_cvi: {
        break;
    }
    case PS_FUNC_cvr: {
        break;
    }
    case PS_FUNC_cvn: {
        break;
    }
    case PS_FUNC_cvs: {
        break;
    }
    case PS_FUNC_cvrs: {
        break;
    }
    /* 3.7.1 Memory */
    case PS_FUNC_array: {
        break;
    }
    case PS_FUNC_packedarray: {
        break;
    }
    case PS_FUNC_dict: {
        break;
    }
    case PS_FUNC_string: {
        break;
    }
    case PS_FUNC_gstate:  {
        break;
    }
    /* 3.7.2 VM */
    case PS_FUNC_save:  {
        break;
    }
    case PS_FUNC_restore:  {
        break;
    }
    case PS_FUNC_gcheck:  {
        break;
    }
    default: {
        printf("ERROR: Postscript built-in %d not indexed.\n", element.i);
        break;
    }
    }
    return 0;
}

/* .
 */
void
execute_postscript(EmbStack *stack, char line[200])
{
    queue_token_list(stack, line);
    analyse_stack(stack);
}

/* .
 */
int
emb_repl(void)
{
    EmbStack stack;
    stack.position = 0;

    puts("embroider 1.0.0-alpha");
    puts("    Copyright 2018-2024 The Embroidermodder Team.");
    puts("    Licensed under the terms of the zlib license.");
    puts("");
    puts("    https://www.libembroidery.org");
    puts("");
    puts("                             WARNING");
    puts("-----------------------------------------------------------------------");
    puts("    embroider is under active development and is not yet");
    puts("    ready for any serious use. Please only use in experimental contexts");
    puts("    not as part of your general workflow.");
    puts("");
    puts("    This interpreter has only just been started, try using the");
    puts("    --help flag for other features.");
    puts("-----------------------------------------------------------------------");
    puts("");

    int running = 1;
    while (running) {
        char line[200];
        int i = 0;
        int c = 0;
        printf("emb> ");
        while (c != EOF) {
            c = fgetc(stdin);
            /* Any non-printable character breaks the "getting characters from
             * the terminal loop".
             */
            if ((c < 0x20) || (c >= 0x80)) {
                break;
            }
            line[i] = c;
            i++;
            if (i == 200) {
                puts("Error: input line too long, please break up your command.");
            }
        }
        line[i] = 0;
        execute_postscript(&stack, line);
        if (!strcmp(line, "quit")) {
            running = 0;
        }
    }
    return 0;
}


/* Our virtual machine
 * -------------------
 *
 * Program state is altered via this function, all other functions
 * pass the program state back and forth to keep it thread-safe.
 *
 * Variables are packed into and removed from this state, the stack is embedded
 * into it. To manage memory each stack item names its successor, or is a negative
 * number indicating that the stack terminates there.
 *
 * DATA TYPE FLAG
 * --------------
 *
 * STRING (any value <=100): which is also the length of the string.
 * INT (101): integer in the range (-32767, 32767).
 * REAL (102): fixed-point real number in the range (-3276.7, 3276.7).
 * FUNCTION (103): interpret the data as an index in the predefined function
 *                 table.
 * VARIABLE (104): reference to memory location outside of the stack.
 *
 * EXAMPLE STACK
 * -------------
 *
 * Stack element 0:
 *     description: (3, BYTE, "a")
 *     literally: {3, , 97}
 *
 * Stack element 1:
 *     description: (6, BYTE, 0)
 *     literally: {6, 0, 0}
 *
 * Stack element 2:
 *     description: (10, REAL, 21.1)
 *     literally: {10, 1, 0, 211}
 *
 * Stack element 3:
 *     description: (-1, REAL, 32.1)
 *     literally: {-1, 1, 1, 55}
 *
 * Altogether, this stack is: ("a", 21.1, 32.1)
 * Literally: {3, 0, 97, 6, 0, 0
 *
 * In order to ensure that the processor is running correctly, each processor
 * call can be alternated with a full stack analysis printout that looks like
 * this.
 */
void
emb_processor(char *state, const char *program, int program_length)
{
    int i;
    printf("state: %s\n", state);
    for (i=0; i<program_length; i++) {
        switch (program[i]) {
        case EMB_CMD_ARC: {
            if (focussed_pattern == NULL) {
                puts("ERROR: there is no focussed pattern, so the arc command cannot be run.");
                return;
            }
            EmbVector p1 = emb_vector_from_bytes(program, i+1);
            EmbVector p2 = emb_vector_from_bytes(program, i+5);
            EmbArc arc;
            arc.start = p1;
            arc.end = p2;
            embPattern_addArc(focussed_pattern, arc);

            i += 8;
            break;
        }
        case EMB_CMD_CIRCLE: {
            if (focussed_pattern == NULL) {
                puts("ERROR: there is no focussed pattern, so the circle command cannot be run.");
                return;
            }
            EmbVector center = emb_vector_from_bytes(program, i+1);
            EmbReal r = emb_real_from_bytes(program, i+5);
            printf("%f %f", center.x, r);

            i += 6;
            break;
        }
        default: {
            puts("Program command not defined.");
            break;
        }
        }
    }
}

/*
 *
 */
void
emb_postscript_compiler(const char *program, char *compiled_program)
{
    strcpy(compiled_program, program);
}

/* The actuator works by creating an on-the-fly EmbProgramState so external
 * callers don't have to manage memory over longer sessions.
 *
 * It also compiles down our command line arguments, postscript and SVG
 * defines etc. into a common "machine code" like program.
 */
int
emb_compiler(const char *program, int language, char *compiled_program)
{
    int i = 0;
    int output_length = 0;
    compiled_program[i] = 0;
    switch (language) {
    case LANG_PS: {
        emb_postscript_compiler(program, compiled_program);
        break;
    }
    default: {
        break;
    }
    }
    return output_length;
}

/* Calls the compiler, then runs the compiled program. */
void
emb_actuator(EmbPattern *pattern, const char *program, int language)
{
    printf("%p\n", pattern);
    char *state = malloc(1000);
    char *compiled_program = malloc(1000);
    int output_length = emb_compiler(program, language, compiled_program);
    emb_processor(state, compiled_program, output_length);
    safe_free(compiled_program);
    safe_free(state);
}

/*! Create the ScriptValue tree to be used for this pattern.
 */
ScriptValue *
emb_create_root(void)
{
    ScriptValue* root = (ScriptValue*)malloc(sizeof(ScriptValue));
    root->type = EMB_DATATYPE_ROOT;
    strcpy(root->label, "root");
    strcpy(root->s, "NULL");
    root->leaves = (ScriptValue*)malloc(sizeof(ScriptValue) * CHUNK_SIZE);
    root->n_leaves = 0;
    root->max_leaves = CHUNK_SIZE;
    return root;
}

/*! Add an ScriptValue as a leaf by describing it using a datatype, label for
 * finding it and the data value as a C string.
 */
int
emb_create_leaf(ScriptValue *branch, int type, char *label, char *data)
{
    int n = branch->n_leaves;
    if (n + 1 >= branch->max_leaves) {
        branch->max_leaves += CHUNK_SIZE;
        size_t new_size = branch->max_leaves * sizeof(ScriptValue);
        branch->leaves = (ScriptValue *)realloc(branch->leaves, new_size);
    }
    branch->n_leaves++;

    ScriptValue *leaf = branch->leaves + n;
    leaf->type = type;
    strcpy(leaf->label, label);
    strcpy(leaf->s, data);
    leaf->n_leaves = 0;
    leaf->max_leaves = 0;

    switch (type) {
    case EMB_DATATYPE_DICT:
    case EMB_DATATYPE_ARRAY: {
        size_t size = sizeof(ScriptValue) * CHUNK_SIZE;
        leaf->leaves = (ScriptValue*)malloc(size);
        leaf->max_leaves = 10;
        break;
    }
    case EMB_DATATYPE_INT: {
        leaf->i = atoi(data);
        break;
    }
    case EMB_DATATYPE_REAL: {
        leaf->r = atof(data);
        break;
    }
    default:
        break;
    }
    return 1;
}

/*! \brief Recursively find the leaf within a tree matching a given key.
 *
 * First identify the leftmost chunk in dot chain, for example:
 *
 *     emb_find_leaf(branch, "collection.entry")
 *
 * After step one chunk will contain "collection", first_dot will be 10,
 * so then the recursion is like this:
 *
 *     emb_find_leaf(branch->leaves + i, "collection.entry" + first_dot + 1)
 *
 * That is: `emb_find_leaf(match, "entry")`.
 */
ScriptValue *
emb_find_leaf(ScriptValue *branch, char *key)
{
    int i;
    EmbString chunk;
    int first_dot;

    /* Step one: check for dot operator, extract leftmost chunk. */
    first_dot = -1;
    strncpy(chunk, key, MAX_STRING_LENGTH-1);
    for (i=0; key[i]; i++) {
        if (key[i] == '.') {
            chunk[i] = 0;
            first_dot = i;
            break;
        }
    }

    /* Step two: loop for the first match of the chunk in the label entry. */
    for (i=0; i<branch->n_leaves; i++) {
        printf("(%d, %s)\n", i, branch->leaves[i].label);
        if (strncmp(branch->leaves[i].label, chunk, MAX_STRING_LENGTH-1)) {
            if (first_dot < 0) {
                /* We're at the end of a chain here, so don't recurse. */
                return branch->leaves + i;
            }
            return emb_find_leaf(branch->leaves + i, key + first_dot + 1);
        }
    }

    /* Failure condition. No match found. */
    return NULL;
}

/*! Recursively free our tree.
 */
void
emb_free_root(ScriptValue *root)
{
    switch (root->type) {
    case EMB_DATATYPE_DICT:
    case EMB_DATATYPE_ARRAY: {
        free(root->leaves);
        free(root);
        break;
    }
    case EMB_DATATYPE_ROOT: {
        free(root);
        break;
    }
    case EMB_DATATYPE_NULL: {
        puts("Error: DATATYPE_NULL");
        break;
    }
    default:
        break;
    }
}

/* Recursively print our tree.
 */
void
emb_print_tree(ScriptValue *tree, int indent)
{
    switch (tree->type) {
    case EMB_DATATYPE_ROOT:
    case EMB_DATATYPE_DICT:
    case EMB_DATATYPE_ARRAY: {
        int i;
        for (i=0; i<tree->n_leaves; i++) {
            emb_print_tree(tree->leaves + i, indent+1);
        }
        break;
    }
    case EMB_DATATYPE_STR: {
        printf("%*c%s: \"%s\"\n", indent, ' ', tree->label, tree->s);
        break;
    }
    case EMB_DATATYPE_INT: {
        printf("%*c%s: %d\n", indent, ' ', tree->label, tree->i);
        break;
    }
    case EMB_DATATYPE_REAL: {
        printf("%*c%s: %f\n", indent, ' ', tree->label, tree->r);
        break;
    }
    default:
        break;
    }
}

