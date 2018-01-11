#pragma once

#include <Box2D/Box2D.h>
#include "engine.h"
#include "game_object.h"
#include "support_object.h"

class Phy_object : public Game_object
{
protected:
    Support_object* support_object;
public:
    Phy_object();
    vec2 Get_vertex(int idx);
    void Hide();
    void Show();
    void Set_pos(const vec2& newpos);
    void Move(const vec2& delta);
    void Rotate(float delta_rad);
};

class Phy_body_object : public Phy_object
{
public:
    Phy_body_object();
    b2Body* Get_body();
    b2Fixture* Get_fixture();
    b2Shape* Get_shape();
    bool TestPoint(const vec2& p);
    void Set_pos(const vec2& newpos);
    void Move(const vec2& delta);
    void Rotate(float delta_rad);
protected:
    b2Body*  body;
    b2Shape* shape;
    b2Fixture* fixture;
protected:
    virtual void Update_body();
};