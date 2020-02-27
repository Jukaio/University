// neon_graphics.cc

#include <neon_graphics.h>
#include <cassert>

#include "stb_image.h"


namespace neon {
	vertex_buffer::vertex_buffer()
		: id_(0)
	{

	}

	bool vertex_buffer::create(const int size, const void* data) {
		if (is_valid()) {
			return false;
		}

		glGenBuffers(1, &id_);
		glBindBuffer(GL_ARRAY_BUFFER, id_);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

		GLenum error = glGetError();
		return error == GL_NO_ERROR;
	}

	void vertex_buffer::update(const int size, const void* data)
	{
		if (!is_valid())
			return;
		glBindBuffer(GL_ARRAY_BUFFER, id_);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	void vertex_buffer::destroy() {
		if (!is_valid())
		{
			return;
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &id_);
		id_ = 0;
	}

	bool vertex_buffer::is_valid() const {
		return id_ != 0;
	}

	void vertex_buffer::bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, id_);
	}

	void vertex_buffer::render(GLenum primitive, int start, int count)
	{
		glDrawArrays(primitive, start, count);
	}

	//	!vertex_buffer

	// index_buffer

	index_buffer::index_buffer()
		: id_(0)
	{
	}

	bool index_buffer::create(const int size, const GLenum type, const void* data)
	{
		if (is_valid())
		{
			return false;
		}

		type_ = type;
		glGenBuffers(1, &id_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);



		GLenum error = glGetError();
		return error == GL_NO_ERROR;
	}

	void index_buffer::destroy()
	{
		if (!is_valid())
		{
			return;
		}
	
		glDeleteBuffers(1, &id_);
		id_ = 0;
	}

	bool index_buffer::is_valid() const
	{
		return id_ != 0;
	}

	void index_buffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
	}

	void index_buffer::render(GLenum primitive, int start, int count)
	{
		glDrawElements(primitive, count, type_, (const void*) nullptr);
	}

	// !index_buffer 


	namespace {
		GLuint create_shader(GLenum type, const char* source) {
			GLuint id = glCreateShader(type);
			glShaderSource(id, 1, &source, nullptr);
			glCompileShader(id);

			return id;
		}

		GLuint create_program(GLuint vid, GLuint fid) {
			GLuint id = glCreateProgram();
			glAttachShader(id, vid);
			glAttachShader(id, fid);
			glLinkProgram(id);

			GLint status = 0;
			glGetProgramiv(id, GL_LINK_STATUS, &status);
			if (status == GL_FALSE) {
				char vsh_err[1024] = {};
				char fsh_err[1024] = {};
				char sh_err[1024] = {};

				glGetShaderInfoLog(vid, sizeof(vsh_err), nullptr, vsh_err);
				glGetShaderInfoLog(fid, sizeof(fsh_err), nullptr, fsh_err);
				glGetProgramInfoLog(id, sizeof(sh_err), nullptr, sh_err);

				assert(false);

				glDeleteProgram(id);
				id = 0;
			}

			glDeleteShader(vid);
			glDeleteShader(fid);

			return id;
		}

	} // !anon

	shader_program::shader_program()
		: id_(0)
	{

	}

	bool shader_program::create(const string& vertex_shader_filename,
								const string& fragment_shader_filename) {

		if (is_valid()) {
			return false;
		}

		dynamic_array<uint8> vertex_shader_file_content;
		if (!file_system::read_file_content(vertex_shader_filename,
			vertex_shader_file_content))
		{
			return false;
		}
		vertex_shader_file_content.push_back(0);
		const char* vertex_shader_source = (const char*)vertex_shader_file_content.data();


		dynamic_array<uint8> fragment_shader_file_content;
		if (!file_system::read_file_content(fragment_shader_filename,
			fragment_shader_file_content))
		{
			return false;
		}
		fragment_shader_file_content.push_back(0);
		const char* fragment_shader_source = (const char*)fragment_shader_file_content.data();

		GLuint vid = create_shader(GL_VERTEX_SHADER, vertex_shader_source);
		GLuint fid = create_shader(GL_FRAGMENT_SHADER, fragment_shader_source);
		id_ = create_program(vid, fid);

		GLenum error = glGetError();
		return error == GL_NO_ERROR;
	}

	void shader_program::destroy() {
		if (is_valid()) {
			return;
		}

		glDeleteProgram(id_);
		id_ = 0;
	}

	GLint shader_program::get_attrib_location(const string& name) const {
		bind();
		return glGetAttribLocation(id_, name.c_str());
	}


	GLint shader_program::get_uniform_location(const string& name) const {
		bind();
		return glGetUniformLocation(id_, name.c_str());
	}

	bool shader_program::set_uniform_mat4(const string& name, const glm::mat4& value) {
		GLuint location = get_uniform_location(name);
		if (location == -1) {
			return false;
		}

		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));

		return true;
	}

	bool shader_program::set_uniform_vec4(const string& name, const glm::vec4& value) {
		GLuint location = get_uniform_location(name);
		if (location == -1) {
			return false;
		}

		glUniform4fv(location, 1, glm::value_ptr(value));

		return true;
	}

	bool shader_program::set_uniform_vec3(const string& name, const glm::vec3& value) {
		GLuint location = get_uniform_location(name);
		if (location == -1) {
			return false;
		}

		glUniform3fv(location, 1, glm::value_ptr(value));
		return true;
	}

	bool shader_program::is_valid() const {
		return id_ != 0;
	}

	void shader_program::bind() const {
		glUseProgram(id_);
	}
	// !shader_program

	//vertex format
	vertex_format::attribute::attribute()
		: index_(0)
		, size_(0)
		, type_(0)
		, normalised_(false)
		, offset_(0)
	{
	}

	vertex_format::vertex_format()
		: stride_(0)
		, attribute_count_(0)
		, attributes_{}
	{
	}

	namespace {
		uint32 size_of_gl_type(GLenum type) {
			switch (type)
			{
				case GL_FLOAT:
					return sizeof(GL_FLOAT);
				case GL_UNSIGNED_BYTE:
					return sizeof(uint8);
			}
			assert(false);
			return 0;
		}
	}	// !anon

	void vertex_format::add_attribute(const int32 index, const uint32 size,
									  const GLenum type, const bool normalized)
	{
		assert(attribute_count_ < ATTRIBUTE_COUNT);
		uint32 at = attribute_count_++;
		attributes_[at].index_ = index;
		attributes_[at].size_ = size;
		attributes_[at].type_ = type;
		attributes_[at].normalised_ = normalized;
		attributes_[at].offset_ = stride_;

		stride_ += size * size_of_gl_type(type);
	}

	bool vertex_format::is_valid() const {
		return attribute_count_ > 0;
	}

	void vertex_format::bind() const {
		for (uint32 index = 0; index < ATTRIBUTE_COUNT; index++) {
			glDisableVertexAttribArray(index);
		}

		for (uint32 index = 0; index < attribute_count_; index++) {
			const attribute& attrib = attributes_[index];
			glEnableVertexAttribArray(attrib.index_);
			glVertexAttribPointer(attrib.index_,
								  attrib.size_,
								  attrib.type_,
								  attrib.normalised_,
								  stride_,
								  (const void*)attrib.offset_);
		}
	}

	//Texture
	texture::texture()
		:id_(0)
	{
	}

	bool texture::create(const string& filename)
	{
		if (is_valid())
			return false;

		dynamic_array<uint8> file_content;
		if (!file_system::read_file_content(filename, file_content))
			return false;

		int width = 0, height = 0, components = 0;
		auto bitmap = stbi_load_from_memory(file_content.data(),
											(int)file_content.size(),
											&width,
											&height,
											&components,
											STBI_rgb_alpha);
		if (!bitmap)
			return false;

		type_ = GL_TEXTURE_2D;

		glGenTextures(1, &id_);
		glBindTexture(GL_TEXTURE_2D, id_);

		glTexImage2D(GL_TEXTURE_2D,
					 0,
					 GL_RGBA,
					 width, //width
					 height, //height
					 0, //border
					 GL_RGBA,
					 GL_UNSIGNED_BYTE,
					 bitmap);
		stbi_image_free(bitmap);

		GLenum error = glGetError();
		return error == GL_NO_ERROR;
	}

	bool texture::create_cubemap(int width, int height, const void **data)
	{
		if (is_valid())
			return false;

		type_ = GL_TEXTURE_CUBE_MAP;

		glGenTextures(1, &id_);
		glBindTexture(GL_TEXTURE_CUBE_MAP, id_);

		for (int i = 0; i < 6; i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
						 0,
						 GL_RGBA,
						 width, //width
						 height, //height
						 0, //border
						 GL_RGBA,
						 GL_UNSIGNED_BYTE,
						 data[i]);
		}


		GLenum error = glGetError();
		return error == GL_NO_ERROR;
	}

	void texture::destroy()
	{
		if (!is_valid())
			return;

		glDeleteTextures(1, &id_);
		id_ = 0;
	}

	bool texture::is_valid() const
	{
		return id_ != 0;
	}

	void texture::bind() const
	{
		glBindTexture(type_, id_);
	}


	//Sampler
	sampler_state::sampler_state()
		: id_(0)
	{

	}

	bool sampler_state::create(const GLenum filter, const GLenum address_mode_u, const GLenum address_mode_v)
	{
		if (is_valid())
			return false;

		glGenSamplers(1, &id_);
		glBindSampler(1, id_);
		glSamplerParameteri(id_, GL_TEXTURE_MIN_FILTER, filter);
		glSamplerParameteri(id_, GL_TEXTURE_MAG_FILTER, filter);
		glSamplerParameteri(id_, GL_TEXTURE_WRAP_S, address_mode_u);
		glSamplerParameteri(id_, GL_TEXTURE_WRAP_T, address_mode_v);

		GLenum error = glGetError();
		return error == GL_NO_ERROR;
	}

	void sampler_state::destroy()
	{
		if (is_valid())
			return;

		glDeleteSamplers(1, &id_);
		id_ = 0;
	}

	bool sampler_state::is_valid() const
	{
		return  id_ != 0;
	}

	void sampler_state::bind() const
	{
		glBindSampler(0, id_);
	}


	//BITMAP FONT
	bitmap_font::bitmap_font()
	{
	}

	bool bitmap_font::create()
	{
		if (!program_.create("assets/bitmap_font_vertex_shader.txt",
							 "assets/bitmap_font_fragment_shader.txt"))
			return false;

		format_.add_attribute(0, 2, GL_FLOAT, false);
		format_.add_attribute(1, 2, GL_FLOAT, false);

		if (!buffer_.create(512, nullptr))
			return false;

		if (!texture_.create("assets/test.png"))
			return false;

		if (!sampler_.create(GL_NEAREST,
							  GL_CLAMP_TO_EDGE,
							  GL_CLAMP_TO_EDGE))
			return false;

		projection_ = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f);

		return true;
	}

	void bitmap_font::destroy()
	{
	}

	void bitmap_font::render(const float pos_x, const float pos_y, const string& text)
	{
		constexpr int characters_per_row = 16;
		const float size = 8.0f;
		const float uv1 = 1.0f / 16.0f;

		float p_x = pos_x;
		float p_y = pos_y;

		for (auto&& character : text)
		{
			int index = character - ' ';

			int x = index % characters_per_row;
			int y = index / characters_per_row + 2;

			float u = (float)x / 16.0f;
			float v = (float)y / 16.0f;

			vertex verts[6] =
			{
			   {p_x       , p_y       , u      , v      },
			   {p_x + size, p_y       , u + uv1, v      },
			   {p_x + size, p_y + size, u + uv1, v + uv1},

			   {p_x + size, p_y + size, u + uv1, v + uv1},
			   {p_x       , p_y + size, u      , v + uv1},
			   {p_x       , p_y       , u      , v      },

			};

			for (auto& vert : verts) {
				vertices_.push_back(vert);
			}

			p_x += size;
		}
	}

	void bitmap_font::flush()
	{
		// note: submit the vertices from CPU to GPU 
		int size = (int)(sizeof(vertex) * vertices_.size());
		buffer_.update(size,
					   vertices_.data());

		// note: render the thing!
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		glEnable(GL_BLEND);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);

		program_.bind();
		program_.set_uniform_mat4("projection", projection_);
		buffer_.bind();
		format_.bind();
		texture_.bind();
		sampler_.bind();

		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices_.size());

		vertices_.clear();

	}

	// FPS Camera
	fps_camera::fps_camera()
		: yaw_(0.0f)
		, pitch_(0.0f)
		, roll_(0.0f)
		, x_axis_(0.0f)
		, y_axis_(0.0f)
		, z_axis_(0.0f)
		, position_(0.0f)
		, projection_(1.0f)
		, view_(1.0f)
	{
	}

	void fps_camera::update()
	{
		glm::vec3 x(1.0f, 0.0f, 0.0f);
		glm::vec3 y(0.0f, 1.0f, 0.0f);
		glm::vec3 z(0.0f, 0.0f, 1.0f);

		// Avoid gimbal lock
		glm::mat4 ry = glm::rotate(glm::mat4(1.0f), yaw_, y);
		x = ry * glm::vec4(x, 0.0f);
		z = ry * glm::vec4(z, 0.0f);

		glm::mat4 rx = glm::rotate(glm::mat4(1.0f), pitch_, x);
		y = rx * glm::vec4(y, 0.0f);
		z = rx * glm::vec4(z, 0.0f);

		view_ = glm::mat4(1.0f);
		view_[0][0] = x.x; view_[1][0] = x.y;	view_[2][0] = x.z;
		view_[0][1] = y.x; view_[1][1] = y.y;	view_[2][1] = y.z;
		view_[0][2] = z.x; view_[1][2] = z.y;	view_[2][2] = z.z;

		view_[3][0] = -glm::dot(position_, x);
		view_[3][1] = -glm::dot(position_, y);
		view_[3][2] = -glm::dot(position_, z);

		// Note: Movement Helpers
		x_axis_ = x;
		y_axis_ = y;
		z_axis_ = z;

	}

	void fps_camera::set_perspective(float fov, float aspect, float z_near, float x_far)
	{
		projection_ = glm::perspective(fov, aspect, z_near, x_far);
	}

	void fps_camera::rotate_x(float amount)
	{
		pitch_ += amount;
	}

	void fps_camera::rotate_y(float amount)
	{
		yaw_ += amount;
	}

	void fps_camera::forward(float amount)
	{
		position_ += z_axis_ * amount;
	}

	void fps_camera::sidestep(float amount)
	{
		position_ += x_axis_ * amount;
	}


	// FPS Camera Controller
	fps_camera_controller::fps_camera_controller(fps_camera& camera, keyboard& kb, mouse& m)
		: camera_(camera)
		, keyboard_(kb)
		, mouse_(m)
	{

	}

	void fps_camera_controller::update(const time& delta_Time)
	{
		constexpr float camera_Speed = 5.0f;
		const float amount = camera_Speed * delta_Time.as_seconds();

		if (keyboard_.is_down(KEYCODE_W))
		{
			camera_.forward(-amount);
		}
		if (keyboard_.is_down(KEYCODE_S))
		{
			camera_.forward(amount);
		}

		if (keyboard_.is_down(KEYCODE_A))
		{
			camera_.sidestep(-amount);
		}
		if (keyboard_.is_down(KEYCODE_D))
		{
			camera_.sidestep(amount);
		}

		if (mouse_.is_down(MOUSE_BUTTON_RIGHT))
		{
			glm::vec2 mouse_delta;
			mouse_delta.x = (float)mouse_.x_;
			mouse_delta.y = (float)mouse_.y_;
			mouse_delta = mouse_delta - mouse_Position_;

			if (mouse_delta.x != 0.0f)
			{
				camera_.rotate_y(glm::radians(mouse_delta.x) * delta_Time.as_seconds());
			}
			if (mouse_delta.y != 0.0f)
			{
				camera_.rotate_x(glm::radians(mouse_delta.y) * delta_Time.as_seconds());
			}
		}
		mouse_Position_ = glm::vec2((float)mouse_.x_, (float)mouse_.y_);

		camera_.update();
	}

	// Skybox
	skybox::skybox()
	{

	}

	bool skybox::create()
	{
		const char* names[]
		{
			"assets/Skybox/xpos.png",
			"assets/Skybox/xneg.png",
			"assets/Skybox/ypos.png",
			"assets/Skybox/yneg.png",
			"assets/Skybox/zpos.png",
			"assets/Skybox/zneg.png",
		};

		image sides[6];
		for (int i = 0; i < 6; i++)
		{
			if (!sides[i].create_from_file(names[i]))
			{
				assert(!"could not find cubemap image\n");
				return false;
			}
		}

		const int width = sides[0].width();
		const int height = sides[0].height();
		for (int i = 1; i < 6; i++)
		{
			if (width != sides[i].width() || height != sides[i].height())
			{
				assert(!"Cubemap Images must have the same dimensions\n");
				return false;
			}
		}

		const void* faces[6]{ }; //Not sure what we are doing here
		for (int i = 0; i < 6; i++) {
			faces[i] = sides[i].data();
		}

		if (!cubemap_.create_cubemap(width, height, faces))
		{
			assert(!"could not create cubemap\n");
			return false;
		}

		const float Q = 1.5f;
		const glm::vec3 vertices[] =
		{
			// x positive
			{  Q,  Q, -Q },
			{  Q,  Q,  Q },
			{  Q, -Q,  Q },
			{  Q, -Q,  Q },
			{  Q, -Q, -Q },
			{  Q,  Q, -Q },

			// x negative
			{ -Q,  Q,  Q },
			{ -Q,  Q, -Q },
			{ -Q, -Q, -Q },
			{ -Q, -Q, -Q },
			{ -Q, -Q,  Q },
			{ -Q,  Q,  Q },

			// y positive
			{ -Q,  Q,  Q },
			{  Q,  Q,  Q },
			{  Q,  Q, -Q },
			{  Q,  Q, -Q },
			{ -Q,  Q, -Q },
			{ -Q,  Q,  Q },

			// y negative
			{ -Q, -Q, -Q },
			{  Q, -Q, -Q },
			{  Q, -Q,  Q },
			{  Q, -Q,  Q },
			{ -Q, -Q,  Q },
			{ -Q, -Q, -Q },

			// z positive
			{ -Q,  Q, -Q },
			{  Q,  Q, -Q },
			{  Q, -Q, -Q },
			{  Q, -Q, -Q },
			{ -Q, -Q, -Q },
			{ -Q,  Q, -Q },

			// z negative
			{  Q,  Q,  Q },
			{ -Q,  Q,  Q },
			{ -Q, -Q,  Q },
			{ -Q, -Q,  Q },
			{  Q, -Q,  Q },
			{  Q,  Q,  Q },
		};

		if (!buffer_.create(sizeof(vertices), vertices))
			return false;

		format_.add_attribute(0, 3, GL_FLOAT, false);

		if (!program_.create("assets/Skybox/vertex_shader.txt",
							 "assets/Skybox/fragment_shader.txt"))
			return false;

		if (!sampler_.create(GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE))
			return false;

		return true;
	}

	void skybox::destroy()
	{
	}

	void skybox::render(const fps_camera& camera)
	{
		glm::mat4 fixed_view = camera.view_;
		fixed_view[3][0] = 0.0f;
		fixed_view[3][1] = 0.0f;
		fixed_view[3][2] = 0.0f;

		glDisable(GL_DEPTH_TEST);

		program_.bind();
		program_.set_uniform_mat4("projection", camera.projection_);
		program_.set_uniform_mat4("view", fixed_view);

		buffer_.bind();
		format_.bind();
		cubemap_.bind();
		sampler_.bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}


	//Terrain
	terrain::terrain()
		: index_count_(0)
	{

	}

	bool terrain::create(const string& heightmap_filename, const string& texture_Filename)
	{
		image heightmap;
		if (!heightmap.create_from_file(heightmap_filename.c_str()))
			return false;

		dynamic_array<vertex> vertices;
		const int32 width = heightmap.width();
		const int32 height = heightmap.height();
		const int32 stride = width * 4;
		for (int32 z = 0; z < height; z++)
		{
			for (int32 x = 0; x < width; x++)
			{
				const uint32 offset = x * 4 + z * stride;
				const uint8* rgba = heightmap.data() + offset;

				vertex tmp;
				tmp.position_ = { x / 25.5f, rgba[1] / 255.0f, z/ 25.5 };
				tmp.texcoord_ = { (float)x / (float)width, (float)z / (float)height };
				vertices.push_back(tmp);
			}
		}

		if (!program_.create("assets/Heightmap/vertex_shader.txt",
			"assets/Heightmap/fragment_shader.txt"))
			return false;


		if (!vertex_buffer_.create(sizeof(vertex) * (int) vertices.size(), vertices.data()))
			return false;

		format_.add_attribute(0, 3, GL_FLOAT, false); // Adding the vertex to format_
		format_.add_attribute(1, 2, GL_FLOAT, false); // TexCoord;
		format_.add_attribute(2, 3, GL_FLOAT, false); // Normals (Unused for now)

		dynamic_array<uint32> indices;
		for (int32 z = 0; z < height - 1; z++)
		{
			for (int32 x = 0; x < width - 1; x++)
			{
				int top_Left_Index_Num = z * width + x;
				int top_Right_Index_Num = z * width + x + 1;
				int bottom_Left_Index_Num = (z + 1) * width + x;
				int bottom_Right_Index_Num = (z + 1) * width + x + 1;
				////////////
				//Triangle 1
				indices.push_back(top_Left_Index_Num);
				indices.push_back(top_Right_Index_Num);
				indices.push_back(bottom_Right_Index_Num);

				//Triangle 2
				indices.push_back(bottom_Right_Index_Num);
				indices.push_back(bottom_Left_Index_Num);
				indices.push_back(top_Left_Index_Num);
			}
		}
		index_count_ = (int) indices.size();
 

		if (!index_buffer_.create(sizeof(uint32) * (int) indices.size(), GL_UNSIGNED_INT, indices.data()))
			return false;

		if (!texture_.create(texture_Filename.c_str()))
			return false;

		if (!sampler_.create(GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE))
			return false;

		glm::mat4 world = glm::translate(glm::mat4(1.0f),
										 glm::vec3(0.0f, -2.0f, 0.0f));
		program_.set_uniform_mat4("world", world);

		return true;
	}

	void terrain::destroy()
	{
	}

	void terrain::render()
	{
		program_.set_uniform_mat4("projection", camera_->projection_);
		program_.set_uniform_mat4("view", camera_->view_);

		glFrontFace(GL_CW);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		program_.bind();
		vertex_buffer_.bind();
		format_.bind();
		index_buffer_.bind();
		texture_.bind();
		sampler_.bind();

		index_buffer_.render(GL_TRIANGLES, 0, index_count_);
	}
	//!Terrain

	// bounding_spere

	bounding_sphere::bounding_sphere()
		: center_{}
		, radius_{}
	{
	}

	bounding_sphere::bounding_sphere(const glm::vec3& center, float radius)
		: center_(center)
		, radius_(radius)
	{
	}

	void bounding_sphere::set_center(const glm::vec3& center) {
		center_ = center;
	}

	void bounding_sphere::set_radius(const float radius) {
		radius_ = radius;
	}

	// !bounding_sphere
	// plane

	plane::plane()
		: normal_{}
		, d_{}
	{
	}

	frustum::frustum()
	{
	}

	// source: https://www.gamedevs.org/uploads/fast-extraction-viewing-frustum-planes-from-world-view-projection-matrix.pdf
	void frustum::construct_from_view_matrix(const glm::mat4& view) {
		// note: extract left plane
		planes_[plane::PLANE_LEFT].normal_ = glm::vec3(view[0][3] + view[0][0],
													   view[1][3] + view[1][0],
													   view[2][3] + view[2][0]);
		planes_[plane::PLANE_LEFT].d_ = view[3][3] + view[3][0];

		// note: extract right plane
		planes_[plane::PLANE_RIGHT].normal_ = glm::vec3(view[0][3] - view[0][0],
														view[1][3] - view[1][0],
														view[2][3] - view[2][0]);
		planes_[plane::PLANE_RIGHT].d_ = view[3][3] - view[3][0];

		// note: extract top plane
		planes_[plane::PLANE_TOP].normal_ = glm::vec3(view[0][3] - view[0][1],
													  view[1][3] - view[1][1],
													  view[2][3] - view[2][1]);
		planes_[plane::PLANE_TOP].d_ = view[3][3] - view[3][1];

		// note: extract bottom plane
		planes_[plane::PLANE_BOTTOM].normal_ = glm::vec3(view[0][3] + view[0][1],
														 view[1][3] + view[1][1],
														 view[2][3] + view[2][1]);
		planes_[plane::PLANE_BOTTOM].d_ = view[3][3] + view[3][1];

		// note: extract far plane
		planes_[plane::PLANE_FAR].normal_ = glm::vec3(view[0][3] - view[0][2],
													  view[1][3] - view[1][2],
													  view[2][3] - view[2][2]);
		planes_[plane::PLANE_FAR].d_ = view[3][3] - view[3][2];

		// note: extract near plane
		planes_[plane::PLANE_NEAR].normal_ = glm::vec3(view[0][2],
													   view[1][2],
													   view[2][2]);
		planes_[plane::PLANE_NEAR].d_ = view[3][2];


		for (int32 i = 0; i < plane::PLANE_COUNT; i++) {
			float length = glm::length(planes_[i].normal_);
			planes_[i].normal_ /= length;
			planes_[i].d_ /= length;
		}
	}

	// !plane

	// frustrum

	bool frustum::is_inside(const glm::vec3& point) const {
		for (int32 index = 0; index < plane::PLANE_COUNT; index++) {
			float dist = glm::dot(planes_[index].normal_, point) +
				planes_[index].d_;
			if (dist < 0.0f)
				return false;
		}

		return true;
	}

	bool frustum::is_inside(const bounding_sphere& sphere) const {
		for (int32 index = 0; index < plane::PLANE_COUNT; index++) {
			float dist = glm::dot(planes_[index].normal_, sphere.center_) +
				planes_[index].d_;
			if (dist < -sphere.radius_)
				return false;
		}

		return true;
	}

	// !frustrum
	// transform

	transform::transform()
		: origin_(0.0f, 0.0f, 0.0f)
		, position_(0.0f, 0.0f, 0.0f)
		, scale_(1.0f, 1.0f, 1.0f)
		, rotation_(0.0f, 0.0f, 0.0f)
	{
	}

	void transform::set_origin(const glm::vec3& origin) {
		origin_ = origin;
	}

	void transform::set_position(const glm::vec3& position) {
		position_ = position;
	}

	void transform::set_scale(const glm::vec3& scale) {
		scale_ = scale;
	}

	void transform::set_rotation(const glm::vec3& rotation) {
		rotation_ = rotation;
	}

	// !transform
	// renderable

	renderable::renderable()
		: program_(nullptr)
		, texture_(nullptr)
		, sampler_state_(nullptr)
		, vertex_buffer_(nullptr)
		, index_buffer_(nullptr)
		, format_(nullptr)
	{
	}

	void renderable::render(const fps_camera& camera) {
		// ...
	}

	// !renderable
	// node

	scene::node::node()
	{
	}

	scene::scene()
	{
	}

	void scene::render(const fps_camera& camera) {
		frustum frustum;
		frustum.construct_from_view_matrix(camera.view_);

		for (auto&& node : nodes_) {
			if (frustum.is_inside(node.sphere_)) {
				node.renderable_.render(camera);
			}
		}
	}

	// !node
	// !Code from Tommi


} // !neon