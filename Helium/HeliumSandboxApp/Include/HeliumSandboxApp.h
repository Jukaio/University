// HeliumSandboxApp.h

#include <HeliumCore.h>
#include <HeliumCollision.h>

#include <vector>

using namespace Helium;

// @pre-defined-colors
constexpr const Color BLACK      = { 0x00, 0x00, 0x00, 0xff };
constexpr const Color DARK_GRAY  = { 0x44, 0x44, 0x44, 0xff };
constexpr const Color GRAY       = { 0x88, 0x88, 0x88, 0xff };
constexpr const Color LIGHT_GRAY = { 0xbb, 0xbb, 0xbb, 0xff };
constexpr const Color WHITE      = { 0xff, 0xff, 0xff, 0xff };
constexpr const Color RED        = { 0xff, 0x00, 0x00, 0xff };
constexpr const Color GREEN      = { 0x00, 0xff, 0x00, 0xff };
constexpr const Color BLUE       = { 0x00, 0x00, 0xff, 0xff };
constexpr const Color MAGENTA    = { 0xff, 0x00, 0xff, 0xff };

// @helper-structs

// @main-app
struct SandboxApp : Application
{
   SandboxApp();

   virtual bool init(const FileSystem *file_system);
   virtual void exit();
   virtual bool tick(double apptime,
                     float deltatime,
                     const Mouse *mouse,
                     const Keyboard *keyboard);
   virtual void draw(const Renderer *renderer);

   // @app-enums
   enum SelectionMode
   {
      SM_NONE,
      SM_POINT,
      SM_SEGMENT,
      SM_CIRCLE,
      SM_AABB,
      SM_OBB,
      SM_COUNT,
   };

   // @interaction-helpers
   void update_interaction();

   // @draw-helpers
   void draw_segment(const LineSegment &segment, const Color &color) const;
   void draw_circle(const BoundingCircle &circle, const Color &color) const;
   void draw_aligned_box(const AxisAlignedBoundingBox &aligned_box, const Color &color) const;
   void draw_oriented_box(const ObjectOrientedBoundingBox &oriented_box, const Color &color) const;
   void draw_grid_center() const;
   void draw_primitives() const;
   void draw_debug_text() const;

   // @members
   const Renderer *renderer_;
   Point mouse_position_;
   SelectionMode selection_mode_ = SM_NONE;
   
   Color intersect_color_;
   LineSegment segment_;
   BoundingCircle circle_;
   AxisAlignedBoundingBox aligned_box_;
   ObjectOrientedBoundingBox oriented_box_;
   Color colors_[SM_COUNT];
   struct
   {
      Vector2 point_;
      LineSegment segment_;
      BoundingCircle circle_;
      AxisAlignedBoundingBox aligned_box_;
      ObjectOrientedBoundingBox oriented_box_;
   } interaction_;
};

