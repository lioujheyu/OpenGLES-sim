#include "context.h"
#include "context_link_def.h"

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
	if (programPool[program].sid4VS == shader) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	if (programPool[program].sid4FS == shader) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

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

	fileIdx.append("shader_src/");
	fileIdx.append(std::to_string((int)shader));

	fileName = cFileName = fileIdx;
	if (shaderPool[shader].type == GL_VERTEX_SHADER) {
		fileName.append(".vssrc");
		cFileName.append(".vsasm");
	}
	else {
		fileName.append(".fssrc");
		cFileName.append(".fsasm");
	}

	shaderFile = fopen(fileName.c_str(),"w");
	fprintf(shaderFile,shaderPool[shader].src.c_str());
	fclose(shaderFile);

	compileCmd.append("cgc -q -oglsl -o ");
	compileCmd+=cFileName;
	if (shaderPool[shader].type == GL_VERTEX_SHADER)
		compileCmd.append(" -profile gp4vp ");
	else
		compileCmd.append(" -profile gp4fp ");
	compileCmd+=fileName;
	system(compileCmd.c_str());

	///Get Assembly code
	std::ifstream ift;
	ift.open(cFileName, std::ifstream::in);
	if (ift.is_open()) {
		std::stringstream buffer;
		buffer << ift.rdbuf();
		shaderPool[shader].asmSrc = (buffer.str());
		shaderPool[shader].isCompiled = GL_TRUE;
	}
	else { /// Compile error or something wrong is happened

	}
}

void Context::DeleteProgram(GLuint program)
{
	if (programPool.find(program) == programPool.end()) {
		RecordError(GL_INVALID_VALUE);
		return;
	}
	else if (usePID == program)
		programPool[program].delFlag = GL_TRUE;
	else {
		if (programPool[program].sid4VS != 0)
			DetachShader(program,programPool[program].sid4VS);

		if (programPool[program].sid4FS != 0)
			DetachShader(program,programPool[program].sid4FS);

		programPool.erase(program);
	}

	printf("Delete Program id: %d\n",program);
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

	printf("Delete Shader id: %d\n",shader);
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

		programPool[program].LinkInit();
	}
}

int Context::GetAttribLocation (GLuint program, const GLchar* name)
{
	if (programPool.find(program) == programPool.end()) {
		RecordError(GL_INVALID_OPERATION);
		return -1;
	}

	if (programPool[program].isLinked == GL_FALSE) {
		RecordError(GL_INVALID_OPERATION);
		return -1;
	}

	programObject t_program = programPool[program];

	if (t_program.srcVSin.find(name) == t_program.srcVSin.end())
		return -1;
	else{
		if (t_program.srcVSin[name].name.compare(0,3,"gl_") == 0)
			return -1;
		else {
			return t_program.srcVSin[name].idx;
		}
	}
}

void Context::GetProgramiv (GLuint program, GLenum pname, GLint* params)
{
	int value = 0;
	programObject t_program;

	if (programPool.find(program) == programPool.end()) {
		RecordError(GL_INVALID_VALUE);
		return;
	}

	t_program = programPool[program];

	switch (pname) {
	case GL_DELETE_STATUS:
		*params = t_program.delFlag;
		break;
	case GL_LINK_STATUS:
		*params = t_program.isLinked;
		break;
	case GL_VALIDATE_STATUS:
		*params = t_program.isLinked;
		break;
	case GL_INFO_LOG_LENGTH:
		t_program.linkInfo.length();
		break;
	case GL_ATTACHED_SHADERS:
		if (t_program.sid4VS != 0)
			value++;
		if (t_program.sid4FS != 0)
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

	if (programPool[program].isLinked == GL_FALSE) {
		RecordError(GL_INVALID_OPERATION);
		return -1;
	}

	if (std::string(name).compare(0,3,"gl_") == 0)
		return -1;

	programObject t_program = programPool[program];

	if (t_program.srcUniform.find(name) == t_program.srcUniform.end()) {
		if (t_program.srcTexture.find(name) == t_program.srcTexture.end())
			return -1;
		else{
			return (t_program.srcTexture[name].idx +
					MAX_VERTEX_UNIFORM_VECTORS +
					MAX_FRAGMENT_UNIFORM_VECTORS);
		}
	}
	else
		return t_program.srcUniform[name].idx;
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

	shaderObject t_shader = shaderPool[shader];
	std::string t_string;
	t_shader.count = count;

	if (length == NULL) {
		for (int i=0; i < count; i++) {
			for (lengthCnt[i]=0; *(*(string+i)+lengthCnt[i]) != '\0'; lengthCnt[i]++)
				t_string.push_back(*(*(string+i)+lengthCnt[i]));

			t_shader.src.append(t_string);
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

			t_shader.src.append(t_string);
		}
	}

	shaderPool[shader] = t_shader;
}

void Context::UseProgram(GLuint program)
{
	if (program != 0) {
		if (programPool.find(program) == programPool.end()) {
			RecordError(GL_INVALID_VALUE);
			return;
		}

		if (programPool[program].isLinked == GL_FALSE) {
			RecordError(GL_INVALID_OPERATION);
			return;
		}
	}

	usePID = program;
}

void Context::ValidateProgram(GLuint program)
{
	programObject t_program;

	if (programPool.find(program) == programPool.end()) {
		RecordError(GL_INVALID_VALUE);
		return;
	}

	t_program = programPool[program];
}
