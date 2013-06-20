#include "context.h"



/*****************************************

    OpenGL ES 2.0 API Layer Implemention

*****************************************/

void Context::ActiveTexture(GLenum texture)
{
    if (texture < GL_TEXTURE0) {
        RecordError(GL_INVALID_ENUM);
    }

    activeTexture = texture - GL_TEXTURE0;
}

void Context::BindTexture(GLenum target, GLuint texture)
{
	if (target != GL_TEXTURE_2D)
    {
        RecordError(GL_INVALID_ENUM);
        return;
    }

	texContext[activeTexture].texBindID = texture;
}

void Context::Clear(GLbitfield mask)
{
	if ((mask & (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)) != mask) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    clearMask = mask;
    clearStat = true;

    //ActiveGPU2CleanBuffer();
}

void Context::ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    // Set RM's registers
    clearColor.r = red;
    clearColor.g = green;
    clearColor.b = blue;
    clearColor.a = alpha;
}

void Context::ClearDepthf (GLfloat depth)
{
	clearDepth = depth;
}

void Context::DeleteTextures(GLsizei n, const GLuint *textures)
{
    if (n < 0) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    for (int i=0; i<n; ++i) {
        if (texImagePool.find(*(textures+i)) == texImagePool.end())
			continue;

        for (int l=0;l<=texImagePool[*(textures+i)].maxLevel;l++)
			delete[] texImagePool[*(textures+i)].data[l];

        texImagePool.erase(*(textures+i));

        printf("Del texture ID: %d\n",*(textures+i));
    }
}

void Context::DepthRangef(GLfloat n, GLfloat f)
{
    vp.n = (n<0)?0:(n>1)?1:n;
    vp.f = (f<0)?0:(f>1)?1:f;
}

void Context::Disable(GLenum cap)
{
    switch (cap) {
    case GL_BLEND:
        blendEnable = false;
        break;
    case GL_CULL_FACE:
        break;
    case GL_DEPTH_TEST:
        depthTestEnable = false;
        break;
    case GL_DITHER:
        break;
    case GL_POLYGON_OFFSET_FILL:
        break;
    case GL_SAMPLE_ALPHA_TO_COVERAGE:
        break;
    case GL_SCISSOR_TEST:
        break;
    case GL_STENCIL_TEST:
        break;
        ///OpenGL ES 3.0
    case GL_PRIMITIVE_RESTART_FIXED_INDEX:
        break;
    case GL_RASTERIZER_DISCARD:
        break;
    default:
        RecordError(GL_INVALID_VALUE);
        return;
    }
}

void Context::DrawArrays(GLenum mode, GLint first, GLsizei count)
{
    if (usePID == 0) {
		printf("Current program is invalid.\n");
		return;
    }
    else if (programPool[usePID].isLinked == GL_FALSE) {
		printf("Current program is invalid.\n");
		return;
    }

    if (first < 0)
        RecordError(GL_INVALID_VALUE);
    else if (count < 0)
        RecordError(GL_INVALID_VALUE);
    else {
        switch (mode) {
        case GL_TRIANGLES:
        case GL_TRIANGLE_FAN:
        case GL_TRIANGLE_STRIP:
            break;
        case GL_POINTS:
        case GL_LINES:
        case GL_LINE_LOOP:
        case GL_LINE_STRIP:
            printf("draw modes in points and lines are not implemented yet");
            return;
        default:
            RecordError(GL_INVALID_ENUM);
            return;
        }

        drawCmd.mode = mode;
        drawCmd.first = first;
        drawCmd.count = count;
        drawCmd.indices = NULL;
    }

    ActiveGPU();
    clearStat = false;
    DumpImage();
}

