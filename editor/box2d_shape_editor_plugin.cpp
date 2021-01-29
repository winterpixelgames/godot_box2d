#include "box2d_shape_editor_plugin.h"

#include <editor/plugins/canvas_item_editor_plugin.h>

#include "../scene/2d/box2d_fixtures.h"
#include "../scene/resources/box2d_shapes.h"

/**
* @author Brian Semrau
*
* Referenced collision_shape_2d_editor_plugin.cpp
*/

void Box2DShapeEditor::_node_removed(Node *p_node) {
	if (p_node == node) {
		node = NULL;
	}
}

void Box2DShapeEditor::_shape_type_changed() {
	// We might want to swap to the Box2DPolygonEditorPlugin
	editor->edit_current();
}

Variant Box2DShapeEditor::get_handle_value(int idx) const {
	switch (shape_type) {
		case Box2DShapeEditor::CIRCLE_SHAPE: {
			Ref<Box2DCircleShape> circle = node->get_shape();

			if (idx == 0) {
				return circle->get_radius();
			}

		} break;

		case Box2DShapeEditor::RECTANGLE_SHAPE: {
			Ref<Box2DRectShape> rect = node->get_shape();

			if (idx < 3) {
				return rect->get_size().abs();
			}

		} break;

		case Box2DShapeEditor::SEGMENT_SHAPE: {
			Ref<Box2DSegmentShape> segment = node->get_shape();

			if (idx == 0) {
				return segment->get_a();
			} else if (idx == 1) {
				return segment->get_b();
			} else if (idx == 2) {
				return segment->get_a_adjacent();
			} else if (idx == 3) {
				return segment->get_b_adjacent();
			}

		} break;

		case Box2DShapeEditor::POLYGON_SHAPE: {

		} break;

		case Box2DShapeEditor::CAPSULE_SHAPE: {
			Ref<Box2DCapsuleShape> capsule = node->get_shape();

			if (idx == 0) {
				return capsule->get_radius();
			} else if (idx == 1) {
				return capsule->get_height();
			}
		} break;

		case Box2DShapeEditor::UNEDITABLE_SHAPE:
		default: {
			ERR_PRINT("Invalid shape type");
		} break;
	}

	return Variant();
}

void Box2DShapeEditor::set_handle(int idx, Point2 &p_point) {
	switch (shape_type) {
		case Box2DShapeEditor::CIRCLE_SHAPE: {
			Ref<Box2DCircleShape> circle = node->get_shape();
			circle->set_radius(p_point.length());

			canvas_item_editor->update_viewport();
		} break;

		case Box2DShapeEditor::RECTANGLE_SHAPE: {
			if (idx < 3) {
				Ref<Box2DRectShape> rect = node->get_shape();

				Vector2 extents = rect->get_size();
				if (idx == 2) {
					extents = p_point * 2.0f;
				} else {
					extents[idx] = p_point[idx] * 2.0f;
				}
				rect->set_size(extents.abs());

				canvas_item_editor->update_viewport();
			}
		} break;

		case Box2DShapeEditor::SEGMENT_SHAPE: {
			// if (edit_handle < 2) {
			Ref<Box2DSegmentShape> segment = node->get_shape();

			if (idx == 0) {
				segment->set_a(p_point);
			} else if (idx == 1) {
				segment->set_b(p_point);
			} else if (idx == 2) {
				segment->set_a_adjacent(p_point);
			} else if (idx == 3) {
				segment->set_b_adjacent(p_point);
			}

			canvas_item_editor->update_viewport();
			// }
		} break;

		case Box2DShapeEditor::POLYGON_SHAPE: {

		} break;

		case Box2DShapeEditor::CAPSULE_SHAPE: {
			if (idx < 2) {
				Ref<Box2DCapsuleShape> capsule = node->get_shape();

				real_t parameter = Math::abs(p_point[idx]);

				if (idx == 0) {
					capsule->set_radius(parameter);
				} else if (idx == 1) {
					capsule->set_height(parameter * 2 - capsule->get_radius() * 2);
				}

				canvas_item_editor->update_viewport();
			}
		} break;

		case Box2DShapeEditor::UNEDITABLE_SHAPE:
		default: {
			ERR_PRINT("Invalid shape type");
		} break;
	}

	node->get_shape()->_change_notify();
}

