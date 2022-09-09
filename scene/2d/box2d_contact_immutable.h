#ifndef BOX2D_CONTACT_IMMUTABLE_H
#define BOX2D_CONTACT_IMMUTABLE_H

#include "core/object.h"

#include <box2d/b2_contact.h>
#include <box2d/b2_world.h>
#include <box2d/b2_fixture.h>

#include "box2d_manifold.h"
#include "box2d_fixtures.h"
#include "box2d_collision_object.h"

class Box2DContactImmutable : public Object {
	GDCLASS(Box2DContactImmutable, Object);
friend class Box2DWorld;
friend class Box2DCollisionObject;

private:
	Box2DFixture* fixture_a;
	Box2DFixture* fixture_b;

	int child_index_a;
	int child_index_b;
	float friction;
	float restitution;
	float restitution_threshold;
	float tangent_speed;
	bool is_touching;

protected:
	static void _bind_methods();

public:	
	void copy_contact(b2Contact* contact);

	Box2DFixture* get_fixture_a();
	int get_child_index_a();

	Box2DFixture* get_fixture_b();
	int get_child_index_b();
	
	bool get_is_touching();
	float get_friction();
	float get_restitution();
	float get_restitution_threshold();
	float get_tangent_speed();

	Box2DContactImmutable();
	~Box2DContactImmutable();
};

#endif // BOX2D_CONTACT_IMMUTABLE_H
