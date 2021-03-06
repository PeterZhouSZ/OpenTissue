#ifndef OPENTISSUE_COLLISION_GJK_GJK_REDUCE_TRIANGLE_H
#define OPENTISSUE_COLLISION_GJK_GJK_REDUCE_TRIANGLE_H
//
// OpenTissue Template Library
// - A generic toolbox for physics-based modeling and simulation.
// Copyright (C) 2008 Department of Computer Science, University of Copenhagen.
//
// OTTL is licensed under zlib: http://opensource.org/licenses/zlib-license.php
//
#include <OpenTissue/configuration.h>

#include <OpenTissue/core/geometry/geometry_barycentric.h>

#include <OpenTissue/collision/gjk/gjk_simplex.h>
#include <OpenTissue/collision/gjk/gjk_outside_vertex_edge_voronoi_plane.h>
#include <OpenTissue/collision/gjk/gjk_outside_edge_face_voronoi_plane.h>

namespace OpenTissue
{
  namespace gjk
  {

    namespace detail
    {
      /**
      * Reduce Triangle.
      * This function implements the case where a simplex
      * is a triangle. The function will compute the closest
      * point to p on the simplex and try to reduce the simplex
      * to the lowest dimensional face on the boundary of the
      * simplex containing the closest point.
      *
      * @param p   The test point.
      * @param S   Initially this argument holds the triangle simplex. Upon
      *            return the argument holds the reduced simplex.
      */
      template< typename V >
      inline void reduce_triangle( V const & p, Simplex<V> & S)
      {
        typedef typename V::value_type    T;
        typedef typename V::value_traits  value_traits;

        int bit_A = 0;
        int bit_B = 0;
        int bit_C = 0;
        size_t idx_A = 0;
        size_t idx_B = 0;
        size_t idx_C = 0;
        
        get_used_indices( S.m_bitmask, idx_A, bit_A, idx_B, bit_B, idx_C, bit_C );

        V const & A = S.m_v[idx_A];
        V const & B = S.m_v[idx_B];
        V const & C = S.m_v[idx_C];
        
        bool const outside_AB  = outside_vertex_edge_voronoi_plane(p, A, B);
        bool const outside_AC  = outside_vertex_edge_voronoi_plane(p, A, C);
        bool const outside_BC  = outside_vertex_edge_voronoi_plane(p, B, C);
        bool const outside_BA  = outside_vertex_edge_voronoi_plane(p, B, A);
        bool const outside_CA  = outside_vertex_edge_voronoi_plane(p, C, A);
        bool const outside_CB  = outside_vertex_edge_voronoi_plane(p, C, B);
        bool const outside_ABC = outside_edge_face_voronoi_plane( p, A, B, C);
        bool const outside_BCA = outside_edge_face_voronoi_plane( p, B, C, A);
        bool const outside_CAB = outside_edge_face_voronoi_plane( p, C, A, B);
        
        // Test if we are in a vertex voronoi region
        if( outside_AB && outside_AC )
        {
          S.m_bitmask = bit_A;
          S.m_v[idx_B].clear();
          S.m_v[idx_C].clear();
          S.m_a[idx_B].clear();
          S.m_a[idx_C].clear();
          S.m_b[idx_B].clear();
          S.m_b[idx_C].clear();
          S.m_w[idx_A] = value_traits::one();
          S.m_w[idx_B] = value_traits::zero();
          S.m_w[idx_C] = value_traits::zero();
          return;
        }
        if( outside_BA && outside_BC )
        {
          S.m_bitmask = bit_B;
          S.m_v[idx_A].clear();
          S.m_v[idx_C].clear();
          S.m_a[idx_A].clear();
          S.m_a[idx_C].clear();
          S.m_b[idx_A].clear();
          S.m_b[idx_C].clear();
          S.m_w[idx_A] = value_traits::zero();
          S.m_w[idx_B] = value_traits::one();
          S.m_w[idx_C] = value_traits::zero();
          return;
        }
        if( outside_CA && outside_CB )
        {
          S.m_bitmask = bit_C;
          S.m_v[idx_A].clear();
          S.m_v[idx_B].clear();
          S.m_a[idx_A].clear();
          S.m_a[idx_B].clear();
          S.m_b[idx_A].clear();
          S.m_b[idx_B].clear();
          S.m_w[idx_A] = value_traits::zero();
          S.m_w[idx_B] = value_traits::zero();
          S.m_w[idx_C] = value_traits::one();
          return;
        }        
        // Test voronoi regions of edges
        if( outside_ABC && !outside_AB && !outside_BA )
        {
          S.m_bitmask = bit_A | bit_B;
          S.m_v[idx_C].clear();
          S.m_a[idx_C].clear();
          S.m_b[idx_C].clear();
          S.m_w[idx_C] = value_traits::zero();          
          OpenTissue::geometry::barycentric_geometric(A,B,p,S.m_w[idx_A],S.m_w[idx_B]);
          return;
        }
        if( outside_BCA && !outside_BC && !outside_CB )
        {
          S.m_bitmask = bit_B | bit_C;
          S.m_v[idx_A].clear();
          S.m_a[idx_A].clear();
          S.m_b[idx_A].clear();
          S.m_w[idx_A] = value_traits::zero();
          OpenTissue::geometry::barycentric_geometric(B,C,p,S.m_w[idx_B],S.m_w[idx_C]);
          return;
        }
        if( outside_CAB && !outside_AC && !outside_CA )
        {
          S.m_bitmask = bit_A | bit_C;
          S.m_v[idx_B].clear();
          S.m_a[idx_B].clear();
          S.m_b[idx_B].clear();
          S.m_w[idx_B] = value_traits::zero();
          OpenTissue::geometry::barycentric_geometric(A,C,p,S.m_w[idx_A],S.m_w[idx_C]);
          return;
        }       
        // Test if we are inside internal face voronnoi region
        if(!outside_ABC && !outside_BCA && !outside_CAB)
        {
          OpenTissue::geometry::barycentric_geometric( A, B, C, p, S.m_w[idx_A], S.m_w[idx_B], S.m_w[idx_C]);
          return;
        }
      }


    } // namespace detail
  } // namespace gjk
} // namespace OpenTissue

// OPENTISSUE_COLLISION_GJK_GJK_REDUCE_TRIANGLE_H
#endif
