// Copyright (c) 2005  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Stream_lines_2/include/CGAL/streamlines_assertions.h $
// $Id: streamlines_assertions.h 53957 2010-02-01 12:55:28Z spion $
// 
//
// Author(s)     : Geert-Jan Giezeman, Sven Schoenherr, Abdelkrim Mebarki
//
// Generated from script create_assertions.sh


// Note that this header file is intentionnaly not protected with a
// macro (as <cassert>). Calling it a second time with another value
// for NDEBUG for example must make a difference.

#include <CGAL/assertions.h>

// macro definitions
// =================
// assertions
// ----------

#undef CGAL_streamlines_assertion
#undef CGAL_streamlines_assertion_msg
#undef CGAL_streamlines_assertion_code

#if defined(CGAL_STREAMLINES_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || defined(NDEBUG)
#  define CGAL_streamlines_assertion(EX) (static_cast<void>(0))
#  define CGAL_streamlines_assertion_msg(EX,MSG) (static_cast<void>(0))
#  define CGAL_streamlines_assertion_code(CODE)
#else
#  define CGAL_streamlines_assertion(EX) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__))
#  define CGAL_streamlines_assertion_msg(EX,MSG) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_streamlines_assertion_code(CODE) CODE
#  define CGAL_streamlines_assertions 1
#endif // CGAL_STREAMLINES_NO_ASSERTIONS


#undef CGAL_streamlines_exactness_assertion
#undef CGAL_streamlines_exactness_assertion_msg
#undef CGAL_streamlines_exactness_assertion_code

#if defined(CGAL_STREAMLINES_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_STREAMLINES_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_streamlines_exactness_assertion(EX) (static_cast<void>(0))
#  define CGAL_streamlines_exactness_assertion_msg(EX,MSG) (static_cast<void>(0))
#  define CGAL_streamlines_exactness_assertion_code(CODE)
#else
#  define CGAL_streamlines_exactness_assertion(EX) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__))
#  define CGAL_streamlines_exactness_assertion_msg(EX,MSG) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_streamlines_exactness_assertion_code(CODE) CODE
#  define CGAL_streamlines_exactness_assertions 1
#endif // CGAL_STREAMLINES_NO_ASSERTIONS


#undef CGAL_streamlines_expensive_assertion
#undef CGAL_streamlines_expensive_assertion_msg
#undef CGAL_streamlines_expensive_assertion_code

#if defined(CGAL_STREAMLINES_NO_ASSERTIONS) \
  || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_STREAMLINES_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_streamlines_expensive_assertion(EX) (static_cast<void>(0))
#  define CGAL_streamlines_expensive_assertion_msg(EX,MSG) (static_cast<void>(0))
#  define CGAL_streamlines_expensive_assertion_code(CODE)
#else
#  define CGAL_streamlines_expensive_assertion(EX) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__))
#  define CGAL_streamlines_expensive_assertion_msg(EX,MSG) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_streamlines_expensive_assertion_code(CODE) CODE
#  define CGAL_streamlines_expensive_assertions 1
#endif // CGAL_STREAMLINES_NO_ASSERTIONS


#undef CGAL_streamlines_expensive_exactness_assertion
#undef CGAL_streamlines_expensive_exactness_assertion_msg
#undef CGAL_streamlines_expensive_exactness_assertion_code

