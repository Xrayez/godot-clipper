#include "clipper.h"

#define PRECISION 10000.0

Clipper::Clipper(): mode(MODE_CLIP),
                    open(false),
                    fill_rule(cl::frEvenOdd),
                    path_type(cl::ptSubject),
                    join_type(cl::kSquare),
                    end_type(cl::kPolygon),
                    clip_type(cl::ctUnion),
                    delta(0.0) {}

void Clipper::add_points(const Vector<Vector2>& points) {

    const cl::Path& path = _scale_up(points, PRECISION);

    switch(mode) {

        case MODE_CLIP: {
            cl.AddPath(path, path_type, open);
        } break;

        case MODE_OFFSET: {
            co.AddPath(path, join_type, end_type);
        } break;

        case MODE_TRIANGULATE: {
            ct.AddPath(path, path_type, open);
        } break;
    }
}

void Clipper::execute() {

    switch(mode) {

        case MODE_CLIP: {
            cl.Execute(clip_type, solution_closed, solution_open, fill_rule);
        } break;

        case MODE_OFFSET: {
            co.Execute(solution_closed, delta * PRECISION);
        } break;

        case MODE_TRIANGULATE: {
            ct.Execute(clip_type, solution_closed, fill_rule);
        } break;
    }
}

void Clipper::clear() {

    solution_closed.clear();
    solution_open.clear();

    cl.Clear();
    co.Clear();
    ct.Clear();
}

int Clipper::get_solution_count() const {

    return solution_closed.size();
}

Vector<Vector2> Clipper::get_solution(int idx) {

    ERR_EXPLAIN("Clipping solution not found");
    ERR_FAIL_INDEX_V(idx, solution_closed.size(), Vector<Vector2>());

    const Vector<Vector2>& points = _scale_down(solution_closed[idx], PRECISION);

    return points;
}

Rect2 Clipper::get_bounds() {

    ERR_EXPLAIN("Cannot get bounds in MODE_OFFSET");
    ERR_FAIL_COND_V(mode == MODE_OFFSET, Rect2());

    cl::Rect64 b(0,0,0,0);

    switch(mode) {

        case MODE_CLIP: {
            b = cl.GetBounds();
        } break;

        case MODE_TRIANGULATE: {
            b = ct.GetBounds();
        } break;
    }

    cl::Point64 pos(b.left, b.top);
    cl::Point64 size(b.right - b.left, b.bottom - b.top);

    Rect2 bounds(
        static_cast<real_t>(pos.x) / PRECISION,
        static_cast<real_t>(pos.y) / PRECISION,
        static_cast<real_t>(size.x) / PRECISION,
        static_cast<real_t>(size.y) / PRECISION
    );
    return bounds;
}

void Clipper::set_mode(ClipMode p_mode, bool reuse_solution) {

    if(mode == p_mode)
        return;

    mode = p_mode;

    if(reuse_solution) {

        // Transfer resulted solution from previous execution
        switch(mode) {

            case MODE_CLIP: {
                cl.AddPaths(solution_closed, path_type, open);
            } break;

            case MODE_OFFSET: {
                co.AddPaths(solution_closed, join_type, end_type);
            } break;

            case MODE_TRIANGULATE: {
                ct.AddPaths(solution_closed, path_type, open);
            } break;
        }
    }
}

_FORCE_INLINE_ cl::Path Clipper::_scale_up(const Vector<Vector2>& points, real_t scale) {

    cl::Path path;
    path.resize(points.size());

    for(int i = 0; i != points.size(); ++i) {
        path[i] = cl::Point64(
            points[i].x * scale,
            points[i].y * scale
        );
    }
    return path;
}

_FORCE_INLINE_ Vector<Vector2> Clipper::_scale_down(const cl::Path& path, real_t scale) {

    Vector<Vector2> points;
    points.resize(path.size());

    for(int i = 0; i != path.size(); ++i) {
        points[i] = Point2(
            static_cast<real_t>(path[i].x) / scale,
            static_cast<real_t>(path[i].y) / scale
        );
    }
    return points;
}

