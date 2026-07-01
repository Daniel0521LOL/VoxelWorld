#include "chunk_manager.h"
#include "chunk_constants.h"
#include "chunk_mesher.h"
#include "godot_cpp/classes/rendering_server.hpp"
#include "godot_cpp/variant/basis.hpp"
#include "godot_cpp/variant/transform3d.hpp"
#include "godot_cpp/variant/vector3.hpp"
using namespace godot;

namespace voxxel {

ChunkManager::~ChunkManager() {
  if (instance.is_valid()) {
    godot::RenderingServer::get_singleton()->free_rid(instance);
  }
}

void ChunkManager::initialize(Ref<ChunkMesher>& p_chunk_mesher, RID p_scenario, Vector3i p_offset, Basis p_basis, Ref<ShaderMaterial> p_shader_material) {
	chunk_mesher = p_chunk_mesher;	
	scenario = p_scenario;
	offset = p_offset;
	basis = p_basis;
	material = p_shader_material;	
	instance = RenderingServer::get_singleton()->instance_create();
}

void ChunkManager::update_mesh(Ref<ChunkData> &p_chunk_data) {
	mesh = chunk_mesher->mesh_chunk(p_chunk_data);
	RenderingServer::get_singleton()->instance_set_scenario(instance, scenario);
	RenderingServer::get_singleton()->instance_set_base(instance, mesh->get_rid());
	Transform3D xform(basis, Vector3(offset * CHUNK_SIZE * BLOCK_SIZE));
	RenderingServer::get_singleton()->instance_set_transform(instance, xform);
	RenderingServer::get_singleton()->instance_set_surface_override_material(instance, 0, material->get_rid());	
}

void ChunkManager::_bind_methods() {}

}
