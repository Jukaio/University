
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
			float u_;
			float v_;
			float light_x_;
			float light_y_;
			float light_z_;
		};

		Celestial();

		bool create(fps_camera& camera, Celestial* parent, const char* texture_Name, glm::vec3 position, glm::vec3 scale, float modifier);
		void render(float dt);
		void render();

		void destroy();

		fps_camera* camera_;

		Celestial* parent_;

		vertex_buffer vbo_;
		shader_program program_;
		vertex_format format_;
		texture texture_;
		sampler_state sampler_;

		glm::vec3 pos_;
		glm::vec3 scale_;
		glm::vec3 position_;

		float rotation_Parent_;
		float rotation_Self_;
		float mod_ = 0;

		float velocity_; //Distance per frame to travel
		float travel_Angle_;
	};
};

#endif // __CELESTIAL__

