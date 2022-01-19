/*
 * This file is part of libembroidery.
 *
 * Copyright 2021 The Embroidermodder Team
 * Distributed under the terms of the zlib license (see LICENSE).
 *
 * ----------------------------------------------------------------
 *
 * GAS assembly comments are C-style.
 * The .S extension means "run through C preprocessor first".
 *
 * x86 is little endian, so all the write functions only
 * reverse big endian ints.
 */

#define __LIBEMBROIDERY_ASM__ 1
#include "embroidery.h"

/* Linux system defines
 * --------------------
 */
#define SYS_EXIT		1
#define SYS_READ		3
#define SYS_WRITE		4
#define SYS_OPEN		5
#define SYS_CLOSE		6
#define SYS_CREAT		8
#define SYS_LINK		9
#define SYS_UNLINK		10
#define SYS_TIME		13
#define SYS_STAT		18
#define STDOUT			1
#define SUCCESS			0

/* #define SYS_MKDIR ?*/

#define MAX_STRING_LENGTH	1024

		.data

welcome_message:
	.ascii "EMBROIDER EMBEDDED VERSION 0.1\n\n"
	.ascii "    Copyright 2021 The Embroidermodder Team\n"
	.ascii "    Licensed under the zlib license.\n"
	.ascii "    Please refer to the manual, included in your download,\n"
	.ascii "    for help on usage. If you do not have a copy visit:\n"
	.ascii "		https://embroidermodder.org\n\n"
	.equ welcome_message_len, . - welcome_message

emb_factorial:
	.float	1.0
	.float	1.0
	.float	2.0
	.float	6.0
	.float	24.0
	.float	120.0
	.float	720.0
	.float	5040.0
	.float	40320.0
	.float	362880.0
	.float	3628800.0

error_code:
	.long	0

length:
	.long	1
dot:
	.ascii	"."

file_pointer:
	.long	0

buffer:
	.long	0

buffer_length:
	.long	0

random_state:
	.long	37

black:
	.byte	0, 0, 0

/*
int memory[100]
EmbArray arrays[100]
EmbPattern patterns[3]
int memory_files = 0
int active_patterns = 0
*/

/*******************************************************************************
 * CODE SECTION
 */
	.text

.globl _start
_start:
	pushl	%ebp
	movl	$welcome_message_len, %edx
	movl	$welcome_message, %ecx
	movl	$STDOUT, %ebx
	call	write

	movl	$STDOUT, %ebx
	movl	$20, (length)
	call	file_pad_spaces

	movl	$0, %ebx
	movl	$SYS_EXIT, %eax
	int	$0x80
	leave
	ret


/*
 * syscall(SYS_WRITE, f, &b, n)
 */
write:
	movl	$SYS_WRITE, %eax
	int	$0x80
	ret


/*
 * syscall(SYS_WRITE, f, &b, 4)
 */
binary_write_int:
	movl	$4, (buffer_length)
	call	write
	ret


/*
 * syscall(SYS_WRITE, f, &b, 2)
 */
binary_write_short:
	movl	$2, (buffer_length)
	call	write
	ret

	.set	binary_write_float, binary_write_int
	.set	binary_write_uint, binary_write_int
	.set	binary_write_ushort, binary_write_short


/*
 * syscall(SYS_READ, f, &b, 1)
 */
/* (int f) returns b */
/* char b
 * fread(&b, 1, 1, f)
 * return b */
binary_read_byte:
	ret


/*
 * syscall(SYS_READ, f, &b, 1)
 */
binary_read_bytes:
	/* (int f, char *s, int n) returns char */
	/* fread(s, 1, n, f) */
	ret

	.set	binary_read_uint8, binary_read_byte


binary_read_float:
	/* (int f) returns float fl */
	/* float fl
	fread(&fl, 4, 1, f)
	return fl */
	ret


bit:
	/* (unsigned char a, int n) returns int */
	/* return ((a & (1 << n)) / (1 << n)) */
	ret


emb_min_int:
	/* (int a, int b) returns int */
	/* if (a<b) return a
	return b */
	ret


emb_max_int:
	/* (int a, int b) returns int */
	/* if (a>b) return a
	return b */
	ret


/* (float a, float b) return float
 * if (a<b) return a
 * return b
 */
emb_min_float:
	ret


/* (float a, float b) return float
 * if (a>b) return a
 * return b
 */
emb_max_float:
	ret


/* (float a) return float
 * if a<0.0: return -a
 * return a
 */
emb_fabs:
	ret


/* Gives the absolute value of the argument.
 *
 * emb_abs takes argument on %eax returns on %eax.
 */
emb_abs:
	cmp	$0, %eax
	jl	emb_abs_positive
	subl	$0, %eax
emb_abs_positive:
	ret


/* Linear something RNG, need to look up better constants
 * all possible outputs happen (1, 999), one at a time.
 * Not 0, so the result is offset.
 *
 * Note that gcd(37, 1000) = gcd(39, 1000) = 1.
 *
 * Returns state in random_state as well as %eax.
 */
random_int:
	movl	(random_state), %eax
	movl	$39, %ebx
	movl	$1000, %ebx
	mul	%ebx
	div	%ecx
	movl	%eax, (random_state)
	/* sub	$1, (random_state) */
	ret


/* Babylonian square root algorithm.
 * NEEDS TEST IN THE TEST SUITE.
 *
 * (float a) return float
 */
emb_sqrt:
	/*
	int i
	float b, epsilon
	epsilon = 0.0001
	b = 1.0
	for (i=0; i<20; i++) {
		b = 0.5*(b+a/b)
	}
	if (emb_fabs(a-b*b) > epsilon) {
		print_log_string(error_emb_sqrt)
	}
	return b
	*/
	ret


/* integer power for the taylor series.
 *
 * (float a, int n) returns float
 */
emb_pow:
	/*
	int i
	float b
	b = a
	if (n==0) return 1.0
	for (i=0; i<n-1; i++) {
		b *= a
	}
	return b
	*/
	ret


/* Taylor series sine algorithm.
 *
 * (float a) returns float
 */
emb_sin:
	/*
	int i, sign
	float b
	b = 0.0
	sign = 1
	for (i=0; i<5; i++) {
		b += sign*emb_pow(a, 2*i+1)/emb_factorial[2*i+1]
		sign *= -1
	}
	return b
	*/
	ret


/* Taylor series cosine algorithm.
 *
 * (float a) returns float
 */
emb_cos:
	/*
	int i, sign
	float b
	b = 0.0
	sign = 1
	for (i=0; i<5; i++) {
		b += sign*emb_pow(a, 2*i)/emb_factorial[2*i]
		sign *= -1
	}
	return b
	*/
	ret


/* Euler's series for arctan.
 * (See Utility Functions section of the manual.)
 *
 * (float y, float x) returns float
 */
emb_atan2:
	/*
	int i
	float a, t, epsilon, coeff
	epsilon = 0.0001
	if (x>epsilon) {
		a = y/(emb_sqrt(x*x+y*y)+x)
		t = 0.0
		coeff = 1.0
		for (i=0; i<20; i++) {
			if (i>0) {
				coeff *= 4.0 * i
				coeff /= (2*i)*(2*i+1)
			}
			t += coeff*(emb_pow(a, 2*i+1)/emb_pow(1+a*a, i+1))
		}
		return 2*t
	}
	if (y>epsilon) {
		return 0.5*3.141592 - emb_atan2(x, y)
	}
	if (y<epsilon) {
		return -0.5*3.141592 - emb_atan2(x, y)
	}
	if (x<epsilon) {
		return 3.141592 + emb_atan2(y, x)
	}
	print_log_string(error_emb_atan2)
	call	print_log_string
	return 0.0
	*/
	ret


/* (int p) returns int */
dereference_int:
	/*
	int out
	fseek(datafile, p, SEEK_SET)
	fread(&out, 4, 1, datafile)
	return out
	*/
	ret


/* int table, int entry returns int */
double_dereference_int:
	/*
	int out
	out = dereference_int(table)
	out = dereference_int(out+4*entry)
	return out
	*/
	ret


/*
 * These use void * so the sign of the char array has no effect
 * as they are cast to char * internally.
 *
 * (void *ptr, int p, int length)
 */
memory_set:
	/*
	int i
	for (i=0; i<length; i++) {
		((char *)ptr)[i] = p
	}
	*/
	ret


/* (char *s, int p) returns int
 */
get_str:
	/*
	int i
	fseek(datafile, p, SEEK_SET)
	for (i=0; i<MAX_STRING_LENGTH; i++) {
		fread(s+i, 1, 1, datafile)
		if (!s[i]) {
			return 1
		}
	}
	return 0
	*/
	ret


/*
 * (const char *a) returns int
 */
string_length:
	/*
	int i
	for (i=0; i<MAX_STRING_LENGTH; i++) {
		if (((char*)a)[i] == 0) {
			return i
		}
	}
	return MAX_STRING_LENGTH
	*/
	ret


/* 
 * (const void *a, const void *b) return int
 */
string_equal:
	/*
	int i
	for (i=0; i< MAX_STRING_LENGTH; i++) {
		if (((char*)a)[i] != ((char*)b)[i]) {
			return 0
		}
		if (!((char*)a)[i]) {
			break
		}
	}
	if (!((char*)b)[i] && i < MAX_STRING_LENGTH) {
		return 1
	}
	return 0
	*/
	ret


/*
 * (void *a, const void *b, int length) returns nothing
 */
memory_copy:
	/*
	int i
	length = emb_min_int(length, MAX_STRING_LENGTH)
	for (i=0; i<length; i++) {
		((char *)a)[i] = ((const char *)b)[i]
	}
	*/
	ret


/*
 * (char *a, const char *b) returns nothing
 */
string_copy:
	/*
	memory_copy(a, b, string_length(b))
	((char *)a)[string_length(b)] = 0
	*/
	ret


/* TODO: find and analyse some HUS encoded files and DST equivalents
 *
 * (int input, int output, int compressionType) return int
 */
husExpand:
	ret


/* TODO: find and analyse some HUS encoded files and DST equivalents
 *
 * (int input, int output, int compressionType) returns int
 */
husCompress:
	ret


/* (int file, void* data, int bytes) returns int
 */
embFile_readInt:
	/* fread(data, 1, bytes, file) */
	ret


/* (int file, void* data, int bytes)
 */
embFile_readInt_be:
	/*
	char *a = (char*)data, c
	fread(data, 1, bytes, file)
	if (bytes==2) {
		c = a[0]
		a[0] = a[1]
		a[1] = c
	}
	else {
		c = a[0]
		a[0] = a[3]
		a[3] = c
		c = a[1]
		a[1] = a[2]
		a[2] = c
	}
	*/
	ret


#if 0
fwriteInt(int file, void* data, int bytes):
	fwrite(data, bytes, 1, file)
	ret


fwriteInt_be(int file, void* data, int bytes):
	char *a = (char *)data, c
	if (bytes==2) {
		c = a[0]
		a[0] = a[1]
		a[1] = c
	}
	else {
		c = a[0]
		a[0] = a[3]
		a[3] = c
		c = a[1]
		a[1] = a[2]
		a[2] = c
	}
	fwrite(a, 1, bytes, file)
	ret


/* (int file, char* buffer, int maxLength) */
binaryReadString:
	/*
	int i
	for (i=0; i < maxLength; i++) {
		fread(buffer+i, 1, 1, file)
		if (!buffer[i])
			break
	}
	*/
	ret


/* (float src) return int */
emb_ceil:
	return (int)(src)+1
	ret


/* (float src) return int */
emb_floor:
	return (int)(src)
	ret


/* Rounds a float (src) and returns it as an int.
 *
 * We assume that the source is within.
 *
 * (float src) return int */
round:
	if (src < 0.0) {
		return emb_ceil(src - 0.5)
	}
	return emb_floor(src + 0.5)
	ret


embTime_initNow(EmbTime* t):
#if ARDUINO
/*TODO: arduino embTime_initNow */
#else
	time_t rawtime
	struct tm* timeinfo
	time(&rawtime)
	timeinfo = localtime(&rawtime)

	t->year = timeinfo->tm_year
	t->month = timeinfo->tm_mon
	t->day = timeinfo->tm_mday
	t->hour = timeinfo->tm_hour
	t->minute = timeinfo->tm_min
	t->second = timeinfo->tm_sec
#endif /* ARDUINO */
	ret


EmbTime embTime_time(EmbTime* t):
#if ARDUINO
/*TODO: arduino embTime_time */
#else

	int divideByZero = 0
	divideByZero = divideByZero / divideByZero
	/*TODO: wrap time() from time.h and verify it works consistently */

#endif /* ARDUINO */
	return *t
	ret


/* Converts a 6 digit hex string (I.E. "00FF00") into an
 * EmbColor and returns it. */
EmbColor embColor_fromHexStr(char* val):
	int i
	EmbColor color
	for (i = 0; i < 6; i++) {
		if (val[i] >= 'A' && val[i] <= 'F') {
			val[i] = '9' + val[i] - 'A' + 1
		}
		val[i] -= '0'
	}

	color.r = val[0] * 16 + val[1]
	color.g = val[2] * 16 + val[3]
	color.b = val[4] * 16 + val[5]
	return color
	ret


int emb_array_to_int(char* buffer):
	int result
	result = 0
	for (; *buffer; buffer++) {
		if (*buffer >= '0' && *buffer <= '9') {
			result = 10*result + *buffer - '0'
		}
	}
	return result
	ret


float emb_array_to_float(char* buffer):
	float result
	int offset
	int decimal_places
	decimal_places = 0
	result = 0.0
	for (offset=0; buffer[offset]; offset++) {
		if (buffer[offset] >= '0' && buffer[offset] <= '9') {
			result = 1.0*(10*result + buffer[offset] - '0')
		}
		decimal_places++
		if (buffer[offset] == '.') {
			decimal_places = 0
		}
	}
	return result / emb_pow(10.0, decimal_places)
	ret


/* Replacing the %d in *printf functionality.
 *
 * Accounts for the sign of the 
 */
emb_int_to_array(char* buffer, int number, int maxDigits):
	int i, j, sign
	unsigned int unumber
	sign = 0
	unumber = number
	if (number < 0.0) {
		unumber = -number
		sign = 1
	}
	for (i = 0; i < maxDigits - 2; i++) {
		buffer[i] = ' '
	}
	buffer[maxDigits - 1] = 0
	for (i = maxDigits - 2; i >= 0; i--) {
		buffer[i] = (char)(unumber % 10) + '0'
		unumber = unumber / 10
		if (unumber == 0)
			break
	}
	if (sign) {
		buffer[i] = '-'
	}
	/* left shift to the front of the buffer so the buffer doesn't change
	 * size in later use
	 */
	for (j = 0; j < maxDigits - i; j++) {
		buffer[j] = buffer[i + j]
	}
	ret


writeInt(int file, int n, int m):
	char buffer[30]
	emb_int_to_array(buffer, n, m)
	embFile_print(file, buffer)
	ret


/* Replacing the %f in *printf functionality.
 */
emb_float_to_array(char* buffer, float number, float tolerance, int before, int after):
	int i, maxDigits, j
	float t
	float afterPos[] = { 1.0e-1, 1.0e-2, 1.0e-3, 1.0e-4, 1.0e-5, 1.0e-6, 1.0e-7, 1.0e-8 }
	float beforePos[] = { 1.0, 1.0e1, 1.0e2, 1.0e3, 1.0e4, 1.0e5, 1.0e6, 1.0e7, 1.0e8 }
	maxDigits = before + after + 1
	for (i = 0; i < maxDigits - 1; i++) {
		buffer[i] = ' '
	}
	buffer[maxDigits - 1] = 0
	for (i = before - 1; i >= 0; i--) {
		t = 0.0
		for (j = 0; j < 9; j++) {
			t += beforePos[i]
			if ((number - tolerance > t) && (t + beforePos[i] > number + tolerance)) {
				buffer[before - 1 - i] = j + '1'
				number -= (j + 1) * beforePos[i]
				break
			}
		}
	}
	buffer[before] = '.'
	for (i = 0; i < after; i++) {
		t = 0.0
		for (j = 0; j < 9; j++) {
			t += afterPos[i]
			if ((number - tolerance > t) && (t + afterPos[i] > number + tolerance)) {
				buffer[before + 1 + i] = j + '1'
				number -= (j + 1) * afterPos[i]
				break
			}
		}
	}
	buffer[before + 1 + after] = 0
	/* lTrim(buffer, ' '); */
	ret


/* puts() abstraction. Uses Serial.print() on ARDUINO */
embLog:
	/* (const char* str) */
	write(1, str, string_length(str))
	write(1, "\n", 1)
	ret


embConstantPi:
	3.1415926535

radians:
	/* (float degree) returns float */
	return degree * embConstantPi / 180.0
	ret


degrees:
	/* (float radian) returns float */
	return radian * 180.0 / embConstantPi
	ret


/* Calculus based approach at determining whether a polygon is clockwise or counterclockwise.
 * Returns true if arc is clockwise.
 */
isArcClockwise:
	/* (EmbArc arc) returns char */
	float edge1 = (arc.mid.x - arc.start.x) * (arc.mid.y + arc.start.y)
	float edge2 = (arc.end.x - arc.mid.x) * (arc.end.y + arc.mid.y)
	float edge3 = (arc.start.x - arc.end.x) * (arc.start.y + arc.end.y)
	if (edge1 + edge2 + edge3 >= 0.0) {
		return 1
	}
	return 0
	ret


/* Calculates the CenterPoint of the Arc */
getArcCenter:
	/* (EmbArc arc, EmbVector* arcCenter) */
	EmbVector a, b, pa, pb
	EmbLine line1, line2
	embVector_subtract(arc.mid, arc.start, &a)
	embVector_average(arc.mid, arc.start, &(line1.start))
	embVector_normalVector(a, &pa, 0)
	embVector_add(line1.start, pa, &(line1.end))

	embVector_subtract(arc.end, arc.mid, &b)
	embVector_average(arc.end, arc.mid, &(line2.start))
	embVector_normalVector(b, &pb, 0)
	embVector_add(line2.start, pb, &(line2.end))

	embLine_intersectionPoint(line1, line2, arcCenter)
	ret


/* Calculates Arc Geometry from Bulge Data.
 * Returns false if there was an error calculating the data.
 */
getArcDataFromBulge:
	/*
	(float bulge, EmbArc* arc, EmbVector* arcCenter,
	float* radius, float* diameter, float* chord,
	EmbVector* chordMid,
	float* sagitta, float* apothem,
	float* incAngleInDegrees, char* clockwise)
	returns char
	*/
	EmbVector f, diff
	float incAngleInRadians
	float chordAngleInRadians
	float sagittaAngleInRadians

	if (bulge >= 0.0) {
		*clockwise = 0
	} else {
		*clockwise = 1
	}

	/* Calculate the Included Angle in Radians */
	incAngleInRadians = emb_atan2(bulge, 1.0) * 4.0

	embVector_subtract(arc->end, arc->start, &diff)
	*chord = embVector_getLength(diff)

	*radius = emb_fabs(*chord / (2.0 * emb_sin(incAngleInRadians / 2.0)))
	*diameter = *radius * 2.0
	*sagitta = emb_fabs((*chord / 2.0) * bulge)
	*apothem = emb_fabs(*radius - *sagitta)

	embVector_average(arc->start, arc->end, chordMid)

	chordAngleInRadians = emb_atan2(diff.y, diff.x)

	if (*clockwise) {
		sagittaAngleInRadians = chordAngleInRadians + radians(90.0)
	} else {
		sagittaAngleInRadians = chordAngleInRadians - radians(90.0)
	}

	f.x = *sagitta * emb_cos(sagittaAngleInRadians)
	f.y = *sagitta * emb_sin(sagittaAngleInRadians)
	embVector_add(*chordMid, f, &(arc->mid))

	getArcCenter(*arc, arcCenter)

	*incAngleInDegrees = degrees(incAngleInRadians)

	/* Confirm the direction of the Arc, it should match the Bulge */
	if (*clockwise != isArcClockwise(*arc)) {
		print_log_string(error_arc_data)
		return 0
	}

	return 1
	ret
#endif

/****************************************************************
 * Calculates the intersection points of two overlapping circles.
 * Returns true if the circles intersect.
 * Returns false if the circles do not intersect.
 *
 * (EmbCircle c0, EmbCircle c1, EmbVector* p3, EmbVector* p4)
 * returns int 
 ****************************************************************/
getCircleCircleIntersections:
#if 0
	EmbVector diff, p2, m
	float a, h, d
	embVector_subtract(c1.center, c0.center, &diff)
	d = embVector_getLength(diff); /* Distance between centers */

/* Circles share centers. This results in division by zero,
 * infinite solutions or one circle being contained within the other.
 */
	if (d == 0.0) {
		return 0
	}
	/* Circles do not touch each other */
	else if (d > (c0.radius + c1.radius)) {
		return 0
	}
	/* One circle is contained within the other */
	else if (d < (c0.radius - c1.radius)) {
		return 0
	}

/*
 * Considering the two right triangles p0p2p3 and p1p2p3 we can write:
 * a^2 + h^2 = r0^2 and b^2 + h^2 = r1^2
 *
 * BEGIN PROOF
	 *
	 * Remove h^2 from the equation by setting them equal to themselves:
	 *     r0^2 - a^2 = r1^2 - b^2
	 * Substitute b with (d - a) since it is proven that d = a + b:
	 *     r0^2 - a^2 = r1^2 - (d - a)^2
	 * Complete the square:
	 *     r0^2 - a^2 = r1^2 - (d^2 -2da + a^2)
	 * Subtract r1^2 from both sides:
	 *     r0^2 - r1^2 - a^2 = -(d^2 -2da + a^2)
	 * Invert the signs:
	 *     r0^2 - r1^2 - a^2 = -d^2 + 2da - a^2
	 * Adding a^2 to each side cancels them out:
	 *     r0^2 - r1^2 = -d^2 + 2da
	 * Add d^2 to both sides to shift it to the other side:
	 *     r0^2 - r1^2 + d^2 = 2da
	 * Divide by 2d to finally solve for a:
	 *     a = (r0^2 - r1^2 + d^2)/ (2d)
	 *
	 * END PROOF
	 */

	a = ((c0.radius * c0.radius) - (c1.radius * c1.radius) + (d * d)) / (2.0 * d)
	/* Solve for h by substituting a into a^2 + h^2 = r0^2 */
	h = emb_sqrt((c0.radius * c0.radius) - (a * a))

	/*Find point p2 by adding the a offset in relation to line d to point p0 */

	embVector_multiply(diff, a / d, &p2)
	embVector_add(c0.center, p2, &p2)

/* Tangent circles have only one intersection
 *
 * TODO: using == in floating point arithmetic
 * doesn't account for the machine accuracy, having
 * a stated (float) tolerance value would help.
 */
	if (d == (c0.radius + c1.radius)) {
		*p3 = *p4 = p2
		return 1
	}

/* Get the perpendicular slope by multiplying by the negative reciprocal
 * Then multiply by the h offset in relation to d to get the actual offsets 
 */
	m.x = -(diff.y * h / d)
	m.y = (diff.x * h / d)

/* Add the offsets to point p2 to obtain the intersection points */
	embVector_add(p2, m, p3)
	embVector_subtract(p2, m, p4)

	return 1
	ret


/****************************************************************
 * Calculates the tangent points on circle from a given point.
 * Returns true if the given point lies outside the circle.
 * Returns false if the given point is inside the circle.
 ****************************************************************/
int getCircleTangentPoints(EmbCircle c, EmbVector point, EmbVector* t0, EmbVector* t1):
	EmbCircle p
	EmbVector diff
	float hyp
	embVector_subtract(point, c.center, &diff)
	hyp = embVector_getLength(diff); /* Distance to center of circle */

	/* Point is inside the circle */
	if (hyp < c.radius) {
		return 0
	}
	/* Point is lies on the circle, so there is only one tangent point */
	else if (hyp == c.center.y) {
		*t0 = *t1 = point
		return 1
	}

	/* Since the tangent lines are always perpendicular to the radius, so
	 * we can use the Pythagorean theorem to solve for the missing side */
	p.radius = emb_sqrt((hyp * hyp) - (c.radius * c.radius))
	p.center = point
	return getCircleCircleIntersections(c, p, t0, t1)
	ret


embEllipse_diameterX:
	/* (EmbEllipse ellipse) returns float */
	return ellipse.radius.x * 2.0
	ret


/* (EmbEllipse ellipse) returns float
 */
embEllipse_diameterY:
	return ellipse.radius.y * 2.0
	ret


/*
 * takes EmbEllipse, returns float width
 *
 * (EmbEllipse ellipse) returns float
 */
embEllipse_width:
	return ellipse.radius.x * 2.0
	ret


embEllipse_height:
	/* (EmbEllipse ellipse) returns float */
	return ellipse.radius.y * 2.0
	ret


embVector_normalVector:
	/* (EmbVector dir, EmbVector* result, int clockwise) */
	float temp
	embVector_normalize(dir, result)
	temp = result->x
	result->x = result->y
	result->y = -temp
	if (!clockwise) {
		embVector_multiply(*result, -1.0, result)
	}
	ret


/*
 * Finds the normalized vector perpendicular (clockwise) to the line
 * given by v1->v2 (normal to the line)
 *
 * (EmbLine line, EmbVector* result, int clockwise)
 */
embLine_normalVector:
	if (!result) {
		print_log_string(error_vector_normal)
		return
	}
	embVector_subtract(line.end, line.end, result)
	embVector_normalVector(*result, result, clockwise)
	ret


/**
 * Finds the intersection of two lines given by v1->v2 and v3->v4
 * and sets the value in the result variable.
 */
unsigned char embLine_intersectionPoint(EmbLine line1, EmbLine line2, EmbVector* result):
	EmbVector D1, D2, C
	float tolerance, det
	tolerance = 1e-10
	embVector_subtract(line1.end, line1.start, &D2)
	C.y = embVector_cross(line1.start, D2)

	embVector_subtract(line2.end, line2.start, &D1)
	C.x = embVector_cross(line2.start, D1)

	det = embVector_cross(D1, D2)

	if (!result) {
		print_log_string(error_line_intersection)
		return 0
	}
	/*TODO: The code below needs revised since division by zero can still occur */
	if (emb_fabs(det) < tolerance) {
		print_log_string(error_line_parallel)
		return 0
	}
	result->x = D2.x * C.x - D1.x * C.y
	result->y = D2.y * C.x - D1.y * C.y
	embVector_multiply(*result, 1.0 / det, result)
	return 1
	ret


/* (EmbRect rect) returns float */
embRect_x:
	return rect.left
	ret


/* (EmbRect rect) returns float */
embRect_y:
	return rect.top
	ret


/* (EmbRect rect) returns float */
embRect_width:
	return rect.right - rect.left
	ret


/* (EmbRect rect) returns float */
embRect_height:
	return rect.bottom - rect.top
	ret


/* Sets the left edge of the rect to x.
 * The right edge is not modified.
 *
 * (EmbRect* rect, float x)
 */
embRect_setX:
	rect->left = x
	ret


/* Sets the top edge of the rect to y.
 * The bottom edge is not modified.
 *
 * (EmbRect* rect, float y)
 */
embRect_setY:
	rect->top = y
	ret


/* Sets the width of the rect to w.
 * The right edge is modified. The left edge is not modified.
 *
 * (EmbRect* rect, float w)
 */
embRect_setWidth:
	rect->right = rect->left + w
	ret


/* Sets the height of the rect to h.
 * The bottom edge is modified. The top edge is not modified.
 *
 * (EmbRect* rect, float h)
 */
embRect_setHeight:
	rect->bottom = rect->top + h
	ret


/* (EmbRect* rect, float x1, float y1, float x2, float y2)
 */
embRect_setCoords:
	rect->left = x1
	rect->top = y1
	rect->right = x2
	rect->bottom = y2
	ret


embRect_setRect(EmbRect* rect, float x, float y, float w, float h):
	rect->left = x
	rect->top = y
	rect->right = x + w
	rect->bottom = y + h
	ret


/* Finds the unit length vector \a result
 * in the same direction as \a vector.
 *
 * (EmbVector vector, EmbVector* result)
 */
embVector_normalize:
	float length
	length = embVector_getLength(vector)

	if (!result) {
		print_log_string(error_normalize)
		return
	}
	result->x = vector.x / length
	result->y = vector.y / length
	ret


/*
 * The scalar multiple \a magnitude of a vector \a vector.
 * Returned as \a result.
 *
 * (EmbVector vector, float magnitude, EmbVector* result)
 */
embVector_multiply:
	if (!result) {
		print_log_string(error_vector_multiply)
		return
	}
	movl	(vector.x), (result.x)
	movl	(vector.y), (result.y)
	mul	(magnitude), (result.x)
	mul	(magnitude), (result.y)
	ret


/*
 * The sum of vectors \a v1 and \a v2 returned as \a result.
 *
 * (EmbVector vector, float magnitude, EmbVector* result)
 */
embVector_add(EmbVector v1, EmbVector v2, EmbVector* result):
	if (!result) {
		print_log_string(error_vector_add)
		return
	}
	result->x = v1.x + v2.x
	result->y = v1.y + v2.y
	ret


/*
 * The average of vectors \a v1 and \a v2 returned as \a result.
 *
 * (EmbVector v1, EmbVector v2, EmbVector* result)
 */
embVector_average:
	if (!result) {
		print_log_string(error_vector_average)
		return
	}
	movl	(v1.x), (result.x)
	movl	(v1.y), (result.y)
	add	(v2.x), (result.x)
	add	(v2.y), (result.y)
	mull	$0.5, (result.x)
	mull	$0.5, (result.x)
	ret
#endif

/*
 * The difference between vectors \a v1 and \a v2 returned as \a result.
 *
 * (EmbVector v1, EmbVector v2, EmbVector* result)
 */
embVector_subtract:
#if 0
	if (!result) {
		print_log_string(error_vector_subtract)
		return
	}
	movl	(v1.x), (result.x)
	movl	(v1.y), (result.y)
	sub	(v2.x), (result.x)
	sub	(v2.y), (result.y)
#endif
	ret


/*
 * The dot product as vectors \a v1 and \a v2 returned as a float.
 *
 * That is
 * (x)   (a) = xa+yb
 * (y) . (b)
 *
 * (EmbVector v1, EmbVector v2) returns float
 */
embVector_dot:
#if 0
	mov	(v1.x), %eax
	mul	(v2.x), %eax
	mov	(v1.y), %ebx
	mul	(v2.y), %ebx
	add	%eax, %ebx
	ret


/*
 * The Euclidean distance between points v1 and v2, aka |v2-v1|.
 *
 * (EmbVector v1, EmbVector v2) returns float
 */
embVector_distance:
	mov	v1, %eax
	mov	v2, %ebx
	mov	v3, %ecx
	call	embVector_subtract
	mov	v3, %eax
	mov	v3, %ebx
	call	embVector_dot
	call	emb_sqrt
	ret
#endif

/*
 * Since we aren't using full vector algebra here, all vectors are "vertical".
 * so this is like the product v1^{T} I_{2} v2 for our vectors \a v1 and \v2
 * so a "component-wise product". The result is stored at the pointer \a result.
 *
 * That is
 *      (1 0) (a) = (xa)
 * (x y)(0 1) (b)   (yb)
 *
 * (EmbVector v1, EmbVector v2, EmbVector* result)
 */
embVector_component_product:
	/*
	if (!result) {
		print_log_string(error_vector_component_product)
		return
	}
	result->x = v1.x * v2.x
	result->y = v1.y * v2.y
	*/
	ret


/*
 * The length or absolute value of the vector \a vector.
 *
 * (EmbVector vector) returns float
 */
embVector_getLength:
	/*
	mov	(vector), %eax
	mov	(vector), %ebx
	call	embVector_dot
	call	emb_sqrt
	*/
	ret


/**
 * The length or absolute value of the vector \a vector. 
 *
 * float embVector_cross(EmbVector a, EmbVector b)
 * 	return a.x * b.y - a.y * b.x
 */
embVector_cross:

	
	ret


/*
 * (int type) returns EmbArray*
 */
embArray_create:
	/*
	int sizes[] = {
		sizeof(EmbArc), sizeof(EmbCircle), sizeof(EmbEllipse),
		sizeof(int), sizeof(EmbLine), sizeof(EmbPathObject),
		sizeof(EmbPoint), sizeof(EmbPolygonObject),
		sizeof(EmbPolylineObject), sizeof(EmbRect), sizeof(EmbSplineObject),
		sizeof(EmbStitch), sizeof(EmbThread), sizeof(EmbVector),
		sizeof(char), sizeof(EmbArray)
	}
	char fname[40]
	EmbArray* p
	p = arrays+memory_files
	p->type = type
	p->length = 0
	p->size = sizes[type]
	p->file_id = memory_files
	memory_files++
	memory[p->file_id] = tmpfile()
	return p
	*/
	ret


/*
 * (EmbArray *p, void *data) returns int
 */
embArray_add:
	/*
	fseek(memory[p->file_id], p->length*p->size, SEEK_SET)
	fwrite(data, p->size, 1, memory[p->file_id])
	p->length++
	return 1;   
	*/ 
	ret


/*
 * (EmbArray *p, void *data, int i) returns int
 */
embArray_get:
	/*
	fseek(memory[p->file_id], i*p->size, SEEK_SET)
	fread(data, p->size, 1, memory[p->file_id])
	return 1;
	*/
	ret


/*
 * (EmbArray *p, void *data, int i) returns int
 */
embArray_set:
	/*
	fseek(memory[p->file_id], i*p->size, SEEK_SET)
	fwrite(data, p->size, 1, memory[p->file_id])
	return 1
	*/
	ret


/* (int file, EmbArray *a, int offset, int n):
 *
 */
embArray_read:
	/*
	int i
	void *data = (void*)embBuffer
	fseek(file, offset, SEEK_SET)
	for (i=0; i<n; i++) {
		fread(data, a->size, 1, file)
		embArray_set(a, data, i)
	}
	*/
	ret


/*
 * (int file, EmbArray *a, int offset, int n)
 */
embArray_write:
	/*
	int i
	void *data = (void*)embBuffer
	fseek(file, offset, SEEK_SET)
	for (i=0; i<n; i++) {
		embArray_get(a, data, i)
		fwrite(data, a->size, 1, file)
	}
	*/
	ret


/* delete file, will be automatic for TMPFILE
 * Expects pointer to EmbArray on eax.
 */
embArray_free:
	/*fclose(memory[p->file_id])*/
	ret


/*! Returns a pointer to an EmbPattern. It is created on the heap.
 * The caller is responsible for freeing the allocated memory with
 * embPattern_free(). */
#if 0
EmbPattern* embPattern_create(void):
	EmbPattern* p
	p = patterns+active_patterns
	active_patterns++
	if (!p) {
		embLog("Ran out of memory for active patterns.")
		return 0
	}

	string_copy(p->name, "Untitled")
	p->currentColorIndex = 0
	p->stitchList = embArray_create(EMB_STITCH)
	p->threads = embArray_create(EMB_THREAD)
	p->hoop.height = 0.0
	p->hoop.width = 0.0
	p->arcs = embArray_create(EMB_ARC)
	p->circles = embArray_create(EMB_CIRCLE)
	p->ellipses = embArray_create(EMB_ELLIPSE)
	p->lines = embArray_create(EMB_LINE)
	p->paths = embArray_create(EMB_PATH)
	p->points = embArray_create(EMB_POINT)
	p->polygons = embArray_create(EMB_POLYGON)
	p->polylines = embArray_create(EMB_POLYLINE)
	p->rects = embArray_create(EMB_RECT)
	p->splines = embArray_create(EMB_SPLINE)
	p->ax = 0
	p->ay = 0
	p->mx = 0
	p->my = 0
	p->lastPosition.x = 0.0
	p->lastPosition.y = 0.0
	p->dstJumpsPerTrim = 6
	p->home.x = 0.0
	p->home.y = 0.0

	return p
	ret


embPattern_hideStitchesOverLength(EmbPattern* p, int length):
	float prevX, prevY
	int i
	EmbStitch st

	if (!p) {
		print_log_string(error_hide_stitches_no_pattern)
		return
	}

	prevX = 0
	prevY = 0
	for (i = 0; i < p->stitchList->length; i++) {
		embArray_get(p->stitchList, &st, i)
		if ((emb_fabs(st.x - prevX) > length) || (emb_fabs(st.y - prevY) > length)) {
			st.flags |= TRIM
			st.flags &= ~NORMAL
		}
		prevX = st.x
		prevY = st.y
		embArray_set(p->stitchList, &st, i)
	}
	ret


int embPattern_addThread(EmbPattern* p, EmbThread thread):
	embArray_add(p->threads, &thread)
	return 1
	ret


embPattern_fixColorCount(EmbPattern* p):
	/* fix color count to be max of color index. */
	int maxColorIndex = 0, i

	if (!p) {
		print_log_string(error_fix_color_count_no_pattern)
		return
	}
	for (i = 0; i < p->stitchList->length; i++) {
		EmbStitch st
		embArray_get(p->stitchList, &st, i)
		maxColorIndex = emb_max_int(maxColorIndex, st.color)
	}
	while (p->threads->length <= maxColorIndex) {
		embPattern_addThread(p, embThread_getRandom())
	}
	/*
	while (p->threadLists->length > (maxColorIndex + 1)) {
		TODO: erase last color    p->threadList.pop_back()
	}
	*/
	ret


/*! Copies all of the EmbStitchList data to EmbPolylineObjectList data for pattern (\a p). */
embPattern_copyStitchListToPolylines(EmbPattern* p):
	EmbPointObject point
	int breakAtFlags, i
	EmbStitch st

	if (!p) {
		print_log_string(error_copy_stitch_list_no_pattern)
		return
	}

	breakAtFlags = (STOP | JUMP | TRIM)

	for (i = 0; i < p->stitchList->length; i++) {
		EmbArray* pointList
		EmbColor color
		pointList = 0
		for (i = 0; i < p->stitchList->length; i++) {
			embArray_get(p->stitchList, &st, i)
			if (st.flags & breakAtFlags) {
				break
			}
			if (!(st.flags & JUMP)) {
				if (!pointList) {
					EmbThread t = pattern_thread(p, st.color)
					pointList = embArray_create(EMB_POINT)
					color = t.color
				}
				point.x = st.x
				point.y = st.y
				point.lineType = 0
				point.color = color
				embArray_add(pointList, &point)
			}
		}

		/* NOTE: Ensure empty polylines are not created. This is critical. */
		if (pointList) {
			EmbPolylineObject currentPolyline
			currentPolyline.pointList = pointList
			currentPolyline.color = color
			currentPolyline.lineType = 1
			/* TODO: Determine what the correct value should be. */

			if (!p->polylines) {
				p->polylines = embArray_create(EMB_POLYLINE)
			}
			embArray_add(p->polylines, &currentPolyline)
		}
		embArray_free(pointList)
	}
	ret


/*! Copies all of the EmbPolylineObjectList data to EmbStitchList data for pattern (\a p). */
embPattern_copyPolylinesToStitchList(EmbPattern* p):
	int firstObject = 1, i, j
	/*int currentColor = polyList->polylineObj->color TODO: polyline color */

	if (!p) {
		embLog("ERROR: embPattern_copyPolylinesToStitchList(), p==0\n")
		return
	}
	if (!p->polylines) {
		embLog("ERROR: embPattern_copyPolylinesToStitchList(), p==0\n")
		return
	}
	for (i = 0; i < p->polylines->length; i++) {
		EmbPolylineObject currentPoly
		EmbArray* currentPointList
		EmbThread thread

		embArray_get(p->polylines, &currentPoly, i)
		currentPointList = currentPoly.pointList
		if (!currentPointList) {
			embLog("ERROR: embPattern_copyPolylinesToStitchList(), currentPointList is null\n")
			return
		}

		string_copy(thread.catalogNumber, "NULL")
		thread.color = currentPoly.color
		string_copy(thread.description, "NULL")
		embPattern_addThread(p, thread)

		EmbVector v
		if (!firstObject) {
			embArray_get(currentPointList, &v, 0)
			embPattern_addStitchAbs(p, v.x, v.y, TRIM, 1)
			embPattern_addStitchRel(p, 0.0, 0.0, STOP, 1)
		}

		embArray_get(currentPointList, &v, 0)
		embPattern_addStitchAbs(p, v.x, v.y, JUMP, 1)
		for (j = 1; j < currentPointList->length; j++) {
			embArray_get(currentPointList, &v, j)
			embPattern_addStitchAbs(p, v.x, v.y, NORMAL, 1)
		}
		firstObject = 0
	}
	ret


/*! Moves all of the EmbStitchList data to EmbPolylineObjectList data for pattern (\a p). */
embPattern_moveStitchListToPolylines(EmbPattern* p):
	if (!p) {
		embLog("ERROR: embPattern_moveStitchListToPolylines(), p==0\n")
		return
	}
	embPattern_copyStitchListToPolylines(p)
	/* Free the stitchList and threadList since their data has now been transferred to polylines */
	embArray_free(p->stitchList)
	ret


/*! Moves all of the EmbPolylineObjectList data to EmbStitchList data for pattern (\a p). */
embPattern_movePolylinesToStitchList(EmbPattern* p):
	if (!p) {
		embLog("ERROR: embPattern_movePolylinesToStitchList(), p==0\n")
		return
	}
	embPattern_copyPolylinesToStitchList(p)
	embArray_free(p->polylines)
	ret


/*! Adds a stitch to the pattern (\a p) at the absolute position (\a x,\a y). Positive y is up. Units are in millimeters. */
embPattern_addStitchAbs(EmbPattern* p, float x, float y, int flags, int isAutoColorIndex):
	EmbStitch s

	if (!p || !p->stitchList) {
		embLog("ERROR: embPattern_addStitchAbs(), p==0\n")
		return
	}

	if (flags & END) {
		if (p->stitchList->length == 0) {
			return
		}
		/* Prevent unnecessary multiple END stitches */
		embArray_get(p->stitchList, &s, p->stitchList->length - 1)
		if (s.flags & END) {
			embLog("ERROR: embPattern_addStitchAbs(), found multiple END stitches\n")
			return
		}

		embPattern_fixColorCount(p)

		/* HideStitchesOverLength(127); TODO: fix or remove this */
	}

	if (flags & STOP) {
		if (p->stitchList->length == 0) {
			return
		}
		if (isAutoColorIndex) {
			p->currentColorIndex++
		}
	}

	/* NOTE: If the stitchList is empty, we will create it before adding stitches to it.
	 * The first coordinate will be the HOME position. */
	if (!p->stitchList) {
		/* NOTE: Always HOME the machine before starting any stitching */
		s.x = p->home.x
		s.y = p->home.y
		s.flags = JUMP
		s.color = p->currentColorIndex
		p->stitchList = embArray_create(EMB_STITCH)
		embArray_add(p->stitchList, &s)
	}

	s.x = x
	s.y = y
	s.flags = flags
	s.color = p->currentColorIndex
	embArray_add(p->stitchList, &s)
	p->lastPosition.x = s.x
	p->lastPosition.y = s.y
	ret


/*! Adds a stitch to the pattern (\a p) at the relative position (\a dx,\a dy) to the previous stitch. Positive y is up. Units are in millimeters. */
embPattern_addStitchRel(EmbPattern* p, float dx, float dy, int flags, int isAutoColorIndex):
	EmbVector home
	float x, y

	if (!p) {
		embLog("ERROR: embPattern_addStitchRel(), p==0\n")
		return
	}
	if (p->stitchList) {
		x = p->lastPosition.x + dx
		y = p->lastPosition.y + dy
	} else {
		/* NOTE: The stitchList is empty, so add it to the HOME position.
		 * The embStitchList_create function will ensure the first coordinate is at the HOME position. */
		x = p->home.x + dx
		y = p->home.y + dy
	}
	embPattern_addStitchAbs(p, x, y, flags, isAutoColorIndex)
	ret


embPattern_changeColor(EmbPattern* p, int index):
	if (!p) {
		embLog("ERROR: embPattern_changeColor(), p==0\n")
		return
	}
	p->currentColorIndex = index
	ret


/*! Reads a file with the given \a fileName and loads the data into \a pattern.
 *  Returns \c true if successful, otherwise returns \c false. */
int embPattern_readAuto(EmbPattern* pattern, const char* fileName) /* TODO: Write test case using this convenience function. */
{
	int reader

	reader = embReaderWriter_getByFileName(fileName)
	if (reader < 0) {
		embLog("ERROR: embPattern_read(), unsupported read file type:")
		embLog(fileName)
		return 0
	}

	return embPattern_read(pattern, fileName, reader)
	ret


/*! Writes the data from \a pattern to a file with the given \a fileName.
 *  Returns \c true if successful, otherwise returns \c false. */
int embPattern_writeAuto(EmbPattern* pattern, const char* fileName) /* TODO: Write test case using this convenience function. */
{
	int writer

	writer = embReaderWriter_getByFileName(fileName)
	if (writer < 0) {
		embLog("ERROR: embPattern_write(), unsupported write file type:")
		embLog(fileName)
		return 0
	}

	return embPattern_write(pattern, fileName, writer)
	ret


/* Very simple scaling of the x and y axis for every point.
* Doesn't insert or delete stitches to preserve density. */
embPattern_scale(EmbPattern* p, float scale):
	int i

	if (!p) {
		embLog("ERROR: embPattern_scale(), p==0\n")
		return
	}

	for (i = 0; i < p->stitchList->length; i++) {
		EmbStitch st
		embArray_get(p->stitchList, &st, i)
		st.x *= scale
		st.y *= scale
		embArray_set(p->stitchList, &st, i)
	}
	ret


/*! Returns an EmbRect that encapsulates all stitches and objects in the pattern (\a p). */
EmbRect embPattern_calcBoundingBox(EmbPattern* p):
	EmbRect boundingRect
	EmbStitch pt
	EmbBezier bezier
	int i, j

	boundingRect.left = 0
	boundingRect.right = 0
	boundingRect.top = 0
	boundingRect.bottom = 0

	if (!p || !p->stitchList) {
		embLog("ERROR: embPattern_calcBoundingBox(), p==0\n")
		return boundingRect
	}

	/* Calculate the bounding rectangle.  It's needed for smart repainting. */
	/* TODO: Come back and optimize this mess so that after going thru all objects
			and stitches, if the rectangle isn't reasonable, then return a default rect */
	if (!p->stitchList && !(p->arcs || p->circles || p->ellipses || p->lines || p->points || p->polygons || p->polylines || p->rects || p->splines)) {
		boundingRect.top = 0.0
		boundingRect.left = 0.0
		boundingRect.bottom = 1.0
		boundingRect.right = 1.0
		return boundingRect
	}
	boundingRect.left = 99999.0
	boundingRect.top = 99999.0
	boundingRect.right = -99999.0
	boundingRect.bottom = -99999.0

	for (i = 0; i < p->stitchList->length; i++) {
		/* If the point lies outside of the accumulated bounding
		* rectangle, then inflate the bounding rect to include it. */
		embArray_get(p->stitchList, &pt, i)
		if (!(pt.flags & TRIM)) {
			boundingRect.left = emb_min_float(boundingRect.left, pt.x)
			boundingRect.top = emb_min_float(boundingRect.top, pt.y)
			boundingRect.right = emb_max_float(boundingRect.right, pt.x)
			boundingRect.bottom = emb_max_float(boundingRect.bottom, pt.y)
		}
	}

	/* TODO: embPattern_calcBoundingBox for arcs, for now just checks the start point */
	for (i = 0; i < p->arcs->length; i++) {
		EmbArc arc
		embArray_get(p->arcs, &arc, i)
		boundingRect.left = emb_min_float(boundingRect.left, arc.start.x)
		boundingRect.top = emb_min_float(boundingRect.top, arc.start.y)
		boundingRect.right = emb_max_float(boundingRect.right, arc.start.x)
		boundingRect.bottom = emb_max_float(boundingRect.bottom, arc.start.y)
	}

	for (i = 0; i < p->circles->length; i++) {
		EmbCircle circle
		embArray_get(p->circles, &circle, i)
		boundingRect.left = emb_min_float(boundingRect.left, circle.center.x - circle.radius)
		boundingRect.top = emb_min_float(boundingRect.top, circle.center.y - circle.radius)
		boundingRect.right = emb_max_float(boundingRect.right, circle.center.x + circle.radius)
		boundingRect.bottom = emb_max_float(boundingRect.bottom, circle.center.y + circle.radius)
	}

	for (i = 0; i < p->ellipses->length; i++) {
		/* TODO: account for rotation */
		EmbEllipse ellipse
		embArray_get(p->ellipses, &ellipse, i)
		boundingRect.left = emb_min_float(boundingRect.left, ellipse.center.x - ellipse.radius.x)
		boundingRect.top = emb_min_float(boundingRect.top, ellipse.center.y - ellipse.radius.y)
		boundingRect.right = emb_max_float(boundingRect.right, ellipse.center.x + ellipse.radius.x)
		boundingRect.bottom = emb_max_float(boundingRect.bottom, ellipse.center.y + ellipse.radius.y)
	}

	for (i = 0; i < p->lines->length; i++) {
		EmbLine line
		embArray_get(p->lines, &line, i)
		boundingRect.left = emb_min_float(boundingRect.left, emb_min_float(line.start.x, line.end.x))
		boundingRect.top = emb_min_float(boundingRect.top, emb_min_float(line.start.y, line.end.y))
		boundingRect.right = emb_max_float(boundingRect.right, emb_max_float(line.start.x, line.end.x))
		boundingRect.bottom = emb_max_float(boundingRect.bottom, emb_max_float(line.start.y, line.end.y))
	}

	for (i = 0; i < p->points->length; i++) {
		EmbPointObject point
		embArray_get(p->points, &point, i)
		boundingRect.left = emb_min_float(boundingRect.left, point.x)
		boundingRect.top = emb_min_float(boundingRect.top, point.y)
		boundingRect.right = emb_max_float(boundingRect.right, point.x)
		boundingRect.bottom = emb_max_float(boundingRect.bottom, point.y)
	}

	for (i = 0; i < p->polygons->length; i++) {
		EmbPolygonObject* polygon
		embArray_get(p->polygons, &polygon, i)
		for (j = 0; j < polygon->pointList->length; j++) {
			EmbVector v
			embArray_get(polygon->pointList, &v, j)
			boundingRect.left = emb_min_float(boundingRect.left, v.x)
			boundingRect.top = emb_min_float(boundingRect.top, v.y)
			boundingRect.right = emb_max_float(boundingRect.right, v.x)
			boundingRect.bottom = emb_max_float(boundingRect.bottom, v.y)
		}
	}

	for (i = 0; i < p->polylines->length; i++) {
		EmbPolylineObject* polyline
		embArray_get(p->polylines, &polyline, i)
		for (j = 0; j < polyline->pointList->length; j++) {
			EmbVector v
			embArray_get(polyline->pointList, &v, j)
			boundingRect.left = emb_min_float(boundingRect.left, v.x)
			boundingRect.top = emb_min_float(boundingRect.top, v.y)
			boundingRect.right = emb_max_float(boundingRect.right, v.x)
			boundingRect.bottom = emb_max_float(boundingRect.bottom, v.y)
		}
	}

	for (i = 0; i < p->rects->length; i++) {
		EmbRect rect
		embArray_get(p->rects, &rect, i)
		/* TODO: other points */
		boundingRect.left = emb_min_float(boundingRect.left, rect.left)
		boundingRect.top = emb_min_float(boundingRect.top, rect.left)
		boundingRect.right = emb_max_float(boundingRect.right, rect.left)
		boundingRect.bottom = emb_max_float(boundingRect.bottom, rect.left)
	}

	for (i = 0; i < p->splines->length; i++) {
		embArray_get(p->splines, &bezier, i)
		/* TODO: other points */
		boundingRect.left = emb_min_float(boundingRect.left, bezier.start.x)
		boundingRect.top = emb_min_float(boundingRect.top, bezier.start.y)
		boundingRect.right = emb_max_float(boundingRect.right, bezier.start.x)
		boundingRect.bottom = emb_max_float(boundingRect.bottom, bezier.start.y)
	}

	return boundingRect
	ret


/*! Flips the entire pattern (\a p) horizontally about the y-axis. */
embPattern_flipHorizontal(EmbPattern* p):
	if (!p) {
		embLog("ERROR: embPattern_flipHorizontal(), p==0\n")
		return
	}
	embPattern_flip(p, 1, 0)
	ret


/*! Flips the entire pattern (\a p) vertically about the x-axis. */
embPattern_flipVertical(EmbPattern* p):
	if (!p) {
		embLog("ERROR: embPattern_flipVertical(), p==0\n")
		return
	}
	embPattern_flip(p, 0, 1)
	ret


/*! Flips the entire pattern (\a p) horizontally about the x-axis if (\a horz) is true.
 *  Flips the entire pattern (\a p) vertically about the y-axis if (\a vert) is true. */
embPattern_flip(EmbPattern* p, int horz, int vert):
	int i, j
	EmbVector flip

	if (!p) {
		embLog("ERROR: embPattern_flip(), p==0\n")
		return
	}

	flip.x = 1.0
	flip.y = 1.0
	if (horz) {
		flip.x = -1.0
	}
	if (vert) {
		flip.y = -1.0
	}

	for (i = 0; i < p->stitchList->length; i++) {
		EmbStitch st
		embArray_get(p->stitchList, &st, i)
		st.x *= flip.x
		st.y *= flip.y
		embArray_get(p->stitchList, &st, i)
	}

	for (i = 0; i < p->arcs->length; i++) {
		EmbArc arc
		embArray_get(p->arcs, &arc, i)
		embVector_component_product(arc.start, flip, &(arc.start))
		embVector_component_product(arc.mid, flip, &(arc.mid))
		embVector_component_product(arc.end, flip, &(arc.end))
		embArray_set(p->arcs, &arc, i)
	}

	for (i = 0; i < p->circles->length; i++) {
		EmbCircle circle
		embArray_get(p->circles, &circle, i)
		embVector_component_product(circle.center, flip, &(circle.center))
		embArray_set(p->circles, &circle, i)
	}

	for (i = 0; i < p->ellipses->length; i++) {
		EmbEllipse ellipse
		embArray_get(p->ellipses, &ellipse, i)
		embVector_component_product(ellipse.center, flip, &(ellipse.center))
		embArray_set(p->ellipses, &ellipse, i)
	}

	for (i = 0; i < p->lines->length; i++) {
		EmbLine line
		embArray_get(p->lines, &line, j)
		embVector_component_product(line.start, flip, &(line.start))
		embVector_component_product(line.end, flip, &(line.end))
		embArray_set(p->lines, &line, j)
	}

	if (p->paths) {
		for (i = 0; i < p->paths->length; i++) {
			EmbPathObject* path
			embArray_get(p->paths, &path, i)
			for (j = 0; j < path->pointList->length; j++) {
				EmbVector point
				embArray_get(path->pointList, &point, j)
				embVector_component_product(point, flip, &point)
				embArray_set(path->pointList, &point, j)
			}
		}
	}

	if (p->points) {
		for (i = 0; i < p->points->length; i++) {
			EmbPointObject point
			embArray_get(p->points, &point, i)
			point.x *= flip.x
			point.y *= flip.y
			embArray_set(p->points, &point, i)
		}
	}

	if (p->polygons) {
		for (i = 0; i < p->polygons->length; i++) {
			EmbPolygonObject* polygon
			embArray_get(p->polygons, polygon, i)
			for (j = 0; j < polygon->pointList->length; j++) {
				EmbVector point
				embArray_get(polygon->pointList, &point, j)
				embVector_component_product(point, flip, &point)
				embArray_set(polygon->pointList, &point, j)
			}
		}
	}

	if (p->polylines) {
		for (i = 0; i < p->polylines->length; i++) {
			EmbPolylineObject* polyline
			embArray_get(p->polylines, polyline, i)
			for (j = 0; j < polyline->pointList->length; j++) {
				EmbVector point
				embArray_get(polyline->pointList, &point, j)
				embVector_component_product(point, flip, &point)
				embArray_set(polyline->pointList, &point, j)
			}
		}
	}

	if (p->rects) {
		for (i = 0; i < p->rects->length; i++) {
			EmbRect rect
			embArray_get(p->rects, &rect, j)
			rect.left *= flip.x
			rect.right *= flip.x
			rect.top *= flip.y
			rect.bottom *= flip.y
			embArray_set(p->rects, &rect, j)
		}
	}

	if (p->splines) {
		for (i = 0; i < p->splines->length; i++) {
			/* TODO: embPattern_flip for splines */
		}
	}
	ret


/* Does this need a tolerance to stop really long jumps?
 */
embPattern_combineJumpStitches(EmbPattern* p):
	int jump = 0, i, j
	EmbStitch st

	if (!p) {
		embLog("ERROR: embPattern_combineJumpStitches(), p==0\n")
		return
	}

	j = 0
	for (i = 0; i < p->stitchList->length; i++) {
		embArray_get(p->stitchList, &st, i)
		embArray_set(p->stitchList, &st, j)
		if (st.flags & JUMP) {
			if (jump == 0) {
				j++
				jump = 1
			}
		} else {
			j++
			jump = 0
		}
	}
	p->stitchList->length = j + 1
	ret


/* TODO: The params determine the max XY movement rather than the length.
 * They need renamed or clarified further. */
embPattern_correctForMaxStitchLength(EmbPattern* p, float maxStitchLength, float maxJumpLength):
	int j = 0, splits, i
	float maxXY, maxLen
	EmbVector st, diff, add
	EmbArray* newList

	if (!p) {
		embLog("ERROR: embPattern_correctForMaxStitchLength(), p==0\n")
		return
	}
	if (p->stitchList->length > 1) {
		EmbStitch stitch
		newList = embArray_create(EMB_STITCH)
		embArray_get(p->stitchList, &stitch, 0)
		embArray_add(newList, &stitch)
		for (i = 1; i < p->stitchList->length; i++) {
			EmbStitch st1, st2
			embArray_get(p->stitchList, &st1, i - 1)
			embArray_get(p->stitchList, &st2, i)
			st.x = st1.x
			st.y = st1.y
			diff.x = st2.x - st.x
			diff.y = st2.y - st.y
			maxXY = embVector_getLength(diff)
			if (maxXY > maxStitchLength) {
				if (st2.flags & (JUMP | TRIM))
					maxLen = maxJumpLength
				else
					maxLen = maxStitchLength

				splits = (int)emb_ceil((float)maxXY / maxLen)

				if (splits > 1) {
					embVector_multiply(diff, (float)(1.0 / splits), &add)

					for (j = 1; j < splits; j++) {
						EmbStitch s
						s = st1
						s.x += add.x * j
						s.y += add.y * j
						embArray_add(newList, &s)
					}
				}
			}
			embArray_add(newList, &st2)
		}
		embArray_free(p->stitchList)
		p->stitchList = newList
	}
	ret


embPattern_center(EmbPattern* p):
	/* TODO: review this. currently not used in anywhere. Also needs to handle various design objects */
	int moveLeft, moveTop, i
	EmbRect boundingRect
	EmbStitch s

	if (!p) {
		embLog("ERROR: embPattern_center(), p==0\n")
		return
	}
	boundingRect = embPattern_calcBoundingBox(p)

	moveLeft = (int)(boundingRect.left - (embRect_width(boundingRect) / 2.0))
	moveTop = (int)(boundingRect.top - (embRect_height(boundingRect) / 2.0))

	for (i = 0; i < p->stitchList->length; i++) {
		embArray_get(p->stitchList, &s, i)
		s.x -= moveLeft
		s.y -= moveTop
		embArray_set(p->stitchList, &s, i)
	}
	ret


/* TODO: Description needed. */
embPattern_loadExternalColorFile(EmbPattern* p, const char* fileName):
	char *dotPos
	char hasRead
	char *buffer = (char*)embBuffer

	hasRead = 0
	string_copy(buffer, (char*)fileName)
	dotPos = buffer + string_length(buffer)
	while (*dotPos != '.') {
		dotPos--
	}
	string_copy(dotPos, ".edr")
	hasRead = embPattern_readAuto(p, buffer)
	if (!hasRead) {
		string_copy(buffer, (char*)fileName)
		string_copy(dotPos, ".rgb")
		hasRead = embPattern_readAuto(p, buffer)
	}
	if (!hasRead) {
		string_copy(buffer, fileName)
		string_copy(dotPos, ".col")
		hasRead = embPattern_readAuto(p, buffer)
	}
	if (!hasRead) {
		string_copy(buffer, fileName)
		string_copy(dotPos, ".inf")
		hasRead = embPattern_readAuto(p, buffer)
	}
	ret


/*! Frees all memory allocated in the pattern (\a p). */
embPattern_free(EmbPattern* p):
	embArray_free(p->stitchList)
	embArray_free(p->arcs)
	embArray_free(p->circles)
	embArray_free(p->ellipses)
	embArray_free(p->lines)
	embArray_free(p->paths)
	embArray_free(p->points)
	embArray_free(p->polygons)
	embArray_free(p->polylines)
	embArray_free(p->rects)
	embArray_free(p->splines)
	ret


/*! Adds a circle object to pattern (\a p) with its center at the absolute
 * position (\a cx,\a cy) with a radius of (\a r). Positive y is up.
 * Units are in millimeters. */
embPattern_addCircleObjectAbs(EmbPattern* p, float cx, float cy, float r, int lineType, EmbColor color):
	EmbCircle circle
	circle.center.x = cx
	circle.center.y = cy
	circle.radius = r
	circle.lineType = 0
	circle.color = color

	if (!p) {
		embLog("ERROR: embPattern_addCircleObjectAbs(), p==0\n")
		return
	}
	embArray_add(p->circles, &circle)
	ret


/*! Adds an ellipse object to pattern (\a p) with its center at the
 * absolute position (\a cx,\a cy) with radii of (\a rx,\a ry). Positive y is up.
 * Units are in millimeters. */
embPattern_addEllipseObjectAbs(EmbPattern* p, float cx, float cy, float rx, float ry, float rotation, int lineType, EmbColor color):
	EmbEllipse ellipse
	ellipse.center.x = cx
	ellipse.center.y = cy
	ellipse.radius.x = rx
	ellipse.radius.y = ry
	ellipse.rotation = rotation
	ellipse.lineType = lineType
	ellipse.color = black

	if (!p) {
		embLog("ERROR: embPattern_addEllipseObjectAbs(), p==0\n")
		return
	}
	embArray_add(p->ellipses, &ellipse)
	ret


/*! Adds a line object to pattern (\a p) starting at the absolute position
 * (\a x1,\a y1) and ending at the absolute position (\a x2,\a y2).
 * Positive y is up. Units are in millimeters.
 */
embPattern_addLineObjectAbs(EmbPattern* p, float x1, float y1, float x2, float y2, int lineType, EmbColor color):
	EmbLine line
	line.start.x = x1
	line.start.y = y1
	line.end.x = x2
	line.end.y = y2
	line.lineType = lineType
	line.color = color

	if (!p) {
		embLog("ERROR: embPattern_addLineObjectAbs(), p==0\n")
		return
	}
	embArray_add(p->lines, &line)
	ret


embPattern_addPathObjectAbs(EmbPattern* p, EmbPathObject* obj):
	if (!p) {
		embLog("ERROR: embPattern_addPathObjectAbs(), p==0\n")
		return
	}
	if (!obj) {
		embLog("ERROR: embPattern_addPathObjectAbs(), obj==0\n")
		return
	}
	if (!obj->pointList) {
		embLog("ERROR: embPattern_addPathObjectAbs(), obj->pointList is empty\n")
		return
	}

	embArray_add(p->paths, obj)
	ret


/*! Adds a point object to pattern (\a p) at the absolute position (\a x,\a y). Positive y is up. Units are in millimeters. */
embPattern_addPointObjectAbs(EmbPattern* p, float x, float y, int lineType, EmbColor color):
	EmbPointObject point
	point.x = x
	point.y = y
	point.lineType = lineType
	point.color = color

	if (!p) {
		embLog("ERROR: embPattern_addPointObjectAbs(), p==0\n")
		return
	}
	embArray_add(p->points, &point)
	ret


embPattern_addPolygonObjectAbs(EmbPattern* p, EmbPolygonObject* obj):
	if (!p) {
		embLog("ERROR: embPattern_addPolygonObjectAbs(), p==0\n")
		return
	}
	if (!obj) {
		embLog("ERROR: embPattern_addPolygonObjectAbs(), obj==0\n")
		return
	}
	if (!obj->pointList) {
		embLog("ERROR: embPattern_addPolygonObjectAbs(), obj->pointList is empty\n")
		return
	}

	embArray_add(p->polygons, obj)
	ret


embPattern_addPolylineObjectAbs(EmbPattern* p, EmbPolylineObject* obj):
	if (!p) {
		embLog("ERROR: embPattern_addPolylineObjectAbs(), p==0\n")
		return
	}
	if (!obj) {
		embLog("ERROR: embPattern_addPolylineObjectAbs(), obj==0\n")
		return
	}
	if (!obj->pointList) {
		embLog("ERROR: embPattern_addPolylineObjectAbs(), obj->pointList is empty\n")
		return
	}

	embArray_add(p->polylines, obj)
	ret


embPattern_colorBlock16(EmbPattern *pattern, int file):
	int i

	/* write remaining colors to reach 16 */
	memory_set(embBuffer, 0, 16*4)

	for (i = 0; i < pattern->threads->length; i++) {
		EmbThread t
		t = pattern_thread(pattern, i)
		embColor_toStr(t.color, embBuffer+4*i)
	}

	fwrite(embBuffer, 1, 16*4, file)
	ret


/**
 * Adds a rectangle object to pattern (\a p) at the absolute position
 * (\a x,\a y) with a width of (\a w) and a height of (\a h).
 * Positive y is up. Units are in millimeters.
 */
embPattern_addRectObjectAbs(EmbPattern* p, float x, float y, float w, float h, int lineType, EmbColor color):
	EmbRect rect
	rect.left = x
	rect.top = y
	rect.right = x + w
	rect.bottom = y + h
	rect.lineType = 0
	rect.color = color

	if (!p) {
		embLog("ERROR: embPattern_addRectObjectAbs(), p==0\n")
		return
	}
	embArray_add(p->rects, &rect)
	ret


embArray_resample(EmbArray *a, EmbArray *usePt):
	int i, j, flag
	j = 0
	for (i=0; i<a->length; i++) {
		embArray_get(usePt, &flag, i)
		if (flag) {
			void *data
			embArray_get(a, data, i)
			embArray_set(a, data, j)
			j++
		}
	}
	a->length = j
	ret


int embVector_collinear(EmbVector a1, EmbVector a2, EmbVector a3, float collinearity_tolerance):
	EmbVector c21, c31
	float angle

	embVector_subtract(a2, a1, &c21)
	embVector_subtract(a3, a1, &c31)
	angle = GetAngle(c21, c31)
	return angle < collinearity_tolerance
	ret


float GetRelativeX(EmbVector a1, EmbVector a2, EmbVector a3):
	EmbVector c12, c32
	embVector_subtract(a1, a2, &c12)
	embVector_subtract(a3, a2, &c32)
	return embVector_dot(c12, c32)
	ret


float GetRelativeY(EmbVector a1, EmbVector a2, EmbVector a3):
	EmbVector c12, c32
	embVector_subtract(a1, a2, &c12)
	embVector_subtract(a3, a2, &c32)
	return embVector_cross(c12, c32)
	ret


float GetAngle(EmbVector a, EmbVector b):
	EmbVector h
	embVector_subtract(a, b, &h)
	return emb_atan2(h.x, h.y)
	ret


embPattern_breakIntoColorBlocks(EmbPattern *pattern):
#if 0
	EmbColor color
	int oldColor, i
	EmbArray *sa2
	VectorStitch vs
	sa2 = new StitchBlock()
	oldColor = pattern.StitchList[0].ColorIndex
	color = pattern.ColorList[oldColor]
	sa2.Thread = new Thread(color.Red, color.Blue, color.Green)
	for (i=0; i<pattern->stitches->length; i++) {
		s = pattern->stitches->stitch[i]
		if (s.ColorIndex != oldColor) {
			yield return sa2
			sa2 = new StitchBlock()
			color = pattern.ColorList[s.ColorIndex]
			sa2.Thread = new Thread(color.Red, color.Blue, color.Green)
			oldColor = s.ColorIndex
		}
		vs = new VectorStitch { Xy = new Point(s.X, s.Y), Color = s.ColorIndex }
		sa2.Stitches.Add(vs)
	}
	yield return sa2
#endif
	ret


int embPolygon_breakIntoSeparateObjects(EmbArray *blocks):
#if 0
	int i, j
	float dx, dy, dy2, dy3
	float previousAngle = 0.0
	for (j=0; j<blocks->length; j++) {
		block = blocks[j]
		EmbArray *stitches = new List<VectorStitch>()
		block.Stitches[0].Type = VectorStitchType.Contour
		block.Stitches[block.Stitches->length - 1].Type = VectorStitchType.Contour

		for (i = 0; i < block.Stitches->length - 2; i++) { /* step 0 */
			dx = (GetRelativeX(block.Stitches[i].Xy, block.Stitches[i + 1].Xy, block.Stitches[i + 2].Xy))
			block.Stitches[i + 1].Type = dx <= 0 ? VectorStitchType.Run : VectorStitchType.Contour
			block.Stitches[i].Angle = GetAngle(block.Stitches[i], block.Stitches[i + 1])
			stitches.Add(block.Stitches[i].Clone())
			if (i > 0) {
				if ((block.Stitches[i].Type == VectorStitchType.Contour) && Math.Abs(block.Stitches[i].Angle - previousAngle) > (20/180*embConstantPi))
				{
					yield return
						new StitchBlock {
								Stitches = stitches,
								Angle = stitches.Average(x => x.Angle),
								Thread = new Thread(block.Thread.Red, block.Thread.Blue, block.Thread.Green)
							}
					stitches = new List<VectorStitch>()
				}
			}
		}

		/* step 1 */
		for (i = 1; i < pattern->stitches->length - 3; i++) {
			if (pattern->stitches->stitch[i + 1].type == VectorStitchType.Contour) {
				dy = GetRelativeY(sa[i + 1].XY, sa[i + 2].XY, sa[i + 3].XY)
				dy2 = GetRelativeY(sa[i].XY, sa[i + 1].XY, sa[i + 2].XY)
				dy3 = GetRelativeY(sa[i + 2].XY, sa[i + 3].XY, sa[i + 4].XY)
				/* if(dy) */
				if (sa.Stitches[i - 1].Type == VectorStitchType.Run || sa.Stitches[i + 1].Type == VectorStitchType.Run)
				{
					sa.Stitches[i].Type = VectorStitchType.Tatami
				}
				else {
					sa.Stitches[i].Type = VectorStitchType.Satin
				}
			}
		}
	}
#endif
	return 1
	ret


int FindOutline(EmbArray *stitchData, EmbArray *result):
	int currColorIndex = 0, oddEven, i
	float dx, dy, dy2, dy3
#if 0
	EmbArray *pOdd = new List<Point>()
	EmbArray *pEven = new List<Point>()
	foreach (StitchBlock sa in stitchData) {
		if (sa.Stitches->length > 0) {
			sa.Stitches[0].Type = VectorStitchType.Contour
			sa.Stitches[sa.Stitches->length - 1].Type = VectorStitchType.Contour
			/* step 0 */
			for (i = 0; i < sa.Stitches->length - 2; i++) {
				dx = (GetRelativeX(sa.Stitches[i].Xy, sa.Stitches[i + 1].Xy, sa.Stitches[i + 2].Xy))
				sa.Stitches[i + 1].Type = dx <= 0 ? VectorStitchType.Run : VectorStitchType.Contour
				sa.Stitches[i].Angle = GetAngle(sa.Stitches[i], sa.Stitches[i + 1])
			}
			/* step 1 */
			for (i = 1; i < sa.Stitches->length - 3; i++) {
				if (sa.Stitches[i + 1].Type == VectorStitchType.Contour) {
					dy = GetRelativeY(sa[i + 1].XY, sa[i + 2].XY, sa[i + 3].XY)
					dy2 = GetRelativeY(sa[i].XY, sa[i + 1].XY, sa[i + 2].XY)
					dy3 = GetRelativeY(sa[i + 2].XY, sa[i + 3].XY, sa[i + 4].XY)
					/* if(dy) */
					if (sa.Stitches[i - 1].Type == VectorStitchType.Run || sa.Stitches[i + 1].Type == VectorStitchType.Run)
					{
						sa.Stitches[i].Type = VectorStitchType.Tatami
					}
					else {
						sa.Stitches[i].Type = VectorStitchType.Satin
					}
				}
			}
		}


		oddEven = 0
		foreach (VectorStitch t in sa.Stitches) {
			if ((t.Type == VectorStitchType.Contour) && (oddEven % 2) == 0) {
				pEven.Add(t.Xy)
				oddEven++
			}
			else if ((t.Type == VectorStitchType.Contour) && (oddEven % 2) == 1) {
				pOdd.Add(t.Xy)
				oddEven++
			}
		}
		currColorIndex++
		EmbArray *so = new StitchObject { SideOne = pEven, SideTwo = pOdd, ColorIndex = currColorIndex }
		yield return so
		pEven = new List<Point>()
		pOdd = new List<Point>()
		/* break; */
	}
#endif
	return 1
	ret


int DrawGraphics(EmbPattern p):
#if 0
	var stitchData = BreakIntoColorBlocks(p)

	/*
	var outBlock = new List<StitchBlock>(BreakIntoSeparateObjects(stitchData))
	foreach(var block in stitchData) {
		foreach (var stitch in block.Stitches) {
			if(stitch.Angle != 0) {
				int aaa = 1
			}
		}
	}
	*/
	/* var xxxxx = outBlock; */
	EmbArray *objectsFound = FindOutline(stitchData)
	EmbArray *outPattern = new Pattern()
	outPattern.AddColor(new Thread(255, 0, 0, "none", "None"))
	int colorIndex = outPattern.ColorList->length - 1

	foreach (StitchObject stitchObject in objectsFound) {
		if (stitchObject.SideOne->length > 1 && stitchObject.SideTwo->length > 1) {
			outPattern.AddColor(new Thread((byte) (rand()%256), (byte) (rand()%256), (byte) (rand()%256),
										   "none", "None"))
			colorIndex++
			outPattern.AddStitchRelative(0, 0, StitchTypes.Stop)
			var points = stitchObject.Generate2(75)
			foreach (var point in points)
			{
				outPattern.AddStitchAbsolute(point.X, point.Y, StitchTypes.Normal)
			}
			/*
			break
			Point t
			StitchObject stitchObject = objectsFound[1]
			if (stitchObject.SideOne->length > 0) {
				outPattern.StitchList.Add(new Stitch(stitchObject.SideOne[0].x, stitchObject.SideOne[0].y,
													 StitchType.Jump, colorIndex))
			}
			foreach (t in stitchObject.SideOne) {
				outPattern.StitchList.Add(new Stitch(t.x, t.y, StitchType.Normal, colorIndex))
			}
			foreach (t in stitchObject.SideTwo) {
				outPattern.StitchList.Add(new Stitch(t.x, t.y, StitchType.Normal, colorIndex))
			}
			break
			*/
		}
	}
	outPattern.AddStitchRelative(0, 0, StitchTypes.End)
	/* return (SimplifyOutline(outPattern)); */
#endif
	return 0
	ret


int SimplifyOutline(EmbPattern *pattern, EmbPattern *patternOut):
	int color
#if 0
	var v = new Vertices()
	v.AddRange(pattern.StitchList.Select(point => new Vector2(point.X, point.Y)))
	output = SimplifyTools.DouglasPeuckerSimplify(v, 10)
	patternOut = embPattern_create()
	for (color=0; color<pattern->threads->length; color++) {
		
		embPattern_addThread(patternOut, pattern->threads->thread[color])
	}

	foreach (var vertex in output) {
		patternOut.AddStitchAbsolute(vertex.X, vertex.Y, StitchTypes.Normal)
	}
#endif
	return 1
	ret



/**
 * Removes all collinear points on the polygon. Has a default bias of 0.
 *
 * @param vertices The polygon that needs simplification.
 * @param collinearityTolerence How close a point can be to collinear before it is removed.
 * @returns A simplified polygon in the same EmbArray.
 */
int embPolygon_collinearSimplify(EmbArray *vertices, float collinearityTolerance):
	int i, prevId, nextId
	EmbVector prev, current, next
	EmbArray *usePt
	/* We can't simplify polygons under 3 vertices */
	if (vertices->length < 3) {
		return 0
	}

	usePt = embArray_create(EMB_FLAG)

	for (i = 0; i < vertices->length; i++) {
		int flag
		prevId = (i-1+vertices->length) % vertices->length
		nextId = (i+1) % vertices->length

		embArray_get(vertices, &prev, prevId)
		embArray_get(vertices, &current, i)
		embArray_get(vertices, &next, nextId)

		flag = 1
		if (embVector_collinear(prev, current, next, collinearityTolerance)) {
			flag = 0
		}
		embArray_add(usePt, &flag)
	}

	embArray_resample(vertices, usePt)
	embArray_free(usePt)
	return 1
	ret


/**
 * Ramer-Douglas-Peucker polygon simplification algorithm. This is the general recursive version that does not use the
 * speed-up technique by using the Melkman convex hull.
 * If you pass in 0, it will remove all collinear points
 */
int embPolygon_DouglasPeuckerSimplify(EmbArray *vertices, float distanceTolerance):
	int i
	EmbArray *_usePt

	_usePt = embArray_create(EMB_FLAG)
	for (i = 0; i < vertices->length; i++) {
		int flag = 1
		embArray_add(_usePt, &flag)
	}
	embPolygon_simplifySection(vertices, _usePt, 0, vertices->length - 1, distanceTolerance)
	embArray_resample(vertices, _usePt)
	embArray_free(_usePt)
	return 1
	ret


embPolygon_simplifySection(EmbArray *vertices, EmbArray *_usePt, int i, int j, float distanceTolerance):
	int k, maxIndex
	EmbVector a, b, c
	float maxDistance, distance
	if ((i + 1) == j)
		return

	embArray_get(vertices, &a, i)
	embArray_get(vertices, &b, j)
	maxDistance = -1.0
	maxIndex = i
	for (k = i + 1; k < j; k++) {
		embArray_get(vertices, &c, k)
		distance = embVector_distancePointLine(c, a, b)

		if (distance > maxDistance) {
			maxDistance = distance
			maxIndex = k
		}
	}
	if (maxDistance <= distanceTolerance) {
		for (k = i + 1; k < j; k++) {
			int flag = 0
			embArray_set(_usePt, &flag, k)
		}
	}
	else {
		embPolygon_simplifySection(vertices, _usePt, i, maxIndex, distanceTolerance)
		embPolygon_simplifySection(vertices, _usePt, maxIndex, j, distanceTolerance)
	}
	ret


/**
 * Find the distance from (\a p) to the line from (\a a) to (\a b) by
 * finding the length of the normal from ab (extended to an infinite line)
 * to p.
 */
float embVector_distancePointLine(EmbVector p, EmbVector a, EmbVector b):
	float r, curve2, s, tolerance
	EmbVector pa, ba

	tolerance = 0.00001
	embVector_subtract(b, a, &ba)
	/* if start == end, then use point-to-point distance */
	if (emb_fabs(ba.x) < tolerance && emb_fabs(ba.y) < tolerance) {
		return embVector_distance(p, a)
	}

	/* otherwise use comp.graphics.algorithms Frequently Asked Questions method */
	/*(1)     		  AC dot AB
				r =   ---------
					  ||AB||^2

				r has the following meaning:
				r=0 Point = A
				r=1 Point = B
				r<0 Point is on the backward extension of AB
				r>1 Point is on the forward extension of AB
				0<r<1 Point is interior to AB
	*/

	embVector_subtract(p, a, &pa)
	curve2 = embVector_dot(ba, ba)
	r = embVector_dot(pa, ba) / curve2

	if (r <= 0.0) return embVector_distance(p, a)
	if (r >= 1.0) return embVector_distance(p, b)

	/*(2)
					(Ay-Cy)(Bx-Ax)-(Ax-Cx)(By-Ay)
				s = -----------------------------
								Curve^2

				Then the distance from C to Point = |s|*Curve.
	*/

	s = (pa.x * ba.y - pa.y * ba.x) / curve2

	return emb_fabs(s) * emb_sqrt(curve2)
	ret


/* From physics2d.net */
int embPolygon_reduceByArea(EmbArray *vertices, EmbArray *result, float areaTolerance):
	float old1, old2, new1
	int index
	EmbVector v1, v2, v3
	if (vertices->length <= 3) {
		return 0
	}

	if (areaTolerance < 0) {
		embLog("areaTolerence must be greater than or equal to zero.")
		return 0
	}

	result = embArray_create(EMB_VECTOR)
	embArray_get(vertices, &v1, vertices->length - 2); 
	embArray_get(vertices, &v2, vertices->length - 1); 
	areaTolerance *= 2
	for (index = 0; index < vertices->length; ++index, v2 = v3) {
		if (index == vertices->length - 1) {
			if (result->length == 0) {
				embLog("The areaTolerance is too high.")
				return 0
			}
			embArray_get(vertices, &v3, 0); 
		}
		else {
			embArray_get(vertices, &v3, index); 
		}
		old1 = embVector_cross(v1, v2)
		old2 = embVector_cross(v2, v3)
		new1 = embVector_cross(v1, v3)
		if (emb_fabs(new1 - (old1 + old2)) > areaTolerance) {
			embArray_add(result, &v2)
			v1 = v2
		}
	}
	return 1
	ret


/**
 * From Eric Jordan's convex decomposition library
 * Merges all parallel edges in the list of vertices
 */
MergeParallelEdges(EmbArray *vertices, float tolerance):
	int lower, upper, i, newNVertices
	EmbVector d0, d1, a, b, c
	float norm0, norm1, cross, dot
	EmbArray *usePoints
	if (vertices->length <= 3) {
		return; /* Can't do anything useful here to a triangle */
	}

	usePoints = embArray_create(EMB_FLAG)
	newNVertices = vertices->length

	/* Gather points to process */
	for (i = 0; i < vertices->length; ++i) {
		lower = (i+vertices->length-1) % vertices->length
		upper = (i+1)% vertices->length

		embArray_get(vertices, &a, lower)
		embArray_get(vertices, &b, i)
		embArray_get(vertices, &c, upper)

		embVector_subtract(b, a, &d0)
		embVector_subtract(c, b, &d1)
		norm0 = embVector_getLength(d0)
		norm1 = embVector_getLength(d1)

		int flag = 0
		if (!(norm0 > 0.0f && norm1 > 0.0f) && newNVertices > 3) {
			/* Merge identical points */
			embArray_add(usePoints, &flag)
			--newNVertices
			continue
		}

		embVector_multiply(d0, 1.0/norm0, &d0)
		embVector_multiply(d1, 1.0/norm1, &d1)
		cross = embVector_cross(d0, d1)
		dot = embVector_dot(d0, d1)

		if (emb_fabs(cross) < tolerance && dot > 0 && newNVertices > 3) {
			flag = 0
			--newNVertices
		}
		else {
			flag = 1
		}
		embArray_add(usePoints, &flag)
	}

	if (newNVertices == vertices->length || newNVertices == 0) {
		embArray_free(usePoints)
		return
	}

	embArray_resample(vertices, usePoints)
	embArray_free(usePoints)
	ret


/* Reduces the polygon by distance. */
int embPolygon_reduceByDistance(EmbArray *vertices, float distance):
	int i, nextId
	float vdist
	EmbArray *usePoints
	EmbVector a, b
	/* We can't simplify polygons under 3 vertices */
	if (vertices->length < 3) return 0

	usePoints = embArray_create(EMB_FLAG)

	for (i = 0; i < vertices->length; i++) {
		nextId = (i + 1) % vertices->length

		embArray_get(vertices, &a, i)
		embArray_get(vertices, &b, nextId)
		vdist = embVector_distance(a, b)

		/* If they are closer than the distance, do not use the i-th point */
		int flag
		if (vdist < distance) {
			flag = 0
		}
		else {
			flag = 1
		}
		embArray_add(usePoints, &flag)
	}

	embArray_resample(vertices, usePoints)
	embArray_free(usePoints)
	return 1
	ret


/* Reduces the polygon by removing the Nth vertex in the vertices list. */
int embPolygon_reduceByNth(EmbArray* vertices, int nth):
	int i
	/* We can't simplify polygons under 3 vertices */
	if (vertices->length < 3)
		return 0

	/* Vertex is not present */
	if (nth >= vertices->length)
		return 0

	/* This isn't an array of vectors. */
	if (vertices->type != EMB_VECTOR)
		return 0

	/* Shift everything left one place then reduce the count. */
	for (i = nth; i < vertices->length - 1; i++) {
		EmbVector v
		embArray_get(vertices, &v, i+1)
		embArray_set(vertices, &v, i)
	}
	vertices->length--

	/* success, trust the data in vertices */
	return 1
	ret


embSatinOutline_generateSatinOutline(EmbArray* lines, float thickness, EmbSatinOutline* result):
	int i, j
	EmbSatinOutline outline
	EmbVector v1, temp
	EmbLine line, line1, line2
	float halfThickness = thickness / 2.0
	int intermediateOutlineCount = 2 * lines->length - 2
	outline.side1 = embArray_create(EMB_VECTOR)
	if (!outline.side1) {
		embLog("ERROR: embSatinOutline_generateSatinOutline() embArray_create()\n")
		return
	}
	outline.side2 = embArray_create(EMB_VECTOR)
	if (!outline.side2) {
		embLog("ERROR: embSatinOutline_generateSatinOutline() embArray_create()\n")
		return
	}

	for (i = 1; i < lines->length; i++) {
		j = (i - 1) * 2
		embArray_get(lines, &(line.start), j - 1)
		embArray_get(lines, &(line.end), j)

		embLine_normalVector(line, &v1, 1)

		embVector_multiply(v1, halfThickness, &temp)
		embVector_add(temp, line.start, &temp)
		embArray_add(outline.side1, &temp)
		embVector_add(temp, line.end, &temp)
		embArray_add(outline.side1, &temp)

		embVector_multiply(v1, -halfThickness, &temp)
		embVector_add(temp, line.start, &temp)
		embArray_add(outline.side2, &temp)
		embVector_add(temp, line.end, &temp)
		embArray_add(outline.side2, &temp)
	}

	if (!result) {
		embLog("ERROR: embSatinOutline_generateSatinOutline(), result==0\n")
		return
	}
	result->side1 = embArray_create(EMB_VECTOR)
	result->side2 = embArray_create(EMB_VECTOR)

	EmbVector a
	embArray_get(outline.side1, &a, 0)
	embArray_add(result->side1, &a)
	embArray_get(outline.side2, &a, 0)
	embArray_add(result->side2, &a)

	for (i = 3; i < intermediateOutlineCount; i += 2) {
		embArray_get(outline.side1, &(line1.start), i - 3)
		embArray_get(outline.side1, &(line1.end), i - 2)
		embArray_get(outline.side1, &(line2.start), i - 1)
		embArray_get(outline.side1, &(line2.end), i)
		embLine_intersectionPoint(line1, line2, &temp)
		embArray_add(result->side1, &temp)

		embArray_get(outline.side2, &(line1.start), i - 3)
		embArray_get(outline.side2, &(line1.end), i - 2)
		embArray_get(outline.side2, &(line2.start), i - 1)
		embArray_get(outline.side2, &(line2.end), i)
		embLine_intersectionPoint(line1, line2, &temp)
		embArray_add(result->side2, &temp)
	}

	embArray_get(outline.side1, &a, 2*lines->length - 3)
	embArray_add(result->side1, &a)
	embArray_get(outline.side2, &a, 2*lines->length - 3)
	embArray_add(result->side2, &a)
	result->length = lines->length
	ret


EmbArray* embSatinOutline_renderStitches(EmbSatinOutline* result, float density):
	int i, j, numberOfSteps
	EmbVector currTop, currBottom, topDiff, bottomDiff, midDiff
	EmbVector midLeft, midRight, topStep, bottomStep
	EmbVector a, b, c
	EmbArray* stitches = 0
	float midLength

	if (!result) {
		embLog("ERROR: embSatinOutline_renderStitches(), result==0\n")
		return 0
	}

	if (result->length > 0) {
		for (j = 0; j < result->length - 1; j++) {
			embArray_get(result->side1, &a, j + 1)
			embArray_get(result->side1, &b, j)
			embVector_subtract(a, b, &topDiff)
			embArray_get(result->side2, &a, j + 1)
			embArray_get(result->side2, &b, j)
			embVector_subtract(a, b, &bottomDiff)

			embArray_get(result->side1, &a, j)
			embArray_get(result->side2, &b, j)
			embVector_average(a, b, &midLeft)
			embArray_get(result->side1, &a, j + 1)
			embArray_get(result->side2, &b, j + 1)
			embVector_average(a, b, &midRight)

			embVector_subtract(midLeft, midRight, &midDiff)
			midLength = embVector_getLength(midDiff)

			numberOfSteps = (int)(midLength * density / 200)
			embVector_multiply(topDiff, 1.0 / numberOfSteps, &topStep)
			embVector_multiply(bottomDiff, 1.0 / numberOfSteps, &bottomStep)
			embArray_get(result->side1, &currTop, j)
			embArray_get(result->side2, &currBottom, j)

			for (i = 0; i < numberOfSteps; i++) {
				if (!stitches) {
					stitches = embArray_create(EMB_VECTOR)
				}
				embArray_add(stitches, &currTop)
				embArray_add(stitches, &currBottom)
				embVector_add(currTop, topStep, &currTop)
				embVector_add(currBottom, bottomStep, &currBottom)
			}
		}
		embArray_add(stitches, &currTop)
		embArray_add(stitches, &currBottom)
	}
	return stitches
	ret


unsigned int readFullSector(int file, unsigned int* numberOfDifatEntriesStillToRead)
CompoundFileDirectoryEntry(bcf_directory_entry *dir, int file)
readNextSector(int file)

/*! Constant representing the number of Double Indirect FAT entries in a single header */
const unsigned int NumberOfDifatEntriesInHeader = 109
const unsigned int sizeOfFatEntry = sizeof(unsigned int)
const unsigned int sizeOfDifatEntry = 4
const unsigned int sizeOfChainingEntryAtEndOfDifatSector = 4
const unsigned int sizeOfDirectoryEntry = 128
/* const int supportedMinorVersion = 0x003E
const int littleEndianByteOrderMark = 0xFFFE; */

int embPattern_write(EmbPattern* pattern, const char* fileName, int format):
	int file
	int r

	if (!fileName) {
		embLog("ERROR: ")
		embLog(fileName)
		embLog("(), fileName==0\n")
		return 0
	}

	if (!pattern->stitchList->length) {
		print_log_string(error_pattern_no_stitches)
		return 0
	}

	/* Check for an END stitch and add one if it is not present */
	EmbStitch st
	embArray_get(pattern->stitchList, &st, pattern->stitchList->length - 1)
	if (st.flags != END) {
		embPattern_addStitchRel(pattern, 0, 0, END, 1)
	}

	file = embFile_open(fileName, "wb", 0)
	if (!file) {
		print_log_string(error_pattern_open_file)
		return 0;    
	}

	r = 0
	switch (format) {
	case EMB_FORMAT_100:
		r = write100(pattern, file, fileName)
		break
	case EMB_FORMAT_10O:
		r = write10o(pattern, file, fileName)
		break
	case EMB_FORMAT_ART:
		print_log_string(error_format_not_supported)
		break
	case EMB_FORMAT_BMC:
		print_log_string(error_format_not_supported)
		break
	case EMB_FORMAT_BRO:
		r = writeBro(pattern, file, fileName)
		break
	case EMB_FORMAT_CND:
		print_log_string(error_format_not_supported)
		break
	case EMB_FORMAT_COL:
		r = writeCol(pattern, file, fileName)
		break
	case EMB_FORMAT_CSD:
		r = writeCsd(pattern, file, fileName)
		break
	case EMB_FORMAT_CSV:
		r = writeCsv(pattern, file, fileName)
		break
	case EMB_FORMAT_DAT:
		r = writeDat(pattern, file, fileName)
		break
	case EMB_FORMAT_DEM:
		print_log_string(error_format_not_supported)
		break
	case EMB_FORMAT_DSB:
		r = writeDsb(pattern, file, fileName)
		break
	case EMB_FORMAT_DST:
		r = writeDst(pattern, file, fileName)
		break
	case EMB_FORMAT_DSZ:
		r = writeDsz(pattern, file, fileName)
		break
	case EMB_FORMAT_DXF:
		r = writeDxf(pattern, file, fileName)
		break
	case EMB_FORMAT_EDR:
		r = writeEdr(pattern, file, fileName)
		break
	case EMB_FORMAT_EMD:
		r = writeEmd(pattern, file, fileName)
		break
	case EMB_FORMAT_EXP:
		r = writeExp(pattern, file, fileName)
		break
	case EMB_FORMAT_EXY:
		r = writeExy(pattern, file, fileName)
		break
	case EMB_FORMAT_EYS:
		print_log_string(error_format_not_supported)
		break
	case EMB_FORMAT_FXY:
		r = writeFxy(pattern, file, fileName)
		break
	case EMB_FORMAT_GC:
		/* Smoothie G-Code */
		print_log_string(error_format_not_supported)
		break
	case EMB_FORMAT_GNC:
		print_log_string(error_format_not_supported)
		break
	case EMB_FORMAT_GT: 
		r = writeGt(pattern, file, fileName)
		break
	case EMB_FORMAT_HUS:
		r = writeHus(pattern, file, fileName)
		break
	case EMB_FORMAT_INB:
		r = writeInb(pattern, file, fileName)
		break
	case EMB_FORMAT_INF:
		r = writeInf(pattern, file, fileName)
		break
	case EMB_FORMAT_JEF:
		r = writeJef(pattern, file, fileName)
		break
	case EMB_FORMAT_KSM:
		r = writeKsm(pattern, file, fileName)
		break
	case EMB_FORMAT_MAX:
		r = writeMax(pattern, file, fileName)
		break
	case EMB_FORMAT_MIT:
		r = writeMit(pattern, file, fileName)
		break
	case EMB_FORMAT_NEW:
		r = writeNew(pattern, file, fileName)
		break
	case EMB_FORMAT_OFM:
		r = writeOfm(pattern, file, fileName)
		break
	case EMB_FORMAT_PCD:
		r = writePcd(pattern, file, fileName)
		break
	case EMB_FORMAT_PCM:
		r = writePcm(pattern, file, fileName)
		break
	case EMB_FORMAT_PCQ:
		r = writePcq(pattern, file, fileName)
		break
	case EMB_FORMAT_PCS:
		r = writePcs(pattern, file, fileName)
		break
	case EMB_FORMAT_PEC:
		r = writePec(pattern, file, fileName)
		break
	case EMB_FORMAT_PEL:
		print_log_string(error_format_not_supported)
		break
	case EMB_FORMAT_PEM:
		print_log_string(error_format_not_supported)
		break
	case EMB_FORMAT_PES:
		r = writePes(pattern, file, fileName)
		break
	case EMB_FORMAT_PHB:
		r = writePhb(pattern, file, fileName)
		break
	case EMB_FORMAT_PHC:
		r = writePhc(pattern, file, fileName)
		break
	case EMB_FORMAT_PLT:
		r = writePlt(pattern, file, fileName)
		break
	case EMB_FORMAT_RGB:
		r = writeRgb(pattern, file, fileName)
		break
	case EMB_FORMAT_SEW:
		r = writeSew(pattern, file, fileName)
		break
	case EMB_FORMAT_SHV:
		r = writeShv(pattern, file, fileName)
		break
	case EMB_FORMAT_SST:
		r = writeSst(pattern, file, fileName)
		break
	case EMB_FORMAT_STX:
		r = writeStx(pattern, file, fileName)
		break
	case EMB_FORMAT_SVG:
		r = writeSvg(pattern, file, fileName)
		break
	case EMB_FORMAT_T01:
		r = writeT01(pattern, file, fileName)
		break
	case EMB_FORMAT_T09:
		r = writeT09(pattern, file, fileName)
		break
	case EMB_FORMAT_TAP:
		r = writeTap(pattern, file, fileName)
		break
	case EMB_FORMAT_THR:
		r = writeThr(pattern, file, fileName)
		break
	case EMB_FORMAT_TXT:
		r = writeTxt(pattern, file, fileName)
		break
	case EMB_FORMAT_U00:
		r = writeU00(pattern, file, fileName)
		break
	case EMB_FORMAT_U01:
		r = writeU01(pattern, file, fileName)
		break
	case EMB_FORMAT_VIP:
		r = writeVip(pattern, file, fileName)
		break
	case EMB_FORMAT_VP3:
		r = writeVp3(pattern, file, fileName)
		break
	case EMB_FORMAT_XXX:
		r = writeXxx(pattern, file, fileName)
		break
	case EMB_FORMAT_ZSK:
		r = writeZsk(pattern, file, fileName)
		break
	default:
		embLog("Emb format not recognised.")
		break
	}

	if (!r) {
		return r
	}

	fclose(file)
	return 0
	ret


int embPattern_read(EmbPattern* pattern, const char* fileName, int format):
	int file
	int r

	if (!pattern) {
		embLog("ERROR: embPattern_read(), pattern==0\n")
		return 0
	}
	if (!fileName) {
		embLog("ERROR: embPattern_read(), fileName==0\n")
		return 0
	}

	file = embFile_open(fileName, "rb", 0)
	if (!file) {
		embLog("ERROR: embPattern_read(), failed to open file\n")
		return 0
	}

	r = 0
	switch (format) {
	case EMB_FORMAT_100:
		r = read100(pattern, file, fileName)
		break
	case EMB_FORMAT_10O:
		r = read10o(pattern, file, fileName)
		break
	case EMB_FORMAT_ART:
		print_log_string(error_format_not_supported)
		break
	case EMB_FORMAT_BMC:
		print_log_string(error_format_not_supported)
		break
	case EMB_FORMAT_BRO:
		r = readBro(pattern, file, fileName)
		break
	case EMB_FORMAT_CND:
		print_log_string(error_format_not_supported)
		break
	case EMB_FORMAT_COL:
		r = readCol(pattern, file, fileName)
		break
	case EMB_FORMAT_CSD:
		r = readCsd(pattern, file, fileName)
		break
	case EMB_FORMAT_CSV:
		r = readCsv(pattern, file, fileName)
	call	readCsv
		break
	case EMB_FORMAT_DAT:
		r = readDat(pattern, file, fileName)
	call	readDat
		break
	case EMB_FORMAT_DEM:
		print_log_string(error_format_not_supported)
	call	readDem
		break
	case EMB_FORMAT_DSB:
		r = readDsb(pattern, file, fileName)
	call	readDsb
		break
	case EMB_FORMAT_DST:
		r = readDst(pattern, file, fileName)
	call	readDst
		break
	case EMB_FORMAT_DSZ:
		r = readDsz(pattern, file, fileName)
	call	readDsz
		break
	case EMB_FORMAT_DXF:
		r = readDxf(pattern, file, fileName)
	call	readDxf
		break
	case EMB_FORMAT_EDR:
		r = readEdr(pattern, file, fileName)
		break
	case EMB_FORMAT_EMD:
		r = readEmd(pattern, file, fileName)
		break
	case EMB_FORMAT_EXP:
		r = readExp(pattern, file, fileName)
		break
	case EMB_FORMAT_EXY:
		r = readExy(pattern, file, fileName)
		break
	case EMB_FORMAT_EYS:
		print_log_string(error_format_not_supported)
		break
	case EMB_FORMAT_FXY:
		r = readFxy(pattern, file, fileName)
		break
	case EMB_FORMAT_GC:
		/* Smoothie G-Code */
		print_log_string(error_format_not_supported)
		break
	case EMB_FORMAT_GNC:
		print_log_string(error_format_not_supported)
		break
	case EMB_FORMAT_GT:
		r = readGt(pattern, file, fileName)
		break
	case EMB_FORMAT_HUS:
		r = readHus(pattern, file, fileName)
		break
	case EMB_FORMAT_INB:
		r = readInb(pattern, file, fileName)
		break
	case EMB_FORMAT_INF:
		r = readInf(pattern, file, fileName)
		break
	case EMB_FORMAT_JEF:
		r = readJef(pattern, file, fileName)
		break
	case EMB_FORMAT_KSM:
		r = readKsm(pattern, file, fileName)
		break
	case EMB_FORMAT_MAX:
		r = readMax(pattern, file, fileName)
		break
	case EMB_FORMAT_MIT:
		r = readMit(pattern, file, fileName)
		break
	case EMB_FORMAT_NEW:
		r = readNew(pattern, file, fileName)
		break
	case EMB_FORMAT_OFM:
		r = readOfm(pattern, file, fileName)
		break
	case EMB_FORMAT_PCD:
		r = readPcd(pattern, file, fileName)
		break
	case EMB_FORMAT_PCM:
		r = readPcm(pattern, file, fileName)
		break
	case EMB_FORMAT_PCQ:
		r = readPcq(pattern, file, fileName)
		break
	case EMB_FORMAT_PCS:
		r = readPcs(pattern, file, fileName)
		break
	case EMB_FORMAT_PEC:
		r = readPec(pattern, file, fileName)
		break
	case EMB_FORMAT_PEL:
		print_log_string(error_format_not_supported)
		break
	case EMB_FORMAT_PEM:
		print_log_string(error_format_not_supported)
		break
	case EMB_FORMAT_PES:
		r = readPes(pattern, file, fileName)
		break
	case EMB_FORMAT_PHB:
		r = readPhb(pattern, file, fileName)
		break
	case EMB_FORMAT_PHC:
		r = readPhc(pattern, file, fileName)
		break
	case EMB_FORMAT_PLT:
		r = readPlt(pattern, file, fileName)
		break
	case EMB_FORMAT_RGB:
		r = readRgb(pattern, file, fileName)
		break
	case EMB_FORMAT_SEW:
		r = readSew(pattern, file, fileName)
		break
	case EMB_FORMAT_SHV:
		r = readShv(pattern, file, fileName)
		break
	case EMB_FORMAT_SST:
		r = readSst(pattern, file, fileName)
		break
	case EMB_FORMAT_STX:
		r = readStx(pattern, file, fileName)
		break
	case EMB_FORMAT_SVG:
		r = readSvg(pattern, file, fileName)
		break
	case EMB_FORMAT_T01:
		r = readT01(pattern, file, fileName)
		break
	case EMB_FORMAT_T09:
		r = readT09(pattern, file, fileName)
		break
	case EMB_FORMAT_TAP:
		r = readTap(pattern, file, fileName)
		break
	case EMB_FORMAT_THR:
		r = readThr(pattern, file, fileName)
		break
	case EMB_FORMAT_TXT:
		r = readTxt(pattern, file, fileName)
		break
	case EMB_FORMAT_U00:
		r = readU00(pattern, file, fileName)
		break
	case EMB_FORMAT_U01:
		r = readU01(pattern, file, fileName)
		break
	case EMB_FORMAT_VIP:
		r = readVip(pattern, file, fileName)
		break
	case EMB_FORMAT_VP3:
		r = readVp3(pattern, file, fileName)
		break
	case EMB_FORMAT_XXX:
		r = readXxx(pattern, file, fileName)
		break
	case EMB_FORMAT_ZSK:
		r = readZsk(pattern, file, fileName)
		break
	default:
		embLog("Emb format not recognised.")
		break
	}

	if (!r) {
		return r
	}

	fclose(file)

	/* Check for an END stitch and add one if it is not present */
	EmbStitch st
	embArray_get(pattern->stitchList, &st, pattern->stitchList->length - 1)
	if (st.flags != END) {
		embPattern_addStitchRel(pattern, 0, 0, END, 1)
	}

	return 1
	ret


/*
 * TODO: documentation.
 * (const char* fileName, const char* mode, int optional)
 * returns int
 */
embFile_open:
	oFile = open(fileName, O_RDWR | O_CREAT, 0666)

	if (!oFile) {
		if (!optional) {
			embLog("ERROR: Cannot open the fileName in the given mode.")
			embLog(fileName)
			embLog(mode)
		}
		return 0
	}
	return oFile
#endif
	ret


fclose:
	/* (int stream):
	return close(stream) */
	ret


/**
 * TODO: documentation.
 * ISSUE: the last line may get cut off in certain cases.
 * ISSUE: how are blank lines dealt with?
 */
embFile_readline:
#if 0
int embFile_readline(int stream, char* line, int maxLength):
	int i, pass
	char c
	pass = 1
	for (i = 0; i < maxLength - 1; i++) {
		if (!fread(&c, 1, 1, stream)) {
			pass = 0
			break
		}
		if (c == '\r') {
			if (!fread(&c, 1, 1, stream)) {
				pass = 0
				break
			}
			if (c != '\n') {
				fseek(stream, -1L, SEEK_CUR)
			}
			break
		}
		if (c == '\n') {
			break
		}
		*line = c
		line++
	}
	*line = 0
	return pass
#endif
	ret

/*
 * Pad the int stream with n bytes all with value c.
 *
 * Caller sets ebx to file descriptor.
 * Caller sets eax to length of padding (in spaces)
 */
file_pad_spaces:
	movl	$0x01, %edx
	movl	$dot, %ecx
	movl	$SYS_WRITE, %eax
	int	$0x80
	movl	(length), %edx
	subl	$1, %edx
	movl	%edx, (length)
	cmp	$0, %edx
	jnz	file_pad_spaces
	ret

/**
 * Copy a block of bytes from int in to int out, if the length argument
 * n is 0 then use null termination (i.e. a c string) otherwise copy that many
 * bytes.
 *
 * (int in, int offset, int out, int n)
 * return int
 */
embFile_copy:
	/*
	fseek(in, offset, SEEK_SET)
	*/
	movl	(length), %eax
	cmp	$0, %eax
	jnz	embFile_copy_null_terminated
	
	/*
	char c
	int i
	for (i=0; i<n; i++) {
		fread(&c, 1, 1, in)
		fwrite(&c, 1, 1, out)
	}
	*/
embFile_copy_:
	movl	$0x01, %edx
	movl	$buffer, %ecx
	movl	$SYS_WRITE, %eax
	int	$0x80
	movl	(length), %edx
	subl	$1, %edx
	movl	%edx, (length)
	cmp	$0, %edx
	ret
embFile_copy_null_terminated:
	/*
	char c = 1
	while (c) {
		fread(&c, 1, 1, in)
		fwrite(&c, 1, 1, out)
	}
	*/
	ret

/*
 * Open a temporary file that we assume will be deleted after fclose
 * is called on it.
 *
 * int tmpfile(void)
 *	return open("/tmp", O_RDWR | O_TMPFILE, 0666)
 */
tmpfile:
	ret


/*
 * TODO: documentation.
 * (int stream, const char* str)
 * returns int
 */
embFile_print:
	/* fwrite((void *)str, 1, string_length(str), stream) */
	ret


#if 0
bcf_file BcfFile

/**
 * TODO: documentation.
 */
int seekToSector(int file, const unsigned int sector):
	unsigned int offset = (sector + 1) * BcfFile.sectorSize
	return fseek(file, offset, SEEK_SET)
	ret


/**
 * TODO: documentation.
 */
int bcfFile_read(int file):
	unsigned int i, numberOfDirectoryEntriesPerSector, directorySectorToReadFrom, fatSectors

	fread(BcfFile.signature, 1, 8, file)
	fread(BcfFile.CLSID, 1, 16, file)
	embFile_readInt(file, &(BcfFile.minorVersion), 2)
	embFile_readInt(file, &(BcfFile.majorVersion), 2)
	embFile_readInt(file, &(BcfFile.byteOrder), 2)
	embFile_readInt(file, &(BcfFile.sectorShift), 2)
	embFile_readInt(file, &(BcfFile.miniSectorShift), 2)
	embFile_readInt(file, &(BcfFile.reserved1), 2)
	embFile_readInt(file, &(BcfFile.reserved2), 4)
	embFile_readInt(file, &(BcfFile.numberOfDirectorySectors), 4)
	embFile_readInt(file, &(BcfFile.numberOfFATSectors), 4)
	embFile_readInt(file, &(BcfFile.firstDirectorySectorLocation), 4)
	embFile_readInt(file, &(BcfFile.transactionSignatureNumber), 4)
	embFile_readInt(file, &(BcfFile.miniStreamCutoffSize), 4)
	embFile_readInt(file, &(BcfFile.firstMiniFATSectorLocation), 4)
	embFile_readInt(file, &(BcfFile.numberOfMiniFatSectors), 4)
	embFile_readInt(file, &(BcfFile.firstDifatSectorLocation), 4)
	embFile_readInt(file, &(BcfFile.numberOfDifatSectors), 4)

	/* version 3 uses 512 byte */
	if (BcfFile.majorVersion == 3) {
		BcfFile.sectorSize = 512
	}
	BcfFile.sectorSize = 4096

	if (!string_equal(BcfFile.signature, "\xd0\xcf\x11\xe0\xa1\xb1\x1a\xe1")) {
		embLog("Failed to parse header\n")
		embLog("bad header signature\n")
		return 0
	}

	BcfFile.fatSectorCount = emb_min_int(BcfFile.numberOfFATSectors, NumberOfDifatEntriesInHeader)

	for (i = 0; i < BcfFile.fatSectorCount; i++) {
		embFile_readInt(file, BcfFile.fatSectorEntries + i, 4)
	}

	for (i = fatSectors; i < NumberOfDifatEntriesInHeader; ++i) {
		unsigned int sectorRef
		embFile_readInt(file, &sectorRef, 4)
		if (sectorRef != CompoundFileSector_FreeSector) {
			embLog("ERROR: bcf_difat_create(), Unexpected sector value\n")
			/* TODO " %x at DIFAT[%d]\n", sectorRef, i); */
		}
	}

	/* parse DIFAT sectors */
	if (BcfFile.sectorSize > sizeOfChainingEntryAtEndOfDifatSector) {
		unsigned int numberOfDifatEntriesStillToRead = BcfFile.numberOfFATSectors - NumberOfDifatEntriesInHeader
		unsigned int difatSectorNumber = BcfFile.firstDifatSectorLocation
		while ((difatSectorNumber != CompoundFileSector_EndOfChain) && (numberOfDifatEntriesStillToRead > 0)) {
			seekToSector(file, difatSectorNumber)
			difatSectorNumber = readFullSector(file, &numberOfDifatEntriesStillToRead)
		}
	}

	BcfFile.numberOfEntriesInFatSector = BcfFile.sectorSize / sizeOfFatEntry
	BcfFile.fatEntryCount = 0
	for (i = 0; i < BcfFile.numberOfFATSectors; ++i) {
		unsigned int j, fatEntries_current, newSize
		unsigned int fatSectorNumber = BcfFile.fatSectorEntries[i]
		seekToSector(file, fatSectorNumber)

		/* load fat from sector */
		fatEntries_current = BcfFile.fatEntryCount
		newSize = fatEntries_current + BcfFile.numberOfEntriesInFatSector
		for (j = fatEntries_current; j < newSize; ++j) {
			embFile_readInt(file, BcfFile.fatEntries + j, 4)
		}
		BcfFile.fatEntryCount = newSize
	}

	/* numberOfDirectoryEntriesPerSector = BcfFile.sectorSize / sizeOfDirectoryEntry
	CompoundFileDirectory(numberOfDirectoryEntriesPerSector); */
	directorySectorToReadFrom = BcfFile.firstDirectorySectorLocation
	while (directorySectorToReadFrom != CompoundFileSector_EndOfChain) {
		seekToSector(file, directorySectorToReadFrom)
		readNextSector(file)
		directorySectorToReadFrom = BcfFile.fatEntries[directorySectorToReadFrom]
	}

	return 1
	ret


/**
 * TODO: documentation.
 */
int GetFile(bcf_file* bcfFile, int file, char* fileToFind):
	int filesize, currentSector, sizeToWrite, currentSize, totalSectors, i
	char input
	int fileOut = tmpfile()
	for (i=0; i<BcfFile.maxNumberOfDirectoryEntries; i++) {
		if (string_equal(fileToFind, BcfFile.dirEntries[i].directoryEntryName))
			break
	}
	filesize = BcfFile.dirEntries[i].streamSize

	currentSize = 0
	currentSector = BcfFile.dirEntries[i].startingSectorLocation
	totalSectors = (int)emb_ceil((float)filesize / BcfFile.sectorSize)
	for (i = 0; i < totalSectors; i++) {
		seekToSector(file, currentSector)
		sizeToWrite = emb_min_int(filesize - currentSize, BcfFile.sectorSize)
		fread(&input, 1, sizeToWrite, file)
		fwrite(&input, 1, sizeToWrite, fileOut)
		currentSize += sizeToWrite
		currentSector = BcfFile.fatEntries[currentSector]
	}
	return fileOut
	ret


/**
 * TODO: documentation.
 */
unsigned int readFullSector(int file, unsigned int* numberOfDifatEntriesStillToRead):
	unsigned int i, sectorRef, nextDifatSectorInChain
	unsigned int entriesToReadInThisSector = 0, entriesInDifat

	entriesInDifat = (BcfFile.sectorSize - sizeOfChainingEntryAtEndOfDifatSector) / sizeOfDifatEntry

	if (*numberOfDifatEntriesStillToRead > entriesInDifat) {
		entriesToReadInThisSector = entriesInDifat
		*numberOfDifatEntriesStillToRead -= entriesToReadInThisSector
	}
	else {
		entriesToReadInThisSector = *numberOfDifatEntriesStillToRead
		*numberOfDifatEntriesStillToRead = 0
	}

	for (i = 0; i < entriesToReadInThisSector; ++i) {
		embFile_readInt(file, &sectorRef, 4)
		BcfFile.fatSectorEntries[BcfFile.fatSectorCount] = sectorRef
		BcfFile.fatSectorCount++
	}
	for (i = entriesToReadInThisSector; i < entriesInDifat; ++i) {
		embFile_readInt(file, &sectorRef, 4)
		if (sectorRef != CompoundFileSector_FreeSector) {
			embLog("ERROR: readFullSector(), Unexpected sector value")
			/* TODO: end of message: %x at DIFAT[%d]]\n", sectorRef, i); */
		}
	}
	embFile_readInt(file, &nextDifatSectorInChain, 4)
	return nextDifatSectorInChain
	ret


/**
 * TODO: documentation.
 */
parseDirectoryEntryName(int file, bcf_directory_entry* dir):
	int i
	unsigned short unicodechar
	for (i = 0; i < 32; ++i) {
		embFile_readInt(file, &unicodechar, 2)
		if (unicodechar != 0x0000) {
			dir->directoryEntryName[i] = (char)unicodechar
		}
	}
	ret


/**
 * TODO: documentation.
 */
EmbTime parseTime(int file):
	EmbTime returnVal
#if 0
	unsigned int ft_low, ft_high
	/*embTime_time(&returnVal); TODO: use embTime_time() rather than time(). */
	embFile_readInt(file, &ft_low, 4)
	embFile_readInt(file, &ft_high, 4)
	/* TODO: translate to actual date time */
#endif
	returnVal.year = 1000; /* for testing */
	return returnVal
	ret


/**
 * TODO: documentation.
 */
CompoundFileDirectoryEntry(bcf_directory_entry *dir, int file):
	memory_set(dir->directoryEntryName, 0, 32)
	parseDirectoryEntryName(file, dir)
	embFile_readInt(file, &(dir->directoryEntryNameLength), 2)
	dir->objectType = (unsigned char)binaryReadByte(file)
	if ((dir->objectType != ObjectTypeStorage) && (dir->objectType != ObjectTypeStream) && (dir->objectType != ObjectTypeRootEntry)) {
		embLog("ERROR: CompoundFileDirectoryEntry(), unexpected object type:\n")
		/* TODO: "%d\n", dir->objectType); */
	}
	dir->colorFlag = (unsigned char)binaryReadByte(file)
	embFile_readInt(file, &(dir->leftSiblingId), 4)
	embFile_readInt(file, &(dir->rightSiblingId), 4)
	embFile_readInt(file, &(dir->childId), 4)
	/* guidSize = 16 */
	fread(dir->CLSID, 1, 16, file)
	embFile_readInt(file, &(dir->stateBits), 4)
	dir->creationTime = parseTime(file)
	dir->modifiedTime = parseTime(file)
	embFile_readInt(file, &(dir->startingSectorLocation), 4)
	embFile_readInt(file, &(dir->streamSize), 4); /* This should really be __int64 or long long, but for our uses we should never run into an issue */
	embFile_readInt(file, &(dir->streamSizeHigh), 4); /* top portion of int64 */
	ret


/**
 * TODO: documentation.
 */
readNextSector(int file):
	unsigned int i
	for (i = 0; i < BcfFile.maxNumberOfDirectoryEntries; ++i) {
		CompoundFileDirectoryEntry(BcfFile.dirEntries + i, file)
	}
	ret


/**
 * TODO: documentation.
 */
int embFormat_getExtension(const char* fileName, char* ending):
	int i
	const char* offset

	if (!fileName) {
		embLog("ERROR: embFormat_getExtension(), fileName==0\n")
		return 0
	}

	if (string_length(fileName) == 0) {
		return 0
	}

	offset = fileName + string_length(fileName)
	while (*offset != '.') {
		offset--
	}

	for (i=0; offset[i]; i++) {
		ending[i] = offset[i]
		if (offset[i] >= 'A' && offset[i] <= 'Z') {
			ending[i] -= 'A' + 'a'
		}
	}
	ending[i] = 0; /* terminate the string */

	return 1
	ret


EmbFormatList embFormat_data(int format):
	EmbFormatList f
	int out
	out = dereference_int(format_list)
	fseek(datafile, out+59*format, SEEK_SET)
	fread(embBuffer, 1, 59, datafile)
	embLog(embBuffer)
	
	memory_copy(f.extension, (char *)embBuffer, 6)
	memory_copy(f.description, (char *)(embBuffer+6), 50)
	f.reader = embBuffer[56]
	f.writer = embBuffer[57]
	f.type = embBuffer[58]

	return f
	ret


/**
 * Returns a pointer to an EmbReaderWriter if the \a fileName is a supported file type.
 */
int embReaderWriter_getByFileName(const char* fileName):
	int i
	char ending[10]

	if (!embFormat_getExtension(fileName, ending)) {
		return -1
	}

	/* checks the first character to see if it is the end symbol */
	for (i = 0; i < 61; i++) {
		EmbFormatList f
		f = embFormat_data(i)
		embLog(f.extension)
		if (string_equal(ending, f.extension)) {
			return i
		}
	}

	embLog("ERROR: embReaderWriter_getByFileName(), unsupported file type:")
	embLog(ending)
	return -1
	ret


char read100(EmbPattern* pattern, int file, const char* fileName):
	unsigned char b[4]
	EmbStitch st

	embPattern_loadExternalColorFile(pattern, fileName)
	while (fread(b, 1, 4, file) == 4) {
		/* What does byte b[1] do? Is it the color index? */
		st.flags = NORMAL
		st.x = (b[2] > 0x80) ? -(b[2] - 0x80) : b[2]
		st.y = (b[3] > 0x80) ? -(b[3] - 0x80) : b[3]
		/*if(!(b[0] & 0xFC)) st.flags = JUMP; TODO: review & fix */
		if (!(b[0] & 0x01))
			st.flags = STOP
		if (b[0] == 0x1F)
			st.flags = END
		st.color = 1
		st.x /= 10.0
		st.y /= 10.0
		embPattern_addStitchRel(pattern, st.x, st.y, st.flags, st.color)
	}

	return 1
	ret


char write100(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish write100 */
	ret


/*
 * (EmbPattern* pattern, int file, const char* fileName)
 * returns errorCode
 */
read10o:
	unsigned char b[3]

	embPattern_loadExternalColorFile(pattern, fileName)

	while (fread(b, 1, 3, file) == 3) {
		EmbStitch st
		st.flags = NORMAL
		st.y = b[1] / 10.0
		st.x = b[2] / 10.0
		if (b[0] & 0x20)
			st.x *= 1.0
		if (b[0] & 0x40)
			st.y *= 1.0
		if (b[0] & 0x01)
			st.flags = TRIM
		if ((b[0] & 0x5) == 5) {
			st.flags = STOP
		}
		if (b[0] == 0xF8 || b[0] == 0x91 || b[0] == 0x87) {
			break
		}
		embPattern_addStitchRel(pattern, st.x, st.y, st.flags, 1)
	}

	return 1
	ret


char write10o(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish write10o */
	ret


char readBro(EmbPattern* pattern, int file, const char* fileName):
	unsigned char x55
	char b[2]
	short unknown[5]
	char name[8]
	int stitchType

	embPattern_loadExternalColorFile(pattern, fileName)

	fread(&x55, 1, 1, file)
	embFile_readInt(file, unknown, 2); /* TODO: determine what this unknown data is */

	fread(name, 1, 8, file)
	embFile_readInt(file, unknown+1, 2); /* TODO: determine what this unknown data is */
	embFile_readInt(file, unknown+2, 2); /* TODO: determine what this unknown data is */
	embFile_readInt(file, unknown+3, 2); /* TODO: determine what this unknown data is */
	embFile_readInt(file, unknown+4, 2)

	fseek(file, 0x100, SEEK_SET)

	while (fread(b, 1, 2, file) == 2) {
		short b1, b2
		stitchType = NORMAL
		b1 = b[0]
		b2 = b[1]
		if (b1 == -128) {
			unsigned char bCode
			fread(&bCode, 1, 1, file)
			embFile_readInt(file, &b1, 2)
			embFile_readInt(file, &b2, 2)
			if (bCode == 2) {
				stitchType = STOP
			} else if (bCode == 3) {
				stitchType = TRIM
			} else if (bCode == 0x7E) {
				break
			}
		}
		embPattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1)
	}

	return 1
	ret


char writeBro(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish writeBro */
	ret


char readCol(EmbPattern* pattern, int file, const char* fileName):
	int nColors, i
	int num, blue, green, red
	EmbThread t
	char line[30]

	pattern->threads->length = 0

	embFile_readline(file, line, 30)
	nColors = emb_array_to_int(line)
	if (nColors < 1) {
		embLog("ERROR: Number of colors is zero.")
		return 0
	}
	for (i = 0; i < nColors; i++) {
		embFile_readline(file, line, 30)
		if (string_length(line) < 1) {
			embLog("ERROR: Empty line in col file.")
			return 0
		}
		/* Acts as a sscanf call. */
		char *blue = line
		char *green = line
		char *red = line
		int cur = 0
		for (i=0; i<30; i++) {
			if (line[i]==',') {
				line[i] = 0
				switch (cur) {
				case 0:
					blue = line+i+1
					cur++
					break
				case 1:
					green = line+i+1
					cur++
					break
				case 2:
					red = line+i+1
					cur++
					break
				default:
					break
				}
			}
		}
		if (cur != 3) {
			break
		}
		t.color.r = (unsigned char)emb_array_to_int(red)
		t.color.g = (unsigned char)emb_array_to_int(green)
		t.color.b = (unsigned char)emb_array_to_int(blue)
		/* sscanf call finishes here */
		string_copy(t.catalogNumber, "NULL")
		string_copy(t.description, "NULL")
		embPattern_addThread(pattern, t)
	}
	return 1
	ret


char writeCol(EmbPattern* pattern, int file, const char* fileName):
	int i
	char *buffer = (char*)embBuffer

	writeInt(buffer, pattern->threads->length, 6)
	embFile_print(file, "\r\n")
	for (i = 0; i < pattern->threads->length; i++) {
		EmbColor c
		c = pattern_thread(pattern, i).color
		writeInt(file, i, 3)
		embFile_print(file, ",")
		writeInt(file, (int)c.r, 3)
		embFile_print(file, ",")
		writeInt(file, (int)c.g, 3)
		embFile_print(file, ",")
		writeInt(file, (int)c.b, 3)
		embFile_print(file, "\r\n")
	}
	return 1
	ret


int csd_sub_mask
int csd_xor_mask

#define CsdSubMaskSize 479
#define CsdXorMaskSize 501

BuildDecryptionTable(int seed):
	int i
	const int mul1 = 0x41C64E6D
	const int add1 = 0x3039
	char c

	for (i = 0; i < CsdSubMaskSize; i++) {
		seed *= mul1
		seed += add1
		c = (char)((seed >> 16) & 0xFF)
		fwrite(&c, 1, 1, csd_sub_mask)
	}
	for (i = 0; i < CsdXorMaskSize; i++) {
		seed *= mul1
		seed += add1
		c = (char)((seed >> 16) & 0xFF)
		fwrite(&c, 1, 1, csd_xor_mask)
	}
	ret


unsigned char DecodeCsdByte(long fileOffset, unsigned char val, int type):
	int newOffset, csd_table
	char _xorMask, _subMask

	csd_table = dereference_int(csd_decoding_table)
	get_str(embBuffer, csd_table)

	fileOffset = fileOffset - 1
	if (type != 0) {
		int final
		int fileOffsetHigh = (int)(fileOffset & 0xFFFFFF00)
		int fileOffsetLow = (int)(fileOffset & 0xFF)

		newOffset = fileOffsetLow
		fileOffsetLow = fileOffsetHigh
		final = fileOffsetLow % 0x300
		if (final != 0x100 && final != 0x200) {
			newOffset = embBuffer[newOffset] | fileOffsetHigh
		} else if (final != 0x100 && final == 0x200) {
			if (newOffset == 0) {
				fileOffsetHigh = fileOffsetHigh - 0x100
			}
			newOffset = embBuffer[newOffset] | fileOffsetHigh
		} else if (newOffset != 1 && newOffset != 0) {
			newOffset = embBuffer[newOffset] | fileOffsetHigh
		} else {
			fileOffsetHigh = fileOffsetHigh - 0x100
			newOffset = embBuffer[newOffset] | fileOffsetHigh
		}
	} else {
		newOffset = (int)fileOffset
	}

	fseek(csd_xor_mask, newOffset % CsdXorMaskSize, SEEK_SET)
	fread(&_xorMask, 1, 1, csd_xor_mask)

	fseek(csd_sub_mask, newOffset % CsdSubMaskSize, SEEK_SET)
	fread(&_subMask, 1, 1, csd_sub_mask)

	return (unsigned char)(val ^ _xorMask) - _subMask
	ret


char readCsd(EmbPattern* pattern, int file, const char* fileName):
	int i, type = 0
	unsigned char identifier[8]
	unsigned char unknown1, unknown2
	char dx = 0, dy = 0
	int colorChange = -1
	int flags
	char endOfStream = 0
	unsigned char colorOrder[14]

	csd_sub_mask = tmpfile()
	csd_xor_mask = tmpfile()

	binaryReadBytes(file, identifier, 8); /* TODO: check return value */

	if (identifier[0] != 0x7C && identifier[2] != 0xC3) {
		type = 1
	}
	if (type == 0) {
		BuildDecryptionTable(0xC)
	} else {
		BuildDecryptionTable(identifier[0])
	}
	/* save embFile function calls by loading in a chunk */
	fread(embBuffer, 1, 16*4, file)
	for (i = 0; i < 16; i++) {
		EmbThread thread
		thread.color.r = DecodeCsdByte(ftell(file), embBuffer[3*i+0], type)
		thread.color.g = DecodeCsdByte(ftell(file), embBuffer[3*i+1], type)
		thread.color.b = DecodeCsdByte(ftell(file), embBuffer[3*i+2], type)
		string_copy(thread.catalogNumber, "")
		string_copy(thread.description, "")
		embPattern_addThread(pattern, thread)
	}
	unknown1 = DecodeCsdByte(ftell(file), embBuffer[3*16+0], type)
	unknown2 = DecodeCsdByte(ftell(file), embBuffer[3*16+1], type)

	for (i = 0; i < 14; i++) {
		colorOrder[i] = (unsigned char)DecodeCsdByte(ftell(file), embBuffer[3*16+2+i], type)
	}
	for (i = 0; !endOfStream; i++) {
		char negativeX, negativeY
		fread(embBuffer, 1, 3, file)
		unsigned char b0 = DecodeCsdByte(ftell(file), embBuffer[0], type)
		unsigned char b1 = DecodeCsdByte(ftell(file), embBuffer[1], type)
		unsigned char b2 = DecodeCsdByte(ftell(file), embBuffer[2], type)

		if (b0 == 0xF8 || b0 == 0x87 || b0 == 0x91) {
			break
		}
		negativeX = ((b0 & 0x20) > 0)
		negativeY = ((b0 & 0x40) > 0)
		b0 = (unsigned char)(b0 & (0xFF ^ 0xE0))

		if ((b0 & 0x1F) == 0)
			flags = NORMAL
		else if ((b0 & 0x0C) > 0) {
			flags = STOP
			if (colorChange >= 14) {
				embLog("Invalid color change detected\n")
			}
			embPattern_changeColor(pattern, colorOrder[colorChange % 14])
			colorChange += 1
		} else if ((b0 & 0x1F) > 0)
			flags = TRIM
		else
			flags = NORMAL
		dx = (char)b2
		dy = (char)b1
		if (negativeX)
			dx = (char)-dx
		if (negativeY)
			dy = (char)-dy
		if (flags == STOP)
			embPattern_addStitchRel(pattern, 0, 0, flags, 1)
		else
			embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1)
	}

	fclose(csd_xor_mask)
	fclose(csd_sub_mask)

	return 1
	ret


char writeCsd(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish writeCsd */
	ret


const char* csvStitchFlagToStr(int flags):
	int i, p
	switch (flags) {
	case NORMAL:
		i = 0
		break
	case JUMP:
		i = 1
		break
	case TRIM:
		i = 2
		break
	case STOP:
		i = 3
		break
	case END:
		i = 4
		break
	default:
		i = 5
		break
	}
	p = double_dereference_int(stitch_labels, i)
	get_str((char*)embBuffer, p)
	return (char*)embBuffer
	ret


char csvStrToStitchFlag(const char* str):
	int i, p
	char out[] = {NORMAL, JUMP, TRIM, STOP, END}
	if (!str) {
		embLog("ERROR: csvStrToStitchFlag(), str==0\n")
		return -1
	}
	for (i=0; i<5; i++) {
		p = double_dereference_int(stitch_labels, i)
		get_str((char*)embBuffer, p)
		if (string_equal(str, (char*)embBuffer)) {
			return out[i]
		}
	}
	return -1
	ret


char readCsv(EmbPattern* pattern, int file, const char* fileName):
	int numColorChanges, pos, cellNum, process, csvMode, expect, flags
	float xx, yy
	unsigned char r = 0, g = 0, b = 0
	char c
	char* buff = (char*)embBuffer

	numColorChanges = 0
	pos = 0
	cellNum = 0
	process = 0
	csvMode = CSV_MODE_NULL
	expect = CSV_EXPECT_QUOTE1
	flags = 0
	while (fread(&c, 1, 1, file)) {
		switch (c) {
		case '"':
			if (expect == CSV_EXPECT_QUOTE1) {
				expect = CSV_EXPECT_QUOTE2
			} else if (expect == CSV_EXPECT_QUOTE2)
				expect = CSV_EXPECT_COMMA
			break
		case ',':
			if (expect == CSV_EXPECT_COMMA) {
				process = 1
			}
			break
		case '\n':
			if (expect == CSV_EXPECT_COMMA) {
				process = 1
			} else if (expect == CSV_EXPECT_QUOTE1) {
				/* Do Nothing. We encountered a blank line. */
			} else {
				print_log_string(error_read_csv_1)
				return 0
			}
			break
		}

		if (process) {
			buff[pos] = 0
			pos = 0
			process = 0
			cellNum++
			expect = CSV_EXPECT_QUOTE1
			if (csvMode == CSV_MODE_NULL) {
				csvMode = buff[0]
			} else if (csvMode == CSV_MODE_VARIABLE) {
				/* Do Nothing */
			} else if (csvMode == CSV_MODE_THREAD) {
				if (cellNum == 2) {
					/* Do Nothing. Ignore Thread Number */
				} else if (cellNum == 3)
					r = (unsigned char)emb_array_to_int(buff)
				else if (cellNum == 4)
					g = (unsigned char)emb_array_to_int(buff)
				else if (cellNum == 5)
					b = (unsigned char)emb_array_to_int(buff)
				else if (cellNum == 6) {
					/* TODO: Thread Description */
				} else if (cellNum == 7) {
					/* TODO: Thread Catalog Number */
					EmbThread t
					t.color.r = r
					t.color.g = g
					t.color.b = b
					/* TODO */
					string_copy(t.description, "NULL")
					string_copy(t.catalogNumber, "NULL")
					embPattern_addThread(pattern, t)
					csvMode = CSV_MODE_NULL
					cellNum = 0
				} else {
					/* TODO: error */
					return 0
				}
			} else if (csvMode == CSV_MODE_STITCH) {
				if (cellNum == 2) {
					flags = csvStrToStitchFlag(buff)
					if (flags == STOP)
						numColorChanges++
					if (flags == END)
						break
				} else if (cellNum == 3) {
					xx = emb_array_to_float(buff)
				} else if (cellNum == 4) {
					yy = emb_array_to_float(buff)
					embPattern_addStitchAbs(pattern, xx, yy, flags, 1)
					csvMode = CSV_MODE_NULL
					cellNum = 0
				} else {
					/* TODO: error */
					return 0
				}
			}

			if (c == '\n') {
				csvMode = CSV_MODE_NULL
				cellNum = 0
			}
		} else {
			if (expect == CSV_EXPECT_QUOTE2 && c != '"')
				buff[pos++] = c
		}
	}

	/* if not enough colors defined, fill in random colors */
	while (pattern->threads->length < numColorChanges) {
		embPattern_addThread(pattern, embThread_getRandom())
	}

	return 1
	ret


/* Copy a block of bytes from the datafile to the elected file
 * if length == 0 use null termination to end copy, otherwise
 * copy length bytes.
 */
string_to_file(int file, int offset, int length):
	char ch = 1
	int i
	fseek(datafile, dereference_int(offset), SEEK_SET)
	if (length == 0) {
		while (ch) {
			fread(&ch, 1, 1, datafile)
			if (ch) {
				fwrite(&ch, 1, 1, file)
			}
		}
	}
	else {
		for (i=0; i<length; i++) {
			fread(&ch, 1, 1, datafile)
			fwrite(&ch, 1, 1, file)
		}
	}
	ret


/* 
 */
print_log_string(int index):
	/* acts as an error number */
	emb_int_to_array((char*)embBuffer, index, 5)
	embLog((char*)embBuffer)
	get_str((char*)embBuffer, 4*index)
	embLog((char*)embBuffer)
	ret


char writeCsv(EmbPattern* pattern, int file, const char* fileName):
	EmbStitch st
	EmbRect boundingRect
	EmbThread thr
	int i
	int stitchCount = 0

	stitchCount = pattern->stitchList->length

	boundingRect = embPattern_calcBoundingBox(pattern)

	if (!stitchCount) {
		print_log_string(error_write_csv_0)
		return 0
	}

	/* write header */
	string_to_file(file, csv_header, 0)

	/* write variables */
	embFile_print(file, "\"#\",\"[VAR_NAME]\",\"[VAR_VALUE]\"\n")
	embFile_print(file, "\">\",\"STITCH_COUNT:\",\"")
	writeInt(file, stitchCount, 6)
	embFile_print(file, "\"\n")
	embFile_print(file, "\">\",\"threads->length:\",\"")
	writeInt(file, pattern->threads->length, 6)
	embFile_print(file, "\"\n")
	writeFloatWrap(file, "\">\",\"EXTENTS_LEFT:\",\"", boundingRect.left, "\"\n")
	writeFloatWrap(file, "\">\",\"EXTENTS_TOP:\",\"", boundingRect.top, "\"\n")
	writeFloatWrap(file, "\">\",\"EXTENTS_RIGHT:\",\"", boundingRect.right, "\"\n")
	writeFloatWrap(file, "\">\",\"EXTENTS_BOTTOM:\",\"", boundingRect.bottom, "\"\n")
	writeFloatWrap(file, "\">\",\"EXTENTS_WIDTH:\",\"", embRect_width(boundingRect), "\"\n")
	writeFloatWrap(file, "\">\",\"EXTENTS_HEIGHT:\",\"", embRect_height(boundingRect), "\"\n")
	embFile_print(file, "\n")

	/* write colors */
	embFile_print(file, "\"#\",\"[THREAD_NUMBER]\",\"[RED]\",\"[GREEN]\",\"[BLUE]\",\"[DESCRIPTION]\",\"[CATALOG_NUMBER]\"\n")
	for (i = 0; i < pattern->threads->length; i++) {
		thr = pattern_thread(pattern, i)
		/* TODO: fix segfault that backtraces here when libembroidery-convert from dst to csv. */
		embFile_print(file, "\"$\",\"")
		writeInt(file, i + 1, 3)
		embFile_print(file, "\",\"")
		writeInt(file, (int)thr.color.r, 4)
		embFile_print(file, "\",\"")
		writeInt(file, (int)thr.color.g, 4)
		embFile_print(file, "\",\"")
		writeInt(file, (int)thr.color.b, 4)
		embFile_print(file, "\",\"")
		embFile_print(file, thr.description)
		embFile_print(file, "\",\"")
		embFile_print(file, thr.catalogNumber)
		embFile_print(file, "\"\n")
	}
	embFile_print(file, "\n")

	/* write stitches */
	embFile_print(file, "\"#\",\"[STITCH_TYPE]\",\"[X]\",\"[Y]\"\n")
	for (i = 0; i < pattern->stitchList->length; i++) {
		embArray_get(pattern->stitchList, &st, i)
		embFile_print(file, "\"*\",\"")
		embFile_print(file, csvStitchFlagToStr(st.flags))
		embFile_print(file, "\",\"")
		writeFloat(file, st.x)
		embFile_print(file, "\",\"")
		writeFloat(file, st.y)
		embFile_print(file, "\"\n")
	}

	return 1
	ret


char readDat(EmbPattern* pattern, int file, const char* fileName):
	unsigned char b0
	short stitchesRemaining
	int fileLength, b1, b2, stitchType

	embPattern_loadExternalColorFile(pattern, fileName)
	fseek(file, 0x00, SEEK_END)
	fileLength = ftell(file)
	fseek(file, 0x02, SEEK_SET)
	embFile_readInt(file, &stitchesRemaining, 2)
	fseek(file, 0x100, SEEK_SET)

	while (ftell(file) < fileLength) {
		b1 = (int)binaryReadUInt8(file)
		b2 = (int)binaryReadUInt8(file)
		b0 = binaryReadByte(file)

		stitchType = NORMAL
		stitchesRemaining--

		if ((b0 & 0x02) == 0)
			stitchType = TRIM

		if (b0 == 0x87) {
			stitchType = STOP
		}
		if (b0 == 0xF8) {
			break
		}
		if (b1 >= 0x80) {
			b1 = -(b1 & 0x7F)
		}
		if (b2 >= 0x80) {
			b2 = -(b2 & 0x7F)
		}
		embPattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1)
	}

	return 1
	ret


char writeDat(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish writeDat */
	ret


char readDsb(EmbPattern* pattern, int file, const char* fileName):
	unsigned char b[4]
	unsigned char header[512]
	embPattern_loadExternalColorFile(pattern, fileName)
	fread(header, 1, 512, file)

	fseek(file, 0x200, SEEK_SET)
	while (fread(b, 1, 3, file) == 3) {
		int x, y
		unsigned char ctrl
		int stitchType = NORMAL

		ctrl = b[0]
		y = b[1]
		x = b[2]

		if (ctrl & 0x01)
			stitchType = TRIM
		if (ctrl & 0x20)
			x = -x
		if (ctrl & 0x40)
			y = -y
		/* ctrl & 0x02 - Speed change? */ /* TODO: review this line */
		/* ctrl & 0x04 - Clutch? */ /* TODO: review this line */
		if ((ctrl & 0x05) == 0x05) {
			stitchType = STOP
		}
		if (ctrl == 0xF8 || ctrl == 0x91 || ctrl == 0x87) {
			break
		}
		embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1)
	}
	return 1
	ret


char writeDsb(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish writeDsb */
	ret


/* .DST (Tajima) embroidery file read/write routines
 * Format comments are thanks to tspilman@dalcoathletic.com who's
 * notes appeared at http://www.wotsit.org under Tajima Format.
 */

encode_record(int file, int *dx, int flags):
	unsigned char b[3]

	encode_dst_ternary(dx, b)

	b[2] |= (char)3

	if (flags & END) {
		b[0] = 0
		b[1] = 0
		b[2] = (char)-13
	}

	/* if(flags & TRIM)
	{
		int v = 5
		int dx = (int)(x/v), dy = (int)(y/v)
		for(i = 1; i < v; i++)
		{
			encode_record(file, dx, dy, JUMP)
		}
		encode_record(file, x - (dx * (v - 1)), y - (dy * (v - 1)), JUMP)
		return
	} */
	if (flags & (JUMP | TRIM)) {
		b[2] = (char)(b[2] | 0x83)
	}
	if (flags & STOP) {
		b[2] = (char)(b[2] | 0xC3)
	}

	fwrite(b, 1, 3, file)
	ret


/*convert 2 characters into 1 int for case statement */
/*#define cci(s) (s[0]*256+s[1]) */
#define cci(c1, c2) (c1 * 256 + c2)

set_dst_variable(EmbPattern* pattern, char* var, char* val):
	unsigned int i
	EmbThread t

	for (i = 0; i <= (unsigned int)string_length(var); i++) {
		/* uppercase the var */
		if (var[i] >= 'a' && var[i] <= 'z') {
			var[i] += 'A' - 'a'
		}
	}

	/* macro converts 2 characters to 1 int, allows case statement... */
	switch (cci(var[0], var[1])) {
	case cci('L', 'A'): /* Design Name (LA) */
		/*pattern->set_variable("Design_Name",val); TODO: review this line. */
		break
	case cci('S', 'T'): /* Stitch count, 7 digits padded by leading 0's */
	case cci('C', 'O'): /* Color change count, 3 digits padded by leading 0's */
	case cci('+', 'X'): /* Design extents (+/-X,+/-Y), 5 digits padded by leading 0's */
	case cci('-', 'X'):
	case cci('+', 'Y'):
	case cci('-', 'Y'):
		/* don't store these variables, they are recalculated at save */
		break
	case cci('A', 'X'): /* Relative coordinates of last point, 6 digits, padded with leading spaces, first char may be +/- */
	case cci('A', 'Y'):
	case cci('M', 'X'): /* Coordinates of last point in previous file of multi-volume design, 6 digits, padded with leading spaces, first char may be +/- */
	case cci('M', 'Y'):
		/* store these variables as-is, they will be converted to numbers and back at save; */
		/*pattern->set_variable(var,val); TODO: review this line. */
		break
	case cci('P', 'D'):
		/* store this string as-is, it will be saved as-is, 6 characters */
		if (string_length(val) != 6) {
			/*pattern->messages.add("Warning: in DST file read, PD is not 6 characters, but ",(int)string_length(val)); */
		}
		/*pattern->set_variable(var,val);*/
		break
		/* Begin extended fields section */
	case cci('A', 'U'): /* Author string, arbitrary length */
	case cci('C', 'P'): /* Copyright string, arbitrary length */
		/*pattern->set_variable(var,val); TODO: review this line. */
		break
	case cci('T', 'C'): /*Thread Color: #RRGGBB,Description,Catalog Number (1st field RGB hex values, 2nd&3rd fields optional arbitrary length) */
		/* TODO: review these lines below.
		description=split_cell_str(val,2)
		catalog_number=split_cell_str(val,3)
		*/
		t.color = embColor_fromHexStr(val)
		string_copy(t.description, "NULL")
		string_copy(t.catalogNumber, "NULL")
		embPattern_addThread(pattern, t)
		break
	default:
		/* unknown field, just save it. */
		/*pattern->set_variable(var,val); TODO: review this line. */
		break
	}
	ret


char readDst(EmbPattern* pattern, int file, const char* fileName):
	char var[3]; /* temporary storage variable name */
	unsigned char b[3]
	int i, valpos
	char *header, *val

	header = (char*)embBuffer
	val = (char*)(embBuffer+512)

	/* TODO: review commented code below
	pattern->clear()
	pattern->set_variable("file_name",filename)
	*/

	embPattern_loadExternalColorFile(pattern, fileName)
	fread(header, 1, 512, file)

	/* TODO: It would probably be a good idea to validate file before accepting it. */

	/* Fill variables from header fields.
	 * See the section on Tajima dst format in the manual for details.
	 */
	for (i = 0; i < 512; i++) {
		if (header[i] == ':' && i > 1) {
			var[0] = header[i - 2]
			var[1] = header[i - 1]
			var[2] = '\0'
			valpos = i + 1
			for (i++; i < 512; i++) {
				/* don't accept : without CR because there's a bug below:
				 * i-valpos must be > 0 which is not the case if
				 * the : is before the third character. */
				if (header[i] == 13 /*||header[i]==':'*/) /* 0x0d = carriage return */
				{
					if (header[i] == ':') /* : indicates another variable, CR was missing! */
					{
						i -= 2
					}
					memory_copy(val, &header[valpos], (size_t)(i - valpos))
					val[i - valpos] = '\0'
					set_dst_variable(pattern, var, val)
					break
				}
			}
		}
	}

	while (fread(b, 1, 3, file) == 3) {
		int x[2], flags
		if (b[2] == 0xF3) {
			break
		}
		decode_dst_ternary(x, b)
		flags = (bit(b[2], 8) * JUMP) | (bit(b[2], 7) * STOP)
		embPattern_addStitchRel(pattern, x[0] / 10.0, x[1] / 10.0, flags, 1)
	}

	/* embPattern_combineJumpStitches(pattern, 5); */
	return 1
	ret


char writeDst(EmbPattern* pattern, int file, const char* fileName):
	EmbRect boundingRect
	int pos[2], dx[2], i
	EmbStitch st

	embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1)

	/* TODO: make sure that pattern->threads->length defaults to 1 in new patterns */
	boundingRect = embPattern_calcBoundingBox(pattern)

	/* pad to 16 char */
	int namelen = string_length(pattern->name)
	for (i=namelen; i<16; i++) {
		pattern->name[i] = ' '
	}
	pattern->name[16] = 0
	embFile_print(file, "LA:")
	embFile_print(file, pattern->name)
	embFile_print(file, "\x0d")

	/* TODO: check that the number of characters adds to 125, or pad
	correctly. */
	embFile_print(file, "ST:")
	writeInt(file, pattern->stitchList->length, 6)
	embFile_print(file, "\x0dCO:")
	writeInt(file, pattern->threads->length - 1, 6); /* number of color changes, not number of colors! */
	embFile_print(file, "\x0d+X:")
	writeInt(file, (int)(boundingRect.right * 10.0), 6)
	embFile_print(file, "\x0d-X:")
	writeInt(file, (int)(emb_fabs(boundingRect.left) * 10.0), 6)
	embFile_print(file, "\x0d+Y:")
	writeInt(file, (int)(boundingRect.bottom * 10.0), 6)
	embFile_print(file, "\x0d-Y:")
	writeInt(file, (int)(emb_fabs(boundingRect.top) * 10.0), 6)
	embFile_print(file, "\x0d")

	/* TODO: review the code below */
	/* will return null pointer if not defined */
	if (pattern->pd[0] == 0 || string_length(pattern->pd) != 6) {
		/* pd is not valid, so fill in a default consisting of "******" */
		string_copy(pattern->pd, "******")
	}
	embFile_print(file, "AX:+")
	writeInt(file, pattern->ax, 6); /* will return 0 if not defined */
	embFile_print(file, "\x0dAY:+")
	writeInt(file, pattern->ay, 6)
	embFile_print(file, "\x0dMX:+")
	writeInt(file, pattern->mx, 6)
	embFile_print(file, "\x0dMY:+")
	writeInt(file, pattern->my, 6)
	embFile_print(file, "\x0dPD:")
	embFile_print(file, pattern->pd); /* 6 char, swap for fwrite */
	embFile_print(file, "\x0d\x1a"); /* 0x1a is the code for end of section. */

	embFile_pad(file, ' ', 512-125)

	/* write stitches */
	pos[0] = 0
	pos[1] = 0
	for (i = 0; i < pattern->stitchList->length; i++) {
		embArray_get(pattern->stitchList, &st, i)
		/* convert from mm to 0.1mm for file format */
		dx[0] = round(st.x * 10.0) - pos[0]
		dx[1] = round(st.y * 10.0) - pos[1]
		pos[0] = round(st.x * 10.0)
		pos[1] = round(st.y * 10.0)
		encode_record(file, dx, st.flags)
	}
	/* finish file with a terminator character */
	fwrite("\xA1\0\0", 1, 3, file)
	return 1
	ret


char readDsz(EmbPattern* pattern, int file, const char* fileName):
	embPattern_loadExternalColorFile(pattern, fileName)

	fseek(file, 0x200, SEEK_SET)
	while (fread(embBuffer, 1, 3, file) == 3) {
		int x, y
		unsigned char ctrl
		int stitchType = NORMAL

		y = embBuffer[0]
		x = embBuffer[1]
		ctrl = embBuffer[2]

		if (ctrl & 0x01)
			stitchType = TRIM
		if (ctrl & 0x20)
			y = -y
		if (ctrl & 0x40)
			x = -x

		if (ctrl & 0x0E) {
			int headNumber = (ctrl & 0x0E) >> 1
			stitchType = STOP
		}
		if (ctrl & 0x10) {
			break
		}
		embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitchType, 1)
	}

	return 1
	ret


char writeDsz(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish writeDsz */
	ret


char readDxf(EmbPattern* pattern, int file, const char* fileName):
	char* dxfVersion = ""
	char* section = ""
	char* tableName = ""
	char* layerName = ""
	char* entityType = ""
	/* layer_names uses the same indexing as the EmbColor array, no need for hash table
	char layer_names[MAX_LAYERS][MAX_LAYER_NAME_LENGTH]
	*/
	int eof = 0; /* End Of File */

	float bulge = 0.0, firstX = 0.0, firstY = 0.0, x = 0.0, y, prevX = 0.0, prevY = 0.0
	char firstStitch = 1
	char bulgeFlag = 0
	int fileLength = 0
	char *buffer = (char*)embBuffer

	fseek(file, 0L, SEEK_END)

	fileLength = ftell(file)
	fseek(file, 0L, SEEK_SET)

	while (ftell(file) < fileLength) {
		embFile_readline(file, buffer, 1000)
		if ((string_equal(buffer, "HEADER")) || (string_equal(buffer, "CLASSES")) || (string_equal(buffer, "TABLES")) || (string_equal(buffer, "BLOCKS")) || (string_equal(buffer, "ENTITIES")) || (string_equal(buffer, "OBJECTS")) || (string_equal(buffer, "THUMBNAILIMAGE"))) {
			section = buffer
			embLog("SECTION:\n")
			embLog(buffer)
		}
		if (string_equal(buffer, "ENDSEC")) {
			section = ""
			embLog("ENDSEC:\n")
			embLog(buffer)
		}
		if ((string_equal(buffer, "ARC")) || (string_equal(buffer, "CIRCLE")) || (string_equal(buffer, "ELLIPSE")) || (string_equal(buffer, "LINE")) || (string_equal(buffer, "LWPOLYLINE")) || (string_equal(buffer, "POINT"))) {
			entityType = buffer
		}
		if (string_equal(buffer, "EOF")) {
			eof = 1
		}

		if (string_equal((char *)section, "HEADER")) {
			if (string_equal(buffer, "$ACADVER")) {
				embFile_readline(file, buffer, 1000)
				embFile_readline(file, dxfVersion, 1000)
				/* TODO: Allow these versions when POLYLINE is handled. */
				/*
				if ((string_equal(dxfVersion, DXF_VERSION_R10))
					|| (string_equal(dxfVersion, DXF_VERSION_R11))
					|| (string_equal(dxfVersion, DXF_VERSION_R12))
					|| (string_equal(dxfVersion, DXF_VERSION_R13)))
					return 0
				*/
			}
		} else if (string_equal((char *)section, "TABLES")) {
			if (string_equal(buffer, "ENDTAB")) {
				tableName = NULL
			}

			if (tableName == NULL) {
				if (string_equal(buffer, "2")) /* Table Name */
				{
					embFile_readline(file, tableName, 1000)
				}
			} else if (string_equal(tableName, "LAYER")) {
				/* Common Group Codes for Tables */
				if (string_equal(buffer, "5")) /* Handle */
				{
					embFile_readline(file, buffer, 1000)
					continue
				} else if (string_equal(buffer, "330")) /* Soft Pointer */
				{
					embFile_readline(file, buffer, 1000)
					continue
				} else if (string_equal(buffer, "100")) /* Subclass Marker */
				{
					embFile_readline(file, buffer, 1000)
					continue
				} else if (string_equal(buffer, "70")) /* Number of Entries in Table */
				{
					embFile_readline(file, buffer, 1000)
					continue
				}
				/* The meaty stuff */
				else if (string_equal(buffer, "2")) /* Layer Name */
				{
					embFile_readline(file, layerName, 1000)
				} else if (string_equal(buffer, "62")) /* Color Number */
				{
					embFile_readline(file, buffer, 1000)
					/*
					TODO: finish this
					unsigned char colorNum = emb_array_to_int(buff)
					EmbColor co
					read _dxfColorTable
					co.r = embBuffer[3*colorNum+0]
					co.g = embBuffer[3*colorNum+1]
					co.b = embBuffer[3*colorNum+2]
					printf("inserting:%s,%d,%d,%d\n", layerName, co.r, co.g, co.b)
					if (embHash_insert(layer_names[i], emb_strdup(layerName), &co)) {
						 TODO: log error: failed inserting into layerColorHash
					}
					*/
					layerName = NULL
				}
			}
		} else if (string_equal(section, "ENTITIES")) {
			/* Common Group Codes for Entities */
			if (string_equal(buffer, "5")) /* Handle */
			{
				embFile_readline(file, buffer, 1000)
				continue
			} else if (string_equal(buffer, "330")) /* Soft Pointer */
			{
				embFile_readline(file, buffer, 1000)
				continue
			} else if (string_equal(buffer, "100")) /* Subclass Marker */
			{
				embFile_readline(file, buffer, 1000)
				continue
			} else if (string_equal(buffer, "8")) /* Layer Name */
			{
				embFile_readline(file, buffer, 1000)
				/* embPattern_changeColor(pattern, colorIndexMap[buff]); TODO: port to C */
				continue
			}

			if (string_equal(entityType, "LWPOLYLINE")) {
				/* The not so important group codes */
				if (string_equal(buffer, "90")) /* Vertices */
				{
					embFile_readline(file, buffer, 1000)
					continue
				} else if (string_equal(buffer, "70")) /* Polyline Flag */
				{
					embFile_readline(file, buffer, 1000)
					continue
				}
				/* TODO: Try to use the widths at some point */
				else if (string_equal(buffer, "40")) /* Starting Width */
				{
					embFile_readline(file, buffer, 1000)
					continue
				} else if (string_equal(buffer, "41")) /* Ending Width */
				{
					embFile_readline(file, buffer, 1000)
					continue
				} else if (string_equal(buffer, "43")) /* Constant Width */
				{
					embFile_readline(file, buffer, 1000)
					continue
				}
				/* The meaty stuff */
				else if (string_equal(buffer, "42")) /* Bulge */
				{
					embFile_readline(file, buffer, 1000)
					bulge = emb_array_to_float(buffer)
					bulgeFlag = 1
				} else if (string_equal(buffer, "10")) /* X */
				{
					embFile_readline(file, buffer, 1000)
					x = emb_array_to_float(buffer)
				} else if (string_equal(buffer, "20")) /* Y */
				{
					embFile_readline(file, buffer, 1000)
					y = emb_array_to_float(buffer)

					if (bulgeFlag) {
						EmbArc arc
						EmbVector arcCenter
						bulgeFlag = 0
						arc.start.x = prevX
						arc.start.y = prevY
						arc.end.x = x
						arc.end.y = y
						/* TODO: sort arcMidX etc. */
						if (!getArcDataFromBulge(bulge, &arc, &arcCenter, 0, 0, 0, 0, 0, 0, 0, 0)) {
							/*TODO: error */
							return 0
						}
						if (firstStitch) {
							/* embPattern_addStitchAbs(pattern, x, y, TRIM, 1); TODO: Add moveTo point to embPath pointList */
						}
						/* embPattern_addStitchAbs(pattern, x, y, ARC, 1); TODO: Add arcTo point to embPath pointList */
					} else {
						/*if(firstStitch) embPattern_addStitchAbs(pattern, x, y, TRIM, 1); TODO: Add moveTo point to embPath pointList */
						/*else		    embPattern_addStitchAbs(pattern, x, y, NORMAL, 1); TODO: Add lineTo point to embPath pointList */
					}
					prevX = x
					prevY = y
					if (firstStitch) {
						firstX = x
						firstY = y
						firstStitch = 0
					}
				} else if (string_equal(buffer, "0")) {
					entityType = NULL
					firstStitch = 1
					if (bulgeFlag) {
						EmbArc arc
						EmbVector arcCenter
						bulgeFlag = 0
						arc.start.x = prevX
						arc.start.y = prevY
						arc.end.x = firstX
						arc.end.y = firstY
						if (!getArcDataFromBulge(bulge, &arc, &arcCenter, 0, 0, 0, 0, 0, 0, 0, 0)) {
							/*TODO: error */
							return 0
						}
						/* embPattern_addStitchAbs(pattern, prevX, prevY, ARC, 1); TODO: Add arcTo point to embPath pointList */
					} else {
						/* embPattern_addStitchAbs(pattern, firstX, firstY, NORMAL, 1); TODO: Add lineTo point to embPath pointList */
					}
				}
			} /* end LWPOLYLINE */
		} /* end ENTITIES section */
	} /* end while loop */

	/*
	EmbColor* testColor = 0
	testColor = embHash_value(layerColorHash, "OMEGA")
	if(!testColor) printf("NULL POINTER!!!!!!!!!!!!!!\n")
	else printf("LAYERCOLOR: %d,%d,%d\n", testColor->r, testColor->g, testColor->b)
	*/

	if (!eof) {
		/* NOTE: The EOF item must be present at the end of file to be considered a valid DXF file. */
		embLog("ERROR: readDxf(), missing EOF at end of DXF file\n")
	}
	return eof
	ret


writeDxf:
	/* (EmbPattern* pattern, int file, const char* fileName) returns char */
	return 0; /*TODO: finish writeDxf */
	ret


readEdr:
	/* (EmbPattern* pattern, int file, const char* fileName) returns char */
	unsigned char b[4]

	pattern->threads->length = 0

	while (fread(b, 1, 4, file) == 4) {
		EmbThread t
		t.color = embColor_fromStr(b)
		string_copy(t.catalogNumber, "NULL")
		string_copy(t.description, "NULL")
		embPattern_addThread(pattern, t)
	}
	return 1
	ret


writeEdr:
	/* (EmbPattern* pattern, int file, const char* fileName) returns char */
	unsigned char b[4]
	int i

	b[3] = 0
	for (i = 0; i < pattern->threads->length; i++) {
		EmbThread t = pattern_thread(pattern, i)
		embColor_toStr(t.color, b)
		fwrite(b, 1, 4, file)
	}
	return 1
	ret


char emdDecode(unsigned char inputByte):
	return (inputByte >= 0x80) ? ((-~inputByte) - 1) : inputByte; /* TODO: eliminate ternary return statement */
	ret


readEmd:
	/* (EmbPattern* pattern, int file, const char* fileName) returns char */
	unsigned char b[2], jemd0[6]; /* TODO: more descriptive name */
	char dx, dy
	int flags, i
	short width, height, colors

	embPattern_loadExternalColorFile(pattern, fileName)

	binaryReadBytes(file, jemd0, 6); /* TODO: check return value */
	embFile_readInt(file, &width, 2)
	embFile_readInt(file, &height, 2)
	embFile_readInt(file, &colors, 2)

	fseek(file, 0x30, SEEK_SET)

	while (fread(b, 1, 2, file) == 2) {
		flags = NORMAL

		if (b[0] == 0x80) {
			if (b[1] == 0x2A) {
				embPattern_addStitchRel(pattern, 0, 0, STOP, 1)
				continue
			} else if (b[1] == 0x80) {
				fread(b, 1, 2, file)
				flags = TRIM
			} else if (b[1] == 0xFD) {
				break
			} else {
				continue
			}
		}
		dx = emdDecode(b[0])
		dy = emdDecode(b[1])
		embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1)
	}

	return 1
	ret


writeEmd:
	/* (EmbPattern* pattern, int file, const char* fileName) returns char */
	return 0; /*TODO: finish writeEmd */
	ret


char expDecode(unsigned char a1):
	return (a1 > 0x80) ? ((-~a1) - 1) : a1
	ret


expEncode(unsigned char* b, char dx, char dy, int flags):
	if (flags == STOP) {
		b[0] = 0x80
		b[1] = 0x01
		b[2] = dx
		b[3] = dy
	} else if (flags == JUMP) {
		b[0] = 0x80
		b[1] = 0x04
		b[2] = dx
		b[3] = dy
	} else if (flags == TRIM || flags == END) {
		b[0] = 0x80
		b[1] = 0x80
		b[2] = 0
		b[3] = 0
	} else {
		b[0] = dx
		b[1] = dy
	}
	ret


readExp:
	/* (EmbPattern* pattern, int file, const char* fileName) returns char */
	char dx = 0, dy = 0
	int flags = 0

	embPattern_loadExternalColorFile(pattern, fileName)

	while (fread(embBuffer, 1, 2, file) != 2) {
		flags = NORMAL
		if (embBuffer[0] == 0x80) {
			if (embBuffer[1] & 1) {
				if (fread(embBuffer, 1, 2, file) != 2) break
				flags = STOP
			} else if ((embBuffer[1] == 2) || (embBuffer[1] == 4) || embBuffer[1] == 6) {
				flags = TRIM
				if (embBuffer[1] == 2)
					flags = NORMAL
				if (fread(embBuffer, 1, 2, file) != 2) break
			} else if (embBuffer[1] == 0x80) {
				if (fread(embBuffer, 1, 2, file) != 2) break
				/* Seems to be b0=0x07 and b1=0x00
				 * Maybe used as extension functions */
				embBuffer[0] = 0
				embBuffer[1] = 0
				flags = TRIM
			}
		}
		dx = expDecode(embBuffer[0])
		dy = expDecode(embBuffer[1])
		embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1)
	}

	return 1
	ret


writeExp:
	/* (EmbPattern* pattern, int file, const char* fileName) returns char */
	float xx, yy
	int i

	/* write stitches */
	xx = yy = 0.0
	for (i = 0; i < pattern->stitchList->length; i++) {
		EmbStitch st
		float dx, dy
		embArray_get(pattern->stitchList, &st, i)
		dx = st.x * 10.0 - xx
		dy = st.y * 10.0 - yy
		xx = st.x * 10.0
		yy = st.y * 10.0
		expEncode(embBuffer, (char)round(dx), (char)round(dy), st.flags)
		if ((embBuffer[0] == 0x80) &&
			((embBuffer[1] == 1) || (embBuffer[1] == 2) || (embBuffer[1] == 4) || (embBuffer[1] == 0x10))) {
			fwrite(embBuffer, 1, 4, file)
		} else {
			fwrite(embBuffer, 1, 2, file)
		}
	}
	embFile_print(file, "\x1a")
	return 1
	ret


char exyDecodeFlags(unsigned char b2):
	int returnCode = 0
	if (b2 == 0xF3)
		return (END)
	if ((b2 & 0xC3) == 0xC3)
		return TRIM | STOP
	if (b2 & 0x80)
		returnCode |= TRIM
	if (b2 & 0x40)
		returnCode |= STOP
	return returnCode
	ret


readExy:
	/* (EmbPattern* pattern, int file, const char* fileName) returns char */
	unsigned char b[3]

	embPattern_loadExternalColorFile(pattern, fileName)

	fseek(file, 0x100, SEEK_SET)

	while (fread(b, 1, 3, file) == 3) {
		int flags
		int x[2]
		decode_dst_ternary(x, b)
		flags = exyDecodeFlags(b[2])
		if (flags & END) {
			break
		}
		embPattern_addStitchRel(pattern, x[0] / 10.0, x[1] / 10.0, flags, 1)
	}

	return 1
	ret


writeExy:
	/* (EmbPattern* pattern, int file, const char* fileName) returns char */
	return 0; /*TODO: finish writeExy */
	ret


readFxy:
	/* (EmbPattern* pattern, int file, const char* fileName) returns char */
	embPattern_loadExternalColorFile(pattern, fileName)
	/* TODO: review for combining code.
	 * This line appears to be the only difference from the GT format. */
	fseek(file, 0x100, SEEK_SET)

	while (1) {
		int stitchType = NORMAL
		int b1 = (int)binaryReadByte(file)
		int b2 = (int)binaryReadByte(file)
		unsigned char commandByte = binaryReadByte(file)

		if (commandByte == 0x91) {
			break
		}
		if ((commandByte & 0x01) == 0x01)
			stitchType = TRIM
		if ((commandByte & 0x02) == 0x02)
			stitchType = STOP
		if ((commandByte & 0x20) == 0x20)
			b1 = -b1
		if ((commandByte & 0x40) == 0x40)
			b2 = -b2
		embPattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1)
	}

	return 1
	ret


writeFxy:
	/* (EmbPattern* pattern, int file, const char* fileName) returns char */
	return 0; /*TODO: finish writeFxy */
	ret


readGt:
	/* (EmbPattern* pattern, int file, const char* fileName) returns char */
	embPattern_loadExternalColorFile(pattern, fileName)
	/* TODO: review for combining code.
	 * This line appears to be the only difference from the FXY format. */
	fseek(file, 0x200, SEEK_SET)

	while (1) {
		int stitchType = NORMAL
		int b1 = (int)binaryReadByte(file)
		int b2 = (int)binaryReadByte(file)
		unsigned char commandByte = binaryReadByte(file)

		if (commandByte == 0x91) {
			break
		}
		if ((commandByte & 0x01) == 0x01)
			stitchType = TRIM
		if ((commandByte & 0x02) == 0x02)
			stitchType = STOP
		if ((commandByte & 0x20) == 0x20)
			b1 = -b1
		if ((commandByte & 0x40) == 0x40)
			b2 = -b2
		embPattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1)
	}

	return 1
	ret


writeGt:
	/* (EmbPattern* pattern, int file, const char* fileName) returns char */
	return 0; /*TODO: finish writeGt */
	ret


short husDecode(unsigned char a1, unsigned char a2):
	unsigned short res = (a2 << 8) + a1
	if (res >= 0x8000) {
		return ((-~res) - 1)
	}
	return res
	ret


char husDecodeStitchType(unsigned char b):
	switch (b) {
	case 0x80:
		return NORMAL
	case 0x81:
		return JUMP
	case 0x84:
		return STOP
	case 0x90:
		return END
	default:
		return NORMAL
	}
	ret


char husDecodeByte(unsigned char b):
	return (char)b
	ret


unsigned char husEncodeByte(float f):
	return (unsigned char)(int)round(f)
	ret


unsigned char husEncodeStitchType(int st):
	switch (st) {
	case NORMAL:
		return (0x80)
	case JUMP:
	case TRIM:
		return (0x81)
	case STOP:
		return (0x84)
	case END:
		return (0x90)
	default:
		return (0x80)
	}
	ret


readHus:
	/* (EmbPattern* pattern, int file, const char* fileName) returns char */
	int fileLength, i, magicCode, numberOfStitches, nColors
	short postitiveXHoopSize, postitiveYHoopSize, negativeXHoopSize, negativeYHoopSize
	int attributeOffset, xOffset, yOffset
	int attributeData = tmpfile()
	int attributeDataDecompressed = tmpfile()
	int xData = tmpfile()
	int yDecompressed = tmpfile()
	int yData = tmpfile()
	int xDecompressed = tmpfile()

	fseek(file, 0x00, SEEK_END)
	fileLength = ftell(file)
	fseek(file, 0x00, SEEK_SET)

	embFile_readInt(file, &magicCode, 4)
	embFile_readInt(file, &numberOfStitches, 4)
	embFile_readInt(file, &nColors, 4)

	embFile_readInt(file, &postitiveXHoopSize, 2)
	embFile_readInt(file, &postitiveYHoopSize, 2)
	embFile_readInt(file, &negativeXHoopSize, 2)
	embFile_readInt(file, &negativeYHoopSize, 2)

	embFile_readInt(file, &attributeOffset, 4)
	embFile_readInt(file, &xOffset, 4)
	embFile_readInt(file, &yOffset, 4)

	binaryReadBytes(file, embBuffer, 8); /* TODO: check return value */

	fread(embBuffer, 1, 2, file)
	for (i = 0; i < nColors; i++) {
		EmbThread t
		short pos
		embFile_readInt(file, &pos, 2)
		t = load_thread(hus_thread, pos)
		embPattern_addThread(pattern, t)
	}

	embFile_copy(file, attributeOffset, attributeData, xOffset - attributeOffset); /* TODO: check return value */
	husExpand(attributeData, attributeDataDecompressed, 10)

	embFile_copy(file, xOffset, attributeData, yOffset - xOffset); /* TODO: check return value */
	husExpand(xData, xDecompressed, 10)

	embFile_copy(file, yOffset, attributeData, fileLength - attributeOffset); /* TODO: check return value */
	husExpand(yData, yDecompressed, 10)

	fclose(xData)
	fclose(yData)
	fclose(attributeData)

	fseek(xDecompressed, 0, SEEK_SET)
	fseek(yDecompressed, 0, SEEK_SET)
	fseek(attributeDataDecompressed, 0, SEEK_SET)
	for (i = 0; i < numberOfStitches; i++) {
		unsigned char c
		float x, y
		int attribute
		fread(&c, 1, 1, xDecompressed)
		x = husDecodeByte(c)
		fread(&c, 1, 1, yDecompressed)
		y = husDecodeByte(c)
		fread(&c, 1, 1, attributeDataDecompressed)
		attribute = husDecodeStitchType(c)
		embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, attribute, 1)
	}

	fclose(xDecompressed)
	fclose(yDecompressed)
	fclose(attributeDataDecompressed)

	return 1
	ret


char writeHus(EmbPattern* pattern, int file, const char* fileName):
	EmbRect boundingRect
	int stitchCount, minColors, patternColor
	int attributeSize, xCompressedSize, yCompressedSize, i
	float previousX, previousY
	int xValues
	int yValues
	int attributeValues
	int xCompressed
	int yCompressed
	int attributeCompressed
	EmbStitch st

	stitchCount = pattern->stitchList->length
	/* embPattern_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */
	patternColor = pattern->threads->length
	minColors = emb_min_int(24, patternColor)
	binaryWriteUInt(file, 0x00C8AF5B)
	binaryWriteUInt(file, stitchCount)
	binaryWriteUInt(file, minColors)

	boundingRect = embPattern_calcBoundingBox(pattern)
	binaryWriteShort(file, (short)round(boundingRect.right * 10.0))
	binaryWriteShort(file, (short)-round(boundingRect.top * 10.0 - 1.0))
	binaryWriteShort(file, (short)round(boundingRect.left * 10.0))
	binaryWriteShort(file, (short)-round(boundingRect.bottom * 10.0 - 1.0))

	binaryWriteUInt(file, 0x2A + 2 * minColors)

	previousX = 0.0
	previousY = 0.0
	for (i = 0; i < pattern->stitchList->length; i++) {
		unsigned x, y, attribute
		embArray_get(pattern->stitchList, &st, i)
		x = husEncodeByte((st.x - previousX) * 10.0)
		fwrite(&x, 1, 1, xValues)
		previousX = st.x
		y = husEncodeByte((st.y - previousY) * 10.0)
		fwrite(&y, 1, 1, yValues)
		previousY = st.y
		attribute = husEncodeStitchType(st.flags)
		fwrite(&attribute, 1, 1, attributeValues)
	}
	attributeSize = husCompress(attributeValues, attributeCompressed, 10)
	xCompressedSize = husCompress(xValues, xCompressed, 10)
	yCompressedSize = husCompress(yValues, yCompressed, 10)
	/* TODO: error if husCompressData returns zero? */

	binaryWriteUInt(file, (unsigned int)(0x2A + 2 * patternColor + attributeSize))
	binaryWriteUInt(file, (unsigned int)(0x2A + 2 * patternColor + attributeSize + xCompressedSize))
	embFile_pad(file, 0, 10)

	for (i = 0; i < patternColor; i++) {
		EmbThread t
		t = pattern_thread(pattern, i)
		short color_index = (short)embThread_findNearestColor(t.color, hus_thread)
		binaryWriteShort(file, color_index)
	}

	embFile_copy(attributeCompressed, 0, file, attributeSize)
	embFile_copy(xCompressed, 0, file, xCompressedSize)
	embFile_copy(yCompressed, 0, file, yCompressedSize)

	fclose(xValues)
	fclose(xCompressed)
	fclose(yValues)
	fclose(yCompressed)
	fclose(attributeValues)
	fclose(attributeCompressed)
	return 1
	ret


char readInb(EmbPattern* pattern, int file, const char* fileName):
	unsigned char fileDescription[8]
	unsigned char nullVal
	int stitchCount
	short width, height
	short colorCount
	short unknown3, unknown2
	short imageWidth, imageHeight
	unsigned char bytesUnknown[300]; /* TODO: determine what this represents */
	short nullbyte
	short left, right, top, bottom
	int x, y, i, fileLength

	embPattern_loadExternalColorFile(pattern, fileName)
	fseek(file, 0, SEEK_END)
	fileLength = ftell(file)
	binaryReadBytes(file, fileDescription, 8); /* TODO: check return value */
	nullVal = binaryReadByte(file)
	fread(embBuffer, 1, 2, file)
	embFile_readInt(file, &stitchCount, 4)
	embFile_readInt(file, &width, 2)
	embFile_readInt(file, &height, 2)
	embFile_readInt(file, &colorCount, 2)
	embFile_readInt(file, &unknown3, 2)
	embFile_readInt(file, &unknown2, 2)
	embFile_readInt(file, &imageWidth, 2)
	embFile_readInt(file, &imageHeight, 2)
	binaryReadBytes(file, bytesUnknown, 300); /* TODO: check return value */
	embFile_readInt(file, &nullbyte, 2)
	embFile_readInt(file, &left, 2)
	embFile_readInt(file, &right, 2)
	embFile_readInt(file, &top, 2)
	embFile_readInt(file, &bottom, 2)
	fseek(file, 0x2000, SEEK_SET)
	/* Calculate stitch count since header has been seen to be blank */
	stitchCount = (int)((fileLength - 0x2000) / 3)
	for (i = 0; i < stitchCount; i++) {
		unsigned char type
		int stitch = NORMAL
		x = binaryReadByte(file)
		y = binaryReadByte(file)
		type = binaryReadByte(file)
		if ((type & 0x40) > 0)
			x = -x
		if ((type & 0x10) > 0)
			y = -y
		if ((type & 1) > 0)
			stitch = STOP
		if ((type & 2) > 0)
			stitch = TRIM
		embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, stitch, 1)
	}

	embPattern_flipVertical(pattern)

	return 1
	ret


char writeInb(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish writeInb */
	ret


char readInf(EmbPattern* pattern, int file, const char* fileName):
	int nColors, i

	fseek(file, 12L, SEEK_SET)
	embFile_readInt_be(file, &nColors, 4)

	pattern->threads->length = 0

	for (i = 0; i < nColors; i++) {
		char colorType[50]
		char colorDescription[50]
		EmbThread t
		fread(embBuffer, 1, 4, file)
		t.color.r = binaryReadByte(file)
		t.color.g = binaryReadByte(file)
		t.color.b = binaryReadByte(file)
		string_copy(t.catalogNumber, "NULL")
		string_copy(t.description, "NULL")
		embPattern_addThread(pattern, t)
		fread(embBuffer, 1, 2, file)
		binaryReadString(file, colorType, 50)
		binaryReadString(file, colorDescription, 50)
	}
	return 1
	ret


char writeInf(EmbPattern* pattern, int file, const char* fileName):
	int i, bytesRemaining
	unsigned int uint
	char *buffer = (char*)embBuffer

	uint = 0x01
	fwriteInt_be(file, &uint, 4)
	uint = 0x08
	fwriteInt_be(file, &uint, 4)
	/* write place holder offset */
	uint = 0x00
	fwriteInt_be(file, &uint, 4)
	fwriteInt_be(file, &(pattern->threads->length), 4)

	for (i = 0; i < pattern->threads->length; i++) {
		EmbColor c
		EmbThread t
		unsigned short sh
		t = pattern_thread(pattern, i)
		c = t.color
		sh = (unsigned short)(14 + string_length(buffer))
		fwriteInt_be(file, &sh, 2); /* record length */
		sh = (unsigned short)i
		fwriteInt_be(file, &sh, 2); /* record number */
		binaryWriteByte(file, c.r)
		binaryWriteByte(file, c.g)
		binaryWriteByte(file, c.b)
		sh = (unsigned short)i
		fwriteInt_be(file, &sh, 2); /* needle number */
		binaryWriteBytes(file, "RGB\0", 4)
		/* Find an inf file format description to see
		 * why RGB appears twice in a row.
		 */
		embFile_print(file, "RGB(")
		writeInt(buffer, (int)c.r, 3)
		embFile_print(file, ",")
		writeInt(buffer, (int)c.b, 3)
		embFile_print(file, ",")
		writeInt(buffer, (int)c.g, 3)
		embFile_print(file, ")")
		binaryWriteByte(file, 0)
	}
	fseek(file, -8, SEEK_END)
	bytesRemaining = ftell(file)
	fseek(file, 8, SEEK_SET)
	fwriteInt_be(file, &bytesRemaining, 4)
	return 1
	ret


char jefGetHoopSize(int width, int height):
	if (width < 50 && height < 50) {
		return HOOP_50X50
	}
	if (width < 110 && height < 110) {
		return HOOP_110X110
	}
	if (width < 140 && height < 200) {
		return HOOP_140X200
	}
	return ((int)HOOP_110X110)
	ret

char jefDecode(unsigned char inputByte):
	if (inputByte >= 0x80)
		return (char)((-~inputByte) - 1)
	return ((char)inputByte)
	ret

jefSetHoopFromId(EmbPattern* pattern, int hoopCode):
	if (!pattern) {
		embLog("ERROR: jefSetHoopFromId(), pattern==0\n")
		return
	}

	switch (hoopCode) {
	case HOOP_126X110:
		pattern->hoop.height = 126.0
		pattern->hoop.width = 110.0
		break
	case HOOP_50X50:
		pattern->hoop.height = 50.0
		pattern->hoop.width = 50.0
		break
	case HOOP_110X110:
		pattern->hoop.height = 110.0
		pattern->hoop.width = 110.0
		break
	case HOOP_140X200:
		pattern->hoop.height = 140.0
		pattern->hoop.width = 200.0
		break
	case HOOP_230X200:
		pattern->hoop.height = 230.0
		pattern->hoop.width = 200.0
		break
	}
	ret


struct hoop_padding {
	int left
	int right
	int top
	int bottom
	ret


struct hoop_padding readRectangle(int file):
	struct hoop_padding r
	embFile_readInt(file, &(r.left), 4)
	embFile_readInt(file, &(r.top), 4)
	embFile_readInt(file, &(r.right), 4)
	embFile_readInt(file, &(r.bottom), 4)
	return r
	ret


char readJef(EmbPattern* pattern, int file, const char* fileName):
	int stitchOffset, formatFlags, nColors, numberOfStitchs
	int hoopSize, i
	struct hoop_padding bounds, rectFrom110x110, rectFrom50x50, rectFrom200x140, rect_from_custom
	int stitchCount
	char date[8], time[8]
	unsigned char b[2]
	char dx = 0, dy = 0
	int flags = 0

	embFile_readInt(file, &stitchOffset, 4)
	embFile_readInt(file, &formatFlags, 4); /* TODO: find out what this means */

	binaryReadBytes(file, (unsigned char*)date, 8); /* TODO: check return value */
	binaryReadBytes(file, (unsigned char*)time, 8); /* TODO: check return value */
	embFile_readInt(file, &nColors, 4)
	embFile_readInt(file, &numberOfStitchs, 4)
	embFile_readInt(file, &hoopSize, 4)
	jefSetHoopFromId(pattern, hoopSize)

	bounds = readRectangle(file)
	rectFrom110x110 = readRectangle(file)
	rectFrom50x50 = readRectangle(file)
	rectFrom200x140 = readRectangle(file)
	rect_from_custom = readRectangle(file)

	for (i = 0; i < nColors; i++) {
		EmbThread t
		int thread_number
		embFile_readInt(file, &thread_number, 4)
		t = load_thread(jef_thread, thread_number % 79)
		embPattern_addThread(pattern, t)
	}
	fseek(file, stitchOffset, SEEK_SET)
	stitchCount = 0
	while (stitchCount < numberOfStitchs + 100) {
		flags = NORMAL
		if (!fread(b, 1, 2, file)) {
			break
		}
		if (b[0] == 0x80) {
			if (b[1] & 1) {
				if (!fread(b, 1, 2, file)) {
					break
				}
				flags = STOP
			} else if ((b[1] == 2) || (b[1] == 4) || b[1] == 6) {
				flags = TRIM
				if (!fread(b, 1, 2, file)) {
					break
				}
			} else if (b[1] == 0x10) {
				break
			}
		}
		dx = jefDecode(b[0])
		dy = jefDecode(b[1])
		embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1)
	}
	return 1
	ret


jefEncode(unsigned char* b, char dx, char dy, int flags):
	if (flags == STOP) {
		b[0] = 0x80
		b[1] = 1
		b[2] = dx
		b[3] = dy
	} else if (flags == END) {
		b[0] = 0x80
		b[1] = 0x10
		b[2] = 0
		b[3] = 0
	} else if (flags == TRIM || flags == JUMP) {
		b[0] = 0x80
		b[1] = 2
		b[2] = dx
		b[3] = dy
	} else {
		b[0] = dx
		b[1] = dy
	}
	ret


char writeJef(EmbPattern* pattern, int file, const char* fileName):
	int colorlistSize, minColors, designWidth, designHeight, i
	EmbRect boundingRect
	EmbTime time
	EmbStitch st
	float dx = 0.0, dy = 0.0, xx = 0.0, yy = 0.0
	unsigned char b[4]

	embPattern_correctForMaxStitchLength(pattern, 12.7, 12.7)

	colorlistSize = pattern->threads->length
	minColors = emb_max_float(colorlistSize, 6)
	binaryWriteInt(file, 0x74 + (minColors * 4))
	binaryWriteInt(file, 0x0A)

	embTime_initNow(&time)

	writeInt(file, (int)(time.year + 1900), 4)
	writeInt(file, (int)(time.month + 1), 2); /* TODO: pad with zeros all date/time entries */
	writeInt(file, (int)(time.day), 2)
	writeInt(file, (int)(time.hour), 2)
	writeInt(file, (int)(time.minute), 2)
	writeInt(file, (int)(time.second), 2)
	binaryWriteByte(file, 0x00)
	binaryWriteByte(file, 0x00)
	binaryWriteInt(file, pattern->threads->length)
	binaryWriteInt(file, pattern->stitchList->length + emb_max_float(0, (6 - colorlistSize) * 2) + 1)

	boundingRect = embPattern_calcBoundingBox(pattern)

	designWidth = (int)(embRect_width(boundingRect) * 10.0)
	designHeight = (int)(embRect_width(boundingRect) * 10.0)

	binaryWriteInt(file, jefGetHoopSize(designWidth, designHeight))

	/* Distance from center of Hoop */
	binaryWriteInt(file, (int)(designWidth / 2)); /* left */
	binaryWriteInt(file, (int)(designHeight / 2)); /* top */
	binaryWriteInt(file, (int)(designWidth / 2)); /* right */
	binaryWriteInt(file, (int)(designHeight / 2)); /* bottom */

	/* Distance from default 110 x 110 Hoop */
	if (emb_min_float(550 - designWidth / 2, 550 - designHeight / 2) >= 0) {
		binaryWriteInt(file, emb_max_float(-1, 550 - designWidth / 2)); /* left */
		binaryWriteInt(file, emb_max_float(-1, 550 - designHeight / 2)); /* top */
		binaryWriteInt(file, emb_max_float(-1, 550 - designWidth / 2)); /* right */
		binaryWriteInt(file, emb_max_float(-1, 550 - designHeight / 2)); /* bottom */
	} else {
		binaryWriteInt(file, -1)
		binaryWriteInt(file, -1)
		binaryWriteInt(file, -1)
		binaryWriteInt(file, -1)
	}

	/* Distance from default 50 x 50 Hoop */
	if (emb_min_float(250 - designWidth / 2, 250 - designHeight / 2) >= 0) {
		binaryWriteInt(file, (int)emb_max_float(-1, 250 - designWidth / 2)); /* left */
		binaryWriteInt(file, (int)emb_max_float(-1, 250 - designHeight / 2)); /* top */
		binaryWriteInt(file, (int)emb_max_float(-1, 250 - designWidth / 2)); /* right */
		binaryWriteInt(file, (int)emb_max_float(-1, 250 - designHeight / 2)); /* bottom */
	} else {
		binaryWriteInt(file, -1)
		binaryWriteInt(file, -1)
		binaryWriteInt(file, -1)
		binaryWriteInt(file, -1)
	}

	/* Distance from default 140 x 200 Hoop */
	binaryWriteInt(file, (int)(700 - designWidth / 2)); /* left */
	binaryWriteInt(file, (int)(1000 - designHeight / 2)); /* top */
	binaryWriteInt(file, (int)(700 - designWidth / 2)); /* right */
	binaryWriteInt(file, (int)(1000 - designHeight / 2)); /* bottom */

	/* repeated Distance from default 140 x 200 Hoop */
	/* TODO: Actually should be distance to custom hoop */
	binaryWriteInt(file, (int)(630 - designWidth / 2)); /* left */
	binaryWriteInt(file, (int)(550 - designHeight / 2)); /* top */
	binaryWriteInt(file, (int)(630 - designWidth / 2)); /* right */
	binaryWriteInt(file, (int)(550 - designHeight / 2)); /* bottom */

	for (i = 0; i < pattern->threads->length; i++) {
		EmbThread t
		t = pattern_thread(pattern, i)
		int j = embThread_findNearestColor(t.color, jef_thread)
		binaryWriteInt(file, j)
	}

	for (i = 0; i < (minColors - colorlistSize); i++) {
		binaryWriteInt(file, 0x0D)
	}

	for (i = 0; i < pattern->stitchList->length; i++) {
		embArray_get(pattern->stitchList, &st, i)
		dx = st.x * 10.0 - xx
		dy = st.y * 10.0 - yy
		xx = st.x * 10.0
		yy = st.y * 10.0
		jefEncode(b, (char)round(dx), (char)round(dy), st.flags)
		if ((b[0] == 0x80) && ((b[1] == 1) || (b[1] == 2) || (b[1] == 4) || (b[1] == 0x10))) {
			fwrite(b, 1, 4, file)
		} else {
			fwrite(b, 1, 2, file)
		}
	}
	return 1
	ret


ksmEncode(unsigned char* b, char dx, char dy, int flags):
	/* TODO: How to encode JUMP stitches? JUMP must be handled. Also check this for the EXP format since it appears to be similar */
	if (flags == TRIM) {
		b[0] = 128
		b[1] = 2
		b[2] = dx
		b[3] = dy
	} else if (flags == STOP) {
		b[0] = 128
		b[1] = 1
		b[2] = dx
		b[3] = dy
	} else {
		b[0] = dx
		b[1] = dy
	}
	ret


char readKsm(EmbPattern* pattern, int file, const char* fileName):
	int prevStitchType = NORMAL
	char b[3]

	fseek(file, 0x200, SEEK_SET)

	while (fread(b, 1, 3, file) == 3) {
		int flags = NORMAL

		if (((prevStitchType & 0x08) == 0x08) && (b[2] & 0x08) == 0x08) {
			flags = STOP
		} else if ((b[2] & 0x1F) != 0) {
			flags = TRIM
		}
		prevStitchType = b[2]
		if (b[2] & 0x40)
			b[1] = -b[1]
		if (b[2] & 0x20)
			b[0] = -b[0]
		embPattern_addStitchRel(pattern, b[1] / 10.0, b[0] / 10.0, flags, 1)
	}
	return 1
	ret


char writeKsm(EmbPattern* pattern, int file, const char* fileName):
	EmbVector pos, diff
	int i

	embFile_pad(file, 0, 0x200)

	/* write stitches */
	pos.x = pos.y = 0
	for (i = 0; i < pattern->stitchList->length; i++) {
		EmbStitch st
		unsigned char b[4]
		embArray_get(pattern->stitchList, &st, i)
		diff.x = st.x - pos.x
		diff.y = st.y - pos.y
		pos.x = st.x
		pos.y = st.y
		ksmEncode(b, (char)(diff.x * 10.0), (char)(diff.y * 10.0), st.flags)
		fwrite(b, 1, 2, file)
	}
	embFile_print(file, "\x1a")
	return 1
	ret


/* Pfaff MAX embroidery file format */

float maxDecode(unsigned char a1, unsigned char a2, unsigned char a3):
	int res = a1 + (a2 << 8) + (a3 << 16)
	if (res > 0x7FFFFF) {
		return (-((~(res)&0x7FFFFF) - 1))
	}
	return res
	ret


maxEncode(int file, int x, int y):
	if (!file) {
		print_log_string(error_max_encode_no_file)
		return
	}

	binaryWriteByte(file, (unsigned char)0)
	binaryWriteByte(file, (unsigned char)(x & 0xFF))
	binaryWriteByte(file, (unsigned char)((x >> 8) & 0xFF))
	binaryWriteByte(file, (unsigned char)((x >> 16) & 0xFF))

	binaryWriteByte(file, (unsigned char)0)
	binaryWriteByte(file, (unsigned char)(y & 0xFF))
	binaryWriteByte(file, (unsigned char)((y >> 8) & 0xFF))
	binaryWriteByte(file, (unsigned char)((y >> 16) & 0xFF))
	ret


char readMax(EmbPattern* pattern, int file, const char* fileName):
	unsigned char b[8]
	float dx, dy
	int i, flags, stitchCount

	fseek(file, 0xD5, SEEK_SET)
	embFile_readInt(file, &stitchCount, 4)

	/* READ STITCH RECORDS */
	for (i = 0; i < stitchCount; i++) {
		flags = NORMAL
		if (fread(b, 1, 8, file) != 8)
			break

		dx = maxDecode(b[0], b[1], b[2])
		dy = maxDecode(b[4], b[5], b[6])
		embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1)
	}

	embPattern_flipVertical(pattern)

	return 1
	ret


char writeMax(EmbPattern* pattern, int file, const char* fileName):
	int i

	string_to_file(file, max_header, 0xD5)
	for (i = 0; i < pattern->stitchList->length; i++) {
		float x, y
		EmbStitch st
		embArray_get(pattern->stitchList, &st, i)
		x = round(st.x * 10.0)
		y = round(st.y * 10.0)
		maxEncode(file, x, y)
	}
	return 1
	ret


char mitDecodeStitch(unsigned char value):
	if (value & 0x80) {
		return -(value & 0x1F)
	}
	return value
	ret


char readMit(EmbPattern* pattern, int file, const char* fileName):
	unsigned char data[2]

	/* embPattern_loadExternalColorFile(pattern, fileName); TODO: review this and uncomment or remove it */

	while (binaryReadBytes(file, data, 2) == 2) {
		float x, y
		x = mitDecodeStitch(data[0]) / 10.0
		y = mitDecodeStitch(data[1]) / 10.0
		embPattern_addStitchRel(pattern, x, y, NORMAL, 1)
	}

	return 1
	ret


unsigned char mitEncodeStitch(float value):
	if (value < 0) {
		return 0x80 | (unsigned char)(-value)
	}
	return (unsigned char)value
	ret


char writeMit(EmbPattern* pattern, int file, const char* fileName):
	EmbStitch st
	EmbVector pos, diff
	int i

	embPattern_correctForMaxStitchLength(pattern, 0x1F, 0x1F)
	pos.x = pos.y = 0
	for (i = 0; i < pattern->stitchList->length; i++) {
		embArray_get(pattern->stitchList, &st, i)
		diff.x = st.x - pos.x
		diff.y = st.y - pos.y
		pos.x = st.x
		pos.y = st.y
		embBuffer[0] = mitEncodeStitch(diff.x)
		embBuffer[1] = mitEncodeStitch(diff.y)
		fwrite(embBuffer, 1, 2, file)
	}
	return 1
	ret


char decodeNewStitch(unsigned char value):
	return (int)value
	ret


char readNew(EmbPattern* pattern, int file, const char* fileName):
	unsigned int stitchCount
	unsigned char data[3]

	embPattern_loadExternalColorFile(pattern, fileName)
	embFile_readInt(file, &stitchCount, 2)
	while (binaryReadBytes(file, data, 3) == 3) {
		int x = decodeNewStitch(data[0])
		int y = decodeNewStitch(data[1])
		int flag = NORMAL
		if (data[2] & 0x40) {
			x = -x
		}
		if (data[2] & 0x20) {
			y = -y
		}
		if (data[2] & 0x10) {
			flag = TRIM
		}
		if (data[2] & 0x01) {
			flag = JUMP
		}
		if ((data[2] & 0x1E) == 0x02) {
			flag = STOP
		}
		/* Unknown values, possibly TRIM
		155 = 1001 1011 = 0x9B
		145 = 1001 0001 = 0x91
		*/
		/*char val = (data[2] & 0x1C)
		if(val != 0 && data[2] != 0x9B && data[2] != 0x91)
		{
			int z = 1
		}*/
		embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, flag, 1)
	}

	return 1
	ret


char writeNew(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish writeNew */
	ret


char* ofmReadLibrary(int file):
	int stringLength = 0
	/* FF FE FF */
	unsigned char leadIn[3]

	binaryReadBytes(file, leadIn, 3); /* TODO: check return value */
	stringLength = binaryReadByte(file)
	fread(embBuffer, 1, stringLength * 2, file); /* TODO: check return value */
	return embBuffer
	ret


int ofmReadClass(int file):
	int len
	char* s = (char*)embBuffer

	fread(embBuffer, 1, 2, file)
	embFile_readInt(file, &len, 2)

	binaryReadBytes(file, (unsigned char*)s, len); /* TODO: check return value */
	s[len] = '\0'
	if (string_equal(s, "CExpStitch"))
		return 0x809C
	if (string_equal(s, "CColorChange"))
		return 0xFFFF
	return 0
	ret


ofmReadBlockHeader(int file):
	int val[10]; /* TODO: determine what these represent */
	unsigned char len
	unsigned short short1
	/* TODO: determine what these 3 variables represent */
	short unknown1 = 0
	short unknown2 = 0
	int unknown3 = 0, i

	embFile_readInt(file, &unknown1, 2)
	embFile_readInt(file, &i, 4)
	unknown2 = (short)i
	embFile_readInt(file, &unknown3, 2)

	fread(embBuffer, 1, 3, file)
	/* int v = binaryReadBytes(3); TODO: review */
	len = binaryReadUInt8(file)
	fread(embBuffer, 1, 2*len, file)
	/* TODO: check return value here */
	fread(embBuffer, 1, 42, file)
	/* 0, 0, 0, 0, 1, 1, 1, 0, 64, 64 */
	for (i=0; i<10; i++) {
		embFile_readInt(file, val+i, 4)
	}
	embFile_readInt(file, &short1, 2); /*  0 */
	ret


ofmReadColorChange(int file, EmbPattern* pattern):
	ofmReadBlockHeader(file)
	embPattern_addStitchRel(pattern, 0.0, 0.0, STOP, 1)
	ret


ofmReadThreads(int file, EmbPattern* p):
	int i, numberOfLibraries
	char* primaryLibraryName = 0
	char* expandedString
	short nColors, stringLen

	/* Magic Code: FF FE FF 00
	 * Number of colors: 2 bytes signed short
	 */
	fread(embBuffer, 1, 4, file)

	embFile_readInt(file, &nColors, 2)
	fread(embBuffer, 1, 2, file)
	embFile_readInt(file, &stringLen, 2)
	expandedString = (char*)embBuffer
	binaryReadBytes(file, (unsigned char*)expandedString, stringLen); /* TODO: check return value */
	for (i = 0; i < nColors; i++) {
		EmbThread thread
		char colorNumberText[10]
		short threadLibrary = 0
		unsigned char colorNameLength
		int colorNumber
		char* colorName = 0
		unsigned char color[3]
		fread(color, 1, 3, file)
		fread(embBuffer, 1, 1, file)
		embFile_readInt(file, &threadLibrary, 2)
		fread(embBuffer, 1, 2, file)
		embFile_readInt(file, &colorNumber, 4)
		fread(embBuffer, 1, 3, file)
		colorNameLength = binaryReadByte(file)
		colorName = (char*)embBuffer
		if (colorNameLength > 1023/2) {
			print_log_string(error_ofm_threads_color_name)
			return
		}
		binaryReadBytes(file, (unsigned char*)colorName, colorNameLength * 2); /* TODO: check return value */
		fread(embBuffer, 1, 2, file)
		emb_int_to_array(colorNumberText, colorNumber, 10)
		thread.color = embColor_fromStr(color)
		string_copy(thread.catalogNumber, colorNumberText)
		string_copy(thread.description, colorName)
		embPattern_addThread(p, thread)
	}
	fread(embBuffer, 1, 2, file)
	primaryLibraryName = ofmReadLibrary(file)
	embFile_readInt(file, &numberOfLibraries, 2)
	for (i = 0; i < numberOfLibraries; i++) {
		/*libraries.Add( TODO: review */
		char* libName = ofmReadLibrary(file)
	}
	ret


float ofmDecode(unsigned char b1, unsigned char b2):
	float val = (float)(short)(b1 << 8 | b2)
	return val
	ret


ofmReadExpanded(int file, EmbPattern* p):
	int i, numberOfStitches = 0

	ofmReadBlockHeader(file)
	embFile_readInt(file, &numberOfStitches, 4)

	for (i = 0; i < numberOfStitches; i++) {
		unsigned char stitch[5]
		binaryReadBytes(file, stitch, 5); /* TODO: check return value */
		if (stitch[0] == 0) {
			embPattern_addStitchAbs(p, ofmDecode(stitch[1], stitch[2]) / 10.0, ofmDecode(stitch[3], stitch[4]) / 10.0, i == 0 ? JUMP : NORMAL, 1)
		} else if (stitch[0] == 32) {
			embPattern_addStitchAbs(p, ofmDecode(stitch[1], stitch[2]) / 10.0, ofmDecode(stitch[3], stitch[4]) / 10.0, i == 0 ? TRIM : NORMAL, 1)
		}
	}
	ret


char readOfm(EmbPattern* pattern, int file, const char* fileName):
	int unknownCount = 0
	short key = 0
	short classNameLength
	char* s = 0
	int fileCompound = 0

	fileCompound = embFile_open(fileName, "rb", 0)
	if (!fileCompound)
		return 0

	bcfFile_read(fileCompound)
	file = GetFile(&BcfFile, fileCompound, "EdsIV Object")
	/* BcfFile.directory.maxEntries = 0; */

	fseek(file, 0x1C6, SEEK_SET)
	ofmReadThreads(file, pattern)
	fseek(file, 0x110, SEEK_CUR)
	fread(embBuffer, 1, 4, file)
	embFile_readInt(file, &classNameLength, 2)
	s = (char*)embBuffer
	binaryReadBytes(file, (unsigned char*)embBuffer, classNameLength); /* TODO: check return value */
	embFile_readInt(file, &unknownCount, 2); /* TODO: determine what unknown count represents */

	fread(embBuffer, 1, 2, file)
	key = ofmReadClass(file)
	while (1) {
		if (key == 0xFEFF) {
			break
		}
		if (key == 0x809C) {
			ofmReadExpanded(file, pattern)
		} else {
			ofmReadColorChange(file, pattern)
		}
		embFile_readInt(file, &key, 2)
		if (key == 0xFFFF) {
			ofmReadClass(file)
		}
	}

	fclose(fileCompound)

	embPattern_flip(pattern, 1, 1)

	return 1
	ret


char writeOfm(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish writeOfm */
	ret


float pcdDecode(unsigned char a1, unsigned char a2, unsigned char a3):
	int res = a1 + (a2 << 8) + (a3 << 16)
	if (res > 0x7FFFFF) {
		return (-((~(res)&0x7FFFFF) - 1))
	}
	return res
	ret


char readPcd(EmbPattern* pattern, int file, const char* fileName):
	char allZeroColor = 1
	int i
	unsigned char b[9]
	float dx = 0, dy = 0
	int flags = 0
	unsigned char version, hoopSize
	unsigned short colorCount = 0, st = 0

	fread(embBuffer, 1, 2, file)
	version = embBuffer[0]
	/* 0 for PCD
	 * 1 for PCQ (MAXI)
	 * 2 for PCS with small hoop(80x80)
	 * and 3 for PCS with large hoop (115x120) */
	hoopSize = embBuffer[1]
	embFile_readInt(file, &colorCount, 2)

	for (i = 0; i < colorCount; i++) {
		EmbThread t
		fread(embBuffer, 1, 4, file)
		t.color = embColor_fromStr(embBuffer)
		string_copy(t.catalogNumber, "NULL")
		string_copy(t.description, "NULL")
		if (t.color.r || t.color.g || t.color.b) {
			allZeroColor = 0
		}
		embPattern_addThread(pattern, t)
	}
	if (allZeroColor)
		embPattern_loadExternalColorFile(pattern, fileName)
	embFile_readInt(file, &st, 2)
	/* READ STITCH RECORDS */
	for (i = 0; i < st; i++) {
		flags = NORMAL
		if (fread(b, 1, 9, file) != 9)
			break

		if (b[8] & 0x01) {
			flags = STOP
		} else if (b[8] & 0x04) {
			flags = TRIM
		} else if (b[8] != 0) {
			/* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
		}
		dx = pcdDecode(b[1], b[2], b[3])
		dy = pcdDecode(b[5], b[6], b[7])
		embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1)
	}

	return 1
	ret


pcEncode(int file, int dx, int dy, int flags)

char writePcd(EmbPattern* pattern, int file, const char* fileName):
	int i
	unsigned short sh

	binaryWriteByte(file, (unsigned char)'2')
	binaryWriteByte(file, 3); /* TODO: select hoop size defaulting to Large PCS hoop */
	sh = (unsigned short)pattern->threads->length
	fwriteInt(file, &sh, 2)

	embPattern_colorBlock16(pattern, file)

	sh = (unsigned short)pattern->stitchList->length
	fwriteInt(file, &sh, 2)
	/* write stitches */
	for (i = 0; i < pattern->stitchList->length; i++) {
		EmbStitch st
		embArray_get(pattern->stitchList, &st, i)
		pcEncode(file, round(st.x * 10.0), round(st.y * 10.0), st.flags)
	}
	return 1
	ret


float pcmDecode(unsigned char a1, unsigned char a2, unsigned char a3):
	int res = a1 + (a2 << 8) + (a3 << 16)
	if (res > 0x7FFFFF) {
		return (-((~(res)&0x7FFFFF) - 1))
	}
	return res
	ret


char readPcm(EmbPattern* pattern, int file, const char* fileName):
	int i = 0
	unsigned char b[9]
	float dx = 0, dy = 0
	int flags = 0, st = 0

	fseek(file, 4, SEEK_SET)

	for (i = 0; i < 16; i++) {
		EmbThread t
		int colorNumber
		fread(embBuffer, 1, 2, file)
		/* zero followed by colorNumber */
		colorNumber = embBuffer[1]
		t = load_thread(pcm_thread, colorNumber)
		embPattern_addThread(pattern, t)
	}
	embFile_readInt_be(file, &st, 2)
	/* READ STITCH RECORDS */
	for (i = 0; i < st; i++) {
		flags = NORMAL
		if (fread(b, 1, 9, file) != 9)
			break

		if (b[8] & 0x01) {
			flags = STOP
		} else if (b[8] & 0x04) {
			flags = TRIM
		} else if (b[8] != 0) {
			/* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
		}
		dx = pcmDecode(b[2], b[1], b[0])
		dy = pcmDecode(b[6], b[5], b[4])
		embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1)
	}

	return 1
	ret


char writePcm(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish writePcm */
	ret


float pcqDecode(unsigned char a1, unsigned char a2, unsigned char a3):
	int res = a1 + (a2 << 8) + (a3 << 16)
	if (res > 0x7FFFFF) {
		return (-((~(res)&0x7FFFFF) - 1))
	}
	return res
	ret


char readPcq(EmbPattern* pattern, int file, const char* fileName):
	char allZeroColor = 1
	unsigned char b[9]
	float dx = 0, dy = 0
	int i, flags = 0
	unsigned char version, hoopSize
	unsigned short colorCount, st
	EmbThread t

	version = binaryReadByte(file)
	hoopSize = binaryReadByte(file)
	/* 0 for PCD, 1 for PCQ (MAXI), 2 for PCS with small hoop(80x80), */
	/* and 3 for PCS with large hoop (115x120) */
	embFile_readInt(file, &colorCount, 2)

	for (i = 0; i < colorCount; i++) {
		fread(b, 1, 4, file)
		t.color = embColor_fromStr(b)
		string_copy(t.catalogNumber, "NULL")
		string_copy(t.description, "NULL")
		if (t.color.r || t.color.g || t.color.b) {
			allZeroColor = 0
		}
		embPattern_addThread(pattern, t)
	}
	if (allZeroColor)
		embPattern_loadExternalColorFile(pattern, fileName)
	embFile_readInt(file, &st, 2)
	/* READ STITCH RECORDS */
	for (i = 0; i < st; i++) {
		flags = NORMAL
		if (fread(b, 1, 9, file) != 9)
			break

		if (b[8] & 0x01) {
			flags = STOP
		} else if (b[8] & 0x04) {
			flags = TRIM
		} else if (b[8] != 0) {
			/* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
		}
		dx = pcqDecode(b[1], b[2], b[3])
		dy = pcqDecode(b[5], b[6], b[7])
		embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1)
	}

	return 1
	ret


char writePcq(EmbPattern* pattern, int file, const char* fileName):
	int i
	unsigned short sh

	fwrite("2\x03", 1, 2, file)
	/* TODO: select hoop size defaulting to Large PCS hoop */
	sh = (unsigned short)pattern->threads->length
	fwriteInt(file, &sh, 2)

	embPattern_colorBlock16(pattern, file)

	sh = (unsigned short)pattern->stitchList->length
	fwriteInt(file, &sh, 2)
	/* write stitches */
	for (i = 0; i < pattern->stitchList->length; i++) {
		EmbStitch st
		embArray_get(pattern->stitchList, &st, i)
		pcEncode(file, round(st.x * 10.0), round(st.y * 10.0), st.flags)
	}
	return 1
	ret


float pcsDecode(unsigned char a1, unsigned char a2, unsigned char a3):
	int res = a1 + (a2 << 8) + (a3 << 16)
	if (res > 0x7FFFFF) {
		return (-((~(res)&0x7FFFFF) - 1))
	}
	return res
	ret


pcEncode(int file, int dx, int dy, int flags):
	unsigned char toWrite[9]

	toWrite[0] = 0
	toWrite[1] = dx & 0xFF
	toWrite[2] = (dx >> 8) & 0xFF
	toWrite[3] = (dx >> 16) & 0xFF

	toWrite[4] = 0
	toWrite[5] = dy & 0xFF
	toWrite[6] = (dy >> 8) & 0xFF
	toWrite[7] = (dy >> 16) & 0xFF
	
	toWrite[8] = 0
	if (flags & STOP) {
		toWrite[8] |= 0x01
	}
	if (flags & TRIM) {
		toWrite[8] |= 0x04
	}
	binaryWriteBytes(file, toWrite, 9)
	ret


char readPcs(EmbPattern* pattern, int file, const char* fileName):
	int i
	unsigned char allZeroColor, version, hoopSize
	unsigned short colorCount, st

	version = binaryReadByte(file)
	hoopSize = binaryReadByte(file); /* 0 for PCD, 1 for PCQ (MAXI), 2 for PCS with small hoop(80x80), */
	/* and 3 for PCS with large hoop (115x120) */

	switch (hoopSize) {
	case 2:
		pattern->hoop.width = 80.0
		pattern->hoop.height = 80.0
		break
	case 3:
		pattern->hoop.width = 115
		pattern->hoop.height = 120.0
		break
	}

	embFile_readInt(file, &colorCount, 2)

	allZeroColor = 1
	for (i = 0; i < colorCount; i++) {
		EmbThread t
		t.color.r = binaryReadByte(file)
		t.color.g = binaryReadByte(file)
		t.color.b = binaryReadByte(file)
		string_copy(t.catalogNumber, "NULL")
		string_copy(t.description, "NULL")
		if (t.color.r || t.color.g || t.color.b) {
			allZeroColor = 0
		}
		embPattern_addThread(pattern, t)
		binaryReadByte(file)
	}

	if (allZeroColor) {
		embPattern_loadExternalColorFile(pattern, fileName)
	}

	embFile_readInt(file, &st, 2)

	/* READ STITCH RECORDS */
	for (i = 0; i < st; i++) {
		int flags
		float dx, dy
		unsigned char b[9]
		flags = NORMAL
		if (fread(b, 1, 9, file) != 9)
			break

		if (b[8] & 0x01) {
			flags = STOP
		} else if (b[8] & 0x04) {
			flags = TRIM
		} else if (b[8] != 0) {
			/* TODO: ONLY INTERESTED IN THIS CASE TO LEARN MORE ABOUT THE FORMAT */
		}
		dx = pcsDecode(b[1], b[2], b[3])
		dy = pcsDecode(b[5], b[6], b[7])
		embPattern_addStitchAbs(pattern, dx / 10.0, dy / 10.0, flags, 1)
	}

	return 1
	ret


EmbArc pattern_arc(EmbPattern *p, int index):
	EmbArc a
	fseek(memory[p->arcs->file_id], sizeof(EmbArc)*index, SEEK_SET)
	fread(&a, sizeof(EmbArc), 1, memory[p->arcs->file_id])
	return a
	ret


EmbThread pattern_thread(EmbPattern *p, int index):
	EmbThread t
	fseek(memory[p->threads->file_id], sizeof(EmbThread)*index, SEEK_SET)
	fread(&t, sizeof(EmbThread), 1, memory[p->threads->file_id])
	return t
	ret


EmbStitch pattern_stitch(EmbPattern *p, int index):
	EmbStitch st
	fseek(memory[p->stitchList->file_id], sizeof(EmbStitch)*index, SEEK_SET)
	fread(&st, sizeof(EmbStitch), 1, memory[p->stitchList->file_id])
	return st
	ret


EmbThread load_thread(int thread_table, int index):
	EmbThread t
	int out
	out = double_dereference_int(brand_codes, thread_table)
	fseek(datafile, out+35*index, SEEK_SET)
	fread(embBuffer, 1, 35, datafile)
	t.color.r = embBuffer[30]
	t.color.g = embBuffer[31]
	t.color.b = embBuffer[32]
	string_copy(t.catalogNumber, "TODO:HUS_CODE")
	string_copy(t.description, (char *)embBuffer)
	return t;    
	ret


char writePcs(EmbPattern* pattern, int file, const char* fileName):
	int i
	unsigned short sh

	/* TODO: select hoop size defaulting to Large PCS hoop */
	fwrite("2\x03", 1, 2, file)
	sh = (unsigned short)pattern->threads->length
	fwriteInt(file, &sh, 2)

	embPattern_colorBlock16(pattern, file)

	sh = (unsigned short)pattern->stitchList->length
	fwriteInt(file, &sh, 2)
	/* write stitches */
	for (i = 0; i < sh; i++) {
		EmbStitch st
		embArray_get(pattern->stitchList, &st, i)
		pcEncode(file, round(st.x * 10.0), round(st.y * 10.0), st.flags)
	}
	return 1
	ret


readPecStitches(EmbPattern* pattern, int file, const char* fileName):
	int stitchNumber = 0

	while (fread(embBuffer, 1, 2, file) == 2) {
		int val1 = (int)embBuffer[0]
		int val2 = (int)embBuffer[1]

		int stitchType = NORMAL
		if (val1 == 0xFF && val2 == 0x00) {
			break
		}
		if (val1 == 0xFE && val2 == 0xB0) {
			(void)binaryReadByte(file)
			embPattern_addStitchRel(pattern, 0.0, 0.0, STOP, 1)
			stitchNumber++
			continue
		}
		/* High bit set means 12-bit offset, otherwise 7-bit signed delta */
		if (val1 & 0x80) {
			if (val1 & 0x20)
				stitchType = TRIM
			if (val1 & 0x10)
				stitchType = JUMP
			val1 = ((val1 & 0x0F) << 8) + val2

			/* Signed 12-bit arithmetic */
			if (val1 & 0x800) {
				val1 -= 0x1000
			}

			val2 = binaryReadUInt8(file)
		} else if (val1 >= 0x40) {
			val1 -= 0x80
		}
		if (val2 & 0x80) {
			if (val2 & 0x20)
				stitchType = TRIM
			if (val2 & 0x10)
				stitchType = JUMP
			val2 = ((val2 & 0x0F) << 8) + binaryReadUInt8(file)

			/* Signed 12-bit arithmetic */
			if (val2 & 0x800) {
				val2 -= 0x1000
			}
		} else if (val2 >= 0x40) {
			val2 -= 0x80
		}
		embPattern_addStitchRel(pattern, val1 / 10.0, val2 / 10.0, stitchType, 1)
		stitchNumber++
	}
	ret


pecEncodeJump(int file, int x, int types):
	int outputVal = emb_abs(x) & 0x7FF
	unsigned int orPart = 0x80

	if (types & TRIM) {
		orPart |= 0x20
	}
	if (types & JUMP) {
		orPart |= 0x10
	}

	if (x < 0) {
		outputVal = x + 0x1000 & 0x7FF
		outputVal |= 0x800
	}
	binaryWriteByte(file, (unsigned char)(((outputVal >> 8) & 0x0F) | orPart))
	binaryWriteByte(file, (unsigned char)(outputVal & 0xFF))
	ret


pecEncodeStop(int file, unsigned char val):
	fwrite("\xFE\xB0", 1, 2, file)
	fwrite(&val, 1, 1, file)
	ret


char readPec(EmbPattern* pattern, int file, const char* fileName):
	unsigned int graphicsOffset
	unsigned char colorChanges
	int i

	fseek(file, 0x38, SEEK_SET)
	colorChanges = (unsigned char)binaryReadByte(file)
	for (i = 0; i <= colorChanges; i++) {
		embPattern_addThread(pattern, load_thread(pec_thread, binaryReadByte(file) % 65))
	}

	/* Get Graphics offset */
	fseek(file, 0x20A, SEEK_SET)

	graphicsOffset = (unsigned int)(binaryReadUInt8(file))
	graphicsOffset |= (binaryReadUInt8(file) << 8)
	graphicsOffset |= (binaryReadUInt8(file) << 16)

	/* \x31\xFF\xF0 */
	fread(embBuffer, 1, 3, file)
	/* Get X and Y size in .1 mm
	 * 0x210 <- what is this?
	 * x size signed short
	 * y size signed short */
	fread(embBuffer, 1, 4, file)
 
	fread(embBuffer, 1, 2, file); /* 0x01E0 */
	fread(embBuffer, 1, 2, file); /* 0x01B0 */
	fread(embBuffer, 1, 2, file); /* distance left from start */
	fread(embBuffer, 1, 2, file); /* distance up from start */

	/* Begin Stitch Data */
	/* 0x21C */
	/*unsigned int end = graphicsOffset + 0x208; */
	readPecStitches(pattern, file, fileName)

	embPattern_flipVertical(pattern)

	return 1
	ret


pecEncode(int file, EmbPattern* p):
	float thisX = 0.0
	float thisY = 0.0
	unsigned char stopCode = 2
	EmbStitch s
	int deltaX, deltaY, i

	for (i = 0; i < p->stitchList->length; i++) {
		embArray_get(p->stitchList, &s, i)

		deltaX = round(s.x - thisX)
		deltaY = round(s.y - thisY)
		thisX += (float)deltaX
		thisY += (float)deltaY

		if (s.flags & STOP) {
			pecEncodeStop(file, stopCode)
			if (stopCode == (unsigned char)2) {
				stopCode = (unsigned char)1
			} else {
				stopCode = (unsigned char)2
			}
		} else if (s.flags & END) {
			binaryWriteByte(file, 0xFF)
			break
		} else if (deltaX < 63 && deltaX > -64 && deltaY < 63 && deltaY > -64 && (!(s.flags & (JUMP | TRIM)))) {
			binaryWriteByte(file, (deltaX < 0) ? (unsigned char)(deltaX + 0x80) : (unsigned char)deltaX)
			binaryWriteByte(file, (deltaY < 0) ? (unsigned char)(deltaY + 0x80) : (unsigned char)deltaY)
		} else {
			pecEncodeJump(file, deltaX, s.flags)
			pecEncodeJump(file, deltaY, s.flags)
		}
	}
	ret


clearImage(unsigned char image[][48]):
	int out
	out = dereference_int(image_frame)
	fseek(datafile, out, SEEK_SET)
	fread(image, 1, 48*38, datafile)
	ret


writeImage(int file, unsigned char image[][48]):
	int i, j

	for (i = 0; i < 38; i++) {
		for (j = 0; j < 6; j++) {
			int offset = j * 8
			unsigned char output = 0
			output |= 0x01 * (image[i][offset] != 0)
			output |= 0x02 * (image[i][offset + 1] != 0)
			output |= 0x04 * (image[i][offset + 2] != 0)
			output |= 0x08 * (image[i][offset + 3] != 0)
			output |= 0x10 * (image[i][offset + 4] != 0)
			output |= 0x20 * (image[i][offset + 5] != 0)
			output |= 0x40 * (image[i][offset + 6] != 0)
			output |= 0x40 * (image[i][offset + 7] != 0)
			binaryWriteByte(file, output)
		}
	}
	ret


writePecStitches(EmbPattern* pattern, int file, const char* fileName):
	EmbStitch st
	EmbRect bounds
	unsigned char image[38][48]
	int i, currentThreadCount, graphicsOffsetLocation, graphicsOffsetValue, height, width, x, y
	float xFactor, yFactor
	char* slashPos, *backslashPos, *dotPos, *start
	slashPos = (char*)fileName+string_length(fileName)
	while (slashPos > fileName && *slashPos != '/') {
		slashPos--
	}
	backslashPos = (char*)fileName+string_length(fileName)
	while (backslashPos > fileName && *backslashPos != '\\') {
		backslashPos--
	}
	dotPos = (char*)fileName+string_length(fileName)
	while (dotPos > fileName && *dotPos != '.') {
		dotPos--
	}

	start = (char*)fileName
	if (slashPos > fileName) {
		start = slashPos + 1
	}
	if (backslashPos > fileName) {
		start = backslashPos + 1
	}

	fwrite("LA:", 1, 3, file)

	while (start < dotPos) {
		binaryWriteByte(file, (unsigned char)*start)
		start++
	}
	embFile_pad(file, 0x20, 16-(int)(dotPos - start))
	binaryWriteByte(file, 0x0D)
	embFile_pad(file, 0x20, 12)
	fwrite("\xFF\x00\x06\x26", 1, 4, file)

	embFile_pad(file, 0x20, 12)
	currentThreadCount = pattern->threads->length
	binaryWriteByte(file, (unsigned char)(currentThreadCount - 1))

	for (i = 0; i < currentThreadCount; i++) {
		EmbThread t = pattern_thread(pattern, i)
		binaryWriteByte(file, (unsigned char)embThread_findNearestColor(t.color, pec_thread))
	}
	embFile_pad(file, 0x20, (int)(0x1CF - currentThreadCount))
	embFile_pad(file, 0, 2)

	graphicsOffsetLocation = ftell(file)
	/* placeholder bytes to be overwritten */
	embFile_pad(file, 0, 3)

	fwrite("\x31\xFF\xF0", 1, 3, file)

	bounds = embPattern_calcBoundingBox(pattern)

	height = round(embRect_height(bounds))
	width = round(embRect_width(bounds))
	/* write 2 byte x size */
	binaryWriteShort(file, (short)width)
	/* write 2 byte y size */
	binaryWriteShort(file, (short)height)

	/* Write 4 miscellaneous int16's */
	binaryWriteShort(file, (short)0x1E0)
	binaryWriteShort(file, (short)0x1B0)

	short sh = (unsigned short)(0x9000 | -round(bounds.left))
	fwriteInt_be(file, &sh, 2)
	sh = (unsigned short)(0x9000 | -round(bounds.top))
	fwriteInt_be(file, &sh, 2)

	pecEncode(file, pattern)
	graphicsOffsetValue = ftell(file) - graphicsOffsetLocation + 2
	fseek(file, graphicsOffsetLocation, SEEK_SET)

	binaryWriteByte(file, (unsigned char)(graphicsOffsetValue & 0xFF))
	binaryWriteByte(file, (unsigned char)((graphicsOffsetValue >> 8) & 0xFF))
	binaryWriteByte(file, (unsigned char)((graphicsOffsetValue >> 16) & 0xFF))

	fseek(file, 0x00, SEEK_END)

	/* Writing all colors */
	clearImage(image)

	yFactor = 32.0 / height
	xFactor = 42.0 / width
	for (i = 0; i < pattern->stitchList->length; i++) {
		int x, y
		embArray_get(pattern->stitchList, &st, i)
		x = round((st.x - bounds.left) * xFactor) + 3
		y = round((st.y - bounds.top) * yFactor) + 3
		image[y][x] = 1
	}
	writeImage(file, image)

	/* Writing each individual color */
	for (i = 0; i < currentThreadCount; i++) {
		clearImage(image)
		for (i = 0; i < pattern->stitchList->length; i++) {
			embArray_get(pattern->stitchList, &st, i)
			x = round((st.x - bounds.left) * xFactor) + 3
			y = round((st.y - bounds.top) * yFactor) + 3
			if (st.flags & STOP) {
				break
			}
			image[y][x] = 1
		}
		writeImage(file, image)
	}
	ret


char writePec(EmbPattern* pattern, int file, const char* fileName):
	/* TODO: There needs to be a matching flipVertical() call after the write
	 * to ensure multiple writes from the same pattern work properly */
	embPattern_flipVertical(pattern)
	embPattern_fixColorCount(pattern)
	embPattern_correctForMaxStitchLength(pattern, 12.7, 204.7)
	embPattern_scale(pattern, 10.0)

	binaryWriteBytes(file, "#PEC0001", 8)

	writePecStitches(pattern, file, fileName)

	return 1
	ret


char readPes(EmbPattern* pattern, int file, const char* fileName):
	int numColors, x
	short pecstart

	fseek(file, 8, SEEK_SET)
	embFile_readInt(file, &pecstart, 4)

	fseek(file, pecstart + 48, SEEK_SET)
	fread(embBuffer, 1, 1, file)
	numColors = embBuffer[0] + 1
	fread(embBuffer, 1, numColors, file)
	for (x = 0; x < numColors; x++) {
		embPattern_addThread(pattern, load_thread(pec_thread, embBuffer[x]))
	}

	fseek(file, pecstart + 532, SEEK_SET)
	readPecStitches(pattern, file, fileName)

	embPattern_flipVertical(pattern)

	return 1
	ret


const char *pesVersionTable[] = {
	"#PES0100",
	"#PES0090",
	"#PES0080",
	"#PES0070",
	"#PES0060",
	"#PES0056",
	"#PES0055",
	"#PES0050",
	"#PES0040",
	"#PES0030",
	"#PES0022",
	"#PES0020",
	"#PES0001",
	"#PEC0001",
	0
	ret


/*
readPESHeader(int file, EmbPattern* pattern):
	char* signature = readString(8)
	if (strcmp(signature, "#PES0100") {
		readPESHeaderV10()
	} else if(strcmp(signature, "#PES0090") {
		readPESHeaderV9()
	} else if(strcmp(signature, "#PES0080") {
		readPESHeaderV8()
	} else if(strcmp(signature, "#PES0070") {
		readPESHeaderV7()
	} else if(strcmp(signature, "#PES0060") {
				readPESHeaderV6()
			} else if(strcmp(signature, "#PES0056"){
				readPESHeaderV5()
			} else if(strcmp(signature, "#PES0055") {
			   readPESHeaderV5()
				 } else if(strcmp(signature, "#PES0050") {
				readPESHeaderV5()
				 } else if(strcmp(signature, "#PES0040") {
				readPESHeaderV4()
				 } else if(strcmp(signature, "#PES0030") {
				readPESHeaderDefault()
				 } else if(strcmp(signature, "#PES0022") {
				readPESHeaderDefault()
				 } else if(strcmp(signature, "#PES0020") {
				readPESHeaderDefault()
				 } else if(strcmp(signature, "#PES0001") {
				readPESHeaderDefault()
				 } else
			if(strcmp(signature, "#PEC0001") {
				//PEC needs to go straight to reading, no default.
			} else {
				readPESHeaderDefault()
			}
		}
	}

readPESHeaderDefault():
	int pecStart = binaryReadInt32()
	skip(pecStart - readPosition)
	ret


readDescriptions():
	int DesignStringLength = binaryReadByte()
	String DesignName = readString(DesignStringLength)
	pattern.setName(DesignName)
	int categoryStringLength = binaryReadByte()
	String Category = readString(categoryStringLength)
	pattern.setCategory(Category)
	int authorStringLength = binaryReadByte()
	String Author = readString(authorStringLength)
	pattern.setAuthor(Author)
	int keywordsStringLength = binaryReadByte()
	String keywords = readString(keywordsStringLength)
	pattern.setKeywords(keywords)
	int commentsStringLength = binaryReadByte()
	String Comments = readString(commentsStringLength)
	pattern.setComments(Comments)
	ret


readPESHeaderV4():
	int pecStart = binaryReadInt32()
	fseek(file, 4, SEEK_CUR)
	readDescriptions()
	skip(pecStart - readPosition)
	ret


	void readPESHeaderV5()  {
		int pecStart = binaryReadInt32()
		fseek(file, 4, SEEK_CUR)
		readDescriptions()
		fseek(file, 24, SEEK_CUR);//36 v6
		int fromImageStringLength = binaryReadByte()
		skip(fromImageStringLength)
		fseek(file, 24, SEEK_CUR)
		int nProgrammableFills = binaryReadInt16()
		if (nProgrammableFills != 0) {
			fseek(file, pecStart, SEEK_SET)
			return
		}
		int nMotifs = binaryReadInt16()
		if (nMotifs != 0) {
			fseek(file, pecStart, SEEK_SET)
			return
		}
		int featherPatternCount = binaryReadInt16()
		if (featherPatternCount != 0) {
			fseek(file, pecStart, SEEK_SET)
			return
		}
		int nColors = binaryReadInt16()
		for (int i = 0; i < nColors; i++) {
			readThread()
		}
		fseek(file, pecStart, SEEK_SET)
	}

	void readPESHeaderV6()  {
		int pecStart = binaryReadInt32()
		fseek(file, 4, SEEK_CUR)
		readDescriptions()
		fseek(file, 36, SEEK_CUR)
		int fromImageStringLength = binaryReadByte()
		String fromImageString = readString(fromImageStringLength)
		if (fromImageString.length() != 0) {
			pattern.setMetadata("image_file", fromImageString)
		}
		fseek(file, 24, SEEK_CUR)
		int nProgrammableFills = binaryReadInt16()
		if (nProgrammableFills != 0) {
			fseek(file, pecStart, SEEK_SET)
			return
		}
		int nMotifs = binaryReadInt16()
		if (nMotifs != 0) {
			fseek(file, pecStart, SEEK_SET)
			return
		}
		int featherPatternCount = binaryReadInt16()
		if (featherPatternCount != 0) {
			fseek(file, pecStart, SEEK_SET)
			return
		}
		int nColors = binaryReadInt16()
		for (int i = 0; i < nColors; i++) {
			readThread()
		}
		fseek(file, pecStart, SEEK_SET)
	}
	
	void readPESHeaderV7()  {
		int pecStart = binaryReadInt32()
		fseek(file, 4, SEEK_CUR)
		readDescriptions()
		fseek(file, 36, SEEK_CUR)
		int fromImageStringLength = binaryReadByte()
		String fromImageString = readString(fromImageStringLength)
		if (fromImageString.length() != 0) {
			pattern.setMetadata("image_file", fromImageString)
		}
		fseek(file, 24, SEEK_CUR)
		int nProgrammableFills = binaryReadInt16()
		if (nProgrammableFills != 0) {
			fseek(file, pecStart, SEEK_SET)
			return
		}
		int nMotifs = binaryReadInt16()
		if (nMotifs != 0) {
			fseek(file, pecStart, SEEK_SET)
			return
		}
		int featherPatternCount = binaryReadInt16()
		if (featherPatternCount != 0) {
			fseek(file, pecStart, SEEK_SET)
			return
		}
		int nColors = binaryReadInt16()
		for (int i = 0; i < nColors; i++) {
			readThread()
		}
		fseek(file, pecStart, SEEK_SET)
	}
	
	void readPESHeaderV8()  {
		int pecStart = binaryReadInt32()
		fseek(file, 4, SEEK_CUR)
		readDescriptions()
		fseek(file, 38, SEEK_CUR)
		int fromImageStringLength = binaryReadByte()
		String fromImageString = readString(fromImageStringLength)
		if (fromImageString.length() != 0) {
			pattern.setMetadata("image_file", fromImageString)
		}
		skip(26)
		int nProgrammableFills = binaryReadInt16()
		if (nProgrammableFills != 0) {
			fseek(file, pecStart, SEEK_SET)
			return
		}
		int nMotifs = binaryReadInt16()
		if (nMotifs != 0) {
			fseek(file, pecStart, SEEK_SET)
			return
		}
		int featherPatternCount = binaryReadInt16()
		if (featherPatternCount != 0) {
			fseek(file, pecStart, SEEK_SET)
			return
		}
		int nColors = binaryReadInt16()
		for (int i = 0; i < nColors; i++) {
			readThread()
		}
		fseek(file, pecStart, SEEK_SET)
	}

	void readPESHeaderV9()  {
		int pecStart = binaryReadInt32()
		fseek(file, 4, SEEK_CUR)
		readDescriptions()
		skip(14)
		int hoopNameStringLength = binaryReadByte()
		String hoopNameString = readString(hoopNameStringLength)
		if (hoopNameString.length() != 0) {
			pattern.setMetadata("hoop_name", hoopNameString)
		}
		skip(30)
		int fromImageStringLength = binaryReadByte()
		String fromImageString = readString(fromImageStringLength)
		if (fromImageString.length() != 0) {
			pattern.setMetadata("image_file", fromImageString)
		}
		skip(34)
		int nProgrammableFills = binaryReadInt16()
		if (nProgrammableFills != 0) {
			fseek(file, pecStart, SEEK_SET)
			return
		}
		int nMotifs = binaryReadInt16()
		if (nMotifs != 0) {
			fseek(file, pecStart, SEEK_SET)
			return
		}
		int featherPatternCount = binaryReadInt16()
		if (featherPatternCount != 0) {
			fseek(file, pecStart, SEEK_SET)
			return
		}
		int nColors = binaryReadInt16()
		for (int i = 0; i < nColors; i++) {
			readThread()
		}
		fseek(file, pecStart, SEEK_SET)
	}

	void readPESHeaderV10()  {
		int pecStart = binaryReadInt32()
		fseek(file, 4, SEEK_CUR)
		readDescriptions()
		skip(14)
		int hoopNameStringLength = binaryReadByte()
		String hoopNameString = readString(hoopNameStringLength)
		if (hoopNameString.length() != 0) {
			pattern.setMetadata("hoop_name", hoopNameString)
		}
		fseek(file, 38, SEEK_CUR)
		int fromImageStringLength = binaryReadByte()
		String fromImageString = readString(fromImageStringLength)
		if (fromImageString.length() != 0) {
			pattern.setMetadata("image_file", fromImageString)
		}
		skip(34)
		int nProgrammableFills = binaryReadInt16()
		if (nProgrammableFills != 0) {
			fseek(file, pecStart, SEEK_SET)
			return
		}
		int nMotifs = binaryReadInt16()
		if (nMotifs != 0) {
			fseek(file, pecStart, SEEK_SET)
			return
		}
		int featherPatternCount = binaryReadInt16()
		if (featherPatternCount != 0) {
			fseek(file, pecStart, SEEK_SET)
			return
		}
		int nColors = binaryReadInt16()
		for (int i = 0; i < nColors; i++) {
			readThread()
		}
		fseek(file, pecStart, SEEK_SET)
	}
	
	void readThread() {
		int color_code_length = binaryReadByte()
		String color_code = readString(color_code_length)
		int red = binaryReadByte()
		int green = binaryReadByte()
		int blue = binaryReadByte()
		skip(5)
		int descriptionStringLength = binaryReadByte()
		String description = readString(descriptionStringLength)

		int brandStringLength = binaryReadByte()
		String brand = readString(brandStringLength)

		int threadChartStringLength = binaryReadByte()
		String threadChart = readString(threadChartStringLength)

		int color = (red & 0xFF) << 16 | (green & 0xFF) << 8 | (blue & 0xFF)
		pattern.add(new EmbThread(color, description, color_code, brand, threadChart))
	}
*/
pesWriteSewSegSection(EmbPattern* pattern, int file, const char* fileName):
	/* TODO: pointer safety */
	int colorInfo
	int flag = 0
	int count = 0
	int colorCode = -1
	int stitchType = 0
	int blockCount = 0
	int colorCount = 0
	int newColorCode = 0
	int colorInfoIndex = 0
	int i
	EmbRect bounds = embPattern_calcBoundingBox(pattern)
	EmbStitch st

	/* TODO: why is this repeated below? */
	/*
	for (i=0; i<pattern->stitchList->length; i++) {
		j = i
		flag = st.flags
		t = pattern_thread(p, st.color)
		newColorCode = embThread_findNearestColor_fromThread(t.color, pec_thread)
		if (newColorCode != colorCode) {
			colorCount++
			colorCode = newColorCode
		}
		while (i<pattern->stitchList->length && (flag == st.flags)) {
			st = pattern->stitchList->stitch[i]
			count++
			i++
		}
		blockCount++
		i = j
	}
	*/

	binaryWriteShort(file, (short)blockCount); /* block count */
	binaryWriteUShort(file, 0xFFFF)
	binaryWriteShort(file, 0x00)

	binaryWriteShort(file, 0x07); /* string length */
	binaryWriteBytes(file, "CSewSeg", 7)

	colorInfo = tmpfile()
	for (i=0; i<colorCount*2; i++) {
		short s = 0
		fwrite(&s, sizeof(short), 1, colorInfo)
	}

	colorCode = -1
	blockCount = 0
	for (i = 0; i < pattern->stitchList->length; i++) {
		EmbThread t
		embArray_get(pattern->stitchList, &st, i)
		flag = st.flags
		t = pattern_thread(pattern, st.color)
		newColorCode = embThread_findNearestColor(t.color, pec_thread)
		if (newColorCode != colorCode) {
			short s
			s = (short)blockCount
			fwrite(&s, sizeof(short), 1, colorInfo)
			s = (short)newColorCode
			fwrite(&s, sizeof(short), 1, colorInfo)
			colorCode = newColorCode
		}
		/* TODO: check if this has an off-by-one error */
		for (count = 0; flag == st.flags; count++) {
			embArray_get(pattern->stitchList, &st, i + count)
		}

		/* 1 for jump, 0 for normal */
		stitchType = flag & JUMP
		binaryWriteShort(file, (short)stitchType)
		/* color code */
		binaryWriteShort(file, (short)colorCode)
		/* stitches in block */
		binaryWriteShort(file, (short)count)
		for (; flag == st.flags && i < pattern->stitchList->length; i++) {
			embArray_get(pattern->stitchList, &st, i)
			binaryWriteShort(file, (short)(st.x - bounds.left))
			binaryWriteShort(file, (short)(st.y + bounds.top))
		}
		if (i < pattern->stitchList->length) {
			binaryWriteUShort(file, 0x8003)
		}
		blockCount++
	}
	binaryWriteShort(file, (short)colorCount)
	embFile_copy(colorInfo, 0, file, 2*colorCount*sizeof(short))
	binaryWriteInt(file, 0)
	fclose(colorInfo)
	ret


pesWriteEmbOneSection(EmbPattern* pattern, int file, const char* fileName):
	/* TODO: pointer safety */
	int i
	int hoopHeight = 1800, hoopWidth = 1300
	EmbRect bounds
	binaryWriteShort(file, 0x07); /* string length */
	binaryWriteBytes(file, "CEmbOne", 7)
	bounds = embPattern_calcBoundingBox(pattern)

	binaryWriteShort(file, 0)
	binaryWriteShort(file, 0)
	binaryWriteShort(file, 0)
	binaryWriteShort(file, 0)

	binaryWriteShort(file, 0)
	binaryWriteShort(file, 0)
	binaryWriteShort(file, 0)
	binaryWriteShort(file, 0)

	/* AffineTransform */
	binaryWriteFloat(file, 1.0f)
	binaryWriteFloat(file, 0.0f)
	binaryWriteFloat(file, 0.0f)
	binaryWriteFloat(file, 1.0f)
	binaryWriteFloat(file, (float)((embRect_width(bounds) - hoopWidth) / 2))
	binaryWriteFloat(file, (float)((embRect_height(bounds) + hoopHeight) / 2))

	binaryWriteShort(file, 1)
	binaryWriteShort(file, 0); /* Translate X */
	binaryWriteShort(file, 0); /* Translate Y */
	binaryWriteShort(file, (short)embRect_width(bounds))
	binaryWriteShort(file, (short)embRect_height(bounds))

	for (i = 0; i < 8; i++) {
		binaryWriteByte(file, 0)
	}

	/*WriteSubObjects(br, pes, SubBlocks); */
	ret


char writePes(EmbPattern* pattern, int file, const char* fileName):
	int pecLocation

	embPattern_flipVertical(pattern)
	embPattern_scale(pattern, 10.0)
	binaryWriteBytes(file, "#PES0001", 8)
	/* WRITE PECPointer 32 bit int */
	binaryWriteInt(file, 0x00)

	binaryWriteShort(file, 0x01)
	binaryWriteShort(file, 0x01)

	/* Write object count */
	binaryWriteUShort(file, 0x01)
	binaryWriteUShort(file, 0xFFFF); /* command */
	binaryWriteUShort(file, 0x00); /* unknown */

	pesWriteEmbOneSection(pattern, file, fileName)
	pesWriteSewSegSection(pattern, file, fileName)

	pecLocation = ftell(file)
	fseek(file, 0x08, SEEK_SET)
	binaryWriteByte(file, (unsigned char)(pecLocation & 0xFF))
	binaryWriteByte(file, (unsigned char)(pecLocation >> 8) & 0xFF)
	binaryWriteByte(file, (unsigned char)(pecLocation >> 16) & 0xFF)
	fseek(file, 0x00, SEEK_END)
	writePecStitches(pattern, file, fileName)
	return 1
	ret


char readPhb(EmbPattern* pattern, int file, const char* fileName):
	unsigned int fileOffset
	short colorCount
	int i
	unsigned int intin

	fseek(file, 0x71, SEEK_SET)
	embFile_readInt(file, &colorCount, 2)

	for (i = 0; i < colorCount; i++) {
		EmbThread t = load_thread(pec_thread, (int)binaryReadByte(file))
		embPattern_addThread(pattern, t)
	}

	/* TODO: check that file begins with #PHB */
	fseek(file, 0x54, SEEK_SET)
	embFile_readInt(file, &fileOffset, 4)
	fileOffset += 0x52

	fseek(file, fileOffset, SEEK_SET)
	embFile_readInt(file, &intin, 4)
	fileOffset += intin + 2

	fseek(file, fileOffset, SEEK_SET)
	embFile_readInt(file, &intin, 4)
	fileOffset += intin

	fseek(file, fileOffset + 14, SEEK_SET); /* 28 */

	colorCount = (short)binaryReadByte(file)
	for (i = 0; i < colorCount; i++) {
		binaryReadByte(file)
	}
	fread(embBuffer, 1, 4, file); /* bytes to end of file */
	fseek(file, 17, SEEK_CUR)
	readPecStitches(pattern, file, fileName)

	embPattern_flipVertical(pattern)
	return 1; /*TODO: finish ReadPhb */
	ret


char writePhb(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish writePhb */
	ret


char readPhc(EmbPattern* pattern, int file, const char* fileName):
	int version, bytesInSection2
	unsigned short pecOffset, bytesInSection, bytesInSection3, colorChanges
	char pecAdd
	EmbThread t
	int i

	fseek(file, 0x07, SEEK_SET)
	version = binaryReadByte(file) - 0x30; /* converting from ansi number */
	fseek(file, 0x4D, SEEK_SET)
	embFile_readInt(file, &colorChanges, 2)

	for (i = 0; i < colorChanges; i++) {
		t = load_thread(pec_thread, (int)binaryReadByte(file))
		embPattern_addThread(pattern, t)
	}
	fseek(file, 0x2B, SEEK_SET)
	pecAdd = binaryReadByte(file)
	int fileLength
	embFile_readInt(file, &fileLength, 4)
	embFile_readInt(file, &pecOffset, 2)
	fseek(file, pecOffset + pecAdd, SEEK_SET)
	embFile_readInt(file, &bytesInSection, 2)
	fseek(file, bytesInSection, SEEK_CUR)
	embFile_readInt(file, &bytesInSection2, 4)
	fseek(file, bytesInSection2, SEEK_CUR)
	embFile_readInt(file, &bytesInSection3, 2)
	fseek(file, bytesInSection3 + 0x12, SEEK_CUR)

	readPecStitches(pattern, file, fileName)

	embPattern_flipVertical(pattern)
	return 1; /*TODO: finish ReadPhc */
	ret


char writePhc(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish writePhc */
	ret


char readPlt(EmbPattern* pattern, int file, const char* fileName):
	float scalingFactor = 40
	char input[512]

	embPattern_loadExternalColorFile(pattern, fileName)

	/* readline needs not to stop at \n, check the file format definition */
	while (!embFile_readline(file, input, 511)) {
		if (input[0] == 'P') {
			int flags, i, success
			char *x_str, *y_str
			float x, y
			if (input[1] == 'D') flags = NORMAL
			else if (input[1] == 'U') flags = STOP
			else break
			/* acts as sscanf call */
			x_str = input+2
			for (i=0; i<511; i++) {
				if (input[i] == ',') {
					input[i] = 0
					y_str = input+i+1
				}
				if (input[i] == ';') {
					input[i] = 0
					success = 1
				}
			}
			if (!success) {
				break
			}
			x = emb_array_to_float(x_str)
			y = emb_array_to_float(y_str)

			embPattern_addStitchAbs(pattern, x / scalingFactor, y / scalingFactor, flags, 1)
		}
	}
	return 1
	ret


char writePlt(EmbPattern* pattern, int file, const char* fileName):
	/* TODO: pointer safety */
	float scalingFactor = 40
	EmbStitch stitch
	int i
	char firstStitchOfBlock = 1

	embFile_print(file, "IN;ND;")

	for (i = 0; i < pattern->stitchList->length; i++) {
		embArray_get(pattern->stitchList, &stitch, i)
		if (stitch.flags & STOP) {
			firstStitchOfBlock = 1
		}
		if (firstStitchOfBlock) {
			embFile_print(file, "PU")
			writePoint(file, stitch.x * scalingFactor, stitch.y * scalingFactor)
			embFile_print(file, ";ST0.00,0.00;SP0;HT0;HS0;TT0;TS0;")
			firstStitchOfBlock = 0
		} else {
			embFile_print(file, "PD")
			writePoint(file, stitch.x * scalingFactor, stitch.y * scalingFactor)
			embFile_print(file, ";")
		}
	}
	embFile_print(file, "PU0.0,0.0;PU0.0,0.0;")

	return 1; /*TODO: finish WritePlt */
	ret


char readRgb(EmbPattern* pattern, int file, const char* fileName):
	EmbThread t
	pattern->threads->length = 0
	string_copy(t.catalogNumber, "NULL")
	string_copy(t.description, "NULL")
	while (fread(embBuffer, 1, 4, file) == 4) {
		t.color = embColor_fromStr(embBuffer)
		embPattern_addThread(pattern, t)
	}
	return 1
	ret


char writeRgb(EmbPattern* pattern, int file, const char* fileName):
	int i

	embBuffer[3] = 0
	for (i = 0; i < pattern->threads->length; i++) {
		EmbThread t
		t = pattern_thread(pattern, i)
		embColor_toStr(t.color, embBuffer)
		fwrite(embBuffer, 1, 4, file)
	}
	return 1
	ret


char sewDecode(unsigned char inputByte):
	/* TODO: fix return statement */
	return (inputByte >= 0x80) ? (char)(-~(inputByte - 1)) : (char)inputByte
	ret


char readSew(EmbPattern* pattern, int file, const char* fileName):
	int i, flags, nColors, fileLength
	char dx, dy, thisStitchIsJump = 0

	fseek(file, 0x00, SEEK_END)
	fileLength = ftell(file)
	fseek(file, 0x00, SEEK_SET)
	nColors = binaryReadByte(file)
	nColors += (binaryReadByte(file) << 8)

	for (i = 0; i < nColors; i++) { 
	
		EmbThread t
		short thread_number
		embFile_readInt(file, &thread_number, 2)
		t = load_thread(jef_thread, thread_number)
		embPattern_addThread(pattern, t)
	}
	fseek(file, 0x1D78, SEEK_SET)

	for (i = 0; ftell(file) < fileLength; i++) {
		unsigned char b0 = binaryReadByte(file)
		unsigned char b1 = binaryReadByte(file)

		flags = NORMAL
		if (thisStitchIsJump) {
			flags = TRIM
			thisStitchIsJump = 0
		}
		if (b0 == 0x80) {
			if (b1 == 1) {
				b0 = binaryReadByte(file)
				b1 = binaryReadByte(file)
				flags = STOP
			} else if ((b1 == 0x02) || (b1 == 0x04)) {
				thisStitchIsJump = 1
				b0 = binaryReadByte(file)
				b1 = binaryReadByte(file)
				flags = TRIM
			} else if (b1 == 0x10) {
				break
			}
		}
		dx = sewDecode(b0)
		dy = sewDecode(b1)
		if (emb_abs(dx) == 127 || emb_abs(dy) == 127) {
			thisStitchIsJump = 1
			flags = TRIM
		}

		embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1)
	}
	embLog("current position: ")
	emb_int_to_array((char*)embBuffer, (int)ftell(file), 10)
	embLog((char*)embBuffer)

	return 1
	ret


sewEncode(unsigned char* b, char dx, char dy, int flags):
	if (flags == STOP) {
		b[0] = 0x80
		b[1] = 1
		b[2] = dx
		b[3] = dy
	} else if (flags == END) {
		b[0] = 0x80
		b[1] = 0x10
		b[2] = 0
		b[3] = 0
	} else if (flags == TRIM || flags == JUMP) {
		b[0] = 0x80
		b[1] = 2
		b[2] = dx
		b[3] = dy
	} else {
		b[0] = dx
		b[1] = dy
	}
	ret

char writeSew(EmbPattern* pattern, int file, const char* fileName):
	int colorlistSize, minColors, i
	float xx, yy

	colorlistSize = pattern->threads->length

	minColors = emb_max_int(pattern->threads->length, 6)
	binaryWriteInt(file, 0x74 + (minColors * 4))
	binaryWriteInt(file, 0x0A)

	for (i = 0; i < pattern->threads->length; i++) {
		int thr
		EmbThread t
		t = pattern_thread(pattern, i)
		thr = embThread_findNearestColor(t.color, jef_thread)
		binaryWriteInt(file, thr)
	}

	embFile_pad(file, 0x0D, (minColors - colorlistSize))
	embFile_pad(file, ' ', 7536)

	xx = 0.0
	yy = 0.0
	for (i = 0; i < pattern->stitchList->length; i++) {
		unsigned char b[4]
		float dx, dy
		EmbStitch st
		embArray_get(pattern->stitchList, &st, i)
		dx = st.x * 10.0 - xx
		dy = st.y * 10.0 - yy
		xx = st.x * 10.0
		yy = st.y * 10.0
		sewEncode(b, (char)round(dx), (char)round(dy), st.flags)
		if ((b[0] == 0x80) && ((b[1] == 1) || (b[1] == 2) || (b[1] == 4) || (b[1] == 0x10))) {
			fwrite(b, 1, 4, file)
		} else {
			fwrite(b, 1, 2, file)
		}
	}
	return 1
	ret


char shvDecode(unsigned char inputByte):
	if (inputByte >= 0x80) {
		return (char)-((unsigned char)((~inputByte) + 1))
	}
	return ((char)inputByte)
	ret


short shvDecodeShort(unsigned short inputByte):
	if (inputByte > 0x8000) {
		return (short)-((unsigned short)((~inputByte) + 1))
	}
	return ((short)inputByte)
	ret


char readShv(EmbPattern* pattern, int file, const char* fileName):
	int i
	char inJump = 0
	unsigned char fileNameLength, designWidth, designHeight
	char halfDesignWidth, halfDesignHeight, halfDesignWidth2, halfDesignHeight2
	char* headerText = "Embroidery disk created using software licensed from Viking Sewing Machines AB, Sweden"
	char dx = 0, dy = 0
	char nColors
	unsigned short magicCode
	int something
	short left, top, right, bottom
	char something2, numberOfSections, something3
	int stitchesPerColor[256]
	int stitchesSinceChange = 0
	int currColorIndex = 0
	unsigned short sx, sy

	fseek(file, string_length(headerText), SEEK_SET)
	fileNameLength = binaryReadUInt8(file)
	fseek(file, fileNameLength, SEEK_CUR)
	designWidth = binaryReadUInt8(file)
	designHeight = binaryReadUInt8(file)
	halfDesignWidth = binaryReadUInt8(file)
	halfDesignHeight = binaryReadUInt8(file)
	halfDesignWidth2 = binaryReadUInt8(file)
	halfDesignHeight2 = binaryReadUInt8(file)
	if ((designHeight % 2) == 1) {
		fseek(file, ((designHeight + 1) * designWidth) / 2, SEEK_CUR)
	} else {
		fseek(file, (designHeight * designWidth) / 2, SEEK_CUR)
	}
	nColors = binaryReadUInt8(file)
	embFile_readInt(file, &magicCode, 2)
	binaryReadByte(file)
	embFile_readInt(file, &something, 4)
	embFile_readInt(file, &left, 2)
	embFile_readInt(file, &top, 2)
	embFile_readInt(file, &right, 2)
	embFile_readInt(file, &bottom, 2)

	something2 = binaryReadByte(file)
	numberOfSections = binaryReadUInt8(file)
	something3 = binaryReadByte(file)

	for (i = 0; i < nColors; i++) {
		EmbThread t
		unsigned int stitchCount, colorNumber
		embFile_readInt_be(file, &stitchCount, 4)
		colorNumber = binaryReadUInt8(file)
		t = load_thread(shv_thread, colorNumber % 43)
		embPattern_addThread(pattern, t)
		stitchesPerColor[i] = stitchCount
		fseek(file, 9, SEEK_CUR)
	}

	fseek(file, -2, SEEK_CUR)

	while (1) {
		unsigned char b0, b1
		int flags
		if (inJump) {
			flags = JUMP
		} else {
			flags = NORMAL
		}
		if (fread(embBuffer, 1, 2, file) != 2) break
		b0 = embBuffer[0]
		b1 = embBuffer[1]
		if (stitchesSinceChange >= stitchesPerColor[currColorIndex]) {
			embPattern_addStitchRel(pattern, 0, 0, STOP, 1)
			currColorIndex++
			stitchesSinceChange = 0
		}
		if (b0 == 0x80) {
			stitchesSinceChange++
			if (b1 == 3) {
				continue
			} else if (b1 == 0x02) {
				inJump = 0
				continue
			} else if (b1 == 0x01) {
				stitchesSinceChange += 2
				sx = binaryReadUInt8(file)
				sx = (unsigned short)(sx << 8 | binaryReadUInt8(file))
				sy = binaryReadUInt8(file)
				sy = (unsigned short)(sy << 8 | binaryReadUInt8(file))
				flags = TRIM
				inJump = 1
				embPattern_addStitchRel(pattern, shvDecodeShort(sx) / 10.0, shvDecodeShort(sy) / 10.0, flags, 1)
				continue
			}
		}
		dx = shvDecode(b0)
		dy = shvDecode(b1)
		stitchesSinceChange++
		embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1)
	}

	embPattern_flipVertical(pattern)

	return 1
	ret


char writeShv(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish writeShv */
	ret


char readSst(EmbPattern* pattern, int file, const char* fileName):
	int fileLength

	embPattern_loadExternalColorFile(pattern, fileName)
	fseek(file, 0, SEEK_END)
	fileLength = ftell(file)
	fseek(file, 0xA0, SEEK_SET); /* skip the all zero header */
	while (ftell(file) < fileLength) {
		int stitchType = NORMAL

		int b1 = (int)binaryReadByte(file)
		int b2 = (int)binaryReadByte(file)
		unsigned char commandByte = binaryReadByte(file)

		if (commandByte == 0x04) {
			break
		}

		if ((commandByte & 0x01) == 0x01)
			stitchType = STOP
		if ((commandByte & 0x02) == 0x02)
			stitchType = JUMP
		if ((commandByte & 0x10) != 0x10)
			b2 = -b2
		if ((commandByte & 0x40) == 0x40)
			b1 = -b1
		embPattern_addStitchRel(pattern, b1 / 10.0, b2 / 10.0, stitchType, 1)
	}

	return 1; /*TODO: finish readSst */
	ret


char writeSst(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish writeSst */
	ret


typedef struct SubDescriptor_ {
	int someNum; /* TODO: better variable naming */
	int someInt; /* TODO: better variable naming */
	int someOtherInt; /* TODO: better variable naming */
	char colorCode[40]
	char colorName[40]
	ret
 SubDescriptor

typedef struct StxThread_ {
	char colorCode[40]
	char colorName[40]
	char sectionName[40]
	SubDescriptor subDescriptors[10]
	EmbColor stxColor
	ret
 StxThread

char stxReadThread(StxThread* thread, int file):
	int j, colorNameLength, sectionNameLength
	int somethingSomething, somethingSomething2, somethingElse, numberOfOtherDescriptors; /* TODO: determine what these represent */
	int codeLength = 0
	char* codeBuff = 0
	char* codeNameBuff = 0
	char* sectionNameBuff = 0
	EmbColor col
	unsigned char whatIsthis; /* TODO: determine what this represents */

	if (!thread) {
		embLog("ERROR: stxReadThread(), thread==0\n")
		return 0
	}
	if (!file) {
		embLog("ERROR: stxReadThread(), file==0\n")
		return 0
	}

	codeLength = binaryReadUInt8(file)
	fread(thread->colorCode, 1, codeLength, file); /* TODO: check return value */
	colorNameLength = binaryReadUInt8(file)
	fread(thread->colorName, 1, colorNameLength, file); /* TODO: check return value */

	col.r = binaryReadUInt8(file)
	col.b = binaryReadUInt8(file)
	col.g = binaryReadUInt8(file)

	whatIsthis = binaryReadUInt8(file)

	sectionNameLength = binaryReadUInt8(file)
	fread(thread->sectionName, 1, sectionNameLength, file); /* TODO: check return value */

	embFile_readInt(file, &somethingSomething, 4)
	embFile_readInt(file, &somethingSomething2, 4)
	embFile_readInt(file, &somethingElse, 4)
	embFile_readInt(file, &numberOfOtherDescriptors, 2)

	if (numberOfOtherDescriptors >= 10) {
		embLog("Ran of out memory for descriptors.")
		return 0
	}
	for (j = 0; j < numberOfOtherDescriptors; j++) {
		SubDescriptor sd
		unsigned char subCodeLength, subColorNameLength

		embFile_readInt(file, &(sd.someNum), 2)
		/* Debug.Assert(sd.someNum == 1); TODO: review */
		embFile_readInt(file, &(sd.someInt), 4)
		subCodeLength = binaryReadUInt8(file)
		fread(sd.colorCode, 1, subCodeLength, file); /* TODO: check return value */
		subColorNameLength = binaryReadUInt8(file)
		fread(sd.colorName, 1, subColorNameLength, file); /* TODO: check return value */
		embFile_readInt(file, &(sd.someOtherInt), 4)
		thread->subDescriptors[j] = sd
	}
	return 1
	ret


char readStx(EmbPattern* pattern, int file, const char* fileName):
	int i, threadCount
	unsigned char* gif = 0
	/* public bitmap Image; */
	StxThread stxThreads[100]
	unsigned char headerBytes[7]
	char* header = 0
	char filetype[4], version[5]
	int paletteLength, imageLength, something1, stitchDataOffset, something3, threadDescriptionOffset, stitchCount, left, right, colors
	int val[6], vala[6]
	int bottom, top

	binaryReadBytes(file, headerBytes, 7); /* TODO: check return value */
	header = (char*)headerBytes

	memory_copy(filetype, &header[0], 3)
	memory_copy(version, &header[3], 4)
	filetype[3] = '\0'
	version[4] = '\0'
	binaryReadByte(file)
	embFile_readInt(file, &paletteLength, 4)
	embFile_readInt(file, &imageLength, 4)
	embFile_readInt(file, &something1, 4)
	embFile_readInt(file, &stitchDataOffset, 4)
	embFile_readInt(file, &something3, 4)
	embFile_readInt(file, &threadDescriptionOffset, 4)
	embFile_readInt(file, &stitchCount, 4)
	embFile_readInt(file, &colors, 4)
	embFile_readInt(file, &right, 2)
	embFile_readInt(file, &left, 2)
	embFile_readInt(file, &bottom, 2)
	embFile_readInt(file, &top, 2)

	/* gif */
	fread(embBuffer, 1, imageLength, file); /* TODO: check return value */
	/*Stream s2 = new MemoryStream(gif); TODO: review */
	/*Image = new bitmap(s2); TODO: review */

	embFile_readInt(file, &threadCount, 2)
	for (i = 0; i < threadCount; i++) {
		EmbThread t
		StxThread st
		stxReadThread(&st, file)

		t.color = st.stxColor
		string_copy(t.description, st.colorName)
		string_copy(t.catalogNumber, st.colorCode)
		embPattern_addThread(pattern, t)
		stxThreads[i] = st
	}

	fread(embBuffer, 1, 15, file)

	for (i=0; i<6; i++) {
		embFile_readInt(file, val+i, 2)
	}
	/* last two val[4] = 0, val[5] = 0 */

	for (i=0; i<6; i++) {
		embFile_readInt(file, vala+i, 2)
	}
	/* last two vala[4] = 0, vala[5] = 0 */

	fread(embBuffer, 1, 8, file)

	/* br.BaseStream.Position = stitchDataOffset; TODO: review */
	for (i = 1; i < stitchCount;) {
		char b0 = binaryReadByte(file)
		char b1 = binaryReadByte(file)
		if (b0 == -128) {
			switch (b1) {
			case 1:
				b0 = binaryReadByte(file)
				b1 = binaryReadByte(file)
				/*embPattern_addStitchRel(b0, b1, STOP); TODO: review */

				i++
				break
			case 2:
				b0 = binaryReadByte(file)
				b1 = binaryReadByte(file)
				embPattern_addStitchRel(pattern, b0 / 10.0, b1 / 10.0, JUMP, 1)
				i++
				break
			case -94:
				/* TODO: Is this a synchronize? If so document it in the comments. */
				break
			default:
				/*Debugger.Break(); TODO: review */
				break
			}
		} else {
			embPattern_addStitchRel(pattern, b0 / 10.0, b1 / 10.0, NORMAL, 1)
			i++
		}
	}

	embPattern_flipVertical(pattern)
	return 1
	ret


char writeStx(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish writeStx */
	ret


char decodeT01RecordFlags(unsigned char b2):
	if (b2 == 0xF3) {
		return END
	}
	switch (b2 & 0xC3) {
	case 0x03:
		return NORMAL
	case 0x83:
		return TRIM
	case 0xC3:
		return STOP
	default:
		return NORMAL
	}
	ret


char readT01(EmbPattern* pattern, int file, const char* fileName):
	unsigned char b[3]

	embPattern_loadExternalColorFile(pattern, fileName)

	while (fread(b, 1, 3, file) == 3) {
		int flags
		int x[2]
		decode_dst_ternary(x, b)
		flags = decodeT01RecordFlags(b[2])
		embPattern_addStitchRel(pattern, x[0] / 10.0, x[1] / 10.0, flags, 1)
		if (flags == END)
			break
	}

	return 1
	ret


char writeT01(EmbPattern* pattern, int file, const char* fileName):
	EmbRect boundingRect
	int pos[2], i

	embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1)

	boundingRect = embPattern_calcBoundingBox(pattern)

	pos[0] = 0
	pos[1] = 0
	for (i = 0; i < pattern->stitchList->length; i++) {
		unsigned char b[4]
		int dx[2]
		EmbStitch st
		embArray_get(pattern->stitchList, &st, i)
		/* convert from mm to 0.1mm for file format */
		dx[0] = round(st.x * 10.0) - pos[0]
		dx[1] = round(st.y * 10.0) - pos[1]
		pos[0] = round(st.x * 10.0)
		pos[1] = round(st.y * 10.0)
		
		encode_dst_ternary(dx, b)

		b[2] |= (char)3

		if (st.flags & END) {
			b[0] = 0
			b[1] = 0
			b[2] = 0xF3
		}
		if (st.flags & (JUMP | TRIM)) {
			b[2] = (char)(b[2] | 0x83)
		}
		if (st.flags & STOP) {
			b[2] = (char)(b[2] | 0xC3)
		}

		fwrite(b, 1, 3, file)
	}
	return 1
	ret


char readT09(EmbPattern* pattern, int file, const char* fileName):
	fseek(file, 0x0C, SEEK_SET)

	while (fread(embBuffer, 1, 3, file) == 3) {
		int stitchType = NORMAL
		int b1 = embBuffer[0]
		int b2 = embBuffer[1]
		if (embBuffer[2] == 0x00) {
			break
		}
		if (embBuffer[2] & 0x10)
			stitchType = STOP
		if (embBuffer[2] & 0x20)
			b1 = -b1
		if (embBuffer[2] & 0x40)
			b2 = -b2

		embPattern_addStitchRel(pattern, b2 / 10.0, b1 / 10.0, stitchType, 1)
	}

	return 1
	ret


char writeT09(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish writeT09 */
	ret


char decodeTapRecordFlags(unsigned char b2):
	if (b2 == 0xF3) {
		return END
	}
	switch (b2 & 0xC3) {
	case 0x03:
		return NORMAL
	case 0x83:
		return TRIM
	case 0xC3:
		return STOP
	default:
		return NORMAL
	}
	ret


int encode_dst_ternary(int *x, unsigned char *b):
	/* cannot encode values > +121 or < -121. */
	if (x[0] > 121 || x[0] < -121) {
		embLog("ERROR: encode_dst_ternary(), x is not in valid range [-121,121]\n")
		return 0
	}
	if (x[1] > 121 || x[1] < -121) {
		embLog("ERROR: encode_dst_ternary(), y is not in valid range [-121,121]\n")
		return 0
	}

	if (x[0] >= +41) {
		b[2] |= 1 << 2
		x[0] -= 81
	}
	if (x[0] <= -41) {
		b[2] |= 1 << 3
		x[0] += 81
	}
	if (x[0] >= +14) {
		b[1] |= 1 << 2
		x[0] -= 27
	}
	if (x[0] <= -14) {
		b[1] |= 1 << 3
		x[0] += 27
	}
	if (x[0] >= +5) {
		b[0] |= 1 << 2
		x[0] -= 9
	}
	if (x[0] <= -5) {
		b[0] |= 1 << 3
		x[0] += 9
	}
	if (x[0] >= +2) {
		b[1] |= 1 << 0
		x[0] -= 3
	}
	if (x[0] <= -2) {
		b[1] |= 1 << 1
		x[0] += 3
	}
	if (x[0] >= +1) {
		b[0] |= 1 << 0
		x[0] -= 1
	}
	if (x[0] <= -1) {
		b[0] |= 1 << 1
		x[0] += 1
	}
	if (x[0] != 0) {
		embLog("ERROR: encode_tap_record(), x!=0\n")
		return 0
	}
	if (x[1] >= +41) {
		b[2] |= 1 << 5
		x[1] -= 81
	}
	if (x[1] <= -41) {
		b[2] |= 1 << 4
		x[1] += 81
	}
	if (x[1] >= +14) {
		b[1] |= 1 << 5
		x[1] -= 27
	}
	if (x[1] <= -14) {
		b[1] |= 1 << 4
		x[1] += 27
	}
	if (x[1] >= +5) {
		b[0] |= 1 << 5
		x[1] -= 9
	}
	if (x[1] <= -5) {
		b[0] |= 1 << 4
		x[1] += 9
	}
	if (x[1] >= +2) {
		b[1] |= 1 << 7
		x[1] -= 3
	}
	if (x[1] <= -2) {
		b[1] |= 1 << 6
		x[1] += 3
	}
	if (x[1] >= +1) {
		b[0] |= 1 << 7
		x[1] -= 1
	}
	if (x[1] <= -1) {
		b[0] |= 1 << 6
		x[1] += 1
	}
	if (x[1] != 0) {
		embLog("ERROR: encode_tap_record(), y!=0\n")
		return 0
	}
	return 1
	ret


/* A version of the stitch decoding with less branching,
 * the BIT macro returns either 0 or 1 based on the value
 * of that bit and then is multiplied by what value that represents.
 */
decode_dst_ternary(int *x, unsigned char *b):
	x[0]  =     bit(b[0], 0) - bit(b[0], 1)
	x[0] +=  9*(bit(b[0], 2) - bit(b[0], 3))
	x[1]  =     bit(b[0], 7) - bit(b[0], 6)
	x[1] +=  9*(bit(b[0], 5) - bit(b[0], 4))
	x[0] +=  3*(bit(b[1], 0) - bit(b[1], 1))
	x[0] += 27*(bit(b[1], 2) - bit(b[1], 3))
	x[1] +=  3*(bit(b[1], 7) - bit(b[1], 6))
	x[1] += 27*(bit(b[1], 5) - bit(b[1], 4))
	x[0] += 81*(bit(b[2], 2) - bit(b[2], 3))
	x[1] += 81*(bit(b[2], 5) - bit(b[2], 4))
	ret


char readTap(EmbPattern* pattern, int file, const char* fileName):
	unsigned char b[3]

	embPattern_loadExternalColorFile(pattern, fileName)

	while (fread(b, 1, 3, file) == 3) {
		int flags
		int x[2]
		decode_dst_ternary(x, b)
		flags = decodeTapRecordFlags(b[2])
		embPattern_addStitchRel(pattern, x[0] / 10.0, x[1] / 10.0, flags, 1)
		if (flags == END)
			break
	}

	return 1
	ret


char writeTap(EmbPattern* pattern, int file, const char* fileName):
	EmbRect boundingRect
	int pos[2], i

	embPattern_correctForMaxStitchLength(pattern, 12.1, 12.1)

	boundingRect = embPattern_calcBoundingBox(pattern)

	pos[0] = 0
	pos[1] = 0
	for (i = 0; i < pattern->stitchList->length; i++) {
		unsigned char b[3]
		int dx[2]
		EmbStitch st
		embArray_get(pattern->stitchList, &st, i)
		/* convert from mm to 0.1mm for file format */
		dx[0] = round(st.x * 10.0) - pos[0]
		dx[1] = round(st.y * 10.0) - pos[1]
		pos[0] = round(st.x * 10.0)
		pos[1] = round(st.y * 10.0)

		encode_dst_ternary(dx, b)

		b[2] |= (char)3

		if (st.flags & END) {
			b[0] = 0
			b[1] = 0
			b[2] = 0xF3
		}
		if (st.flags & (JUMP | TRIM)) {
			b[2] = (char)(b[2] | 0x83)
		}
		if (st.flags & STOP) {
			b[2] = (char)(b[2] | 0xC3)
		}

		fwrite(b, 1, 3, file)
	}
	return 1
	ret


#define NOTFRM 0x00080000

typedef struct ThredHeader_ /* thred file header */
{
	unsigned int sigVersion; /* signature and version */
	unsigned int length; /* length of ThredHeader + length of stitch data */
	unsigned short numStiches; /* number of stitches */
	unsigned short hoopSize; /* size of hoop */
	unsigned short reserved[7]; /* reserved for expansion */
	ret
 ThredHeader

typedef struct ThredExtension_ /* thred v1.0 file header extension */
{
	float hoopX; /* hoop size x dimension in 1/6 mm units */
	float hoopY; /* hoop size y dimension in 1/6 mm units */
	float stitchGranularity; /* stitches per millimeter--not implemented */
	char creatorName[50]; /* name of the file creator */
	char modifierName[50]; /* name of last file modifier */
	char auxFormat; /* auxiliary file format, 0=PCS,1=DST,2=PES */
	char reserved[31]; /* reserved for expansion */
	ret
 ThredExtension

/*
bit definitions for attributes of stitch
0-3     stitch color
4-14    form pointer
15-18   spares
19      not a form stitch
20      center walk stitch
21      edge walk stitch
22      underlay stitch
23      knot stitch
24      feather stitch
25-27   layer
28      spare
29-30   stitch type 00=not a form stitch, 01=form fill, 10=form border fill, 11=applique stitches
31      set for user edited stitches
*/

char readThr(EmbPattern* pattern, int file, const char* fileName):
	ThredHeader header
	/* EmbColor c; */
	EmbThread thread
	int currentColor, i

	embFile_readInt(file, &header.sigVersion, 4)
	embFile_readInt(file, &header.length, 4)
	embFile_readInt(file, &header.numStiches , 2)
	embFile_readInt(file, &header.hoopSize, 2)
	for (i=0; i<7; i++) {
		embFile_readInt(file, header.reserved + i, 2)
	}

	if ((header.sigVersion & 0xffffff) == 0x746872) {
		unsigned int verVar = (header.sigVersion & 0xff000000) >> 24
		switch (verVar) {
		case 0:
			break
		case 1:
		case 2:
			fseek(file, 144, SEEK_CUR); /* skip the file header extension */
			break
		default:
			return 0; /* unsupported version */
		}
	}

	currentColor = -1
	for (i = 0; i < header.numStiches; i++) {
		int type = NORMAL
		float x = binaryReadFloat(file) / 10.0f
		float y = binaryReadFloat(file) / 10.0f
		unsigned int color
		embFile_readInt(file, &color, 4)

		if ((int)(color & 0xF) != currentColor) {
			currentColor = (int)color & 0xF
			embPattern_changeColor(pattern, currentColor)
			type = STOP | TRIM
		}
		embPattern_addStitchAbs(pattern, x, y, type, 0)
	}
	fseek(file, 16, SEEK_CUR); /* skip bitmap name (16 chars) */

	fread(embBuffer, 1, 4, file)
	/* background color: c = embColor_fromStr(embBuffer); */

	string_copy(thread.description, "NULL")
	string_copy(thread.catalogNumber, "NULL")
	fread(embBuffer, 1, 16*4, file)
	for (i = 0; i < 16; i++) {
		thread.color = embColor_fromStr(embBuffer+4*i)
		embPattern_addThread(pattern, thread)
	}
	/*  64 bytes of rgbx(4 bytes) colors (16 custom colors) */
	/*  16 bytes of thread size (ascii representation ie. '4') */

	return 1
	ret


char writeThr(EmbPattern* pattern, int file, const char* fileName):
	int i, stitchCount
	unsigned char version = 0
	ThredHeader header
	ThredExtension extension
	char bitmapName[16]
	EmbStitch st

	stitchCount = pattern->stitchList->length

	memory_set(&header, 0, sizeof(ThredHeader))
	header.sigVersion = 0x746872 | (version << 24)
	header.length = stitchCount * 12 + 16
	if (version == 1 || version == 2) {
		header.length = header.length + sizeof(ThredHeader)
	}
	header.numStiches = (unsigned short)stitchCount; /* number of stitches in design */
	header.hoopSize = 5

	binaryWriteUInt(file, header.sigVersion)
	binaryWriteUInt(file, header.length)
	binaryWriteUShort(file, header.numStiches)
	binaryWriteUShort(file, header.hoopSize)
	for (i=0; i<7; i++) {
		binaryWriteUShort(file, header.reserved[i])
	}

	if (version == 1 || version == 2) {
		memory_set(&extension, 0, sizeof(ThredExtension))
		extension.auxFormat = 1
		extension.hoopX = 640
		extension.hoopY = 640

		binaryWriteFloat(file, extension.hoopX)
		binaryWriteFloat(file, extension.hoopY)
		binaryWriteFloat(file, extension.stitchGranularity)
		binaryWriteBytes(file, extension.creatorName, 50)
		binaryWriteBytes(file, extension.modifierName, 50)
		binaryWriteByte(file, extension.auxFormat)
		binaryWriteBytes(file, extension.reserved, 31)
	}

	/* write stitches */
	for (i = 0; i < pattern->stitchList->length; i++) {
		embArray_get(pattern->stitchList, &st, i)
		binaryWriteFloat(file, (float)(st.x * 10.0))
		binaryWriteFloat(file, (float)(st.y * 10.0))
		binaryWriteUInt(file, NOTFRM | (st.color & 0x0F))
	}
	binaryWriteBytes(file, bitmapName, 16)
	/* background color */
	fread("\xFF\xFF\xFF\x00", 1, 4, file)

	embPattern_colorBlock16(pattern, file)

	embFile_pad(file, '4', 16)

	return 1
	ret


char readTxt(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish readTxt */
	ret


char writeTxt(EmbPattern* pattern, int file, const char* fileName):
	int i

	writeInt(file, pattern->stitchList->length, 6)
	embFile_print(file, "\n")

	for (i = 0; i < pattern->stitchList->length; i++) {
		EmbStitch st
		embArray_get(pattern->stitchList, &st, i)
		/* embFile_print(file, "%.1f,%.1f color:%i flags:%i\n", st.x, st.y, st.color, st.flags); */
		writePoint(file, st.x, st.y)
		embFile_print(file, " color:")
		writeInt(file, st.color, 6)
		embFile_print(file, " flags:")
		writeInt(file, st.flags, 6)
		embFile_print(file, "\n")
	}
	return 1
	ret


/**
 * 
 */

encode_u00_stitch(EmbStitch st, unsigned char *data):
	char dx, dy
	dx = (char)round(10.0*st.x)
	dy = (char)round(10.0*st.y)
	data[2] = dx
	data[1] = dy
	data[0] = 0
	if (dx < 0.0) {
		data[0] |= 0x20
	}
	if (dy < 0.0) {
		data[0] |= 0x40
	}
	switch (st.flags) {
	case JUMP:
		data[0] |= 0x10
		break
	case STOP:
		data[0] |= 0x01
		break
	case END:
		data[0] = 0xF8
		break
	case NORMAL:
	default:
		break
	}
	ret


EmbStitch decode_u00_stitch(unsigned char *data):
	EmbStitch st
	st.flags = NORMAL
	if (data[0] == 0xF8 || data[0] == 0x87 || data[0] == 0x91) {
		st.flags = END
	}
	if ((data[0] & 0x0F) == 0) {
		st.flags = NORMAL
	} else if ((data[0] & 0x1f) == 1) {
		st.flags = JUMP
	} else if ((data[0] & 0x0F) > 0) {
		st.flags = STOP
	}

	st.x = data[2]/10.0
	st.y = data[1]/10.0
	if ((data[0] & 0x20) > 0)
		st.x *= -1.0
	if ((data[0] & 0x40) > 0)
		st.y *= -1.0
	return st
	ret


char readU00(EmbPattern* pattern, int file, const char* fileName):
	int i

	/* 16 3byte RGB's start @ 0x08 followed by 14 bytes between 0 and 15 with index of color for each color change */
	fseek(file, 0x08, SEEK_SET)

	for (i = 0; i < 16; i++) {
		EmbThread t
		fread(embBuffer, 1, 3, file)
		t.color = embColor_fromStr(embBuffer)
		embPattern_addThread(pattern, t)
	}

	fseek(file, 0x100, SEEK_SET)
	while (fread(embBuffer, 1, 3, file) == 3) {
		EmbStitch st
		st = decode_u00_stitch(embBuffer)
		if (st.flags == END) {
			break
		}
		embPattern_addStitchRel(pattern, st.x, st.y, st.flags, 1)
	}

	return 1
	ret


char writeU00(EmbPattern* pattern, int file, const char* fileName):
	unsigned char b[4], i

	embFile_pad(file, ' ', 8)

	for (i = 0; i < pattern->threads->length; i++) {
		EmbThread t
		t = pattern_thread(pattern, i)
		embColor_toStr(t.color, b)
		fwrite(b, 1, 3, file)
	}

	/* this should pad to 256 bytes */
	embFile_pad(file, ' ', 0x100 - 3*pattern->threads->length - 8)

	for (i = 0; i < pattern->stitchList->length; i++) {
		EmbStitch st
		embArray_get(pattern->stitchList, &st, i)
		encode_u00_stitch(st, b)
		fwrite(b, 1, 3, file)
	}
	return 1
	ret


char readU01(EmbPattern* pattern, int file, const char* fileName):
	return readU00(pattern, file, fileName)
	ret


char writeU01(EmbPattern* pattern, int file, const char* fileName):
	return writeU00(pattern, file, fileName)
	ret


char vipDecodeByte(unsigned char b):
	if (b >= 0x80)
		return (-(unsigned char)(~b + 1))
	return b
	ret


char vipDecodeStitchType(unsigned char b):
	switch (b) {
	case 0x80:
		return NORMAL
	case 0x81:
		return TRIM
	case 0x84:
		return STOP
	case 0x90:
		return END
	default:
		return NORMAL
	}
	ret


typedef struct VipHeader_ {
	int magicCode
	int numberOfStitches
	int nColors
	short postitiveXHoopSize
	short postitiveYHoopSize
	short negativeXHoopSize
	short negativeYHoopSize
	int attributeOffset
	int xOffset
	int yOffset
	unsigned char stringVal[8]
	short unknown
	int colorLength
	ret
 VipHeader

char readVip(EmbPattern* pattern, int file, const char* fileName):
	int fileLength
	int i
	unsigned char prevByte = 0
	int attributeData
	int attributeDataDecompressed
	int decodedColors
	int xData
	int xDecompressed
	int yData
	int yDecompressed
	VipHeader header

	fseek(file, 0x0, SEEK_END)
	fileLength = ftell(file)
	fseek(file, 0x00, SEEK_SET)
	embFile_readInt(file, &(header.magicCode), 4)
	embFile_readInt(file, &(header.numberOfStitches), 4)
	embFile_readInt(file, &(header.nColors), 4)

	embFile_readInt(file, &(header.postitiveXHoopSize), 2)
	embFile_readInt(file, &(header.postitiveYHoopSize), 2)
	embFile_readInt(file, &(header.negativeXHoopSize), 2)
	embFile_readInt(file, &(header.negativeYHoopSize), 2)

	embFile_readInt(file, &(header.attributeOffset), 4)
	embFile_readInt(file, &(header.xOffset), 4)
	embFile_readInt(file, &(header.yOffset), 4)

	/*stringVal = embBuffer; TODO: review this and uncomment or remove
	 */

	binaryReadBytes(file, header.stringVal, 8); /* TODO: check return value */

	embFile_readInt(file, &(header.unknown), 2)
	embFile_readInt(file, &(header.colorLength), 4)

	fseek(datafile, vip_decoding_table, SEEK_SET)
	fread(embBuffer, 1, header.nColors*4, datafile)
	for (i = 0; i < header.nColors * 4; ++i) {
		unsigned char inputByte = binaryReadByte(file)
		unsigned char tmpByte = (unsigned char)(inputByte ^ embBuffer[i])
		unsigned char c = (unsigned char)(tmpByte ^ prevByte)
		fwrite(&c, 1, 1, decodedColors)
		prevByte = inputByte
	}
	for (i = 0; i < header.nColors; i++) {
		EmbThread thread
		int startIndex = i << 2
		fseek(decodedColors, startIndex, SEEK_SET)
		fread(&(thread.color.r), 1, 1, decodedColors)
		fread(&(thread.color.g), 1, 1, decodedColors)
		fread(&(thread.color.b), 1, 1, decodedColors)
		/* printf("%d\n", decodedColors[startIndex + 3]); */
		embPattern_addThread(pattern, thread)
	}

	embFile_copy(file, header.attributeOffset, attributeData, header.xOffset - header.attributeOffset); /* TODO: check return value */
	husExpand(attributeData, attributeDataDecompressed, 10)

	embFile_copy(file, header.xOffset, xData, header.yOffset - header.xOffset); /* TODO: check return value */
	husExpand(xData, xDecompressed, 10)

	embFile_copy(file, header.yOffset, yData, fileLength - header.yOffset); /* TODO: check return value */
	husExpand(yData, yDecompressed, 10)

	for (i = 0; i < header.numberOfStitches; i++) {
		unsigned char cx, cy, catt
		float x, y
		int attribute
		fread(&cx, 1, 1, xDecompressed)
		fread(&cy, 1, 1, yDecompressed)
		fread(&catt, 1, 1, attributeDataDecompressed)
		x = vipDecodeByte(cx)
		y = vipDecodeByte(cy)
		attribute = vipDecodeStitchType(catt)
		embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, attribute, 1)
	}

	fclose(attributeData)
	fclose(xData)
	fclose(yData)
	fclose(attributeDataDecompressed)
	fclose(xDecompressed)
	fclose(yDecompressed)

	return 1
	ret


vipEncodeByte:
	/* (float f) return unsigned char */
	return (unsigned char)(int)round(f)
	ret

unsigned char vipEncodeStitchType(int st):
	switch (st) {
	case NORMAL:
		return (0x80)
	case JUMP:
	case TRIM:
		return (0x81)
	case STOP:
		return (0x84)
	case END:
		return (0x90)
	default:
		return (0x80)
	}
	ret


char writeVip(EmbPattern* pattern, int file, const char* fileName):
	EmbRect boundingRect
	int stitchCount, minColors, patternColor, attributeSize = 0,
		xCompressedSize = 0, yCompressedSize = 0
	EmbVector previous
	EmbStitch st
	int i
	int xValues
	int yValues
	int attributeValues
	int xCompressed
	int yCompressed
	int attributeCompressed
	int decodedColors
	unsigned char prevByte = 0

	stitchCount = pattern->stitchList->length
	minColors = pattern->threads->length
	/* embPattern_correctForMaxStitchLength(pattern, 0x7F, 0x7F); */

	patternColor = minColors
	if (minColors > 24)
		minColors = 24

	binaryWriteUInt(file, 0x0190FC5D)
	binaryWriteUInt(file, stitchCount)
	binaryWriteUInt(file, minColors)

	boundingRect = embPattern_calcBoundingBox(pattern)
	binaryWriteShort(file, (short)round(boundingRect.right * 10.0))
	binaryWriteShort(file, (short)-round(boundingRect.top * 10.0 - 1.0))
	binaryWriteShort(file, (short)round(boundingRect.left * 10.0))
	binaryWriteShort(file, (short)-round(boundingRect.bottom * 10.0 - 1.0))

	binaryWriteUInt(file, 0x38 + (minColors << 3))

	previous.x = 0.0
	previous.y = 0.0
	for (i = 0; i < pattern->stitchList->length; i++) {
		unsigned char c
		embArray_get(pattern->stitchList, &st, i)
		c = vipEncodeByte((st.x - previous.x) * 10.0)
		fwrite(&c, 1, 1, xValues)
		c = vipEncodeByte((st.y - previous.y) * 10.0)
		fwrite(&c, 1, 1, yValues)
		previous.x = st.x
		previous.y = st.y
		c = vipEncodeStitchType(st.flags)
		fwrite(&c, 1, 1, attributeValues)
	}
	attributeSize = husCompress(attributeValues, attributeCompressed, 10)
	xCompressedSize = husCompress(xValues, xCompressed, 10)
	yCompressedSize = husCompress(yValues, yCompressed, 10)

	binaryWriteUInt(file, (unsigned int)(0x38 + (minColors << 3) + attributeSize))
	binaryWriteUInt(file, (unsigned int)(0x38 + (minColors << 3) + attributeSize + xCompressedSize))
	embFile_pad(file, 0, 10)

	binaryWriteInt(file, minColors << 2)

	for (i = 0; i < minColors; i++) {
		EmbThread t
		int byteChunk = i << 2
		t = pattern_thread(pattern, i)
		binaryWriteByte(decodedColors, t.color.r)
		binaryWriteByte(decodedColors, t.color.g)
		binaryWriteByte(decodedColors, t.color.b)
		binaryWriteByte(decodedColors, 0x01)
	}

	fseek(datafile, vip_decoding_table, SEEK_SET)
	fread(embBuffer, 1, minColors << 2, datafile)
	for (i = 0; i < minColors << 2; ++i) {
		unsigned char color
		fread(&color, 1, 1, decodedColors)
		unsigned char tmpByte = (unsigned char)(color ^ embBuffer[i])
		prevByte = (unsigned char)(tmpByte ^ prevByte)
		binaryWriteByte(file, prevByte)
	}
	for (i = 0; i <= minColors; i++) {
		binaryWriteInt(file, 1)
	}
	binaryWriteUInt(file, 0); /* string length */
	binaryWriteShort(file, 0)
	embFile_copy(attributeCompressed, 0, file, attributeSize)
	embFile_copy(xCompressed, 0, file, xCompressedSize)
	embFile_copy(yCompressed, 0, file, yCompressedSize)

	fclose(attributeCompressed)
	fclose(xCompressed)
	fclose(yCompressed)
	fclose(attributeValues)
	fclose(xValues)
	fclose(yValues)
	fclose(decodedColors)

	return 1
	ret


unsigned char* vp3ReadString(int file):
	short stringLength
	if (!file) {
		embLog("ERROR: vp3ReadString(), file==0\n")
		return 0
	}
	embFile_readInt_be(file, &stringLength, 2)
	fread(embBuffer, 1, stringLength, file); /* TODO: check return value */
	return embBuffer
	ret


char vp3Decode(unsigned char inputByte):
	if (inputByte > 0x80) {
		return (int)-((unsigned char)((~inputByte) + 1))
	}
	return ((int)inputByte)
	ret


short vp3DecodeInt16(unsigned short inputByte):
	if (inputByte > 0x8000) {
		return -((short)((~inputByte) + 1))
	}
	return ((short)inputByte)
	ret


typedef struct _vp3Hoop {
	int right
	int bottom
	int left
	int top
	int threadLength
	char unknown2
	unsigned char nColors
	unsigned short unknown3
	int unknown4
	int numberOfBytesRemaining

	int xOffset
	int yOffset

	unsigned char byte1
	unsigned char byte2
	unsigned char byte3

	/* Centered hoop dimensions */
	int right2
	int left2
	int bottom2
	int top2

	int width
	int height
	ret
 vp3Hoop

vp3Hoop vp3ReadHoopSection(int file):
	vp3Hoop hoop

	if (!file) {
		embLog("ERROR: vp3ReadHoopSection(), file==0\n")
		hoop.bottom = 0
		hoop.left = 0
		hoop.right = 0
		hoop.top = 0
		return hoop
	}

	embFile_readInt_be(file, &(hoop.right), 4)
	embFile_readInt_be(file, &(hoop.left), 4)
	embFile_readInt_be(file, &(hoop.bottom), 4)
	embFile_readInt_be(file, &(hoop.top), 4)

	embFile_readInt(file, &hoop.threadLength, 4); /* yes, it seems this is _not_ big endian */
	hoop.unknown2 = binaryReadByte(file)
	hoop.nColors = binaryReadByte(file)
	embFile_readInt_be(file, &(hoop.unknown3), 2)
	embFile_readInt_be(file, &(hoop.unknown4), 4)
	embFile_readInt_be(file, &(hoop.numberOfBytesRemaining), 4)

	embFile_readInt_be(file, &(hoop.xOffset), 4)
	embFile_readInt_be(file, &(hoop.yOffset), 4)

	hoop.byte1 = binaryReadByte(file)
	hoop.byte2 = binaryReadByte(file)
	hoop.byte3 = binaryReadByte(file)

	/* Centered hoop dimensions */
	embFile_readInt_be(file, &(hoop.right2), 4)
	embFile_readInt_be(file, &(hoop.left2), 4)
	embFile_readInt_be(file, &(hoop.bottom2), 4)
	embFile_readInt_be(file, &(hoop.top2), 4)

	embFile_readInt_be(file, &(hoop.width), 4)
	embFile_readInt_be(file, &(hoop.height), 4)
	return hoop
	ret


char readVp3(EmbPattern* pattern, int file, const char* fileName):
	unsigned char magicString[5]
	unsigned char some
	unsigned char* softwareVendorString = 0
	unsigned char v1[18]
	unsigned char* anotherSoftwareVendorString = 0
	int nColors
	long colorSectionOffset
	unsigned char magicCode[6]
	short someShort
	unsigned char someByte
	int bytesRemainingInFile
	unsigned char* fileCommentString = 0; /* some software writes used settings here */
	int hoopConfigurationOffset
	unsigned char* anotherCommentString = 0
	int i

	binaryReadBytes(file, magicString, 5); /* %vsm% */ /* TODO: check return value */

	some = binaryReadByte(file); /* 0 */
	softwareVendorString = vp3ReadString(file)
	embFile_readInt(file, &someShort, 2)
	someByte = binaryReadByte(file)
	embFile_readInt(file, &bytesRemainingInFile, 4)
	fileCommentString = vp3ReadString(file)
	hoopConfigurationOffset = (int)ftell(file)

	vp3ReadHoopSection(file)

	anotherCommentString = vp3ReadString(file)

	/* TODO: review v1 thru v18 variables and use emb_unused() if needed */
	fread(v1, 1, 18, file)

	binaryReadBytes(file, magicCode, 6)
	if (!(magicCode[5] == 0 && string_equal("\x78\x78\x55\x55\x01", magicCode))) {
		return 0
	}

	anotherSoftwareVendorString = vp3ReadString(file)

	embFile_readInt_be(file, &nColors, 2)
	embLog("ERROR: Number of Colors: %d\n" /*, nColors */)
	colorSectionOffset = (int)ftell(file)

	for (i = 0; i < nColors; i++) {
		EmbThread t
		char tableSize
		int startX, startY, offsetToNextColorX, offsetToNextColorY
		unsigned char *threadColorNumber, *colorName, *threadVendor
		int unknownThreadString

		fseek(file, colorSectionOffset, SEEK_SET)
		fread(embBuffer, 1, 3, file)
		embLog("ERROR: Color Check Byte #1: 0 == %d\n")
		embLog("ERROR: Color Check Byte #2: 5 == %d\n")
		embLog("ERROR: Color Check Byte #3: 0 == %d\n")
		embFile_readInt_be(file, &colorSectionOffset, 4)
		colorSectionOffset += ftell(file)
		embFile_readInt_be(file, &startX, 4)
		embFile_readInt_be(file, &startY, 4)
		embPattern_addStitchAbs(pattern, startX / 1000.0, -startY / 1000.0, JUMP, 1)

		tableSize = binaryReadByte(file)
		binaryReadByte(file)
		t.color.r = binaryReadByte(file)
		t.color.g = binaryReadByte(file)
		t.color.b = binaryReadByte(file)
		embPattern_addThread(pattern, t)
		fseek(file, 6 * tableSize - 1, SEEK_CUR)

		threadColorNumber = vp3ReadString(file)
		colorName = vp3ReadString(file)
		threadVendor = vp3ReadString(file)

		embFile_readInt_be(file, &offsetToNextColorX, 4)
		embFile_readInt_be(file, &offsetToNextColorY, 4)

		embFile_readInt_be(file, &unknownThreadString, 2)
		fseek(file, unknownThreadString, SEEK_CUR)
		/*
		embFile_readInt_be(file, &numberOfBytesInColor, 4)
		fseek(file, 0x3, SEEK_CUR)
		*/
		fseek(file, 0x7, SEEK_CUR)
		while (ftell(file) < colorSectionOffset - 1) {
			int lastFilePosition = ftell(file)

			int x = vp3Decode(binaryReadByte(file))
			int y = vp3Decode(binaryReadByte(file))
			if (x == 0x80) {
				switch (y) {
				case 0x00:
				case 0x03:
					break
				case 0x01:
					{
					unsigned short sh
					embFile_readInt_be(file, &sh, 2)
					x = vp3DecodeInt16(sh)
					embFile_readInt_be(file, &sh, 2)
					y = vp3DecodeInt16(sh)
					fread(embBuffer, 1, 2, file); /* binaryReadInt16BE(file); */
					embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, TRIM, 1)
					}
					break
				default:
					break
				}
			} else {
				embPattern_addStitchRel(pattern, x / 10.0, y / 10.0, NORMAL, 1)
			}

			if (ftell(file) == lastFilePosition) {
				embLog("ERROR: format-vp3.c could not read stitch block in entirety\n")
				return 0
			}
		}
		if (i + 1 < nColors)
			embPattern_addStitchRel(pattern, 0, 0, STOP, 1)
	}

	embPattern_flipVertical(pattern)

	return 1
	ret


vp3WriteStringLen(int file, const char* str, int len):
	short sh = (short)len
	fwriteInt_be(file, &sh, 2)
	fwrite(str, 1, len, file)
	ret


vp3WriteString(int file, const char* str):
	vp3WriteStringLen(file, str, string_length(str))
	ret


vp3PatchByteCount(int file, int offset, int adjustment):
	int i
	int currentPos = ftell(file)
	fseek(file, offset, SEEK_SET)
	i = currentPos - offset + adjustment
	embLog("Patching byte count: \n" /*, i */)
	fwriteInt_be(file, &i, 4)
	fseek(file, currentPos, SEEK_SET)
	ret


char writeVp3(EmbPattern* pattern, int file, const char* fileName):
	EmbRect bounds
	EmbStitch st
	int remainingBytesPos, remainingBytesPos2, colorSectionStitchBytes,
		first, i, flag, intout
	short nColors
	EmbColor newColor, color = { 0xFE, 0xFE, 0xFE }
	first = 1
	nColors = 0

	bounds = embPattern_calcBoundingBox(pattern)

	embPattern_correctForMaxStitchLength(pattern, 3200.0, 3200.0); /* VP3 can encode signed 16bit deltas */

	embPattern_flipVertical(pattern)

	binaryWriteBytes(file, "%vsm%", 5)
	binaryWriteByte(file, 0)
	vp3WriteString(file, "Embroidermodder")
	binaryWriteByte(file, 0)
	binaryWriteByte(file, 2)
	binaryWriteByte(file, 0)

	remainingBytesPos = ftell(file)
	binaryWriteInt(file, 0); /* placeholder */
	vp3WriteString(file, "")
	intout = bounds.right * 1000
	fwriteInt_be(file, &intout, 4)
	intout = bounds.bottom * 1000
	fwriteInt_be(file, &intout, 4)
	intout = bounds.left * 1000
	fwriteInt_be(file, &intout, 4)
	intout = bounds.top * 1000
	fwriteInt_be(file, &intout, 4)
	binaryWriteInt(file, 0); /* this would be some (unknown) function of thread length */
	binaryWriteByte(file, 0)

	nColors = 0

	for (i = 0; i < pattern->stitchList->length; i++) {
		embArray_get(pattern->stitchList, &st, i)

		/* pointer = mainPointer; */
		flag = st.flags
		EmbThread t
		t = pattern_thread(pattern, st.color)
		newColor = t.color
		if (newColor.r != color.r || newColor.g != color.g || newColor.b != color.b) {
			nColors++
			color = newColor
		} else if (flag & END || flag & STOP) {
			nColors++
		}

		while (flag == st.flags) {
			i++
			embArray_get(pattern->stitchList, &st, i)
		}
		/* mainPointer = pointer; */
	}

	binaryWriteByte(file, nColors)
	fwrite("\x0C\x00\x01\x00\x03\x00", 1, 6, file)

	remainingBytesPos2 = ftell(file)
	embFile_pad(file, 0, 4); /* placeholder */

	embFile_pad(file, 0, 4); /* origin X */
	embFile_pad(file, 0, 4); /* origin Y */
	embFile_pad(file, 0, 3)

	intout = bounds.right * 1000
	fwriteInt_be(file, &intout, 4)
	intout = bounds.bottom * 1000
	fwriteInt_be(file, &intout, 4)
	intout = bounds.left * 1000
	fwriteInt_be(file, &intout, 4)
	intout = bounds.top * 1000
	fwriteInt_be(file, &intout, 4)

	intout = (bounds.right - bounds.left) * 1000
	fwriteInt_be(file, &intout, 4)
	intout = (bounds.bottom - bounds.top) * 1000
	fwriteInt_be(file, &intout, 4); 

	vp3WriteString(file, "")
	short sh = 25700
	fwriteInt_be(file, &sh, 2)
	intout = 4096
	fwriteInt_be(file, &intout, 4)
	embFile_pad(file, 0, 8)
	fwriteInt_be(file, &intout, 4)

	fwrite("xxPP\x01\0", 1, 6, file)
	vp3WriteString(file, "")
	fwriteInt_be(file, &nColors, 2)

	for (i = 0; i < pattern->stitchList->length; i++) {
		char colorName[8] = { 0 }
		float lastX, lastY
		int colorSectionLengthPos
		EmbStitch s, s1
		int lastColor

		if (!first) {
			binaryWriteByte(file, 0)
		}
		binaryWriteByte(file, 0)
		binaryWriteByte(file, 5)
		binaryWriteByte(file, 0)

		colorSectionLengthPos = ftell(file)
		binaryWriteInt(file, 0); /* placeholder */

		/* pointer = mainPointer; */
		EmbThread t
		t = pattern_thread(pattern, st.color)
		color = t.color

		embArray_get(pattern->stitchList, &s1, i)
		if (first && (st.flags & JUMP) && s1.flags & JUMP) {
			i++
		}

		embArray_get(pattern->stitchList, &s, i)
		embLog("format-vp3.c DEBUG %d, %lf, %lf\n" /*, s.flags, s.x, s.y */)
		intout = s.x*1000
		fwriteInt_be(file, &intout, 4)
		intout = -s.y*1000
		fwriteInt_be(file, &intout, 4)
		/* pointer = pointer->next; */

		first = 0

		lastX = s.x
		lastY = s.y
		lastColor = s.color

		binaryWriteByte(file, 1)
		binaryWriteByte(file, 0)

		embLog("format-vp3.c writeVp3(), switching to color (%d, %d, %d)\n" /*, color.r, color.g, color.b */)
		binaryWriteByte(file, color.r)
		binaryWriteByte(file, color.g)
		binaryWriteByte(file, color.b)

		binaryWriteByte(file, 0)
		binaryWriteByte(file, 0)
		binaryWriteByte(file, 0)
		binaryWriteByte(file, 5)
		binaryWriteByte(file, 40)

		vp3WriteString(file, "")
		
		char hex[] = "0123456789ABCDEF"
		colorName[0] = '#'
		colorName[1] = hex[color.b % 16]
		colorName[2] = hex[color.b / 16]
		colorName[3] = hex[color.g % 16]
		colorName[4] = hex[color.g / 16]
		colorName[5] = hex[color.r % 16]
		colorName[6] = hex[color.r / 16]
		colorName[7] = 0

		vp3WriteString(file, colorName)
		vp3WriteString(file, "")

		embFile_pad(file, 0, 8)

		vp3WriteStringLen(file, "\0", 1)

		colorSectionStitchBytes = ftell(file)
		binaryWriteInt(file, 0); /* placeholder */

		binaryWriteByte(file, 10)
		binaryWriteByte(file, 246)
		binaryWriteByte(file, 0)

		for (i = 0; i < pattern->stitchList->length; i++) {
			short dx, dy

			EmbStitch s
			embArray_get(pattern->stitchList, &s, i)

			if (s.color != lastColor) {
				break
			}
			if (s.flags & END || s.flags & STOP) {
				break
			}
			dx = (s.x - lastX) * 10
			dy = (s.y - lastY) * 10
			lastX = lastX + dx / 10.0; /* output is in ints, ensure rounding errors do not sum up */
			lastY = lastY + dy / 10.0

			if (dx < -127 || dx > 127 || dy < -127 || dy > 127) {
				binaryWriteByte(file, 128)
				binaryWriteByte(file, 1)
				fwriteInt_be(file, &dx, 2)
				fwriteInt_be(file, &dy, 2)
				binaryWriteByte(file, 128)
				binaryWriteByte(file, 2)
			} else {
				binaryWriteByte(file, dx)
				binaryWriteByte(file, dy)
			}
		}

		vp3PatchByteCount(file, colorSectionStitchBytes, -4)
		vp3PatchByteCount(file, colorSectionLengthPos, -3)
		/* mainPointer = pointer; */
	}

	vp3PatchByteCount(file, remainingBytesPos2, -4)
	vp3PatchByteCount(file, remainingBytesPos, -4)

	embPattern_flipVertical(pattern)

	return 1
	ret


char xxxDecodeByte(unsigned char inputByte):
	if (inputByte >= 0x80)
		return (char)((-~inputByte) - 1)
	return ((char)inputByte)
	ret


char readXxx(EmbPattern* pattern, int file, const char* fileName):
	unsigned char b[4], b0, b1
	int flags, paletteOffset, i
	short nColors, dx, dy
	char endOfStream = 0, thisStitchJump = 0
	EmbThread thread

	fseek(file, 0x27, SEEK_SET)
	embFile_readInt(file, &nColors, 2)
	fseek(file, 0xFC, SEEK_SET)
	embFile_readInt(file, &paletteOffset, 4)
	fseek(file, paletteOffset + 6, SEEK_SET)

	for (i = 0; i < nColors; i++) {
		fread(b, 1, 4, file)
		thread.color = embColor_fromStr(b)
		embPattern_addThread(pattern, thread)
	}
	fseek(file, 0x100, SEEK_SET)

	dx = 0
	dy = 0
	for (i = 0; !endOfStream && ftell(file) < paletteOffset; i++) {
		flags = NORMAL
		if (thisStitchJump)
			flags = TRIM
		thisStitchJump = 0
		b0 = binaryReadByte(file)
		b1 = binaryReadByte(file)

		if (b0 == 0x7E || b0 == 0x7D) /* TODO: ARE THERE OTHER BIG JUMP CODES? */
		{
			dx = b1 + (binaryReadByte(file) << 8)
			dx = ((short)dx)
			embFile_readInt(file, &dy, 2)
			flags = TRIM
		} else if (b0 == 0x7F) {
			if (b1 != 0x17 && b1 != 0x46 && b1 >= 8) /* TODO: LOOKS LIKE THESE CODES ARE IN THE HEADER */
			{
				b0 = 0
				b1 = 0
				thisStitchJump = 1
				flags = STOP
			} else if (b1 == 1) {
				flags = TRIM
				b0 = binaryReadByte(file)
				b1 = binaryReadByte(file)
			} else {
				continue
			}
			dx = xxxDecodeByte(b0)
			dy = xxxDecodeByte(b1)
		} else {
			dx = xxxDecodeByte(b0)
			dy = xxxDecodeByte(b1)
		}
		embPattern_addStitchRel(pattern, dx / 10.0, dy / 10.0, flags, 1)
	}
	/*
	lastStitch = pattern->stitchList
	secondLast = 0
	if (lastStitch)
 {
		while (lastStitch->next)
		{
			secondLast = lastStitch
			lastStitch = lastStitch->next
		}
		if((!pattern->stitchList) && lastStitch->stitch.flags == STOP && secondLast)
		{
			lastStitch = 0
			secondLast->next = NULL
			embPattern_changeColor(pattern, pattern->currentColorIndex - 1)
		}
	}
	
	Is this trimming the last stitch... and?
	*/

	return 1
	ret


xxxEncodeStop(int file, EmbStitch s):
	binaryWriteByte(file, (unsigned char)0x7F)
	binaryWriteByte(file, (unsigned char)(s.color + 8))
	ret


xxxEncodeStitch(int file, float deltaX, float deltaY, int flags):
	if ((flags & (JUMP | TRIM)) && (emb_fabs(deltaX) > 124 || emb_fabs(deltaY) > 124)) {
		binaryWriteByte(file, 0x7E)
		binaryWriteShort(file, (short)deltaX)
		binaryWriteShort(file, (short)deltaY)
	} else {
		/* TODO: Verify this works after changing this to unsigned char */
		binaryWriteByte(file, (unsigned char)round(deltaX))
		binaryWriteByte(file, (unsigned char)round(deltaY))
	}
	ret


xxxEncodeDesign(int file, EmbPattern* p):
	float thisX = 0.0f
	float thisY = 0.0f
	float previousX, previousY, deltaX, deltaY
	int i

	if (p->stitchList) {
		EmbStitch s
		embArray_get(p->stitchList, &s, 0)
		thisX = s.x
		thisY = s.y
	} else {
		return
	}

	for (i = 0; i < p->stitchList->length; i++) {
		EmbStitch s
		embArray_get(p->stitchList, &s, i)
		previousX = thisX
		previousY = thisY
		thisX = s.x
		thisY = s.y
		deltaX = thisX - previousX
		deltaY = thisY - previousY
		if (s.flags & STOP) {
			xxxEncodeStop(file, s)
		} else if (s.flags & END) {
		} else {
			xxxEncodeStitch(file, deltaX * 10.0f, deltaY * 10.0f, s.flags)
		}
		embArray_set(p->stitchList, &s, i)
	}
	ret


char writeXxx(EmbPattern* pattern, int file, const char* fileName):
	char i
	EmbRect rect
	int endOfStitches
	unsigned char b[4]
	short sh

	embPattern_correctForMaxStitchLength(pattern, 124, 127)

	embFile_pad(file, 0, 0x17)
	binaryWriteUInt(file, (unsigned int)pattern->stitchList->length)
	embFile_pad(file, 0, 0x0C)
	binaryWriteUShort(file, (unsigned short)pattern->threads->length)
	embFile_pad(file, 0, 2)

	rect = embPattern_calcBoundingBox(pattern)
	sh = (short)(embRect_width(rect) * 10.0)
	fwriteInt(file, &sh, 2)
	sh = (short)(embRect_height(rect) * 10.0)
	fwriteInt(file, &sh, 2)

	sh = (short)(embRect_width(rect) / 2.0 * 10)
	fwriteInt(file, &sh, 2); /*TODO: xEnd from start point x=0 */
	sh = (short)(embRect_height(rect) / 2.0 * 10)
	fwriteInt(file, &sh, 2); /*TODO: yEnd from start point y=0 */
	sh = (short)(embRect_width(rect) / 2.0 * 10)
	fwriteInt(file, &sh, 2); /*TODO: left from start x = 0     */
	sh = (short)(embRect_height(rect) / 2.0 * 10)
	fwriteInt(file, &sh, 2); /*TODO: bottom from start y = 0   */
	embFile_pad(file, 0, 0xC5)
	binaryWriteInt(file, 0x0000); /* place holder for end of stitches */

	xxxEncodeDesign(file, pattern)

	endOfStitches = ftell(file)

	fseek(file, 0xFC, SEEK_SET)

	binaryWriteUInt(file, endOfStitches)

	fseek(file, 0, SEEK_END)

	/* Is this really correct? */
	fwrite("\x7F\x7F\x03\x14\x00\x00", 1, 6, file)

	for (i = 0; i < 22; i++) {
		if (i < pattern->threads->length) {
			EmbThread t
			t = pattern_thread(pattern, i)
			b[0] = 0
			embColor_toStr(t.color, b+1)
			fwrite(b, 1, 4, file)
		} else {
			binaryWriteUInt(file, 0x01000000)
		}
	}

	fwrite("\x00\x01", 1, 2, file)
	return 1
	ret


char readZsk(EmbPattern* pattern, int file, const char* fileName):
	unsigned char b[3]
	int stitchType
	unsigned char colorNumber
	EmbThread t

	fseek(file, 0x230, SEEK_SET)
	colorNumber = binaryReadUInt8(file)
	while (colorNumber != 0) {
		fread(b, 1, 3, file)
		t.color = embColor_fromStr(b)
		string_copy(t.catalogNumber, "NULL")
		string_copy(t.description, "NULL")
		embPattern_addThread(pattern, t)
		fseek(file, 0x48, SEEK_CUR)
		fread(&colorNumber, 1, 1, file)
	}
	fseek(file, 0x2E, SEEK_CUR)

	while (fread(b, 1, 3, file) == 3) {
		stitchType = NORMAL
		if (b[0] & 0x4) {
			b[2] = -b[2]
		}
		if (b[0] & 0x8) {
			b[1] = -b[1]
		}
		if (b[0] & 0x02) {
			stitchType = JUMP
		}
		if (b[0] & 0x20) {
			if (b[1] == 2) {
				stitchType = TRIM
			} else if (b[1] == 0x80) {
				break
			} else {
				if (b[2] != 0) {
					colorNumber = b[2]
				}
				stitchType = STOP; /* TODO: need to determine what b[1] is used for.*/
				embPattern_changeColor(pattern, colorNumber - 1)
			}
			b[1] = 0
			b[2] = 0
		}
		embPattern_addStitchRel(pattern, b[1] / 10.0, b[2] / 10.0, stitchType, 0)
	}

	return 1
	ret


char writeZsk(EmbPattern* pattern, int file, const char* fileName):
	return 0; /*TODO: finish writeZsk */
	ret


/* EmbColor (unsigned char *b)
 */
embColor_from_str:
	EmbColor c
	c.r = b[0]
	c.g = b[1]
	c.b = b[2]
	return c
	ret


/* (EmbColor c, unsigned char *b)
 */
embColor_to_str:
	b[0] = c.r
	b[1] = c.g
	b[2] = c.b
	ret
#endif

/*
 * Writes out a color to the int file in hex format without using
 * printf or varadic functions (for embedded systems).
 */
write_svg_color:
	/*(int file, EmbColor color):
	char hex[] = "0123456789ABCDEF"
	embFile_print(file, "stroke=\"#")
	fwrite(hex + (color.r % 16), 1, 1, file)
	fwrite(hex + (color.r / 16), 1, 1, file)
	fwrite(hex + (color.g % 16), 1, 1, file)
	fwrite(hex + (color.g / 16), 1, 1, file)
	fwrite(hex + (color.b % 16), 1, 1, file)
	fwrite(hex + (color.b / 16), 1, 1, file)
	embFile_print(file, "\" ")
	*/
	ret


/* (int file, float x, float y)
 */
write_point:
	/* 
	(file, x)
	call	write_float
	embFile_print(file, ",")
	(file, y)
	call	write_float
	*/
	ret


/* (int file, float number):
 * TODO: fix bugs in embFloatToArray
 */
write_float:
	/*
	char *buffer = (char*)embBuffer
	(buffer, number, 1.0e-7, 3, 5)
	call	emb_float_to_array
	(file, buffer)
	call	embFile_print
	*/
	ret


writeFloatWrap:
	/*
	(int file, char *prefix, float number, char *suffix):
	embFile_print(file, prefix)
	writeFloat(file, number)
	embFile_print(file, suffix)
	*/
	ret


/*
 * (int file, char *attribute, float number)
 */
writeFloatAttribute:
	/*
	(file, attribute)
	call	embFile_print
	writeFloatWrap(file, "=\"", number, "\" ")
	call	write_float_wrap
	*/
	ret

	.data

svg_creator:
	.long	0
svg_expect:
	.long	0

	.text
#if 0
int svgMultiValue
int svgAttributes = 0
int element_set = 0
char currentElementToken
int attributes
int currentValue
char currentElementName[30]
char currentAttribute[30]


EmbColor svgColorToEmbColor(char* colorStr):
	EmbColor c
	char ch, *r, *g, *b
	int i, length, percent, hash, intfunc

	/* Trim out any junk spaces, remove the rgb() function, parentheses and commas.
	 * TODO: create a state variable the replace percent, hash, intfunc, default for color keyword.
	 */
	length = 0
	percent = 0
	hash = 0
	intfunc = 0
	r = colorStr
	g = 0
	b = 0
	if (colorStr[0] == 'r' && colorStr[1] == 'g' && colorStr[2] == 'b') {
		intfunc = 1
		colorStr += 3
	}
	for (i=0; colorStr[i]; i++) {
		ch = colorStr[i]
		if (!hash) {
			if (ch == '(' || ch == ')') continue
		}
		if (ch == ',') {
			/* we have commas, so replace them with zeros and split into r, g, b */
			if (g == 0) {
				g = colorStr + length + 1
			}
			else {
				b = colorStr + length + 1
			}
			ch = 0
		}
		if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') continue
		if (ch == '%') {
			percent = 1
			continue
		}
		if (ch == '#') {
			hash = 1
			continue
		}
		colorStr[length] = ch
		length++
	}
	colorStr[length] = 0

	/* SVGTiny1.2 Spec Section 11.13.1 syntax for color values */
	if (hash) {
		if (length == 3) {
			/* Three digit hex - #rgb */
			/* Convert the 3 digit hex to a six digit hex */
			colorStr[4] = colorStr[2]
			colorStr[5] = colorStr[2]
			colorStr[2] = colorStr[1]
			colorStr[3] = colorStr[1]
			colorStr[1] = colorStr[0]
			colorStr[6] = 0
		}
		c = embColor_fromHexStr(colorStr)
	} else if (percent) {
		/* Float functional - rgb(R%, G%, B%), by now it is stored in r, g and b */
		c.r = (unsigned char)round(255.0 / 100.0 * emb_array_to_float((char*)r))
		c.g = (unsigned char)round(255.0 / 100.0 * emb_array_to_float((char*)g))
		c.b = (unsigned char)round(255.0 / 100.0 * emb_array_to_float((char*)b))
	} else if (intfunc) {
		/* Integer functional - rgb(rrr, ggg, bbb), by now it is stored in r, g and b. */
		c.r = (unsigned char)emb_array_to_int((char*)r)
		c.g = (unsigned char)emb_array_to_int((char*)g)
		c.b = (unsigned char)emb_array_to_int((char*)b)
	} else {
		/* Color keyword */
		int tableColor = threadColor(&c, colorStr, SVG_Colors)
		if (!tableColor) {
			embLog("SVG color string not found:\n")
			embLog(colorStr)
		}
	}

	/* Returns black if all else fails */
	return c
	ret


int svgPathCmdToEmbPathFlag(char cmd):
	/* TODO: This function needs some work */
	/*
	if     (toUpper(cmd) == 'M') return MOVETO
	else if(toUpper(cmd) == 'L') return LINETO
	else if(toUpper(cmd) == 'C') return CUBICTOCONTROL1
	else if(toUpper(cmd) == 'CC') return CUBICTOCONTROL2
	else if(toUpper(cmd) == 'CCC') return CUBICTOEND
	else if(toUpper(cmd) == 'A') return ELLIPSETORAD
	else if(toUpper(cmd) == 'AA') return ELLIPSETOEND
	else if(toUpper(cmd) == 'Q') return QUADTOCONTROL
	else if(toUpper(cmd) == 'QQ') return QUADTOEND
	else if(toUpper(cmd) == 'Z') return LINETO
	*/

	/*else if(toUpper(cmd) == 'B') return BULGETOCONTROL; */ /* NOTE: This is not part of the SVG spec, but hopefully Bulges will be added to the SVG spec someday */
	/*else if(toUpper(cmd) == 'BB') return BULGETOEND; */ /* NOTE: This is not part of the SVG spec, but hopefully Bulges will be added to the SVG spec someday */
	/*else { embLog("ERROR: svgPathCmdToEmbPathFlag(), unknown command '%c'\n", cmd); return MOVETO; } */

	return LINETO
	ret


svgElement_addAttribute(const char* name, const char* value):
	int i
	if (!element_set) {
		embLog("ERROR: svgElement_addAttribute(), no recognised element.")
		return
	}

	fwrite(name, 1, string_length(name), attributes)
	embFile_pad(attributes, 0, 50-string_length(name))

	for (i=0; i<string_length(value); i++) {
		char c = value[i]
		if (c == '"' || c == '\'' || c == '/' || c == ',') continue
		fwrite(&c, 1, 1, attributes)
	}

	embFile_pad(attributes, 0, 950-string_length(value))
	svgAttributes++
	ret


char* svgAttribute_getValue(const char* name):
	if (!element_set) {
		embLog("ERROR: svgAttribute_getValue(), element==0\n")
		return "none"
	}
	if (!name) {
		embLog("ERROR: svgAttribute_getValue(), name==0\n")
		return "none"
	}

	int i
	for (i=0; i<svgAttributes; i++) {
		fread((char*)embBuffer, 1, 1000, attributes)
		if (string_equal((char*)embBuffer, name)) {
			return embBuffer+50
		}
	}
	return 0
	ret


svgAddToPattern(EmbPattern* p):
	EmbPointObject test
	EmbColor color
	EmbPathObject* path

	if (!p) {
		embLog("ERROR: svgAddToPattern(), p==0\n")
		return
	}

	currentElementToken = identify_element(currentElementName)

	switch (currentElementToken) {
	case ELEMENT_CIRCLE:
		{
		float cx, cy, r
		cx = emb_array_to_float(svgAttribute_getValue("cx"))
		cy = emb_array_to_float(svgAttribute_getValue("cy"))
		r = emb_array_to_float(svgAttribute_getValue("r"))
		embPattern_addCircleObjectAbs(p, cx, cy, r, 0, black)
		}
		break
	case ELEMENT_ELLIPSE:
		{
		float cx, cy, rx, ry
		cx = emb_array_to_float(svgAttribute_getValue("cx"))
		cy = emb_array_to_float(svgAttribute_getValue("cy"))
		rx = emb_array_to_float(svgAttribute_getValue("rx"))
		ry = emb_array_to_float(svgAttribute_getValue("ry"))
		embPattern_addEllipseObjectAbs(p, cx, cy, rx, ry, 0.0, 0, black)
		}
		break
	case ELEMENT_LINE:
		{
		char* x1 = svgAttribute_getValue("x1")
		char* y1 = svgAttribute_getValue("y1")
		char* x2 = svgAttribute_getValue("x2")
		char* y2 = svgAttribute_getValue("y2")
		
		float x1_f = emb_array_to_float(x1)
		float y1_f = emb_array_to_float(y1)
		float x2_f = emb_array_to_float(x2)
		float y2_f = emb_array_to_float(y2)

		/* If the starting and ending points are the same, it is a point */
		if (string_equal(x1, x2) && string_equal(y1, y2)) {
			embPattern_addPointObjectAbs(p, x1_f, y1_f, 0, black)
		}
		else {
			embPattern_addLineObjectAbs(p, x1_f, y1_f, x2_f, y2_f, 0, black)
		}
		}
		break
	case ELEMENT_PATH:
		{
		/* TODO: finish */

		char* pointStr = svgAttribute_getValue("d")
		char* mystrok = svgAttribute_getValue("stroke")

		int last = string_length(pointStr)
		int size = 32
		int i = 0
		int pos = 0
		/* An odometer aka 'tripometer' used for stepping thru the pathData */
		int trip = -1; /* count of float[] that has been filled. 0=first item of array, -1=not filled = empty array */
		int reset = -1
		EmbVector position, f, l, c1, c2
		int cmd = 0
		float pathData[7]
		unsigned int numMoves = 0
		int pendingTask = 0
		int relative = 0
		position.x = 0.0
		position.y = 0.0
		f = position
		l = position
		c1 = position
		c2 = position

		EmbArray* pointList = 0
		EmbArray* flagList

		char* pathbuff = (char*)embBuffer
		if (!pathbuff) {
			embLog("ERROR: svgAddToPattern(), cannot allocate memory for pathbuff\n")
			return
		}

		embLog("stroke:")
		embLog(mystrok)

		/* M44.219,26.365c0,10.306-8.354,18.659-18.652,18.659c-10.299,0-18.663-8.354-18.663-18.659c0-10.305,8.354-18.659,18.659-18.659C35.867,7.707,44.219,16.06,44.219,26.365z */
		for (i = 0; i < last; i++) {
			char c = pointStr[i]
			switch (c) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '.':
				pathbuff[pos++] = (char)c; /* add a more char */
				break

			case ' ':
			case ',':

				/*printf("    ,'%s'    ~POS=%d  ~TRIP=%d  ~[pos]=%d\n", pathbuff,pos,trip, pathbuff[pos]);*/
				if (pos > 0) { /* append float to array, if it not yet stored */
					pathbuff[pos] = 0
					pos = 0
					embLog("    ,val:"); 
					embLog(pathbuff)
					pathData[++trip] = emb_array_to_float(pathbuff)
				}
				break

			case '-':

				if (pos > 0) { /* append float to array, if it not yet stored */
					pathbuff[pos] = 0
					pos = 0
					embLog("    -val:"); 
					embLog(pathbuff)
					pathData[++trip] = emb_array_to_float(pathbuff)
				}
				pathbuff[pos++] = (char)c; /* add a more char */
				break

			default:
				/*** ASSUMED ANY COMMAND FOUND ***/

				if (pos > 0) { /* just make sure: append float to array, if it not yet stored */
					pathbuff[pos] = 0
					pos = 0
					embLog("    >val:"); 
					embLog(pathbuff)
					pathData[++trip] = emb_array_to_float(pathbuff)
				}

				/**** Compose Point List ****/

				/* below "while" is for avoid losing last 'z' command that maybe never accommodated. */
				pendingTask = 1
				if (i == last - 1) {
					pendingTask = 2
				}

				while (pendingTask > 0) {
					pendingTask -= 1

					/* Check whether prior command need to be saved */
					if (trip >= 0) {
						trip = -1
						reset = -1

						relative = 0; /* relative to prior coordinate point or absolute coordinate? */

						if (cmd == 'M') {
							position.x = pathData[0]
							position.y = pathData[1]
							f = position
						} else if (cmd == 'm') {
							position.x = pathData[0]
							position.y = pathData[1]
							f = position
							relative = 1
						} else if (cmd == 'L') {
							position.x = pathData[0]
							position.y = pathData[1]
						} else if (cmd == 'l') {
							position.x = pathData[0]
							position.y = pathData[1]
							relative = 1
						} else if (cmd == 'H') {
							position.x = pathData[0]
							position.y = l.y
						} else if (cmd == 'h') {
							position.x = pathData[0]
							position.y = l.y
							relative = 1
						} else if (cmd == 'V') {
							position.x = l.x
							position.y = pathData[1]
						} else if (cmd == 'v') {
							position.x = l.x
							position.y = pathData[1]
							relative = 1
						} else if (cmd == 'C') {
							position.x = pathData[4]
							position.y = pathData[5]
							c1.x = pathData[0]
							c1.y = pathData[1]
							c2.x = pathData[2]
							c2.y = pathData[3]
						} else if (cmd == 'c') {
							position.x = pathData[4]
							position.y = pathData[5]
							c1.x = pathData[0]
							c1.y = pathData[1]
							c2.x = pathData[2]
							c2.y = pathData[3]
							relative = 1
						}
						/*
							else if(cmd == 'S') { position.x = pathData[0]; position.y = pathData[1]; }
							else if(cmd == 's') { position.x = pathData[0]; position.y = pathData[1]; }
							else if(cmd == 'Q') { position.x = pathData[0]; position.y = pathData[1]; }
							else if(cmd == 'q') { position.x = pathData[0]; position.y = pathData[1]; }
							else if(cmd == 'T') { position.x = pathData[0]; position.y = pathData[1]; }
							else if(cmd == 't') { position.x = pathData[0]; position.y = pathData[1]; }
							else if(cmd == 'A') { position.x = pathData[0]; position.y = pathData[1]; }
							else if(cmd == 'a') { position.x = pathData[0]; position.y = pathData[1]; }
							*/
						else if (cmd == 'Z') {
							position = f
						} else if (cmd == 'z') {
							position = f
						}

						if (!pointList && !flagList) {
							pointList = embArray_create(EMB_POINT)
							flagList = embArray_create(EMB_FLAG)
						}
						test.x = position.x
						test.y = position.y
						test.lineType = 0
						test.color = black
						int flag = svgPathCmdToEmbPathFlag(cmd)
						embArray_add(pointList, &test)
						embArray_add(flagList, &flag)
						l = position

						pathbuff[0] = (char)cmd; /* set the command for compare */
						pathbuff[1] = 0
						pos = 0

						/*
						printf("*prior:%s (%f, %f,  %f, %f,     %f,%f,  %f) \n", pathbuff,
							pathData[0],
							pathData[1],
							pathData[2],
							pathData[3],
							pathData[4],
							pathData[5],
							pathData[6]); */
					}

					/* assign new command */
					if (trip == -1 && reset == -1) {
						pathbuff[0] = (char)c; /* set the command for compare */
						pathbuff[1] = 0

						embLog("cmd:")
						embLog(pathbuff)
						cmd = c
						if (c>='A' && c<='Z') {
							c += 'a' - 'A'
						}
						int resetValues[] = {
						  /*a  b  c  d  e  f  g  h  i  j  k  l  m */
							7,-1, 6,-1,-1,-1,-1, 1,-1,-1,-1, 2, 2,
						  /*n  o  p  q  r  s  t  u  v  w  x  y  z */
						   -1,-1,-1, 4,-1, 4, 2,-1, 1,-1,-1,-1, 0
						}
						if (c>='a' && c<='z') {
							reset = resetValues[c-'a']
							if (c=='m') numMoves++
						}
						if (reset < 0) {
							embLog("ERROR: svgAddToPattern(), %s is not a valid svg path command, skipping...")
							embLog(pathbuff)
							trip = -1
							break
						}
					}
					/* avoid losing 'z' command that maybe never accommodated. */
					if (i == last - 1) {
						trip = 2
					}
				} /* while pendingTask */

				break
			}
			if (pos >= size - 1) {
				/* increase pathbuff length - leave room for 0 */
				if (!pathbuff) {
					print_log_string(error_svg_add_realloc)
					return
				}
			}
		}

		/* TODO: subdivide numMoves > 1 */

		color = svgColorToEmbColor(svgAttribute_getValue("stroke"))
		path->pointList = pointList
		path->flagList = flagList
		path->color = color
		path->lineType = 1
		embPattern_addPathObjectAbs(p, path)
		}
		break
	case ELEMENT_POLYGON:
	case ELEMENT_POLYLINE:
	{
		char* pointStr = svgAttribute_getValue("points")
		int last = string_length(pointStr)
		int size = 32
		int i = 0
		int pos = 0
		unsigned char odd = 1
		EmbPointObject a
		a.x = 0.0
		a.y = 0.0

		EmbArray* pointList = 0

		/* if this goes over, switch the embArray_create(EMB_CHAR) */
		char* polybuff = (char*)embBuffer

		for (i = 0; i < last; i++) {
			char c = pointStr[i]
			switch (c) {
			case ' ':
				if (pos == 0)
					break
				polybuff[pos] = 0
				pos = 0
				/*Compose Point List */
				if (odd) {
					odd = 0
					a.x = emb_array_to_float(polybuff)
				} else {
					odd = 1
					a.y = emb_array_to_float(polybuff)

					if (!pointList) {
						pointList = embArray_create(EMB_POINT)
					}
					a.lineType = 0
					a.color = black
					embArray_add(pointList, &a)
				}

				break
			default:
				polybuff[pos++] = (char)c
				if (pos == 1024) {
					embLog("Buffer overflow: polybuff.")
					return
				}
				break
			}
		}

		char *s = svgAttribute_getValue("stroke")
		if (currentElementToken == ELEMENT_POLYGON) {
			EmbPolygonObject polygonObj
			polygonObj.pointList = pointList
			polygonObj.color = svgColorToEmbColor(s)
			polygonObj.lineType = 1; /* TODO: use lineType enum */
			embArray_add(p->polygons, &polygonObj)
		}
		else { /* polyline */
			EmbPolylineObject polylineObj
			polylineObj.pointList = pointList
			polylineObj.color = svgColorToEmbColor(s)
			polylineObj.lineType = 1; /* TODO: use lineType enum */
			embArray_add(p->polylines, &polylineObj)
		}

		}
		break
	case ELEMENT_RECT:
		{
		float x1, y1, width, height
		x1 = emb_array_to_float(svgAttribute_getValue("x"))
		y1 = emb_array_to_float(svgAttribute_getValue("y"))
		width = emb_array_to_float(svgAttribute_getValue("width"))
		height = emb_array_to_float(svgAttribute_getValue("height"))
		embPattern_addRectObjectAbs(p, x1, y1, width, height, 0, black)
		}
		break
	default:
		break
	}
	ret


int svgIsElement(const char* buff):
	if (string_in_table(buff, svg_element_token_table)) {
		return SVG_ELEMENT
	}

	/* Attempt to identify the program that created the SVG file. This should be in a comment at that occurs before the svg element. */
	else if (string_equal(buff, "Embroidermodder")) {
		svgCreator = SVG_CREATOR_EMBROIDERMODDER
	} else if (string_equal(buff, "Illustrator")) {
		svgCreator = SVG_CREATOR_ILLUSTRATOR
	} else if (string_equal(buff, "Inkscape")) {
		svgCreator = SVG_CREATOR_INKSCAPE
	}

	return SVG_NULL
	ret


char svgIsMediaProperty(const char* buff):
	if (string_in_table(buff, svg_media_property_token_table)) {
		return SVG_MEDIA_PROPERTY
	}
	return SVG_NULL
	ret


char svgIsProperty(const char* buff):
	if (string_in_table(buff, svg_property_token_table)) {
		return SVG_PROPERTY
	}
	return SVG_NULL
	ret


char string_in_table(const char *buff, int table):
	int out
	out = dereference_int(table)
	embBuffer[0] = 1
	while (embBuffer[0]) {
		get_str((char *)embBuffer, out)
		if (string_equal((char *)embBuffer, buff)) {
			return 1
		}
		out += 4
	}
	return 0
	ret


char svgIsSvgAttribute(const char* buff):
	if (string_in_table(buff, svg_token_table)) {
		return SVG_ATTRIBUTE
	}

	if (svgCreator == SVG_CREATOR_INKSCAPE) {
		if (string_in_table(buff, inkscape_token_table)) {
			return SVG_ATTRIBUTE
		}
	}

	embLog("svgIsSvgAttribute(), unknown:")
	embLog(buff)
	return SVG_NULL
	ret


int svgIsCatchAllAttribute(const char* buff):
	if (string_in_table(buff, svg_property_token_table)) {
		return SVG_CATCH_ALL
	}
	if (svgCreator == SVG_CREATOR_INKSCAPE) {
		if (string_in_table(buff, svg_attribute_token_table)) {
			return SVG_CATCH_ALL
		}
	}

	return SVG_NULL
	ret


char svgHasAttribute(const char *buff, int out, const char *errormsg):
	if (string_in_table(buff, out)) {
		return SVG_ATTRIBUTE
	}

	embLog("")
	embLog(errormsg)
	embLog("attribute unknown:")
	embLog(buff)

	return SVG_NULL
	ret



char identify_element(char *token):
	int offset
	char id
	for (id=0; id < ELEMENT_UNKNOWN; id++) {
		offset = dereference_int(svg_element_token_table)
		get_str((char*)embBuffer, offset + 4*id)
		if (string_equal(embBuffer, token)) {
			break
		}
	}
	return id
	ret


svgProcess(int c, const char* buff):
	if (svgExpect == SVG_EXPECT_ELEMENT) {
		char advance = 0
		if (buff[0] == '/') {
			return
		}

		advance = (char)svgIsElement(buff)

		if (advance) {
			embLog("ELEMENT:\n")
			svgExpect = SVG_EXPECT_ATTRIBUTE
			element_set = 1
			svgAttributes = 0
			ftruncate(attributes, 0)
			string_copy(currentElementName, buff)
		} else {
			return
		}
	} else if (svgExpect == SVG_EXPECT_ATTRIBUTE) {
		char advance = 0
		if (!element_set) {
			embLog("There is no current element but the parser expects one.")
			return
		}
		currentElementToken = identify_element(currentElementName)
		
		switch (currentElementToken) {
		case ELEMENT_A:
		case ELEMENT_CIRCLE:
		case ELEMENT_DEFS:
		case ELEMENT_ELLIPSE:
		case ELEMENT_FOREIGN_OBJECT:
		case ELEMENT_G:
		case ELEMENT_LINE:
		case ELEMENT_LINEAR_GRADIENT:
		case ELEMENT_PATH:
		case ELEMENT_POLYGON:
		case ELEMENT_POLYLINE:
		case ELEMENT_RADIAL_GRADIENT:
		case ELEMENT_RECT:
		case ELEMENT_SOLID_COLOR:
		case ELEMENT_STOP:
		case ELEMENT_SVG:
		case ELEMENT_SWITCH:
		case ELEMENT_TEXT:
		case ELEMENT_TEXT_AREA:
		case ELEMENT_TSPAN:
		case ELEMENT_USE:
			advance = svgIsProperty(buff)
			break;		
		case ELEMENT_ANIMATION:
		case ELEMENT_AUDIO:
		case ELEMENT_IMAGE:
		case ELEMENT_METADATA:
		case ELEMENT_TITLE:
		case ELEMENT_VIDEO:
			advance = svgIsMediaProperty(buff)
			break
		default:
			break
		}

		if (!advance) {
			if (currentElementToken == ELEMENT_XML) {
				int xmlTokens = double_dereference_int(svg_token_lists, 0)
				advance = svgHasAttribute(buff, xmlTokens, "?xml")
			}
			else if (currentElementToken == ELEMENT_SVG) {
				advance = svgIsSvgAttribute(buff)
			}
			else if (currentElementToken != ELEMENT_UNKNOWN) {
				char element_token[30]
				int out2
				int out = double_dereference_int(svg_token_lists, currentElementToken)
				out2 = dereference_int(svg_element_token_table)
				get_str(element_token, out2+4*currentElementToken)
				
				advance = svgHasAttribute(buff, out, element_token)
			}
		}

		if (advance) {
			embLog("ATTRIBUTE:\n")
			svgExpect = SVG_EXPECT_VALUE
			string_copy(currentAttribute, buff)
		}
	} else if (svgExpect == SVG_EXPECT_VALUE) {
		int last = string_length(buff) - 1
		embLog("VALUE:\n")

		/* single-value */
		if ((buff[0] == '"' || buff[0] == '\'') && (buff[last] == '/' || buff[last] == '"' || buff[last] == '\'') && !svgMultiValue) {
			svgExpect = SVG_EXPECT_ATTRIBUTE
			svgElement_addAttribute(currentAttribute, buff)
		} else /* multi-value */
		{
			svgMultiValue = 1
			if (!currentValue) {
				string_copy(currentValue, buff)
			} else {
				char *buffer = (char*)embBuffer
				int length
				string_copy(buffer, currentValue)
				length = string_length(buff) + string_length(buffer) + 2
				if (!currentValue) {
					embLog("ERROR: svgProcess(), cannot allocate memory for currentValue\n")
					return
				}
				string_copy(currentValue, buffer)
				string_copy(currentValue+string_length(buffer), " ")
				string_copy(currentValue+string_length(buffer)+1, buff)
			}

			if (buff[last] == '/' || buff[last] == '"' || buff[last] == '\'') {
				svgMultiValue = 0
				svgExpect = SVG_EXPECT_ATTRIBUTE
				svgElement_addAttribute(currentAttribute, currentValue)
			}
		}
	}

	if (svgExpect != SVG_EXPECT_NULL) {
		embLog(buff)
	}

	if (c == '>') {
		svgExpect = SVG_EXPECT_NULL
	}
	ret


/*! Reads a file with the given \a fileName and loads the data into \a p.
 *  Returns \c true if successful, otherwise returns \c false. */
char readSvg(EmbPattern* p, int file, const char* fileName):
	int pos
	char c
	char* buff = (char*)embBuffer

	svgCreator = SVG_CREATOR_NULL
	svgExpect = SVG_EXPECT_NULL
	svgMultiValue = 0
	element_set = 0

	/* Pre-flip in case of multiple reads on the same p */
	embPattern_flipVertical(p)

	pos = 0
	while (fread(&c, 1, 1, file)) {
		switch (c) {
		case '<':
			if (svgExpect == SVG_EXPECT_NULL) {
				svgAddToPattern(p)
				svgExpect = SVG_EXPECT_ELEMENT
			}
		case '>':
			if (pos == 0) { /* abnormal case that may occur in svg element where '>' is all by itself */
				/*TODO: log a warning about this absurdity! */
				svgExpect = SVG_EXPECT_ELEMENT
				break
			}
		case ' ':
		case '\t':
		case '\r':
		case '\n':
		case '=':
			if (pos == 0)
				break
			buff[pos] = 0
			pos = 0
			svgProcess(c, buff)
			break
		default:
			buff[pos++] = (char)c
			break
		}
		if (pos >= 1024) {
			embLog("ERROR: readSvg(), buffer overflow.")
			return 0
		}
	}

	/* Flip the p since SVG Y+ is down and libembroidery Y+ is up. */
	embPattern_flipVertical(p)

	return 1; /*TODO: finish readSvg */
	ret


writeCircles(int file, EmbArray* a, int i):
	EmbCircle circle
	embArray_get(a, &circle, i)
	/* TODO: use proper thread width for stoke-width rather than just 0.2 */
	embFile_print(file, "\n<circle stroke-width=\"0.2\" fill=\"none\" ")
	write_svg_color(file, circle.color)
	writeFloatAttribute(file, "cx", circle.center.x)
	writeFloatAttribute(file, "cy", circle.center.y)
	writeFloatAttribute(file, "r", circle.radius)
	embFile_print(file, "/>")
	ret


writeEllipses(int file, EmbArray* a, int i):
	EmbEllipse ellipse
	embArray_get(a, &ellipse, i)
	/* TODO: use proper thread width for stoke-width rather than just 0.2 */
	embFile_print(file, "\n<ellipse stroke-width=\"0.2\" fill=\"none\" ")
	write_svg_color(file, ellipse.color)
	writeFloatAttribute(file, "cx", ellipse.center.x)
	writeFloatAttribute(file, "cy", ellipse.center.y)
	writeFloatAttribute(file, "rx", ellipse.radius.x)
	writeFloatAttribute(file, "ry", ellipse.radius.y)
	embFile_print(file, "/>")
	ret


writeLines(int file, EmbArray* a, int i):
	EmbLine line
	embArray_get(a, &line, i)
	/* TODO: use proper thread width for stoke-width rather than just 0.2 */
	embFile_print(file, "\n<line stroke-width=\"0.2\" fill=\"none\" ")
	write_svg_color(file, line.color)
	writeFloatAttribute(file, "x1", line.start.x)
	writeFloatAttribute(file, "y1", line.start.y)
	writeFloatAttribute(file, "x2", line.end.x)
	writeFloatAttribute(file, "y2", line.end.y)
	embFile_print(file, " />")
	ret


writePoints(int file, EmbArray* a, int i):
	EmbPointObject point
	embArray_get(a, &point, i)
	/* See SVG Tiny 1.2 Spec:
	 * Section 9.5 The 'line' element
	 * Section C.6 'path' element implementation notes */
	/* TODO: use proper thread width for stoke-width rather than just 0.2 */
	embFile_print(file, "\n<line stroke-linecap=\"round\" stroke-width=\"0.2\" fill=\"none\" ")
	write_svg_color(file, point.color)
	writeFloatAttribute(file, "x1", point.x)
	writeFloatAttribute(file, "y1", point.y)
	writeFloatAttribute(file, "x2", point.x)
	writeFloatAttribute(file, "y2", point.y)
	embFile_print(file, " />")
	ret


writePolygons(int file, EmbArray* a, int i):
	int j
	EmbPolygonObject polygon
	EmbVector v
	embArray_get(a, &polygon, i)
	/* TODO: use proper thread width for stoke-width rather than just 0.2 */
	embFile_print(file, "\n<polygon stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" fill=\"none\" ")
	write_svg_color(file, polygon.color)
	embFile_print(file, "points=\"")
	embArray_get(polygon.pointList, &v, 0)
	writePoint(file, v.x, v.y)
	for (j = 1; j < polygon.pointList->length; j++) {
		embArray_get(polygon.pointList, &v, j)
		fwrite(" ", 1, 1, file)
		writePoint(file, v.x, v.y)
	}
	embFile_print(file, "\" />")
	ret


writePolylines(int file, EmbArray* a, int i):
	int j
	EmbPolylineObject polyline
	EmbVector v
	embArray_get(a, &polyline, i)
	/* TODO: use proper thread width for stoke-width rather than just 0.2 */
	embFile_print(file, "\n<polyline stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" ")
	write_svg_color(file, polyline.color)
	embFile_print(file, "fill=\"none\" points=\"")
	embArray_get(polyline.pointList, &v, 0)
	writePoint(file, v.x, v.y)
	for (j = 1; j < polyline.pointList->length; j++) {
		embArray_get(polyline.pointList, &v, j)
		fwrite(" ", 1, 1, file)
		writePoint(file, v.x, v.y)
	}
	embFile_print(file, "\" />")
	ret
#endif


/*
 * (int file, EmbArray* p, int i)
 */
writeRects:
#if 0
	EmbRect rect
	embArray_get(p, &rect, i)
	/* TODO: use proper thread width for stoke-width rather than just 0.2 */
	embFile_print(file, "\n<rect stroke-width=\"0.2\" fill=\"none\" ")
	write_svg_color(file, rect.color)
	writeFloatAttribute(file, "x", embRect_x(rect))
	writeFloatAttribute(file, "y", embRect_y(rect))
	writeFloatAttribute(file, "width", embRect_width(rect))
	writeFloatAttribute(file, "height", embRect_height(rect))
	embFile_print(file, " />")
#endif
	ret


writeSvg:
#if 0
char writeSvg(EmbPattern* p, int file, const char* fileName):
	int i
	EmbRect boundingRect

	/* Pre-flip the p since SVG Y+ is down and libembroidery Y+ is up. */
	embPattern_flipVertical(p)

	boundingRect = embPattern_calcBoundingBox(p)
	embFile_print(file,
		"<?xml version=\"1.0\"?>\n" \
		"<!-- Embroidermodder 2 SVG Embroidery File -->\n" \
		"<!-- http://embroidermodder.github.io -->\n" \
		"<svg viewBox=\"")

	/* TODO: See the SVG Tiny Version 1.2 Specification Section 7.14.
	 *       Until all of the formats and API is stable, the width, height and viewBox attributes need to be left unspecified.
	 *       If the attribute values are incorrect, some applications wont open it at all.
	 */
	writeFloatWrap(file, "", boundingRect.left, " ")
	writeFloatWrap(file, "", boundingRect.top, " ")
	writeFloatWrap(file, "", embRect_width(boundingRect), " ")
	writeFloatWrap(file, "", embRect_height(boundingRect),
		"\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.2\" baseProfile=\"tiny\">")

	/*TODO: Low Priority: Indent output properly. */

	for (i = 0; i < p->circles->length; i++) {
		writeCircles(file, p->circles, i)
	}
	for (i = 0; i < p->ellipses->length; i++) {
		writeEllipses(file, p->ellipses, i)
	}
	for (i = 0; i < p->lines->length; i++) {
		writeLines(file, p->lines, i)
	}
	for (i = 0; i < p->points->length; i++) {
		writePoints(file, p->points, i)
	}
	for (i = 0; i < p->polygons->length; i++) {
		writePolygons(file, p->polygons, i)
	}
	for (i = 0; i < p->polylines->length; i++) {
		writePolylines(file, p->polylines, i)
	}
	for (i = 0; i < p->rects->length; i++) {
		writeRects(file, p->rects, i)
	}
	int isNormal = 0
	for (i = 0; i < p->stitchList->length; i++) {
		/*TODO: Low Priority Optimization:
		 *      Make sure that the line length that is output doesn't exceed 1000 characters. */
		EmbStitch st
		/*TODO: #ifdef SVG_DEBUG for Josh which outputs JUMPS/TRIMS instead of chopping them out */
		embArray_get(p->stitchList, &st, i)
		if (st.flags == NORMAL && !isNormal) {
			EmbThread t
			isNormal = 1
			t = pattern_thread(p, st.color)
			/* TODO: use proper thread width for stoke-width rather than just 0.2 */
			embFile_print(file, "\n<polyline stroke-linejoin=\"round\" stroke-linecap=\"round\" stroke-width=\"0.2\" ")
			write_svg_color(file, t.color)
			embFile_print(file, "fill=\"none\" points=\"")
			writePoint(file, st.x, st.y)
		} else if (st.flags == NORMAL && isNormal) {
			fwrite(" ", 1, 1, file)
			writePoint(file, st.x, st.y)
		} else if (st.flags != NORMAL && isNormal) {
			isNormal = 0
			embFile_print(file, "\"/>")
		}
	}

	embFile_print(file, "\n</svg>\n")

	/* Reset the p so future writes(regardless of format) are not flipped */
	embPattern_flipVertical(p)

	return 1
#endif
	ret


/* int (EmbColor a, EmbColor b) */
embColor_distance:
	/*
	int d
	d = (a.r - b.r) * (a.r - b.r)
	d += (a.g - b.g) * (a.g - b.g)
	d += (a.b - b.b) * (a.b - b.b)
	return d
	*/
	ret


/* int embThread_findNearestColor(EmbColor color, int thread_table)
 * returns index
 */
embThread_findNearestColor:
	/*
	int currentClosestValue, closestIndex, i, length

	currentClosestValue = 256 * 256 * 3
	closestIndex = -1
	length = double_dereference_int(table_lengths, thread_table)

	for (i = 0; i < length; i++) {
		int delta
		EmbThread t
		t = load_thread(thread_table, i)
		delta = embColor_distance(color, t.color)
		call	embColor_distance

		if (delta <= currentClosestValue) {
			currentClosestValue = delta
			closestIndex = i
		}
	}
	return closestIndex
	*/
	ret


/**
 * Returns a random thread color, useful in filling in cases where the
 * actual color of the thread doesn't matter but one needs to be declared
 * to test or render a pattern.
 *
 * returns c The resulting color.
 */
	.data
embThread_random:
	.byte	0, 0, 0, 0
	.ascii	"random........................"
	.ascii	"NULL......"

	.text
embThread_getRandom:
	call	random_int
	mov	%al, (embThread_random+1)
	call	random_int
	mov	%al, (embThread_random+2)
	call	random_int
	mov	%al, (embThread_random+3)
	ret


/*
 * int embColor_equal(EmbColor a, EmbColor b)
 * returns result on %al
 */
	.data
embColor_equal_args:
	.byte	0, 0, 0, 0, 0, 0

	.text
embColor_equal:
	mov	(embColor_equal_args+3), %al
	cmp	(embColor_equal_args), %al
	jne	embColor_equal_mismatch
	mov	(embColor_equal_args+4), %al
	cmp	(embColor_equal_args+1), %al
	jne	embColor_equal_mismatch
	mov	(embColor_equal_args+5), %al
	cmp	(embColor_equal_args+2), %al
	jne	embColor_equal_mismatch

	mov	$1, %al
	ret

embColor_equal_mismatch:
	mov	$0, %al
	ret


/*
thread_color_loop_num:
	.long	0
int thread_color(EmbColor *c, const char* name, int brand):
	int length, i
	length = double_dereference_int(table_lengths, brand)
	*c = black
*/


thread_color_loop:
	/*
	for (i=0; i<length; i++) {
	EmbThread t = load_thread(brand, i)
	if (string_equal(t.description, name)) {
	call	string_equal
	cmp	strings_are_equal, $0
	jlt	thread_color_condition
	cmp	
	jlt	thread_color_loop

	movl	$0, (error_code)
	*/
	ret

thread_color_condition:
	/*
	movl	t.color, *c
	movl	$1, (error_code)
	*/
	ret


/*
 * (EmbColor color, int brand)
 * returns int error_code
 */
thread_color_num:
	/* int length, i*/
	/* length = double_dereference_int(table_lengths, brand)*/

	/*for (i=0; i<length; i++) {*/
	/*	EmbThread t = load_thread(brand, i)*/
	/*	if (embColor_equal(t.color, color)) {*/
			/* return t.catalogNumber; */
	/*		return 0*/
	/*	}*/
	/*}*/

	/*return -1*/
	ret


/*
 * (char *result, EmbColor color, int brand)
 * returns int error_code
 */
thread_color_name:
	/*int length, i*/
	/*length = double_dereference_int(table_lengths, brand)*/

	/*for (i=0; i<length; i++) {*/
	/*	EmbThread t = load_thread(brand, i)*/
	/*	if (embColor_equal(t.color, color)) {*/
	/*		string_copy(result, t.description)*/
	/*call	string_copy*/
	/*		return*/
	/*	}*/
	/*}*/

	/* (result, "COLOR NOT FOUND") */
	call	string_copy
	ret


	.data
datafile:
	.long	0
datafile_name:
	.string	"libembroidery_data.bin"
datafile_mode:
	.long	0 /* "rb" */

	.text
/* For now we are assuming that there is only one pattern loaded at a time.
 * Therefore the arrays shifted to the file "libembroidery_memory.bin" can
 * be assumed to be for this active pattern pattern.
 *
 * (void)
 * returns error_code
 */
init_embroidery:
	movl	(datafile_mode), %ecx
	movl	datafile_name, %ebx
	movl	$SYS_OPEN, %eax
	int	$0x80
	ret


/*
 * (void)
 * returns int error_code
 */
close_embroidery:
	movl	(datafile), %ebx
	movl	$SYS_CLOSE, %eax
	int	$0x80
	ret


