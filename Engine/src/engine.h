#pragma once

#include <vector>
#include <atomic>
#include <SDL.h>
#include <SDL_opengl.h>
#include <Box2D/Box2D.h>
#include "texture.h"
#include "game_object.h"
#include "base_class.h"
#include "support_rectangle.h"

typedef void (Base_class::*Callback_frame)(Uint32);
typedef void (Base_class::*Callback_mouse_m)(int, int);
typedef void (Base_class::*Callback_mouse_k)(int,int,int);
typedef void (Base_class::*Callback_window)(int, int);
typedef std::atomic_bool abool;

#define engine Engine::Instance()
extern float   phy_scale;

class Engine: public Base_class
{
public:
    int     phy_step;
    int     phy_vel_iters;
    int     phy_pos_iters;
    float   phy_hz;
    int     phy_accum;
    abool   phy_pause;
    b2World phy_world;
    Uint32  last;
private:
    bool    init;
    abool   done;
    bool    phy_updated;
    SDL_Window*   window;
    SDL_GLContext gl_context;
    Callback  callback_frame;
    Callback  callback_window_resize;
    Callback  callback_mouse_down;
    Callback  callback_mouse_up;
    Callback  callback_mouse_move;
    std::vector<Game_object*> game_objects;
    std::vector<Texture*>     textures;
    Texture empty_texture; 
public:
    bool     Init(const char* title, int width, int height, int exflags=0);
    bool     Init_physics(const vec2& gravity, float scale=250.0f, int time_update = 16, int vel_iters = 6, int pos_iters = 2);
    Texture* Load_texture(const char*filename);
    void     Cleanup();
    void     Run();
    bool     Set_gui_font(const char * filename, float size);
    int      Get_surface_width();
    int      Get_surface_height();
    b2Body*  Create_body(const b2BodyDef& def);
    void     Delete_body(b2Body* def);
    void     Add_game_object(Game_object* obj);
    void     Pause_physics();
    void     Start_physics();
    void     Select_object(Game_object* obj);
    Support_rectangle* Create_support_rectangle();
    static Engine& Instance()
    {
        static Engine s;
        return s;
    }
    template<typename T>
    void Set_callback_mouse_move(Base_class* obj, void (T::*func)(int, int))
    {
        callback_mouse_move.obj  = obj;
        callback_mouse_move.func = reinterpret_cast<Mem_pointer>(func);
    };
    template<typename T>
    void Set_callback_mouse_down(Base_class* obj, void (T::*func)(int, int, int))
    {
        callback_mouse_down.obj  = obj;
        callback_mouse_down.func = reinterpret_cast<Mem_pointer>(func);
    };
    template<typename T>
    void Set_callback_mouse_up(Base_class* obj, void (T::*func)(int, int, int))
    {
        callback_mouse_up.obj  = obj;
        callback_mouse_up.func = reinterpret_cast<Mem_pointer>(func);
    };
    template<typename T>
    void Set_callback_frame(Base_class* obj, void (T::*func)(Uint32))
    {
        callback_frame.obj  = obj;
        callback_frame.func = reinterpret_cast<Mem_pointer>(func);
    };
    template<typename T>
    void Set_callback_window_resize(Base_class* obj, void (T::*func)(int,int))
    {
        callback_window_resize.obj  = obj;
        callback_window_resize.func = reinterpret_cast<Mem_pointer>(func);
    };
private:
    Engine();
   ~Engine();
    Engine(Engine const&);
    Engine& operator= (Engine const&);
    void Parse_events();
    void Update_physics(int delta);
};

static inline float m2p(const float val)
{
    return val * phy_scale;
}

static inline float p2m(const float val)
{
    return val / phy_scale;
}