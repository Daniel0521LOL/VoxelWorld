#include "world_data.h"

using namespace godot;

namespace voxxel {

void WorldData::_bind_methods() {
}

Ref<ChunkData> WorldData::get_chunk(const Vector3i &p_chunk_pos) {
    if (chunks.has(p_chunk_pos)) {
        return chunks[p_chunk_pos];
    }
    return Ref<ChunkData>();
}

Ref<ChunkData> WorldData::initialize_chunk(const Vector3i &p_chunk_pos) {
    if (!chunks.has(p_chunk_pos)) {
        Ref<ChunkData> new_chunk;
        new_chunk.instantiate();
        chunks[p_chunk_pos] = new_chunk;
        return new_chunk;
    }
    return chunks[p_chunk_pos];
}

}