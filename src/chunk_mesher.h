#ifndef CHUNK_MESHER_H
#define CHUNK_MESHER_H

#include "chunk_constants.h"
#include "chunk_data.h"
#include "godot_cpp/classes/mesh.hpp"
#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/core/math.hpp"

using namespace godot;

namespace voxxel {

class ChunkMesher : public RefCounted {
	GDCLASS(ChunkMesher, RefCounted)

	protected:
	static void _bind_methods() {}

	public:
	ChunkMesher() = default;
	virtual ~ChunkMesher() = default;

	virtual Ref<Mesh> mesh_chunk(const Ref<ChunkData> &p_data) = 0;
};

} // namespace voxxel

#endif // CHUNK_MESHER_H