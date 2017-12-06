#include "support_rectangle.h"
#include "engine.h"

SupportRectangle::SupportRectangle() :
    GameObject(), selectedVertex(-1), dragPoint(false), dragRect(false),
    a(b2Vec2_zero), b(b2Vec2_zero),
    c(b2Vec2_zero), d(b2Vec2_zero), sqared(true)
{
    Engine.AddGameObject(this);
}

void SupportRectangle::SetRect(const vec2& _min, const vec2& _max)
{
    if (_max.Length() < _min.Length()) {
        a = _max;
        c = _min;
    }
    else {
        a = _min;
        c = _max;
    }

    b = vec2(c.x, a.y);
    d = vec2(a.x, c.y);
    CallCenter(pos);
    OnChanged();
}

void SupportRectangle::Draw()
{
    //Rectagle
    if (selected)
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    else
        glColor4f(1.0f, 1.0f, 1.0f, 0.5f);

    glLineWidth(4.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glVertex2f(c.x, c.y);
    glVertex2f(d.x, d.y);
    glEnd();
    //Vertexes
    glPointSize(POINT_SIZE);
    glBegin(GL_POINTS);
    if (selectedVertex == 0) glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    else glColor4f(0.0f, 0.7f, 0.0f, 1.0f);
    glVertex2f(a.x, a.y);
    if (selectedVertex == 1) glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    else glColor4f(0.0f, 0.7f, 0.0f, 1.0f);
    glVertex2f(b.x, b.y);
    if (selectedVertex == 2) glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    else glColor4f(0.0f, 0.7f, 0.0f, 1.0f);
    glVertex2f(c.x, c.y);
    if (selectedVertex == 3) glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    else glColor4f(0.0f, 0.7f, 0.0f, 1.0f);
    glVertex2f(d.x, d.y);
    glEnd();
    //Center
    glPointSize(POINT_SIZE/2.0f);
    glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
    glBegin(GL_POINTS);
    glVertex2f(pos.x, pos.y);
    glEnd();
}

void SupportRectangle::Rotate(float deltaRad)
{
    if (deltaRad == 0.0f)
        return;
   angle += deltaRad;

   float cc = cosf(deltaRad);
   float ss = sinf(deltaRad);
   float x;

   a -= pos;
   x = a.x * cc - a.y * ss;
   a.y = (a.x * ss + a.y * cc) + pos.y;
   a.x = x + pos.x;

   b -= pos;
   x = b.x * cc - b.y * ss;
   b.y = (b.x * ss + b.y * cc) + pos.y;
   b.x = x + pos.x;

   c -= pos;
   x = c.x * cc - c.y * ss;
   c.y = (c.x * ss + c.y * cc) + pos.y;
   c.x = x + pos.x;

   d -= pos;
   x = d.x * cc - d.y * ss;
   d.y = (d.x * ss + d.y * cc) + pos.y;
   d.x = x + pos.x;
}


void SupportRectangle::OnMouseMove(int x, int y)
{
    if (!selected) return;

    vec2 cursor((float)x, (float)y);
    if (dragRect) {
        vec2 delta = cursor - dragStart;
        a += delta;
        b += delta;
        c += delta;
        d += delta;
        pos += delta;
        dragStart = cursor;
    }
    else if (dragPoint) {
        switch (selectedVertex)
        {
        case 0: a = cursor; if (sqared) { d.x = a.x; b.y = a.y; } break;
        case 1: b = cursor; if (sqared) { c.x = b.x; a.y = b.y; } break;
        case 2: c = cursor; if (sqared) { b.x = c.x; d.y = c.y; } break;
        case 3: d = cursor; if (sqared) { a.x = d.x; c.y = d.y; } break;
        }
        CallCenter(pos);
    }
    else if (InPoint(a, cursor)) selectedVertex = 0;
    else if (InPoint(b, cursor)) selectedVertex = 1;
    else if (InPoint(c, cursor)) selectedVertex = 2;
    else if (InPoint(d, cursor)) selectedVertex = 3;
    else selectedVertex = -1;
}

void SupportRectangle::OnMouseDown(int x, int y, int b)
{
    if (!visible) return;

    if (selectedVertex != -1) {
        dragPoint = true;
        dragRect = false;
    }
    else if (PointInRect(vec2((float)x, (float)y))) {
        dragRect = true;
        dragPoint = false;
        dragStart = vec2((float)x, (float)y);
    }
}

void SupportRectangle::OnMouseUp(int x, int y, int b)
{
    if (dragPoint || dragRect)
        OnChanged();
    dragPoint = false;
    dragRect = false;
}

bool SupportRectangle::InPoint(const vec2 & point, const vec2 & cursor)
{
    vec2 d = point - cursor;
    float r = POINT_SIZE / 2.0f;
    return d.LengthSquared() < r*r;
}

void SupportRectangle::CallCenter(vec2& center)
{
    vec2 p1 = (a + b); p1 *= 0.5f;
    vec2 p2 = (d + c); p2 *= 0.5f;
    vec2 p3 = (a + d); p3 *= 0.5f;
    vec2 p4 = (b + c); p4 *= 0.5f;

        // Store the values for fast access and easy
        // equations-to-code conversion
        float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
        float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

        float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
        // If d is zero, there is no intersection
        if (d == 0) return;

        // Get the x and y
        float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
        float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
        float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

        // Check if the x and y coordinates are within both lines
        if (x < std::min(x1, x2) || x > std::max(x1, x2) ||
            x < std::min(x3, x4) || x > std::max(x3, x4)) return;
        if (y < std::min(y1, y2) || y > std::max(y1, y2) ||
            y < std::min(y3, y4) || y > std::max(y3, y4)) return;

        // Return the point of intersection
        center = vec2(x, y);
}

bool SupportRectangle::PointInRect(const vec2 & point)
{
    /*
    int pnpoly(int nvert, float *vertx, float *verty, float testx, float testy)
    {
    int i, j, c = 0;
    for (i = 0, j = nvert - 1; i < nvert; j = i++) {
    if (((verty[i]>testy) != (verty[j]>testy)) &&
    (testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
    c = !c;
    }
    return c;
    }
    */
    bool r = false;

    if (((a.y>point.y) != (d.y>point.y)) &&
        (point.x < (d.x - a.x) * (point.y - a.y) / (d.y - a.y) + a.x))
        r = !r;

    if (((b.y>point.y) != (a.y>point.y)) &&
        (point.x < (a.x - b.x) * (point.y - b.y) / (a.y - b.y) + b.x))
        r = !r;

    if (((c.y>point.y) != (b.y>point.y)) &&
        (point.x < (b.x - c.x) * (point.y - c.y) / (b.y - c.y) + c.x))
        r = !r;

    if (((d.y>point.y) != (c.y>point.y)) &&
        (point.x < (c.x - d.x) * (point.y - d.y) / (c.y - d.y) + d.x))
        r = !r;

    return r || (selectedVertex != -1);
}