void Clipper::_bind_methods() {

//------------------------------------------------------------------------------
// Clipper methods
//------------------------------------------------------------------------------

    ClassDB::bind_method(D_METHOD("add_points", "points"), &Clipper::add_points);
    ClassDB::bind_method(D_METHOD("execute"), &Clipper::execute);

    ClassDB::bind_method(D_METHOD("get_solution_count"), &Clipper::get_solution_count);
    ClassDB::bind_method(D_METHOD("get_solution", "index"), &Clipper::get_solution);

    ClassDB::bind_method(D_METHOD("clear"), &Clipper::clear);

    ClassDB::bind_method(D_METHOD("get_bounds"), &Clipper::get_bounds);

    ADD_PROPERTY(PropertyInfo(Variant::RECT2, "bounds"), "", "get_bounds");

//------------------------------------------------------------------------------
// Configuration methods
//------------------------------------------------------------------------------
    ClassDB::bind_method(D_METHOD("set_mode", "mode", "reuse_solution"), &Clipper::set_mode, DEFVAL(true));
    ClassDB::bind_method(D_METHOD("get_mode"), &Clipper::get_mode);

    ClassDB::bind_method(D_METHOD("set_open", "is_open"), &Clipper::set_open);
    ClassDB::bind_method(D_METHOD("is_open"), &Clipper::is_open);

    ClassDB::bind_method(D_METHOD("set_path_type", "path_type"), &Clipper::set_path_type);
    ClassDB::bind_method(D_METHOD("get_path_type"), &Clipper::get_path_type);

    ClassDB::bind_method(D_METHOD("set_clip_type", "clip_type"), &Clipper::set_clip_type);
    ClassDB::bind_method(D_METHOD("get_clip_type"), &Clipper::get_clip_type);

    ClassDB::bind_method(D_METHOD("set_fill_rule", "fill_rule"), &Clipper::set_fill_rule);
    ClassDB::bind_method(D_METHOD("get_fill_rule"), &Clipper::get_fill_rule);

    ClassDB::bind_method(D_METHOD("set_join_type", "join_type"), &Clipper::set_join_type);
    ClassDB::bind_method(D_METHOD("get_join_type"), &Clipper::get_join_type);

    ClassDB::bind_method(D_METHOD("set_end_type", "end_type"), &Clipper::set_end_type);
    ClassDB::bind_method(D_METHOD("get_end_type"), &Clipper::get_clip_type);

    ClassDB::bind_method(D_METHOD("set_delta", "delta"), &Clipper::set_delta);
    ClassDB::bind_method(D_METHOD("get_delta"), &Clipper::get_delta);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "mode"), "", "get_mode");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "open"), "set_open", "is_open");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "path_type"), "set_path_type", "get_path_type");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "clip_type"), "set_clip_type", "get_clip_type");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "fill_rule"), "set_fill_rule", "get_fill_rule");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "end_type"), "set_end_type", "get_end_type");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "join_type"), "set_join_type", "get_join_type");
    ADD_PROPERTY(PropertyInfo(Variant::REAL, "delta"), "set_delta", "get_delta");

//------------------------------------------------------------------------------
// Meta methods
//------------------------------------------------------------------------------
    ClassDB::bind_method(D_METHOD("get_version"), &Clipper::get_version);

//------------------------------------------------------------------------------
// Enums
//------------------------------------------------------------------------------
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

    BIND_ENUM_CONSTANT(kSquare);
    BIND_ENUM_CONSTANT(kRound);
    BIND_ENUM_CONSTANT(kMiter);

    BIND_ENUM_CONSTANT(kPolygon);
    BIND_ENUM_CONSTANT(kOpenJoined);
    BIND_ENUM_CONSTANT(kOpenButt);
    BIND_ENUM_CONSTANT(kOpenSquare);
    BIND_ENUM_CONSTANT(kOpenRound);
}