void Context::Enable(GLenum cap)
{
    switch (cap) {
    case GL_BLEND:
        blendEnable = true;
        break;
    case GL_CULL_FACE:
        break;
    case GL_DEPTH_TEST:
        depthTestEnable = true;
        break;
    case GL_DITHER:
        break;
    case GL_POLYGON_OFFSET_FILL:
        break;
    case GL_SAMPLE_ALPHA_TO_COVERAGE:
        break;
    case GL_SCISSOR_TEST:
        break;
    case GL_STENCIL_TEST:
        break;
	///OpenGL ES 3.0
    case GL_PRIMITIVE_RESTART_FIXED_INDEX:
        break;
    case GL_RASTERIZER_DISCARD:
        break;
    default:
        RecordError(GL_INVALID_VALUE);
        return;
    }
}

void Context::EnableVertexAttribArray(GLuint index)
{
    if (index >= MAX_ATTRIBUTE_NUMBER) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    vertexAttrib[index].enable = GL_TRUE;
}

void Context::GenerateMipmap(GLenum target)
{
	texContext[activeTexture].genMipmap = GL_TRUE;
}

/// @note (elvis#1#): Searching the free texture id under std::map is not efficient.
void Context::GenTextures(GLsizei n, GLuint* textures)
{
	if (n < 0) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    textureImage texObj;

	int i = 0;
	unsigned int key = 1;
	while(i<n) {
		if (texImagePool.find(key) == texImagePool.end()){
			texImagePool[key] = texObj;
			*(textures+i) = key;
			printf("Gen Texture ID: %d\n",key);

			i++;
			key++;
		}
		else
			key++;
	}
}

GLenum Context::GetError(void)
{
	GLenum errorFlag;

	if (errorStack.empty())
		return GL_NO_ERROR;
	else{
		errorFlag = errorStack.top();
		errorStack.pop();
		return errorFlag;
	}
}

GLboolean Context::IsTexture(GLuint texture)
{
	return (texImagePool.find(texture) != texImagePool.end());
}

void Context::TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
{
	if (target != GL_TEXTURE_2D) {
        RecordError(GL_INVALID_ENUM);
        return;
    }

    if (level < 0 || (float)level > log2f((float)std::max(width,height))) {
        RecordError(GL_INVALID_ENUM);
        return;
    }

    if (border != 0 || width < 64 || height < 64 ) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    GLint externalFormat = (GLint)format;

    /// @todo : check type between internalformat and externalformat
    if (internalformat != externalFormat) {
        RecordError(GL_INVALID_OPERATION);
        return;
    }

    int biSizeImage = width*height;
    unsigned char * image = new unsigned char[biSizeImage*4];

	/// @note (elvis#1#): Unsure format conversion is performed in API implementation or in Hardware
	for (int i=0; i<biSizeImage;i++){
		switch (format) {
		case GL_ALPHA:
			switch (type){
			case GL_UNSIGNED_BYTE:
				image[i*4] = image[i*4+1] = image[i*4+2] = image[i*4+3] = *((unsigned char *)pixels+i);
				break;

			default:
				RecordError(GL_INVALID_OPERATION);
				return;
			}
			break;

		case GL_RGB:
			switch (type){
			case GL_UNSIGNED_BYTE:
				image[i*4]   = *((unsigned char *)pixels+i*3);
				image[i*4+1] = *((unsigned char *)pixels+i*3+1);
				image[i*4+2] = *((unsigned char *)pixels+i*3+2);
				image[i*4+3] = 255;
				break;

			default:
				RecordError(GL_INVALID_OPERATION);
				return;
			}
			break;

		case GL_RGBA:
			switch (type){
			case GL_UNSIGNED_BYTE:
				image[i*4]   = *((unsigned char *)pixels+i*4);
				image[i*4+1] = *((unsigned char *)pixels+i*4+1);
				image[i*4+2] = *((unsigned char *)pixels+i*4+2);
				image[i*4+3] = *((unsigned char *)pixels+i*4+3);
				break;

			default:
				RecordError(GL_INVALID_OPERATION);
				return;
			}
			break;

		case GL_LUMINANCE:
			switch (type){
			case GL_UNSIGNED_BYTE:
				image[i*4] = image[i*4+1] = image[i*4+2] = *((unsigned char *)pixels+i);
				image[i*4+3] = 255;
				break;

			default:
				RecordError(GL_INVALID_OPERATION);
				return;
			}
			break;

		case GL_LUMINANCE_ALPHA:
			switch (type){
			case GL_UNSIGNED_BYTE:
				image[i*4] = image[i*4+1] = image[i*4+2] = *((unsigned char *)pixels+i*2);
				image[i*4+3] = *((unsigned char *)pixels+i*2+1);
				break;

			default:
				RecordError(GL_INVALID_OPERATION);
				return;
			}
			break;

		default:
			RecordError(GL_INVALID_ENUM);
			return;
		}
    }

    //Create default texture object for texture2D if GenTexture() has not be called.
    if(texImagePool.empty())
    {
        textureImage texObj;
        texImagePool[0] = texObj;
		texContext[activeTexture].texBindID = 0;
    }

	// @todo : image data should be copied into buffer of mipmap arrays
	textureImage temp;

    temp.border = border;
    temp.widthLevel[level] = width;
    temp.heightLevel[level] = height;
    temp.maxLevel = (level>temp.maxLevel)?level:temp.maxLevel;

    temp.data[level] = image;

	texImagePool[texContext[activeTexture].texBindID] =temp;
}

