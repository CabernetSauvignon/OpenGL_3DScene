#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "glad/glad.h"

class Shader
{
	// Поля класса
public:
	GLuint programID; // Шейдерная программа

	// Методы класса
private:
	void checkCompileErrors(unsigned int shader, std::string type);
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometyPath);
	~Shader();
	void UseProgram(); // Использовать шейдерную программу
	void DetachProgram(); // Деактивировать шейдерную программу

	// Функции для работы с юниформами
	void Set_Float1_Uniform(const std::string& name, GLfloat v0) const;
	void Set_Float2_Uniform(const std::string& name, GLfloat v0, GLfloat v1) const;
	void Set_Float3_Uniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2) const;
	void Set_Float4_Uniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const;

	void Set_Int1_Uniform(const std::string& name, GLint v0) const;
	void Set_Int2_Uniform(const std::string& name, GLint v0, GLint v1) const;
	void Set_Int3_Uniform(const std::string& name, GLint v0, GLint v1, GLint v2) const;
	void Set_Int4_Uniform(const std::string& name, GLint v0, GLint v1, GLint v2, GLint v3) const;

	void Set_Uint1_Uniform(const std::string& name, GLuint v0) const;
	void Set_Uint2_Uniform(const std::string& name, GLuint v0, GLuint v1) const;
	void Set_Uint3_Uniform(const std::string& name, GLuint v0, GLuint v1, GLuint v2) const;
	void Set_UInt4_Uniform(const std::string& name, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const;

	void Set_Float1v_Uniform(const std::string& name, GLsizei count, const GLfloat* value) const;
	void Set_Float2v_Uniform(const std::string& name, GLsizei count, const GLfloat* value) const;
	void Set_Float3v_Uniform(const std::string& name, GLsizei count, const GLfloat* value) const;
	void Set_Float4v_Uniform(const std::string& name, GLsizei count, const GLfloat* value) const;

	void Set_Int1v_Uniform(const std::string& name, GLsizei count, const GLint* value) const;
	void Set_Int2v_Uniform(const std::string& name, GLsizei count, const GLint* value) const;
	void Set_Int3v_Uniform(const std::string& name, GLsizei count, const GLint* value) const;
	void Set_Int4v_Uniform(const std::string& name, GLsizei count, const GLint* value) const;

	void Set_Uint1v_Uniform(const std::string& name, GLsizei count, const GLuint* value) const;
	void Set_Uint2v_Uniform(const std::string& name, GLsizei count, const GLuint* value) const;
	void Set_Uint3v_Uniform(const std::string& name, GLsizei count, const GLuint* value) const;
	void Set_UInt4v_Uniform(const std::string& name, GLsizei count, const GLuint* value) const;

	void Set_Matrix2fv_Uniform(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) const;
	void Set_Matrix3fv_Uniform(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) const;
	void Set_Matrix4fv_Uniform(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) const;
	void Set_Matrix2x3fv_Uniform(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) const;
	void Set_Matrix3x2fv_Uniform(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) const;
	void Set_Matrix2x4fv_Uniform(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) const;
	void Set_Matrix4x2fv_Uniform(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) const;
	void Set_Matrix3x4fv_Uniform(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) const;
	void Set_Matrix4x3fv_Uniform(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) const;
};

