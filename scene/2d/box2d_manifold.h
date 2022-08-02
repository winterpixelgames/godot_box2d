#ifndef BOX2D_MANIFOLD_H
#define BOX2D_MANIFOLD_H

#include <box2d/b2_collision.h>
#include "core/object.h"


class Box2DManifold : public Object {
	GDCLASS(Box2DManifold, Object);

friend class Box2DWorld;

private:
	b2Manifold* _manifold{nullptr};

protected:
	void _notification(int p_what);
	static void _bind_methods();

public:	

	Box2DManifold();
	virtual ~Box2DManifold();
};

#endif // BOX2D_MANIFOLD_H
