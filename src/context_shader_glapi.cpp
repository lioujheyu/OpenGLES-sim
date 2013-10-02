/* 
 * Copyright (c) 2013, Liou Jhe-Yu <lioujheyu@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 *	@file context_shader_glapi.cpp
 *  @brief OpenGL ES 2.0 Shader-Related API Layer Implementation
 *  @author Liou Jhe-Yu (lioujheyu@gmail.com)
 */

#include "context.h"

void Context::AttachShader(GLuint program, GLuint shader)
{
	if (shaderPool.find(shader) == shaderPool.end())
		RecordError(GL_INVALID_VALUE);
	else if (programPool.find(program) == programPool.end())
		RecordError(GL_INVALID_VALUE);
	///check if the shader has been already attached to the program
	else if (programPool[program].sid4VS == shader)
		RecordError(GL_INVALID_OPERATION);
	else if (programPool[program].sid4FS == shader)
		RecordError(GL_INVALID_OPERATION);
	else {
		switch (shaderPool[shader].type) {
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
}

GLuint Context::CreateProgram(void)
{
	programObject t_program;

	for (int pid=1;; pid++) {
		if (programPool.find(pid) == programPool.end()) {
			programPool[pid] = t_program;
			return pid;
		}
	}
}

GLint Context::CreateShader(GLenum type)
{
	if ((type != GL_VERTEX_SHADER) && (type!= GL_FRAGMENT_SHADER)) {
		RecordError(GL_INVALID_ENUM);
		return 0;
	}

	shaderObject t_shader;
	t_shader.type = type;

	for (int sid=1;; sid++) {
		if (shaderPool.find(sid) == shaderPool.end()) {
			shaderPool[sid] = t_shader;
			return sid;
		}
	}
}

/**
 *	@brief Compile source in shaderObject
 *
 *	The procedure will write vertex shader or fragment shader source into
 *	.vssrc or .fssrc file, and then use cgc to compile them and write the
 *	assembly output in .vsasm or .fsasm file. Finally read these asm source
 *	from file as string input back into shader object.
 */
void Context::CompileShader(GLuint shader)
{
	if (shaderPool.find(shader) == shaderPool.end()) {
		RecordError(GL_INVALID_VALUE);
		return;
	}

	if (shaderPool[shader].isCompiled == GL_TRUE)
		return;

	FILE *shaderFile;

	std::string fileName, cFileName;
	std::string compileCmd, fileIdx;

	fileIdx.append(std::to_string((int)shader));

	if (shaderPool[shader].type == GL_VERTEX_SHADER) {
		fileName = fileIdx + ".vssrc";
		cFileName = fileIdx + ".vsasm";
	}
	else {
		fileName = fileIdx + ".fssrc";
		cFileName = fileIdx + ".fsasm";
	}

	shaderFile = fopen(fileName.c_str(),"w");
	fprintf(shaderFile,shaderPool[shader].src.c_str());
	fclose(shaderFile);

	compileCmd = "cgc -q -oglsl -o ";
	compileCmd+=cFileName;
	if (shaderPool[shader].type == GL_VERTEX_SHADER)
		compileCmd.append(" -profile gp4vp ");
	else
		compileCmd.append(" -profile gp4fp ");
	compileCmd+=fileName;

	//compiler error or something happened make output there.
	if (system(compileCmd.c_str()) != 0)
		exit(1);

	//Get Assembly code
	std::ifstream ift;
	ift.open(cFileName, std::ifstream::in);
	std::stringstream buffer;
	buffer << ift.rdbuf();
	shaderPool[shader].asmSrc = (buffer.str());
	shaderPool[shader].isCompiled = GL_TRUE;
}

void Context::DeleteProgram(GLuint program)
{
	if (programPool.find(program) == programPool.end())
		RecordError(GL_INVALID_VALUE);
	else if (usePID == program)
		programPool[program].delFlag = GL_TRUE;
	else {
		if (programPool[program].sid4VS != 0)
			DetachShader(program,programPool[program].sid4VS);

		if (programPool[program].sid4FS != 0)
			DetachShader(program,programPool[program].sid4FS);

		programPool.erase(program);
	}
}

void Context::DeleteShader(GLuint shader)
{
	if (shaderPool.find(shader) == shaderPool.end())
		RecordError(GL_INVALID_VALUE);
	else {
		if (shaderPool[shader].attachList.empty())
			shaderPool.erase(shader);
		else
			shaderPool[shader].delFlag = GL_TRUE;
	}
}

void Context::DetachShader(GLuint program, GLuint shader)
{
	std::vector<GLuint>::iterator it;

	if (shaderPool.find(shader) == shaderPool.end())
		RecordError(GL_INVALID_VALUE);
	else if (programPool.find(program) == programPool.end())
		RecordError(GL_INVALID_VALUE);
	else {
		it = std::find(shaderPool[shader].attachList.begin(),
					shaderPool[shader].attachList.end(),
					program );

		if (it == shaderPool[shader].attachList.end())
			RecordError(GL_INVALID_OPERATION);
		else {
			shaderPool[shader].attachList.erase(it);
			if (shaderPool[shader].delFlag == GL_TRUE)
				DeleteShader(shader);

			if (programPool[program].sid4VS == shader)
				programPool[program].sid4VS = 0;
			else
				programPool[program].sid4FS = 0;

			programPool[program].LinkInit();
		}
	}
}

int Context::GetAttribLocation (GLuint program, const GLchar* name)
{
	if (programPool.find(program) == programPool.end()) {
		RecordError(GL_INVALID_OPERATION);
		return -1;
	}
	else if (programPool[program].isLinked == GL_FALSE) {
		RecordError(GL_INVALID_OPERATION);
		return -1;
	}
	else if (programPool[program].srcVSin.find(name) ==
			 programPool[program].srcVSin.end()) {
		//RecordError(GL_INVALID_OPERATION);
		return -1;
	}
	else{
		if (programPool[program].srcVSin[name].name.compare(0,3,"gl_") == 0)
			return -1;
		else {
			return programPool[program].srcVSin[name].idx;
		}
	}
}

void Context::GetProgramiv (GLuint program, GLenum pname, GLint* params)
{
	int value = 0;

	if (programPool.find(program) == programPool.end())
		RecordError(GL_INVALID_VALUE);
	else {
		switch (pname) {
		case GL_DELETE_STATUS:
			*params = programPool[program].delFlag;
			break;
		case GL_LINK_STATUS:
			*params = programPool[program].isLinked;
			break;
		case GL_VALIDATE_STATUS:
			*params = programPool[program].isLinked;
			break;
		case GL_INFO_LOG_LENGTH:
			programPool[program].linkInfo.length();
			break;
		case GL_ATTACHED_SHADERS:
			if (programPool[program].sid4VS != 0)
				value++;
			if (programPool[program].sid4FS != 0)
				value++;
			*params = value;
			break;
		case GL_ACTIVE_ATTRIBUTES:
			break;
		case GL_ACTIVE_ATTRIBUTE_MAX_LENGTH:
			break;
		case GL_ACTIVE_UNIFORMS:
			break;
		case GL_ACTIVE_UNIFORM_MAX_LENGTH:
			break;
		default:
			RecordError(GL_INVALID_ENUM);
			return;
		}
	}
}

void Context::GetShaderiv (GLuint shader, GLenum pname, GLint* params)
{
	if (shaderPool.find(shader) == shaderPool.end()) {
		RecordError(GL_INVALID_VALUE);
		return;
	}
}

int Context::GetUniformLocation (GLuint program, const GLchar* name)
{
	if (programPool.find(program) == programPool.end()) {
		RecordError(GL_INVALID_OPERATION);
		return -1;
	}
	else if (programPool[program].isLinked == GL_FALSE) {
		RecordError(GL_INVALID_OPERATION);
		return -1;
	}
	else if (std::string(name).compare(0,3,"gl_") == 0)
		return -1;

	if (programPool[program].srcUniform.find(name) ==
		programPool[program].srcUniform.end()) {
		if (programPool[program].srcTexture.find(name) ==
			programPool[program].srcTexture.end())
			return -1;
		else{
			return (programPool[program].srcTexture[name].idx +
					MAX_VERTEX_UNIFORM_VECTORS +
					MAX_FRAGMENT_UNIFORM_VECTORS);
		}
	}
	else
		return programPool[program].srcUniform[name].idx;
}

GLboolean Context::IsProgram(GLuint program)
{
	return (programPool.find(program) != programPool.end());
}

GLboolean Context::IsShader(GLuint shader)
{
	return (shaderPool.find(shader) != shaderPool.end());
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

	GLint* lengthCnt = new GLint[count];

	std::string t_string;
	shaderPool[shader].count = count;

	if (length == NULL) {
		for (int i=0; i < count; i++) {
			for (lengthCnt[i]=0; *(*(string+i)+lengthCnt[i]) != '\0'; lengthCnt[i]++)
				t_string.push_back(*(*(string+i)+lengthCnt[i]));

			shaderPool[shader].src.append(t_string);
		}
	}
	else {
		for (int i = 0; i < count; i++) {
			if (length[i] == '\0') {
				for (lengthCnt[i]=0; *(*(string+i)+lengthCnt[i]) != '\0'; lengthCnt[i]++)
					t_string.push_back(*(*(string+i)+lengthCnt[i]));
			}
			else
				t_string.append(*(string+i),length[i]);

			shaderPool[shader].src.append(t_string);
		}
	}

	shaderPool[shader] = shaderPool[shader];
}

void Context::UseProgram(GLuint program)
{
	//Spec defines if program = 0 is not an error. It means to clean use state.
	if (program == 0)
		usePID = program;
	else if (programPool.find(program) == programPool.end())
		RecordError(GL_INVALID_VALUE);
	else if (programPool[program].isLinked == GL_FALSE)
		RecordError(GL_INVALID_OPERATION);
	else
		usePID = program;
}

void Context::ValidateProgram(GLuint program)
{
	/// @todo ValidateProgram is unfinished
	if (programPool.find(program) == programPool.end()) {
		RecordError(GL_INVALID_VALUE);
		return;
	}
}
