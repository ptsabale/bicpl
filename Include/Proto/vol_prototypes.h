#ifndef  DEF_vol_prototypes
#define  DEF_vol_prototypes

public  Volume  create_box_filtered_volume(
    Volume   volume,
    nc_type  nc_data_type,
    BOOLEAN  sign_flag,
    Real     real_min_value,
    Real     real_max_value,
    Real     x_width,
    Real     y_width,
    Real     z_width );

public  void  modify_labels_in_range(
    Volume   volume,
    Volume   label_volume,
    int      src_label,
    int      dest_label,
    Real     min_threshold,
    Real     max_threshold );

public  void  initialize_colour_coding(
    colour_coding_struct   *colour_coding,
    Colour_coding_types    type,
    Colour                 under_colour,
    Colour                 over_colour,
    Real                   min_value,
    Real                   max_value );

public  void  set_colour_coding_type(
    colour_coding_struct   *colour_coding,
    Colour_coding_types    type );

public  void  set_colour_coding_min_max(
    colour_coding_struct   *colour_coding,
    Real                   min_value,
    Real                   max_value );

public  void  get_colour_coding_min_max(
    colour_coding_struct   *colour_coding,
    Real                   *min_value,
    Real                   *max_value );

public  Colour  get_colour_coding_under_colour(
    colour_coding_struct   *colour_coding );

public  void  set_colour_coding_under_colour(
    colour_coding_struct   *colour_coding,
    Colour                 under_colour );

public  Colour  get_colour_coding_over_colour(
    colour_coding_struct   *colour_coding );

public  void  set_colour_coding_over_colour(
    colour_coding_struct   *colour_coding,
    Colour                 over_colour );

public  Colour  get_colour_code(
    colour_coding_struct  *colour_coding,
    Real                  value );

public  void  colour_code_object(
    Volume                 volume,
    int                    continuity,
    colour_coding_struct   *colour_coding,
    object_struct          *object );

public  int    get_volume_cross_section(
    Volume   volume,
    Real     origin[],
    Real     x_axis[],
    Real     y_axis[],
    Real     clipped_voxels[][MAX_DIMENSIONS] );

public  void    get_volume_mapping_range(
    Volume   volume,
    Real     origin[],
    Real     x_axis[],
    Real     y_axis[],
    Real     x_trans,
    Real     y_trans,
    Real     x_scale,
    Real     y_scale,
    Real     *x_pixel_start,
    Real     *x_pixel_end,
    Real     *y_pixel_start,
    Real     *y_pixel_end );

public  void  create_volume_slice(
    Volume          volume1,
    Filter_types    filter_type1,
    Real            filter_width1,
    Real            slice_position1[],
    Real            x_axis1[],
    Real            y_axis1[],
    Real            x_translation1,
    Real            y_translation1,
    Real            x_scale1,
    Real            y_scale1,
    Volume          volume2,
    Filter_types    filter_type2,
    Real            filter_width2,
    Real            slice_position2[],
    Real            x_axis2[],
    Real            y_axis2[],
    Real            x_translation2,
    Real            y_translation2,
    Real            x_scale2,
    Real            y_scale2,
    int             x_viewport_size,
    int             y_viewport_size,
    Pixel_types     pixel_type,
    int             degrees_continuity,
    unsigned short  **cmode_colour_map,
    Colour          **rgb_colour_map,
    Colour          empty_colour,
    void            *render_storage,
    int             *n_pixels_alloced,
    pixels_struct   *pixels );

public  BOOLEAN  find_volume_crop_bounds(
    Volume          volume,
    Real            min_crop_threshold,
    Real            max_crop_threshold,
    int             limits[2][MAX_DIMENSIONS] );

public  Volume  create_cropped_volume(
    Volume          volume,
    int             limits[2][MAX_DIMENSIONS] );

public  void  dilate_labeled_voxels_3d(
    Volume          volume,
    Volume          label_volume,
    int             min_inside_label,
    int             max_inside_label,
    Real            min_inside_value,
    Real            max_inside_value,
    int             min_outside_label,
    int             max_outside_label,
    Real            min_outside_value,
    Real            max_outside_value,
    int             new_label,
    Neighbour_types connectivity );

public  int  get_slice_weights_for_filter(
    Volume         volume,
    Real           voxel_position[],
    Real           voxel_direction[],   /* if filter_type != NEAREST */
    Filter_types   filter_type,
    Real           full_width_half_max,
    Real           ***positions,
    Real           *weights[] );

public  BOOLEAN  fill_connected_voxels(
    Volume              volume,
    Volume              label_volume,
    Neighbour_types     connectivity,
    int                 voxel[],
    int                 min_label_threshold,
    int                 max_label_threshold,
    int                 desired_label,
    Real                min_threshold,
    Real                max_threshold );

