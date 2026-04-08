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

    for (int i = 0; i < block_definitions.size(); ++i) {
        Ref<BlockDefinition> def = block_definitions[i];
        if (def.is_valid()) {
            print_line("Processing block definition: " + def->get_name());
            Ref<Image> img = def->get_tex_top()->get_image();
            if (texture_array.find(def->get_tex_top()->get_image()) == -1) {
                texture_array.push_back(img);
                print_line("Texture array now has " + itos(texture_array.size()) + " unique textures.");
                print_line("Assigned texture ID " + itos(texture_array.find(img)) + " to block '" + def->get_name() + "'.");
            }
            int id = texture_array.find(img);
            BlockInfo info;
            info.name = def->get_name();
            for (int j = 0; j < 6; ++j) {
                info.texture_ids[j] = id;
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