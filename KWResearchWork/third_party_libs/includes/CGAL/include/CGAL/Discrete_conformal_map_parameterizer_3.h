// Copyright (c) 2005  INRIA (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Surface_mesh_parameterization/include/CGAL/Discrete_conformal_map_parameterizer_3.h $
// $Id: Discrete_conformal_map_parameterizer_3.h 56667 2010-06-09 07:37:13Z sloriot $
//
//
// Author(s)     : Laurent Saboret, Pierre Alliez, Bruno Levy


#ifndef CGAL_DISCRETE_CONFORMAL_MAP_PARAMETERIZER_3_H
#define CGAL_DISCRETE_CONFORMAL_MAP_PARAMETERIZER_3_H

#include <CGAL/Fixed_border_parameterizer_3.h>
#include <CGAL/surface_mesh_parameterization_assertions.h>

namespace CGAL {


/// The class Discrete_conformal_map_parameterizer_3
/// implements the Discrete Conformal Map (DCM) parameterization [EDD+95].
/// This algorithm is also called "Discrete Conformal Parameterization (DCP)",
/// "Discrete Harmonic Map" or "Fixed Conformal Parameterization" by other authors.
///
/// This is a conformal parameterization, i.e. it attempts to preserve angles.
///
/// One-to-one mapping is guaranteed if surface's border is mapped onto a convex polygon.
///
/// This class is a Strategy [GHJV95] called by the main
/// parameterization algorithm Fixed_border_parameterizer_3::parameterize().
/// - It provides default BorderParameterizer_3 and SparseLinearAlgebraTraits_d template
///   parameters that make sense.
/// - It implements compute_w_ij() to compute w_ij = (i, j) coefficient of matrix A
///   for j neighbor vertex of i based on Discrete Conformal Map method.
///
/// @heading Is Model for the Concepts: Model of the ParameterizerTraits_3 concept.
///
/// @heading Design Pattern:
/// Discrete_conformal_map_parameterizer_3 class is a
/// Strategy [GHJV95]: it implements a strategy of surface parameterization
/// for models of ParameterizationMesh_3.
///
/// @heading Parameters:
/// @param ParameterizationMesh_3       3D surface mesh.
/// @param BorderParameterizer_3        Strategy to parameterize the surface border.
/// @param SparseLinearAlgebraTraits_d  Traits class to solve a sparse linear system.
///        Note: the system is *not* symmetric because Fixed_border_parameterizer_3
///        does not remove (yet) border vertices from the system.

template
<
    class ParameterizationMesh_3,
    class BorderParameterizer_3
                = Circular_border_arc_length_parameterizer_3<ParameterizationMesh_3>,
    class SparseLinearAlgebraTraits_d
                = OpenNL::DefaultLinearSolverTraits<typename ParameterizationMesh_3::NT>
>
class Discrete_conformal_map_parameterizer_3
    : public Fixed_border_parameterizer_3<ParameterizationMesh_3,
                                        BorderParameterizer_3,
                                        SparseLinearAlgebraTraits_d>
{
// Private types
private:
    // Superclass
    typedef Fixed_border_parameterizer_3<ParameterizationMesh_3,
                                        BorderParameterizer_3,
                                        SparseLinearAlgebraTraits_d>
                                            Base;

// Public types
public:
    // We have to repeat the types exported by superclass
    /// @cond SKIP_IN_MANUAL
    typedef typename Base::Error_code       Error_code;
    typedef ParameterizationMesh_3          Adaptor;
    typedef BorderParameterizer_3           Border_param;
    typedef SparseLinearAlgebraTraits_d     Sparse_LA;
    /// @endcond

// Private types
private:
    // Mesh_Adaptor_3 subtypes:
    typedef typename Adaptor::NT            NT;
    typedef typename Adaptor::Point_2       Point_2;
    typedef typename Adaptor::Point_3       Point_3;
    typedef typename Adaptor::Vector_2      Vector_2;
    typedef typename Adaptor::Vector_3      Vector_3;
    typedef typename Adaptor::Facet         Facet;
    typedef typename Adaptor::Facet_handle  Facet_handle;
    typedef typename Adaptor::Facet_const_handle
                                            Facet_const_handle;
    typedef typename Adaptor::Facet_iterator Facet_iterator;
    typedef typename Adaptor::Facet_const_iterator
                                            Facet_const_iterator;
    typedef typename Adaptor::Vertex        Vertex;
    typedef typename Adaptor::Vertex_handle Vertex_handle;
    typedef typename Adaptor::Vertex_const_handle
                                            Vertex_const_handle;
    typedef typename Adaptor::Vertex_iterator Vertex_iterator;
    typedef typename Adaptor::Vertex_const_iterator
                                            Vertex_const_iterator;
    typedef typename Adaptor::Border_vertex_iterator
                                            Border_vertex_iterator;
    typedef typename Adaptor::Border_vertex_const_iterator
                                            Border_vertex_const_iterator;
    typedef typename Adaptor::Vertex_around_facet_circulator
                                            Vertex_around_facet_circulator;
    typedef typename Adaptor::Vertex_around_facet_const_circulator
                                            Vertex_around_facet_const_circulator;
    typedef typename Adaptor::Vertex_around_vertex_circulator
                                            Vertex_around_vertex_circulator;
    typedef typename Adaptor::Vertex_around_vertex_const_circulator
                                            Vertex_around_vertex_const_circulator;

    // SparseLinearAlgebraTraits_d subtypes:
    typedef typename Sparse_LA::Vector      Vector;
    typedef typename Sparse_LA::Matrix      Matrix;

    using Base::cotangent;

// Public operations
public:
    /// Constructor
    Discrete_conformal_map_parameterizer_3(Border_param border_param = Border_param(),
                                            ///< Object that maps the surface's border to 2D space.
                                           Sparse_LA sparse_la = Sparse_LA())
                                            ///< Traits object to access a sparse linear system.
    :   Fixed_border_parameterizer_3<Adaptor,
                                   Border_param,
                                   Sparse_LA>(border_param, sparse_la)
    {}

    // Default copy constructor and operator =() are fine

// Protected operations
protected:
    /// Compute w_ij = (i,j) coefficient of matrix A for j neighbor vertex of i.
    virtual NT compute_w_ij(const Adaptor& mesh,
                            Vertex_const_handle main_vertex_v_i,
                            Vertex_around_vertex_const_circulator neighbor_vertex_v_j)
    {
        Point_3 position_v_i = mesh.get_vertex_position(main_vertex_v_i);
        Point_3 position_v_j = mesh.get_vertex_position(neighbor_vertex_v_j);

        // Compute cotangent of (v_i,v_k,v_j) corner (i.e. cotan of v_k corner)
        // if v_k is the vertex before v_j when circulating around v_i
        Vertex_around_vertex_const_circulator previous_vertex_v_k = neighbor_vertex_v_j;
        previous_vertex_v_k --;
        Point_3 position_v_k = mesh.get_vertex_position(previous_vertex_v_k);
        double cotg_beta_ij  = cotangent(position_v_i, position_v_k, position_v_j);

        // Compute cotangent of (v_j,v_l,v_i) corner (i.e. cotan of v_l corner)
        // if v_l is the vertex after v_j when circulating around v_i
        Vertex_around_vertex_const_circulator next_vertex_v_l = neighbor_vertex_v_j;
        next_vertex_v_l ++;
        Point_3 position_v_l = mesh.get_vertex_position(next_vertex_v_l);
        double cotg_alpha_ij = cotangent(position_v_j, position_v_l, position_v_i);

        double weight = cotg_beta_ij+cotg_alpha_ij;
        return weight;
    }
};


} //namespace CGAL

#endif //CGAL_DISCRETE_CONFORMAL_MAP_PARAMETERIZER_3_H
