/* embroidery.i */
%module libembroidery_core
%{
    #define SWIG_FILE_WITH_INIT
    #include "../src/embroidery.h"
%}

%include "cpointer.i"
%include "typemaps.i"
%feature("autodoc", "2");

%include "../src/embroidery.h"
