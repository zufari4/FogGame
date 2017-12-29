#include "Support_object.h"

Support_object::Support_object():
    Game_object(), is_drag(false), drag_start(b2Vec2_zero), callback_change(nullptr)
{
    type = otSupport;
}

void Support_object::Draw_shape()
{
    if (selected) glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    else glColor4f(1.0f, 1.0f, 1.0f, 0.5f);

    glLineWidth(LINE_WIDTH);
    glBegin(GL_LINE_LOOP);
    for (auto v : vertices)
        glVertex2f(v.x, v.y);
    glEnd();
}

bool Support_object::Point_in_shape(const vec2& p)
{
    if (vertices.size() < 3)
        return false;
    unsigned i, j;
    bool c = false;
    for (i = 0, j = vertices.size() - 1; i < vertices.size(); j = i++) {
        if (((vertices[i].y > p.y) != (vertices[j].y > p.y)) &&
            (p.x < (vertices[j].x - vertices[i].x) * (p.y - vertices[i].y) / (vertices[j].y - vertices[i].y) + vertices[i].x))
            c = !c;
    }
    return c;
}

bool Support_object::Point_in_vertex(const vec2& vertex, const vec2& point)
{
    vec2  d = vertex - point;
    float r = POINT_SIZE / 2.0f;
    return d.LengthSquared() < r*r;
}

void Support_object::On_mouse_move(int x, int y)
{
    if (!visible || !selected) return;

    if (is_drag) {
        vec2 cursor((float)x, (float)y);
        vec2 delta = cursor - drag_start;
        drag_start = cursor;
        Move(delta);
    }
}

void Support_object::On_mouse_down(int x, int y, int b)
{
    if (!visible || !selected) return;

    is_drag = true;
    drag_start = vec2((float)x, (float)y);
}

void Support_object::On_mouse_up(int x, int y, int b)
{
    if (is_drag) {
        is_drag = false;
        On_changed();
    }
}

void Support_object::On_changed()
{
    if (callback_change)
        callback_change();
}

