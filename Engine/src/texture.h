#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>
#include <string>
#include <SDL_opengl.h>

class Texture {
public:
    GLuint   id;
    uint32_t width;
    uint32_t height;
    uint32_t nwidth;
    uint32_t nheight;
    std::string filename;
    float tcoord[8];
    float vertex[8];

    Texture();
    ~Texture();
    bool Load(const char* _filename);
    void Draw(float x, float y);
};

#endif