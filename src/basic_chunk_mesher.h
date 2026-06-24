#ifndef VOXXEL_BASIC_CHUNK_MESHER_H
#define VOXXEL_BASIC_CHUNK_MESHER_H

#include "chunk_mesher.h"
#include "godot_cpp/classes/surface_tool.hpp"

using namespace godot;

namespace voxxel {

class BasicChunkMesher : public ChunkMesher {
	GDCLASS(BasicChunkMesher, ChunkMesher)

	public:
	BasicChunkMesher() = default;
	~BasicChunkMesher() override = default;

	Ref<Mesh> mesh_chunk(const Ref<ChunkData> &p_data) override;

	protected:
	static void _bind_methods();

	private:
	constexpr static int CHUNK_SIZE = 16;
	constexpr static int BLOCK_SIZE = 1;
	const LocalVector<Vector3> CUBE_VERTICES = {
		Vector3(0, 0, 0),
		Vector3(1, 0, 0),
		Vector3(1, 0, 1),
		Vector3(0, 0, 1),
		Vector3(0, 1, 0),
		Vector3(1, 1, 0),
		Vector3(1, 1, 1),
		Vector3(0, 1, 1)
	};
	const LocalVector<LocalVector<int>> TRIANGLES = {
		{ 0, 2, 1 },
		{ 0, 3, 2 }, // Bottom face
		{ 4, 5, 6 },
		{ 4, 6, 7 }, // Top face
		{ 0, 5, 4 },
		{ 0, 1, 5 }, // Front face
		{ 2, 7, 6 },
		{ 2, 3, 7 }, // Back face
		{ 1, 6, 5 },
		{ 1, 2, 6 }, // Right face
		{ 3, 4, 7 },
		{ 3, 0, 4 } // Left face
	};
	const LocalVector<Vector2> FACE_UV = {
		Vector2(1, 1),
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1),
		Vector2(0, 0)
	};

	Vector<int> get_visible_faces(const Ref<ChunkData> &p_data, int x, int y, int z) const;
	void add_face(int x, int y, int z, int face_index, LocalVector<LocalVector<Vector3>> &vertices);
	void add_block(int x, int y, int z, const Ref<ChunkData> &p_data, LocalVector<LocalVector<Vector3>> &vertices);
};

} // namespace voxxel

#endif // VOXXEL_BASIC_CHUNK_MESHER_H