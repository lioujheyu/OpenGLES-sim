#include <stdio.h>
#include <GLES3/gl3.h>

#include "src/context.h"

// glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include <glm/glm.hpp>
// glm::perspective
#include <glm/gtc/matrix_transform.hpp>
// glm::value_ptr
#include <glm/gtc/type_ptr.hpp>

#include "bitmap.h"
#include "shader.h"

#include "data/banana.h"

bool LoadTexture(char *filename, unsigned int *texture)
{
	unsigned char *bitmap;
	_BITMAPINFO *info;

    bitmap = LoadDIBitmap(filename, &info);

    if (!bitmap)
        return false;

    glGenTextures(1, texture);

    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, info->bmiHeader.biWidth,
                 info->bmiHeader.biHeight, 0,
                 (info->bmiHeader.biBitCount==32)? GL_RGBA : GL_RGB,
				 GL_UNSIGNED_BYTE, bitmap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    free(bitmap);
    free(info);

    return true;
}

int LoadCubeMap(char *xneg, char *yneg, char *zneg,
				 char *xpos, char *ypos, char *zpos,
				 unsigned int *texture)
{
	unsigned char *bitmap[6];
	_BITMAPINFO *info[6];

	bitmap[0] = LoadDIBitmap(xneg, &info[0]);
	if (!bitmap[0])	return 1;
	bitmap[1] = LoadDIBitmap(yneg, &info[1]);
	if (!bitmap[1])	return 2;
	bitmap[2] = LoadDIBitmap(zneg, &info[2]);
	if (!bitmap[2])	return 3;
	bitmap[3] = LoadDIBitmap(xpos, &info[3]);
	if (!bitmap[3])	return 4;
	bitmap[4] = LoadDIBitmap(ypos, &info[4]);
	if (!bitmap[4])	return 5;
	bitmap[5] = LoadDIBitmap(zpos, &info[5]);
	if (!bitmap[5])	return 6;

	glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture[0]);

    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA,
				 info[0]->bmiHeader.biWidth, info[0]->bmiHeader.biHeight, 0,
                 (info[0]->bmiHeader.biBitCount==32)? GL_RGBA : GL_RGB,
				 GL_UNSIGNED_BYTE, bitmap[0]);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA,
				 info[1]->bmiHeader.biWidth, info[1]->bmiHeader.biHeight, 0,
                 (info[1]->bmiHeader.biBitCount==32)? GL_RGBA : GL_RGB,
				 GL_UNSIGNED_BYTE, bitmap[1]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA,
				 info[2]->bmiHeader.biWidth, info[2]->bmiHeader.biHeight, 0,
                 (info[2]->bmiHeader.biBitCount==32)? GL_RGBA : GL_RGB,
				 GL_UNSIGNED_BYTE, bitmap[2]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA,
				 info[3]->bmiHeader.biWidth, info[3]->bmiHeader.biHeight, 0,
                 (info[3]->bmiHeader.biBitCount==32)? GL_RGBA : GL_RGB,
				 GL_UNSIGNED_BYTE, bitmap[3]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA,
				 info[4]->bmiHeader.biWidth, info[4]->bmiHeader.biHeight, 0,
                 (info[4]->bmiHeader.biBitCount==32)? GL_RGBA : GL_RGB,
				 GL_UNSIGNED_BYTE, bitmap[4]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA,
				 info[5]->bmiHeader.biWidth, info[5]->bmiHeader.biHeight, 0,
                 (info[5]->bmiHeader.biBitCount==32)? GL_RGBA : GL_RGB,
				 GL_UNSIGNED_BYTE, bitmap[5]);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	return 0;
}