void Context::TexParameteri(GLenum target, GLenum pname, GLint param)
{
	if (target != GL_TEXTURE_2D) {
        RecordError(GL_INVALID_ENUM);
        return;
    }

    switch (pname)
    {
    case GL_TEXTURE_MIN_FILTER:
        /*****************************************************
            GL_NEAREST or GL_LINEAR mode : Not apply mipmap

            GL_NEAREST_MIPMAP_NEAREST
            GL_NEAREST_MIPMAP_LINEAR     apply mipmap
            GL_LINEAR_MIPMAP_NEAREST
            GL_LINEAR_MIPMAP_LINEAR
        *****************************************************/
        switch (param){
        case GL_NEAREST:
		case GL_LINEAR:
		case GL_NEAREST_MIPMAP_NEAREST:
		case GL_NEAREST_MIPMAP_LINEAR:
		case GL_LINEAR_MIPMAP_NEAREST:
		case GL_LINEAR_MIPMAP_LINEAR:
			texContext[activeTexture].minFilter = param;
			break;
		default:
			RecordError(GL_INVALID_OPERATION);
			return;
        }

        break;

    case GL_TEXTURE_MAG_FILTER:
        /*****************************************************
            support GL_NEAREST or GL_LINEAR mode
        *****************************************************/
        switch (param){
        case GL_NEAREST:
		case GL_LINEAR:
			texContext[activeTexture].magFilter = param;
			break;
		default:
			RecordError(GL_INVALID_OPERATION);
			return;
        }

        break;

    case GL_TEXTURE_WRAP_S:
        texContext[activeTexture].wrapS = param;
        break;

    case GL_TEXTURE_WRAP_T:
        texContext[activeTexture].wrapT = param;
        break;

/********  OpenGL ES 3.0 ***********/
	case GL_TEXTURE_BASE_LEVEL:
		texContext[activeTexture].baseLevel = param;
		break;

	case GL_TEXTURE_MAX_LEVEL:
		texContext[activeTexture].maxLevel = param;
		break;

	case GL_TEXTURE_MIN_LOD:
		break;

	case GL_TEXTURE_MAX_LOD:
		break;

	case GL_TEXTURE_SWIZZLE_R:
	case GL_TEXTURE_SWIZZLE_G:
	case GL_TEXTURE_SWIZZLE_B:
	case GL_TEXTURE_SWIZZLE_A:
		break;

	case GL_TEXTURE_WRAP_R:
		break;

    default:
        RecordError(GL_INVALID_ENUM);
        break;
    }
}

void Context::Uniform1f (GLint location, GLfloat x)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (location >= (MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS)) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "float") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	uniformPool[location].x = x;
}

void Context::Uniform2f(GLint location, GLfloat x, GLfloat y)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (location >= (MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS)) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "float2") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	uniformPool[location].x = x;
	uniformPool[location].y = y;
}

