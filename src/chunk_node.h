#ifndef VOXXEL_CHUNK_NODE_H
#define VOXXEL_CHUNK_NODE_H

#include "godot_cpp/classes/mesh_instance3d.hpp"
#include "chunk_data.h"
#include "chunk_mesher.h"
#include "basic_chunk_mesher.h"
#include "greedy_chunk_mesher.h"

using namespace godot;

namespace voxxel {

class VoxelChunk : public MeshInstance3D {
    GDCLASS(VoxelChunk, MeshInstance3D)

protected:
	static void _bind_methods();

public:
	VoxelChunk() = default;
    ~VoxelChunk() override = default;

    void set_chunk_data(const Ref<ChunkData> &p_chunk_data);
    void set_mesher(const Ref<ChunkMesher> &p_mesher);
    Ref<ChunkData> get_chunk_data() const;

private:
    void update_mesh();

    Ref<ChunkData> chunk_data;
    Ref<ChunkMesher> mesher;
};

} // namespace voxxel

#endif // VOXXEL_CHUNK_NODE_H