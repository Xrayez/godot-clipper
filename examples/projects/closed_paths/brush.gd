extends Node2D

const MIN_BRUSH_RADIUS = 8.0
const MAX_BRUSH_RADIUS = 512.0

enum BrushType {
	CIRCLE
	RECT
}
export(BrushType) var type = BrushType.CIRCLE setget set_type
export var size = 64 setget set_size


func set_type(p_type):
	type = p_type
	update()


func set_size(p_size):
	size = p_size
	update()


func get_points(maxerror = 0.5):

	var points = PoolVector2Array([])

	match type:
		BrushType.CIRCLE:
			var maxpoints = 1024 # I think this is renderer limit

			var radius = size / 2.0

			var numpoints = ceil(PI / acos(1.0 - maxerror / radius))
			numpoints = clamp(numpoints, 3, maxpoints)

			for i in numpoints:
				var phi = i * PI * 2.0 / numpoints
				var v = Vector2(sin(phi), cos(phi))
				points.push_back(v * radius)

		BrushType.RECT:
			var half = size
			points.push_back(Vector2(-half, -half))
			points.push_back(Vector2(half, -half))
			points.push_back(Vector2(half, half))
			points.push_back(Vector2(-half, half))

	return points


func get_points_transformed():
	var points = get_points()
	var transformed = []

	for p in points:
		p = transform.xform(p)
		transformed.push_back(p)

	return transformed


func draw_brush():
	var points = get_points()
	if points.size():
		draw_colored_polygon(points, Color(1.0, 1.0, 1.0, 0.5))


func _draw():
	draw_brush()
