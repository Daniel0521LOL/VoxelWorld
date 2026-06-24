#include "basic_chunk_mesher.h"

namespace voxxel {

void BasicChunkMesher::_bind_methods() {}

Ref<Mesh> BasicChunkMesher::mesh_chunk(const Ref<ChunkData> &p_data) {
	if (p_data.is_null()) {
		return Ref<Mesh>();
	}

	LocalVector<LocalVector<Vector3>> vertices;
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				add_block(x, y, z, p_data, vertices);
			}
		}
	}

	Ref<SurfaceTool> surface_tool;
	surface_tool.instantiate();
	surface_tool->begin(Mesh::PRIMITIVE_TRIANGLES);

	int uv_index = 0;
	for (const LocalVector<Vector3> &triangle_vertices : vertices) {
		for (const Vector3 &vertex : triangle_vertices) {
			surface_tool->set_uv(FACE_UV[uv_index % FACE_UV.size()]);
			surface_tool->add_vertex(vertex);
			uv_index++;
		}
	}
	surface_tool->generate_normals();
	surface_tool->generate_tangents();
	return surface_tool->commit();
}

Vector<int> BasicChunkMesher::get_visible_faces(const Ref<ChunkData> &p_data, int x, int y, int z) const {
	Vector<int> visible_faces;

	if (p_data.is_null()) {
		return visible_faces;
	}

	for (int i = 0; i < 6; i++) {
		switch (i) {
			case 0: // Bottom
				if (y == 0 || p_data->get_block(Vector3i(x, y - 1, z)) == 0) {
					visible_faces.push_back(i);
				}
				break;
			case 1: // Top
				if (y == CHUNK_SIZE - 1 || p_data->get_block(Vector3i(x, y + 1, z)) == 0) {
					visible_faces.push_back(i);
				}
				break;
			case 2: // Front
				if (z == 0 || p_data->get_block(Vector3i(x, y, z - 1)) == 0) {
					visible_faces.push_back(i);
				}
				break;
			case 3: // Back
				if (z == CHUNK_SIZE - 1 || p_data->get_block(Vector3i(x, y, z + 1)) == 0) {
					visible_faces.push_back(i);
				}
				break;
			case 4: // Right
				if (x == CHUNK_SIZE - 1 || p_data->get_block(Vector3i(x + 1, y, z)) == 0) {
					visible_faces.push_back(i);
				}
				break;
			case 5: // Left
				if (x == 0 || p_data->get_block(Vector3i(x - 1, y, z)) == 0) {
					visible_faces.push_back(i);
				}
				break;
			default:
				break;
		}
	}
	return visible_faces;
}

void BasicChunkMesher::add_face(int x, int y, int z, int face_index, LocalVector<LocalVector<Vector3>> &vertices) {
	LocalVector<Vector3> triangle_vertices;
	for (int vertex_index : TRIANGLES[face_index * 2]) {
		Vector3 vertex = CUBE_VERTICES[vertex_index] + Vector3(x, y, z) * BLOCK_SIZE;
		triangle_vertices.push_back(vertex);
	}
	vertices.push_back(triangle_vertices);
	triangle_vertices.clear();
	for (int vertex_index : TRIANGLES[face_index * 2 + 1]) {
		Vector3 vertex = CUBE_VERTICES[vertex_index] + Vector3(x, y, z) * BLOCK_SIZE;
		triangle_vertices.push_back(vertex);
	}
	vertices.push_back(triangle_vertices);
}

void BasicChunkMesher::add_block(int x, int y, int z, const Ref<ChunkData> &p_data, LocalVector<LocalVector<Vector3>> &vertices) {
	if (p_data->get_block(Vector3i(x, y, z)) == 0) {
		return; // Skip air blocks
	}

	Vector<int> visible_faces = get_visible_faces(p_data, x, y, z);
	for (int face_index : visible_faces) {
		add_face(x, y, z, face_index, vertices);
	}
}

} // namespace voxxel