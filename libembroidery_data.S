
	.long	.svg_property_token_table	/* 0 */
	.long	svg_attribute_token_table	/* 1 */
	.long	svg_token_lists			/* 2 */
	.long	brand_codes			/* 3 */
	.long	image_frame			/* 4 */
	.long	csv_header			/* 5 */
	.long	max_header			/* 6 */
	.long	csd_decoding_table		/* 7 */
	.long	vip_decoding_table		/* 8 */
	.long	format_list			/* 9 */
	.long	svg_token_table			/* 10 */
	.long	inkscape_token_table		/* 11 */
	.long	svg_element_token_table		/* 12 */
	.long	svg_media_property_token_table  /* 13 */
	.long	stitch_labels			/* 14 */
/*	.long	dxf_version_year		   15 */
	.long	dxf_version_r			/* 15 */
	.long	table_lengths			/* 16 */

/*
 * ------------------------------------
 * error string table
 * ------------------------------------
 */
	.long	.error_emb_sqrt$				/* 17 */
	.long	error_emb_atan2				/* 18 */
	.long	error_hus_expand			/* 19 */
	.long	error_hus_compress			/* 20 */
	.long	error_arc_data				/* 21 */
	.long	error_format_not_supported		/* 22 */
	.long	error_line_intersection			/* 23 */
	.long	error_line_parallel			/* 24 */
	.long	error_normalize				/* 25 */
	.long	error_pattern_no_stitches		/* 26 */
	.long	error_pattern_open_file			/* 27 */
	.long	error_vector_a.long			/* 28 */
	.long	error_vector_average			/* 29 */
	.long	error_vector_component_product		/* 30 */
	.long	error_vector_multiply			/* 31 */
	.long	error_vector_normal			/* 32 */
	.long	error_vector_subtract
	.long	error_pattern_create_malloc
	.long	error_hide_stitches_no_pattern
	.long	error_fix_color_count_no_pattern
	.long	error_copy_stitch_list_no_pattern
	.long	error_copy_polylines_no_point_list
	.long	error_move_stitch_list_no_pattern
	.long	error_add_stitch_abs_no_pattern
	.long	error_add_stitch_abs_multiple_end
	.long	error_add_stitch_rel_no_pattern
	.long	error_change_color_no_pattern
	.long	error_pattern_read_unsupported
	.long	error_pattern_write_unsupported
	.long	error_pattern_scale
	.long	error_bounding_box_no_pattern
	.long	error_flip_horizontal_no_pattern
	.long	error_flip_vertical_no_pattern
	.long	error_flip_no_pattern
	.long	error_combine_jump_stitches
	.long	error_pattern_max_stitch_length
	.long	error_pattern_center
	.long	error_add_circle
	.long	error_add_ellipse
	.long	error_add_line
	.long	error_add_path
	.long	error_add_path_obj
	.long	error_add_path_obj_empty
	.long	error_add_point
	.long	error_add_polygon_abs
	.long	error_add_polygon_abs_obj
	.long	error_add_polygon_abs_empty
	.long	error_add_polyline_abs
	.long	error_add_polyline_abs_obj
	.long	error_add_polyline_abs_empty
	.long	error_add_rect
	.long	error_generate_satin_array_create
	.long	error_generate_satin_result_memory
	.long	error_render_stitches_result_memory
	.long	error_read_no_pattern
	.long	error_read_no_filename
	.long	error_read_cannot_open
	.long	error_cannot_open
	.long	error_bcf_difat_malloc
	.long	error_bcf_difat_sector_value
	.long	error_read_sector_value
	.long	error_bcf_fat_create
	.long	error_col_empty_line
	.long	error_compound_entry_malloc
	.long	error_compound_malloc
	.long	error_compound_unexpected_object_type
	.long	error_csv_string
	.long	error_format_get_extension
	.long	error_no_colors
	.long	error_read_dxf
	.long	error_unsupported
	.long	error_hus_decompress_data
	.long	error_hus_compress_data
	.long	error_read_hus
	.long	error_write_hus
	.long	error_jef_hoop_no_pattern
	.long	error_max_encode_no_file
	.long	error_ofm_.bytes_library_name
	.long	error_ofm_.bytes_color_name
	.long	error_read_ofm_malloc
	.long	error_stx_.byte_no_.byte
	.long	error_stx_.byte_no_file
	.long	error_stx_.byte_malloc
	.long	error_read_stx_gif_malloc
	.long	error_read_stx_malloc
	.long	error_encode_dst_x_out_of_range
	.long	error_encode_dst_y_out_of_range
	.long	error_encode_tap_x
	.long	error_encode_tap_y
	.long	error_vip_decompress_malloc
	.long	error_read_vip_string_val_malloc
	.long	error_read_vip_decoded_colors_malloc
	.long	error_read_vip_attribute_malloc
	.long	error_read_vip_x_malloc
	.long	error_read_vip_y_malloc
	.long	error_vip_compress_malloc
	.long	error_vp3_read_string_file
	.long	error_vp3_read_string_malloc
	.long	error_vp3_read_hoop_no_file
	.long	error_number_of_colors
	.long	error_check_color_byte_1
	.long	error_check_color_byte_2
	.long	error_check_color_byte_3
	.long	error_format_vp3_cannot_read
	.long	error_svg_add_attribute_no_element
	.long	error_svg_add_attribute_element_malloc
	.long	error_svg_add_attribute_list_malloc
	.long	error_svg_create_malloc
	.long	error_svg_create_element_null
	.long	error_svg_get_value_no_element
	.long	error_svg_get_value_no_name
	.long	error_svg_add_no_pattern
	.long	error_svg_add_malloc
	.long	error_svg_add_invalid_path
	.long	error_svg_add_realloc
	.long	error_svg_process_malloc
	.long	error_read_svg
	.long	error_write_csv_0
	.long	error_read_csv_0
	.long	error_read_csv_1
	.long	error_read_csv_2
	.long	0

error_string_table:
/*
; --------------------------------------------------------------
; Do not include the \n since it will be added at runtime.
; Each entry has a pointer in the header table.
; --------------------------------------------------------------
*/

error_emb_sqrt:
	.string	"ERROR: emb_sqrt did not converge."
error_emb_atan2:
	.string	"ERROR: arctan2 of (0, 0) is undefined."
error_hus_expand:
	.string	"ERROR: husExpand() buffer overflow."
error_hus_compress:
	.string	"ERROR: huscompress() buffer overflow."
error_arc_data:
	.string	"ERROR: Arc and Bulge direction do not match."
error_format_not_supported:
	.string	"ERROR: This format is not implemented."
error_line_intersection:
	.string	"ERROR: embLine_intersectionPoint(), no memory for result."
error_line_parallel:
	.string	"ERROR: embLine_intersectionPoint(), intersecting lines cannot be parallel."
error_normalize:
	.string	"ERROR: embVector_normalize(), result==0."
error_pattern_no_stitches:
	.string	"ERROR: embPattern_write(), pattern contains no stitches."
error_pattern_open_file:
	.string	"ERROR: embPattern_write(), failed to open file."
error_vector_add:
	.string	"ERROR: embVector_add(), result==0"
error_vector_average:
	.string	"ERROR: embVector_average(), result==0"
error_vector_component_product:
	.string	"ERROR: embVector_component_product(), result==0"
error_vector_multiply:
	.string	"ERROR: embVector_multiply(), result==0."
error_vector_normal:
	.string	"ERROR: embLine_normalVector(), no memory for result."
error_vector_subtract:
	.string	"ERROR: embVector_subtract(), result==0"
error_pattern_create_malloc:
	.string	"ERROR: embPattern_create(), unable to allocate memory for p."
error_hide_stitches_no_pattern:
	.string	"ERROR: embPattern_hideStitchesOverLength(), p==0"
error_fix_color_count_no_pattern:
	.string	"ERROR: embPattern_fixColorCount(), p==0"
error_copy_stitch_list_no_pattern:
	.string	"ERROR: embPattern_copyStitchListToPolylines(), p==0"
error_copy_polylines_no_point_list:
	.string	"ERROR: embPattern_copyPolylinesToStitchList(), currentPointList is null"
error_move_stitch_list_no_pattern:
	.string	"ERROR: embPattern_moveStitchListToPolylines(), p==0"
error_add_stitch_abs_no_pattern:
	.string	"ERROR: embPattern_addStitchAbs(), p==0"
error_add_stitch_abs_multiple_end:
	.string	"ERROR: embPattern_addStitchAbs(), found multiple END stitches"
error_add_stitch_rel_no_pattern:
	.string	"ERROR: embPattern_addStitchRel(), p==0"
error_change_color_no_pattern:
	.string	"ERROR: embPattern_changeColor(), p==0"
error_pattern_read_unsupported:
	.string	"ERROR: embPattern_read(), unsupported read file type:"
error_pattern_write_unsupported:
	.string	"ERROR: embPattern_write(), unsupported write file type:"
error_pattern_scale:
	.string	"ERROR: embPattern_scale(), p==0"
error_bounding_box_no_pattern:
	.string	"ERROR: embPattern_calcBoundingBox(), p==0"
error_flip_horizontal_no_pattern:
	.string	"ERROR: embPattern_flipHorizontal(), p==0"
error_flip_vertical_no_pattern:
	.string	"ERROR: embPattern_flipVertical(), pattern memory not supplied"
error_flip_no_pattern:
	.string	"ERROR: embPattern_flip(), pattern memory not supplied."
error_combine_jump_stitches:
	.string	"ERROR: embPattern_combineJumpStitches(), p==0"
error_pattern_max_stitch_length:
	.string	"ERROR: embPattern_correctForMaxStitchLength(), p==0"
error_pattern_center:
	.string	"ERROR: embPattern_center(), p==0"
error_add_circle:
	.string	"ERROR: embPattern_addCircleObjectAbs(), p==0"
error_add_ellipse:
	.string	"ERROR: embPattern_addEllipseObjectAbs(), p==0"
error_add_line:
	.string	"ERROR: embPattern_addLineObjectAbs(), p==0"
error_add_path:
	.string	"ERROR: embPattern_addPathObjectAbs(), p==0"
error_add_path_obj:
	.string	"ERROR: embPattern_addPathObjectAbs(), obj==0"
error_add_path_obj_empty:
	.string	"ERROR: embPattern_addPathObjectAbs(), obj->pointList is empty"
error_add_point:
	.string	"ERROR: embPattern_addPointObjectAbs(), p==0"
error_add_polygon_abs:
	.string	"ERROR: embPattern_addPolygonObjectAbs(), p==0"
error_add_polygon_abs_obj:
	.string	"ERROR: embPattern_addPolygonObjectAbs(), obj==0"
error_add_polygon_abs_empty:
	.string	"ERROR: embPattern_addPolygonObjectAbs(), obj->pointList is empty"
error_add_polyline_abs:
	.string	"ERROR: embPattern_addPolylineObjectAbs(), p==0"
error_add_polyline_abs_obj:
	.string	"ERROR: embPattern_addPolylineObjectAbs(), obj==0"
error_add_polyline_abs_empty:
	.string	"ERROR: embPattern_addPolylineObjectAbs(), obj->pointList is empty"
error_add_rect:
	.string	"ERROR: embPattern_addRectObjectAbs(), p==0"
error_generate_satin_array_create:
	.string	"ERROR: embSatinOutline_generateSatinOutline() embArray_create()"
error_generate_satin_result_memory:
	.string	"ERROR: embSatinOutline_generateSatinOutline(), result==0"
error_render_stitches_result_memory:
	.string	"ERROR: embSatinOutline_renderStitches(), result==0"
error_read_no_pattern:
	.string	"ERROR: embPattern_read(), pattern==0"
error_read_no_filename:
	.string	"ERROR: embPattern_read(), fileName==0"
error_read_cannot_open:
	.string	"ERROR: embPattern_read(), failed to open file"
error_cannot_open:
	.string	"ERROR: Cannot open the fileName in the given mode."
error_bcf_difat_malloc:
	.string	"ERROR: bcf_difat_create(), cannot allocate memory for difat"
error_bcf_difat_sector_value:
	.string	"ERROR: bcf_difat_create(), Unexpected sector value"
error_read_sector_value:
	.string	"ERROR: readFullSector(), Unexpected sector value"
error_bcf_fat_create:
	.string	"ERROR: bcfFileFat_create(), cannot allocate memory for fat"
error_col_empty_line:
	.string	"ERROR: Empty line in col file."
error_compound_entry_malloc:
	.string	"ERROR: CompoundFileDirectoryEntry(), cannot allocate memory for dir"
error_compound_malloc:
	.string	"ERROR: CompoundFileDirectory(), cannot allocate memory for dir"
error_compound_unexpected_object_type:
	.string	"ERROR: CompoundFileDirectoryEntry(), unexpected object type:"
error_csv_string:
	.string	"ERROR: csvStrToStitchFlag(), str==0"
error_format_get_extension:
	.string	"ERROR: embFormat_getExtension(), fileName==0"
error_no_colors:
	.string	"ERROR: Number of colors is zero."
error_read_dxf:
	.string	"ERROR: readDxf(), missing EOF at end of DXF file"
error_unsupported:
	.string	"ERROR: embReaderWriter_getByFileName(), unsupported file type:"
error_hus_decompress_data:
	.string	"ERROR: husDecompressData(), malloc()"
error_hus_compress_data:
	.string	"ERROR: husCompressData(), malloc()"
error_read_hus:
	.string	"ERROR: readHus(), malloc()"
error_write_hus:
	.string	"ERROR: writeHus(), malloc()"
error_jef_hoop_no_pattern:
	.string	"ERROR: jefSetHoopFromId(), pattern==0"
error_max_encode_no_file:
	.string	"ERROR: maxEncode(), file==0"
error_ofm_.bytes_library_name:
	.string	"ERROR: ofmReadLibrary(), unable to allocate memory for libraryName"
error_ofm_.bytes_color_name:
	.string	"ERROR: ofmRead.bytes(), ran out of memory for colorName"
error_read_ofm_malloc:
	.string	"ERROR: readOfm(), malloc()"
error_stx_.byte_no_.byte:
	.string	"ERROR: stxRead.byte(), .byte==0"
error_stx_.byte_no_file:
	.string	"ERROR: stxRead.byte(), file==0"
error_stx_.byte_malloc:
	.string	"ERROR: stxRead.byte(), malloc()"
error_read_stx_gif_malloc:
	.string	"ERROR: readStx(), unable to allocate memory for gif"
error_read_stx_malloc:
	.string	"ERROR: readStx(), malloc()"
error_encode_dst_x_out_of_range:
	.string	"ERROR: encode_dst_ternary(), x is not in valid range [-121,121]"
error_encode_dst_y_out_of_range:
	.string	"ERROR: encode_dst_ternary(), y is not in valid range [-121,121]"
error_encode_tap_x:
	.string	"ERROR: encode_tap_record(), x!=0"
error_encode_tap_y:
	.string	"ERROR: encode_tap_record(), y!=0"
error_vip_decompress_malloc:
	.string	"ERROR: vipDecompressData(), malloc()"
error_read_vip_string_val_malloc:
	.string	"ERROR: readVip(), cannot allocate memory for stringVal"
error_read_vip_decoded_colors_malloc:
	.string	"ERROR: readVip(), cannot allocate memory for decodedColors"
error_read_vip_attribute_malloc:
	.string	"ERROR: readVip(), cannot allocate memory for attributeData"
error_read_vip_x_malloc:
	.string	"ERROR: readVip(), cannot allocate memory for xData"
error_read_vip_y_malloc:
	.string	"ERROR: readVip(), cannot allocate memory for yData"
error_vip_compress_malloc:
	.string	"ERROR: vipCompressData(), cannot allocate memory for compressedData"
error_vp3_read_string_file:
	.string	"ERROR: vp3ReadString(), file==0"
error_vp3_read_string_malloc:
	.string	"ERROR: vp3ReadString(), malloc()"
error_vp3_read_hoop_no_file:
	.string	"ERROR: vp3ReadHoopSection(), file==0"
error_number_of_colors:
	.string	"ERROR: Number of Colors: %d"
error_check_color_byte_1:
	.string	"ERROR: Color Check Byte #1: 0 == %d"
error_check_color_byte_2:
	.string	"ERROR: Color Check Byte #2: 5 == %d"
error_check_color_byte_3:
	.string	"ERROR: Color Check Byte #3: 0 == %d"
error_format_vp3_cannot_read:
	.string	"ERROR: format-vp3.c could not read stitch block in entirety"
error_svg_add_attribute_no_element:
	.string	"ERROR: svgElement_addAttribute(), element==0."
error_svg_add_attribute_element_malloc:
	.string	"ERROR: svgElement_addAttribute(), cannot allocate memory for element->attributeList."
error_svg_add_attribute_list_malloc:
	.string	"ERROR: svgElement_addAttribute(), cannot allocate memory for list."
error_svg_create_malloc:
	.string	"ERROR: svgElement_create(), cannot allocate memory for element"
error_svg_create_element_null:
	.string	"ERROR: svgElement_create(), element->name is null"
error_svg_get_value_no_element:
	.string	"ERROR: svgAttribute_getValue(), element==0"
error_svg_get_value_no_name:
	.string	"ERROR: svgAttribute_getValue(), name==0"
error_svg_add_no_pattern:
	.string	"ERROR: svgAddToPattern(), p==0"
error_svg_add_malloc:
	.string	"ERROR: svgAddToPattern(), cannot allocate memory for pathbuff"
error_svg_add_invalid_path:
	.string	"ERROR: svgAddToPattern(), %s is not a valid svg path command, skipping..."
error_svg_add_realloc:
	.string	"ERROR: svgAddToPattern(), cannot re-allocate memory for pathbuff"
error_svg_process_malloc:
	.string	"ERROR: svgProcess(), cannot allocate memory for currentValue"
error_read_svg:
	.string	"ERROR: readSvg(), buffer overflow."
error_write_csv_0:
	.string	"ERROR: writeCsv(), pattern contains no stitches."
error_read_csv_0:
	.string	"ERROR: readCsv(), unable to allocate memory for buff."
error_read_csv_1:
	.string	"ERROR: readCsv(), premature newline."
error_read_csv_2:
	.string	"ERROR: readCsv(), cannot re-allocate memory for buff."
end_error_string_table:

error_string_table_length:
	.long	end_error_string_table-error_string_table


#if 0
; .byte table.
; --------------------------------------------------------------
; This section has macros for the counting of the length of the table,
; 
; --------------------------------------------------------------

%define	.byte_entry_length	35
%macro	table_length_entry	2

	.long	(%2 - %1)/.byte_entry_length

%endmacro

table_lengths:
	table_length_entry	arc_polyester_codes, arc_polyester_end
	table_length_entry	arc_rayon_codes, arc_rayon_end
	table_length_entry	coats_and_clark_rayon_codes, coats_and_clark_rayon_end
	table_length_entry	exquisite_polyester_codes, exquisite_polyester_end
	table_length_entry	fufu_polyester_codes, fufu_polyester_end
	table_length_entry	fufu_rayon_codes, fufu_rayon_end
	table_length_entry	hemingworth_polyester_codes, hemingworth_polyester_end
	table_length_entry	isacord_polyester_codes, isacord_polyester_end
	table_length_entry	isafil_rayon_codes, isafil_rayon_end
	table_length_entry	marathon_polyester_codes, marathon_polyester_end
	table_length_entry	marathon_rayon_codes, marathon_rayon_end
	table_length_entry	madeira_polyester_codes, madeira_polyester_end
	table_length_entry	madeira_rayon_codes, madeira_rayon_end
	table_length_entry	metro_polyester_codes, metro_polyester_end
	table_length_entry	pantone_codes, pantone_end
	table_length_entry	robison_anton_polyester_codes, robison_anton_polyester_end
	table_length_entry	robison_anton_rayon_codes, robison_anton_rayon_end
	table_length_entry	sigma_polyester_codes, sigma_polyester_end
	table_length_entry	sulky_rayon_codes, sulky_rayon_end
	table_length_entry	.byte_art_rayon_codes, .byte_art_rayon_end
	table_length_entry	.byte_art_polyester_codes, .byte_art_polyester_end
	table_length_entry	.byteelight_polyester_codes, .byteelight_polyester_end
	table_length_entry	z102_isacord_polyester_codes, z102_isacord_polyester_end
	table_length_entry	svg_color_codes, svg_color_end
	table_length_entry	hus_.byte_table, hus_.byte_end
	table_length_entry	jef_.byte_table, jef_.byte_end
	table_length_entry	pcm_.byte_table, pcm_.byte_end
	table_length_entry	pec_.byte_table, pec_.byte_end
	table_length_entry	shv_.byte_table, shv_.byte_end
	table_length_entry	dxf_color_table, dxf_color_end


svg_property_token_table:
	.long	audio_level_token
	.long	buffered_rendering_token
	.long	color_token
	.long	color_rendering_token
	.long	direction_token
	.long	display_token
	.long	display_align_token
	.long	fill_token
	.long	fill_opacity_token
	.long	fill_rule_token
	.long	font_family_token
	.long	font_size_token
	.long	font_style_token
	.long	font_variant_token
	.long	font_weight_token
	.long	image_rendering_token
	.long	line_increment_token
	.long	opacity_token
	.long	pointer_events_token
	.long	shape_rendering_token
	.long	solid_color_token
	.long	solid_opacity_token
	.long	stop_color_token
	.long	stop_opacity_token
	.long	stroke_token
	.long	stroke_dasharray_token
	.long	stroke_linecap_token
	.long	stroke_linejoin_token
	.long	stroke_miterlimit_token
	.long	stroke_opacity_token
	.long	stroke_width_token
	.long	text_align_token
	.long	text_anchor_token
	.long	text_rendering_token
	.long	unicode_bidi_token
	.long	vector_effect_token
	.long	viewport_fill_token
	.long	viewport_fill_opacity_token
	.long	visibility_token
	.long	0


svg_attribute_token_table:
	.long	about_token
	.long	accent_height_token
	.long	accumulate_token
	.long	additive_token
	.long	alphabetic_token
	.long	arabic_form_token
	.long	ascent_token
	.long	attribute_name_token
	.long	attribute_type_token
	.long	bandwidth_token
	.long	base_profile_token
	.long	bbox_token
	.long	begin_token
	.long	by_token
	.long	calc_mode_token
	.long	cap_height_token
	.long	class_token
	.long	content_token
	.long	content_script_type_token
	.long	cx_token
	.long	cy_token
	.long	d_token
	.long	datatype_token
	.long	default_action_token
	.long	descent_token
	.long	dur_token
	.long	editable_token
	.long	end_token
	.long	ev_event_token
	.long	event_token
	.long	external_resources_required_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	font_family_token
	.long	font_stretch_token
	.long	font_style_token
	.long	font_variant_token
	.long	font_weight_token
	.long	from_token
	.long	g1_token
	.long	g2_token
	.long	glyph_name_token
	.long	gradient_units_token
	.long	handler_token
	.long	hanging_token
	.long	height_token
	.long	horiz_adv_x_token
	.long	horiz_origin_x_token
	.long	id_token
	.long	ideographic_token
	.long	initial_visibility_token
	.long	k_token
	.long	key_points_token
	.long	key_splines_token
	.long	key_times_token
	.long	lang_token
	.long	mathematical_token
	.long	max_token
	.long	media_character_encoding_token
	.long	media_content_encoding_token
	.long	media_size_token
	.long	media_time_token
	.long	min_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	observer_token
	.long	offset_token
	.long	origin_token
	.long	overlay_token
	.long	overline_position_token
	.long	overline_thickness_token
	.long	panose_1_token
	.long	path_token
	.long	path_length_token
	.long	phase_token
	.long	playback_order_token
	.long	points_token
	.long	preserve_aspect_ratio_token
	.long	propagate_token
	.long	property_token
	.long	r_token
	.long	rel_token
	.long	repeat_count_token
	.long	repeat_dur_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	restart_token
	.long	rev_token
	.long	role_token
	.long	rotate_token
	.long	rx_token
	.long	ry_token
	.long	slope_token
	.long	snapshot_time_token
	.long	stemh_token
	.long	stemv_token
	.long	strikethrough_position_token
	.long	strikethrough_thickness_token
	.long	sync_behavior_token
	.long	sync_behavior_default_token
	.long	sync_master_token
	.long	sync_tolerance_token
	.long	sync_tolerance_default_token
	.long	system_language_token
	.long	target_token
	.long	timeline_begin_token
	.long	to_token
	.long	transform_token
	.long	transform_behavior_token
	.long	type_token
	.long	typeof_token
	.long	u1_token
	.long	u2_token
	.long	underline_position_token
	.long	underline_thickness_token
	.long	unicode_token
	.long	unicode_range_token
	.long	units_per_em_token
	.long	values_token
	.long	version_token
	.long	viewbox_token
	.long	width_token
	.long	widths_token
	.long	x_token
	.long	x_height_token
	.long	x1_token
	.long	x2_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.long	xlink_role_token
	.long	xlink_show_token
	.long	xlink_title_token
	.long	xlink_type_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	y_token
	.long	y1_token
	.long	y2_token
	.long	zoom_and_pan_token
	.long	slash_token
	.long	0


solid_color_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	id_token
	.long	property_token
	.long	rel_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0

stop_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	id_token
	.long	offset_token
	.long	property_token
	.long	rel_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0

svg_token_table:
	.long	about_token
	.long	base_profile_token
	.long	class_token
	.long	content_token
	.long	content_script_type_token
	.long	datatype_token
	.long	external_resources_required_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	height_token
	.long	id_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	playback_order_token
	.long	preserve_aspect_ratio_token
	.long	property_token
	.long	rel_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	snapshot_time_token
	.long	sync_behavior_default_token
	.long	sync_tolerance_default_token
	.long	timeline_begin_token
	.long	typeof_token
	.long	version_token
	.long	viewbox_token
	.long	width_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	zoom_and_pan_token
	.long	slash_token
	.long	0


inkscape_token_table:
	.long	xmlns_dc_token
	.long	xmlns_cc_token
	.long	xmlns_rdf_token
	.long	xmlns_svg_token
	.long	xmlns_token
	.long	0


svg_element_token_table:
	.long	xml_token
	.long	a_token
	.long	animate_token
	.long	animate_color_token
	.long	animate_motion_token
	.long	animate_transform_token
	.long	animation_token
	.long	audio_token
	.long	circle_token
	.long	defs_token
	.long	desc_token
	.long	discard_token
	.long	ellipse_token
	.long	font_token
	.long	font_face_token
	.long	font_face_src_token
	.long	font_face_uri_token
	.long	foreign_object_token
	.long	g_token
	.long	glyph_token
	.long	handler_token
	.long	hkern_token
	.long	image_token
	.long	line_token
	.long	linear_gradient_token
	.long	listener_token
	.long	metadata_token
	.long	missing_glyph_token
	.long	mpath_token
	.long	path_token
	.long	polygon_token
	.long	polyline_token
	.long	prefetch_token
	.long	radial_gradient_token
	.long	rect_token
	.long	script_token
	.long	set_token
	.long	solid_color_token
	.long	stop_token
	.long	svg_token
	.long	switch_token
	.long	tbreak_token
	.long	text_token
	.long	text_area_token
	.long	title_token
	.long	tspan_token
	.long	use_token
	.long	video_token
	.long	0

;	_tODO: not implemented _sVG _full 1.1 _spec _elements
%if 0
not_implemented_svg_tokens:
	.long	alt_glyph_token
	.long	alt_glyph_def_token
	.long	altGlyphItem_token
	.long	clip_path_token
	.long	color_profile_token
	.long	cursor_token
	.long	feBlend_token
	.long	fe_colorMatrix_token
	.long	fe_component_transfer_token
	.long	fe_composite_token
	.long	fe_convolveMatrix_token
	.long	feDiffuse_lighting_token
	.long	feDisplacementMap_token
	.long	feDistant_light_token
	.long	fe_flood_token
	.long	fe_funcA_token
	.long	fe_funcB_token
	.long	fe_funcG_token
	.long	fe_funcR_token
	.long	feGaussianBlur_token
	.long	feImage_token
	.long	feMerge_token
	.long	feMergeNode_token
	.long	feMorphology_token
	.long	feOffset_token
	.long	fe_point_light_token
	.long	fe_specular_lighting_token
	.long	fe_spot_light_token
	.long	fe_tile_token
	.long	fe_turbulence_token
	.long	filter
	.long	font_face_format_token
	.long	font_face_name_token
	.long	glyphRef_token
	.long	marker_token
	.long	mask_token
	.long	pattern_token
	.long	style_token
	.long	symbol_token
	.long	text_path_token
	.long	tref_token
	.long	view_token
	.long	vkern_token
	.long	0
%endif


svg_media_property_token_table:
	.long	audio_level_token
	.long	buffered_rendering_token
	.long	display_token
	.long	image_rendering_token
	.long	pointer_events_token
	.long	shape_rendering_token
	.long	text_rendering_token
	.long	viewport_fill_token
	.long	viewport_fill_opacity_token
	.long	visibility_token
	.long	0


xml_token_table:
	.long	encoding_token
	.long	standalone_token
	.long	version_token
	.long	slash_token
	.long	0


link_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	external_resources_required_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	id_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	target_token
	.long	transform_token
	.long	typeof_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.long	xlink_role_token
	.long	xlink_show_token
	.long	xlink_title_token
	.long	xlink_type_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


animate_token_table:
	.long	about_token
	.long	accumulate_token
	.long	additive_token
	.long	attribute_name_token
	.long	attribute_type_token
	.long	begin_token
	.long	by_token
	.long	calc_mode_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	dur_token
	.long	end_token
	.long	fill_token
	.long	from_token
	.long	id_token
	.long	key_splines_token
	.long	key_times_token
	.long	max_token
	.long	min_token
	.long	property_token
	.long	rel_token
	.long	repeat_count_token
	.long	repeat_dur_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	restart_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	to_token
	.long	typeof_token
	.long	values_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.long	xlink_role_token
	.long	xlink_show_token
	.long	xlink_title_token
	.long	xlink_type_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


animate_color_token_table:
	.long	about_token
	.long	accumulate_token
	.long	additive_token
	.long	attribute_name_token
	.long	attribute_type_token
	.long	begin_token
	.long	by_token
	.long	calc_mode_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	dur_token
	.long	end_token
	.long	fill_token
	.long	from_token
	.long	id_token
	.long	key_splines_token
	.long	key_times_token
	.long	max_token
	.long	min_token
	.long	property_token
	.long	rel_token
	.long	repeat_count_token
	.long	repeat_dur_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	restart_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	to_token
	.long	typeof_token
	.long	values_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.long	xlink_role_token
	.long	xlink_show_token
	.long	xlink_title_token
	.long	xlink_type_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


animate_motion_token_table:
	.long	about_token
	.long	accumulate_token
	.long	additive_token
	.long	begin_token
	.long	by_token
	.long	calc_mode_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	dur_token
	.long	end_token
	.long	fill_token
	.long	from_token
	.long	id_token
	.long	key_points_token
	.long	key_splines_token
	.long	key_times_token
	.long	max_token
	.long	min_token
	.long	origin_token
	.long	path_token
	.long	property_token
	.long	rel_token
	.long	repeat_count_token
	.long	repeat_dur_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	restart_token
	.long	rev_token
	.long	role_token
	.long	rotate_token
	.long	system_language_token
	.long	to_token
	.long	typeof_token
	.long	values_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.long	xlink_role_token
	.long	xlink_show_token
	.long	xlink_title_token
	.long	xlink_type_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


animate_transform_token_table:
	.long	about_token
	.long	accumulate_token
	.long	additive_token
	.long	attribute_name_token
	.long	attribute_type_token
	.long	begin_token
	.long	by_token
	.long	calc_mode_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	dur_token
	.long	end_token
	.long	fill_token
	.long	from_token
	.long	id_token
	.long	key_splines_token
	.long	key_times_token
	.long	max_token
	.long	min_token
	.long	property_token
	.long	rel_token
	.long	repeat_count_token
	.long	repeat_dur_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	restart_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	to_token
	.long	type_token
	.long	typeof_token
	.long	values_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.long	xlink_role_token
	.long	xlink_show_token
	.long	xlink_title_token
	.long	xlink_type_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


animation_token_table:
	.long	about_token
	.long	begin_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	dur_token
	.long	end_token
	.long	external_resources_required_token
	.long	fill_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	height_token
	.long	id_token
	.long	initial_visibility_token
	.long	max_token
	.long	min_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	preserve_aspect_ratio_token
	.long	property_token
	.long	rel_token
	.long	repeat_count_token
	.long	repeat_dur_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	restart_token
	.long	rev_token
	.long	role_token
	.long	sync_behavior_token
	.long	sync_master_token
	.long	sync_tolerance_token
	.long	system_language_token
	.long	transform_token
	.long	typeof_token
	.long	width_token
	.long	x_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.long	xlink_role_token
	.long	xlink_show_token
	.long	xlink_title_token
	.long	xlink_type_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	y_token
	.long	slash_token
	.long	0


audio_token_table:
	.long	about_token
	.long	begin_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	dur_token
	.long	end_token
	.long	external_resources_required_token
	.long	fill_token
	.long	id_token
	.long	max_token
	.long	min_token
	.long	property_token
	.long	rel_token
	.long	repeat_count_token
	.long	repeat_dur_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	restart_token
	.long	rev_token
	.long	role_token
	.long	sync_behavior_token
	.long	sync_master_token
	.long	sync_tolerance_token
	.long	system_language_token
	.long	type_token
	.long	typeof_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.long	xlink_role_token
	.long	xlink_show_token
	.long	xlink_title_token
	.long	xlink_type_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


circle_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	cx_token
	.long	cy_token
	.long	datatype_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	id_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	property_token
	.long	r_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	transform_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


defs_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	id_token
	.long	property_token
	.long	rel_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


desc_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	id_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


discard_token_table:
	.long	about_token
	.long	begin_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	id_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.byte	system_language_token
	.long	typeof_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.byte	xlink_role_token
	.byte	xlink_show_token
	.byte	xlink_title_token
	.byte	xlink_type_token
	.byte	xml_base_token
	.byte	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


ellipse_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	cx_token
	.long	cy_token
	.long	datatype_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	id_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	rx_token
	.long	ry_token
	.long	system_language_token
	.long	transform_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


font_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	external_resources_required_token
	.long	horiz_adv_x_token
	.long	horiz_origin_x_token
	.long	id_token
	.long	property_token
	.long	rel_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


font_face_token_table:
	.long	about_token
	.long	accent_height_token
	.long	alphabetic_token
	.long	ascent_token
	.long	bbox_token
	.long	cap_height_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	descent_token
	.long	external_resources_required_token
	.long	font_family_token
	.long	font_stretch_token
	.long	font_style_token
	.long	font_variant_token
	.long	font_weight_token
	.long	hanging_token
	.long	id_token
	.long	ideographic_token
	.long	mathematical_token
	.long	overline_position_token
	.long	overline_thickness_token
	.long	panose_1_token
	.long	property_token
	.long	rel_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	slope_token
	.long	stemh_token
	.long	stemv_token
	.long	strikethrough_position_token
	.long	strikethrough_thickness_token
	.long	typeof_token
	.long	underline_position_token
	.long	underline_thickness_token
	.long	unicode_range_token
	.long	units_per_em_token
	.long	widths_token
	.long	x_height_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


font_face_src_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	id_token
	.long	property_token
	.long	rel_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


font_face_uri_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	external_resources_required_token
	.long	id_token
	.long	property_token
	.long	rel_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	typeof_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.long	xlink_role_token
	.long	xlink_show_token
	.long	xlink_title_token
	.long	xlink_type_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


foreign_object_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	external_resources_required_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	height_token
	.long	id_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	transform_token
	.long	typeof_token
	.long	width_token
	.long	x_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.long	xlink_role_token
	.long	xlink_show_token
	.long	xlink_title_token
	.long	xlink_type_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	y_token
	.long	slash_token
	.long	0


group_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	external_resources_required_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	id_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	transform_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


glyph_token_table:
	.long	about_token
	.long	arabic_form_token
	.long	class_token
	.long	content_token
	.long	d_token
	.long	datatype_token
	.long	glyph_name_token
	.long	horiz_adv_x_token
	.long	id_token
	.long	lang_token
	.long	property_token
	.long	rel_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	typeof_token
	.long	unicode_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


handler_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	ev_event_token
	.long	external_resources_required_token
	.long	id_token
	.long	property_token
	.long	rel_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	type_token
	.long	typeof_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.long	xlink_role_token
	.long	xlink_show_token
	.long	xlink_title_token
	.long	xlink_type_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


hkern_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	g1_token
	.long	g2_token
	.long	id_token
	.long	k_token
	.long	property_token
	.long	rel_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	typeof_token
	.long	u1_token
	.long	u2_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


image_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	external_resources_required_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	height_token
	.long	id_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	opacity_token
	.long	preserve_aspect_ratio_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	transform_token
	.long	type_token
	.long	typeof_token
	.long	width_token
	.long	x_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.long	xlink_role_token
	.long	xlink_show_token
	.long	xlink_title_token
	.long	xlink_type_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	y_token
	.long	slash_token
	.long	0


line_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	id_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	transform_token
	.long	typeof_token
	.long	x1_token
	.long	x2_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	y1_token
	.long	y2_token
	.long	slash_token
	.long	0


linear_gradient_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	gradient_units_token
	.long	id_token
	.long	property_token
	.long	rel_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	typeof_token
	.long	x1_token
	.long	x2_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	y1_token
	.long	y2_token
	.long	slash_token
	.long	0


listener_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	default_action_token
	.long	event_token
	.long	handler_token
	.long	id_token
	.long	observer_token
	.long	phase_token
	.long	propagate_token
	.long	property_token
	.long	rel_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	target_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


metadata_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	id_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


missing_glyph_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	d_token
	.long	datatype_token
	.long	horiz_adv_x_token
	.long	id_token
	.long	property_token
	.long	rel_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


mpath_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	id_token
	.long	property_token
	.long	rel_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	typeof_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.long	xlink_role_token
	.long	xlink_show_token
	.long	xlink_title_token
	.long	xlink_type_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


path_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	d_token
	.long	datatype_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	id_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	path_length_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	transform_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


polygon_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	id_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	points_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	transform_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


polyline_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	id_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	points_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	transform_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


prefetch_token_table:
	.long	about_token
	.long	bandwidth_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	id_token
	.long	media_character_encoding_token
	.long	media_content_encoding_token
	.long	media_size_token
	.long	media_time_token
	.long	property_token
	.long	rel_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	typeof_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.long	xlink_role_token
	.long	xlink_show_token
	.long	xlink_title_token
	.long	xlink_type_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


radial_gradient_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	cx_token
	.long	cy_token
	.long	datatype_token
	.long	gradient_units_token
	.long	id_token
	.long	property_token
	.long	r_token
	.long	rel_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


rect_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	height_token
	.long	id_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	rx_token
	.long	ry_token
	.long	system_language_token
	.long	transform_token
	.long	typeof_token
	.long	width_token
	.long	x_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	y_token
	.long	slash_token
	.long	0


script_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	external_resources_required_token
	.long	id_token
	.long	property_token
	.long	rel_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	type_token
	.long	typeof_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.long	xlink_role_token
	.long	xlink_show_token
	.long	xlink_title_token
	.long	xlink_type_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


set_token_table:
	.long	about_token
	.long	attribute_name_token
	.long	attribute_type_token
	.long	begin_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	dur_token
	.long	end_token
	.long	fill_token
	.long	id_token
	.long	max_token
	.long	min_token
	.long	property_token
	.long	rel_token
	.long	repeat_count_token
	.long	repeat_dur_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	to_token
	.long	typeof_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.long	xlink_role_token
	.long	xlink_show_token
	.long	xlink_title_token
	.long	xlink_type_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


switch_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	external_resources_required_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	id_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	transform_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


tbreak_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	id_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


text_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	editable_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	id_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	rotate_token
	.long	system_language_token
	.long	transform_token
	.long	typeof_token
	.long	x_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	y_token
	.long	slash_token
	.long	0


text_area_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	editable_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	height_token
	.long	id_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	transform_token
	.long	typeof_token
	.long	width_token
	.long	x_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	y_token
	.long	slash_token
	.long	0


title_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	id_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


tspan_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	id_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	typeof_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	slash_token
	.long	0


use_token_table:
	.long	about_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	external_resources_required_token
	.long	focus_highlight_token
	.long	focusable_token
	.long	id_token
	.long	nav_down_token
	.long	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	property_token
	.long	rel_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	rev_token
	.long	role_token
	.long	system_language_token
	.long	transform_token
	.long	typeof_token
	.long	x_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.long	xlink_role_token
	.long	xlink_show_token
	.long	xlink_title_token
	.long	xlink_type_token
	.long	xml_base_token
	.byte	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	y_token
	.long	slash_token
	.long	0

video_token_table:
	.long	about_token
	.long	begin_token
	.long	class_token
	.long	content_token
	.long	datatype_token
	.long	dur_token
	.long	end_token
	.byte	external_resources_required_token
	.byte	fill_token
	.byte	focus_highlight_token
	.byte	focusable_token
	.byte	height_token
	.byte	id_token
	.byte	initial_visibility_token
	.byte	max_token
	.byte	min_token
	.byte	nav_down_token
	.byte	nav_down_left_token
	.long	nav_down_right_token
	.long	nav_left_token
	.long	nav_next_token
	.long	nav_prev_token
	.long	nav_right_token
	.long	nav_up_token
	.long	nav_up_left_token
	.long	nav_up_right_token
	.long	overlay_token
	.long	preserve_aspect_ratio_token
	.long	property_token
	.long	rel_token
	.long	repeat_count_token
	.long	repeat_dur_token
	.long	required_extensions_token
	.long	required_features_token
	.long	required_fonts_token
	.long	required_formats_token
	.long	resource_token
	.long	restart_token
	.long	rev_token
	.long	role_token
	.long	sync_behavior_token
	.long	sync_master_token
	.long	sync_tolerance_token
	.long	system_language_token
	.long	transform_token
	.long	transform_behavior_token
	.long	type_token
	.long	typeof_token
	.long	width_token
	.long	x_token
	.long	xlink_actuate_token
	.long	xlink_arcrole_token
	.long	xlink_href_token
	.long	xlink_role_token
	.long	xlink_show_token
	.long	xlink_title_token
	.long	xlink_type_token
	.long	xml_base_token
	.long	xml_id_token
	.long	xml_lang_token
	.long	xml_space_token
	.long	y_token
	.long	slash_token
	.long	0


svg_token_lists:
	.long	xml_token_table
	.long	link_token_table
	.long	animate_token_table
	.long	animate_color_token_table
	.long	animate_motion_token_table
	.long	animate_transform_token_table
	.long	animation_token_table
	.long	audio_token_table
	.long	circle_token_table
	.long	defs_token_table
	.long	desc_token_table
	.long	discard_token_table
	.long	ellipse_token_table
	.long	font_token_table
	.long	font_face_token_table
	.long	font_face_src_token_table
	.long	font_face_uri_token_table
	.long	foreign_object_token_table
	.long	group_token_table
	.long	glyph_token_table
	.long	handler_token_table
	.long	hkern_token_table
	.long	image_token_table
	.long	line_token_table
	.long	linear_gradient_token_table
	.long	listener_token_table
	.long	metadata_token_table
	.long	missing_glyph_token_table
	.long	mpath_token_table
	.long	path_token_table
	.long	polygon_token_table
	.long	polyline_token_table
	.long	prefetch_token_table
	.long	radial_gradient_token_table
	.long	rect_token_table
	.long	script_token_table
	.long	set_token_table
	.long	solid_color_token_table
	.long	stop_token_table
	.long	svg_token_table
	.long	switch_token_table
	.long	tbreak_token_table
	.long	text_token_table
	.long	text_area_token_table
	.long	title_token_table
	.long	tspan_token_table
	.long	use_token_table
	.long	video_token_table
	.long	0

; ------------------------------------------------------------------------------
;                            FILE FORMAT DATA
; ------------------------------------------------------------------------------

%macro	csv_comment	1

	.byte	34, "#", 34, ", ", 34, %1, 34, 10

%endmacro

; ------------------------------------------------------------------------------
; TODO: This list needs reviewed in case some stitch formats
; also can contain object data (EMBFORMAT_STCHANDOBJ).

%define STITCHONLY	1
%define OBJECTONLY	2
%define STCHANDOBJ	2

%macro	format_entry	5

%%startofext:
	.byte	%1
%%endofext:
	times	6 + %%startofext - %%endofext db 0

%%startofstr:
	.byte	%2
%%endofstr:
	times	50 + %%startofstr - %%endofstr db 0

	.byte	%3, %4, %5

%endmacro

; ------------------------------------------------------------------------------

format_list:
	format_entry	".10o", "Toyota Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".100", "Toyota Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".art", "Bernina Embroidery Format", ' ', ' ', STITCHONLY
	format_entry	".bmc", "Bitmap Cache Embroidery Format", ' ', ' ', STITCHONLY
	format_entry	".bro", "Bits & Volts Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".cnd", "Melco Embroidery Format", ' ', ' ', STITCHONLY
	format_entry	".col", "Embroidery .byte Color Format", 'U', 'U', STITCHONLY
	format_entry	".csd", "Singer Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".csv", "Comma Separated Values Format", 'U', 'U', STITCHONLY
	format_entry	".dat", "Barudan Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".dem", "Melco Embroidery Format", ' ', ' ', STITCHONLY
	format_entry	".dsb", "Barudan Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".dst", "Tajima Embroidery Format", 'U', 'U', STITCHONLY
	format_entry	".dsz", "ZSK USA Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".dxf", "Drawing Exchange Format", ' ', ' ', OBJECTONLY
	format_entry	".edr", "Embird Embroidery Format", 'U', 'U', STITCHONLY
	format_entry	".emd", "Elna Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".exp", "Melco Embroidery Format", 'U', 'U', STITCHONLY
	format_entry	".exy", "Eltac Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".eys", "Sierra Expanded Embroidery Format", ' ', ' ', STITCHONLY
	format_entry	".fxy", "Fortron Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".gc", "Smoothie G-Code Format", ' ', ' ', STITCHONLY
	format_entry	".gnc", "Great Notions Embroidery Format", ' ', ' ', STITCHONLY
	format_entry	".gt", "Gold .byte Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".hus", "Husqvarna Viking Embroidery Format", 'U', 'U', STITCHONLY
	format_entry	".inb", "Inbro Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".inf", "Embroidery Color Format", 'U', 'U', STITCHONLY
	format_entry	".jef", "Janome Embroidery Format", 'U', 'U', STITCHONLY
	format_entry	".ksm", "Pfaff Embroidery Format", 'U', 'U', STITCHONLY
	format_entry	".max", "Pfaff Embroidery Format", 'U', 'U', STITCHONLY
	format_entry	".mit", "Mitsubishi Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".new", "Ameco Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".ofm", "Melco Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".pcd", "Pfaff Embroidery Format", 'U', 'U', STITCHONLY
	format_entry	".pcm", "Pfaff Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".pcq", "Pfaff Embroidery Format", 'U', 'U', STITCHONLY
	format_entry	".pcs", "Pfaff Embroidery Format", 'U', 'U', STITCHONLY
	format_entry	".pec", "Brother Embroidery Format", 'U', 'U', STITCHONLY
	format_entry	".pel", "Brother Embroidery Format", ' ', ' ', STITCHONLY
	format_entry	".pem", "Brother Embroidery Format", ' ', ' ', STITCHONLY
	format_entry	".pes", "Brother Embroidery Format", 'U', 'U', STITCHONLY
	format_entry	".phb", "Brother Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".phc", "Brother Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".plt", "AutoCAD Plot Drawing Format", 'U', 'U', STITCHONLY
	format_entry	".rgb", "RGB Embroidery Format", 'U', 'U', STITCHONLY
	format_entry	".sew", "Janome Embroidery Format", 'U', 'U', STITCHONLY
	format_entry	".shv", "Husqvarna Viking Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".sst", "Sunstar Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".stx", "Data Stitch Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".svg", "Scalable Vector Graphics", 'U', 'U', OBJECTONLY
	format_entry	".t01", "Pfaff Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".t09", "Pfaff Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".tap", "Happy Embroidery Format", 'U', 'U', STITCHONLY
	format_entry	".thr", "ThredWorks Embroidery Format", 'U', 'U', STITCHONLY
	format_entry	".txt", "Text File", ' ', 'U', STITCHONLY
	format_entry	".u00", "Barudan Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".u01", "Barudan Embroidery Format", ' ', ' ', STITCHONLY
	format_entry	".vip", "Pfaff Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".vp3", "Pfaff Embroidery Format", 'U', 'U', STITCHONLY
	format_entry	".xxx", "Singer Embroidery Format", 'U', 'U', STITCHONLY
	format_entry	".zsk", "ZSK USA Embroidery Format", 'U', ' ', STITCHONLY


stitch_labels:
	.long	stitch_token
	.long	jump_token
	.long	trim_token
	.long	st_color_token
	.long	st_end_token
	.long	unknown_token
	.long	0

stitch_token:
	.string	"STITCH"
jump_token:
	.string	"JUMP"
trim_token:
	.string	"TRIM"
st_color_token:
	.string	"COLOR"
st_end_token:
	.string	"END"
unknown_token:
	.string	"UNKNOWN"


csv_header:
	csv_comment	"Embroidermodder 2 CSV Embroidery File"
	csv_comment	"http://embroidermodder.github.io"
	.byte	10
	csv_comment	"General Notes:"
	csv_comment	"This file can be read by Excel or LibreOffice as CSV (Comma Separated Value) or with a text editor."
	csv_comment	"Lines beginning with # are comments."
	csv_comment	"Lines beginning with > are variables: [VAR_NAME], [VAR_VALUE]"
	csv_comment	"Lines beginning with $ are .bytes: [.byte_NUMBER], [RED], [GREEN], [BLUE], [DESCRIPTION], [CATALOG_NUMBER]"
	csv_comment	"Lines beginning with * are stitch entries: [STITCH_TYPE], [X], [Y]"
	.byte	10
	csv_comment	"Stitch Entry Notes:"
	csv_comment	"STITCH instructs the machine to move to the position [X][Y] and then make a stitch."
	csv_comment	"JUMP instructs the machine to move to the position [X][Y] without making a stitch."
	csv_comment	"TRIM instructs the machine to cut the .byte before moving to the position [X][Y] without making a stitch."
	csv_comment	"COLOR instructs the machine to stop temporarily so that the user can change to a different color .byte before resuming."
	csv_comment	"END instructs the machine that the design is completed and there are no further instructions."
	csv_comment	"UNKNOWN encompasses instructions that may not be supported currently."
	csv_comment	"[X] and [Y] are absolute coordinates in millimeters (mm)."
	.byte	10, 0


csd_decoding_table:
	.byte	0x43, 0x6E, 0x72, 0x7A, 0x76, 0x6C, 0x61, 0x6F, 0x7C, 0x29, 0x5D, 0x62, 0x60, 0x6E, 0x61, 0x62
	.byte	0x20, 0x41, 0x66, 0x6A, 0x3A, 0x35, 0x5A, 0x63, 0x7C, 0x37, 0x3A, 0x2A, 0x25, 0x24, 0x2A, 0x33
	.byte	0x00, 0x10, 0x14, 0x03, 0x72, 0x4C, 0x48, 0x42, 0x08, 0x7A, 0x5E, 0x0B, 0x6F, 0x45, 0x47, 0x5F
	.byte	0x40, 0x54, 0x5C, 0x57, 0x55, 0x59, 0x53, 0x3A, 0x32, 0x6F, 0x53, 0x54, 0x50, 0x5C, 0x4A, 0x56
	.byte	0x2F, 0x2F, 0x62, 0x2C, 0x22, 0x65, 0x25, 0x28, 0x38, 0x30, 0x38, 0x22, 0x2B, 0x25, 0x3A, 0x6F
	.byte	0x27, 0x38, 0x3E, 0x3F, 0x74, 0x37, 0x33, 0x77, 0x2E, 0x30, 0x3D, 0x34, 0x2E, 0x32, 0x2B, 0x2C
	.byte	0x0C, 0x18, 0x42, 0x13, 0x16, 0x0A, 0x15, 0x02, 0x0B, 0x1C, 0x1E, 0x0E, 0x08, 0x60, 0x64, 0x0D
	.byte	0x09, 0x51, 0x25, 0x1A, 0x18, 0x16, 0x19, 0x1A, 0x58, 0x10, 0x14, 0x5B, 0x08, 0x15, 0x1B, 0x5F
	.byte	0xD5, 0xD2, 0xAE, 0xA3, 0xC1, 0xF0, 0xF4, 0xE8, 0xF8, 0xEC, 0xA6, 0xAB, 0xCD, 0xF8, 0xFD, 0xFB
	.byte	0xE2, 0xF0, 0xFE, 0xFA, 0xF5, 0xB5, 0xF7, 0xF9, 0xFC, 0xB9, 0xF5, 0xEF, 0xF4, 0xF8, 0xEC, 0xBF
	.byte	0xC3, 0xCE, 0xD7, 0xCD, 0xD0, 0xD7, 0xCF, 0xC2, 0xDB, 0xA4, 0xA0, 0xB0, 0xAF, 0xBE, 0x98, 0xE2
	.byte	0xC2, 0x91, 0xE5, 0xDC, 0xDA, 0xD2, 0x96, 0xC4, 0x98, 0xF8, 0xC9, 0xD2, 0xDD, 0xD3, 0x9E, 0xDE
	.byte	0xAE, 0xA5, 0xE2, 0x8C, 0xB6, 0xAC, 0xA3, 0xA9, 0xBC, 0xA8, 0xA6, 0xEB, 0x8B, 0xBF, 0xA1, 0xAC
	.byte	0xB5, 0xA3, 0xBB, 0xB6, 0xA7, 0xD8, 0xDC, 0x9A, 0xAA, 0xF9, 0x82, 0xFB, 0x9D, 0xB9, 0xAB, 0xB3
	.byte	0x94, 0xC1, 0xA0, 0x8C, 0x8B, 0x8E, 0x95, 0x8F, 0x87, 0x99, 0xE7, 0xE1, 0xA3, 0x83, 0x8B, 0xCF
	.byte	0xA3, 0x85, 0x9D, 0x83, 0xD4, 0xB7, 0x83, 0x84, 0x91, 0x97, 0x9F, 0x88, 0x8F, 0xDD, 0xAD, 0x90


vip_decoding_table:
	.byte	0x2E, 0x82, 0xE4, 0x6F, 0x38, 0xA9, 0xDC, 0xC6, 0x7B, 0xB6, 0x28, 0xAC, 0xFD, 0xAA, 0x8A, 0x4E
	.byte	0x76, 0x2E, 0xF0, 0xE4, 0x25, 0x1B, 0x8A, 0x68, 0x4E, 0x92, 0xB9, 0xB4, 0x95, 0xF0, 0x3E, 0xEF
	.byte	0xF7, 0x40, 0x24, 0x18, 0x39, 0x31, 0xBB, 0xE1, 0x53, 0xA8, 0x1F, 0xB1, 0x3A, 0x07, 0xFB, 0xCB
	.byte	0xE6, 0x00, 0x81, 0x50, 0x0E, 0x40, 0xE1, 0x2C, 0x73, 0x50, 0x0D, 0x91, 0xD6, 0x0A, 0x5D, 0xD6
	.byte	0x8B, 0xB8, 0x62, 0xAE, 0x47, 0x00, 0x53, 0x5A, 0xB7, 0x80, 0xAA, 0x28, 0xF7, 0x5D, 0x70, 0x5E
	.byte	0x2C, 0x0B, 0x98, 0xE3, 0xA0, 0x98, 0x60, 0x47, 0x89, 0x9B, 0x82, 0xFB, 0x40, 0xC9, 0xB4, 0x00
	.byte	0x0E, 0x68, 0x6A, 0x1E, 0x09, 0x85, 0xC0, 0x53, 0x81, 0xD1, 0x98, 0x89, 0xAF, 0xE8, 0x85, 0x4F
	.byte	0xE3, 0x69, 0x89, 0x03, 0xA1, 0x2E, 0x8F, 0xCF, 0xED, 0x91, 0x9F, 0x58, 0x1E, 0xD6, 0x84, 0x3C
	.byte	0x09, 0x27, 0xBD, 0xF4, 0xC3, 0x90, 0xC0, 0x51, 0x1B, 0x2B, 0x63, 0xBC, 0xB9, 0x3D, 0x40, 0x4D
	.byte	0x62, 0x6F, 0xE0, 0x8C, 0xF5, 0x5D, 0x08, 0xFD, 0x3D, 0x50, 0x36, 0xD7, 0xC9, 0xC9, 0x43, 0xE4
	.byte	0x2D, 0xCB, 0x95, 0xB6, 0xF4, 0x0D, 0xEA, 0xC2, 0xFD, 0x66, 0x3F, 0x5E, 0xBD, 0x69, 0x06, 0x2A
	.byte	0x03, 0x19, 0x47, 0x2B, 0xDF, 0x38, 0xEA, 0x4F, 0x80, 0x49, 0x95, 0xB2, 0xD6, 0xF9, 0x9A, 0x75
	.byte	0xF4, 0xD8, 0x9B, 0x1D, 0xB0, 0xA4, 0x69, 0xDB, 0xA9, 0x21, 0x79, 0x6F, 0xD8, 0xDE, 0x33, 0xFE
	.byte	0x9F, 0x04, 0xE5, 0x9A, 0x6B, 0x9B, 0x73, 0x83, 0x62, 0x7C, 0xB9, 0x66, 0x76, 0xF2, 0x5B, 0xC9
	.byte	0x5E, 0xFC, 0x74, 0xAA, 0x6C, 0xF1, 0xCD, 0x93, 0xCE, 0xE9, 0x80, 0x53, 0x03, 0x3B, 0x97, 0x4B
	.byte	0x39, 0x76, 0xC2, 0xC1, 0x56, 0xCB, 0x70, 0xFD, 0x3B, 0x3E, 0x52, 0x57, 0x81, 0x5D, 0x56, 0x8D
	.byte	0x51, 0x90, 0xD4, 0x76, 0xD7, 0xD5, 0x16, 0x02, 0x6D, 0xF2, 0x4D, 0xE1, 0x0E, 0x96, 0x4F, 0xA1
	.byte	0x3A, 0xA0, 0x60, 0x59, 0x64, 0x04, 0x1A, 0xE4, 0x67, 0xB6, 0xED, 0x3F, 0x74, 0x20, 0x55, 0x1F
	.byte	0xFB, 0x23, 0x92, 0x91, 0x53, 0xC8, 0x65, 0xAB, 0x9D, 0x51, 0xD6, 0x73, 0xDE, 0x01, 0xB1, 0x80
	.byte	0xB7, 0xC0, 0xD6, 0x80, 0x1C, 0x2E, 0x3C, 0x83, 0x63, 0xEE, 0xBC, 0x33, 0x25, 0xE2, 0x0E, 0x7A
	.byte	0x67, 0xDE, 0x3F, 0x71, 0x14, 0x49, 0x9C, 0x92, 0x93, 0x0D, 0x26, 0x9A, 0x0E, 0xDA, 0xED, 0x6F
	.byte	0xA4, 0x89, 0x0C, 0x1B, 0xF0, 0xA1, 0xDF, 0xE1, 0x9E, 0x3C, 0x04, 0x78, 0xE4, 0xAB, 0x6D, 0xFF
	.byte	0x9C, 0xAF, 0xCA, 0xC7, 0x88, 0x17, 0x9C, 0xE5, 0xB7, 0x33, 0x6D, 0xDC, 0xED, 0x8F, 0x6C, 0x18
	.byte	0x1D, 0x71, 0x06, 0xB1, 0xC5, 0xE2, 0xCF, 0x13, 0x77, 0x81, 0xC5, 0xB7, 0x0A, 0x14, 0x0A, 0x6B
	.byte	0x40, 0x26, 0xA0, 0x88, 0xD1, 0x62, 0x6A, 0xB3, 0x50, 0x12, 0xB9, 0x9B, 0xB5, 0x83, 0x9B, 0x37


max_header:
	.byte	0x56, 0x43, 0x53, 0x4D, 0xFC, 0x03, 0x00, 0x00
	.byte	0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte	0xF6, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte	0x08, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	.byte	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte	0x00, 0x00, 0x00, 0x00, 0x31, 0x33, 0x37, 0x38
	.byte	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte	0x4D, 0x61, 0x64, 0x65, 0x69, 0x72, 0x61, 0x20
	.byte	0x52, 0x61, 0x79, 0x6F, 0x6E, 0x20, 0x34, 0x30
	.byte	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte	0x01, 0x38, 0x09, 0x31, 0x33, 0x30, 0x2F, 0x37
	.byte	0x30, 0x35, 0x20, 0x48, 0xFA, 0x00, 0x00, 0x00
	.byte	0x00, 0x00, 0x00, 0x00, 0x00


image_frame:
	.byte	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.byte	0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0
	.byte	0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0
	.byte	0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	.byte	0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0
	.byte	0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0
	.byte	0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0
	.byte	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0


/* ------------------------------------------------------------------------------
*                              THREAD TABLES
 ------------------------------------------------------------------------------*/

/*
    Converted from the table at:
 	 https://www.w3.org/TR/SVGb/types.html#ColorKeywords
    NOTE: This supports both UK and US English names,
    so the repeated values aren't an error.
*/
svg_color_codes:
	.byte	"aliceblue", 0xf0, 0xf8, 0xff, 0
	.byte	"antiquewhite", 0xfa, 0xeb, 0xd7, 1
	.byte	"aqua", 0x00, 0xff, 0xff, 2
	.byte	"aquamarine", 0x7f, 0xff, 0xd4, 3
	.byte	"azure", 0xf0, 0xff, 0xff, 4
	.byte	"beige", 0xf5, 0xf5, 0xdc, 5
	.byte	"bisque", 0xff, 0xe4, 0xc4, 6
	.byte	"black", 0x00, 0x00, 0x00, 7
	.byte	"blanchedalmond", 0xff, 0xeb, 0xcd, 8
	.byte	"blue", 0x00, 0x00, 0xff, 9
	.byte	"blueviolet", 0x8a, 0x2b, 0xe2, 10
	.byte	"brown", 0xa5, 0x2a, 0x2a, 11
	.byte	"burlywood", 0xde, 0xb8, 0x1b, 12
	.byte	"cadetblue", 0x5f, 0x9e, 0xa0, 13
	.byte	"chartreuse", 0x7f, 0xff, 0x00, 14
	.byte	"chocolate", 0xd2, 0x2d, 0x1e, 15
	.byte	"coral", 0xFF, 0x7f, 0x0e, 16
	.byte	"cornflowerblue", 0x1c, 0x5f, 0xed, 17
	.byte	"cornsilk", 0xff, 0xf8, 0xdc, 18
	.byte	"crimson", 0xdc, 0x0e, 0x3c, 19
	.byte	"cyan", 0x00, 0xff, 0xff, 20
	.byte	"darkblue", 0x00, 0x00, 0x8b, 21
	.byte	"darkcyan", 0x00, 0x8b, 0x8b, 22
	.byte	"darkgoldenrod", 0xb8, 0x1a, 0x0b, 23
	.byte	"darkgray", 0xa9, 0xa9, 0xa9, 24
	.byte	"darkgreen", 0x00, 0x1c, 0x00, 25
	.byte	"darkgrey", 0xa9, 0xa9, 0xa9, 26
	.byte	"darkkhaki", 0xbd, 0xb7, 0x6b, 27
	.byte	"darkmagenta", 0x8b, 0x00, 0x8b, 28
	.byte	"darkolivegreen", 0x0d, 0x6b, 0x2f, 29
	.byte	"darkorange", 0xff, 0x8c, 0x00, 30
	.byte	"darkorchid", 0x3f, 0x0e, 0xcc, 31
	.byte	"darkred", 0x8b, 0x00, 0x00, 32
	.byte	"darksalmon", 0xe9, 0x3c, 0x7a, 33
	.byte	"darkseagreen", 0x8f, 0xbc, 0x8f, 34
	.byte	"darkslateblue", 0x1e, 0x3d, 0x8b, 35
	.byte	"darkslategray", 0x2f, 0x4f, 0x4f, 36
	.byte	"darkslategrey", 0x2f, 0x4f, 0x4f, 37
	.byte	"darkturquoise", 0x00, 0xce, 0xd1, 38
	.byte	"darkviolet", 0x5e, 0x00, 0xd3, 39
	.byte	"deeppink", 0xff, 0x0e, 0x5d, 40
	.byte	"deepskyblue", 0x00, 0xbf, 0xff, 41
	.byte	"dimgray", 0x2d, 0x2d, 0x2d, 42
	.byte	"dimgrey", 0x2d, 0x2d, 0x2d, 43
	.byte	"dodgerblue", 0x1e, 0x5a, 0xff, 44
	.byte	"firebrick", 0xb2, 0x0a, 0x0a, 45
	.byte	"floralwhite", 0xff, 0xfa, 0xf0, 46
	.byte	"forestgreen", 0x0a, 0x8b, 0x0a, 47
	.byte	"fuchsia", 0xff, 0x00, 0xff, 48
	.byte	"gainsboro", 0xdc, 0xdc, 0xdc, 49
	.byte	"ghostwhite", 0xf8, 0xf8, 0xff, 50
	.byte	"gold", 0xff, 0xd7, 0x00, 51
	.byte	"goldenrod", 0xda, 0xa5, 0x0e, 52
	.byte	"gray", 0x0e, 0x0e, 0x0e, 53
	.byte	"grey", 0x0e, 0x0e, 0x0e, 54
	.byte	"green", 0x00, 0x0e, 0x00, 55
	.byte	"greenyellow", 0xad, 0xff, 0x2f, 56
	.byte	"honeydew", 0xf0, 0xff, 0xf0, 57
	.byte	"hotpink", 0xff, 0x2d, 0xb4, 58
	.byte	"indianred", 0xcd, 0x5c, 0x5c, 59
	.byte	"indigo", 0x4b, 0x00, 0x0a, 60
	.byte	"ivory", 0xff, 0xff, 0xf0, 61
	.byte	"khaki", 0xf0, 0xe6, 0x8c, 62
	.byte	"lavender", 0xe6, 0xe6, 0xfa, 63
	.byte	"lavenderblush", 0xff, 0xf0, 0xf5, 64
	.byte	"lawngreen", 0x7c, 0xfc, 0x00, 65
	.byte	"lemonchiffon", 0xff, 0xfa, 0xcd, 66
	.byte	"lightblue", 0xad, 0xd8, 0xe6, 67
	.byte	"lightcoral", 0xf0, 0x0e, 0x0e, 68
	.byte	"lightcyan", 0xe0, 0xff, 0xff, 69
	.byte	"lightgoldenrodyellow", 0xfa, 0xfa, 0xd2, 70
	.byte	"lightgray", 0xd3, 0xd3, 0xd3, 71
	.byte	"lightgreen", 0x5a, 0xee, 0x5a, 72
	.byte	"lightgrey", 0xd3, 0xd3, 0xd3, 73
	.byte	"lightpink", 0xff, 0xb6, 0xc1, 74
	.byte	"lightsalmon", 0xff, 0xa0, 0x7a, 75
	.byte	"lightseagreen", 0x0e, 0xb2, 0xaa, 76
	.byte	"lightskyblue", 0x1b, 0xce, 0xfa, 77
	.byte	"lightslategray", 0x4d, 0x3a, 0x3f, 78
	.byte	"lightslategrey", 0x4d, 0x3a, 0x3f, 79
	.byte	"lightsteelblue", 0xb0, 0xc4, 0xde, 80
	.byte	"lightyellow", 0xff, 0xff, 0xe0, 81
	.byte	"lime", 0x00, 0xff, 0x00, 82
	.byte	"limegreen", 0x0e, 0xcd, 0x0e, 83
	.byte	"linen", 0xfa, 0xf0, 0xe6, 84
	.byte	"magenta", 0xff, 0x00, 0xff, 85
	.byte	"maroon", 0x0e, 0x00, 0x00, 86
	.byte	"mediumaquamarine", 0x2a, 0xcd, 0xaa, 87
	.byte	"mediumblue", 0x00, 0x00, 0xcd, 88
	.byte	"mediumorchid", 0xba, 0x0d, 0xd3, 89
	.byte	"mediumpurple", 0x5d, 0x2e, 0xdb, 90
	.byte	"mediumseagreen", 0x3c, 0xb3, 0x2f, 91
	.byte	"mediumslateblue", 0x7b, 0x2c, 0xee, 92
	.byte	"mediumspringgreen", 0x00, 0xfa, 0x9a, 93
	.byte	"mediumturquoise", 0x1e, 0xd1, 0xcc, 94
	.byte	"mediumvioletred", 0xc7, 0x0f, 0x0d, 95
	.byte	"midnightblue", 0x0d, 0x0d, 0x2e, 96
	.byte	"mintcream", 0xf5, 0xff, 0xfa, 97
	.byte	"mistyrose", 0xff, 0xe4, 0xe1, 98
	.byte	"moccasin", 0xff, 0xe4, 0xb5, 99
	.byte	"navajowhite", 0xff, 0xde, 0xad, 100
	.byte	"navy", 0x00, 0x00, 0x0e, 101
	.byte	"oldlace", 0xfd, 0xf5, 0xe6, 102
	.byte	"olive", 0x0e, 0x0e, 0x00, 103
	.byte	"olivedrab", 0x6b, 0x8e, 0x0b, 104
	.byte	"orange", 0xff, 0xa5, 0x00, 105
	.byte	"orangered", 0xff, 0x2d, 0x00, 106
	.byte	"orchid", 0xda, 0x2e, 0xd6, 107
	.byte	"palegoldenrod", 0xee, 0xe8, 0xaa, 109
	.byte	"palegreen", 0x3e, 0xfb, 0x3e, 110
	.byte	"paleturquoise", 0xaf, 0xee, 0xee, 111
	.byte	"palevioletred", 0xdb, 0x2e, 0x5d, 112
	.byte	"papayawhip", 0xff, 0xef, 0xd5, 113
	.byte	"peachpuff", 0xff, 0xda, 0xb9, 114
	.byte	"peru", 0xcd, 0x0d, 0x3f, 115
	.byte	"pink", 0xff, 0xc0, 0xcb, 116
	.byte	"plum", 0xdd, 0xa0, 0xdd, 117
	.byte	"powderblue", 0xb0, 0xe0, 0xe6, 118
	.byte	"purple", 0x0e, 0x00, 0x0e, 119
	.byte	"red", 0xff, 0x00, 0x00, 120
	.byte	"rosybrown", 0xbc, 0x8f, 0x8f, 121
	.byte	"royalblue", 0x1d, 0x2d, 0xe1, 122
	.byte	"saddlebrown", 0x8b, 0x2d, 0x0d, 123
	.byte	"salmon", 0xfa, 0x0e, 0x1e, 124
	.byte	"sandybrown", 0xf4, 0xa4, 0x3c, 125
	.byte	"seagreen", 0x2e, 0x8b, 0x1b, 126
	.byte	"seashell", 0xff, 0xf5, 0xee, 127
	.byte	"sienna", 0xa0, 0x0a, 0x2d, 128
	.byte	"silver", 0xc0, 0xc0, 0xc0, 129
	.byte	"skyblue", 0x1b, 0xce, 0xeb, 130
	.byte	"slateblue", 0x6a, 0x5a, 0xcd, 131
	.byte	"slategray", 0x2e, 0x0e, 0x5a, 132
	.byte	"slategrey", 0x2e, 0x0e, 0x5a, 133
	.byte	"snow", 0xff, 0xfa, 0xfa, 134
	.byte	"springgreen", 0x00, 0xff, 0x7f, 135
	.byte	"steelblue", 0x2e, 0x0a, 0xb4, 136
	.byte	"tan", 0xd2, 0xb4, 0x8c, 137
	.byte	"teal", 0x00, 0x0e, 0x0e, 138
	.byte	"thistle", 0xd8, 0xbf, 0xd8, 139
	.byte	"tomato", 0xff, 0x3f, 0x2f, 140
	.byte	"turquoise", 0x1c, 0xe0, 0xd0, 141
	.byte	"violet", 0xee, 0x0a, 0xee, 142
	.byte	"wheat", 0xf5, 0xde, 0xb3, 143
	.byte	"white", 0xff, 0xff, 0xff, 144
	.byte	"whitesmoke", 0xf5, 0xf5, 0xf5, 145
	.byte	"yellow", 0xff, 0xff, 0x00, 146
	.byte	"yellowgreen", 0x9a, 0xcd, 0x0e, 147
svg_color_end:

arc_polyester_codes:
arc_polyester_end:

arc_rayon_codes:
arc_rayon_end:

coats_and_clark_rayon_codes:
coats_and_clark_rayon_end:

exquisite_polyester_codes:
exquisite_polyester_end:

fufu_polyester_codes:
fufu_polyester_end:

fufu_rayon_codes:
fufu_rayon_end:

hemingworth_polyester_codes:
	.byte	"Pure White", 0xFF, 0xFF, 0xFF, 1001
	.byte	"Lemon Ice", 0xDD, 0xE0, 0x0F, 1271
	.byte	"Neon Green", 0xC9, 0xDD, 0x03, 1272
	.byte	"Brilliant Lime", 0x60, 0xDD, 0x49, 1273
	.byte	"Mango", 0xFF, 0xCC, 0x1E, 1274
	.byte	"Neon Yellow", 0xFF, 0xED, 0x38, 1275
	.byte	"Tropical Orange", 0xFF, 0xA9, 0x52, 1276
	.byte	"Neon Orange", 0xFF, 0x93, 0x38, 1277
	.byte	"Rebel Peach", 0xFF, 0x58, 0x5F, 1278
	.byte	"Shy Flamingo", 0xF2, 0x8C, 0xA3, 1279
	.byte	"Neon Pink", 0xFE, 0x8A, 0x9E, 1280
	.byte	"Neon Peach", 0xFC, 0x07, 0x4F, 1281
	.byte	"Dove Gray", 0xCF, 0xC3, 0xC3, 1067
	.byte	"Silver Lining", 0xC9, 0xCA, 0xC8, 1068
	.byte	"Storm Cloud", 0xB2, 0xB4, 0xB3, 1069
	.byte	"Platinum", 0xC6, 0xC6, 0xBC, 1070
	.byte	"Graphite", 0x61, 0x63, 0x65, 1244
	.byte	"Light Charcoal", 0x4D, 0x4F, 0x53, 1245
	.byte	"Chrome", 0x8E, 0x90, 0x8F, 1072
	.byte	"Antique Silver", 0x74, 0x76, 0x78, 1077
	.byte	"Pewter Gray", 0x6C, 0x6F, 0x70, 1073
	.byte	"Black Stallion", 0x19, 0x1D, 0x1F, 1079
	.byte	"Charcoal", 0x1B, 0x24, 0x2A, 1087
	.byte	"Classic Black", 0x00, 0x00, 0x00, 1000
	.byte	"Marshmallow", 0xD5, 0xD2, 0xCA, 1118
	.byte	"Ice Blue", 0xDA, 0xE3, 0xEA, 1119
	.byte	"Nautical Blue", 0xA6, 0xBC, 0xC6, 1076
	.byte	"Sea Storm", 0x81, 0x8A, 0x8F, 1074
	.byte	"Bronzed Steel", 0x59, 0x5A, 0x5C, 1078
	.byte	"Silvery Gray", 0xB9, 0xC9, 0xD0, 1239
	.byte	"Granite", 0x7D, 0x9A, 0xAA, 1240
	.byte	"Shadow", 0x5E, 0x6A, 0x71, 1085
	.byte	"Dark Slate Blue", 0x00, 0x3C, 0x69, 1241
	.byte	"Deep Slate Blue", 0x00, 0x39, 0x46, 1242
	.byte	"Pacific Waters", 0x00, 0x42, 0x50, 1081
	.byte	"Dark Slate", 0x37, 0x42, 0x4A, 1086
	.byte	"Smoky Blue", 0x00, 0x5B, 0x82, 1192
	.byte	"Light Slate Blue", 0x5E, 0x9C, 0xAE, 1193
	.byte	"Hyacinth", 0x6A, 0xAD, 0xE4, 1188
	.byte	"Bluebird", 0x4B, 0x92, 0xDB, 1187
	.byte	"Misty Blue", 0x8F, 0xCA, 0xE7, 1186
	.byte	"Cornflower Blue", 0xC2, 0xDE, 0xEA, 1185
	.byte	"Pale Blue", 0xA0, 0xCF, 0xEB, 1256
	.byte	"Country Blue", 0x00, 0x98, 0xDB, 1255
	.byte	"Azure", 0x3D, 0x7E, 0xDB, 1202
	.byte	"Royal Blue", 0x00, 0x39, 0xA6, 1203
	.byte	"Brilliant Blue", 0x00, 0x33, 0x8D, 1204
	.byte	"Deep Blue", 0x0B, 0x22, 0x65, 1205
	.byte	"Winter Blue", 0x98, 0xC6, 0xEA, 1189
	.byte	"Winter Sky", 0xAA, 0xCA, 0xE6, 1190
	.byte	"Sky Blue", 0x8E, 0xBA, 0xE5, 1191
	.byte	"China Blue", 0x00, 0x73, 0xCF, 1198
	.byte	"Dark Blueberry", 0x00, 0x41, 0x65, 1201
	.byte	"Salem Blue", 0x00, 0x41, 0x53, 1200
	.byte	"Navy", 0x00, 0x22, 0x44, 1199
	.byte	"Sailor Blue", 0x00, 0x2C, 0x5F, 1265
	.byte	"Dark Blue ", 0x00, 0x28, 0x57, 1264
	.byte	"Berry Blue", 0x00, 0x35, 0x91, 1263
	.byte	"True Blue", 0x00, 0x2C, 0x77, 1261
	.byte	"Periwinkle", 0x6F, 0x9A, 0xD3, 1262
	.byte	"Iceberg Blue", 0x65, 0xCF, 0xE9, 1197
	.byte	"Medium Aquamarine", 0x00, 0x75, 0xB0, 1195
	.byte	"Dark Aquamarine", 0x00, 0x66, 0xA1, 1196
	.byte	"Peacock Blue", 0x00, 0x69, 0x83, 1194
	.byte	"Dark Turquoise", 0x00, 0x3D, 0x4C, 1258
	.byte	"Turquoise", 0x00, 0x98, 0xC3, 1259
	.byte	"Caribbean Blue", 0x00, 0xB0, 0xCA, 1260
	.byte	"Summer Sky", 0x6F, 0xD4, 0xE4, 1257
	.byte	"Crystal Lake", 0xBB, 0xE7, 0xE6, 1178
	.byte	"Icicle Blue", 0xC1, 0xE2, 0xE5, 1172
	.byte	"Frosty Blue", 0x8F, 0xDF, 0xE2, 1173
	.byte	"Blue Lagoon", 0x00, 0xAF, 0xD8, 1174
	.byte	"Blue Satin", 0x00, 0x67, 0x78, 1181
	.byte	"Teal Blue", 0x00, 0x7C, 0x92, 1180
	.byte	"Light Teal Blue", 0x00, 0x9A, 0xA6, 1176
	.byte	"Wintergreen", 0x7C, 0xA2, 0x95, 1175
	.byte	"Mint Green", 0x63, 0xCE, 0xCA, 1177
	.byte	"Navajo Turquoise", 0x00, 0x87, 0x7C, 1179
	.byte	"Peacock Green", 0x00, 0x7B, 0x69, 1182
	.byte	"Forest Glen", 0x02, 0x4E, 0x43, 1183
	.byte	"Deep Teal", 0x00, 0x49, 0x53, 1184
	.byte	"Deep Sea", 0x15, 0x65, 0x70, 1082
	.byte	"Dragonfly", 0x00, 0x50, 0x5C, 1113
	.byte	"Blue Steel", 0x44, 0x69, 0x7D, 1084
	.byte	"Dark Sage", 0x49, 0x6C, 0x60, 1114
	.byte	"Silver Green", 0x94, 0x9D, 0x9E, 1115
	.byte	"Antique Gray", 0x91, 0xBA, 0xA3, 1243
	.byte	"Ocean Spray", 0xB9, 0xCC, 0xC3, 1100
	.byte	"Sea Foam", 0xA6, 0xE6, 0xBC, 1088
	.byte	"Cucumber Melon", 0x00, 0xB5, 0x88, 1094
	.byte	"Light Jade", 0x00, 0x98, 0x5F, 1106
	.byte	"Jade", 0x00, 0x9B, 0x74, 1107
	.byte	"Dark Jade", 0x00, 0x7D, 0x57, 1105
	.byte	"Caribbean", 0x00, 0x6A, 0x4D, 1104
	.byte	"Dark Teal", 0x00, 0x68, 0x5B, 1254
	.byte	"Minty Teal", 0x0D, 0x77, 0x6E, 1253
	.byte	"Lemony Lime", 0xC3, 0xE7, 0x6F, 1099
	.byte	"Kiwi Lime", 0xCC, 0xDC, 0x00, 1247
	.byte	"Electric Green", 0x69, 0xBE, 0x28, 1097
	.byte	"Green Apple", 0x92, 0xD4, 0x00, 1091
	.byte	"Key Lime", 0x7A, 0xB8, 0x00, 1092
	.byte	"Kelly Green", 0x3F, 0x9C, 0x35, 1093
	.byte	"Meadow", 0x00, 0xAF, 0x3F, 1248
	.byte	"Grassy Green", 0x00, 0x79, 0x34, 1095
	.byte	"Dark Kelly Green", 0x00, 0x85, 0x42, 1108
	.byte	"Christmas Green", 0x00, 0x69, 0x3C, 1109
	.byte	"Winter Pine ", 0x1C, 0x45, 0x3B, 1250
	.byte	"Holly Leaf", 0x17, 0x5E, 0x54, 1249
	.byte	"Pistachio Nut", 0xC8, 0xE5, 0x9A, 1096
	.byte	"Dusty Green", 0x69, 0x92, 0x3A, 1251
	.byte	"Bush Ivy ", 0x55, 0x76, 0x30, 1252
	.byte	"Leafy Green", 0x73, 0x96, 0x00, 1089
	.byte	"Kentucky Grass", 0x53, 0x68, 0x2B, 1090
	.byte	"Ivy", 0x03, 0x56, 0x42, 1103
	.byte	"Evergreen", 0x28, 0x4E, 0x36, 1110
	.byte	"Mountain Meadow", 0x00, 0x44, 0x38, 1111
	.byte	"Forest Green", 0x00, 0x4D, 0x46, 1112
	.byte	"Oregano", 0x57, 0x58, 0x4F, 1121
	.byte	"Jungle Green", 0x40, 0x4A, 0x29, 1123
	.byte	"Thyme", 0x83, 0x84, 0x7A, 1120
	.byte	"Light Avocado", 0x82, 0x7C, 0x34, 1058
	.byte	"Split Pea", 0xB1, 0x9B, 0x00, 1061
	.byte	"Spring Leaf", 0xB5, 0xA3, 0x00, 1059
	.byte	"Almond Cream", 0xF8, 0xE4, 0x98, 1060
	.byte	"Eggshell", 0xD7, 0xD3, 0xC7, 1229
	.byte	"Cornsilk Green", 0xD5, 0xC8, 0x33, 1098
	.byte	"Avocado", 0x6A, 0x70, 0x29, 1101
	.byte	"Seaweed", 0x89, 0x8F, 0x4B, 1102
	.byte	"Olive Green", 0x65, 0x55, 0x1C, 1246
	.byte	"Coconut Shell", 0x4B, 0x45, 0x2C, 1117
	.byte	"Parsley", 0x4B, 0x47, 0x1A, 1116
	.byte	"Dried Sage", 0x71, 0x86, 0x74, 1083
	.byte	"Mocha", 0x4F, 0x4C, 0x25, 1125
	.byte	"Warm Earth", 0x5D, 0x4F, 0x4B, 1131
	.byte	"Dark Chocolate", 0x45, 0x23, 0x25, 1126
	.byte	"Deep Walnut", 0x4E, 0x2E, 0x2D, 1128
	.byte	"Teddybear Brown", 0x6E, 0x32, 0x19, 1130
	.byte	"Light Chestnut", 0x60, 0x35, 0x1D, 1134
	.byte	"Pecan Pie", 0x6C, 0x4D, 0x23, 1140
	.byte	"Dark Alder", 0x76, 0x6A, 0x65, 1237
	.byte	"Army Green", 0x5B, 0x49, 0x1F, 1137
	.byte	"Pharaoh Gold", 0x6E, 0x5A, 0x2A, 1135
	.byte	"Autumn Haystack", 0xAB, 0x84, 0x22, 1136
	.byte	"Sahara", 0x85, 0x68, 0x22, 1122
	.byte	"Weathered Wood", 0x67, 0x5C, 0x53, 1236
	.byte	"Soft Beige", 0x9A, 0x99, 0x6E, 1124
	.byte	"Mercury", 0xC2, 0xB2, 0xB5, 1149
	.byte	"Old Lace", 0xA5, 0xAC, 0xAF, 1146
	.byte	"Caramel Cappuccino", 0xAE, 0x7D, 0x5B, 1145
	.byte	"Brown Sugar", 0xA7, 0x6F, 0x3E, 1133
	.byte	"Light Cinnamon", 0xA2, 0x50, 0x22, 1064
	.byte	"Cinnamon", 0x86, 0x43, 0x1E, 1238
	.byte	"Apple Cider", 0xB2, 0x54, 0x1A, 1163
	.byte	"Indian Paintbrush", 0x9A, 0x3B, 0x26, 1144
	.byte	"Rust", 0x83, 0x38, 0x20, 1164
	.byte	"Toasted Almond", 0x82, 0x5C, 0x26, 1142
	.byte	"Pale Caramel", 0xC5, 0x92, 0x17, 1063
	.byte	"Honey Butter", 0xDD, 0xB9, 0x9A, 1062
	.byte	"Sandy Shore", 0xD2, 0xC2, 0x95, 1057
	.byte	"Ecru", 0xC2, 0xC2, 0xA0, 1056
	.byte	"Malt", 0xB3, 0xB3, 0x8C, 1055
	.byte	"Antique Lace", 0xC7, 0xB3, 0x7F, 1054
	.byte	"Champagne", 0xBD, 0x92, 0x71, 1171
	.byte	"Butter Taffy", 0xB3, 0x99, 0x5D, 1138
	.byte	"Cream Soda", 0xCE, 0xA9, 0x8C, 1235
	.byte	"Conch Shell", 0xE3, 0x9B, 0x6C, 1139
	.byte	"New Penny", 0xBA, 0x6F, 0x2E, 1132
	.byte	"Pumpkin Spice", 0xBB, 0x65, 0x0E, 1141
	.byte	"Soft Sunlight", 0xEB, 0xE8, 0xB1, 1042
	.byte	"Lemon Drop", 0xEE, 0xEC, 0x83, 1043
	.byte	"Daffodil", 0xF3, 0xEC, 0x7A, 1045
	.byte	"Lemon Citrus", 0xF5, 0xEC, 0x5A, 1225
	.byte	"Sunshine Yellow", 0xFA, 0xE7, 0x00, 1226
	.byte	"Canary Yellow", 0xF2, 0xEE, 0x72, 1044
	.byte	"Sunflower", 0xFC, 0xD9, 0x00, 1227
	.byte	"Sun", 0xFA, 0xDC, 0x41, 1046
	.byte	"Dandelion", 0xFE, 0xD1, 0x00, 1047
	.byte	"Buttercup", 0xF3, 0xCF, 0x45, 1048
	.byte	"Ginger Root", 0xEF, 0xBD, 0x47, 1050
	.byte	"Goldenrod", 0xEA, 0xAB, 0x00, 1051
	.byte	"Cornsilk", 0xDC, 0xD6, 0xB2, 1037
	.byte	"Macadamia", 0xC6, 0xBC, 0x89, 1038
	.byte	"Yellow Plumeria", 0xF8, 0xE4, 0x98, 1039
	.byte	"Maize", 0xF8, 0xDE, 0x6E, 1040
	.byte	"Dried Banana", 0xFA, 0xDA, 0x63, 1049
	.byte	"Butternut", 0xFF, 0xCB, 0x4F, 1053
	.byte	"Orange Meringue", 0xFF, 0xA1, 0x00, 1232
	.byte	"September Sunset", 0xFF, 0xB6, 0x12, 1231
	.byte	"Orange Cream", 0xFF, 0xB6, 0x52, 1230
	.byte	"Cantaloupe", 0xFF, 0xBC, 0x3D, 1041
	.byte	"Old Gold", 0xCE, 0x8E, 0x00, 1052
	.byte	"Auburn", 0x9D, 0x53, 0x24, 1143
	.byte	"Citrus Burst", 0xE9, 0x83, 0x00, 1024
	.byte	"Orange Slice", 0xFF, 0x70, 0x00, 1025
	.byte	"Fiery Sunset", 0xE3, 0x72, 0x22, 1027
	.byte	"Hunter Orange", 0xFB, 0x4F, 0x14, 1028
	.byte	"Fall Harvest", 0xDD, 0x48, 0x14, 1029
	.byte	"Candy Apple", 0xCD, 0x20, 0x2C, 1030
	.byte	"Christmas Red", 0xC3, 0x00, 0x14, 1270
	.byte	"Pomegranate", 0xA7, 0x02, 0x32, 1032
	.byte	"Rummy Raisin", 0x88, 0x23, 0x32, 1031
	.byte	"Cardinal Red", 0xA5, 0x11, 0x00, 1002
	.byte	"Rusty Red", 0x9E, 0x30, 0x39, 1234
	.byte	"Redwood", 0x78, 0x30, 0x14, 1233
	.byte	"Carrot", 0xD5, 0x5C, 0x19, 1065
	.byte	"Paprika", 0xAA, 0x27, 0x2F, 1066
	.byte	"Cherrywood", 0x5F, 0x33, 0x27, 1129
	.byte	"Burnt Sienna", 0x5D, 0x35, 0x26, 1127
	.byte	"Merlot", 0x59, 0x2C, 0x35, 1160
	.byte	"Loganberry", 0x6A, 0x1A, 0x41, 1159
	.byte	"Cranberry", 0x6E, 0x27, 0x14, 1158
	.byte	"Mulberry", 0x66, 0x20, 0x46, 1157
	.byte	"Magenta", 0x85, 0x00, 0x3C, 1156
	.byte	"Raspberry", 0x64, 0x1F, 0x14, 1155
	.byte	"Salmon", 0xFF, 0x81, 0x8D, 1166
	.byte	"Georgia Peach", 0xFF, 0xA4, 0x8A, 1015
	.byte	"Rose Sunset", 0xFF, 0xB0, 0xB7, 1011
	.byte	"Bubblegum Pink", 0xF3, 0x78, 0x9B, 1012
	.byte	"Carnation", 0xDB, 0x4D, 0x69, 1014
	.byte	"Very Berry", 0x91, 0x00, 0x4B, 1013
	.byte	"Raspberry Red", 0x82, 0x24, 0x0C, 1224
	.byte	"Dark Salmon", 0xF5, 0x43, 0x59, 1018
	.byte	"Apricot Dream", 0xF4, 0x58, 0x7A, 1017
	.byte	"Coral Reef", 0xFF, 0x8B, 0x7C, 1016
	.byte	"Frosted Peach", 0xFF, 0xC1, 0x9C, 1022
	.byte	"Tangerine", 0xFF, 0x8F, 0x70, 1020
	.byte	"Dark Mango", 0xFF, 0x6D, 0x42, 1026
	.byte	"Marigold", 0xFF, 0xA0, 0x2F, 1023
	.byte	"Spun Silk", 0xEC, 0xC1, 0x82, 1168
	.byte	"Whipped Papaya", 0xFB, 0xCE, 0x92, 1021
	.byte	"Baby Peach", 0xFD, 0xC4, 0x80, 1228
	.byte	"Pink Pearl", 0xFF, 0xC2, 0xA2, 1167
	.byte	"Peaches 'n Cream", 0xEF, 0xC5, 0xCE, 1169
	.byte	"Peach Pastel", 0xEF, 0xBE, 0x9C, 1170
	.byte	"Old Penny", 0x77, 0x4A, 0x39, 1162
	.byte	"Dusty Rose", 0xB2, 0x6F, 0x7E, 1151
	.byte	"Winter Rose", 0xD4, 0x90, 0xA8, 1165
	.byte	"Valentine Pink", 0xF6, 0xA3, 0xBB, 1161
	.byte	"Petal Peach", 0xFF, 0xB7, 0xAE, 1019
	.byte	"Soft Petal", 0xEF, 0xD6, 0xDB, 1150
	.byte	"Fuchsia", 0x92, 0x00, 0x75, 1036
	.byte	"Pink Kiss", 0xF3, 0x75, 0xC6, 1004
	.byte	"Baby Pink", 0xF3, 0xBB, 0xCE, 1003
	.byte	"Whisper Pink", 0xF1, 0xDB, 0xDF, 1005
	.byte	"Gentle Blush", 0xF3, 0xC9, 0xD3, 1006
	.byte	"English Rose", 0xF4, 0xB2, 0xC1, 1007
	.byte	"Sweet Pea", 0xF3, 0x9E, 0xBC, 1008
	.byte	"Rosy Blush", 0xF7, 0x7A, 0xB4, 1009
	.byte	"Passion Pink", 0xD7, 0x1F, 0x85, 1010
	.byte	"Mulled Wine", 0x77, 0x20, 0x59, 1035
	.byte	"Primrose", 0xC5, 0x00, 0x84, 1034
	.byte	"Azalea", 0xA1, 0x00, 0x6B, 1033
	.byte	"Snowflake", 0xD1, 0xD4, 0xD3, 1148
	.byte	"Moonlight", 0xCA, 0xD1, 0xE7, 1147
	.byte	"Tulip", 0x9D, 0xAB, 0xE2, 1207
	.byte	"Purple Iris", 0x88, 0x84, 0xD5, 1206
	.byte	"Grape", 0x1A, 0x21, 0x55, 1209
	.byte	"Moon Shadow", 0x64, 0x59, 0xC4, 1211
	.byte	"Electric Purple", 0x21, 0x24, 0x92, 1208
	.byte	"Indigo", 0x41, 0x12, 0x44, 1210
	.byte	"Royal Purple", 0x3B, 0x00, 0x83, 1223
	.byte	"Eggplant", 0x15, 0x1C, 0x54, 1267
	.byte	"Dark Purple", 0x49, 0x0E, 0x6F, 1269
	.byte	"Pure Purple", 0x57, 0x06, 0x8C, 1268
	.byte	"Pale Orchid", 0xDC, 0xC7, 0xDF, 1217
	.byte	"Dusty Mauve", 0xC2, 0xAC, 0xBE, 1219
	.byte	"Orchid", 0xDC, 0x9D, 0xDD, 1218
	.byte	"Heather", 0xB3, 0x82, 0xC7, 1213
	.byte	"Lavender", 0x9C, 0x5F, 0xB5, 1214
	.byte	"Soft Grape", 0x4B, 0x08, 0xA1, 1266
	.byte	"Freesia", 0xC1, 0xAF, 0xE5, 1221
	.byte	"Lilac", 0xC5, 0xB9, 0xE3, 1222
	.byte	"Peony", 0x6E, 0x2C, 0x6B, 1215
	.byte	"Dark Fuschia", 0x7D, 0x00, 0x63, 1216
	.byte	"Grape Jelly", 0x75, 0x28, 0x64, 1220
	.byte	"Deep Orchid", 0x55, 0x51, 0x7B, 1080
	.byte	"Misty Blue Gray", 0x5C, 0x7F, 0x92, 1075
	.byte	"Iron Ore", 0xAF, 0xAD, 0xC3, 1071
	.byte	"Light Mauve", 0xD8, 0xAA, 0xB3, 1152
	.byte	"Dark Mauve", 0x89, 0x68, 0x7C, 1153
	.byte	"Wild Plum", 0x64, 0x44, 0x59, 1154
	.byte	"Huckleberry", 0x4B, 0x30, 0x6A, 1212
hemingworth_polyester_end:


isacord_polyester_codes:
	.byte	"?", 0xFF, 0xFF, 0xFF, 10
	.byte	"?", 0xFF, 0xFF, 0xFF, 15
	.byte	"?", 0xFF, 0xFF, 0xFF, 17
	.byte	"?", 0x00, 0x00, 0x00, 20
	.byte	"?", 0xFF, 0xFD, 0xED, 101
	.byte	"?", 0x6D, 0x75, 0x7B, 108
	.byte	"?", 0x51, 0x5B, 0x61, 111
	.byte	"?", 0x5D, 0x5D, 0x5D, 112
	.byte	"?", 0xCF, 0xCF, 0xCF, 124
	.byte	"?", 0xA1, 0xA9, 0xB4, 131
	.byte	"?", 0x19, 0x20, 0x24, 132
	.byte	"?", 0x9E, 0xA5, 0xAA, 142
	.byte	"?", 0xCF, 0xD1, 0xD5, 145
	.byte	"?", 0xC6, 0xBD, 0xB4, 150
	.byte	"?", 0xD5, 0xC4, 0xB3, 151
	.byte	"?", 0x7C, 0x82, 0x83, 152
	.byte	"?", 0xFE, 0xF5, 0xF0, 180
	.byte	"?", 0xE9, 0xD7, 0xD9, 182
	.byte	"?", 0xEB, 0xE3, 0xDD, 184
	.byte	"?", 0xE0, 0xDA, 0x5F, 221
	.byte	"?", 0xBF, 0xBA, 0x28, 232
	.byte	"?", 0xFA, 0xF6, 0xCC, 250
	.byte	"?", 0xF9, 0xF8, 0xE8, 270
	.byte	"?", 0xFD, 0xF7, 0x6C, 310
	.byte	"?", 0xF5, 0xD3, 0x00, 311
	.byte	"?", 0x79, 0x7E, 0x24, 345
	.byte	"?", 0xB0, 0xAA, 0x76, 352
	.byte	"?", 0x89, 0x8F, 0x2B, 442
	.byte	"?", 0x98, 0x99, 0x6D, 453
	.byte	"?", 0x6B, 0x7E, 0x6F, 463
	.byte	"?", 0x3E, 0x4F, 0x34, 465
	.byte	"?", 0xED, 0xEF, 0x05, 501
	.byte	"?", 0xF5, 0xD3, 0x00, 506
	.byte	"?", 0xFD, 0xE8, 0x96, 520
	.byte	"?", 0xD7, 0xCE, 0x8A, 532
	.byte	"?", 0xB1, 0x8B, 0x00, 542
	.byte	"?", 0xB2, 0x8F, 0x11, 546
	.byte	"?", 0xB6, 0x9F, 0x56, 552
	.byte	"?", 0xF8, 0xD7, 0x3E, 600
	.byte	"?", 0xF8, 0xD7, 0x3E, 605
	.byte	"?", 0xF7, 0xDC, 0x00, 608
	.byte	"?", 0xFE, 0xF0, 0x9A, 630
	.byte	"?", 0xFD, 0xE8, 0x96, 640
	.byte	"?", 0xF5, 0xD2, 0xA6, 651
	.byte	"?", 0xFE, 0xF9, 0xEA, 660
	.byte	"?", 0xFA, 0xF6, 0xE7, 670
	.byte	"?", 0xBE, 0xBE, 0xA8, 672
	.byte	"?", 0xF7, 0xC3, 0x5F, 700
	.byte	"?", 0xF5, 0xCA, 0x00, 702
	.byte	"?", 0xDF, 0xA2, 0x00, 704
	.byte	"?", 0xFC, 0xF5, 0x38, 706
	.byte	"?", 0xFA, 0xDC, 0x59, 713
	.byte	"?", 0x8C, 0x7E, 0x6A, 722
	.byte	"?", 0x59, 0x49, 0x00, 747
	.byte	"?", 0xD6, 0xBF, 0x94, 761
	.byte	"?", 0x65, 0x64, 0x52, 776
	.byte	"?", 0xF1, 0xAF, 0x00, 800
	.byte	"?", 0xF5, 0xBA, 0x5D, 811
	.byte	"?", 0xE1, 0xA2, 0x3E, 821
	.byte	"?", 0xCC, 0xAB, 0x3F, 822
	.byte	"?", 0xDF, 0xA2, 0x00, 824
	.byte	"?", 0xD0, 0xA4, 0x4F, 832
	.byte	"?", 0xCD, 0x94, 0x4A, 842
	.byte	"?", 0xE3, 0xBC, 0x61, 851
	.byte	"?", 0x94, 0x7C, 0x4A, 853
	.byte	"?", 0xCB, 0xBF, 0xA2, 861
	.byte	"?", 0xA5, 0x86, 0x6A, 862
	.byte	"?", 0xEB, 0xE7, 0xDD, 870
	.byte	"?", 0x9F, 0xA0, 0x86, 873
	.byte	"?", 0x9A, 0x89, 0x7B, 874
	.byte	"?", 0xF3, 0xB2, 0x59, 904
	.byte	"?", 0xCA, 0x83, 0x2C, 922
	.byte	"?", 0xC0, 0x73, 0x14, 931
	.byte	"?", 0xAC, 0x66, 0x13, 932
	.byte	"?", 0x74, 0x48, 0x08, 933
	.byte	"?", 0xBD, 0x95, 0x65, 934
	.byte	"?", 0xC9, 0x83, 0x00, 940
	.byte	"?", 0xAF, 0x7D, 0x3E, 941
	.byte	"?", 0x48, 0x39, 0x28, 945
	.byte	"?", 0xFE, 0xFE, 0xED, 970
	.byte	"?", 0x6A, 0x41, 0x29, 1055
	.byte	"?", 0xFD, 0xE2, 0xC1, 1060
	.byte	"?", 0xA6, 0x8A, 0x68, 1061
	.byte	"?", 0xED, 0x92, 0x06, 1102
	.byte	"?", 0xEE, 0x9C, 0x00, 1106
	.byte	"?", 0xEE, 0x87, 0x51, 1114
	.byte	"?", 0xA3, 0x52, 0x14, 1115
	.byte	"?", 0xF8, 0xC0, 0x00, 1120
	.byte	"?", 0xB7, 0x97, 0x6B, 1123
	.byte	"?", 0x9D, 0x5A, 0x21, 1134
	.byte	"?", 0xF3, 0xD8, 0xA8, 1140
	.byte	"?", 0xFA, 0xCF, 0xAE, 1141
	.byte	"?", 0x7A, 0x44, 0x27, 1154
	.byte	"?", 0xDF, 0xC8, 0xAB, 1172
	.byte	"?", 0xE8, 0x97, 0x63, 1211
	.byte	"?", 0xF1, 0xA2, 0x36, 1220
	.byte	"?", 0xE5, 0x57, 0x1D, 1300
	.byte	"?", 0xD9, 0x67, 0x4C, 1301
	.byte	"?", 0xE4, 0x50, 0x1E, 1304
	.byte	"?", 0xEA, 0x71, 0x34, 1305
	.byte	"?", 0xE1, 0x2A, 0x23, 1306
	.byte	"?", 0xC1, 0x48, 0x17, 1311
	.byte	"?", 0xC4, 0x53, 0x31, 1312
	.byte	"?", 0xD5, 0x81, 0x5E, 1332
	.byte	"?", 0xBB, 0x3D, 0x2E, 1334
	.byte	"?", 0xBE, 0x2D, 0x1A, 1335
	.byte	"?", 0x5F, 0x1B, 0x23, 1342
	.byte	"?", 0x7A, 0x34, 0x41, 1346
	.byte	"?", 0xFB, 0xBF, 0x95, 1351
	.byte	"?", 0xF4, 0xA7, 0x73, 1352
	.byte	"?", 0x69, 0x39, 0x20, 1355
	.byte	"?", 0xF9, 0xC5, 0x98, 1362
	.byte	"?", 0x43, 0x27, 0x31, 1366
	.byte	"?", 0x46, 0x45, 0x37, 1375
	.byte	"?", 0xF4, 0xA7, 0x82, 1430
	.byte	"?", 0xE2, 0x2D, 0x2A, 1501
	.byte	"?", 0xA9, 0x31, 0x21, 1514
	.byte	"?", 0xEC, 0x71, 0x68, 1521
	.byte	"?", 0xF6, 0xB0, 0x8E, 1532
	.byte	"?", 0xF9, 0xC5, 0xB9, 1551
	.byte	"?", 0x80, 0x6A, 0x61, 1565
	.byte	"?", 0xE3, 0x6C, 0x63, 1600
	.byte	"?", 0xE4, 0x47, 0x33, 1701
	.byte	"?", 0xDF, 0x00, 0x32, 1703
	.byte	"?", 0xE0, 0x00, 0x3D, 1704
	.byte	"?", 0xCF, 0x00, 0x40, 1725
	.byte	"?", 0xF1, 0xCD, 0xCE, 1755
	.byte	"?", 0xE9, 0xC9, 0xBD, 1760
	.byte	"?", 0xE8, 0xC0, 0xB8, 1761
	.byte	"?", 0xE0, 0x00, 0x46, 1800
	.byte	"?", 0xD6, 0x44, 0x5D, 1805
	.byte	"?", 0xF4, 0x9E, 0x95, 1840
	.byte	"?", 0xFC, 0xDA, 0xD5, 1860
	.byte	"?", 0x63, 0x62, 0x54, 1874
	.byte	"?", 0x39, 0x45, 0x35, 1876
	.byte	"?", 0xE1, 0x00, 0x57, 1900
	.byte	"?", 0xBD, 0x00, 0x41, 1902
	.byte	"?", 0xC0, 0x03, 0x43, 1903
	.byte	"?", 0xA9, 0x02, 0x3A, 1904
	.byte	"?", 0xBE, 0x00, 0x4F, 1906
	.byte	"?", 0x91, 0x02, 0x30, 1911
	.byte	"?", 0x86, 0x02, 0x3E, 1912
	.byte	"?", 0x9A, 0x0C, 0x3B, 1913
	.byte	"?", 0xA3, 0x30, 0x50, 1921
	.byte	"?", 0xF2, 0x8D, 0xA6, 1940
	.byte	"?", 0xCE, 0x42, 0x7A, 1950
	.byte	"?", 0x95, 0x95, 0x95, 1972
	.byte	"?", 0xA3, 0x31, 0x45, 2011
	.byte	"?", 0x9F, 0x45, 0x4C, 2022
	.byte	"?", 0xC7, 0x97, 0x9B, 2051
	.byte	"?", 0x9F, 0x00, 0x3F, 2101
	.byte	"?", 0x78, 0x09, 0x3F, 2113
	.byte	"?", 0x6D, 0x06, 0x27, 2115
	.byte	"?", 0x43, 0x27, 0x32, 2123
	.byte	"?", 0xE6, 0x77, 0x8B, 2152
	.byte	"?", 0xDF, 0x83, 0x90, 2153
	.byte	"?", 0xF9, 0xBF, 0xC0, 2155
	.byte	"?", 0xFB, 0xD1, 0xD6, 2160
	.byte	"?", 0xD8, 0xD5, 0xD0, 2166
	.byte	"?", 0xF7, 0xDE, 0xD6, 2170
	.byte	"?", 0xF7, 0xDE, 0xDE, 2171
	.byte	"?", 0xE8, 0x41, 0x8C, 2220
	.byte	"?", 0x8C, 0x0C, 0x4A, 2222
	.byte	"?", 0x88, 0x3A, 0x40, 2224
	.byte	"?", 0xEE, 0x71, 0xA1, 2230
	.byte	"?", 0xA9, 0x5A, 0x68, 2241
	.byte	"?", 0xFA, 0xC8, 0xD3, 2250
	.byte	"?", 0xD3, 0x00, 0x7E, 2300
	.byte	"?", 0xD2, 0x00, 0x67, 2320
	.byte	"?", 0x65, 0x15, 0x33, 2333
	.byte	"?", 0x3A, 0x21, 0x2B, 2336
	.byte	"?", 0xFD, 0xE5, 0xEC, 2363
	.byte	"?", 0x97, 0x00, 0x59, 2500
	.byte	"?", 0xAA, 0x43, 0x81, 2504
	.byte	"?", 0x82, 0x00, 0x52, 2506
	.byte	"?", 0xE2, 0x00, 0x78, 2520
	.byte	"?", 0xBF, 0x00, 0x6A, 2521
	.byte	"?", 0xF1, 0x89, 0xAF, 2550
	.byte	"?", 0xF7, 0xB4, 0xCA, 2560
	.byte	"?", 0x49, 0x49, 0x49, 2576
	.byte	"?", 0x89, 0x34, 0x80, 2600
	.byte	"?", 0x6C, 0x00, 0x51, 2611
	.byte	"?", 0xD9, 0x94, 0xB9, 2640
	.byte	"?", 0xE6, 0xB7, 0xCF, 2650
	.byte	"?", 0xEC, 0xD2, 0xDE, 2655
	.byte	"?", 0x60, 0x6D, 0x8C, 2674
	.byte	"?", 0x61, 0x00, 0x51, 2711
	.byte	"?", 0x49, 0x02, 0x51, 2715
	.byte	"?", 0x89, 0x34, 0x7F, 2720
	.byte	"?", 0xC6, 0x90, 0xA1, 2764
	.byte	"?", 0x6F, 0x06, 0x7B, 2810
	.byte	"?", 0xA9, 0x74, 0xAB, 2830
	.byte	"?", 0x4C, 0x0F, 0x7B, 2900
	.byte	"?", 0x66, 0x40, 0x90, 2905
	.byte	"?", 0x83, 0x58, 0x9D, 2910
	.byte	"?", 0x8C, 0x6D, 0xAA, 2920
	.byte	"?", 0xC9, 0xB5, 0xD4, 3040
	.byte	"?", 0xC7, 0x90, 0xBA, 3045
	.byte	"?", 0x70, 0x70, 0x70, 3062
	.byte	"?", 0x2A, 0x37, 0x7E, 3102
	.byte	"?", 0x35, 0x24, 0x7A, 3110
	.byte	"?", 0x26, 0x07, 0x51, 3114
	.byte	"?", 0x35, 0x3A, 0x90, 3210
	.byte	"?", 0x52, 0x4A, 0x90, 3211
	.byte	"?", 0x7D, 0x77, 0xAF, 3241
	.byte	"?", 0x90, 0x83, 0xA3, 3251
	.byte	"?", 0x14, 0x21, 0x4E, 3323
	.byte	"?", 0x7F, 0x8B, 0xC2, 3331
	.byte	"?", 0x1B, 0x3C, 0x78, 3333
	.byte	"?", 0x2E, 0x4B, 0x9B, 3335
	.byte	"?", 0x11, 0x26, 0x3C, 3344
	.byte	"?", 0x20, 0x2A, 0x65, 3353
	.byte	"?", 0x17, 0x1B, 0x4A, 3355
	.byte	"?", 0x00, 0x22, 0x32, 3444
	.byte	"?", 0x2D, 0x44, 0x91, 3522
	.byte	"?", 0x26, 0x12, 0x57, 3536
	.byte	"?", 0x3A, 0x28, 0x85, 3541
	.byte	"?", 0x23, 0x3B, 0x7D, 3543
	.byte	"?", 0x27, 0x3C, 0x82, 3544
	.byte	"?", 0x27, 0x26, 0x51, 3554
	.byte	"?", 0x28, 0x43, 0x8C, 3600
	.byte	"?", 0x24, 0x3A, 0x7D, 3611
	.byte	"?", 0x40, 0x55, 0xA1, 3612
	.byte	"?", 0x1A, 0x4C, 0x8D, 3622
	.byte	"?", 0x92, 0xB1, 0xDC, 3640
	.byte	"?", 0x64, 0x8D, 0xC7, 3641
	.byte	"?", 0xD0, 0xDE, 0xEE, 3650
	.byte	"?", 0xC8, 0xD6, 0xED, 3652
	.byte	"?", 0x00, 0x50, 0x7F, 3732
	.byte	"?", 0x12, 0x25, 0x3C, 3743
	.byte	"?", 0xB7, 0xD1, 0xE3, 3750
	.byte	"?", 0xAF, 0xC9, 0xE5, 3761
	.byte	"?", 0xCE, 0xD2, 0xD1, 3770
	.byte	"?", 0x3D, 0x6A, 0xA1, 3810
	.byte	"?", 0x7B, 0xA2, 0xD3, 3815
	.byte	"?", 0x91, 0xB9, 0xE2, 3820
	.byte	"?", 0xB4, 0xCE, 0xEB, 3840
	.byte	"?", 0x50, 0x71, 0x93, 3842
	.byte	"?", 0x00, 0x7E, 0xBA, 3900
	.byte	"?", 0x00, 0x82, 0xC4, 3901
	.byte	"?", 0x00, 0x6C, 0xA5, 3902
	.byte	"?", 0x4A, 0xBD, 0xF0, 3910
	.byte	"?", 0x86, 0xAA, 0xCA, 3951
	.byte	"?", 0x69, 0x76, 0x98, 3953
	.byte	"?", 0xA6, 0xD8, 0xF6, 3962
	.byte	"?", 0xE1, 0xE1, 0xE1, 3971
	.byte	"?", 0x00, 0x93, 0xB9, 4010
	.byte	"?", 0x50, 0x77, 0x93, 4032
	.byte	"?", 0x26, 0x56, 0x74, 4033
	.byte	"?", 0xEA, 0xF0, 0xF9, 4071
	.byte	"?", 0x83, 0x86, 0x89, 4073
	.byte	"?", 0x2D, 0xB0, 0xCF, 4101
	.byte	"?", 0x00, 0x95, 0xC6, 4103
	.byte	"?", 0x00, 0xA4, 0xD9, 4111
	.byte	"?", 0x00, 0xA9, 0xC9, 4113
	.byte	"?", 0x00, 0x82, 0xAD, 4116
	.byte	"?", 0x00, 0x40, 0x5D, 4133
	.byte	"?", 0x19, 0x20, 0x24, 4174
	.byte	"?", 0x4F, 0xB4, 0xCB, 4220
	.byte	"?", 0x8D, 0xCE, 0xE4, 4230
	.byte	"?", 0x8D, 0xCD, 0xDB, 4240
	.byte	"?", 0xD5, 0xEB, 0xF2, 4250
	.byte	"?", 0x00, 0x7B, 0x8D, 4410
	.byte	"?", 0x00, 0x91, 0xA5, 4421
	.byte	"?", 0x00, 0x7D, 0x8C, 4423
	.byte	"?", 0x00, 0x79, 0x86, 4425
	.byte	"?", 0x5F, 0xBF, 0xD1, 4430
	.byte	"?", 0x00, 0x69, 0x81, 4442
	.byte	"?", 0x00, 0x7F, 0x92, 4452
	.byte	"?", 0x00, 0x2F, 0x38, 4515
	.byte	"?", 0x00, 0x73, 0x89, 4531
	.byte	"?", 0x00, 0x7B, 0x8D, 4610
	.byte	"?", 0x00, 0xA3, 0xA0, 4620
	.byte	"?", 0x0B, 0x7F, 0x85, 4625
	.byte	"?", 0x00, 0x5B, 0x63, 4643
	.byte	"?", 0x23, 0x45, 0x44, 4644
	.byte	"?", 0x00, 0x5B, 0x63, 5005
	.byte	"?", 0x00, 0xA6, 0xAD, 5010
	.byte	"?", 0xB4, 0xDC, 0xD8, 5050
	.byte	"?", 0x00, 0x87, 0x6E, 5100
	.byte	"?", 0x00, 0x90, 0x84, 5101
	.byte	"?", 0x48, 0xBA, 0xB7, 5115
	.byte	"?", 0x00, 0xAF, 0x8C, 5210
	.byte	"?", 0x8C, 0xCC, 0xC2, 5220
	.byte	"?", 0x47, 0xB9, 0xAE, 5230
	.byte	"?", 0x19, 0x7E, 0x6D, 5233
	.byte	"?", 0x00, 0x6E, 0x42, 5324
	.byte	"?", 0x00, 0x4D, 0x3D, 5326
	.byte	"?", 0x00, 0x2F, 0x38, 5335
	.byte	"?", 0x00, 0x2D, 0x1F, 5374
	.byte	"?", 0x00, 0x86, 0x63, 5411
	.byte	"?", 0x00, 0x6B, 0x4E, 5415
	.byte	"?", 0x00, 0x86, 0x63, 5422
	.byte	"?", 0x52, 0xBA, 0x84, 5500
	.byte	"?", 0x14, 0xA3, 0x63, 5510
	.byte	"?", 0x00, 0x78, 0x48, 5513
	.byte	"?", 0x00, 0x86, 0x63, 5515
	.byte	"?", 0x52, 0xA0, 0x4F, 5531
	.byte	"?", 0x94, 0xAD, 0xA1, 5552
	.byte	"?", 0x10, 0x38, 0x28, 5555
	.byte	"?", 0x85, 0xC8, 0x75, 5610
	.byte	"?", 0x14, 0xB2, 0x6D, 5613
	.byte	"?", 0x1A, 0x78, 0x1E, 5633
	.byte	"?", 0x15, 0x74, 0x36, 5643
	.byte	"?", 0xC9, 0xE3, 0xC5, 5650
	.byte	"?", 0x6B, 0x91, 0x81, 5664
	.byte	"?", 0xA5, 0xC2, 0x78, 5822
	.byte	"?", 0x70, 0x95, 0x3F, 5833
	.byte	"?", 0x27, 0x30, 0x14, 5866
	.byte	"?", 0x81, 0xC7, 0x50, 5912
	.byte	"?", 0x45, 0x70, 0x21, 5933
	.byte	"?", 0x50, 0x67, 0x02, 5934
	.byte	"?", 0xBB, 0xDB, 0x41, 5940
	.byte	"?", 0x00, 0x35, 0x18, 5944
	.byte	"?", 0xE3, 0xEB, 0x00, 6010
	.byte	"?", 0xBE, 0xD7, 0x82, 6051
	.byte	"?", 0x91, 0x96, 0x00, 6133
	.byte	"?", 0x48, 0x46, 0x01, 6156
isacord_polyester_end:


isafil_rayon_codes:
	.byte	"?", 0xFF, 0xFF, 0xFF, 10
	.byte	"?", 0xFF, 0xFF, 0xFF, 15
	.byte	"?", 0xFF, 0xFF, 0xFF, 17
	.byte	"?", 0x00, 0x00, 0x00, 20
	.byte	"?", 0xFF, 0xFD, 0xED, 101
	.byte	"?", 0x7D, 0x7D, 0x7D, 104
	.byte	"?", 0x51, 0x5B, 0x61, 107
	.byte	"?", 0x6D, 0x75, 0x7B, 108
	.byte	"?", 0xAC, 0xAC, 0xAC, 109
	.byte	"?", 0x51, 0x5B, 0x61, 111
	.byte	"?", 0x5D, 0x5D, 0x5D, 112
	.byte	"?", 0xCF, 0xCF, 0xCF, 124
	.byte	"?", 0xA1, 0xA9, 0xB4, 131
	.byte	"?", 0x6D, 0x75, 0x7B, 141
	.byte	"?", 0x9E, 0xA5, 0xAA, 142
	.byte	"?", 0xCF, 0xD1, 0xD5, 145
	.byte	"?", 0xC6, 0xBD, 0xB4, 150
	.byte	"?", 0xD5, 0xC4, 0xB3, 151
	.byte	"?", 0x7C, 0x82, 0x83, 152
	.byte	"?", 0x89, 0x8F, 0x94, 156
	.byte	"?", 0xFE, 0xF5, 0xF0, 180
	.byte	"?", 0xE9, 0xD7, 0xD9, 182
	.byte	"?", 0xEB, 0xE3, 0xDD, 184
	.byte	"?", 0xE0, 0xDA, 0x5F, 221
	.byte	"?", 0xBF, 0xBA, 0x28, 232
	.byte	"?", 0xEC, 0xE9, 0xC1, 241
	.byte	"?", 0xFA, 0xF6, 0xCC, 250
	.byte	"?", 0xEC, 0xE7, 0xA5, 251
	.byte	"?", 0xEC, 0xEA, 0xDB, 260
	.byte	"?", 0xF9, 0xF8, 0xE8, 270
	.byte	"?", 0xFD, 0xF7, 0x6C, 310
	.byte	"?", 0xF5, 0xD3, 0x00, 311
	.byte	"?", 0x79, 0x7E, 0x24, 345
	.byte	"?", 0xB0, 0xAA, 0x76, 352
	.byte	"?", 0x89, 0x8F, 0x2B, 442
	.byte	"?", 0x98, 0x99, 0x6D, 453
	.byte	"?", 0x6E, 0x77, 0x2E, 454
	.byte	"?", 0x6B, 0x7E, 0x6F, 463
	.byte	"?", 0x3E, 0x4F, 0x34, 465
	.byte	"?", 0xED, 0xEF, 0x05, 501
	.byte	"?", 0xFA, 0xF6, 0xCC, 505
	.byte	"?", 0xF5, 0xD3, 0x00, 506
	.byte	"?", 0xFF, 0xFB, 0xD1, 510
	.byte	"?", 0xFD, 0xE8, 0x96, 520
	.byte	"?", 0xD7, 0xCE, 0x8A, 532
	.byte	"?", 0xB1, 0x8B, 0x00, 542
	.byte	"?", 0xAA, 0x8D, 0x00, 545
	.byte	"?", 0xB2, 0x8F, 0x11, 546
	.byte	"?", 0xAC, 0x94, 0x36, 551
	.byte	"?", 0xB6, 0x9F, 0x56, 552
	.byte	"?", 0xF4, 0xEE, 0x8C, 580
	.byte	"?", 0xF1, 0xEB, 0x35, 590
	.byte	"?", 0xF8, 0xD7, 0x3E, 600
	.byte	"?", 0xF8, 0xD7, 0x3E, 605
	.byte	"?", 0xF7, 0xCB, 0x47, 610
	.byte	"?", 0xF7, 0xE4, 0x00, 615
	.byte	"?", 0xFD, 0xE8, 0x96, 620
	.byte	"?", 0xEE, 0xDB, 0x00, 625
	.byte	"?", 0xFE, 0xF0, 0x9A, 630
	.byte	"?", 0xFD, 0xE1, 0xAF, 635
	.byte	"?", 0xFD, 0xE8, 0x96, 640
	.byte	"?", 0xF5, 0xD2, 0xA6, 651
	.byte	"?", 0xFE, 0xF9, 0xEA, 660
	.byte	"?", 0xFA, 0xF6, 0xE7, 670
	.byte	"?", 0xBE, 0xBE, 0xA8, 672
	.byte	"?", 0xF7, 0xC3, 0x5F, 700
	.byte	"?", 0xF5, 0xCA, 0x00, 702
	.byte	"?", 0xDF, 0xA2, 0x00, 704
	.byte	"?", 0xFC, 0xF5, 0x38, 706
	.byte	"?", 0xFA, 0xDC, 0x59, 713
	.byte	"?", 0x8C, 0x7E, 0x6A, 722
	.byte	"?", 0x82, 0x70, 0x00, 726
	.byte	"?", 0x63, 0x62, 0x54, 732
	.byte	"?", 0x59, 0x49, 0x00, 747
	.byte	"?", 0xD6, 0xBF, 0x94, 761
	.byte	"?", 0x65, 0x64, 0x52, 776
	.byte	"?", 0xF1, 0xAF, 0x00, 800
	.byte	"?", 0xF3, 0xC2, 0x00, 805
	.byte	"?", 0xF5, 0xBA, 0x5D, 811
	.byte	"?", 0xE1, 0xA2, 0x3E, 821
	.byte	"?", 0xCC, 0xAB, 0x3F, 822
	.byte	"?", 0xDF, 0xA2, 0x00, 824
	.byte	"?", 0xF3, 0xB0, 0x44, 830
	.byte	"?", 0xD0, 0xA4, 0x4F, 832
	.byte	"?", 0xCD, 0x94, 0x4A, 842
	.byte	"?", 0xE3, 0xBC, 0x61, 851
	.byte	"?", 0x94, 0x7C, 0x4A, 853
	.byte	"?", 0x00, 0x1F, 0x48, 866
	.byte	"?", 0xEB, 0xE7, 0xDD, 870
	.byte	"?", 0x9F, 0xA0, 0x86, 873
	.byte	"?", 0x9A, 0x89, 0x7B, 874
	.byte	"?", 0xEE, 0x9C, 0x00, 900
	.byte	"?", 0xF3, 0xB2, 0x59, 904
	.byte	"?", 0xCA, 0x83, 0x2C, 922
	.byte	"?", 0xC0, 0x73, 0x14, 931
	.byte	"?", 0xAC, 0x66, 0x13, 932
	.byte	"?", 0x74, 0x48, 0x08, 933
	.byte	"?", 0xBD, 0x95, 0x65, 934
	.byte	"?", 0x80, 0x68, 0x00, 936
	.byte	"?", 0xC9, 0x83, 0x00, 940
	.byte	"?", 0xAF, 0x7D, 0x3E, 941
	.byte	"?", 0x48, 0x39, 0x28, 945
	.byte	"?", 0xFE, 0xEC, 0xD9, 961
	.byte	"?", 0xFE, 0xFE, 0xED, 970
	.byte	"?", 0xDD, 0x97, 0x3A, 1041
	.byte	"?", 0x6A, 0x41, 0x29, 1055
	.byte	"?", 0xFD, 0xE2, 0xC1, 1060
	.byte	"?", 0xA6, 0x8A, 0x68, 1061
	.byte	"?", 0xD7, 0x68, 0x14, 1099
	.byte	"?", 0xED, 0x87, 0x3F, 1100
	.byte	"?", 0xEC, 0x87, 0x0E, 1101
	.byte	"?", 0xED, 0x92, 0x06, 1102
	.byte	"?", 0xEE, 0x9C, 0x00, 1106
	.byte	"?", 0xC4, 0x53, 0x31, 1113
	.byte	"?", 0xEE, 0x87, 0x51, 1114
	.byte	"?", 0xA3, 0x52, 0x14, 1115
	.byte	"?", 0xF8, 0xC0, 0x00, 1120
	.byte	"?", 0xB7, 0x97, 0x6B, 1123
	.byte	"?", 0x9D, 0x5A, 0x21, 1134
	.byte	"?", 0xF3, 0xD8, 0xA8, 1140
	.byte	"?", 0xFA, 0xCF, 0xAE, 1141
	.byte	"?", 0xDF, 0xC8, 0xAB, 1172
	.byte	"?", 0xE8, 0x97, 0x63, 1211
	.byte	"?", 0xF1, 0xA2, 0x36, 1220
	.byte	"?", 0x3D, 0x27, 0x23, 1276
	.byte	"?", 0xE5, 0x57, 0x1D, 1300
	.byte	"?", 0xE8, 0x64, 0x3C, 1302
	.byte	"?", 0xE4, 0x50, 0x1E, 1304
	.byte	"?", 0xEA, 0x71, 0x34, 1305
	.byte	"?", 0xE1, 0x2A, 0x23, 1306
	.byte	"?", 0xC1, 0x48, 0x17, 1311
	.byte	"?", 0xC4, 0x53, 0x31, 1312
	.byte	"?", 0xD7, 0x62, 0x3E, 1313
	.byte	"?", 0xED, 0x7C, 0x56, 1320
	.byte	"?", 0x92, 0x29, 0x1B, 1324
	.byte	"?", 0xD5, 0x81, 0x5E, 1332
	.byte	"?", 0xBB, 0x3D, 0x2E, 1334
	.byte	"?", 0xBE, 0x2D, 0x1A, 1335
	.byte	"?", 0x5F, 0x1B, 0x23, 1342
	.byte	"?", 0x7A, 0x34, 0x41, 1346
	.byte	"?", 0x84, 0x29, 0x1D, 1348
	.byte	"?", 0xFB, 0xBF, 0x95, 1351
	.byte	"?", 0xF4, 0xA7, 0x73, 1352
	.byte	"?", 0x69, 0x39, 0x20, 1355
	.byte	"?", 0xF9, 0xC6, 0xA1, 1361
	.byte	"?", 0xF9, 0xC5, 0x98, 1362
	.byte	"?", 0x43, 0x27, 0x31, 1366
	.byte	"?", 0x46, 0x45, 0x37, 1375
	.byte	"?", 0x4D, 0x2E, 0x18, 1376
	.byte	"?", 0xD6, 0x4F, 0x42, 1421
	.byte	"?", 0xF4, 0xA7, 0x82, 1430
	.byte	"?", 0xE2, 0x2D, 0x2A, 1501
	.byte	"?", 0xA9, 0x31, 0x21, 1514
	.byte	"?", 0xEC, 0x71, 0x68, 1521
	.byte	"?", 0xF6, 0xB0, 0x8E, 1532
	.byte	"?", 0xF9, 0xC5, 0xB9, 1551
	.byte	"?", 0x80, 0x6A, 0x61, 1565
	.byte	"?", 0x46, 0x45, 0x37, 1573
	.byte	"?", 0xE3, 0x6C, 0x63, 1600
	.byte	"?", 0xF9, 0xC7, 0xB9, 1630
	.byte	"?", 0xE4, 0x47, 0x33, 1701
	.byte	"?", 0xDF, 0x00, 0x32, 1703
	.byte	"?", 0xE4, 0x47, 0x33, 1705
	.byte	"?", 0xCF, 0x00, 0x40, 1725
	.byte	"?", 0xDB, 0x68, 0x6B, 1750
	.byte	"?", 0xF1, 0xCD, 0xCE, 1755
	.byte	"?", 0xE9, 0xC9, 0xBD, 1760
	.byte	"?", 0xE8, 0xC0, 0xB8, 1761
	.byte	"?", 0xE0, 0x00, 0x46, 1800
	.byte	"?", 0xE4, 0x34, 0x49, 1802
	.byte	"?", 0xD6, 0x44, 0x5D, 1805
	.byte	"?", 0xF4, 0x9E, 0x95, 1840
	.byte	"?", 0xB7, 0x66, 0x63, 1842
	.byte	"?", 0xE3, 0x6C, 0x63, 1849
	.byte	"?", 0xF0, 0x88, 0x7D, 1850
	.byte	"?", 0xFA, 0xC7, 0xC1, 1855
	.byte	"?", 0xFC, 0xDA, 0xD5, 1860
	.byte	"?", 0xFD, 0xE3, 0xD3, 1870
	.byte	"?", 0x63, 0x62, 0x54, 1874
	.byte	"?", 0x39, 0x45, 0x35, 1876
	.byte	"?", 0xE1, 0x00, 0x57, 1900
	.byte	"?", 0xBD, 0x00, 0x41, 1902
	.byte	"?", 0xC0, 0x03, 0x43, 1903
	.byte	"?", 0xA9, 0x02, 0x3A, 1904
	.byte	"?", 0x96, 0x00, 0x18, 1905
	.byte	"?", 0xBE, 0x00, 0x4F, 1906
	.byte	"?", 0x91, 0x02, 0x30, 1911
	.byte	"?", 0x86, 0x02, 0x3E, 1912
	.byte	"?", 0x9A, 0x0C, 0x3B, 1913
	.byte	"?", 0xA4, 0x1F, 0x39, 1914
	.byte	"?", 0xA3, 0x30, 0x50, 1921
	.byte	"?", 0xF2, 0x8D, 0xA6, 1940
	.byte	"?", 0xCE, 0x42, 0x7A, 1950
	.byte	"?", 0xF2, 0xB9, 0xBE, 1960
	.byte	"?", 0x95, 0x95, 0x95, 1972
	.byte	"?", 0xA3, 0x31, 0x45, 2011
	.byte	"?", 0x9F, 0x45, 0x4C, 2022
	.byte	"?", 0xC7, 0x97, 0x9B, 2051
	.byte	"?", 0xD1, 0x8D, 0x89, 2053
	.byte	"?", 0x97, 0x00, 0x38, 2100
	.byte	"?", 0x9F, 0x00, 0x3F, 2101
	.byte	"?", 0x78, 0x09, 0x3F, 2113
	.byte	"?", 0x43, 0x27, 0x32, 2123
	.byte	"?", 0xE6, 0x77, 0x8B, 2152
	.byte	"?", 0xDF, 0x83, 0x90, 2153
	.byte	"?", 0xF9, 0xBF, 0xC0, 2155
	.byte	"?", 0xFB, 0xD1, 0xD6, 2160
	.byte	"?", 0xFD, 0xE3, 0xDB, 2165
	.byte	"?", 0xD8, 0xD5, 0xD0, 2166
	.byte	"?", 0xFE, 0xED, 0xE2, 2168
	.byte	"?", 0xF7, 0xDE, 0xD6, 2170
	.byte	"?", 0xF7, 0xDE, 0xDE, 2171
	.byte	"?", 0xFC, 0xD9, 0xC4, 2180
	.byte	"?", 0xE8, 0x41, 0x8C, 2220
	.byte	"?", 0x8C, 0x0C, 0x4A, 2222
	.byte	"?", 0x88, 0x3A, 0x40, 2224
	.byte	"?", 0xEE, 0x71, 0xA1, 2230
	.byte	"?", 0xA9, 0x5A, 0x68, 2241
	.byte	"?", 0xFA, 0xC8, 0xD3, 2250
	.byte	"?", 0xD3, 0x00, 0x7E, 2300
	.byte	"?", 0xBF, 0x00, 0x6A, 2310
	.byte	"?", 0xD2, 0x00, 0x67, 2320
	.byte	"?", 0x78, 0x0C, 0x38, 2332
	.byte	"?", 0x65, 0x15, 0x33, 2333
	.byte	"?", 0x3A, 0x21, 0x2B, 2336
	.byte	"?", 0xF2, 0xE0, 0xDC, 2360
	.byte	"?", 0xFD, 0xE5, 0xEC, 2363
	.byte	"?", 0x97, 0x00, 0x59, 2500
	.byte	"?", 0x8B, 0x17, 0x71, 2502
	.byte	"?", 0xAA, 0x43, 0x81, 2504
	.byte	"?", 0xB4, 0x00, 0x73, 2505
	.byte	"?", 0x82, 0x00, 0x52, 2506
	.byte	"?", 0xD6, 0x3C, 0x81, 2513
	.byte	"?", 0xE2, 0x00, 0x78, 2520
	.byte	"?", 0xBF, 0x00, 0x6A, 2521
	.byte	"?", 0xEE, 0x71, 0xA1, 2524
	.byte	"?", 0xF1, 0x89, 0xAF, 2550
	.byte	"?", 0xF7, 0xB4, 0xCA, 2555
	.byte	"?", 0xF7, 0xB4, 0xCA, 2560
	.byte	"?", 0x49, 0x49, 0x49, 2576
	.byte	"?", 0x39, 0x42, 0x48, 2578
	.byte	"?", 0x89, 0x34, 0x80, 2600
	.byte	"?", 0x6C, 0x00, 0x51, 2611
	.byte	"?", 0xCD, 0x73, 0xA6, 2620
	.byte	"?", 0xD9, 0x94, 0xB9, 2640
	.byte	"?", 0xDD, 0xBD, 0xD5, 2645
	.byte	"?", 0xE6, 0xB7, 0xCF, 2650
	.byte	"?", 0xEC, 0xD2, 0xDE, 2655
	.byte	"?", 0x60, 0x6D, 0x8C, 2674
	.byte	"?", 0x64, 0x6A, 0x6E, 2675
	.byte	"?", 0x61, 0x00, 0x51, 2711
	.byte	"?", 0x70, 0x41, 0x91, 2712
	.byte	"?", 0x49, 0x02, 0x51, 2715
	.byte	"?", 0x2F, 0x20, 0x6F, 2743
	.byte	"?", 0xC6, 0x90, 0xA1, 2764
	.byte	"?", 0x6F, 0x06, 0x7B, 2810
	.byte	"?", 0xAD, 0x85, 0xB1, 2820
	.byte	"?", 0xA9, 0x74, 0xAB, 2830
	.byte	"?", 0x4C, 0x0F, 0x7B, 2900
	.byte	"?", 0x66, 0x40, 0x90, 2905
	.byte	"?", 0x83, 0x58, 0x9D, 2910
	.byte	"?", 0x8C, 0x6D, 0xAA, 2920
	.byte	"?", 0xC9, 0xB5, 0xD4, 3040
	.byte	"?", 0xC7, 0x90, 0xBA, 3045
	.byte	"?", 0x70, 0x70, 0x70, 3062
	.byte	"?", 0x2A, 0x37, 0x7E, 3102
	.byte	"?", 0x3C, 0x1F, 0x81, 3103
	.byte	"?", 0x35, 0x24, 0x7A, 3110
	.byte	"?", 0x26, 0x07, 0x51, 3114
	.byte	"?", 0x28, 0x13, 0x5B, 3133
	.byte	"?", 0x6E, 0x5D, 0xA3, 3200
	.byte	"?", 0x35, 0x3A, 0x90, 3210
	.byte	"?", 0x52, 0x4A, 0x90, 3211
	.byte	"?", 0x78, 0x5F, 0xA3, 3213
	.byte	"?", 0x24, 0x17, 0x57, 3222
	.byte	"?", 0x7D, 0x77, 0xAF, 3241
	.byte	"?", 0x90, 0x83, 0xA3, 3251
	.byte	"?", 0xB2, 0xAA, 0xBD, 3262
	.byte	"?", 0x39, 0x2D, 0x88, 3301
	.byte	"?", 0x56, 0x61, 0xA8, 3321
	.byte	"?", 0x32, 0x38, 0x87, 3322
	.byte	"?", 0x14, 0x21, 0x4E, 3323
	.byte	"?", 0x3A, 0x28, 0x85, 3330
	.byte	"?", 0x7F, 0x8B, 0xC2, 3331
	.byte	"?", 0x1B, 0x3C, 0x78, 3333
	.byte	"?", 0xB9, 0xBD, 0xD9, 3340
	.byte	"?", 0x11, 0x26, 0x3C, 3344
	.byte	"?", 0x20, 0x2A, 0x65, 3353
	.byte	"?", 0x17, 0x1B, 0x4A, 3355
	.byte	"?", 0x95, 0x9A, 0xCA, 3420
	.byte	"?", 0x6A, 0x76, 0xB5, 3430
	.byte	"?", 0x11, 0x26, 0x3C, 3443
	.byte	"?", 0x00, 0x22, 0x32, 3444
	.byte	"?", 0x2D, 0x44, 0x91, 3522
	.byte	"?", 0x26, 0x12, 0x57, 3536
	.byte	"?", 0x53, 0x42, 0x8A, 3540
	.byte	"?", 0x3A, 0x28, 0x85, 3541
	.byte	"?", 0x23, 0x3B, 0x7D, 3543
	.byte	"?", 0x27, 0x3C, 0x82, 3544
	.byte	"?", 0x27, 0x26, 0x51, 3554
	.byte	"?", 0x28, 0x43, 0x8C, 3600
	.byte	"?", 0x24, 0x3A, 0x7D, 3611
	.byte	"?", 0x40, 0x55, 0xA1, 3612
	.byte	"?", 0x1A, 0x4C, 0x8D, 3622
	.byte	"?", 0x1E, 0x56, 0x9F, 3631
	.byte	"?", 0x92, 0xB1, 0xDC, 3640
	.byte	"?", 0x64, 0x8D, 0xC7, 3641
	.byte	"?", 0xD0, 0xDE, 0xEE, 3650
	.byte	"?", 0xEA, 0xF0, 0xF9, 3661
	.byte	"?", 0x00, 0x50, 0x7F, 3732
	.byte	"?", 0x12, 0x25, 0x3C, 3743
	.byte	"?", 0xB7, 0xD1, 0xE3, 3750
	.byte	"?", 0xD0, 0xDE, 0xEE, 3752
	.byte	"?", 0xAF, 0xC9, 0xE5, 3761
	.byte	"?", 0xCE, 0xD2, 0xD1, 3770
	.byte	"?", 0x3D, 0x6A, 0xA1, 3810
	.byte	"?", 0x91, 0xB9, 0xE2, 3820
	.byte	"?", 0x00, 0x77, 0x9E, 3822
	.byte	"?", 0xB4, 0xCE, 0xEB, 3840
	.byte	"?", 0x50, 0x71, 0x93, 3842
	.byte	"?", 0xD5, 0xE3, 0xF4, 3845
	.byte	"?", 0x9A, 0xB8, 0xD3, 3851
	.byte	"?", 0x00, 0x7E, 0xBA, 3900
	.byte	"?", 0x00, 0x82, 0xC4, 3901
	.byte	"?", 0x00, 0x6C, 0xA5, 3902
	.byte	"?", 0x4A, 0xBD, 0xF0, 3910
	.byte	"?", 0x86, 0xAA, 0xCA, 3951
	.byte	"?", 0x48, 0x5E, 0x8A, 3952
	.byte	"?", 0x69, 0x76, 0x98, 3953
	.byte	"?", 0xC5, 0xE1, 0xF3, 3961
	.byte	"?", 0xA6, 0xD8, 0xF6, 3962
	.byte	"?", 0xE1, 0xE1, 0xE1, 3971
	.byte	"?", 0x00, 0x93, 0xB9, 4010
	.byte	"?", 0x00, 0x65, 0x87, 4022
	.byte	"?", 0x87, 0xC7, 0xEA, 4030
	.byte	"?", 0x50, 0x77, 0x93, 4032
	.byte	"?", 0x26, 0x56, 0x74, 4033
	.byte	"?", 0x9E, 0xD4, 0xE6, 4040
	.byte	"?", 0xEA, 0xF0, 0xF9, 4071
	.byte	"?", 0x00, 0x96, 0xC1, 4100
	.byte	"?", 0x2D, 0xB0, 0xCF, 4101
	.byte	"?", 0x00, 0x95, 0xC6, 4103
	.byte	"?", 0x00, 0x81, 0xAA, 4105
	.byte	"?", 0x00, 0xA4, 0xD9, 4111
	.byte	"?", 0x00, 0xA9, 0xC9, 4113
	.byte	"?", 0x5D, 0xBF, 0xD2, 4121
	.byte	"?", 0x00, 0x40, 0x5D, 4133
	.byte	"?", 0x19, 0x20, 0x24, 4174
	.byte	"?", 0x19, 0x20, 0x24, 4175
	.byte	"?", 0x4F, 0xB4, 0xCB, 4220
	.byte	"?", 0x8D, 0xCE, 0xE4, 4230
	.byte	"?", 0x2D, 0xB0, 0xCF, 4231
	.byte	"?", 0x00, 0x65, 0x87, 4232
	.byte	"?", 0x8D, 0xCD, 0xDB, 4240
	.byte	"?", 0xD5, 0xEB, 0xF2, 4250
	.byte	"?", 0x00, 0x73, 0x89, 4400
	.byte	"?", 0x00, 0x7B, 0x8D, 4410
	.byte	"?", 0x00, 0xB2, 0xCA, 4420
	.byte	"?", 0x00, 0x91, 0xA5, 4421
	.byte	"?", 0x00, 0x7D, 0x8C, 4423
	.byte	"?", 0x00, 0x79, 0x86, 4425
	.byte	"?", 0x5F, 0xBF, 0xD1, 4430
	.byte	"?", 0x00, 0x42, 0x50, 4432
	.byte	"?", 0x8D, 0xCE, 0xE4, 4440
	.byte	"?", 0x00, 0x69, 0x81, 4442
	.byte	"?", 0x00, 0x7F, 0x92, 4452
	.byte	"?", 0x00, 0x81, 0x92, 4500
	.byte	"?", 0x00, 0x70, 0x79, 4513
	.byte	"?", 0x00, 0x2F, 0x38, 4515
	.byte	"?", 0x00, 0x64, 0x6A, 4516
	.byte	"?", 0x00, 0x73, 0x89, 4531
	.byte	"?", 0x00, 0x7B, 0x8D, 4610
	.byte	"?", 0x00, 0xA3, 0xA0, 4620
	.byte	"?", 0x0B, 0x7F, 0x85, 4625
	.byte	"?", 0x00, 0x5B, 0x63, 4643
	.byte	"?", 0x23, 0x45, 0x44, 4644
	.byte	"?", 0x8C, 0xCD, 0xD3, 4840
	.byte	"?", 0x00, 0x6F, 0x73, 5000
	.byte	"?", 0x00, 0x5B, 0x63, 5005
	.byte	"?", 0x00, 0xA6, 0xAD, 5010
	.byte	"?", 0x49, 0xBA, 0xC0, 5020
	.byte	"?", 0xCF, 0xDD, 0xE0, 5040
	.byte	"?", 0xB4, 0xDC, 0xD8, 5050
	.byte	"?", 0x00, 0x87, 0x6E, 5100
	.byte	"?", 0x00, 0x90, 0x84, 5101
	.byte	"?", 0x00, 0xB1, 0xAE, 5111
	.byte	"?", 0x48, 0xBA, 0xB7, 5115
	.byte	"?", 0x00, 0xAF, 0x8C, 5210
	.byte	"?", 0x8C, 0xCC, 0xC2, 5220
	.byte	"?", 0x47, 0xB9, 0xAE, 5230
	.byte	"?", 0x19, 0x7E, 0x6D, 5233
	.byte	"?", 0x8C, 0xCC, 0xC2, 5240
	.byte	"?", 0x00, 0x5B, 0x63, 5255
	.byte	"?", 0x00, 0x6E, 0x42, 5324
	.byte	"?", 0x00, 0x4D, 0x3D, 5326
	.byte	"?", 0x00, 0x2F, 0x38, 5335
	.byte	"?", 0x00, 0x2D, 0x1F, 5374
	.byte	"?", 0x00, 0x2F, 0x38, 5375
	.byte	"?", 0x00, 0x86, 0x63, 5411
	.byte	"?", 0x00, 0x6B, 0x4E, 5415
	.byte	"?", 0x00, 0x86, 0x63, 5422
	.byte	"?", 0x00, 0x6B, 0x56, 5425
	.byte	"?", 0x00, 0x88, 0x79, 5431
	.byte	"?", 0xDB, 0xE9, 0xE5, 5460
	.byte	"?", 0x6A, 0xC0, 0x93, 5470
	.byte	"?", 0x52, 0xBA, 0x84, 5500
	.byte	"?", 0x14, 0xA3, 0x63, 5510
	.byte	"?", 0x00, 0x78, 0x48, 5513
	.byte	"?", 0x00, 0x86, 0x63, 5515
	.byte	"?", 0x52, 0xA0, 0x4F, 5531
	.byte	"?", 0x6E, 0xA2, 0x93, 5542
	.byte	"?", 0x94, 0xAD, 0xA1, 5552
	.byte	"?", 0x10, 0x38, 0x28, 5555
	.byte	"?", 0x63, 0xBE, 0x5F, 5600
	.byte	"?", 0x85, 0xC8, 0x75, 5610
	.byte	"?", 0x2C, 0xB4, 0x31, 5611
	.byte	"?", 0x14, 0xB2, 0x6D, 5613
	.byte	"?", 0x40, 0xB7, 0x80, 5620
	.byte	"?", 0x1A, 0x78, 0x1E, 5633
	.byte	"?", 0x15, 0x74, 0x36, 5643
	.byte	"?", 0xC9, 0xE3, 0xC5, 5650
	.byte	"?", 0x6B, 0x91, 0x81, 5664
	.byte	"?", 0x3A, 0x6D, 0x57, 5765
	.byte	"?", 0x10, 0x38, 0x28, 5766
	.byte	"?", 0x02, 0x14, 0x0C, 5776
	.byte	"?", 0xA5, 0xC2, 0x78, 5822
	.byte	"?", 0xB4, 0xD3, 0x83, 5832
	.byte	"?", 0x70, 0x95, 0x3F, 5833
	.byte	"?", 0xA2, 0xD2, 0x89, 5840
	.byte	"?", 0x27, 0x30, 0x14, 5866
	.byte	"?", 0x81, 0xC7, 0x50, 5912
	.byte	"?", 0x45, 0x70, 0x21, 5933
	.byte	"?", 0x50, 0x67, 0x02, 5934
	.byte	"?", 0xBB, 0xDB, 0x41, 5940
	.byte	"?", 0x00, 0x35, 0x18, 5944
	.byte	"?", 0xE3, 0xEB, 0x00, 6010
	.byte	"?", 0xBE, 0xD7, 0x82, 6051
	.byte	"?", 0x2D, 0x3B, 0x01, 6065
	.byte	"?", 0xDC, 0xDD, 0xD1, 6071
	.byte	"?", 0x91, 0x96, 0x00, 6133
	.byte	"?", 0x48, 0x46, 0x01, 6156
isafil_rayon_end:


marathon_polyester_codes:
marathon_polyester_end:


marathon_rayon_codes:
marathon_rayon_end:


madeira_polyester_codes:
madeira_polyester_end:


madeira_rayon_codes:
madeira_rayon_end:


metro_polyester_codes:
metro_polyester_end:


pantone_codes:
	.byte	"?", 0xFF, 0xFF, 0x7D, 100
	.byte	"?", 0xFF, 0xFF, 0x36, 101
	.byte	"?", 0xFF, 0xFC, 0x0D, 102
	.byte	"?", 0xD1, 0xCB, 0x00, 103
	.byte	"?", 0xB3, 0xAD, 0x00, 104
	.byte	"?", 0x80, 0x7C, 0x00, 105
	.byte	"?", 0xFF, 0xFA, 0x4F, 106
	.byte	"?", 0xFF, 0xF5, 0x36, 107
	.byte	"?", 0xFF, 0xF0, 0x0D, 108
	.byte	"?", 0xFF, 0xE6, 0x00, 109
	.byte	"?", 0xED, 0xD1, 0x00, 110
	.byte	"?", 0xBA, 0xA6, 0x00, 111
	.byte	"?", 0x9E, 0x8E, 0x00, 112
	.byte	"?", 0xFF, 0xED, 0x57, 113
	.byte	"?", 0xFF, 0xEB, 0x45, 114
	.byte	"?", 0xFF, 0xE8, 0x33, 115
	.byte	"?", 0xFF, 0xD6, 0x00, 116
	.byte	"?", 0xD9, 0xB2, 0x00, 117
	.byte	"?", 0xBA, 0x99, 0x00, 118
	.byte	"?", 0x82, 0x72, 0x00, 119
	.byte	"?", 0xFF, 0xE8, 0x6B, 120
	.byte	"?", 0xFF, 0xF2, 0xB0, 1205
	.byte	"?", 0xFF, 0xE3, 0x4F, 121
	.byte	"?", 0xFF, 0xE8, 0x8C, 1215
	.byte	"?", 0xFF, 0xD4, 0x33, 122
	.byte	"?", 0xFF, 0xD4, 0x61, 1225
	.byte	"?", 0xFF, 0xC2, 0x0F, 123
	.byte	"?", 0xFF, 0xB5, 0x17, 1235
	.byte	"?", 0xF0, 0xAD, 0x00, 124
	.byte	"?", 0xD1, 0x97, 0x00, 1245
	.byte	"?", 0xBD, 0x8C, 0x00, 125
	.byte	"?", 0xA8, 0x7B, 0x00, 1255
	.byte	"?", 0xA1, 0x78, 0x00, 126
	.byte	"?", 0x7D, 0x5B, 0x00, 1265
	.byte	"?", 0xFF, 0xED, 0x80, 127
	.byte	"?", 0xFF, 0xE3, 0x59, 128
	.byte	"?", 0xFF, 0xD6, 0x3B, 129
	.byte	"?", 0xFF, 0xB3, 0x00, 130
	.byte	"?", 0xE8, 0x9E, 0x00, 131
	.byte	"?", 0xB3, 0x81, 0x00, 132
	.byte	"?", 0x70, 0x5A, 0x00, 133
	.byte	"?", 0xFF, 0xE3, 0x8C, 134
	.byte	"?", 0xFF, 0xDB, 0x87, 1345
	.byte	"?", 0xFF, 0xCF, 0x66, 135
	.byte	"?", 0xFF, 0xCC, 0x70, 1355
	.byte	"?", 0xFF, 0xBA, 0x3D, 136
	.byte	"?", 0xFF, 0xB5, 0x47, 1365
	.byte	"?", 0xFF, 0xA6, 0x1A, 137
	.byte	"?", 0xFF, 0x99, 0x1A, 1375
	.byte	"?", 0xFC, 0x92, 0x00, 138
	.byte	"?", 0xED, 0x85, 0x00, 1385
	.byte	"?", 0xC4, 0x7C, 0x00, 139
	.byte	"?", 0xA1, 0x5F, 0x00, 1395
	.byte	"?", 0x75, 0x56, 0x00, 140
	.byte	"?", 0x5E, 0x3C, 0x00, 1405
	.byte	"?", 0xFF, 0xCF, 0x7D, 141
	.byte	"?", 0xFF, 0xB8, 0x3D, 142
	.byte	"?", 0xFF, 0xA6, 0x26, 143
	.byte	"?", 0xFF, 0x85, 0x00, 144
	.byte	"?", 0xEB, 0x7C, 0x00, 145
	.byte	"?", 0xAB, 0x61, 0x00, 146
	.byte	"?", 0x70, 0x51, 0x00, 147
	.byte	"?", 0xFF, 0xD6, 0xA1, 148
	.byte	"?", 0xFF, 0xBA, 0x75, 1485
	.byte	"?", 0xFF, 0xC4, 0x87, 149
	.byte	"?", 0xFF, 0xAB, 0x54, 1495
	.byte	"?", 0xFF, 0xA6, 0x4D, 150
	.byte	"?", 0xFF, 0x94, 0x3B, 1505
	.byte	"?", 0xFF, 0x85, 0x0D, 151
	.byte	"?", 0xFC, 0x7C, 0x00, 152
	.byte	"?", 0xE6, 0x60, 0x00, 1525
	.byte	"?", 0xD1, 0x71, 0x00, 153
	.byte	"?", 0x9E, 0x4A, 0x00, 1535
	.byte	"?", 0xA8, 0x5B, 0x00, 154
	.byte	"?", 0x47, 0x22, 0x00, 1545
	.byte	"?", 0xFF, 0xE0, 0xB8, 155
	.byte	"?", 0xFF, 0xC7, 0xA8, 1555
	.byte	"?", 0xFF, 0xC7, 0x94, 156
	.byte	"?", 0xFF, 0xA8, 0x82, 1565
	.byte	"?", 0xFF, 0x91, 0x4D, 157
	.byte	"?", 0xFF, 0x8C, 0x47, 1575
	.byte	"?", 0xFF, 0x63, 0x08, 158
	.byte	"?", 0xFF, 0x70, 0x1A, 1585
	.byte	"?", 0xED, 0x51, 0x00, 159
	.byte	"?", 0xF2, 0x63, 0x00, 1595
	.byte	"?", 0xAD, 0x42, 0x00, 160
	.byte	"?", 0xB3, 0x4F, 0x00, 1605
	.byte	"?", 0x5C, 0x2C, 0x00, 161
	.byte	"?", 0x91, 0x40, 0x00, 1615
	.byte	"?", 0xFF, 0xD9, 0xC7, 162
	.byte	"?", 0xFF, 0xB0, 0xA1, 1625
	.byte	"?", 0xFF, 0xB0, 0x8F, 163
	.byte	"?", 0xFF, 0x9C, 0x85, 1635
	.byte	"?", 0xFF, 0x8A, 0x45, 164
	.byte	"?", 0xFF, 0x82, 0x57, 1645
	.byte	"?", 0xFF, 0x69, 0x0A, 165
	.byte	"?", 0xFF, 0x5E, 0x17, 1655
	.byte	"?", 0xFF, 0x5C, 0x00, 166
	.byte	"?", 0xFF, 0x52, 0x00, 1665
	.byte	"?", 0xD4, 0x55, 0x00, 167
	.byte	"?", 0xB8, 0x3D, 0x00, 1675
	.byte	"?", 0x69, 0x2D, 0x00, 168
	.byte	"?", 0x8F, 0x2E, 0x00, 1685
	.byte	"?", 0xFF, 0xCC, 0xCC, 169
	.byte	"?", 0xFF, 0x99, 0x8F, 170
	.byte	"?", 0xFF, 0x78, 0x52, 171
	.byte	"?", 0xFF, 0x57, 0x1F, 172
	.byte	"?", 0xF5, 0x4C, 0x00, 173
	.byte	"?", 0xA3, 0x31, 0x00, 174
	.byte	"?", 0x66, 0x24, 0x00, 175
	.byte	"?", 0xFF, 0xBF, 0xD1, 176
	.byte	"?", 0xFF, 0x9E, 0xC9, 1765
	.byte	"?", 0xFF, 0xBA, 0xE0, 1767
	.byte	"?", 0xFF, 0x8C, 0x99, 177
	.byte	"?", 0xFF, 0x87, 0xB5, 1775
	.byte	"?", 0xFF, 0x6B, 0xA3, 1777
	.byte	"?", 0xFF, 0x69, 0x70, 178
	.byte	"?", 0xFF, 0x54, 0x80, 1785
	.byte	"?", 0xFF, 0x3D, 0x66, 1787
	.byte	"?", 0xFF, 0x29, 0x1F, 1788
	.byte	"?", 0xFF, 0x36, 0x00, 179
	.byte	"?", 0xFF, 0x0F, 0x00, 1795
	.byte	"?", 0xF5, 0x00, 0x02, 1797
	.byte	"?", 0xE3, 0x30, 0x00, 180
	.byte	"?", 0xC4, 0x12, 0x00, 1805
	.byte	"?", 0xB8, 0x00, 0x07, 1807
	.byte	"?", 0x87, 0x23, 0x00, 181
	.byte	"?", 0x7D, 0x0C, 0x00, 1815
	.byte	"?", 0x57, 0x09, 0x00, 1817
	.byte	"?", 0xFF, 0xBD, 0xE6, 182
	.byte	"?", 0xFF, 0x8A, 0xC9, 183
	.byte	"?", 0xFF, 0x52, 0x96, 184
	.byte	"?", 0xFF, 0x17, 0x3D, 185
	.byte	"?", 0xF5, 0x00, 0x2F, 186
	.byte	"?", 0xCC, 0x00, 0x2B, 187
	.byte	"?", 0x80, 0x04, 0x00, 188
	.byte	"?", 0xFF, 0xA1, 0xE6, 189
	.byte	"?", 0xFF, 0xB8, 0xED, 1895
	.byte	"?", 0xFF, 0x73, 0xC7, 190
	.byte	"?", 0xFF, 0x96, 0xE8, 1905
	.byte	"?", 0xFF, 0x3D, 0x9E, 191
	.byte	"?", 0xFF, 0x4A, 0xCC, 1915
	.byte	"?", 0xFF, 0x00, 0x52, 192
	.byte	"?", 0xFF, 0x00, 0x73, 1925
	.byte	"?", 0xDE, 0x00, 0x4B, 193
	.byte	"?", 0xF2, 0x00, 0x68, 1935
	.byte	"?", 0xAB, 0x00, 0x3E, 194
	.byte	"?", 0xCF, 0x00, 0x5B, 1945
	.byte	"?", 0x73, 0x00, 0x2E, 195
	.byte	"?", 0xA1, 0x00, 0x40, 1955
	.byte	"?", 0xFF, 0xBF, 0xF5, 196
	.byte	"?", 0xFF, 0x8C, 0xE6, 197
	.byte	"?", 0xFF, 0x38, 0xAB, 198
	.byte	"?", 0xFF, 0x00, 0x61, 199
	.byte	"?", 0xE0, 0x00, 0x53, 200
	.byte	"?", 0xB5, 0x00, 0x43, 201
	.byte	"?", 0x91, 0x00, 0x39, 202
	.byte	"?", 0xFF, 0xA8, 0xF7, 203
	.byte	"?", 0xFF, 0x6B, 0xF7, 204
	.byte	"?", 0xFF, 0x29, 0xE8, 205
	.byte	"?", 0xF7, 0x00, 0x99, 206
	.byte	"?", 0xCF, 0x00, 0x76, 207
	.byte	"?", 0xA1, 0x00, 0x67, 208
	.byte	"?", 0x78, 0x00, 0x4F, 209
	.byte	"?", 0xFF, 0x9C, 0xF0, 210
	.byte	"?", 0xFF, 0x73, 0xEB, 211
	.byte	"?", 0xFF, 0x47, 0xE3, 212
	.byte	"?", 0xFF, 0x0D, 0xBA, 213
	.byte	"?", 0xEB, 0x00, 0x9B, 214
	.byte	"?", 0xBA, 0x00, 0x79, 215
	.byte	"?", 0x82, 0x07, 0x4E, 216
	.byte	"?", 0xFF, 0xB8, 0xFF, 217
	.byte	"?", 0xFA, 0x63, 0xFF, 218
	.byte	"?", 0xFC, 0x1F, 0xFF, 219
	.byte	"?", 0xD4, 0x00, 0xB8, 220
	.byte	"?", 0xB3, 0x00, 0x98, 221
	.byte	"?", 0x69, 0x00, 0x5E, 222
	.byte	"?", 0xFF, 0x8A, 0xFF, 223
	.byte	"?", 0xFC, 0x5E, 0xFF, 224
	.byte	"?", 0xFC, 0x2B, 0xFF, 225
	.byte	"?", 0xFF, 0x00, 0xFF, 226
	.byte	"?", 0xCF, 0x00, 0xC0, 227
	.byte	"?", 0x96, 0x00, 0x90, 228
	.byte	"?", 0x66, 0x00, 0x57, 229
	.byte	"?", 0xFF, 0xA8, 0xFF, 230
	.byte	"?", 0xFC, 0x7A, 0xFF, 231
	.byte	"?", 0xF7, 0x54, 0xFF, 232
	.byte	"?", 0xE3, 0x00, 0xFF, 233
	.byte	"?", 0xB1, 0x00, 0xBD, 234
	.byte	"?", 0x91, 0x00, 0x99, 235
	.byte	"?", 0xFC, 0xB3, 0xFF, 236
	.byte	"?", 0xFA, 0xBA, 0xFF, 2365
	.byte	"?", 0xF7, 0x82, 0xFF, 237
	.byte	"?", 0xE6, 0x6E, 0xFF, 2375
	.byte	"?", 0xF0, 0x5E, 0xFF, 238
	.byte	"?", 0xCF, 0x36, 0xFF, 2385
	.byte	"?", 0xE3, 0x36, 0xFF, 239
	.byte	"?", 0xBA, 0x0D, 0xFF, 2395
	.byte	"?", 0xD1, 0x0F, 0xFF, 240
	.byte	"?", 0xA8, 0x00, 0xFF, 2405
	.byte	"?", 0xB6, 0x00, 0xFA, 241
	.byte	"?", 0x9D, 0x00, 0xEB, 2415
	.byte	"?", 0x75, 0x00, 0x82, 242
	.byte	"?", 0x77, 0x00, 0xBD, 2425
	.byte	"?", 0xF2, 0xB5, 0xFF, 243
	.byte	"?", 0xE8, 0x9E, 0xFF, 244
	.byte	"?", 0xDB, 0x78, 0xFF, 245
	.byte	"?", 0xB5, 0x1A, 0xFF, 246
	.byte	"?", 0xA3, 0x00, 0xFF, 247
	.byte	"?", 0x96, 0x00, 0xFA, 248
	.byte	"?", 0x6E, 0x00, 0xB8, 249
	.byte	"?", 0xF2, 0xD1, 0xFF, 250
	.byte	"?", 0xDE, 0x9C, 0xFF, 251
	.byte	"?", 0xC2, 0x70, 0xFF, 252
	.byte	"?", 0x91, 0x0D, 0xFF, 253
	.byte	"?", 0x80, 0x00, 0xFF, 254
	.byte	"?", 0x5E, 0x00, 0xBF, 255
	.byte	"?", 0xED, 0xCC, 0xFF, 256
	.byte	"?", 0xCF, 0xA6, 0xFF, 2562
	.byte	"?", 0xC7, 0xAB, 0xFF, 2563
	.byte	"?", 0xB5, 0xA3, 0xFF, 2567
	.byte	"?", 0xDB, 0xA8, 0xFF, 257
	.byte	"?", 0xB3, 0x87, 0xFF, 2572
	.byte	"?", 0xB3, 0x91, 0xFF, 2573
	.byte	"?", 0x99, 0x8C, 0xFF, 2577
	.byte	"?", 0x91, 0x3D, 0xFF, 258
	.byte	"?", 0x8A, 0x47, 0xFF, 2582
	.byte	"?", 0x8A, 0x5E, 0xFF, 2583
	.byte	"?", 0x69, 0x57, 0xFF, 2587
	.byte	"?", 0x5F, 0x00, 0xD9, 259
	.byte	"?", 0x66, 0x1A, 0xFF, 2592
	.byte	"?", 0x63, 0x1C, 0xFF, 2593
	.byte	"?", 0x26, 0x00, 0xFF, 2597
	.byte	"?", 0x5B, 0x00, 0xBD, 260
	.byte	"?", 0x5C, 0x00, 0xF7, 2602
	.byte	"?", 0x4D, 0x00, 0xFA, 2603
	.byte	"?", 0x2D, 0x00, 0xED, 2607
	.byte	"?", 0x50, 0x00, 0x99, 261
	.byte	"?", 0x4F, 0x00, 0xDB, 2612
	.byte	"?", 0x50, 0x00, 0xD9, 2613
	.byte	"?", 0x2E, 0x00, 0xD9, 2617
	.byte	"?", 0x3F, 0x00, 0x73, 262
	.byte	"?", 0x3C, 0x00, 0x8F, 2622
	.byte	"?", 0x47, 0x00, 0xAD, 2623
	.byte	"?", 0x28, 0x00, 0xB0, 2627
	.byte	"?", 0xE6, 0xDB, 0xFF, 263
	.byte	"?", 0xB8, 0xBA, 0xFF, 2635
	.byte	"?", 0xBD, 0xB8, 0xFF, 264
	.byte	"?", 0x99, 0xA3, 0xFF, 2645
	.byte	"?", 0x75, 0x70, 0xFF, 265
	.byte	"?", 0x75, 0x82, 0xFF, 2655
	.byte	"?", 0x36, 0x1A, 0xFF, 266
	.byte	"?", 0x61, 0x66, 0xFF, 2665
	.byte	"?", 0x1C, 0x00, 0xFF, 267
	.byte	"?", 0x28, 0x00, 0xE0, 268
	.byte	"?", 0x09, 0x00, 0xE6, 2685
	.byte	"?", 0x26, 0x00, 0xAB, 269
	.byte	"?", 0x0C, 0x00, 0x82, 2695
	.byte	"?", 0xB0, 0xBA, 0xFF, 270
	.byte	"?", 0x99, 0xB3, 0xFF, 2705
	.byte	"?", 0xCF, 0xE8, 0xFF, 2706
	.byte	"?", 0xD4, 0xF0, 0xFF, 2707
	.byte	"?", 0xBD, 0xE6, 0xFF, 2708
	.byte	"?", 0x91, 0xA1, 0xFF, 271
	.byte	"?", 0x6E, 0x8C, 0xFF, 2715
	.byte	"?", 0x8C, 0xB5, 0xFF, 2716
	.byte	"?", 0xB5, 0xE0, 0xFF, 2717
	.byte	"?", 0x54, 0x96, 0xFF, 2718
	.byte	"?", 0x6B, 0x85, 0xFF, 272
	.byte	"?", 0x3B, 0x52, 0xFF, 2725
	.byte	"?", 0x36, 0x57, 0xFF, 2726
	.byte	"?", 0x4A, 0x94, 0xFF, 2727
	.byte	"?", 0x0A, 0x4F, 0xFF, 2728
	.byte	"?", 0x00, 0x09, 0xEB, 273
	.byte	"?", 0x00, 0x0D, 0xFF, 2735
	.byte	"?", 0x00, 0x17, 0xFF, 2736
	.byte	"?", 0x00, 0x20, 0xFA, 2738
	.byte	"?", 0x00, 0x00, 0xB8, 274
	.byte	"?", 0x00, 0x0B, 0xD9, 2745
	.byte	"?", 0x00, 0x12, 0xE6, 2746
	.byte	"?", 0x00, 0x1E, 0xD9, 2747
	.byte	"?", 0x00, 0x1A, 0xD9, 2748
	.byte	"?", 0x03, 0x00, 0x91, 275
	.byte	"?", 0x00, 0x05, 0xB3, 2755
	.byte	"?", 0x00, 0x0B, 0xB5, 2756
	.byte	"?", 0x00, 0x20, 0xB3, 2757
	.byte	"?", 0x00, 0x26, 0xBD, 2758
	.byte	"?", 0x02, 0x00, 0x73, 276
	.byte	"?", 0x00, 0x04, 0x8C, 2765
	.byte	"?", 0x00, 0x08, 0x87, 2766
	.byte	"?", 0x00, 0x1A, 0x75, 2767
	.byte	"?", 0x00, 0x1F, 0x8F, 2768
	.byte	"?", 0xBA, 0xED, 0xFF, 277
	.byte	"?", 0x9C, 0xDB, 0xFF, 278
	.byte	"?", 0x52, 0xA8, 0xFF, 279
	.byte	"?", 0x00, 0x3B, 0xD1, 280
	.byte	"?", 0x00, 0x31, 0xAD, 281
	.byte	"?", 0x00, 0x26, 0x75, 282
	.byte	"?", 0xA6, 0xE8, 0xFF, 283
	.byte	"?", 0x73, 0xCF, 0xFF, 284
	.byte	"?", 0x1C, 0x91, 0xFF, 285
	.byte	"?", 0x00, 0x55, 0xFA, 286
	.byte	"?", 0x00, 0x48, 0xE0, 287
	.byte	"?", 0x00, 0x41, 0xC4, 288
	.byte	"?", 0x00, 0x24, 0x6B, 289
	.byte	"?", 0xBF, 0xFA, 0xFF, 290
	.byte	"?", 0x96, 0xFA, 0xFF, 2905
	.byte	"?", 0xAB, 0xF7, 0xFF, 291
	.byte	"?", 0x69, 0xED, 0xFF, 2915
	.byte	"?", 0x82, 0xE3, 0xFF, 292
	.byte	"?", 0x26, 0xC2, 0xFF, 2925
	.byte	"?", 0x00, 0x6B, 0xFA, 293
	.byte	"?", 0x00, 0x8A, 0xFF, 2935
	.byte	"?", 0x00, 0x55, 0xC9, 294
	.byte	"?", 0x00, 0x79, 0xDB, 2945
	.byte	"?", 0x00, 0x45, 0xA1, 295
	.byte	"?", 0x00, 0x58, 0xA1, 2955
	.byte	"?", 0x00, 0x29, 0x4D, 296
	.byte	"?", 0x00, 0x39, 0x5C, 2965
	.byte	"?", 0x82, 0xFC, 0xFF, 297
	.byte	"?", 0xB3, 0xFF, 0xF2, 2975
	.byte	"?", 0x4F, 0xED, 0xFF, 298
	.byte	"?", 0x69, 0xFF, 0xF0, 2985
	.byte	"?", 0x26, 0xCF, 0xFF, 299
	.byte	"?", 0x1A, 0xE3, 0xFF, 2995
	.byte	"?", 0x00, 0x8F, 0xFF, 300
	.byte	"?", 0x00, 0xA0, 0xFA, 3005
	.byte	"?", 0x00, 0x73, 0xD1, 301
	.byte	"?", 0x00, 0x89, 0xCC, 3015
	.byte	"?", 0x00, 0x60, 0x80, 302
	.byte	"?", 0x00, 0x68, 0x7D, 3025
	.byte	"?", 0x00, 0x3B, 0x42, 303
	.byte	"?", 0x00, 0x47, 0x44, 3035
	.byte	"?", 0xB3, 0xFF, 0xEB, 304
	.byte	"?", 0x7D, 0xFF, 0xE8, 305
	.byte	"?", 0x40, 0xFF, 0xED, 306
	.byte	"?", 0x00, 0x9C, 0xBA, 307
	.byte	"?", 0x00, 0x80, 0x87, 308
	.byte	"?", 0x00, 0x47, 0x41, 309
	.byte	"?", 0x91, 0xFF, 0xE6, 310
	.byte	"?", 0x91, 0xFF, 0xE0, 3105
	.byte	"?", 0x5E, 0xFF, 0xE0, 311
	.byte	"?", 0x5E, 0xFF, 0xD1, 3115
	.byte	"?", 0x0A, 0xFF, 0xE3, 312
	.byte	"?", 0x2B, 0xFF, 0xC9, 3125
	.byte	"?", 0x00, 0xDE, 0xCC, 313
	.byte	"?", 0x00, 0xE8, 0xC3, 3135
	.byte	"?", 0x00, 0xB3, 0xA2, 314
	.byte	"?", 0x00, 0xC4, 0x9F, 3145
	.byte	"?", 0x00, 0x91, 0x80, 315
	.byte	"?", 0x00, 0x9E, 0x78, 3155
	.byte	"?", 0x00, 0x52, 0x3C, 316
	.byte	"?", 0x00, 0x59, 0x40, 3165
	.byte	"?", 0xD1, 0xFF, 0xEB, 317
	.byte	"?", 0x9E, 0xFF, 0xD9, 318
	.byte	"?", 0x7A, 0xFF, 0xCF, 319
	.byte	"?", 0x00, 0xED, 0xA4, 320
	.byte	"?", 0x00, 0xC4, 0x87, 321
	.byte	"?", 0x00, 0xA6, 0x6F, 322
	.byte	"?", 0x00, 0x87, 0x54, 323
	.byte	"?", 0xB8, 0xFF, 0xE0, 324
	.byte	"?", 0xA1, 0xFF, 0xD1, 3242
	.byte	"?", 0xA8, 0xFF, 0xCF, 3245
	.byte	"?", 0x91, 0xFF, 0xC2, 3248
	.byte	"?", 0x70, 0xFF, 0xBD, 325
	.byte	"?", 0x87, 0xFF, 0xC2, 3252
	.byte	"?", 0x82, 0xFF, 0xB8, 3255
	.byte	"?", 0x69, 0xFF, 0xAB, 3258
	.byte	"?", 0x21, 0xFF, 0x9E, 326
	.byte	"?", 0x4A, 0xFF, 0xAB, 3262
	.byte	"?", 0x4F, 0xFF, 0xA1, 3265
	.byte	"?", 0x1A, 0xFF, 0x82, 3268
	.byte	"?", 0x00, 0xD4, 0x77, 327
	.byte	"?", 0x00, 0xFF, 0x8F, 3272
	.byte	"?", 0x0D, 0xFF, 0x87, 3275
	.byte	"?", 0x00, 0xF2, 0x6D, 3278
	.byte	"?", 0x00, 0xAD, 0x5F, 328
	.byte	"?", 0x00, 0xD9, 0x75, 3282
	.byte	"?", 0x00, 0xED, 0x77, 3285
	.byte	"?", 0x00, 0xCC, 0x5E, 3288
	.byte	"?", 0x00, 0x8A, 0x4A, 329
	.byte	"?", 0x00, 0x8A, 0x46, 3292
	.byte	"?", 0x00, 0xC9, 0x5F, 3295
	.byte	"?", 0x00, 0x94, 0x40, 3298
	.byte	"?", 0x00, 0x66, 0x35, 330
	.byte	"?", 0x00, 0x4F, 0x24, 3302
	.byte	"?", 0x00, 0x63, 0x27, 3305
	.byte	"?", 0x00, 0x47, 0x1D, 3308
	.byte	"?", 0xC2, 0xFF, 0xD6, 331
	.byte	"?", 0xB3, 0xFF, 0xCC, 332
	.byte	"?", 0x91, 0xFF, 0xBA, 333
	.byte	"?", 0x00, 0xF7, 0x63, 334
	.byte	"?", 0x00, 0xB3, 0x3E, 335
	.byte	"?", 0x00, 0x87, 0x2D, 336
	.byte	"?", 0xB0, 0xFF, 0xCC, 337
	.byte	"?", 0xA6, 0xFF, 0xBF, 3375
	.byte	"?", 0x87, 0xFF, 0xAD, 338
	.byte	"?", 0x8C, 0xFF, 0xAB, 3385
	.byte	"?", 0x29, 0xFF, 0x70, 339
	.byte	"?", 0x63, 0xFF, 0x8C, 3395
	.byte	"?", 0x00, 0xE8, 0x4F, 340
	.byte	"?", 0x26, 0xFF, 0x59, 3405
	.byte	"?", 0x00, 0xB5, 0x3C, 341
	.byte	"?", 0x00, 0xC7, 0x2E, 3415
	.byte	"?", 0x00, 0x91, 0x2A, 342
	.byte	"?", 0x00, 0x94, 0x21, 3425
	.byte	"?", 0x02, 0x63, 0x1C, 343
	.byte	"?", 0x00, 0x57, 0x10, 3435
	.byte	"?", 0xBA, 0xFF, 0xC4, 344
	.byte	"?", 0x9E, 0xFF, 0xAD, 345
	.byte	"?", 0x73, 0xFF, 0x87, 346
	.byte	"?", 0x00, 0xF7, 0x23, 347
	.byte	"?", 0x00, 0xC2, 0x1D, 348
	.byte	"?", 0x00, 0x94, 0x0D, 349
	.byte	"?", 0x0D, 0x40, 0x00, 350
	.byte	"?", 0xD4, 0xFF, 0xD6, 351
	.byte	"?", 0xBA, 0xFF, 0xBF, 352
	.byte	"?", 0x9E, 0xFF, 0xA3, 353
	.byte	"?", 0x33, 0xFF, 0x1A, 354
	.byte	"?", 0x0F, 0xFF, 0x00, 355
	.byte	"?", 0x09, 0xBA, 0x00, 356
	.byte	"?", 0x16, 0x70, 0x00, 357
	.byte	"?", 0xBA, 0xFF, 0x9E, 358
	.byte	"?", 0xA3, 0xFF, 0x82, 359
	.byte	"?", 0x6B, 0xFF, 0x33, 360
	.byte	"?", 0x4F, 0xFF, 0x00, 361
	.byte	"?", 0x46, 0xE8, 0x00, 362
	.byte	"?", 0x3E, 0xC2, 0x00, 363
	.byte	"?", 0x34, 0x94, 0x00, 364
	.byte	"?", 0xE0, 0xFF, 0xB5, 365
	.byte	"?", 0xCC, 0xFF, 0x8F, 366
	.byte	"?", 0xAD, 0xFF, 0x69, 367
	.byte	"?", 0x6E, 0xFF, 0x00, 368
	.byte	"?", 0x61, 0xED, 0x00, 369
	.byte	"?", 0x52, 0xBA, 0x00, 370
	.byte	"?", 0x40, 0x70, 0x00, 371
	.byte	"?", 0xE6, 0xFF, 0xAB, 372
	.byte	"?", 0xD6, 0xFF, 0x8A, 373
	.byte	"?", 0xC2, 0xFF, 0x6E, 374
	.byte	"?", 0x96, 0xFF, 0x38, 375
	.byte	"?", 0x74, 0xF2, 0x00, 376
	.byte	"?", 0x6B, 0xC2, 0x00, 377
	.byte	"?", 0x43, 0x66, 0x00, 378
	.byte	"?", 0xE8, 0xFF, 0x6B, 379
	.byte	"?", 0xDE, 0xFF, 0x47, 380
	.byte	"?", 0xCC, 0xFF, 0x17, 381
	.byte	"?", 0xB5, 0xFF, 0x00, 382
	.byte	"?", 0xA5, 0xCF, 0x00, 383
	.byte	"?", 0x90, 0xB0, 0x00, 384
	.byte	"?", 0x68, 0x6B, 0x00, 385
	.byte	"?", 0xF0, 0xFF, 0x70, 386
	.byte	"?", 0xE6, 0xFF, 0x42, 387
	.byte	"?", 0xDB, 0xFF, 0x36, 388
	.byte	"?", 0xCC, 0xFF, 0x26, 389
	.byte	"?", 0xB7, 0xEB, 0x00, 390
	.byte	"?", 0x95, 0xAB, 0x00, 391
	.byte	"?", 0x79, 0x82, 0x00, 392
	.byte	"?", 0xF7, 0xFF, 0x73, 393
	.byte	"?", 0xFC, 0xFF, 0x52, 3935
	.byte	"?", 0xF0, 0xFF, 0x3D, 394
	.byte	"?", 0xF7, 0xFF, 0x26, 3945
	.byte	"?", 0xEB, 0xFF, 0x26, 395
	.byte	"?", 0xF0, 0xFF, 0x00, 3955
	.byte	"?", 0xE3, 0xFF, 0x0F, 396
	.byte	"?", 0xEB, 0xFF, 0x00, 3965
	.byte	"?", 0xCC, 0xE3, 0x00, 397
	.byte	"?", 0xB5, 0xB5, 0x00, 3975
	.byte	"?", 0xAB, 0xB8, 0x00, 398
	.byte	"?", 0x96, 0x92, 0x00, 3985
	.byte	"?", 0x91, 0x91, 0x00, 399
	.byte	"?", 0x5C, 0x59, 0x00, 3995
	.byte	"?", 0xD6, 0xD0, 0xC9, 400
	.byte	"?", 0xC4, 0xBB, 0xAF, 401
	.byte	"?", 0xB0, 0xA5, 0x97, 402
	.byte	"?", 0x91, 0x87, 0x79, 403
	.byte	"?", 0x70, 0x67, 0x58, 404
	.byte	"?", 0x47, 0x40, 0x30, 405
	.byte	"?", 0xD6, 0xCB, 0xC9, 406
	.byte	"?", 0xBD, 0xAE, 0xAC, 407
	.byte	"?", 0xA8, 0x97, 0x96, 408
	.byte	"?", 0x8C, 0x7A, 0x77, 409
	.byte	"?", 0x70, 0x5C, 0x59, 410
	.byte	"?", 0x47, 0x34, 0x2E, 411
	.byte	"?", 0x05, 0x04, 0x02, 412
	.byte	"?", 0xCC, 0xCC, 0xBA, 413
	.byte	"?", 0xB3, 0xB3, 0xA1, 414
	.byte	"?", 0x96, 0x96, 0x84, 415
	.byte	"?", 0x80, 0x80, 0x6B, 416
	.byte	"?", 0x58, 0x59, 0x43, 417
	.byte	"?", 0x3E, 0x40, 0x2C, 418
	.byte	"?", 0x00, 0x00, 0x00, 419
	.byte	"?", 0xD9, 0xD9, 0xD9, 420
	.byte	"?", 0xBD, 0xBD, 0xBD, 421
	.byte	"?", 0xAB, 0xAB, 0xAB, 422
	.byte	"?", 0x8F, 0x8F, 0x8F, 423
	.byte	"?", 0x63, 0x63, 0x63, 424
	.byte	"?", 0x3B, 0x3B, 0x3B, 425
	.byte	"?", 0x00, 0x00, 0x00, 426
	.byte	"?", 0xE3, 0xE3, 0xE3, 427
	.byte	"?", 0xCD, 0xD1, 0xD1, 428
	.byte	"?", 0xA8, 0xAD, 0xAD, 429
	.byte	"?", 0x85, 0x8C, 0x8C, 430
	.byte	"?", 0x52, 0x5B, 0x5C, 431
	.byte	"?", 0x2D, 0x39, 0x3B, 432
	.byte	"?", 0x09, 0x0C, 0x0D, 433
	.byte	"?", 0xED, 0xE6, 0xE8, 434
	.byte	"?", 0xDE, 0xD6, 0xDB, 435
	.byte	"?", 0xC2, 0xBF, 0xBF, 436
	.byte	"?", 0x8A, 0x8C, 0x8A, 437
	.byte	"?", 0x39, 0x45, 0x00, 438
	.byte	"?", 0x29, 0x33, 0x00, 439
	.byte	"?", 0x20, 0x27, 0x00, 440
	.byte	"?", 0xDA, 0xE8, 0xD8, 441
	.byte	"?", 0xBE, 0xCF, 0xBC, 442
	.byte	"?", 0x9D, 0xB3, 0x9D, 443
	.byte	"?", 0x7E, 0x94, 0x7E, 444
	.byte	"?", 0x47, 0x59, 0x47, 445
	.byte	"?", 0x32, 0x40, 0x31, 446
	.byte	"?", 0x27, 0x2E, 0x20, 447
	.byte	"?", 0x2D, 0x3E, 0x00, 448
	.byte	"?", 0x4F, 0x3A, 0x00, 4485
	.byte	"?", 0x3D, 0x52, 0x00, 449
	.byte	"?", 0x8A, 0x6E, 0x07, 4495
	.byte	"?", 0x50, 0x67, 0x00, 450
	.byte	"?", 0xA3, 0x8B, 0x24, 4505
	.byte	"?", 0xAB, 0xB5, 0x73, 451
	.byte	"?", 0xC2, 0xB0, 0x61, 4515
	.byte	"?", 0xC2, 0xCF, 0x9C, 452
	.byte	"?", 0xD4, 0xC5, 0x81, 4525
	.byte	"?", 0xDB, 0xE3, 0xBF, 453
	.byte	"?", 0xE3, 0xDA, 0x9F, 4535
	.byte	"?", 0xE8, 0xED, 0xD6, 454
	.byte	"?", 0xF0, 0xE9, 0xC2, 4545
	.byte	"?", 0x59, 0x4A, 0x00, 455
	.byte	"?", 0x91, 0x7C, 0x00, 456
	.byte	"?", 0xB8, 0x9C, 0x00, 457
	.byte	"?", 0xE6, 0xE6, 0x45, 458
	.byte	"?", 0xF0, 0xED, 0x73, 459
	.byte	"?", 0xF5, 0xF2, 0x8F, 460
	.byte	"?", 0xF7, 0xF7, 0xA6, 461
	.byte	"?", 0x40, 0x26, 0x00, 462
	.byte	"?", 0x36, 0x15, 0x00, 4625
	.byte	"?", 0x6B, 0x3D, 0x00, 463
	.byte	"?", 0x8F, 0x4A, 0x06, 4635
	.byte	"?", 0x95, 0x53, 0x00, 464
	.byte	"?", 0xB8, 0x74, 0x3B, 4645
	.byte	"?", 0xCC, 0xAD, 0x6B, 465
	.byte	"?", 0xD1, 0x9B, 0x73, 4655
	.byte	"?", 0xE0, 0xC7, 0x91, 466
	.byte	"?", 0xE6, 0xBC, 0x9C, 4665
	.byte	"?", 0xE8, 0xD9, 0xA8, 467
	.byte	"?", 0xF0, 0xD5, 0xBD, 4675
	.byte	"?", 0xF0, 0xE8, 0xC4, 468
	.byte	"?", 0xF5, 0xE4, 0xD3, 4685
	.byte	"?", 0x4A, 0x1A, 0x00, 469
	.byte	"?", 0x42, 0x0D, 0x00, 4695
	.byte	"?", 0xAB, 0x48, 0x00, 470
	.byte	"?", 0x82, 0x31, 0x26, 4705
	.byte	"?", 0xD1, 0x56, 0x00, 471
	.byte	"?", 0xA8, 0x62, 0x5D, 4715
	.byte	"?", 0xFF, 0xA8, 0x7A, 472
	.byte	"?", 0xBF, 0x82, 0x7C, 4725
	.byte	"?", 0xFF, 0xC4, 0xA3, 473
	.byte	"?", 0xD9, 0xA9, 0xA7, 4735
	.byte	"?", 0xFF, 0xD9, 0xBD, 474
	.byte	"?", 0xE6, 0xBE, 0xBC, 4745
	.byte	"?", 0xFF, 0xE3, 0xCC, 475
	.byte	"?", 0xF0, 0xD8, 0xD3, 4755
	.byte	"?", 0x38, 0x1C, 0x00, 476
	.byte	"?", 0x4F, 0x18, 0x00, 477
	.byte	"?", 0x6B, 0x12, 0x00, 478
	.byte	"?", 0xB0, 0x85, 0x73, 479
	.byte	"?", 0xD9, 0xB5, 0xB0, 480
	.byte	"?", 0xE8, 0xCF, 0xC9, 481
	.byte	"?", 0xF2, 0xE0, 0xDE, 482
	.byte	"?", 0x66, 0x07, 0x00, 483
	.byte	"?", 0xB5, 0x09, 0x00, 484
	.byte	"?", 0xFF, 0x0D, 0x00, 485
	.byte	"?", 0xFF, 0x87, 0x96, 486
	.byte	"?", 0xFF, 0xA6, 0xB8, 487
	.byte	"?", 0xFF, 0xBD, 0xCF, 488
	.byte	"?", 0xFF, 0xD9, 0xE3, 489
	.byte	"?", 0x47, 0x13, 0x00, 490
	.byte	"?", 0x7A, 0x1A, 0x00, 491
	.byte	"?", 0x94, 0x22, 0x00, 492
	.byte	"?", 0xF2, 0x83, 0xBB, 493
	.byte	"?", 0xFF, 0xAB, 0xDE, 494
	.byte	"?", 0xFF, 0xC2, 0xE3, 495
	.byte	"?", 0xFF, 0xD6, 0xE8, 496
	.byte	"?", 0x38, 0x11, 0x00, 497
	.byte	"?", 0x33, 0x0E, 0x00, 4975
	.byte	"?", 0x66, 0x25, 0x00, 498
	.byte	"?", 0x85, 0x32, 0x41, 4985
	.byte	"?", 0x85, 0x31, 0x00, 499
	.byte	"?", 0xA8, 0x58, 0x68, 4995
	.byte	"?", 0xE3, 0x8D, 0xB3, 500
	.byte	"?", 0xC4, 0x7A, 0x8F, 5005
	.byte	"?", 0xF7, 0xB5, 0xD7, 501
	.byte	"?", 0xE3, 0xAA, 0xC1, 5015
	.byte	"?", 0xFC, 0xCF, 0xE3, 502
	.byte	"?", 0xED, 0xC2, 0xD1, 5025
	.byte	"?", 0xFF, 0xE3, 0xEB, 503
	.byte	"?", 0xF7, 0xDF, 0xE1, 5035
	.byte	"?", 0x32, 0x00, 0x00, 504
	.byte	"?", 0x60, 0x00, 0x00, 505
	.byte	"?", 0x77, 0x00, 0x00, 506
	.byte	"?", 0xDE, 0x82, 0xC4, 507
	.byte	"?", 0xF2, 0xA3, 0xE3, 508
	.byte	"?", 0xFF, 0xC2, 0xED, 509
	.byte	"?", 0xFF, 0xD4, 0xF0, 510
	.byte	"?", 0x3D, 0x00, 0x66, 511
	.byte	"?", 0x2B, 0x00, 0x41, 5115
	.byte	"?", 0x61, 0x00, 0xCE, 512
	.byte	"?", 0x59, 0x24, 0x82, 5125
	.byte	"?", 0x8A, 0x1F, 0xFF, 513
	.byte	"?", 0x82, 0x57, 0xB8, 5135
	.byte	"?", 0xD9, 0x80, 0xFF, 514
	.byte	"?", 0xB3, 0x8C, 0xE0, 5145
	.byte	"?", 0xED, 0x9E, 0xFF, 515
	.byte	"?", 0xD4, 0xB3, 0xEB, 5155
	.byte	"?", 0xF7, 0xBA, 0xFF, 516
	.byte	"?", 0xE8, 0xCF, 0xF2, 5165
	.byte	"?", 0xFF, 0xD1, 0xFF, 517
	.byte	"?", 0xF2, 0xE0, 0xF7, 5175
	.byte	"?", 0x2E, 0x00, 0x5C, 518
	.byte	"?", 0x1C, 0x00, 0x22, 5185
	.byte	"?", 0x44, 0x00, 0x9D, 519
	.byte	"?", 0x3D, 0x0C, 0x4E, 5195
	.byte	"?", 0x5C, 0x00, 0xE0, 520
	.byte	"?", 0x7A, 0x5E, 0x85, 5205
	.byte	"?", 0xBA, 0x87, 0xFF, 521
	.byte	"?", 0xB5, 0x9E, 0xC2, 5215
	.byte	"?", 0xD4, 0xA1, 0xFF, 522
	.byte	"?", 0xD4, 0xBA, 0xD9, 5225
	.byte	"?", 0xE6, 0xBD, 0xFF, 523
	.byte	"?", 0xE6, 0xD4, 0xE6, 5235
	.byte	"?", 0xF0, 0xD9, 0xFF, 524
	.byte	"?", 0xF0, 0xE6, 0xED, 5245
	.byte	"?", 0x27, 0x00, 0x85, 525
	.byte	"?", 0x0D, 0x0B, 0x4D, 5255
	.byte	"?", 0x3B, 0x00, 0xED, 526
	.byte	"?", 0x20, 0x25, 0x8A, 5265
	.byte	"?", 0x45, 0x00, 0xFF, 527
	.byte	"?", 0x38, 0x48, 0xA8, 5275
	.byte	"?", 0x96, 0x73, 0xFF, 528
	.byte	"?", 0x72, 0x80, 0xC4, 5285
	.byte	"?", 0xBD, 0x99, 0xFF, 529
	.byte	"?", 0xA8, 0xB3, 0xE6, 5295
	.byte	"?", 0xD1, 0xB0, 0xFF, 530
	.byte	"?", 0xC7, 0xCE, 0xED, 5305
	.byte	"?", 0xE6, 0xCC, 0xFF, 531
	.byte	"?", 0xE4, 0xE4, 0xF2, 5315
	.byte	"?", 0x00, 0x19, 0x3F, 532
	.byte	"?", 0x00, 0x22, 0x7B, 533
	.byte	"?", 0x00, 0x2C, 0xAA, 534
	.byte	"?", 0x94, 0xB3, 0xED, 535
	.byte	"?", 0xB0, 0xC7, 0xF2, 536
	.byte	"?", 0xC7, 0xDB, 0xF7, 537
	.byte	"?", 0xDE, 0xE8, 0xFA, 538
	.byte	"?", 0x00, 0x27, 0x4D, 539
	.byte	"?", 0x00, 0x22, 0x3D, 5395
	.byte	"?", 0x00, 0x34, 0x73, 540
	.byte	"?", 0x3A, 0x72, 0x8A, 5405
	.byte	"?", 0x00, 0x44, 0x9E, 541
	.byte	"?", 0x5A, 0x8A, 0x96, 5415
	.byte	"?", 0x5E, 0xC1, 0xF7, 542
	.byte	"?", 0x79, 0xA6, 0xAD, 5425
	.byte	"?", 0x96, 0xE3, 0xFF, 543
	.byte	"?", 0xB8, 0xCD, 0xD4, 5435
	.byte	"?", 0xB3, 0xF0, 0xFF, 544
	.byte	"?", 0xCC, 0xDC, 0xDE, 5445
	.byte	"?", 0xC7, 0xF7, 0xFF, 545
	.byte	"?", 0xDA, 0xE8, 0xE8, 5455
	.byte	"?", 0x02, 0x27, 0x2B, 546
	.byte	"?", 0x00, 0x2B, 0x24, 5463
	.byte	"?", 0x00, 0x0D, 0x09, 5467
	.byte	"?", 0x00, 0x34, 0x40, 547
	.byte	"?", 0x16, 0x7A, 0x58, 5473
	.byte	"?", 0x1D, 0x42, 0x30, 5477
	.byte	"?", 0x00, 0x46, 0x5C, 548
	.byte	"?", 0x43, 0xB0, 0x8B, 5483
	.byte	"?", 0x48, 0x70, 0x5D, 5487
	.byte	"?", 0x56, 0xAD, 0xBA, 549
	.byte	"?", 0x73, 0xC9, 0xAD, 5493
	.byte	"?", 0x82, 0x9E, 0x90, 5497
	.byte	"?", 0x7B, 0xC1, 0xC9, 550
	.byte	"?", 0x9C, 0xDB, 0xC5, 5503
	.byte	"?", 0xA1, 0xB5, 0xA8, 5507
	.byte	"?", 0xA2, 0xD7, 0xDE, 551
	.byte	"?", 0xC7, 0xF2, 0xE1, 5513
	.byte	"?", 0xBE, 0xD1, 0xC5, 5517
	.byte	"?", 0xC5, 0xE8, 0xE8, 552
	.byte	"?", 0xDC, 0xF7, 0xEB, 5523
	.byte	"?", 0xD5, 0xE3, 0xDA, 5527
	.byte	"?", 0x14, 0x33, 0x19, 553
	.byte	"?", 0x10, 0x2E, 0x14, 5535
	.byte	"?", 0x11, 0x54, 0x22, 554
	.byte	"?", 0x32, 0x7A, 0x3D, 5545
	.byte	"?", 0x18, 0x70, 0x31, 555
	.byte	"?", 0x5A, 0x9E, 0x68, 5555
	.byte	"?", 0x66, 0xBA, 0x80, 556
	.byte	"?", 0x84, 0xBD, 0x8F, 5565
	.byte	"?", 0x98, 0xD9, 0xAD, 557
	.byte	"?", 0xA9, 0xD4, 0xB2, 5575
	.byte	"?", 0xBA, 0xE8, 0xCA, 558
	.byte	"?", 0xCA, 0xE6, 0xCC, 5585
	.byte	"?", 0xCE, 0xF0, 0xD8, 559
	.byte	"?", 0xDD, 0xED, 0xDA, 5595
	.byte	"?", 0x0D, 0x40, 0x18, 560
	.byte	"?", 0x05, 0x0F, 0x07, 5605
	.byte	"?", 0x12, 0x7A, 0x38, 561
	.byte	"?", 0x2E, 0x52, 0x2B, 5615
	.byte	"?", 0x1A, 0xB0, 0x58, 562
	.byte	"?", 0x5A, 0x7D, 0x57, 5625
	.byte	"?", 0x79, 0xFC, 0xAC, 563
	.byte	"?", 0x89, 0xA3, 0x86, 5635
	.byte	"?", 0xA1, 0xFF, 0xCC, 564
	.byte	"?", 0xAE, 0xBF, 0xA6, 5645
	.byte	"?", 0xC4, 0xFF, 0xDE, 565
	.byte	"?", 0xC5, 0xD1, 0xBE, 5655
	.byte	"?", 0xDB, 0xFF, 0xE8, 566
	.byte	"?", 0xDA, 0xE6, 0xD5, 5665
	.byte	"?", 0x0E, 0x4D, 0x1C, 567
	.byte	"?", 0x14, 0xA3, 0x46, 568
	.byte	"?", 0x04, 0xD4, 0x5B, 569
	.byte	"?", 0x85, 0xFF, 0xB5, 570
	.byte	"?", 0xAD, 0xFF, 0xCF, 571
	.byte	"?", 0xC4, 0xFF, 0xDB, 572
	.byte	"?", 0xDB, 0xFF, 0xE8, 573
	.byte	"?", 0x31, 0x4A, 0x0E, 574
	.byte	"?", 0x1F, 0x2E, 0x07, 5743
	.byte	"?", 0x24, 0x36, 0x00, 5747
	.byte	"?", 0x3E, 0x78, 0x00, 575
	.byte	"?", 0x3F, 0x54, 0x10, 5753
	.byte	"?", 0x54, 0x73, 0x06, 5757
	.byte	"?", 0x4F, 0x9C, 0x00, 576
	.byte	"?", 0x5C, 0x6E, 0x1D, 5763
	.byte	"?", 0x84, 0x9C, 0x32, 5767
	.byte	"?", 0xAE, 0xE6, 0x7C, 577
	.byte	"?", 0x90, 0x9E, 0x5A, 5773
	.byte	"?", 0xA5, 0xB8, 0x5E, 5777
	.byte	"?", 0xC0, 0xF0, 0x90, 578
	.byte	"?", 0xAF, 0xBA, 0x86, 5783
	.byte	"?", 0xCE, 0xDE, 0x99, 5787
	.byte	"?", 0xCD, 0xF7, 0xA3, 579
	.byte	"?", 0xC9, 0xD1, 0xA5, 5793
	.byte	"?", 0xDC, 0xE8, 0xB0, 5797
	.byte	"?", 0xDC, 0xFA, 0xB9, 580
	.byte	"?", 0xDE, 0xE3, 0xC8, 5803
	.byte	"?", 0xE9, 0xF0, 0xCE, 5807
	.byte	"?", 0x46, 0x47, 0x00, 581
	.byte	"?", 0x36, 0x36, 0x05, 5815
	.byte	"?", 0x78, 0x8A, 0x00, 582
	.byte	"?", 0x69, 0x66, 0x0E, 5825
	.byte	"?", 0xA3, 0xD4, 0x00, 583
	.byte	"?", 0x99, 0x96, 0x32, 5835
	.byte	"?", 0xD3, 0xF0, 0x32, 584
	.byte	"?", 0xB3, 0xB1, 0x5F, 5845
	.byte	"?", 0xDE, 0xFA, 0x55, 585
	.byte	"?", 0xD1, 0xD1, 0x90, 5855
	.byte	"?", 0xE8, 0xFF, 0x78, 586
	.byte	"?", 0xDE, 0xDE, 0xA6, 5865
	.byte	"?", 0xF2, 0xFF, 0x99, 587
	.byte	"?", 0xEB, 0xEB, 0xC0, 5875
	.byte	"?", 0xFF, 0xFF, 0xB5, 600
	.byte	"?", 0xFF, 0xFF, 0x99, 601
	.byte	"?", 0xFF, 0xFF, 0x7D, 602
	.byte	"?", 0xFC, 0xFC, 0x4E, 603
	.byte	"?", 0xF7, 0xF7, 0x1E, 604
	.byte	"?", 0xED, 0xE8, 0x00, 605
	.byte	"?", 0xE0, 0xD7, 0x00, 606
	.byte	"?", 0xFC, 0xFC, 0xCF, 607
	.byte	"?", 0xFA, 0xFA, 0xAA, 608
	.byte	"?", 0xF5, 0xF5, 0x84, 609
	.byte	"?", 0xF0, 0xF0, 0x65, 610
	.byte	"?", 0xE3, 0xE1, 0x12, 611
	.byte	"?", 0xCC, 0xC8, 0x00, 612
	.byte	"?", 0xB3, 0xAB, 0x00, 613
	.byte	"?", 0xF5, 0xF5, 0xC4, 614
	.byte	"?", 0xF0, 0xED, 0xAF, 615
	.byte	"?", 0xE8, 0xE3, 0x97, 616
	.byte	"?", 0xD4, 0xCF, 0x6E, 617
	.byte	"?", 0xB3, 0xAD, 0x17, 618
	.byte	"?", 0x91, 0x8C, 0x00, 619
	.byte	"?", 0x78, 0x72, 0x00, 620
	.byte	"?", 0xD9, 0xFA, 0xE1, 621
	.byte	"?", 0xBA, 0xF5, 0xC6, 622
	.byte	"?", 0x9C, 0xE6, 0xAE, 623
	.byte	"?", 0x72, 0xCC, 0x85, 624
	.byte	"?", 0x4B, 0xAB, 0x60, 625
	.byte	"?", 0x17, 0x5E, 0x22, 626
	.byte	"?", 0x04, 0x29, 0x0A, 627
	.byte	"?", 0xCF, 0xFF, 0xF0, 628
	.byte	"?", 0xA8, 0xFF, 0xE8, 629
	.byte	"?", 0x87, 0xFF, 0xE3, 630
	.byte	"?", 0x52, 0xFA, 0xDC, 631
	.byte	"?", 0x13, 0xF2, 0xCE, 632
	.byte	"?", 0x00, 0xBF, 0xAC, 633
	.byte	"?", 0x00, 0x99, 0x8B, 634
	.byte	"?", 0xAD, 0xFF, 0xEB, 635
	.byte	"?", 0x8C, 0xFF, 0xE8, 636
	.byte	"?", 0x73, 0xFF, 0xE8, 637
	.byte	"?", 0x2B, 0xFF, 0xE6, 638
	.byte	"?", 0x00, 0xF2, 0xE6, 639
	.byte	"?", 0x00, 0xC7, 0xC7, 640
	.byte	"?", 0x00, 0xAB, 0xB3, 641
	.byte	"?", 0xD2, 0xF0, 0xFA, 642
	.byte	"?", 0xB8, 0xE4, 0xF5, 643
	.byte	"?", 0x8B, 0xCC, 0xF0, 644
	.byte	"?", 0x64, 0xA7, 0xE8, 645
	.byte	"?", 0x46, 0x96, 0xE3, 646
	.byte	"?", 0x00, 0x56, 0xC4, 647
	.byte	"?", 0x00, 0x2D, 0x75, 648
	.byte	"?", 0xD9, 0xED, 0xFC, 649
	.byte	"?", 0xBE, 0xE3, 0xFA, 650
	.byte	"?", 0x95, 0xC5, 0xF0, 651
	.byte	"?", 0x5C, 0x97, 0xE6, 652
	.byte	"?", 0x00, 0x4E, 0xCC, 653
	.byte	"?", 0x00, 0x39, 0x9E, 654
	.byte	"?", 0x00, 0x2B, 0x7A, 655
	.byte	"?", 0xDB, 0xF5, 0xFF, 656
	.byte	"?", 0xC2, 0xEB, 0xFF, 657
	.byte	"?", 0x96, 0xCC, 0xFF, 658
	.byte	"?", 0x5C, 0xA6, 0xFF, 659
	.byte	"?", 0x1A, 0x6E, 0xFF, 660
	.byte	"?", 0x00, 0x48, 0xE8, 661
	.byte	"?", 0x00, 0x3B, 0xD1, 662
	.byte	"?", 0xED, 0xF0, 0xFF, 663
	.byte	"?", 0xE3, 0xE8, 0xFF, 664
	.byte	"?", 0xC8, 0xCF, 0xFA, 665
	.byte	"?", 0xA4, 0xA6, 0xED, 666
	.byte	"?", 0x69, 0x70, 0xDB, 667
	.byte	"?", 0x3E, 0x40, 0xB3, 668
	.byte	"?", 0x20, 0x1E, 0x87, 669
	.byte	"?", 0xFF, 0xDE, 0xFF, 670
	.byte	"?", 0xFC, 0xCC, 0xFF, 671
	.byte	"?", 0xF7, 0xA8, 0xFF, 672
	.byte	"?", 0xF0, 0x82, 0xFF, 673
	.byte	"?", 0xE8, 0x54, 0xFF, 674
	.byte	"?", 0xCD, 0x00, 0xF7, 675
	.byte	"?", 0xBB, 0x00, 0xC7, 676
	.byte	"?", 0xFA, 0xDE, 0xFF, 677
	.byte	"?", 0xF7, 0xC9, 0xFF, 678
	.byte	"?", 0xF2, 0xBA, 0xFF, 679
	.byte	"?", 0xE1, 0x8E, 0xFA, 680
	.byte	"?", 0xC1, 0x5F, 0xF5, 681
	.byte	"?", 0xA8, 0x2F, 0xE0, 682
	.byte	"?", 0x81, 0x00, 0x91, 683
	.byte	"?", 0xFA, 0xCF, 0xFA, 684
	.byte	"?", 0xF7, 0xBA, 0xF7, 685
	.byte	"?", 0xF2, 0xAA, 0xF2, 686
	.byte	"?", 0xDC, 0x7E, 0xE0, 687
	.byte	"?", 0xC4, 0x59, 0xCF, 688
	.byte	"?", 0x9D, 0x27, 0xA8, 689
	.byte	"?", 0x69, 0x03, 0x69, 690
	.byte	"?", 0xFC, 0xD7, 0xE8, 691
	.byte	"?", 0xFA, 0xC0, 0xE1, 692
	.byte	"?", 0xF0, 0xA8, 0xD3, 693
	.byte	"?", 0xE6, 0x83, 0xBA, 694
	.byte	"?", 0xBF, 0x50, 0x8A, 695
	.byte	"?", 0x99, 0x18, 0x46, 696
	.byte	"?", 0x7D, 0x09, 0x25, 697
	.byte	"?", 0xFF, 0xD6, 0xEB, 698
	.byte	"?", 0xFF, 0xC2, 0xE6, 699
	.byte	"?", 0xFF, 0xA3, 0xDB, 700
	.byte	"?", 0xFF, 0x78, 0xCC, 701
	.byte	"?", 0xF2, 0x4B, 0xA0, 702
	.byte	"?", 0xD6, 0x24, 0x63, 703
	.byte	"?", 0xBA, 0x00, 0x25, 704
	.byte	"?", 0xFF, 0xE8, 0xF2, 705
	.byte	"?", 0xFF, 0xD4, 0xE6, 706
	.byte	"?", 0xFF, 0xB3, 0xDB, 707
	.byte	"?", 0xFF, 0x8A, 0xC7, 708
	.byte	"?", 0xFF, 0x57, 0x9E, 709
	.byte	"?", 0xFF, 0x36, 0x6B, 710
	.byte	"?", 0xFA, 0x00, 0x32, 711
	.byte	"?", 0xFF, 0xDB, 0xB0, 712
	.byte	"?", 0xFF, 0xCF, 0x96, 713
	.byte	"?", 0xFF, 0xB8, 0x75, 714
	.byte	"?", 0xFF, 0xA1, 0x4A, 715
	.byte	"?", 0xFF, 0x87, 0x17, 716
	.byte	"?", 0xFA, 0x70, 0x00, 717
	.byte	"?", 0xEB, 0x63, 0x00, 718
	.byte	"?", 0xFF, 0xE6, 0xBF, 719
	.byte	"?", 0xFC, 0xD7, 0xA7, 720
	.byte	"?", 0xF7, 0xBC, 0x77, 721
	.byte	"?", 0xE8, 0x95, 0x38, 722
	.byte	"?", 0xD4, 0x74, 0x0B, 723
	.byte	"?", 0xA1, 0x4C, 0x00, 724
	.byte	"?", 0x82, 0x3B, 0x00, 725
	.byte	"?", 0xFA, 0xE6, 0xC0, 726
	.byte	"?", 0xF2, 0xCE, 0xA0, 727
	.byte	"?", 0xE6, 0xB5, 0x77, 728
	.byte	"?", 0xD1, 0x90, 0x52, 729
	.byte	"?", 0xB5, 0x6E, 0x2B, 730
	.byte	"?", 0x75, 0x37, 0x00, 731
	.byte	"?", 0x5C, 0x28, 0x00, 732
	.byte	"?", 0xFF, 0xF5, 0xD1, 7401
	.byte	"?", 0xFF, 0xF0, 0xB3, 7402
	.byte	"?", 0xFF, 0xE6, 0x80, 7403
	.byte	"?", 0xFF, 0xE8, 0x33, 7404
	.byte	"?", 0xFF, 0xE6, 0x00, 7405
	.byte	"?", 0xFF, 0xD1, 0x00, 7406
	.byte	"?", 0xE3, 0xB1, 0x22, 7407
	.byte	"?", 0xFF, 0xBF, 0x0D, 7408
	.byte	"?", 0xFF, 0xB3, 0x0D, 7409
	.byte	"?", 0xFF, 0xB3, 0x73, 7410
	.byte	"?", 0xFF, 0xA6, 0x4F, 7411
	.byte	"?", 0xED, 0x8A, 0x00, 7412
	.byte	"?", 0xF5, 0x73, 0x00, 7413
	.byte	"?", 0xE3, 0x7B, 0x00, 7414
	.byte	"?", 0xFF, 0xD1, 0xD9, 7415
	.byte	"?", 0xFF, 0x66, 0x66, 7416
	.byte	"?", 0xFF, 0x40, 0x40, 7417
	.byte	"?", 0xF2, 0x49, 0x61, 7418
	.byte	"?", 0xD1, 0x54, 0x73, 7419
	.byte	"?", 0xCC, 0x29, 0x76, 7420
	.byte	"?", 0x63, 0x00, 0x46, 7421
	.byte	"?", 0xFF, 0xE8, 0xF2, 7422
	.byte	"?", 0xFF, 0x73, 0xC7, 7423
	.byte	"?", 0xFF, 0x40, 0xB3, 7424
	.byte	"?", 0xED, 0x18, 0xA6, 7425
	.byte	"?", 0xD1, 0x00, 0x73, 7426
	.byte	"?", 0xB8, 0x00, 0x40, 7427
	.byte	"?", 0x73, 0x17, 0x3F, 7428
	.byte	"?", 0xFF, 0xD1, 0xF7, 7429
	.byte	"?", 0xFA, 0xB0, 0xFF, 7430
	.byte	"?", 0xF2, 0x96, 0xED, 7431
	.byte	"?", 0xE6, 0x67, 0xDF, 7432
	.byte	"?", 0xD9, 0x36, 0xB8, 7433
	.byte	"?", 0xCC, 0x29, 0xAD, 7434
	.byte	"?", 0xA6, 0x00, 0x95, 7435
	.byte	"?", 0xF7, 0xEB, 0xFF, 7436
	.byte	"?", 0xF0, 0xCC, 0xFF, 7437
	.byte	"?", 0xD9, 0xA6, 0xFF, 7438
	.byte	"?", 0xCC, 0xA6, 0xFF, 7439
	.byte	"?", 0xB3, 0x99, 0xFF, 7440
	.byte	"?", 0xA3, 0x80, 0xFF, 7441
	.byte	"?", 0x80, 0x4D, 0xFF, 7442
	.byte	"?", 0xF0, 0xF2, 0xFF, 7443
	.byte	"?", 0xCC, 0xD4, 0xFF, 7444
	.byte	"?", 0xAD, 0xC6, 0xF7, 7445
	.byte	"?", 0x91, 0x9E, 0xFF, 7446
	.byte	"?", 0x53, 0x57, 0xCF, 7447
	.byte	"?", 0x4E, 0x43, 0x73, 7448
	.byte	"?", 0x27, 0x00, 0x20, 7449
	.byte	"?", 0xCC, 0xE6, 0xFF, 7450
	.byte	"?", 0x99, 0xC9, 0xFF, 7451
	.byte	"?", 0x80, 0xAD, 0xFF, 7452
	.byte	"?", 0x80, 0xBD, 0xFF, 7453
	.byte	"?", 0x73, 0xAE, 0xE6, 7454
	.byte	"?", 0x33, 0x78, 0xFF, 7455
	.byte	"?", 0x6B, 0x9A, 0xED, 7456
	.byte	"?", 0xE0, 0xFF, 0xFA, 7457
	.byte	"?", 0x90, 0xF0, 0xE4, 7458
	.byte	"?", 0x5F, 0xDE, 0xD1, 7459
	.byte	"?", 0x00, 0xF2, 0xF2, 7460
	.byte	"?", 0x38, 0xB8, 0xFF, 7461
	.byte	"?", 0x00, 0x73, 0xE6, 7462
	.byte	"?", 0x00, 0x33, 0x59, 7463
	.byte	"?", 0xBF, 0xFF, 0xE6, 7464
	.byte	"?", 0x80, 0xFF, 0xBF, 7465
	.byte	"?", 0x4D, 0xFF, 0xC4, 7466
	.byte	"?", 0x0D, 0xFF, 0xBF, 7467
	.byte	"?", 0x00, 0xA5, 0xB8, 7468
	.byte	"?", 0x00, 0x7A, 0x99, 7469
	.byte	"?", 0x1C, 0x77, 0x8C, 7470
	.byte	"?", 0xB8, 0xFF, 0xDB, 7471
	.byte	"?", 0x7A, 0xFF, 0xBF, 7472
	.byte	"?", 0x46, 0xEB, 0x91, 7473
	.byte	"?", 0x14, 0xC7, 0x8F, 7474
	.byte	"?", 0x59, 0xB3, 0x86, 7475
	.byte	"?", 0x00, 0x66, 0x3A, 7476
	.byte	"?", 0x10, 0x52, 0x49, 7477
	.byte	"?", 0xD1, 0xFF, 0xDB, 7478
	.byte	"?", 0x73, 0xFF, 0x80, 7479
	.byte	"?", 0x66, 0xFF, 0x80, 7480
	.byte	"?", 0x66, 0xFF, 0x73, 7481
	.byte	"?", 0x33, 0xFF, 0x40, 7482
	.byte	"?", 0x11, 0x73, 0x00, 7483
	.byte	"?", 0x00, 0x80, 0x13, 7484
	.byte	"?", 0xF0, 0xFF, 0xE6, 7485
	.byte	"?", 0xCC, 0xFF, 0xB3, 7486
	.byte	"?", 0xB3, 0xFF, 0x8C, 7487
	.byte	"?", 0x91, 0xFF, 0x66, 7488
	.byte	"?", 0x5F, 0xED, 0x2F, 7489
	.byte	"?", 0x5B, 0xA6, 0x21, 7490
	.byte	"?", 0x68, 0x99, 0x00, 7491
	.byte	"?", 0xD1, 0xED, 0x77, 7492
	.byte	"?", 0xC5, 0xE6, 0x93, 7493
	.byte	"?", 0xA3, 0xD9, 0x82, 7494
	.byte	"?", 0x86, 0xB3, 0x24, 7495
	.byte	"?", 0x5F, 0x9E, 0x00, 7496
	.byte	"?", 0x73, 0x86, 0x39, 7497
	.byte	"?", 0x26, 0x33, 0x00, 7498
	.byte	"?", 0xFF, 0xFA, 0xD9, 7499
	.byte	"?", 0xF7, 0xF2, 0xD2, 7500
	.byte	"?", 0xF0, 0xE6, 0xC0, 7501
	.byte	"?", 0xE6, 0xD3, 0x95, 7502
	.byte	"?", 0xBF, 0xA8, 0x7C, 7503
	.byte	"?", 0x99, 0x73, 0x54, 7504
	.byte	"?", 0x73, 0x50, 0x22, 7505
	.byte	"?", 0xFF, 0xF2, 0xD9, 7506
	.byte	"?", 0xFF, 0xE6, 0xB3, 7507
	.byte	"?", 0xF5, 0xD0, 0x93, 7508
	.byte	"?", 0xF2, 0xC2, 0x79, 7509
	.byte	"?", 0xE3, 0x9F, 0x40, 7510
	.byte	"?", 0xBF, 0x69, 0x00, 7511
	.byte	"?", 0xAB, 0x5C, 0x00, 7512
	.byte	"?", 0xF7, 0xCB, 0xB2, 7513
	.byte	"?", 0xF2, 0xB8, 0x96, 7514
	.byte	"?", 0xE0, 0x92, 0x70, 7515
	.byte	"?", 0xA6, 0x50, 0x00, 7516
	.byte	"?", 0x8F, 0x39, 0x00, 7517
	.byte	"?", 0x66, 0x3D, 0x2E, 7518
	.byte	"?", 0x42, 0x35, 0x00, 7519
	.byte	"?", 0xFF, 0xD6, 0xCF, 7520
	.byte	"?", 0xE6, 0xAC, 0xB8, 7521
	.byte	"?", 0xD6, 0x81, 0x96, 7522
	.byte	"?", 0xCC, 0x7A, 0x85, 7523
	.byte	"?", 0xBA, 0x54, 0x4A, 7524
	.byte	"?", 0xB3, 0x62, 0x59, 7525
	.byte	"?", 0xA6, 0x3A, 0x00, 7526
	.byte	"?", 0xED, 0xE8, 0xDF, 7527
	.byte	"?", 0xE6, 0xDF, 0xCF, 7528
	.byte	"?", 0xD4, 0xCB, 0xBA, 7529
	.byte	"?", 0xAD, 0xA0, 0x89, 7530
	.byte	"?", 0x80, 0x73, 0x5D, 7531
	.byte	"?", 0x59, 0x4A, 0x2D, 7532
	.byte	"?", 0x26, 0x1E, 0x06, 7533
	.byte	"?", 0xE6, 0xE1, 0xD3, 7534
	.byte	"?", 0xCC, 0xC6, 0xAD, 7535
	.byte	"?", 0xAD, 0xA6, 0x87, 7536
	.byte	"?", 0xC6, 0xCC, 0xB8, 7537
	.byte	"?", 0xA2, 0xB3, 0x9B, 7538
	.byte	"?", 0xA0, 0xA3, 0x95, 7539
	.byte	"?", 0x47, 0x47, 0x47, 7540
	.byte	"?", 0xED, 0xF2, 0xF2, 7541
	.byte	"?", 0xC1, 0xD6, 0xD0, 7542
	.byte	"?", 0xA6, 0xB3, 0xB3, 7543
	.byte	"?", 0x8A, 0x97, 0x99, 7544
	.byte	"?", 0x49, 0x5C, 0x5E, 7545
	.byte	"?", 0x30, 0x45, 0x47, 7546
	.byte	"?", 0x0A, 0x0F, 0x0F, 7547
pantone_end:


; Based on the manufacturer table at 
;   https://help.brother-usa.com/app/answers/detail/a_id/75245/~/.byte-color-conversion-chart
; using a colour picker.

robison_anton_polyester_codes:
	.byte	"Black", 0x00, 0x00, 0x00, 5596
	.byte	"White", 0xFF, 0xFF, 0xFF, 5597
; unfinished
robison_anton_polyester_end:


robison_anton_rayon_codes:
	.byte	"Light Pink", 0xEF, 0xCC, 0xCE, 2243
	.byte	"Pink", 0xFC, 0xBF, 0xC9, 2223
	.byte	"Pink Bazaar", 0xEF, 0xC6, 0xD3, 2599
	.byte	"Pink Mist", 0xF9, 0xB2, 0xB7, 2373
	.byte	"Emily Pink", 0xF9, 0xAF, 0xAD, 2374
	.byte	"Rose", 0xFC, 0x9B, 0xB2, 2293
	.byte	"Rose Cerise", 0xFC, 0x8C, 0x99, 2244
	.byte	"Carnation", 0xF2, 0xAF, 0xC1, 2237
	.byte	"Shrimp", 0xE5, 0x56, 0x6D, 2246
	.byte	"Bashful Pink", 0xF4, 0x47, 0x6B, 2248
	.byte	"Begonia", 0xE5, 0x56, 0x6D, 2228
	.byte	"Azalea", 0xF9, 0x84, 0x8E, 2412
	.byte	"Dusty Rose", 0xF2, 0x68, 0x77, 2375
	.byte	"Rose Tint", 0xD8, 0x89, 0x9B, 2591
	.byte	"Burgundy", 0x8C, 0x26, 0x33, 2249
	.byte	"TH Burgundy", 0x7C, 0x21, 0x28, 2608
	.byte	"Russet", 0x7A, 0x26, 0x38, 2252
	.byte	"Pro Firebrand", 0x75, 0x26, 0x3D, 2622
	.byte	"Wine", 0x77, 0x2D, 0x35, 2225
	.byte	"Intense Maroon", 0x59, 0x33, 0x44, 2587
	.byte	"Dark Maroon", 0x4F, 0x21, 0x3A, 2376
	.byte	"Carbernet", 0x93, 0x16, 0x38, 2494
	.byte	"Mountain Rose", 0xF9, 0xB2, 0xB7, 2495
	.byte	"Warm Wine", 0x66, 0x1E, 0x2B, 2496
	.byte	"Primrose", 0xE5, 0x56, 0x6D, 2491
	.byte	"Perfect Ruby", 0x8E, 0x23, 0x44, 2497
	.byte	"Brushed Burgundy", 0x6D, 0x21, 0x3F, 2498
	.byte	"Passion Rose", 0x8E, 0x23, 0x44, 2499
	.byte	"New Berry", 0xAD, 0x00, 0x75, 2500
	.byte	"Petal Pink", 0xFC, 0xC9, 0xC6, 2501
	.byte	"Memphis Belle", 0xF4, 0xBF, 0xD1, 2502
	.byte	"Desert Bloom", 0xF7, 0xBF, 0xBF, 2503
	.byte	"Wild Pink", 0xCE, 0x00, 0x7C, 2259
	.byte	"Floral Pink", 0xED, 0x72, 0xAA, 2415
	.byte	"Hot Pink", 0xD3, 0x6B, 0x9E, 2260
	.byte	"Crimson", 0xD6, 0x02, 0x70, 2416
	.byte	"Ruby Glint", 0xE2, 0x28, 0x82, 2261
	.byte	"Cherrystone", 0xAA, 0x00, 0x4F, 2504
	.byte	"Cherry Punch", 0xAA, 0x00, 0x4F, 2417
	.byte	"Cherry Blossom", 0xEA, 0x0F, 0x6B, 2262
	.byte	"Red Berry", 0xAF, 0x1E, 0x2D, 2418
	.byte	"Jockey Red", 0xBF, 0x0A, 0x30, 2281
	.byte	"Very Red", 0xBF, 0x0A, 0x30, 2419
	.byte	"Red Berry", 0xBF, 0x0A, 0x30, 2378
	.byte	"Foxy Red", 0xCE, 0x11, 0x26, 2263
	.byte	"Tuxedo Red", 0xD6, 0x28, 0x28, 2420
	.byte	"Lipstick", 0xBF, 0x0A, 0x30, 2233
	.byte	"Scarlet", 0xC4, 0x1E, 0x3A, 2219
	.byte	"Radiant Red", 0xC4, 0x1E, 0x3A, 2266
	.byte	"Wildfire", 0xA3, 0x26, 0x38, 2267
	.byte	"Carolina Red", 0x8C, 0x26, 0x33, 2268
	.byte	"Red Jubilee", 0x75, 0x26, 0x3D, 2421
	.byte	"Cranberry", 0x99, 0x21, 0x35, 2270
	.byte	"Antique Red", 0xA3, 0x26, 0x38, 2505
	.byte	"Devil Red", 0xC4, 0x1E, 0x3A, 2506
	.byte	"Rosewood", 0xD8, 0x1C, 0x3F, 2508
	.byte	"Bitteroot", 0xFC, 0x5E, 0x72, 2509
	.byte	"Bisque", 0xF2, 0xC4, 0xAF, 2377
	.byte	"Flesh", 0xF4, 0xCC, 0xAA, 2413
	.byte	"Flesh Pink", 0xF9, 0xBA, 0xAA, 2253
	.byte	"Opal Mist", 0xF7, 0xBF, 0xBF, 2255
	.byte	"Candy Apple Red", 0xAF, 0x00, 0x3D, 2507
	.byte	"Tawny", 0xF9, 0xBF, 0x9E, 2256
	.byte	"Peach", 0xF9, 0xC6, 0xAA, 2257
	.byte	"Melon", 0xF9, 0x8E, 0x6D, 2294
	.byte	"Flamingo", 0xF9, 0xA5, 0x8C, 2258
	.byte	"Coral", 0xF9, 0x89, 0x72, 2414
	.byte	"Persimmon", 0xF4, 0x3F, 0x4F, 2277
	.byte	"Peach Blossom", 0xF9, 0xC6, 0xAA, 2510
	.byte	"Illusion", 0xF9, 0xBA, 0xAA, 2511
	.byte	"Melonade", 0xF9, 0x89, 0x72, 2512
	.byte	"Honeysuckle", 0xE2, 0x3D, 0x28, 2513
	.byte	"Brite Jade", 0x00, 0x8C, 0x82, 2514
	.byte	"Bluestone", 0x00, 0xB2, 0xA0, 2515
	.byte	"Aqua Pearl", 0x47, 0xD6, 0xC1, 2516
	.byte	"Seafrost", 0x87, 0xDD, 0xD1, 2517
	.byte	"J. Turquoise", 0x00, 0x87, 0x89, 2492
	.byte	"Indian Ocean Blue", 0x2D, 0xC6, 0xD6, 2518
	.byte	"Surf Blue", 0x00, 0xA5, 0xDB, 2519
	.byte	"Mid Windsor", 0x00, 0xA3, 0xDD, 2520
	.byte	"Deep Windsor", 0x00, 0x3F, 0x54, 2589
	.byte	"Pro Dark Blue", 0x00, 0x2D, 0x47, 2620
	.byte	"Mallard Blue", 0x00, 0x6D, 0x75, 2521
	.byte	"Sky Blue", 0x9B, 0xC4, 0xE2, 2239
	.byte	"Lake Blue", 0xAF, 0xBC, 0xDB, 2304
	.byte	"Pro Lusty Blue", 0x5B, 0x77, 0xCC, 2614
	.byte	"Slate Blue", 0x6D, 0x87, 0xA8, 2275
	.byte	"Blue Frost", 0x99, 0xD6, 0xDD, 2305
	.byte	"Periwinkle", 0x28, 0xC4, 0xD8, 2306
	.byte	"Aquamarine", 0x00, 0xAD, 0xC6, 2307
	.byte	"California Blue", 0x00, 0xA0, 0xC4, 2389
	.byte	"Baltic Blue", 0x00, 0x8E, 0xD6, 2441
	.byte	"Solar Blue", 0x00, 0x54, 0xA0, 2442
	.byte	"Pacific Blue", 0x00, 0x8E, 0xD6, 2388
	.byte	"Boo Boo Blue", 0x00, 0xA3, 0xDD, 2730
	.byte	"Pro Band Blue", 0x00, 0x70, 0x9E, 2737
	.byte	"Pro Peacock", 0x00, 0x7A, 0xA5, 2740
	.byte	"Light Blue", 0xC9, 0xE8, 0xDD, 2222
	.byte	"Royal", 0x1E, 0x1C, 0x77, 2210
	.byte	"Blue Suede", 0x00, 0x2B, 0x7F, 2438
	.byte	"Imperial Blue", 0x33, 0x56, 0x87, 2302
	.byte	"Bridgeport Blue", 0xAF, 0xBC, 0xDB, 2522
	.byte	"China Blue", 0x33, 0x56, 0x87, 2523
	.byte	"Pro Imperial", 0x26, 0x54, 0x7C, 2612
	.byte	"Country Blue", 0x77, 0x96, 0xB2, 2524
	.byte	"Heron Blue", 0xC1, 0xC9, 0xDD, 2525
	.byte	"Pro Saxon", 0x77, 0x96, 0xB2, 2624
	.byte	"Bright Blue", 0x66, 0x89, 0xCC, 2526
	.byte	"Soldier Blue", 0x59, 0x60, 0xA8, 2527
	.byte	"Pro Brilliance", 0x00, 0x51, 0xBA, 2619
	.byte	"Atlantis Blue", 0x66, 0x89, 0xCC, 2528
	.byte	"Dolphin Blue", 0x3A, 0x75, 0xC4, 2529
	.byte	"Caribbean Blue", 0x75, 0xAA, 0xDB, 2530
	.byte	"Dana Blue", 0xC4, 0xD8, 0xE2, 2531
	.byte	"Cadet Blue", 0xC4, 0xD8, 0xE2, 2532
	.byte	"Ozone", 0x60, 0xAF, 0xDD, 2533
	.byte	"Salem Blue", 0x00, 0x3D, 0x6B, 2534
	.byte	"Blue Ribbon", 0x0F, 0x2B, 0x5B, 2439
	.byte	"Pro Navy", 0x19, 0x21, 0x68, 2625
	.byte	"Blue Ink", 0x2B, 0x26, 0x5B, 2440
	.byte	"Pro Midnight", 0x00, 0x26, 0x54, 2613
	.byte	"Pro College Blue", 0x00, 0x26, 0x49, 2647
	.byte	"Light Midnight", 0x35, 0x3F, 0x5B, 2386
	.byte	"Fleet Blue", 0x35, 0x26, 0x4F, 2450
	.byte	"Light Navy", 0x11, 0x21, 0x51, 2303
	.byte	"Flag Blue", 0x14, 0x21, 0x3D, 2603
	.byte	"TH Navy", 0x00, 0x26, 0x54, 2609
	.byte	"Navy", 0x14, 0x21, 0x3D, 2215
	.byte	"Midnight Navy", 0x14, 0x21, 0x3D, 2387
	.byte	"Pastel Blue", 0xC6, 0xD1, 0xD6, 2382
	.byte	"Blue Hint", 0xC1, 0xC9, 0xDD, 2598
	.byte	"Ice Blue", 0xB5, 0xD1, 0xE8, 2300
	.byte	"Paris Blue", 0xD1, 0xCE, 0xDD, 2283
	.byte	"Baby Blue", 0x99, 0xBA, 0xDD, 2206
	.byte	"Sun Blue", 0xAF, 0xBC, 0xDB, 2269
	.byte	"Cristy Blue", 0xA5, 0xBA, 0xE0, 2383
	.byte	"Ultra Blue", 0x75, 0xB2, 0xDD, 2433
	.byte	"Tropic Blue", 0x75, 0xAA, 0xDB, 2434
	.byte	"Blue Horizon", 0x66, 0x89, 0xCC, 2435
	.byte	"Oriental Blue", 0x7F, 0x8C, 0xBF, 2301
	.byte	"Copen", 0x6D, 0x87, 0xA8, 2245
	.byte	"Jay Blue", 0x5B, 0x77, 0xCC, 2384
	.byte	"Blue", 0x2D, 0x33, 0x8E, 2220
	.byte	"Sapphire", 0x2D, 0x33, 0x8E, 2280
	.byte	"Pro Royal", 0x00, 0x33, 0x7F, 2627
	.byte	"Fire Blue", 0x00, 0x38, 0x93, 2436
	.byte	"Jamie Blue", 0x2D, 0x33, 0x8E, 2385
	.byte	"Empire Blue", 0x3F, 0x28, 0x93, 2437
	.byte	"Enchanted Sea", 0x3A, 0x56, 0x4F, 2535
	.byte	"Pro Twinkle", 0x84, 0x99, 0xA5, 2617
	.byte	"Rockport Blue", 0x9B, 0xAA, 0xBF, 2536
	.byte	"Wonder Blue", 0x5E, 0x99, 0xAA, 2577
	.byte	"Traditional Gray", 0xAD, 0xAF, 0xAA, 2540
	.byte	"Steel", 0xBF, 0xBA, 0xAF, 2537
	.byte	"Pro Pearl", 0xBA, 0xB7, 0xAF, 2741
	.byte	"Pro Cool Gray", 0xC4, 0xC1, 0xBA, 2733
	.byte	"Stainless Steel", 0xCC, 0xC1, 0xB2, 2538
	.byte	"Chrome", 0xD1, 0xCC, 0xBF, 2539
	.byte	"Pro Night Sky", 0xAD, 0xAF, 0xAA, 2618
	.byte	"Gull", 0x8C, 0x89, 0x84, 2731
	.byte	"Mineral", 0x68, 0x66, 0x63, 2729
	.byte	"Black Chrome", 0x44, 0x3D, 0x38, 2541
	.byte	"Heather", 0xDD, 0xC6, 0xC4, 2271
	.byte	"Grape", 0xD3, 0xB7, 0xA3, 2272
	.byte	"Satin Wine", 0xB5, 0x93, 0x9B, 2314
	.byte	"Ducky Mauve", 0x8E, 0x68, 0x77, 2422
	.byte	"Pale Orchid", 0xFC, 0xBF, 0xC9, 2423
	.byte	"Orchid", 0xE5, 0xBF, 0xC6, 2379
	.byte	"Lavender", 0xEF, 0xC6, 0xD3, 2276
	.byte	"Violet", 0xED, 0xC4, 0xDD, 2285
	.byte	"Cachet", 0xB5, 0x8C, 0xB2, 2424
	.byte	"Tulip", 0xC9, 0xAD, 0xD8, 2286
	.byte	"Mid Lilac", 0xE2, 0x9E, 0xD6, 2588
	.byte	"Port Wine", 0x51, 0x26, 0x54, 2600
	.byte	"Pro Maroon", 0x51, 0x2D, 0x44, 2616
	.byte	"Laurie Lilac", 0x8E, 0x47, 0xAD, 2425
	.byte	"Iris", 0xAF, 0x72, 0xC1, 2288
	.byte	"Raspberry", 0x9B, 0x4F, 0x96, 2426
	.byte	"Mulberry", 0x66, 0x11, 0x6D, 2380
	.byte	"Plum Wine", 0x63, 0x30, 0x5E, 2490
	.byte	"Purple Twist", 0x1E, 0x1C, 0x77, 2429
	.byte	"Violet Blue", 0x33, 0x28, 0x75, 2427
	.byte	"Purple Maze", 0x35, 0x00, 0x6D, 2428
	.byte	"Pro Brite Star", 0x2B, 0x11, 0x66, 2736
	.byte	"Pro Violet", 0x38, 0x19, 0x7A, 2742
	.byte	"Pro Purple", 0x35, 0x00, 0x6D, 2628
	.byte	"Purple", 0x8E, 0x47, 0xAD, 2254
	.byte	"Purple Shadow", 0x5B, 0x02, 0x7A, 2430
	.byte	"Dark Purple", 0x4C, 0x14, 0x5E, 2381
	.byte	"Mauve", 0x89, 0x77, 0xBA, 2287
	.byte	"Purple Accent", 0x44, 0x23, 0x5E, 2431
	.byte	"Hot Peony", 0xAA, 0x00, 0x66, 2590
	.byte	"Passion", 0xCE, 0x00, 0x7C, 2291
	.byte	"Strawberry", 0xAA, 0x00, 0x4F, 2432
	.byte	"Plum", 0x9E, 0x23, 0x87, 2292
	.byte	"Misty", 0x5E, 0x99, 0xAA, 2308
	.byte	"Mystic Teal", 0x60, 0x91, 0x91, 2443
	.byte	"Teal", 0x60, 0x91, 0x91, 2309
	.byte	"Dark Teal", 0x00, 0x3F, 0x54, 2444
	.byte	"Mint Julep", 0x93, 0xDD, 0xDB, 2310
	.byte	"Turquoise", 0x7F, 0xD6, 0xDB, 2204
	.byte	"M.D. Green", 0x00, 0x72, 0x72, 2445
	.byte	"Seafoam", 0x70, 0xCE, 0x9B, 2311
	.byte	"Isle Green", 0x70, 0xCE, 0x9B, 2312
	.byte	"Peppermint", 0x35, 0xC4, 0xAF, 2390
	.byte	"Oceanic Green", 0x00, 0x6D, 0x75, 2446
	.byte	"Pro Teal", 0x00, 0x6B, 0x77, 2621
	.byte	"Garden Green", 0x00, 0x66, 0x63, 2447
	.byte	"Pro Green", 0x00, 0x6D, 0x66, 2735
	.byte	"Pine Green", 0x00, 0x8C, 0x82, 2391
	.byte	"Greenstone", 0x00, 0x82, 0x72, 2448
	.byte	"Fern Green", 0x00, 0x66, 0x63, 2449
	.byte	"Pro Hunter", 0x00, 0x6D, 0x66, 2615
	.byte	"Palm Leaf", 0xBC, 0xC1, 0xB2, 2241
	.byte	"Flite Green", 0xC6, 0xD6, 0xA0, 2282
	.byte	"Willow", 0x9E, 0xAA, 0x99, 2221
	.byte	"Sprite", 0xB2, 0xD8, 0xD8, 2313
	.byte	"Moss", 0x7A, 0xA8, 0x91, 2278
	.byte	"Wintergreen", 0x7A, 0xA8, 0x91, 2594
	.byte	"Green Forest", 0x00, 0x60, 0x56, 2451
	.byte	"Pro Forest", 0x00, 0x60, 0x56, 2743
	.byte	"Harbor Green", 0x4F, 0x6D, 0x5E, 2392
	.byte	"Evergreen", 0x02, 0x49, 0x30, 2315
	.byte	"Pro Dark Green", 0x00, 0x44, 0x38, 2734
	.byte	"Lizzy Lime", 0x2B, 0x4C, 0x3F, 2631
	.byte	"D.H. Green", 0x28, 0x2D, 0x26, 2411
	.byte	"Celery", 0xF2, 0xEA, 0xBC, 2316
	.byte	"Pistachio", 0xCC, 0xC6, 0x93, 2250
	.byte	"Olive Drab", 0x5E, 0x66, 0x3A, 2317
	.byte	"Olive", 0x77, 0x91, 0x82, 2202
	.byte	"Pale Green", 0xC9, 0xE8, 0xDD, 2318
	.byte	"Green Pearl", 0x93, 0xDD, 0xDB, 2452
	.byte	"Sea Mist", 0x93, 0xDD, 0xDB, 2393
	.byte	"Mint", 0xB5, 0xE8, 0xBF, 2238
	.byte	"Spruce", 0xAA, 0xDD, 0x6D, 2279
	.byte	"Nile", 0xA0, 0xDB, 0x8E, 2211
	.byte	"Green Oak", 0xB5, 0xCC, 0x8E, 2319
	.byte	"Erin Green", 0x8C, 0xD6, 0x00, 2320
	.byte	"Pro Erin", 0x56, 0xAA, 0x1C, 2738
	.byte	"Emerald", 0x33, 0x9E, 0x35, 2214
	.byte	"Dark Emerald", 0x00, 0x7A, 0x3D, 2453
	.byte	"Light Kelly", 0x00, 0x7A, 0x3D, 2410
	.byte	"Kelly", 0x00, 0x7A, 0x3D, 2240
	.byte	"Dark Green", 0x00, 0x87, 0x51, 2208
	.byte	"Fleece Green", 0x00, 0x6B, 0x3F, 2454
	.byte	"TH Green", 0x00, 0x68, 0x54, 2607
	.byte	"Harvest Green", 0x1E, 0xB5, 0x3A, 2578
	.byte	"Vibrant Green", 0x00, 0x9E, 0x49, 2579
	.byte	"Green Grass", 0x00, 0x9E, 0x49, 2580
	.byte	"Deep Green", 0x00, 0x6B, 0x3F, 2284
	.byte	"Green Bay", 0x00, 0x6B, 0x54, 2455
	.byte	"Jungle Green", 0x00, 0x7C, 0x66, 2597
	.byte	"Peapod", 0xA3, 0xAF, 0x07, 2456
	.byte	"Pastoral Green", 0x7F, 0xBA, 0x00, 2321
	.byte	"Green Dust", 0x7F, 0xBA, 0x00, 2457
	.byte	"Ming", 0x7F, 0xBA, 0x00, 2322
	.byte	"Meadow", 0x56, 0x8E, 0x14, 2226
	.byte	"Tamarack", 0x93, 0x99, 0x05, 2230
	.byte	"Palmetto", 0x56, 0x63, 0x14, 2229
	.byte	"Green Petal", 0x02, 0x49, 0x30, 2458
	.byte	"Sage", 0x54, 0x77, 0x30, 2595
	.byte	"Hedge", 0x3F, 0x49, 0x26, 2601
	.byte	"Green", 0x3A, 0x77, 0x28, 2209
	.byte	"Green Sail", 0x19, 0x38, 0x33, 2459
	.byte	"Holly", 0x21, 0x5B, 0x33, 2323
	.byte	"Field Green", 0x26, 0x51, 0x42, 2460
	.byte	"Dress Green", 0x3F, 0x49, 0x26, 2584
	.byte	"Foliage Green", 0x99, 0x84, 0x0A, 2542
	.byte	"Autumn Green", 0xA3, 0x82, 0x05, 2543
	.byte	"Desert Cactus", 0x89, 0x77, 0x19, 2544
	.byte	"Cypress", 0x70, 0x70, 0x14, 2545
	.byte	"Crescent Moon", 0x84, 0x82, 0x05, 2546
	.byte	"Pebblestone", 0xE2, 0xE5, 0x84, 2547
	.byte	"Sun Shadow", 0x99, 0x8E, 0x07, 2548
	.byte	"Blue Spruce", 0x00, 0x49, 0x4F, 2549
	.byte	"Newport", 0x4F, 0x6D, 0x5E, 2550
	.byte	"Spring Garden", 0x77, 0x91, 0x82, 2551
	.byte	"Water Lilly", 0x54, 0x68, 0x56, 2554
	.byte	"Ivy", 0x0C, 0x30, 0x26, 2552
	.byte	"Dark Army Green", 0x23, 0x3A, 0x2D, 2553
	.byte	"Army Green", 0x21, 0x3D, 0x30, 2728
	.byte	"Pastel Green", 0xC9, 0xD6, 0xA3, 2555
	.byte	"Pollen Gold", 0xE0, 0xAA, 0x0F, 2556
	.byte	"Pale Yellow", 0xF4, 0xE2, 0x87, 2557
	.byte	"Buttercup", 0xFF, 0xC6, 0x1E, 2558
	.byte	"Tusk", 0xF7, 0xE8, 0xAA, 2559
	.byte	"Moonbeam", 0xF9, 0xDD, 0x16, 2560
	.byte	"Black Eyed Susie", 0xC6, 0xA0, 0x0C, 2561
	.byte	"Bullion", 0xA3, 0x7F, 0x14, 2562
	.byte	"Chinese Yellow", 0xF7, 0xE8, 0xAA, 2324
	.byte	"Maize", 0xF7, 0xE8, 0xAA, 2264
	.byte	"Wheat", 0xEA, 0xDD, 0x96, 2461
	.byte	"Pro Maize", 0xF9, 0xE0, 0x8C, 2732
	.byte	"Glow", 0xFF, 0xD8, 0x7F, 2234
	.byte	"Star Gold", 0xFC, 0xD8, 0x56, 2408
	.byte	"Mango", 0xFC, 0xA3, 0x11, 2394
	.byte	"Yellow Mist", 0xFC, 0xA3, 0x11, 2409
	.byte	"Yellow", 0xFC, 0xA3, 0x11, 2213
	.byte	"Sunflower", 0xF9, 0xDD, 0x16, 2462
	.byte	"Lemon", 0xF4, 0xED, 0x47, 2325
	.byte	"Daffodil", 0xF9, 0xE8, 0x14, 2326
	.byte	"Merit Gold", 0xFC, 0xB5, 0x14, 2463
	.byte	"Cornsilk", 0xFF, 0xCC, 0x49, 2395
	.byte	"Nectar", 0xFF, 0xC6, 0x1E, 2464
	.byte	"Scholastic", 0xFC, 0xBF, 0x49, 2465
	.byte	"Canary Yellow", 0xFC, 0xE0, 0x16, 2235
	.byte	"Pro Gold", 0xFF, 0xC6, 0x1E, 2626
	.byte	"Manila", 0xFC, 0xD1, 0x16, 2466
	.byte	"Goldenrod", 0xFC, 0xD1, 0x16, 2242
	.byte	"Brite Yellow", 0xFF, 0xCC, 0x49, 2396
	.byte	"Honeydew", 0xF9, 0x9B, 0x0C, 2327
	.byte	"Pumpkin", 0xF7, 0x7F, 0x00, 2328
	.byte	"Orangeade", 0xF7, 0x49, 0x02, 2467
	.byte	"Sun Orange", 0xF7, 0x49, 0x02, 2397
	.byte	"Paprika", 0xF9, 0x56, 0x02, 2236
	.byte	"Saffron", 0xF9, 0x3F, 0x26, 2329
	.byte	"Tex Orange", 0xF9, 0x56, 0x02, 2468
	.byte	"Orange", 0xF9, 0x6B, 0x07, 2218
	.byte	"Dark Tex Orange", 0xF9, 0x63, 0x02, 2469
	.byte	"Old Dark Tex Orange", 0xA5, 0x3F, 0x0F, 2581
	.byte	"Golden Poppy", 0xFC, 0x87, 0x44, 2330
	.byte	"Rust", 0xBC, 0x4F, 0x07, 2289
	.byte	"Copper", 0xAF, 0x75, 0x05, 2295
	.byte	"Light Bronze", 0xC1, 0x8E, 0x60, 2493
	.byte	"Visor Gold", 0xFC, 0xCE, 0x87, 2398
	.byte	"Goldenlite", 0xFF, 0xCC, 0x49, 2605
	.byte	"Honey", 0xFC, 0xBA, 0x5E, 2247
	.byte	"Marigold", 0xFF, 0xCC, 0x49, 2216
	.byte	"Mustard", 0xE0, 0xAA, 0x0F, 2331
	.byte	"Sun Gold", 0xE0, 0xAA, 0x0F, 2212
	.byte	"Karat", 0xE0, 0xAA, 0x0F, 2470
	.byte	"Penny", 0xF2, 0xBF, 0x49, 2332
	.byte	"New Gold", 0xFC, 0xCE, 0x87, 2399
	.byte	"Pro Beige", 0xE2, 0xD6, 0xB5, 2630
	.byte	"Marine Gold", 0xC6, 0xA0, 0x0C, 2596
	.byte	"Ginger", 0xA3, 0x7F, 0x14, 2333
	.byte	"Shimmering Gold", 0xC6, 0xA0, 0x0C, 2471
	.byte	"Old Gold", 0xBF, 0x91, 0x0C, 2201
	.byte	"Salmon", 0xEA, 0xB2, 0xB2, 2299
	.byte	"Dark Rust", 0xC1, 0x38, 0x28, 2205
	.byte	"Terra Cotta", 0xA0, 0x30, 0x33, 2334
	.byte	"Pro Red", 0xAF, 0x1E, 0x2D, 2623
	.byte	"Auburn", 0xAF, 0x1E, 0x2D, 2472
	.byte	"Bone", 0xFA, 0xE6, 0xCC, 2582
	.byte	"Ivory", 0xFA, 0xE6, 0xCF, 2335
	.byte	"Opaline", 0xF7, 0xD3, 0xB5, 2473
	.byte	"Ecru", 0xED, 0xD3, 0xBC, 2232
	.byte	"Wicker", 0xAA, 0x75, 0x3F, 2489
	.byte	"Tan", 0xD3, 0xA8, 0x7C, 2273
	.byte	"Cottage Beige", 0xED, 0xD3, 0xB5, 2593
	.byte	"Rattan", 0xC1, 0xA8, 0x75, 2474
	.byte	"Gold", 0xE2, 0xBF, 0x9B, 2203
	.byte	"Mocha Cream", 0xD3, 0xA8, 0x7C, 2475
	.byte	"Topaz", 0xBF, 0x91, 0x0C, 2400
	.byte	"Ashley Gold", 0xD1, 0x8E, 0x54, 2401
	.byte	"Amber Beige", 0xD8, 0xB5, 0x96, 2336
	.byte	"Seashell", 0xD6, 0xCC, 0xAF, 2476
	.byte	"Light Maize", 0xF2, 0xE3, 0xC4, 2604
	.byte	"Beige", 0xAA, 0x75, 0x3F, 2224
	.byte	"Sand Dune", 0x6B, 0x47, 0x14, 2477
	.byte	"Taupe", 0xD1, 0xBF, 0x91, 2298
	.byte	"Pro Brown", 0x6C, 0x46, 0x3D, 2610
	.byte	"Chocolate", 0x87, 0x60, 0x28, 2227
	.byte	"Pro Walnut", 0x75, 0x54, 0x26, 2629
	.byte	"Light Cocoa", 0x75, 0x54, 0x26, 2478
	.byte	"Cocoa Mulch", 0xB2, 0x82, 0x60, 2488
	.byte	"Brown", 0x59, 0x3D, 0x2B, 2251
	.byte	"Dark Brown", 0x59, 0x3D, 0x2B, 2372
	.byte	"Espresso", 0x3F, 0x30, 0x2B, 2337
	.byte	"Bamboo", 0xC1, 0x8E, 0x60, 2338
	.byte	"Almond", 0xAF, 0x75, 0x05, 2479
	.byte	"Toast", 0xBA, 0x75, 0x30, 2231
	.byte	"Sienna", 0x75, 0x54, 0x26, 2402
	.byte	"K.A. Bronze", 0xB2, 0x6B, 0x70, 2480
	.byte	"Pro Cinnamon", 0xA2, 0x46, 0x4E, 2611
	.byte	"Date", 0x9B, 0x4F, 0x19, 2290
	.byte	"Hazel", 0x9B, 0x4F, 0x19, 2481
	.byte	"Coffee Bean", 0x5B, 0x2D, 0x28, 2339
	.byte	"Dogwood", 0x59, 0x3D, 0x2B, 2563
	.byte	"Mahogany", 0x3F, 0x30, 0x2B, 2564
	.byte	"Best Brown", 0x3D, 0x30, 0x28, 2566
	.byte	"Mushroom", 0x63, 0x3A, 0x11, 2567
	.byte	"Perfect Tan", 0xC1, 0xA8, 0x75, 2568
	.byte	"Earthen Tan", 0x7A, 0x5B, 0x11, 2569
	.byte	"Golden Tan", 0xC1, 0xA8, 0x75, 2570
	.byte	"14 Kt. Gold", 0xF2, 0xBF, 0x49, 2586
	.byte	"TH Gold", 0xF2, 0xCE, 0x68, 2606
	.byte	"24 Kt. Gold", 0xD8, 0x8C, 0x02, 2602
	.byte	"Platinum", 0xC1, 0xB5, 0xA5, 2571
	.byte	"Pro Gray", 0x99, 0x89, 0x7C, 2739
	.byte	"Grayrod", 0xAD, 0xA0, 0x7A, 2572
	.byte	"Pewter", 0xAD, 0xA0, 0x7A, 2573
	.byte	"Aspen White", 0xF5, 0xE3, 0xCC, 2574
	.byte	"Dark Taupe", 0x66, 0x59, 0x4C, 2575
	.byte	"Egyptian Brown", 0x49, 0x35, 0x33, 2576
	.byte	"Oyster", 0xF5, 0xEB, 0xE0, 2403
	.byte	"Gray", 0xDD, 0xC6, 0xC4, 2207
	.byte	"Pearl Gray", 0xDB, 0xD3, 0xD3, 2340
	.byte	"Steel Gray", 0xD8, 0xCC, 0xD1, 2274
	.byte	"Skylight", 0xCC, 0xC1, 0xC6, 2482
	.byte	"Cloud", 0xAF, 0xAA, 0xA3, 2483
	.byte	"Silver Steel", 0xAD, 0xAF, 0xAA, 2592
	.byte	"Banner Gray", 0x91, 0x96, 0x93, 2585
	.byte	"Silvery Gray", 0x8C, 0x89, 0x84, 2484
	.byte	"Cinder", 0xCC, 0xC1, 0xC6, 2404
	.byte	"Saturn Gray", 0xDB, 0xD3, 0xD3, 2485
	.byte	"Dover Gray", 0xCC, 0xC1, 0xC6, 2405
	.byte	"Storm Gray", 0xB2, 0xA8, 0xB5, 2486
	.byte	"Sterling", 0xA8, 0x93, 0xAD, 2406
	.byte	"Metal", 0x66, 0x6D, 0x70, 2407
	.byte	"Twilight", 0x68, 0x66, 0x63, 2217
	.byte	"Aged Charcoal", 0x44, 0x3D, 0x38, 2565
	.byte	"Charcoal", 0x77, 0x77, 0x72, 2265
	.byte	"Smokey", 0x35, 0x38, 0x42, 2487
	.byte	"Ash", 0x3A, 0x49, 0x72, 2341
	.byte	"Black", 0x1C, 0x26, 0x30, 2296
	.byte	"Snow White", 0xF5, 0xEB, 0xE0, 2297
	.byte	"Natural White", 0xF5, 0xED, 0xDE, 2342
	.byte	"Eggshell", 0xF0, 0xE8, 0xD6, 2343
	.byte	"Jet Black", 0x1C, 0x26, 0x30, 2632
robison_anton_rayon_end:


sigma_polyester_codes:
	.byte	"White", 0xFF, 0xFF, 0xFF, 10
	.byte	"Black", 0x00, 0x00, 0x00, 20
	.byte	"Light Neon Green", 0xED, 0xFF, 0x50, 21
	.byte	"Neon Green", 0x96, 0xE8, 0x45, 32
	.byte	"Light Neon Orange", 0xFF, 0xE7, 0x56, 33
	.byte	"Med Neon Orange", 0xFF, 0x78, 0x24, 43
	.byte	"Neon Pink", 0xF2, 0x8D, 0xA6, 46
	.byte	"Neon Orange Pink", 0xC7, 0x0C, 0x57, 47
	.byte	"Silver", 0xE2, 0x2D, 0x2A, 101
	.byte	"Silver Diamond", 0xB8, 0xB8, 0xB8, 102
	.byte	"Lava Stone", 0x88, 0x91, 0x86, 112
	.byte	"Medium Grey", 0x73, 0x7F, 0x7F, 115
	.byte	"Dark Platinum", 0x56, 0x5E, 0x5A, 116
	.byte	"Charcoal", 0x51, 0x52, 0x50, 117
	.byte	"Badger Grey", 0x78, 0x76, 0x68, 118
	.byte	"Pumpkin Orange", 0xED, 0x57, 0x2F, 135
	.byte	"Turquoise", 0x2E, 0xA5, 0x9C, 138
	.byte	"Dark Wedgewood", 0x39, 0x62, 0x76, 142
	.byte	"Cardinal Red", 0x9B, 0x3B, 0x40, 213
	.byte	"Maroon", 0x6C, 0x3E, 0x47, 216
	.byte	"Rust", 0xBA, 0x6E, 0x4D, 253
	.byte	"Medium Rust", 0xBB, 0x3D, 0x2E, 255
	.byte	"Natural Pink", 0xF9, 0xDF, 0xCF, 301
	.byte	"Baby Pink", 0xFB, 0xDE, 0xD6, 303
	.byte	"Piggy Pink", 0xF7, 0xCD, 0xD5, 304
	.byte	"Sweet Pink", 0xF2, 0xAF, 0xB4, 305
	.byte	"Blushing Pink", 0xE8, 0x41, 0x8C, 307
	.byte	"Pink", 0xE7, 0x7F, 0x9D, 309
	.byte	"Rose Pink", 0xF0, 0x6F, 0x8C, 313
	.byte	"Green", 0x00, 0x83, 0x40, 317
	.byte	"Shocking Pink", 0xDF, 0x99, 0xB6, 321
	.byte	"Ruby", 0x82, 0x00, 0x52, 325
	.byte	"Garnet", 0xB1, 0x41, 0x5F, 333
	.byte	"Light Purple", 0xC3, 0x94, 0xAE, 345
	.byte	"Medium Purple", 0xA8, 0x6E, 0x91, 347
	.byte	"Dark Grape", 0x69, 0x41, 0x69, 348
	.byte	"Pastel Light Pink", 0xE6, 0xCF, 0xD5, 376
	.byte	"Light Baby Blue", 0xA8, 0xBE, 0xD7, 379
	.byte	"Crystal Blue", 0xA0, 0xBF, 0xD7, 380
	.byte	"Very Light Lavender", 0x90, 0xA6, 0xC6, 381
	.byte	"Cornflower", 0x8F, 0xAF, 0xC6, 382
	.byte	"Lavender", 0xB1, 0xB8, 0xD3, 383
	.byte	"Denim", 0x41, 0x6C, 0x9B, 385
	.byte	"Light Violet", 0x7D, 0x77, 0xAF, 386
	.byte	"Misty Rose", 0xFA, 0xDA, 0xF4, 387
	.byte	"Grape", 0x66, 0x40, 0x90, 390
	.byte	"Lt. Weathered Blue", 0xEA, 0xF0, 0xF9, 402
	.byte	"Baby Blue", 0xA6, 0xD8, 0xF6, 403
	.byte	"Med Baby Blue", 0x7B, 0x9C, 0xB0, 404
	.byte	"Med Pastel Blue", 0x64, 0x8D, 0xC7, 406
	.byte	"Blue Raspberry", 0x3D, 0x6A, 0xA1, 409
	.byte	"Med Royal Blue", 0x2D, 0x44, 0x91, 413
	.byte	"Ocean Blue", 0x14, 0x3D, 0x7A, 414
	.byte	"Med Navy", 0x11, 0x32, 0x63, 415
	.byte	"Dark Navy", 0x0E, 0x1F, 0x38, 423
	.byte	"Bright Sunshine", 0x0E, 0x1F, 0x38, 432
	.byte	"Teal", 0x00, 0x91, 0xA5, 443
	.byte	"Deep Teal", 0x00, 0x5B, 0x63, 448
	.byte	"Dark Teal", 0x00, 0x47, 0x4D, 449
	.byte	"Old Gold", 0xE5, 0xB1, 0x5C, 466
	.byte	"Cream", 0xD5, 0xBF, 0x9B, 501
	.byte	"Pale Salmon", 0xFF, 0xD0, 0x85, 503
	.byte	"Med Peach", 0xF6, 0xB0, 0x8E, 505
	.byte	"Pink Salmon", 0xB3, 0xE8, 0x51, 506
	.byte	"Dark Peach", 0xF1, 0xA2, 0x36, 508
	.byte	"Dark Brown", 0x6E, 0x43, 0x37, 513
	.byte	"Pale Red", 0xD8, 0x49, 0x3E, 527
	.byte	"Heron Blue", 0x69, 0x76, 0x98, 541
	.byte	"Pale Yellow", 0xFD, 0xE8, 0x96, 601
	.byte	"Pastel Yellow", 0xED, 0xE5, 0x5D, 602
	.byte	"Golden Puppy", 0xDF, 0xA2, 0x00, 609
	.byte	"Buttercup", 0xFD, 0xE8, 0x96, 612
	.byte	"Treasure Gold", 0xCE, 0xB2, 0x4C, 616
	.byte	"Old Gold", 0xAD, 0x95, 0x3E, 619
	.byte	"Pale Apricot", 0xFE, 0xF9, 0xEA, 627
	.byte	"Tan", 0xBD, 0x95, 0x65, 628
	.byte	"Mellow Yellow", 0xFD, 0xF7, 0x6C, 632
	.byte	"Lemon", 0xED, 0xEF, 0x05, 633
	.byte	"Amber", 0xF8, 0xC3, 0x00, 646
	.byte	"Mandarina", 0xE7, 0x78, 0x17, 649
	.byte	"Orange", 0xE6, 0x65, 0x35, 650
	.byte	"Golden Rod", 0xC6, 0x96, 0x32, 652
	.byte	"Light Olive", 0x98, 0x99, 0x6D, 653
	.byte	"Bright Gold", 0xC9, 0x83, 0x00, 654
	.byte	"Blue-Green", 0x00, 0x7B, 0x8D, 688
	.byte	"Forrest Green", 0x00, 0x4D, 0x3D, 695
	.byte	"Midnight Blue", 0x00, 0x7E, 0xBA, 697
	.byte	"Med Red", 0xCF, 0x00, 0x40, 700
	.byte	"Med Blue", 0x28, 0x43, 0x8C, 809
	.byte	"Sweet Apricot", 0xD0, 0xB4, 0x78, 812
	.byte	"Skin", 0xE5, 0xBE, 0x6C, 818
	.byte	"Jade", 0x44, 0x92, 0x84, 825
	.byte	"Light Silver", 0xCF, 0xCF, 0xCF, 829
	.byte	"Papaya Whip", 0xDC, 0x87, 0x5E, 831
	.byte	"Cooper", 0xB4, 0x70, 0x5D, 832
	.byte	"Light Pecan", 0x9B, 0x5C, 0x4B, 833
	.byte	"Burnt Rust", 0xA9, 0x31, 0x21, 838
	.byte	"Vegas Gold", 0xB1, 0x8B, 0x00, 842
	.byte	"Med Brown", 0x86, 0x46, 0x2E, 857
	.byte	"Med Russett", 0x61, 0x41, 0x25, 859
	.byte	"Med Copper", 0xB2, 0x5C, 0x31, 864
	.byte	"Dark Driftwood", 0x80, 0x6A, 0x61, 873
	.byte	"Birch", 0x63, 0x48, 0x31, 878
	.byte	"Dark Chocolate", 0x1A, 0x0C, 0x06, 891
	.byte	"Sky Blue 2", 0x96, 0xD5, 0xC8, 903
	.byte	"Aquamarine", 0xB4, 0xDC, 0xD8, 904
	.byte	"Golden Brown", 0xAF, 0x7D, 0x3E, 905
	.byte	"Sea Blue", 0x00, 0xA3, 0xA0, 906
	.byte	"Deep Sea", 0x00, 0x40, 0x5D, 913
	.byte	"Pastel Mint", 0xC9, 0xE3, 0xC5, 947
	.byte	"True Green", 0x55, 0xAF, 0x78, 949
	.byte	"Med Olive", 0x85, 0x83, 0x25, 951
	.byte	"Olive", 0x61, 0x60, 0x1C, 955
	.byte	"Light Jade", 0x70, 0x91, 0x88, 961
	.byte	"Smith Apple", 0xBE, 0xDC, 0x8C, 984
	.byte	"Light Lime", 0xBE, 0xE6, 0x78, 985
	.byte	"Grass Green", 0x76, 0xC8, 0x50, 988
	.byte	"Deep Teal", 0x46, 0x6E, 0x64, 448
	.byte	"Med Forrest Green", 0x35, 0x69, 0x36, 992
	.byte	"Deep Violet", 0x4B, 0x48, 0x84, 1031
	.byte	"Light Natural", 0xED, 0xED, 0xD2, 1140
	.byte	"Wheat", 0xF3, 0xD8, 0xA8, 1145
	.byte	"Desert Sand", 0xC8, 0xBE, 0x96, 1148
	.byte	"Egyptian Blue", 0x24, 0x3A, 0x7D, 1163
	.byte	"Gecko", 0x86, 0xBE, 0x4E, 1183
	.byte	"Burgandy", 0x8E, 0x40, 0x44, 1241
	.byte	"Med Orchid", 0x89, 0x34, 0x80, 1323
	.byte	"Med Purple", 0x8C, 0x6D, 0xAA, 1324
	.byte	"Very Old Gold", 0xB6, 0xA3, 0x6C, 1552
	.byte	"Light Spruce", 0x2E, 0x9F, 0x76, 1615
	.byte	"Paris Green", 0x98, 0xC1, 0x73, 1619
	.byte	"Timberwolf", 0xCD, 0xCD, 0xCD, 1707
	.byte	"Bright Blue", 0x2A, 0x37, 0x7E, 2031
	.byte	"Turquoise Blue", 0x00, 0x6C, 0xA5, 2093
	.byte	"Dark Wine", 0x83, 0x44, 0x55, 2250
	.byte	"Beige", 0xD0, 0xA4, 0x4F, 2518
	.byte	"Gold", 0xED, 0x92, 0x06, 2519
	.byte	"Med Orange", 0xED, 0xEF, 0x05, 3001
	.byte	"Dark Salmon", 0xC0, 0x7A, 0x46, 3014
	.byte	"Fire Red", 0xB4, 0x3C, 0x3C, 3015
	.byte	"Saddle Brown", 0x91, 0x5F, 0x46, 3142
	.byte	"Yellow Sun", 0xFF, 0xC5, 0x00, 4117
	.byte	"Deep Taupe", 0xA6, 0x8A, 0x68, 4371
	.byte	"Sky Blue", 0x00, 0xA4, 0xD9, 4419
	.byte	"Wild Peacock", 0x0B, 0x7F, 0x85, 4627
	.byte	"Millard Green", 0x00, 0x2D, 0x1F, 4735
	.byte	"Dark Blue", 0x11, 0x26, 0x3C, 5552
	.byte	"Powder Blue", 0x91, 0xB9, 0xE2, 5554
	.byte	"Froggy Green", 0x42, 0x96, 0x48, 5557
	.byte	"Stone Grey", 0x87, 0x8C, 0x8C, 8010
sigma_polyester_end:


sulky_rayon_codes:
	.byte	"Cornsilk", 0xEF, 0xC8, 0x10, 502
	.byte	"Deep Arctic Sky", 0x0C, 0x08, 0x2D, 505
	.byte	"Nutmeg", 0xB2, 0x6C, 0x29, 521
	.byte	"Autumn Gold", 0xE7, 0x90, 0x02, 523
	.byte	"English Green", 0x34, 0x48, 0x1E, 525
	.byte	"Cobalt Blue", 0x11, 0x36, 0x75, 526
	.byte	"Forest Green", 0x11, 0x14, 0x08, 538
	.byte	"Lipstick", 0xE1, 0x00, 0x00, 561
	.byte	"Spice", 0xFF, 0xB4, 0x35, 562
	.byte	"Butterfly Gold", 0xF3, 0xA0, 0x01, 567
	.byte	"Cinnamon", 0xE6, 0x6D, 0x00, 568
	.byte	"Garden Green", 0x16, 0x5F, 0x28, 569
	.byte	"Deep Aqua", 0x08, 0x8E, 0x6C, 571
	.byte	"Blue Ribbon", 0x10, 0x0A, 0x7C, 572
	.byte	"Mint Julep", 0x35, 0x69, 0x3D, 580
	.byte	"Dusty Peach", 0xE9, 0xBD, 0x96, 619
	.byte	"Sunset", 0xCD, 0x39, 0x00, 621
	.byte	"Moss Green", 0x77, 0x71, 0x13, 630
	.byte	"Med. Aqua", 0x1C, 0x6F, 0x51, 640
	.byte	"Arctic Sky", 0x26, 0x23, 0x45, 643
	.byte	"Bright White", 0xF9, 0xF9, 0xFF, 1001
	.byte	"Soft White", 0xF9, 0xF9, 0xF4, 1002
	.byte	"Black", 0x00, 0x00, 0x00, 1005
	.byte	"Steel Gray", 0xB7, 0xA9, 0xAC, 1011
	.byte	"Med. Peach", 0xE1, 0xAF, 0x9A, 1015
	.byte	"Pastel Coral", 0xEC, 0x96, 0x8C, 1016
	.byte	"Pastel Peach", 0xEF, 0xDF, 0xBD, 1017
	.byte	"Peach", 0xEC, 0xA0, 0x82, 1019
	.byte	"Dark Peach", 0xF0, 0x82, 0x78, 1020
	.byte	"Maple", 0xEB, 0x66, 0x02, 1021
	.byte	"Cream", 0xFF, 0xF7, 0xD5, 1022
	.byte	"Yellow", 0xFF, 0xE6, 0x69, 1023
	.byte	"Goldenrod", 0xFF, 0xB8, 0x00, 1024
	.byte	"Mine Gold", 0xD7, 0x80, 0x00, 1025
	.byte	"Baby Blue", 0xBE, 0xC3, 0xE1, 1028
	.byte	"Med. Blue", 0xA0, 0xC3, 0xEB, 1029
	.byte	"Periwinkle", 0xA6, 0xA2, 0xC6, 1030
	.byte	"Med. Orchid", 0xDF, 0xBE, 0xC8, 1031
	.byte	"Med. Purple", 0xE6, 0x8C, 0xEB, 1032
	.byte	"Dk. Orchid", 0xD8, 0x64, 0x96, 1033
	.byte	"Burgundy", 0xC6, 0x32, 0x3C, 1034
	.byte	"Dk. Burgundy", 0x79, 0x00, 0x00, 1035
	.byte	"Lt.Red", 0xF9, 0x00, 0x00, 1037
	.byte	"True Red", 0xEB, 0x00, 0x00, 1039
	.byte	"Med. Dk. Khaki", 0x87, 0x73, 0x75, 1040
	.byte	"Med. Dk. Gray", 0x8C, 0x7F, 0x83, 1041
	.byte	"Bright Navy Blue", 0x32, 0x1E, 0x50, 1042
	.byte	"Dk. Navy", 0x19, 0x05, 0x25, 1043
	.byte	"Midnight Blue", 0x1D, 0x06, 0x2F, 1044
	.byte	"Lt. Teal", 0xC3, 0xEF, 0xBF, 1045
	.byte	"Teal", 0x2E, 0x83, 0x59, 1046
	.byte	"Mint Green", 0xA6, 0xC2, 0x84, 1047
	.byte	"Grass Green", 0x42, 0xA0, 0x21, 1049
	.byte	"Xmas Green", 0x1E, 0x64, 0x19, 1051
	.byte	"Med. Dk. Ecru", 0xEE, 0xBE, 0xAE, 1054
	.byte	"Tawny Tan", 0xEB, 0xBC, 0x80, 1055
	.byte	"Med Tawny Tan", 0xAF, 0x5B, 0x00, 1056
	.byte	"Dk Tawny Tan", 0x64, 0x27, 0x02, 1057
	.byte	"Tawny Brown", 0x66, 0x35, 0x00, 1058
	.byte	"Dk Tawny Brown", 0x53, 0x06, 0x01, 1059
	.byte	"Pale Yellow", 0xFF, 0xF7, 0xB9, 1061
	.byte	"Pale Yellow-Green", 0xF0, 0xF8, 0xEC, 1063
	.byte	"Pale Peach", 0xE6, 0xB4, 0xAA, 1064
	.byte	"Orange Yellow", 0xFF, 0x91, 0x00, 1065
	.byte	"Primrose", 0xFF, 0xF1, 0x80, 1066
	.byte	"Lemon Yellow", 0xFF, 0xFF, 0x85, 1067
	.byte	"Pink Tint", 0xF3, 0xDB, 0xD9, 1068
	.byte	"Gold", 0xF6, 0xCE, 0x69, 1070
	.byte	"Off White", 0xF9, 0xF9, 0xEA, 1071
	.byte	"Pale Powder Blue", 0xD6, 0xD5, 0xE8, 1074
	.byte	"Royal Blue", 0x5A, 0x5A, 0x8B, 1076
	.byte	"Jade Tint", 0xBE, 0xCD, 0xC8, 1077
	.byte	"Tangerine", 0xFF, 0x66, 0x00, 1078
	.byte	"Emerald Green", 0x17, 0x55, 0x23, 1079
	.byte	"Orchid", 0xDC, 0x82, 0xA0, 1080
	.byte	"Brick", 0xF0, 0x6E, 0x78, 1081
	.byte	"Ecru", 0xF7, 0xE3, 0xBB, 1082
	.byte	"Spark Gold", 0xFF, 0xC1, 0x00, 1083
	.byte	"Silver", 0xE2, 0xCF, 0xC7, 1085
	.byte	"Pale Sea Foam", 0xF9, 0xF9, 0xE0, 1086
	.byte	"Deep Peacock", 0x16, 0x62, 0x5F, 1090
	.byte	"Med Turquoise", 0x26, 0xBF, 0xCA, 1094
	.byte	"Turquoise", 0x10, 0xD1, 0xBD, 1095
	.byte	"Dk Turquoise", 0x0F, 0x69, 0x78, 1096
	.byte	"Lt Grass Green", 0xC2, 0xD3, 0x7D, 1100
	.byte	"True Green", 0x09, 0x85, 0x31, 1101
	.byte	"Dk Khaki", 0x02, 0x14, 0x0F, 1103
	.byte	"Pastel Yellow-Grn", 0xA5, 0xAF, 0x68, 1104
	.byte	"Lt Mauve", 0xFA, 0xA4, 0xA4, 1108
	.byte	"Hot Pink", 0xDC, 0x64, 0x96, 1109
	.byte	"Pastel Orchid", 0xFC, 0xCB, 0xDF, 1111
	.byte	"Royal Purple", 0x46, 0x01, 0x6E, 1112
	.byte	"Pastel Mauve", 0xF0, 0xC8, 0xB4, 1113
	.byte	"Lt Pink", 0xF0, 0xB9, 0xB9, 1115
	.byte	"Mauve", 0xF5, 0xA9, 0xA0, 1117
	.byte	"Dk Mauve", 0xB4, 0x6E, 0x75, 1119
	.byte	"Pale Pink", 0xF0, 0xD6, 0xD2, 1120
	.byte	"Pink", 0xFA, 0xB9, 0xCB, 1121
	.byte	"Purple", 0x82, 0x28, 0x8E, 1122
	.byte	"Sun Yellow", 0xFF, 0xEC, 0x00, 1124
	.byte	"Tan", 0xDC, 0x8C, 0x17, 1126
	.byte	"Med Ecru", 0xFA, 0xEC, 0xC6, 1127
	.byte	"Dk Ecru", 0xC3, 0x94, 0x71, 1128
	.byte	"Brown", 0x6A, 0x1F, 0x06, 1129
	.byte	"Dark Brown", 0x55, 0x16, 0x02, 1130
	.byte	"Cloister Brown", 0x49, 0x00, 0x02, 1131
	.byte	"Peacock Blue", 0x50, 0x7D, 0xAA, 1134
	.byte	"Pastel Yellow", 0xFF, 0xF0, 0x72, 1135
	.byte	"Yellow Orange", 0xFF, 0xBE, 0x00, 1137
	.byte	"True Blue", 0x4A, 0x58, 0x70, 1143
	.byte	"Powder Blue", 0xB4, 0xE1, 0xEB, 1145
	.byte	"Xmas Red", 0xEB, 0x00, 0x00, 1147
	.byte	"Lt Coral", 0xFF, 0xBD, 0xBD, 1148
	.byte	"Deep Ecru", 0xE8, 0xC8, 0x9C, 1149
	.byte	"Powder Blue Tint", 0xE2, 0xE2, 0xEB, 1151
	.byte	"Coral", 0xFA, 0x99, 0x99, 1154
	.byte	"Lt Army Green", 0x63, 0x63, 0x27, 1156
	.byte	"Dk Maple", 0xBA, 0x45, 0x00, 1158
	.byte	"Temple Gold", 0xD3, 0x9D, 0x00, 1159
	.byte	"Deep Teal", 0x10, 0x39, 0x4A, 1162
	.byte	"Lt Sky Blue", 0xDF, 0xE5, 0xEB, 1165
	.byte	"Med Steel Gray", 0x8E, 0x7E, 0x7E, 1166
	.byte	"Maize Yellow", 0xFF, 0xD2, 0x26, 1167
	.byte	"True Orange", 0xF5, 0x74, 0x0A, 1168
	.byte	"Bayberry Red", 0x9C, 0x00, 0x00, 1169
	.byte	"Lt Brown", 0x97, 0x5F, 0x2F, 1170
	.byte	"Weathered Blue", 0x08, 0x18, 0x0E, 1171
	.byte	"Med Weathered Blue", 0x6E, 0x78, 0x8C, 1172
	.byte	"Med Army Green", 0x59, 0x59, 0x1D, 1173
	.byte	"Dk Pine Green", 0x0D, 0x29, 0x04, 1174
	.byte	"Dk Avocado", 0x15, 0x2D, 0x04, 1175
	.byte	"Med Dk Avocado", 0x51, 0x53, 0x08, 1176
	.byte	"Avocado", 0x89, 0x98, 0x12, 1177
	.byte	"Dk Taupe", 0x8F, 0x62, 0x3D, 1179
	.byte	"Med Taupe", 0xA5, 0x89, 0x73, 1180
	.byte	"Rust", 0xCB, 0x00, 0x00, 1181
	.byte	"Blue Black", 0x02, 0x01, 0x14, 1182
	.byte	"Black Cherry", 0x32, 0x06, 0x14, 1183
	.byte	"Orange Red", 0xFF, 0x66, 0x00, 1184
	.byte	"Golden Yellow", 0xFC, 0xBE, 0x05, 1185
	.byte	"Sable Brown", 0x5B, 0x00, 0x00, 1186
	.byte	"Mimosa Yellow", 0xFF, 0xE5, 0x00, 1187
	.byte	"Red Geranium", 0xFF, 0x00, 0x4B, 1188
	.byte	"Dk Chestnut", 0x4B, 0x12, 0x2D, 1189
	.byte	"Med Burgundy", 0xA0, 0x46, 0x56, 1190
	.byte	"Dk Rose", 0xBD, 0x1E, 0x60, 1191
	.byte	"Fuchsia", 0xD2, 0x1E, 0x82, 1192
	.byte	"Lavender", 0xE6, 0xAF, 0xD2, 1193
	.byte	"Lt Purple", 0xD2, 0x74, 0xD7, 1194
	.byte	"Dk Purple", 0x37, 0x01, 0x50, 1195
	.byte	"Blue", 0x96, 0xC3, 0xE1, 1196
	.byte	"Med Navy", 0x22, 0x0F, 0x34, 1197
	.byte	"Dusty Navy", 0x3C, 0x50, 0x75, 1198
	.byte	"Admiral Navy Blue", 0x2A, 0x14, 0x3F, 1199
	.byte	"Med Dk Navy", 0x14, 0x0B, 0x2D, 1200
	.byte	"Med Powder Blue", 0x64, 0x8B, 0xBE, 1201
	.byte	"Deep Turquoise", 0x18, 0x2B, 0x56, 1202
	.byte	"Lt Weathered Blue", 0xAE, 0xB8, 0xC3, 1203
	.byte	"Pastel Jade", 0xA8, 0xC8, 0xBC, 1204
	.byte	"Med Jade", 0x6E, 0x90, 0xA5, 1205
	.byte	"Dark Jade", 0x1E, 0x6E, 0x6F, 1206
	.byte	"Sea Foam Green", 0x80, 0xA3, 0x88, 1207
	.byte	"Mallard Green", 0x0C, 0x3D, 0x03, 1208
	.byte	"Lt Avocado", 0xBD, 0xD1, 0x63, 1209
	.byte	"Dk Army Green", 0x27, 0x3B, 0x00, 1210
	.byte	"Lt Khaki", 0x95, 0xA4, 0x90, 1211
	.byte	"Khaki", 0x63, 0x63, 0x2D, 1212
	.byte	"Taupe", 0xB9, 0xA0, 0x96, 1213
	.byte	"Med Chestnut", 0x64, 0x28, 0x28, 1214
	.byte	"Blackberry", 0x50, 0x0A, 0x1E, 1215
	.byte	"Med Maple", 0xAC, 0x1C, 0x01, 1216
	.byte	"Chestnut", 0x97, 0x1F, 0x01, 1217
	.byte	"Silver Gray", 0xDF, 0xDF, 0xCB, 1218
	.byte	"Gray", 0x98, 0x88, 0x8C, 1219
	.byte	"Charcoal Gray", 0x76, 0x59, 0x60, 1220
	.byte	"Lt Baby Blue", 0xD1, 0xDB, 0xFF, 1222
	.byte	"Baby Blue Tint", 0xDC, 0xE0, 0xF1, 1223
	.byte	"Bright Pink", 0xF0, 0xA0, 0xB9, 1224
	.byte	"Pastel Pink", 0xFA, 0xCB, 0xCB, 1225
	.byte	"Dkl Periwinkle", 0x57, 0x36, 0x9E, 1226
	.byte	"Gold Green", 0xAF, 0x89, 0x01, 1227
	.byte	"Drab Green", 0x96, 0xAA, 0x8B, 1228
	.byte	"Lt Putty", 0xE0, 0xDB, 0xDB, 1229
	.byte	"Dk Teal", 0x0B, 0x41, 0x33, 1230
	.byte	"Med Rose", 0xE5, 0x32, 0x6A, 1231
	.byte	"Classic Green", 0x19, 0x32, 0x07, 1232
	.byte	"Ocean Teal", 0x0D, 0x22, 0x10, 1233
	.byte	"Almost Black", 0x3C, 0x1B, 0x1F, 1234
	.byte	"Deep Purple", 0x78, 0x32, 0x98, 1235
	.byte	"Lt Silver", 0xEA, 0xE4, 0xE4, 1236
	.byte	"Deep Mauve", 0xBC, 0x3D, 0x2C, 1237
	.byte	"Orange Sunrise", 0xFF, 0x83, 0x00, 1238
	.byte	"Apricot", 0xFF, 0xAB, 0x57, 1239
	.byte	"Smokey Grey", 0x74, 0x58, 0x6C, 1240
	.byte	"Nassau Blue", 0x54, 0x3A, 0x8D, 1242
	.byte	"Orange Flame", 0xFF, 0x00, 0x00, 1246
	.byte	"Mahogany", 0x66, 0x00, 0x00, 1247
	.byte	"Med Pastel Blue", 0xD2, 0xE6, 0xF0, 1248
	.byte	"Cornflower Blue", 0x62, 0xAA, 0xDC, 1249
	.byte	"Duck Wing Blue", 0x27, 0x5C, 0x70, 1250
	.byte	"Bright Turquoise", 0x30, 0x6F, 0x75, 1251
	.byte	"Bright Peacock", 0x09, 0xA1, 0xA8, 1252
	.byte	"Dk Sapphire", 0x1B, 0x4C, 0xA4, 1253
	.byte	"Dusty Lavender", 0xE6, 0xB9, 0xF5, 1254
	.byte	"Deep Orchid", 0xBE, 0x19, 0x82, 1255
	.byte	"Sweet Pink", 0xEB, 0x82, 0x96, 1256
	.byte	"Deep Coral", 0xE6, 0x00, 0x41, 1257
	.byte	"Coral Reed", 0xF0, 0xC4, 0xA0, 1258
	.byte	"Salmon Peach", 0xE2, 0x82, 0x64, 1259
	.byte	"Red Jubilee", 0xB3, 0x00, 0x00, 1263
	.byte	"Cognac", 0x6A, 0x00, 0x00, 1264
	.byte	"Burnt Toast", 0x9B, 0x6B, 0x2C, 1265
	.byte	"Toast", 0x9C, 0x6D, 0x45, 1266
	.byte	"Mink Brown", 0x86, 0x4C, 0x31, 1267
	.byte	"Light Gray Khaki", 0xEF, 0xEF, 0xE5, 1268
	.byte	"Dk Gray Khaki", 0xB7, 0xB7, 0xAF, 1270
	.byte	"Evergreen", 0x3C, 0x4F, 0x31, 1271
	.byte	"Hedge Green", 0x4A, 0x4A, 0x19, 1272
	.byte	"Nile Green", 0x5C, 0x9A, 0x1A, 1274
	.byte	"Sea Mist", 0xE0, 0xE6, 0xC8, 1275
	.byte	"Pistachio", 0x70, 0x77, 0x0F, 1276
	.byte	"Ivy Green", 0x02, 0x76, 0x02, 1277
	.byte	"Bright Green", 0x00, 0xAF, 0x38, 1278
	.byte	"Willow Green", 0x93, 0xD1, 0x6C, 1279
	.byte	"Dk Willow Green", 0x46, 0xB7, 0x74, 1280
	.byte	"Slate Gray", 0x48, 0x3D, 0x59, 1283
	.byte	"Dk Winter Sky", 0x46, 0x6E, 0x78, 1284
	.byte	"Dk Sage Green", 0x13, 0x4F, 0x45, 1285
	.byte	"Dk French Green", 0x34, 0x32, 0x13, 1286
	.byte	"French Green", 0x41, 0x55, 0x45, 1287
	.byte	"Aqua", 0x0F, 0xA5, 0x6F, 1288
	.byte	"Ice Blue", 0xDC, 0xEB, 0xF0, 1289
	.byte	"Winter Sky", 0x72, 0x74, 0x83, 1291
	.byte	"Heron Blue", 0xD1, 0xDC, 0xFA, 1292
	.byte	"Deep Nassau Blue", 0x44, 0x23, 0x5D, 1293
	.byte	"Deep Slate Gray", 0x41, 0x20, 0x44, 1294
	.byte	"Sterling", 0x82, 0x87, 0x8C, 1295
	.byte	"Hyacinth", 0xD2, 0xAA, 0xF0, 1296
	.byte	"Lt Plum", 0x73, 0x5A, 0x64, 1297
	.byte	"Dk Plum", 0x64, 0x46, 0x64, 1298
	.byte	"Purple Shadow", 0x41, 0x14, 0x46, 1299
	.byte	"Plum", 0x7E, 0x1E, 0x46, 1300
	.byte	"Deep Eggplant", 0x32, 0x00, 0x46, 1301
	.byte	"Eggplant", 0x6E, 0x0A, 0x96, 1302
	.byte	"Dewberry", 0xB4, 0x73, 0x64, 1304
	.byte	"Sage Green", 0xAE, 0xC6, 0xBB, 1305
	.byte	"Gun Metal Gray", 0x7E, 0x6C, 0x7C, 1306
	.byte	"Petal Pink", 0xDB, 0x64, 0x78, 1307
	.byte	"Magenta", 0x78, 0x23, 0x46, 1309
	.byte	"Mulberry", 0x96, 0x1A, 0x32, 1311
	.byte	"Wine", 0x84, 0x00, 0x00, 1312
	.byte	"Bittersweet", 0xFC, 0x8F, 0x0C, 1313
	.byte	"Poppy", 0xFF, 0x00, 0x00, 1317
	.byte	"Gray Khaki", 0xCB, 0xCB, 0xBD, 1321
	.byte	"Chartreuse", 0x81, 0x89, 0x01, 1322
	.byte	"Whisper Gray", 0xF8, 0xF5, 0xF1, 1325
	.byte	"Dk Whisper Gray", 0xD5, 0xC7, 0xC3, 1327
	.byte	"Nickel Gray", 0xC0, 0xB2, 0xB7, 1328
	.byte	"Dk Nickel Gray", 0xAB, 0xA0, 0xA8, 1329
	.byte	"Pale Green", 0xED, 0xF6, 0xD4, 1331
	.byte	"Deep Chartreuse", 0x86, 0x81, 0x05, 1332
	.byte	"Sunflower Gold", 0xF3, 0xB6, 0x00, 1333
	.byte	"Green Peacock", 0x34, 0x96, 0x69, 1503
	.byte	"Putty", 0xC1, 0xCB, 0xB9, 1508
	.byte	"Lime Green", 0x7A, 0xB3, 0x1D, 1510
	.byte	"Deep Rose", 0xEE, 0x50, 0x78, 1511
	.byte	"Wild Peacock", 0x00, 0x7A, 0x67, 1513
	.byte	"Rosebud", 0xFF, 0x8C, 0xCB, 1515
	.byte	"Coachman Green", 0x01, 0x4F, 0x3A, 1517
	.byte	"Lt Rose", 0xCD, 0x05, 0x4D, 1533
	.byte	"Sapphire", 0x34, 0x7D, 0xCB, 1534
	.byte	"Team Blue", 0x23, 0x23, 0x8B, 1535
	.byte	"Midnight Teal", 0x08, 0x17, 0x05, 1536
	.byte	"Peach Fluff", 0xFF, 0xD6, 0xC7, 1543
	.byte	"Purple Accent", 0x9C, 0x64, 0x84, 1545
	.byte	"Flax", 0xE6, 0xAE, 0x6F, 1549
	.byte	"Desert Cactus", 0x6C, 0x8E, 0x87, 1550
	.byte	"Ocean Aqua", 0x80, 0xB0, 0xAE, 1551
	.byte	"Dk Desert Cactus", 0x6C, 0x7C, 0x71, 1552
	.byte	"Purple Passion", 0x8C, 0x74, 0x8C, 1554
	.byte	"Tea Rose", 0xEB, 0x71, 0x83, 1558
	.byte	"Marine Aqua", 0x68, 0xE0, 0xF8, 1560
	.byte	"Deep Hyacinth", 0xB5, 0x8C, 0xC7, 1561
	.byte	"Shrimp", 0xFA, 0xD2, 0xAA, 1800
	.byte	"Flesh", 0xFA, 0xDC, 0x96, 1801
	.byte	"Soft Blush", 0xFF, 0xC8, 0x96, 1802
	.byte	"Island Peach", 0xFF, 0x9B, 0x6E, 1803
	.byte	"Bayou Blue", 0x37, 0x5A, 0x73, 1804
	.byte	"Ocean View", 0x28, 0x50, 0x5A, 1805
	.byte	"Madras Blue", 0xA0, 0xB9, 0xC3, 1806
	.byte	"Soft Heather", 0xB4, 0x96, 0x82, 1807
	.byte	"Velvet Slipper", 0xD2, 0xAF, 0x9B, 1808
	.byte	"Iced Mauve", 0xA0, 0x7D, 0x82, 1809
	.byte	"Wild Mulberry", 0x64, 0x50, 0x55, 1810
	.byte	"Wineberry", 0x3C, 0x28, 0x37, 1811
	.byte	"Wildflower", 0x6E, 0x2D, 0x5A, 1812
	.byte	"Plum Wine", 0x6E, 0x2D, 0x41, 1813
	.byte	"Orchid Kiss", 0xAF, 0x4B, 0x69, 1814
	.byte	"Japanese Fern", 0x91, 0xB4, 0x32, 1815
	.byte	"Honeydew", 0xD7, 0xF5, 0x8C, 1816
	.byte	"Lemon Grass", 0xAA, 0xAF, 0x14, 1817
	.byte	"Fairway Mist", 0xC8, 0xF5, 0x8C, 1818
	.byte	"Outback", 0xC3, 0x91, 0x3C, 1819
	.byte	"Fruit Shake", 0xC3, 0x8C, 0x73, 1820
	.byte	"Creamy Peach", 0xFA, 0xC8, 0x96, 1821
	.byte	"Toffee", 0x96, 0x5A, 0x37, 1822
	.byte	"Cocoa", 0x96, 0x5A, 0x28, 1823
	.byte	"Gentle Rain", 0xD2, 0xC3, 0xAF, 1824
	.byte	"Barnyard Grass", 0x5F, 0x96, 0x19, 1825
	.byte	"Galley Gold", 0xAA, 0x82, 0x0A, 1826
	.byte	"Coral Sunset", 0xFF, 0x64, 0x3C, 1827
	.byte	"Seashell", 0xFF, 0xE6, 0xAA, 1828
	.byte	"Crème Brulee", 0xF0, 0xEB, 0xA5, 1829
	.byte	"Lilac", 0xB4, 0x73, 0x96, 1830
	.byte	"Liimeade", 0x91, 0xE1, 0x2D, 1831
	.byte	"Desert Glow", 0xE1, 0x91, 0x19, 1832
	.byte	"Pumpkin Pie", 0xD2, 0x5F, 0x00, 1833
	.byte	"Pea Soup", 0xAF, 0xAA, 0x05, 1834
	.byte	"Peapod Green", 0x6E, 0x82, 0x05, 1835
	.byte	"Loden Green", 0x3C, 0x4B, 0x05, 1836
	.byte	"Lt. Cocoa", 0x9B, 0x73, 0x5A, 1837
	.byte	"Cocoa Cream", 0xCD, 0xAA, 0x7D, 1838
	.byte	"Cameo", 0x87, 0xC8, 0x87, 1839
	.byte	"Sand", 0xF9, 0xE6, 0xCA, 508
	.byte	"Bone", 0xFD, 0xF3, 0xDA, 520
	.byte	"Dark Ash", 0x5D, 0x34, 0x46, 1241
	.byte	"Spring Moss", 0xE0, 0xC6, 0x3B, 1243
	.byte	"Summer Gold", 0xDD, 0xAB, 0x00, 1260
	.byte	"Dk. Autumn Gold", 0xA9, 0x88, 0x03, 1262
	.byte	"Mushroom", 0xAC, 0x87, 0x83, 1269
	.byte	"Dark Forest", 0x36, 0x36, 0x1F, 1273
	.byte	"Watermelon", 0xFA, 0x5F, 0x7F, 1303
	.byte	"Caribbean Mist", 0xA3, 0xC2, 0xD7, 1644
sulky_rayon_end:


.byte_art_rayon_codes:
.byte_art_rayon_end:


.byte_art_polyester_codes:
.byte_art_polyester_end:


.byteelight_polyester_codes:
.byteelight_polyester_end:


z102_isacord_polyester_codes:
	.byte	"?", 0xF8, 0xFF, 0xFF, 17
	.byte	"?", 0x00, 0x00, 0x00, 20
	.byte	"?", 0xB7, 0xBA, 0xBA, 105
	.byte	"?", 0x73, 0x78, 0x7A, 108
	.byte	"?", 0x45, 0x4B, 0x58, 138
	.byte	"?", 0x9E, 0xA9, 0xA6, 142
	.byte	"?", 0xC8, 0xC6, 0xBD, 150
	.byte	"?", 0xFA, 0xEE, 0x5C, 220
	.byte	"?", 0xE5, 0xCB, 0x4F, 221
	.byte	"?", 0xFF, 0xF4, 0x6A, 230
	.byte	"?", 0xFE, 0xF9, 0xD9, 270
	.byte	"?", 0xFF, 0xDC, 0x00, 311
	.byte	"?", 0x62, 0x4F, 0x00, 345
	.byte	"?", 0xB8, 0xB2, 0x5A, 352
	.byte	"?", 0x8D, 0x8F, 0x5B, 453
	.byte	"?", 0xFF, 0xF4, 0xA5, 520
	.byte	"?", 0xB9, 0x8E, 0x03, 542
	.byte	"?", 0xE4, 0xC1, 0x80, 651
	.byte	"?", 0xC5, 0xBF, 0xA6, 672
	.byte	"?", 0x96, 0x83, 0x6D, 722
	.byte	"?", 0x4E, 0x35, 0x00, 747
	.byte	"?", 0xDD, 0xCB, 0xA5, 761
	.byte	"?", 0x60, 0x58, 0x40, 776
	.byte	"?", 0xFF, 0xAF, 0x02, 800
	.byte	"?", 0xF6, 0xAE, 0x32, 811
	.byte	"?", 0xC8, 0x93, 0x34, 822
	.byte	"?", 0xE5, 0x93, 0x00, 824
	.byte	"?", 0xC8, 0x93, 0x40, 832
	.byte	"?", 0x9E, 0x94, 0x7F, 873
	.byte	"?", 0xC8, 0x70, 0x0B, 922
	.byte	"?", 0xBB, 0x57, 0x04, 931
	.byte	"?", 0xB1, 0x90, 0x72, 1061
	.byte	"?", 0xFF, 0x81, 0x01, 1102
	.byte	"?", 0xB1, 0x50, 0x0A, 1115
	.byte	"?", 0xC0, 0x9C, 0x72, 1123
	.byte	"?", 0x84, 0x3D, 0x07, 1134
	.byte	"?", 0xD8, 0xA6, 0x7D, 1141
	.byte	"?", 0x82, 0x42, 0x1B, 1154
	.byte	"?", 0xFF, 0x73, 0x19, 1300
	.byte	"?", 0xFF, 0x3D, 0x1E, 1305
	.byte	"?", 0xBA, 0x40, 0x05, 1311
	.byte	"?", 0xC7, 0x3C, 0x13, 1312
	.byte	"?", 0xE6, 0x6B, 0x21, 1332
	.byte	"?", 0x3D, 0x1C, 0x11, 1346
	.byte	"?", 0xFF, 0xBC, 0x95, 1351
	.byte	"?", 0xFF, 0xCC, 0x93, 1362
	.byte	"?", 0x37, 0x37, 0x32, 1375
	.byte	"?", 0xFF, 0xAF, 0x94, 1532
	.byte	"?", 0x5B, 0x40, 0x32, 1565
	.byte	"?", 0xFF, 0x60, 0x46, 1600
	.byte	"?", 0xFF, 0x6D, 0x71, 1753
	.byte	"?", 0xEB, 0xBA, 0xAE, 1755
	.byte	"?", 0xEB, 0x2D, 0x2B, 1805
	.byte	"?", 0xFF, 0x98, 0x8F, 1840
	.byte	"?", 0x43, 0x43, 0x31, 1874
	.byte	"?", 0xC1, 0x19, 0x14, 1902
	.byte	"?", 0xC8, 0x10, 0x0D, 1903
	.byte	"?", 0xBF, 0x0A, 0x21, 1906
	.byte	"?", 0xD2, 0x3C, 0x3E, 1921
	.byte	"?", 0x8F, 0x8C, 0x93, 1972
	.byte	"?", 0xA3, 0x1A, 0x1C, 2011
	.byte	"?", 0x4D, 0x03, 0x08, 2115
	.byte	"?", 0xFF, 0xCD, 0xCC, 2155
	.byte	"?", 0x87, 0x1C, 0x45, 2500
	.byte	"?", 0xDB, 0x40, 0x83, 2508
	.byte	"?", 0xFF, 0x66, 0x8A, 2520
	.byte	"?", 0xC9, 0x12, 0x43, 2521
	.byte	"?", 0xFF, 0xA0, 0xB6, 2530
	.byte	"?", 0xFE, 0xA5, 0xB9, 2550
	.byte	"?", 0x62, 0x6C, 0x7E, 2674
	.byte	"?", 0x5E, 0x19, 0x42, 2711
	.byte	"?", 0x33, 0x00, 0x1D, 2715
	.byte	"?", 0xA5, 0x7B, 0x8D, 2764
	.byte	"?", 0x70, 0x2A, 0x69, 2810
	.byte	"?", 0xB3, 0x85, 0xBC, 2830
	.byte	"?", 0x24, 0x00, 0x47, 2900
	.byte	"?", 0x72, 0x45, 0x93, 2910
	.byte	"?", 0x63, 0x4D, 0x86, 2920
	.byte	"?", 0x00, 0x01, 0x36, 3110
	.byte	"?", 0x00, 0x00, 0x21, 3355
	.byte	"?", 0x05, 0x4A, 0xBD, 3522
	.byte	"?", 0x1C, 0x00, 0x5D, 3541
	.byte	"?", 0x00, 0x1F, 0x71, 3544
	.byte	"?", 0x00, 0x2E, 0x5E, 3622
	.byte	"?", 0x71, 0xAA, 0xD8, 3630
	.byte	"?", 0x00, 0x17, 0x48, 3644
	.byte	"?", 0xC8, 0xDB, 0xE4, 3650
	.byte	"?", 0x9F, 0xC7, 0xDF, 3730
	.byte	"?", 0x08, 0x2E, 0x4D, 3743
	.byte	"?", 0x98, 0xB0, 0xBC, 3750
	.byte	"?", 0x23, 0x67, 0x9C, 3810
	.byte	"?", 0x3D, 0x65, 0x7E, 3842
	.byte	"?", 0x00, 0x66, 0x9F, 3901
	.byte	"?", 0x47, 0xAE, 0xDD, 3910
	.byte	"?", 0xBB, 0xDF, 0xEB, 3962
	.byte	"?", 0xBA, 0xBE, 0xB7, 3971
	.byte	"?", 0x01, 0x5D, 0x7E, 4032
	.byte	"?", 0xD5, 0xDD, 0xDB, 4071
	.byte	"?", 0x88, 0x8D, 0x8E, 4073
	.byte	"?", 0x00, 0x7C, 0xA6, 4103
	.byte	"?", 0x3E, 0xBB, 0xC8, 4111
	.byte	"?", 0x00, 0x5C, 0x79, 4116
	.byte	"?", 0x80, 0xCC, 0xD8, 4240
	.byte	"?", 0xAC, 0xCE, 0xC7, 4250
	.byte	"?", 0x00, 0x6E, 0x74, 4410
	.byte	"?", 0x00, 0x2A, 0x29, 4515
	.byte	"?", 0x38, 0xA4, 0xAE, 4620
	.byte	"?", 0xAF, 0xD8, 0xCD, 5050
	.byte	"?", 0x14, 0x9B, 0x7B, 5210
	.byte	"?", 0x7A, 0xC8, 0xAF, 5220
	.byte	"?", 0x18, 0x71, 0x66, 5233
	.byte	"?", 0x00, 0x4B, 0x23, 5374
	.byte	"?", 0x00, 0x68, 0x35, 5415
	.byte	"?", 0x5C, 0x9C, 0x51, 5531
	.byte	"?", 0x0E, 0x95, 0x43, 5613
	.byte	"?", 0x5E, 0x7A, 0x17, 5833
	.byte	"?", 0x22, 0x59, 0x26, 5944
	.byte	"?", 0xBC, 0xD6, 0x33, 6011
	.byte	"?", 0xBB, 0xCD, 0x91, 6051
	.byte	"?", 0x97, 0x8B, 0x3C, 6133
z102_isacord_polyester_end:


brand_codes:
	.long	arc_polyester_codes		; 0
	.long	arc_rayon_codes			; 1
	.long	coats_and_clark_rayon_codes	; 2
	.long	exquisite_polyester_codes	; 3
	.long	fufu_polyester_codes		; 4
	.long	fufu_rayon_codes		; 5
	.long	hemingworth_polyester_codes 	; 6
	.long	isacord_polyester_codes		; 7
	.long	isafil_rayon_codes		; 8
	.long	marathon_polyester_codes	; 9
	.long	marathon_rayon_codes		; 10
	.long	madeira_polyester_codes		; 11
	.long	madeira_rayon_codes		; 12
	.long	metro_polyester_codes		; 13
	.long	pantone_codes			; 14
	.long	robison_anton_polyester_codes	; 15
	.long	robison_anton_rayon_codes	; 16
	.long	sigma_polyester_codes		; 17
	.long	sulky_rayon_codes		; 18
	.long	.byte_art_rayon_codes		; 19
	.long	.byte_art_polyester_codes	; 20
	.long	.byteelight_polyester_codes	; 21
	.long	z102_isacord_polyester_codes	; 22
	.long	svg_color_codes			; 23
	.long	hus_.byte_table		; 24
	.long	jef_.byte_table		; 25
	.long	pcm_.byte_table		; 26
	.long	pec_.byte_table		; 27
	.long	shv_.byte_table		; 28
	.long	dxf_color_table			; 29
	.long	0


; Based on the DraftSight color table
dxf_color_table:
	.byte	"BYBLOCK", 0, 0, 0, 0
	.byte	"red", 255, 0, 0, 1
	.byte	"yellow", 255, 255, 0, 2
	.byte	"green", 0, 255, 0, 3
	.byte	"cyan", 0, 255, 255, 4
	.byte	"blue", 0, 0, 255, 5
	.byte	"magenta", 255, 0, 255, 6
	.byte	"white", 255, 255, 255, 7
	.byte	"dark gray", 128, 128, 128, 8
	.byte	"light gray", 192, 192, 192, 9
	.byte	"dxf10", 255, 0, 0, 10
	.byte	"dxf11", 255, 127, 127, 11
	.byte	"dxf12", 204, 0, 0, 12
	.byte	"dxf13", 204, 102, 102, 13
	.byte	"dxf", 153, 0, 0, 14
	.byte	"dxf", 153, 76, 76, 15
	.byte	"dxf", 127, 0, 0, 16
	.byte	"dxf", 127, 63, 63, 17
	.byte	"dxf", 76, 0, 0, 18
	.byte	"dxf", 76, 38, 38, 19
	.byte	"dxf", 255, 63, 0, 20
	.byte	"dxf", 255, 159, 127, 21
	.byte	"dxf", 204, 51, 0, 22
	.byte	"dxf", 204, 127, 102, 23
	.byte	"dxf", 153, 38, 0, 24
	.byte	"dxf", 153, 95, 76, 25
	.byte	"dxf", 127, 31, 0, 26
	.byte	"dxf", 127, 79, 63, 27
	.byte	"dxf", 76, 19, 0, 28
	.byte	"dxf", 76, 47, 38, 29
	.byte	"dxf", 255, 127, 0, 30
	.byte	"dxf", 255, 191, 127, 31
	.byte	"dxf", 204, 102, 0, 32
	.byte	"dxf", 204, 153, 102, 33
	.byte	"dxf", 153, 76, 0, 34
	.byte	"dxf", 153, 114, 76, 35
	.byte	"dxf", 127, 63, 0, 36
	.byte	"dxf", 127, 95, 63, 37
	.byte	"dxf", 76, 38, 0, 38
	.byte	"dxf", 76, 57, 38, 39
	.byte	"dxf", 255, 191, 0, 40
	.byte	"dxf", 255, 223, 127, 41
	.byte	"dxf", 204, 153, 0, 42
	.byte	"dxf", 204, 178, 102, 43
	.byte	"dxf", 153, 114, 0, 44
	.byte	"dxf", 153, 133, 76, 45
	.byte	"dxf", 127, 95, 0, 46
	.byte	"dxf", 127, 111, 63, 47
	.byte	"dxf", 76, 57, 0, 48
	.byte	"dxf", 76, 66, 38, 49
	.byte	"dxf", 255, 255, 0, 50
	.byte	"dxf", 255, 255, 127, 51
	.byte	"dxf", 204, 204, 0, 52
	.byte	"dxf", 204, 204, 102, 53
	.byte	"dxf", 153, 153, 0, 54
	.byte	"dxf", 153, 153, 76, 55
	.byte	"dxf", 127, 127, 0, 56
	.byte	"dxf", 127, 127, 63, 57
	.byte	"dxf", 76, 76, 0, 58
	.byte	"dxf", 76, 76, 38, 59
	.byte	"dxf", 191, 255, 0, 60
	.byte	"dxf", 223, 255, 127, 61
	.byte	"dxf", 153, 204, 0, 62
	.byte	"dxf", 178, 204, 102, 63
	.byte	"dxf", 114, 153, 0, 64
	.byte	"dxf", 133, 153, 76, 65
	.byte	"dxf", 95, 127, 0, 66
	.byte	"dxf", 111, 127, 63, 67
	.byte	"dxf", 57, 76, 0, 68
	.byte	"dxf", 66, 76, 38, 69
	.byte	"dxf", 127, 255, 0, 70
	.byte	"dxf", 191, 255, 127, 71
	.byte	"dxf", 102, 204, 0, 72
	.byte	"dxf", 153, 204, 102, 73
	.byte	"dxf", 76, 153, 0, 74
	.byte	"dxf", 114, 153, 76, 75
	.byte	"dxf", 63, 127, 0, 76
	.byte	"dxf", 95, 127, 63, 77
	.byte	"dxf", 38, 76, 0, 78
	.byte	"dxf", 57, 76, 38, 79
	.byte	"dxf", 63, 255, 0, 80
	.byte	"dxf", 159, 255, 127, 81
	.byte	"dxf", 51, 204, 0, 82
	.byte	"dxf", 127, 204, 102, 83
	.byte	"dxf", 38, 153, 0, 84
	.byte	"dxf", 95, 153, 76, 85
	.byte	"dxf", 31, 127, 0, 86
	.byte	"dxf", 79, 127, 63, 87
	.byte	"dxf", 19, 76, 0, 88
	.byte	"dxf", 47, 76, 38, 89
	.byte	"dxf", 0, 255, 0, 90
	.byte	"dxf", 127, 255, 127, 91
	.byte	"dxf", 0, 204, 0, 92
	.byte	"dxf", 102, 204, 102, 93
	.byte	"dxf", 0, 153, 0, 94
	.byte	"dxf", 76, 153, 76, 95
	.byte	"dxf", 0, 127, 0, 96
	.byte	"dxf", 63, 127, 63, 97
	.byte	"dxf", 0, 76, 0, 98
	.byte	"dxf", 38, 76, 38, 99
	.byte	"dxf", 0, 255, 63, 100
	.byte	"dxf", 127, 255, 159, 101
	.byte	"dxf", 0, 204, 51, 102
	.byte	"dxf", 102, 204, 127, 103
	.byte	"dxf", 0, 153, 38, 104
	.byte	"dxf", 76, 153, 95, 105
	.byte	"dxf", 0, 127, 31, 106
	.byte	"dxf", 63, 127, 79, 107
	.byte	"dxf", 0, 76, 19, 108
	.byte	"dxf", 38, 76, 47, 109
	.byte	"dxf", 0, 255, 127, 110
	.byte	"dxf", 127, 255, 191, 111
	.byte	"dxf", 0, 204, 102, 112
	.byte	"dxf", 102, 204, 153, 113
	.byte	"dxf", 0, 153, 76, 114
	.byte	"dxf", 76, 153, 114, 115
	.byte	"dxf", 0, 127, 63, 116
	.byte	"dxf", 63, 127, 95, 117
	.byte	"dxf", 0, 76, 38, 118
	.byte	"dxf", 38, 76, 57, 119
	.byte	"dxf", 0, 255, 191, 120
	.byte	"dxf", 127, 255, 223, 121
	.byte	"dxf", 0, 204, 153, 122
	.byte	"dxf", 102, 204, 178, 123
	.byte	"dxf", 0, 153, 114, 124
	.byte	"dxf", 76, 153, 133, 125
	.byte	"dxf", 0, 127, 95, 126
	.byte	"dxf", 63, 127, 111, 127
	.byte	"dxf", 0, 76, 57, 128
	.byte	"dxf", 38, 76, 66, 129
	.byte	"dxf", 0, 255, 255, 130
	.byte	"dxf", 127, 255, 255, 131
	.byte	"dxf", 0, 204, 204, 132
	.byte	"dxf", 102, 204, 204, 133
	.byte	"dxf", 0, 153, 153, 134
	.byte	"dxf", 76, 153, 153, 135
	.byte	"dxf", 0, 127, 127, 136
	.byte	"dxf", 63, 127, 127, 137
	.byte	"dxf", 0, 76, 76, 138
	.byte	"dxf", 38, 76, 76, 139
	.byte	"dxf", 0, 191, 255, 140
	.byte	"dxf", 127, 223, 255, 141
	.byte	"dxf", 0, 153, 204, 142
	.byte	"dxf", 102, 178, 204, 143
	.byte	"dxf", 0, 114, 153, 144
	.byte	"dxf", 76, 133, 153, 145
	.byte	"dxf", 0, 95, 127, 146
	.byte	"dxf", 63, 111, 127, 147
	.byte	"dxf", 0, 57, 76, 148
	.byte	"dxf", 38, 66, 76, 149
	.byte	"dxf", 0, 127, 255, 150
	.byte	"dxf", 127, 191, 255, 151
	.byte	"dxf", 0, 102, 204, 152
	.byte	"dxf", 102, 153, 204, 153
	.byte	"dxf", 0, 76, 153, 154
	.byte	"dxf", 76, 114, 153, 155
	.byte	"dxf", 0, 63, 127, 156
	.byte	"dxf", 63, 95, 127, 157
	.byte	"dxf", 0, 38, 76, 158
	.byte	"dxf", 38, 57, 76, 159
	.byte	"dxf", 0, 63, 255, 160
	.byte	"dxf", 127, 159, 255, 161
	.byte	"dxf", 0, 51, 204, 162
	.byte	"dxf", 102, 127, 204, 163
	.byte	"dxf", 0, 38, 153, 164
	.byte	"dxf", 76, 95, 153, 165
	.byte	"dxf", 0, 31, 127, 166
	.byte	"dxf", 63, 79, 127, 167
	.byte	"dxf", 0, 19, 76, 168
	.byte	"dxf", 38, 47, 76, 169
	.byte	"dxf", 0, 0, 255, 170
	.byte	"dxf", 127, 127, 255, 171
	.byte	"dxf", 0, 0, 204, 172
	.byte	"dxf", 102, 102, 204, 173
	.byte	"dxf", 0, 0, 153, 174
	.byte	"dxf", 76, 76, 153, 175
	.byte	"dxf", 0, 0, 127, 176
	.byte	"dxf", 63, 63, 127, 177
	.byte	"dxf", 0, 0, 76, 178
	.byte	"dxf", 38, 38, 76, 179
	.byte	"dxf", 63, 0, 255, 180
	.byte	"dxf", 159, 127, 255, 181
	.byte	"dxf", 51, 0, 204, 182
	.byte	"dxf", 127, 102, 204, 183
	.byte	"dxf", 38, 0, 153, 184
	.byte	"dxf", 95, 76, 153, 185
	.byte	"dxf", 31, 0, 127, 186
	.byte	"dxf", 79, 63, 127, 187
	.byte	"dxf", 19, 0, 76, 188
	.byte	"dxf", 47, 38, 76, 189
	.byte	"dxf", 127, 0, 255, 190
	.byte	"dxf", 191, 127, 255, 191
	.byte	"dxf", 102, 0, 204, 192
	.byte	"dxf", 153, 102, 204, 193
	.byte	"dxf", 76, 0, 153, 194
	.byte	"dxf", 114, 76, 153, 195
	.byte	"dxf", 63, 0, 127, 196
	.byte	"dxf", 95, 63, 127, 197
	.byte	"dxf", 38, 0, 76, 198
	.byte	"dxf", 57, 38, 76, 199
	.byte	"dxf", 191, 0, 255, 200
	.byte	"dxf", 223, 127, 255, 201
	.byte	"dxf", 153, 0, 204, 202
	.byte	"dxf", 178, 102, 204, 203
	.byte	"dxf", 114, 0, 153, 204
	.byte	"dxf", 133, 76, 153, 205
	.byte	"dxf", 95, 0, 127, 206
	.byte	"dxf", 111, 63, 127, 207
	.byte	"dxf", 57, 0, 76, 208
	.byte	"dxf", 66, 38, 76, 209
	.byte	"dxf", 255, 0, 255, 210
	.byte	"dxf", 255, 127, 255, 211
	.byte	"dxf", 204, 0, 204, 212
	.byte	"dxf", 204, 102, 204, 213
	.byte	"dxf", 153, 0, 153, 214
	.byte	"dxf", 153, 76, 153, 215
	.byte	"dxf", 127, 0, 127, 216
	.byte	"dxf", 127, 63, 127, 217
	.byte	"dxf", 76, 0, 76, 218
	.byte	"dxf", 76, 38, 76, 219
	.byte	"dxf", 255, 0, 191, 220
	.byte	"dxf", 255, 127, 223, 221
	.byte	"dxf", 204, 0, 153, 222
	.byte	"dxf", 204, 102, 178, 223
	.byte	"dxf", 153, 0, 114, 224
	.byte	"dxf", 153, 76, 133, 225
	.byte	"dxf", 127, 0, 95, 226
	.byte	"dxf", 127, 63, 111, 227
	.byte	"dxf", 76, 0, 57, 228
	.byte	"dxf", 76, 38, 66, 229
	.byte	"dxf", 255, 0, 127, 230
	.byte	"dxf", 255, 127, 191, 231
	.byte	"dxf", 204, 0, 102, 232
	.byte	"dxf", 204, 102, 153, 233
	.byte	"dxf", 153, 0, 76, 234
	.byte	"dxf", 153, 76, 114, 235
	.byte	"dxf", 127, 0, 63, 236
	.byte	"dxf", 127, 63, 95, 237
	.byte	"dxf", 76, 0, 38, 238
	.byte	"dxf", 76, 38, 57, 239
	.byte	"dxf", 255, 0, 63, 240
	.byte	"dxf", 255, 127, 159, 241
	.byte	"dxf", 204, 0, 51, 242
	.byte	"dxf", 204, 102, 127, 243
	.byte	"dxf", 153, 0, 38, 244
	.byte	"dxf", 153, 76, 95, 245
	.byte	"dxf", 127, 0, 31, 246
	.byte	"dxf", 127, 63, 79, 247
	.byte	"dxf", 76, 0, 19, 248
	.byte	"dxf", 76, 38, 47, 249
	.byte	"dxf", 51, 51, 51, 250
	.byte	"dxf", 91, 91, 91, 251
	.byte	"dxf", 132, 132, 132, 252
	.byte	"dxf", 173, 173, 173, 253
	.byte	"dxf254", 214, 214, 214, 254
	.byte	"dxf255", 255, 255, 255, 255
	.byte	"dxf256", 0, 0, 0, 256	; (BYLAYER)
dxf_color_end:

; TODO: HUS catalog numbers
hus_.byte_table:
	.byte	"Black", 0, 0, 0, 0
	.byte	"Blue", 0, 0, 255, 1
	.byte	"Light Green", 0, 255, 0, 2
	.byte	"Red", 255, 0, 0, 3
	.byte	"Purple", 255, 0, 255, 4
	.byte	"Yellow", 255, 255, 0, 5
	.byte	"Gray", 127, 127, 127, 6
	.byte	"Light Blue", 51, 154, 255, 7
	.byte	"Green", 51, 204, 102, 8
	.byte	"Orange", 255, 127, 0, 9
	.byte	"Pink", 255, 160, 180, 10
	.byte	"Brown", 153, 75, 0, 11
	.byte	"White", 255, 255, 255, 12
	.byte	"Dark Blue", 0, 0, 127, 13
	.byte	"Dark Green", 0, 127, 0, 14
	.byte	"Dark Red", 127, 0, 0, 15
	.byte	"Light Red", 255, 127, 127, 16
	.byte	"Dark Purple", 127, 0, 127, 17
	.byte	"Light Purple", 255, 127, 255, 18
	.byte	"Dark Yellow", 200, 200, 0, 19
	.byte	"Light Yellow", 255, 255, 153, 20
	.byte	"Dark Gray", 60, 60, 60, 21
	.byte	"Light Gray", 192, 192, 192, 22
	.byte	"Dark Orange", 232, 63, 0, 23
	.byte	"Light Orange", 255, 165, 65, 24
	.byte	"Dark Pink", 255, 102, 122, 25
	.byte	"Light Pink", 255, 204, 204, 26
	.byte	"Dark Brown", 115, 40, 0, 27
	.byte	"Light Brown", 175, 90, 10, 28
	.byte	"END", 0, 0, 0, 0
hus_.byte_end:


jef_.byte_table:
	.byte	"Black", 0, 0, 0, 0
	.byte	"Black", 0, 0, 0, 1
	.byte	"White", 255, 255, 255, 2
	.byte	"Yellow", 255, 255, 23, 3
	.byte	"Orange", 250, 160, 96, 4
	.byte	"Olive Green", 92, 118, 73, 5
	.byte	"Green", 64, 192, 48, 6
	.byte	"Sky", 101, 194, 200, 7
	.byte	"Purple", 172, 128, 190, 8
	.byte	"Pink", 245, 188, 203, 9
	.byte	"Red", 255, 0, 0, 10
	.byte	"Brown", 192, 128, 0, 11
	.byte	"Blue", 0, 0, 240, 12
	.byte	"Gold", 228, 195, 93, 13
	.byte	"Dark Brown", 165, 42, 42, 14
	.byte	"Pale Violet", 213, 176, 212, 15
	.byte	"Pale Yellow", 252, 242, 148, 16
	.byte	"Pale Pink", 240, 208, 192, 17
	.byte	"Peach", 255, 192, 0, 18
	.byte	"Beige", 201, 164, 128, 19
	.byte	"Wine Red", 155, 61, 75, 20
	.byte	"Pale Sky", 160, 184, 204, 21
	.byte	"Yellow Green", 127, 194, 28, 22
	.byte	"Silver Grey", 185, 185, 185, 23
	.byte	"Grey", 160, 160, 160, 24
	.byte	"Pale Aqua", 152, 214, 189, 25
	.byte	"Baby Blue", 184, 240, 240, 26
	.byte	"Powder Blue", 54, 139, 160, 27
	.byte	"Bright Blue", 79, 131, 171, 28
	.byte	"Slate Blue", 56, 106, 145, 29
	.byte	"Nave Blue", 0, 32, 107, 30
	.byte	"Salmon Pink", 229, 197, 202, 31
	.byte	"Coral", 249, 103, 107, 32
	.byte	"Burnt Orange", 227, 49, 31, 33
	.byte	"Cinnamon", 226, 161, 136, 34
	.byte	"Umber", 181, 148, 116, 35
	.byte	"Blonde", 228, 207, 153, 36
	.byte	"Sunflower", 225, 203, 0, 37
	.byte	"Orchid Pink", 225, 173, 212, 38
	.byte	"Peony Purple", 195, 0, 126, 39
	.byte	"Burgundy", 128, 0, 75, 40
	.byte	"Royal Purple", 160, 96, 176, 41
	.byte	"Cardinal Red", 192, 64, 32, 42
	.byte	"Opal Green", 202, 224, 192, 43
	.byte	"Moss Green", 137, 152, 86, 44
	.byte	"Meadow Green", 0, 170, 0, 45
	.byte	"Dark Green", 33, 138, 33, 46
	.byte	"Aquamarine", 93, 174, 148, 47
	.byte	"Emerald Green", 76, 191, 143, 48
	.byte	"Peacock Green", 0, 119, 114, 49
	.byte	"Dark Grey", 112, 112, 112, 50
	.byte	"Ivory White", 242, 255, 255, 51
	.byte	"Hazel", 177, 88, 24, 52
	.byte	"Toast", 203, 138, 7, 53
	.byte	"Salmon", 247, 146, 123, 54
	.byte	"Cocoa Brown", 152, 105, 45, 55
	.byte	"Sienna", 162, 113, 72, 56
	.byte	"Sepia", 123, 85, 74, 57
	.byte	"Dark Sepia", 79, 57, 70, 58
	.byte	"Violet Blue", 82, 58, 151, 59
	.byte	"Blue Ink", 0, 0, 160, 60
	.byte	"Solar Blue", 0, 150, 222, 61
	.byte	"Green Dust", 178, 221, 83, 62
	.byte	"Crimson", 250, 143, 187, 63
	.byte	"Floral Pink", 222, 100, 158, 64
	.byte	"Wine", 181, 80, 102, 65
	.byte	"Olive Drab", 94, 87, 71, 66
	.byte	"Meadow", 76, 136, 31, 67
	.byte	"Mustard", 228, 220, 121, 68
	.byte	"Yellow Ochre", 203, 138, 26, 69
	.byte	"Old Gold", 198, 170, 66, 70
	.byte	"Honeydew", 236, 176, 44, 71
	.byte	"Tangerine", 248, 128, 64, 72
	.byte	"Canary Yellow", 255, 229, 5, 73
	.byte	"Vermillion", 250, 122, 122, 74
	.byte	"Bright Green", 107, 224, 0, 75
	.byte	"Ocean Blue", 56, 108, 174, 76
	.byte	"Beige Grey", 227, 196, 180, 77
	.byte	"Bamboo", 227, 172, 129, 78
jef_.byte_end:


pcm_.byte_table:
	.byte	"PCM Color 1", 0x00, 0x00, 0x00, 1
	.byte	"PCM Color 2", 0x00, 0x00, 0x80, 2
	.byte	"PCM Color 3", 0x00, 0x00, 0xFF, 3
	.byte	"PCM Color 4", 0x00, 0x80, 0x80, 4
	.byte	"PCM Color 5", 0x00, 0xFF, 0xFF, 5
	.byte	"PCM Color 6", 0x80, 0x00, 0x80, 6
	.byte	"PCM Color 7", 0xFF, 0x00, 0xFF, 7
	.byte	"PCM Color 8", 0x80, 0x00, 0x00, 8
	.byte	"PCM Color 9", 0xFF, 0x00, 0x00, 9
	.byte	"PCM Color 10", 0x00, 0x80, 0x00, 10
	.byte	"PCM Color 11", 0x00, 0xFF, 0x00, 11
	.byte	"PCM Color 12", 0x80, 0x80, 0x00, 12
	.byte	"PCM Color 13", 0xFF, 0xFF, 0x00, 13
	.byte	"PCM Color 14", 0x80, 0x80, 0x80, 14
	.byte	"PCM Color 15", 0xC0, 0xC0, 0xC0, 15
	.byte	"PCM Color 16", 0xFF, 0xFF, 0xFF, 16
pcm_.byte_end:


pec_.byte_table:
	.byte	"Unknown", 0, 0, 0, 0
	.byte	"Prussian Blue", 14, 31, 124, 1
	.byte	"Blue", 10, 85, 163, 2
	.byte	"Teal Green", 0, 135, 119, 3		; TODO: Verify RGB value is correct
	.byte	"Cornflower Blue", 75, 107, 175, 4
	.byte	"Red", 237, 23, 31, 5
	.byte	"Reddish Brown", 209, 92, 0, 6
	.byte	"Magenta", 145, 54, 151, 7
	.byte	"Light Lilac", 228, 154, 203, 8
	.byte	"Lilac", 145, 95, 172, 9
	.byte	"Mint Green", 158, 214, 125, 10		; TODO: Verify RGB value is correct.
	.byte	"Deep Gold", 232, 169, 0, 11
	.byte	"Orange", 254, 186, 53, 12
	.byte	"Yellow", 255, 255, 0, 13
	.byte	"Lime Green", 112, 188, 31, 14
	.byte	"Brass", 186, 152, 0, 15
	.byte	"Silver", 168, 168, 168, 16
	.byte	"Russet Brown", 125, 111, 0, 17		; TODO: Verify RGB value is correct.
	.byte	"Cream Brown", 255, 255, 179, 18
	.byte	"Pewter", 79, 85, 86, 19
	.byte	"Black", 0, 0, 0, 20
	.byte	"Ultramarine", 11, 61, 145, 21
	.byte	"Royal Purple", 119, 1, 118, 22
	.byte	"Dark Gray", 41, 49, 51, 23
	.byte	"Dark Brown", 42, 19, 1, 24
	.byte	"Deep Rose", 246, 74, 138, 25
	.byte	"Light Brown", 178, 118, 36, 26
	.byte	"Salmon Pink", 252, 187, 197, 27	; TODO: Verify RGB value is correct.
	.byte	"Vermillion", 254, 55, 15, 28
	.byte	"White", 240, 240, 240, 29
	.byte	"Violet", 106, 28, 138, 30
	.byte	"Seacrest", 168, 221, 196, 31
	.byte	"Sky Blue", 37, 132, 187, 32
	.byte	"Pumpkin", 254, 179, 67, 33
	.byte	"Cream Yellow", 255, 243, 107, 34
	.byte	"Khaki", 208, 166, 96, 35
	.byte	"Clay Brown", 209, 84, 0, 36
	.byte	"Leaf Green", 102, 186, 73, 37
	.byte	"Peacock Blue", 19, 74, 70, 38
	.byte	"Gray", 135, 135, 135, 39
	.byte	"Warm Gray", 216, 204, 198, 40		; TODO: Verify RGB value is correct.
	.byte	"Dark Olive", 67, 86, 7, 41
	.byte	"Flesh Pink", 253, 217, 222, 42		; TODO: Verify RGB value is correct.
	.byte	"Pink", 249, 147, 188, 43
	.byte	"Deep Green", 0, 56, 34, 44
	.byte	"Lavender", 178, 175, 212, 45
	.byte	"Wisteria Violet", 104, 106, 176, 46
	.byte	"Beige", 239, 227, 185, 47
	.byte	"Carmine", 247, 56, 102, 48
	.byte	"Amber Red", 181, 75, 100, 49		; TODO: Verify RGB value is correct.
	.byte	"Olive Green", 19, 43, 26, 50
	.byte	"Dark Fuschia", 199, 1, 86, 51		; TODO: Verify RGB value is correct.
	.byte	"Tangerine", 254, 158, 50, 52
	.byte	"Light Blue", 168, 222, 235, 53
	.byte	"Emerald Green", 0, 103, 62, 54		; TODO: Verify RGB value is correct.
	.byte	"Purple", 78, 41, 144, 55
	.byte	"Moss Green", 47, 126, 32, 56
	.byte	"Flesh Pink", 255, 204, 204, 57		; TODO: Verify RGB value is correct.
							; TODO: Flesh Pink is Index 42, is this Index incorrect?
	.byte	"Harvest Gold", 255, 217, 17, 58
	.byte	"Electric Blue", 9, 91, 166, 59
	.byte	"Lemon Yellow", 240, 249, 112, 60
	.byte	"Fresh Green", 227, 243, 91, 61
	.byte	"Orange", 255, 153, 0, 62		; TODO: Verify RGB value is correct.
							; TODO: Orange is Index 12, is this Index incorrect?
	.byte	"Cream Yellow", 255, 240, 141, 63	; TODO: Verify RGB value is correct.
							; TODO: Cream Yellow is Index 34, is this Index incorrect?
	.byte	"Applique", 255, 200, 200, 64
pec_.byte_end:


; SHV Colors
; TODO: catalog numbers

shv_.byte_table:
	.byte	"Black", 0, 0, 0, 0
	.byte	"Blue", 0, 0, 255, 1
	.byte	"Green", 51, 204, 102, 2
	.byte	"Red", 255, 0, 0, 3
	.byte	"Purple", 255, 0, 255, 4
	.byte	"Yellow", 255, 255, 0, 5
	.byte	"Grey", 127, 127, 127, 6
	.byte	"Light Blue", 51, 154, 255, 7
	.byte	"Light Green", 0, 255, 0, 8
	.byte	"Orange", 255, 127, 0, 9
	.byte	"Pink", 255, 160, 180, 10
	.byte	"Brown", 153, 75, 0, 11
	.byte	"White", 255, 255, 255, 12
	.byte	"Black", 0, 0, 0, 13
	.byte	"Black", 0, 0, 0, 14
	.byte	"Black", 0, 0, 0, 15
	.byte	"Black", 0, 0, 0, 16
	.byte	"Black", 0, 0, 0, 17
	.byte	"Black", 0, 0, 0, 18
	.byte	"Light Red", 255, 127, 127, 19
	.byte	"Light Purple", 255, 127, 255, 20
	.byte	"Light Yellow", 255, 255, 153, 21
	.byte	"Light Grey", 192, 192, 192, 22
	.byte	"Black", 0, 0, 0, 23
	.byte	"Black", 0, 0, 0, 24
	.byte	"Light Orange", 255, 165, 65, 25
	.byte	"Light Pink", 255, 204, 204, 26
	.byte	"Light Brown", 175, 90, 10, 27
	.byte	"Black", 0, 0, 0, 28
	.byte	"Black", 0, 0, 0,29
	.byte	"Black", 0, 0, 0, 30
	.byte	"Black", 0, 0, 0, 31
	.byte	"Black", 0, 0, 0, 32
	.byte	"Dark Blue", 0, 0, 127, 33
	.byte	"Dark Green", 0, 127, 0, 34
	.byte	"Dark Red", 127, 0, 0, 35
	.byte	"Dark Purple", 127, 0, 127, 36
	.byte	"Dark Yellow", 200, 200, 0, 37
	.byte	"Dark Gray", 60, 60, 60, 38
	.byte	"Black", 0, 0, 0, 39
	.byte	"Black", 0, 0, 0, 40
	.byte	"Dark Orange", 232, 63, 0, 41
	.byte	"Dark Pink", 255, 102, 122, 42
shv_.byte_end:

dxf_version_r:
	.long	DXF_VERSION_R10
	.long	DXF_VERSION_R11
	.long	DXF_VERSION_R12
	.long	DXF_VERSION_R13
	.long	DXF_VERSION_R14
	.long	DXF_VERSION_R15
	.long	DXF_VERSION_R18
	.long	DXF_VERSION_R21
	.long	DXF_VERSION_R24
	.long	DXF_VERSION_R27


dxf_version_year:
	.long	DXF_VERSION_2000
	.long	DXF_VERSION_2002
	.long	DXF_VERSION_2004
	.long	DXF_VERSION_2006
	.long	DXF_VERSION_2007
	.long	DXF_VERSION_2009
	.long	DXF_VERSION_2010
	.long	DXF_VERSION_2013
	.long	0

/*
;-------------------------------------------------------------------------------
;	String table
;-------------------------------------------------------------------------------
 */

DXF_VERSION_R10:
	.string	"AC1006"
DXF_VERSION_R11:
	.long	"AC1009"
DXF_VERSION_R12:
	.long	"AC1009"
DXF_VERSION_R13:
	.long	"AC1012"
DXF_VERSION_R14:
	.long	"AC1014"
DXF_VERSION_R15:
	.long	"AC1015"
DXF_VERSION_R18:
	.long	"AC1018"
DXF_VERSION_R21:
	.long	"AC1021"
DXF_VERSION_R24:
	.long	"AC1024"
DXF_VERSION_R27:
	.long	"AC1027"

DXF_VERSION_2000:
	.string	"AC1015"
DXF_VERSION_2002:
	.string	"AC1015"
DXF_VERSION_2004:
	.string	"AC1018"
DXF_VERSION_2006:
	.string	"AC1018"
DXF_VERSION_2007:
	.string	"AC1021"
DXF_VERSION_2009:
	.string	"AC1021"
DXF_VERSION_2010:
	.string	"AC1024"
DXF_VERSION_2013:
	.string	"AC1027"

audio_level_token:
	.string	"audio-level"
buffered_rendering_token:
	.string	"buffered-rendering"
color_token:
	.string	"color"
color_rendering_token:
	.string	"color-rendering"
direction_token:
	.string	"direction"
display_token:
	.string	"display"
display_align_token:
	.string	"display-align"
fill_token:
	.string	"fill"
fill_opacity_token:
	.string	"fill-opacity"
fill_rule_token:
	.string	"fill-rule"
font_family_token:
	.string	"font-family"
font_size_token:
	.string	"font-size"
font_style_token:
	.string	"font-style"
font_variant_token:
	.string	"font-variant"
font_weight_token:
	.string	"font-weight"
image_rendering_token:
	.string	"image-rendering"
line_increment_token:
	.string	"line-increment"
opacity_token:
	.string	"opacity"
pointer_events_token:
	.string	"pointer-events"
shape_rendering_token:
	.string	"shape-rendering"
solid_color_token:
	.string	"solid-color"
solid_opacity_token:
	.string	"solid-opacity"
stop_color_token:
	.string	"stop-color"
stop_opacity_token:
	.string	"stop-opacity"
stroke_token:
	.string	"stroke"
stroke_dasharray_token:
	.string	"stroke-dasharray"
stroke_linecap_token:
	.string	"stroke-linecap"
stroke_linejoin_token:
	.string	"stroke-linejoin"
stroke_miterlimit_token:
	.string	"stroke-miterlimit"
stroke_opacity_token:
	.string	"stroke-opacity"
stroke_width_token:
	.string	"stroke-width"
text_align_token:
	.string	"text-align"
text_anchor_token:
	.string	"text-anchor"
text_rendering_token:
	.string	"text-rendering"
unicode_bidi_token:
	.string	"unicode-bidi"
vector_effect_token:
	.string	"vector-effect"
viewport_fill_token:
	.string	"viewport-fill"
viewport_fill_opacity_token:
	.string	"viewport-fill-opacity"
visibility_token:
	.string	"visibility"
about_token:
	.string	"about"
accent_height_token:
	.string	"accent-height"
accumulate_token:
	.string	"accumulate"
additive_token:
	.string	"additive"
alphabetic_token:
	.string	"alphabetic"
arabic_form_token:
	.string	"arabic-form"
ascent_token:
	.string	"ascent"
attribute_name_token:
	.string	"attributeName"
attribute_type_token:
	.string	"attributeType"
bandwidth_token:
	.string	"bandwidth"
base_profile_token:
	.string	"baseProfile"
bbox_token:
	.string	"bbox"
begin_token:
	.string	"begin"
by_token:
	.string	"by"
calc_mode_token:
	.string	"calcMode"
cap_height_token:
	.string	"cap-height"
class_token:
	.string	"class"
content_token:
	.string	"content"
content_script_type_token:
	.string	"contentScriptType"
cx_token:
	.string	"cx"
cy_token:
	.string	"cy"
d_token:
	.string	"d"
datatype_token:
	.string	"datatype"
default_action_token:
	.string	"defaultAction"
descent_token:
	.string	"descent"
dur_token:
	.string	"dur"
editable_token:
	.string	"editable"
end_token:
	.string	"end"
ev_event_token:
	.string	"ev:event"
event_token:
	.string	"event"
external_resources_required_token:
	.string	"externalResourcesRequired"
focus_highlight_token:
	.string	"focusHighlight"
focusable_token:
	.string	"focusable"
font_stretch_token:
	.string	"font-stretch"
from_token:
	.string	"from"
g1_token:
	.string	"g1"
g2_token:
	.string	"g2"
glyph_name_token:
	.string	"glyph-name"
gradient_units_token:
	.string	"gradientUnits"
handler_token:
	.string	"handler"
hanging_token:
	.string	"hanging"
height_token:
	.string	"height"
horiz_adv_x_token:
	.string	"horiz-adv-x"
horiz_origin_x_token:
	.string	"horiz-origin-x"
id_token:
	.string	"id"
ideographic_token:
	.string	"ideographic"
initial_visibility_token:
	.string	"initialVisibility"
k_token:
	.string	"k"
key_points_token:
	.string	"keyPoints"
key_splines_token:
	.string	"keySplines"
key_times_token:
	.string	"keyTimes"
lang_token:
	.string	"lang"
mathematical_token:
	.string	"mathematical"
max_token:
	.string	"max"
media_character_encoding_token:
	.string	"mediaCharacterEncoding"
media_content_encoding_token:
	.string	"mediaContentEncodings"
media_size_token:
	.string	"mediaSize"
media_time_token:
	.string	"mediaTime"
min_token:
	.string	"min"
nav_down_token:
	.string	"nav-down"
nav_down_left_token:
	.string	"nav-down-left"
nav_down_right_token:
	.string	"nav-down-right"
nav_left_token:
	.string	"nav-left"
nav_next_token:
	.string	"nav-next"
nav_prev_token:
	.string	"nav-prev"
nav_right_token:
	.string	"nav-right"
nav_up_token:
	.string	"nav-up"
nav_up_left_token:
	.string	"nav-up-left"
nav_up_right_token:
	.string	"nav-up-right"
observer_token:
	.string	"observer"
offset_token:
	.string	"offset"
origin_token:
	.string	"origin"
overlay_token:
	.string	"overlay"
overline_position_token:
	.string	"overline-position"
overline_thickness_token:
	.string	"overline-thickness"
panose_1_token:
	.string	"panose-1"
path_token:
	.string	"path"
path_length_token:
	.string	"pathLength"
phase_token:
	.string	"phase"
playback_order_token:
	.string	"playbackOrder"
points_token:
	.string	"points"
preserve_aspect_ratio_token:
	.string	"preserveAspectRatio"
propagate_token:
	.string	"propagate"
property_token:
	.string	"property"
r_token:
	.string	"r"
rel_token:
	.string	"rel"
repeat_count_token:
	.string	"repeatCount"
repeat_dur_token:
	.string	"repeatDur"
required_extensions_token:
	.string	"requiredExtensions"
required_features_token:
	.string	"requiredFeatures"
required_fonts_token:
	.string	"requiredFonts"
required_formats_token:
	.string	"requiredFormats"
resource_token:
	.string	"resource"
restart_token:
	.string	"restart"
rev_token:
	.string	"rev"
role_token:
	.string	"role"
rotate_token:
	.string	"rotate"
rx_token:
	.string	"rx"
ry_token:
	.string	"ry"
slope_token:
	.string	"slope"
snapshot_time_token:
	.string	"snapshotTime"
stemh_token:
	.string	"stemh"
stemv_token:
	.string	"stemv"
strikethrough_position_token:
	.string	"strikethrough-position"
strikethrough_thickness_token:
	.string	"strikethrough-thickness"
sync_behavior_token:
	.string	"syncBehavior"
sync_behavior_default_token:
	.string	"syncBehaviorDefault"
sync_master_token:
	.string	"syncMaster"
sync_tolerance_token:
	.string	"syncTolerance"
sync_tolerance_default_token:
	.string	"syncToleranceDefault"
system_language_token:
	.string	"systemLanguage"
target_token:
	.string	"target"
timeline_begin_token:
	.string	"timelineBegin"
to_token:
	.string	"to"
transform_token:
	.string	"transform"
transform_behavior_token:
	.string	"transformBehavior"
type_token:
	.string	"type"
typeof_token:
	.string	"typeof"
u1_token:
	.string	"u1"
u2_token:
	.string	"u2"
underline_position_token:
	.string	"underline-position"
underline_thickness_token:
	.string	"underline-thickness"
unicode_token:
	.string	"unicode"
unicode_range_token:
	.string	"unicode-range"
units_per_em_token:
	.string	"units-per-em"
values_token:
	.string	"values"
version_token:
	.string	"version"
viewbox_token:
	.string	"viewBox"
width_token:
	.string	"width"
widths_token:
	.string	"widths"
x_token:
	.string	"x"
x_height_token:
	.string	"x-height"
x1_token:
	.string	"x1"
x2_token:
	.string	"x2"
xlink_actuate_token:
	.string	"xlink:actuate"
xlink_arcrole_token:
	.string	"xlink:arcrole",
xlink_href_token:
	.string	"xlink:href"
xlink_role_token:
	.string	"xlink:role"
xlink_show_token:
	.string	"xlink:show"
xlink_title_token:
	.string	"xlink:title"
xlink_type_token:
	.string	"xlink:type",
xml_base_token:
	.string	"xml:base"
xml_id_token:
	.string	"xml:id"
xml_lang_token:
	.string	"xml:lang"
xml_space_token:
	.string	"xml:space"
y_token:
	.string	"y"
y1_token:
	.string	"y1"
y2_token:
	.string	"y2"
zoom_and_pan_token:
	.string	"zoomAndPan"
slash_token:
	.string	"/"

; svg elements
xml_token:
	.string	"?xml"
a_token:
	.string	"a"
animate_token:
	.string	"animate"
animate_color_token:
	.string	"animateColor"
animate_motion_token:
	.string	"animateMotion"
animate_transform_token:
	.string	"animateTransform"
animation_token:
	.string	"animation"
audio_token:
	.string	"audio"
circle_token:
	.string	"circle"
defs_token:
	.string	"defs"
desc_token:
	.string	"desc"
discard_token:
	.string	"discard"
ellipse_token:
	.string	"ellipse"
font_token:
	.string	"font"
font_face_token:
	.string	"fontFace"
font_face_src_token:
	.string	"fontFaceSrc"
font_face_uri_token:
	.string	"fontFaceUri"
foreign_object_token:
	.string	"foreign"
g_token:
	.string	"g"
glyph_token:
	.string	"glyph"
hkern_token:
	.string	"hkern"
image_token:
	.string	"image"
line_token:
	.string	"line"
linear_gradient_token:
	.string	"linearGradient"
listener_token:
	.string	"listener"
metadata_token:
	.string	"metadata"
missing_glyph_token:
	.string	"missingGlyph"
mpath_token:
	.string	"mpath"
polygon_token:
	.string	"polygon"
polyline_token:
	.string	"polyline"
prefetch_token:
	.string	"prefetch"
radial_gradient_token:
	.string	"radialGradient"
rect_token:
	.string	"rect"
script_token:
	.string	"script"
set_token:
	.string	"set"
stop_token:
	.string	"stop"
svg_token:
	.string	"svg"
switch_token:
	.string	"switch"
tbreak_token:
	.string	"tbreak"
text_token:
	.string	"text"
text_area_token:
	.string	"textArea"
title_token:
	.string	"title"
tspan_token:
	.string	"tspan"
use_token:
	.string	"use"
video_token:
	.string	"video"

encoding_token:
	.string	"encoding"
standalone_token:
	.string	"standalone"
xmlns_token:
	.string	"xmlns"
xmlns_svg_token:
	.string	"xmlns:svg"
xmlns_rdf_token:
	.string	"xmlns:rdf"
xmlns_dc_token:
	.string	"xmlns:dc"
xmlns_cc_token:
	.string	"xmlns:cc"
#endif
