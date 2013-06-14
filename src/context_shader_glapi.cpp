#include "context.h"
#include "context_link_glapi.h"
#include "context_link.tab.h"

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

	switch (shaderPool[shader].type){
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

	for (int pid=1;;pid++){
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

	for (int sid=1;;sid++) {
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

	FILE *shaderFile;

	std::string fileName, cFileName;
	std::string compileCmd, fileIdx;

	for (int i=0; i<shaderPool[shader].count; i++) {
		fileIdx.append("shader_src/");
		fileIdx.append(std::to_string((int)shader));
		fileIdx.push_back('_');
		fileIdx.append(std::to_string(i));

		fileName = cFileName = fileIdx;
		if (shaderPool[shader].type == GL_VERTEX_SHADER) {
			fileName.append(".vstemp");
			cFileName.append(".vsasm");
		}
		else {
			fileName.append(".fstemp");
			cFileName.append(".fsasm");
		}

		shaderFile = fopen(fileName.c_str(),"w");
		fprintf(shaderFile,shaderPool[shader].sourcePool[i].c_str());
		fclose(shaderFile);

		compileCmd.erase(0,std::string::npos);
		compileCmd.append("cgc -oglsl -o ");
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
			shaderPool[shader].compiledSourcePool.push_back(buffer.str());
			shaderPool[shader].isCompiled = GL_TRUE;
		}
		else { /// Compile error or something wrong is happened

		}
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

		if (programPool[program].sid4VS == shader){
			programPool[program].symTableVS.clear();
			programPool[program].sid4VS = 0;
		}
		else {
			programPool[program].sid4FS = 0;
			programPool[program].symTableFS.clear();
		}

		programPool[program].isLinked = GL_FALSE;
	}
}

void Context::GetProgramiv (GLuint program, GLenum pname, GLint* params)
{
	int value = 0;;
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
		for (int i=0;i < count;i++) {
			for (lengthCnt[i]=0; *(*(string+i)+lengthCnt[i]) != '\0'; lengthCnt[i]++)
				t_string.push_back(*(*(string+i)+lengthCnt[i]));

			t_shader.sourcePool.push_back(t_string);
		}
	}
	else {
		for (int i = 0;i < count;i++) {
			if (length[i] == '\0') {
				for (lengthCnt[i]=0; *(*(string+i)+lengthCnt[i]) != '\0'; lengthCnt[i]++)
					t_string.push_back(*(*(string+i)+lengthCnt[i]));
			}
			else
				t_string.append(*(string+i),length[i]);

			t_shader.sourcePool.push_back(t_string);
		}
	}

	shaderPool[shader] = t_shader;
}

void Context::ValidateProgram (GLuint program)
{
	programObject t_program;

	if (programPool.find(program) == programPool.end()) {
		RecordError(GL_INVALID_VALUE);
		return;
	}

	t_program = programPool[program];

	if (t_program.isLinked != GL_TRUE) {
		switch (t_program.linkStatus) {
		case LS_NO_ERROR:
			t_program.linkInfo = "The Program is not yet linked";
			break;
		case LS_SHADER_MISSING:
			t_program.linkInfo = "A vertex shader and a fragment shader are not both present in the program object.";
			break;
		case LS_ATTR_EXCEED:
			t_program.linkInfo = "The number of active attribute variables supported by the implementation has been exceeded.";
			break;
		case LS_UNIFORM_EXCEED:
			t_program.linkInfo = "The number of active uniform variables supported by the implementation has been exceeded.";
			break;
		case LS_MAIN_FUNCTION_MISSING:
			t_program.linkInfo = "The main function is missing for the vertex shader or the fragment shader";
			break;
		case LS_VS_FS_VARRYING_UNMATCH:
			t_program.linkInfo = "A varying variable actually used in the fragment shader is not declared in the same way (or is not declared at all) in the vertex shader.";
			break;
		case LS_DECLARATION_UNRESOLVED:
			t_program.linkInfo = "A reference to a function or variable name is unresolved.";
			break;
		case LS_SHADER_IS_NOT_COMPILED:
			t_program.linkInfo = "One or more of the attached shader objects has not been successfully compiled or loaded with a pre-compiled shader binary.";
			break;
		default:
			break;
		}
	}
	else
		t_program.linkInfo.clear();

	programPool[program] = t_program;
}