public  int  get_neighbour_directions(
    Neighbour_types   connectivity,
    int               *dx[],
    int               *dy[] );

public  int  get_3D_neighbour_directions(
    Neighbour_types   connectivity,
    int               *dx[],
    int               *dy[],
    int               *dz[] );

public  BOOLEAN  should_change_this_one(
    Volume          volume,
    Volume          label_volume,
    int             voxel[],
    Real            min_threshold,
    Real            max_threshold,
    int             label_min_threshold,
    int             label_max_threshold,
    int             desired_label );

public  void  interpolate_volume_to_slice(
    Volume          volume1,
    int             n_dims1,
    int             sizes1[],
    Real            origin1[],
    Real            x_axis1[],
    Real            y_axis1[],
    Volume          volume2,
    int             n_dims2,
    int             sizes2[],
    Real            origin2[],
    Real            x_axis2[],
    Real            y_axis2[],
    int             degrees_continuity,
    unsigned short  **cmode_colour_map,
    Colour          **rgb_colour_map,
    Colour          empty_colour,
    pixels_struct   *pixels );

public  void  set_label_volume_real_range(
    Volume  volume );

public  Volume  create_label_volume(
    Volume  volume,
    nc_type type );

public  void  set_all_volume_label_data(
    Volume    volume,
    int       value );

public  void  set_volume_label_data(
    Volume          volume,
    int             voxel[],
    int             value );

public  int  get_volume_label_data(
    Volume          volume,
    int             voxel[] );

public  int  get_3D_volume_label_data(
    Volume          volume,
    int             x,
    int             y,
    int             z );

public  BOOLEAN  get_voxel_label_bit(
    Volume          volume,
    int             voxel[],
    int             bit );

public  void  set_voxel_label_bit(
    Volume          volume,
    int             voxel[],
    int             bit,
    BOOLEAN         value );

public  void  set_all_volume_label_data_bit(
    Volume         volume,
    int            bit,
    BOOLEAN        value );

public  BOOLEAN  get_volume_voxel_activity(
    Volume     volume,
    Real       voxel[],
    BOOLEAN    activity_if_mixed );

public  Status  load_label_volume(
    char     filename[],
    Volume   label_volume );

public  Status  save_label_volume(
    char     filename[],
    char     original_filename[],
    Volume   label_volume );

public  Status  input_tags_as_labels(
    FILE    *file,
    Volume  volume,
    Volume  label_volume );

public  Status  output_labels_as_tags(
    FILE    *file,
    Volume  volume,
    Volume  label_volume,
    int     desired_label,
    Real    size,
    int     patient_id );

public  Status  input_landmarks_as_labels(
    FILE    *file,
    Volume  volume,
    Volume  label_volume );

public  void  get_mapping(
    Volume          volume,
    Real            origin[],
    Real            x_axis[],
    Real            y_axis[],
    Real            x_translation,
    Real            y_translation,
    Real            x_scale,
    Real            y_scale,
    Real            pix_origin[],
    Real            pix_x_axis[],
    Real            pix_y_axis[] );

public  void  map_voxel_to_pixel(
    int    n,
    Real   voxel[],
    Real   origin[],
    Real   x_axis[],
    Real   y_axis[],
    Real   *x_pixel,
    Real   *y_pixel );

public  BOOLEAN  convert_slice_pixel_to_voxel(
    Volume          volume,
    Real            x_pixel,
    Real            y_pixel,
    Real            origin[],
    Real            x_axis[],
    Real            y_axis[],
    Real            x_translation,
    Real            y_translation,
    Real            x_scale,
    Real            y_scale,
    Real            voxel[] );

public  void  convert_voxel_to_slice_pixel(
    Volume          volume,
    Real            voxel[],
    Real            origin[],
    Real            x_axis[],
    Real            y_axis[],
    Real            x_translation,
    Real            y_translation,
    Real            x_scale,
    Real            y_scale,
    Real            *x_pixel,
    Real            *y_pixel );

public  void  resize_volume_slice(
    int          old_x_viewport_size,
    int          old_y_viewport_size,
    int          old_used_x_viewport_size,
    int          old_used_y_viewport_size,
    int          new_x_viewport_size,
    int          new_y_viewport_size,
    Real         *x_translation,
    Real         *y_translation,
    Real         *x_scale,
    Real         *y_scale,
    int          *used_x_viewport_size,
    int          *used_y_viewport_size );

public  void  fit_volume_slice_to_viewport(
    Volume       volume,
    Real         origin[],
    Real         x_axis[],
    Real         y_axis[],
    int          x_viewport_size,
    int          y_viewport_size,
    Real         fraction_oversize,
    Real         *x_translation,
    Real         *y_translation,
    Real         *x_scale,
    Real         *y_scale,
    int          *used_x_viewport_size,
    int          *used_y_viewport_size );

