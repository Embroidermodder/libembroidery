/*
 * EmbroiderBot
 * Copyright 2021-2022 The Embroidermodder Team
 * Distributed under the terms of the zlib license (see LICENSE).
 */

#include "embroidery_embedded.h"

int file_pointer = 0;
int buffer_length = 0;
unsigned char black[] = {0, 0, 0};
int memory[100];
/*
EmbArray arrays[100];
EmbPattern patterns[3];
*/
int memory_files = 0;
int active_patterns = 0;

void reverse_byte_order(void *data, int bytes)
{
  char *a = (char*)data;
  if (bytes==2) {
    char c = a[0];
    a[0] = a[1];
    a[1] = c;
  }
  else {
    char c = a[0];
    a[0] = a[3];
    a[3] = c;
    c = a[1];
    a[1] = a[2];
    a[2] = c;
  }
}

#if 0
length:
  .long  1
dot:
  .ascii  "."

buffer:
  .long  0


.globl _start
_start:
  pushl  %ebp
  movl  $welcome_message_len, %edx
  movl  $welcome_message, %ecx
  movl  $STDOUT, %ebx
  call  write

  movl  $STDOUT, %ebx
  movl  $20, (length)
  call  file_pad_spaces

  movl  $0, %ebx
  movl  $SYS_EXIT, %eax
  int  $0x80
  leave
}

/*
 * syscall(SYS_WRITE, f, &b, n)
 */
write:
  movl  $SYS_WRITE, %eax
  int  $0x80
}

/*
 * syscall(SYS_WRITE, f, &b, 4)
 */
binary_write_int:
  movl  $4, (buffer_length)
  call  write
}

/*
 * syscall(SYS_WRITE, f, &b, 2)
 */
binary_write_short:
  movl  $2, (buffer_length)
  call  write
}

  .set  binary_write_float, binary_write_int
  .set  binary_write_uint, binary_write_int
  .set  binary_write_ushort, binary_write_short

/*
 * syscall(SYS_READ, f, &b, 1)
 */
/* (int f) returns b */
/* char b
 * fread(&b, 1, 1, f)
 * return b */
binary_read_byte:
}

/*
 * syscall(SYS_READ, f, &b, 1)
 */
binary_read_bytes:
  /* (int f, char *s, int n) returns char */
  /* fread(s, 1, n, f) */
}

  .set  binary_read_uint8, binary_read_byte

binary_read_float:
  /* (int f) returns float fl */
  /* float fl
  fread(&fl, 4, 1, f)
  return fl */
}

bit:
  /* (unsigned char a, int n) returns int */
  /* return ((a & (1 << n)) / (1 << n)) */
}

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
}

/* (int p) returns int */
dereference_int:
  /*
  int out
  fseek(datafile, p, SEEK_SET)
  fread(&out, 4, 1, datafile)
  return out
  */
}

/* int table, int entry returns int */
double_dereference_int:
  /*
  int out
  out = dereference_int(table)
  out = dereference_int(out+4*entry)
  return out
  */
}

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
}
#endif

#define MAX_STRING_LENGTH 100

/*
int
get_str(char *s, int p)
{
  int i;
  fseek(datafile, p, SEEK_SET);
  for (i=0; i<MAX_STRING_LENGTH; i++) {
    fread(s+i, 1, 1, datafile);
    if (!s[i]) {
      return 1;
    }
  }
  return 0;
}
*/

int
string_length(const char *a)
{
  int i;
  for (i=0; i<MAX_STRING_LENGTH; i++) {
    if (((char*)a)[i] == 0) {
      return i;
    }
  }
  return MAX_STRING_LENGTH;
}

int
string_equal(const void *a, const void *b)
{
  int i;
  for (i=0; i< MAX_STRING_LENGTH; i++) {
    if (((char*)a)[i] != ((char*)b)[i]) {
      return 0;
    }
    if (!((char*)a)[i]) {
      break;
    }
  }
  if (!((char*)b)[i] && i < MAX_STRING_LENGTH) {
    return 1;
  }
  return 0;
}

void
memory_copy(void *a, const void *b, int length)
{
  int i;
  length = EMB_MIN(length, MAX_STRING_LENGTH);
  for (i=0; i<length; i++) {
    ((char *)a)[i] = ((const char *)b)[i];
  }
}

void
string_copy(char *a, const char *b)
{
  memory_copy(a, b, string_length(b));
  ((char *)a)[string_length(b)] = 0;
}

#if 0
/* TODO: find and analyse some HUS encoded files and DST equivalents
 *
 * (int input, int output, int compressionType) return int
 */
void
husExpand(char *input)
{
    
}

/* TODO: find and analyse some HUS encoded files and DST equivalents
 *
 * (int input, int output, int compressionType) returns int
 */
void
husCompress:
}

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
}

/* (float src) return int */
emb_ceil:
  return (int)(src)+1
}

/* (float src) return int */
emb_floor:
  return (int)(src)
}

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
}

embTime_initNow(EmbTime* t)
{
/*TODO: arduino embTime_initNow */
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
}

EmbTime embTime_time(EmbTime* t)
{
/*TODO: arduino embTime_time */

  int divideByZero = 0
  divideByZero = divideByZero / divideByZero
  /*TODO: wrap time() from time.h and verify it works consistently */
  return *t
}
#endif

/* Converts a 6 digit hex string (I.E. "00FF00") into an
 * EmbColor and returns it. */
EmbColor embColor_fromHexStr(char* val)
{
  int i;
  EmbColor color;
  for (i = 0; i < 6; i++) {
    if (val[i] >= 'A' && val[i] <= 'F') {
      val[i] = '9' + val[i] - 'A' + 1;
    }
    val[i] -= '0';
  }

  color.r = val[0] * 16 + val[1];
  color.g = val[2] * 16 + val[3];
  color.b = val[4] * 16 + val[5];
  return color;
}

#if 0
int emb_array_to_int(char* buffer)
{
  int result
  result = 0
  for (; *buffer; buffer++) {
    if (*buffer >= '0' && *buffer <= '9') {
      result = 10*result + *buffer - '0'
    }
  }
  return result
}

float emb_array_to_float(char* buffer)
{
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
}

/* Replacing the %d in *printf functionality.
 *
 * Accounts for the sign of the 
 */
emb_int_to_array(char* buffer, int number, int maxDigits)
{
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
}

writeInt(int file, int n, int m)
{
  char buffer[30]
  emb_int_to_array(buffer, n, m)
  embFile_print(file, buffer)
}

/* Replacing the %f in *printf functionality.
 */
emb_float_to_array(char* buffer, float number, float tolerance, int before, int after)
{
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
}

/* puts() abstraction. Uses Serial.print() on ARDUINO */
embLog:
  /* (const char* str) */
  write(1, str, string_length(str))
  write(1, "\n", 1)
}

embConstantPi:
  3.1415926535

radians:
  /* (float degree) returns float */
  return degree * embConstantPi / 180.0
}

degrees:
  /* (float radian) returns float */
  return radian * 180.0 / embConstantPi
}

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
}

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
}

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
}

/****************************************************************
 * Calculates the tangent points on circle from a given point.
 * Returns true if the given point lies outside the circle.
 * Returns false if the given point is inside the circle.
 ****************************************************************/
