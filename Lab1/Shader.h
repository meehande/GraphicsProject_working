#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


#include <GL/glew.h>

using namespace std;

class Shader {

public:
	GLuint Program;

	//constructor
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath){
		//GET CODE FROM FILE
		string vertexCode;
		string fragmentCode;
		ifstream vShaderFile;
		ifstream fShaderFile;

		vShaderFile.exceptions(ifstream::badbit);
		fShaderFile.exceptions(ifstream::badbit);
		try {
			//open file
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			//create string stream
			stringstream vShaderStream, fShaderStream;
			//read into stream
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//close file
			vShaderFile.close();
			fShaderFile.close();
			//convert stream to string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (ifstream::failure e) {
			cout << "SHADER ERROR: FILE NOT READ SUCCESSFULLY\n";
		}

		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar* fShaderCode = fragmentCode.c_str();

		//COMPILE SHADERS
		GLuint vertex, fragment;
		GLint success;
		GLchar infoLog[512];
		
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if(!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			cout << "SHADER ERROR: VERTEX SHADER NOT COMPILED\n" << vertexPath << endl <<infoLog << endl;
		}

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if(!success) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			cout << "SHADER ERROR: FRAGMENT SHADER NOT COMPILED\n" << fragmentPath << infoLog << endl;
		}

		//SHADER PROGRAM
		this->Program = glCreateProgram();
		glAttachShader(this->Program, vertex);
		glAttachShader(this->Program, fragment);
		glLinkProgram(this->Program);
		glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
		if(!success){
			glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
			cout << "SHADER ERROR: SHADER PROGRAM NOT LINKED\n" << infoLog << endl;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}


	//use this shader program
	void use() {
		glUseProgram(this->Program);
	}


};

#endif