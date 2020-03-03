#include "Celestial.h"

# define PI 3.14159265358979323846

namespace neon
{
	Celestial::Celestial()
		: camera_(nullptr)
		, parent_(nullptr)
		, pos_(0.0f)
		, scale_(1.0f)
		, rotation_Parent_(0.0f)
		, rotation_Self_(0.0f)
		, velocity_(1.0f)
		, travel_Angle_(0)
	{
		
	}

	bool Celestial::create(fps_camera& camera, Celestial* parent, const char* texture_Path, glm::vec3 position, glm::vec3 scale, float modifier)
	{
		camera_ = &camera;
		parent_ = parent;
		pos_ = position;
		scale_ = scale;
		mod_ = modifier;

		if(pos_.y != 0)
			travel_Angle_ = velocity_ / pos_.y;

		float size = 1.0f;

		vertex vertices[] =
		{
			{ -size,	-size,	size,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f  },
			{ -size,	size,	size,		0.0f, 1.0f,		0.0f, 0.0f, 1.0f  },
			{ size,		size,	size,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f  },
			{ -size,	-size,	size,		0.0f, 0.0f,		0.0f, 0.0f, 1.0f  },
			{ size,		size,	size,		1.0f, 1.0f,		0.0f, 0.0f, 1.0f  },
			{ size,		-size,	size,		1.0f, 0.0f,		0.0f, 0.0f, 1.0f  },

			{ -size,	-size,	-size,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f  },
			{ -size,	size,	-size,		1.0f, 0.0f,		-1.0f, 0.0f, 0.0f  },
			{ -size,	size,	size,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f  },
			{ -size,	-size,	-size,		0.0f, 0.0f,		-1.0f, 0.0f, 0.0f  },
			{ -size,	size,	size,		1.0f, 1.0f,		-1.0f, 0.0f, 0.0f  },
			{ -size,	-size,	size,		0.0f, 1.0f,		-1.0f, 0.0f, 0.0f  },

			{ size,		-size,	-size,		1.0f, 0.0f,		0.0f, 0.0f, -1.0f  },
			{ size,		size,	-size,		1.0f, 1.0f,		0.0f, 0.0f, -1.0f  },
			{ -size,	size,	-size,		0.0f, 1.0f,		0.0f, 0.0f, -1.0f  },
			{ size,		-size,	-size,		1.0f, 0.0f,		0.0f, 0.0f, -1.0f  },
			{ -size,	size,	-size,		0.0f, 1.0f,		0.0f, 0.0f, -1.0f  },
			{ -size,	-size,	-size,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f  },

			{ size,		-size,	size,		0.0f, 1.0f,		1.0f, 0.0f, 0.0f  },
			{ size,		size,	size,		1.0f, 1.0f,		1.0f, 0.0f, 0.0f  },
			{ size,		size,	-size,		1.0f, 0.0f,		1.0f, 0.0f, 0.0f  },
			{ size,		-size,	size,		0.0f, 1.0f,		1.0f, 0.0f, 0.0f  }, 
			{ size,		size,	-size,		1.0f, 0.0f,		1.0f, 0.0f, 0.0f  },
			{ size,		-size,	-size,		0.0f, 0.0f,		1.0f, 0.0f, 0.0f  },

			{ -size,	size,	size,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f  }, 
			{ -size,	size,	-size,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f  },
			{ size,		size,	-size,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f  },
			{ -size,	size,	size,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f  },    
			{ size,		size,	-size,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f  },
			{ size,		size,	size,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f  },

			{ -size,	-size,	-size,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f  },
			{ -size,	-size,	size,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f  },
			{ size,		-size,	size,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f  },
			{ -size,	-size,	-size,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f  }, // Triangle 2, side 6    
			{ size,		-size,	size,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f  },
			{ size,		-size,	-size,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f  },
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
		program_.set_uniform_vec4("mod_color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		program_.set_uniform_vec3("light_color", glm::vec3(1.0f, 1.0f, 1.0f));
		program_.set_uniform_vec3("light_pos", glm::vec3(0.0f, 0.0f, 5.0f));

		format_.add_attribute(0, 3, GL_FLOAT, false);
		format_.add_attribute(1, 2, GL_FLOAT, false);
		format_.add_attribute(2, 3, GL_FLOAT, false);
		

		if (!texture_.create(texture_Path))
		{
			return false;
		}

		if (!sampler_.create(GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE)) {
			return false;
		}

		return true;
	}

	void Celestial::render(float dt)
	{
		glm::vec3 origin;
		if (parent_ != nullptr)
			origin = parent_->position_;
		else
			origin = glm::vec3(0.0f);


		glm::mat4 world = glm::mat4(1.0f);
		world[3][0] = origin.x; world[3][1] = origin.y; world[3][2] = origin.z;


		//world = glm::translate(world, origin);
		world = glm::rotate(world,
							rotation_Parent_,
							glm::vec3(0.0f, 0.0f, 1.0f));
		world = glm::translate(world,pos_);
		world = glm::rotate(world,
							rotation_Self_,
							glm::vec3(0.4f, 0.69f, 0.0f));
		
		world = glm::scale(world, scale_);

		rotation_Parent_ += dt * (travel_Angle_ * 10);
		rotation_Self_ += dt;


		position_ = glm::vec3(world[3][0], world[3][1], world[3][2]);

		glm::vec3 light_pos = glm::vec3(0.0f, 0.0f, 15.0f);

		program_.bind();
		program_.set_uniform_mat4("projection", camera_->projection_); // new matrices
		program_.set_uniform_mat4("view", camera_->view_);
		program_.set_uniform_mat4("world", world);



		program_.set_uniform_vec3("light_pos", light_pos);

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

	void Celestial::render()
	{
	}

	void Celestial::destroy()
	{

	}

};