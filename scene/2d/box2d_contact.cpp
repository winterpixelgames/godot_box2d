#include "box2d_contact.h"
#include "box2d_fixtures.h"
#include <core/engine.h>

void Box2DContact::_bind_methods() {
	ClassDB::bind_method(D_METHOD("is_touching"), &Box2DContact::is_touching);
	ClassDB::bind_method(D_METHOD("set_enabled", "enabled"), &Box2DContact::set_enabled);
	ClassDB::bind_method(D_METHOD("is_enabled"), &Box2DContact::is_enabled);
	
	ClassDB::bind_method(D_METHOD("get_fixture_a"), &Box2DContact::get_fixture_a);
	ClassDB::bind_method(D_METHOD("get_child_index_a"), &Box2DContact::get_child_index_a);
	ClassDB::bind_method(D_METHOD("get_fixture_b"), &Box2DContact::get_fixture_b);
	ClassDB::bind_method(D_METHOD("get_child_index_b"), &Box2DContact::get_child_index_b);
	ClassDB::bind_method(D_METHOD("set_friction", "friction"), &Box2DContact::set_friction);
	ClassDB::bind_method(D_METHOD("get_friction"), &Box2DContact::get_friction);
	ClassDB::bind_method(D_METHOD("reset_friction"), &Box2DContact::reset_friction);
	ClassDB::bind_method(D_METHOD("set_restitution", "restitution"), &Box2DContact::set_restitution);
	ClassDB::bind_method(D_METHOD("get_restitution"), &Box2DContact::get_restitution);
	ClassDB::bind_method(D_METHOD("reset_restitution"), &Box2DContact::reset_restitution);
	ClassDB::bind_method(D_METHOD("set_restitution_threshold", "threshold"), &Box2DContact::set_restitution_threshold);
	ClassDB::bind_method(D_METHOD("get_restitution_threshold"), &Box2DContact::get_restitution_threshold);
	ClassDB::bind_method(D_METHOD("reset_restitution_threshold"), &Box2DContact::reset_restitution_threshold);
	ClassDB::bind_method(D_METHOD("set_tangent_speed", "speed"), &Box2DContact::set_tangent_speed);
	ClassDB::bind_method(D_METHOD("get_tangent_speed"), &Box2DContact::get_tangent_speed);

	ClassDB::bind_method(D_METHOD("get_manifold"), &Box2DContact::get_manifold);
}

void Box2DContactImpulse::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_count"), &Box2DContactImpulse::get_count);
	ClassDB::bind_method(D_METHOD("get_normal_impulse", "index"), &Box2DContactImpulse::get_normal_impulse);
	ClassDB::bind_method(D_METHOD("get_tangent_impulse", "index"), &Box2DContactImpulse::get_tangent_impulse);
}
