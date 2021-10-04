; Assemble:
; $ nasm -f bin -l libembroidery_data.lst -o libembroidery_data.o libembroidery_data.asm
;
; Testing program (run on little-endian machine):
; $ gcc test.c
; $ ./a.out

	dd	svg_property_token_table
	dd	svg_attribute_token_table
	dd	svg_token_lists
;	dd	brand_codes
;	dd	image_frame
;	dd	format_list
	dd	0

svg_property_token_table:
	dd	audio_level_token
	dd	buffered_rendering_token
	dd	color_token
	dd	color_rendering_token
	dd	direction_token
	dd	display_token
	dd	display_align_token
	dd	fill_token
	dd	fill_opacity_token
	dd	fill_rule_token
	dd	font_family_token
	dd	font_size_token
	dd	font_style_token
	dd	font_variant_token
	dd	font_weight_token
	dd	image_rendering_token
	dd	line_increment_token
	dd	opacity_token
	dd	pointer_events_token
	dd	shape_rendering_token
	dd	solid_color_token
	dd	solid_opacity_token
	dd	stop_color_token
	dd	stop_opacity_token
	dd	stroke_token
	dd	stroke_dasharray_token
	dd	stroke_linecap_token
	dd	stroke_linejoin_token
	dd	stroke_miterlimit_token
	dd	stroke_opacity_token
	dd	stroke_width_token
	dd	text_align_token
	dd	text_anchor_token
	dd	text_rendering_token
	dd	unicode_bidi_token
	dd	vector_effect_token
	dd	viewport_fill_token
	dd	viewport_fill_opacity_token
	dd	visibility_token
	dd	0


svg_attribute_token_table:
	dd	about_token
	dd	accent_height_token
	dd	accumulate_token
	dd	additive_token
	dd	alphabetic_token
	dd	arabic_form_token
	dd	ascent_token
	dd	attribute_name_token
	dd	attribute_type_token
	dd	bandwidth_token
	dd	base_profile_token
	dd	bbox_token
	dd	begin_token
	dd	by_token
	dd	calc_mode_token
	dd	cap_height_token
	dd	class_token
	dd	content_token
	dd	content_script_type_token
	dd	cx_token
	dd	cy_token
	dd	d_token
	dd	datatype_token
	dd	default_action_token
	dd	descent_token
	dd	dur_token
	dd	editable_token
	dd	end_token
	dd	ev_event_token
	dd	event_token
	dd	external_resources_required_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	font_family_token
	dd	font_stretch_token
	dd	font_style_token
	dd	font_variant_token
	dd	font_weight_token
	dd	from_token
	dd	g1_token
	dd	g2_token
	dd	glyph_name_token
	dd	gradient_units_token
	dd	handler_token
	dd	hanging_token
	dd	height_token
	dd	horiz_adv_x_token
	dd	horiz_origin_x_token
	dd	id_token
	dd	ideographic_token
	dd	initial_visibility_token
	dd	k_token
	dd	key_points_token
	dd	key_splines_token
	dd	key_times_token
	dd	lang_token
	dd	mathematical_token
	dd	max_token
	dd	media_character_encoding_token
	dd	media_content_encoding_token
	dd	media_size_token
	dd	media_time_token
	dd	min_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	observer_token
	dd	offset_token
	dd	origin_token
	dd	overlay_token
	dd	overline_position_token
	dd	overline_thickness_token
	dd	panose_1_token
	dd	path_token
	dd	path_length_token
	dd	phase_token
	dd	playback_order_token
	dd	points_token
	dd	preserve_aspect_ratio_token
	dd	propagate_token
	dd	property_token
	dd	r_token
	dd	rel_token
	dd	repeat_count_token
	dd	repeat_dur_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	restart_token
	dd	rev_token
	dd	role_token
	dd	rotate_token
	dd	rx_token
	dd	ry_token
	dd	slope_token
	dd	snapshot_time_token
	dd	stemh_token
	dd	stemv_token
	dd	strikethrough_position_token
	dd	strikethrough_thickness_token
	dd	sync_behavior_token
	dd	sync_behavior_default_token
	dd	sync_master_token
	dd	sync_tolerance_token
	dd	sync_tolerance_default_token
	dd	system_language_token
	dd	target_token
	dd	timeline_begin_token
	dd	to_token
	dd	transform_token
	dd	transform_behavior_token
	dd	type_token
	dd	typeof_token
	dd	u1_token
	dd	u2_token
	dd	underline_position_token
	dd	underline_thickness_token
	dd	unicode_token
	dd	unicode_range_token
	dd	units_per_em_token
	dd	values_token
	dd	version_token
	dd	viewbox_token
	dd	width_token
	dd	widths_token
	dd	x_token
	dd	x_height_token
	dd	x1_token
	dd	x2_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	dd	xlink_role_token
	dd	xlink_show_token
	dd	xlink_title_token
	dd	xlink_type_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	y_token
	dd	y1_token
	dd	y2_token
	dd	zoom_and_pan_token
	dd	slash_token
	dd	0


solid_color_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	id_token
	dd	property_token
	dd	rel_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0

stop_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	id_token
	dd	offset_token
	dd	property_token
	dd	rel_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0

svg_token_table:
	dd	about_token
	dd	base_profile_token
	dd	class_token
	dd	content_token
	dd	content_script_type_token
	dd	datatype_token
	dd	external_resources_required_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	height_token
	dd	id_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	playback_order_token
	dd	preserve_aspect_ratio_token
	dd	property_token
	dd	rel_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	snapshot_time_token
	dd	sync_behavior_default_token
	dd	sync_tolerance_default_token
	dd	timeline_begin_token
	dd	typeof_token
	dd	version_token
	dd	viewbox_token
	dd	width_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	zoom_and_pan_token
	dd	slash_token
	dd	0


inkscape_token_table:
	dd	xmlns_dc_token
	dd	xmlns_cc_token
	dd	xmlns_rdf_token
	dd	xmlns_svg_token
	dd	xmlns_token
	dd	0


svg_element_token_table:
	dd	xml_token
	dd	a_token
	dd	animate_token
	dd	animate_color_token
	dd	animate_motion_token
	dd	animate_transform_token
	dd	animation_token
	dd	audio_token
	dd	circle_token
	dd	defs_token
	dd	desc_token
	dd	discard_token
	dd	ellipse_token
	dd	font_token
	dd	font_face_token
	dd	font_face_src_token
	dd	font_face_uri_token
	dd	foreign_object_token
	dd	g_token
	dd	glyph_token
	dd	handler_token
	dd	hkern_token
	dd	image_token
	dd	line_token
	dd	linear_gradient_token
	dd	listener_token
	dd	metadata_token
	dd	missing_glyph_token
	dd	mpath_token
	dd	path_token
	dd	polygon_token
	dd	polyline_token
	dd	prefetch_token
	dd	radial_gradient_token
	dd	rect_token
	dd	script_token
	dd	set_token
	dd	solid_color_token
	dd	stop_token
	dd	svg_token
	dd	switch_token
	dd	tbreak_token
	dd	text_token
	dd	text_area_token
	dd	title_token
	dd	tspan_token
	dd	use_token
	dd	video_token
	dd	0

;	_tODO: not implemented _sVG _full 1.1 _spec _elements
%if 0
not_implemented_svg_tokens:
	dd	alt_glyph_token
	dd	alt_glyph_def_token
	dd	altGlyphItem_token
	dd	clip_path_token
	dd	color_profile_token
	dd	cursor_token
	dd	feBlend_token
	dd	fe_colorMatrix_token
	dd	fe_component_transfer_token
	dd	fe_composite_token
	dd	fe_convolveMatrix_token
	dd	feDiffuse_lighting_token
	dd	feDisplacementMap_token
	dd	feDistant_light_token
	dd	fe_flood_token
	dd	fe_funcA_token
	dd	fe_funcB_token
	dd	fe_funcG_token
	dd	fe_funcR_token
	dd	feGaussianBlur_token
	dd	feImage_token
	dd	feMerge_token
	dd	feMergeNode_token
	dd	feMorphology_token
	dd	feOffset_token
	dd	fe_point_light_token
	dd	fe_specular_lighting_token
	dd	fe_spot_light_token
	dd	fe_tile_token
	dd	fe_turbulence_token
	dd	filter
	dd	font_face_format_token
	dd	font_face_name_token
	dd	glyphRef_token
	dd	marker_token
	dd	mask_token
	dd	pattern_token
	dd	style_token
	dd	symbol_token
	dd	text_path_token
	dd	tref_token
	dd	view_token
	dd	vkern_token
	dd	0
%endif


svg_media_property_token_table:
	dd	audio_level_token
	dd	buffered_rendering_token
	dd	display_token
	dd	image_rendering_token
	dd	pointer_events_token
	dd	shape_rendering_token
	dd	text_rendering_token
	dd	viewport_fill_token
	dd	viewport_fill_opacity_token
	dd	visibility_token
	dd	0


xml_token_table:
	dd	encoding_token
	dd	standalone_token
	dd	version_token
	dd	slash_token
	dd	0


link_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	external_resources_required_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	id_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	target_token
	dd	transform_token
	dd	typeof_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	dd	xlink_role_token
	dd	xlink_show_token
	dd	xlink_title_token
	dd	xlink_type_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


animate_token_table:
	dd	about_token
	dd	accumulate_token
	dd	additive_token
	dd	attribute_name_token
	dd	attribute_type_token
	dd	begin_token
	dd	by_token
	dd	calc_mode_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	dur_token
	dd	end_token
	dd	fill_token
	dd	from_token
	dd	id_token
	dd	key_splines_token
	dd	key_times_token
	dd	max_token
	dd	min_token
	dd	property_token
	dd	rel_token
	dd	repeat_count_token
	dd	repeat_dur_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	restart_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	to_token
	dd	typeof_token
	dd	values_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	dd	xlink_role_token
	dd	xlink_show_token
	dd	xlink_title_token
	dd	xlink_type_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


animate_color_token_table:
	dd	about_token
	dd	accumulate_token
	dd	additive_token
	dd	attribute_name_token
	dd	attribute_type_token
	dd	begin_token
	dd	by_token
	dd	calc_mode_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	dur_token
	dd	end_token
	dd	fill_token
	dd	from_token
	dd	id_token
	dd	key_splines_token
	dd	key_times_token
	dd	max_token
	dd	min_token
	dd	property_token
	dd	rel_token
	dd	repeat_count_token
	dd	repeat_dur_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	restart_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	to_token
	dd	typeof_token
	dd	values_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	dd	xlink_role_token
	dd	xlink_show_token
	dd	xlink_title_token
	dd	xlink_type_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


animate_motion_token_table:
	dd	about_token
	dd	accumulate_token
	dd	additive_token
	dd	begin_token
	dd	by_token
	dd	calc_mode_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	dur_token
	dd	end_token
	dd	fill_token
	dd	from_token
	dd	id_token
	dd	key_points_token
	dd	key_splines_token
	dd	key_times_token
	dd	max_token
	dd	min_token
	dd	origin_token
	dd	path_token
	dd	property_token
	dd	rel_token
	dd	repeat_count_token
	dd	repeat_dur_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	restart_token
	dd	rev_token
	dd	role_token
	dd	rotate_token
	dd	system_language_token
	dd	to_token
	dd	typeof_token
	dd	values_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	dd	xlink_role_token
	dd	xlink_show_token
	dd	xlink_title_token
	dd	xlink_type_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


animate_transform_token_table:
	dd	about_token
	dd	accumulate_token
	dd	additive_token
	dd	attribute_name_token
	dd	attribute_type_token
	dd	begin_token
	dd	by_token
	dd	calc_mode_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	dur_token
	dd	end_token
	dd	fill_token
	dd	from_token
	dd	id_token
	dd	key_splines_token
	dd	key_times_token
	dd	max_token
	dd	min_token
	dd	property_token
	dd	rel_token
	dd	repeat_count_token
	dd	repeat_dur_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	restart_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	to_token
	dd	type_token
	dd	typeof_token
	dd	values_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	dd	xlink_role_token
	dd	xlink_show_token
	dd	xlink_title_token
	dd	xlink_type_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


animation_token_table:
	dd	about_token
	dd	begin_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	dur_token
	dd	end_token
	dd	external_resources_required_token
	dd	fill_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	height_token
	dd	id_token
	dd	initial_visibility_token
	dd	max_token
	dd	min_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	preserve_aspect_ratio_token
	dd	property_token
	dd	rel_token
	dd	repeat_count_token
	dd	repeat_dur_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	restart_token
	dd	rev_token
	dd	role_token
	dd	sync_behavior_token
	dd	sync_master_token
	dd	sync_tolerance_token
	dd	system_language_token
	dd	transform_token
	dd	typeof_token
	dd	width_token
	dd	x_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	dd	xlink_role_token
	dd	xlink_show_token
	dd	xlink_title_token
	dd	xlink_type_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	y_token
	dd	slash_token
	dd	0


audio_token_table:
	dd	about_token
	dd	begin_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	dur_token
	dd	end_token
	dd	external_resources_required_token
	dd	fill_token
	dd	id_token
	dd	max_token
	dd	min_token
	dd	property_token
	dd	rel_token
	dd	repeat_count_token
	dd	repeat_dur_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	restart_token
	dd	rev_token
	dd	role_token
	dd	sync_behavior_token
	dd	sync_master_token
	dd	sync_tolerance_token
	dd	system_language_token
	dd	type_token
	dd	typeof_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	dd	xlink_role_token
	dd	xlink_show_token
	dd	xlink_title_token
	dd	xlink_type_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


circle_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	cx_token
	dd	cy_token
	dd	datatype_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	id_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	property_token
	dd	r_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	transform_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


defs_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	id_token
	dd	property_token
	dd	rel_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


desc_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	id_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


discard_token_table:
	dd	about_token
	dd	begin_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	id_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	db	system_language_token
	dd	typeof_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	db	xlink_role_token
	db	xlink_show_token
	db	xlink_title_token
	db	xlink_type_token
	db	xml_base_token
	db	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


ellipse_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	cx_token
	dd	cy_token
	dd	datatype_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	id_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	rx_token
	dd	ry_token
	dd	system_language_token
	dd	transform_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


font_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	external_resources_required_token
	dd	horiz_adv_x_token
	dd	horiz_origin_x_token
	dd	id_token
	dd	property_token
	dd	rel_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


font_face_token_table:
	dd	about_token
	dd	accent_height_token
	dd	alphabetic_token
	dd	ascent_token
	dd	bbox_token
	dd	cap_height_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	descent_token
	dd	external_resources_required_token
	dd	font_family_token
	dd	font_stretch_token
	dd	font_style_token
	dd	font_variant_token
	dd	font_weight_token
	dd	hanging_token
	dd	id_token
	dd	ideographic_token
	dd	mathematical_token
	dd	overline_position_token
	dd	overline_thickness_token
	dd	panose_1_token
	dd	property_token
	dd	rel_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	slope_token
	dd	stemh_token
	dd	stemv_token
	dd	strikethrough_position_token
	dd	strikethrough_thickness_token
	dd	typeof_token
	dd	underline_position_token
	dd	underline_thickness_token
	dd	unicode_range_token
	dd	units_per_em_token
	dd	widths_token
	dd	x_height_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


font_face_src_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	id_token
	dd	property_token
	dd	rel_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


font_face_uri_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	external_resources_required_token
	dd	id_token
	dd	property_token
	dd	rel_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	typeof_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	dd	xlink_role_token
	dd	xlink_show_token
	dd	xlink_title_token
	dd	xlink_type_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


foreign_object_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	external_resources_required_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	height_token
	dd	id_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	transform_token
	dd	typeof_token
	dd	width_token
	dd	x_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	dd	xlink_role_token
	dd	xlink_show_token
	dd	xlink_title_token
	dd	xlink_type_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	y_token
	dd	slash_token
	dd	0


group_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	external_resources_required_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	id_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	transform_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


glyph_token_table:
	dd	about_token
	dd	arabic_form_token
	dd	class_token
	dd	content_token
	dd	d_token
	dd	datatype_token
	dd	glyph_name_token
	dd	horiz_adv_x_token
	dd	id_token
	dd	lang_token
	dd	property_token
	dd	rel_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	typeof_token
	dd	unicode_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


handler_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	ev_event_token
	dd	external_resources_required_token
	dd	id_token
	dd	property_token
	dd	rel_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	type_token
	dd	typeof_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	dd	xlink_role_token
	dd	xlink_show_token
	dd	xlink_title_token
	dd	xlink_type_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


hkern_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	g1_token
	dd	g2_token
	dd	id_token
	dd	k_token
	dd	property_token
	dd	rel_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	typeof_token
	dd	u1_token
	dd	u2_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


image_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	external_resources_required_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	height_token
	dd	id_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	opacity_token
	dd	preserve_aspect_ratio_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	transform_token
	dd	type_token
	dd	typeof_token
	dd	width_token
	dd	x_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	dd	xlink_role_token
	dd	xlink_show_token
	dd	xlink_title_token
	dd	xlink_type_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	y_token
	dd	slash_token
	dd	0


line_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	id_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	transform_token
	dd	typeof_token
	dd	x1_token
	dd	x2_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	y1_token
	dd	y2_token
	dd	slash_token
	dd	0


linear_gradient_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	gradient_units_token
	dd	id_token
	dd	property_token
	dd	rel_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	typeof_token
	dd	x1_token
	dd	x2_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	y1_token
	dd	y2_token
	dd	slash_token
	dd	0


listener_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	default_action_token
	dd	event_token
	dd	handler_token
	dd	id_token
	dd	observer_token
	dd	phase_token
	dd	propagate_token
	dd	property_token
	dd	rel_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	target_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


metadata_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	id_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


missing_glyph_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	d_token
	dd	datatype_token
	dd	horiz_adv_x_token
	dd	id_token
	dd	property_token
	dd	rel_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


mpath_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	id_token
	dd	property_token
	dd	rel_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	typeof_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	dd	xlink_role_token
	dd	xlink_show_token
	dd	xlink_title_token
	dd	xlink_type_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


path_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	d_token
	dd	datatype_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	id_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	path_length_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	transform_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


polygon_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	id_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	points_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	transform_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


polyline_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	id_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	points_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	transform_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


prefetch_token_table:
	dd	about_token
	dd	bandwidth_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	id_token
	dd	media_character_encoding_token
	dd	media_content_encoding_token
	dd	media_size_token
	dd	media_time_token
	dd	property_token
	dd	rel_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	typeof_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	dd	xlink_role_token
	dd	xlink_show_token
	dd	xlink_title_token
	dd	xlink_type_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


radial_gradient_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	cx_token
	dd	cy_token
	dd	datatype_token
	dd	gradient_units_token
	dd	id_token
	dd	property_token
	dd	r_token
	dd	rel_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


rect_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	height_token
	dd	id_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	rx_token
	dd	ry_token
	dd	system_language_token
	dd	transform_token
	dd	typeof_token
	dd	width_token
	dd	x_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	y_token
	dd	slash_token
	dd	0


script_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	external_resources_required_token
	dd	id_token
	dd	property_token
	dd	rel_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	type_token
	dd	typeof_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	dd	xlink_role_token
	dd	xlink_show_token
	dd	xlink_title_token
	dd	xlink_type_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


set_token_table:
	dd	about_token
	dd	attribute_name_token
	dd	attribute_type_token
	dd	begin_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	dur_token
	dd	end_token
	dd	fill_token
	dd	id_token
	dd	max_token
	dd	min_token
	dd	property_token
	dd	rel_token
	dd	repeat_count_token
	dd	repeat_dur_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	to_token
	dd	typeof_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	dd	xlink_role_token
	dd	xlink_show_token
	dd	xlink_title_token
	dd	xlink_type_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


switch_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	external_resources_required_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	id_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	transform_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


tbreak_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	id_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


text_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	editable_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	id_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	rotate_token
	dd	system_language_token
	dd	transform_token
	dd	typeof_token
	dd	x_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	y_token
	dd	slash_token
	dd	0


text_area_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	editable_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	height_token
	dd	id_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	transform_token
	dd	typeof_token
	dd	width_token
	dd	x_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	y_token
	dd	slash_token
	dd	0


title_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	id_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


tspan_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	id_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	typeof_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	slash_token
	dd	0


use_token_table:
	dd	about_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	external_resources_required_token
	dd	focus_highlight_token
	dd	focusable_token
	dd	id_token
	dd	nav_down_token
	dd	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	property_token
	dd	rel_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	rev_token
	dd	role_token
	dd	system_language_token
	dd	transform_token
	dd	typeof_token
	dd	x_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	dd	xlink_role_token
	dd	xlink_show_token
	dd	xlink_title_token
	dd	xlink_type_token
	dd	xml_base_token
	db	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	y_token
	dd	slash_token
	dd	0

video_token_table:
	dd	about_token
	dd	begin_token
	dd	class_token
	dd	content_token
	dd	datatype_token
	dd	dur_token
	dd	end_token
	db	external_resources_required_token
	db	fill_token
	db	focus_highlight_token
	db	focusable_token
	db	height_token
	db	id_token
	db	initial_visibility_token
	db	max_token
	db	min_token
	db	nav_down_token
	db	nav_down_left_token
	dd	nav_down_right_token
	dd	nav_left_token
	dd	nav_next_token
	dd	nav_prev_token
	dd	nav_right_token
	dd	nav_up_token
	dd	nav_up_left_token
	dd	nav_up_right_token
	dd	overlay_token
	dd	preserve_aspect_ratio_token
	dd	property_token
	dd	rel_token
	dd	repeat_count_token
	dd	repeat_dur_token
	dd	required_extensions_token
	dd	required_features_token
	dd	required_fonts_token
	dd	required_formats_token
	dd	resource_token
	dd	restart_token
	dd	rev_token
	dd	role_token
	dd	sync_behavior_token
	dd	sync_master_token
	dd	sync_tolerance_token
	dd	system_language_token
	dd	transform_token
	dd	transform_behavior_token
	dd	type_token
	dd	typeof_token
	dd	width_token
	dd	x_token
	dd	xlink_actuate_token
	dd	xlink_arcrole_token
	dd	xlink_href_token
	dd	xlink_role_token
	dd	xlink_show_token
	dd	xlink_title_token
	dd	xlink_type_token
	dd	xml_base_token
	dd	xml_id_token
	dd	xml_lang_token
	dd	xml_space_token
	dd	y_token
	dd	slash_token
	dd	0


svg_token_lists:
	dd	xml_token_table
	dd	link_token_table
	dd	animate_token_table
	dd	animate_color_token_table
	dd	animate_motion_token_table
	dd	animate_transform_token_table
	dd	animation_token_table
	dd	audio_token_table
	dd	circle_token_table
	dd	defs_token_table
	dd	desc_token_table
	dd	discard_token_table
	dd	ellipse_token_table
	dd	font_token_table
	dd	font_face_token_table
	dd	font_face_src_token_table
	dd	font_face_uri_token_table
	dd	foreign_object_token_table
	dd	group_token_table
	dd	glyph_token_table
	dd	handler_token_table
	dd	hkern_token_table
	dd	image_token_table
	dd	line_token_table
	dd	linear_gradient_token_table
	dd	listener_token_table
	dd	metadata_token_table
	dd	missing_glyph_token_table
	dd	mpath_token_table
	dd	path_token_table
	dd	polygon_token_table
	dd	polyline_token_table
	dd	prefetch_token_table
	dd	radial_gradient_token_table
	dd	rect_token_table
	dd	script_token_table
	dd	set_token_table
	dd	solid_color_token_table
	dd	stop_token_table
	dd	svg_token_table
	dd	switch_token_table
	dd	tbreak_token_table
	dd	text_token_table
	dd	text_area_token_table
	dd	title_token_table
	dd	tspan_token_table
	dd	use_token_table
	dd	video_token_table
	dd	0

; ------------------------------------------------------------------------------
;                            FILE FORMAT DATA
; ------------------------------------------------------------------------------

%macro	csv_comment	1

	db	34, "#", 34, ", ", 34, %1, 34, 10

%endmacro

; ------------------------------------------------------------------------------
; TODO: This list needs reviewed in case some stitch formats
; also can contain object data (EMBFORMAT_STCHANDOBJ).

%define STITCHONLY	1
%define OBJECTONLY	2
%define STCHANDOBJ	2

%macro	format_entry	5

%%startofext:
	db	%1
%%endofext:
	times	6 + %%startofext - %%endofext db 0

%%startofstr:
	db	%2
%%endofstr:
	times	50 + %%startofstr - %%endofstr db 0

	db	%3, %4, %5

%endmacro

; ------------------------------------------------------------------------------

formatTable:
	format_entry	".10o", "Toyota Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".100", "Toyota Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".art", "Bernina Embroidery Format", ' ', ' ', STITCHONLY
	format_entry	".bmc", "Bitmap Cache Embroidery Format", ' ', ' ', STITCHONLY
	format_entry	".bro", "Bits & Volts Embroidery Format", 'U', ' ', STITCHONLY
	format_entry	".cnd", "Melco Embroidery Format", ' ', ' ', STITCHONLY
	format_entry	".col", "Embroidery Thread Color Format", 'U', 'U', STITCHONLY
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
	format_entry	".gt", "Gold Thread Embroidery Format", 'U', ' ', STITCHONLY
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
	format_entry	"END", "END", ' ', ' ', 0


stitchTypeLabels:
	dd	stitch_token
	dd	jump_token
	dd	trim_token
	dd	st_color_token
	dd	st_end_token
	dd	unknown_token
	dd	0

stitch_token:
	db	"STITCH", 0
jump_token:
	db	"JUMP", 0
trim_token:
	db	"TRIM", 0
st_color_token:
	db	"COLOR", 0
st_end_token:
	db	"END", 0
unknown_token:
	db	"UNKNOWN", 0


csvHeader:
	csv_comment	"Embroidermodder 2 CSV Embroidery File"
	csv_comment	"http://embroidermodder.github.io"
	db	10
	csv_comment	"General Notes:"
	csv_comment	"This file can be read by Excel or LibreOffice as CSV (Comma Separated Value) or with a text editor."
	csv_comment	"Lines beginning with # are comments."
	csv_comment	"Lines beginning with > are variables: [VAR_NAME], [VAR_VALUE]"
	csv_comment	"Lines beginning with $ are threads: [THREAD_NUMBER], [RED], [GREEN], [BLUE], [DESCRIPTION], [CATALOG_NUMBER]"
	csv_comment	"Lines beginning with * are stitch entries: [STITCH_TYPE], [X], [Y]"
	db	10
	csv_comment	"Stitch Entry Notes:"
	csv_comment	"STITCH instructs the machine to move to the position [X][Y] and then make a stitch."
	csv_comment	"JUMP instructs the machine to move to the position [X][Y] without making a stitch."
	csv_comment	"TRIM instructs the machine to cut the thread before moving to the position [X][Y] without making a stitch."
	csv_comment	"COLOR instructs the machine to stop temporarily so that the user can change to a different color thread before resuming."
	csv_comment	"END instructs the machine that the design is completed and there are no further instructions."
	csv_comment	"UNKNOWN encompasses instructions that may not be supported currently."
	csv_comment	"[X] and [Y] are absolute coordinates in millimeters (mm)."
	db	10, 0


vipDecodingTable:
	db	0x2E, 0x82, 0xE4, 0x6F, 0x38, 0xA9, 0xDC, 0xC6, 0x7B, 0xB6, 0x28, 0xAC, 0xFD, 0xAA, 0x8A, 0x4E
	db	0x76, 0x2E, 0xF0, 0xE4, 0x25, 0x1B, 0x8A, 0x68, 0x4E, 0x92, 0xB9, 0xB4, 0x95, 0xF0, 0x3E, 0xEF
	db	0xF7, 0x40, 0x24, 0x18, 0x39, 0x31, 0xBB, 0xE1, 0x53, 0xA8, 0x1F, 0xB1, 0x3A, 0x07, 0xFB, 0xCB
	db	0xE6, 0x00, 0x81, 0x50, 0x0E, 0x40, 0xE1, 0x2C, 0x73, 0x50, 0x0D, 0x91, 0xD6, 0x0A, 0x5D, 0xD6
	db	0x8B, 0xB8, 0x62, 0xAE, 0x47, 0x00, 0x53, 0x5A, 0xB7, 0x80, 0xAA, 0x28, 0xF7, 0x5D, 0x70, 0x5E
	db	0x2C, 0x0B, 0x98, 0xE3, 0xA0, 0x98, 0x60, 0x47, 0x89, 0x9B, 0x82, 0xFB, 0x40, 0xC9, 0xB4, 0x00
	db	0x0E, 0x68, 0x6A, 0x1E, 0x09, 0x85, 0xC0, 0x53, 0x81, 0xD1, 0x98, 0x89, 0xAF, 0xE8, 0x85, 0x4F
	db	0xE3, 0x69, 0x89, 0x03, 0xA1, 0x2E, 0x8F, 0xCF, 0xED, 0x91, 0x9F, 0x58, 0x1E, 0xD6, 0x84, 0x3C
	db	0x09, 0x27, 0xBD, 0xF4, 0xC3, 0x90, 0xC0, 0x51, 0x1B, 0x2B, 0x63, 0xBC, 0xB9, 0x3D, 0x40, 0x4D
	db	0x62, 0x6F, 0xE0, 0x8C, 0xF5, 0x5D, 0x08, 0xFD, 0x3D, 0x50, 0x36, 0xD7, 0xC9, 0xC9, 0x43, 0xE4
	db	0x2D, 0xCB, 0x95, 0xB6, 0xF4, 0x0D, 0xEA, 0xC2, 0xFD, 0x66, 0x3F, 0x5E, 0xBD, 0x69, 0x06, 0x2A
	db	0x03, 0x19, 0x47, 0x2B, 0xDF, 0x38, 0xEA, 0x4F, 0x80, 0x49, 0x95, 0xB2, 0xD6, 0xF9, 0x9A, 0x75
	db	0xF4, 0xD8, 0x9B, 0x1D, 0xB0, 0xA4, 0x69, 0xDB, 0xA9, 0x21, 0x79, 0x6F, 0xD8, 0xDE, 0x33, 0xFE
	db	0x9F, 0x04, 0xE5, 0x9A, 0x6B, 0x9B, 0x73, 0x83, 0x62, 0x7C, 0xB9, 0x66, 0x76, 0xF2, 0x5B, 0xC9
	db	0x5E, 0xFC, 0x74, 0xAA, 0x6C, 0xF1, 0xCD, 0x93, 0xCE, 0xE9, 0x80, 0x53, 0x03, 0x3B, 0x97, 0x4B
	db	0x39, 0x76, 0xC2, 0xC1, 0x56, 0xCB, 0x70, 0xFD, 0x3B, 0x3E, 0x52, 0x57, 0x81, 0x5D, 0x56, 0x8D
	db	0x51, 0x90, 0xD4, 0x76, 0xD7, 0xD5, 0x16, 0x02, 0x6D, 0xF2, 0x4D, 0xE1, 0x0E, 0x96, 0x4F, 0xA1
	db	0x3A, 0xA0, 0x60, 0x59, 0x64, 0x04, 0x1A, 0xE4, 0x67, 0xB6, 0xED, 0x3F, 0x74, 0x20, 0x55, 0x1F
	db	0xFB, 0x23, 0x92, 0x91, 0x53, 0xC8, 0x65, 0xAB, 0x9D, 0x51, 0xD6, 0x73, 0xDE, 0x01, 0xB1, 0x80
	db	0xB7, 0xC0, 0xD6, 0x80, 0x1C, 0x2E, 0x3C, 0x83, 0x63, 0xEE, 0xBC, 0x33, 0x25, 0xE2, 0x0E, 0x7A
	db	0x67, 0xDE, 0x3F, 0x71, 0x14, 0x49, 0x9C, 0x92, 0x93, 0x0D, 0x26, 0x9A, 0x0E, 0xDA, 0xED, 0x6F
	db	0xA4, 0x89, 0x0C, 0x1B, 0xF0, 0xA1, 0xDF, 0xE1, 0x9E, 0x3C, 0x04, 0x78, 0xE4, 0xAB, 0x6D, 0xFF
	db	0x9C, 0xAF, 0xCA, 0xC7, 0x88, 0x17, 0x9C, 0xE5, 0xB7, 0x33, 0x6D, 0xDC, 0xED, 0x8F, 0x6C, 0x18
	db	0x1D, 0x71, 0x06, 0xB1, 0xC5, 0xE2, 0xCF, 0x13, 0x77, 0x81, 0xC5, 0xB7, 0x0A, 0x14, 0x0A, 0x6B
	db	0x40, 0x26, 0xA0, 0x88, 0xD1, 0x62, 0x6A, 0xB3, 0x50, 0x12, 0xB9, 0x9B, 0xB5, 0x83, 0x9B, 0x37


maxHeader:
	db	0x56, 0x43, 0x53, 0x4D, 0xFC, 0x03, 0x00, 0x00
	db	0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	db	0xF6, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	db	0x08, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00
	db	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	db	0x00, 0x00, 0x00, 0x00, 0x31, 0x33, 0x37, 0x38
	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	db	0x4D, 0x61, 0x64, 0x65, 0x69, 0x72, 0x61, 0x20
	db	0x52, 0x61, 0x79, 0x6F, 0x6E, 0x20, 0x34, 0x30
	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	db	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	db	0x01, 0x38, 0x09, 0x31, 0x33, 0x30, 0x2F, 0x37
	db	0x30, 0x35, 0x20, 0x48, 0xFA, 0x00, 0x00, 0x00
	db	0x00, 0x00, 0x00, 0x00, 0x00


imageWithFrame:
	db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	db	0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0
	db	0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0
	db	0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
	db	0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0
	db	0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0
	db	0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0
	db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0


; ------------------------------------------------------------------------------
;                              THREAD TABLES
; ------------------------------------------------------------------------------

%macro	thread	5

%%startofstr:
	db	%1
%%endofstr:
	times	30 + %%startofstr - %%endofstr db 0

	db	%2, %3, %4
	dw	%5

%endmacro

