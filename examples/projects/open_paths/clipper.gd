extends Node2D

var line = [Vector2(0, 100), Vector2(200, 100)]
var rect = [Vector2(50, 50), Vector2(150, 50), Vector2(150, 150), Vector2(50, 150)]

var clipper = Clipper.new()


func _ready():
	test_open_paths()


func test_open_paths():
	clipper.clear()

	clipper.set_mode(Clipper.MODE_CLIP)

	clipper.path_type = Clipper.ptSubject
	clipper.open = true # curve
	clipper.add_points(line)

	clipper.path_type = Clipper.ptClip
	clipper.open = false # polygon
	clipper.add_points(rect)

	clipper.execute()

	update()


func _draw():

	draw_multiline(line, Color.magenta)
	draw_colored_polygon(rect, Color.magenta)

	for idx in clipper.get_solution_count(Clipper.TYPE_OPEN):
		var line = clipper.get_solution(idx, Clipper.TYPE_OPEN)
		draw_multiline(line, Color.green)


func _on_operation_selected(ID):
	match ID:
		0:
			clipper.clip_type = Clipper.ctUnion
		1:
			clipper.clip_type = Clipper.ctDifference
		2:
			clipper.clip_type = Clipper.ctIntersection
		3:
			clipper.clip_type = Clipper.ctXor # same as union (?)

	test_open_paths()
