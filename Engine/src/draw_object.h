#pragma once

#include "base_class.h"

class Draw_object : public Base_class
{
public:
	Draw_object();
	virtual ~Draw_object() {};
	virtual void  Draw() const {};
	virtual void  Hide();
	virtual void  Show();
	virtual void  Set_pos(const vec2& newpos);
	virtual const vec2& Get_pos() const;
	virtual float Get_angle() const;
	virtual void  Rotate(float delta_rad);
	virtual void  Move(const vec2& delta);
	virtual void  Set_selected(bool value);
	virtual bool  Is_visible() const;
	virtual bool  Has_edit() const;
protected:
	vec2 pos_;
	float angle_;
	bool selected_;
	bool visible_;
};