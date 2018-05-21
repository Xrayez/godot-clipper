#include "clipper.h"

void Clipper::_bind_methods() {

    ClassDB::bind_method(D_METHOD("get_version"), &Clipper::get_version);

    using namespace clipperlib;
    // Use namespace declaration to avoid having
    // prepended namespace name in enum constants
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