void Box2DShapeEditor::commit_handle(int idx, Variant &p_org) {
	undo_redo->create_action(TTR("Set Handle"));

	switch (shape_type) {
		case Box2DShapeEditor::CIRCLE_SHAPE: {
			Ref<Box2DCircleShape> circle = node->get_shape();

			undo_redo->add_do_method(circle.ptr(), "set_radius", circle->get_radius());
			undo_redo->add_do_method(canvas_item_editor, "update_viewport");
			undo_redo->add_undo_method(circle.ptr(), "set_radius", p_org);
			undo_redo->add_undo_method(canvas_item_editor, "update_viewport");
		} break;

		case Box2DShapeEditor::RECTANGLE_SHAPE: {
			Ref<Box2DRectShape> rect = node->get_shape();

			undo_redo->add_do_method(rect.ptr(), "set_size", rect->get_size());
			undo_redo->add_do_method(canvas_item_editor, "update_viewport");
			undo_redo->add_undo_method(rect.ptr(), "set_size", p_org);
			undo_redo->add_undo_method(canvas_item_editor, "update_viewport");
		} break;

		case Box2DShapeEditor::SEGMENT_SHAPE: {
			Ref<Box2DSegmentShape> segment = node->get_shape();

			if (idx == 0) {
				undo_redo->add_do_method(segment.ptr(), "set_a", segment->get_a());
				undo_redo->add_do_method(canvas_item_editor, "update_viewport");
				undo_redo->add_undo_method(segment.ptr(), "set_a", p_org);
				undo_redo->add_undo_method(canvas_item_editor, "update_viewport");
			} else if (idx == 1) {
				undo_redo->add_do_method(segment.ptr(), "set_b", segment->get_b());
				undo_redo->add_do_method(canvas_item_editor, "update_viewport");
				undo_redo->add_undo_method(segment.ptr(), "set_b", p_org);
				undo_redo->add_undo_method(canvas_item_editor, "update_viewport");
			} else if (idx == 2) {
				undo_redo->add_do_method(segment.ptr(), "set_a_adjacent", segment->get_a_adjacent());
				undo_redo->add_do_method(canvas_item_editor, "update_viewport");
				undo_redo->add_undo_method(segment.ptr(), "set_a_adjacent", p_org);
				undo_redo->add_undo_method(canvas_item_editor, "update_viewport");
			} else if (idx == 3) {
				undo_redo->add_do_method(segment.ptr(), "set_b_adjacent", segment->get_b_adjacent());
				undo_redo->add_do_method(canvas_item_editor, "update_viewport");
				undo_redo->add_undo_method(segment.ptr(), "set_b_adjacent", p_org);
				undo_redo->add_undo_method(canvas_item_editor, "update_viewport");
			}
		} break;

		case Box2DShapeEditor::POLYGON_SHAPE: {

		} break;

		case Box2DShapeEditor::CAPSULE_SHAPE: {
			Ref<Box2DCapsuleShape> capsule = node->get_shape();

			if (idx == 0) {
				undo_redo->add_do_method(capsule.ptr(), "set_radius", capsule->get_radius());
				undo_redo->add_do_method(canvas_item_editor, "update_viewport");
				undo_redo->add_undo_method(capsule.ptr(), "set_radius", p_org);
				undo_redo->add_do_method(canvas_item_editor, "update_viewport");
			} else if (idx == 1) {
				undo_redo->add_do_method(capsule.ptr(), "set_height", capsule->get_height());
				undo_redo->add_do_method(canvas_item_editor, "update_viewport");
				undo_redo->add_undo_method(capsule.ptr(), "set_height", p_org);
				undo_redo->add_undo_method(canvas_item_editor, "update_viewport");
			}
		} break;

		case Box2DShapeEditor::UNEDITABLE_SHAPE:
		default: {
			ERR_PRINT("Invalid shape type");
		} break;
	}

	undo_redo->commit_action();
}

