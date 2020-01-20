#include "Celestial.h"

namespace neon
{
	Celestial::Celestial()
		: rotation_Self_(0.0f)
		, rotation_Universe_(0.0f)
		, pos_Mat_(1.0f)
		, position_(glm::vec3(0.0f))
	{
		
	}

	bool Celestial::create(fps_camera& camera, glm::vec3 position)
	{
		camera_ = &camera;
		pos_ = position;
		vertex vertices[] =
		{
			// Triangle 1, side 1
			{  1.0f ,  1.0f ,  1.0f ,    0xff0000ff,     1.0f, 0.0f  }, // Triangle 1, side 1
			{  1.0f , -1.0f ,  1.0f ,    0xff00ff00,     1.0f, 1.0f  },
			{ -1.0f , -1.0f ,  1.0f ,    0xffff0000,     0.0f, 1.0f  },   
			{  1.0f ,  1.0f ,  1.0f ,    0xff4b3319,     1.0f, 0.0f  }, // Triangle 2, side 1
			{ -1.0f , -1.0f ,  1.0f ,    0xff4b3319,     0.0f, 1.0f  },
			{ -1.0f ,  1.0f ,  1.0f ,    0xff4b3319,     0.0f, 0.0f  },
			{  1.0f ,  1.0f ,  1.0f ,    0xff0000ff,     1.0f, 0.0f  }, // Triangle 1, side 2
			{  1.0f , -1.0f , -1.0f ,    0xffff0000,     0.0f, 1.0f  },
			{  1.0f , -1.0f ,  1.0f ,    0xff00ff00,     0.0f, 0.0f  },    
			{  1.0f ,  1.0f ,  1.0f ,    0xff4b3319,     1.0f, 0.0f  }, // Triangle 2, side 2     
			{  1.0f ,  1.0f , -1.0f ,    0xff4b3319,     1.0f, 1.0f  },
			{  1.0f , -1.0f , -1.0f ,    0xff4b3319,     0.0f, 1.0f  },
			{  1.0f ,  1.0f , -1.0f ,    0xff0000ff,     1.0f, 1.0f  }, // Triangle 1, side 3
			{ -1.0f , -1.0f , -1.0f ,    0xffff0000,     0.0f, 0.0f  },
			{  1.0f , -1.0f , -1.0f ,    0xff00ff00,     1.0f, 0.0f  },  
			{  1.0f ,  1.0f , -1.0f ,    0xff4b3319,     1.0f, 1.0f  }, // Triangle 2, side 3      
			{ -1.0f ,  1.0f , -1.0f ,    0xff4b3319,     0.0f, 1.0f  },
			{ -1.0f , -1.0f , -1.0f ,    0xff4b3319,     0.0f, 0.0f  },
			{ -1.0f ,  1.0f , -1.0f ,    0xff0000ff,     1.0f, 0.0f  }, // Triangle 1, side 4
			{ -1.0f , -1.0f ,  1.0f ,    0xffff0000,     0.0f, 1.0f  },
			{ -1.0f , -1.0f , -1.0f ,    0xff00ff00,     0.0f, 0.0f  }, 
			{ -1.0f ,  1.0f , -1.0f ,    0xff4b3319,     1.0f, 0.0f  }, // Triangle 2, side 4 
			{ -1.0f ,  1.0f ,  1.0f ,    0xff4b3319,     1.0f, 1.0f  },
			{ -1.0f , -1.0f ,  1.0f ,    0xff4b3319,     0.0f, 1.0f  },
			{ -1.0f ,  1.0f ,  1.0f ,    0xff0000ff,     0.0f, 1.0f  }, // Triangle 1, side 5
			{  1.0f ,  1.0f , -1.0f ,    0xffff0000,     1.0f, 0.0f  },
			{  1.0f ,  1.0f ,  1.0f ,    0xff00ff00,     1.0f, 1.0f  },
			{ -1.0f ,  1.0f , -1.0f ,    0xff4b3319,     0.0f, 0.0f  }, // Triangle 2, side 5     
			{  1.0f ,  1.0f , -1.0f ,    0xff4b3319,     1.0f, 0.0f  },
			{ -1.0f ,  1.0f ,  1.0f ,    0xff4b3319,     0.0f, 1.0f  },
			{ -1.0f , -1.0f ,  1.0f ,    0xff0000ff,     1.0f, 1.0f  }, // Triangle 1, side 6
			{  1.0f , -1.0f ,  1.0f ,    0xff00ff00,     0.0f, 1.0f  },
			{  1.0f , -1.0f , -1.0f ,    0xffff0000,     0.0f, 0.0f  },
			{ -1.0f , -1.0f , -1.0f ,    0xff4b3319,     1.0f, 0.0f  }, // Triangle 2, side 6    
			{ -1.0f , -1.0f ,  1.0f ,    0xff4b3319,     1.0f, 1.0f  },
			{  1.0f , -1.0f , -1.0f ,    0xff4b3319,     0.0f, 0.0f  },
		}; // Big triangle and smaller triangle

		if (!vbo_.create(sizeof(vertices), vertices)) {
			return false;
		}

		if (!program_.create("assets/vertex_shader.txt",
			"assets/fragment_shader.txt"))
		{
			return false;
		}

		program_.bind();
		glm::mat4 world = glm::translate(glm::mat4(1.0f),
										 glm::vec3(pos_));

		program_.set_uniform_mat4("world", world);
		program_.set_uniform_vec4("mod_color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));


		format_.add_attribute(0, 3, GL_FLOAT, false);
		format_.add_attribute(1, 4, GL_UNSIGNED_BYTE, true);
		format_.add_attribute(2, 2, GL_FLOAT, false);

		if (!texture_.create("assets/RopeBunny.png"))
		{
			return false;
		}

		if (!sampler_.create(GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE)) {
			return false;
		}


		return true;
	}

	void Celestial::update(float dt)
	{
		glm::mat4 world = glm::mat4(1.0f);
		world = glm::rotate(world,
							rotation_Universe_,
							glm::vec3(0.0f, 1.0f, 0.0f));

		world = glm::translate(world,
							   glm::vec3(0.0f) + glm::vec3(pos_));

		world = glm::rotate(world,
							rotation_Self_,
							glm::vec3(0.5f, 0.5f, 0.0f));

		rotation_Self_ += dt / 500.0f;
		rotation_Universe_ += dt / 500.0f;

		program_.bind();
		program_.set_uniform_mat4("projection", camera_->projection_); // new matrices
		program_.set_uniform_mat4("view", camera_->view_);
		program_.set_uniform_mat4("world", world);

		vbo_.bind();
		format_.bind();
		texture_.bind();
		sampler_.bind();

		glEnable(GL_DEPTH_TEST);

		glEnable(GL_CULL_FACE); // remove this to render the inside of the cube, or comment it out
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);

		glEnable(GL_BLEND);
		glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
		glDrawArrays(GL_TRIANGLES, 0, 99);
	}

	void Celestial::destroy()
	{

	}

	void Celestial::set_Position(float x, float y, float z)
	{
		position_ = glm::vec3(x, y, z);
	}
};
