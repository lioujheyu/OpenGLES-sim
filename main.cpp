#include <stdio.h>
#include <GLES3/gl3.h>

using namespace std;

int main()
{
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