void draw_road()
{
	Shader shader;
	shader.init("shader_src/NormalMapping.vert",
				"shader_src/NormalMapping.frag");
	shader.bind();

    unsigned int texture[2];

    glActiveTexture(GL_TEXTURE0);
    if (LoadTexture("data/stone_wall.bmp", &texture[0]) == false) {
		printf("Fail to load image\n");
		exit(1);
    }

    glActiveTexture(GL_TEXTURE1);
    if (LoadTexture("data/stone_wall_normal_map.bmp", &texture[1]) == false) {
		printf("Fail to load image\n");
		exit(1);
    }

//	glActiveTexture(GL_TEXTURE0);
//	if (LoadTexture("data/road.bmp", &texture[0]) == false) {
//		printf("Fail to load image\n");
//		exit(1);
//	}
//
//	glActiveTexture(GL_TEXTURE1);
//	if (LoadTexture("data/four_NM_height.bmp", &texture[1]) == false) {
//		printf("Fail to load image\n");
//		exit(1);
//	}

    GLfloat vertexPos[] = { -1.0f, -0.7f, 0.0f, 1.0f,
                             1.0f, -0.7f, 0.0f, 1.0f,
                             1.0f, -0.7f, 4.0f, 1.0f,
                            -1.0f, -0.7f, 4.0f, 1.0f
                          };

	GLfloat vertexNormal[] = { 0.0f, 1.0f, 0.0f,
							   0.0f, 1.0f, 0.0f,
							   0.0f, 1.0f, 0.0f
							 };

    GLfloat texCoord[] = { 0.0f, 0.0f,
                           1.0f, 0.0f,
                           1.0f, 2.0f,
                           0.0f, 2.0f,
                         };

    glEnable(GL_DEPTH_TEST);

    glViewport(0,0,1024,768);
	glClearColor(0.0,0.0,0.0,1.0);
	glClearDepthf(1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glm::vec3 eye_pos = glm::vec3(0.0f, 0.2f, -0.5f);
	glm::mat4 Projection = glm::perspective(90.0f, 1024.0f / 768.0f, 0.1f, 100.f);
    glm::mat4 View = glm::lookAt(
						eye_pos,          // Camera position in World space
						glm::vec3(0,0,0), // and looks at the origin
						glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
					);
	//glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(3.0f));
	glm::mat4 MVP = Projection * View;

    int v_coord_loc = glGetAttribLocation(shader.id(), "obj_vertex");
    int v_tex0_loc = glGetAttribLocation(shader.id(), "obj_texCoord");
    int v_normal_loc = glGetAttribLocation(shader.id(), "obj_texCoord");
    int c_map = glGetUniformLocation(shader.id(), "ColorMap");
    int n_map = glGetUniformLocation(shader.id(), "NormalMap");
    int mvp = glGetUniformLocation(shader.id(), "MVP");
    int eye_loc = glGetUniformLocation(shader.id(), "eye_pos");

    glUniform1i(c_map, 0);
    glUniform1i(n_map, 1);
    glUniform3fv(eye_loc, 1, &eye_pos[0]);
    glUniformMatrix4fv(mvp, 1, 0, &MVP[0][0]);

    glVertexAttribPointer(v_coord_loc, 4, GL_FLOAT, GL_FALSE, 0, vertexPos);
    glEnableVertexAttribArray(v_coord_loc);

    glVertexAttribPointer(v_normal_loc, 3, GL_FLOAT, GL_FALSE, 0, vertexNormal);
    glEnableVertexAttribArray(v_normal_loc);

    glVertexAttribPointer(v_tex0_loc, 2, GL_FLOAT, GL_FALSE, 0, texCoord);
    glEnableVertexAttribArray(v_tex0_loc);

    glDrawArrays(GL_TRIANGLE_FAN,0,4);

    glDeleteTextures(2, texture);

    shader.unbind();
}

void draw_banana()
{
	Shader shader;
	shader.init("shader_src/drawObj.vert", "shader_src/drawObj.frag");
	shader.bind();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);

	glViewport(0,0,1024,768);
	glClearColor(0.0,0.0,0.0,1.0);
	glClearDepthf(1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	unsigned int texture[2];
	glActiveTexture(GL_TEXTURE0);
    if (LoadTexture("data/banana.bmp", &texture[0]) == false) {
		printf("Fail to load image\n");
		exit(1);
    }

	glm::vec3 eye_pos = glm::vec3(2.0f, 1.0f, 1.0f);
	glm::vec3 light_pos = glm::vec3(1.0f, 1.5f, -2.0f);
    glm::mat4 Projection = glm::perspective(90.0f, 1024.0f / 768.0f, 0.1f, 100.f);
    glm::mat4 View = glm::lookAt(
						eye_pos, // Camera is at (2,1,1), in World Space
						glm::vec3(0,0,0), // and looks at the origin
						glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
					);
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(3.5f));
	glm::mat4 VP = Projection * View;

	int v_coord_loc = glGetAttribLocation(shader.id(), "obj_vertex");
	int v_normal_loc = glGetAttribLocation(shader.id(), "obj_normal");
    int v_tex0_loc = glGetAttribLocation(shader.id(), "obj_texcoord");
    int c_map_loc = glGetUniformLocation(shader.id(), "ColorMap");
    int vp_loc = glGetUniformLocation(shader.id(), "VP");
    int model_loc = glGetUniformLocation(shader.id(), "model_mat");
    int light_loc = glGetUniformLocation(shader.id(), "light_pos");
    int eye_loc = glGetUniformLocation(shader.id(), "eye_pos");
    printf("%d, %d, %d, %d, %d, %d, %d\n", v_coord_loc, v_normal_loc, v_tex0_loc, c_map_loc, vp_loc, model_loc, light_loc);

	glUniform1i(c_map_loc, 0);
    glUniformMatrix4fv(vp_loc, 1, 0, &VP[0][0]);
	glUniformMatrix4fv(model_loc, 1, 0, &Model[0][0]);
    glUniform3fv(light_loc, 1, &light_pos[0]);
    glUniform3fv(eye_loc, 1, &eye_pos[0]);

    glVertexAttribPointer(v_coord_loc, 3, GL_FLOAT, GL_FALSE, 0, bananaVerts);
    glEnableVertexAttribArray(v_coord_loc);

    glVertexAttribPointer(v_normal_loc, 3, GL_FLOAT, GL_FALSE, 0, bananaNormals);
    glEnableVertexAttribArray(v_normal_loc);

    glVertexAttribPointer(v_tex0_loc, 2, GL_FLOAT, GL_FALSE, 0, bananaTexCoords);
    glEnableVertexAttribArray(v_tex0_loc);

	glDrawArrays(GL_TRIANGLES, 0, bananaNumVerts);

	glDeleteTextures(1, texture);

	shader.unbind();
}

