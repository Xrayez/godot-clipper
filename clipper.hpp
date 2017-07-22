#ifndef GODOT_CLIPPER_HPP
#define GODOT_CLIPPER_HPP

#include "reference.h"
#include "lib/clipper.hpp"

namespace cl = ClipperLib;

class Clipper : public Reference {
    GDCLASS(Clipper, Reference);

public:
//------------------------------------------------------------------------------
// Clipper constants
//------------------------------------------------------------------------------
    enum ClipType {
        INTERSECTION = cl::ctIntersection,
        UNION        = cl::ctUnion,
        DIFFERENCE   = cl::ctDifference,
        XOR          = cl::ctXor
    };
    enum PolyType { 
        SUBJECT = cl::ptSubject,
        CLIP    = cl::ptClip
    };
    enum PolyFillType { 
        EVEN_ODD = cl::pftEvenOdd, 
        NON_ZERO = cl::pftNonZero, 
        POSITIVE = cl::pftPositive, 
        NEGATIVE = cl::pftNegative
    };
    enum InitOptions {
        REVERSE_SOLUTION   = 1, 
        STRICTLY_SIMPLE    = 2, 
        PRESERVE_COLLINEAR = 4
    };
    enum JoinType { 
        SQUARE = cl::jtSquare, 
        ROUND  = cl::jtRound, 
        MITER  = cl::jtMiter
    };
    enum EndType {
        CLOSED_POLYGON = cl::etClosedPolygon, 
        CLOSED_LINE    = cl::etClosedLine, 
        OPEN_BUTT      = cl::etOpenButt, 
        OPEN_SQUARE    = cl::etOpenSquare, 
        OPEN_ROUND     = cl::etOpenRound
    };
//------------------------------------------------------------------------------
// Meta methods
//------------------------------------------------------------------------------
    String get_version() { return CLIPPER_VERSION; }

protected:
    static void  _bind_methods();
};

#endif