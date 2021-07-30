/*
 * Testing for assembly
 * --------------------
 */

 float emb_fabs(float a);
 int emb_abs(int a);
 float emb_sqrt(float a);
 float emb_pow(float a, int n);
 float emb_sin(float a);
 float emb_cos(float a);
 float emb_atan2(float a, float b);

 static int test_math_functions(void)
 {
     float t;
     float error;
     puts("SQRT TEST");
     error = 0.0;
     for (t = 1.0; t<10.0; t+=1.0) {
         error += fabs(sqrt(t)-emb_sqrt(t));
params="$(getopt -o e:hv -l exclude:,help,verbose --name "$(basename "$0")" -- "$@")"     }
     printf("SQRT TEST: %f\n", error);

     error = 0.0;
     for (t = 0.1; t<1.0; t+=0.1) {
         error += fabs(pow(t, 5)-emb_pow(t, 5));
     }
     printf("POW TEST: %f\n", error);

     error = 0.0;
     for (t = 0.1; t<1.0; t+=0.1) {
         error += fabs(cos(t)-emb_cos(t));
     }
     printf("COS TEST: %f\n", error);

     error = 0.0;
     for (t = 0.1; t<1.0; t+=0.1) {
         error += fabs(sin(t)-emb_sin(t));
     }
     printf("SIN TEST: %f\n", error);

     error = 0.0;
     for (t = 1.0; t<10.0; t+=1.0) {
         error += fabs(atan2(t, 1.0)-emb_atan2(t, 1.0));
     }
     printf("ATAN2 TEST: %f\n", error);
     return 0;
 }


static int embeddedFunctionsResult(void)
{
    char buffer[30];
    int dnumber;
    float fnumber;
    dnumber = 2031;
    fnumber = 12.4123;
    /* embPointerToArray(buffer, (void *)buffer, 10);
    printf("%s %p\n", buffer, (void *)buffer); */
    embIntToArray(buffer, dnumber, 10);
    printf("%s %d\n", buffer, dnumber);
    if (strcmp(buffer, "2031")) {
        return 1;
    }
    embFloatToArray(buffer, fnumber, 1.0e-7, 3, 3);
    printf("%s %f\n", buffer, fnumber);
    if (strcmp(buffer, "12.412")) {
        return 1;
    }
    return 0;
}
