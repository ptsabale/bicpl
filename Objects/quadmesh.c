/* ----------------------------------------------------------------------------
@COPYRIGHT  :
              Copyright 1993,1994,1995 David MacDonald,
              McConnell Brain Imaging Centre,
              Montreal Neurological Institute, McGill University.
              Permission to use, copy, modify, and distribute this
              software and its documentation for any purpose and without
              fee is hereby granted, provided that the above copyright
              notice appear in all copies.  The author and McGill University
              make no representations about the suitability of this
              software for any purpose.  It is provided "as is" without
              express or implied warranty.
---------------------------------------------------------------------------- */

#include  <volume_io/internal_volume_io.h>
#include  <objects.h>
#include  <geom.h>

#ifndef lint
static char rcsid[] = "$Header: /private-cvsroot/libraries/bicpl/Objects/quadmesh.c,v 1.15 2000-02-05 21:27:10 stever Exp $";
#endif

/* ----------------------------- MNI Header -----------------------------------
@NAME       : initialize_quadmesh
@INPUT      : col
              spr
              m
              n
@OUTPUT     : quadmesh
@RETURNS    : 
@DESCRIPTION: Initializes a quadmesh to the given size.
@METHOD     : 
@GLOBALS    : 
@CALLS      : 
@CREATED    :         1993    David MacDonald
@MODIFIED   : 
---------------------------------------------------------------------------- */

public  void  initialize_quadmesh(
    quadmesh_struct   *quadmesh,
    Colour            col,
    Surfprop          *spr,
    int               m,
    int               n )
{
    ALLOC( quadmesh->colours, 1 );

    quadmesh->colour_flag = ONE_COLOUR;

    quadmesh->colours[0] = col;

    if( spr != (Surfprop *) 0 )
        quadmesh->surfprop = *spr;
    else
        get_default_surfprop( &quadmesh->surfprop );

    quadmesh->m = m;
    quadmesh->n = n;
    quadmesh->m_closed = FALSE;
    quadmesh->n_closed = FALSE;
    if( quadmesh->m > 0 && quadmesh->n > 0 )
    {
        ALLOC( quadmesh->points, m * n );
        ALLOC( quadmesh->normals, m * n );
    }

    quadmesh->bintree = (bintree_struct_ptr) NULL;
}

/* ----------------------------- MNI Header -----------------------------------
@NAME       : delete_quadmesh
@INPUT      : quadmesh
@OUTPUT     : 
@RETURNS    : 
@DESCRIPTION: Deletes a quadmesh structure.
@METHOD     : 
@GLOBALS    : 
@CALLS      : 
@CREATED    :         1993    David MacDonald
@MODIFIED   : 
---------------------------------------------------------------------------- */

public  void  delete_quadmesh(
    quadmesh_struct *quadmesh )
{
    free_colours( quadmesh->colour_flag, quadmesh->colours,
                  quadmesh->m * quadmesh->n,
                  (quadmesh->m-1) * (quadmesh->n-1) );

    if( quadmesh->m > 0 && quadmesh->n > 0 )
    {
        FREE( quadmesh->points );

        if( quadmesh->normals != (Vector *) NULL )
            FREE( quadmesh->normals );
    }

    delete_bintree_if_any( &quadmesh->bintree );   
}

/* ----------------------------- MNI Header -----------------------------------
@NAME       : set_quadmesh_point
@INPUT      : quadmesh
              i
              j
              point
              normal
@OUTPUT     : 
@RETURNS    : 
@DESCRIPTION: Sets the point and normal of the quadmesh.
@METHOD     : 
@GLOBALS    : 
@CALLS      : 
@CREATED    :         1993    David MacDonald
@MODIFIED   : 
---------------------------------------------------------------------------- */

public  void  set_quadmesh_point(
    quadmesh_struct  *quadmesh,
    int              i,
    int              j,
    Point            *point,
    Vector           *normal )
{
    int  ind;

    ind = IJ( i, j, quadmesh->n );

    quadmesh->points[ind] = *point;
    if( normal != NULL && quadmesh->normals != NULL )
        quadmesh->normals[ind] = *normal;
}

/* ----------------------------- MNI Header -----------------------------------
@NAME       : get_quadmesh_point
@INPUT      : quadmesh
              i
              j
@OUTPUT     : point
@RETURNS    : TRUE if i,j is valid
@DESCRIPTION: Passes back the specified point of the quadmesh.
@METHOD     : 
@GLOBALS    : 
@CALLS      : 
@CREATED    :         1993    David MacDonald
@MODIFIED   : 
---------------------------------------------------------------------------- */

public  BOOLEAN  get_quadmesh_point(
    quadmesh_struct  *quadmesh,
    int              i,
    int              j,
    Point            *point )
{
    if( i < 0 || i >= quadmesh->m ||
        j < 0 || j >= quadmesh->n )
        return( FALSE );

    *point = quadmesh->points[IJ(i,j,quadmesh->n)];

    return( TRUE );
}
    
/* ----------------------------- MNI Header -----------------------------------
@NAME       : get_quadmesh_n_objects
@INPUT      : quadmesh
@OUTPUT     : m
              n
@RETURNS    : 
@DESCRIPTION: Passes back the number of patches in the quadmesh.
@METHOD     : 
@GLOBALS    : 
@CALLS      : 
@CREATED    :         1993    David MacDonald
@MODIFIED   : 
---------------------------------------------------------------------------- */

