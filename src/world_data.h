#ifndef WORLD_DATA_H
#define WORLD_DATA_H

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/templates/hash_map.hpp"
#include "chunk_node.h"
#include "chunk_data.h"

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
private:
    HashMap<Vector3i, Ref<ChunkData>> chunks;    
};

} // namespace voxxel

#endif // WORLD_DATA_H