; Converted from the table at:
;	 https://www.w3.org/TR/SVGb/types.html#ColorKeywords
; NOTE: This supports both UK and US English names, so the repeated values
; aren't an error.
;
svg_color_codes:
	thread	"aliceblue", 0xf0, 0xf8, 0xff, 0
	thread	"antiquewhite", 0xfa, 0xeb, 0xd7, 1
	thread	"aqua", 0x00, 0xff, 0xff, 2
	thread	"aquamarine", 0x7f, 0xff, 0xd4, 3
	thread	"azure", 0xf0, 0xff, 0xff, 4
	thread	"beige", 0xf5, 0xf5, 0xdc, 5
	thread	"bisque", 0xff, 0xe4, 0xc4, 6
	thread	"black", 0x00, 0x00, 0x00, 7
	thread	"blanchedalmond", 0xff, 0xeb, 0xcd, 8
	thread	"blue", 0x00, 0x00, 0xff, 9
	thread	"blueviolet", 0x8a, 0x2b, 0xe2, 10
	thread	"brown", 0xa5, 0x2a, 0x2a, 11
	thread	"burlywood", 0xde, 0xb8, 0x1b, 12
	thread	"cadetblue", 0x5f, 0x9e, 0xa0, 13
	thread	"chartreuse", 0x7f, 0xff, 0x00, 14
	thread	"chocolate", 0xd2, 0x2d, 0x1e, 15
	thread	"coral", 0xFF, 0x7f, 0x0e, 16
	thread	"cornflowerblue", 0x1c, 0x5f, 0xed, 17
	thread	"cornsilk", 0xff, 0xf8, 0xdc, 18
	thread	"crimson", 0xdc, 0x0e, 0x3c, 19
	thread	"cyan", 0x00, 0xff, 0xff, 20
	thread	"darkblue", 0x00, 0x00, 0x8b, 21
	thread	"darkcyan", 0x00, 0x8b, 0x8b, 22
	thread	"darkgoldenrod", 0xb8, 0x1a, 0x0b, 23
	thread	"darkgray", 0xa9, 0xa9, 0xa9, 24
	thread	"darkgreen", 0x00, 0x1c, 0x00, 25
	thread	"darkgrey", 0xa9, 0xa9, 0xa9, 26
	thread	"darkkhaki", 0xbd, 0xb7, 0x6b, 27
	thread	"darkmagenta", 0x8b, 0x00, 0x8b, 28
	thread	"darkolivegreen", 0x0d, 0x6b, 0x2f, 29
	thread	"darkorange", 0xff, 0x8c, 0x00, 30
	thread	"darkorchid", 0x3f, 0x0e, 0xcc, 31
	thread	"darkred", 0x8b, 0x00, 0x00, 32
	thread	"darksalmon", 0xe9, 0x3c, 0x7a, 33
	thread	"darkseagreen", 0x8f, 0xbc, 0x8f, 34
	thread	"darkslateblue", 0x1e, 0x3d, 0x8b, 35
	thread	"darkslategray", 0x2f, 0x4f, 0x4f, 36
	thread	"darkslategrey", 0x2f, 0x4f, 0x4f, 37
	thread	"darkturquoise", 0x00, 0xce, 0xd1, 38
	thread	"darkviolet", 0x5e, 0x00, 0xd3, 39
	thread	"deeppink", 0xff, 0x0e, 0x5d, 40
	thread	"deepskyblue", 0x00, 0xbf, 0xff, 41
	thread	"dimgray", 0x2d, 0x2d, 0x2d, 42
	thread	"dimgrey", 0x2d, 0x2d, 0x2d, 43
	thread	"dodgerblue", 0x1e, 0x5a, 0xff, 44
	thread	"firebrick", 0xb2, 0x0a, 0x0a, 45
	thread	"floralwhite", 0xff, 0xfa, 0xf0, 46
	thread	"forestgreen", 0x0a, 0x8b, 0x0a, 47
	thread	"fuchsia", 0xff, 0x00, 0xff, 48
	thread	"gainsboro", 0xdc, 0xdc, 0xdc, 49
	thread	"ghostwhite", 0xf8, 0xf8, 0xff, 50
	thread	"gold", 0xff, 0xd7, 0x00, 51
	thread	"goldenrod", 0xda, 0xa5, 0x0e, 52
	thread	"gray", 0x0e, 0x0e, 0x0e, 53
	thread	"grey", 0x0e, 0x0e, 0x0e, 54
	thread	"green", 0x00, 0x0e, 0x00, 55
	thread	"greenyellow", 0xad, 0xff, 0x2f, 56
	thread	"honeydew", 0xf0, 0xff, 0xf0, 57
	thread	"hotpink", 0xff, 0x2d, 0xb4, 58
	thread	"indianred", 0xcd, 0x5c, 0x5c, 59
	thread	"indigo", 0x4b, 0x00, 0x0a, 60
	thread	"ivory", 0xff, 0xff, 0xf0, 61
	thread	"khaki", 0xf0, 0xe6, 0x8c, 62
	thread	"lavender", 0xe6, 0xe6, 0xfa, 63
	thread	"lavenderblush", 0xff, 0xf0, 0xf5, 64
	thread	"lawngreen", 0x7c, 0xfc, 0x00, 65
	thread	"lemonchiffon", 0xff, 0xfa, 0xcd, 66
	thread	"lightblue", 0xad, 0xd8, 0xe6, 67
	thread	"lightcoral", 0xf0, 0x0e, 0x0e, 68
	thread	"lightcyan", 0xe0, 0xff, 0xff, 69
	thread	"lightgoldenrodyellow", 0xfa, 0xfa, 0xd2, 70
	thread	"lightgray", 0xd3, 0xd3, 0xd3, 71
	thread	"lightgreen", 0x5a, 0xee, 0x5a, 72
	thread	"lightgrey", 0xd3, 0xd3, 0xd3, 73
	thread	"lightpink", 0xff, 0xb6, 0xc1, 74
	thread	"lightsalmon", 0xff, 0xa0, 0x7a, 75
	thread	"lightseagreen", 0x0e, 0xb2, 0xaa, 76
	thread	"lightskyblue", 0x1b, 0xce, 0xfa, 77
	thread	"lightslategray", 0x4d, 0x3a, 0x3f, 78
	thread	"lightslategrey", 0x4d, 0x3a, 0x3f, 79
	thread	"lightsteelblue", 0xb0, 0xc4, 0xde, 80
	thread	"lightyellow", 0xff, 0xff, 0xe0, 81
	thread	"lime", 0x00, 0xff, 0x00, 82
	thread	"limegreen", 0x0e, 0xcd, 0x0e, 83
	thread	"linen", 0xfa, 0xf0, 0xe6, 84
	thread	"magenta", 0xff, 0x00, 0xff, 85
	thread	"maroon", 0x0e, 0x00, 0x00, 86
	thread	"mediumaquamarine", 0x2a, 0xcd, 0xaa, 87
	thread	"mediumblue", 0x00, 0x00, 0xcd, 88
	thread	"mediumorchid", 0xba, 0x0d, 0xd3, 89
	thread	"mediumpurple", 0x5d, 0x2e, 0xdb, 90
	thread	"mediumseagreen", 0x3c, 0xb3, 0x2f, 91
	thread	"mediumslateblue", 0x7b, 0x2c, 0xee, 92
	thread	"mediumspringgreen", 0x00, 0xfa, 0x9a, 93
	thread	"mediumturquoise", 0x1e, 0xd1, 0xcc, 94
	thread	"mediumvioletred", 0xc7, 0x0f, 0x0d, 95
	thread	"midnightblue", 0x0d, 0x0d, 0x2e, 96
	thread	"mintcream", 0xf5, 0xff, 0xfa, 97
	thread	"mistyrose", 0xff, 0xe4, 0xe1, 98
	thread	"moccasin", 0xff, 0xe4, 0xb5, 99
	thread	"navajowhite", 0xff, 0xde, 0xad, 100
	thread	"navy", 0x00, 0x00, 0x0e, 101
	thread	"oldlace", 0xfd, 0xf5, 0xe6, 102
	thread	"olive", 0x0e, 0x0e, 0x00, 103
	thread	"olivedrab", 0x6b, 0x8e, 0x0b, 104
	thread	"orange", 0xff, 0xa5, 0x00, 105
	thread	"orangered", 0xff, 0x2d, 0x00, 106
	thread	"orchid", 0xda, 0x2e, 0xd6, 107
	thread	"palegoldenrod", 0xee, 0xe8, 0xaa, 109
	thread	"palegreen", 0x3e, 0xfb, 0x3e, 110
	thread	"paleturquoise", 0xaf, 0xee, 0xee, 111
	thread	"palevioletred", 0xdb, 0x2e, 0x5d, 112
	thread	"papayawhip", 0xff, 0xef, 0xd5, 113
	thread	"peachpuff", 0xff, 0xda, 0xb9, 114
	thread	"peru", 0xcd, 0x0d, 0x3f, 115
	thread	"pink", 0xff, 0xc0, 0xcb, 116
	thread	"plum", 0xdd, 0xa0, 0xdd, 117
	thread	"powderblue", 0xb0, 0xe0, 0xe6, 118
	thread	"purple", 0x0e, 0x00, 0x0e, 119
	thread	"red", 0xff, 0x00, 0x00, 120
	thread	"rosybrown", 0xbc, 0x8f, 0x8f, 121
	thread	"royalblue", 0x1d, 0x2d, 0xe1, 122
	thread	"saddlebrown", 0x8b, 0x2d, 0x0d, 123
	thread	"salmon", 0xfa, 0x0e, 0x1e, 124
	thread	"sandybrown", 0xf4, 0xa4, 0x3c, 125
	thread	"seagreen", 0x2e, 0x8b, 0x1b, 126
	thread	"seashell", 0xff, 0xf5, 0xee, 127
	thread	"sienna", 0xa0, 0x0a, 0x2d, 128
	thread	"silver", 0xc0, 0xc0, 0xc0, 129
	thread	"skyblue", 0x1b, 0xce, 0xeb, 130
	thread	"slateblue", 0x6a, 0x5a, 0xcd, 131
	thread	"slategray", 0x2e, 0x0e, 0x5a, 132
	thread	"slategrey", 0x2e, 0x0e, 0x5a, 133
	thread	"snow", 0xff, 0xfa, 0xfa, 134
	thread	"springgreen", 0x00, 0xff, 0x7f, 135
	thread	"steelblue", 0x2e, 0x0a, 0xb4, 136
	thread	"tan", 0xd2, 0xb4, 0x8c, 137
	thread	"teal", 0x00, 0x0e, 0x0e, 138
	thread	"thistle", 0xd8, 0xbf, 0xd8, 139
	thread	"tomato", 0xff, 0x3f, 0x2f, 140
	thread	"turquoise", 0x1c, 0xe0, 0xd0, 141
	thread	"violet", 0xee, 0x0a, 0xee, 142
	thread	"wheat", 0xf5, 0xde, 0xb3, 143
	thread	"white", 0xff, 0xff, 0xff, 144
	thread	"whitesmoke", 0xf5, 0xf5, 0xf5, 145
	thread	"yellow", 0xff, 0xff, 0x00, 146
	thread	"yellowgreen", 0x9a, 0xcd, 0x0e, 147
	thread	"END", 0, 0, 0, -1

arc_polyester_codes:
	thread	"END", 0, 0, 0, -1

arc_rayon_codes:
	thread	"END", 0, 0, 0, -1

coats_and_clark_rayon_codes:
	thread	"END", 0, 0, 0, -1

exquisite_polyester_codes:
	thread	"END", 0, 0, 0, -1

fufu_polyester_codes:
	thread	"END", 0, 0, 0, -1

fufu_rayon_codes:
	thread	"END", 0, 0, 0, -1

hemingworth_polyester_codes:
	thread	"Pure White", 0xFF, 0xFF, 0xFF, 1001
	thread	"Lemon Ice", 0xDD, 0xE0, 0x0F, 1271
	thread	"Neon Green", 0xC9, 0xDD, 0x03, 1272
	thread	"Brilliant Lime", 0x60, 0xDD, 0x49, 1273
	thread	"Mango", 0xFF, 0xCC, 0x1E, 1274
	thread	"Neon Yellow", 0xFF, 0xED, 0x38, 1275
	thread	"Tropical Orange", 0xFF, 0xA9, 0x52, 1276
	thread	"Neon Orange", 0xFF, 0x93, 0x38, 1277
	thread	"Rebel Peach", 0xFF, 0x58, 0x5F, 1278
	thread	"Shy Flamingo", 0xF2, 0x8C, 0xA3, 1279
	thread	"Neon Pink", 0xFE, 0x8A, 0x9E, 1280
	thread	"Neon Peach", 0xFC, 0x07, 0x4F, 1281
	thread	"Dove Gray", 0xCF, 0xC3, 0xC3, 1067
	thread	"Silver Lining", 0xC9, 0xCA, 0xC8, 1068
	thread	"Storm Cloud", 0xB2, 0xB4, 0xB3, 1069
	thread	"Platinum", 0xC6, 0xC6, 0xBC, 1070
	thread	"Graphite", 0x61, 0x63, 0x65, 1244
	thread	"Light Charcoal", 0x4D, 0x4F, 0x53, 1245
	thread	"Chrome", 0x8E, 0x90, 0x8F, 1072
	thread	"Antique Silver", 0x74, 0x76, 0x78, 1077
	thread	"Pewter Gray", 0x6C, 0x6F, 0x70, 1073
	thread	"Black Stallion", 0x19, 0x1D, 0x1F, 1079
	thread	"Charcoal", 0x1B, 0x24, 0x2A, 1087
	thread	"Classic Black", 0x00, 0x00, 0x00, 1000
	thread	"Marshmallow", 0xD5, 0xD2, 0xCA, 1118
	thread	"Ice Blue", 0xDA, 0xE3, 0xEA, 1119
	thread	"Nautical Blue", 0xA6, 0xBC, 0xC6, 1076
	thread	"Sea Storm", 0x81, 0x8A, 0x8F, 1074
	thread	"Bronzed Steel", 0x59, 0x5A, 0x5C, 1078
	thread	"Silvery Gray", 0xB9, 0xC9, 0xD0, 1239
	thread	"Granite", 0x7D, 0x9A, 0xAA, 1240
	thread	"Shadow", 0x5E, 0x6A, 0x71, 1085
	thread	"Dark Slate Blue", 0x00, 0x3C, 0x69, 1241
	thread	"Deep Slate Blue", 0x00, 0x39, 0x46, 1242
	thread	"Pacific Waters", 0x00, 0x42, 0x50, 1081
	thread	"Dark Slate", 0x37, 0x42, 0x4A, 1086
	thread	"Smoky Blue", 0x00, 0x5B, 0x82, 1192
	thread	"Light Slate Blue", 0x5E, 0x9C, 0xAE, 1193
	thread	"Hyacinth", 0x6A, 0xAD, 0xE4, 1188
	thread	"Bluebird", 0x4B, 0x92, 0xDB, 1187
	thread	"Misty Blue", 0x8F, 0xCA, 0xE7, 1186
	thread	"Cornflower Blue", 0xC2, 0xDE, 0xEA, 1185
	thread	"Pale Blue", 0xA0, 0xCF, 0xEB, 1256
	thread	"Country Blue", 0x00, 0x98, 0xDB, 1255
	thread	"Azure", 0x3D, 0x7E, 0xDB, 1202
	thread	"Royal Blue", 0x00, 0x39, 0xA6, 1203
	thread	"Brilliant Blue", 0x00, 0x33, 0x8D, 1204
	thread	"Deep Blue", 0x0B, 0x22, 0x65, 1205
	thread	"Winter Blue", 0x98, 0xC6, 0xEA, 1189
	thread	"Winter Sky", 0xAA, 0xCA, 0xE6, 1190
	thread	"Sky Blue", 0x8E, 0xBA, 0xE5, 1191
	thread	"China Blue", 0x00, 0x73, 0xCF, 1198
	thread	"Dark Blueberry", 0x00, 0x41, 0x65, 1201
	thread	"Salem Blue", 0x00, 0x41, 0x53, 1200
	thread	"Navy", 0x00, 0x22, 0x44, 1199
	thread	"Sailor Blue", 0x00, 0x2C, 0x5F, 1265
	thread	"Dark Blue ", 0x00, 0x28, 0x57, 1264
	thread	"Berry Blue", 0x00, 0x35, 0x91, 1263
	thread	"True Blue", 0x00, 0x2C, 0x77, 1261
	thread	"Periwinkle", 0x6F, 0x9A, 0xD3, 1262
	thread	"Iceberg Blue", 0x65, 0xCF, 0xE9, 1197
	thread	"Medium Aquamarine", 0x00, 0x75, 0xB0, 1195
	thread	"Dark Aquamarine", 0x00, 0x66, 0xA1, 1196
	thread	"Peacock Blue", 0x00, 0x69, 0x83, 1194
	thread	"Dark Turquoise", 0x00, 0x3D, 0x4C, 1258
	thread	"Turquoise", 0x00, 0x98, 0xC3, 1259
	thread	"Caribbean Blue", 0x00, 0xB0, 0xCA, 1260
	thread	"Summer Sky", 0x6F, 0xD4, 0xE4, 1257
	thread	"Crystal Lake", 0xBB, 0xE7, 0xE6, 1178
	thread	"Icicle Blue", 0xC1, 0xE2, 0xE5, 1172
	thread	"Frosty Blue", 0x8F, 0xDF, 0xE2, 1173
	thread	"Blue Lagoon", 0x00, 0xAF, 0xD8, 1174
	thread	"Blue Satin", 0x00, 0x67, 0x78, 1181
	thread	"Teal Blue", 0x00, 0x7C, 0x92, 1180
	thread	"Light Teal Blue", 0x00, 0x9A, 0xA6, 1176
	thread	"Wintergreen", 0x7C, 0xA2, 0x95, 1175
	thread	"Mint Green", 0x63, 0xCE, 0xCA, 1177
	thread	"Navajo Turquoise", 0x00, 0x87, 0x7C, 1179
	thread	"Peacock Green", 0x00, 0x7B, 0x69, 1182
	thread	"Forest Glen", 0x02, 0x4E, 0x43, 1183
	thread	"Deep Teal", 0x00, 0x49, 0x53, 1184
	thread	"Deep Sea", 0x15, 0x65, 0x70, 1082
	thread	"Dragonfly", 0x00, 0x50, 0x5C, 1113
	thread	"Blue Steel", 0x44, 0x69, 0x7D, 1084
	thread	"Dark Sage", 0x49, 0x6C, 0x60, 1114
	thread	"Silver Green", 0x94, 0x9D, 0x9E, 1115
	thread	"Antique Gray", 0x91, 0xBA, 0xA3, 1243
	thread	"Ocean Spray", 0xB9, 0xCC, 0xC3, 1100
	thread	"Sea Foam", 0xA6, 0xE6, 0xBC, 1088
	thread	"Cucumber Melon", 0x00, 0xB5, 0x88, 1094
	thread	"Light Jade", 0x00, 0x98, 0x5F, 1106
	thread	"Jade", 0x00, 0x9B, 0x74, 1107
	thread	"Dark Jade", 0x00, 0x7D, 0x57, 1105
	thread	"Caribbean", 0x00, 0x6A, 0x4D, 1104
	thread	"Dark Teal", 0x00, 0x68, 0x5B, 1254
	thread	"Minty Teal", 0x0D, 0x77, 0x6E, 1253
	thread	"Lemony Lime", 0xC3, 0xE7, 0x6F, 1099
	thread	"Kiwi Lime", 0xCC, 0xDC, 0x00, 1247
	thread	"Electric Green", 0x69, 0xBE, 0x28, 1097
	thread	"Green Apple", 0x92, 0xD4, 0x00, 1091
	thread	"Key Lime", 0x7A, 0xB8, 0x00, 1092
	thread	"Kelly Green", 0x3F, 0x9C, 0x35, 1093
	thread	"Meadow", 0x00, 0xAF, 0x3F, 1248
	thread	"Grassy Green", 0x00, 0x79, 0x34, 1095
	thread	"Dark Kelly Green", 0x00, 0x85, 0x42, 1108
	thread	"Christmas Green", 0x00, 0x69, 0x3C, 1109
	thread	"Winter Pine ", 0x1C, 0x45, 0x3B, 1250
	thread	"Holly Leaf", 0x17, 0x5E, 0x54, 1249
	thread	"Pistachio Nut", 0xC8, 0xE5, 0x9A, 1096
	thread	"Dusty Green", 0x69, 0x92, 0x3A, 1251
	thread	"Bush Ivy ", 0x55, 0x76, 0x30, 1252
	thread	"Leafy Green", 0x73, 0x96, 0x00, 1089
	thread	"Kentucky Grass", 0x53, 0x68, 0x2B, 1090
	thread	"Ivy", 0x03, 0x56, 0x42, 1103
	thread	"Evergreen", 0x28, 0x4E, 0x36, 1110
	thread	"Mountain Meadow", 0x00, 0x44, 0x38, 1111
	thread	"Forest Green", 0x00, 0x4D, 0x46, 1112
	thread	"Oregano", 0x57, 0x58, 0x4F, 1121
	thread	"Jungle Green", 0x40, 0x4A, 0x29, 1123
	thread	"Thyme", 0x83, 0x84, 0x7A, 1120
	thread	"Light Avocado", 0x82, 0x7C, 0x34, 1058
	thread	"Split Pea", 0xB1, 0x9B, 0x00, 1061
	thread	"Spring Leaf", 0xB5, 0xA3, 0x00, 1059
	thread	"Almond Cream", 0xF8, 0xE4, 0x98, 1060
	thread	"Eggshell", 0xD7, 0xD3, 0xC7, 1229
	thread	"Cornsilk Green", 0xD5, 0xC8, 0x33, 1098
	thread	"Avocado", 0x6A, 0x70, 0x29, 1101
	thread	"Seaweed", 0x89, 0x8F, 0x4B, 1102
	thread	"Olive Green", 0x65, 0x55, 0x1C, 1246
	thread	"Coconut Shell", 0x4B, 0x45, 0x2C, 1117
	thread	"Parsley", 0x4B, 0x47, 0x1A, 1116
	thread	"Dried Sage", 0x71, 0x86, 0x74, 1083
	thread	"Mocha", 0x4F, 0x4C, 0x25, 1125
	thread	"Warm Earth", 0x5D, 0x4F, 0x4B, 1131
	thread	"Dark Chocolate", 0x45, 0x23, 0x25, 1126
	thread	"Deep Walnut", 0x4E, 0x2E, 0x2D, 1128
	thread	"Teddybear Brown", 0x6E, 0x32, 0x19, 1130
	thread	"Light Chestnut", 0x60, 0x35, 0x1D, 1134
	thread	"Pecan Pie", 0x6C, 0x4D, 0x23, 1140
	thread	"Dark Alder", 0x76, 0x6A, 0x65, 1237
	thread	"Army Green", 0x5B, 0x49, 0x1F, 1137
	thread	"Pharaoh Gold", 0x6E, 0x5A, 0x2A, 1135
	thread	"Autumn Haystack", 0xAB, 0x84, 0x22, 1136
	thread	"Sahara", 0x85, 0x68, 0x22, 1122
	thread	"Weathered Wood", 0x67, 0x5C, 0x53, 1236
	thread	"Soft Beige", 0x9A, 0x99, 0x6E, 1124
	thread	"Mercury", 0xC2, 0xB2, 0xB5, 1149
	thread	"Old Lace", 0xA5, 0xAC, 0xAF, 1146
	thread	"Caramel Cappuccino", 0xAE, 0x7D, 0x5B, 1145
	thread	"Brown Sugar", 0xA7, 0x6F, 0x3E, 1133
	thread	"Light Cinnamon", 0xA2, 0x50, 0x22, 1064
	thread	"Cinnamon", 0x86, 0x43, 0x1E, 1238
	thread	"Apple Cider", 0xB2, 0x54, 0x1A, 1163
	thread	"Indian Paintbrush", 0x9A, 0x3B, 0x26, 1144
	thread	"Rust", 0x83, 0x38, 0x20, 1164
	thread	"Toasted Almond", 0x82, 0x5C, 0x26, 1142
	thread	"Pale Caramel", 0xC5, 0x92, 0x17, 1063
	thread	"Honey Butter", 0xDD, 0xB9, 0x9A, 1062
	thread	"Sandy Shore", 0xD2, 0xC2, 0x95, 1057
	thread	"Ecru", 0xC2, 0xC2, 0xA0, 1056
	thread	"Malt", 0xB3, 0xB3, 0x8C, 1055
	thread	"Antique Lace", 0xC7, 0xB3, 0x7F, 1054
	thread	"Champagne", 0xBD, 0x92, 0x71, 1171
	thread	"Butter Taffy", 0xB3, 0x99, 0x5D, 1138
	thread	"Cream Soda", 0xCE, 0xA9, 0x8C, 1235
	thread	"Conch Shell", 0xE3, 0x9B, 0x6C, 1139
	thread	"New Penny", 0xBA, 0x6F, 0x2E, 1132
	thread	"Pumpkin Spice", 0xBB, 0x65, 0x0E, 1141
	thread	"Soft Sunlight", 0xEB, 0xE8, 0xB1, 1042
	thread	"Lemon Drop", 0xEE, 0xEC, 0x83, 1043
	thread	"Daffodil", 0xF3, 0xEC, 0x7A, 1045
	thread	"Lemon Citrus", 0xF5, 0xEC, 0x5A, 1225
	thread	"Sunshine Yellow", 0xFA, 0xE7, 0x00, 1226
	thread	"Canary Yellow", 0xF2, 0xEE, 0x72, 1044
	thread	"Sunflower", 0xFC, 0xD9, 0x00, 1227
	thread	"Sun", 0xFA, 0xDC, 0x41, 1046
	thread	"Dandelion", 0xFE, 0xD1, 0x00, 1047
	thread	"Buttercup", 0xF3, 0xCF, 0x45, 1048
	thread	"Ginger Root", 0xEF, 0xBD, 0x47, 1050
	thread	"Goldenrod", 0xEA, 0xAB, 0x00, 1051
	thread	"Cornsilk", 0xDC, 0xD6, 0xB2, 1037
	thread	"Macadamia", 0xC6, 0xBC, 0x89, 1038
	thread	"Yellow Plumeria", 0xF8, 0xE4, 0x98, 1039
	thread	"Maize", 0xF8, 0xDE, 0x6E, 1040
	thread	"Dried Banana", 0xFA, 0xDA, 0x63, 1049
	thread	"Butternut", 0xFF, 0xCB, 0x4F, 1053
	thread	"Orange Meringue", 0xFF, 0xA1, 0x00, 1232
	thread	"September Sunset", 0xFF, 0xB6, 0x12, 1231
	thread	"Orange Cream", 0xFF, 0xB6, 0x52, 1230
	thread	"Cantaloupe", 0xFF, 0xBC, 0x3D, 1041
	thread	"Old Gold", 0xCE, 0x8E, 0x00, 1052
	thread	"Auburn", 0x9D, 0x53, 0x24, 1143
	thread	"Citrus Burst", 0xE9, 0x83, 0x00, 1024
	thread	"Orange Slice", 0xFF, 0x70, 0x00, 1025
	thread	"Fiery Sunset", 0xE3, 0x72, 0x22, 1027
	thread	"Hunter Orange", 0xFB, 0x4F, 0x14, 1028
	thread	"Fall Harvest", 0xDD, 0x48, 0x14, 1029
	thread	"Candy Apple", 0xCD, 0x20, 0x2C, 1030
	thread	"Christmas Red", 0xC3, 0x00, 0x14, 1270
	thread	"Pomegranate", 0xA7, 0x02, 0x32, 1032
	thread	"Rummy Raisin", 0x88, 0x23, 0x32, 1031
	thread	"Cardinal Red", 0xA5, 0x11, 0x00, 1002
	thread	"Rusty Red", 0x9E, 0x30, 0x39, 1234
	thread	"Redwood", 0x78, 0x30, 0x14, 1233
	thread	"Carrot", 0xD5, 0x5C, 0x19, 1065
	thread	"Paprika", 0xAA, 0x27, 0x2F, 1066
	thread	"Cherrywood", 0x5F, 0x33, 0x27, 1129
	thread	"Burnt Sienna", 0x5D, 0x35, 0x26, 1127
	thread	"Merlot", 0x59, 0x2C, 0x35, 1160
	thread	"Loganberry", 0x6A, 0x1A, 0x41, 1159
	thread	"Cranberry", 0x6E, 0x27, 0x14, 1158
	thread	"Mulberry", 0x66, 0x20, 0x46, 1157
	thread	"Magenta", 0x85, 0x00, 0x3C, 1156
	thread	"Raspberry", 0x64, 0x1F, 0x14, 1155
	thread	"Salmon", 0xFF, 0x81, 0x8D, 1166
	thread	"Georgia Peach", 0xFF, 0xA4, 0x8A, 1015
	thread	"Rose Sunset", 0xFF, 0xB0, 0xB7, 1011
	thread	"Bubblegum Pink", 0xF3, 0x78, 0x9B, 1012
	thread	"Carnation", 0xDB, 0x4D, 0x69, 1014
	thread	"Very Berry", 0x91, 0x00, 0x4B, 1013
	thread	"Raspberry Red", 0x82, 0x24, 0x0C, 1224
	thread	"Dark Salmon", 0xF5, 0x43, 0x59, 1018
	thread	"Apricot Dream", 0xF4, 0x58, 0x7A, 1017
	thread	"Coral Reef", 0xFF, 0x8B, 0x7C, 1016
	thread	"Frosted Peach", 0xFF, 0xC1, 0x9C, 1022
	thread	"Tangerine", 0xFF, 0x8F, 0x70, 1020
	thread	"Dark Mango", 0xFF, 0x6D, 0x42, 1026
	thread	"Marigold", 0xFF, 0xA0, 0x2F, 1023
	thread	"Spun Silk", 0xEC, 0xC1, 0x82, 1168
	thread	"Whipped Papaya", 0xFB, 0xCE, 0x92, 1021
	thread	"Baby Peach", 0xFD, 0xC4, 0x80, 1228
	thread	"Pink Pearl", 0xFF, 0xC2, 0xA2, 1167
	thread	"Peaches 'n Cream", 0xEF, 0xC5, 0xCE, 1169
	thread	"Peach Pastel", 0xEF, 0xBE, 0x9C, 1170
	thread	"Old Penny", 0x77, 0x4A, 0x39, 1162
	thread	"Dusty Rose", 0xB2, 0x6F, 0x7E, 1151
	thread	"Winter Rose", 0xD4, 0x90, 0xA8, 1165
	thread	"Valentine Pink", 0xF6, 0xA3, 0xBB, 1161
	thread	"Petal Peach", 0xFF, 0xB7, 0xAE, 1019
	thread	"Soft Petal", 0xEF, 0xD6, 0xDB, 1150
	thread	"Fuchsia", 0x92, 0x00, 0x75, 1036
	thread	"Pink Kiss", 0xF3, 0x75, 0xC6, 1004
	thread	"Baby Pink", 0xF3, 0xBB, 0xCE, 1003
	thread	"Whisper Pink", 0xF1, 0xDB, 0xDF, 1005
	thread	"Gentle Blush", 0xF3, 0xC9, 0xD3, 1006
	thread	"English Rose", 0xF4, 0xB2, 0xC1, 1007
	thread	"Sweet Pea", 0xF3, 0x9E, 0xBC, 1008
	thread	"Rosy Blush", 0xF7, 0x7A, 0xB4, 1009
	thread	"Passion Pink", 0xD7, 0x1F, 0x85, 1010
	thread	"Mulled Wine", 0x77, 0x20, 0x59, 1035
	thread	"Primrose", 0xC5, 0x00, 0x84, 1034
	thread	"Azalea", 0xA1, 0x00, 0x6B, 1033
	thread	"Snowflake", 0xD1, 0xD4, 0xD3, 1148
	thread	"Moonlight", 0xCA, 0xD1, 0xE7, 1147
	thread	"Tulip", 0x9D, 0xAB, 0xE2, 1207
	thread	"Purple Iris", 0x88, 0x84, 0xD5, 1206
	thread	"Grape", 0x1A, 0x21, 0x55, 1209
	thread	"Moon Shadow", 0x64, 0x59, 0xC4, 1211
	thread	"Electric Purple", 0x21, 0x24, 0x92, 1208
	thread	"Indigo", 0x41, 0x12, 0x44, 1210
	thread	"Royal Purple", 0x3B, 0x00, 0x83, 1223
	thread	"Eggplant", 0x15, 0x1C, 0x54, 1267
	thread	"Dark Purple", 0x49, 0x0E, 0x6F, 1269
	thread	"Pure Purple", 0x57, 0x06, 0x8C, 1268
	thread	"Pale Orchid", 0xDC, 0xC7, 0xDF, 1217
	thread	"Dusty Mauve", 0xC2, 0xAC, 0xBE, 1219
	thread	"Orchid", 0xDC, 0x9D, 0xDD, 1218
	thread	"Heather", 0xB3, 0x82, 0xC7, 1213
	thread	"Lavender", 0x9C, 0x5F, 0xB5, 1214
	thread	"Soft Grape", 0x4B, 0x08, 0xA1, 1266
	thread	"Freesia", 0xC1, 0xAF, 0xE5, 1221
	thread	"Lilac", 0xC5, 0xB9, 0xE3, 1222
	thread	"Peony", 0x6E, 0x2C, 0x6B, 1215
	thread	"Dark Fuschia", 0x7D, 0x00, 0x63, 1216
	thread	"Grape Jelly", 0x75, 0x28, 0x64, 1220
	thread	"Deep Orchid", 0x55, 0x51, 0x7B, 1080
	thread	"Misty Blue Gray", 0x5C, 0x7F, 0x92, 1075
	thread	"Iron Ore", 0xAF, 0xAD, 0xC3, 1071
	thread	"Light Mauve", 0xD8, 0xAA, 0xB3, 1152
	thread	"Dark Mauve", 0x89, 0x68, 0x7C, 1153
	thread	"Wild Plum", 0x64, 0x44, 0x59, 1154
	thread	"Huckleberry", 0x4B, 0x30, 0x6A, 1212
	thread	"END", 0, 0, 0, -1


