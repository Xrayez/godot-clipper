#ifndef GODOT_CLIPPER_HPP
#define GODOT_CLIPPER_HPP

#include "reference.h"

#include "lib/clipper.h"
#include "lib/clipper_offset.h"
#include "lib/clipper_triangulation.h"

namespace cl = clipperlib;

enum ClipMode {
    MODE_CLIP,
    MODE_OFFSET,
    MODE_TRIANGULATE
};

class Clipper : public Reference {
    GDCLASS(Clipper, Reference);

public:
    Clipper();

    void add_path(const Vector<Vector2> &points, cl::PathType polytype, bool is_open);

    void set_mode(ClipMode p_mode) { mode = p_mode; }
    ClipMode get_mode() const { return mode; }

//------------------------------------------------------------------------------
// Meta methods
//------------------------------------------------------------------------------
    String get_version() const { return CLIPPER_VERSION; }

protected:
    static void  _bind_methods();

private:
    ClipMode mode;

    cl::Clipper cl;
    cl::ClipperOffset co;
    cl::ClipperTri ct;
};

VARIANT_ENUM_CAST(ClipMode);

VARIANT_ENUM_CAST(cl::ClipType);
VARIANT_ENUM_CAST(cl::PathType);
VARIANT_ENUM_CAST(cl::FillRule);

#endif
