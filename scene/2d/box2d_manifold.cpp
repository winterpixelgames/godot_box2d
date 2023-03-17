#include "box2d_manifold.h"

#include "../../util/box2d_types_converter.h"

void Box2DManifold::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_local_normal"), &Box2DManifold::get_local_normal);
	ClassDB::bind_method(D_METHOD("get_local_point"), &Box2DManifold::get_local_point);
	ClassDB::bind_method(D_METHOD("get_type"), &Box2DManifold::get_type);
	ClassDB::bind_method(D_METHOD("get_point_count"), &Box2DManifold::get_point_count);
	ClassDB::bind_method(D_METHOD("get_normal"), &Box2DManifold::get_normal);
	ClassDB::bind_method(D_METHOD("get_point", "index"), &Box2DManifold::get_point);
	ClassDB::bind_method(D_METHOD("get_separation", "index"), &Box2DManifold::get_separation);

	BIND_ENUM_CONSTANT(TYPE_CIRCLES);
	BIND_ENUM_CONSTANT(TYPE_SDF);
	BIND_ENUM_CONSTANT(TYPE_FACEA);
	BIND_ENUM_CONSTANT(TYPE_FACEB);
}

void Box2DManifold::_notification(int p_what) {
}

Vector2 Box2DManifold::get_local_normal() const {
	return Vector2(_manifold->localNormal.x, _manifold->localNormal.y);
}

Vector2 Box2DManifold::get_local_point() const {
	return b2_to_gd(_manifold->localPoint);
}

Box2DManifold::Type Box2DManifold::get_type() const {
	return static_cast<Box2DManifold::Type>(_manifold->type);
}

int Box2DManifold::get_point_count() const {
	return _manifold->pointCount;
}

Vector2 Box2DManifold::get_normal() const {
	return Vector2(_world_manifold.normal.x, _world_manifold.normal.y);
}

Vector2 Box2DManifold::get_point(const int p_idx) const {
	ERR_FAIL_COND_V(p_idx < 0 || p_idx >= b2_maxManifoldPoints, Vector2());
	ERR_FAIL_COND_V(p_idx >= _manifold->pointCount, Vector2());
	return b2_to_gd(_world_manifold.points[p_idx]);
}

float Box2DManifold::get_separation(const int p_idx) const {
	ERR_FAIL_COND_V(p_idx < 0 || p_idx >= b2_maxManifoldPoints, 0.0);
	ERR_FAIL_COND_V(p_idx >= _manifold->pointCount, 0.0);
	return B2_TO_GD * _world_manifold.separations[p_idx];
}

Box2DManifold::Box2DManifold() {
}

Box2DManifold::Box2DManifold(b2Manifold *p_manifold) {
	_manifold = p_manifold;
}

Box2DManifold::~Box2DManifold() {
}
