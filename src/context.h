#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include <stdio.h>
#include <GLES3/gl3.h>

struct attribute
{
    GLboolean   enable;
    GLint       size;
    GLenum      type;
    GLboolean   normalized;
    GLsizei     stride;
    const GLvoid * ptr;
};

struct drawCommand
{
    GLenum      mode;
    GLint       first;
    GLsizei     count;
    const GLvoid  * indices;
};

struct ViewPort
{
    GLint       x,y;
    GLint       w,h;

    GLfloat     n;
    GLfloat     f;

    ViewPort()
    {
        w = 640;
        h = 480;
        x = 0;
        y = 0;
        n = 0.f;
        f = 1.0f;
    }
};

class Context{

public:

    Context();
    ~Context();

    void                SetCurrent(bool current);
    static void         SetCurrentContext(Context * context);
    static Context *    GetCurrentContext();
    void                RecordError(GLenum error);

//OpenGL ES 2.0 API
    void DepthRangef(GLfloat n, GLfloat f);
    void DrawArrays(GLenum mode, GLint first, GLsizei count);
    void EnableVertexAttribArray(GLuint index);
    void VertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
    void Viewport(GLint x, GLint y, GLsizei width, GLsizei height);


    bool            m_current;

    char *          draw_buffer0;
    char *          draw_buffer1;

    ViewPort        vp;

    attribute       vertexAttrib[8];
    drawCommand     drawCmd;

};


#endif // CONTEXT_H_INCLUDED

