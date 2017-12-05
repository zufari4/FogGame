#pragma once

#include <vector>
#include <atomic>
#include <SDL.h>
#include <SDL_opengl.h>
#include <Box2D/Box2D.h>
#include "Texture.h"
#include "GameObject.h"
#include "BaseClass.h"
#include "SupportRectangle.h"

typedef void(BaseClass::*FrameCallback)(Uint32);
typedef void(BaseClass::*MouseKeyCallback)(int,int,int);
typedef void(BaseClass::*MouseMoveCallback)(int,int);

#define Engine engine::Instance()
extern float phyScale;

class engine: public BaseClass
{
public:
    
    int     phyStep;
    int     phyVelIters;
    int     phyPosIters;
    float   phyHz;
    int     phyAccum;
    std::atomic_bool phyPause;
    b2World phyWorld;
    Uint32  last;
    static engine& Instance()
    {
        static engine s;
        return s;
    }
    bool Init(const char* title, int width, int height, int exflags=0);
    bool InitPhysics(const vec2& gravity, float scale=250.0f, int TimeUpdate = 16, int velIters = 6, int posIters = 2);
    Texture* LoadTexture(const char*filename);
    void Cleanup();
    void Run();
    bool SetGUIFont(const char * filename, float size);
    SupportRectangle* CreateSupportRectangle();
    int GetSurfaceWidth();
    int GetSurfaceHeight();
    b2Body* CreateBody(b2BodyDef* def);
    void DeleteBody(b2Body* def);
    void AddGameObject(GameObject* obj);
    void PausePhysics();
    void StartPhysics();
    void SelectObject(GameObject* obj);
    template<typename T>
    void SetMouseMoveCallback(BaseClass* obj, void (T::*func)(int, int))
    {
        mouseMoveCallback.obj = obj;
        mouseMoveCallback.func = reinterpret_cast<MemPointer>(func);
    };
    template<typename T>
    void SetMouseDownCallback(BaseClass* obj, void (T::*func)(int, int, int))
    {
        mouseDownCallback.obj = obj;
        mouseDownCallback.func = reinterpret_cast<MemPointer>(func);
    };
    template<typename T>
    void SetMouseUpCallback(BaseClass* obj, void (T::*func)(int, int, int))
    {
        mouseUpCallback.obj = obj;
        mouseUpCallback.func = reinterpret_cast<MemPointer>(func);
    };
    template<typename T>
    void SetFrameCallback(BaseClass* obj, void (T::*func)(Uint32))
    {
        frameCallback.obj = obj;
        frameCallback.func = reinterpret_cast<MemPointer>(func);
    };
    template<typename T>
    void SetWindowResizeCallback(BaseClass* obj, void (T::*func)(int,int))
    {
        windowResizeCallback.obj = obj;
        windowResizeCallback.func = reinterpret_cast<MemPointer>(func);
    };
private:
    bool init;
    SDL_Window *window;
    SDL_GLContext glContext;
    ClassCallback frameCallback;
    ClassCallback windowResizeCallback;
    ClassCallback mouseDownCallback;
    ClassCallback mouseUpCallback;
    ClassCallback mouseMoveCallback;

    std::vector<GameObject*> gameObjects;
    std::vector<Texture*> textures;
    Texture emptyTexture;
    std::atomic_bool done;
   
    bool needUpdate;
    engine();
    ~engine();
    engine(engine const&);
    engine& operator= (engine const&);
    void ParseEvent();
    void UpdatePhysics(int delta);
};

static inline float m2p(const float val)
{
    return val * phyScale;
}

static inline float p2m(const float val)
{
    return val / phyScale;
}