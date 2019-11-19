// HeliumCollision.cc

#include "HeliumCore.h"
#include "HeliumCollision.h"

#include <math.h>

namespace Helium
{
   namespace Collision
   {
      // @constants
      constexpr const float EPSILON = 0.0001f;

      // @helper-functions
      template <typename T> 
      T min(T a, T b) 
      { 
         return a < b ? a : b; 
      }

      template <typename T> 
      T max(T a, T b) 
      { 
         return a > b ? a : b; 
      }

      template <typename T> 
      T clamp(T v, T a, T b) 
      { 
         return v < a ? a : v > b ? b : v; 
      }


	  //Segment-Point Intersection
	  bool intersect(const LineSegment& segment, const Vector2& point)
	  {
		  float distance_start = point.distance(segment.start_);
		  float distance_end = point.distance(segment.end_);

		  float length = segment.start_.distance(segment.end_);

		  if (distance_start + distance_end >= length - EPSILON &&
			  distance_start + distance_end <= length + EPSILON)
			  return true;
		  return false;
	  }

	  bool intersect(const Vector2& point, const LineSegment& segment)
	  {
		  return intersect(segment, point);
	  }


      // TODO: PASS
      bool intersect(const Vector2 &point, const BoundingCircle &circle)
      {
		  Vector2 x = point - circle.center_;
		  float distance = x.length();

		  if (distance <= circle.radius_)
			  return true;

         return false;
      }

      bool intersect(const Vector2 &point, const AxisAlignedBoundingBox &aligned_box)
      {
		  if (point.x_ >= aligned_box.center_.x_ - aligned_box.half_.x_ &&
			  point.x_ <= aligned_box.center_.x_ + aligned_box.half_.x_ &&
			  point.y_ >= aligned_box.center_.y_ - aligned_box.half_.y_ &&
			  point.y_ <= aligned_box.center_.y_ + aligned_box.half_.y_)
			  return true;
         return false;
      }

      bool intersect(const LineSegment &segment, const BoundingCircle &circle)
      {
		  if (intersect(segment.start_, circle) || intersect(segment.end_, circle))
			 return true;

		  float length = Vector2(segment.start_.x_ - segment.end_.x_, segment.start_.y_ - segment.end_.y_).length();

		  BoundingCircle circle_local({ circle.center_ - segment.start_, circle.radius_ });
		  LineSegment segment_local({ segment.start_ - segment.start_, segment.end_ - segment.start_ });
		  float dot = circle_local.center_.dot(segment_local.end_.unit());

		  Vector2 closest = segment.start_ + (segment_local.end_.unit() * dot);

		  if (!intersect(closest, segment))
			  return false;

		  Vector2 y = closest - circle.center_;
		  float distance = y.length();
		  if (distance <= circle.radius_)
			  return true;
         return false;
      }

      bool intersect(const BoundingCircle &circle, const Vector2 &point)
      {
         return intersect(point, circle);
      }

      bool intersect(const BoundingCircle &circle, const LineSegment &segment)
      {
         return intersect(segment, circle);
      }

      bool intersect(const BoundingCircle &circle_a, const BoundingCircle &circle_b)
      {
		  Vector2 x = circle_a.center_ - circle_b.center_;
		  float distance = x.length();

		  if (distance <= circle_a.radius_ + circle_b.radius_)
			  return true;

         return false;
      }

      bool intersect(const BoundingCircle &circle, const AxisAlignedBoundingBox &aligned_box)
      {
		  Vector2 temp(circle.center_);

		  if (circle.center_.x_ < aligned_box.center_.x_ - aligned_box.half_.x_)
		  {
			  temp.x_ = aligned_box.center_.x_ - aligned_box.half_.x_;
		  }
		  else if (circle.center_.x_ > aligned_box.center_.x_ + aligned_box.half_.x_)
		  {
			  temp.x_ = aligned_box.center_.x_ + aligned_box.half_.x_;
		  }

		  if (circle.center_.y_ < aligned_box.center_.y_ - aligned_box.half_.y_)
		  {
			  temp.y_ = aligned_box.center_.y_ - aligned_box.half_.y_;
		  }
		  else if (circle.center_.y_ > aligned_box.center_.y_ + aligned_box.half_.y_)
		  {
			  temp.y_ = aligned_box.center_.y_ + aligned_box.half_.y_;
		  }

		  Vector2 x = circle.center_ - temp;
		  float distance = x.length();

		  if (distance <= circle.radius_)
			  return true;

         return false;
      }

      bool intersect(const AxisAlignedBoundingBox &aligned_box, const Vector2 &point)
      {
         return intersect(point, aligned_box);
      }

      bool intersect(const AxisAlignedBoundingBox &aligned_box, const BoundingCircle &circle)
      {
         return intersect(circle, aligned_box);
      }

      bool intersect(const AxisAlignedBoundingBox &aligned_box_a, const AxisAlignedBoundingBox &aligned_box_b)
      {
		  if (aligned_box_a.center_.x_ + aligned_box_a.half_.x_ >= aligned_box_b.center_.x_ - aligned_box_b.half_.x_ &&
			  aligned_box_a.center_.x_ - aligned_box_a.half_.x_ <= aligned_box_b.center_.x_ + aligned_box_b.half_.x_ &&
			  aligned_box_a.center_.y_ + aligned_box_a.half_.y_ >= aligned_box_b.center_.y_ - aligned_box_b.half_.y_ &&
			  aligned_box_a.center_.y_ - aligned_box_a.half_.y_ <= aligned_box_b.center_.y_ + aligned_box_b.half_.y_)
			  return true;

         return false;
      }

      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      // !! TODO: PASS WITH DISTINCTION !!
      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      bool intersect(const LineSegment &segment_a, const LineSegment &segment_b)
      {
         return false;
      }

      bool intersect(const AxisAlignedBoundingBox &aligned_box, const LineSegment &segment)
      {
         return false;
      }

      bool intersect(const LineSegment &segment, const AxisAlignedBoundingBox &aligned_box)
      {
         return false;
      }

      bool intersect(const ObjectOrientedBoundingBox &oriented_box, const Vector2 &point)
      {
         return false;
      }

      bool intersect(const ObjectOrientedBoundingBox &oriented_box, const LineSegment &segment)
      {
         return false;
      }

      bool intersect(const ObjectOrientedBoundingBox &oriented_box, const BoundingCircle &circle)
      {
         return false;
      }

      bool intersect(const ObjectOrientedBoundingBox &oriented_box, const AxisAlignedBoundingBox &aligned_box)
      {
         return false;
      }

      bool intersect(const ObjectOrientedBoundingBox &oriented_box_a, const ObjectOrientedBoundingBox &oriented_box_b)
      {
         return false;
      }
   } // Collision
} // Helium

