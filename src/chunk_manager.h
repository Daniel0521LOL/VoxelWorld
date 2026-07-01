#pragma once

#include "chunk_data.h"
#include "chunk_mesher.h"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/shader_material.hpp"
#include "godot_cpp/variant/basis.hpp"
#include "godot_cpp/variant/rid.hpp"
#include "godot_cpp/variant/vector3i.hpp"
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/rendering_server.hpp>

using namespace godot;

namespace voxxel {

class ChunkManager : public RefCounted {
	GDCLASS(ChunkManager, RefCounted)

	public:
			ChunkManager() = default;
			~ChunkManager();
			
			void initialize(Ref<ChunkMesher>& p_chunk_mesher, RID p_scenario, Vector3i p_offset, Basis p_basis, Ref<ShaderMaterial> p_shader_material);			
			void update_mesh(Ref<ChunkData> &p_chunk_data);
			
	protected:
	static void _bind_methods();

	private:
			Vector3i offset;			
			Ref<ChunkMesher> chunk_mesher;
			Ref<ShaderMaterial> material;			
			Ref<Mesh> mesh;
			RID instance;
			RID scenario;
			Basis basis;			
};

}
