#include "helper.h"
#include "PreProcess.h"

int main(int argc,char** argv)
{
    {
        TopoDS_Solid Box = BRepPrimAPI_MakeBox(1,1,1);
        write_step(Box,"box1.step");
    } 
    {
        gp_Pnt
            p1 {0,0,0},
            p2 {1,0,0},
            p3 {1,1,0},
            p4 {0,1,0},

            p5 {0,0,0},
            p6 {1,0,0},
            p7 {1,0,1},
            p8 {0,0,1};

        TopoDS_Wire wire = BRepBuilderAPI_MakePolygon(p1,p2,p3,p4,Standard_True),
                    wire1 = BRepBuilderAPI_MakePolygon(p5,p6,p7,p8,true);

        TopoDS_Face face1 = BRepBuilderAPI_MakeFace(wire),
                    face2 = BRepBuilderAPI_MakeFace(wire1);
        BRepBuilderAPI_Sewing sw{};
        sw.Add(wire);
        sw.Add(wire1);
        sw.Perform();
        write_step(sw.SewedShape(),"face1.step");                   
    }
    {
        gp_Pnt
            p1 {0,0,0},
            p2 {1,0,0},
            p3 {1,1,0},
            p4 {0,1,0},

            p5 {0,0,0},
            p6 {1,0,0},
            p7 {1,0,1},
            p8 {0,0,1};

        TopoDS_Wire wire = BRepBuilderAPI_MakePolygon(p1,p2,p3,p4,Standard_True),
                    wire1 = BRepBuilderAPI_MakePolygon(p5,p6,p7,p8,true);

        TopoDS_Face face1 = BRepBuilderAPI_MakeFace(wire),
                    face2 = BRepBuilderAPI_MakeFace(wire1);
        gp_Dir dir{0,0,1};
        BRepFeat_MakePrism prism{wire, wire1,TopoDS_Face(),dir,Standard_True,Standard_True};
        prism.Perform(1);
        TopoDS_Shape shape = prism;
        assert(prism.IsDone());
        write_step(shape,"face2.step");
    }

    {
        //圆角
        TopoDS_Solid Box = BRepPrimAPI_MakeBox(1,1,1);
        BRepFilletAPI_MakeFillet mf{Box};

        TopExp_Explorer exp{Box,TopAbs_EDGE};
        while (exp.More())
        {
            mf.Add(0.1,TopoDS::Edge(exp.Current()));
            exp.Next();
        }
        write_step(mf.Shape(),"box2.step");
    }
    {
        //倒角
        TopoDS_Solid Box = BRepPrimAPI_MakeBox(1,1,1);
        BRepFilletAPI_MakeChamfer mf{Box};

        TopExp_Explorer exp{Box,TopAbs_EDGE};
        while (exp.More())
        {
            mf.Add(0.1,TopoDS::Edge(exp.Current()));
            exp.Next();
        }
        write_step(mf.Shape(),"box3.step");
    }
    {
        //平面圆角
        TopoDS_Solid Box = BRepPrimAPI_MakeBox(1,1,1);
        TopExp_Explorer exp1{Box,TopAbs_FACE};
        TopoDS_Face face = TopoDS::Face(exp1.Current());
        BRepFilletAPI_MakeFillet2d mf{face};

        TopExp_Explorer exp{face,TopAbs_VERTEX};
        while (exp.More())
        {
            mf.AddFillet(TopoDS::Vertex(exp.Current()),0.05);
            if (mf.Status() != ChFi2d_IsDone)
            {
                auto status = mf.Status();
                //return -1;
            }
            exp.Next();
        }
        //write_step(mf.Shape(),"box4.step");
    }
    {
        gp_Pnt
            p1 {0,0,0},
            p2 {1,0,0},
            p3 {1,1,0},
            p4 {0,1,0},

            p5 {0,0,0},
            p6 {1,0,0},
            p7 {1,0,1},
            p8 {0,0,1};

        TopoDS_Wire wire = BRepBuilderAPI_MakePolygon(p1,p2,p3,p4,Standard_True),
                    wire1 = BRepBuilderAPI_MakePolygon(p5,p6,p7,p8,true);

        TopoDS_Face face1 = BRepBuilderAPI_MakeFace(wire),
                    face2 = BRepBuilderAPI_MakeFace(wire1);
        BRepBuilderAPI_Sewing sw{};
        sw.Add(wire);
        sw.Add(wire1);
        sw.Perform();
        BRepOffsetAPI_MakeThickSolid mts{};
        //mts.MakeThickSolidBySimple(sw.SewedShape(),0.9);
        
        //write_step(mts.Shape(),"box5.step");
    }
    {
        TopoDS_Shape shape = BRepPrimAPI_MakeBox(1,1,1);
        gp_Dir dir {0,0,1};
        Standard_Real angle { 5 * M_PI / 180};
        gp_Pln neutral { gp_Pnt{0,0,1},dir};

        BRepOffsetAPI_DraftAngle draft{shape};
        TopTools_ListIteratorOfListOfShape itl{};
        TopTools_ListOfShape lof;
        for(itl.Initialize(lof);itl.More();itl.Next())
        {
            draft.Add(TopoDS::Face(itl.Value()),dir,angle,neutral);
        }
        draft.AddDone();
        draft.Build();
        write_step(draft.Shape(),"box6.step");
    }
    {
        gp_Pnt 
            p11{0,0,0},
            p22{1,1,1},
            p33{2,1.5,1};
        TopoDS_Wire wire = BRepBuilderAPI_MakePolygon(p11,p22,p33);
        gp_Pnt
            p1 {0,0,0},
            p2 {1,0,0},
            p3 {1,1,0},
            p4 {0,1,0},

            p5 {0,0,0},
            p6 {1,0,0},
            p7 {1,0,1},
            p8 {0,0,1};

        TopoDS_Wire wire2 = BRepBuilderAPI_MakePolygon(p1,p2,p3,p4,Standard_True),
                    wire1 = BRepBuilderAPI_MakePolygon(p5,p6,p7,p8,true);

        TopoDS_Face face1 = BRepBuilderAPI_MakeFace(wire),
                    face2 = BRepBuilderAPI_MakeFace(wire1);
        TopoDS_Shape shape = BRepOffsetAPI_MakePipe(wire,wire1);
        write_step(shape,"pipe.step");
    }
    {
        gp_Pnt 
            p11{0,0,0},
            p22{1,1,1},
            p33{2,1.5,1};
        TopoDS_Wire wire = BRepBuilderAPI_MakePolygon(p11,p22,p33);
        gp_Pnt
            p1 {0,0,0},
            p2 {1,0,0},
            p3 {1,1,0},
            p4 {0,1,0},

            p5 {0,0,0},
            p6 {1,0,0},
            p7 {1,0,1},
            p8 {0,0,1};

        TopoDS_Wire wire2 = BRepBuilderAPI_MakePolygon(p1,p2,p3,p4,Standard_True),
                    wire1 = BRepBuilderAPI_MakePolygon(p5,p6,p7,p8,true);

        TopoDS_Face face1 = BRepBuilderAPI_MakeFace(wire),
                    face2 = BRepBuilderAPI_MakeFace(wire1);
        //TopoDS_Shape shape = BRepOffsetAPI_MakeEvolved(face1,wire);
        //write_step(shape,"pipe.step");
    }

    {
        gp_Pnt 
            gp1 {-2,-2,0},
            gp2 {2,-2,0},
            gp3 {2,2,0},
            gp4 {-2,2,0},

            gp5 {-1,-1,0},
            gp6 {1,-1,0},
            gp7 {1,1,0},
            gp8 {-1,1,0};

        TopoDS_Wire 
            wire = BRepBuilderAPI_MakePolygon(gp1,gp2,gp3,gp4,Standard_True),
            wire2 = BRepBuilderAPI_MakePolygon(gp5,gp6,gp7,gp8,Standard_True);

        TopoDS_Face
            face1 = BRepBuilderAPI_MakeFace(wire),
            face2 = BRepBuilderAPI_MakeFace(wire2);

        TopoDS_Shape box = BRepPrimAPI_MakeBox(1,1,1);
        TopExp_Explorer exp{box,TopAbs_FACE};
        TopoDS_Face face3 = TopoDS::Face(exp.Current());

        BRepFeat_MakePrism prism(box,face3,face3,gp_Dir(0,0,1),Standard_True,Standard_True);

        //write_step(prism.Shape(),"prim.step");
    }

    {
        TopoDS_Shape S = BRepPrimAPI_MakeBox(400.,250.,300.); 
        TopExp_Explorer Ex; 
        Ex.Init(S,TopAbs_FACE); 
        Ex.Next(); 
        Ex.Next(); 
        Ex.Next(); 
        Ex.Next(); 
        Ex.Next(); 
        TopoDS_Face F = TopoDS::Face(Ex.Current()); 
        Handle(Geom_Surface) surf = BRep_Tool::Surface(F); 
        gp_Circ2d 
        c(gp_Ax2d(gp_Pnt2d(200.,130.),gp_Dir2d(1.,0.)),50.); 
        BRepBuilderAPI_MakeWire MW; 
        Handle(Geom2d_Curve) aline = new Geom2d_Circle(c); 
        MW.Add(BRepBuilderAPI_MakeEdge(aline,surf,0.,M_PI)); 
        MW.Add(BRepBuilderAPI_MakeEdge(aline,surf,M_PI,2.* M_PI)); 
        BRepBuilderAPI_MakeFace MKF; 
        MKF.Init(surf,Standard_False,0.1); 
        MKF.Add(MW.Wire()); 
        TopoDS_Face FP = MKF.Face(); 
        BRepLib::BuildCurves3d(FP); 
        BRepFeat_MakeDPrism MKDP (S,FP,F,2 * M_PI,Standard_True, 
                                    Standard_True); 
        MKDP.Perform(200); 
        TopoDS_Shape res1 = MKDP.Shape(); 

        write_step(res1,"custom.step");
    }
    {
        TopoDS_Shape S = BRepPrimAPI_MakeBox(400.,250.,300.); 
        TopExp_Explorer Ex; 
        Ex.Init(S,TopAbs_FACE); 
        Ex.Next(); 
        Ex.Next(); 
        Ex.Next(); 
        Ex.Next(); 
        Ex.Next(); 
        TopoDS_Face F = TopoDS::Face(Ex.Current()); 
        Handle(Geom_Surface) surf = BRep_Tool::Surface(F); 
        gp_Circ2d 
        c(gp_Ax2d(gp_Pnt2d(200.,130.),gp_Dir2d(1.,0.)),50.); 
        BRepBuilderAPI_MakeWire MW; 
        Handle(Geom2d_Curve) aline = new Geom2d_Circle(c); 
        MW.Add(BRepBuilderAPI_MakeEdge(aline,surf,0.,M_PI)); 
        MW.Add(BRepBuilderAPI_MakeEdge(aline,surf,M_PI,2.* M_PI)); 
        BRepBuilderAPI_MakeFace MKF; 
        MKF.Init(surf,Standard_False,0.1); 
        MKF.Add(MW.Wire()); 
        TopoDS_Face FP = MKF.Face(); 
        BRepLib::BuildCurves3d(FP); 
        BRepFeat_MakeRevol MKDP (S,FP,F,gp_Ax1({0,0,0},{1,0,0}),Standard_True, 
                                    Standard_False); 
        MKDP.PerformThruAll(); 
        TopoDS_Shape res1 = MKDP.Shape(); 

        write_step(res1,"custom1.step");
    }
    {
        TopoDS_Shape S = BRepPrimAPI_MakeBox(400.,250.,300.); 
        TopExp_Explorer Ex; 
        Ex.Init(S,TopAbs_FACE); 
        Ex.Next(); 
        Ex.Next(); 
        TopoDS_Face F1 = TopoDS::Face(Ex.Current()); 
        Handle(Geom_Surface) surf = BRep_Tool::Surface(F1); 
        BRepBuilderAPI_MakeWire MW1; 
        gp_Pnt2d p1,p2; 
        p1 = gp_Pnt2d(100.,100.); 
        p2 = gp_Pnt2d(200.,100.); 
        Handle(Geom2d_Line) aline = GCE2d_MakeLine(p1,p2).Value(); 
        
        MW1.Add(BRepBuilderAPI_MakeEdge(aline,surf,0.,p1.Distance(p2))); 
        p1 = p2; 
        p2 = gp_Pnt2d(150.,200.); 
        aline = GCE2d_MakeLine(p1,p2).Value(); 
        
        MW1.Add(BRepBuilderAPI_MakeEdge(aline,surf,0.,p1.Distance(p2))); 
        p1 = p2; 
        p2 = gp_Pnt2d(100.,100.); 
        aline = GCE2d_MakeLine(p1,p2).Value(); 
        
        MW1.Add(BRepBuilderAPI_MakeEdge(aline,surf,0.,p1.Distance(p2))); 
        BRepBuilderAPI_MakeFace MKF1; 
        MKF1.Init(surf,Standard_False,0.1); 
        MKF1.Add(MW1.Wire()); 
        TopoDS_Face FP = MKF1.Face(); 
        BRepLib::BuildCurves3d(FP); 
        TColgp_Array1OfPnt CurvePoles(1,3); 
        gp_Pnt pt = gp_Pnt(150.,0.,150.); 
        CurvePoles(1) = pt; 
        pt = gp_Pnt(200.,100.,150.); 
        CurvePoles(2) = pt; 
        pt = gp_Pnt(150.,200.,150.); 
        CurvePoles(3) = pt; 
        Handle(Geom_BezierCurve) curve = new Geom_BezierCurve 
        (CurvePoles); 
        TopoDS_Edge E = BRepBuilderAPI_MakeEdge(curve); 
        TopoDS_Wire W = BRepBuilderAPI_MakeWire(E); 
        BRepFeat_MakePipe MKPipe (S,FP,F1,W,Standard_False, 
        Standard_True); 
        MKPipe.Perform(); 
        TopoDS_Shape res1 = MKPipe.Shape(); 
        write_step(res1,"custom2.step");
    }
    {
        BRepBuilderAPI_MakeWire mkw; 
        gp_Pnt p1 = gp_Pnt(0.,0.,0.); 
        gp_Pnt p2 = gp_Pnt(200.,0.,0.); 
        mkw.Add(BRepBuilderAPI_MakeEdge(p1,p2)); 
        p1 = p2; 
        p2 = gp_Pnt(200.,0.,50.); 
        mkw.Add(BRepBuilderAPI_MakeEdge(p1,p2)); 
        p1 = p2; 
        p2 = gp_Pnt(50.,0.,50.); 
        mkw.Add(BRepBuilderAPI_MakeEdge(p1,p2)); 
        p1 = p2; 
        p2 = gp_Pnt(50.,0.,200.); 
        mkw.Add(BRepBuilderAPI_MakeEdge(p1,p2)); 
        p1 = p2; 
        p2 = gp_Pnt(0.,0.,200.); 
        mkw.Add(BRepBuilderAPI_MakeEdge(p1,p2)); 
        p1 = p2; 
        mkw.Add(BRepBuilderAPI_MakeEdge(p2,gp_Pnt(0.,0.,0.))); 
        TopoDS_Shape S = BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace
            (mkw.Wire()),gp_Vec{0,500,0});
        TopoDS_Wire W = BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(gp_Pnt 
            (50.,45.,100.), 
        gp_Pnt(100.,45.,50.))); 
        Handle(Geom_Plane) aplane = 
            new Geom_Plane(gp_Pnt(0.,45.,0.),  gp_Vec(0.,1.,0.)); 
        BRepFeat_MakeLinearForm aform(S, W, aplane, gp_Dir 
            (0.,5.,0.), gp_Dir(0.,-3.,0.),  1, Standard_True); 
        aform.Perform(); 
        TopoDS_Shape res = aform.Shape(); 
        write_step(res,"custom3.step");
    }
    {
        Handle(Geom2d_Curve) c1 { new Geom2d_Circle(gp_Ax2d(gp_Pnt2d(0,0),gp_Vec2d(0,1)),1.0) },
            c2 { new Geom2d_Circle(gp_Ax2d(gp_Pnt2d(0.5,0.5),gp_Dir2d(0,1)),1.0) };
        
        gp_Pnt2d p1{};
        Geom2dAPI_InterCurveCurve icc(c1,c2);
        auto n = icc.NbPoints();
        auto p2 = p1;

        auto sn = icc.NbSegments();
        Handle(Geom2d_Curve) scurve{};
        Handle(Geom2d_Curve) scurve2{};

        //icc.Segment(1,scurve,scurve2);
        //TopoDS_Edge eg = BRepBuilderAPI_MakeEdge(icc);
        //write_step(eg,"edge1.step");
    }
    return 0;
}