void Context::Uniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (location >= (MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS)) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "float3") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	uniformPool[location].x = x;
	uniformPool[location].y = y;
	uniformPool[location].z = z;
}

void Context::Uniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (location >= (MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS)) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "float4") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	uniformPool[location].x = x;
	uniformPool[location].y = y;
	uniformPool[location].z = z;
	uniformPool[location].w = w;
}

void Context::Uniform1i(GLint location, GLint x)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "int") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	uniformPool[location].x = (float)x;
}

void Context::Uniform2i(GLint location, GLint x, GLint y)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (location >= (MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS)) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "int2") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	uniformPool[location].x = (float)x;
	uniformPool[location].y = (float)y;
}

void Context::Uniform3i(GLint location, GLint x, GLint y, GLint z)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (location >= (MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS)) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "int3") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	uniformPool[location].x = (float)x;
	uniformPool[location].y = (float)y;
	uniformPool[location].z = (float)z;
}

void Context::Uniform4i(GLint location, GLint x, GLint y, GLint z, GLint w)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (location >= (MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS)) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "int4") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	uniformPool[location].x = (float)x;
	uniformPool[location].y = (float)y;
	uniformPool[location].z = (float)z;
	uniformPool[location].w = (float)w;
}

void Context::Uniform1fv(GLint location, GLsizei count, const GLfloat * value)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (location >= (MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS)) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "float") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (count > 1 && t_program.srcUniform[t_program.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++)
		uniformPool[location+i].x = *(value+i);
}

void Context::Uniform2fv(GLint location, GLsizei count, const GLfloat * value)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (location >= (MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS)) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "float2") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (count > 1 && t_program.srcUniform[t_program.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++) {
		uniformPool[location+i].x = *(value + 2*i);
		uniformPool[location+i].y = *(value + 2*i + 1);
	}
}

void Context::Uniform3fv(GLint location, GLsizei count, const GLfloat * value)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (location >= (MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS)) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "float3") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (count > 1 && t_program.srcUniform[t_program.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++) {
		uniformPool[location+i].x = *(value + 3*i);
		uniformPool[location+i].y = *(value + 3*i + 1);
		uniformPool[location+i].z = *(value + 3*i + 2);
	}
}

void Context::Uniform4fv(GLint location, GLsizei count, const GLfloat * value)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (location >= (MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS)) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "float3") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (count > 1 && t_program.srcUniform[t_program.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++) {
		uniformPool[location+i].x = *(value + 4*i);
		uniformPool[location+i].y = *(value + 4*i + 1);
		uniformPool[location+i].z = *(value + 4*i + 2);
		uniformPool[location+i].w = *(value + 4*i + 3);
	}
}

void Context::Uniform1iv(GLint location, GLsizei count, const GLint * value)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "int") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (count > 1 && t_program.srcUniform[t_program.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++)
		uniformPool[location+i].x = (float)*(value + i);
}

void Context::Uniform2iv(GLint location, GLsizei count, const GLint * value)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (location >= (MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS)) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "int2") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (count > 1 && t_program.srcUniform[t_program.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++) {
		uniformPool[location+i].x = (float)*(value + 2*i);
		uniformPool[location+i].y = (float)*(value + 2*i + 1);
	}
}

void Context::Uniform3iv(GLint location, GLsizei count, const GLint * value)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (location >= (MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS)) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "int3") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (count > 1 && t_program.srcUniform[t_program.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++) {
		uniformPool[location+i].x = (float)*(value + 3*i);
		uniformPool[location+i].y = (float)*(value + 3*i + 1);
		uniformPool[location+i].z = (float)*(value + 3*i + 2);
	}
}

void Context::Uniform4iv(GLint location, GLsizei count, const GLint * value)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (location >= (MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS)) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "int4") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (count > 1 && t_program.srcUniform[t_program.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++) {
		uniformPool[location+i].x = (float)*(value + 4*i);
		uniformPool[location+i].y = (float)*(value + 4*i + 1);
		uniformPool[location+i].z = (float)*(value + 4*i + 2);
		uniformPool[location+i].w = (float)*(value + 4*i + 3);
	}
}