#if defined(CGAL_STREAMLINES_NO_ASSERTIONS) || defined(CGAL_NO_ASSERTIONS) \
  || (!defined(CGAL_STREAMLINES_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_STREAMLINES_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_streamlines_expensive_exactness_assertion(EX) (static_cast<void>(0))
#  define CGAL_streamlines_expensive_exactness_assertion_msg(EX,MSG) (static_cast<void>(0))
#  define CGAL_streamlines_expensive_exactness_assertion_code(CODE)
#else
#  define CGAL_streamlines_expensive_exactness_assertion(EX) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__))
#  define CGAL_streamlines_expensive_exactness_assertion_msg(EX,MSG) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::assertion_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_streamlines_expensive_exactness_assertion_code(CODE) CODE
#  define CGAL_streamlines_expensive_exactness_assertions 1
#endif // CGAL_STREAMLINES_NO_ASSERTIONS


// preconditions
// -------------

#undef CGAL_streamlines_precondition
#undef CGAL_streamlines_precondition_msg
#undef CGAL_streamlines_precondition_code

#if defined(CGAL_STREAMLINES_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || defined(NDEBUG)
#  define CGAL_streamlines_precondition(EX) (static_cast<void>(0))
#  define CGAL_streamlines_precondition_msg(EX,MSG) (static_cast<void>(0))
#  define CGAL_streamlines_precondition_code(CODE)
#else
#  define CGAL_streamlines_precondition(EX) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__))
#  define CGAL_streamlines_precondition_msg(EX,MSG) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_streamlines_precondition_code(CODE) CODE
#  define CGAL_streamlines_preconditions 1
#endif // CGAL_STREAMLINES_NO_PRECONDITIONS


#undef CGAL_streamlines_exactness_precondition
#undef CGAL_streamlines_exactness_precondition_msg
#undef CGAL_streamlines_exactness_precondition_code

#if defined(CGAL_STREAMLINES_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_STREAMLINES_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_streamlines_exactness_precondition(EX) (static_cast<void>(0))
#  define CGAL_streamlines_exactness_precondition_msg(EX,MSG) (static_cast<void>(0))
#  define CGAL_streamlines_exactness_precondition_code(CODE)
#else
#  define CGAL_streamlines_exactness_precondition(EX) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__))
#  define CGAL_streamlines_exactness_precondition_msg(EX,MSG) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_streamlines_exactness_precondition_code(CODE) CODE
#  define CGAL_streamlines_exactness_preconditions 1
#endif // CGAL_STREAMLINES_NO_PRECONDITIONS


#undef CGAL_streamlines_expensive_precondition
#undef CGAL_streamlines_expensive_precondition_msg
#undef CGAL_streamlines_expensive_precondition_code

#if defined(CGAL_STREAMLINES_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_STREAMLINES_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_streamlines_expensive_precondition(EX) (static_cast<void>(0))
#  define CGAL_streamlines_expensive_precondition_msg(EX,MSG) (static_cast<void>(0))
#  define CGAL_streamlines_expensive_precondition_code(CODE)
#else
#  define CGAL_streamlines_expensive_precondition(EX) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__))
#  define CGAL_streamlines_expensive_precondition_msg(EX,MSG) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_streamlines_expensive_precondition_code(CODE) CODE
#  define CGAL_streamlines_expensive_preconditions 1
#endif // CGAL_STREAMLINES_NO_PRECONDITIONS


#undef CGAL_streamlines_expensive_exactness_precondition
#undef CGAL_streamlines_expensive_exactness_precondition_msg
#undef CGAL_streamlines_expensive_exactness_precondition_code

#if defined(CGAL_STREAMLINES_NO_PRECONDITIONS) || defined(CGAL_NO_PRECONDITIONS) \
  || (!defined(CGAL_STREAMLINES_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_STREAMLINES_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_streamlines_expensive_exactness_precondition(EX) (static_cast<void>(0))
#  define CGAL_streamlines_expensive_exactness_precondition_msg(EX,MSG) (static_cast<void>(0))
#  define CGAL_streamlines_expensive_exactness_precondition_code(CODE)
#else
#  define CGAL_streamlines_expensive_exactness_precondition(EX) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__))
#  define CGAL_streamlines_expensive_exactness_precondition_msg(EX,MSG) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::precondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_streamlines_expensive_exactness_precondition_code(CODE) CODE
#  define CGAL_streamlines_expensive_exactness_preconditions 1
#endif // CGAL_STREAMLINES_NO_PRECONDITIONS


// postconditions
// --------------

#undef CGAL_streamlines_postcondition
#undef CGAL_streamlines_postcondition_msg
#undef CGAL_streamlines_postcondition_code

#if defined(CGAL_STREAMLINES_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || defined(NDEBUG)
#  define CGAL_streamlines_postcondition(EX) (static_cast<void>(0))
#  define CGAL_streamlines_postcondition_msg(EX,MSG) (static_cast<void>(0))
#  define CGAL_streamlines_postcondition_code(CODE)
#else
#  define CGAL_streamlines_postcondition(EX) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__))
#  define CGAL_streamlines_postcondition_msg(EX,MSG) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_streamlines_postcondition_code(CODE) CODE
#  define CGAL_streamlines_postconditions 1
#endif // CGAL_STREAMLINES_NO_POSTCONDITIONS


#undef CGAL_streamlines_exactness_postcondition
#undef CGAL_streamlines_exactness_postcondition_msg
#undef CGAL_streamlines_exactness_postcondition_code

#if defined(CGAL_STREAMLINES_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_STREAMLINES_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_streamlines_exactness_postcondition(EX) (static_cast<void>(0))
#  define CGAL_streamlines_exactness_postcondition_msg(EX,MSG) (static_cast<void>(0))
#  define CGAL_streamlines_exactness_postcondition_code(CODE)
#else
#  define CGAL_streamlines_exactness_postcondition(EX) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__))
#  define CGAL_streamlines_exactness_postcondition_msg(EX,MSG) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_streamlines_exactness_postcondition_code(CODE) CODE
#  define CGAL_streamlines_exactness_postconditions 1
#endif // CGAL_STREAMLINES_NO_POSTCONDITIONS


#undef CGAL_streamlines_expensive_postcondition
#undef CGAL_streamlines_expensive_postcondition_msg
#undef CGAL_streamlines_expensive_postcondition_code

#if defined(CGAL_STREAMLINES_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_STREAMLINES_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_streamlines_expensive_postcondition(EX) (static_cast<void>(0))
#  define CGAL_streamlines_expensive_postcondition_msg(EX,MSG) (static_cast<void>(0))
#  define CGAL_streamlines_expensive_postcondition_code(CODE)
#else
#  define CGAL_streamlines_expensive_postcondition(EX) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__))
#  define CGAL_streamlines_expensive_postcondition_msg(EX,MSG) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_streamlines_expensive_postcondition_code(CODE) CODE
#  define CGAL_streamlines_expensive_postconditions 1
#endif // CGAL_STREAMLINES_NO_POSTCONDITIONS


#undef CGAL_streamlines_expensive_exactness_postcondition
#undef CGAL_streamlines_expensive_exactness_postcondition_msg
#undef CGAL_streamlines_expensive_exactness_postcondition_code

#if defined(CGAL_STREAMLINES_NO_POSTCONDITIONS) || defined(CGAL_NO_POSTCONDITIONS) \
  || (!defined(CGAL_STREAMLINES_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_STREAMLINES_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_streamlines_expensive_exactness_postcondition(EX) (static_cast<void>(0))
#  define CGAL_streamlines_expensive_exactness_postcondition_msg(EX,MSG) (static_cast<void>(0))
#  define CGAL_streamlines_expensive_exactness_postcondition_code(CODE)
#else
#  define CGAL_streamlines_expensive_exactness_postcondition(EX) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__))
#  define CGAL_streamlines_expensive_exactness_postcondition_msg(EX,MSG) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::postcondition_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_streamlines_expensive_exactness_postcondition_code(CODE) CODE
#  define CGAL_streamlines_expensive_exactness_postconditions 1
#endif // CGAL_STREAMLINES_NO_POSTCONDITIONS


// warnings
// --------

#undef CGAL_streamlines_warning
#undef CGAL_streamlines_warning_msg
#undef CGAL_streamlines_warning_code

#if defined(CGAL_STREAMLINES_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || defined(NDEBUG)
#  define CGAL_streamlines_warning(EX) (static_cast<void>(0))
#  define CGAL_streamlines_warning_msg(EX,MSG) (static_cast<void>(0))
#  define CGAL_streamlines_warning_code(CODE)
#else
#  define CGAL_streamlines_warning(EX) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::warning_fail( # EX , __FILE__, __LINE__))
#  define CGAL_streamlines_warning_msg(EX,MSG) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_streamlines_warning_code(CODE) CODE
#  define CGAL_streamlines_warnings 1
#endif // CGAL_STREAMLINES_NO_WARNINGS


#undef CGAL_streamlines_exactness_warning
#undef CGAL_streamlines_exactness_warning_msg
#undef CGAL_streamlines_exactness_warning_code

#if defined(CGAL_STREAMLINES_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_STREAMLINES_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || defined(NDEBUG)
#  define CGAL_streamlines_exactness_warning(EX) (static_cast<void>(0))
#  define CGAL_streamlines_exactness_warning_msg(EX,MSG) (static_cast<void>(0))
#  define CGAL_streamlines_exactness_warning_code(CODE)
#else
#  define CGAL_streamlines_exactness_warning(EX) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::warning_fail( # EX , __FILE__, __LINE__))
#  define CGAL_streamlines_exactness_warning_msg(EX,MSG) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_streamlines_exactness_warning_code(CODE) CODE
#  define CGAL_streamlines_exactness_warnings 1
#endif // CGAL_STREAMLINES_NO_WARNINGS


#undef CGAL_streamlines_expensive_warning
#undef CGAL_streamlines_expensive_warning_msg
#undef CGAL_streamlines_expensive_warning_code

#if defined(CGAL_STREAMLINES_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_STREAMLINES_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_streamlines_expensive_warning(EX) (static_cast<void>(0))
#  define CGAL_streamlines_expensive_warning_msg(EX,MSG) (static_cast<void>(0))
#  define CGAL_streamlines_expensive_warning_code(CODE)
#else
#  define CGAL_streamlines_expensive_warning(EX) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::warning_fail( # EX , __FILE__, __LINE__))
#  define CGAL_streamlines_expensive_warning_msg(EX,MSG) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_streamlines_expensive_warning_code(CODE) CODE
#  define CGAL_streamlines_expensive_warnings 1
#endif // CGAL_STREAMLINES_NO_WARNINGS


#undef CGAL_streamlines_expensive_exactness_warning
#undef CGAL_streamlines_expensive_exactness_warning_msg
#undef CGAL_streamlines_expensive_exactness_warning_code

#if defined(CGAL_STREAMLINES_NO_WARNINGS) || defined(CGAL_NO_WARNINGS) \
  || (!defined(CGAL_STREAMLINES_CHECK_EXACTNESS) && !defined(CGAL_CHECK_EXACTNESS))\
  || (!defined(CGAL_STREAMLINES_CHECK_EXPENSIVE) && !defined(CGAL_CHECK_EXPENSIVE)) \
  || defined(NDEBUG)
#  define CGAL_streamlines_expensive_exactness_warning(EX) (static_cast<void>(0))
#  define CGAL_streamlines_expensive_exactness_warning_msg(EX,MSG) (static_cast<void>(0))
#  define CGAL_streamlines_expensive_exactness_warning_code(CODE)
#else
#  define CGAL_streamlines_expensive_exactness_warning(EX) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::warning_fail( # EX , __FILE__, __LINE__))
#  define CGAL_streamlines_expensive_exactness_warning_msg(EX,MSG) \
   (CGAL::possibly(EX)?(static_cast<void>(0)): ::CGAL::warning_fail( # EX , __FILE__, __LINE__, MSG))
#  define CGAL_streamlines_expensive_exactness_warning_code(CODE) CODE
#  define CGAL_streamlines_expensive_exactness_warnings 1
#endif // CGAL_STREAMLINES_NO_WARNINGS
