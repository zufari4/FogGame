#pragma once
#include "game_object.h"
#include "physic_revolute_joint.h"
#include "editable_circle.h"

class Physic_revolute_joint_editable : Game_object, Physic_revolute_joint, Editable_circle
{
public:
	Physic_revolute_joint_editable();
	virtual ~Physic_revolute_joint_editable() {};
	bool Cursor_enter(const vec2& cursor) const override;
	void On_mouse_move(float x, float y) override;
	void On_mouse_down(float x, float y, int b) override;
	void On_mouse_up(float x, float y, int b) override;
	void Draw() const override;
	void Update(Uint32) override;
	void Connect_at_point(const vec2& a) override;
	void Show() override;
protected:
	void On_stop_drag_object() override;
};