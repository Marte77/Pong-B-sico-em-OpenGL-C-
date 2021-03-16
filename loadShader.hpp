
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <ios>
#include <sstream>  
#include <string>  
#include <vector>
#include <stdio.h>
#include <stdlib.h>

GLuint CarregarShaders(const char* path_vertex, const char* path_fragment) {
	//criar os shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//ler os shaders dos ficheiros
		//ler vertexshader
	std::string vertexshaderCod;
	std::ifstream vertexshaderStream(path_vertex, std::ios::in);
	if (vertexshaderStream.is_open()) {
		std::stringstream sstr;
		sstr << vertexshaderStream.rdbuf();
		vertexshaderCod = sstr.str();
		vertexshaderStream.close();
	}
	else {
		std::cout << "impossivel abrir o ficheiro vertexshader path:" << path_vertex << std::endl;
		return 0;
	}
	std::string fragmentshaderCod;
	std::ifstream fragmentshaderStream(path_fragment, std::ios::in);
	if (fragmentshaderStream.is_open()) {
		std::stringstream sstr;
		sstr << fragmentshaderStream.rdbuf();
		fragmentshaderCod = sstr.str();
		fragmentshaderStream.close();
	}
	else {
		std::cout << "impossivel abrir o ficheiro fragmentshader path:" << path_fragment << std::endl;
		return 0;
	}

	GLint resultado = GL_FALSE;
	int logLenght;
	//compilar vertexshader
	std::cout << "vou compilar o vertexshader path:" << path_vertex << std::endl;
	char const* vertexSourcePonteiro = vertexshaderCod.c_str();
	glShaderSource(VertexShaderID, 1, &vertexSourcePonteiro, NULL);
	glCompileShader(VertexShaderID);

	//verificar vertexshader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &resultado);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &logLenght);
	if (logLenght > 0) {
		std::vector<char> VertexShaderErrorMessage(logLenght + 1);
		glGetShaderInfoLog(VertexShaderID, logLenght, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	//compilar fragmentshader
	std::cout << "vou compilar o fragmentshader path:" << path_fragment << std::endl;
	char const* fragmentSourcePTR = fragmentshaderCod.c_str();
	glShaderSource(FragmentShaderID, 1, &fragmentSourcePTR, NULL);
	glCompileShader(FragmentShaderID);
	//verificar fragmentshader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &resultado);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &logLenght);
	if (logLenght > 0) {
		std::vector<char> FragmentShaderErrorMessage(logLenght + 1);
		glGetShaderInfoLog(FragmentShaderID, logLenght, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	//linkar o programa e os shaders
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	//verificar programa
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &resultado);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &logLenght);
	if (logLenght > 0) {
		std::vector<char> ProgramErrorMessage(logLenght + 1);
		glGetProgramInfoLog(ProgramID, logLenght, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	return ProgramID;
}

