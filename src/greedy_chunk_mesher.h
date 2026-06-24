#ifndef VOXXEL_GREEDY_CHUNK_MESHER_H
#define VOXXEL_GREEDY_CHUNK_MESHER_H

#include "block_registry.h"
#include "chunk_mesher.h"
#include "godot_cpp/classes/surface_tool.hpp"

using namespace godot;

namespace voxxel {

class GreedyChunkMesher : public ChunkMesher {
	GDCLASS(GreedyChunkMesher, ChunkMesher)

	public:
	GreedyChunkMesher() = default;
	~GreedyChunkMesher() override = default;
	Ref<Mesh> mesh_chunk(const Ref<ChunkData> &p_data) override;
	void set_block_registry(const Ref<BlockRegistry> &p_registry);

	protected:
	static void _bind_methods();

	private:
	Ref<BlockRegistry> block_registry;

	const Vector2i NO_FACE = Vector2i(-1, -1);

	struct SliceData {
		LocalVector<uint8_t> blocks;
		LocalVector<bool> included;
		Vector3i face_dir;
		int slice_offset;

		SliceData(Vector3i p_face_dir, int p_slice_offset) : face_dir(p_face_dir), slice_offset(p_slice_offset) {
			blocks.resize(CHUNK_SIZE * CHUNK_SIZE);
			included.resize(CHUNK_SIZE * CHUNK_SIZE);
		}

		uint8_t get_block(int x, int y) const {
			int index = x + (y * CHUNK_SIZE);
			if (index < 0 || index >= (int)blocks.size()) {
				return 0; // Return air block for out of bounds
			}
			return blocks[index];
		}

		void set_block(int x, int y, uint8_t block_id) {
			int index = x + (y * CHUNK_SIZE);
			if (index >= 0 && index < (int)blocks.size()) {
				blocks[index] = block_id;
			}
		}

		bool is_included(int x, int y) const {
			int index = x + (y * CHUNK_SIZE);
			if (index < 0 || index >= (int)included.size()) {
				return false; // Out of bounds
			}
			return included[index];
		}

		void set_included(int x, int y, bool value) {
			int index = x + (y * CHUNK_SIZE);
			if (index >= 0 && index < (int)included.size()) {
				included[index] = value;
			}
		}
	};

	bool is_face_visible(const Ref<ChunkData> &p_data, Vector3i block_pos, Vector3i face_dir);
	SliceData get_slice(const Ref<ChunkData> &p_data, int slice_offset, Vector3i face_dir);
	Vector2i greedy_mesh_starting_from(SliceData &slice_data, int start_x, int start_y);
	void mesh_slice(SliceData &slice_data, Ref<SurfaceTool> &surface_tool);
};

} // namespace voxxel

#endif // VOXXEL_GREEDY_CHUNK_MESHER_H