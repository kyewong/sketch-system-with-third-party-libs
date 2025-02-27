// Copyright (c) 2006  GeometryFactory (France). All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Surface_mesh_simplification/include/CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Count_ratio_stop_predicate.h $
// $Id: Count_ratio_stop_predicate.h 56667 2010-06-09 07:37:13Z sloriot $
//
// Author(s)     : Fernando Cacciola <fernando.cacciola@geometryfactory.com>
//
#ifndef CGAL_SURFACE_MESH_SIMPLIFICATION_POLICIES_EDGE_COLLAPSE_COUNT_RATIO_STOP_PREDICATE_H
#define CGAL_SURFACE_MESH_SIMPLIFICATION_POLICIES_EDGE_COLLAPSE_COUNT_RATIO_STOP_PREDICATE_H 1

#include <CGAL/Surface_mesh_simplification/Detail/Common.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Edge_profile.h>

namespace CGAL {

namespace Surface_mesh_simplification 
{

//*******************************************************************************************************************
//                                -= stopping condition predicate =-
//
// Determines whether the simplification has finished.
// The arguments are (current_cost,vertex,vertex,is_edge,initial_pair_count,current_pair_count,surface) and the result is bool
//
//*******************************************************************************************************************

// 
// Stops when the ratio of initial to current vertex pairs is below some value.
//
template<class ECM_>    
class Count_ratio_stop_predicate
{
public:

  typedef ECM_ ECM ;
  
  typedef Edge_profile<ECM> Profile ;
  
  typedef typename boost::graph_traits<ECM>::edge_descriptor edge_descriptor ;
  typedef typename boost::graph_traits<ECM>::edges_size_type size_type ;
  
  typedef typename halfedge_graph_traits<ECM>::Point Point ;
  typedef typename Kernel_traits<Point>::Kernel      Kernel ;
  typedef typename Kernel::FT                        FT ;
  
public :
  
  Count_ratio_stop_predicate( double aRatio ) : mRatio(aRatio) {}
  
  bool operator()( FT const&      // aCurrentCost
                 , Profile const& //aEdgeProfile
                 , size_type      aInitialCount
                 , size_type      aCurrentCount
                 ) const 
  {
    return ( static_cast<double>(aCurrentCount) / static_cast<double>(aInitialCount) ) < mRatio ;
  }
  
private:
  
  double mRatio ;
};    

} // namespace Surface_mesh_simplification

} //namespace CGAL

#endif // CGAL_SURFACE_MESH_SIMPLIFICATION_POLICIES_EDGE_COLLAPSE_COUNT_RATIO_STOP_PREDICATE_H //
// EOF //
 
