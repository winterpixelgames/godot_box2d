#ifndef BOX2D_CONTACT_H
#define BOX2D_CONTACT_H

#include "core/object.h"

#include <box2d/b2_contact.h>
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>

#include "box2d_manifold.h"
#include "box2d_fixtures.h"
#include "box2d_collision_object.h"

class Box2DContact : public Object {
	GDCLASS(Box2DContact, Object);

friend class Box2DCollisionObject;

private:
	b2Contact* _contact{nullptr};
	Box2DManifold manifold{};

	void _set_contact(b2Contact *contact);

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:

	Box2DManifold* get_manifold();

	bool is_touching();
	void set_enabled(bool flag);
	bool is_enabled();

	//b2Contact* GetNext(); //TODO, will need a pool
	//const b2Contact* GetNext() const;

	Box2DFixture* get_fixture_a();
	int get_child_index_a();

	Box2DFixture* get_fixture_b();
	int get_child_index_b();

	void set_friction(float friction);
	float get_friction();
	void reset_friction();

	void set_restitution(float restitution);
	float get_restitution();
	void reset_restitution();
	void set_restitution_threshold(float threshold);
	float get_restitution_threshold();
	void reset_restitution_threshold();

	void set_tangent_speed(float speed);
	float get_tangent_speed();

	Box2DContact();
	Box2DContact(b2Contact *contact);
	~Box2DContact();
};

class Box2DContactImpulse : public Object {
	GDCLASS(Box2DContactImpulse, Object);

private:
	b2ContactImpulse impulse{};

	void _set_values(const b2ContactImpulse *contact);

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:	
	int get_count() const;
	float get_normal_impulse(const int p_index) const;
	float get_tangent_impulse(const int p_index) const;

	Box2DContactImpulse();
	Box2DContactImpulse(const b2ContactImpulse *contact);
	~Box2DContactImpulse();
};

#endif // BOX2D_CONTACT_H
