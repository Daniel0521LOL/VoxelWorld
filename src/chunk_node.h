#ifndef VOXXEL_CHUNK_NODE_H
#define VOXXEL_CHUNK_NODE_H

#include "basic_chunk_mesher.h"
#include "chunk_data.h"
#include "chunk_mesher.h"
#include "godot_cpp/classes/collision_shape3d.hpp"
#include "godot_cpp/classes/concave_polygon_shape3d.hpp"
#include "godot_cpp/classes/mesh_instance3d.hpp"
#include "godot_cpp/classes/shape3d.hpp"
#include "godot_cpp/classes/static_body3d.hpp"
#include "greedy_chunk_mesher.h"

using namespace godot;

namespace voxxel {

class VoxelChunk : public StaticBody3D {
	GDCLASS(VoxelChunk, StaticBody3D)

	protected:
	static void _bind_methods();

	public:
	VoxelChunk() = default;
	~VoxelChunk() override = default;

	void _ready() override;

	void set_chunk_data(const Ref<ChunkData> &p_chunk_data);
	void set_mesher(const Ref<ChunkMesher> &p_mesher);
	void set_mesh_material(const Ref<Material> &p_material);
	Ref<ChunkData> get_chunk_data() const;

	private:
	void update_mesh();

	Ref<ChunkData> chunk_data;
	Ref<ChunkMesher> mesher;
	MeshInstance3D *mesh_instance = nullptr;
	CollisionShape3D *collision_shape = nullptr;
};

} // namespace voxxel

#endif // VOXXEL_CHUNK_NODE_H