bool Box2DShapeEditor::forward_canvas_gui_input(const Ref<InputEvent> &p_event) {
	if (!node) {
		return false;
	}

	if (!node->get_shape().is_valid()) {
		return false;
	}

	if (shape_type == -1) {
		return false;
	}

	Ref<InputEventMouseButton> mb = p_event;
	Transform2D xform = canvas_item_editor->get_canvas_transform() * node->get_global_transform();

	if (mb.is_valid()) {

		Vector2 gpoint = mb->get_position();

		if (mb->get_button_index() == BUTTON_LEFT) {
			if (mb->is_pressed()) {
				for (int i = 0; i < handles.size(); i++) {
					if (xform.xform(handles[i]).distance_to(gpoint) < 8) {
						edit_handle = i;

						break;
					}
				}

				if (edit_handle == -1) {
					pressed = false;

					return false;
				}

				original = get_handle_value(edit_handle);
				pressed = true;

				return true;

			} else {
				if (pressed) {
					commit_handle(edit_handle, original);

					edit_handle = -1;
					pressed = false;

					return true;
				}
			}
		}

		return false;
	}

	Ref<InputEventMouseMotion> mm = p_event;

	if (mm.is_valid()) {
		if (edit_handle == -1 || !pressed) {
			return false;
		}

		Vector2 cpoint = canvas_item_editor->snap_point(canvas_item_editor->get_canvas_transform().affine_inverse().xform(mm->get_position()));
		cpoint = node->get_global_transform().affine_inverse().xform(cpoint);

		set_handle(edit_handle, cpoint);

		return true;
	}

	return false;
}

void Box2DShapeEditor::_get_current_shape_type() {
	if (!node) {
		return;
	}

	Ref<Box2DShape> s = node->get_shape();

	if (!s.is_valid()) {
		return;
	}

	if (Object::cast_to<Box2DCircleShape>(*s)) {
		shape_type = CIRCLE_SHAPE;
	} else if (Object::cast_to<Box2DRectShape>(*s)) {
		shape_type = RECTANGLE_SHAPE;
	} else if (Object::cast_to<Box2DSegmentShape>(*s)) {
		shape_type = SEGMENT_SHAPE;
	} else if (Object::cast_to<Box2DPolygonShape>(*s)) {
		shape_type = UNEDITABLE_SHAPE;
	} else if (Object::cast_to<Box2DCapsuleShape>(*s)) {
		shape_type = CAPSULE_SHAPE;
	} else {
		shape_type = UNEDITABLE_SHAPE;
	}

	canvas_item_editor->update_viewport();
}

void Box2DShapeEditor::forward_canvas_draw_over_viewport(Control *p_overlay) {
	if (!node) {
		return;
	}

	if (!node->get_shape().is_valid()) {
		return;
	}

	_get_current_shape_type();

	if (shape_type == -1) {
		return;
	}

	Transform2D gt = canvas_item_editor->get_canvas_transform() * node->get_global_transform();

	Ref<Theme> theme = EditorNode::get_singleton()->get_editor_theme();
	Ref<Texture> h = theme->get_icon("EditorHandle", "EditorIcons");
	Vector2 size = h->get_size() * 0.5;

	handles.clear();

	switch (shape_type) {
		case Box2DShapeEditor::CIRCLE_SHAPE: {
			Ref<Box2DCircleShape> shape = node->get_shape();

			handles.resize(1);
			handles.write[0] = Point2(shape->get_radius(), 0);

			p_overlay->draw_texture(h, gt.xform(handles[0]) - size);
		} break;

		case Box2DShapeEditor::RECTANGLE_SHAPE: {
			Ref<Box2DRectShape> shape = node->get_shape();

			handles.resize(3);
			Vector2 ext = shape->get_size() * 0.5f;
			handles.write[0] = Point2(ext.x, 0);
			handles.write[1] = Point2(0, -ext.y);
			handles.write[2] = Point2(ext.x, -ext.y);

			p_overlay->draw_texture(h, gt.xform(handles[0]) - size);
			p_overlay->draw_texture(h, gt.xform(handles[1]) - size);
			p_overlay->draw_texture(h, gt.xform(handles[2]) - size);
		} break;

		case Box2DShapeEditor::SEGMENT_SHAPE: {
			Ref<Box2DSegmentShape> shape = node->get_shape();

			if (shape->is_one_sided()) {
				handles.resize(4);

				handles.write[0] = shape->get_a();
				handles.write[1] = shape->get_b();
				handles.write[2] = shape->get_a_adjacent();
				handles.write[3] = shape->get_b_adjacent();

				p_overlay->draw_texture(h, gt.xform(handles[0]) - size);
				p_overlay->draw_texture(h, gt.xform(handles[1]) - size);
				p_overlay->draw_texture(h, gt.xform(handles[2]) - size);
				p_overlay->draw_texture(h, gt.xform(handles[3]) - size);
			} else {
				handles.resize(2);

				handles.write[0] = shape->get_a();
				handles.write[1] = shape->get_b();

				p_overlay->draw_texture(h, gt.xform(handles[0]) - size);
				p_overlay->draw_texture(h, gt.xform(handles[1]) - size);
			}
		} break;

		case Box2DShapeEditor::POLYGON_SHAPE: {

		} break;

		case Box2DShapeEditor::CAPSULE_SHAPE: {
			Ref<Box2DCapsuleShape> shape = node->get_shape();

			handles.resize(2);
			float radius = shape->get_radius();
			float height = shape->get_height() / 2;

			handles.write[0] = Point2(radius, -height);
			handles.write[1] = Point2(0, -(height + radius));

			p_overlay->draw_texture(h, gt.xform(handles[0]) - size);
			p_overlay->draw_texture(h, gt.xform(handles[1]) - size);
		} break;

		case Box2DShapeEditor::UNEDITABLE_SHAPE:
		default: {
			ERR_PRINT("Invalid shape type");
		} break;
	}
}

