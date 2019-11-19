// HeliumSandboxApp.cc

#include "HeliumSandboxApp.h"

// @sandbox-app
SandboxApp::SandboxApp()
{
}

bool SandboxApp::init(const FileSystem *file_system)
{
   // note: set primitive collision color
   intersect_color_ = RED;

   // note: init primitives
   segment_ = { { -500.0f, 50.0f }, { -450.0f, -50.0f } };
   circle_ = { { -200.0f, 0.0f,}, 50.0f };
   aligned_box_ = { { 200.0f, 0.0f }, { 100.0f, 60.0f } };
   oriented_box_ = { { 500.0f, 0.0f }, { 60.0f, 120.0f }, 0.0f };

   // note: init interaction primitives
   interaction_.point_ = {};
   interaction_.segment_ = {};
   interaction_.circle_ = { {}, 50.0f };
   interaction_.aligned_box_ = { {}, { 50.0f, 50.0f } };
   interaction_.oriented_box_ = { {}, { 60.0f, 30.0f }, 32.0f };

   return true;
}

void SandboxApp::exit()
{
}

bool SandboxApp::tick(double apptime,
                  float deltatime,
                  const Mouse *mouse, 
                  const Keyboard *keyboard)
{
   // @store-mouse-position
   mouse_position_ = { mouse->x_, mouse->y_ };

   // note: selection mode
   if (keyboard->key_[Keyboard::KEY_0].pressed_)
      selection_mode_ = SelectionMode::SM_NONE;
   else if (keyboard->key_[Keyboard::KEY_1].pressed_)
      selection_mode_ = SelectionMode::SM_POINT;
   else if (keyboard->key_[Keyboard::KEY_2].pressed_)
      selection_mode_ = SelectionMode::SM_SEGMENT;
   else if (keyboard->key_[Keyboard::KEY_3].pressed_)
      selection_mode_ = SelectionMode::SM_CIRCLE;
   else if (keyboard->key_[Keyboard::KEY_4].pressed_)
      selection_mode_ = SelectionMode::SM_AABB;
   else if (keyboard->key_[Keyboard::KEY_5].pressed_)
      selection_mode_ = SelectionMode::SM_OBB;

   oriented_box_.rotation_ = 20.0f * (float)apptime;

   update_interaction();

   return !keyboard->key_[Keyboard::ESCAPE].pressed_;
}

void SandboxApp::draw(const Renderer *renderer)
{
   renderer_ = renderer;
   renderer_->clear(WHITE);

   draw_grid_center();
   draw_primitives();
   draw_debug_text();
}

void SandboxApp::update_interaction()
{
   intersect_color_ = RED;
   for (int index = 0; index < SM_COUNT; index++)
      colors_[index] = BLUE;

   Vector2 mouse_point = Vector2(float(mouse_position_.x_ - 640),
                                 float(360 - mouse_position_.y_));


   SelectionMode mode = SelectionMode::SM_NONE;
   switch (selection_mode_)
   {
      case SelectionMode::SM_POINT:
      {
         interaction_.point_ = mouse_point;
		 if (Collision::intersect(interaction_.point_, segment_))
			 mode = SM_SEGMENT;
         else if (Collision::intersect(interaction_.point_, circle_))
            mode = SM_CIRCLE;
         else if (Collision::intersect(interaction_.point_, aligned_box_))
            mode = SM_AABB;
         else if (Collision::intersect(oriented_box_, interaction_.point_))
            mode = SM_OBB;
      } break;
      case SelectionMode::SM_SEGMENT:
      {
         interaction_.segment_.start_ = mouse_point + Vector2( 100.0f, 100.0f);
         interaction_.segment_.end_   = mouse_point + Vector2(-100.0f, -100.0f);
         
         if (Collision::intersect(interaction_.segment_, segment_))
            mode = SM_SEGMENT;
         else if (Collision::intersect(interaction_.segment_, circle_))
            mode = SM_CIRCLE;
         else if (Collision::intersect(interaction_.segment_, aligned_box_))
            mode = SM_AABB;
         else if (Collision::intersect(oriented_box_, interaction_.segment_))
            mode = SM_OBB;
      } break;
      case SelectionMode::SM_CIRCLE:
      {
         interaction_.circle_.center_ = mouse_point;

         if (Collision::intersect(interaction_.circle_, segment_))
            mode = SM_SEGMENT;
         else if (Collision::intersect(interaction_.circle_, circle_))
            mode = SM_CIRCLE;
         else if (Collision::intersect(interaction_.circle_, aligned_box_))
            mode = SM_AABB;
         else if (Collision::intersect(oriented_box_, interaction_.circle_))
            mode = SM_OBB;
      } break;
      case SelectionMode::SM_AABB:
      {
         interaction_.aligned_box_.center_ = mouse_point;

         if (Collision::intersect(interaction_.aligned_box_, segment_))
            mode = SM_SEGMENT;
         else if (Collision::intersect(interaction_.aligned_box_, circle_))
            mode = SM_CIRCLE;
         else if (Collision::intersect(interaction_.aligned_box_, aligned_box_))
            mode = SM_AABB;
         else if (Collision::intersect(oriented_box_, interaction_.aligned_box_))
            mode = SM_OBB;
      } break;
      case SelectionMode::SM_OBB:
      {
         interaction_.oriented_box_.center_ = mouse_point;

         if (Collision::intersect(interaction_.oriented_box_, segment_))
            mode = SM_SEGMENT;
         else if (Collision::intersect(interaction_.oriented_box_, circle_))
            mode = SM_CIRCLE;
         else if (Collision::intersect(interaction_.oriented_box_, aligned_box_))
            mode = SM_AABB;
         else if (Collision::intersect(interaction_.oriented_box_, oriented_box_))
            mode = SM_OBB;
      } break;
   }

   if (mode != SelectionMode::SM_NONE)
   {
      intersect_color_ = GREEN;
      colors_[mode] = GREEN;
   }
}

