extends Node2D

export(bool) var snap_to_grid = false
export(Vector2) var grid_size = Vector2(64, 64)

var clipper = Clipper.new()
var polys = []


func _process(_delta):
	var pos = get_global_mouse_position()

#	Snap to grid
	if snap_to_grid:
		pos = pos.snapped(grid_size)

	$brush.global_position = pos


func _unhandled_input(event):
	if event.is_action_pressed("click"):
		var clip_points = $brush.get_points_transformed()
		execute(clip_points)


func execute(clip_points):

	clipper.clear()

	# Subject
	for poly in polys:
		clipper.path_type = Clipper.ptSubject
		clipper.add_points(poly)

	# Clip
	clipper.path_type = Clipper.ptClip
	clipper.add_points(clip_points)

	# Execute
	clipper.execute()

	# Get result
	polys.clear()
	for idx in clipper.get_solution_count():
		var points = clipper.get_solution(idx)
		polys.push_back(points)

	update()


func _draw():

	match clipper.mode:

		Clipper.MODE_CLIP:

			for poly in polys:
				var color = Color(randf(), randf(), randf())
				draw_polygon(poly, PoolColorArray([color]))

		Clipper.MODE_OFFSET:
			pass # to be implemented

		Clipper.MODE_TRIANGULATE:
			pass # to be implemented

			var idx = 0
			while idx < polys.size():
				var tri_points = PoolVector2Array([polys[idx], polys[idx + 1], polys[idx + 2]])
				draw_polygon(tri_points, PoolColorArray([Color(randf(), randf(), randf())]))
				idx += 3


func _on_operation_item_selected(ID):
	match ID:
		0:
			clipper.clip_type = Clipper.ctUnion
		1:
			clipper.clip_type = Clipper.ctDifference
		2:
			clipper.clip_type = Clipper.ctIntersection
		3:
			clipper.clip_type = Clipper.ctXor
