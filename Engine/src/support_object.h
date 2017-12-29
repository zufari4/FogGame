#pragma once

#include <Box2D/Box2D.h>
#include "game_object.h"
#include <vector>
#include <functional>

#define POINT_SIZE 10.0f
#define CIRCLE_STEP 19
#define LINE_WIDTH 2.0f

class Support_object : public Game_object
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
    virtual void On_mouse_move(int x, int y);
    virtual void On_mouse_down(int x, int y, int b);
    virtual void On_mouse_up(int x, int y, int b);
    void Draw_shape();
    void On_changed();
private:
    std::function<void(void)> callback_change;
};