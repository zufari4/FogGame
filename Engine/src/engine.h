#pragma once

#include <vector>
#include <atomic>
#include <functional>
#include <SDL.h>
#include <SDL_opengl.h>
#include <Box2D/Box2D.h>
#include "texture.h"
#include "game_object.h"
#include "base_class.h"
#include "phy_object.h"
#include "support_rectangle.h"

typedef std::atomic_bool abool;

#define engine Engine::Instance()
extern float   phy_scale;
extern float   phy_scale_inv;

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
    std::function<void(Uint32)>  callback_frame;
    std::function<void(int, int)> callback_window_resize;
    std::function<void(int, int)> callback_mouse_move;
    std::function<void(int, int, int)> callback_mouse_down;
    std::function<void(int, int, int)> callback_mouse_up;  
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
    void     Delete_body(b2Body* b);
    b2Joint* Create_joint(b2JointDef* def);
    void     Delete_join(b2Joint* j);
    void     Add_game_object(Game_object* obj);
    void     Pause_physics();
    void     Start_physics();
    void     Select_object(Game_object* obj);
    b2Body*  Get_body_at_point(const vec2& p);

    static Engine& Instance()
    {
        static Engine s;
        return s;
    }

    template<class T> void Set_callback_mouse_move(T* const object, void(T::* const func)(int, int))
    {
        callback_mouse_move = std::bind(func, object, std::placeholders::_1, std::placeholders::_2);
    }
    template<class T> void Set_callback_mouse_down(T* const object, void(T::* const func)(int, int, int))
    {
        callback_mouse_down = std::bind(func, object, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    }
    template<class T> void Set_callback_mouse_up(T* const object, void(T::* const func)(int, int, int))
    {
        callback_mouse_up = std::bind(func, object, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    }
    template<class T> void Set_callback_frame(T* const object, void(T::* const func)(Uint32))
    {
        callback_frame = std::bind(func, object, std::placeholders::_1);
    }
    template<class T> void Set_callback_window_resize(T* const object, void(T::* const func)(int, int))
    {
        callback_window_resize = std::bind(func, object, std::placeholders::_1, std::placeholders::_2);
    }

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
    return val * phy_scale_inv;
}

static inline vec2 m2pv(const vec2& val)
{
    return phy_scale * val;
}

static inline vec2 p2mv(const vec2& val)
{
    return phy_scale_inv * val;
}