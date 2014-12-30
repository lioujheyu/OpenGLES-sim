#ifndef __SHADER_H
#define __SHADER_H

#include <cstring>

#include <cstdlib>

#ifdef GLES
#	include <GLES3/gl3.h>
#else
#	include <GL/glew.h>
#endif // GLES

class Shader {
public:
	Shader();
	Shader(const char *vsFile, const char *fsFile);
	~Shader();

    void init(const char *vsFile, const char *fsFile);
    void initASM(const char *vsFileASM, const char *fsFileASM);

	void bind();
	void unbind();

	unsigned int id();

private:
	unsigned int shader_id;
	unsigned int shader_vp;
	unsigned int shader_fp;
};

#endif