/**
 *	Reference from http://www.keithlantz.net/2011/10/rendering-a-skybox-using-a-cube-map-with-opengl-and-glsl/
 *	Seems image are coming from here
 *	http://forums.epicgames.com/threads/506748-My-skies-and-and-cliff-textures-(large-images
 *	Modified by Elvis.
 */
void draw_cubemap()
{
	Shader shader;
	shader.init("shader_src/CubeMap.vert", "shader_src/CubeMap.frag");
	shader.bind();

	unsigned int texture[2];
	glActiveTexture(GL_TEXTURE0);
	if ( LoadCubeMap("data/sky_cube/xneg.bmp", "data/sky_cube/yneg.bmp", "data/sky_cube/zneg.bmp",
					 "data/sky_cube/xpos.bmp", "data/sky_cube/ypos.bmp", "data/sky_cube/zpos.bmp",
					 &texture[0]) != 0 ) {
		printf("Fail to load image\n");
		exit(1);
    }

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

    glViewport(0,0,1024,768);
	glClearColor(0.0,0.0,0.0,1.0);
	glClearDepthf(1.0);

	int v_coord_loc = glGetAttribLocation(shader.id(), "obj_vertex");
	int mvp_loc = glGetUniformLocation(shader.id(), "MVP");
	int cubemap_loc = glGetUniformLocation(shader.id(), "cubemap");

	glm::mat4 Projection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 100.0f);
//	glm::mat4 View       = glm::mat4(1.0f);
	glm::mat4 View = glm::lookAt(
						glm::vec3(-0.4f, -0.5f, -0.5f),          // Camera position in World space
						glm::vec3(0,0,0), // and looks at the origin
						glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
					);
	glm::mat4 Model      = glm::scale(glm::mat4(1.0f),glm::vec3(0.5,0.5,0.5));
	glm::mat4 MVP		 = Projection * View * Model;

	GLfloat cube_vertices[] = {
	  -1.0,  1.0,  1.0,
	  -1.0, -1.0,  1.0,
	   1.0, -1.0,  1.0,
	   1.0,  1.0,  1.0,
	  -1.0,  1.0, -1.0,
	  -1.0, -1.0, -1.0,
	   1.0, -1.0, -1.0,
	   1.0,  1.0, -1.0,
	};

	glUniformMatrix4fv(mvp_loc, 1, 0, &MVP[0][0]);
	for (int i=0; i<4; i++)
		printf("%f %f %f %f\n", *(&MVP[0][i]), *(&MVP[1][i]), *(&MVP[2][i]), *(&MVP[3][i]));
	printf("\n");

	glUniform1i(cubemap_loc, 0);

	glVertexAttribPointer(v_coord_loc, 3, GL_FLOAT, GL_FALSE, 0, cube_vertices);
    glEnableVertexAttribArray(v_coord_loc);

	GLushort cube_indices[] = {
	  0, 1, 2, 3,
	  3, 2, 6, 7,
	  7, 6, 5, 4,
	  4, 5, 1, 0,
	  0, 3, 7, 4,
	  1, 2, 6, 5,
	};

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, &cube_indices[0]);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, &cube_indices[4]);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, &cube_indices[8]);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, &cube_indices[12]);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, &cube_indices[16]);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, &cube_indices[20]);

	glDeleteTextures(1, texture);

	shader.unbind();
}

int main()
{
    //Initial a new context, need to be hidden after egl or glfw library is imported.
    Context::SetCurrentContext(new Context());

//	draw_road();
//	draw_banana();
	draw_cubemap();

	Context::GetCurrentContext()->DumpImage();
}
