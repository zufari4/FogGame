#include "game_object.h"
#include "engine.h"

Game_object::Game_object():
    pos(b2Vec2_zero), angle(0), visible(false), selected(false)
{
    engine.Add_game_object(this);
}
