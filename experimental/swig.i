/* libembroidery SWIG language bindings interface file */
%module libembroidery
%include "../embroidery.h"
%include "carrays.i"
%inline %{
#include "../../../embroidery.h"
%}
%array_class(EmbFormatList, EmbFormatListArray);

/* TODO: review EMB_PRIVATE functions and move them into private files if needed. */