void Box2DShapeEditor::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			get_tree()->connect("node_removed", this, "_node_removed");
		} break;

		case NOTIFICATION_EXIT_TREE: {
			get_tree()->disconnect("node_removed", this, "_node_removed");
		} break;
	}
}

void Box2DShapeEditor::edit(Node *p_node) {
	if (!canvas_item_editor) {
		canvas_item_editor = CanvasItemEditor::get_singleton();
	}

	if (node) {
		node->disconnect("_shape_type_changed", this, "_shape_type_changed");
	}

	if (p_node) {
		node = Object::cast_to<Box2DFixture>(p_node);

		if (node) {
			node->connect("_shape_type_changed", this, "_shape_type_changed", Vector<Variant>(), CONNECT_DEFERRED);
		}

		_get_current_shape_type();
	} else {
		edit_handle = -1;
		shape_type = UNEDITABLE_SHAPE;

		node = NULL;
	}

	canvas_item_editor->update_viewport();
}

void Box2DShapeEditor::_bind_methods() {
	ClassDB::bind_method("_get_current_shape_type", &Box2DShapeEditor::_get_current_shape_type);
	ClassDB::bind_method(D_METHOD("_node_removed"), &Box2DShapeEditor::_node_removed);
	ClassDB::bind_method(D_METHOD("_shape_type_changed"), &Box2DShapeEditor::_shape_type_changed);
}

Box2DShapeEditor::Box2DShapeEditor(EditorNode *p_editor) :
		editor(p_editor),
		undo_redo(p_editor->get_undo_redo()) {}

void Box2DShapeEditorPlugin::edit(Object *p_obj) {
	box2d_shape_editor->edit(Object::cast_to<Node>(p_obj));
}

bool Box2DShapeEditorPlugin::handles(Object *p_obj) const {
	Box2DFixture *node = Object::cast_to<Box2DFixture>(p_obj);
	// Handle null shapes so we can at least connect _shape_changed
	return node && (node->get_shape().is_null() || !node->get_shape()->is_class("Box2DPolygonShape"));
}

void Box2DShapeEditorPlugin::make_visible(bool visible) {
	if (!visible) {
		edit(NULL);
	}
}

Box2DShapeEditorPlugin::Box2DShapeEditorPlugin(EditorNode *p_editor) {
	editor = p_editor;
	box2d_shape_editor = memnew(Box2DShapeEditor(p_editor));
	p_editor->get_gui_base()->add_child(box2d_shape_editor);
}

Box2DShapeEditorPlugin::~Box2DShapeEditorPlugin() {}
