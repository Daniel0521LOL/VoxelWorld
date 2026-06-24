#include "chunk_node.h"
using namespace godot;

namespace voxxel {

void VoxelChunk::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_chunk_data", "chunk_data"), &VoxelChunk::set_chunk_data);
	ClassDB::bind_method(D_METHOD("get_chunk_data"), &VoxelChunk::get_chunk_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "chunk_data", PROPERTY_HINT_RESOURCE_TYPE, "ChunkData"), "set_chunk_data", "get_chunk_data");
}

void VoxelChunk::_ready() {
	mesh_instance = memnew(MeshInstance3D);
	add_child(mesh_instance);

	collision_shape = memnew(CollisionShape3D);
	add_child(collision_shape);

	update_mesh();
}

void VoxelChunk::update_mesh() {
	if (mesh_instance == nullptr || collision_shape == nullptr) {
		return;
	}

	if (chunk_data.is_valid() && mesher.is_valid()) {
		Ref<Mesh> mesh = mesher->mesh_chunk(chunk_data);
		if (mesh.is_null()) {
			mesh_instance->set_mesh(nullptr);
			collision_shape->set_shape(nullptr);
			return;
		}

		mesh_instance->set_mesh(mesh);
		Ref<Shape3D> shape = mesh->create_trimesh_shape();
		if (shape.is_null()) {
			collision_shape->set_shape(nullptr);
			return;
		}
		collision_shape->set_shape(shape);
	} else {
		mesh_instance->set_mesh(nullptr);
		collision_shape->set_shape(nullptr);
	}
}

void VoxelChunk::set_mesher(const Ref<ChunkMesher> &p_mesher) {
	mesher = p_mesher;
	update_mesh();
}

void VoxelChunk::set_chunk_data(const Ref<ChunkData> &p_chunk_data) {
	chunk_data = p_chunk_data;
	update_mesh();
}

void VoxelChunk::set_mesh_material(const Ref<Material> &p_material) {
	if (mesh_instance) {
		mesh_instance->set_material_override(p_material);
	}
}

Ref<ChunkData> VoxelChunk::get_chunk_data() const {
	return chunk_data;
}

} // namespace voxxel