isacord_polyester_codes:
	thread	"?", 0xFF, 0xFF, 0xFF, 10
	thread	"?", 0xFF, 0xFF, 0xFF, 15
	thread	"?", 0xFF, 0xFF, 0xFF, 17
	thread	"?", 0x00, 0x00, 0x00, 20
	thread	"?", 0xFF, 0xFD, 0xED, 101
	thread	"?", 0x6D, 0x75, 0x7B, 108
	thread	"?", 0x51, 0x5B, 0x61, 111
	thread	"?", 0x5D, 0x5D, 0x5D, 112
	thread	"?", 0xCF, 0xCF, 0xCF, 124
	thread	"?", 0xA1, 0xA9, 0xB4, 131
	thread	"?", 0x19, 0x20, 0x24, 132
	thread	"?", 0x9E, 0xA5, 0xAA, 142
	thread	"?", 0xCF, 0xD1, 0xD5, 145
	thread	"?", 0xC6, 0xBD, 0xB4, 150
	thread	"?", 0xD5, 0xC4, 0xB3, 151
	thread	"?", 0x7C, 0x82, 0x83, 152
	thread	"?", 0xFE, 0xF5, 0xF0, 180
	thread	"?", 0xE9, 0xD7, 0xD9, 182
	thread	"?", 0xEB, 0xE3, 0xDD, 184
	thread	"?", 0xE0, 0xDA, 0x5F, 221
	thread	"?", 0xBF, 0xBA, 0x28, 232
	thread	"?", 0xFA, 0xF6, 0xCC, 250
	thread	"?", 0xF9, 0xF8, 0xE8, 270
	thread	"?", 0xFD, 0xF7, 0x6C, 310
	thread	"?", 0xF5, 0xD3, 0x00, 311
	thread	"?", 0x79, 0x7E, 0x24, 345
	thread	"?", 0xB0, 0xAA, 0x76, 352
	thread	"?", 0x89, 0x8F, 0x2B, 442
	thread	"?", 0x98, 0x99, 0x6D, 453
	thread	"?", 0x6B, 0x7E, 0x6F, 463
	thread	"?", 0x3E, 0x4F, 0x34, 465
	thread	"?", 0xED, 0xEF, 0x05, 501
	thread	"?", 0xF5, 0xD3, 0x00, 506
	thread	"?", 0xFD, 0xE8, 0x96, 520
	thread	"?", 0xD7, 0xCE, 0x8A, 532
	thread	"?", 0xB1, 0x8B, 0x00, 542
	thread	"?", 0xB2, 0x8F, 0x11, 546
	thread	"?", 0xB6, 0x9F, 0x56, 552
	thread	"?", 0xF8, 0xD7, 0x3E, 600
	thread	"?", 0xF8, 0xD7, 0x3E, 605
	thread	"?", 0xF7, 0xDC, 0x00, 608
	thread	"?", 0xFE, 0xF0, 0x9A, 630
	thread	"?", 0xFD, 0xE8, 0x96, 640
	thread	"?", 0xF5, 0xD2, 0xA6, 651
	thread	"?", 0xFE, 0xF9, 0xEA, 660
	thread	"?", 0xFA, 0xF6, 0xE7, 670
	thread	"?", 0xBE, 0xBE, 0xA8, 672
	thread	"?", 0xF7, 0xC3, 0x5F, 700
	thread	"?", 0xF5, 0xCA, 0x00, 702
	thread	"?", 0xDF, 0xA2, 0x00, 704
	thread	"?", 0xFC, 0xF5, 0x38, 706
	thread	"?", 0xFA, 0xDC, 0x59, 713
	thread	"?", 0x8C, 0x7E, 0x6A, 722
	thread	"?", 0x59, 0x49, 0x00, 747
	thread	"?", 0xD6, 0xBF, 0x94, 761
	thread	"?", 0x65, 0x64, 0x52, 776
	thread	"?", 0xF1, 0xAF, 0x00, 800
	thread	"?", 0xF5, 0xBA, 0x5D, 811
	thread	"?", 0xE1, 0xA2, 0x3E, 821
	thread	"?", 0xCC, 0xAB, 0x3F, 822
	thread	"?", 0xDF, 0xA2, 0x00, 824
	thread	"?", 0xD0, 0xA4, 0x4F, 832
	thread	"?", 0xCD, 0x94, 0x4A, 842
	thread	"?", 0xE3, 0xBC, 0x61, 851
	thread	"?", 0x94, 0x7C, 0x4A, 853
	thread	"?", 0xCB, 0xBF, 0xA2, 861
	thread	"?", 0xA5, 0x86, 0x6A, 862
	thread	"?", 0xEB, 0xE7, 0xDD, 870
	thread	"?", 0x9F, 0xA0, 0x86, 873
	thread	"?", 0x9A, 0x89, 0x7B, 874
	thread	"?", 0xF3, 0xB2, 0x59, 904
	thread	"?", 0xCA, 0x83, 0x2C, 922
	thread	"?", 0xC0, 0x73, 0x14, 931
	thread	"?", 0xAC, 0x66, 0x13, 932
	thread	"?", 0x74, 0x48, 0x08, 933
	thread	"?", 0xBD, 0x95, 0x65, 934
	thread	"?", 0xC9, 0x83, 0x00, 940
	thread	"?", 0xAF, 0x7D, 0x3E, 941
	thread	"?", 0x48, 0x39, 0x28, 945
	thread	"?", 0xFE, 0xFE, 0xED, 970
	thread	"?", 0x6A, 0x41, 0x29, 1055
	thread	"?", 0xFD, 0xE2, 0xC1, 1060
	thread	"?", 0xA6, 0x8A, 0x68, 1061
	thread	"?", 0xED, 0x92, 0x06, 1102
	thread	"?", 0xEE, 0x9C, 0x00, 1106
	thread	"?", 0xEE, 0x87, 0x51, 1114
	thread	"?", 0xA3, 0x52, 0x14, 1115
	thread	"?", 0xF8, 0xC0, 0x00, 1120
	thread	"?", 0xB7, 0x97, 0x6B, 1123
	thread	"?", 0x9D, 0x5A, 0x21, 1134
	thread	"?", 0xF3, 0xD8, 0xA8, 1140
	thread	"?", 0xFA, 0xCF, 0xAE, 1141
	thread	"?", 0x7A, 0x44, 0x27, 1154
	thread	"?", 0xDF, 0xC8, 0xAB, 1172
	thread	"?", 0xE8, 0x97, 0x63, 1211
	thread	"?", 0xF1, 0xA2, 0x36, 1220
	thread	"?", 0xE5, 0x57, 0x1D, 1300
	thread	"?", 0xD9, 0x67, 0x4C, 1301
	thread	"?", 0xE4, 0x50, 0x1E, 1304
	thread	"?", 0xEA, 0x71, 0x34, 1305
	thread	"?", 0xE1, 0x2A, 0x23, 1306
	thread	"?", 0xC1, 0x48, 0x17, 1311
	thread	"?", 0xC4, 0x53, 0x31, 1312
	thread	"?", 0xD5, 0x81, 0x5E, 1332
	thread	"?", 0xBB, 0x3D, 0x2E, 1334
	thread	"?", 0xBE, 0x2D, 0x1A, 1335
	thread	"?", 0x5F, 0x1B, 0x23, 1342
	thread	"?", 0x7A, 0x34, 0x41, 1346
	thread	"?", 0xFB, 0xBF, 0x95, 1351
	thread	"?", 0xF4, 0xA7, 0x73, 1352
	thread	"?", 0x69, 0x39, 0x20, 1355
	thread	"?", 0xF9, 0xC5, 0x98, 1362
	thread	"?", 0x43, 0x27, 0x31, 1366
	thread	"?", 0x46, 0x45, 0x37, 1375
	thread	"?", 0xF4, 0xA7, 0x82, 1430
	thread	"?", 0xE2, 0x2D, 0x2A, 1501
	thread	"?", 0xA9, 0x31, 0x21, 1514
	thread	"?", 0xEC, 0x71, 0x68, 1521
	thread	"?", 0xF6, 0xB0, 0x8E, 1532
	thread	"?", 0xF9, 0xC5, 0xB9, 1551
	thread	"?", 0x80, 0x6A, 0x61, 1565
	thread	"?", 0xE3, 0x6C, 0x63, 1600
	thread	"?", 0xE4, 0x47, 0x33, 1701
	thread	"?", 0xDF, 0x00, 0x32, 1703
	thread	"?", 0xE0, 0x00, 0x3D, 1704
	thread	"?", 0xCF, 0x00, 0x40, 1725
	thread	"?", 0xF1, 0xCD, 0xCE, 1755
	thread	"?", 0xE9, 0xC9, 0xBD, 1760
	thread	"?", 0xE8, 0xC0, 0xB8, 1761
	thread	"?", 0xE0, 0x00, 0x46, 1800
	thread	"?", 0xD6, 0x44, 0x5D, 1805
	thread	"?", 0xF4, 0x9E, 0x95, 1840
	thread	"?", 0xFC, 0xDA, 0xD5, 1860
	thread	"?", 0x63, 0x62, 0x54, 1874
	thread	"?", 0x39, 0x45, 0x35, 1876
	thread	"?", 0xE1, 0x00, 0x57, 1900
	thread	"?", 0xBD, 0x00, 0x41, 1902
	thread	"?", 0xC0, 0x03, 0x43, 1903
	thread	"?", 0xA9, 0x02, 0x3A, 1904
	thread	"?", 0xBE, 0x00, 0x4F, 1906
	thread	"?", 0x91, 0x02, 0x30, 1911
	thread	"?", 0x86, 0x02, 0x3E, 1912
	thread	"?", 0x9A, 0x0C, 0x3B, 1913
	thread	"?", 0xA3, 0x30, 0x50, 1921
	thread	"?", 0xF2, 0x8D, 0xA6, 1940
	thread	"?", 0xCE, 0x42, 0x7A, 1950
	thread	"?", 0x95, 0x95, 0x95, 1972
	thread	"?", 0xA3, 0x31, 0x45, 2011
	thread	"?", 0x9F, 0x45, 0x4C, 2022
	thread	"?", 0xC7, 0x97, 0x9B, 2051
	thread	"?", 0x9F, 0x00, 0x3F, 2101
	thread	"?", 0x78, 0x09, 0x3F, 2113
	thread	"?", 0x6D, 0x06, 0x27, 2115
	thread	"?", 0x43, 0x27, 0x32, 2123
	thread	"?", 0xE6, 0x77, 0x8B, 2152
	thread	"?", 0xDF, 0x83, 0x90, 2153
	thread	"?", 0xF9, 0xBF, 0xC0, 2155
	thread	"?", 0xFB, 0xD1, 0xD6, 2160
	thread	"?", 0xD8, 0xD5, 0xD0, 2166
	thread	"?", 0xF7, 0xDE, 0xD6, 2170
	thread	"?", 0xF7, 0xDE, 0xDE, 2171
	thread	"?", 0xE8, 0x41, 0x8C, 2220
	thread	"?", 0x8C, 0x0C, 0x4A, 2222
	thread	"?", 0x88, 0x3A, 0x40, 2224
	thread	"?", 0xEE, 0x71, 0xA1, 2230
	thread	"?", 0xA9, 0x5A, 0x68, 2241
	thread	"?", 0xFA, 0xC8, 0xD3, 2250
	thread	"?", 0xD3, 0x00, 0x7E, 2300
	thread	"?", 0xD2, 0x00, 0x67, 2320
	thread	"?", 0x65, 0x15, 0x33, 2333
	thread	"?", 0x3A, 0x21, 0x2B, 2336
	thread	"?", 0xFD, 0xE5, 0xEC, 2363
	thread	"?", 0x97, 0x00, 0x59, 2500
	thread	"?", 0xAA, 0x43, 0x81, 2504
	thread	"?", 0x82, 0x00, 0x52, 2506
	thread	"?", 0xE2, 0x00, 0x78, 2520
	thread	"?", 0xBF, 0x00, 0x6A, 2521
	thread	"?", 0xF1, 0x89, 0xAF, 2550
	thread	"?", 0xF7, 0xB4, 0xCA, 2560
	thread	"?", 0x49, 0x49, 0x49, 2576
	thread	"?", 0x89, 0x34, 0x80, 2600
	thread	"?", 0x6C, 0x00, 0x51, 2611
	thread	"?", 0xD9, 0x94, 0xB9, 2640
	thread	"?", 0xE6, 0xB7, 0xCF, 2650
	thread	"?", 0xEC, 0xD2, 0xDE, 2655
	thread	"?", 0x60, 0x6D, 0x8C, 2674
	thread	"?", 0x61, 0x00, 0x51, 2711
	thread	"?", 0x49, 0x02, 0x51, 2715
	thread	"?", 0x89, 0x34, 0x7F, 2720
	thread	"?", 0xC6, 0x90, 0xA1, 2764
	thread	"?", 0x6F, 0x06, 0x7B, 2810
	thread	"?", 0xA9, 0x74, 0xAB, 2830
	thread	"?", 0x4C, 0x0F, 0x7B, 2900
	thread	"?", 0x66, 0x40, 0x90, 2905
	thread	"?", 0x83, 0x58, 0x9D, 2910
	thread	"?", 0x8C, 0x6D, 0xAA, 2920
	thread	"?", 0xC9, 0xB5, 0xD4, 3040
	thread	"?", 0xC7, 0x90, 0xBA, 3045
	thread	"?", 0x70, 0x70, 0x70, 3062
	thread	"?", 0x2A, 0x37, 0x7E, 3102
	thread	"?", 0x35, 0x24, 0x7A, 3110
	thread	"?", 0x26, 0x07, 0x51, 3114
	thread	"?", 0x35, 0x3A, 0x90, 3210
	thread	"?", 0x52, 0x4A, 0x90, 3211
	thread	"?", 0x7D, 0x77, 0xAF, 3241
	thread	"?", 0x90, 0x83, 0xA3, 3251
	thread	"?", 0x14, 0x21, 0x4E, 3323
	thread	"?", 0x7F, 0x8B, 0xC2, 3331
	thread	"?", 0x1B, 0x3C, 0x78, 3333
	thread	"?", 0x2E, 0x4B, 0x9B, 3335
	thread	"?", 0x11, 0x26, 0x3C, 3344
	thread	"?", 0x20, 0x2A, 0x65, 3353
	thread	"?", 0x17, 0x1B, 0x4A, 3355
	thread	"?", 0x00, 0x22, 0x32, 3444
	thread	"?", 0x2D, 0x44, 0x91, 3522
	thread	"?", 0x26, 0x12, 0x57, 3536
	thread	"?", 0x3A, 0x28, 0x85, 3541
	thread	"?", 0x23, 0x3B, 0x7D, 3543
	thread	"?", 0x27, 0x3C, 0x82, 3544
	thread	"?", 0x27, 0x26, 0x51, 3554
	thread	"?", 0x28, 0x43, 0x8C, 3600
	thread	"?", 0x24, 0x3A, 0x7D, 3611
	thread	"?", 0x40, 0x55, 0xA1, 3612
	thread	"?", 0x1A, 0x4C, 0x8D, 3622
	thread	"?", 0x92, 0xB1, 0xDC, 3640
	thread	"?", 0x64, 0x8D, 0xC7, 3641
	thread	"?", 0xD0, 0xDE, 0xEE, 3650
	thread	"?", 0xC8, 0xD6, 0xED, 3652
	thread	"?", 0x00, 0x50, 0x7F, 3732
	thread	"?", 0x12, 0x25, 0x3C, 3743
	thread	"?", 0xB7, 0xD1, 0xE3, 3750
	thread	"?", 0xAF, 0xC9, 0xE5, 3761
	thread	"?", 0xCE, 0xD2, 0xD1, 3770
	thread	"?", 0x3D, 0x6A, 0xA1, 3810
	thread	"?", 0x7B, 0xA2, 0xD3, 3815
	thread	"?", 0x91, 0xB9, 0xE2, 3820
	thread	"?", 0xB4, 0xCE, 0xEB, 3840
	thread	"?", 0x50, 0x71, 0x93, 3842
	thread	"?", 0x00, 0x7E, 0xBA, 3900
	thread	"?", 0x00, 0x82, 0xC4, 3901
	thread	"?", 0x00, 0x6C, 0xA5, 3902
	thread	"?", 0x4A, 0xBD, 0xF0, 3910
	thread	"?", 0x86, 0xAA, 0xCA, 3951
	thread	"?", 0x69, 0x76, 0x98, 3953
	thread	"?", 0xA6, 0xD8, 0xF6, 3962
	thread	"?", 0xE1, 0xE1, 0xE1, 3971
	thread	"?", 0x00, 0x93, 0xB9, 4010
	thread	"?", 0x50, 0x77, 0x93, 4032
	thread	"?", 0x26, 0x56, 0x74, 4033
	thread	"?", 0xEA, 0xF0, 0xF9, 4071
	thread	"?", 0x83, 0x86, 0x89, 4073
	thread	"?", 0x2D, 0xB0, 0xCF, 4101
	thread	"?", 0x00, 0x95, 0xC6, 4103
	thread	"?", 0x00, 0xA4, 0xD9, 4111
	thread	"?", 0x00, 0xA9, 0xC9, 4113
	thread	"?", 0x00, 0x82, 0xAD, 4116
	thread	"?", 0x00, 0x40, 0x5D, 4133
	thread	"?", 0x19, 0x20, 0x24, 4174
	thread	"?", 0x4F, 0xB4, 0xCB, 4220
	thread	"?", 0x8D, 0xCE, 0xE4, 4230
	thread	"?", 0x8D, 0xCD, 0xDB, 4240
	thread	"?", 0xD5, 0xEB, 0xF2, 4250
	thread	"?", 0x00, 0x7B, 0x8D, 4410
	thread	"?", 0x00, 0x91, 0xA5, 4421
	thread	"?", 0x00, 0x7D, 0x8C, 4423
	thread	"?", 0x00, 0x79, 0x86, 4425
	thread	"?", 0x5F, 0xBF, 0xD1, 4430
	thread	"?", 0x00, 0x69, 0x81, 4442
	thread	"?", 0x00, 0x7F, 0x92, 4452
	thread	"?", 0x00, 0x2F, 0x38, 4515
	thread	"?", 0x00, 0x73, 0x89, 4531
	thread	"?", 0x00, 0x7B, 0x8D, 4610
	thread	"?", 0x00, 0xA3, 0xA0, 4620
	thread	"?", 0x0B, 0x7F, 0x85, 4625
	thread	"?", 0x00, 0x5B, 0x63, 4643
	thread	"?", 0x23, 0x45, 0x44, 4644
	thread	"?", 0x00, 0x5B, 0x63, 5005
	thread	"?", 0x00, 0xA6, 0xAD, 5010
	thread	"?", 0xB4, 0xDC, 0xD8, 5050
	thread	"?", 0x00, 0x87, 0x6E, 5100
	thread	"?", 0x00, 0x90, 0x84, 5101
	thread	"?", 0x48, 0xBA, 0xB7, 5115
	thread	"?", 0x00, 0xAF, 0x8C, 5210
	thread	"?", 0x8C, 0xCC, 0xC2, 5220
	thread	"?", 0x47, 0xB9, 0xAE, 5230
	thread	"?", 0x19, 0x7E, 0x6D, 5233
	thread	"?", 0x00, 0x6E, 0x42, 5324
	thread	"?", 0x00, 0x4D, 0x3D, 5326
	thread	"?", 0x00, 0x2F, 0x38, 5335
	thread	"?", 0x00, 0x2D, 0x1F, 5374
	thread	"?", 0x00, 0x86, 0x63, 5411
	thread	"?", 0x00, 0x6B, 0x4E, 5415
	thread	"?", 0x00, 0x86, 0x63, 5422
	thread	"?", 0x52, 0xBA, 0x84, 5500
	thread	"?", 0x14, 0xA3, 0x63, 5510
	thread	"?", 0x00, 0x78, 0x48, 5513
	thread	"?", 0x00, 0x86, 0x63, 5515
	thread	"?", 0x52, 0xA0, 0x4F, 5531
	thread	"?", 0x94, 0xAD, 0xA1, 5552
	thread	"?", 0x10, 0x38, 0x28, 5555
	thread	"?", 0x85, 0xC8, 0x75, 5610
	thread	"?", 0x14, 0xB2, 0x6D, 5613
	thread	"?", 0x1A, 0x78, 0x1E, 5633
	thread	"?", 0x15, 0x74, 0x36, 5643
	thread	"?", 0xC9, 0xE3, 0xC5, 5650
	thread	"?", 0x6B, 0x91, 0x81, 5664
	thread	"?", 0xA5, 0xC2, 0x78, 5822
	thread	"?", 0x70, 0x95, 0x3F, 5833
	thread	"?", 0x27, 0x30, 0x14, 5866
	thread	"?", 0x81, 0xC7, 0x50, 5912
	thread	"?", 0x45, 0x70, 0x21, 5933
	thread	"?", 0x50, 0x67, 0x02, 5934
	thread	"?", 0xBB, 0xDB, 0x41, 5940
	thread	"?", 0x00, 0x35, 0x18, 5944
	thread	"?", 0xE3, 0xEB, 0x00, 6010
	thread	"?", 0xBE, 0xD7, 0x82, 6051
	thread	"?", 0x91, 0x96, 0x00, 6133
	thread	"?", 0x48, 0x46, 0x01, 6156
	thread	"END", 0, 0, 0, -1


isafil_rayon_codes:
	thread	"?", 0xFF, 0xFF, 0xFF, 10
	thread	"?", 0xFF, 0xFF, 0xFF, 15
	thread	"?", 0xFF, 0xFF, 0xFF, 17
	thread	"?", 0x00, 0x00, 0x00, 20
	thread	"?", 0xFF, 0xFD, 0xED, 101
	thread	"?", 0x7D, 0x7D, 0x7D, 104
	thread	"?", 0x51, 0x5B, 0x61, 107
	thread	"?", 0x6D, 0x75, 0x7B, 108
	thread	"?", 0xAC, 0xAC, 0xAC, 109
	thread	"?", 0x51, 0x5B, 0x61, 111
	thread	"?", 0x5D, 0x5D, 0x5D, 112
	thread	"?", 0xCF, 0xCF, 0xCF, 124
	thread	"?", 0xA1, 0xA9, 0xB4, 131
	thread	"?", 0x6D, 0x75, 0x7B, 141
	thread	"?", 0x9E, 0xA5, 0xAA, 142
	thread	"?", 0xCF, 0xD1, 0xD5, 145
	thread	"?", 0xC6, 0xBD, 0xB4, 150
	thread	"?", 0xD5, 0xC4, 0xB3, 151
	thread	"?", 0x7C, 0x82, 0x83, 152
	thread	"?", 0x89, 0x8F, 0x94, 156
	thread	"?", 0xFE, 0xF5, 0xF0, 180
	thread	"?", 0xE9, 0xD7, 0xD9, 182
	thread	"?", 0xEB, 0xE3, 0xDD, 184
	thread	"?", 0xE0, 0xDA, 0x5F, 221
	thread	"?", 0xBF, 0xBA, 0x28, 232
	thread	"?", 0xEC, 0xE9, 0xC1, 241
	thread	"?", 0xFA, 0xF6, 0xCC, 250
	thread	"?", 0xEC, 0xE7, 0xA5, 251
	thread	"?", 0xEC, 0xEA, 0xDB, 260
	thread	"?", 0xF9, 0xF8, 0xE8, 270
	thread	"?", 0xFD, 0xF7, 0x6C, 310
	thread	"?", 0xF5, 0xD3, 0x00, 311
	thread	"?", 0x79, 0x7E, 0x24, 345
	thread	"?", 0xB0, 0xAA, 0x76, 352
	thread	"?", 0x89, 0x8F, 0x2B, 442
	thread	"?", 0x98, 0x99, 0x6D, 453
	thread	"?", 0x6E, 0x77, 0x2E, 454
	thread	"?", 0x6B, 0x7E, 0x6F, 463
	thread	"?", 0x3E, 0x4F, 0x34, 465
	thread	"?", 0xED, 0xEF, 0x05, 501
	thread	"?", 0xFA, 0xF6, 0xCC, 505
	thread	"?", 0xF5, 0xD3, 0x00, 506
	thread	"?", 0xFF, 0xFB, 0xD1, 510
	thread	"?", 0xFD, 0xE8, 0x96, 520
	thread	"?", 0xD7, 0xCE, 0x8A, 532
	thread	"?", 0xB1, 0x8B, 0x00, 542
	thread	"?", 0xAA, 0x8D, 0x00, 545
	thread	"?", 0xB2, 0x8F, 0x11, 546
	thread	"?", 0xAC, 0x94, 0x36, 551
	thread	"?", 0xB6, 0x9F, 0x56, 552
	thread	"?", 0xF4, 0xEE, 0x8C, 580
	thread	"?", 0xF1, 0xEB, 0x35, 590
	thread	"?", 0xF8, 0xD7, 0x3E, 600
	thread	"?", 0xF8, 0xD7, 0x3E, 605
	thread	"?", 0xF7, 0xCB, 0x47, 610
	thread	"?", 0xF7, 0xE4, 0x00, 615
	thread	"?", 0xFD, 0xE8, 0x96, 620
	thread	"?", 0xEE, 0xDB, 0x00, 625
	thread	"?", 0xFE, 0xF0, 0x9A, 630
	thread	"?", 0xFD, 0xE1, 0xAF, 635
	thread	"?", 0xFD, 0xE8, 0x96, 640
	thread	"?", 0xF5, 0xD2, 0xA6, 651
	thread	"?", 0xFE, 0xF9, 0xEA, 660
	thread	"?", 0xFA, 0xF6, 0xE7, 670
	thread	"?", 0xBE, 0xBE, 0xA8, 672
	thread	"?", 0xF7, 0xC3, 0x5F, 700
	thread	"?", 0xF5, 0xCA, 0x00, 702
	thread	"?", 0xDF, 0xA2, 0x00, 704
	thread	"?", 0xFC, 0xF5, 0x38, 706
	thread	"?", 0xFA, 0xDC, 0x59, 713
	thread	"?", 0x8C, 0x7E, 0x6A, 722
	thread	"?", 0x82, 0x70, 0x00, 726
	thread	"?", 0x63, 0x62, 0x54, 732
	thread	"?", 0x59, 0x49, 0x00, 747
	thread	"?", 0xD6, 0xBF, 0x94, 761
	thread	"?", 0x65, 0x64, 0x52, 776
	thread	"?", 0xF1, 0xAF, 0x00, 800
	thread	"?", 0xF3, 0xC2, 0x00, 805
	thread	"?", 0xF5, 0xBA, 0x5D, 811
	thread	"?", 0xE1, 0xA2, 0x3E, 821
	thread	"?", 0xCC, 0xAB, 0x3F, 822
	thread	"?", 0xDF, 0xA2, 0x00, 824
	thread	"?", 0xF3, 0xB0, 0x44, 830
	thread	"?", 0xD0, 0xA4, 0x4F, 832
	thread	"?", 0xCD, 0x94, 0x4A, 842
	thread	"?", 0xE3, 0xBC, 0x61, 851
	thread	"?", 0x94, 0x7C, 0x4A, 853
	thread	"?", 0x00, 0x1F, 0x48, 866
	thread	"?", 0xEB, 0xE7, 0xDD, 870
	thread	"?", 0x9F, 0xA0, 0x86, 873
	thread	"?", 0x9A, 0x89, 0x7B, 874
	thread	"?", 0xEE, 0x9C, 0x00, 900
	thread	"?", 0xF3, 0xB2, 0x59, 904
	thread	"?", 0xCA, 0x83, 0x2C, 922
	thread	"?", 0xC0, 0x73, 0x14, 931
	thread	"?", 0xAC, 0x66, 0x13, 932
	thread	"?", 0x74, 0x48, 0x08, 933
	thread	"?", 0xBD, 0x95, 0x65, 934
	thread	"?", 0x80, 0x68, 0x00, 936
	thread	"?", 0xC9, 0x83, 0x00, 940
	thread	"?", 0xAF, 0x7D, 0x3E, 941
	thread	"?", 0x48, 0x39, 0x28, 945
	thread	"?", 0xFE, 0xEC, 0xD9, 961
	thread	"?", 0xFE, 0xFE, 0xED, 970
	thread	"?", 0xDD, 0x97, 0x3A, 1041
	thread	"?", 0x6A, 0x41, 0x29, 1055
	thread	"?", 0xFD, 0xE2, 0xC1, 1060
	thread	"?", 0xA6, 0x8A, 0x68, 1061
	thread	"?", 0xD7, 0x68, 0x14, 1099
	thread	"?", 0xED, 0x87, 0x3F, 1100
	thread	"?", 0xEC, 0x87, 0x0E, 1101
	thread	"?", 0xED, 0x92, 0x06, 1102
	thread	"?", 0xEE, 0x9C, 0x00, 1106
	thread	"?", 0xC4, 0x53, 0x31, 1113
	thread	"?", 0xEE, 0x87, 0x51, 1114
	thread	"?", 0xA3, 0x52, 0x14, 1115
	thread	"?", 0xF8, 0xC0, 0x00, 1120
	thread	"?", 0xB7, 0x97, 0x6B, 1123
	thread	"?", 0x9D, 0x5A, 0x21, 1134
	thread	"?", 0xF3, 0xD8, 0xA8, 1140
	thread	"?", 0xFA, 0xCF, 0xAE, 1141
	thread	"?", 0xDF, 0xC8, 0xAB, 1172
	thread	"?", 0xE8, 0x97, 0x63, 1211
	thread	"?", 0xF1, 0xA2, 0x36, 1220
	thread	"?", 0x3D, 0x27, 0x23, 1276
	thread	"?", 0xE5, 0x57, 0x1D, 1300
	thread	"?", 0xE8, 0x64, 0x3C, 1302
	thread	"?", 0xE4, 0x50, 0x1E, 1304
	thread	"?", 0xEA, 0x71, 0x34, 1305
	thread	"?", 0xE1, 0x2A, 0x23, 1306
	thread	"?", 0xC1, 0x48, 0x17, 1311
	thread	"?", 0xC4, 0x53, 0x31, 1312
	thread	"?", 0xD7, 0x62, 0x3E, 1313
	thread	"?", 0xED, 0x7C, 0x56, 1320
	thread	"?", 0x92, 0x29, 0x1B, 1324
	thread	"?", 0xD5, 0x81, 0x5E, 1332
	thread	"?", 0xBB, 0x3D, 0x2E, 1334
	thread	"?", 0xBE, 0x2D, 0x1A, 1335
	thread	"?", 0x5F, 0x1B, 0x23, 1342
	thread	"?", 0x7A, 0x34, 0x41, 1346
	thread	"?", 0x84, 0x29, 0x1D, 1348
	thread	"?", 0xFB, 0xBF, 0x95, 1351
	thread	"?", 0xF4, 0xA7, 0x73, 1352
	thread	"?", 0x69, 0x39, 0x20, 1355
	thread	"?", 0xF9, 0xC6, 0xA1, 1361
	thread	"?", 0xF9, 0xC5, 0x98, 1362
	thread	"?", 0x43, 0x27, 0x31, 1366
	thread	"?", 0x46, 0x45, 0x37, 1375
	thread	"?", 0x4D, 0x2E, 0x18, 1376
	thread	"?", 0xD6, 0x4F, 0x42, 1421
	thread	"?", 0xF4, 0xA7, 0x82, 1430
	thread	"?", 0xE2, 0x2D, 0x2A, 1501
	thread	"?", 0xA9, 0x31, 0x21, 1514
	thread	"?", 0xEC, 0x71, 0x68, 1521
	thread	"?", 0xF6, 0xB0, 0x8E, 1532
	thread	"?", 0xF9, 0xC5, 0xB9, 1551
	thread	"?", 0x80, 0x6A, 0x61, 1565
	thread	"?", 0x46, 0x45, 0x37, 1573
	thread	"?", 0xE3, 0x6C, 0x63, 1600
	thread	"?", 0xF9, 0xC7, 0xB9, 1630
	thread	"?", 0xE4, 0x47, 0x33, 1701
	thread	"?", 0xDF, 0x00, 0x32, 1703
	thread	"?", 0xE4, 0x47, 0x33, 1705
	thread	"?", 0xCF, 0x00, 0x40, 1725
	thread	"?", 0xDB, 0x68, 0x6B, 1750
	thread	"?", 0xF1, 0xCD, 0xCE, 1755
	thread	"?", 0xE9, 0xC9, 0xBD, 1760
	thread	"?", 0xE8, 0xC0, 0xB8, 1761
	thread	"?", 0xE0, 0x00, 0x46, 1800
	thread	"?", 0xE4, 0x34, 0x49, 1802
	thread	"?", 0xD6, 0x44, 0x5D, 1805
	thread	"?", 0xF4, 0x9E, 0x95, 1840
	thread	"?", 0xB7, 0x66, 0x63, 1842
	thread	"?", 0xE3, 0x6C, 0x63, 1849
	thread	"?", 0xF0, 0x88, 0x7D, 1850
	thread	"?", 0xFA, 0xC7, 0xC1, 1855
	thread	"?", 0xFC, 0xDA, 0xD5, 1860
	thread	"?", 0xFD, 0xE3, 0xD3, 1870
	thread	"?", 0x63, 0x62, 0x54, 1874
	thread	"?", 0x39, 0x45, 0x35, 1876
	thread	"?", 0xE1, 0x00, 0x57, 1900
	thread	"?", 0xBD, 0x00, 0x41, 1902
	thread	"?", 0xC0, 0x03, 0x43, 1903
	thread	"?", 0xA9, 0x02, 0x3A, 1904
	thread	"?", 0x96, 0x00, 0x18, 1905
	thread	"?", 0xBE, 0x00, 0x4F, 1906
	thread	"?", 0x91, 0x02, 0x30, 1911
	thread	"?", 0x86, 0x02, 0x3E, 1912
	thread	"?", 0x9A, 0x0C, 0x3B, 1913
	thread	"?", 0xA4, 0x1F, 0x39, 1914
	thread	"?", 0xA3, 0x30, 0x50, 1921
	thread	"?", 0xF2, 0x8D, 0xA6, 1940
	thread	"?", 0xCE, 0x42, 0x7A, 1950
	thread	"?", 0xF2, 0xB9, 0xBE, 1960
	thread	"?", 0x95, 0x95, 0x95, 1972
	thread	"?", 0xA3, 0x31, 0x45, 2011
	thread	"?", 0x9F, 0x45, 0x4C, 2022
	thread	"?", 0xC7, 0x97, 0x9B, 2051
	thread	"?", 0xD1, 0x8D, 0x89, 2053
	thread	"?", 0x97, 0x00, 0x38, 2100
	thread	"?", 0x9F, 0x00, 0x3F, 2101
	thread	"?", 0x78, 0x09, 0x3F, 2113
	thread	"?", 0x43, 0x27, 0x32, 2123
	thread	"?", 0xE6, 0x77, 0x8B, 2152
	thread	"?", 0xDF, 0x83, 0x90, 2153
	thread	"?", 0xF9, 0xBF, 0xC0, 2155
	thread	"?", 0xFB, 0xD1, 0xD6, 2160
	thread	"?", 0xFD, 0xE3, 0xDB, 2165
	thread	"?", 0xD8, 0xD5, 0xD0, 2166
	thread	"?", 0xFE, 0xED, 0xE2, 2168
	thread	"?", 0xF7, 0xDE, 0xD6, 2170
	thread	"?", 0xF7, 0xDE, 0xDE, 2171
	thread	"?", 0xFC, 0xD9, 0xC4, 2180
	thread	"?", 0xE8, 0x41, 0x8C, 2220
	thread	"?", 0x8C, 0x0C, 0x4A, 2222
	thread	"?", 0x88, 0x3A, 0x40, 2224
	thread	"?", 0xEE, 0x71, 0xA1, 2230
	thread	"?", 0xA9, 0x5A, 0x68, 2241
	thread	"?", 0xFA, 0xC8, 0xD3, 2250
	thread	"?", 0xD3, 0x00, 0x7E, 2300
	thread	"?", 0xBF, 0x00, 0x6A, 2310
	thread	"?", 0xD2, 0x00, 0x67, 2320
	thread	"?", 0x78, 0x0C, 0x38, 2332
	thread	"?", 0x65, 0x15, 0x33, 2333
	thread	"?", 0x3A, 0x21, 0x2B, 2336
	thread	"?", 0xF2, 0xE0, 0xDC, 2360
	thread	"?", 0xFD, 0xE5, 0xEC, 2363
	thread	"?", 0x97, 0x00, 0x59, 2500
	thread	"?", 0x8B, 0x17, 0x71, 2502
	thread	"?", 0xAA, 0x43, 0x81, 2504
	thread	"?", 0xB4, 0x00, 0x73, 2505
	thread	"?", 0x82, 0x00, 0x52, 2506
	thread	"?", 0xD6, 0x3C, 0x81, 2513
	thread	"?", 0xE2, 0x00, 0x78, 2520
	thread	"?", 0xBF, 0x00, 0x6A, 2521
	thread	"?", 0xEE, 0x71, 0xA1, 2524
	thread	"?", 0xF1, 0x89, 0xAF, 2550
	thread	"?", 0xF7, 0xB4, 0xCA, 2555
	thread	"?", 0xF7, 0xB4, 0xCA, 2560
	thread	"?", 0x49, 0x49, 0x49, 2576
	thread	"?", 0x39, 0x42, 0x48, 2578
	thread	"?", 0x89, 0x34, 0x80, 2600
	thread	"?", 0x6C, 0x00, 0x51, 2611
	thread	"?", 0xCD, 0x73, 0xA6, 2620
	thread	"?", 0xD9, 0x94, 0xB9, 2640
	thread	"?", 0xDD, 0xBD, 0xD5, 2645
	thread	"?", 0xE6, 0xB7, 0xCF, 2650
	thread	"?", 0xEC, 0xD2, 0xDE, 2655
	thread	"?", 0x60, 0x6D, 0x8C, 2674
	thread	"?", 0x64, 0x6A, 0x6E, 2675
	thread	"?", 0x61, 0x00, 0x51, 2711
	thread	"?", 0x70, 0x41, 0x91, 2712
	thread	"?", 0x49, 0x02, 0x51, 2715
	thread	"?", 0x2F, 0x20, 0x6F, 2743
	thread	"?", 0xC6, 0x90, 0xA1, 2764
	thread	"?", 0x6F, 0x06, 0x7B, 2810
	thread	"?", 0xAD, 0x85, 0xB1, 2820
	thread	"?", 0xA9, 0x74, 0xAB, 2830
	thread	"?", 0x4C, 0x0F, 0x7B, 2900
	thread	"?", 0x66, 0x40, 0x90, 2905
	thread	"?", 0x83, 0x58, 0x9D, 2910
	thread	"?", 0x8C, 0x6D, 0xAA, 2920
	thread	"?", 0xC9, 0xB5, 0xD4, 3040
	thread	"?", 0xC7, 0x90, 0xBA, 3045
	thread	"?", 0x70, 0x70, 0x70, 3062
	thread	"?", 0x2A, 0x37, 0x7E, 3102
	thread	"?", 0x3C, 0x1F, 0x81, 3103
	thread	"?", 0x35, 0x24, 0x7A, 3110
	thread	"?", 0x26, 0x07, 0x51, 3114
	thread	"?", 0x28, 0x13, 0x5B, 3133
	thread	"?", 0x6E, 0x5D, 0xA3, 3200
	thread	"?", 0x35, 0x3A, 0x90, 3210
	thread	"?", 0x52, 0x4A, 0x90, 3211
	thread	"?", 0x78, 0x5F, 0xA3, 3213
	thread	"?", 0x24, 0x17, 0x57, 3222
	thread	"?", 0x7D, 0x77, 0xAF, 3241
	thread	"?", 0x90, 0x83, 0xA3, 3251
	thread	"?", 0xB2, 0xAA, 0xBD, 3262
	thread	"?", 0x39, 0x2D, 0x88, 3301
	thread	"?", 0x56, 0x61, 0xA8, 3321
	thread	"?", 0x32, 0x38, 0x87, 3322
	thread	"?", 0x14, 0x21, 0x4E, 3323
	thread	"?", 0x3A, 0x28, 0x85, 3330
	thread	"?", 0x7F, 0x8B, 0xC2, 3331
	thread	"?", 0x1B, 0x3C, 0x78, 3333
	thread	"?", 0xB9, 0xBD, 0xD9, 3340
	thread	"?", 0x11, 0x26, 0x3C, 3344
	thread	"?", 0x20, 0x2A, 0x65, 3353
	thread	"?", 0x17, 0x1B, 0x4A, 3355
	thread	"?", 0x95, 0x9A, 0xCA, 3420
	thread	"?", 0x6A, 0x76, 0xB5, 3430
	thread	"?", 0x11, 0x26, 0x3C, 3443
	thread	"?", 0x00, 0x22, 0x32, 3444
	thread	"?", 0x2D, 0x44, 0x91, 3522
	thread	"?", 0x26, 0x12, 0x57, 3536
	thread	"?", 0x53, 0x42, 0x8A, 3540
	thread	"?", 0x3A, 0x28, 0x85, 3541
	thread	"?", 0x23, 0x3B, 0x7D, 3543
	thread	"?", 0x27, 0x3C, 0x82, 3544
	thread	"?", 0x27, 0x26, 0x51, 3554
	thread	"?", 0x28, 0x43, 0x8C, 3600
	thread	"?", 0x24, 0x3A, 0x7D, 3611
	thread	"?", 0x40, 0x55, 0xA1, 3612
	thread	"?", 0x1A, 0x4C, 0x8D, 3622
	thread	"?", 0x1E, 0x56, 0x9F, 3631
	thread	"?", 0x92, 0xB1, 0xDC, 3640
	thread	"?", 0x64, 0x8D, 0xC7, 3641
	thread	"?", 0xD0, 0xDE, 0xEE, 3650
	thread	"?", 0xEA, 0xF0, 0xF9, 3661
	thread	"?", 0x00, 0x50, 0x7F, 3732
	thread	"?", 0x12, 0x25, 0x3C, 3743
	thread	"?", 0xB7, 0xD1, 0xE3, 3750
	thread	"?", 0xD0, 0xDE, 0xEE, 3752
	thread	"?", 0xAF, 0xC9, 0xE5, 3761
	thread	"?", 0xCE, 0xD2, 0xD1, 3770
	thread	"?", 0x3D, 0x6A, 0xA1, 3810
	thread	"?", 0x91, 0xB9, 0xE2, 3820
	thread	"?", 0x00, 0x77, 0x9E, 3822
	thread	"?", 0xB4, 0xCE, 0xEB, 3840
	thread	"?", 0x50, 0x71, 0x93, 3842
	thread	"?", 0xD5, 0xE3, 0xF4, 3845
	thread	"?", 0x9A, 0xB8, 0xD3, 3851
	thread	"?", 0x00, 0x7E, 0xBA, 3900
	thread	"?", 0x00, 0x82, 0xC4, 3901
	thread	"?", 0x00, 0x6C, 0xA5, 3902
	thread	"?", 0x4A, 0xBD, 0xF0, 3910
	thread	"?", 0x86, 0xAA, 0xCA, 3951
	thread	"?", 0x48, 0x5E, 0x8A, 3952
	thread	"?", 0x69, 0x76, 0x98, 3953
	thread	"?", 0xC5, 0xE1, 0xF3, 3961
	thread	"?", 0xA6, 0xD8, 0xF6, 3962
	thread	"?", 0xE1, 0xE1, 0xE1, 3971
	thread	"?", 0x00, 0x93, 0xB9, 4010
	thread	"?", 0x00, 0x65, 0x87, 4022
	thread	"?", 0x87, 0xC7, 0xEA, 4030
	thread	"?", 0x50, 0x77, 0x93, 4032
	thread	"?", 0x26, 0x56, 0x74, 4033
	thread	"?", 0x9E, 0xD4, 0xE6, 4040
	thread	"?", 0xEA, 0xF0, 0xF9, 4071
	thread	"?", 0x00, 0x96, 0xC1, 4100
	thread	"?", 0x2D, 0xB0, 0xCF, 4101
	thread	"?", 0x00, 0x95, 0xC6, 4103
	thread	"?", 0x00, 0x81, 0xAA, 4105
	thread	"?", 0x00, 0xA4, 0xD9, 4111
	thread	"?", 0x00, 0xA9, 0xC9, 4113
	thread	"?", 0x5D, 0xBF, 0xD2, 4121
	thread	"?", 0x00, 0x40, 0x5D, 4133
	thread	"?", 0x19, 0x20, 0x24, 4174
	thread	"?", 0x19, 0x20, 0x24, 4175
	thread	"?", 0x4F, 0xB4, 0xCB, 4220
	thread	"?", 0x8D, 0xCE, 0xE4, 4230
	thread	"?", 0x2D, 0xB0, 0xCF, 4231
	thread	"?", 0x00, 0x65, 0x87, 4232
	thread	"?", 0x8D, 0xCD, 0xDB, 4240
	thread	"?", 0xD5, 0xEB, 0xF2, 4250
	thread	"?", 0x00, 0x73, 0x89, 4400
	thread	"?", 0x00, 0x7B, 0x8D, 4410
	thread	"?", 0x00, 0xB2, 0xCA, 4420
	thread	"?", 0x00, 0x91, 0xA5, 4421
	thread	"?", 0x00, 0x7D, 0x8C, 4423
	thread	"?", 0x00, 0x79, 0x86, 4425
	thread	"?", 0x5F, 0xBF, 0xD1, 4430
	thread	"?", 0x00, 0x42, 0x50, 4432
	thread	"?", 0x8D, 0xCE, 0xE4, 4440
	thread	"?", 0x00, 0x69, 0x81, 4442
	thread	"?", 0x00, 0x7F, 0x92, 4452
	thread	"?", 0x00, 0x81, 0x92, 4500
	thread	"?", 0x00, 0x70, 0x79, 4513
	thread	"?", 0x00, 0x2F, 0x38, 4515
	thread	"?", 0x00, 0x64, 0x6A, 4516
	thread	"?", 0x00, 0x73, 0x89, 4531
	thread	"?", 0x00, 0x7B, 0x8D, 4610
	thread	"?", 0x00, 0xA3, 0xA0, 4620
	thread	"?", 0x0B, 0x7F, 0x85, 4625
	thread	"?", 0x00, 0x5B, 0x63, 4643
	thread	"?", 0x23, 0x45, 0x44, 4644
	thread	"?", 0x8C, 0xCD, 0xD3, 4840
	thread	"?", 0x00, 0x6F, 0x73, 5000
	thread	"?", 0x00, 0x5B, 0x63, 5005
	thread	"?", 0x00, 0xA6, 0xAD, 5010
	thread	"?", 0x49, 0xBA, 0xC0, 5020
	thread	"?", 0xCF, 0xDD, 0xE0, 5040
	thread	"?", 0xB4, 0xDC, 0xD8, 5050
	thread	"?", 0x00, 0x87, 0x6E, 5100
	thread	"?", 0x00, 0x90, 0x84, 5101
	thread	"?", 0x00, 0xB1, 0xAE, 5111
	thread	"?", 0x48, 0xBA, 0xB7, 5115
	thread	"?", 0x00, 0xAF, 0x8C, 5210
	thread	"?", 0x8C, 0xCC, 0xC2, 5220
	thread	"?", 0x47, 0xB9, 0xAE, 5230
	thread	"?", 0x19, 0x7E, 0x6D, 5233
	thread	"?", 0x8C, 0xCC, 0xC2, 5240
	thread	"?", 0x00, 0x5B, 0x63, 5255
	thread	"?", 0x00, 0x6E, 0x42, 5324
	thread	"?", 0x00, 0x4D, 0x3D, 5326
	thread	"?", 0x00, 0x2F, 0x38, 5335
	thread	"?", 0x00, 0x2D, 0x1F, 5374
	thread	"?", 0x00, 0x2F, 0x38, 5375
	thread	"?", 0x00, 0x86, 0x63, 5411
	thread	"?", 0x00, 0x6B, 0x4E, 5415
	thread	"?", 0x00, 0x86, 0x63, 5422
	thread	"?", 0x00, 0x6B, 0x56, 5425
	thread	"?", 0x00, 0x88, 0x79, 5431
	thread	"?", 0xDB, 0xE9, 0xE5, 5460
	thread	"?", 0x6A, 0xC0, 0x93, 5470
	thread	"?", 0x52, 0xBA, 0x84, 5500
	thread	"?", 0x14, 0xA3, 0x63, 5510
	thread	"?", 0x00, 0x78, 0x48, 5513
	thread	"?", 0x00, 0x86, 0x63, 5515
	thread	"?", 0x52, 0xA0, 0x4F, 5531
	thread	"?", 0x6E, 0xA2, 0x93, 5542
	thread	"?", 0x94, 0xAD, 0xA1, 5552
	thread	"?", 0x10, 0x38, 0x28, 5555
	thread	"?", 0x63, 0xBE, 0x5F, 5600
	thread	"?", 0x85, 0xC8, 0x75, 5610
	thread	"?", 0x2C, 0xB4, 0x31, 5611
	thread	"?", 0x14, 0xB2, 0x6D, 5613
	thread	"?", 0x40, 0xB7, 0x80, 5620
	thread	"?", 0x1A, 0x78, 0x1E, 5633
	thread	"?", 0x15, 0x74, 0x36, 5643
	thread	"?", 0xC9, 0xE3, 0xC5, 5650
	thread	"?", 0x6B, 0x91, 0x81, 5664
	thread	"?", 0x3A, 0x6D, 0x57, 5765
	thread	"?", 0x10, 0x38, 0x28, 5766
	thread	"?", 0x02, 0x14, 0x0C, 5776
	thread	"?", 0xA5, 0xC2, 0x78, 5822
	thread	"?", 0xB4, 0xD3, 0x83, 5832
	thread	"?", 0x70, 0x95, 0x3F, 5833
	thread	"?", 0xA2, 0xD2, 0x89, 5840
	thread	"?", 0x27, 0x30, 0x14, 5866
	thread	"?", 0x81, 0xC7, 0x50, 5912
	thread	"?", 0x45, 0x70, 0x21, 5933
	thread	"?", 0x50, 0x67, 0x02, 5934
	thread	"?", 0xBB, 0xDB, 0x41, 5940
	thread	"?", 0x00, 0x35, 0x18, 5944
	thread	"?", 0xE3, 0xEB, 0x00, 6010
	thread	"?", 0xBE, 0xD7, 0x82, 6051
	thread	"?", 0x2D, 0x3B, 0x01, 6065
	thread	"?", 0xDC, 0xDD, 0xD1, 6071
	thread	"?", 0x91, 0x96, 0x00, 6133
	thread	"?", 0x48, 0x46, 0x01, 6156
	thread	"END", 0, 0, 0, -1


