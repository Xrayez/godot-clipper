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

//------------------------------------------------------------------------------
// Clipping methods
//------------------------------------------------------------------------------
    void set_mode(ClipMode p_mode) { mode = p_mode; }
    ClipMode get_mode() const { return mode; }

    void add_points(const Vector<Vector2>& points);
    void execute();

    int get_solution_count() const;
    Vector<Vector2> get_solution(int idx);

    void clear();

//------------------------------------------------------------------------------
// Configuration methods
//------------------------------------------------------------------------------
    // Path and execute configuration, define these before adding new paths
    // Each path added will have the same configuration as the previous one
    // Define parameters that are relevant to particular operation

    void set_open(bool p_is_open) { open = p_is_open; }
    bool is_open() const { return open; }

    void set_path_type(cl::PathType p_path_type) { path_type = p_path_type; }
    cl::PathType get_path_type() const { return path_type; }

    void set_clip_type(cl::ClipType p_clip_type) { clip_type = p_clip_type; }
    cl::ClipType get_clip_type() const { return clip_type; }

    void set_join_type(cl::JoinType p_join_type) { join_type = p_join_type; }
    cl::JoinType get_join_type() const { return join_type; }

    void set_end_type(cl::EndType p_end_type) { end_type = p_end_type; }
    cl::EndType get_end_type() const { return end_type; }

    void set_fill_rule(cl::FillRule p_fill_rule) { fill_rule = p_fill_rule; }
    cl::FillRule get_fill_rule() const { return fill_rule; }

    void set_delta(real_t p_delta) { delta = p_delta; }
    real_t get_delta() const { return delta; }

//------------------------------------------------------------------------------
// Meta methods
//------------------------------------------------------------------------------
    String get_version() const { return CLIPPER_VERSION; }

protected:
    static void  _bind_methods();

private:
    cl::Path _scale_up(const Vector<Vector2>& points, real_t scale);
    Vector<Vector2> _scale_down(const cl::Path& path, real_t scale);

    bool open;
    cl::FillRule fill_rule;
    cl::PathType path_type;
    cl::JoinType join_type;
    cl::ClipType clip_type;
    cl::EndType end_type;
    real_t delta;

    ClipMode mode;

    cl::Paths solution_closed;
    cl::Paths solution_open;

    cl::Clipper cl;
    cl::ClipperOffset co;
    cl::ClipperTri ct;
};

VARIANT_ENUM_CAST(ClipMode);

VARIANT_ENUM_CAST(cl::ClipType);
VARIANT_ENUM_CAST(cl::PathType);
VARIANT_ENUM_CAST(cl::FillRule);

VARIANT_ENUM_CAST(cl::JoinType);
VARIANT_ENUM_CAST(cl::EndType);

#endif
