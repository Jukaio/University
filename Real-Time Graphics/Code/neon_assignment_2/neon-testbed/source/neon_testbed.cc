// neon_testbed.cc

#include "neon_testbed.h"
#include <cassert>
#include <math.h>


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

		Change_Light_Color(glm::vec3(1.0f, 1.0f, 1.0f));
		Change_Light_Position(glm::vec3(0.0f, 0.0f, 15.0f));
		return true;
	}

	void testbed::Change_Light_Color(glm::vec3 color)
	{
		// Change light color and position
		for (auto&& celestial : celestials_)
		{
			celestial.Set_Light_Color(color);
			red_ = color.x;
			green_ = color.y;
			blue_ = color.b;
		}
	}
	void testbed::Change_Light_Position(glm::vec3 pos)
	{
		// Change light color and position
		for (auto&& celestial : celestials_)
		{
			celestial.Set_Light_Pos(pos);
			light_x_ = pos.x;
			light_y_ = pos.y;
			light_z_ = pos.z;
		}
	}

	void testbed::Do_Action(keycode key, float& variable_to_change, bool go_up, bool is_color) // 1 or -1
	{
		if (keyboard_.is_down(key))
		{
			switch (is_color)
			{
				case true:
					if (go_up)
					{
						if (variable_to_change <= 1)
						{
							variable_to_change += 0.02f;
							Change_Light_Color(glm::vec3(red_, green_, blue_));
						}
					}
					else
					{
						if (variable_to_change >= 0)
						{
							variable_to_change -= 0.02f;
							Change_Light_Color(glm::vec3(red_, green_, blue_));
						}
					}
					break;

				case false:
					if (go_up)
					{
						variable_to_change += 0.5f;
						Change_Light_Position(glm::vec3(light_x_, light_y_, light_z_));

					}
					else
					{

						variable_to_change -= 0.5f;
						Change_Light_Position(glm::vec3(light_x_, light_y_, light_z_));

					}
					break;
			}
		}
	}

    void testbed::exit() {
    }

    bool testbed::tick(const time& dt) {
        if (keyboard_.is_pressed(KEYCODE_ESCAPE)) {
            return false;
        }
		/* Change Light Data */
		// Change Color
		// Red
		Do_Action(KEYCODE_F, red_, true);
		Do_Action(KEYCODE_V, red_, false);
		// Green
		Do_Action(KEYCODE_G, green_, true);
		Do_Action(KEYCODE_B, green_, false);
		// Blue
		Do_Action(KEYCODE_H, blue_, true);
		Do_Action(KEYCODE_N, blue_, false);

		// Change Position
		// x
		Do_Action(KEYCODE_LEFT, light_x_, false, false);
		Do_Action(KEYCODE_RIGHT, light_x_, true, false);
		// y
		Do_Action(KEYCODE_SPACE, light_y_, true, false);
		Do_Action(KEYCODE_C, light_y_, false, false);
		// z
		Do_Action(KEYCODE_UP, light_z_, false, false);
		Do_Action(KEYCODE_DOWN, light_z_, true, false);
	    /* End Change Light Data */

        controller_.update(dt); // run controller update, duh

        string mouseX = std::to_string(mouse_.x_); // just me getting debug data
        string mouseY = std::to_string(mouse_.y_);

        string text = "FPS: " + std::to_string((int)(1.0f / dt.as_seconds()));

        font_.render(2.0f, 2.0f, text);

        glClearColor(0.1f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        skybox_.render(camera_); // Render skybox


		for (int i = 0; i < 4; i++)
			celestials_[i].render(dt.as_seconds());

        font_.flush();

        return true;
    }
} // !neon

