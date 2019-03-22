# Godot Clipper module

# Work in progress!

This is only a preview. The library is currently undergoing a rewrite by the
original author, so expect API to be changed at any point in this module.

This is not Clipper 6.4.2!
The code is taken from
[Clipper2](https://sourceforge.net/p/polyclipping/code/HEAD/tree/sandbox/Clipper2/)
sandbox, which adds additional support for robust polygon triangulation.

---

## Descriptiton

This is a wrapper for the popular polygon clipping library written by
Angus Johnson: [Clipper](https://sourceforge.net/projects/polyclipping/)

Currently you'll find three Clipper modules combined:

* Clipper - boolean polygon operations (union, intersection, difference, xor)
* ClipperOffset - inflates/deflates polygons
* ClipperTri - triangulates clipping solution (polygons)

For any information regarding the library itself please refer to the official
[documentation](http://www.angusj.com/delphi/clipper/documentation/Docs/Units/ClipperLib/_Body.htm) page (not up to date with the latest version though).

## Installation

```bash
# Change directory to `modules` subfolder of Godot repository
cd godot/modules/
# Clone the module under directory named `clipper`
git clone https://github.com/Xrayez/godot-clipper.git clipper && cd ..
# Compile the engine manually, for instance:
scons platform=windows target=release_debug bits=64
```

## Usage example

```gdscript
var rect_1 = [Vector2(0, 0), Vector2(100, 0), Vector2(100, 100), Vector2(0, 100)]
var rect_2 = [Vector2(50, 50), Vector2(150, 50), Vector2(150, 150), Vector2(50, 150)]

var clipper = Clipper.new()

clipper.set_mode(Clipper.MODE_CLIP)

# Subject
clipper.path_type = Clipper.ptSubject
clipper.add_points(rect_1)

# Clip
clipper.path_type = Clipper.ptClip
clipper.add_points(rect_2)

# Execute
clipper.clip_type = Clipper.ctDifference
clipper.execute()

# Get result
for idx in clipper.get_solution_count():
	var points = clipper.get_solution(idx)

# Switch to other modes
# transfers clipping solution from previous operation by default
clipper.set_mode(Clipper.MODE_TRIANGULATE)
clipper.clip_type = Clipper.ctUnion
clipper.execute()

# Get result...
```

### Result

![Clipping solution](examples/images/solution.png)