int getCircleTangentPoints(EmbCircle c, EmbVector point, EmbVector* t0, EmbVector* t1)
{
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
}

embEllipse_diameterX:
  /* (EmbEllipse ellipse) returns float */
  return ellipse.radius.x * 2.0
}

/* (EmbEllipse ellipse) returns float
 */
embEllipse_diameterY:
  return ellipse.radius.y * 2.0
}

/*
 * takes EmbEllipse, returns float width
 *
 * (EmbEllipse ellipse) returns float
 */
embEllipse_width:
  return ellipse.radius.x * 2.0
}

embEllipse_height:
  /* (EmbEllipse ellipse) returns float */
  return ellipse.radius.y * 2.0
}

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
}

/*
 * Finds the normalized vector perpendicular (clockwise) to the line
 * given by v1->v2 (normal to the line).
 */
void
embLine_normalVector(EmbLine line, EmbVector* result, int clockwise)
  if (!result) {
    print_log_string(error_vector_normal);
    return;
  }
  embVector_subtract(line.end, line.end, result);
  embVector_normalVector(*result, result, clockwise);
}

/**
 * Finds the intersection of two lines given by v1->v2 and v3->v4
 * and sets the value in the result variable.
 */
unsigned char embLine_intersectionPoint(EmbLine line1, EmbLine line2, EmbVector* result)
{
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
}

/* (EmbRect rect) returns float */
embRect_x:
  return rect.left
}

/* (EmbRect rect) returns float */
embRect_y:
  return rect.top
}

/* (EmbRect rect) returns float */
embRect_width:
  return rect.right - rect.left
}

/* (EmbRect rect) returns float */
embRect_height:
  return rect.bottom - rect.top
}

/* Sets the left edge of the rect to x.
 * The right edge is not modified.
 *
 * (EmbRect* rect, float x)
 */
embRect_setX:
  rect->left = x
}

/* Sets the top edge of the rect to y.
 * The bottom edge is not modified.
 *
 * (EmbRect* rect, float y)
 */
embRect_setY:
  rect->top = y
}

/* Sets the width of the rect to w.
 * The right edge is modified. The left edge is not modified.
 *
 * (EmbRect* rect, float w)
 */
embRect_setWidth:
  rect->right = rect->left + w
}

/* Sets the height of the rect to h.
 * The bottom edge is modified. The top edge is not modified.
 *
 * (EmbRect* rect, float h)
 */
embRect_setHeight:
  rect->bottom = rect->top + h
}

/* (EmbRect* rect, float x1, float y1, float x2, float y2)
 */
embRect_setCoords:
  rect->left = x1
  rect->top = y1
  rect->right = x2
  rect->bottom = y2
}

embRect_setRect(EmbRect* rect, float x, float y, float w, float h)
{
  rect->left = x
  rect->top = y
  rect->right = x + w
  rect->bottom = y + h
}

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
}

int
embArray_add(EmbArray *p, void *data)
{
  fseek(memory[p->file_id], p->length*p->size, SEEK_SET);
  fwrite(data, p->size, 1, memory[p->file_id]);
  p->length++
  return 1;   
}

int
embArray_get(EmbArray *p, void *data, int i)
{
  fseek(memory[p->file_id], i*p->size, SEEK_SET);
  fread(data, p->size, 1, memory[p->file_id]);
  return 1;
}

int
embArray_set(EmbArray *p, void *data, int i)
{
  fseek(memory[p->file_id], i*p->size, SEEK_SET);
  fwrite(data, p->size, 1, memory[p->file_id]);
  return 1;
}

int
embArray_read(int file, EmbArray *a, int offset, int n)
{
  int i;
  void *data = (void*)embBuffer;
  fseek(file, offset, SEEK_SET);
  for (i=0; i<n; i++) {
    fread(data, a->size, 1, file);
    embArray_set(a, data, i);
  }
}

int
embArray_write(int file, EmbArray *a, int offset, int n)
{
  int i;
  void *data = (void*)embBuffer;
  fseek(file, offset, SEEK_SET);
  for (i=0; i<n; i++) {
    embArray_get(a, data, i);
    fwrite(data, a->size, 1, file);
  }
}

/* delete file, will be automatic for TMPFILE
 * Expects pointer to EmbArray on eax.
 */
void
embArray_free(void)
{
  fclose(memory[p->file_id]);
}

/* Returns a pointer to an EmbPattern. It is created on the heap.
 * The caller is responsible for freeing the allocated memory with
 * embPattern_free(). */
EmbPattern* embPattern_create(void)
{
  EmbPattern* p
  p = patterns+active_patterns
  active_patterns++
  if (!p) {
    embLog("Ran out of memory for active patterns.")
    return 0
  }

  strcpy(p->name, "Untitled")
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
}

