#include "support_circle.h"

Support_circle::Support_circle():
    Support_object(),
    radius_(40.0f/250.0f),
    selected_vertex_(-1), drag_point_(false)
{
    Get_circle_vertexes(pos.x, pos.y, radius_, CIRCLE_STEP, vertices);
}

void Support_circle::Draw()
{
    // Circle
    if (selected) glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    else  glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
    Draw_shape();
    // Center
    glPointSize(POINT_SIZE / 2.0f);
    glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
    glBegin(GL_POINTS);
    glVertex2f(pos.x, pos.y);
    glEnd();
    // Point
    if (selected) {
        if (selected_vertex_ == 0) glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
        else glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
        glPointSize(POINT_SIZE);
        glBegin(GL_POINTS);
        glVertex2f(vertices[0].x, vertices[0].y);
        glEnd();
    }
}

bool Support_circle::Cursor_enter(const vec2& cursor)
{
    if (Point_in_shape(cursor)) return true;
    else if (Point_in_vertex(vertices[0], cursor)) return true;
    else return false;
}

void Support_circle::Set_radius(float val)
{
    radius_ = val;
    Get_circle_vertexes(pos.x, pos.y, radius_, CIRCLE_STEP, vertices);
    On_changed();
}

float Support_circle::Get_radius()
{
    return radius_;
}

void Support_circle::On_mouse_move(float x, float y)
{
    Support_object::On_mouse_move(x, y);
    if (!visible || !selected || is_drag) return;

    vec2 cursor(x, y);
    if (drag_point_) {
        radius_ = (pos - cursor).Length();
        Get_circle_vertexes(pos.x, pos.y, radius_, CIRCLE_STEP, vertices);
    }
    else if (Point_in_vertex(vertices[0], cursor)) selected_vertex_ = 0;
    else selected_vertex_ = -1;
}

void Support_circle::On_mouse_down(float x, float y, int b)
{
    if (!visible || !selected) return;

    if (selected_vertex_ != -1) {
        drag_point_ = true;
        is_drag = false;
    }
    else {
        drag_point_ = false;
        Support_object::On_mouse_down(x, y, b);
    }
}

void Support_circle::On_mouse_up(float x, float y, int b)
{
    if (drag_point_) {
        drag_point_ = false;
        On_changed();
    }
    else
        Support_object::On_mouse_up(x, y, b);
}

bool Support_circle::Point_in_shape(const vec2& p)
{
    return (pos - p).LengthSquared() < (radius_*radius_);
}

void Support_circle::Get_circle_vertexes(double cx, double cy, double r, int num_segments, std::vector<vec2>& out)
{
    out.clear();
    double theta = 3.14159265 * 2.0 / double(num_segments);
    double c = cos(theta);
    double s = sin(theta);
    double t;
    double x = r;//we start at angle = 0 
    double y = 0;

    for (int ii = 0; ii < num_segments; ii++) {
        out.emplace_back((float)(x + cx), (float)(y + cy));
        //apply the rotation matrix                          
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
}

