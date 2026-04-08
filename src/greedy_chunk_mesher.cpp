#include "greedy_chunk_mesher.h"

using namespace godot;

namespace voxxel {

void GreedyChunkMesher::_bind_methods() {}

void GreedyChunkMesher::set_block_registry(const Ref<BlockRegistry> &p_registry) {
    block_registry = p_registry;
}

bool GreedyChunkMesher::is_face_visible(const Ref<ChunkData> &p_data, Vector3i block_pos, Vector3i face_dir) {
    if (p_data->get_block(block_pos) == 0) {
        return false; // No face if the block itself is air
    }
    Vector3i neighbor_pos = block_pos + face_dir;
    uint8_t block_id = p_data->get_block(neighbor_pos);
    return block_id == 0; // Face is visible if the neighboring block is air (block_id 0)
}

GreedyChunkMesher::SliceData GreedyChunkMesher::get_slice(const Ref<ChunkData> &p_data, int slice_offset, Vector3i face_dir) {
    SliceData slice_data(face_dir, slice_offset);
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            Vector3i block_pos;
            if (face_dir == Directions::UP || face_dir == Directions::DOWN) {
                block_pos = Vector3i(x, slice_offset, y);
            } else if (face_dir == Directions::FRONT || face_dir == Directions::BACK) {
                block_pos = Vector3i(x, y, slice_offset);
            } else {
                block_pos = Vector3i(slice_offset, x, y);
            }
            uint8_t block_id = p_data->get_block(block_pos);
            slice_data.set_block(x, y, block_id);
            slice_data.set_included(x, y, is_face_visible(p_data, block_pos, face_dir));
        }
    }
    return slice_data;
}

Vector2i GreedyChunkMesher::greedy_mesh_starting_from(SliceData &slice_data, int start_x, int start_y) {
    int x = start_x;
    int y = start_y;
    uint8_t block_id = slice_data.get_block(x, y);
    
    if (block_id == 0 || !slice_data.is_included(x, y)) {
        return NO_FACE;
    }

    while (x < CHUNK_SIZE && slice_data.get_block(x, y) == block_id && slice_data.is_included(x, y)) {
        x++;
    }
    while (y < CHUNK_SIZE) {
        bool row_match = true;
        for (int i = start_x; i < x; i++) {
            if (slice_data.get_block(i, y) != block_id || !slice_data.is_included(i, y)) {
                row_match = false;
                break;
            }
        }
        if (!row_match) {
            break;
        }
        y++;
    }
    return Vector2i(x, y);
}

