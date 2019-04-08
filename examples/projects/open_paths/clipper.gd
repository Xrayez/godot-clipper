extends Node2D

const DRAW_OFFSET = Vector2(50, 50)

var line = [Vector2(0, 100), Vector2(200, 100), Vector2(200, 200)]
var rect = [Vector2(50, 50), Vector2(150, 50), Vector2(150, 150), Vector2(50, 150)]

var clipper = Clipper.new()


func _ready():
	test_open_paths()


func test_open_paths():
	clipper.clear()

	match clipper.mode:

		Clipper.MODE_CLIP:

			clipper.path_type = Clipper.ptSubject
			clipper.open = true # curve
			clipper.add_points(line)

			clipper.path_type = Clipper.ptClip
			clipper.open = false # polygon
			clipper.add_points(rect)

		Clipper.MODE_OFFSET:

			clipper.path_type = Clipper.ptSubject
			clipper.open = true # curve

			# Offset amount
			clipper.delta = 20.0

			# Creates square "passages" from open path (line):
			clipper.end_type = Clipper.kOpenSquare

			clipper.add_points(line)

	clipper.execute()

	update()


func _draw():

	print(true)

	draw_set_transform(DRAW_OFFSET, 0, Vector2.ONE)

	match clipper.mode:

		Clipper.MODE_CLIP:

			draw_polyline(line, Color.red)
			draw_colored_polygon(rect, Color.red)

			for idx in clipper.get_solution_count(Clipper.TYPE_OPEN):
				var line = clipper.get_solution(idx, Clipper.TYPE_OPEN)
				draw_polyline(line, Color.green)

		Clipper.MODE_OFFSET:

			# Line offseting results in polygon

			draw_polyline(line, Color.red)

			for idx in clipper.get_solution_count(Clipper.TYPE_CLOSED):
				var polygon = clipper.get_solution(idx, Clipper.TYPE_CLOSED)
				draw_polyline(polygon, Color.green)
				draw_line(polygon[0], polygon[-1], Color.green) # last


func _on_operation_selected(ID):
	match ID:
		0:
			clipper.clip_type = Clipper.ctUnion
		1:
			clipper.clip_type = Clipper.ctDifference
		2:
			clipper.clip_type = Clipper.ctIntersection
		3:
			clipper.clip_type = Clipper.ctXor # same as union for lines (?)

	test_open_paths()


func _on_mode_selected(ID):
	var is_reusing_solution = false

	match ID:
		0:
			clipper.set_mode(Clipper.MODE_CLIP, is_reusing_solution)
		1:
			clipper.set_mode(Clipper.MODE_OFFSET, is_reusing_solution)

	test_open_paths()
