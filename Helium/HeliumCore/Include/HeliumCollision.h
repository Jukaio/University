// HeliumCollision.h

#ifndef HELIUM_COLLISION_H_INCLUDED
#define HELIUM_COLLISION_H_INCLUDED

#include <HeliumCore.h>

namespace Helium
{
   struct LineSegment
   {
      Vector2 start_;
      Vector2 end_;
   };

   struct BoundingCircle
   {
      Vector2 center_;
      float radius_;
   };

   struct AxisAlignedBoundingBox
   {
      Vector2 center_;
      Vector2 half_;
   };

   struct ObjectOrientedBoundingBox
   {
      Vector2 center_;
      Vector2 half_;
      float rotation_;
   };

   namespace Collision
   {
      // TODO: PASS
      bool intersect(const Vector2 &point, const BoundingCircle &circle);
      bool intersect(const Vector2 &point, const AxisAlignedBoundingBox &aligned_box);

	  bool intersect(const LineSegment& segment, const Vector2 &point);
	  bool intersect(const Vector2& point, const LineSegment& segment);
      bool intersect(const LineSegment &segment, const BoundingCircle &circle);

      bool intersect(const BoundingCircle &circle, const Vector2 &point);
      bool intersect(const BoundingCircle &circle, const LineSegment &segment);
      bool intersect(const BoundingCircle &circle_a, const BoundingCircle &circle_b);
      bool intersect(const BoundingCircle &circle, const AxisAlignedBoundingBox &aligned_box);

      bool intersect(const AxisAlignedBoundingBox &aligned_box, const Vector2 &point);
      bool intersect(const AxisAlignedBoundingBox &aligned_box, const BoundingCircle &circle);
      bool intersect(const AxisAlignedBoundingBox &aligned_box_a, const AxisAlignedBoundingBox &aligned_box_b);

      // TODO: PASS WITH DISTINCTION
      bool intersect(const LineSegment &segment_a, const LineSegment &segment_b);
      bool intersect(const LineSegment &segment, const AxisAlignedBoundingBox &aligned_box);
      bool intersect(const AxisAlignedBoundingBox &aligned_box, const LineSegment &segment);

      bool intersect(const ObjectOrientedBoundingBox &oriented_box, const Vector2 &point);
      bool intersect(const ObjectOrientedBoundingBox &oriented_box, const LineSegment &segment);
      bool intersect(const ObjectOrientedBoundingBox &oriented_box, const BoundingCircle &circle);
      bool intersect(const ObjectOrientedBoundingBox &oriented_box, const AxisAlignedBoundingBox &aligned_box);
      bool intersect(const ObjectOrientedBoundingBox &oriented_box_a, const ObjectOrientedBoundingBox &oriented_box_b);
   } // Collision

} // Helium

#endif // HELIUM_COLLISION_H_INCLUDED
