//neon.graphics.h

#ifndef NEON_GRAPHICS_H_INCLUDED
#define NEON_GRAPHICS_H_INCLUDED

#include <neon_core.h>
#include <neon_opengl.h>
#pragma warning(push)
#pragma warning(disable: 4201)
#pragma warning(disable: 4127)
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#pragma warning(pop)


namespace neon
{
	struct vertex_buffer
	{
		vertex_buffer();

		bool create(const int size, const void* data);
		void update(const int size, const void* data);
		void destroy();

		bool is_valid() const;
		void bind() const;
		void render(GLenum primitive, int start, int count);


		GLuint id_;
	};

	struct index_buffer
	{
		index_buffer();

		// note: Type -> GL_UNSINGED_SHORT, GL_UNSIGNED_INT
		bool create(const int size, const GLenum type, const void* data);
		void destroy();

		bool is_valid() const;
		void bind() const;
		void render(GLenum primitive, int statart, int count);

		GLuint id_;
		GLuint type_;
	};

	struct shader_program
	{
		shader_program();

		bool create(const string& vertex_shader_filename,
					const string& fragment_shader_filename);
		void destroy();

		GLint get_attrib_location(const string& name) const;
		GLint get_uniform_location(const string& name) const;

		bool set_uniform_mat4(const string& name, const glm::mat4& value);
		bool set_uniform_vec4(const string& name, const glm::vec4& value);
		bool set_uniform_vec3(const string& name, const glm::vec3& value);


		bool is_valid() const;
		void bind() const;
		GLint id_;
	};

	constexpr uint32 ATTRIBUTE_COUNT = 4;

	struct vertex_format
	{
		struct attribute
		{
			attribute();

			int32 index_;
			GLenum type_;
			uint32 size_;
			bool normalised_;
			uint64 offset_;
		};
		vertex_format();

		void add_attribute(const int32 index, const uint32 size,
						   const GLenum type, const bool normalised);

		bool is_valid() const;
		void bind() const;

		uint32 stride_;
		uint32 attribute_count_;
		attribute attributes_[ATTRIBUTE_COUNT];
	};

	struct texture
	{
		texture();

		bool create(const string &filename);
		bool create_cubemap(int width, int height, const void** data);
		void destroy();

		bool is_valid() const;
		void bind() const;

		GLuint id_;
		GLenum type_;
	};

	struct sampler_state
	{
		sampler_state();

		bool create(const GLenum filter,
					const GLenum address_mode_u,
					const GLenum address_mode_v);
		void destroy();

		bool is_valid() const;
		void bind() const;

		GLuint id_;
	};

	struct bitmap_font
	{
		struct vertex
		{
			float x_, y_;
			float u_, v_;
		};

		bitmap_font();

		bool create();
		void destroy();

		void render(const float x, const float y, const string& text);
		void flush();

		shader_program program_;
		vertex_format format_;
		vertex_buffer buffer_;
		texture texture_;
		sampler_state sampler_;

		dynamic_array<vertex> vertices_;
		glm::mat4 projection_;

	};

	struct fps_camera
	{
		fps_camera();

		void update();

		void set_perspective(float fov, float aspect, float z_near, float x_far);
		void rotate_x(float amount);
		void rotate_y(float amount);
		void forward(float amount);
		void sidestep(float amount);

		float yaw_;
		float pitch_;
		float roll_;

		glm::vec3 x_axis_;
		glm::vec3 y_axis_;
		glm::vec3 z_axis_;
		glm::vec3 position_;

		glm::mat4 projection_;
		glm::mat4 view_;
	};

	struct fps_camera_controller
	{
		fps_camera_controller(fps_camera& camera, keyboard& kb, mouse& m);

		void update(const time &delta_Time);

		fps_camera& camera_;
		keyboard& keyboard_;
		mouse& mouse_;
		glm::vec2 mouse_Position_;
	};

	struct skybox
	{
		skybox();
		bool create();
		void destroy();

		void render(const fps_camera& camera);


		shader_program program_;
		vertex_buffer buffer_;
		vertex_format format_;
		texture cubemap_;
		sampler_state sampler_;
	};

	struct terrain
	{
		struct vertex
		{
			glm::vec3 position_;
			glm::vec2 texcoord_;
			glm::vec3 normal_;
		};
		terrain();

		bool create(const string &heightmap_filename, const string &texture_Filename);
		void destroy();

		void render();

		shader_program program_;
		vertex_buffer vertex_buffer_;
		vertex_format format_;
		index_buffer index_buffer_;
		texture texture_;
		sampler_state sampler_;
		int index_count_;

		fps_camera* camera_;
	};

	struct bounding_sphere 
	{
		bounding_sphere();
		explicit bounding_sphere(const glm::vec3& center, float radius);

		void set_center(const glm::vec3& center);
		void set_radius(const float radius);

		glm::vec3 center_;
		float radius_;
	};

	struct plane 
	{
		enum plane_type_id {
			PLANE_NEAR,
			PLANE_FAR,
			PLANE_LEFT,
			PLANE_RIGHT,
			PLANE_TOP,
			PLANE_BOTTOM,
			PLANE_COUNT,
		};

		plane();

		glm::vec3 normal_;
		float d_;
	};

	struct frustum 
	{
		frustum();

		void construct_from_view_matrix(const glm::mat4& view);

		bool is_inside(const glm::vec3& point) const;
		bool is_inside(const bounding_sphere& sphere) const;

		plane planes_[plane::PLANE_COUNT];
	};

	struct transform 
	{
		transform();

		void set_origin(const glm::vec3& origin);
		void set_position(const glm::vec3& position);
		void set_scale(const glm::vec3& scale);
		void set_rotation(const glm::vec3& rotation);

		glm::vec3 origin_;
		glm::vec3 position_;
		glm::vec3 scale_;
		glm::vec3 rotation_;
	};

	struct renderable 
	{
		renderable();

		void render(const fps_camera& camera);

		shader_program* program_;
		texture* texture_;
		sampler_state* sampler_state_;
		vertex_buffer* vertex_buffer_;
		index_buffer* index_buffer_;
		vertex_format* format_;
	};

	struct scene
	{
		struct node {
			node();

			renderable renderable_;
			transform transform_;
			bounding_sphere sphere_;
		};

		scene();

		void render(const fps_camera& camera);

		dynamic_array<node> nodes_;
	};

} // !neon



#endif // !NEON_GRAPHICS_H_INCLUDED
