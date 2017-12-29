#include "support_rectangle.h"
#include "engine.h"

Support_rectangle::Support_rectangle():
    Support_object(), selected_vertex(-1), sqared(true), drag_point(false)
{
    vertices.resize(4);
    Set_rect(vec2(0.0f, 0.0f), vec2(10.0f,10.0f));
}

void Support_rectangle::Set_rect(const vec2& _min, const vec2& _max)
{
    if (_max.Length() < _min.Length()) {
        vertices[0] = _max;
        vertices[2] = _min;
    }
    else {
        vertices[0] = _min;
        vertices[2] = _max;
    }
    vertices[1] = vec2(vertices[2].x, vertices[0].y);
    vertices[3] = vec2(vertices[0].x, vertices[2].y);
    pos = Calc_center();
    On_changed();
}

void Support_rectangle::Draw()
{
    //Rectangle
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

        if (selected_vertex == 2) glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
        else glColor4f(0.0f, 0.7f, 0.0f, 1.0f);
        glVertex2f(vertices[2].x, vertices[2].y);

        if (selected_vertex == 3) glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
        else glColor4f(0.0f, 0.7f, 0.0f, 1.0f);
        glVertex2f(vertices[3].x, vertices[3].y);

        glEnd();
    }
    //Center
    glPointSize(POINT_SIZE/2.0f);
    glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
    glBegin(GL_POINTS);
    glVertex2f(pos.x, pos.y);
    glEnd();
}

void Support_rectangle::On_mouse_move(int x, int y)
{
    Support_object::On_mouse_move(x, y);
    if (!visible || !selected || is_drag) return;

    vec2 cursor((float)x, (float)y);

    if (drag_point) {
        switch (selected_vertex)
        {
        case 0: vertices[0] = cursor; if (sqared) { vertices[3].x = vertices[0].x; vertices[1].y = vertices[0].y; } break;
        case 1: vertices[1] = cursor; if (sqared) { vertices[2].x = vertices[1].x; vertices[0].y = vertices[1].y; } break;
        case 2: vertices[2] = cursor; if (sqared) { vertices[1].x = vertices[2].x; vertices[3].y = vertices[2].y; } break;
        case 3: vertices[3] = cursor; if (sqared) { vertices[0].x = vertices[3].x; vertices[2].y = vertices[3].y; } break;
        }
        pos = Calc_center();
    }
    else if (Point_in_vertex(vertices[0], cursor)) selected_vertex = 0;
    else if (Point_in_vertex(vertices[1], cursor)) selected_vertex = 1;
    else if (Point_in_vertex(vertices[2], cursor)) selected_vertex = 2;
    else if (Point_in_vertex(vertices[3], cursor)) selected_vertex = 3;
    else selected_vertex = -1;
}

void Support_rectangle::On_mouse_down(int x, int y, int b)
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

void Support_rectangle::On_mouse_up(int x, int y, int b)
{
    if (drag_point) {
        drag_point = false;
        On_changed();
    }
    else
        Support_object::On_mouse_up(x, y, b);
}

vec2 Support_rectangle::Calc_center()
{
    vec2 p1 = 0.5f * (vertices[0] + vertices[1]);
    vec2 p2 = 0.5f * (vertices[3] + vertices[2]);
    vec2 p3 = 0.5f * (vertices[0] + vertices[3]);
    vec2 p4 = 0.5f * (vertices[1] + vertices[2]);

    // Store the values for fast access and easy
    // equations-to-code conversion
    float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;
    
    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0) return pos;
    
    // Get the x and y
    float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
    float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
    float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;
    
    // Check if the x and y coordinates are within both lines
    if (x < std::min(x1, x2) || x > std::max(x1, x2) ||
        x < std::min(x3, x4) || x > std::max(x3, x4)) return pos;
    if (y < std::min(y1, y2) || y > std::max(y1, y2) ||
        y < std::min(y3, y4) || y > std::max(y3, y4)) return pos;
    
    // Return the point of intersection
    return vec2(x, y);
}

bool Support_rectangle::Cursor_enter(const vec2& cursor)
{
    if (Point_in_shape(cursor)) return true;
    else if (Point_in_vertex(vertices[0], cursor)) return true;
    else if (Point_in_vertex(vertices[1], cursor)) return true;
    else if (Point_in_vertex(vertices[2], cursor)) return true;
    else if (Point_in_vertex(vertices[3], cursor)) return true;
    else return false;
}

