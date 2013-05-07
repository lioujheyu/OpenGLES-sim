#include "context.h"

static Context *currentContext = NULL;

Context::Context()
{
    m_current = false;
}

Context::~Context()
{

}

void Context::SetCurrent(bool current)
{
    m_current = current;

    if (!m_current) //&& m_disposed)
        delete this;
}

void Context::SetCurrentContext(Context* context)
{
    Context* oldContext = GetCurrentContext();

    if (oldContext != context)
    {
        if (oldContext != 0)
            oldContext->SetCurrent(false);

        currentContext = context;

        if (context != 0)
            context->SetCurrent(true);
    }
}

Context* Context::GetCurrentContext()
{
    return currentContext;
}

void Context::RecordError(GLenum error)
{

}

/*****************************************

    OpenGL ES 3.0 API Layer Implemention

*****************************************/

void Context::DrawArrays(GLenum mode, GLint first, GLsizei count)
{
    if (first < 0)
    {
        RecordError(GL_INVALID_VALUE);
    }
    else if (count < 0)
    {
        RecordError(GL_INVALID_VALUE);
    }
    else
    {
        switch (mode)
        {
        case GL_TRIANGLES:
        case GL_TRIANGLE_FAN:
        case GL_TRIANGLE_STRIP:
            break;
        case GL_POINTS:
        case GL_LINES:
        case GL_LINE_LOOP:
        case GL_LINE_STRIP:
            printf("draw modes in points and lines are not finished yet");
            return;
        default:
            RecordError(GL_INVALID_ENUM);
            return;
        }

        DrawCmd.mode = mode;
        DrawCmd.first = first;
        DrawCmd.count = count;
        DrawCmd.indices = NULL;

    }

    /*  Init GL state table  */
    draw_init_table();

    /*  Perform DrawArrays command  */
    drawarrays_fixed_pipeline();

    /*  Update the Tiled linked-list  */
    refresh_display_list();
}

void Context::EnableVertexAttribArray(GLuint index)
{
    if (index > 8)
    {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    VertexAttrib[index].enable = GL_TRUE;
}

void Context::VertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)
{
    if (size < 2 || size > 5)
    {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    if (indx > 8)
    {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    switch(type)
    {
    case GL_SHORT:
    case GL_BYTE:
    case GL_FLOAT:
        break;

    default:
        RecordError(GL_INVALID_ENUM);
        return;
    }

    if (stride < 0)
    {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    VertexAttrib[indx].size = size;
    VertexAttrib[indx].type = type;
    VertexAttrib[indx].normalized = normalized;
    VertexAttrib[indx].stride = stride;
    VertexAttrib[indx].ptr = ptr;
}
