#include "context.h"

/*******************************************************

    OpenGL ES 2.0 Shader-Related API Layer Implemention

********************************************************/

void Context::AttachShader(GLuint program, GLuint shader)
{
	if (shaderPool.find(shader) == shaderPool.end()) {
		RecordError(GL_INVALID_VALUE);
		return;
	}

	if (programPool.find(program) == programPool.end()) {
		RecordError(GL_INVALID_VALUE);
		return;
	}

	///check if the shader has been already attached to the program
	if (programPool[program].sid4VS == shader){
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	if (programPool[program].sid4FS == shader){
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	switch (shaderPool[shader].shaderType){
	case GL_VERTEX_SHADER:
		if (programPool[program].sid4VS == 0) {
			programPool[program].sid4VS = shader;
			shaderPool[shader].attachList.push_back(program);
		}
		else {
			RecordError(GL_INVALID_OPERATION);
			return;
		}
		break;
	case GL_FRAGMENT_SHADER:
		if (programPool[program].sid4FS == 0) {
			programPool[program].sid4FS = shader;
			shaderPool[shader].attachList.push_back(program);
		}
		else {
			RecordError(GL_INVALID_OPERATION);
			return;
		}
		break;
	}
}

GLuint Context::CreateProgram(void)
{
	programObject t_program;

	for (int pid=0;;pid++){
		if (programPool.find(pid) == programPool.end()) {
			programPool[pid] = t_program;
			return pid;
		}
		else
			pid++;
	}
}

GLint Context::CreateShader(GLenum type)
{
	if ((type != GL_VERTEX_SHADER) && (type!= GL_FRAGMENT_SHADER)) {
		RecordError(GL_INVALID_ENUM);
		return 0;
	}

	shaderObject t_shader;
	t_shader.shaderType = type;

	for (int sid=0;;sid++) {
		if (shaderPool.find(sid) == shaderPool.end()) {
			shaderPool[sid] = t_shader;
			return sid;
		}
		else
			sid++;
	}
}

void Context::DeleteProgram(GLuint program)
{
	if (programPool.find(program) == programPool.end()) {
		RecordError(GL_INVALID_VALUE);
		return;
	}
	else if (useProgramID == program)
		programPool[program].delFlag = GL_TRUE;
	else {
		DetachShader(program,programPool[program].sid4VS);
		DetachShader(program,programPool[program].sid4FS);
		programPool.erase(program);
	}
}

void Context::DeleteShader(GLuint shader)
{
    if (shaderPool.find(shader) == shaderPool.end()) {
		RecordError(GL_INVALID_VALUE);
		return;
    }
	else {
		if (shaderPool[shader].attachList.empty())
			shaderPool.erase(shader);
		else
			shaderPool[shader].delFlag = GL_TRUE;
	}
}

void Context::DetachShader(GLuint program, GLuint shader)
{
	if (shaderPool.find(shader) == shaderPool.end()) {
		RecordError(GL_INVALID_VALUE);
		return;
	}

	if (programPool.find(program) == programPool.end()) {
		RecordError(GL_INVALID_VALUE);
		return;
	}

	std::vector<GLuint>::iterator it;
	it = std::find(shaderPool[shader].attachList.begin(),
				   shaderPool[shader].attachList.end(),
				   program );

	if (it == shaderPool[shader].attachList.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else {
		shaderPool[shader].attachList.erase(it);
		if (shaderPool[shader].delFlag == GL_TRUE)
			DeleteShader(shader);

		if (programPool[program].sid4VS == shader)
			programPool[program].sid4VS = 0;
		else
			programPool[program].sid4FS = 0;
	}
}

void Context::ShaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length)
{
	if (shaderPool.find(shader) == shaderPool.end()) {
		RecordError(GL_INVALID_VALUE);
		return;
	}

	if (count < 0) {
		RecordError(GL_INVALID_VALUE);
		return;
	}


}
