#include "voxel_finite_world.h"

using namespace godot;

namespace voxxel {

void VoxelFiniteWorld::_bind_methods() {
    ClassDB::bind_method(D_METHOD("generate_world"), &VoxelFiniteWorld::generate_world);
    ClassDB::bind_method(D_METHOD("set_material", "material"), &VoxelFiniteWorld::set_material);
    ClassDB::bind_method(D_METHOD("get_material"), &VoxelFiniteWorld::get_material);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "material", PROPERTY_HINT_RESOURCE_TYPE, "Material"), "set_material", "get_material");
}

void VoxelFiniteWorld::generate_world(Ref<BlockRegistry> p_block_registry) {
    world_data.instantiate();
    Ref<GreedyChunkMesher> greedy_mesher;
    greedy_mesher.instantiate();
    greedy_mesher->set_block_registry(p_block_registry);
    mesher = greedy_mesher;
    noise.instantiate();
    for (int x = 0; x < WORLD_SIZE.x; x++) {
        for (int y = 0; y < WORLD_SIZE.y; y++) {
            for (int z = 0; z < WORLD_SIZE.z; z++) {
                Vector3i chunk_pos(x, y, z);
                Ref<ChunkData> chunk_data = world_data->initialize_chunk(chunk_pos);
                // Simple noise-based terrain generation
                for (int bx = 0; bx < CHUNK_SIZE; bx++) {
                    for (int by = 0; by < CHUNK_SIZE; by++) {
                        for (int bz = 0; bz < CHUNK_SIZE; bz++) {
                            Vector3 world_pos = Vector3(
                                (chunk_pos.x * CHUNK_SIZE) + bx,
                                (chunk_pos.y * CHUNK_SIZE) + by,
                                (chunk_pos.z * CHUNK_SIZE) + bz
                            );
                            float height = noise->get_noise_3dv(world_pos / 10.0) * 10.0 + 20.0;
                            if (world_pos.y < height) {
                                if (world_pos.y < height - 5) {
                                    chunk_data->set_block(Vector3i(bx, by, bz), 1); // Set block ID to 1 for stone block
                                } else {
                                    chunk_data->set_block(Vector3i(bx, by, bz), 3); // Set block ID to 2 for solid block
                                }
                            }
                        }
                    }
                }

                VoxelChunk *chunk_node = memnew(VoxelChunk);
                chunk_node->set_mesher(mesher);
                chunk_node->set_chunk_data(chunk_data);
                chunk_node->set_position(Vector3(chunk_pos) * CHUNK_SIZE);
                chunks[chunk_pos] = chunk_node;
                add_child(chunk_node);
            }
        }
    }
    update_material();
}

void VoxelFiniteWorld::set_material(Ref<Material> p_material) {
    material = p_material;
    update_material();
}

void VoxelFiniteWorld::update_material() {
    for (const KeyValue<Vector3i, VoxelChunk *> &elem : chunks) {
        VoxelChunk *chunk = elem.value;
        chunk->set_mesh_material(material);
    }
}

Ref<Material> VoxelFiniteWorld::get_material() const {
    return material;
}

} // namespace voxxel