#include "Shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath,const char* tessellationControlPath, const char* tessellationEvaluationPath, const char* geometryPath)
{
	//Get all the shader codes
	std::string VertexShaderCode = readShader(vertexPath);
	std::string FragmentShaderCode = readShader(fragmentPath);
	std::string tessellationControlCode = readShader(tessellationControlPath);
	std::string tessellationEvaluationCode = readShader(tessellationEvaluationPath);
	std::string geometryCode = readShader(geometryPath);

	//Make the shaders
	GLuint vertex, fragment, tessellationcontrol, tessellationevaluation, geometry;
	GLint success;
	GLchar infoLog[512];
	vertex = glCreateShader(GL_VERTEX_SHADER);
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	//Compile vertex shader
	glShaderSource(vertex, 1, &VertexSourcePointer, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "Error compiling vertex shader: " << infoLog << std::endl;
	}
	//Compile fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(fragment, 1, &FragmentSourcePointer, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "Error compiling fragment shader: " << infoLog << std::endl;
	}
	//Compile tessellation control shader
	tessellationcontrol = glCreateShader(GL_TESS_CONTROL_SHADER);
	char const* TessellationControlSourcePointer = tessellationControlCode.c_str();
	glShaderSource(tessellationcontrol, 1, &TessellationControlSourcePointer, NULL);
	glCompileShader(tessellationcontrol);
	glGetShaderiv(tessellationcontrol, GL_COMPILE_STATUS, &success);
	if (!success)
	{
			glGetShaderInfoLog(tessellationcontrol, 512, NULL, infoLog);
			std::cout << "Error compiling tessellationcontrol shader: " << infoLog << std::endl;
	}\
	//Compile tessellation evaluation shader
	tessellationevaluation = glCreateShader(GL_TESS_EVALUATION_SHADER);
		char const* TessellationEvaluationSourcePointer = tessellationEvaluationCode.c_str();
	glShaderSource(tessellationevaluation, 1, &TessellationEvaluationSourcePointer, NULL);
	glCompileShader(tessellationevaluation);
	glGetShaderiv(tessellationevaluation, GL_COMPILE_STATUS, &success);
	if (!success)
	{
			glGetShaderInfoLog(tessellationevaluation, 512, NULL, infoLog);
			std::cout << "Error compiling tessellationevaluation shader: " << infoLog << std::endl;
	}

	//Compile the geometry shader
	geometry = glCreateShader(GL_GEOMETRY_SHADER);
	char const* geometrySourcePointer = geometryCode.c_str();
	glShaderSource(geometry, 1, &geometrySourcePointer, NULL);
	glCompileShader(geometry);
	glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
	if (!success)
	{
			glGetShaderInfoLog(geometry, 512, NULL, infoLog);
			std::cout << "Error compiling geometry shader: " << infoLog << std::endl;
	}
	//Create shader program
	this->shaderProgram = glCreateProgram();
	//Attach fragment and vertex shader
	if (VertexShaderCode != "") glAttachShader(this->shaderProgram, vertex);
	if (tessellationControlCode != "") glAttachShader(this->shaderProgram, tessellationcontrol);
	if (tessellationEvaluationCode != "") glAttachShader(this->shaderProgram, tessellationevaluation);
	if (geometryCode != "") glAttachShader(this->shaderProgram, geometry);
	if (FragmentShaderCode != "") glAttachShader(this->shaderProgram, fragment);
	glLinkProgram(this->shaderProgram);

	//See if linking was correct
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
			glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
			std::cout << "Error linking shaderprogram: " << infoLog << std::endl;
	}
	//Delete shaders since they are already bind to the program
	glDeleteShader(vertex);
	glDeleteShader(tessellationcontrol);
	glDeleteShader(tessellationevaluation);
	glDeleteShader(geometry);
	glDeleteShader(fragment);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	std::cout << "Shader initialized" << std::endl;
}

Shader::~Shader()
{

}

std::string Shader::readShader(const char* shaderPath)
{
	std::string shaderCode;
	std::ifstream VertexShaderStream(shaderPath);
	if(VertexShaderStream.is_open()){
		//Open shader file
		std::string Line = "";
		while(getline(VertexShaderStream, Line)) {
			shaderCode += "\n" + Line;
			//Push currentline to string
		}
		VertexShaderStream.close();
	}
	return shaderCode;
}

void Shader::Use()
{
	//Bind this shader program
  glUseProgram(shaderProgram);
	
}
