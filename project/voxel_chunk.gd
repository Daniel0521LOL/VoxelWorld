extends VoxelChunk

func _ready() -> void:
	test_initialize_chunk_data()

func test_initialize_chunk_data():
	var chunk_data = ChunkData.new()
	pattern_checkerboard(chunk_data)
	#for x in range(0, 16):
		#for y in range(0, 16):
			#for z in range(0, 16):
				#if randf() <= 0.3:
					#chunk_data.set_block(Vector3i(x, y, z), 1)
	set_chunk_data(chunk_data)

func pattern_checkerboard(chunk_data: ChunkData):
	for x in range(2):
		for y in range(16):
			for z in range(16):
				# The modulo check creates the alternating pattern
				if (x + y + z) % 3 != 0:
					chunk_data.set_block(Vector3i(x, y, z), 1)
					
func pattern_sierpinski(chunk_data: ChunkData):
	for x in range(16):
		for y in range(16):
			for z in range(16):
				if _is_sierpinski(x, y, z):
					chunk_data.set_block(Vector3i(x, y, z), 1)

func _is_sierpinski(x: int, y: int, z: int) -> bool:
	var tx = x
	var ty = y
	var tz = z
	# Standard Menger Sponge logic
	while tx > 0 or ty > 0 or tz > 0:
		if (tx % 3 == 1 and ty % 3 == 1) or \
		   (ty % 3 == 1 and tz % 3 == 1) or \
		   (tx % 3 == 1 and tz % 3 == 1):
			return false
		tx /= 3
		ty /= 3
		tz /= 3
	return true

func pattern_l_shape(chunk_data: ChunkData):
	# A 3x1 row
	chunk_data.set_block(Vector3i(1, 1, 1), 1)
	chunk_data.set_block(Vector3i(2, 1, 1), 1)
	chunk_data.set_block(Vector3i(3, 1, 1), 1)
	# A 1x2 column attached to the end
	chunk_data.set_block(Vector3i(3, 1, 2), 1)
	chunk_data.set_block(Vector3i(3, 1, 3), 1)

func pattern_stairs(chunk_data: ChunkData):
	for i in range(4):
		chunk_data.set_block(Vector3i(i, i, 1), 1)
		chunk_data.set_block(Vector3i(i + 1, i, 1), 1) # Double wide step

func pattern_donut(chunk_data: ChunkData):
	for x in range(1, 4):
		for z in range(1, 4):
			if x == 2 and z == 2: 
				continue # Skip the middle
			chunk_data.set_block(Vector3i(x, 1, z), 1)
