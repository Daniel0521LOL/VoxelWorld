#include "chunk_node.h"

using namespace godot;

namespace voxxel {

void VoxelChunk::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_chunk_data", "chunk_data"), &VoxelChunk::set_chunk_data);
    ClassDB::bind_method(D_METHOD("get_chunk_data"), &VoxelChunk::get_chunk_data);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "chunk_data", PROPERTY_HINT_RESOURCE_TYPE, "ChunkData"), "set_chunk_data", "get_chunk_data");
}

void VoxelChunk::update_mesh() {
    if (chunk_data.is_valid() && mesher.is_valid()) {
        Ref<Mesh> mesh = mesher->mesh_chunk(chunk_data);
        set_mesh(mesh);
    } else {
        set_mesh(nullptr);
    }
}

void VoxelChunk::set_mesher(const Ref<ChunkMesher> &p_mesher) {
    mesher = p_mesher;
    update_mesh();
}

void VoxelChunk::set_chunk_data(const Ref<ChunkData> &p_chunk_data) {
    chunk_data = p_chunk_data;
    update_mesh();
}

Ref<ChunkData> VoxelChunk::get_chunk_data() const {
    return chunk_data;
}

} // namespace voxxel