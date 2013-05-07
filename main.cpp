#include <stdio.h>
#include <GLES3/gl3.h>
#include "context.h"

//using namespace std;

int main()
{
    //Dirty Context setting, need to be hidden after egl or glfw library is imported or something magic is happen.
    Context::SetCurrentContext(new Context());

    GLfloat vertexPos[] = { -1.0f, -1.0f, 0.0f,
                             1.0f, -1.0f, 0.0f,
                             1.0f,  1.0f, 0.0f,
                            -1.0f,  1.0f, 0.0f
                          };

    //int v_coord_loc = glGetAttribLocation(shader.id(), "v_coord_in");
    int v_coord_loc = 0;
    glVertexAttribPointer(v_coord_loc, 3, GL_FLOAT, GL_FALSE, 0, vertexPos);
    glEnableVertexAttribArray(v_coord_loc);


    return 0;
}
