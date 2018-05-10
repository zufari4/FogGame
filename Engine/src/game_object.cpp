#include "game_object.h"
#include "engine.h"

Game_object::Game_object():
    type(otUnknown),
    visible(false),
    selected(false)
{
    Engine::Add_game_object(this);
}

void Game_object::Hide()
{
    visible = false;
}

void Game_object::Show()
{
    visible = true;
}

Object_type Game_object::Get_type()
{
    return type;
}

bool Game_object::Cursor_enter(const vec2&)
{
   return false;
}
