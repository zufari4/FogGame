#include "support_circle.h"

Support_circle::Support_circle():
    Game_object(),
    radius(40)
{
    Get_circle_vertexes(pos.x, pos.x, radius, CIRCLE_STEP, vertices);
}

void Support_circle::Draw()
{
    //Circle
    if (selected)
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    else
        glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for (auto v : vertices)
        glVertex2f(v.x, v.y);
    glEnd();
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

void Support_circle::Move(const vec2& delta)
{
    pos += delta;
    for (auto& v : vertices)
        v += delta;
}

void Support_circle::Set_pos(const vec2& p)
{
    Move(p - pos);
    On_changed();
}

void Support_circle::Get_circle_vertexes(float cx, float cy, float r, int pix_on_step, std::vector<vec2>& out)
{
    out.clear();
    int num_segments = int(3.14159265f * 2.0f * r / float(pix_on_step));
    float theta = 3.14159265f * 2.0f / float(num_segments);
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;
    float x = r;//we start at angle = 0 
    float y = 0;

    for (int ii = 0; ii < num_segments; ii++) {
        out.emplace_back(x + cx, y + cy);
        //apply the rotation matrix                          
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
}

