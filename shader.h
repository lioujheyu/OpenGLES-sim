#ifndef __SHADER_H
#define __SHADER_H

#include <cstring>

#include <cstdlib>
#include <GLES3/gl3.h>

class Shader {
public:
	Shader();
	Shader(const char *vsFile, const char *fsFile);
	~Shader();

    void init(const char *vsFile, const char *fsFile);

	void bind();
	void unbind();

	unsigned int id();

private:
	unsigned int shader_id;
	unsigned int shader_vp;
	unsigned int shader_fp;
};

#endif
