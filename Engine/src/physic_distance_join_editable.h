#pragma once
#include "game_object.h"
#include "physic_distance_join.h"
#include "editable_line_segment.h"

class Physic_distance_join_editable : Game_object, Physic_distance_join, Editable_line_segment
{
public:
	Physic_distance_join_editable();
	virtual ~Physic_distance_join_editable() {};
	bool Cursor_enter(const vec2& cursor) const override;
	void On_mouse_move(float x, float y) override;
	void On_mouse_down(float x, float y, int b) override;
	void On_mouse_up(float x, float y, int b) override;
	void Draw() const override;
	void Update(Uint32) override;
	void Connect_at_points(const vec2& a, const vec2& b) override;
	void Show() override;
protected:
	void On_stop_drag_object() override;
	void On_stop_drag_vertex() override;
};