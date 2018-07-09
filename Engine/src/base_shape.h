#pragma once
#include "draw_object.h"
#include <vector>

class Base_shape : virtual public Draw_object
{
public:
    Base_shape();
    virtual ~Base_shape() {};
	virtual void  Draw() const override;
    virtual void  Set_pos(const vec2& newpos) override;
	virtual void  Set_pos(const vec2& newpos, float angle);
    virtual void  Move(const vec2& delta) override;
    virtual void  Rotate(float delta_rad) override;
    virtual const vec2& Get_vertex(int idx) const;
	virtual const std::vector<vec2>& Get_vertexes() const;
	virtual bool  Point_in_shape(const vec2& p) const;
protected:
	std::vector<vec2> vertex_;
	std::vector<vec2> vertex_identity_;
	std::vector<vec2> vertex_rotated_;
};