public  void  get_quadmesh_n_objects(
    quadmesh_struct  *quadmesh,
    int              *m,
    int              *n )
{
    if( quadmesh->m_closed )
        *m = quadmesh->m;
    else
        *m = quadmesh->m - 1;

    if( quadmesh->n_closed )
        *n = quadmesh->n;
    else
        *n = quadmesh->n - 1;
}

/* ----------------------------- MNI Header -----------------------------------
@NAME       : compute_quadmesh_normals
@INPUT      : quadmesh
@OUTPUT     : 
@RETURNS    : 
@DESCRIPTION: Computes the normals of a quadmesh.
@METHOD     : 
@GLOBALS    : 
@CALLS      : 
@CREATED    :         1993    David MacDonald
@MODIFIED   : 
---------------------------------------------------------------------------- */

public  void  compute_quadmesh_normals(
    quadmesh_struct  *quadmesh )
{
    int                i, j, m, n, n_neighs;
    Point              neighbours[4];
    progress_struct    progress;

    m = quadmesh->m;
    n = quadmesh->n;

    if( quadmesh->normals == (Vector *) NULL )
        ALLOC( quadmesh->normals, m * n );

    for_less( i, 0, m * n )
        fill_Vector( quadmesh->normals[i], 0.0, 0.0, 0.0 );

    initialize_progress_report( &progress, FALSE, m, "Computing Normals" );

    for_less( i, 0, m )
    {
        for_less( j, 0, n )
        {
            n_neighs = 0;
            if( get_quadmesh_point( quadmesh, i,   j-1, &neighbours[n_neighs]) )
                ++n_neighs;
            if( get_quadmesh_point( quadmesh, i+1, j  , &neighbours[n_neighs]) )
                ++n_neighs;
            if( get_quadmesh_point( quadmesh, i,   j+1, &neighbours[n_neighs]) )
                ++n_neighs;
            if( get_quadmesh_point( quadmesh, i-1, j  , &neighbours[n_neighs]) )
                ++n_neighs;

            if( n_neighs < 2 )
            {
                handle_internal_error( "compute_quadmesh_normals" );
            }
            else if( n_neighs == 2 )
            {
                neighbours[n_neighs] = quadmesh->points[IJ(i,j,n)];
                ++n_neighs;
            }

            find_polygon_normal( n_neighs, neighbours,
                                 &quadmesh->normals[IJ(i,j,n)] );
            NORMALIZE_VECTOR( quadmesh->normals[IJ(i,j,n)],
                              quadmesh->normals[IJ(i,j,n)] );
        }

        update_progress_report( &progress, i + 1 );
    }

    terminate_progress_report( &progress );
}

/* ----------------------------- MNI Header -----------------------------------
@NAME       : get_quadmesh_patch_indices
@INPUT      : quadmesh
              i
              j
@OUTPUT     : indices
@RETURNS    : 
@DESCRIPTION: Passes back the indices of the quadmesh points making up the
              i,j'th patch
@METHOD     : 
@GLOBALS    : 
@CALLS      : 
@CREATED    :         1993    David MacDonald
@MODIFIED   : 
---------------------------------------------------------------------------- */

public  void  get_quadmesh_patch_indices(
    quadmesh_struct  *quadmesh,
    int              i,
    int              j,
    int              indices[] )
{
    indices[0] = IJ(                   i,                   j, quadmesh->n );
    indices[1] = IJ( (i+1) % quadmesh->m,                   j, quadmesh->n );
    indices[2] = IJ( (i+1) % quadmesh->m, (j+1) % quadmesh->n, quadmesh->n );
    indices[3] = IJ(                   i, (j+1) % quadmesh->n, quadmesh->n );
}

/* ----------------------------- MNI Header -----------------------------------
@NAME       : get_quadmesh_patch
@INPUT      : quadmesh
              i
              j
@OUTPUT     : points
@RETURNS    : 
@DESCRIPTION: Passes back the 4 points defining the i,j'th patch.
@METHOD     : 
@GLOBALS    : 
@CALLS      : 
@CREATED    :         1993    David MacDonald
@MODIFIED   : 
---------------------------------------------------------------------------- */

public  void  get_quadmesh_patch(
    quadmesh_struct  *quadmesh,
    int              i,
    int              j,
    Point            points[] )
{
    int   p, indices[4];

    get_quadmesh_patch_indices( quadmesh, i, j, indices );

    for_less( p, 0, 4 )
        points[p] = quadmesh->points[indices[p]];
}

public  void  reverse_quadmesh_vertices(
    quadmesh_struct  *quadmesh )
{
    int     i, j, i1, i2;
    Point   tmp_point;
    Vector  tmp_normal;

    for_less( i, 0, quadmesh->m )
    {
        for_less( j, 0, quadmesh->n / 2 )
        {
            i1 = IJ( i, j, quadmesh->n );
            i2 = IJ( i, quadmesh->n - 1 - j, quadmesh->n );

            tmp_point = quadmesh->points[i1];
            quadmesh->points[i1] = quadmesh->points[i2];
            quadmesh->points[i2] = tmp_point;

            if( quadmesh->normals != NULL )
            {
                tmp_normal = quadmesh->normals[i1];
                quadmesh->normals[i1] = quadmesh->normals[i2];
                quadmesh->normals[i2] = tmp_normal;
            }
        }
    }
}