embPattern_hideStitchesOverLength(EmbPattern* p, int length)
{
  float prevX, prevY
  int i
  EmbStitch st

  if (!p) {
    print_log_string(error_hide_stitches_no_pattern)
    return;
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
}

int embPattern_addThread(EmbPattern* p, EmbThread thread)
{
  embArray_add(p->threads, &thread)
  return 1
}

embPattern_fixColorCount(EmbPattern* p)
{
  /* fix color count to be max of color index. */
  int maxColorIndex = 0, i

  if (!p) {
    print_log_string(error_fix_color_count_no_pattern)
    return;
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
}

/* Copies all of the EmbStitchList data to EmbPolylineObjectList data for pattern (\a p). */
embPattern_copyStitchListToPolylines(EmbPattern* p)
{
  EmbPointObject point
  int breakAtFlags, i
  EmbStitch st

  if (!p) {
    print_log_string(error_copy_stitch_list_no_pattern)
    return;
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
}

/* Copies all of the EmbPolylineObjectList data to EmbStitchList data for pattern (\a p). */
embPattern_copyPolylinesToStitchList(EmbPattern* p)
{
  int firstObject = 1, i, j
  /*int currentColor = polyList->polylineObj->color TODO: polyline color */

  if (!p) {
    embLog("ERROR: embPattern_copyPolylinesToStitchList(), p==0\n")
    return;
  }
  if (!p->polylines) {
    embLog("ERROR: embPattern_copyPolylinesToStitchList(), p==0\n")
    return;
  }
  for (i = 0; i < p->polylines->length; i++) {
    EmbPolylineObject currentPoly
    EmbArray* currentPointList
    EmbThread thread

    embArray_get(p->polylines, &currentPoly, i)
    currentPointList = currentPoly.pointList
    if (!currentPointList) {
      embLog("ERROR: embPattern_copyPolylinesToStitchList(), currentPointList is null\n")
      return;
    }

    strcpy(thread.catalogNumber, "NULL")
    thread.color = currentPoly.color
    strcpy(thread.description, "NULL")
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
}

/* Moves all of the EmbStitchList data to EmbPolylineObjectList data for pattern (\a p). */
embPattern_moveStitchListToPolylines(EmbPattern* p)
{
  if (!p) {
    embLog("ERROR: embPattern_moveStitchListToPolylines(), p==0\n")
    return;
  }
  embPattern_copyStitchListToPolylines(p)
  /* Free the stitchList and threadList since their data has now been transferred to polylines */
  embArray_free(p->stitchList)
}

/* Moves all of the EmbPolylineObjectList data to EmbStitchList data for pattern (\a p). */
embPattern_movePolylinesToStitchList(EmbPattern* p)
{
  if (!p) {
    embLog("ERROR: embPattern_movePolylinesToStitchList(), p==0\n")
    return;
  }
  embPattern_copyPolylinesToStitchList(p)
  embArray_free(p->polylines)
}

/* Adds a stitch to the pattern (\a p) at the absolute position (\a x,\a y). Positive y is up. Units are in millimeters. */
embPattern_addStitchAbs(EmbPattern* p, float x, float y, int flags, int isAutoColorIndex)
{
  EmbStitch s

  if (!p || !p->stitchList) {
    embLog("ERROR: embPattern_addStitchAbs(), p==0\n")
    return;
  }

  if (flags & END) {
    if (p->stitchList->length == 0) {
      return;
    }
    /* Prevent unnecessary multiple END stitches */
    embArray_get(p->stitchList, &s, p->stitchList->length - 1)
    if (s.flags & END) {
      embLog("ERROR: embPattern_addStitchAbs(), found multiple END stitches\n")
      return;
    }

    embPattern_fixColorCount(p)

    /* HideStitchesOverLength(127); TODO: fix or remove this */
  }

  if (flags & STOP) {
    if (p->stitchList->length == 0) {
      return;
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
}

/* Adds a stitch to the pattern (\a p) at the relative position
 * (\a dx,\a dy) to the previous stitch. Positive y is up.
 * Units are in millimeters.
 */
embPattern_addStitchRel(EmbPattern* p, float dx, float dy, int flags, int isAutoColorIndex)
{
  EmbVector home
  float x, y

  if (!p) {
    embLog("ERROR: embPattern_addStitchRel(), p==0\n")
    return;
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
}

embPattern_changeColor(EmbPattern* p, int index)
{
  if (!p) {
    embLog("ERROR: embPattern_changeColor(), p==0\n")
    return;
  }
  p->currentColorIndex = index
}

/* Reads a file with the given \a fileName and loads the data into \a pattern.
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
}

/* Writes the data from \a pattern to a file with the given \a fileName.
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
}

/* Very simple scaling of the x and y axis for every point.
* Doesn't insert or delete stitches to preserve density. */
void embPattern_scale(EmbPattern* p, float scale)
{
  int i;

  if (!p) {
    embLog("ERROR: embPattern_scale(), p==0\n")
    return;
  }

  for (i = 0; i < p->stitchList->length; i++) {
    EmbStitch st
    embArray_get(p->stitchList, &st, i)
    st.x *= scale
    st.y *= scale
    embArray_set(p->stitchList, &st, i)
  }
}

/* Returns an EmbRect that encapsulates all stitches and objects in the pattern (\a p). */
EmbRect embPattern_calcBoundingBox(EmbPattern* p)
{
  EmbRect boundingRect;
  EmbStitch pt;
  EmbBezier bezier;
  int i, j;

  boundingRect.left = 0;
  boundingRect.right = 0;
  boundingRect.top = 0;
  boundingRect.bottom = 0;

  if (!p || !p->stitchList) {
    embLog("ERROR: embPattern_calcBoundingBox(), p==0\n")
    return boundingRect;
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
}
#endif

/* Flips the entire pattern (\a p) horizontally about the x-axis if (\a horz) is true.
 *  Flips the entire pattern (\a p) vertically about the y-axis if (\a vert) is true. */
int
embPattern_flip(EmbPattern* p, int horz, int vert)
{
  int i, j;
  EmbVector flip;

  if (!p) {
    embLog("ERROR: embPattern_flip(), p==0\n");
    return 0;
  }

  flip.x = 1.0;
  flip.y = 1.0;
  if (horz) {
    flip.x = -1.0;
  }
  if (vert) {
    flip.y = -1.0;
  }

  for (i = 0; i < p->stitchList->length; i++) {
    EmbStitch st;
    embArray_get(p->stitchList, &st, i);
    st.x *= flip.x;
    st.y *= flip.y;
    embArray_get(p->stitchList, &st, i);
  }

  for (i = 0; i < p->arcs->length; i++) {
    EmbArc arc;
    embArray_get(p->arcs, &arc, i);
    embVector_component_product(arc.start, arc.start, flip);
    embVector_component_product(arc.mid, arc.mid, flip);
    embVector_component_product(arc.end, arc.end, flip);
    embArray_set(p->arcs, &arc, i);
  }

  for (i = 0; i < p->circles->length; i++) {
    EmbCircle circle;
    embArray_get(p->circles, &circle, i);
    embVector_component_product(circle.center, circle.center, flip);
    embArray_set(p->circles, &circle, i);
  }

  for (i = 0; i < p->ellipses->length; i++) {
    EmbEllipse ellipse;
    embArray_get(p->ellipses, &ellipse, i);
    embVector_component_product(ellipse.center, ellipse.center, flip);
    embArray_set(p->ellipses, &ellipse, i);
  }

  for (i = 0; i < p->lines->length; i++) {
    EmbLine line;
    embArray_get(p->lines, &line, j);
    embVector_component_product(line.start, line.start, flip);
    embVector_component_product(line.end, line.end, flip);
    embArray_set(p->lines, &line, j);
  }

  if (p->paths) {
    for (i = 0; i < p->paths->length; i++) {
      EmbPath* path;
      embArray_get(p->paths, &path, i);
      for (j = 0; j < path->pointList->length; j++) {
        EmbVector point;
        embArray_get(path->pointList, &point, j);
        embVector_component_product(point, point, flip);
        embArray_set(path->pointList, &point, j);
      }
    }
  }

  if (p->points) {
    for (i = 0; i < p->points->length; i++) {
      EmbPoint point;
      embArray_get(p->points, &point, i);
      point.position.x *= flip.x;
      point.position.y *= flip.y;
      embArray_set(p->points, &point, i);
    }
  }

  if (p->polygons) {
    for (i = 0; i < p->polygons->length; i++) {
      EmbPolygon* polygon;
      embArray_get(p->polygons, polygon, i);
      for (j = 0; j < polygon->pointList->length; j++) {
        EmbVector point;
        embArray_get(polygon->pointList, &point, j);
        embVector_component_product(point, point, flip);
        embArray_set(polygon->pointList, &point, j);
      }
    }
  }

  if (p->polylines) {
    for (i = 0; i < p->polylines->length; i++) {
      EmbPolyline* polyline;
      embArray_get(p->polylines, polyline, i);
      for (j = 0; j < polyline->pointList->length; j++) {
        EmbVector point;
        embArray_get(polyline->pointList, &point, j);
        embVector_component_product(point, point, flip);
        embArray_set(polyline->pointList, &point, j);
      }
    }
  }

  if (p->rects) {
    for (i = 0; i < p->rects->length; i++) {
      EmbRect rect;
      embArray_get(p->rects, &rect, j);
      rect.left *= flip.x;
      rect.right *= flip.x;
      rect.top *= flip.y;
      rect.bottom *= flip.y;
      embArray_set(p->rects, &rect, j);
    }
  }

  if (p->splines) {
    for (i = 0; i < p->splines->length; i++) {
      /* TODO: embPattern_flip for splines */
    }
  }
  return 1;
}

#if 0
/* Does this need a tolerance to stop really long jumps?
 */
embPattern_combineJumpStitches(EmbPattern* p)
{
  int jump = 0, i, j
  EmbStitch st

  if (!p) {
    embLog("ERROR: embPattern_combineJumpStitches(), p==0\n")
    return;
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
}

/* TODO: The params determine the max XY movement rather than the length.
 * They need renamed or clarified further. */
embPattern_correctForMaxStitchLength(EmbPattern* p, float maxStitchLength, float maxJumpLength)
{
  int j = 0, splits, i
  float maxXY, maxLen
  EmbVector st, diff, add
  EmbArray* newList

  if (!p) {
    embLog("ERROR: embPattern_correctForMaxStitchLength(), p==0\n")
    return;
  }
  if (p->stitchList->length > 1) {
    EmbStitch stitch
    newList = embArray_create(EMB_STITCH)
    embArray_get(p->stitchList, &stitch, 0)
    embArray_add(newList, &stitch)
    for (i = 1; i < p->stitchList->length; i++) {
      EmbStitch st1, st2;
      embArray_get(p->stitchList, &st1, i - 1);
      embArray_get(p->stitchList, &st2, i);
      st.x = st1.x;
      st.y = st1.y;
      diff.x = st2.x - st.x;
      diff.y = st2.y - st.y;
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
}

embPattern_center(EmbPattern* p)
{
  /* TODO: review this. currently not used in anywhere. Also needs to handle various design objects */
  int moveLeft, moveTop, i
  EmbRect boundingRect
  EmbStitch s

  if (!p) {
    embLog("ERROR: embPattern_center(), p==0\n")
    return;
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
}

/* TODO: Description needed. */
embPattern_loadExternalColorFile(EmbPattern* p, const char* fileName)
{
  char *dotPos
  char hasRead
  char *buffer = (char*)embBuffer

  hasRead = 0
  strcpy(buffer, (char*)fileName)
  dotPos = buffer + string_length(buffer)
  while (*dotPos != '.') {
    dotPos--
  }
  strcpy(dotPos, ".edr")
  hasRead = embPattern_readAuto(p, buffer)
  if (!hasRead) {
    strcpy(buffer, (char*)fileName)
    strcpy(dotPos, ".rgb")
    hasRead = embPattern_readAuto(p, buffer)
  }
  if (!hasRead) {
    strcpy(buffer, fileName)
    strcpy(dotPos, ".col")
    hasRead = embPattern_readAuto(p, buffer)
  }
  if (!hasRead) {
    strcpy(buffer, fileName)
    strcpy(dotPos, ".inf")
    hasRead = embPattern_readAuto(p, buffer)
  }
}

/* Frees all memory allocated in the pattern (\a p). */
embPattern_free(EmbPattern* p)
{
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
}

/* Adds a circle object to pattern (\a p) with its center at the absolute
 * position (\a cx,\a cy) with a radius of (\a r). Positive y is up.
 * Units are in millimeters. */
embPattern_addCircleObjectAbs(EmbPattern* p, float cx, float cy, float r, int lineType, EmbColor color)
{
  EmbCircle circle
  circle.center.x = cx
  circle.center.y = cy
  circle.radius = r
  circle.lineType = 0
  circle.color = color

  if (!p) {
    embLog("ERROR: embPattern_addCircleObjectAbs(), p==0\n")
    return;
  }
  embArray_add(p->circles, &circle)
}

/* Adds an ellipse object to pattern (\a p) with its center at the
 * absolute position (\a cx,\a cy) with radii of (\a rx,\a ry). Positive y is up.
 * Units are in millimeters. */
embPattern_addEllipseObjectAbs(EmbPattern* p, float cx, float cy, float rx, float ry, float rotation, int lineType, EmbColor color)
{
  EmbEllipse ellipse;
  ellipse.center.x = cx;
  ellipse.center.y = cy;
  ellipse.radius.x = rx;
  ellipse.radius.y = ry;
  ellipse.rotation = rotation;
  ellipse.lineType = lineType;
  ellipse.color = black;

  if (!p) {
    embLog("ERROR: embPattern_addEllipseObjectAbs(), p==0\n");
    return;
  }
  embArray_add(p->ellipses, &ellipse);
}

/* Adds a line object to pattern (\a p) starting at the absolute position
 * (\a x1,\a y1) and ending at the absolute position (\a x2,\a y2).
 * Positive y is up. Units are in millimeters.
 */
embPattern_addLineObjectAbs(EmbPattern* p, float x1, float y1, float x2, float y2, int lineType, EmbColor color)
{
  EmbLine line
  line.start.x = x1
  line.start.y = y1
  line.end.x = x2
  line.end.y = y2
  line.lineType = lineType
  line.color = color

  if (!p) {
    embLog("ERROR: embPattern_addLineObjectAbs(), p==0\n")
    return;
  }
  embArray_add(p->lines, &line)
}

embPattern_addPathObjectAbs(EmbPattern* p, EmbPathObject* obj)
{
  if (!p) {
    embLog("ERROR: embPattern_addPathObjectAbs(), p==0\n")
    return;
  }
  if (!obj) {
    embLog("ERROR: embPattern_addPathObjectAbs(), obj==0\n")
    return;
  }
  if (!obj->pointList) {
    embLog("ERROR: embPattern_addPathObjectAbs(), obj->pointList is empty\n")
    return;
  }

  embArray_add(p->paths, obj)
}

/* Adds a point object to pattern (\a p) at the absolute position (\a x,\a y). Positive y is up. Units are in millimeters. */
embPattern_addPointObjectAbs(EmbPattern* p, float x, float y, int lineType, EmbColor color)
{
  EmbPointObject point
  point.position.x = x
  point.position.y = y
  point.lineType = lineType
  point.color = color

  if (!p) {
    embLog("ERROR: embPattern_addPointObjectAbs(), p==0\n")
    return;
  }
  embArray_add(p->points, &point)
}

embPattern_addPolygonObjectAbs(EmbPattern* p, EmbPolygonObject* obj)
{
  if (!p) {
    embLog("ERROR: embPattern_addPolygonObjectAbs(), p==0\n")
    return;
  }
  if (!obj) {
    embLog("ERROR: embPattern_addPolygonObjectAbs(), obj==0\n")
    return;
  }
  if (!obj->pointList) {
    embLog("ERROR: embPattern_addPolygonObjectAbs(), obj->pointList is empty\n")
    return;
  }

  embArray_add(p->polygons, obj)
}

embPattern_addPolylineObjectAbs(EmbPattern* p, EmbPolylineObject* obj)
{
  if (!p) {
    embLog("ERROR: embPattern_addPolylineObjectAbs(), p==0\n")
    return;
  }
  if (!obj) {
    embLog("ERROR: embPattern_addPolylineObjectAbs(), obj==0\n")
    return;
  }
  if (!obj->pointList) {
    embLog("ERROR: embPattern_addPolylineObjectAbs(), obj->pointList is empty\n")
    return;
  }

  embArray_add(p->polylines, obj)
}

embPattern_colorBlock16(EmbPattern *pattern, int file)
{
  int i

  /* write remaining colors to reach 16 */
  memory_set(embBuffer, 0, 16*4)

  for (i = 0; i < pattern->threads->length; i++) {
    EmbThread t
    t = pattern_thread(pattern, i)
    embColor_toStr(t.color, embBuffer+4*i)
  }

  fwrite(embBuffer, 1, 16*4, file)
}

/**
 * Adds a rectangle object to pattern (\a p) at the absolute position
 * (\a x,\a y) with a width of (\a w) and a height of (\a h).
 * Positive y is up. Units are in millimeters.
 */
embPattern_addRectObjectAbs(EmbPattern* p, float x, float y, float w, float h, int lineType, EmbColor color)
{
  EmbRect rect
  rect.left = x
  rect.top = y
  rect.right = x + w
  rect.bottom = y + h
  rect.lineType = 0
  rect.color = color

  if (!p) {
    embLog("ERROR: embPattern_addRectObjectAbs(), p==0\n")
    return;
  }
  embArray_add(p->rects, &rect)
}

embArray_resample(EmbArray *a, EmbArray *usePt)
{
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
}

int embVector_collinear(EmbVector a1, EmbVector a2, EmbVector a3, float collinearity_tolerance)
{
  EmbVector c21, c31
  float angle

  embVector_subtract(a2, a1, &c21)
  embVector_subtract(a3, a1, &c31)
  angle = GetAngle(c21, c31)
  return angle < collinearity_tolerance
}

float GetRelativeX(EmbVector a1, EmbVector a2, EmbVector a3)
{
  EmbVector c12, c32
  embVector_subtract(a1, a2, &c12)
  embVector_subtract(a3, a2, &c32)
  return embVector_dot(c12, c32)
}

float GetRelativeY(EmbVector a1, EmbVector a2, EmbVector a3)
{
  EmbVector c12, c32
  embVector_subtract(a1, a2, &c12)
  embVector_subtract(a3, a2, &c32)
  return embVector_cross(c12, c32)
}

float GetAngle(EmbVector a, EmbVector b)
{
  EmbVector h
  embVector_subtract(a, b, &h)
  return emb_atan2(h.x, h.y)
}

embPattern_breakIntoColorBlocks(EmbPattern *pattern)
{
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
}

int embPolygon_breakIntoSeparateObjects(EmbArray *blocks)
{
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
          yield return;
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
  return 1
}

int FindOutline(EmbArray *stitchData, EmbArray *result)
{
  int currColorIndex = 0, oddEven, i
  float dx, dy, dy2, dy3
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
  return 1
}

int DrawGraphics(EmbPattern p)
{
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
  return 0
}

int SimplifyOutline(EmbPattern *pattern, EmbPattern *patternOut)
{
  int color
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
  return 1
}

/**
 * Removes all collinear points on the polygon. Has a default bias of 0.
 *
 * @param vertices The polygon that needs simplification.
 * @param collinearityTolerence How close a point can be to collinear before it is removed.
 * @returns A simplified polygon in the same EmbArray.
 */
int embPolygon_collinearSimplify(EmbArray *vertices, float collinearityTolerance)
{
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
}

/**
 * Ramer-Douglas-Peucker polygon simplification algorithm. This is the general recursive version that does not use the
 * speed-up technique by using the Melkman convex hull.
 * If you pass in 0, it will remove all collinear points
 */
int embPolygon_DouglasPeuckerSimplify(EmbArray *vertices, float distanceTolerance)
{
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
}

embPolygon_simplifySection(EmbArray *vertices, EmbArray *_usePt, int i, int j, float distanceTolerance)
{
  int k, maxIndex
  EmbVector a, b, c
  float maxDistance, distance
  if ((i + 1) == j)
    return;

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
}

/**
 * Find the distance from (\a p) to the line from (\a a) to (\a b) by
 * finding the length of the normal from ab (extended to an infinite line)
 * to p.
 */
float embVector_distancePointLine(EmbVector p, EmbVector a, EmbVector b)
{
  float r, curve2, s, tolerance
  EmbVector pa, ba

  tolerance = 0.00001
  embVector_subtract(b, a, &ba)
  /* if start == end, then use point-to-point distance */
  if (emb_fabs(ba.x) < tolerance && emb_fabs(ba.y) < tolerance) {
    return embVector_distance(p, a)
  }

  /* otherwise use comp.graphics.algorithms Frequently Asked Questions method */
  /*(1)           AC dot AB
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
}

/* From physics2d.net */
int embPolygon_reduceByArea(EmbArray *vertices, EmbArray *result, float areaTolerance)
{
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
}

/**
 * From Eric Jordan's convex decomposition library
 * Merges all parallel edges in the list of vertices
 */
MergeParallelEdges(EmbArray *vertices, float tolerance)
{
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
    return;
  }

  embArray_resample(vertices, usePoints)
  embArray_free(usePoints)
}

/* Reduces the polygon by distance. */
int embPolygon_reduceByDistance(EmbArray *vertices, float distance)
{
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
}

/* Reduces the polygon by removing the Nth vertex in the vertices list. */
int embPolygon_reduceByNth(EmbArray* vertices, int nth)
{
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
}

embSatinOutline_generateSatinOutline(EmbArray* lines, float thickness, EmbSatinOutline* result)
{
  int i, j
  EmbSatinOutline outline
  EmbVector v1, temp
  EmbLine line, line1, line2
  float halfThickness = thickness / 2.0
  int intermediateOutlineCount = 2 * lines->length - 2
  outline.side1 = embArray_create(EMB_VECTOR)
  if (!outline.side1) {
    embLog("ERROR: embSatinOutline_generateSatinOutline() embArray_create()\n")
    return;
  }
  outline.side2 = embArray_create(EMB_VECTOR)
  if (!outline.side2) {
    embLog("ERROR: embSatinOutline_generateSatinOutline() embArray_create()\n")
    return;
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
    return;
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
}

EmbArray* embSatinOutline_renderStitches(EmbSatinOutline* result, float density)
{
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
}


int embPattern_write(EmbPattern* pattern, const char* fileName, int format)
{
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
  case EMB_FORMAT_COL:
    r = writeCol(pattern, file, fileName);
    break;
  case EMB_FORMAT_CSV:
    r = writeCsv(pattern, file, fileName);
    break;
  case EMB_FORMAT_JEF:
    r = writeJef(pattern, file, fileName);
    break;
  case EMB_FORMAT_PEC:
    r = writePec(pattern, file, fileName);
    break;
  case EMB_FORMAT_PES:
    r = writePes(pattern, file, fileName);
    break;
  case EMB_FORMAT_SVG:
    r = writeSvg(pattern, file, fileName);
    break;
  default:
    embLog("Emb format not recognised.");
    break;
  }

  if (!r) {
    return r
  }

  fclose(file)
  return 0
}

int embPattern_read(EmbPattern* pattern, const char* fileName, int format)
{
  int file;
  int r;

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
  case EMB_FORMAT_COL:
    r = readCol(pattern, file, fileName);
    break;
  case EMB_FORMAT_CSV:
    r = readCsv(pattern, file, fileName);
    break;
  case EMB_FORMAT_DST:
    r = readDst(pattern, file, fileName);
    break;
  case EMB_FORMAT_JEF:
    r = readJef(pattern, file, fileName);
    break;
  case EMB_FORMAT_PEC:
    r = readPec(pattern, file, fileName);
    break;
  case EMB_FORMAT_PES:
    r = readPes(pattern, file, fileName);
    break;
  case EMB_FORMAT_RGB:
    r = readRgb(pattern, file, fileName);
    break;
  case EMB_FORMAT_SEW:
    r = readSew(pattern, file, fileName);
    break;
  case EMB_FORMAT_SVG:
    r = readSvg(pattern, file, fileName);
    break;
  case EMB_FORMAT_THR:
    r = readThr(pattern, file, fileName);
    break;
  default:
    embLog("Emb format not recognised.");
    break;
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
}

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
}

/**
 * TODO: documentation.
 * ISSUE: the last line may get cut off in certain cases.
 * ISSUE: how are blank lines dealt with?
 */
embFile_readline:
int embFile_readline(int stream, char* line, int maxLength)
{
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
}

/*
 * Pad the int stream with n bytes all with value c.
 *
 * Caller sets ebx to file descriptor.
 * Caller sets eax to length of padding (in spaces)
 */
file_pad_spaces:
  movl  $0x01, %edx
  movl  $dot, %ecx
  movl  $SYS_WRITE, %eax
  int  $0x80
  movl  (length), %edx
  subl  $1, %edx
  movl  %edx, (length)
  cmp  $0, %edx
  jnz  file_pad_spaces
}

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
  movl  (length), %eax
  cmp  $0, %eax
  jnz  embFile_copy_null_terminated
  
  /*
  char c
  int i
  for (i=0; i<n; i++) {
    fread(&c, 1, 1, in)
    fwrite(&c, 1, 1, out)
  }
  */
embFile_copy_:
  movl  $0x01, %edx
  movl  $buffer, %ecx
  movl  $SYS_WRITE, %eax
  int  $0x80
  movl  (length), %edx
  subl  $1, %edx
  movl  %edx, (length)
  cmp  $0, %edx
}
embFile_copy_null_terminated:
  /*
  char c = 1
  while (c) {
    fread(&c, 1, 1, in)
    fwrite(&c, 1, 1, out)
  }
  */
}

/*
 * Open a temporary file that we assume will be deleted after fclose
 * is called on it.
 *
 * int tmpfile(void)
 *  return open("/tmp", O_RDWR | O_TMPFILE, 0666)
 */
tmpfile:
}

/*
 * TODO: documentation.
 * (int stream, const char* str)
 * returns int
 */
embFile_print:
  /* fwrite((void *)str, 1, string_length(str), stream) */
}

/*
 * TODO: documentation.
 */
int embFormat_getExtension(const char* fileName, char* ending)
{
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
}

EmbFormatList embFormat_data(int format)
{
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
}

/**
 * Returns a pointer to an EmbReaderWriter if the \a fileName is a supported file type.
 */
int embReaderWriter_getByFileName(const char* fileName)
{
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
}

const char* csvStitchFlagToStr(int flags)
{
  int i, p;
  switch (flags) {
  case NORMAL:
    i = 0;
    break;
  case JUMP:
    i = 1;
    break;
  case TRIM:
    i = 2;
    break;
  case STOP:
    i = 3;
    break;
  case END:
    i = 4;
    break;
  default:
    i = 5;
    break;
  }
  p = double_dereference_int(stitch_labels, i);
  get_str((char*)embBuffer, p);
  return (char*)embBuffer;
}

char csvStrToStitchFlag(const char* str)
{
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
}

char readCsv(EmbPattern* pattern, int file, const char* fileName)
{
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
          strcpy(t.description, "NULL")
          strcpy(t.catalogNumber, "NULL")
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
}

/* Copy a block of bytes from the datafile to the elected file
 * if length == 0 use null termination to end copy, otherwise
 * copy length bytes.
 */
string_to_file(int file, int offset, int length)
{
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
}

/* 
 */
print_log_string(int index)
{
  /* acts as an error number */
  emb_int_to_array((char*)embBuffer, index, 5)
  embLog((char*)embBuffer)
  get_str((char*)embBuffer, 4*index)
  embLog((char*)embBuffer)
}

char writeCsv(EmbPattern* pattern, int file, const char* fileName)
{
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
}

EmbArc pattern_arc(EmbPattern *p, int index)
{
  EmbArc a;
  fseek(memory[p->arcs->file_id], sizeof(EmbArc)*index, SEEK_SET);
  fread(&a, sizeof(EmbArc), 1, memory[p->arcs->file_id]);
  return a;
}

EmbThread pattern_thread(EmbPattern *p, int index)
{
  EmbThread t;
  fseek(memory[p->threads->file_id], sizeof(EmbThread)*index, SEEK_SET);
  fread(&t, sizeof(EmbThread), 1, memory[p->threads->file_id]);
  return t;
}

EmbStitch pattern_stitch(EmbPattern *p, int index)
{
  EmbStitch st
  fseek(memory[p->stitchList->file_id], sizeof(EmbStitch)*index, SEEK_SET)
  fread(&st, sizeof(EmbStitch), 1, memory[p->stitchList->file_id])
  return st
}

EmbThread load_thread(int thread_table, int index)
{
  EmbThread t
  int out
  out = double_dereference_int(brand_codes, thread_table)
  fseek(datafile, out+35*index, SEEK_SET)
  fread(embBuffer, 1, 35, datafile)
  t.color.r = embBuffer[30]
  t.color.g = embBuffer[31]
  t.color.b = embBuffer[32]
  strcpy(t.catalogNumber, "TODO:HUS_CODE")
  strcpy(t.description, (char *)embBuffer)
  return t;    
}

char writePcs(EmbPattern* pattern, int file, const char* fileName)
{
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
}

readPecStitches(EmbPattern* pattern, int file, const char* fileName)
{
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
}

pecEncodeJump(int file, int x, int types)
{
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
}

pecEncodeStop(int file, unsigned char val)
{
  fwrite("\xFE\xB0", 1, 2, file)
  fwrite(&val, 1, 1, file)
}

char readPec(EmbPattern* pattern, int file, const char* fileName)
{
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
}

pecEncode(int file, EmbPattern* p)
{
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
}

clearImage(unsigned char image[][48])
{
  int out
  out = dereference_int(image_frame)
  fseek(datafile, out, SEEK_SET)
  fread(image, 1, 48*38, datafile)
}

writeImage(int file, unsigned char image[][48])
{
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
}

writePecStitches(EmbPattern* pattern, int file, const char* fileName)
{
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
}

char writePec(EmbPattern* pattern, int file, const char* fileName)
{
  /* TODO: There needs to be a matching flipVertical() call after the write
   * to ensure multiple writes from the same pattern work properly */
  embPattern_flipVertical(pattern)
  embPattern_fixColorCount(pattern)
  embPattern_correctForMaxStitchLength(pattern, 12.7, 204.7)
  embPattern_scale(pattern, 10.0)

  binaryWriteBytes(file, "#PEC0001", 8)

  writePecStitches(pattern, file, fileName)

  return 1
}

char readPes(EmbPattern* pattern, int file, const char* fileName)
{
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
}

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
}

/*
readPESHeader(int file, EmbPattern* pattern)
{
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

void readPESHeaderDefault(FILE *f)
{
  int pecStart = binaryReadInt32();
  skip(pecStart - readPosition);
}

void readDescriptions()
{
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
}

readPESHeaderV4()
{
  int pecStart = binaryReadInt32()
  fseek(file, 4, SEEK_CUR)
  readDescriptions()
  skip(pecStart - readPosition)
}

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
      return;
    }
    int nMotifs = binaryReadInt16()
    if (nMotifs != 0) {
      fseek(file, pecStart, SEEK_SET)
      return;
    }
    int featherPatternCount = binaryReadInt16()
    if (featherPatternCount != 0) {
      fseek(file, pecStart, SEEK_SET)
      return;
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
      return;
    }
    int nMotifs = binaryReadInt16()
    if (nMotifs != 0) {
      fseek(file, pecStart, SEEK_SET)
      return;
    }
    int featherPatternCount = binaryReadInt16()
    if (featherPatternCount != 0) {
      fseek(file, pecStart, SEEK_SET)
      return;
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
      return;
    }
    int nMotifs = binaryReadInt16()
    if (nMotifs != 0) {
      fseek(file, pecStart, SEEK_SET)
      return;
    }
    int featherPatternCount = binaryReadInt16()
    if (featherPatternCount != 0) {
      fseek(file, pecStart, SEEK_SET)
      return;
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
      return;
    }
    int nMotifs = binaryReadInt16()
    if (nMotifs != 0) {
      fseek(file, pecStart, SEEK_SET)
      return;
    }
    int featherPatternCount = binaryReadInt16()
    if (featherPatternCount != 0) {
      fseek(file, pecStart, SEEK_SET)
      return;
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
      return;
    }
    int nMotifs = binaryReadInt16()
    if (nMotifs != 0) {
      fseek(file, pecStart, SEEK_SET)
      return;
    }
    int featherPatternCount = binaryReadInt16()
    if (featherPatternCount != 0) {
      fseek(file, pecStart, SEEK_SET);
      return;
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
      return;
    }
    int nMotifs = binaryReadInt16()
    if (nMotifs != 0) {
      fseek(file, pecStart, SEEK_SET)
      return;
    }
    int featherPatternCount = binaryReadInt16()
    if (featherPatternCount != 0) {
      fseek(file, pecStart, SEEK_SET)
      return;
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
pesWriteSewSegSection(EmbPattern* pattern, int file, const char* fileName)
{
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
}

pesWriteEmbOneSection(EmbPattern* pattern, int file, const char* fileName)
{
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
}

char writePes(EmbPattern* pattern, int file, const char* fileName)
{
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
}

char readPhb(EmbPattern* pattern, int file, const char* fileName)
{
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
}

char writePhb(EmbPattern* pattern, int file, const char* fileName)
{
  return 0; /*TODO: finish writePhb */
}

char readPhc(EmbPattern* pattern, int file, const char* fileName)
{
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
}

char writePhc(EmbPattern* pattern, int file, const char* fileName)
{
  return 0; /*TODO: finish writePhc */
}

char readPlt(EmbPattern* pattern, int file, const char* fileName)
{
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
}

char writePlt(EmbPattern* pattern, int file, const char* fileName)
{
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
}

char readRgb(EmbPattern* pattern, int file, const char* fileName)
{
  EmbThread t
  pattern->threads->length = 0
  strcpy(t.catalogNumber, "NULL")
  strcpy(t.description, "NULL")
  while (fread(embBuffer, 1, 4, file) == 4) {
    t.color = embColor_fromStr(embBuffer)
    embPattern_addThread(pattern, t)
  }
  return 1
}

char writeRgb(EmbPattern* pattern, int file, const char* fileName)
{
  int i

  embBuffer[3] = 0
  for (i = 0; i < pattern->threads->length; i++) {
    EmbThread t
    t = pattern_thread(pattern, i)
    embColor_toStr(t.color, embBuffer)
    fwrite(embBuffer, 1, 4, file)
  }
  return 1
}

char sewDecode(unsigned char inputByte)
{
  /* TODO: fix return statement */
  return (inputByte >= 0x80) ? (char)(-~(inputByte - 1)) : (char)inputByte
}

char readSew(EmbPattern* pattern, int file, const char* fileName)
{
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
}

sewEncode(unsigned char* b, char dx, char dy, int flags)
{
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
}

char writeSew(EmbPattern* pattern, int file, const char* fileName)
{
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
}

int encode_dst_ternary(int *x, unsigned char *b)
{
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
}

/* A version of the stitch decoding with less branching,
 * the BIT macro returns either 0 or 1 based on the value
 * of that bit and then is multiplied by what value that represents.
 */
decode_dst_ternary(int *x, unsigned char *b)
{
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
}

EmbColor embColor_from_str(char *b)
{
  EmbColor c
  c.r = b[0]
  c.g = b[1]
  c.b = b[2]
  return c
}

void embColor_to_str(EmbColor c, char *b)
{
  b[0] = c.r
  b[1] = c.g
  b[2] = c.b
}

/*
 * Writes out a color to the int file in hex format without using
 * printf or varadic functions (for embedded systems).
 */
void write_svg_color(int file, EmbColor color)
{
  char hex[] = "0123456789ABCDEF"
  /*
  embFile_print(file, "stroke=\"#")
  fwrite(hex + (color.r % 16), 1, 1, file)
  fwrite(hex + (color.r / 16), 1, 1, file)
  fwrite(hex + (color.g % 16), 1, 1, file)
  fwrite(hex + (color.g / 16), 1, 1, file)
  fwrite(hex + (color.b % 16), 1, 1, file)
  fwrite(hex + (color.b / 16), 1, 1, file)
  embFile_print(file, "\" ")
  */
}

void write_point(int file, float x, float y)
{
  /* 
  (file, x)
  call  write_float
  embFile_print(file, ",")
  (file, y)
  call  write_float
  */
}

/*
 * TODO: fix bugs in embFloatToArray
 */
write_float(int file, float number)
  /*
  char *buffer = (char*)embBuffer
  (buffer, number, 1.0e-7, 3, 5)
  call  emb_float_to_array
  (file, buffer)
  call  embFile_print
  */
}

writeFloatWrap()
  /*
  (int file, char *prefix, float number, char *suffix)
{
  embFile_print(file, prefix)
  writeFloat(file, number)
  embFile_print(file, suffix)
  */
}

void writeFloatAttribute(int file, char *attribute, float number)
{
  /*
  (file, attribute)
  call  embFile_print
  writeFloatWrap(file, "=\"", number, "\" ")
  call  write_float_wrap
  */
}

  .data

svg_creator:
  .long  0
svg_expect:
  .long  0

  .text
int svgMultiValue
int svgAttributes = 0
int element_set = 0
char currentElementToken
int attributes
int currentValue
char currentElementName[30]
char currentAttribute[30]

EmbColor svgColorToEmbColor(char* colorStr)
{
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
}

int svgPathCmdToEmbPathFlag(char cmd)
{
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
}

svgElement_addAttribute(const char* name, const char* value)
{
  int i
  if (!element_set) {
    embLog("ERROR: svgElement_addAttribute(), no recognised element.")
    return;
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
}

char* svgAttribute_getValue(const char* name)
{
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
}

svgAddToPattern(EmbPattern* p)
{
  EmbPointObject test
  EmbColor color
  EmbPathObject* path

  if (!p) {
    embLog("ERROR: svgAddToPattern(), p==0\n")
    return;
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
      return;
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
          return;
        }
      }
    }

    /* TODO: subdivide numMoves > 1 */

    color = svgColorToEmbColor(svgAttribute_getValue("stroke"))
    path.pointList = pointList;
    path.flagList = flagList;
    path.color = color;
    path.lineType = 1;
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
          return;
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
}

int svgIsElement(const char* buff)
{
  if (string_in_table(buff, svg_element_token_table)) {
    return SVG_ELEMENT;
  }

  /* Attempt to identify the program that created the SVG file. This should be in a comment at that occurs before the svg element. */
  else if (string_equal(buff, "Embroidermodder")) {
    svgCreator = SVG_CREATOR_EMBROIDERMODDER;
  } else if (string_equal(buff, "Illustrator")) {
    svgCreator = SVG_CREATOR_ILLUSTRATOR;
  } else if (string_equal(buff, "Inkscape")) {
    svgCreator = SVG_CREATOR_INKSCAPE;
  }

  return SVG_NULL;
}

char svgIsMediaProperty(const char* buff)
{
  if (string_in_table(buff, svg_media_property_token_table)) {
    return SVG_MEDIA_PROPERTY
  }
  return SVG_NULL
}

char svgIsProperty(const char* buff)
{
  if (string_in_table(buff, svg_property_token_table)) {
    return SVG_PROPERTY
  }
  return SVG_NULL
}

char string_in_table(const char *buff, int table)
{
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
}

char svgIsSvgAttribute(const char* buff)
{
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
}

int svgIsCatchAllAttribute(const char* buff)
{
  if (string_in_table(buff, svg_property_token_table)) {
    return SVG_CATCH_ALL
  }
  if (svgCreator == SVG_CREATOR_INKSCAPE) {
    if (string_in_table(buff, svg_attribute_token_table)) {
      return SVG_CATCH_ALL
    }
  }

  return SVG_NULL
}

char svgHasAttribute(const char *buff, int out, const char *errormsg)
{
  if (string_in_table(buff, out)) {
    return SVG_ATTRIBUTE
  }

  embLog("")
  embLog(errormsg)
  embLog("attribute unknown:")
  embLog(buff)

  return SVG_NULL
}


char identify_element(char *token)
{
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
}

svgProcess(int c, const char* buff)
{
  if (svgExpect == SVG_EXPECT_ELEMENT) {
    char advance = 0
    if (buff[0] == '/') {
      return;
    }

    advance = (char)svgIsElement(buff)

    if (advance) {
      embLog("ELEMENT:\n")
      svgExpect = SVG_EXPECT_ATTRIBUTE
      element_set = 1
      svgAttributes = 0
      ftruncate(attributes, 0)
      strcpy(currentElementName, buff)
    } else {
      return;
    }
  } else if (svgExpect == SVG_EXPECT_ATTRIBUTE) {
    char advance = 0
    if (!element_set) {
      embLog("There is no current element but the parser expects one.")
      return;
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
      strcpy(currentAttribute, buff)
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
        strcpy(currentValue, buff)
      } else {
        char *buffer = (char*)embBuffer
        int length
        strcpy(buffer, currentValue)
        length = string_length(buff) + string_length(buffer) + 2
        if (!currentValue) {
          embLog("ERROR: svgProcess(), cannot allocate memory for currentValue\n")
          return;
        }
        strcpy(currentValue, buffer)
        strcpy(currentValue+string_length(buffer), " ")
        strcpy(currentValue+string_length(buffer)+1, buff)
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
}

/* Reads a file with the given \a fileName and loads the data into \a p.
 *  Returns \c true if successful, otherwise returns \c false. */
char readSvg(EmbPattern* p, int file, const char* fileName)
{
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
}

writeCircles(int file, EmbArray* a, int i)
{
  EmbCircle circle
  embArray_get(a, &circle, i)
  /* TODO: use proper thread width for stoke-width rather than just 0.2 */
  embFile_print(file, "\n<circle stroke-width=\"0.2\" fill=\"none\" ")
  write_svg_color(file, circle.color)
  writeFloatAttribute(file, "cx", circle.center.x)
  writeFloatAttribute(file, "cy", circle.center.y)
  writeFloatAttribute(file, "r", circle.radius)
  embFile_print(file, "/>")
}

writeEllipses(int file, EmbArray* a, int i)
{
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
}

writeLines(int file, EmbArray* a, int i)
{
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
}

writePoints(int file, EmbArray* a, int i)
{
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
}

writePolygons(int file, EmbArray* a, int i)
{
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
}

writePolylines(int file, EmbArray* a, int i)
{
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
}

/*
 * (int file, EmbArray* p, int i)
 */
writeRects:
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
}

writeSvg:
char writeSvg(EmbPattern* p, int file, const char* fileName)
{
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
}


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
    call  embColor_distance

    if (delta <= currentClosestValue) {
      currentClosestValue = delta
      closestIndex = i
    }
  }
  return closestIndex
  */
}

