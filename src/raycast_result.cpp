#include "raycast_result.h"

using namespace godot;

namespace voxxel {

void RaycastResult::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_hit", "hit"), &RaycastResult::set_hit);
	ClassDB::bind_method(D_METHOD("is_hit"), &RaycastResult::is_hit);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "hit"), "set_hit", "is_hit");

	ClassDB::bind_method(D_METHOD("set_chunk_pos", "chunk_pos"), &RaycastResult::set_chunk_pos);
	ClassDB::bind_method(D_METHOD("get_chunk_pos"), &RaycastResult::get_chunk_pos);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "chunk_pos"), "set_chunk_pos", "get_chunk_pos");

	ClassDB::bind_method(D_METHOD("set_block_pos", "block_pos"), &RaycastResult::set_block_pos);
	ClassDB::bind_method(D_METHOD("get_block_pos"), &RaycastResult::get_block_pos);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "block_pos"), "set_block_pos", "get_block_pos");

	ClassDB::bind_method(D_METHOD("set_face_normal", "face_normal"), &RaycastResult::set_face_normal);
	ClassDB::bind_method(D_METHOD("get_face_normal"), &RaycastResult::get_face_normal);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "face_normal"), "set_face_normal", "get_face_normal");
}

void RaycastResult::set_hit(bool p_hit) {
	hit = p_hit;
}

void RaycastResult::set_chunk_pos(const Vector3i &p_chunk_pos) {
	chunk_pos = p_chunk_pos;
}

void RaycastResult::set_block_pos(const Vector3i &p_block_pos) {
	block_pos = p_block_pos;
}

void RaycastResult::set_face_normal(const Vector3i &p_face_normal) {
	face_normal = p_face_normal;
}

bool RaycastResult::is_hit() {
	return hit;
}

Vector3i RaycastResult::get_chunk_pos() const {
	return chunk_pos;
}

Vector3i RaycastResult::get_block_pos() const {
	return block_pos;
}

Vector3i RaycastResult::get_face_normal() const {
	return face_normal;
}

} // namespace voxxel