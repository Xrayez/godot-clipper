#ifndef GODOT_CLIPPER_HPP
#define GODOT_CLIPPER_HPP

#include "reference.h"

#include "lib/clipper.h"
#include "lib/clipper_offset.h"
#include "lib/clipper_triangulation.h"

namespace cl = clipperlib;

class Clipper : public Reference {
    GDCLASS(Clipper, Reference);

public:
//------------------------------------------------------------------------------
// Meta methods
//------------------------------------------------------------------------------
    String get_version() const { return CLIPPER_VERSION; }

protected:
    static void  _bind_methods();
};

VARIANT_ENUM_CAST(clipperlib::ClipType);
VARIANT_ENUM_CAST(clipperlib::PathType);
VARIANT_ENUM_CAST(clipperlib::FillRule);

#endif
