#include "Support_object.h"

Support_object::Support_object():
    Game_object()
{

}

void Support_object::Move(const vec2& delta)
{
    pos += delta;
    for (auto& v : vertices)
        v += delta;
}

void Support_object::Set_pos(const vec2& p)
{
    Move(p - pos);
}

void Support_object::Rotate(float delta_rad)
{
    if (delta_rad == 0.0f)
        return;
    angle += delta_rad;

    float cc = cosf(delta_rad);
    float ss = sinf(delta_rad);
    float x;

    for (auto& v : vertices) {
        v -= pos;
        x = v.x * cc - v.y * ss;
        v.y = (v.x * ss + v.y * cc) + pos.y;
        v.x = x + pos.x;
    }
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
    int i, j, c = 0;
    for (i = 0, j = vertices.size() - 1; i < vertices.size(); j = i++) {
        if (((vertices[i].y > p.y) != (vertices[j].y > p.y)) &&
            (p.x < (vertices[j].x - vertices[i].x) * (p.y - vertices[i].y) / (vertices[j].y - vertices[i].y) + vertices[i].x))
            c = !c;
    }
    return c;
}

void Support_object::On_changed()
{

}