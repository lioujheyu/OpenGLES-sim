#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include <stdio.h>
#include <GLES3/gl3.h>

struct AttribPointer
{
    GLboolean   enable;
    GLint       size;
    GLenum      type;
    GLboolean   normalized;
    GLsizei     stride;
    const GLvoid * ptr;
};

struct DrawCommand
{
    GLenum      mode;
    GLint       first;
    GLsizei     count;
    const GLvoid  * indices;
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
    void DrawArrays(GLenum mode, GLint first, GLsizei count);
    void EnableVertexAttribArray(GLuint index);
    void VertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);

private:
    bool    m_current;

    char *  draw_buffer0;
    char *  draw_buffer1;

    AttribPointer VertexAttrib[8];
    DrawCommand DrawCmd;

};


#endif // CONTEXT_H_INCLUDED

