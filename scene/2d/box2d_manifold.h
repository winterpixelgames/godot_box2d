#ifndef BOX2D_MANIFOLD_H
#define BOX2D_MANIFOLD_H

#include <box2d/b2_collision.h>
#include <box2d/b2_contact.h>

#include "../../util/box2d_types_converter.h"

#include "core/object.h"

// Separate from Box2DManifold for performance reasons. Use this instead of Box2DManifold when you can.
struct Box2DManifoldWrapper {
private:
	b2Manifold* manifold{nullptr};
	b2WorldManifold world_manifold{};

public:
	const b2Manifold* get_manifold() { return manifold; }
	const b2WorldManifold* get_world_manifold() { return &world_manifold; }

	Vector2 get_local_normal() const { return Vector2(manifold->localNormal.x, manifold->localNormal.y); }
	Vector2 get_local_point() const { return b2_to_gd(manifold->localPoint); }
	//float get_sdf_radius() const;
	b2Manifold::Type get_type() const { return manifold->type; }
	int get_point_count() const { return manifold->pointCount; }

	Vector2 get_normal() const { return Vector2(world_manifold.normal.x, world_manifold.normal.y); }

	Vector2 get_point(const int p_idx) const {
		ERR_FAIL_COND_V(p_idx < 0 || p_idx >= b2_maxManifoldPoints, Vector2());
		ERR_FAIL_COND_V(p_idx >= manifold->pointCount, Vector2());
		return b2_to_gd(world_manifold.points[p_idx]);
	}

	float get_separation(const int p_idx) const {
		ERR_FAIL_COND_V(p_idx < 0 || p_idx >= b2_maxManifoldPoints, 0.0);
		ERR_FAIL_COND_V(p_idx >= manifold->pointCount, 0.0);
		return B2_TO_GD * world_manifold.separations[p_idx];
	}

	Box2DManifoldWrapper() {};
	Box2DManifoldWrapper(b2Contact* p_contact) : manifold(p_contact->GetManifold()) {
		p_contact->GetWorldManifold(&world_manifold);
	}
	~Box2DManifoldWrapper() {};
};

class Box2DManifold : public Object {
	GDCLASS(Box2DManifold, Object);

public:
	enum Type {
		TYPE_CIRCLES = b2Manifold::Type::e_circles,
		TYPE_SDF = b2Manifold::Type::e_sdf,
		TYPE_FACEA = b2Manifold::Type::e_faceA,
		TYPE_FACEB = b2Manifold::Type::e_faceB,
	};

private:
	Box2DManifoldWrapper manifold{};

	friend class Box2DContact;

	void _update_manifold(b2Contact* p_contact) { manifold = Box2DManifoldWrapper(p_contact); }

protected:
	static void _bind_methods();

public:
	Vector2 get_local_normal() const { return manifold.get_local_normal(); };
	Vector2 get_local_point() const { return manifold.get_local_point(); }
	//float get_sdf_radius() const { return manifold.get_sdf_radius(); }
	Type get_type() const { return static_cast<Type>(manifold.get_type()); }
	int get_point_count() const { return manifold.get_point_count(); }

	Vector2 get_normal() const { return manifold.get_normal(); }
	Vector2 get_point(const int p_idx) const { return manifold.get_point(p_idx); }
	float get_separation(const int p_idx) const { return manifold.get_separation(p_idx); }

	Box2DManifold() {};
	Box2DManifold(b2Contact* p_contact) : manifold(p_contact) {};
	~Box2DManifold() {};
};

VARIANT_ENUM_CAST(Box2DManifold::Type);

#endif // BOX2D_MANIFOLD_H
