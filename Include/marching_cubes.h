#ifndef  DEF_MARCHING_CUBES
#define  DEF_MARCHING_CUBES

#include  <def_geometry.h>

typedef  enum  { ON_FIRST_CORNER, ON_EDGE, ON_SECOND_CORNER } Point_classes;

typedef  enum  { MARCHING_CUBES, MARCHING_NO_HOLES } Marching_cubes_methods;

#define  MAX_TRIANGLES_PER_VOXEL        4
#define  MAX_POINTS_PER_VOXEL           3 * MAX_TRIANGLES_PER_VOXEL

#define  MAX_POINTS_PER_VOXEL_POLYGON  12

typedef  enum  {
                 USE_VOXEL_VALUES,
                 TRILINEAR_INTERPOLATION,
                 TRICUBIC_INTERPOLATION
               } evaluation_methods;

typedef struct
{
    int   coord[3];
    int   edge_intersected;

}  voxel_point_type;

typedef  struct
{
    Boolean  surface_point_exists;
    int      point_index;

} axis_struct;

typedef  struct
{
    Real          value;
    Vector        gradient;
    axis_struct   edge_info[N_DIMENSIONS];

} voxel_struct;

#endif