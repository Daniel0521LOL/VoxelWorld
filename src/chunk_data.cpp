#include "chunk_data.h"

using namespace godot;

namespace voxxel {

ChunkData::ChunkData() {
	// Initialize chunk data with 16x16x16 = 4096 bytes (all air blocks)
	for (int i = 0; i < 16 * 16 * 16; i++) {
		data.push_back(0);
	}
}

void ChunkData::_bind_methods() {
	// Bind methods and properties here
	ClassDB::bind_method(D_METHOD("get_block", "pos"), &ChunkData::get_block);
	ClassDB::bind_method(D_METHOD("set_block", "pos", "block_id"), &ChunkData::set_block);
}

} // namespace voxxel
