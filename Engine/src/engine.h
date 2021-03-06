#pragma once

#include <vector>
#include <atomic>
#include <SDL.h>
#include <SDL_opengl.h>
#include <Box2D/Box2D.h>
#include "texture.h"
#include "game_object.h"
#include "base_class.h"
#include "physic_object.h"

namespace Engine
{
    typedef void (Base_class::*i1_callback)(Uint32);
    typedef void (Base_class::*f2_callback)(float, float);
    typedef void (Base_class::*f3_callback)(float, float, float);
    typedef struct
    {
        Base_class* obj  = nullptr;
        i1_callback func = nullptr;
    } i1_callback_link;
    typedef struct
    {
        Base_class* obj  = nullptr;
        f2_callback func = nullptr;
    } f2_callback_link;
    typedef struct
    {
        Base_class* obj  = nullptr;
        f3_callback func = nullptr;
    } f3_callback_link;

    bool Init(const char* title, int width, int height, float scale = 1.0f, Uint32 exflags = 0);
    bool Init_physics(const vec2& gravity, double phy_hz = 60, int vel_iters = 6, int pos_iters = 2);
    void Run();
    void Setup_camera(float width, float height, float scale);
    Texture* Load_texture(const char*filename);
    void Stop();
    void Pause_physics();
    void Start_physics();
    float Get_dpi();
    float Get_surface_width();
    float Get_surface_height();
    void Add_game_object(Game_object* obj);
    b2Body* Get_body_at_point(const vec2& p);
	std::vector<b2Body*> Get_bodies_at_point(const vec2& p);
    bool  Physic_paused();
    float Get_camera_scale();
    b2World& Get_world();
    unsigned Get_fps();
	const vec2 s2w(float x, float y);
	const vec2 s2w(int x, int y);
    void SetWindowTitle(const char* text);
    void _Set_callback_frame(Base_class* object, i1_callback function);
    void _Set_callback_window_resize(Base_class* object, f2_callback function);
    void _Set_callback_mouse_down(Base_class* object, f3_callback function);
    void _Set_callback_mouse_up(Base_class* object, f3_callback function);
    void _Set_callback_mouse_move(Base_class* object, f2_callback function);
	size_t Get_count_game_objects();
    template<class T> void Set_callback_mouse_move(T* object, void (T::*funcpointer)(float, float))
    {
        _Set_callback_mouse_move(object, reinterpret_cast<f2_callback>(funcpointer));
    }

    template<class T> void Set_callback_mouse_down(T* object, void (T::*funcpointer)(float, float, float))
    {
        _Set_callback_mouse_down(object, reinterpret_cast<f3_callback>(funcpointer));
    }

    template<class T> void Set_callback_mouse_up(T* object, void (T::*funcpointer)(float, float, float))
    {
        _Set_callback_mouse_up(object, reinterpret_cast<f3_callback>(funcpointer));
    }

    template<class T> void Set_callback_frame(T* object, void (T::*funcpointer)(Uint32))
    {
        _Set_callback_frame(object, reinterpret_cast<i1_callback>(funcpointer));
    }

    template<class T> void Set_callback_window_resize(Base_class* object, void (T::*funcpointer)(float, float))
    {
        _Set_callback_window_resize(object, reinterpret_cast<f2_callback>(funcpointer));
    }
}