/**
 * Returns a random thread color, useful in filling in cases where the
 * actual color of the thread doesn't matter but one needs to be declared
 * to test or render a pattern.
 *
 * returns c The resulting color.
 */
  .data
embThread_random:
  .byte  0, 0, 0, 0
  .ascii  "random........................"
  .ascii  "NULL......"

  .text
embThread_getRandom:
  call  random_int
  mov  %al, (embThread_random+1)
  call  random_int
  mov  %al, (embThread_random+2)
  call  random_int
  mov  %al, (embThread_random+3)
}

/*
thread_color_loop_num:
  .long  0
int thread_color(EmbColor *c, const char* name, int brand)
{
  int length, i
  length = double_dereference_int(table_lengths, brand)
  *c = black
*/

thread_color_loop:
  /*
  for (i=0; i<length; i++) {
  EmbThread t = load_thread(brand, i)
  if (string_equal(t.description, name)) {
  call  string_equal
  cmp  strings_are_equal, $0
  jlt  thread_color_condition
  cmp  
  jlt  thread_color_loop

  movl  $0, (error_code)
  */
}

thread_color_condition:
  /*
  movl  t.color, *c
  movl  $1, (error_code)
  */
}

int
thread_color_num(EmbColor color, int brand)
{
  int length, i;
  length = double_dereference_int(table_lengths, brand);

  for (i=0; i<length; i++) {
    EmbThread t = load_thread(brand, i);
    if (embColor_equal(t.color, color)) {
      return t.catalogNumber;
    }
  }

  return -1;
}

int
thread_color_name(char *result, EmbColor color, int brand)
{
  int length, i;
  length = double_dereference_int(table_lengths, brand);

  for (i=0; i<length; i++) {
    EmbThread t = load_thread(brand, i);
    if (embColor_equal(t.color, color)) {
      strcpy(result, t.description);
      return;
    }
  }

  strcpy(result, "COLOR NOT FOUND");
}

int datafile = 0;
const char *datafile_name = "libembroidery_data.bin";
const char *datafile_mode = "rb";

/* For now we are assuming that there is only one pattern loaded at a time.
 * Therefore the arrays shifted to the file "libembroidery_memory.bin" can
 * be assumed to be for this active pattern pattern.
 */
int init_embroidery(void)
{
  movl  (datafile_mode), %ecx
  movl  datafile_name, %ebx
  movl  $SYS_OPEN, %eax
  int  $0x80
}

int close_embroidery(void)
{
  movl  (datafile), %ebx
  movl  $SYS_CLOSE, %eax
  int  $0x80
}

#endif
