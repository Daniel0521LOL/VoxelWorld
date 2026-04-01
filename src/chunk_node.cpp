#include "chunk_node.h"

using namespace godot;

namespace voxxel {

VoxelChunk::~VoxelChunk() {
    memdelete(mesher);
}

void VoxelChunk::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_chunk_data", "chunk_data"), &VoxelChunk::set_chunk_data);
    ClassDB::bind_method(D_METHOD("get_chunk_data"), &VoxelChunk::get_chunk_data);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "chunk_data", PROPERTY_HINT_RESOURCE_TYPE, "ChunkData"), "set_chunk_data", "get_chunk_data");
}

void VoxelChunk::set_chunk_data(const Ref<ChunkData> &p_chunk_data) {
    chunk_data = p_chunk_data;
    if (chunk_data.is_valid()) {
        Ref<Mesh> mesh = mesher->mesh_chunk(chunk_data);
        set_mesh(mesh);
    } else {
        set_mesh(nullptr);
    }
}

Ref<ChunkData> VoxelChunk::get_chunk_data() const {
    return chunk_data;
}

} // namespace voxxel