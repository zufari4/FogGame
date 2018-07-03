#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

Texture::Texture() :
    id(0)
{
}

Texture::~Texture()
{
    if (id != 0) {
        glDeleteTextures(1, &id);
        id = 0;
    }
}

bool Texture::Load(const char* _filename)
{
    filename = _filename;
    int comp;
    stbi_set_flip_vertically_on_load(false);
    unsigned char* imageData = stbi_load(_filename, (int*)&width, (int*)&height, &comp, 0);
    if (imageData == NULL)
        return false;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (comp == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    else if (comp == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, (GLint*)&nwidth);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, (GLint*)&nheight);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(imageData);
    
    float tsx = (float)width / (float)nwidth;
    float tsy = (float)height / (float)nheight;
    tcoord[0] = 0.0f; tcoord[1] = tsy;
    tcoord[2] = tsx ; tcoord[3] = tsy;
    tcoord[4] = 0.0f; tcoord[5] = 0.0f;
    tcoord[6] = tsx ; tcoord[7] = 0.0f;

    return true;
}

void Texture::Draw(float x, float y)
{
    if (id == 0) return;

    vertex[0] = x - width / 2.0f; vertex[1] = y - height / 2.0f;
    vertex[2] = x + width / 2.0f; vertex[3] = y - height / 2.0f;
    vertex[4] = x - width / 2.0f; vertex[5] = y + height / 2.0f;
    vertex[6] = x + width / 2.0f; vertex[7] = y + height / 2.0f;

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, id);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(tcoord[0], tcoord[1]); glVertex2f(vertex[0], vertex[1]);
    glTexCoord2f(tcoord[2], tcoord[3]); glVertex2f(vertex[2], vertex[3]);
    glTexCoord2f(tcoord[4], tcoord[5]); glVertex2f(vertex[4], vertex[5]);
    glTexCoord2f(tcoord[6], tcoord[7]); glVertex2f(vertex[6], vertex[7]);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}