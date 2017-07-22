#ifndef GODOT_CLIPPER_HPP
#define GODOT_CLIPPER_HPP

#include "reference.h"
#include "lib/clipper.hpp"

class Clipper : public Reference {
    GDCLASS(Clipper, Reference);

public:
    String get_version() { return CLIPPER_VERSION; }

protected:
    static void  _bind_methods();
};

#endif