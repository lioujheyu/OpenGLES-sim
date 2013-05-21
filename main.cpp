#include <stdio.h>
#include <GLES3/gl3.h>
#include "src/context.h"

int main()
{
    //Dirty Context setting, need to be hidden after egl or glfw library is imported or something magic is happen.
    Context::SetCurrentContext(new Context());

    GLfloat vertexPos[] = { -1.0f, -1.0f, 0.0f,
                             1.0f, -1.0f, 0.0f,
                             1.0f,  1.0f, 0.0f,
                            -1.0f,  1.0f, 0.0f
                          };

    GLfloat color[] = { 255, 255, 255,
                        255, 255, 255,
                        255, 255, 255,
                        255, 255, 255
                      };

    glViewport(0,0,1024,512);
	glClearColor(1.0,0,0,1.0);
	glClearDepthf(1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    //int v_coord_loc = glGetAttribLocation(shader.id(), "v_coord_in");
    int v_coord_loc = 0;
    int v_color_loc = 1;
    glVertexAttribPointer(v_coord_loc, 3, GL_FLOAT, GL_FALSE, 0, vertexPos);
    glEnableVertexAttribArray(v_coord_loc);

    glVertexAttribPointer(v_color_loc, 3, GL_FLOAT, GL_FALSE, 0, color);
    glEnableVertexAttribArray(v_color_loc);

    glDrawArrays(GL_TRIANGLE_STRIP,0,4);


    return 0;
}
