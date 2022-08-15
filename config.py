
def can_build(env, platform):
    return True

def configure(env):
    pass

def get_icons_path():
    return "icons"

def get_doc_classes():
	return [
		"Box2DShapeQueryParameters",
		"Box2DWorld",
		"Box2DCollisionObject",
		"Box2DPhysicsTestMotionResult",
		"Box2DPhysicsBody",
		"Box2DKinematicCollision",
		"Box2DArea",
		"Box2DFixture",
		"Box2DShape",
		"Box2DCircleShape",
		"Box2DRectShape",
		"Box2DSegmentShape",
		"Box2DPolygonShape",
		"Box2DCapsuleShape",
		"Box2DSDFShape",
		"Box2DJoint",
		"Box2DRevoluteJoint",
		"Box2DPrismaticJoint",
		"Box2DDistanceJoint",
		"Box2DWeldJoint",
	]

def get_doc_path():
	return "doc_classes"
