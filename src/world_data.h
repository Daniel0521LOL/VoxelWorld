#ifndef WORLD_DATA_H
#define WORLD_DATA_H

#include "chunk_data.h"
#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/templates/hash_map.hpp"
#include "raycast_result.h"

using namespace godot;

namespace voxxel {

class WorldData : public RefCounted {
	GDCLASS(WorldData, RefCounted)

	protected:
	static void _bind_methods();

	public:
	WorldData() = default;
	~WorldData() override = default;

	Ref<ChunkData> get_chunk(const Vector3i &p_chunk_pos);
	Ref<ChunkData> initialize_chunk(const Vector3i &p_chunk_pos);

	Ref<RaycastResult> raycast(const Vector3 &p_origin, const Vector3 &p_direction, float p_max_distance);

	uint8_t get_block(const Vector3i &p_global_pos);

	private:
	HashMap<Vector3i, Ref<ChunkData>> chunks;
};

} // namespace voxxel

#endif // WORLD_DATA_H