void GreedyChunkMesher::mesh_slice(SliceData &slice_data, Ref<SurfaceTool> &surface_tool) {
    float offset_coord;
    if (slice_data.face_dir.abs() == slice_data.face_dir) {
        offset_coord = (slice_data.slice_offset + 1) * BLOCK_SIZE;
    } else {
        offset_coord = (slice_data.slice_offset) * BLOCK_SIZE;
    }

    for (int y = 0; y < CHUNK_SIZE; y++) {
        for (int x = 0; x < CHUNK_SIZE; x++) {
            if (slice_data.is_included(x, y)) {
                Vector2i end = greedy_mesh_starting_from(slice_data, x, y);

                if (end == NO_FACE) {
                    continue; // No face to mesh
                }

                for (int mark_y = y; mark_y < end.y; mark_y++) {
                    for (int mark_x = x; mark_x < end.x; mark_x++) {
                        slice_data.set_included(mark_x, mark_y, false);
                    }
                }

                float x1 = x * BLOCK_SIZE;
                float y1 = y * BLOCK_SIZE;
                float x2 = end.x * BLOCK_SIZE;
                float y2 = end.y * BLOCK_SIZE;
                
                Vector3 v1, v2, v3, v4;
                if (slice_data.face_dir == Directions::UP) {
                    v1 = Vector3(x1, offset_coord, y1);
                    v2 = Vector3(x2, offset_coord, y1);
                    v3 = Vector3(x2, offset_coord, y2);
                    v4 = Vector3(x1, offset_coord, y2);
                } else if (slice_data.face_dir == Directions::DOWN) {
                    v1 = Vector3(x1, offset_coord, y1);
                    v2 = Vector3(x1, offset_coord, y2);
                    v3 = Vector3(x2, offset_coord, y2);
                    v4 = Vector3(x2, offset_coord, y1);
                } else if (slice_data.face_dir == Directions::FRONT) {
                    // Swapped v2 and v4 assignments for CW winding
                    v1 = Vector3(x1, y1, offset_coord);
                    v2 = Vector3(x1, y2, offset_coord);
                    v3 = Vector3(x2, y2, offset_coord);
                    v4 = Vector3(x2, y1, offset_coord);
                } else if (slice_data.face_dir == Directions::BACK) {
                    v1 = Vector3(x1, y1, offset_coord);
                    v2 = Vector3(x2, y1, offset_coord);
                    v3 = Vector3(x2, y2, offset_coord);
                    v4 = Vector3(x1, y2, offset_coord);
                } else if (slice_data.face_dir == Directions::RIGHT) {
                    v1 = Vector3(offset_coord, x1, y1);
                    v2 = Vector3(offset_coord, x1, y2);
                    v3 = Vector3(offset_coord, x2, y2);
                    v4 = Vector3(offset_coord, x2, y1);
                } else { // LEFT
                    v1 = Vector3(offset_coord, x1, y1);
                    v2 = Vector3(offset_coord, x2, y1);
                    v3 = Vector3(offset_coord, x2, y2);
                    v4 = Vector3(offset_coord, x1, y2);
                }

                uint8_t block_id = slice_data.get_block(x, y);
                uint16_t texture_id = block_registry->get_face_texture_id(block_id, 0); // TEMPORARY: using top texture for all faces, need to implement per-face texture IDs in block registry and slice data
                // Use R channel of vertex color to store texture ID
                Color vertex_color = Color(texture_id / 255.0f, 1.0f, 1.0f, 1.0f);

                float w = end.x - x;
                float h = end.y - y;
                
                surface_tool->set_color(vertex_color);
                surface_tool->set_normal(slice_data.face_dir);
                surface_tool->set_uv(Vector2(0, 0));
                surface_tool->add_vertex(v1);
                surface_tool->set_color(vertex_color);
                surface_tool->set_normal(slice_data.face_dir);
                surface_tool->set_uv(Vector2(w, 0));
                surface_tool->add_vertex(v2);
                surface_tool->set_color(vertex_color);
                surface_tool->set_normal(slice_data.face_dir);
                surface_tool->set_uv(Vector2(w, h));
                surface_tool->add_vertex(v3);
                
                surface_tool->set_color(vertex_color);
                surface_tool->set_normal(slice_data.face_dir);
                surface_tool->set_uv(Vector2(0, 0));
                surface_tool->add_vertex(v1);
                surface_tool->set_color(vertex_color);
                surface_tool->set_normal(slice_data.face_dir);
                surface_tool->set_uv(Vector2(w, h));
                surface_tool->add_vertex(v3);
                surface_tool->set_color(vertex_color);
                surface_tool->set_normal(slice_data.face_dir);
                surface_tool->set_uv(Vector2(0, h));
                surface_tool->add_vertex(v4);
            }
        }
    }
}

Ref<Mesh> GreedyChunkMesher::mesh_chunk(const Ref<ChunkData> &p_data) {
    Ref<SurfaceTool> surface_tool = memnew(SurfaceTool());
    surface_tool->begin(Mesh::PRIMITIVE_TRIANGLES);
    for (int i = 0; i < 6; i++) {
        for (int offset = 0; offset < CHUNK_SIZE; offset++) {
            SliceData slice_data = get_slice(p_data, offset, Directions::DIRECTIONS[i]);
            mesh_slice(slice_data, surface_tool);
        }
    }
    return surface_tool->commit();
}

} // namespace voxxel