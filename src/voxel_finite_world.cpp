#include "voxel_finite_world.h"
#include "godot_cpp/variant/utility_functions.hpp"

using namespace godot;

namespace voxxel {

VoxelFiniteWorld::VoxelFiniteWorld() {
	Ref<GreedyChunkMesher> greedy_mesher;
	greedy_mesher.instantiate();
	greedy_mesher->set_block_registry(block_registry);
	mesher = greedy_mesher;
}

void VoxelFiniteWorld::_ready() {
	UtilityFunctions::print("VoxelFiniteWorld ready ...");	
	world_data = generate_world(WORLD_SIZE);
	initialize_chunks();
	update_all_chunks();
}

void VoxelFiniteWorld::_bind_methods() {
//	ClassDB::bind_method(D_METHOD("generate_world"), &VoxelFiniteWorld::generate_world);
	ClassDB::bind_method(D_METHOD("set_material", "material"), &VoxelFiniteWorld::set_material);
	ClassDB::bind_method(D_METHOD("set_block_registry", "block_registry"), &VoxelFiniteWorld::set_block_registry);
	ClassDB::bind_method(D_METHOD("get_material"), &VoxelFiniteWorld::get_material);
	ClassDB::bind_method(D_METHOD("get_block_registry"), &VoxelFiniteWorld::get_block_registry);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "material", PROPERTY_HINT_RESOURCE_TYPE, "ShaderMaterial"), "set_material", "get_material");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "block_registry", PROPERTY_HINT_RESOURCE_TYPE, "BlockRegistry"), "set_block_registry", "get_block_registry");
}

Ref<WorldData> VoxelFiniteWorld::generate_world(const Vector3i world_size) {
	Ref<FastNoiseLite> noise;	
	noise.instantiate();
	Ref<WorldData> _world_data;
	_world_data.instantiate();
	UtilityFunctions::print("Beginning World Generation ...");	
	for (int x = 0; x < WORLD_SIZE.x; x++) {
		for (int y = 0; y < WORLD_SIZE.y; y++) {
			for (int z = 0; z < WORLD_SIZE.z; z++) {
				Vector3i chunk_pos(x, y, z);
				Ref<ChunkData> chunk_data = _world_data->initialize_chunk(chunk_pos);
				// Simple noise-based terrain generation
				for (int bx = 0; bx < CHUNK_SIZE; bx++) {
					for (int by = 0; by < CHUNK_SIZE; by++) {
						for (int bz = 0; bz < CHUNK_SIZE; bz++) {
							Vector3 world_pos = Vector3(
											(chunk_pos.x * CHUNK_SIZE) + bx,
											(chunk_pos.y * CHUNK_SIZE) + by,
											(chunk_pos.z * CHUNK_SIZE) + bz);
							float height = noise->get_noise_3dv(world_pos / 10.0) * 10.0 + 20.0;
							if (world_pos.y < height) {
								if (world_pos.y < height - 5) {
									chunk_data->set_block(Vector3i(bx, by, bz), 1); // Set block ID to 1 for stone block
								} else {
									chunk_data->set_block(Vector3i(bx, by, bz), 2);// Set block ID to 2 for solid block
								}
							}
						}
					}
				}
			}
		}
	}

	UtilityFunctions::print("World generation finished!");	
  return _world_data;	
}

void VoxelFiniteWorld::set_material(Ref<ShaderMaterial> p_material) {
	material = p_material;	
}

Ref<ShaderMaterial> VoxelFiniteWorld::get_material() const {
	return material;
}

void VoxelFiniteWorld::set_block_registry(Ref<BlockRegistry> p_block_registry) {
	block_registry = p_block_registry;
	if (mesher.is_valid()) {
		mesher->set_block_registry(p_block_registry);
	}
}

Ref<BlockRegistry> VoxelFiniteWorld::get_block_registry() const {
	return block_registry;
}

void VoxelFiniteWorld::initialize_chunks() {

	UtilityFunctions::print("Initializing Chunks ...");	
	Ref<World3D> world_3d = get_world_3d();
	if (world_3d.is_null()) {
		UtilityFunctions::print("ERROR: world of VoxelFiniteWorld invalid!");		
		return;
	}
	RID scenario = world_3d->get_scenario();
	for (int x = 0; x < WORLD_SIZE.x; x++) {
		for (int y = 0; y < WORLD_SIZE.y; y++) {
			for (int z = 0; z < WORLD_SIZE.z; z++) {
				Vector3i chunk_coords(x, y, z);				
				Ref<ChunkManager> new_chunk;
				new_chunk.instantiate();	
				new_chunk->initialize(mesher, scenario, chunk_coords, get_global_basis(), material);
				chunks[chunk_coords] = new_chunk;				
			}
		}
	}
}


void VoxelFiniteWorld::update_chunk(const Vector3i chunk_coord) {
	UtilityFunctions::print("Updating chunk data for a chunk.");	
	Ref<ChunkManager> chunk_manager = chunks[chunk_coord];
	Ref<ChunkData> chunk_data = world_data->get_chunk(chunk_coord);
  chunk_manager->update_mesh(chunk_data);	
}


void VoxelFiniteWorld::update_all_chunks() {	
	for (int x = 0; x < WORLD_SIZE.x; x++) {
		for (int y = 0; y < WORLD_SIZE.y; y++) {
			for (int z = 0; z < WORLD_SIZE.z; z++) {
				update_chunk(Vector3i(x, y, z));				
			}
		}
	}
}

} // Namespace voxxel
