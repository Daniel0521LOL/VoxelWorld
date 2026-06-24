#ifndef VOXXEL_BLOCK_DEFINITION_H
#define VOXXEL_BLOCK_DEFINITION_H

#include "godot_cpp/classes/resource.hpp"
#include "godot_cpp/classes/texture2d.hpp"
#include "godot_cpp/variant/typed_array.hpp"

using namespace godot;

namespace voxxel {

class BlockDefinition : public Resource {
	GDCLASS(BlockDefinition, Resource);

	public:
	enum TextureMode {
		SINGLE, // One texture for all sides
		SIX_WAY // Unique texture for every face
	};

	BlockDefinition() = default;
	~BlockDefinition() override = default;

	void set_id(uint8_t p_id) { id = p_id; };
	uint8_t get_id() const { return id; };

	void set_name(const String &p_name) { name = p_name; };
	String get_name() const { return name; };

	void set_tex_top(const Ref<Texture2D> p_tex) { tex_top = p_tex; };
	Ref<Texture2D> get_tex_top() const { return tex_top; };

	void set_tex_bottom(const Ref<Texture2D> p_tex) { tex_bottom = p_tex; };
	Ref<Texture2D> get_tex_bottom() const { return tex_bottom; };

	void set_tex_left(const Ref<Texture2D> p_tex) { tex_left = p_tex; };
	Ref<Texture2D> get_tex_left() const { return tex_left; };

	void set_tex_right(const Ref<Texture2D> p_tex) { tex_right = p_tex; };
	Ref<Texture2D> get_tex_right() const { return tex_right; };

	void set_tex_front(const Ref<Texture2D> p_tex) { tex_front = p_tex; };
	Ref<Texture2D> get_tex_front() const { return tex_front; };

	void set_tex_back(const Ref<Texture2D> p_tex) { tex_back = p_tex; };
	Ref<Texture2D> get_tex_back() const { return tex_back; };

	void set_texture_mode(int p_mode) { mode = static_cast<TextureMode>(p_mode); };
	int get_texture_mode() const { return mode; };

	Vector<Ref<Texture2D>> get_textures() const {
		Vector<Ref<Texture2D>> textures;
		switch (mode) {
			case SINGLE:
				textures.push_back(tex_top);
				break;
			case SIX_WAY:
				textures.push_back(tex_top);
				textures.push_back(tex_bottom);
				textures.push_back(tex_left);
				textures.push_back(tex_right);
				textures.push_back(tex_front);
				textures.push_back(tex_back);
				break;
		}
		return textures;
	};

	protected:
	static void _bind_methods();

	private:
	uint8_t id;
	String name;
	TextureMode mode = SINGLE;

	// Texture slots
	Ref<Texture2D> tex_top;
	Ref<Texture2D> tex_bottom;
	Ref<Texture2D> tex_left;
	Ref<Texture2D> tex_right;
	Ref<Texture2D> tex_front;
	Ref<Texture2D> tex_back;
};

} // namespace voxxel

#endif // VOXXEL_BLOCK_DEFINITION_H