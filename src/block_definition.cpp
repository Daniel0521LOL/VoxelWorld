#include "block_definition.h"

using namespace godot;

namespace voxxel {

void BlockDefinition::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_id", "id"), &BlockDefinition::set_id);
    ClassDB::bind_method(D_METHOD("get_id"), &BlockDefinition::get_id);
    ClassDB::bind_method(D_METHOD("set_name", "name"), &BlockDefinition::set_name);
    ClassDB::bind_method(D_METHOD("get_name"), &BlockDefinition::get_name);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");

    // Texture Bindings
    ADD_GROUP("Textures", "tex_");
    
    // We bind all, but you can use _get_property_list to hide them dynamically if desired
    ClassDB::bind_method(D_METHOD("get_tex_top"), &BlockDefinition::get_tex_top);
    ClassDB::bind_method(D_METHOD("set_tex_top", "tex"), &BlockDefinition::set_tex_top);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_top", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_tex_top", "get_tex_top");

    ClassDB::bind_method(D_METHOD("get_tex_bottom"), &BlockDefinition::get_tex_bottom);
    ClassDB::bind_method(D_METHOD("set_tex_bottom", "tex"), &BlockDefinition::set_tex_bottom);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_bottom", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_tex_bottom", "get_tex_bottom");

    ClassDB::bind_method(D_METHOD("get_tex_left"), &BlockDefinition::get_tex_left);
    ClassDB::bind_method(D_METHOD("set_tex_left", "tex"), &BlockDefinition::set_tex_left);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_left", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_tex_left", "get_tex_left");

    ClassDB::bind_method(D_METHOD("get_tex_right"), &BlockDefinition::get_tex_right);
    ClassDB::bind_method(D_METHOD("set_tex_right", "tex"), &BlockDefinition::set_tex_right);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_right", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_tex_right", "get_tex_right");

    ClassDB::bind_method(D_METHOD("get_tex_front"), &BlockDefinition::get_tex_front);
    ClassDB::bind_method(D_METHOD("set_tex_front", "tex"), &BlockDefinition::set_tex_front);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_front", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_tex_front", "get_tex_front");

    ClassDB::bind_method(D_METHOD("get_tex_back"), &BlockDefinition::get_tex_back);
    ClassDB::bind_method(D_METHOD("set_tex_back", "tex"), &BlockDefinition::set_tex_back);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tex_back", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_tex_back", "get_tex_back");
}

} // namespace voxxel