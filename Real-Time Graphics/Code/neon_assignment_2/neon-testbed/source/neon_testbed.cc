// neon_testbed.cc

#include "neon_testbed.h"
#include <cassert>


namespace neon {
    // note: application factory
    application* application::create(int& width, int& height, string& title) {
        width = 1280; height = 720;
        title = "neon-testbed";
        return new testbed;
    }

    // note: derived application class
    testbed::testbed()
        : rotation_(0.0f)
        , controller_(camera_, keyboard_, mouse_) // controller demands to have these, so we have to send it
    {
    }

	bool testbed::enter() {
		GLuint vao = 0; // vertex array object
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		if (!font_.create())
		{
			return false;
		}

		if (!skybox_.create()) {
			return false;
		}

		if (!terrain_.create("assets/heightmap/heightmap.png",
			"assets/heightmap/texture.png"))
		{
			return false;
		}

		world_ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -20.0f));
		world_ = glm::scale(world_, glm::vec3(0.01f));


		camera_.set_perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 1000.0f); //Just changing it so that our perspective is controlled by the camera instead.
		camera_.update();
		camera_.forward(50.0f);
		camera_.sidestep(0.0f);
		terrain_.camera_ = &camera_;

		celestials_[0].create(camera_,
							  nullptr,
							  "assets/Planet_Textures/sun.jpg",
							  glm::vec3(0.0f, 0.0f, 0.0f), //Position
							  glm::vec3(4.0f, 4.0f, 4.0f), 1.0f);//Scale

		celestials_[1].create(camera_,
							  &celestials_[0],
							  "assets/Planet_Textures/mercury.jpg",
							  glm::vec3(0.0f, 12.0f, 0.0f),
							  glm::vec3(4.0f, 4.0f, 4.0f), 1.0f);

		celestials_[2].create(camera_,
							  &celestials_[0],
							  "assets/Planet_Textures/venus.jpg",
							  glm::vec3(0.0f, 24.0f, 0.0f),
							  glm::vec3(4.0f, 4.0f, 4.0f), 1.0f);;

		celestials_[3].create(camera_,
							  &celestials_[0],
							  "assets/Planet_Textures/earth.jpg",
							  glm::vec3(0.0f, 32.0f, 0.0f),
							  glm::vec3(4.0f, 4.0f, 4.0f), 1.0f);

		return true;
	}

    void testbed::exit() {
    }

    bool testbed::tick(const time& dt) {
        if (keyboard_.is_pressed(KEYCODE_ESCAPE)) {
            return false;
        }

        controller_.update(dt); // run controller update, duh

        string mouseX = std::to_string(mouse_.x_); // just me getting debug data
        string mouseY = std::to_string(mouse_.y_);

        string text = "dt: " + std::to_string((int)dt.as_milliseconds());

        font_.render(2.0f, 2.0f, text);

        glClearColor(0.1f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        skybox_.render(camera_); // Render skybox


		for (int i = 0; i < 10; i++)
			celestials_[i].render(dt.as_seconds());

        //program_.bind();
        //program_.set_uniform_mat4("projection", camera_.projection_); // new matrices
        //program_.set_uniform_mat4("view", camera_.view_);
        //program_.set_uniform_mat4("world", world);
        //vbo_.bind();
        //format_.bind();
        //texture_.bind();
        //sampler_.bind();

        //glEnable(GL_DEPTH_TEST);

        //glEnable(GL_CULL_FACE); // remove this to render the inside of the cube, or comment it out
        //glCullFace(GL_BACK);
        //glFrontFace(GL_CW);

        //glEnable(GL_BLEND);
        //glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
        //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
        //glDrawArrays(GL_TRIANGLES, 0, 99);

        font_.flush();

        return true;
    }
} // !neon

