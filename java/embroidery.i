/* embroidery.i */
%module libembroidery
%{
    #define SWIG_FILE_WITH_INIT
    #include "../src/embroidery.h"
%}
%include "../src/embroidery.h"
