#ifndef RAYCAST_RESULT_H
#define RAYCAST_RESULT_H

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/variant/vector3i.hpp"

using namespace godot;

namespace voxxel {

class RaycastResult : public RefCounted {
    GDCLASS(RaycastResult, RefCounted)

public:
    RaycastResult() = default;
    ~RaycastResult() override = default;

    void set_hit(bool p_hit);
    void set_chunk_pos(const Vector3i &p_chunk_pos);
    void set_block_pos(const Vector3i &p_block_pos);
    void set_face_normal(const Vector3i &p_face_normal);
    bool is_hit();
    Vector3i get_chunk_pos() const;
    Vector3i get_block_pos() const;
    Vector3i get_face_normal() const;

protected:
    static void _bind_methods();

private:
    bool hit;
    Vector3i chunk_pos;
    Vector3i block_pos;
    Vector3i face_normal;
};

} // namespace voxxel


#endif // RAYCAST_RESULT_H