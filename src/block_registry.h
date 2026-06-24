#ifndef VOXXEL_BLOCK_REGISTRY_H
#define VOXXEL_BLOCK_REGISTRY_H

#include "block_definition.h"
#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/classes/texture2d.hpp"
#include "godot_cpp/classes/texture2d_array.hpp"
#include "godot_cpp/variant/array.hpp"

using namespace godot;

namespace voxxel {

class BlockRegistry : public Resource {
	GDCLASS(BlockRegistry, Resource);

	public:
	BlockRegistry() = default;
	~BlockRegistry() override = default;
	void juice_registry();
	void set_block_definitions(const Array &p_definitions);
	Array get_block_definitions() const;
	int get_face_texture_id(uint8_t block_id, int face_index) const;
	Ref<Texture2DArray> get_texture_array() const;

	protected:
	static void _bind_methods();

	private:
	struct BlockInfo {
		String name;
		int texture_ids[6];
	};

	Array block_definitions = Array();
	Vector<BlockInfo> blocks;
	Ref<Texture2DArray> textures;
};

} // namespace voxxel

#endif // VOXXEL_BLOCK_REGISTRY_H