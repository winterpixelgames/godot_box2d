#ifndef BOX2D_CONTACT_H
#define BOX2D_CONTACT_H

#include "core/object.h"

#include <box2d/b2_contact.h>
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>

#include "box2d_manifold.h"
#include "box2d_fixtures.h"
#include "box2d_collision_object.h"

// Separate from Box2DContact for performance reasons. Use this instead of Box2DContact when you can.
struct Box2DContactWrapper {
private:
	b2Contact *contact{nullptr};
	Box2DManifoldWrapper manifold{};

public:
	b2Contact* get_contact() { return contact; }
	const Box2DManifoldWrapper* get_manifold() const { return &manifold; }
	Box2DManifoldWrapper* get_manifold() { return &manifold; }

	bool is_touching() const { return contact->IsTouching(); }
	void set_enabled(const bool p_flag) { contact->SetEnabled(p_flag); }
	bool is_enabled() const { return contact->IsEnabled(); }

	Box2DFixture* get_fixture_a() { return contact->GetFixtureA()->GetUserData().owner; }
	int get_child_index_a() { return contact->GetChildIndexA(); }

	Box2DFixture* get_fixture_b() { return contact->GetFixtureB()->GetUserData().owner; }
	int get_child_index_b() { return contact->GetChildIndexB(); }

	void set_friction(const float p_friction) { contact->SetFriction(p_friction); }
	float get_friction() const { return contact->GetFriction(); }
	void reset_friction() { contact->ResetFriction(); }

	void set_restitution(const float p_restitution) { contact->SetRestitution(p_restitution); }
	float get_restitution() const { return contact->GetRestitution(); }
	void reset_restitution() { contact->ResetRestitution(); }
	void set_restitution_threshold(const float p_threshold) { contact->SetRestitutionThreshold(p_threshold); }
	float get_restitution_threshold() const { return contact->GetRestitutionThreshold(); }
	void reset_restitution_threshold() { contact->ResetRestitutionThreshold(); }

	void set_tangent_speed(const float p_speed) { contact->SetTangentSpeed(p_speed * GD_TO_B2); }
	float get_tangent_speed() const { return contact->GetTangentSpeed() * B2_TO_GD; }

	Box2DContactWrapper() {};
	Box2DContactWrapper(b2Contact *p_contact) : contact(p_contact), manifold(p_contact) {};
	~Box2DContactWrapper() {};
};

class Box2DContact : public Object {
	GDCLASS(Box2DContact, Object);

private:
	Box2DContactWrapper contact{};
	Box2DManifold manifold{};

	friend class Box2DCollisionObject;

	void _update_contact(b2Contact *p_contact) {
		contact = Box2DContactWrapper(p_contact);
		manifold._update_manifold(p_contact);
	}

protected:
	static void _bind_methods();

public:
	Box2DManifold* get_manifold() { return &manifold; }

	bool is_touching() const { return contact.is_touching(); }
	void set_enabled(const bool p_flag) { contact.set_enabled(p_flag); }
	bool is_enabled() const { return contact.is_enabled(); }

	//b2Contact* GetNext(); //TODO, will need a pool
	//const b2Contact* GetNext() const;

	Box2DFixture* get_fixture_a() { return contact.get_fixture_a(); }
	int get_child_index_a() { return contact.get_child_index_a(); }

	Box2DFixture* get_fixture_b() { return contact.get_fixture_b(); }
	int get_child_index_b() { return contact.get_child_index_b(); }

	void set_friction(const float p_friction) { contact.set_friction(p_friction); }
	float get_friction() const { return contact.get_friction(); }
	void reset_friction() { contact.reset_friction(); }

	void set_restitution(const float p_restitution) { contact.set_restitution(p_restitution); }
	float get_restitution() const { return contact.get_restitution(); }
	void reset_restitution() { contact.reset_restitution(); }
	void set_restitution_threshold(const float p_threshold) { contact.set_restitution_threshold(p_threshold); }
	float get_restitution_threshold() const { return contact.get_restitution_threshold(); }
	void reset_restitution_threshold() { contact.reset_restitution_threshold(); }

	void set_tangent_speed(const float p_speed) { contact.set_tangent_speed(p_speed); }
	float get_tangent_speed() const { return contact.get_tangent_speed(); }

	Box2DContact() {}
	Box2DContact(b2Contact *p_contact) : contact(p_contact), manifold(p_contact) {};
	~Box2DContact() {}
};

struct Box2DContactImpulseWrapper {
private:
	b2ContactImpulse impulse{};
public:
	int get_count() const { return impulse.count; }

	float get_normal_impulse(const int p_index) const {
		ERR_FAIL_COND_V(p_index < 0 || p_index > impulse.count, 0.0);
		return B2_TO_GD * impulse.normalImpulses[p_index];
	}

	float get_tangent_impulse(const int p_index) const {
		ERR_FAIL_COND_V(p_index < 0 || p_index > impulse.count, 0.0);
		return B2_TO_GD * impulse.tangentImpulses[p_index];
	}

	Box2DContactImpulseWrapper() {};
	Box2DContactImpulseWrapper(const b2ContactImpulse *p_impulse) : impulse(*p_impulse) {};
	~Box2DContactImpulseWrapper() {};
};

class Box2DContactImpulse : public Object {
	GDCLASS(Box2DContactImpulse, Object);

private:
	Box2DContactImpulseWrapper impulse{};

protected:
	static void _bind_methods();

public:	
	int get_count() const { return impulse.get_count(); }
	float get_normal_impulse(const int p_index) const { return impulse.get_normal_impulse(p_index); }
	float get_tangent_impulse(const int p_index) const { return impulse.get_tangent_impulse(p_index); }

	Box2DContactImpulse() {}
	Box2DContactImpulse(const b2ContactImpulse *p_impulse) : impulse(p_impulse) {};
	~Box2DContactImpulse() {}
};

#endif // BOX2D_CONTACT_H
