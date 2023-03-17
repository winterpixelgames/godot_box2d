#include "box2d_contact.h"
#include "box2d_fixtures.h"
#include <core/engine.h>

void Box2DContact::_set_contact(b2Contact *contact) {
	this->_contact = contact;
	this->manifold._manifold = contact->GetManifold();
	contact->GetWorldManifold(&this->manifold._world_manifold);
}

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

void Box2DContact::_notification(int p_what) {
	// Nothing right now
}

Box2DContact::Box2DContact() {
}

Box2DContact::Box2DContact(b2Contact *contact) {
	_set_contact(contact);
}

Box2DContact::~Box2DContact() {
}

Box2DManifold* Box2DContact::get_manifold(){
	return &manifold;
}
	
bool Box2DContact::is_touching() {
	return _contact->IsTouching();
}

void Box2DContact::set_enabled(bool flag) {
	_contact->SetEnabled(flag);
}
	
bool Box2DContact::is_enabled() {
	return _contact->IsEnabled();
}

Box2DFixture* Box2DContact::get_fixture_a() {
	return _contact->GetFixtureA()->GetUserData().owner;
}
	
int Box2DContact::get_child_index_a() {
	return _contact->GetChildIndexA();
}

Box2DFixture* Box2DContact::get_fixture_b() {
	return _contact->GetFixtureB()->GetUserData().owner;
}

int Box2DContact::get_child_index_b() {
	return _contact->GetChildIndexB();
}

void Box2DContact::set_friction(float friction) {
	_contact->SetFriction(friction);
}
	
float Box2DContact::get_friction() {
	return _contact->GetFriction();
}
	
void Box2DContact::reset_friction() {
	_contact->ResetFriction();
}

void Box2DContact::set_restitution(float restitution) {
	_contact->SetRestitution(restitution);
}
	
float Box2DContact::get_restitution() {
	return _contact->GetRestitution();
}
	
void Box2DContact::reset_restitution() {
	_contact->ResetRestitution();
}
	
void Box2DContact::set_restitution_threshold(float threshold) {
	_contact->SetRestitutionThreshold(threshold);
}

float Box2DContact::get_restitution_threshold() {
	return _contact->GetRestitutionThreshold();
}
void Box2DContact::reset_restitution_threshold() {
	_contact->ResetRestitutionThreshold();
}

void Box2DContact::set_tangent_speed(float speed) {
	_contact->SetTangentSpeed(speed);
}
	
float Box2DContact::get_tangent_speed() {
	return _contact->GetTangentSpeed();
}

void Box2DContactImpulse::_set_values(const b2ContactImpulse *contact) {
	impulse = *contact;
}

void Box2DContactImpulse::_notification(int p_what) {
}

void Box2DContactImpulse::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_count"), &Box2DContactImpulse::get_count);
	ClassDB::bind_method(D_METHOD("get_normal_impulse", "index"), &Box2DContactImpulse::get_normal_impulse);
	ClassDB::bind_method(D_METHOD("get_tangent_impulse", "index"), &Box2DContactImpulse::get_tangent_impulse);
}

int Box2DContactImpulse::get_count() const {
	return impulse.count;
}

float Box2DContactImpulse::get_normal_impulse(const int p_index) const {
	ERR_FAIL_COND_V(p_index < 0 || p_index > impulse.count, 0.0);
	return B2_TO_GD * (impulse.normalImpulses[p_index]);
}

float Box2DContactImpulse::get_tangent_impulse(const int p_index) const {
	ERR_FAIL_COND_V(p_index < 0 || p_index > impulse.count, 0.0);
	return B2_TO_GD * (impulse.tangentImpulses[p_index]);
}

Box2DContactImpulse::Box2DContactImpulse() {
}

Box2DContactImpulse::Box2DContactImpulse(const b2ContactImpulse *contact) {
	_set_values(contact);
}

Box2DContactImpulse::~Box2DContactImpulse() {
}
