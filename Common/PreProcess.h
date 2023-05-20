#ifndef INC_PREPROCESS_H
#define INC_PREPROCESS_H

#include <cassert>

#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx> 

#include <Geom2d_Circle.hxx>
#include <Geom_BezierCurve.hxx>
#include <Geom_Plane.hxx>

#include <BRepLib.hxx>

#include <GCE2d_MakeLine.hxx>
#include <BRepFeat_MakePipe.hxx>

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>

#include <BRepFeat_MakePrism.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepFilletAPI_MakeFillet2d.hxx>
#include <BRepOffsetAPI_DraftAngle.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_MakeEvolved.hxx>

#include <BRepOffsetAPI_MakeThickSolid.hxx>
#include <BRepFeat_MakeDPrism.hxx>
#include <BRepFeat_MakeRevol.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepFeat_MakeLinearForm.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_Copy.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <GeomPlate_PointConstraint.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <BRepAdaptor_Curve.hxx>

#include <BRepPrimAPI_MakeBox.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <GeomPlate_BuildPlateSurface.hxx>

#include <TopExp_Explorer.hxx>

#endif //