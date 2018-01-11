#include "support_line.h"

Support_line::Support_line():
    Support_object(), selected_vertex(-1), drag_point(false)
{
    vertices.resize(2);
    Set_line(vec2(0.0f, 0.0f), vec2(100.0f, 0.0f));
}

void Support_line::Draw()
{
    Draw_shape();
    //Vertexes
    if (selected) {
        glPointSize(POINT_SIZE);
        glBegin(GL_POINTS);

        if (selected_vertex == 0) glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
        else glColor4f(0.0f, 0.7f, 0.0f, 1.0f);
        glVertex2f(vertices[0].x, vertices[0].y);

        if (selected_vertex == 1) glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
        else glColor4f(0.0f, 0.7f, 0.0f, 1.0f);
        glVertex2f(vertices[1].x, vertices[1].y);

        glEnd();
    }
}

bool Support_line::Cursor_enter(const vec2& cursor)
{
    if (Point_on_line(cursor)) return true;
    else if (Point_in_vertex(vertices[0], cursor)) return true;
    else if (Point_in_vertex(vertices[1], cursor)) return true;
    else return false;
}

bool Support_line::Point_on_line(const vec2& point)
{
    vec2 l = vertices[1] - vertices[0];
    if (l.x == 0.0f || l.y == 0.0f)
        return true;
    float d = ((point.x - vertices[0].x) / l.x) - ((point.y - vertices[0].y) / l.y);
    return fabsf(d) < 0.03f;
}

void Support_line::Set_line(const vec2& a, const vec2& b, bool notify /*= true*/)
{
    vertices[0] = a;
    vertices[1] = b;
    pos = 0.5f * (a + b);
    if (notify)
        On_changed();
}

void Support_line::On_mouse_move(float x, float y)
{
    Support_object::On_mouse_move(x, y);
    if (!visible || !selected || is_drag) return;

    vec2 cursor(x, y);

    if (drag_point) {
        switch (selected_vertex)
        {
        case 0: vertices[0] = cursor; break;
        case 1: vertices[1] = cursor; break;
        }
        pos = 0.5f * (vertices[0] + vertices[1]);
    }
    else if (Point_in_vertex(vertices[0], cursor)) selected_vertex = 0;
    else if (Point_in_vertex(vertices[1], cursor)) selected_vertex = 1;
    else selected_vertex = -1;
}

void Support_line::On_mouse_down(float x, float y, int b)
{
    if (!visible || !selected) return;

    if (selected_vertex != -1) {
        drag_point = true;
        is_drag = false;
    }
    else {
        drag_point = false;
        Support_object::On_mouse_down(x, y, b);
    }
}

void Support_line::On_mouse_up(float x, float y, int b)
{
    if (drag_point) {
        drag_point = false;
        On_changed();
    }
    else
        Support_object::On_mouse_up(x, y, b);
}
