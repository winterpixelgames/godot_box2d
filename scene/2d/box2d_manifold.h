#ifndef BOX2D_MANIFOLD_H
#define BOX2D_MANIFOLD_H

#include <box2d/b2_collision.h>
#include "core/object.h"


class Box2DManifold : public Object {
	GDCLASS(Box2DManifold, Object);

friend class Box2DWorld;
friend class Box2DCollisionObject;

public:
	enum Type {
		TYPE_CIRCLES = b2Manifold::Type::e_circles,
		TYPE_SDF = b2Manifold::Type::e_sdf,
		TYPE_FACEA = b2Manifold::Type::e_faceA,
		TYPE_FACEB = b2Manifold::Type::e_faceB,
	};

private:
	b2Manifold* _manifold{nullptr};
	b2WorldManifold _world_manifold{};

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:
	// b2Manifold
	Vector2 get_local_normal() const;
	Vector2 get_local_point() const;
	//float get_sdf_radius() const;
	Type get_type() const;
	int get_point_count() const;

	// b2WorldManifold
	Vector2 get_normal() const;
	Vector2 get_point(const int p_idx) const;
	float get_separation(const int p_idx) const;

	Box2DManifold();
	~Box2DManifold();
};

VARIANT_ENUM_CAST(Box2DManifold::Type);

#endif // BOX2D_MANIFOLD_H
