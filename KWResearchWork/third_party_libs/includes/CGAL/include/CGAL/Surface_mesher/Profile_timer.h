// Copyright (c) 2008       GeometryFactory (France)
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Surface_mesher/include/CGAL/Surface_mesher/Profile_timer.h $
// $Id: Profile_timer.h 47789 2009-01-23 15:01:25Z lrineau $
//
//
// Author(s)     : Laurent Rineau

// This file is an adaptation of <CGAL/Profile_timer.h>, so that the
// macros are prefixed with CGAL_SURFACE_MESHER_ instead of CGAL_.

#ifndef CGAL_SURFACE_MESHER_PROFILE_TIMER_H
#define CGAL_SURFACE_MESHER_PROFILE_TIMER_H
#include <CGAL/Profile_timer.h>

#ifdef CGAL_SURFACE_MESHER_PROFILE
#  define CGAL_SURFACE_MESHER_TIME_PROFILER(NAME) \
          static CGAL::Profile_timer CGAL_profile_timer_tmp(NAME); \
          CGAL::Profile_timer::Local CGAL_local_profile_timer_tmp(&CGAL_profile_timer_tmp);
#else
#  define CGAL_SURFACE_MESHER_TIME_PROFILER(NAME)
#endif

#endif // CGAL_SURFACE_MESHER_TIME_PROFILER
