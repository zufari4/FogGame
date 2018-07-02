#pragma once
#include "game_object.h"
#include "physic_box.h"
#include "editable_box.h"

class Physic_box_editable : public Game_object, Physic_box, Editable_box
{
public:
	Physic_box_editable();
	virtual ~Physic_box_editable() {};
	bool Cursor_enter(const vec2& cursor) const override;
	void Set_pos(const vec2& newpos) override;
	void On_mouse_move(float x, float y) override;
	void On_mouse_down(float x, float y, int b) override;
	void On_mouse_up(float x, float y, int b) override;
	void Draw() const override;
	void Update(Uint32) override;
	b2Body* Get_body() const override;
protected:
	void On_drag_point(const vec2& pos) override;
	void On_stop_drag_object() override;
	void On_stop_drag_vertex() override;

	bool sqared_;
};
