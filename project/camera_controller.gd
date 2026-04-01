extends Camera3D

@export_group("Movement Settings")
@export var speed: float = 10.0
@export var acceleration: float = 10.0
@export var mouse_sensitivity: float = 0.1

var _velocity: Vector3 = Vector3.ZERO
var _rotation_input: float = 0.0
var _tilt_input: float = 0.0
var _mouse_input: bool = false

func _ready():
	# Captures the mouse so it doesn't leave the game window
	Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)

func _unhandled_input(event):
	# Handle mouse movement
	if event is InputEventMouseMotion and Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED:
		_rotation_input = -event.relative.x * mouse_sensitivity
		_tilt_input = -event.relative.y * mouse_sensitivity
		_mouse_input = true
	
	# Toggle mouse capture with the 'Esc' key
	if event.is_action_pressed("ui_cancel"):
		if Input.get_mouse_mode() == Input.MOUSE_MODE_CAPTURED:
			Input.set_mouse_mode(Input.MOUSE_MODE_VISIBLE)
		else:
			Input.set_mouse_mode(Input.MOUSE_MODE_CAPTURED)

func _physics_process(delta):
	_update_rotation(delta)
	_update_movement(delta)

func _update_rotation(delta):
	# Update horizontal rotation (Y-axis)
	rotate_y(deg_to_rad(_rotation_input))
	
	# Update vertical tilt (X-axis) and clamp it so you don't flip upside down
	rotation.x += deg_to_rad(_tilt_input)
	rotation.x = clamp(rotation.x, deg_to_rad(-89), deg_to_rad(89))
	
	# Reset inputs
	_rotation_input = 0.0
	_tilt_input = 0.0

func _update_movement(delta):
	# Get input direction
	var input_dir = Input.get_vector("ui_left", "ui_right", "ui_up", "ui_down")
	
	# Calculate direction relative to camera orientation
	var direction = (transform.basis * Vector3(input_dir.x, 0, input_dir.y)).normalized()
	
	# Vertical movement (E for Up, Q for Down)
	if Input.is_key_pressed(KEY_E): direction.y += 1
	if Input.is_key_pressed(KEY_Q): direction.y -= 1
	
	# Smoothly interpolate velocity for a "weighty" feel
	_velocity = _velocity.lerp(direction * speed, acceleration * delta)
	
	# Apply movement
	global_translate(_velocity * delta)
