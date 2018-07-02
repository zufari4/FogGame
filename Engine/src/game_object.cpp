#include "game_object.h"
#include "engine.h"

Game_object::Game_object(Object_type type):
    type_(type)
{
    Engine::Add_game_object(this);
}