marathon_polyester_codes:
	thread	"END", 0, 0, 0, -1


marathon_rayon_codes:
	thread	"END", 0, 0, 0, -1


madeira_polyester_codes:
	thread	"END", 0, 0, 0, -1


madeira_rayon_codes:
	thread	"END", 0, 0, 0, -1


metro_polyester_codes:
	thread	"END", 0, 0, 0, -1


pantone_codes:
	thread	"?", 0xFF, 0xFF, 0x7D, 100
	thread	"?", 0xFF, 0xFF, 0x36, 101
	thread	"?", 0xFF, 0xFC, 0x0D, 102
	thread	"?", 0xD1, 0xCB, 0x00, 103
	thread	"?", 0xB3, 0xAD, 0x00, 104
	thread	"?", 0x80, 0x7C, 0x00, 105
	thread	"?", 0xFF, 0xFA, 0x4F, 106
	thread	"?", 0xFF, 0xF5, 0x36, 107
	thread	"?", 0xFF, 0xF0, 0x0D, 108
	thread	"?", 0xFF, 0xE6, 0x00, 109
	thread	"?", 0xED, 0xD1, 0x00, 110
	thread	"?", 0xBA, 0xA6, 0x00, 111
	thread	"?", 0x9E, 0x8E, 0x00, 112
	thread	"?", 0xFF, 0xED, 0x57, 113
	thread	"?", 0xFF, 0xEB, 0x45, 114
	thread	"?", 0xFF, 0xE8, 0x33, 115
	thread	"?", 0xFF, 0xD6, 0x00, 116
	thread	"?", 0xD9, 0xB2, 0x00, 117
	thread	"?", 0xBA, 0x99, 0x00, 118
	thread	"?", 0x82, 0x72, 0x00, 119
	thread	"?", 0xFF, 0xE8, 0x6B, 120
	thread	"?", 0xFF, 0xF2, 0xB0, 1205
	thread	"?", 0xFF, 0xE3, 0x4F, 121
	thread	"?", 0xFF, 0xE8, 0x8C, 1215
	thread	"?", 0xFF, 0xD4, 0x33, 122
	thread	"?", 0xFF, 0xD4, 0x61, 1225
	thread	"?", 0xFF, 0xC2, 0x0F, 123
	thread	"?", 0xFF, 0xB5, 0x17, 1235
	thread	"?", 0xF0, 0xAD, 0x00, 124
	thread	"?", 0xD1, 0x97, 0x00, 1245
	thread	"?", 0xBD, 0x8C, 0x00, 125
	thread	"?", 0xA8, 0x7B, 0x00, 1255
	thread	"?", 0xA1, 0x78, 0x00, 126
	thread	"?", 0x7D, 0x5B, 0x00, 1265
	thread	"?", 0xFF, 0xED, 0x80, 127
	thread	"?", 0xFF, 0xE3, 0x59, 128
	thread	"?", 0xFF, 0xD6, 0x3B, 129
	thread	"?", 0xFF, 0xB3, 0x00, 130
	thread	"?", 0xE8, 0x9E, 0x00, 131
	thread	"?", 0xB3, 0x81, 0x00, 132
	thread	"?", 0x70, 0x5A, 0x00, 133
	thread	"?", 0xFF, 0xE3, 0x8C, 134
	thread	"?", 0xFF, 0xDB, 0x87, 1345
	thread	"?", 0xFF, 0xCF, 0x66, 135
	thread	"?", 0xFF, 0xCC, 0x70, 1355
	thread	"?", 0xFF, 0xBA, 0x3D, 136
	thread	"?", 0xFF, 0xB5, 0x47, 1365
	thread	"?", 0xFF, 0xA6, 0x1A, 137
	thread	"?", 0xFF, 0x99, 0x1A, 1375
	thread	"?", 0xFC, 0x92, 0x00, 138
	thread	"?", 0xED, 0x85, 0x00, 1385
	thread	"?", 0xC4, 0x7C, 0x00, 139
	thread	"?", 0xA1, 0x5F, 0x00, 1395
	thread	"?", 0x75, 0x56, 0x00, 140
	thread	"?", 0x5E, 0x3C, 0x00, 1405
	thread	"?", 0xFF, 0xCF, 0x7D, 141
	thread	"?", 0xFF, 0xB8, 0x3D, 142
	thread	"?", 0xFF, 0xA6, 0x26, 143
	thread	"?", 0xFF, 0x85, 0x00, 144
	thread	"?", 0xEB, 0x7C, 0x00, 145
	thread	"?", 0xAB, 0x61, 0x00, 146
	thread	"?", 0x70, 0x51, 0x00, 147
	thread	"?", 0xFF, 0xD6, 0xA1, 148
	thread	"?", 0xFF, 0xBA, 0x75, 1485
	thread	"?", 0xFF, 0xC4, 0x87, 149
	thread	"?", 0xFF, 0xAB, 0x54, 1495
	thread	"?", 0xFF, 0xA6, 0x4D, 150
	thread	"?", 0xFF, 0x94, 0x3B, 1505
	thread	"?", 0xFF, 0x85, 0x0D, 151
	thread	"?", 0xFC, 0x7C, 0x00, 152
	thread	"?", 0xE6, 0x60, 0x00, 1525
	thread	"?", 0xD1, 0x71, 0x00, 153
	thread	"?", 0x9E, 0x4A, 0x00, 1535
	thread	"?", 0xA8, 0x5B, 0x00, 154
	thread	"?", 0x47, 0x22, 0x00, 1545
	thread	"?", 0xFF, 0xE0, 0xB8, 155
	thread	"?", 0xFF, 0xC7, 0xA8, 1555
	thread	"?", 0xFF, 0xC7, 0x94, 156
	thread	"?", 0xFF, 0xA8, 0x82, 1565
	thread	"?", 0xFF, 0x91, 0x4D, 157
	thread	"?", 0xFF, 0x8C, 0x47, 1575
	thread	"?", 0xFF, 0x63, 0x08, 158
	thread	"?", 0xFF, 0x70, 0x1A, 1585
	thread	"?", 0xED, 0x51, 0x00, 159
	thread	"?", 0xF2, 0x63, 0x00, 1595
	thread	"?", 0xAD, 0x42, 0x00, 160
	thread	"?", 0xB3, 0x4F, 0x00, 1605
	thread	"?", 0x5C, 0x2C, 0x00, 161
	thread	"?", 0x91, 0x40, 0x00, 1615
	thread	"?", 0xFF, 0xD9, 0xC7, 162
	thread	"?", 0xFF, 0xB0, 0xA1, 1625
	thread	"?", 0xFF, 0xB0, 0x8F, 163
	thread	"?", 0xFF, 0x9C, 0x85, 1635
	thread	"?", 0xFF, 0x8A, 0x45, 164
	thread	"?", 0xFF, 0x82, 0x57, 1645
	thread	"?", 0xFF, 0x69, 0x0A, 165
	thread	"?", 0xFF, 0x5E, 0x17, 1655
	thread	"?", 0xFF, 0x5C, 0x00, 166
	thread	"?", 0xFF, 0x52, 0x00, 1665
	thread	"?", 0xD4, 0x55, 0x00, 167
	thread	"?", 0xB8, 0x3D, 0x00, 1675
	thread	"?", 0x69, 0x2D, 0x00, 168
	thread	"?", 0x8F, 0x2E, 0x00, 1685
	thread	"?", 0xFF, 0xCC, 0xCC, 169
	thread	"?", 0xFF, 0x99, 0x8F, 170
	thread	"?", 0xFF, 0x78, 0x52, 171
	thread	"?", 0xFF, 0x57, 0x1F, 172
	thread	"?", 0xF5, 0x4C, 0x00, 173
	thread	"?", 0xA3, 0x31, 0x00, 174
	thread	"?", 0x66, 0x24, 0x00, 175
	thread	"?", 0xFF, 0xBF, 0xD1, 176
	thread	"?", 0xFF, 0x9E, 0xC9, 1765
	thread	"?", 0xFF, 0xBA, 0xE0, 1767
	thread	"?", 0xFF, 0x8C, 0x99, 177
	thread	"?", 0xFF, 0x87, 0xB5, 1775
	thread	"?", 0xFF, 0x6B, 0xA3, 1777
	thread	"?", 0xFF, 0x69, 0x70, 178
	thread	"?", 0xFF, 0x54, 0x80, 1785
	thread	"?", 0xFF, 0x3D, 0x66, 1787
	thread	"?", 0xFF, 0x29, 0x1F, 1788
	thread	"?", 0xFF, 0x36, 0x00, 179
	thread	"?", 0xFF, 0x0F, 0x00, 1795
	thread	"?", 0xF5, 0x00, 0x02, 1797
	thread	"?", 0xE3, 0x30, 0x00, 180
	thread	"?", 0xC4, 0x12, 0x00, 1805
	thread	"?", 0xB8, 0x00, 0x07, 1807
	thread	"?", 0x87, 0x23, 0x00, 181
	thread	"?", 0x7D, 0x0C, 0x00, 1815
	thread	"?", 0x57, 0x09, 0x00, 1817
	thread	"?", 0xFF, 0xBD, 0xE6, 182
	thread	"?", 0xFF, 0x8A, 0xC9, 183
	thread	"?", 0xFF, 0x52, 0x96, 184
	thread	"?", 0xFF, 0x17, 0x3D, 185
	thread	"?", 0xF5, 0x00, 0x2F, 186
	thread	"?", 0xCC, 0x00, 0x2B, 187
	thread	"?", 0x80, 0x04, 0x00, 188
	thread	"?", 0xFF, 0xA1, 0xE6, 189
	thread	"?", 0xFF, 0xB8, 0xED, 1895
	thread	"?", 0xFF, 0x73, 0xC7, 190
	thread	"?", 0xFF, 0x96, 0xE8, 1905
	thread	"?", 0xFF, 0x3D, 0x9E, 191
	thread	"?", 0xFF, 0x4A, 0xCC, 1915
	thread	"?", 0xFF, 0x00, 0x52, 192
	thread	"?", 0xFF, 0x00, 0x73, 1925
	thread	"?", 0xDE, 0x00, 0x4B, 193
	thread	"?", 0xF2, 0x00, 0x68, 1935
	thread	"?", 0xAB, 0x00, 0x3E, 194
	thread	"?", 0xCF, 0x00, 0x5B, 1945
	thread	"?", 0x73, 0x00, 0x2E, 195
	thread	"?", 0xA1, 0x00, 0x40, 1955
	thread	"?", 0xFF, 0xBF, 0xF5, 196
	thread	"?", 0xFF, 0x8C, 0xE6, 197
	thread	"?", 0xFF, 0x38, 0xAB, 198
	thread	"?", 0xFF, 0x00, 0x61, 199
	thread	"?", 0xE0, 0x00, 0x53, 200
	thread	"?", 0xB5, 0x00, 0x43, 201
	thread	"?", 0x91, 0x00, 0x39, 202
	thread	"?", 0xFF, 0xA8, 0xF7, 203
	thread	"?", 0xFF, 0x6B, 0xF7, 204
	thread	"?", 0xFF, 0x29, 0xE8, 205
	thread	"?", 0xF7, 0x00, 0x99, 206
	thread	"?", 0xCF, 0x00, 0x76, 207
	thread	"?", 0xA1, 0x00, 0x67, 208
	thread	"?", 0x78, 0x00, 0x4F, 209
	thread	"?", 0xFF, 0x9C, 0xF0, 210
	thread	"?", 0xFF, 0x73, 0xEB, 211
	thread	"?", 0xFF, 0x47, 0xE3, 212
	thread	"?", 0xFF, 0x0D, 0xBA, 213
	thread	"?", 0xEB, 0x00, 0x9B, 214
	thread	"?", 0xBA, 0x00, 0x79, 215
	thread	"?", 0x82, 0x07, 0x4E, 216
	thread	"?", 0xFF, 0xB8, 0xFF, 217
	thread	"?", 0xFA, 0x63, 0xFF, 218
	thread	"?", 0xFC, 0x1F, 0xFF, 219
	thread	"?", 0xD4, 0x00, 0xB8, 220
	thread	"?", 0xB3, 0x00, 0x98, 221
	thread	"?", 0x69, 0x00, 0x5E, 222
	thread	"?", 0xFF, 0x8A, 0xFF, 223
	thread	"?", 0xFC, 0x5E, 0xFF, 224
	thread	"?", 0xFC, 0x2B, 0xFF, 225
	thread	"?", 0xFF, 0x00, 0xFF, 226
	thread	"?", 0xCF, 0x00, 0xC0, 227
	thread	"?", 0x96, 0x00, 0x90, 228
	thread	"?", 0x66, 0x00, 0x57, 229
	thread	"?", 0xFF, 0xA8, 0xFF, 230
	thread	"?", 0xFC, 0x7A, 0xFF, 231
	thread	"?", 0xF7, 0x54, 0xFF, 232
	thread	"?", 0xE3, 0x00, 0xFF, 233
	thread	"?", 0xB1, 0x00, 0xBD, 234
	thread	"?", 0x91, 0x00, 0x99, 235
	thread	"?", 0xFC, 0xB3, 0xFF, 236
	thread	"?", 0xFA, 0xBA, 0xFF, 2365
	thread	"?", 0xF7, 0x82, 0xFF, 237
	thread	"?", 0xE6, 0x6E, 0xFF, 2375
	thread	"?", 0xF0, 0x5E, 0xFF, 238
	thread	"?", 0xCF, 0x36, 0xFF, 2385
	thread	"?", 0xE3, 0x36, 0xFF, 239
	thread	"?", 0xBA, 0x0D, 0xFF, 2395
	thread	"?", 0xD1, 0x0F, 0xFF, 240
	thread	"?", 0xA8, 0x00, 0xFF, 2405
	thread	"?", 0xB6, 0x00, 0xFA, 241
	thread	"?", 0x9D, 0x00, 0xEB, 2415
	thread	"?", 0x75, 0x00, 0x82, 242
	thread	"?", 0x77, 0x00, 0xBD, 2425
	thread	"?", 0xF2, 0xB5, 0xFF, 243
	thread	"?", 0xE8, 0x9E, 0xFF, 244
	thread	"?", 0xDB, 0x78, 0xFF, 245
	thread	"?", 0xB5, 0x1A, 0xFF, 246
	thread	"?", 0xA3, 0x00, 0xFF, 247
	thread	"?", 0x96, 0x00, 0xFA, 248
	thread	"?", 0x6E, 0x00, 0xB8, 249
	thread	"?", 0xF2, 0xD1, 0xFF, 250
	thread	"?", 0xDE, 0x9C, 0xFF, 251
	thread	"?", 0xC2, 0x70, 0xFF, 252
	thread	"?", 0x91, 0x0D, 0xFF, 253
	thread	"?", 0x80, 0x00, 0xFF, 254
	thread	"?", 0x5E, 0x00, 0xBF, 255
	thread	"?", 0xED, 0xCC, 0xFF, 256
	thread	"?", 0xCF, 0xA6, 0xFF, 2562
	thread	"?", 0xC7, 0xAB, 0xFF, 2563
	thread	"?", 0xB5, 0xA3, 0xFF, 2567
	thread	"?", 0xDB, 0xA8, 0xFF, 257
	thread	"?", 0xB3, 0x87, 0xFF, 2572
	thread	"?", 0xB3, 0x91, 0xFF, 2573
	thread	"?", 0x99, 0x8C, 0xFF, 2577
	thread	"?", 0x91, 0x3D, 0xFF, 258
	thread	"?", 0x8A, 0x47, 0xFF, 2582
	thread	"?", 0x8A, 0x5E, 0xFF, 2583
	thread	"?", 0x69, 0x57, 0xFF, 2587
	thread	"?", 0x5F, 0x00, 0xD9, 259
	thread	"?", 0x66, 0x1A, 0xFF, 2592
	thread	"?", 0x63, 0x1C, 0xFF, 2593
	thread	"?", 0x26, 0x00, 0xFF, 2597
	thread	"?", 0x5B, 0x00, 0xBD, 260
	thread	"?", 0x5C, 0x00, 0xF7, 2602
	thread	"?", 0x4D, 0x00, 0xFA, 2603
	thread	"?", 0x2D, 0x00, 0xED, 2607
	thread	"?", 0x50, 0x00, 0x99, 261
	thread	"?", 0x4F, 0x00, 0xDB, 2612
	thread	"?", 0x50, 0x00, 0xD9, 2613
	thread	"?", 0x2E, 0x00, 0xD9, 2617
	thread	"?", 0x3F, 0x00, 0x73, 262
	thread	"?", 0x3C, 0x00, 0x8F, 2622
	thread	"?", 0x47, 0x00, 0xAD, 2623
	thread	"?", 0x28, 0x00, 0xB0, 2627
	thread	"?", 0xE6, 0xDB, 0xFF, 263
	thread	"?", 0xB8, 0xBA, 0xFF, 2635
	thread	"?", 0xBD, 0xB8, 0xFF, 264
	thread	"?", 0x99, 0xA3, 0xFF, 2645
	thread	"?", 0x75, 0x70, 0xFF, 265
	thread	"?", 0x75, 0x82, 0xFF, 2655
	thread	"?", 0x36, 0x1A, 0xFF, 266
	thread	"?", 0x61, 0x66, 0xFF, 2665
	thread	"?", 0x1C, 0x00, 0xFF, 267
	thread	"?", 0x28, 0x00, 0xE0, 268
	thread	"?", 0x09, 0x00, 0xE6, 2685
	thread	"?", 0x26, 0x00, 0xAB, 269
	thread	"?", 0x0C, 0x00, 0x82, 2695
	thread	"?", 0xB0, 0xBA, 0xFF, 270
	thread	"?", 0x99, 0xB3, 0xFF, 2705
	thread	"?", 0xCF, 0xE8, 0xFF, 2706
	thread	"?", 0xD4, 0xF0, 0xFF, 2707
	thread	"?", 0xBD, 0xE6, 0xFF, 2708
	thread	"?", 0x91, 0xA1, 0xFF, 271
	thread	"?", 0x6E, 0x8C, 0xFF, 2715
	thread	"?", 0x8C, 0xB5, 0xFF, 2716
	thread	"?", 0xB5, 0xE0, 0xFF, 2717
	thread	"?", 0x54, 0x96, 0xFF, 2718
	thread	"?", 0x6B, 0x85, 0xFF, 272
	thread	"?", 0x3B, 0x52, 0xFF, 2725
	thread	"?", 0x36, 0x57, 0xFF, 2726
	thread	"?", 0x4A, 0x94, 0xFF, 2727
	thread	"?", 0x0A, 0x4F, 0xFF, 2728
	thread	"?", 0x00, 0x09, 0xEB, 273
	thread	"?", 0x00, 0x0D, 0xFF, 2735
	thread	"?", 0x00, 0x17, 0xFF, 2736
	thread	"?", 0x00, 0x20, 0xFA, 2738
	thread	"?", 0x00, 0x00, 0xB8, 274
	thread	"?", 0x00, 0x0B, 0xD9, 2745
	thread	"?", 0x00, 0x12, 0xE6, 2746
	thread	"?", 0x00, 0x1E, 0xD9, 2747
	thread	"?", 0x00, 0x1A, 0xD9, 2748
	thread	"?", 0x03, 0x00, 0x91, 275
	thread	"?", 0x00, 0x05, 0xB3, 2755
	thread	"?", 0x00, 0x0B, 0xB5, 2756
	thread	"?", 0x00, 0x20, 0xB3, 2757
	thread	"?", 0x00, 0x26, 0xBD, 2758
	thread	"?", 0x02, 0x00, 0x73, 276
	thread	"?", 0x00, 0x04, 0x8C, 2765
	thread	"?", 0x00, 0x08, 0x87, 2766
	thread	"?", 0x00, 0x1A, 0x75, 2767
	thread	"?", 0x00, 0x1F, 0x8F, 2768
	thread	"?", 0xBA, 0xED, 0xFF, 277
	thread	"?", 0x9C, 0xDB, 0xFF, 278
	thread	"?", 0x52, 0xA8, 0xFF, 279
	thread	"?", 0x00, 0x3B, 0xD1, 280
	thread	"?", 0x00, 0x31, 0xAD, 281
	thread	"?", 0x00, 0x26, 0x75, 282
	thread	"?", 0xA6, 0xE8, 0xFF, 283
	thread	"?", 0x73, 0xCF, 0xFF, 284
	thread	"?", 0x1C, 0x91, 0xFF, 285
	thread	"?", 0x00, 0x55, 0xFA, 286
	thread	"?", 0x00, 0x48, 0xE0, 287
	thread	"?", 0x00, 0x41, 0xC4, 288
	thread	"?", 0x00, 0x24, 0x6B, 289
	thread	"?", 0xBF, 0xFA, 0xFF, 290
	thread	"?", 0x96, 0xFA, 0xFF, 2905
	thread	"?", 0xAB, 0xF7, 0xFF, 291
	thread	"?", 0x69, 0xED, 0xFF, 2915
	thread	"?", 0x82, 0xE3, 0xFF, 292
	thread	"?", 0x26, 0xC2, 0xFF, 2925
	thread	"?", 0x00, 0x6B, 0xFA, 293
	thread	"?", 0x00, 0x8A, 0xFF, 2935
	thread	"?", 0x00, 0x55, 0xC9, 294
	thread	"?", 0x00, 0x79, 0xDB, 2945
	thread	"?", 0x00, 0x45, 0xA1, 295
	thread	"?", 0x00, 0x58, 0xA1, 2955
	thread	"?", 0x00, 0x29, 0x4D, 296
	thread	"?", 0x00, 0x39, 0x5C, 2965
	thread	"?", 0x82, 0xFC, 0xFF, 297
	thread	"?", 0xB3, 0xFF, 0xF2, 2975
	thread	"?", 0x4F, 0xED, 0xFF, 298
	thread	"?", 0x69, 0xFF, 0xF0, 2985
	thread	"?", 0x26, 0xCF, 0xFF, 299
	thread	"?", 0x1A, 0xE3, 0xFF, 2995
	thread	"?", 0x00, 0x8F, 0xFF, 300
	thread	"?", 0x00, 0xA0, 0xFA, 3005
	thread	"?", 0x00, 0x73, 0xD1, 301
	thread	"?", 0x00, 0x89, 0xCC, 3015
	thread	"?", 0x00, 0x60, 0x80, 302
	thread	"?", 0x00, 0x68, 0x7D, 3025
	thread	"?", 0x00, 0x3B, 0x42, 303
	thread	"?", 0x00, 0x47, 0x44, 3035
	thread	"?", 0xB3, 0xFF, 0xEB, 304
	thread	"?", 0x7D, 0xFF, 0xE8, 305
	thread	"?", 0x40, 0xFF, 0xED, 306
	thread	"?", 0x00, 0x9C, 0xBA, 307
	thread	"?", 0x00, 0x80, 0x87, 308
	thread	"?", 0x00, 0x47, 0x41, 309
	thread	"?", 0x91, 0xFF, 0xE6, 310
	thread	"?", 0x91, 0xFF, 0xE0, 3105
	thread	"?", 0x5E, 0xFF, 0xE0, 311
	thread	"?", 0x5E, 0xFF, 0xD1, 3115
	thread	"?", 0x0A, 0xFF, 0xE3, 312
	thread	"?", 0x2B, 0xFF, 0xC9, 3125
	thread	"?", 0x00, 0xDE, 0xCC, 313
	thread	"?", 0x00, 0xE8, 0xC3, 3135
	thread	"?", 0x00, 0xB3, 0xA2, 314
	thread	"?", 0x00, 0xC4, 0x9F, 3145
	thread	"?", 0x00, 0x91, 0x80, 315
	thread	"?", 0x00, 0x9E, 0x78, 3155
	thread	"?", 0x00, 0x52, 0x3C, 316
	thread	"?", 0x00, 0x59, 0x40, 3165
	thread	"?", 0xD1, 0xFF, 0xEB, 317
	thread	"?", 0x9E, 0xFF, 0xD9, 318
	thread	"?", 0x7A, 0xFF, 0xCF, 319
	thread	"?", 0x00, 0xED, 0xA4, 320
	thread	"?", 0x00, 0xC4, 0x87, 321
	thread	"?", 0x00, 0xA6, 0x6F, 322
	thread	"?", 0x00, 0x87, 0x54, 323
	thread	"?", 0xB8, 0xFF, 0xE0, 324
	thread	"?", 0xA1, 0xFF, 0xD1, 3242
	thread	"?", 0xA8, 0xFF, 0xCF, 3245
	thread	"?", 0x91, 0xFF, 0xC2, 3248
	thread	"?", 0x70, 0xFF, 0xBD, 325
	thread	"?", 0x87, 0xFF, 0xC2, 3252
	thread	"?", 0x82, 0xFF, 0xB8, 3255
	thread	"?", 0x69, 0xFF, 0xAB, 3258
	thread	"?", 0x21, 0xFF, 0x9E, 326
	thread	"?", 0x4A, 0xFF, 0xAB, 3262
	thread	"?", 0x4F, 0xFF, 0xA1, 3265
	thread	"?", 0x1A, 0xFF, 0x82, 3268
	thread	"?", 0x00, 0xD4, 0x77, 327
	thread	"?", 0x00, 0xFF, 0x8F, 3272
	thread	"?", 0x0D, 0xFF, 0x87, 3275
	thread	"?", 0x00, 0xF2, 0x6D, 3278
	thread	"?", 0x00, 0xAD, 0x5F, 328
	thread	"?", 0x00, 0xD9, 0x75, 3282
	thread	"?", 0x00, 0xED, 0x77, 3285
	thread	"?", 0x00, 0xCC, 0x5E, 3288
	thread	"?", 0x00, 0x8A, 0x4A, 329
	thread	"?", 0x00, 0x8A, 0x46, 3292
	thread	"?", 0x00, 0xC9, 0x5F, 3295
	thread	"?", 0x00, 0x94, 0x40, 3298
	thread	"?", 0x00, 0x66, 0x35, 330
	thread	"?", 0x00, 0x4F, 0x24, 3302
	thread	"?", 0x00, 0x63, 0x27, 3305
	thread	"?", 0x00, 0x47, 0x1D, 3308
	thread	"?", 0xC2, 0xFF, 0xD6, 331
	thread	"?", 0xB3, 0xFF, 0xCC, 332
	thread	"?", 0x91, 0xFF, 0xBA, 333
	thread	"?", 0x00, 0xF7, 0x63, 334
	thread	"?", 0x00, 0xB3, 0x3E, 335
	thread	"?", 0x00, 0x87, 0x2D, 336
	thread	"?", 0xB0, 0xFF, 0xCC, 337
	thread	"?", 0xA6, 0xFF, 0xBF, 3375
	thread	"?", 0x87, 0xFF, 0xAD, 338
	thread	"?", 0x8C, 0xFF, 0xAB, 3385
	thread	"?", 0x29, 0xFF, 0x70, 339
	thread	"?", 0x63, 0xFF, 0x8C, 3395
	thread	"?", 0x00, 0xE8, 0x4F, 340
	thread	"?", 0x26, 0xFF, 0x59, 3405
	thread	"?", 0x00, 0xB5, 0x3C, 341
	thread	"?", 0x00, 0xC7, 0x2E, 3415
	thread	"?", 0x00, 0x91, 0x2A, 342
	thread	"?", 0x00, 0x94, 0x21, 3425
	thread	"?", 0x02, 0x63, 0x1C, 343
	thread	"?", 0x00, 0x57, 0x10, 3435
	thread	"?", 0xBA, 0xFF, 0xC4, 344
	thread	"?", 0x9E, 0xFF, 0xAD, 345
	thread	"?", 0x73, 0xFF, 0x87, 346
	thread	"?", 0x00, 0xF7, 0x23, 347
	thread	"?", 0x00, 0xC2, 0x1D, 348
	thread	"?", 0x00, 0x94, 0x0D, 349
	thread	"?", 0x0D, 0x40, 0x00, 350
	thread	"?", 0xD4, 0xFF, 0xD6, 351
	thread	"?", 0xBA, 0xFF, 0xBF, 352
	thread	"?", 0x9E, 0xFF, 0xA3, 353
	thread	"?", 0x33, 0xFF, 0x1A, 354
	thread	"?", 0x0F, 0xFF, 0x00, 355
	thread	"?", 0x09, 0xBA, 0x00, 356
	thread	"?", 0x16, 0x70, 0x00, 357
	thread	"?", 0xBA, 0xFF, 0x9E, 358
	thread	"?", 0xA3, 0xFF, 0x82, 359
	thread	"?", 0x6B, 0xFF, 0x33, 360
	thread	"?", 0x4F, 0xFF, 0x00, 361
	thread	"?", 0x46, 0xE8, 0x00, 362
	thread	"?", 0x3E, 0xC2, 0x00, 363
	thread	"?", 0x34, 0x94, 0x00, 364
	thread	"?", 0xE0, 0xFF, 0xB5, 365
	thread	"?", 0xCC, 0xFF, 0x8F, 366
	thread	"?", 0xAD, 0xFF, 0x69, 367
	thread	"?", 0x6E, 0xFF, 0x00, 368
	thread	"?", 0x61, 0xED, 0x00, 369
	thread	"?", 0x52, 0xBA, 0x00, 370
	thread	"?", 0x40, 0x70, 0x00, 371
	thread	"?", 0xE6, 0xFF, 0xAB, 372
	thread	"?", 0xD6, 0xFF, 0x8A, 373
	thread	"?", 0xC2, 0xFF, 0x6E, 374
	thread	"?", 0x96, 0xFF, 0x38, 375
	thread	"?", 0x74, 0xF2, 0x00, 376
	thread	"?", 0x6B, 0xC2, 0x00, 377
	thread	"?", 0x43, 0x66, 0x00, 378
	thread	"?", 0xE8, 0xFF, 0x6B, 379
	thread	"?", 0xDE, 0xFF, 0x47, 380
	thread	"?", 0xCC, 0xFF, 0x17, 381
	thread	"?", 0xB5, 0xFF, 0x00, 382
	thread	"?", 0xA5, 0xCF, 0x00, 383
	thread	"?", 0x90, 0xB0, 0x00, 384
	thread	"?", 0x68, 0x6B, 0x00, 385
	thread	"?", 0xF0, 0xFF, 0x70, 386
	thread	"?", 0xE6, 0xFF, 0x42, 387
	thread	"?", 0xDB, 0xFF, 0x36, 388
	thread	"?", 0xCC, 0xFF, 0x26, 389
	thread	"?", 0xB7, 0xEB, 0x00, 390
	thread	"?", 0x95, 0xAB, 0x00, 391
	thread	"?", 0x79, 0x82, 0x00, 392
	thread	"?", 0xF7, 0xFF, 0x73, 393
	thread	"?", 0xFC, 0xFF, 0x52, 3935
	thread	"?", 0xF0, 0xFF, 0x3D, 394
	thread	"?", 0xF7, 0xFF, 0x26, 3945
	thread	"?", 0xEB, 0xFF, 0x26, 395
	thread	"?", 0xF0, 0xFF, 0x00, 3955
	thread	"?", 0xE3, 0xFF, 0x0F, 396
	thread	"?", 0xEB, 0xFF, 0x00, 3965
	thread	"?", 0xCC, 0xE3, 0x00, 397
	thread	"?", 0xB5, 0xB5, 0x00, 3975
	thread	"?", 0xAB, 0xB8, 0x00, 398
	thread	"?", 0x96, 0x92, 0x00, 3985
	thread	"?", 0x91, 0x91, 0x00, 399
	thread	"?", 0x5C, 0x59, 0x00, 3995
	thread	"?", 0xD6, 0xD0, 0xC9, 400
	thread	"?", 0xC4, 0xBB, 0xAF, 401
	thread	"?", 0xB0, 0xA5, 0x97, 402
	thread	"?", 0x91, 0x87, 0x79, 403
	thread	"?", 0x70, 0x67, 0x58, 404
	thread	"?", 0x47, 0x40, 0x30, 405
	thread	"?", 0xD6, 0xCB, 0xC9, 406
	thread	"?", 0xBD, 0xAE, 0xAC, 407
	thread	"?", 0xA8, 0x97, 0x96, 408
	thread	"?", 0x8C, 0x7A, 0x77, 409
	thread	"?", 0x70, 0x5C, 0x59, 410
	thread	"?", 0x47, 0x34, 0x2E, 411
	thread	"?", 0x05, 0x04, 0x02, 412
	thread	"?", 0xCC, 0xCC, 0xBA, 413
	thread	"?", 0xB3, 0xB3, 0xA1, 414
	thread	"?", 0x96, 0x96, 0x84, 415
	thread	"?", 0x80, 0x80, 0x6B, 416
	thread	"?", 0x58, 0x59, 0x43, 417
	thread	"?", 0x3E, 0x40, 0x2C, 418
	thread	"?", 0x00, 0x00, 0x00, 419
	thread	"?", 0xD9, 0xD9, 0xD9, 420
	thread	"?", 0xBD, 0xBD, 0xBD, 421
	thread	"?", 0xAB, 0xAB, 0xAB, 422
	thread	"?", 0x8F, 0x8F, 0x8F, 423
	thread	"?", 0x63, 0x63, 0x63, 424
	thread	"?", 0x3B, 0x3B, 0x3B, 425
	thread	"?", 0x00, 0x00, 0x00, 426
	thread	"?", 0xE3, 0xE3, 0xE3, 427
	thread	"?", 0xCD, 0xD1, 0xD1, 428
	thread	"?", 0xA8, 0xAD, 0xAD, 429
	thread	"?", 0x85, 0x8C, 0x8C, 430
	thread	"?", 0x52, 0x5B, 0x5C, 431
	thread	"?", 0x2D, 0x39, 0x3B, 432
	thread	"?", 0x09, 0x0C, 0x0D, 433
	thread	"?", 0xED, 0xE6, 0xE8, 434
	thread	"?", 0xDE, 0xD6, 0xDB, 435
	thread	"?", 0xC2, 0xBF, 0xBF, 436
	thread	"?", 0x8A, 0x8C, 0x8A, 437
	thread	"?", 0x39, 0x45, 0x00, 438
	thread	"?", 0x29, 0x33, 0x00, 439
	thread	"?", 0x20, 0x27, 0x00, 440
	thread	"?", 0xDA, 0xE8, 0xD8, 441
	thread	"?", 0xBE, 0xCF, 0xBC, 442
	thread	"?", 0x9D, 0xB3, 0x9D, 443
	thread	"?", 0x7E, 0x94, 0x7E, 444
	thread	"?", 0x47, 0x59, 0x47, 445
	thread	"?", 0x32, 0x40, 0x31, 446
	thread	"?", 0x27, 0x2E, 0x20, 447
	thread	"?", 0x2D, 0x3E, 0x00, 448
	thread	"?", 0x4F, 0x3A, 0x00, 4485
	thread	"?", 0x3D, 0x52, 0x00, 449
	thread	"?", 0x8A, 0x6E, 0x07, 4495
	thread	"?", 0x50, 0x67, 0x00, 450
	thread	"?", 0xA3, 0x8B, 0x24, 4505
	thread	"?", 0xAB, 0xB5, 0x73, 451
	thread	"?", 0xC2, 0xB0, 0x61, 4515
	thread	"?", 0xC2, 0xCF, 0x9C, 452
	thread	"?", 0xD4, 0xC5, 0x81, 4525
	thread	"?", 0xDB, 0xE3, 0xBF, 453
	thread	"?", 0xE3, 0xDA, 0x9F, 4535
	thread	"?", 0xE8, 0xED, 0xD6, 454
	thread	"?", 0xF0, 0xE9, 0xC2, 4545
	thread	"?", 0x59, 0x4A, 0x00, 455
	thread	"?", 0x91, 0x7C, 0x00, 456
	thread	"?", 0xB8, 0x9C, 0x00, 457
	thread	"?", 0xE6, 0xE6, 0x45, 458
	thread	"?", 0xF0, 0xED, 0x73, 459
	thread	"?", 0xF5, 0xF2, 0x8F, 460
	thread	"?", 0xF7, 0xF7, 0xA6, 461
	thread	"?", 0x40, 0x26, 0x00, 462
	thread	"?", 0x36, 0x15, 0x00, 4625
	thread	"?", 0x6B, 0x3D, 0x00, 463
	thread	"?", 0x8F, 0x4A, 0x06, 4635
	thread	"?", 0x95, 0x53, 0x00, 464
	thread	"?", 0xB8, 0x74, 0x3B, 4645
	thread	"?", 0xCC, 0xAD, 0x6B, 465
	thread	"?", 0xD1, 0x9B, 0x73, 4655
	thread	"?", 0xE0, 0xC7, 0x91, 466
	thread	"?", 0xE6, 0xBC, 0x9C, 4665
	thread	"?", 0xE8, 0xD9, 0xA8, 467
	thread	"?", 0xF0, 0xD5, 0xBD, 4675
	thread	"?", 0xF0, 0xE8, 0xC4, 468
	thread	"?", 0xF5, 0xE4, 0xD3, 4685
	thread	"?", 0x4A, 0x1A, 0x00, 469
	thread	"?", 0x42, 0x0D, 0x00, 4695
	thread	"?", 0xAB, 0x48, 0x00, 470
	thread	"?", 0x82, 0x31, 0x26, 4705
	thread	"?", 0xD1, 0x56, 0x00, 471
	thread	"?", 0xA8, 0x62, 0x5D, 4715
	thread	"?", 0xFF, 0xA8, 0x7A, 472
	thread	"?", 0xBF, 0x82, 0x7C, 4725
	thread	"?", 0xFF, 0xC4, 0xA3, 473
	thread	"?", 0xD9, 0xA9, 0xA7, 4735
	thread	"?", 0xFF, 0xD9, 0xBD, 474
	thread	"?", 0xE6, 0xBE, 0xBC, 4745
	thread	"?", 0xFF, 0xE3, 0xCC, 475
	thread	"?", 0xF0, 0xD8, 0xD3, 4755
	thread	"?", 0x38, 0x1C, 0x00, 476
	thread	"?", 0x4F, 0x18, 0x00, 477
	thread	"?", 0x6B, 0x12, 0x00, 478
	thread	"?", 0xB0, 0x85, 0x73, 479
	thread	"?", 0xD9, 0xB5, 0xB0, 480
	thread	"?", 0xE8, 0xCF, 0xC9, 481
	thread	"?", 0xF2, 0xE0, 0xDE, 482
	thread	"?", 0x66, 0x07, 0x00, 483
	thread	"?", 0xB5, 0x09, 0x00, 484
	thread	"?", 0xFF, 0x0D, 0x00, 485
	thread	"?", 0xFF, 0x87, 0x96, 486
	thread	"?", 0xFF, 0xA6, 0xB8, 487
	thread	"?", 0xFF, 0xBD, 0xCF, 488
	thread	"?", 0xFF, 0xD9, 0xE3, 489
	thread	"?", 0x47, 0x13, 0x00, 490
	thread	"?", 0x7A, 0x1A, 0x00, 491
	thread	"?", 0x94, 0x22, 0x00, 492
	thread	"?", 0xF2, 0x83, 0xBB, 493
	thread	"?", 0xFF, 0xAB, 0xDE, 494
	thread	"?", 0xFF, 0xC2, 0xE3, 495
	thread	"?", 0xFF, 0xD6, 0xE8, 496
	thread	"?", 0x38, 0x11, 0x00, 497
	thread	"?", 0x33, 0x0E, 0x00, 4975
	thread	"?", 0x66, 0x25, 0x00, 498
	thread	"?", 0x85, 0x32, 0x41, 4985
	thread	"?", 0x85, 0x31, 0x00, 499
	thread	"?", 0xA8, 0x58, 0x68, 4995
	thread	"?", 0xE3, 0x8D, 0xB3, 500
	thread	"?", 0xC4, 0x7A, 0x8F, 5005
	thread	"?", 0xF7, 0xB5, 0xD7, 501
	thread	"?", 0xE3, 0xAA, 0xC1, 5015
	thread	"?", 0xFC, 0xCF, 0xE3, 502
	thread	"?", 0xED, 0xC2, 0xD1, 5025
	thread	"?", 0xFF, 0xE3, 0xEB, 503
	thread	"?", 0xF7, 0xDF, 0xE1, 5035
	thread	"?", 0x32, 0x00, 0x00, 504
	thread	"?", 0x60, 0x00, 0x00, 505
	thread	"?", 0x77, 0x00, 0x00, 506
	thread	"?", 0xDE, 0x82, 0xC4, 507
	thread	"?", 0xF2, 0xA3, 0xE3, 508
	thread	"?", 0xFF, 0xC2, 0xED, 509
	thread	"?", 0xFF, 0xD4, 0xF0, 510
	thread	"?", 0x3D, 0x00, 0x66, 511
	thread	"?", 0x2B, 0x00, 0x41, 5115
	thread	"?", 0x61, 0x00, 0xCE, 512
	thread	"?", 0x59, 0x24, 0x82, 5125
	thread	"?", 0x8A, 0x1F, 0xFF, 513
	thread	"?", 0x82, 0x57, 0xB8, 5135
	thread	"?", 0xD9, 0x80, 0xFF, 514
	thread	"?", 0xB3, 0x8C, 0xE0, 5145
	thread	"?", 0xED, 0x9E, 0xFF, 515
	thread	"?", 0xD4, 0xB3, 0xEB, 5155
	thread	"?", 0xF7, 0xBA, 0xFF, 516
	thread	"?", 0xE8, 0xCF, 0xF2, 5165
	thread	"?", 0xFF, 0xD1, 0xFF, 517
	thread	"?", 0xF2, 0xE0, 0xF7, 5175
	thread	"?", 0x2E, 0x00, 0x5C, 518
	thread	"?", 0x1C, 0x00, 0x22, 5185
	thread	"?", 0x44, 0x00, 0x9D, 519
	thread	"?", 0x3D, 0x0C, 0x4E, 5195
	thread	"?", 0x5C, 0x00, 0xE0, 520
	thread	"?", 0x7A, 0x5E, 0x85, 5205
	thread	"?", 0xBA, 0x87, 0xFF, 521
	thread	"?", 0xB5, 0x9E, 0xC2, 5215
	thread	"?", 0xD4, 0xA1, 0xFF, 522
	thread	"?", 0xD4, 0xBA, 0xD9, 5225
	thread	"?", 0xE6, 0xBD, 0xFF, 523
	thread	"?", 0xE6, 0xD4, 0xE6, 5235
	thread	"?", 0xF0, 0xD9, 0xFF, 524
	thread	"?", 0xF0, 0xE6, 0xED, 5245
	thread	"?", 0x27, 0x00, 0x85, 525
	thread	"?", 0x0D, 0x0B, 0x4D, 5255
	thread	"?", 0x3B, 0x00, 0xED, 526
	thread	"?", 0x20, 0x25, 0x8A, 5265
	thread	"?", 0x45, 0x00, 0xFF, 527
	thread	"?", 0x38, 0x48, 0xA8, 5275
	thread	"?", 0x96, 0x73, 0xFF, 528
	thread	"?", 0x72, 0x80, 0xC4, 5285
	thread	"?", 0xBD, 0x99, 0xFF, 529
	thread	"?", 0xA8, 0xB3, 0xE6, 5295
	thread	"?", 0xD1, 0xB0, 0xFF, 530
	thread	"?", 0xC7, 0xCE, 0xED, 5305
	thread	"?", 0xE6, 0xCC, 0xFF, 531
	thread	"?", 0xE4, 0xE4, 0xF2, 5315
	thread	"?", 0x00, 0x19, 0x3F, 532
	thread	"?", 0x00, 0x22, 0x7B, 533
	thread	"?", 0x00, 0x2C, 0xAA, 534
	thread	"?", 0x94, 0xB3, 0xED, 535
	thread	"?", 0xB0, 0xC7, 0xF2, 536
	thread	"?", 0xC7, 0xDB, 0xF7, 537
	thread	"?", 0xDE, 0xE8, 0xFA, 538
	thread	"?", 0x00, 0x27, 0x4D, 539
	thread	"?", 0x00, 0x22, 0x3D, 5395
	thread	"?", 0x00, 0x34, 0x73, 540
	thread	"?", 0x3A, 0x72, 0x8A, 5405
	thread	"?", 0x00, 0x44, 0x9E, 541
	thread	"?", 0x5A, 0x8A, 0x96, 5415
	thread	"?", 0x5E, 0xC1, 0xF7, 542
	thread	"?", 0x79, 0xA6, 0xAD, 5425
	thread	"?", 0x96, 0xE3, 0xFF, 543
	thread	"?", 0xB8, 0xCD, 0xD4, 5435
	thread	"?", 0xB3, 0xF0, 0xFF, 544
	thread	"?", 0xCC, 0xDC, 0xDE, 5445
	thread	"?", 0xC7, 0xF7, 0xFF, 545
	thread	"?", 0xDA, 0xE8, 0xE8, 5455
	thread	"?", 0x02, 0x27, 0x2B, 546
	thread	"?", 0x00, 0x2B, 0x24, 5463
	thread	"?", 0x00, 0x0D, 0x09, 5467
	thread	"?", 0x00, 0x34, 0x40, 547
	thread	"?", 0x16, 0x7A, 0x58, 5473
	thread	"?", 0x1D, 0x42, 0x30, 5477
	thread	"?", 0x00, 0x46, 0x5C, 548
	thread	"?", 0x43, 0xB0, 0x8B, 5483
	thread	"?", 0x48, 0x70, 0x5D, 5487
	thread	"?", 0x56, 0xAD, 0xBA, 549
	thread	"?", 0x73, 0xC9, 0xAD, 5493
	thread	"?", 0x82, 0x9E, 0x90, 5497
	thread	"?", 0x7B, 0xC1, 0xC9, 550
	thread	"?", 0x9C, 0xDB, 0xC5, 5503
	thread	"?", 0xA1, 0xB5, 0xA8, 5507
	thread	"?", 0xA2, 0xD7, 0xDE, 551
	thread	"?", 0xC7, 0xF2, 0xE1, 5513
	thread	"?", 0xBE, 0xD1, 0xC5, 5517
	thread	"?", 0xC5, 0xE8, 0xE8, 552
	thread	"?", 0xDC, 0xF7, 0xEB, 5523
	thread	"?", 0xD5, 0xE3, 0xDA, 5527
	thread	"?", 0x14, 0x33, 0x19, 553
	thread	"?", 0x10, 0x2E, 0x14, 5535
	thread	"?", 0x11, 0x54, 0x22, 554
	thread	"?", 0x32, 0x7A, 0x3D, 5545
	thread	"?", 0x18, 0x70, 0x31, 555
	thread	"?", 0x5A, 0x9E, 0x68, 5555
	thread	"?", 0x66, 0xBA, 0x80, 556
	thread	"?", 0x84, 0xBD, 0x8F, 5565
	thread	"?", 0x98, 0xD9, 0xAD, 557
	thread	"?", 0xA9, 0xD4, 0xB2, 5575
	thread	"?", 0xBA, 0xE8, 0xCA, 558
	thread	"?", 0xCA, 0xE6, 0xCC, 5585
	thread	"?", 0xCE, 0xF0, 0xD8, 559
	thread	"?", 0xDD, 0xED, 0xDA, 5595
	thread	"?", 0x0D, 0x40, 0x18, 560
	thread	"?", 0x05, 0x0F, 0x07, 5605
	thread	"?", 0x12, 0x7A, 0x38, 561
	thread	"?", 0x2E, 0x52, 0x2B, 5615
	thread	"?", 0x1A, 0xB0, 0x58, 562
	thread	"?", 0x5A, 0x7D, 0x57, 5625
	thread	"?", 0x79, 0xFC, 0xAC, 563
	thread	"?", 0x89, 0xA3, 0x86, 5635
	thread	"?", 0xA1, 0xFF, 0xCC, 564
	thread	"?", 0xAE, 0xBF, 0xA6, 5645
	thread	"?", 0xC4, 0xFF, 0xDE, 565
	thread	"?", 0xC5, 0xD1, 0xBE, 5655
	thread	"?", 0xDB, 0xFF, 0xE8, 566
	thread	"?", 0xDA, 0xE6, 0xD5, 5665
	thread	"?", 0x0E, 0x4D, 0x1C, 567
	thread	"?", 0x14, 0xA3, 0x46, 568
	thread	"?", 0x04, 0xD4, 0x5B, 569
	thread	"?", 0x85, 0xFF, 0xB5, 570
	thread	"?", 0xAD, 0xFF, 0xCF, 571
	thread	"?", 0xC4, 0xFF, 0xDB, 572
	thread	"?", 0xDB, 0xFF, 0xE8, 573
	thread	"?", 0x31, 0x4A, 0x0E, 574
	thread	"?", 0x1F, 0x2E, 0x07, 5743
	thread	"?", 0x24, 0x36, 0x00, 5747
	thread	"?", 0x3E, 0x78, 0x00, 575
	thread	"?", 0x3F, 0x54, 0x10, 5753
	thread	"?", 0x54, 0x73, 0x06, 5757
	thread	"?", 0x4F, 0x9C, 0x00, 576
	thread	"?", 0x5C, 0x6E, 0x1D, 5763
	thread	"?", 0x84, 0x9C, 0x32, 5767
	thread	"?", 0xAE, 0xE6, 0x7C, 577
	thread	"?", 0x90, 0x9E, 0x5A, 5773
	thread	"?", 0xA5, 0xB8, 0x5E, 5777
	thread	"?", 0xC0, 0xF0, 0x90, 578
	thread	"?", 0xAF, 0xBA, 0x86, 5783
	thread	"?", 0xCE, 0xDE, 0x99, 5787
	thread	"?", 0xCD, 0xF7, 0xA3, 579
	thread	"?", 0xC9, 0xD1, 0xA5, 5793
	thread	"?", 0xDC, 0xE8, 0xB0, 5797
	thread	"?", 0xDC, 0xFA, 0xB9, 580
	thread	"?", 0xDE, 0xE3, 0xC8, 5803
	thread	"?", 0xE9, 0xF0, 0xCE, 5807
	thread	"?", 0x46, 0x47, 0x00, 581
	thread	"?", 0x36, 0x36, 0x05, 5815
	thread	"?", 0x78, 0x8A, 0x00, 582
	thread	"?", 0x69, 0x66, 0x0E, 5825
	thread	"?", 0xA3, 0xD4, 0x00, 583
	thread	"?", 0x99, 0x96, 0x32, 5835
	thread	"?", 0xD3, 0xF0, 0x32, 584
	thread	"?", 0xB3, 0xB1, 0x5F, 5845
	thread	"?", 0xDE, 0xFA, 0x55, 585
	thread	"?", 0xD1, 0xD1, 0x90, 5855
	thread	"?", 0xE8, 0xFF, 0x78, 586
	thread	"?", 0xDE, 0xDE, 0xA6, 5865
	thread	"?", 0xF2, 0xFF, 0x99, 587
	thread	"?", 0xEB, 0xEB, 0xC0, 5875
	thread	"?", 0xFF, 0xFF, 0xB5, 600
	thread	"?", 0xFF, 0xFF, 0x99, 601
	thread	"?", 0xFF, 0xFF, 0x7D, 602
	thread	"?", 0xFC, 0xFC, 0x4E, 603
	thread	"?", 0xF7, 0xF7, 0x1E, 604
	thread	"?", 0xED, 0xE8, 0x00, 605
	thread	"?", 0xE0, 0xD7, 0x00, 606
	thread	"?", 0xFC, 0xFC, 0xCF, 607
	thread	"?", 0xFA, 0xFA, 0xAA, 608
	thread	"?", 0xF5, 0xF5, 0x84, 609
	thread	"?", 0xF0, 0xF0, 0x65, 610
	thread	"?", 0xE3, 0xE1, 0x12, 611
	thread	"?", 0xCC, 0xC8, 0x00, 612
	thread	"?", 0xB3, 0xAB, 0x00, 613
	thread	"?", 0xF5, 0xF5, 0xC4, 614
	thread	"?", 0xF0, 0xED, 0xAF, 615
	thread	"?", 0xE8, 0xE3, 0x97, 616
	thread	"?", 0xD4, 0xCF, 0x6E, 617
	thread	"?", 0xB3, 0xAD, 0x17, 618
	thread	"?", 0x91, 0x8C, 0x00, 619
	thread	"?", 0x78, 0x72, 0x00, 620
	thread	"?", 0xD9, 0xFA, 0xE1, 621
	thread	"?", 0xBA, 0xF5, 0xC6, 622
	thread	"?", 0x9C, 0xE6, 0xAE, 623
	thread	"?", 0x72, 0xCC, 0x85, 624
	thread	"?", 0x4B, 0xAB, 0x60, 625
	thread	"?", 0x17, 0x5E, 0x22, 626
	thread	"?", 0x04, 0x29, 0x0A, 627
	thread	"?", 0xCF, 0xFF, 0xF0, 628
	thread	"?", 0xA8, 0xFF, 0xE8, 629
	thread	"?", 0x87, 0xFF, 0xE3, 630
	thread	"?", 0x52, 0xFA, 0xDC, 631
	thread	"?", 0x13, 0xF2, 0xCE, 632
	thread	"?", 0x00, 0xBF, 0xAC, 633
	thread	"?", 0x00, 0x99, 0x8B, 634
	thread	"?", 0xAD, 0xFF, 0xEB, 635
	thread	"?", 0x8C, 0xFF, 0xE8, 636
	thread	"?", 0x73, 0xFF, 0xE8, 637
	thread	"?", 0x2B, 0xFF, 0xE6, 638
	thread	"?", 0x00, 0xF2, 0xE6, 639
	thread	"?", 0x00, 0xC7, 0xC7, 640
	thread	"?", 0x00, 0xAB, 0xB3, 641
	thread	"?", 0xD2, 0xF0, 0xFA, 642
	thread	"?", 0xB8, 0xE4, 0xF5, 643
	thread	"?", 0x8B, 0xCC, 0xF0, 644
	thread	"?", 0x64, 0xA7, 0xE8, 645
	thread	"?", 0x46, 0x96, 0xE3, 646
	thread	"?", 0x00, 0x56, 0xC4, 647
	thread	"?", 0x00, 0x2D, 0x75, 648
	thread	"?", 0xD9, 0xED, 0xFC, 649
	thread	"?", 0xBE, 0xE3, 0xFA, 650
	thread	"?", 0x95, 0xC5, 0xF0, 651
	thread	"?", 0x5C, 0x97, 0xE6, 652
	thread	"?", 0x00, 0x4E, 0xCC, 653
	thread	"?", 0x00, 0x39, 0x9E, 654
	thread	"?", 0x00, 0x2B, 0x7A, 655
	thread	"?", 0xDB, 0xF5, 0xFF, 656
	thread	"?", 0xC2, 0xEB, 0xFF, 657
	thread	"?", 0x96, 0xCC, 0xFF, 658
	thread	"?", 0x5C, 0xA6, 0xFF, 659
	thread	"?", 0x1A, 0x6E, 0xFF, 660
	thread	"?", 0x00, 0x48, 0xE8, 661
	thread	"?", 0x00, 0x3B, 0xD1, 662
	thread	"?", 0xED, 0xF0, 0xFF, 663
	thread	"?", 0xE3, 0xE8, 0xFF, 664
	thread	"?", 0xC8, 0xCF, 0xFA, 665
	thread	"?", 0xA4, 0xA6, 0xED, 666
	thread	"?", 0x69, 0x70, 0xDB, 667
	thread	"?", 0x3E, 0x40, 0xB3, 668
	thread	"?", 0x20, 0x1E, 0x87, 669
	thread	"?", 0xFF, 0xDE, 0xFF, 670
	thread	"?", 0xFC, 0xCC, 0xFF, 671
	thread	"?", 0xF7, 0xA8, 0xFF, 672
	thread	"?", 0xF0, 0x82, 0xFF, 673
	thread	"?", 0xE8, 0x54, 0xFF, 674
	thread	"?", 0xCD, 0x00, 0xF7, 675
	thread	"?", 0xBB, 0x00, 0xC7, 676
	thread	"?", 0xFA, 0xDE, 0xFF, 677
	thread	"?", 0xF7, 0xC9, 0xFF, 678
	thread	"?", 0xF2, 0xBA, 0xFF, 679
	thread	"?", 0xE1, 0x8E, 0xFA, 680
	thread	"?", 0xC1, 0x5F, 0xF5, 681
	thread	"?", 0xA8, 0x2F, 0xE0, 682
	thread	"?", 0x81, 0x00, 0x91, 683
	thread	"?", 0xFA, 0xCF, 0xFA, 684
	thread	"?", 0xF7, 0xBA, 0xF7, 685
	thread	"?", 0xF2, 0xAA, 0xF2, 686
	thread	"?", 0xDC, 0x7E, 0xE0, 687
	thread	"?", 0xC4, 0x59, 0xCF, 688
	thread	"?", 0x9D, 0x27, 0xA8, 689
	thread	"?", 0x69, 0x03, 0x69, 690
	thread	"?", 0xFC, 0xD7, 0xE8, 691
	thread	"?", 0xFA, 0xC0, 0xE1, 692
	thread	"?", 0xF0, 0xA8, 0xD3, 693
	thread	"?", 0xE6, 0x83, 0xBA, 694
	thread	"?", 0xBF, 0x50, 0x8A, 695
	thread	"?", 0x99, 0x18, 0x46, 696
	thread	"?", 0x7D, 0x09, 0x25, 697
	thread	"?", 0xFF, 0xD6, 0xEB, 698
	thread	"?", 0xFF, 0xC2, 0xE6, 699
	thread	"?", 0xFF, 0xA3, 0xDB, 700
	thread	"?", 0xFF, 0x78, 0xCC, 701
	thread	"?", 0xF2, 0x4B, 0xA0, 702
	thread	"?", 0xD6, 0x24, 0x63, 703
	thread	"?", 0xBA, 0x00, 0x25, 704
	thread	"?", 0xFF, 0xE8, 0xF2, 705
	thread	"?", 0xFF, 0xD4, 0xE6, 706
	thread	"?", 0xFF, 0xB3, 0xDB, 707
	thread	"?", 0xFF, 0x8A, 0xC7, 708
	thread	"?", 0xFF, 0x57, 0x9E, 709
	thread	"?", 0xFF, 0x36, 0x6B, 710
	thread	"?", 0xFA, 0x00, 0x32, 711
	thread	"?", 0xFF, 0xDB, 0xB0, 712
	thread	"?", 0xFF, 0xCF, 0x96, 713
	thread	"?", 0xFF, 0xB8, 0x75, 714
	thread	"?", 0xFF, 0xA1, 0x4A, 715
	thread	"?", 0xFF, 0x87, 0x17, 716
	thread	"?", 0xFA, 0x70, 0x00, 717
	thread	"?", 0xEB, 0x63, 0x00, 718
	thread	"?", 0xFF, 0xE6, 0xBF, 719
	thread	"?", 0xFC, 0xD7, 0xA7, 720
	thread	"?", 0xF7, 0xBC, 0x77, 721
	thread	"?", 0xE8, 0x95, 0x38, 722
	thread	"?", 0xD4, 0x74, 0x0B, 723
	thread	"?", 0xA1, 0x4C, 0x00, 724
	thread	"?", 0x82, 0x3B, 0x00, 725
	thread	"?", 0xFA, 0xE6, 0xC0, 726
	thread	"?", 0xF2, 0xCE, 0xA0, 727
	thread	"?", 0xE6, 0xB5, 0x77, 728
	thread	"?", 0xD1, 0x90, 0x52, 729
	thread	"?", 0xB5, 0x6E, 0x2B, 730
	thread	"?", 0x75, 0x37, 0x00, 731
	thread	"?", 0x5C, 0x28, 0x00, 732
	thread	"?", 0xFF, 0xF5, 0xD1, 7401
	thread	"?", 0xFF, 0xF0, 0xB3, 7402
	thread	"?", 0xFF, 0xE6, 0x80, 7403
	thread	"?", 0xFF, 0xE8, 0x33, 7404
	thread	"?", 0xFF, 0xE6, 0x00, 7405
	thread	"?", 0xFF, 0xD1, 0x00, 7406
	thread	"?", 0xE3, 0xB1, 0x22, 7407
	thread	"?", 0xFF, 0xBF, 0x0D, 7408
	thread	"?", 0xFF, 0xB3, 0x0D, 7409
	thread	"?", 0xFF, 0xB3, 0x73, 7410
	thread	"?", 0xFF, 0xA6, 0x4F, 7411
	thread	"?", 0xED, 0x8A, 0x00, 7412
	thread	"?", 0xF5, 0x73, 0x00, 7413
	thread	"?", 0xE3, 0x7B, 0x00, 7414
	thread	"?", 0xFF, 0xD1, 0xD9, 7415
	thread	"?", 0xFF, 0x66, 0x66, 7416
	thread	"?", 0xFF, 0x40, 0x40, 7417
	thread	"?", 0xF2, 0x49, 0x61, 7418
	thread	"?", 0xD1, 0x54, 0x73, 7419
	thread	"?", 0xCC, 0x29, 0x76, 7420
	thread	"?", 0x63, 0x00, 0x46, 7421
	thread	"?", 0xFF, 0xE8, 0xF2, 7422
	thread	"?", 0xFF, 0x73, 0xC7, 7423
	thread	"?", 0xFF, 0x40, 0xB3, 7424
	thread	"?", 0xED, 0x18, 0xA6, 7425
	thread	"?", 0xD1, 0x00, 0x73, 7426
	thread	"?", 0xB8, 0x00, 0x40, 7427
	thread	"?", 0x73, 0x17, 0x3F, 7428
	thread	"?", 0xFF, 0xD1, 0xF7, 7429
	thread	"?", 0xFA, 0xB0, 0xFF, 7430
	thread	"?", 0xF2, 0x96, 0xED, 7431
	thread	"?", 0xE6, 0x67, 0xDF, 7432
	thread	"?", 0xD9, 0x36, 0xB8, 7433
	thread	"?", 0xCC, 0x29, 0xAD, 7434
	thread	"?", 0xA6, 0x00, 0x95, 7435
	thread	"?", 0xF7, 0xEB, 0xFF, 7436
	thread	"?", 0xF0, 0xCC, 0xFF, 7437
	thread	"?", 0xD9, 0xA6, 0xFF, 7438
	thread	"?", 0xCC, 0xA6, 0xFF, 7439
	thread	"?", 0xB3, 0x99, 0xFF, 7440
	thread	"?", 0xA3, 0x80, 0xFF, 7441
	thread	"?", 0x80, 0x4D, 0xFF, 7442
	thread	"?", 0xF0, 0xF2, 0xFF, 7443
	thread	"?", 0xCC, 0xD4, 0xFF, 7444
	thread	"?", 0xAD, 0xC6, 0xF7, 7445
	thread	"?", 0x91, 0x9E, 0xFF, 7446
	thread	"?", 0x53, 0x57, 0xCF, 7447
	thread	"?", 0x4E, 0x43, 0x73, 7448
	thread	"?", 0x27, 0x00, 0x20, 7449
	thread	"?", 0xCC, 0xE6, 0xFF, 7450
	thread	"?", 0x99, 0xC9, 0xFF, 7451
	thread	"?", 0x80, 0xAD, 0xFF, 7452
	thread	"?", 0x80, 0xBD, 0xFF, 7453
	thread	"?", 0x73, 0xAE, 0xE6, 7454
	thread	"?", 0x33, 0x78, 0xFF, 7455
	thread	"?", 0x6B, 0x9A, 0xED, 7456
	thread	"?", 0xE0, 0xFF, 0xFA, 7457
	thread	"?", 0x90, 0xF0, 0xE4, 7458
	thread	"?", 0x5F, 0xDE, 0xD1, 7459
	thread	"?", 0x00, 0xF2, 0xF2, 7460
	thread	"?", 0x38, 0xB8, 0xFF, 7461
	thread	"?", 0x00, 0x73, 0xE6, 7462
	thread	"?", 0x00, 0x33, 0x59, 7463
	thread	"?", 0xBF, 0xFF, 0xE6, 7464
	thread	"?", 0x80, 0xFF, 0xBF, 7465
	thread	"?", 0x4D, 0xFF, 0xC4, 7466
	thread	"?", 0x0D, 0xFF, 0xBF, 7467
	thread	"?", 0x00, 0xA5, 0xB8, 7468
	thread	"?", 0x00, 0x7A, 0x99, 7469
	thread	"?", 0x1C, 0x77, 0x8C, 7470
	thread	"?", 0xB8, 0xFF, 0xDB, 7471
	thread	"?", 0x7A, 0xFF, 0xBF, 7472
	thread	"?", 0x46, 0xEB, 0x91, 7473
	thread	"?", 0x14, 0xC7, 0x8F, 7474
	thread	"?", 0x59, 0xB3, 0x86, 7475
	thread	"?", 0x00, 0x66, 0x3A, 7476
	thread	"?", 0x10, 0x52, 0x49, 7477
	thread	"?", 0xD1, 0xFF, 0xDB, 7478
	thread	"?", 0x73, 0xFF, 0x80, 7479
	thread	"?", 0x66, 0xFF, 0x80, 7480
	thread	"?", 0x66, 0xFF, 0x73, 7481
	thread	"?", 0x33, 0xFF, 0x40, 7482
	thread	"?", 0x11, 0x73, 0x00, 7483
	thread	"?", 0x00, 0x80, 0x13, 7484
	thread	"?", 0xF0, 0xFF, 0xE6, 7485
	thread	"?", 0xCC, 0xFF, 0xB3, 7486
	thread	"?", 0xB3, 0xFF, 0x8C, 7487
	thread	"?", 0x91, 0xFF, 0x66, 7488
	thread	"?", 0x5F, 0xED, 0x2F, 7489
	thread	"?", 0x5B, 0xA6, 0x21, 7490
	thread	"?", 0x68, 0x99, 0x00, 7491
	thread	"?", 0xD1, 0xED, 0x77, 7492
	thread	"?", 0xC5, 0xE6, 0x93, 7493
	thread	"?", 0xA3, 0xD9, 0x82, 7494
	thread	"?", 0x86, 0xB3, 0x24, 7495
	thread	"?", 0x5F, 0x9E, 0x00, 7496
	thread	"?", 0x73, 0x86, 0x39, 7497
	thread	"?", 0x26, 0x33, 0x00, 7498
	thread	"?", 0xFF, 0xFA, 0xD9, 7499
	thread	"?", 0xF7, 0xF2, 0xD2, 7500
	thread	"?", 0xF0, 0xE6, 0xC0, 7501
	thread	"?", 0xE6, 0xD3, 0x95, 7502
	thread	"?", 0xBF, 0xA8, 0x7C, 7503
	thread	"?", 0x99, 0x73, 0x54, 7504
	thread	"?", 0x73, 0x50, 0x22, 7505
	thread	"?", 0xFF, 0xF2, 0xD9, 7506
	thread	"?", 0xFF, 0xE6, 0xB3, 7507
	thread	"?", 0xF5, 0xD0, 0x93, 7508
	thread	"?", 0xF2, 0xC2, 0x79, 7509
	thread	"?", 0xE3, 0x9F, 0x40, 7510
	thread	"?", 0xBF, 0x69, 0x00, 7511
	thread	"?", 0xAB, 0x5C, 0x00, 7512
	thread	"?", 0xF7, 0xCB, 0xB2, 7513
	thread	"?", 0xF2, 0xB8, 0x96, 7514
	thread	"?", 0xE0, 0x92, 0x70, 7515
	thread	"?", 0xA6, 0x50, 0x00, 7516
	thread	"?", 0x8F, 0x39, 0x00, 7517
	thread	"?", 0x66, 0x3D, 0x2E, 7518
	thread	"?", 0x42, 0x35, 0x00, 7519
	thread	"?", 0xFF, 0xD6, 0xCF, 7520
	thread	"?", 0xE6, 0xAC, 0xB8, 7521
	thread	"?", 0xD6, 0x81, 0x96, 7522
	thread	"?", 0xCC, 0x7A, 0x85, 7523
	thread	"?", 0xBA, 0x54, 0x4A, 7524
	thread	"?", 0xB3, 0x62, 0x59, 7525
	thread	"?", 0xA6, 0x3A, 0x00, 7526
	thread	"?", 0xED, 0xE8, 0xDF, 7527
	thread	"?", 0xE6, 0xDF, 0xCF, 7528
	thread	"?", 0xD4, 0xCB, 0xBA, 7529
	thread	"?", 0xAD, 0xA0, 0x89, 7530
	thread	"?", 0x80, 0x73, 0x5D, 7531
	thread	"?", 0x59, 0x4A, 0x2D, 7532
	thread	"?", 0x26, 0x1E, 0x06, 7533
	thread	"?", 0xE6, 0xE1, 0xD3, 7534
	thread	"?", 0xCC, 0xC6, 0xAD, 7535
	thread	"?", 0xAD, 0xA6, 0x87, 7536
	thread	"?", 0xC6, 0xCC, 0xB8, 7537
	thread	"?", 0xA2, 0xB3, 0x9B, 7538
	thread	"?", 0xA0, 0xA3, 0x95, 7539
	thread	"?", 0x47, 0x47, 0x47, 7540
	thread	"?", 0xED, 0xF2, 0xF2, 7541
	thread	"?", 0xC1, 0xD6, 0xD0, 7542
	thread	"?", 0xA6, 0xB3, 0xB3, 7543
	thread	"?", 0x8A, 0x97, 0x99, 7544
	thread	"?", 0x49, 0x5C, 0x5E, 7545
	thread	"?", 0x30, 0x45, 0x47, 7546
	thread	"?", 0x0A, 0x0F, 0x0F, 7547
	thread	"END", 0, 0, 0, -1


