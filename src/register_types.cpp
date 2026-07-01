#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "basic_chunk_mesher.h"
#include "block_definition.h"
#include "block_registry.h"
#include "chunk_data.h"
#include "chunk_mesher.h"
#include "chunk_manager.h"
#include "greedy_chunk_mesher.h"
#include "voxel_finite_world.h"
#include "world_data.h"

using namespace godot;

void initialize_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	GDREGISTER_CLASS(voxxel::ChunkData);
	GDREGISTER_CLASS(voxxel::ChunkManager);	
	GDREGISTER_ABSTRACT_CLASS(voxxel::ChunkMesher);
	GDREGISTER_CLASS(voxxel::BasicChunkMesher);
	GDREGISTER_CLASS(voxxel::GreedyChunkMesher);
	GDREGISTER_CLASS(voxxel::WorldData);
	GDREGISTER_CLASS(voxxel::VoxelFiniteWorld);
	GDREGISTER_CLASS(voxxel::BlockDefinition);
	GDREGISTER_CLASS(voxxel::BlockRegistry);
	GDREGISTER_INTERNAL_CLASS(voxxel::RaycastResult);
}

void uninitialize_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
// Initialization
GDExtensionBool GDE_EXPORT voxel_world_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
	init_obj.register_initializer(initialize_gdextension_types);
	init_obj.register_terminator(uninitialize_gdextension_types);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
