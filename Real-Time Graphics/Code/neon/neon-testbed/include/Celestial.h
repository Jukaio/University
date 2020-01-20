
#ifndef __CELESTIAL__
#define __CELESTIAL__

#include "neon_graphics.h"
#pragma warning(push)
#pragma warning(disable: 4201)
#pragma warning(disable: 4127)
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace neon
{
	struct Celestial
	{
		struct vertex
		{
			float x_;
			float y_;
			float z_;
			unsigned int color_;
			float u_;
			float v_;
		};

		Celestial();

		bool create(fps_camera& camera, glm::vec3 position);
		void update(float dt);
		void destroy();

		void set_Position(float x, float y, float z);

		fps_camera* camera_;

		vertex_buffer vbo_;
		shader_program program_;
		vertex_format format_;
		texture texture_;
		sampler_state sampler_;
		glm::vec3 position_;
		glm::vec3 pos_;
		glm::mat4 pos_Mat_;
		float rotation_Self_;
		float rotation_Universe_;
	};
};

#endif // __CELESTIAL__