; Based on the manufacturer table at 
;   https://help.brother-usa.com/app/answers/detail/a_id/75245/~/thread-color-conversion-chart
; using a colour picker.

robisonAnton_polyester_codes:
	thread	"Black", 0x00, 0x00, 0x00, 5596
	thread	"White", 0xFF, 0xFF, 0xFF, 5597
; unfinished
	thread	"END", 0, 0, 0, -1


robison_anton_rayon_codes:
	thread	"Light Pink", 0xEF, 0xCC, 0xCE, 2243
	thread	"Pink", 0xFC, 0xBF, 0xC9, 2223
	thread	"Pink Bazaar", 0xEF, 0xC6, 0xD3, 2599
	thread	"Pink Mist", 0xF9, 0xB2, 0xB7, 2373
	thread	"Emily Pink", 0xF9, 0xAF, 0xAD, 2374
	thread	"Rose", 0xFC, 0x9B, 0xB2, 2293
	thread	"Rose Cerise", 0xFC, 0x8C, 0x99, 2244
	thread	"Carnation", 0xF2, 0xAF, 0xC1, 2237
	thread	"Shrimp", 0xE5, 0x56, 0x6D, 2246
	thread	"Bashful Pink", 0xF4, 0x47, 0x6B, 2248
	thread	"Begonia", 0xE5, 0x56, 0x6D, 2228
	thread	"Azalea", 0xF9, 0x84, 0x8E, 2412
	thread	"Dusty Rose", 0xF2, 0x68, 0x77, 2375
	thread	"Rose Tint", 0xD8, 0x89, 0x9B, 2591
	thread	"Burgundy", 0x8C, 0x26, 0x33, 2249
	thread	"TH Burgundy", 0x7C, 0x21, 0x28, 2608
	thread	"Russet", 0x7A, 0x26, 0x38, 2252
	thread	"Pro Firebrand", 0x75, 0x26, 0x3D, 2622
	thread	"Wine", 0x77, 0x2D, 0x35, 2225
	thread	"Intense Maroon", 0x59, 0x33, 0x44, 2587
	thread	"Dark Maroon", 0x4F, 0x21, 0x3A, 2376
	thread	"Carbernet", 0x93, 0x16, 0x38, 2494
	thread	"Mountain Rose", 0xF9, 0xB2, 0xB7, 2495
	thread	"Warm Wine", 0x66, 0x1E, 0x2B, 2496
	thread	"Primrose", 0xE5, 0x56, 0x6D, 2491
	thread	"Perfect Ruby", 0x8E, 0x23, 0x44, 2497
	thread	"Brushed Burgundy", 0x6D, 0x21, 0x3F, 2498
	thread	"Passion Rose", 0x8E, 0x23, 0x44, 2499
	thread	"New Berry", 0xAD, 0x00, 0x75, 2500
	thread	"Petal Pink", 0xFC, 0xC9, 0xC6, 2501
	thread	"Memphis Belle", 0xF4, 0xBF, 0xD1, 2502
	thread	"Desert Bloom", 0xF7, 0xBF, 0xBF, 2503
	thread	"Wild Pink", 0xCE, 0x00, 0x7C, 2259
	thread	"Floral Pink", 0xED, 0x72, 0xAA, 2415
	thread	"Hot Pink", 0xD3, 0x6B, 0x9E, 2260
	thread	"Crimson", 0xD6, 0x02, 0x70, 2416
	thread	"Ruby Glint", 0xE2, 0x28, 0x82, 2261
	thread	"Cherrystone", 0xAA, 0x00, 0x4F, 2504
	thread	"Cherry Punch", 0xAA, 0x00, 0x4F, 2417
	thread	"Cherry Blossom", 0xEA, 0x0F, 0x6B, 2262
	thread	"Red Berry", 0xAF, 0x1E, 0x2D, 2418
	thread	"Jockey Red", 0xBF, 0x0A, 0x30, 2281
	thread	"Very Red", 0xBF, 0x0A, 0x30, 2419
	thread	"Red Berry", 0xBF, 0x0A, 0x30, 2378
	thread	"Foxy Red", 0xCE, 0x11, 0x26, 2263
	thread	"Tuxedo Red", 0xD6, 0x28, 0x28, 2420
	thread	"Lipstick", 0xBF, 0x0A, 0x30, 2233
	thread	"Scarlet", 0xC4, 0x1E, 0x3A, 2219
	thread	"Radiant Red", 0xC4, 0x1E, 0x3A, 2266
	thread	"Wildfire", 0xA3, 0x26, 0x38, 2267
	thread	"Carolina Red", 0x8C, 0x26, 0x33, 2268
	thread	"Red Jubilee", 0x75, 0x26, 0x3D, 2421
	thread	"Cranberry", 0x99, 0x21, 0x35, 2270
	thread	"Antique Red", 0xA3, 0x26, 0x38, 2505
	thread	"Devil Red", 0xC4, 0x1E, 0x3A, 2506
	thread	"Rosewood", 0xD8, 0x1C, 0x3F, 2508
	thread	"Bitteroot", 0xFC, 0x5E, 0x72, 2509
	thread	"Bisque", 0xF2, 0xC4, 0xAF, 2377
	thread	"Flesh", 0xF4, 0xCC, 0xAA, 2413
	thread	"Flesh Pink", 0xF9, 0xBA, 0xAA, 2253
	thread	"Opal Mist", 0xF7, 0xBF, 0xBF, 2255
	thread	"Candy Apple Red", 0xAF, 0x00, 0x3D, 2507
	thread	"Tawny", 0xF9, 0xBF, 0x9E, 2256
	thread	"Peach", 0xF9, 0xC6, 0xAA, 2257
	thread	"Melon", 0xF9, 0x8E, 0x6D, 2294
	thread	"Flamingo", 0xF9, 0xA5, 0x8C, 2258
	thread	"Coral", 0xF9, 0x89, 0x72, 2414
	thread	"Persimmon", 0xF4, 0x3F, 0x4F, 2277
	thread	"Peach Blossom", 0xF9, 0xC6, 0xAA, 2510
	thread	"Illusion", 0xF9, 0xBA, 0xAA, 2511
	thread	"Melonade", 0xF9, 0x89, 0x72, 2512
	thread	"Honeysuckle", 0xE2, 0x3D, 0x28, 2513
	thread	"Brite Jade", 0x00, 0x8C, 0x82, 2514
	thread	"Bluestone", 0x00, 0xB2, 0xA0, 2515
	thread	"Aqua Pearl", 0x47, 0xD6, 0xC1, 2516
	thread	"Seafrost", 0x87, 0xDD, 0xD1, 2517
	thread	"J. Turquoise", 0x00, 0x87, 0x89, 2492
	thread	"Indian Ocean Blue", 0x2D, 0xC6, 0xD6, 2518
	thread	"Surf Blue", 0x00, 0xA5, 0xDB, 2519
	thread	"Mid Windsor", 0x00, 0xA3, 0xDD, 2520
	thread	"Deep Windsor", 0x00, 0x3F, 0x54, 2589
	thread	"Pro Dark Blue", 0x00, 0x2D, 0x47, 2620
	thread	"Mallard Blue", 0x00, 0x6D, 0x75, 2521
	thread	"Sky Blue", 0x9B, 0xC4, 0xE2, 2239
	thread	"Lake Blue", 0xAF, 0xBC, 0xDB, 2304
	thread	"Pro Lusty Blue", 0x5B, 0x77, 0xCC, 2614
	thread	"Slate Blue", 0x6D, 0x87, 0xA8, 2275
	thread	"Blue Frost", 0x99, 0xD6, 0xDD, 2305
	thread	"Periwinkle", 0x28, 0xC4, 0xD8, 2306
	thread	"Aquamarine", 0x00, 0xAD, 0xC6, 2307
	thread	"California Blue", 0x00, 0xA0, 0xC4, 2389
	thread	"Baltic Blue", 0x00, 0x8E, 0xD6, 2441
	thread	"Solar Blue", 0x00, 0x54, 0xA0, 2442
	thread	"Pacific Blue", 0x00, 0x8E, 0xD6, 2388
	thread	"Boo Boo Blue", 0x00, 0xA3, 0xDD, 2730
	thread	"Pro Band Blue", 0x00, 0x70, 0x9E, 2737
	thread	"Pro Peacock", 0x00, 0x7A, 0xA5, 2740
	thread	"Light Blue", 0xC9, 0xE8, 0xDD, 2222
	thread	"Royal", 0x1E, 0x1C, 0x77, 2210
	thread	"Blue Suede", 0x00, 0x2B, 0x7F, 2438
	thread	"Imperial Blue", 0x33, 0x56, 0x87, 2302
	thread	"Bridgeport Blue", 0xAF, 0xBC, 0xDB, 2522
	thread	"China Blue", 0x33, 0x56, 0x87, 2523
	thread	"Pro Imperial", 0x26, 0x54, 0x7C, 2612
	thread	"Country Blue", 0x77, 0x96, 0xB2, 2524
	thread	"Heron Blue", 0xC1, 0xC9, 0xDD, 2525
	thread	"Pro Saxon", 0x77, 0x96, 0xB2, 2624
	thread	"Bright Blue", 0x66, 0x89, 0xCC, 2526
	thread	"Soldier Blue", 0x59, 0x60, 0xA8, 2527
	thread	"Pro Brilliance", 0x00, 0x51, 0xBA, 2619
	thread	"Atlantis Blue", 0x66, 0x89, 0xCC, 2528
	thread	"Dolphin Blue", 0x3A, 0x75, 0xC4, 2529
	thread	"Caribbean Blue", 0x75, 0xAA, 0xDB, 2530
	thread	"Dana Blue", 0xC4, 0xD8, 0xE2, 2531
	thread	"Cadet Blue", 0xC4, 0xD8, 0xE2, 2532
	thread	"Ozone", 0x60, 0xAF, 0xDD, 2533
	thread	"Salem Blue", 0x00, 0x3D, 0x6B, 2534
	thread	"Blue Ribbon", 0x0F, 0x2B, 0x5B, 2439
	thread	"Pro Navy", 0x19, 0x21, 0x68, 2625
	thread	"Blue Ink", 0x2B, 0x26, 0x5B, 2440
	thread	"Pro Midnight", 0x00, 0x26, 0x54, 2613
	thread	"Pro College Blue", 0x00, 0x26, 0x49, 2647
	thread	"Light Midnight", 0x35, 0x3F, 0x5B, 2386
	thread	"Fleet Blue", 0x35, 0x26, 0x4F, 2450
	thread	"Light Navy", 0x11, 0x21, 0x51, 2303
	thread	"Flag Blue", 0x14, 0x21, 0x3D, 2603
	thread	"TH Navy", 0x00, 0x26, 0x54, 2609
	thread	"Navy", 0x14, 0x21, 0x3D, 2215
	thread	"Midnight Navy", 0x14, 0x21, 0x3D, 2387
	thread	"Pastel Blue", 0xC6, 0xD1, 0xD6, 2382
	thread	"Blue Hint", 0xC1, 0xC9, 0xDD, 2598
	thread	"Ice Blue", 0xB5, 0xD1, 0xE8, 2300
	thread	"Paris Blue", 0xD1, 0xCE, 0xDD, 2283
	thread	"Baby Blue", 0x99, 0xBA, 0xDD, 2206
	thread	"Sun Blue", 0xAF, 0xBC, 0xDB, 2269
	thread	"Cristy Blue", 0xA5, 0xBA, 0xE0, 2383
	thread	"Ultra Blue", 0x75, 0xB2, 0xDD, 2433
	thread	"Tropic Blue", 0x75, 0xAA, 0xDB, 2434
	thread	"Blue Horizon", 0x66, 0x89, 0xCC, 2435
	thread	"Oriental Blue", 0x7F, 0x8C, 0xBF, 2301
	thread	"Copen", 0x6D, 0x87, 0xA8, 2245
	thread	"Jay Blue", 0x5B, 0x77, 0xCC, 2384
	thread	"Blue", 0x2D, 0x33, 0x8E, 2220
	thread	"Sapphire", 0x2D, 0x33, 0x8E, 2280
	thread	"Pro Royal", 0x00, 0x33, 0x7F, 2627
	thread	"Fire Blue", 0x00, 0x38, 0x93, 2436
	thread	"Jamie Blue", 0x2D, 0x33, 0x8E, 2385
	thread	"Empire Blue", 0x3F, 0x28, 0x93, 2437
	thread	"Enchanted Sea", 0x3A, 0x56, 0x4F, 2535
	thread	"Pro Twinkle", 0x84, 0x99, 0xA5, 2617
	thread	"Rockport Blue", 0x9B, 0xAA, 0xBF, 2536
	thread	"Wonder Blue", 0x5E, 0x99, 0xAA, 2577
	thread	"Traditional Gray", 0xAD, 0xAF, 0xAA, 2540
	thread	"Steel", 0xBF, 0xBA, 0xAF, 2537
	thread	"Pro Pearl", 0xBA, 0xB7, 0xAF, 2741
	thread	"Pro Cool Gray", 0xC4, 0xC1, 0xBA, 2733
	thread	"Stainless Steel", 0xCC, 0xC1, 0xB2, 2538
	thread	"Chrome", 0xD1, 0xCC, 0xBF, 2539
	thread	"Pro Night Sky", 0xAD, 0xAF, 0xAA, 2618
	thread	"Gull", 0x8C, 0x89, 0x84, 2731
	thread	"Mineral", 0x68, 0x66, 0x63, 2729
	thread	"Black Chrome", 0x44, 0x3D, 0x38, 2541
	thread	"Heather", 0xDD, 0xC6, 0xC4, 2271
	thread	"Grape", 0xD3, 0xB7, 0xA3, 2272
	thread	"Satin Wine", 0xB5, 0x93, 0x9B, 2314
	thread	"Ducky Mauve", 0x8E, 0x68, 0x77, 2422
	thread	"Pale Orchid", 0xFC, 0xBF, 0xC9, 2423
	thread	"Orchid", 0xE5, 0xBF, 0xC6, 2379
	thread	"Lavender", 0xEF, 0xC6, 0xD3, 2276
	thread	"Violet", 0xED, 0xC4, 0xDD, 2285
	thread	"Cachet", 0xB5, 0x8C, 0xB2, 2424
	thread	"Tulip", 0xC9, 0xAD, 0xD8, 2286
	thread	"Mid Lilac", 0xE2, 0x9E, 0xD6, 2588
	thread	"Port Wine", 0x51, 0x26, 0x54, 2600
	thread	"Pro Maroon", 0x51, 0x2D, 0x44, 2616
	thread	"Laurie Lilac", 0x8E, 0x47, 0xAD, 2425
	thread	"Iris", 0xAF, 0x72, 0xC1, 2288
	thread	"Raspberry", 0x9B, 0x4F, 0x96, 2426
	thread	"Mulberry", 0x66, 0x11, 0x6D, 2380
	thread	"Plum Wine", 0x63, 0x30, 0x5E, 2490
	thread	"Purple Twist", 0x1E, 0x1C, 0x77, 2429
	thread	"Violet Blue", 0x33, 0x28, 0x75, 2427
	thread	"Purple Maze", 0x35, 0x00, 0x6D, 2428
	thread	"Pro Brite Star", 0x2B, 0x11, 0x66, 2736
	thread	"Pro Violet", 0x38, 0x19, 0x7A, 2742
	thread	"Pro Purple", 0x35, 0x00, 0x6D, 2628
	thread	"Purple", 0x8E, 0x47, 0xAD, 2254
	thread	"Purple Shadow", 0x5B, 0x02, 0x7A, 2430
	thread	"Dark Purple", 0x4C, 0x14, 0x5E, 2381
	thread	"Mauve", 0x89, 0x77, 0xBA, 2287
	thread	"Purple Accent", 0x44, 0x23, 0x5E, 2431
	thread	"Hot Peony", 0xAA, 0x00, 0x66, 2590
	thread	"Passion", 0xCE, 0x00, 0x7C, 2291
	thread	"Strawberry", 0xAA, 0x00, 0x4F, 2432
	thread	"Plum", 0x9E, 0x23, 0x87, 2292
	thread	"Misty", 0x5E, 0x99, 0xAA, 2308
	thread	"Mystic Teal", 0x60, 0x91, 0x91, 2443
	thread	"Teal", 0x60, 0x91, 0x91, 2309
	thread	"Dark Teal", 0x00, 0x3F, 0x54, 2444
	thread	"Mint Julep", 0x93, 0xDD, 0xDB, 2310
	thread	"Turquoise", 0x7F, 0xD6, 0xDB, 2204
	thread	"M.D. Green", 0x00, 0x72, 0x72, 2445
	thread	"Seafoam", 0x70, 0xCE, 0x9B, 2311
	thread	"Isle Green", 0x70, 0xCE, 0x9B, 2312
	thread	"Peppermint", 0x35, 0xC4, 0xAF, 2390
	thread	"Oceanic Green", 0x00, 0x6D, 0x75, 2446
	thread	"Pro Teal", 0x00, 0x6B, 0x77, 2621
	thread	"Garden Green", 0x00, 0x66, 0x63, 2447
	thread	"Pro Green", 0x00, 0x6D, 0x66, 2735
	thread	"Pine Green", 0x00, 0x8C, 0x82, 2391
	thread	"Greenstone", 0x00, 0x82, 0x72, 2448
	thread	"Fern Green", 0x00, 0x66, 0x63, 2449
	thread	"Pro Hunter", 0x00, 0x6D, 0x66, 2615
	thread	"Palm Leaf", 0xBC, 0xC1, 0xB2, 2241
	thread	"Flite Green", 0xC6, 0xD6, 0xA0, 2282
	thread	"Willow", 0x9E, 0xAA, 0x99, 2221
	thread	"Sprite", 0xB2, 0xD8, 0xD8, 2313
	thread	"Moss", 0x7A, 0xA8, 0x91, 2278
	thread	"Wintergreen", 0x7A, 0xA8, 0x91, 2594
	thread	"Green Forest", 0x00, 0x60, 0x56, 2451
	thread	"Pro Forest", 0x00, 0x60, 0x56, 2743
	thread	"Harbor Green", 0x4F, 0x6D, 0x5E, 2392
	thread	"Evergreen", 0x02, 0x49, 0x30, 2315
	thread	"Pro Dark Green", 0x00, 0x44, 0x38, 2734
	thread	"Lizzy Lime", 0x2B, 0x4C, 0x3F, 2631
	thread	"D.H. Green", 0x28, 0x2D, 0x26, 2411
	thread	"Celery", 0xF2, 0xEA, 0xBC, 2316
	thread	"Pistachio", 0xCC, 0xC6, 0x93, 2250
	thread	"Olive Drab", 0x5E, 0x66, 0x3A, 2317
	thread	"Olive", 0x77, 0x91, 0x82, 2202
	thread	"Pale Green", 0xC9, 0xE8, 0xDD, 2318
	thread	"Green Pearl", 0x93, 0xDD, 0xDB, 2452
	thread	"Sea Mist", 0x93, 0xDD, 0xDB, 2393
	thread	"Mint", 0xB5, 0xE8, 0xBF, 2238
	thread	"Spruce", 0xAA, 0xDD, 0x6D, 2279
	thread	"Nile", 0xA0, 0xDB, 0x8E, 2211
	thread	"Green Oak", 0xB5, 0xCC, 0x8E, 2319
	thread	"Erin Green", 0x8C, 0xD6, 0x00, 2320
	thread	"Pro Erin", 0x56, 0xAA, 0x1C, 2738
	thread	"Emerald", 0x33, 0x9E, 0x35, 2214
	thread	"Dark Emerald", 0x00, 0x7A, 0x3D, 2453
	thread	"Light Kelly", 0x00, 0x7A, 0x3D, 2410
	thread	"Kelly", 0x00, 0x7A, 0x3D, 2240
	thread	"Dark Green", 0x00, 0x87, 0x51, 2208
	thread	"Fleece Green", 0x00, 0x6B, 0x3F, 2454
	thread	"TH Green", 0x00, 0x68, 0x54, 2607
	thread	"Harvest Green", 0x1E, 0xB5, 0x3A, 2578
	thread	"Vibrant Green", 0x00, 0x9E, 0x49, 2579
	thread	"Green Grass", 0x00, 0x9E, 0x49, 2580
	thread	"Deep Green", 0x00, 0x6B, 0x3F, 2284
	thread	"Green Bay", 0x00, 0x6B, 0x54, 2455
	thread	"Jungle Green", 0x00, 0x7C, 0x66, 2597
	thread	"Peapod", 0xA3, 0xAF, 0x07, 2456
	thread	"Pastoral Green", 0x7F, 0xBA, 0x00, 2321
	thread	"Green Dust", 0x7F, 0xBA, 0x00, 2457
	thread	"Ming", 0x7F, 0xBA, 0x00, 2322
	thread	"Meadow", 0x56, 0x8E, 0x14, 2226
	thread	"Tamarack", 0x93, 0x99, 0x05, 2230
	thread	"Palmetto", 0x56, 0x63, 0x14, 2229
	thread	"Green Petal", 0x02, 0x49, 0x30, 2458
	thread	"Sage", 0x54, 0x77, 0x30, 2595
	thread	"Hedge", 0x3F, 0x49, 0x26, 2601
	thread	"Green", 0x3A, 0x77, 0x28, 2209
	thread	"Green Sail", 0x19, 0x38, 0x33, 2459
	thread	"Holly", 0x21, 0x5B, 0x33, 2323
	thread	"Field Green", 0x26, 0x51, 0x42, 2460
	thread	"Dress Green", 0x3F, 0x49, 0x26, 2584
	thread	"Foliage Green", 0x99, 0x84, 0x0A, 2542
	thread	"Autumn Green", 0xA3, 0x82, 0x05, 2543
	thread	"Desert Cactus", 0x89, 0x77, 0x19, 2544
	thread	"Cypress", 0x70, 0x70, 0x14, 2545
	thread	"Crescent Moon", 0x84, 0x82, 0x05, 2546
	thread	"Pebblestone", 0xE2, 0xE5, 0x84, 2547
	thread	"Sun Shadow", 0x99, 0x8E, 0x07, 2548
	thread	"Blue Spruce", 0x00, 0x49, 0x4F, 2549
	thread	"Newport", 0x4F, 0x6D, 0x5E, 2550
	thread	"Spring Garden", 0x77, 0x91, 0x82, 2551
	thread	"Water Lilly", 0x54, 0x68, 0x56, 2554
	thread	"Ivy", 0x0C, 0x30, 0x26, 2552
	thread	"Dark Army Green", 0x23, 0x3A, 0x2D, 2553
	thread	"Army Green", 0x21, 0x3D, 0x30, 2728
	thread	"Pastel Green", 0xC9, 0xD6, 0xA3, 2555
	thread	"Pollen Gold", 0xE0, 0xAA, 0x0F, 2556
	thread	"Pale Yellow", 0xF4, 0xE2, 0x87, 2557
	thread	"Buttercup", 0xFF, 0xC6, 0x1E, 2558
	thread	"Tusk", 0xF7, 0xE8, 0xAA, 2559
	thread	"Moonbeam", 0xF9, 0xDD, 0x16, 2560
	thread	"Black Eyed Susie", 0xC6, 0xA0, 0x0C, 2561
	thread	"Bullion", 0xA3, 0x7F, 0x14, 2562
	thread	"Chinese Yellow", 0xF7, 0xE8, 0xAA, 2324
	thread	"Maize", 0xF7, 0xE8, 0xAA, 2264
	thread	"Wheat", 0xEA, 0xDD, 0x96, 2461
	thread	"Pro Maize", 0xF9, 0xE0, 0x8C, 2732
	thread	"Glow", 0xFF, 0xD8, 0x7F, 2234
	thread	"Star Gold", 0xFC, 0xD8, 0x56, 2408
	thread	"Mango", 0xFC, 0xA3, 0x11, 2394
	thread	"Yellow Mist", 0xFC, 0xA3, 0x11, 2409
	thread	"Yellow", 0xFC, 0xA3, 0x11, 2213
	thread	"Sunflower", 0xF9, 0xDD, 0x16, 2462
	thread	"Lemon", 0xF4, 0xED, 0x47, 2325
	thread	"Daffodil", 0xF9, 0xE8, 0x14, 2326
	thread	"Merit Gold", 0xFC, 0xB5, 0x14, 2463
	thread	"Cornsilk", 0xFF, 0xCC, 0x49, 2395
	thread	"Nectar", 0xFF, 0xC6, 0x1E, 2464
	thread	"Scholastic", 0xFC, 0xBF, 0x49, 2465
	thread	"Canary Yellow", 0xFC, 0xE0, 0x16, 2235
	thread	"Pro Gold", 0xFF, 0xC6, 0x1E, 2626
	thread	"Manila", 0xFC, 0xD1, 0x16, 2466
	thread	"Goldenrod", 0xFC, 0xD1, 0x16, 2242
	thread	"Brite Yellow", 0xFF, 0xCC, 0x49, 2396
	thread	"Honeydew", 0xF9, 0x9B, 0x0C, 2327
	thread	"Pumpkin", 0xF7, 0x7F, 0x00, 2328
	thread	"Orangeade", 0xF7, 0x49, 0x02, 2467
	thread	"Sun Orange", 0xF7, 0x49, 0x02, 2397
	thread	"Paprika", 0xF9, 0x56, 0x02, 2236
	thread	"Saffron", 0xF9, 0x3F, 0x26, 2329
	thread	"Tex Orange", 0xF9, 0x56, 0x02, 2468
	thread	"Orange", 0xF9, 0x6B, 0x07, 2218
	thread	"Dark Tex Orange", 0xF9, 0x63, 0x02, 2469
	thread	"Old Dark Tex Orange", 0xA5, 0x3F, 0x0F, 2581
	thread	"Golden Poppy", 0xFC, 0x87, 0x44, 2330
	thread	"Rust", 0xBC, 0x4F, 0x07, 2289
	thread	"Copper", 0xAF, 0x75, 0x05, 2295
	thread	"Light Bronze", 0xC1, 0x8E, 0x60, 2493
	thread	"Visor Gold", 0xFC, 0xCE, 0x87, 2398
	thread	"Goldenlite", 0xFF, 0xCC, 0x49, 2605
	thread	"Honey", 0xFC, 0xBA, 0x5E, 2247
	thread	"Marigold", 0xFF, 0xCC, 0x49, 2216
	thread	"Mustard", 0xE0, 0xAA, 0x0F, 2331
	thread	"Sun Gold", 0xE0, 0xAA, 0x0F, 2212
	thread	"Karat", 0xE0, 0xAA, 0x0F, 2470
	thread	"Penny", 0xF2, 0xBF, 0x49, 2332
	thread	"New Gold", 0xFC, 0xCE, 0x87, 2399
	thread	"Pro Beige", 0xE2, 0xD6, 0xB5, 2630
	thread	"Marine Gold", 0xC6, 0xA0, 0x0C, 2596
	thread	"Ginger", 0xA3, 0x7F, 0x14, 2333
	thread	"Shimmering Gold", 0xC6, 0xA0, 0x0C, 2471
	thread	"Old Gold", 0xBF, 0x91, 0x0C, 2201
	thread	"Salmon", 0xEA, 0xB2, 0xB2, 2299
	thread	"Dark Rust", 0xC1, 0x38, 0x28, 2205
	thread	"Terra Cotta", 0xA0, 0x30, 0x33, 2334
	thread	"Pro Red", 0xAF, 0x1E, 0x2D, 2623
	thread	"Auburn", 0xAF, 0x1E, 0x2D, 2472
	thread	"Bone", 0xFA, 0xE6, 0xCC, 2582
	thread	"Ivory", 0xFA, 0xE6, 0xCF, 2335
	thread	"Opaline", 0xF7, 0xD3, 0xB5, 2473
	thread	"Ecru", 0xED, 0xD3, 0xBC, 2232
	thread	"Wicker", 0xAA, 0x75, 0x3F, 2489
	thread	"Tan", 0xD3, 0xA8, 0x7C, 2273
	thread	"Cottage Beige", 0xED, 0xD3, 0xB5, 2593
	thread	"Rattan", 0xC1, 0xA8, 0x75, 2474
	thread	"Gold", 0xE2, 0xBF, 0x9B, 2203
	thread	"Mocha Cream", 0xD3, 0xA8, 0x7C, 2475
	thread	"Topaz", 0xBF, 0x91, 0x0C, 2400
	thread	"Ashley Gold", 0xD1, 0x8E, 0x54, 2401
	thread	"Amber Beige", 0xD8, 0xB5, 0x96, 2336
	thread	"Seashell", 0xD6, 0xCC, 0xAF, 2476
	thread	"Light Maize", 0xF2, 0xE3, 0xC4, 2604
	thread	"Beige", 0xAA, 0x75, 0x3F, 2224
	thread	"Sand Dune", 0x6B, 0x47, 0x14, 2477
	thread	"Taupe", 0xD1, 0xBF, 0x91, 2298
	thread	"Pro Brown", 0x6C, 0x46, 0x3D, 2610
	thread	"Chocolate", 0x87, 0x60, 0x28, 2227
	thread	"Pro Walnut", 0x75, 0x54, 0x26, 2629
	thread	"Light Cocoa", 0x75, 0x54, 0x26, 2478
	thread	"Cocoa Mulch", 0xB2, 0x82, 0x60, 2488
	thread	"Brown", 0x59, 0x3D, 0x2B, 2251
	thread	"Dark Brown", 0x59, 0x3D, 0x2B, 2372
	thread	"Espresso", 0x3F, 0x30, 0x2B, 2337
	thread	"Bamboo", 0xC1, 0x8E, 0x60, 2338
	thread	"Almond", 0xAF, 0x75, 0x05, 2479
	thread	"Toast", 0xBA, 0x75, 0x30, 2231
	thread	"Sienna", 0x75, 0x54, 0x26, 2402
	thread	"K.A. Bronze", 0xB2, 0x6B, 0x70, 2480
	thread	"Pro Cinnamon", 0xA2, 0x46, 0x4E, 2611
	thread	"Date", 0x9B, 0x4F, 0x19, 2290
	thread	"Hazel", 0x9B, 0x4F, 0x19, 2481
	thread	"Coffee Bean", 0x5B, 0x2D, 0x28, 2339
	thread	"Dogwood", 0x59, 0x3D, 0x2B, 2563
	thread	"Mahogany", 0x3F, 0x30, 0x2B, 2564
	thread	"Best Brown", 0x3D, 0x30, 0x28, 2566
	thread	"Mushroom", 0x63, 0x3A, 0x11, 2567
	thread	"Perfect Tan", 0xC1, 0xA8, 0x75, 2568
	thread	"Earthen Tan", 0x7A, 0x5B, 0x11, 2569
	thread	"Golden Tan", 0xC1, 0xA8, 0x75, 2570
	thread	"14 Kt. Gold", 0xF2, 0xBF, 0x49, 2586
	thread	"TH Gold", 0xF2, 0xCE, 0x68, 2606
	thread	"24 Kt. Gold", 0xD8, 0x8C, 0x02, 2602
	thread	"Platinum", 0xC1, 0xB5, 0xA5, 2571
	thread	"Pro Gray", 0x99, 0x89, 0x7C, 2739
	thread	"Grayrod", 0xAD, 0xA0, 0x7A, 2572
	thread	"Pewter", 0xAD, 0xA0, 0x7A, 2573
	thread	"Aspen White", 0xF5, 0xE3, 0xCC, 2574
	thread	"Dark Taupe", 0x66, 0x59, 0x4C, 2575
	thread	"Egyptian Brown", 0x49, 0x35, 0x33, 2576
	thread	"Oyster", 0xF5, 0xEB, 0xE0, 2403
	thread	"Gray", 0xDD, 0xC6, 0xC4, 2207
	thread	"Pearl Gray", 0xDB, 0xD3, 0xD3, 2340
	thread	"Steel Gray", 0xD8, 0xCC, 0xD1, 2274
	thread	"Skylight", 0xCC, 0xC1, 0xC6, 2482
	thread	"Cloud", 0xAF, 0xAA, 0xA3, 2483
	thread	"Silver Steel", 0xAD, 0xAF, 0xAA, 2592
	thread	"Banner Gray", 0x91, 0x96, 0x93, 2585
	thread	"Silvery Gray", 0x8C, 0x89, 0x84, 2484
	thread	"Cinder", 0xCC, 0xC1, 0xC6, 2404
	thread	"Saturn Gray", 0xDB, 0xD3, 0xD3, 2485
	thread	"Dover Gray", 0xCC, 0xC1, 0xC6, 2405
	thread	"Storm Gray", 0xB2, 0xA8, 0xB5, 2486
	thread	"Sterling", 0xA8, 0x93, 0xAD, 2406
	thread	"Metal", 0x66, 0x6D, 0x70, 2407
	thread	"Twilight", 0x68, 0x66, 0x63, 2217
	thread	"Aged Charcoal", 0x44, 0x3D, 0x38, 2565
	thread	"Charcoal", 0x77, 0x77, 0x72, 2265
	thread	"Smokey", 0x35, 0x38, 0x42, 2487
	thread	"Ash", 0x3A, 0x49, 0x72, 2341
	thread	"Black", 0x1C, 0x26, 0x30, 2296
	thread	"Snow White", 0xF5, 0xEB, 0xE0, 2297
	thread	"Natural White", 0xF5, 0xED, 0xDE, 2342
	thread	"Eggshell", 0xF0, 0xE8, 0xD6, 2343
	thread	"Jet Black", 0x1C, 0x26, 0x30, 2632
	thread	"END", 0, 0, 0, -1


