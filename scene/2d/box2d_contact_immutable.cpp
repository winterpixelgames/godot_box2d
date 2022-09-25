#include "box2d_contact_immutable.h"
#include "box2d_fixtures.h"
#include <core/engine.h>

#include "box2d_manifold.h"
#include "box2d_fixtures.h"
#include "box2d_collision_object.h"

void Box2DContactImmutable::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_fixture_a"), &Box2DContactImmutable::get_fixture_a);
	ClassDB::bind_method(D_METHOD("get_child_index_a"), &Box2DContactImmutable::get_child_index_a);
	ClassDB::bind_method(D_METHOD("get_fixture_b"), &Box2DContactImmutable::get_fixture_b);
	ClassDB::bind_method(D_METHOD("get_child_index_b"), &Box2DContactImmutable::get_child_index_b);
	ClassDB::bind_method(D_METHOD("get_friction"), &Box2DContactImmutable::get_friction);
	ClassDB::bind_method(D_METHOD("get_restitution"), &Box2DContactImmutable::get_restitution);
	ClassDB::bind_method(D_METHOD("get_restitution_threshold"), &Box2DContactImmutable::get_restitution_threshold);
	ClassDB::bind_method(D_METHOD("get_tangent_speed"), &Box2DContactImmutable::get_tangent_speed);
	ClassDB::bind_method(D_METHOD("get_is_touching"), &Box2DContactImmutable::get_is_touching);
}

void Box2DContactImmutable::copy_contact(b2Contact* contact) {
	fixture_a = contact->GetFixtureA()->GetUserData().owner;
	fixture_b = contact->GetFixtureB()->GetUserData().owner;
	child_index_a = contact->GetChildIndexA();
	child_index_b = contact->GetChildIndexB();
	friction = contact->GetFriction();
	restitution = contact->GetRestitution();
	restitution_threshold = contact->GetRestitutionThreshold();
	tangent_speed = contact->GetTangentSpeed();
	is_touching = contact->IsTouching();
	// float restitution;
	// float restitution_threshold;
	// float tangent_speed;
	// bool is_touching;

}

Box2DContactImmutable::Box2DContactImmutable() {}

Box2DContactImmutable::~Box2DContactImmutable() {}

Box2DFixture* Box2DContactImmutable::get_fixture_a() {
	return fixture_a;
}

int Box2DContactImmutable::get_child_index_a() {
	return child_index_a;
}

Box2DFixture* Box2DContactImmutable::get_fixture_b() {
	return fixture_b;
}

int Box2DContactImmutable::get_child_index_b() {
	return child_index_b;
}

bool Box2DContactImmutable::get_is_touching() {
	return is_touching;
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
