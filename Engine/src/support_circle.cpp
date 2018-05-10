#include "support_circle.h"

Support_circle::Support_circle():
    Support_object(),
    radius(40.0/250.0)
{
    Get_circle_vertexes(pos.x, pos.x, radius, CIRCLE_STEP, vertices);
}

void Support_circle::Draw()
{
    //Circle
    if (selected) glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    else  glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
    Draw_shape();
    //Center
    glPointSize(POINT_SIZE / 2.0f);
    glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
    glBegin(GL_POINTS);
    glVertex2f(pos.x, pos.y);
    glEnd();
}

bool Support_circle::Cursor_enter(const vec2& cursor)
{
    return (pos - cursor).LengthSquared() < (radius*radius);
}

void Support_circle::Set_radius(float val)
{
    radius = val;
    Get_circle_vertexes(pos.x, pos.x, radius, CIRCLE_STEP, vertices);
    On_changed();
}

float Support_circle::Get_radius()
{
    return radius;
}

void Support_circle::Get_circle_vertexes(double cx, double cy, double r, int pix_on_step, std::vector<vec2>& out)
{
    out.clear();
    int num_segments = pix_on_step;
    double theta = 3.14159265 * 2.0 / double(num_segments);
    double c = cos(theta);
    double s = sin(theta);
    double t;
    double x = r;//we start at angle = 0 
    double y = 0;

    for (int ii = 0; ii < num_segments; ii++) {
        out.emplace_back(x + cx, y + cy);
        //apply the rotation matrix                          
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
}