sigma_polyester_codes:
	thread	"White", 0xFF, 0xFF, 0xFF, 10
	thread	"Black", 0x00, 0x00, 0x00, 20
	thread	"Light Neon Green", 0xED, 0xFF, 0x50, 21
	thread	"Neon Green", 0x96, 0xE8, 0x45, 32
	thread	"Light Neon Orange", 0xFF, 0xE7, 0x56, 33
	thread	"Med Neon Orange", 0xFF, 0x78, 0x24, 43
	thread	"Neon Pink", 0xF2, 0x8D, 0xA6, 46
	thread	"Neon Orange Pink", 0xC7, 0x0C, 0x57, 47
	thread	"Silver", 0xE2, 0x2D, 0x2A, 101
	thread	"Silver Diamond", 0xB8, 0xB8, 0xB8, 102
	thread	"Lava Stone", 0x88, 0x91, 0x86, 112
	thread	"Medium Grey", 0x73, 0x7F, 0x7F, 115
	thread	"Dark Platinum", 0x56, 0x5E, 0x5A, 116
	thread	"Charcoal", 0x51, 0x52, 0x50, 117
	thread	"Badger Grey", 0x78, 0x76, 0x68, 118
	thread	"Pumpkin Orange", 0xED, 0x57, 0x2F, 135
	thread	"Turquoise", 0x2E, 0xA5, 0x9C, 138
	thread	"Dark Wedgewood", 0x39, 0x62, 0x76, 142
	thread	"Cardinal Red", 0x9B, 0x3B, 0x40, 213
	thread	"Maroon", 0x6C, 0x3E, 0x47, 216
	thread	"Rust", 0xBA, 0x6E, 0x4D, 253
	thread	"Medium Rust", 0xBB, 0x3D, 0x2E, 255
	thread	"Natural Pink", 0xF9, 0xDF, 0xCF, 301
	thread	"Baby Pink", 0xFB, 0xDE, 0xD6, 303
	thread	"Piggy Pink", 0xF7, 0xCD, 0xD5, 304
	thread	"Sweet Pink", 0xF2, 0xAF, 0xB4, 305
	thread	"Blushing Pink", 0xE8, 0x41, 0x8C, 307
	thread	"Pink", 0xE7, 0x7F, 0x9D, 309
	thread	"Rose Pink", 0xF0, 0x6F, 0x8C, 313
	thread	"Green", 0x00, 0x83, 0x40, 317
	thread	"Shocking Pink", 0xDF, 0x99, 0xB6, 321
	thread	"Ruby", 0x82, 0x00, 0x52, 325
	thread	"Garnet", 0xB1, 0x41, 0x5F, 333
	thread	"Light Purple", 0xC3, 0x94, 0xAE, 345
	thread	"Medium Purple", 0xA8, 0x6E, 0x91, 347
	thread	"Dark Grape", 0x69, 0x41, 0x69, 348
	thread	"Pastel Light Pink", 0xE6, 0xCF, 0xD5, 376
	thread	"Light Baby Blue", 0xA8, 0xBE, 0xD7, 379
	thread	"Crystal Blue", 0xA0, 0xBF, 0xD7, 380
	thread	"Very Light Lavender", 0x90, 0xA6, 0xC6, 381
	thread	"Cornflower", 0x8F, 0xAF, 0xC6, 382
	thread	"Lavender", 0xB1, 0xB8, 0xD3, 383
	thread	"Denim", 0x41, 0x6C, 0x9B, 385
	thread	"Light Violet", 0x7D, 0x77, 0xAF, 386
	thread	"Misty Rose", 0xFA, 0xDA, 0xF4, 387
	thread	"Grape", 0x66, 0x40, 0x90, 390
	thread	"Lt. Weathered Blue", 0xEA, 0xF0, 0xF9, 402
	thread	"Baby Blue", 0xA6, 0xD8, 0xF6, 403
	thread	"Med Baby Blue", 0x7B, 0x9C, 0xB0, 404
	thread	"Med Pastel Blue", 0x64, 0x8D, 0xC7, 406
	thread	"Blue Raspberry", 0x3D, 0x6A, 0xA1, 409
	thread	"Med Royal Blue", 0x2D, 0x44, 0x91, 413
	thread	"Ocean Blue", 0x14, 0x3D, 0x7A, 414
	thread	"Med Navy", 0x11, 0x32, 0x63, 415
	thread	"Dark Navy", 0x0E, 0x1F, 0x38, 423
	thread	"Bright Sunshine", 0x0E, 0x1F, 0x38, 432
	thread	"Teal", 0x00, 0x91, 0xA5, 443
	thread	"Deep Teal", 0x00, 0x5B, 0x63, 448
	thread	"Dark Teal", 0x00, 0x47, 0x4D, 449
	thread	"Old Gold", 0xE5, 0xB1, 0x5C, 466
	thread	"Cream", 0xD5, 0xBF, 0x9B, 501
	thread	"Pale Salmon", 0xFF, 0xD0, 0x85, 503
	thread	"Med Peach", 0xF6, 0xB0, 0x8E, 505
	thread	"Pink Salmon", 0xB3, 0xE8, 0x51, 506
	thread	"Dark Peach", 0xF1, 0xA2, 0x36, 508
	thread	"Dark Brown", 0x6E, 0x43, 0x37, 513
	thread	"Pale Red", 0xD8, 0x49, 0x3E, 527
	thread	"Heron Blue", 0x69, 0x76, 0x98, 541
	thread	"Pale Yellow", 0xFD, 0xE8, 0x96, 601
	thread	"Pastel Yellow", 0xED, 0xE5, 0x5D, 602
	thread	"Golden Puppy", 0xDF, 0xA2, 0x00, 609
	thread	"Buttercup", 0xFD, 0xE8, 0x96, 612
	thread	"Treasure Gold", 0xCE, 0xB2, 0x4C, 616
	thread	"Old Gold", 0xAD, 0x95, 0x3E, 619
	thread	"Pale Apricot", 0xFE, 0xF9, 0xEA, 627
	thread	"Tan", 0xBD, 0x95, 0x65, 628
	thread	"Mellow Yellow", 0xFD, 0xF7, 0x6C, 632
	thread	"Lemon", 0xED, 0xEF, 0x05, 633
	thread	"Amber", 0xF8, 0xC3, 0x00, 646
	thread	"Mandarina", 0xE7, 0x78, 0x17, 649
	thread	"Orange", 0xE6, 0x65, 0x35, 650
	thread	"Golden Rod", 0xC6, 0x96, 0x32, 652
	thread	"Light Olive", 0x98, 0x99, 0x6D, 653
	thread	"Bright Gold", 0xC9, 0x83, 0x00, 654
	thread	"Blue-Green", 0x00, 0x7B, 0x8D, 688
	thread	"Forrest Green", 0x00, 0x4D, 0x3D, 695
	thread	"Midnight Blue", 0x00, 0x7E, 0xBA, 697
	thread	"Med Red", 0xCF, 0x00, 0x40, 700
	thread	"Med Blue", 0x28, 0x43, 0x8C, 809
	thread	"Sweet Apricot", 0xD0, 0xB4, 0x78, 812
	thread	"Skin", 0xE5, 0xBE, 0x6C, 818
	thread	"Jade", 0x44, 0x92, 0x84, 825
	thread	"Light Silver", 0xCF, 0xCF, 0xCF, 829
	thread	"Papaya Whip", 0xDC, 0x87, 0x5E, 831
	thread	"Cooper", 0xB4, 0x70, 0x5D, 832
	thread	"Light Pecan", 0x9B, 0x5C, 0x4B, 833
	thread	"Burnt Rust", 0xA9, 0x31, 0x21, 838
	thread	"Vegas Gold", 0xB1, 0x8B, 0x00, 842
	thread	"Med Brown", 0x86, 0x46, 0x2E, 857
	thread	"Med Russett", 0x61, 0x41, 0x25, 859
	thread	"Med Copper", 0xB2, 0x5C, 0x31, 864
	thread	"Dark Driftwood", 0x80, 0x6A, 0x61, 873
	thread	"Birch", 0x63, 0x48, 0x31, 878
	thread	"Dark Chocolate", 0x1A, 0x0C, 0x06, 891
	thread	"Sky Blue 2", 0x96, 0xD5, 0xC8, 903
	thread	"Aquamarine", 0xB4, 0xDC, 0xD8, 904
	thread	"Golden Brown", 0xAF, 0x7D, 0x3E, 905
	thread	"Sea Blue", 0x00, 0xA3, 0xA0, 906
	thread	"Deep Sea", 0x00, 0x40, 0x5D, 913
	thread	"Pastel Mint", 0xC9, 0xE3, 0xC5, 947
	thread	"True Green", 0x55, 0xAF, 0x78, 949
	thread	"Med Olive", 0x85, 0x83, 0x25, 951
	thread	"Olive", 0x61, 0x60, 0x1C, 955
	thread	"Light Jade", 0x70, 0x91, 0x88, 961
	thread	"Smith Apple", 0xBE, 0xDC, 0x8C, 984
	thread	"Light Lime", 0xBE, 0xE6, 0x78, 985
	thread	"Grass Green", 0x76, 0xC8, 0x50, 988
	thread	"Deep Teal", 0x46, 0x6E, 0x64, 448
	thread	"Med Forrest Green", 0x35, 0x69, 0x36, 992
	thread	"Deep Violet", 0x4B, 0x48, 0x84, 1031
	thread	"Light Natural", 0xED, 0xED, 0xD2, 1140
	thread	"Wheat", 0xF3, 0xD8, 0xA8, 1145
	thread	"Desert Sand", 0xC8, 0xBE, 0x96, 1148
	thread	"Egyptian Blue", 0x24, 0x3A, 0x7D, 1163
	thread	"Gecko", 0x86, 0xBE, 0x4E, 1183
	thread	"Burgandy", 0x8E, 0x40, 0x44, 1241
	thread	"Med Orchid", 0x89, 0x34, 0x80, 1323
	thread	"Med Purple", 0x8C, 0x6D, 0xAA, 1324
	thread	"Very Old Gold", 0xB6, 0xA3, 0x6C, 1552
	thread	"Light Spruce", 0x2E, 0x9F, 0x76, 1615
	thread	"Paris Green", 0x98, 0xC1, 0x73, 1619
	thread	"Timberwolf", 0xCD, 0xCD, 0xCD, 1707
	thread	"Bright Blue", 0x2A, 0x37, 0x7E, 2031
	thread	"Turquoise Blue", 0x00, 0x6C, 0xA5, 2093
	thread	"Dark Wine", 0x83, 0x44, 0x55, 2250
	thread	"Beige", 0xD0, 0xA4, 0x4F, 2518
	thread	"Gold", 0xED, 0x92, 0x06, 2519
	thread	"Med Orange", 0xED, 0xEF, 0x05, 3001
	thread	"Dark Salmon", 0xC0, 0x7A, 0x46, 3014
	thread	"Fire Red", 0xB4, 0x3C, 0x3C, 3015
	thread	"Saddle Brown", 0x91, 0x5F, 0x46, 3142
	thread	"Yellow Sun", 0xFF, 0xC5, 0x00, 4117
	thread	"Deep Taupe", 0xA6, 0x8A, 0x68, 4371
	thread	"Sky Blue", 0x00, 0xA4, 0xD9, 4419
	thread	"Wild Peacock", 0x0B, 0x7F, 0x85, 4627
	thread	"Millard Green", 0x00, 0x2D, 0x1F, 4735
	thread	"Dark Blue", 0x11, 0x26, 0x3C, 5552
	thread	"Powder Blue", 0x91, 0xB9, 0xE2, 5554
	thread	"Froggy Green", 0x42, 0x96, 0x48, 5557
	thread	"Stone Grey", 0x87, 0x8C, 0x8C, 8010
	thread	"END", 0, 0, 0, -1


