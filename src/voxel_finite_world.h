#ifndef VOXEL_FINITE_WORLD_H
#define VOXEL_FINITE_WORLD_H

#include "block_registry.h"
#include "chunk_data.h"
#include "chunk_mesher.h"
#include "greedy_chunk_mesher.h"
#include "chunk_manager.h"
#include "godot_cpp/classes/texture2d_array.hpp"
#include "godot_cpp/classes/fast_noise_lite.hpp"
#include "godot_cpp/classes/material.hpp"
#include "godot_cpp/classes/shader_material.hpp"
#include "godot_cpp/classes/world3d.hpp"
#include "godot_cpp/classes/window.hpp"
#include "godot_cpp/classes/scene_tree.hpp"
#include "godot_cpp/classes/node3d.hpp"
#include "godot_cpp/classes/visual_shader_node_vec2_constant.hpp"
#include "godot_cpp/variant/vector3i.hpp"
#include "world_data.h"

using namespace godot;

namespace voxxel {

class VoxelFiniteWorld : public Node3D {
	GDCLASS(VoxelFiniteWorld, Node3D)

	public:
	VoxelFiniteWorld();
	~VoxelFiniteWorld() override = default;

	void _ready() override;

	void set_material(Ref<ShaderMaterial> p_material);
	Ref<ShaderMaterial> get_material() const;

	void set_block_registry(Ref<BlockRegistry> p_block_registry);
	Ref<BlockRegistry> get_block_registry() const;

	Ref<WorldData> get_world_data() const {
		return world_data;
	} // TEMPORARY, need encapsulation later

	protected:
	static void _bind_methods();

	private:
	const Vector3i WORLD_SIZE = Vector3i(8, 4, 8);

	Ref<ShaderMaterial> material;
	Ref<WorldData> world_data;
  Ref<ChunkMesher> mesher;	
	HashMap<Vector3i, Ref<ChunkManager>> chunks{};
  Ref<BlockRegistry> block_registry;
	
	Ref<WorldData> generate_world(const Vector3i world_size); // TODO: Make WorldGenerator a standalone component
	void initialize_chunks();
	void update_chunk(const Vector3i chunk_coord);	
  void update_all_chunks();
};

} // namespace voxxel

#endif // VOXEL_FINITE_WORLD_H
