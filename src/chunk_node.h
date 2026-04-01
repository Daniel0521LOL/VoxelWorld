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
    ~VoxelChunk() override;

    void set_chunk_data(const Ref<ChunkData> &p_chunk_data);
    Ref<ChunkData> get_chunk_data() const;

private:
    Ref<ChunkData> chunk_data;
    ChunkMesher* mesher = memnew(GreedyChunkMesher);
};

} // namespace voxxel