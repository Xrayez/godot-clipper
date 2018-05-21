#include "clipper.h"

#define PRECISION 10000.0

Clipper::Clipper(): mode(MODE_CLIP) {}

void Clipper::add_path(const Vector<Vector2> &points, cl::PathType polytype, bool is_open) {

    // Scaling needs to be taken into account as well

    // switch(mode) {

    //     case MODE_CLIP:
    //         cl.AddPath()
    // }
}

void Clipper::_bind_methods() {

    ClassDB::bind_method(D_METHOD("set_mode", "mode"), &Clipper::set_mode);
    ClassDB::bind_method(D_METHOD("get_mode"), &Clipper::get_mode);

    ClassDB::bind_method(D_METHOD("add_path", "points", "path_type", "is_open"), &Clipper::add_path);

    ClassDB::bind_method(D_METHOD("get_version"), &Clipper::get_version);

    using namespace clipperlib;
    // Use namespace declaration to avoid having
    // prepended namespace name in enum constants
    BIND_ENUM_CONSTANT(MODE_CLIP);
    BIND_ENUM_CONSTANT(MODE_OFFSET);
    BIND_ENUM_CONSTANT(MODE_TRIANGULATE);

    BIND_ENUM_CONSTANT(ctNone);
    BIND_ENUM_CONSTANT(ctIntersection);
    BIND_ENUM_CONSTANT(ctUnion);
    BIND_ENUM_CONSTANT(ctDifference);
    BIND_ENUM_CONSTANT(ctXor);

    BIND_ENUM_CONSTANT(ptSubject);
    BIND_ENUM_CONSTANT(ptClip);

    BIND_ENUM_CONSTANT(frEvenOdd);
    BIND_ENUM_CONSTANT(frNonZero);
    BIND_ENUM_CONSTANT(frPositive);
    BIND_ENUM_CONSTANT(frNegative);
}
