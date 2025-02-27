// Copyright (c) 2008  GeometryFactory Sarl (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/GraphicsView/include/CGAL/Qt/GraphicsViewPolylineInput.h $
// $Id: GraphicsViewPolylineInput.h 53096 2009-11-18 15:19:18Z lrineau $
// 
//
// Author(s)     : Andreas Fabri <Andreas.Fabri@geometryfactory.com>
//                 Laurent Rineau <Laurent.Rineau@geometryfactory.com>

#ifndef CGAL_QT_GRAPHICS_VIEW_POLYLINE_INPUT_H
#define CGAL_QT_GRAPHICS_VIEW_POLYLINE_INPUT_H

#include <CGAL/auto_link/Qt4.h>
#include <QPolygonF>
#include <QPointF>

#include <CGAL/Qt/GraphicsViewInput.h>
#include <CGAL/Qt/Converter.h>

class QGraphicsScene;
class QGraphicsSceneMouseEvent;
class QGraphicsItem;
class QGraphicsPathItem;
class QKeyEvent;
class QEvent;
class QObject;

namespace CGAL {
namespace Qt {

class GraphicsViewPolylineInput_non_templated_base : public GraphicsViewInput
{
public:
  void setNumberOfVertices(int n)
  {
    n_ = n;
  }
  
  bool eventFilter(QObject *obj, QEvent *event);
  
protected:
  // protected constructor
  GraphicsViewPolylineInput_non_templated_base(QObject* parent, 
                                     QGraphicsScene* s,
                                     int n = 0,
                                     bool closed = true);


  // mousePressEvent returns true iff the event is consummed
  bool mousePressEvent(QGraphicsSceneMouseEvent *event);

  void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

  // keyPressEvent returns true iff the event is consummed
  bool keyPressEvent(QKeyEvent *event);

  void rubberbands(const QPointF& p);

  virtual void generate_polygon() = 0;

protected:
  QPolygonF polygon;
  bool closed_;

private:
  QGraphicsPathItem *path_item;
  QGraphicsLineItem *b, *e;
  int n_;
  QPointF sp;
  QGraphicsScene *scene_;
}; // end class GraphicsViewPolylineInput_non_templated_base

template <typename K>
class GraphicsViewPolylineInput : public GraphicsViewPolylineInput_non_templated_base
{
public:
  GraphicsViewPolylineInput(QObject* parent, QGraphicsScene* s, int n = 0, bool closed = true)
    : GraphicsViewPolylineInput_non_templated_base(parent, s, n, closed)
  {
  }

protected:
  void generate_polygon() {
    std::list<typename K::Point_2> points;
    Converter<K> convert;
    convert(points, this->polygon); 
    if(closed_){
      points.push_back(points.front());
    }
    emit(generate(CGAL::make_object(points)));
  }
}; // end class GraphicsViewPolylineInput

} // namespace Qt
} // namespace CGAL

#endif // CGAL_QT_GRAPHICS_VIEW_POLYLINE_INPUT_H
