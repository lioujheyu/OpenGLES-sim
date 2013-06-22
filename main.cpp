#include <stdio.h>
#include <GLES3/gl3.h>
#include "src/context.h"
#include "bitmap.h"
#include "shader.h"
bool LoadTexture(char *filename, unsigned int *texture)
{
	unsigned char *bitmap;
	_BITMAPINFO *info;

    bitmap = LoadDIBitmap(filename, &info);

    if (!bitmap)
        return false;

    glGenTextures(1, texture);

    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info->bmiHeader.biWidth,
                 info->bmiHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 bitmap);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    free(bitmap);
    free(info);

    return true;
}

bool LoadRGBATexture(char *filename, unsigned int *texture)
{
	unsigned char *bitmap;
	_BITMAPINFO *info;

    bitmap = LoadDIBitmap(filename, &info);

    if (!bitmap)
        return false;

    glGenTextures(1, texture);

    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, info->bmiHeader.biWidth,
                 info->bmiHeader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 bitmap);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenerateMipmap(GL_TEXTURE_2D);

    free(bitmap);
    free(info);

    return true;
}

void TextureExample()
{

}

int main()
{
    //Initial a new context, need to be hidden after egl or glfw library is imported or something magic is happen.
    Context::SetCurrentContext(new Context());

	Shader shader;

	shader.init("shader_src/TransformVertexShader.vertexshader",
			"shader_src/TextureFragmentShader.fragmentshader");

	shader.bind();

    unsigned int texture[2];

    glActiveTexture(GL_TEXTURE0);
    if (LoadTexture("data/road.bmp", &texture[0]) == false) {
		printf("Fail to load image\n");
		exit(1);
    }

    glActiveTexture(GL_TEXTURE1);
    if (LoadRGBATexture("data/four_NM_height.bmp", &texture[1]) == false) {
		printf("Fail to load image\n");
		exit(1);
    }

	//The projection transformation in vertex shader has not yet implementation.
    GLfloat vertexPos[] = { -1.0f, -1.0f, 0.0f, 1.0,
                             1.0f, -1.0f, 0.0f, 1.0,
                          1.0f/16,  0.0f, 1.0f,16.0,
                         -1.0f/16,  0.0f, 1.0f,16.0
                          };

//	GLfloat vertexPos[] = { -1.0f, -1.0f, 0.0f,
//                             1.0f, -1.0f, 0.0f,
//                             1.0f,  1.0f, 0.0f,
//                            -1.0f,  1.0f, 0.0f
//                          };

    GLfloat texCoord[] = { 0.0f, 0.0f,
                           1.0f, 0.0f,
                           1.0f, 1.0f,
                           0.0f, 1.0f,
                         };

	GLfloat mvp4x4[] = {1.0f, 0.0f, 0.0f, 0.0f,
	                    0.0f, 1.0f, 0.0f, 0.0f,
	                    0.0f, 0.0f, 1.0f, 0.0f,
	                    0.0f, 0.0f, 0.0f, 1.0f
	                   };

    glEnable(GL_DEPTH_TEST);

    glViewport(0,0,1024,768);
	glClearColor(0.0,0.0,0.0,1.0);
	glClearDepthf(1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    int v_coord_loc = glGetAttribLocation(shader.id(), "vertexPosition_modelspace");
    int v_tex0_loc = glGetAttribLocation(shader.id(), "vertexUV");
    int c_map = glGetUniformLocation(shader.id(), "ColorMap");
    int n_map = glGetUniformLocation(shader.id(), "NormalMap");
    int mvp = glGetUniformLocation(shader.id(), "MVP");
    printf("%d, %d, %d, %d, %d\n", v_coord_loc, v_tex0_loc, c_map, n_map, mvp);

    glUniform1i(c_map, texture[0]);
    glUniform1i(n_map, texture[1]);
    glUniformMatrix4fv(mvp, 1, 0, mvp4x4);


    //int v_tex0_loc = 4;
    glVertexAttribPointer(v_coord_loc, 4, GL_FLOAT, GL_FALSE, 0, vertexPos);
    glEnableVertexAttribArray(v_coord_loc);

    glVertexAttribPointer(v_tex0_loc, 2, GL_FLOAT, GL_FALSE, 0, texCoord);
    glEnableVertexAttribArray(v_tex0_loc);

    glDrawArrays(GL_TRIANGLE_FAN,0,4);

	glDeleteTextures(2, texture);

    shader.unbind();

    return 0;
}