sulky_rayon_codes:
	thread	"Cornsilk", 0xEF, 0xC8, 0x10, 502
	thread	"Deep Arctic Sky", 0x0C, 0x08, 0x2D, 505
	thread	"Nutmeg", 0xB2, 0x6C, 0x29, 521
	thread	"Autumn Gold", 0xE7, 0x90, 0x02, 523
	thread	"English Green", 0x34, 0x48, 0x1E, 525
	thread	"Cobalt Blue", 0x11, 0x36, 0x75, 526
	thread	"Forest Green", 0x11, 0x14, 0x08, 538
	thread	"Lipstick", 0xE1, 0x00, 0x00, 561
	thread	"Spice", 0xFF, 0xB4, 0x35, 562
	thread	"Butterfly Gold", 0xF3, 0xA0, 0x01, 567
	thread	"Cinnamon", 0xE6, 0x6D, 0x00, 568
	thread	"Garden Green", 0x16, 0x5F, 0x28, 569
	thread	"Deep Aqua", 0x08, 0x8E, 0x6C, 571
	thread	"Blue Ribbon", 0x10, 0x0A, 0x7C, 572
	thread	"Mint Julep", 0x35, 0x69, 0x3D, 580
	thread	"Dusty Peach", 0xE9, 0xBD, 0x96, 619
	thread	"Sunset", 0xCD, 0x39, 0x00, 621
	thread	"Moss Green", 0x77, 0x71, 0x13, 630
	thread	"Med. Aqua", 0x1C, 0x6F, 0x51, 640
	thread	"Arctic Sky", 0x26, 0x23, 0x45, 643
	thread	"Bright White", 0xF9, 0xF9, 0xFF, 1001
	thread	"Soft White", 0xF9, 0xF9, 0xF4, 1002
	thread	"Black", 0x00, 0x00, 0x00, 1005
	thread	"Steel Gray", 0xB7, 0xA9, 0xAC, 1011
	thread	"Med. Peach", 0xE1, 0xAF, 0x9A, 1015
	thread	"Pastel Coral", 0xEC, 0x96, 0x8C, 1016
	thread	"Pastel Peach", 0xEF, 0xDF, 0xBD, 1017
	thread	"Peach", 0xEC, 0xA0, 0x82, 1019
	thread	"Dark Peach", 0xF0, 0x82, 0x78, 1020
	thread	"Maple", 0xEB, 0x66, 0x02, 1021
	thread	"Cream", 0xFF, 0xF7, 0xD5, 1022
	thread	"Yellow", 0xFF, 0xE6, 0x69, 1023
	thread	"Goldenrod", 0xFF, 0xB8, 0x00, 1024
	thread	"Mine Gold", 0xD7, 0x80, 0x00, 1025
	thread	"Baby Blue", 0xBE, 0xC3, 0xE1, 1028
	thread	"Med. Blue", 0xA0, 0xC3, 0xEB, 1029
	thread	"Periwinkle", 0xA6, 0xA2, 0xC6, 1030
	thread	"Med. Orchid", 0xDF, 0xBE, 0xC8, 1031
	thread	"Med. Purple", 0xE6, 0x8C, 0xEB, 1032
	thread	"Dk. Orchid", 0xD8, 0x64, 0x96, 1033
	thread	"Burgundy", 0xC6, 0x32, 0x3C, 1034
	thread	"Dk. Burgundy", 0x79, 0x00, 0x00, 1035
	thread	"Lt.Red", 0xF9, 0x00, 0x00, 1037
	thread	"True Red", 0xEB, 0x00, 0x00, 1039
	thread	"Med. Dk. Khaki", 0x87, 0x73, 0x75, 1040
	thread	"Med. Dk. Gray", 0x8C, 0x7F, 0x83, 1041
	thread	"Bright Navy Blue", 0x32, 0x1E, 0x50, 1042
	thread	"Dk. Navy", 0x19, 0x05, 0x25, 1043
	thread	"Midnight Blue", 0x1D, 0x06, 0x2F, 1044
	thread	"Lt. Teal", 0xC3, 0xEF, 0xBF, 1045
	thread	"Teal", 0x2E, 0x83, 0x59, 1046
	thread	"Mint Green", 0xA6, 0xC2, 0x84, 1047
	thread	"Grass Green", 0x42, 0xA0, 0x21, 1049
	thread	"Xmas Green", 0x1E, 0x64, 0x19, 1051
	thread	"Med. Dk. Ecru", 0xEE, 0xBE, 0xAE, 1054
	thread	"Tawny Tan", 0xEB, 0xBC, 0x80, 1055
	thread	"Med Tawny Tan", 0xAF, 0x5B, 0x00, 1056
	thread	"Dk Tawny Tan", 0x64, 0x27, 0x02, 1057
	thread	"Tawny Brown", 0x66, 0x35, 0x00, 1058
	thread	"Dk Tawny Brown", 0x53, 0x06, 0x01, 1059
	thread	"Pale Yellow", 0xFF, 0xF7, 0xB9, 1061
	thread	"Pale Yellow-Green", 0xF0, 0xF8, 0xEC, 1063
	thread	"Pale Peach", 0xE6, 0xB4, 0xAA, 1064
	thread	"Orange Yellow", 0xFF, 0x91, 0x00, 1065
	thread	"Primrose", 0xFF, 0xF1, 0x80, 1066
	thread	"Lemon Yellow", 0xFF, 0xFF, 0x85, 1067
	thread	"Pink Tint", 0xF3, 0xDB, 0xD9, 1068
	thread	"Gold", 0xF6, 0xCE, 0x69, 1070
	thread	"Off White", 0xF9, 0xF9, 0xEA, 1071
	thread	"Pale Powder Blue", 0xD6, 0xD5, 0xE8, 1074
	thread	"Royal Blue", 0x5A, 0x5A, 0x8B, 1076
	thread	"Jade Tint", 0xBE, 0xCD, 0xC8, 1077
	thread	"Tangerine", 0xFF, 0x66, 0x00, 1078
	thread	"Emerald Green", 0x17, 0x55, 0x23, 1079
	thread	"Orchid", 0xDC, 0x82, 0xA0, 1080
	thread	"Brick", 0xF0, 0x6E, 0x78, 1081
	thread	"Ecru", 0xF7, 0xE3, 0xBB, 1082
	thread	"Spark Gold", 0xFF, 0xC1, 0x00, 1083
	thread	"Silver", 0xE2, 0xCF, 0xC7, 1085
	thread	"Pale Sea Foam", 0xF9, 0xF9, 0xE0, 1086
	thread	"Deep Peacock", 0x16, 0x62, 0x5F, 1090
	thread	"Med Turquoise", 0x26, 0xBF, 0xCA, 1094
	thread	"Turquoise", 0x10, 0xD1, 0xBD, 1095
	thread	"Dk Turquoise", 0x0F, 0x69, 0x78, 1096
	thread	"Lt Grass Green", 0xC2, 0xD3, 0x7D, 1100
	thread	"True Green", 0x09, 0x85, 0x31, 1101
	thread	"Dk Khaki", 0x02, 0x14, 0x0F, 1103
	thread	"Pastel Yellow-Grn", 0xA5, 0xAF, 0x68, 1104
	thread	"Lt Mauve", 0xFA, 0xA4, 0xA4, 1108
	thread	"Hot Pink", 0xDC, 0x64, 0x96, 1109
	thread	"Pastel Orchid", 0xFC, 0xCB, 0xDF, 1111
	thread	"Royal Purple", 0x46, 0x01, 0x6E, 1112
	thread	"Pastel Mauve", 0xF0, 0xC8, 0xB4, 1113
	thread	"Lt Pink", 0xF0, 0xB9, 0xB9, 1115
	thread	"Mauve", 0xF5, 0xA9, 0xA0, 1117
	thread	"Dk Mauve", 0xB4, 0x6E, 0x75, 1119
	thread	"Pale Pink", 0xF0, 0xD6, 0xD2, 1120
	thread	"Pink", 0xFA, 0xB9, 0xCB, 1121
	thread	"Purple", 0x82, 0x28, 0x8E, 1122
	thread	"Sun Yellow", 0xFF, 0xEC, 0x00, 1124
	thread	"Tan", 0xDC, 0x8C, 0x17, 1126
	thread	"Med Ecru", 0xFA, 0xEC, 0xC6, 1127
	thread	"Dk Ecru", 0xC3, 0x94, 0x71, 1128
	thread	"Brown", 0x6A, 0x1F, 0x06, 1129
	thread	"Dark Brown", 0x55, 0x16, 0x02, 1130
	thread	"Cloister Brown", 0x49, 0x00, 0x02, 1131
	thread	"Peacock Blue", 0x50, 0x7D, 0xAA, 1134
	thread	"Pastel Yellow", 0xFF, 0xF0, 0x72, 1135
	thread	"Yellow Orange", 0xFF, 0xBE, 0x00, 1137
	thread	"True Blue", 0x4A, 0x58, 0x70, 1143
	thread	"Powder Blue", 0xB4, 0xE1, 0xEB, 1145
	thread	"Xmas Red", 0xEB, 0x00, 0x00, 1147
	thread	"Lt Coral", 0xFF, 0xBD, 0xBD, 1148
	thread	"Deep Ecru", 0xE8, 0xC8, 0x9C, 1149
	thread	"Powder Blue Tint", 0xE2, 0xE2, 0xEB, 1151
	thread	"Coral", 0xFA, 0x99, 0x99, 1154
	thread	"Lt Army Green", 0x63, 0x63, 0x27, 1156
	thread	"Dk Maple", 0xBA, 0x45, 0x00, 1158
	thread	"Temple Gold", 0xD3, 0x9D, 0x00, 1159
	thread	"Deep Teal", 0x10, 0x39, 0x4A, 1162
	thread	"Lt Sky Blue", 0xDF, 0xE5, 0xEB, 1165
	thread	"Med Steel Gray", 0x8E, 0x7E, 0x7E, 1166
	thread	"Maize Yellow", 0xFF, 0xD2, 0x26, 1167
	thread	"True Orange", 0xF5, 0x74, 0x0A, 1168
	thread	"Bayberry Red", 0x9C, 0x00, 0x00, 1169
	thread	"Lt Brown", 0x97, 0x5F, 0x2F, 1170
	thread	"Weathered Blue", 0x08, 0x18, 0x0E, 1171
	thread	"Med Weathered Blue", 0x6E, 0x78, 0x8C, 1172
	thread	"Med Army Green", 0x59, 0x59, 0x1D, 1173
	thread	"Dk Pine Green", 0x0D, 0x29, 0x04, 1174
	thread	"Dk Avocado", 0x15, 0x2D, 0x04, 1175
	thread	"Med Dk Avocado", 0x51, 0x53, 0x08, 1176
	thread	"Avocado", 0x89, 0x98, 0x12, 1177
	thread	"Dk Taupe", 0x8F, 0x62, 0x3D, 1179
	thread	"Med Taupe", 0xA5, 0x89, 0x73, 1180
	thread	"Rust", 0xCB, 0x00, 0x00, 1181
	thread	"Blue Black", 0x02, 0x01, 0x14, 1182
	thread	"Black Cherry", 0x32, 0x06, 0x14, 1183
	thread	"Orange Red", 0xFF, 0x66, 0x00, 1184
	thread	"Golden Yellow", 0xFC, 0xBE, 0x05, 1185
	thread	"Sable Brown", 0x5B, 0x00, 0x00, 1186
	thread	"Mimosa Yellow", 0xFF, 0xE5, 0x00, 1187
	thread	"Red Geranium", 0xFF, 0x00, 0x4B, 1188
	thread	"Dk Chestnut", 0x4B, 0x12, 0x2D, 1189
	thread	"Med Burgundy", 0xA0, 0x46, 0x56, 1190
	thread	"Dk Rose", 0xBD, 0x1E, 0x60, 1191
	thread	"Fuchsia", 0xD2, 0x1E, 0x82, 1192
	thread	"Lavender", 0xE6, 0xAF, 0xD2, 1193
	thread	"Lt Purple", 0xD2, 0x74, 0xD7, 1194
	thread	"Dk Purple", 0x37, 0x01, 0x50, 1195
	thread	"Blue", 0x96, 0xC3, 0xE1, 1196
	thread	"Med Navy", 0x22, 0x0F, 0x34, 1197
	thread	"Dusty Navy", 0x3C, 0x50, 0x75, 1198
	thread	"Admiral Navy Blue", 0x2A, 0x14, 0x3F, 1199
	thread	"Med Dk Navy", 0x14, 0x0B, 0x2D, 1200
	thread	"Med Powder Blue", 0x64, 0x8B, 0xBE, 1201
	thread	"Deep Turquoise", 0x18, 0x2B, 0x56, 1202
	thread	"Lt Weathered Blue", 0xAE, 0xB8, 0xC3, 1203
	thread	"Pastel Jade", 0xA8, 0xC8, 0xBC, 1204
	thread	"Med Jade", 0x6E, 0x90, 0xA5, 1205
	thread	"Dark Jade", 0x1E, 0x6E, 0x6F, 1206
	thread	"Sea Foam Green", 0x80, 0xA3, 0x88, 1207
	thread	"Mallard Green", 0x0C, 0x3D, 0x03, 1208
	thread	"Lt Avocado", 0xBD, 0xD1, 0x63, 1209
	thread	"Dk Army Green", 0x27, 0x3B, 0x00, 1210
	thread	"Lt Khaki", 0x95, 0xA4, 0x90, 1211
	thread	"Khaki", 0x63, 0x63, 0x2D, 1212
	thread	"Taupe", 0xB9, 0xA0, 0x96, 1213
	thread	"Med Chestnut", 0x64, 0x28, 0x28, 1214
	thread	"Blackberry", 0x50, 0x0A, 0x1E, 1215
	thread	"Med Maple", 0xAC, 0x1C, 0x01, 1216
	thread	"Chestnut", 0x97, 0x1F, 0x01, 1217
	thread	"Silver Gray", 0xDF, 0xDF, 0xCB, 1218
	thread	"Gray", 0x98, 0x88, 0x8C, 1219
	thread	"Charcoal Gray", 0x76, 0x59, 0x60, 1220
	thread	"Lt Baby Blue", 0xD1, 0xDB, 0xFF, 1222
	thread	"Baby Blue Tint", 0xDC, 0xE0, 0xF1, 1223
	thread	"Bright Pink", 0xF0, 0xA0, 0xB9, 1224
	thread	"Pastel Pink", 0xFA, 0xCB, 0xCB, 1225
	thread	"Dkl Periwinkle", 0x57, 0x36, 0x9E, 1226
	thread	"Gold Green", 0xAF, 0x89, 0x01, 1227
	thread	"Drab Green", 0x96, 0xAA, 0x8B, 1228
	thread	"Lt Putty", 0xE0, 0xDB, 0xDB, 1229
	thread	"Dk Teal", 0x0B, 0x41, 0x33, 1230
	thread	"Med Rose", 0xE5, 0x32, 0x6A, 1231
	thread	"Classic Green", 0x19, 0x32, 0x07, 1232
	thread	"Ocean Teal", 0x0D, 0x22, 0x10, 1233
	thread	"Almost Black", 0x3C, 0x1B, 0x1F, 1234
	thread	"Deep Purple", 0x78, 0x32, 0x98, 1235
	thread	"Lt Silver", 0xEA, 0xE4, 0xE4, 1236
	thread	"Deep Mauve", 0xBC, 0x3D, 0x2C, 1237
	thread	"Orange Sunrise", 0xFF, 0x83, 0x00, 1238
	thread	"Apricot", 0xFF, 0xAB, 0x57, 1239
	thread	"Smokey Grey", 0x74, 0x58, 0x6C, 1240
	thread	"Nassau Blue", 0x54, 0x3A, 0x8D, 1242
	thread	"Orange Flame", 0xFF, 0x00, 0x00, 1246
	thread	"Mahogany", 0x66, 0x00, 0x00, 1247
	thread	"Med Pastel Blue", 0xD2, 0xE6, 0xF0, 1248
	thread	"Cornflower Blue", 0x62, 0xAA, 0xDC, 1249
	thread	"Duck Wing Blue", 0x27, 0x5C, 0x70, 1250
	thread	"Bright Turquoise", 0x30, 0x6F, 0x75, 1251
	thread	"Bright Peacock", 0x09, 0xA1, 0xA8, 1252
	thread	"Dk Sapphire", 0x1B, 0x4C, 0xA4, 1253
	thread	"Dusty Lavender", 0xE6, 0xB9, 0xF5, 1254
	thread	"Deep Orchid", 0xBE, 0x19, 0x82, 1255
	thread	"Sweet Pink", 0xEB, 0x82, 0x96, 1256
	thread	"Deep Coral", 0xE6, 0x00, 0x41, 1257
	thread	"Coral Reed", 0xF0, 0xC4, 0xA0, 1258
	thread	"Salmon Peach", 0xE2, 0x82, 0x64, 1259
	thread	"Red Jubilee", 0xB3, 0x00, 0x00, 1263
	thread	"Cognac", 0x6A, 0x00, 0x00, 1264
	thread	"Burnt Toast", 0x9B, 0x6B, 0x2C, 1265
	thread	"Toast", 0x9C, 0x6D, 0x45, 1266
	thread	"Mink Brown", 0x86, 0x4C, 0x31, 1267
	thread	"Light Gray Khaki", 0xEF, 0xEF, 0xE5, 1268
	thread	"Dk Gray Khaki", 0xB7, 0xB7, 0xAF, 1270
	thread	"Evergreen", 0x3C, 0x4F, 0x31, 1271
	thread	"Hedge Green", 0x4A, 0x4A, 0x19, 1272
	thread	"Nile Green", 0x5C, 0x9A, 0x1A, 1274
	thread	"Sea Mist", 0xE0, 0xE6, 0xC8, 1275
	thread	"Pistachio", 0x70, 0x77, 0x0F, 1276
	thread	"Ivy Green", 0x02, 0x76, 0x02, 1277
	thread	"Bright Green", 0x00, 0xAF, 0x38, 1278
	thread	"Willow Green", 0x93, 0xD1, 0x6C, 1279
	thread	"Dk Willow Green", 0x46, 0xB7, 0x74, 1280
	thread	"Slate Gray", 0x48, 0x3D, 0x59, 1283
	thread	"Dk Winter Sky", 0x46, 0x6E, 0x78, 1284
	thread	"Dk Sage Green", 0x13, 0x4F, 0x45, 1285
	thread	"Dk French Green", 0x34, 0x32, 0x13, 1286
	thread	"French Green", 0x41, 0x55, 0x45, 1287
	thread	"Aqua", 0x0F, 0xA5, 0x6F, 1288
	thread	"Ice Blue", 0xDC, 0xEB, 0xF0, 1289
	thread	"Winter Sky", 0x72, 0x74, 0x83, 1291
	thread	"Heron Blue", 0xD1, 0xDC, 0xFA, 1292
	thread	"Deep Nassau Blue", 0x44, 0x23, 0x5D, 1293
	thread	"Deep Slate Gray", 0x41, 0x20, 0x44, 1294
	thread	"Sterling", 0x82, 0x87, 0x8C, 1295
	thread	"Hyacinth", 0xD2, 0xAA, 0xF0, 1296
	thread	"Lt Plum", 0x73, 0x5A, 0x64, 1297
	thread	"Dk Plum", 0x64, 0x46, 0x64, 1298
	thread	"Purple Shadow", 0x41, 0x14, 0x46, 1299
	thread	"Plum", 0x7E, 0x1E, 0x46, 1300
	thread	"Deep Eggplant", 0x32, 0x00, 0x46, 1301
	thread	"Eggplant", 0x6E, 0x0A, 0x96, 1302
	thread	"Dewberry", 0xB4, 0x73, 0x64, 1304
	thread	"Sage Green", 0xAE, 0xC6, 0xBB, 1305
	thread	"Gun Metal Gray", 0x7E, 0x6C, 0x7C, 1306
	thread	"Petal Pink", 0xDB, 0x64, 0x78, 1307
	thread	"Magenta", 0x78, 0x23, 0x46, 1309
	thread	"Mulberry", 0x96, 0x1A, 0x32, 1311
	thread	"Wine", 0x84, 0x00, 0x00, 1312
	thread	"Bittersweet", 0xFC, 0x8F, 0x0C, 1313
	thread	"Poppy", 0xFF, 0x00, 0x00, 1317
	thread	"Gray Khaki", 0xCB, 0xCB, 0xBD, 1321
	thread	"Chartreuse", 0x81, 0x89, 0x01, 1322
	thread	"Whisper Gray", 0xF8, 0xF5, 0xF1, 1325
	thread	"Dk Whisper Gray", 0xD5, 0xC7, 0xC3, 1327
	thread	"Nickel Gray", 0xC0, 0xB2, 0xB7, 1328
	thread	"Dk Nickel Gray", 0xAB, 0xA0, 0xA8, 1329
	thread	"Pale Green", 0xED, 0xF6, 0xD4, 1331
	thread	"Deep Chartreuse", 0x86, 0x81, 0x05, 1332
	thread	"Sunflower Gold", 0xF3, 0xB6, 0x00, 1333
	thread	"Green Peacock", 0x34, 0x96, 0x69, 1503
	thread	"Putty", 0xC1, 0xCB, 0xB9, 1508
	thread	"Lime Green", 0x7A, 0xB3, 0x1D, 1510
	thread	"Deep Rose", 0xEE, 0x50, 0x78, 1511
	thread	"Wild Peacock", 0x00, 0x7A, 0x67, 1513
	thread	"Rosebud", 0xFF, 0x8C, 0xCB, 1515
	thread	"Coachman Green", 0x01, 0x4F, 0x3A, 1517
	thread	"Lt Rose", 0xCD, 0x05, 0x4D, 1533
	thread	"Sapphire", 0x34, 0x7D, 0xCB, 1534
	thread	"Team Blue", 0x23, 0x23, 0x8B, 1535
	thread	"Midnight Teal", 0x08, 0x17, 0x05, 1536
	thread	"Peach Fluff", 0xFF, 0xD6, 0xC7, 1543
	thread	"Purple Accent", 0x9C, 0x64, 0x84, 1545
	thread	"Flax", 0xE6, 0xAE, 0x6F, 1549
	thread	"Desert Cactus", 0x6C, 0x8E, 0x87, 1550
	thread	"Ocean Aqua", 0x80, 0xB0, 0xAE, 1551
	thread	"Dk Desert Cactus", 0x6C, 0x7C, 0x71, 1552
	thread	"Purple Passion", 0x8C, 0x74, 0x8C, 1554
	thread	"Tea Rose", 0xEB, 0x71, 0x83, 1558
	thread	"Marine Aqua", 0x68, 0xE0, 0xF8, 1560
	thread	"Deep Hyacinth", 0xB5, 0x8C, 0xC7, 1561
	thread	"Shrimp", 0xFA, 0xD2, 0xAA, 1800
	thread	"Flesh", 0xFA, 0xDC, 0x96, 1801
	thread	"Soft Blush", 0xFF, 0xC8, 0x96, 1802
	thread	"Island Peach", 0xFF, 0x9B, 0x6E, 1803
	thread	"Bayou Blue", 0x37, 0x5A, 0x73, 1804
	thread	"Ocean View", 0x28, 0x50, 0x5A, 1805
	thread	"Madras Blue", 0xA0, 0xB9, 0xC3, 1806
	thread	"Soft Heather", 0xB4, 0x96, 0x82, 1807
	thread	"Velvet Slipper", 0xD2, 0xAF, 0x9B, 1808
	thread	"Iced Mauve", 0xA0, 0x7D, 0x82, 1809
	thread	"Wild Mulberry", 0x64, 0x50, 0x55, 1810
	thread	"Wineberry", 0x3C, 0x28, 0x37, 1811
	thread	"Wildflower", 0x6E, 0x2D, 0x5A, 1812
	thread	"Plum Wine", 0x6E, 0x2D, 0x41, 1813
	thread	"Orchid Kiss", 0xAF, 0x4B, 0x69, 1814
	thread	"Japanese Fern", 0x91, 0xB4, 0x32, 1815
	thread	"Honeydew", 0xD7, 0xF5, 0x8C, 1816
	thread	"Lemon Grass", 0xAA, 0xAF, 0x14, 1817
	thread	"Fairway Mist", 0xC8, 0xF5, 0x8C, 1818
	thread	"Outback", 0xC3, 0x91, 0x3C, 1819
	thread	"Fruit Shake", 0xC3, 0x8C, 0x73, 1820
	thread	"Creamy Peach", 0xFA, 0xC8, 0x96, 1821
	thread	"Toffee", 0x96, 0x5A, 0x37, 1822
	thread	"Cocoa", 0x96, 0x5A, 0x28, 1823
	thread	"Gentle Rain", 0xD2, 0xC3, 0xAF, 1824
	thread	"Barnyard Grass", 0x5F, 0x96, 0x19, 1825
	thread	"Galley Gold", 0xAA, 0x82, 0x0A, 1826
	thread	"Coral Sunset", 0xFF, 0x64, 0x3C, 1827
	thread	"Seashell", 0xFF, 0xE6, 0xAA, 1828
	thread	"Crème Brulee", 0xF0, 0xEB, 0xA5, 1829
	thread	"Lilac", 0xB4, 0x73, 0x96, 1830
	thread	"Liimeade", 0x91, 0xE1, 0x2D, 1831
	thread	"Desert Glow", 0xE1, 0x91, 0x19, 1832
	thread	"Pumpkin Pie", 0xD2, 0x5F, 0x00, 1833
	thread	"Pea Soup", 0xAF, 0xAA, 0x05, 1834
	thread	"Peapod Green", 0x6E, 0x82, 0x05, 1835
	thread	"Loden Green", 0x3C, 0x4B, 0x05, 1836
	thread	"Lt. Cocoa", 0x9B, 0x73, 0x5A, 1837
	thread	"Cocoa Cream", 0xCD, 0xAA, 0x7D, 1838
	thread	"Cameo", 0x87, 0xC8, 0x87, 1839
	thread	"Sand", 0xF9, 0xE6, 0xCA, 508
	thread	"Bone", 0xFD, 0xF3, 0xDA, 520
	thread	"Dark Ash", 0x5D, 0x34, 0x46, 1241
	thread	"Spring Moss", 0xE0, 0xC6, 0x3B, 1243
	thread	"Summer Gold", 0xDD, 0xAB, 0x00, 1260
	thread	"Dk. Autumn Gold", 0xA9, 0x88, 0x03, 1262
	thread	"Mushroom", 0xAC, 0x87, 0x83, 1269
	thread	"Dark Forest", 0x36, 0x36, 0x1F, 1273
	thread	"Watermelon", 0xFA, 0x5F, 0x7F, 1303
	thread	"Caribbean Mist", 0xA3, 0xC2, 0xD7, 1644
	thread	"END", 0, 0, 0, -1


thread_art_rayon_codes:
	thread	"END", 0, 0, 0, -1


thread_art_polyester_codes:
	thread	"END", 0, 0, 0, -1


threadelight_polyester_codes:
	thread	"END", 0, 0, 0, -1


z102_isacord_polyester_codes:
	thread	"?", 0xF8, 0xFF, 0xFF, 17
	thread	"?", 0x00, 0x00, 0x00, 20
	thread	"?", 0xB7, 0xBA, 0xBA, 105
	thread	"?", 0x73, 0x78, 0x7A, 108
	thread	"?", 0x45, 0x4B, 0x58, 138
	thread	"?", 0x9E, 0xA9, 0xA6, 142
	thread	"?", 0xC8, 0xC6, 0xBD, 150
	thread	"?", 0xFA, 0xEE, 0x5C, 220
	thread	"?", 0xE5, 0xCB, 0x4F, 221
	thread	"?", 0xFF, 0xF4, 0x6A, 230
	thread	"?", 0xFE, 0xF9, 0xD9, 270
	thread	"?", 0xFF, 0xDC, 0x00, 311
	thread	"?", 0x62, 0x4F, 0x00, 345
	thread	"?", 0xB8, 0xB2, 0x5A, 352
	thread	"?", 0x8D, 0x8F, 0x5B, 453
	thread	"?", 0xFF, 0xF4, 0xA5, 520
	thread	"?", 0xB9, 0x8E, 0x03, 542
	thread	"?", 0xE4, 0xC1, 0x80, 651
	thread	"?", 0xC5, 0xBF, 0xA6, 672
	thread	"?", 0x96, 0x83, 0x6D, 722
	thread	"?", 0x4E, 0x35, 0x00, 747
	thread	"?", 0xDD, 0xCB, 0xA5, 761
	thread	"?", 0x60, 0x58, 0x40, 776
	thread	"?", 0xFF, 0xAF, 0x02, 800
	thread	"?", 0xF6, 0xAE, 0x32, 811
	thread	"?", 0xC8, 0x93, 0x34, 822
	thread	"?", 0xE5, 0x93, 0x00, 824
	thread	"?", 0xC8, 0x93, 0x40, 832
	thread	"?", 0x9E, 0x94, 0x7F, 873
	thread	"?", 0xC8, 0x70, 0x0B, 922
	thread	"?", 0xBB, 0x57, 0x04, 931
	thread	"?", 0xB1, 0x90, 0x72, 1061
	thread	"?", 0xFF, 0x81, 0x01, 1102
	thread	"?", 0xB1, 0x50, 0x0A, 1115
	thread	"?", 0xC0, 0x9C, 0x72, 1123
	thread	"?", 0x84, 0x3D, 0x07, 1134
	thread	"?", 0xD8, 0xA6, 0x7D, 1141
	thread	"?", 0x82, 0x42, 0x1B, 1154
	thread	"?", 0xFF, 0x73, 0x19, 1300
	thread	"?", 0xFF, 0x3D, 0x1E, 1305
	thread	"?", 0xBA, 0x40, 0x05, 1311
	thread	"?", 0xC7, 0x3C, 0x13, 1312
	thread	"?", 0xE6, 0x6B, 0x21, 1332
	thread	"?", 0x3D, 0x1C, 0x11, 1346
	thread	"?", 0xFF, 0xBC, 0x95, 1351
	thread	"?", 0xFF, 0xCC, 0x93, 1362
	thread	"?", 0x37, 0x37, 0x32, 1375
	thread	"?", 0xFF, 0xAF, 0x94, 1532
	thread	"?", 0x5B, 0x40, 0x32, 1565
	thread	"?", 0xFF, 0x60, 0x46, 1600
	thread	"?", 0xFF, 0x6D, 0x71, 1753
	thread	"?", 0xEB, 0xBA, 0xAE, 1755
	thread	"?", 0xEB, 0x2D, 0x2B, 1805
	thread	"?", 0xFF, 0x98, 0x8F, 1840
	thread	"?", 0x43, 0x43, 0x31, 1874
	thread	"?", 0xC1, 0x19, 0x14, 1902
	thread	"?", 0xC8, 0x10, 0x0D, 1903
	thread	"?", 0xBF, 0x0A, 0x21, 1906
	thread	"?", 0xD2, 0x3C, 0x3E, 1921
	thread	"?", 0x8F, 0x8C, 0x93, 1972
	thread	"?", 0xA3, 0x1A, 0x1C, 2011
	thread	"?", 0x4D, 0x03, 0x08, 2115
	thread	"?", 0xFF, 0xCD, 0xCC, 2155
	thread	"?", 0x87, 0x1C, 0x45, 2500
	thread	"?", 0xDB, 0x40, 0x83, 2508
	thread	"?", 0xFF, 0x66, 0x8A, 2520
	thread	"?", 0xC9, 0x12, 0x43, 2521
	thread	"?", 0xFF, 0xA0, 0xB6, 2530
	thread	"?", 0xFE, 0xA5, 0xB9, 2550
	thread	"?", 0x62, 0x6C, 0x7E, 2674
	thread	"?", 0x5E, 0x19, 0x42, 2711
	thread	"?", 0x33, 0x00, 0x1D, 2715
	thread	"?", 0xA5, 0x7B, 0x8D, 2764
	thread	"?", 0x70, 0x2A, 0x69, 2810
	thread	"?", 0xB3, 0x85, 0xBC, 2830
	thread	"?", 0x24, 0x00, 0x47, 2900
	thread	"?", 0x72, 0x45, 0x93, 2910
	thread	"?", 0x63, 0x4D, 0x86, 2920
	thread	"?", 0x00, 0x01, 0x36, 3110
	thread	"?", 0x00, 0x00, 0x21, 3355
	thread	"?", 0x05, 0x4A, 0xBD, 3522
	thread	"?", 0x1C, 0x00, 0x5D, 3541
	thread	"?", 0x00, 0x1F, 0x71, 3544
	thread	"?", 0x00, 0x2E, 0x5E, 3622
	thread	"?", 0x71, 0xAA, 0xD8, 3630
	thread	"?", 0x00, 0x17, 0x48, 3644
	thread	"?", 0xC8, 0xDB, 0xE4, 3650
	thread	"?", 0x9F, 0xC7, 0xDF, 3730
	thread	"?", 0x08, 0x2E, 0x4D, 3743
	thread	"?", 0x98, 0xB0, 0xBC, 3750
	thread	"?", 0x23, 0x67, 0x9C, 3810
	thread	"?", 0x3D, 0x65, 0x7E, 3842
	thread	"?", 0x00, 0x66, 0x9F, 3901
	thread	"?", 0x47, 0xAE, 0xDD, 3910
	thread	"?", 0xBB, 0xDF, 0xEB, 3962
	thread	"?", 0xBA, 0xBE, 0xB7, 3971
	thread	"?", 0x01, 0x5D, 0x7E, 4032
	thread	"?", 0xD5, 0xDD, 0xDB, 4071
	thread	"?", 0x88, 0x8D, 0x8E, 4073
	thread	"?", 0x00, 0x7C, 0xA6, 4103
	thread	"?", 0x3E, 0xBB, 0xC8, 4111
	thread	"?", 0x00, 0x5C, 0x79, 4116
	thread	"?", 0x80, 0xCC, 0xD8, 4240
	thread	"?", 0xAC, 0xCE, 0xC7, 4250
	thread	"?", 0x00, 0x6E, 0x74, 4410
	thread	"?", 0x00, 0x2A, 0x29, 4515
	thread	"?", 0x38, 0xA4, 0xAE, 4620
	thread	"?", 0xAF, 0xD8, 0xCD, 5050
	thread	"?", 0x14, 0x9B, 0x7B, 5210
	thread	"?", 0x7A, 0xC8, 0xAF, 5220
	thread	"?", 0x18, 0x71, 0x66, 5233
	thread	"?", 0x00, 0x4B, 0x23, 5374
	thread	"?", 0x00, 0x68, 0x35, 5415
	thread	"?", 0x5C, 0x9C, 0x51, 5531
	thread	"?", 0x0E, 0x95, 0x43, 5613
	thread	"?", 0x5E, 0x7A, 0x17, 5833
	thread	"?", 0x22, 0x59, 0x26, 5944
	thread	"?", 0xBC, 0xD6, 0x33, 6011
	thread	"?", 0xBB, 0xCD, 0x91, 6051
	thread	"?", 0x97, 0x8B, 0x3C, 6133
	thread	"END", 0, 0, 0, -1

%if 0
brand_codes:
	dd	arc_polyester_codes	; 0
	dd	arc_rayon_codes		; 1
	dd	coats_and_clark_rayon_codes	; 2
	dd	exquisite_polyester_codes	; 3
	dd	fufu_polyester_codes	; 4
	dd	fufu_rayon_codes	; 5
	dd	hemingworth_polyester_codes ; 6
;	Isacord_Polyester_codes	; 7
;	Isafil_Rayon_codes	; 8
;	Marathon_Polyester_codes	; 9
;	Marathon_Rayon_codes	; 10
;	Madeira_Polyester_codes	; 11
;	Madeira_Rayon_codes, /* 12 */
;	Metro_Polyester_codes, /* 13 */
;	Pantone_codes, /* 14 */
;	RobisonAnton_Polyester_codes, /* 15 */
;	RobisonAnton_Rayon_codes, /* 16 */
;	Sigma_Polyester_codes, /* 17 */
;	Sulky_Rayon_codes, /* 18 */
;	ThreadArt_Rayon_codes, /* 19 */
;	ThreadArt_Polyester_codes, /* 20 */
;	ThreaDelight_Polyester_codes, /* 21 */
;	Z102_Isacord_Polyester_codes, /* 22 */
;	svg_color_codes /* 23 */

