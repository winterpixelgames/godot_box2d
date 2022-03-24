#ifndef BOX2D_TYPES_CONVERTER_H
#define BOX2D_TYPES_CONVERTER_H

#include <core/math/transform_2d.h>
#include <core/math/vector2.h>
#include <core/math/vector3.h>
#include <core/typedefs.h>

#include <box2d/b2_collision.h>
#include <box2d/b2_math.h>

/**
* @author Brian Semrau
*
* Conversion functions for switching between Box2D/Godot data structures and units.
*/

extern void load_box2d_cached_conversion_factors();
extern float get_box2d_conversion_factor();
extern float get_box2d_conversion_factor_inv();

#define B2_TO_GD get_box2d_conversion_factor()
#define GD_TO_B2 get_box2d_conversion_factor_inv()

extern void b2_to_gd(b2Vec2 const &inVal, Vector2 &outVal);
extern Vector2 b2_to_gd(b2Vec2 const &inVal);
extern Transform2D b2_to_gd(b2Transform const &inVal);

extern void gd_to_b2(Vector2 const &inVal, b2Vec2 &outVal);
extern b2Vec2 gd_to_b2(Vector2 const &inVal);
extern b2Transform gd_to_b2(Transform2D const &inVal);
extern b2AABB gd_to_b2(Rect2 const &inVal);

#endif // BOX2D_TYPES_CONVERTER_H
