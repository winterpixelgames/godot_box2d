#include "box2d_manifold.h"

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
