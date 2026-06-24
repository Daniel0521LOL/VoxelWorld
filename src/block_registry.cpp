#include "block_registry.h"

using namespace godot;

namespace voxxel {

void BlockRegistry::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_texture_array"), &BlockRegistry::get_texture_array);
	ClassDB::bind_method(D_METHOD("juice_registry"), &BlockRegistry::juice_registry);
	ClassDB::bind_method(D_METHOD("set_block_definitions", "definitions"), &BlockRegistry::set_block_definitions);
	ClassDB::bind_method(D_METHOD("get_block_definitions"), &BlockRegistry::get_block_definitions);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "block_definitions", PROPERTY_HINT_RESOURCE_TYPE, "BlockDefinition", PROPERTY_USAGE_DEFAULT), "set_block_definitions", "get_block_definitions");
}

void BlockRegistry::juice_registry() {
	TypedArray<Image> texture_array = Array();
	Vector<Ref<Texture2D>> unique_textures;

	for (int i = 0; i < block_definitions.size(); ++i) {
		Ref<BlockDefinition> def = block_definitions[i];
		if (def.is_valid()) {
			BlockInfo info;
			info.name = def->get_name();

			Vector<Ref<Texture2D>> textures = def->get_textures();

			if (def->get_texture_mode() == BlockDefinition::SINGLE) {
				// If SINGLE mode, ensure all faces use the same texture ID
				if (unique_textures.find(textures[0]) == -1) {
					unique_textures.push_back(textures[0]);
					texture_array.push_back(textures[0]->get_image());
				}
				int id = unique_textures.find(textures[0]);
				for (int j = 0; j < 6; ++j) {
					info.texture_ids[j] = id;
				}
			} else {
				for (int j = 0; j < 6; ++j) {
					if (unique_textures.find(textures[j]) == -1) {
						unique_textures.push_back(textures[j]);
						texture_array.push_back(textures[j]->get_image());
					}
					info.texture_ids[j] = unique_textures.find(textures[j]);
				}
			}

			if (blocks.size() <= def->get_id()) {
				blocks.resize(def->get_id() + 1);
			}

			blocks.set(def->get_id(), info);
		}
	}

	print_line("Juicing registry with " + itos(texture_array.size()) + " unique textures.");
	for (int i = 0; i < blocks.size(); ++i) {
		if (i < blocks.size()) {
			print_line("Block ID " + itos(i) + ": " + blocks[i].name + " with texture ID " + itos(blocks[i].texture_ids[0]));
		}
	}

	if (textures.is_null()) {
		textures.instantiate();
	}
	textures->create_from_images(texture_array);
}

int BlockRegistry::get_face_texture_id(uint8_t block_id, int face_index) const {
	if (block_id >= blocks.size() || face_index < 0 || face_index >= 6) {
		return -1; // Invalid block ID or face index
	}
	return blocks[block_id].texture_ids[face_index];
}

Ref<Texture2DArray> BlockRegistry::get_texture_array() const {
	return textures;
}

void BlockRegistry::set_block_definitions(const Array &p_definitions) {
	block_definitions = p_definitions;
}

Array BlockRegistry::get_block_definitions() const {
	return block_definitions;
}

} // namespace voxxel