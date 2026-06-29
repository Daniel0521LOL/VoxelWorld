#include "chunk_data.h"
#include "chunk_mesher.h"
#include "godot_cpp/classes/ref.hpp"
#include "godot_cpp/variant/rid.hpp"
#include "godot_cpp/variant/vector3i.hpp"
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/rendering_server.hpp>

using namespace godot;

namespace voxxel {

class ChunkManager {
	public:
			ChunkManager(Ref<ChunkMesher>& p_chunk_mesher, RID p_scenario, Vector3i p_offset);			
			void update_mesh(Ref<ChunkData> &p_chunk_data);
			
	private:
			Vector3i offset;			
			Ref<ChunkMesher> chunk_mesher;			
			Ref<Mesh> mesh;
			RID instance;
			RID scenario;			
};

}
