#include "box2d_contact_immutable.h"
#include "box2d_fixtures.h"
#include <core/engine.h>

void Box2DContactImmutable::_bind_methods() {
	ClassDB::bind_method(D_METHOD("is_touching"), &Box2DContactImmutable::is_touching);
	ClassDB::bind_method(D_METHOD("set_enabled", "enabled"), &Box2DContactImmutable::set_enabled);
	ClassDB::bind_method(D_METHOD("is_enabled"), &Box2DContactImmutable::is_enabled);
	
	ClassDB::bind_method(D_METHOD("get_fixture_a"), &Box2DContactImmutable::get_fixture_a);
	ClassDB::bind_method(D_METHOD("get_child_index_a"), &Box2DContactImmutable::get_child_index_a);
	ClassDB::bind_method(D_METHOD("get_fixture_b"), &Box2DContactImmutable::get_fixture_b);
	ClassDB::bind_method(D_METHOD("get_child_index_b"), &Box2DContactImmutable::get_child_index_b);
	ClassDB::bind_method(D_METHOD("set_friction", "friction"), &Box2DContactImmutable::set_friction);
	ClassDB::bind_method(D_METHOD("get_friction"), &Box2DContactImmutable::get_friction);
	ClassDB::bind_method(D_METHOD("reset_friction"), &Box2DContactImmutable::reset_friction);
	ClassDB::bind_method(D_METHOD("set_restitution", "restitution"), &Box2DContactImmutable::set_restitution);
	ClassDB::bind_method(D_METHOD("get_restitution"), &Box2DContactImmutable::get_restitution);
	ClassDB::bind_method(D_METHOD("reset_restitution"), &Box2DContactImmutable::reset_restitution);
	ClassDB::bind_method(D_METHOD("set_restitution_threshold", "threshold"), &Box2DContactImmutable::set_restitution_threshold);
	ClassDB::bind_method(D_METHOD("get_restitution_threshold"), &Box2DContactImmutable::get_restitution_threshold);
	ClassDB::bind_method(D_METHOD("reset_restitution_threshold"), &Box2DContactImmutable::reset_restitution_threshold);
	ClassDB::bind_method(D_METHOD("set_tangent_speed", "speed"), &Box2DContactImmutable::set_tangent_speed);
	ClassDB::bind_method(D_METHOD("get_tangent_speed"), &Box2DContactImmutable::get_tangent_speed);

}

void Box2DContactImmutable::copy_contact(b2Contact* contact) {
	fixture_a = contact->GetFixtureA()->GetUserData().owner;
	fixture_b = contact->GetFixtureB()->GetUserData().owner;
	child_index_a = contact->GetChildIndexA();
	child_index_b = contact->GetChildIndexB();
	friction = contact->GetFriction();
	// int child_index_a;
	// int child_index_b;
	// float friction;
	// float restitution;
	// float restitution_threshold;
	// float tangent_speed;
	// bool is_touching;

}

Box2DContactImmutable::Box2DContactImmutable() {}

Box2DContactImmutable::~Box2DContactImmutable() {}

Box2DFixture* Box2DContactImmutable::get_fixture_a() {
	return nullptr;
}

int Box2DContactImmutable::get_child_index_a() {
	return 0;
}

Box2DFixture* Box2DContactImmutable::get_fixture_b() {
	return nullptr;
}

int Box2DContactImmutable::get_child_index_b() {
	return 0;
}

bool Box2DContactImmutable::is_touching() {
	return false;
}

float Box2DContactImmutable::get_friction() {
	return friction;
}

float Box2DContactImmutable::get_restitution() {
	return restitution;
}

float Box2DContactImmutable::get_restitution_threshold() {
	return restitution_threshold;
}

float Box2DContactImmutable::get_tangent_speed() {
	return tangent_speed;
}
