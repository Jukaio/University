// neon_testbed.h

#ifndef NEON_TESTBED_H_INCLUDED
#define NEON_TESTBED_H_INCLUDED

#include <neon_core.h>
#include <neon_opengl.h>
#include "neon_graphics.h"
#include "neon_framebuffer.h"
#include "Celestial.h"

namespace neon 
{
	struct vertex
	{
		float x_; 
		float y_;
		float z_;
		uint32 color_;
		float u_;
		float v_;
	};
   struct testbed : application {
      testbed();
      virtual bool enter() final;
      virtual void exit() final;
      virtual bool tick(const time &dt) final;
	  void Change_Light_Color(glm::vec3 color);
	  void Change_Light_Position(glm::vec3 pos);
	  void Do_Action(keycode key, float& variable_to_change, bool go_up, bool has_normalised_bound = true);
	  float red_, green_, blue_;
	  float light_x_, light_y_, light_z_;

	  vertex_buffer vbo_;
	  shader_program program_;
	  vertex_format format_;
	  texture texture_;
	  sampler_state sampler_;
	  glm::mat4 mat;
	  glm::mat4 world_;

	  float rotation_;
	  bitmap_font font_;

	  fps_camera camera_;
	  fps_camera_controller controller_;

	  skybox skybox_;
	  terrain terrain_;
	  framebuffer framebuffer_;

	  Celestial sun_;
	  Celestial mercury_;

	  Celestial venus_;
	  Celestial earth_;
	  Celestial mars_;
	  Celestial jupiter_;
	  Celestial saturn_;
	  Celestial uranus_;
	  Celestial neptune_;

	  Celestial moon_;

	  Celestial celestials_[4];
   };

   

} // !neon

#endif // !NEON_TESTBED_H_INCLUDED