; Based on the DraftSight color table
dxf_color_table:
	db	0, 0, 0		; BYBLOCK
	db	255, 0, 0	; red
	db	255, 255, 0	; yellow
	db	0, 255, 0	; green
	db	0, 255, 255	; cyan
	db	0, 0, 255	; blue
	db	255, 0, 255	; magenta
	db	255, 255, 255	; white
	db	128, 128, 128	; dark gray
	db	192, 192, 192	; light gray
	db	255, 0, 0	; 10
	db	255, 127, 127	; 11
	db	204, 0, 0	; 12
	db	204, 102, 102	; 13
	db	153, 0, 0	; 14
	db	153, 76, 76	; 15
	db	127, 0, 0	; 16
	db	127, 63, 63	; 17
	db	76, 0, 0	; 18
	db	76, 38, 38	; 19
	db	255, 63, 0	; 20
	db	255, 159, 127	; 21
	db	204, 51, 0	; 22
	db	204, 127, 102	; 23
	db	153, 38, 0	; 24
	db	153, 95, 76	; 25
	db	127, 31, 0	; 26
	db	127, 79, 63	; 27
	db	76, 19, 0	; 28
	db	76, 47, 38	; 29
	db	255, 127, 0	; 30
	db	255, 191, 127	; 31
	db	204, 102, 0	; 32
	db	204, 153, 102	; 33
	db	153, 76, 0	; 34
	db	153, 114, 76	; 35
	db	127, 63, 0	; 36
	db	127, 95, 63	; 37
	db	76, 38, 0	; 38
	db	76, 57, 38	; 39
	db	255, 191, 0	; 40
	db	255, 223, 127	; 41
	db	204, 153, 0	; 42
	db	204, 178, 102	; 43
	db	153, 114, 0	; 44
	db	153, 133, 76	; 45
	db	127, 95, 0	; 46
	db	127, 111, 63	; 47
	db	76, 57, 0	; 48
	db	76, 66, 38	; 49
	db	255, 255, 0	; 50
	db	255, 255, 127	; 51
	db	204, 204, 0	; 52
	db	204, 204, 102	; 53
	db	153, 153, 0	; 54
	db	153, 153, 76	; 55
	db	127, 127, 0	; 56
	db	127, 127, 63	; 57
	db	76, 76, 0	; 58
	db	76, 76, 38	; 59
	db	191, 255, 0	; 60
	db	223, 255, 127	; 61
	db	153, 204, 0	; 62
	db	178, 204, 102	; 63
	db	114, 153, 0	; 64
	db	133, 153, 76	; 65
	db	95, 127, 0	; 66
	db	111, 127, 63	; 67
	db	57, 76, 0	; 68
	db	66, 76, 38	; 69
	db	127, 255, 0	; 70
	db	191, 255, 127	; 71
	db	102, 204, 0	; 72
	db	153, 204, 102	; 73
	db	76, 153, 0	; 74
	db	114, 153, 76	; 75
	db	63, 127, 0	; 76
	db	95, 127, 63	; 77
	db	38, 76, 0	; 78
	db	57, 76, 38	; 79
	db	63, 255, 0	; 80
	db	159, 255, 127	; 81
	db	51, 204, 0	; 82
	db	127, 204, 102	; 83
	db	38, 153, 0	; 84
	db	95, 153, 76	; 85
	db	31, 127, 0	; 86
	db	79, 127, 63	; 87
	db	19, 76, 0	; 88
	db	47, 76, 38	; 89
	db	0, 255, 0	; 90
	db	127, 255, 127	; 91
	db	0, 204, 0	; 92
	db	102, 204, 102	; 93
	db	0, 153, 0	; 94
	db	76, 153, 76	; 95
	db	0, 127, 0	; 96
	db	63, 127, 63	; 97
	db	0, 76, 0	; 98
	db	38, 76, 38	; 99
	db	0, 255, 63	; 100
	db	127, 255, 159	; 101
	db	0, 204, 51	; 102
	db	102, 204, 127	; 103
	db	0, 153, 38	; 104
	db	76, 153, 95	; 105
	db	0, 127, 31	; 106
	db	63, 127, 79	; 107
	db	0, 76, 19	; 108
	db	38, 76, 47	; 109
	db	0, 255, 127	; 110
	db	127, 255, 191	; 111
	db	0, 204, 102	; 112
	db	102, 204, 153	; 113
	db	0, 153, 76	; 114
	db	76, 153, 114	; 115
	db	0, 127, 63	; 116
	db	63, 127, 95	; 117
	db	0, 76, 38	; 118
	db	38, 76, 57	; 119
	db	0, 255, 191	; 120
	db	127, 255, 223	; 121
	db	0, 204, 153	; 122
	db	102, 204, 178	; 123
	db	0, 153, 114	; 124
	db	76, 153, 133	; 125
	db	0, 127, 95	; 126
	db	63, 127, 111	; 127
	db	0, 76, 57	; 128
	db	38, 76, 66	; 129
	db	0, 255, 255	; 130
	db	127, 255, 255	; 131
	db	0, 204, 204	; 132
	db	102, 204, 204	; 133
	db	0, 153, 153	; 134
	db	76, 153, 153	; 135
	db	0, 127, 127	; 136
	db	63, 127, 127	; 137
	db	0, 76, 76	; 138
	db	38, 76, 76	; 139
	db	0, 191, 255	; 140
	db	127, 223, 255	; 141
	db	0, 153, 204	; 142
	db	102, 178, 204	; 143
	db	0, 114, 153	; 144
	db	76, 133, 153	; 145
	db	0, 95, 127	; 146
	db	63, 111, 127	; 147
	db	0, 57, 76	; 148
	db	38, 66, 76	; 149
	db	0, 127, 255	; 150
	db	127, 191, 255	; 151
	db	0, 102, 204	; 152
	db	102, 153, 204	; 153
	db	0, 76, 153	; 154
	db	76, 114, 153	; 155
	db	0, 63, 127	; 156
	db	63, 95, 127	; 157
	db	0, 38, 76	; 158
	db	38, 57, 76	; 159
	db	0, 63, 255	; 160
	db	127, 159, 255	; 161
	db	0, 51, 204	; 162
	db	102, 127, 204	; 163
	db	0, 38, 153	; 164
	db	76, 95, 153	; 165
	db	0, 31, 127	; 166
	db	63, 79, 127	; 167
	db	0, 19, 76	; 168
	db	38, 47, 76	; 169
	db	0, 0, 255	; 170
	db	127, 127, 255	; 171
	db	0, 0, 204	; 172
	db	102, 102, 204	; 173
	db	0, 0, 153	; 174
	db	76, 76, 153	; 175
	db	0, 0, 127	; 176
	db	63, 63, 127	; 177
	db	0, 0, 76	; 178
	db	38, 38, 76	; 179
	db	63, 0, 255	; 180
	db	159, 127, 255	; 181
	db	51, 0, 204	; 182
	db	127, 102, 204	; 183
	db	38, 0, 153	; 184
	db	95, 76, 153	; 185
	db	31, 0, 127	; 186
	db	79, 63, 127	; 187
	db	19, 0, 76	; 188
	db	47, 38, 76	; 189
	db	127, 0, 255	; 190
	db	191, 127, 255	; 191
	db	102, 0, 204	; 192
	db	153, 102, 204	; 193
	db	76, 0, 153	; 194
	db	114, 76, 153	; 195
	db	63, 0, 127	; 196
	db	95, 63, 127	; 197
	db	38, 0, 76	; 198
	db	57, 38, 76	; 199
	db	191, 0, 255	; 200
	db	223, 127, 255	; 201
	db	153, 0, 204	; 202
	db	178, 102, 204	; 203
	db	114, 0, 153	; 204
	db	133, 76, 153	; 205
	db	95, 0, 127	; 206
	db	111, 63, 127	; 207
	db	57, 0, 76	; 208
	db	66, 38, 76	; 209
	db	255, 0, 255	; 210
	db	255, 127, 255	; 211
	db	204, 0, 204	; 212
	db	204, 102, 204	; 213
	db	153, 0, 153	; 214
	db	153, 76, 153	; 215
	db	127, 0, 127	; 216
	db	127, 63, 127	; 217
	db	76, 0, 76	; 218
	db	76, 38, 76	; 219
	db	255, 0, 191	; 220
	db	255, 127, 223	; 221
	db	204, 0, 153	; 222
	db	204, 102, 178	; 223
	db	153, 0, 114	; 224
	db	153, 76, 133	; 225
	db	127, 0, 95	; 226
	db	127, 63, 111	; 227
	db	76, 0, 57	; 228
	db	76, 38, 66	; 229
	db	255, 0, 127	; 230
	db	255, 127, 191	; 231
	db	204, 0, 102	; 232
	db	204, 102, 153	; 233
	db	153, 0, 76	; 234
	db	153, 76, 114	; 235
	db	127, 0, 63	; 236
	db	127, 63, 95	; 237
	db	76, 0, 38	; 238
	db	76, 38, 57	; 239
	db	255, 0, 63	; 240
	db	255, 127, 159	; 241
	db	204, 0, 51	; 242
	db	204, 102, 127	; 243
	db	153, 0, 38	; 244
	db	153, 76, 95	; 245
	db	127, 0, 31	; 246
	db	127, 63, 79	; 247
	db	76, 0, 19	; 248
	db	76, 38, 47	; 249
	db	51, 51, 51	; 250
	db	91, 91, 91	; 251
	db	132, 132, 132	; 252
	db	173, 173, 173	; 253
	db	214, 214, 214	; 254
	db	255, 255, 255	; 255
	db	0, 0, 0	; 256 (BYLAYER)

husThreadCount:	db	29

; TODO: HUS catalog numbers
hus_thread_table:
	thread	"Black", 0, 0, 0, 0
	thread	"Blue", 0, 0, 255, 1
	thread	"Light Green", 0, 255, 0, 2
	thread	"Red", 255, 0, 0, 3
	thread	"Purple", 255, 0, 255, 4
	thread	"Yellow", 255, 255, 0, 5
	thread	"Gray", 127, 127, 127, 6
	thread	"Light Blue", 51, 154, 255, 7
	thread	"Green", 51, 204, 102, 8
	thread	"Orange", 255, 127, 0, 9
	thread	"Pink", 255, 160, 180, 10
	thread	"Brown", 153, 75, 0, 11
	thread	"White", 255, 255, 255, 12
	thread	"Dark Blue", 0, 0, 127, 13
;	thread2	{ 0, 127, 0, "Dark Green", 14
;	thread2	{ 127, 0, 0, "Dark Red", 15
;	thread2	{ 255, 127, 127, "Light Red", 16
;	thread	127, 0, 127, "Dark Purple", 17
;	thread	255, 127, 255, "Light Purple", 18
;	thread	200, 200, 0, "Dark Yellow", 19
;	thread	255, 255, 153, "Light Yellow", 20
;	thread	60, 60, 60, "Dark Gray", 21
;	thread	192, 192, 192, "Light Gray", 22
;	thread	232, 63, 0, "Dark Orange", 23
;	thread	255, 165, 65, "Light Orange", 24
;	thread	255, 102, 122, "Dark Pink", 25
;	thread	{ 255, 204, 204, "Light Pink", 26
	thread	"Dark Brown", 115, 40, 0, 27
	thread	"Light Brown", 175, 90, 10, 28


jef_thread_table:
	thread	"Black", 0, 0, 0, 0
	thread	"Black", 0, 0, 0, 1
	thread	"White", 255, 255, 255, 2
	thread	"Yellow", 255, 255, 23, 3
;	thread	{ 250, 160, 96, "Orange", 0
;	thread	{ 92, 118, 73, "Olive Green", 0
;	thread	{ 64, 192, 48, "Green", 0
;;	thread	{ 101, 194, 200, "Sky", 0
;	thread	{ 172, 128, 190, "Purple", 0
;	thread	{ 245, 188, 203, "Pink", 0
;	thread	{ 255, 0, 0, "Red", 0
;	thread	{ 192, 128, 0, "Brown", 0
;	thread	{ 0, 0, 240, "Blue", 0
;	thread	{ 228, 195, 93, "Gold", 0
;	thread	{ 165, 42, 42, "Dark Brown", 0
;	thread	{ 213, 176, 212, "Pale Violet", 0
;	thread	{ 252, 242, 148, "Pale Yellow", 0
;	thread	{ 240, 208, 192, "Pale Pink", 0
;	thread	{ 255, 192, 0, "Peach", 0
;;	thread	{ 201, 164, 128, "Beige", 0
;	thread	{ 155, 61, 75, "Wine Red", 0
;	thread	{ 160, 184, 204, "Pale Sky", 0
;	thread	{ 127, 194, 28, "Yellow Green", 0
;	thread	{ 185, 185, 185, "Silver Grey", 0
;	thread	{ 160, 160, 160, "Grey", 0
;	thread	{ 152, 214, 189, "Pale Aqua", 0
;	thread	{ 184, 240, 240, "Baby Blue", 0
;	thread	{ 54, 139, 160, "Powder Blue", 0
;	dd	""
;	thread	{ 79, 131, 171, "Bright Blue", 0
;	dd	""
;	thread	{ 56, 106, 145, "Slate Blue", 0
;	dd	""
;	thread	{ 0, 32, 107, "Nave Blue", 0
;	dd	""
;	thread	{ 229, 197, 202, "Salmon Pink", 0
;	dd	""
;	thread	{ 249, 103, 107, "Coral", 0
;	dd	""
;	thread	{ 227, 49, 31, "Burnt Orange", 0
;	dd	""
;	thread	{ 226, 161, 136, "Cinnamon", 0
;	dd	""
;	thread	{ 181, 148, 116, "Umber", 0
;	dd	""
;	thread	{ 228, 207, 153, "Blonde", 0
;	dd	""
;	thread	{ 225, 203, 0, "Sunflower", 0
;	dd	""
;	thread	{ 225, 173, 212, "Orchid Pink", 0
;	dd	""
;	thread	{ 195, 0, 126, "Peony Purple", 0
;	dd	""
;	thread	{ 128, 0, 75, "Burgundy", 0
;	dd	""
;	thread	{ 160, 96, 176, "Royal Purple", 0
;	dd	""
;;	thread	{ 192, 64, 32, "Cardinal Red", 0
;	dd	""
;	thread	{ 202, 224, 192, "Opal Green", 0
;	dd	""
;	thread	{ 137, 152, 86, "Moss Green", 0
;	dd	""
;	thread	{ 0, 170, 0, "Meadow Green", 0
;	dd	""
;	thread	{ 33, 138, 33, "Dark Green", 0
;	dd	""
;	thread	{ 93, 174, 148, "Aquamarine", 0
;	dd	""
;	thread	{ 76, 191, 143, "Emerald Green", 0
;	dd	""
;	thread	{ 0, 119, 114, "Peacock Green", 0
;	dd	""
;	thread	{ 112, 112, 112, "Dark Grey", 0
;	dd	""
;	thread	{ 242, 255, 255, "Ivory White", 0
;	dd	""
;	thread	{ 177, 88, 24, "Hazel", 0
;	dd	""
;	thread	{ 203, 138, 7, "Toast", 0
;	dd	""
;;	thread	{ 247, 146, 123, "Salmon", 0
;	dd	""
;	thread	{ 152, 105, 45, "Cocoa Brown", 0
;	dd	""
;	thread	{ 162, 113, 72, "Sienna", 0
;	dd	""
;	thread	{ 123, 85, 74, "Sepia", 0
;	dd	""
;	thread	{ 79, 57, 70, "Dark Sepia", 0
;	dd	""
;	thread	{ 82, 58, 151, "Violet Blue", 0
;	dd	""
;	thread	{ 0, 0, 160, "Blue Ink", 0
;	dd	""
;	thread	{ 0, 150, 222, "Solar Blue", 0
;	dd	""
;	thread	{ 178, 221, 83, "Green Dust", 0
;	dd	""
;	thread	{ 250, 143, 187, "Crimson", 0
;	dd	""
;	thread	{ 222, 100, 158, "Floral Pink", 0
;	dd	""
;	thread	{ 181, 80, 102, "Wine", 0
;	dd	""
;	thread	{ 94, 87, 71, "Olive Drab", 0
;	dd	""
;	thread	{ 76, 136, 31, "Meadow", 0
;	dd	""
;	thread	{ 228, 220, 121, "Mustard", 0
;	dd	""
;	thread	{ 203, 138, 26, "Yellow Ochre", 0
;	dd	""
;	thread	{ 198, 170, 66, "Old Gold", 0
;	dd	""
;	thread	{ 236, 176, 44, "Honeydew", 0
;	dd	""
;	thread	{ 248, 128, 64, "Tangerine", 0
;	dd	""
;	thread	{ 255, 229, 5, "Canary Yellow", 0
;	dd	""
;	thread	{ 250, 122, 122, "Vermillion", 0
;	dd	""
;	thread	{ 107, 224, 0, "Bright Green", 0
	thread	"Ocean Blue", 56, 108, 174, 0
	thread	"Beige Grey", 227, 196, 180, 0
	thread	"Bamboo", 227, 172, 129, 0


pcmThreadCount
	dd	65

pcmThreads:
	thread	"PCM Color 1", 0x00, 0x00, 0x00, 0
	thread	"PCM Color 2", 0x00, 0x00, 0x80, 0
	thread	"PCM Color 3", 0x00, 0x00, 0xFF, 0
	thread	"PCM Color 4", 0x00, 0x80, 0x80, 0
	thread	"PCM Color 5", 0x00, 0xFF, 0xFF, 0
	thread	"PCM Color 6", 0x80, 0x00, 0x80, 0
;	thread	{ 0xFF, 0x00, 0xFF, "PCM Color 7", 0
;	thread	{ 0x80, 0x00, 0x00, "PCM Color 8", 0
;	thread	{ 0xFF, 0x00, 0x00, "PCM Color 9", 0
;	thread	{ 0x00, 0x80, 0x00, "PCM Color 10", 0
;	thread	{ 0x00, 0xFF, 0x00, "PCM Color 11", 0
;	thread	{ 0x80, 0x80, 0x00, "PCM Color 12", 0
;	thread	{ 0xFF, 0xFF, 0x00, "PCM Color 13", 0
;	thread	{ 0x80, 0x80, 0x80, "PCM Color 14", 0
;	thread	{ 0xC0, 0xC0, 0xC0, "PCM Color 15", 0
;	thread	{ 0xFF, 0xFF, 0xFF, "PCM Color 16", 0


;static const int pecThreadCount = 65;
;;static const EmbThread pecThreads[] = {
;	thread	{ 0, 0, 0, "Unknown", 0
;	dd	"", /* Index  0 */
;	thread	{ 14, 31, 124, "Prussian Blue", 0
;	dd	"", /* Index  1 */
;	thread	{ 10, 85, 163, "Blue", 0
;	dd	"", /* Index  2 */
;	thread	{ 0, 135, 119, "Teal Green", 0
;	dd	"", /* Index  3 */ /* TODO: Verify RGB value is correct */
;	thread	{ 75, 107, 175, "Cornflower Blue", 0
;	dd	"", /* Index  4 */
;	thread	{ 237, 23, 31, "Red", 0
;	dd	"", /* Index  5 */
;	thread	{ 209, 92, 0, "Reddish Brown", 0
;	dd	"", /* Index  6 */
;	thread	{ 145, 54, 151, "Magenta", 0
;	dd	"", /* Index  7 */
;	thread	{ 228, 154, 203, "Light Lilac", 0
;	dd	"", /* Index  8 */
;	thread	{ 145, 95, 172, "Lilac", 0
;	dd	"", /* Index  9 */
;	thread	{ 158, 214, 125, "Mint Green", 0
;	dd	"", /* Index 10 */ /* TODO: Verify RGB value is correct */
;	thread	{ 232, 169, 0, "Deep Gold", 0
;	dd	"", /* Index 11 */
;	thread	{ 254, 186, 53, "Orange", 0
;	dd	"", /* Index 12 */
;	thread	{ 255, 255, 0, "Yellow", 0
;	dd	"", /* Index 13 */
;	thread	{ 112, 188, 31, "Lime Green", 0
;	dd	"", /* Index 14 */
;	thread	{ 186, 152, 0, "Brass", 0
;	dd	"", /* Index 15 */
;	thread	{ 168, 168, 168, "Silver", 0
;	dd	"", /* Index 16 */
;	thread	{ 125, 111, 0, "Russet Brown", 0
;	dd	"", /* Index 17 */ /* TODO: Verify RGB value is correct */
;	thread	{ 255, 255, 179, "Cream Brown", 0
;	dd	"", /* Index 18 */
;	thread	{ 79, 85, 86, "Pewter", 0
;	dd	"", /* Index 19 */
;	thread	{ 0, 0, 0, "Black", 0
;	dd	"", /* Index 20 */
;	thread	{ 11, 61, 145, "Ultramarine", 0
;	dd	"", /* Index 21 */
;	thread	{ 119, 1, 118, "Royal Purple", 0
;	dd	"", /* Index 22 */
;	thread	{ 41, 49, 51, "Dark Gray", 0
;	dd	"", /* Index 23 */
;	thread	{ 42, 19, 1, "Dark Brown", 0
;	dd	"", /* Index 24 */
;	thread	{ 246, 74, 138, "Deep Rose", 0
;	dd	"", /* Index 25 */
;	thread	{ 178, 118, 36, "Light Brown", 0
;	dd	"", /* Index 26 */
;	thread	{ 252, 187, 197, "Salmon Pink", 0
;	dd	"", /* Index 27 */ /* TODO: Verify RGB value is correct */
;	thread	{ 254, 55, 15, "Vermillion", 0
;	dd	"", /* Index 28 */
;	thread	{ 240, 240, 240, "White", 0
;	dd	"", /* Index 29 */
;	thread	{ 106, 28, 138, "Violet", 0
;	dd	"", /* Index 30 */
;	thread	{ 168, 221, 196, "Seacrest", 0
;	dd	"", /* Index 31 */
;	thread	{ 37, 132, 187, "Sky Blue", 0
;	dd	"", /* Index 32 */
;	thread	{ 254, 179, 67, "Pumpkin", 0
;	dd	"", /* Index 33 */
;	thread	{ 255, 243, 107, "Cream Yellow", 0
;	dd	"", /* Index 34 */
;	thread	{ 208, 166, 96, "Khaki", 0
;	dd	"", /* Index 35 */
;	thread	{ 209, 84, 0, "Clay Brown", 0
;	dd	"", /* Index 36 */
;	thread	{ 102, 186, 73, "Leaf Green", 0
;	dd	"", /* Index 37 */
;	thread	{ 19, 74, 70, "Peacock Blue", 0
;	dd	"", /* Index 38 */
;	thread	{ 135, 135, 135, "Gray", 0
;	dd	"", /* Index 39 */
;	thread	{ 216, 204, 198, "Warm Gray", 0
;	dd	"", /* Index 40 */ /* TODO: Verify RGB value is correct */
;	thread	{ 67, 86, 7, "Dark Olive", 0
;	dd	"", /* Index 41 */
;	thread	{ 253, 217, 222, "Flesh Pink", 0
;	dd	"", /* Index 42 */ /* TODO: Verify RGB value is correct */
;	thread	{ 249, 147, 188, "Pink", 0
;	dd	"", /* Index 43 */
;	thread	{ 0, 56, 34, "Deep Green", 0
;	dd	"", /* Index 44 */
;	thread	{ 178, 175, 212, "Lavender", 0
;	dd	"", /* Index 45 */
;	thread	{ 104, 106, 176, "Wisteria Violet", 0
;	dd	"", /* Index 46 */
;	thread	{ 239, 227, 185, "Beige", 0
;	dd	"", /* Index 47 */
;	thread	{ 247, 56, 102, "Carmine", 0
;	dd	"", /* Index 48 */
;	thread	{ 181, 75, 100, "Amber Red", 0
;	dd	"", /* Index 49 */ /* TODO: Verify RGB value is correct */
;	thread	{ 19, 43, 26, "Olive Green", 0
;	dd	"", /* Index 50 */
;	thread	{ 199, 1, 86, "Dark Fuschia", 0
;	dd	"", /* Index 51 */ /* TODO: Verify RGB value is correct */
;	thread	{ 254, 158, 50, "Tangerine", 0
;	dd	"", /* Index 52 */
;	thread	{ 168, 222, 235, "Light Blue", 0
;	dd	"", /* Index 53 */
;	thread	{ 0, 103, 62, "Emerald Green", 0
;	dd	"", /* Index 54 */ /* TODO: Verify RGB value is correct */
;	thread	{ 78, 41, 144, "Purple", 0
;	dd	"", /* Index 55 */
;	thread	{ 47, 126, 32, "Moss Green", 0
;	dd	"", /* Index 56 */
;	thread	{ 255, 204, 204, "Flesh Pink", 0
;	dd	"", /* Index 57 */ /* TODO: Verify RGB value is correct */ /* TODO: Flesh Pink is Index 42, is this Index incorrect? */
;	thread	{ 255, 217, 17, "Harvest Gold", 0
;	dd	"", /* Index 58 */
;	thread	{ 9, 91, 166, "Electric Blue", 0
;	dd	"", /* Index 59 */
;	thread	{ 240, 249, 112, "Lemon Yellow", 0
;	dd	"", /* Index 60 */
;	thread	{ 227, 243, 91, "Fresh Green", 0
;	dd	"", /* Index 61 */
;	thread	{ 255, 153, 0, "Orange", 0
;	dd	"", /* Index 62 */ /* TODO: Verify RGB value is correct */ /* TODO: Orange is Index 12, is this Index incorrect? */
;	thread	{ 255, 240, 141, "Cream Yellow", 0
;	dd	"", /* Index 63 */ /* TODO: Verify RGB value is correct */ /* TODO: Cream Yellow is Index 34, is this Index incorrect? */
;	thread	{ 255, 200, 200, "Applique", 0
;	dd	"" } /* Index 64 */


; SHV Colors
; TODO: catalog numbers

shvThreadCount:
	db	42

shvThreads:
	thread	"Black", 0, 0, 0, 0
	thread	"Blue", 0, 0, 255, 0
	thread	"Green", 51, 204, 102, 0
	thread	"Red", 255, 0, 0, 0
	thread	"Purple", 255, 0, 255, 0
	thread	"Yellow", 255, 255, 0, 0
	thread	"Grey", 127, 127, 127, 0
	thread	51, 154, 255, "Light Blue", 0
	thread	0, 255, 0, "Light Green", 0
	thread	255, 127, 0, "Orange", 0
	thread	255, 160, 180, "Pink", 0
	thread	153, 75, 0, "Brown", 0
	thread	255, 255, 255, "White", 0
	thread	0, 0, 0, "Black", 0
	thread	0, 0, 0, "Black", 0
	thread	0, 0, 0, "Black", 0
	thread	0, 0, 0, "Black", 0
	thread	0, 0, 0, "Black", 0
	thread	0, 0, 0, "Black", 0
	thread	255, 127, 127, "Light Red", 0
	thread	255, 127, 255, "Light Purple", 0
	thread	255, 255, 153, "Light Yellow", 0
	thread	192, 192, 192, "Light Grey", 0
	thread	0, 0, 0, "Black", 0
	thread	0, 0, 0, "Black", 0
	thread	255, 165, 65, "Light Orange", 0
	thread	255, 204, 204, "Light Pink", 0
	thread	175, 90, 10, "Light Brown", 0
	thread	0, 0, 0, "Black", 0
	thread	0, 0, 0, "Black", 0
	thread	0, 0, 0, "Black", 0
	thread	0, 0, 0, "Black", 0
	thread	0, 0, 0, "Black", 0
	thread	0, 0, 127, "Dark Blue", 0
	thread	0, 127, 0, "Dark Green", 0
	thread	127, 0, 0, "Dark Red", 0
	thread	127, 0, 127, "Dark Purple", 0
	thread	200, 200, 0, "Dark Yellow", 0
	thread	60, 60, 60, "Dark Gray", 0
	thread	0, 0, 0, "Black", 0
	thread	0, 0, 0, "Black", 0
	thread	232, 63, 0, "Dark Orange", 0
	thread	255, 102, 122, "Dark Pink", 0

%endif
;-------------------------------------------------------------------------------
;	String table
;-------------------------------------------------------------------------------

audio_level_token:
	db	"audio-level", 0
buffered_rendering_token:
	db	"buffered-rendering", 0
color_token:
	db	"color", 0
color_rendering_token:
	db	"color-rendering", 0
direction_token:
	db	"direction", 0
display_token:
	db	"display", 0
display_align_token:
	db	"display-align", 0
fill_token:
	db	"fill", 0
fill_opacity_token:
	db	"fill-opacity", 0
fill_rule_token:
	db	"fill-rule", 0
font_family_token:
	db	"font-family", 0
font_size_token:
	db	"font-size", 0
font_style_token:
	db	"font-style", 0
font_variant_token:
	db	"font-variant", 0
font_weight_token:
	db	"font-weight", 0
image_rendering_token:
	db	"image-rendering", 0
line_increment_token:
	db	"line-increment", 0
opacity_token:
	db	"opacity", 0
pointer_events_token:
	db	"pointer-events", 0
shape_rendering_token:
	db	"shape-rendering", 0
solid_color_token:
	db	"solid-color", 0
solid_opacity_token:
	db	"solid-opacity", 0
stop_color_token:
	db	"stop-color", 0
stop_opacity_token:
	db	"stop-opacity", 0
stroke_token:
	db	"stroke", 0
stroke_dasharray_token:
	db	"stroke-dasharray", 0
stroke_linecap_token:
	db	"stroke-linecap", 0
stroke_linejoin_token:
	db	"stroke-linejoin", 0
stroke_miterlimit_token:
	db	"stroke-miterlimit", 0
stroke_opacity_token:
	db	"stroke-opacity", 0
stroke_width_token:
	db	"stroke-width", 0
text_align_token:
	db	"text-align", 0
text_anchor_token:
	db	"text-anchor", 0
text_rendering_token:
	db	"text-rendering", 0
unicode_bidi_token:
	db	"unicode-bidi", 0
vector_effect_token:
	db	"vector-effect", 0
viewport_fill_token:
	db	"viewport-fill", 0
viewport_fill_opacity_token:
	db	"viewport-fill-opacity", 0
visibility_token:
	db	"visibility", 0
about_token:
	db	"about", 0
accent_height_token:
	db	"accent-height", 0
accumulate_token:
	db	"accumulate", 0
additive_token:
	db	"additive", 0
alphabetic_token:
	db	"alphabetic", 0
arabic_form_token:
	db	"arabic-form", 0
ascent_token:
	db	"ascent", 0
attribute_name_token:
	db	"attributeName", 0
attribute_type_token:
	db	"attributeType", 0
bandwidth_token:
	db	"bandwidth", 0
base_profile_token:
	db	"baseProfile", 0
bbox_token:
	db	"bbox", 0
begin_token:
	db	"begin", 0
by_token:
	db	"by", 0
calc_mode_token:
	db	"calcMode", 0
cap_height_token:
	db	"cap-height", 0
class_token:
	db	"class", 0
content_token:
	db	"content", 0
content_script_type_token:
	db	"contentScriptType", 0
cx_token:
	db	"cx", 0
cy_token:
	db	"cy", 0
d_token:
	db	"d", 0
datatype_token:
	db	"datatype", 0
default_action_token:
	db	"defaultAction", 0
descent_token:
	db	"descent", 0
dur_token:
	db	"dur", 0
editable_token:
	db	"editable", 0
end_token:
	db	"end", 0
ev_event_token:
	db	"ev:event", 0
event_token:
	db	"event", 0
external_resources_required_token:
	db	"externalResourcesRequired", 0
focus_highlight_token:
	db	"focusHighlight", 0
focusable_token:
	db	"focusable", 0
font_stretch_token:
	db	"font-stretch", 0
from_token:
	db	"from", 0
g1_token:
	db	"g1", 0
g2_token:
	db	"g2", 0
glyph_name_token:
	db	"glyph-name", 0
gradient_units_token:
	db	"gradientUnits", 0
handler_token:
	db	"handler", 0
hanging_token:
	db	"hanging", 0
height_token:
	db	"height", 0
horiz_adv_x_token:
	db	"horiz-adv-x", 0
horiz_origin_x_token:
	db	"horiz-origin-x", 0
id_token:
	db	"id", 0
ideographic_token:
	db	"ideographic", 0
initial_visibility_token:
	db	"initialVisibility", 0
k_token:
	db	"k", 0
key_points_token:
	db	"keyPoints", 0
key_splines_token:
	db	"keySplines", 0
key_times_token:
	db	"keyTimes", 0
lang_token:
	db	"lang", 0
mathematical_token:
	db	"mathematical", 0
max_token:
	db	"max", 0
media_character_encoding_token:
	db	"mediaCharacterEncoding", 0
media_content_encoding_token:
	db	"mediaContentEncodings", 0
media_size_token:
	db	"mediaSize", 0
media_time_token:
	db	"mediaTime", 0
min_token:
	db	"min", 0
nav_down_token:
	db	"nav-down", 0
nav_down_left_token:
	db	"nav-down-left", 0
nav_down_right_token:
	db	"nav-down-right", 0
nav_left_token:
	db	"nav-left", 0
nav_next_token:
	db	"nav-next", 0
nav_prev_token:
	db	"nav-prev", 0
nav_right_token:
	db	"nav-right", 0
nav_up_token:
	db	"nav-up", 0
nav_up_left_token:
	db	"nav-up-left", 0
nav_up_right_token:
	db	"nav-up-right", 0
observer_token:
	db	"observer", 0
offset_token:
	db	"offset", 0
origin_token:
	db	"origin", 0
overlay_token:
	db	"overlay", 0
overline_position_token:
	db	"overline-position", 0
overline_thickness_token:
	db	"overline-thickness", 0
panose_1_token:
	db	"panose-1", 0
path_token:
	db	"path", 0
path_length_token:
	db	"pathLength", 0
phase_token:
	db	"phase", 0
playback_order_token:
	db	"playbackOrder", 0
points_token:
	db	"points", 0
preserve_aspect_ratio_token:
	db	"preserveAspectRatio", 0
propagate_token:
	db	"propagate", 0
property_token:
	db	"property", 0
r_token:
	db	"r", 0
rel_token:
	db	"rel", 0
repeat_count_token:
	db	"repeatCount", 0
repeat_dur_token:
	db	"repeatDur", 0
required_extensions_token:
	db	"requiredExtensions", 0
required_features_token:
	db	"requiredFeatures", 0
required_fonts_token:
	db	"requiredFonts", 0
required_formats_token:
	db	"requiredFormats", 0
resource_token:
	db	"resource", 0
restart_token:
	db	"restart", 0
rev_token:
	db	"rev", 0
role_token:
	db	"role", 0
rotate_token:
	db	"rotate", 0
rx_token:
	db	"rx", 0
ry_token:
	db	"ry", 0
slope_token:
	db	"slope", 0
snapshot_time_token:
	db	"snapshotTime", 0
stemh_token:
	db	"stemh", 0
stemv_token:
	db	"stemv", 0
strikethrough_position_token:
	db	"strikethrough-position", 0
strikethrough_thickness_token:
	db	"strikethrough-thickness", 0
sync_behavior_token:
	db	"syncBehavior", 0
sync_behavior_default_token:
	db	"syncBehaviorDefault", 0
sync_master_token:
	db	"syncMaster", 0
sync_tolerance_token:
	db	"syncTolerance", 0
sync_tolerance_default_token:
	db	"syncToleranceDefault", 0
system_language_token:
	db	"systemLanguage", 0
target_token:
	db	"target", 0
timeline_begin_token:
	db	"timelineBegin", 0
to_token:
	db	"to", 0
transform_token:
	db	"transform", 0
transform_behavior_token:
	db	"transformBehavior", 0
type_token:
	db	"type", 0
typeof_token:
	db	"typeof", 0
u1_token:
	db	"u1", 0
u2_token:
	db	"u2", 0
underline_position_token:
	db	"underline-position", 0
underline_thickness_token:
	db	"underline-thickness", 0
unicode_token:
	db	"unicode", 0
unicode_range_token:
	db	"unicode-range", 0
units_per_em_token:
	db	"units-per-em", 0
values_token:
	db	"values", 0
version_token:
	db	"version", 0
viewbox_token:
	db	"viewBox", 0
width_token:
	db	"width", 0
widths_token:
	db	"widths", 0
x_token:
	db	"x", 0
x_height_token:
	db	"x-height", 0
x1_token:
	db	"x1", 0
x2_token:
	db	"x2", 0
xlink_actuate_token:
	db	"xlink:actuate", 0
xlink_arcrole_token:
	db	"xlink:arcrole",
xlink_href_token:
	db	"xlink:href", 0
xlink_role_token:
	db	"xlink:role", 0
xlink_show_token:
	db	"xlink:show", 0
xlink_title_token:
	db	"xlink:title", 0
xlink_type_token:
	db	"xlink:type",
xml_base_token:
	db	"xml:base", 0
xml_id_token:
	db	"xml:id", 0
xml_lang_token:
	db	"xml:lang", 0
xml_space_token:
	db	"xml:space", 0
y_token:
	db	"y", 0
y1_token:
	db	"y1", 0
y2_token:
	db	"y2", 0
zoom_and_pan_token:
	db	"zoomAndPan", 0
slash_token:
	db	"/", 0

; svg elements
xml_token:
	db	"?xml", 0
a_token:
	db	"a", 0
animate_token:
	db	"animate", 0
animate_color_token:
	db	"animateColor", 0
animate_motion_token:
	db	"animateMotion", 0
animate_transform_token:
	db	"animateTransform", 0
animation_token:
	db	"animation", 0
audio_token:
	db	"audio", 0
circle_token:
	db	"circle", 0
defs_token:
	db	"defs", 0
desc_token:
	db	"desc", 0
discard_token:
	db	"discard", 0
ellipse_token:
	db	"ellipse", 0
font_token:
	db	"font", 0
font_face_token:
	db	"fontFace", 0
font_face_src_token:
	db	"fontFaceSrc", 0
font_face_uri_token:
	db	"fontFaceUri", 0
foreign_object_token:
	db	"foreign", 0
g_token:
	db	"g", 0
glyph_token:
	db	"glyph", 0
hkern_token:
	db	"hkern", 0
image_token:
	db	"image", 0
line_token:
	db	"line", 0
linear_gradient_token:
	db	"linearGradient", 0
listener_token:
	db	"listener", 0
metadata_token:
	db	"metadata", 0
missing_glyph_token:
	db	"missingGlyph", 0
mpath_token:
	db	"mpath", 0
polygon_token:
	db	"polygon", 0
polyline_token:
	db	"polyline", 0
prefetch_token:
	db	"prefetch", 0
radial_gradient_token:
	db	"radialGradient", 0
rect_token:
	db	"rect", 0
script_token:
	db	"script", 0
set_token:
	db	"set", 0
stop_token:
	db	"stop", 0
svg_token:
	db	"svg", 0
switch_token:
	db	"switch", 0
tbreak_token:
	db	"tbreak", 0
text_token:
	db	"text", 0
text_area_token:
	db	"textArea", 0
title_token:
	db	"title", 0
tspan_token:
	db	"tspan", 0
use_token:
	db	"use", 0
video_token:
	db	"video", 0

encoding_token:
	db	"encoding", 0
standalone_token:
	db	"standalone", 0
xmlns_token:
	db	"xmlns", 0
xmlns_svg_token:
	db	"xmlns:svg", 0
xmlns_rdf_token:
	db	"xmlns:rdf", 0
xmlns_dc_token:
	db	"xmlns:dc", 0
xmlns_cc_token:
	db	"xmlns:cc", 0