void Context::UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (location >= (MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS)) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "float2x2") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (count > 1 && t_program.srcUniform[t_program.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++) {
		uniformPool[location+ 2*i].x     = *(value + 4*i);
		uniformPool[location+ 2*i].y     = *(value + 4*i + 1);
		uniformPool[location+ 2*i + 1].x = *(value + 4*i + 2);
		uniformPool[location+ 2*i + 1].y = *(value + 4*i + 3);
	}
}

void Context::UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (location >= (MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS)) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "float3x3") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (count > 1 && t_program.srcUniform[t_program.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++) {
		uniformPool[location+ 3*i].x     = *(value + 9*i);
		uniformPool[location+ 3*i].y     = *(value + 9*i + 1);
		uniformPool[location+ 3*i].z     = *(value + 9*i + 2);
		uniformPool[location+ 3*i + 1].x = *(value + 9*i + 3);
		uniformPool[location+ 3*i + 1].y = *(value + 9*i + 4);
		uniformPool[location+ 3*i + 1].z = *(value + 9*i + 5);
		uniformPool[location+ 3*i + 2].x = *(value + 9*i + 6);
		uniformPool[location+ 3*i + 2].y = *(value + 9*i + 7);
		uniformPool[location+ 3*i + 2].z = *(value + 9*i + 8);
	}
}

void Context::UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	programObject t_program = programPool[usePID];

	if (location >= (MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS)) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.uniformUsage.find(location) == t_program.uniformUsage.end()) {
		printf("%d \n",t_program.uniformUsage.size());
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (t_program.srcUniform[t_program.uniformUsage[location]].declareType != "float4x4") {
		RecordError(GL_INVALID_OPERATION);
		return;
	}
	else if (count > 1 && t_program.srcUniform[t_program.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++) {
		uniformPool[location + 4*i].x     = *(value + 16*i);
		uniformPool[location + 4*i].y     = *(value + 16*i + 1);
		uniformPool[location + 4*i].z     = *(value + 16*i + 2);
		uniformPool[location + 4*i].w     = *(value + 16*i + 3);
		uniformPool[location + 4*i + 1].x = *(value + 16*i + 4);
		uniformPool[location + 4*i + 1].y = *(value + 16*i + 5);
		uniformPool[location + 4*i + 1].z = *(value + 16*i + 6);
		uniformPool[location + 4*i + 1].w = *(value + 16*i + 7);
		uniformPool[location + 4*i + 2].x = *(value + 16*i + 8);
		uniformPool[location + 4*i + 2].y = *(value + 16*i + 9);
		uniformPool[location + 4*i + 2].z = *(value + 16*i + 10);
		uniformPool[location + 4*i + 2].w = *(value + 16*i + 11);
		uniformPool[location + 4*i + 3].x = *(value + 16*i + 12);
		uniformPool[location + 4*i + 3].y = *(value + 16*i + 13);
		uniformPool[location + 4*i + 3].z = *(value + 16*i + 14);
		uniformPool[location + 4*i + 3].w = *(value + 16*i + 15);
	}
}

void Context::VertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)
{
    if (size<2 || size>4) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    if (indx >= MAX_ATTRIBUTE_NUMBER) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    switch(type) {
    case GL_SHORT:
    case GL_BYTE:
    case GL_FLOAT:
        break;
    default:
        RecordError(GL_INVALID_ENUM);
        return;
    }

    if (stride < 0) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    vertexAttrib[indx].size = size;
    vertexAttrib[indx].type = type;
    vertexAttrib[indx].normalized = normalized;
    vertexAttrib[indx].stride = stride;
    vertexAttrib[indx].ptr = ptr;
}

void Context::Viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    if (width < 0 || height < 0)
    {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    vp.x = x;
    vp.y = y;
    vp.w = width;
    vp.h = height;

/// @fixme (elvis#1#): dirty buffer setting before buffer management is ready
    drawBuffer[0] = new unsigned char [width*height*4];
    drawBuffer[1] = new float [width*height];
}