void SandboxApp::draw_segment(const LineSegment &segment, const Color &color) const
{
   renderer_->draw_line(segment.start_, segment.end_, color);
}

void SandboxApp::draw_circle(const BoundingCircle &circle, const Color &color) const
{
   renderer_->draw_circle(circle.center_, circle.radius_, color);
}

void SandboxApp::draw_aligned_box(const AxisAlignedBoundingBox &aligned_box, const Color &color) const
{
   renderer_->draw_rectangle(aligned_box.center_ - aligned_box.half_,
                             aligned_box.center_ + aligned_box.half_, 
                             color);
}

void SandboxApp::draw_oriented_box(const ObjectOrientedBoundingBox &oriented_box, const Color &color) const
{
   Matrix3 r = Matrix3::rotate(oriented_box.rotation_);
   Matrix3 t = Matrix3::translate(oriented_box.center_);
   Matrix3 m = t * r;

   Vector2 corners[5] =
   {
      { -oriented_box.half_.x_, -oriented_box.half_.y_ },
      {  oriented_box.half_.x_, -oriented_box.half_.y_ },
      {  oriented_box.half_.x_,  oriented_box.half_.y_ },
      { -oriented_box.half_.x_,  oriented_box.half_.y_ },
      { -oriented_box.half_.x_, -oriented_box.half_.y_ },
   };

   for (int index = 0; index < 5; index++)
      corners[index] = m.transform(corners[index]);

   renderer_->draw_line_strip(5, corners, color);
}

void SandboxApp::draw_grid_center() const
{
   renderer_->set_screen_origin(Renderer::CENTER);
   for (int y_index = -300; y_index <= 300; y_index += 100)
      renderer_->draw_line({ -5.0f, y_index * 1.0f }, { 5.0f, y_index * 1.0f }, LIGHT_GRAY);
   renderer_->draw_line({ 0.0f, -360.0f }, { 0.0f, 360.0f }, LIGHT_GRAY);

   for (int x_index = -600; x_index <= 600; x_index += 100)
      renderer_->draw_line({ x_index * 1.0f, -5.0f }, { x_index * 1.0f, 5.0f }, LIGHT_GRAY);
   renderer_->draw_line({ -640.0f, 0.0f }, { 640.0f, 0.0f }, LIGHT_GRAY);
}

void SandboxApp::draw_primitives() const
{
   switch (selection_mode_)
   {
      case SelectionMode::SM_POINT:
      {
         renderer_->draw_point(interaction_.point_, intersect_color_);
      } break;
      case SelectionMode::SM_SEGMENT:
      {
         draw_segment(interaction_.segment_, intersect_color_);
      } break;
      case SelectionMode::SM_CIRCLE:
      {
         draw_circle(interaction_.circle_, intersect_color_);
      } break;
      case SelectionMode::SM_AABB:
      {
         draw_aligned_box(interaction_.aligned_box_, intersect_color_);
      } break;
      case SelectionMode::SM_OBB:
      {
         draw_oriented_box(interaction_.oriented_box_, intersect_color_);
      } break;
   }

   draw_segment(segment_, colors_[SM_SEGMENT]);
   draw_circle(circle_, colors_[SM_CIRCLE]);
   draw_aligned_box(aligned_box_, colors_[SM_AABB]);
   draw_oriented_box(oriented_box_, colors_[SM_OBB]);
}

void SandboxApp::draw_debug_text() const
{
   const char *selection_mode_string[] =
   {
      "SM_NONE",
      "SM_POINT",
      "SM_SEGMENT",
      "SM_CIRCLE",
      "SM_AABB",
      "SM_OOB",
   };

   int mouse_x = mouse_position_.x_ - 640;
   int mouse_y = 360 - mouse_position_.y_;

   renderer_->set_screen_origin(Renderer::TOP_LEFT);
   renderer_->draw_text({ 2,  2 }, BLACK, "X: %d Y: %d", mouse_x, mouse_y);
   renderer_->draw_text({ 2, 12 }, BLACK, "MODE: %s", selection_mode_string[selection_mode_]);
}

namespace Helium
{
   Application *create_application()
   {
      return new SandboxApp;
   }
}
