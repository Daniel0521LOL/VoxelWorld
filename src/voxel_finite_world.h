#ifndef VOXEL_FINITE_WORLD_H
#define VOXEL_FINITE_WORLD_H

#include "godot_cpp/classes/fast_noise_lite.hpp"
#include "godot_cpp/classes/material.hpp"
#include "chunk_node.h"
#include "chunk_mesher.h"
#include "chunk_data.h"
#include "world_data.h"
#include "block_registry.h"

using namespace godot;

namespace voxxel {

class VoxelFiniteWorld : public Node3D {
    GDCLASS(VoxelFiniteWorld, Node3D)

public:
    VoxelFiniteWorld() = default;
    ~VoxelFiniteWorld() override = default;

    void set_material(Ref<Material> p_material);
    Ref<Material> get_material() const;

    void generate_world(Ref<BlockRegistry> p_block_registry);

    Ref<WorldData> get_world_data() const {
        return world_data;
    } // TEMPORARY, need encapsulation later

protected:
    static void _bind_methods();

private:
    const Vector3i WORLD_SIZE = Vector3i(8, 4, 8);

    Ref<WorldData> world_data;
    HashMap<Vector3i, VoxelChunk *> chunks = HashMap<Vector3i, VoxelChunk *>();
    Ref<Material> material;
    Ref<ChunkMesher> mesher;
    Ref<FastNoiseLite> noise;

    void update_material();
};

} // namespace voxxel

#endif // VOXEL_FINITE_WORLD_H