; Assemble:
; $ nasm -f bin -l libembroidery_data.lst -o libembroidery_data.o libembroidery_data.asm
;
; Testing program (run on little-endian machine):
; $ gcc test.c
; $ ./a.out

	dd	svg_property_token_table
	dd	svg_attribute_token_table
	dd	svg_token_lists
	dd	brand_codes
	dd	image_frame
	dd	format_list
	dd	0

%include "svg_data.asm"
%include "format_data.asm"
%include "thread_tables.asm"

