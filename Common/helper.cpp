#include "helper.h"

void write_step(TopoDS_Shape const &shape, Standard_CString const &fname)
{
    STEPControl_Writer writer{};
    writer.Transfer(shape,STEPControl_AsIs);
    writer.Write(fname);
}
