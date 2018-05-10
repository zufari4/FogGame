#pragma once

#include <Box2D/Box2D.h>
#include "draw_object.h"
#include <vector>
#include <functional>

#define POINT_SIZE 10.0f
#define CIRCLE_STEP 19
#define LINE_WIDTH 2.0f

class Support_object : public Draw_object
{
public:
    Support_object();

    template<class T> void Set_callback_change(T* const object, void(T::* const func)())
    {
        callback_change = std::bind(func, object);
    }

protected:
    bool is_drag;
    vec2 drag_start;

    virtual bool Point_in_shape(const vec2& p);
    bool Point_in_vertex(const vec2& vertex, const vec2& point);
    virtual void On_mouse_move(float x, float y);
    virtual void On_mouse_down(float x, float y, int b);
    virtual void On_mouse_up(float x, float y, int b);
    void Draw_shape();
    void On_changed();
private:
    std::function<void(void)> callback_change;
};