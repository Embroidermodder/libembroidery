/* libembroidery SWIG language bindings interface file */
%module libembroidery
%include "carrays.i"
%array_class(EmbFormatList, EmbFormatListArray);
%inline %{
#include "../libembroidery/embroidery.h"
%}

/* TODO: review EMB_PRIVATE functions and move them into private files if needed. */
%include "../libembroidery/embroidery.h"