public  void   scale_slice_about_viewport_centre(
    Real        scale_factor,
    int         x_viewport_size,
    int         y_viewport_size,
    Real        *x_translation,
    Real        *y_translation,
    Real        *x_scale,
    Real        *y_scale );

public  BOOLEAN  voxel_is_within_volume(
    Volume   volume,
    Real     voxel_position[] );

public  BOOLEAN  int_voxel_is_within_volume(
    Volume   volume,
    int      indices[] );

public  void  convert_real_to_int_voxel(
    int      n_dimensions,
    Real     voxel[],
    int      int_voxel[] );

public  BOOLEAN  voxel_contains_range(
    Volume   volume,
    int      int_voxel[],
    Real     min_value,
    Real     max_value );

public  Status  output_volume_free_format(
    char           prefix[],
    Volume         volume,
    int            axis_ordering[] );

public  void   *initialize_render_storage();

public  void   delete_render_storage(
    void  *ptr );

public  void  render_volume_to_slice(
    int             n_dims1,
    int             sizes1[],
    void            *volume_data1,
    Data_types      volume1_type,
    int             n_slices1,
    Real            weights1[],
    int             strides1[],
    Real            **origins1,
    Real            x_axis1[],
    Real            y_axis1[],
    int             n_dims2,
    int             sizes2[],
    void            *volume_data2,
    Data_types      volume2_type,
    int             n_slices2,
    Real            weights2[],
    int             strides2[],
    Real            **origins2,
    Real            x_axis2[],
    Real            y_axis2[],
    unsigned short  **cmode_colour_map,
    Colour          **rgb_colour_map,
    Colour          empty_colour,
    void            *render_storage,
    pixels_struct   *pixels );

public  void  render_the_slice (
    void            *volume_data1,
    Data_types      volume1_type,
    int             y,
    int             start_x,
    int             end_x,
    int             **y_offsets1,
    int             **row_offsets1,
    void            **start_slices1,
    int             n_slices1,
    Real            weights1[],
    void            *volume_data2,
    Data_types      volume2_type,
    int             **y_offsets2,
    int             **row_offsets2,
    void            **start_slices2,
    int             n_slices2,
    Real            weights2[],
    unsigned short  **cmode_colour_map,
    Colour          **rgb_colour_map,
    pixels_struct   *pixels );

public  void  initialize_resample_volume(
    resample_struct      *resample,
    Volume               src_volume,
    General_transform    *dest_to_src_transform,
    Volume               dest_volume );

public  BOOLEAN  do_more_resampling(
    resample_struct  *resample,
    Real             max_seconds,
    Real             *fraction_done );

public  void  resample_volume(
    Volume                   src_volume,
    General_transform        *dest_to_src_transform,
    Volume                   dest_volume );

public  void  scan_lines_to_voxels(
    lines_struct     *lines,
    Volume           volume,
    Volume           label_volume,
    int              label );

public  void  scan_marker_to_voxels(
    marker_struct    *marker,
    Volume           volume,
    Volume           label_volume,
    int              label );

public  void  scan_object_to_volume(
    object_struct    *object,
    Volume           volume,
    Volume           label_volume,
    int              label,
    Real             max_distance );

public  void  scan_polygons_to_voxels(
    polygons_struct     *polygons,
    Volume              volume,
    Volume              label_volume,
    int                 label,
    Real                max_distance );

public  Volume  smooth_resample_volume(
    Volume              volume,
    int                 new_nx,
    int                 new_ny,
    int                 new_nz );

public  void  convert_voxel_to_talairach(
    Real   x_voxel,
    Real   y_voxel,
    Real   z_voxel,
    int    nx_voxels,
    int    ny_voxels,
    int    nz_voxels,
    Real   *x_tal,
    Real   *y_tal,
    Real   *z_tal );

public  void  convert_talairach_to_voxel(
    Real   x_tal,
    Real   y_tal,
    Real   z_tal,
    int    nx_voxels,
    int    ny_voxels,
    int    nz_voxels,
    Real   *x_voxel,
    Real   *y_voxel,
    Real   *z_voxel );

public  void  convert_talairach_to_mm(
    Real   x_tal,
    Real   y_tal,
    Real   z_tal,
    Real   *x_mm,
    Real   *y_mm,
    Real   *z_mm );

public  void  convert_mm_to_talairach(
    Real   x_mm,
    Real   y_mm,
    Real   z_mm,
    Real   *x_tal,
    Real   *y_tal,
    Real   *z_tal );
#endif
