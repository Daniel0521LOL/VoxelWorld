#include "chunk_manager.h"
#include "chunk_constants.h"
#include "chunk_mesher.h"
#include "godot_cpp/classes/rendering_server.hpp"
#include "godot_cpp/variant/basis.hpp"
#include "godot_cpp/variant/transform3d.hpp"
using namespace godot;

namespace voxxel {

ChunkManager::ChunkManager(Ref<ChunkMesher>& p_chunk_mesher, RID p_scenario, Vector3i p_offset) {
	chunk_mesher = p_chunk_mesher;	
	scenario = p_scenario;
	offset = p_offset;	
}

void ChunkManager::update_mesh(Ref<ChunkData> &p_chunk_data) {
	Ref<Mesh> mesh = chunk_mesher->mesh_chunk(p_chunk_data);
	instance = RenderingServer::get_singleton()->instance_create();
	RenderingServer::get_singleton()->instance_set_scenario(instance, scenario);
	RenderingServer::get_singleton()->instance_set_base(instance, mesh->get_rid());
	Transform3D xform(Basis, offset * CHUNK_SIZE);
	RenderingServer::get_singleton()->instance_set_transform(instance, xform);
}

}
