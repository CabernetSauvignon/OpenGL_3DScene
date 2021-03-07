#include "Shader.h"

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // Получение исходного кода вершинного/фрагментного шейдера
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    // Убеждаемся, что объекты ifstream могут выбросить исключение
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // Открываем файлы
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // Считываем содержимое файловых буферов в потоки 
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        // Закрываем файлы
        vertexShaderFile.close();
        fragmentShaderFile.close();

        // Конвертируем данные из потока в строковые переменные
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vertexShaderCode = vertexCode.c_str();
    const char* fragmentShaderCode = fragmentCode.c_str();

    // Компилируем шейдеры
    unsigned int vertexShader, fragmentShader;

    // Вершинный шейдер
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");

    // Фрагментный шейдер
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    // Шейдерная программа
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);
    checkCompileErrors(programID, "PROGRAM");

    // После того, как мы связали шейдеры с нашей программой, удаляем их, так как они нам больше не нужны
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
    // Получение исходного кода вершинного/фрагментного шейдера
    std::string vertexCode;
    std::string geometryCode;
    std::string fragmentCode;
    std::ifstream vertexShaderFile;
    std::ifstream geometryShaderFile;
    std::ifstream fragmentShaderFile;

    // Убеждаемся, что объекты ifstream могут выбросить исключение
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    geometryShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // Открываем файлы
        vertexShaderFile.open(vertexPath);
        geometryShaderFile.open(geometryPath);
        fragmentShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, gShaderStream, fShaderStream;

        // Считываем содержимое файловых буферов в потоки 
        vShaderStream << vertexShaderFile.rdbuf();
        gShaderStream << geometryShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        // Закрываем файлы
        vertexShaderFile.close();
        geometryShaderFile.close();
        fragmentShaderFile.close();

        // Конвертируем данные из потока в строковые переменные
        vertexCode = vShaderStream.str();
        geometryCode = gShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vertexShaderCode = vertexCode.c_str();
    const char* geometryShaderCode = geometryCode.c_str();
    const char* fragmentShaderCode = fragmentCode.c_str();

    // Компилируем шейдеры
    unsigned int vertexShader, geometryShader, fragmentShader;

    // Вершинный шейдер
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");

    // Геометрический шейдер
    geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &geometryShaderCode, NULL);
    glCompileShader(geometryShader);
    checkCompileErrors(geometryShader, "GEOMETRY");

    // Фрагментный шейдер
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    // Шейдерная программа
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, geometryShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);
    checkCompileErrors(programID, "PROGRAM");

    // После того, как мы связали шейдеры с нашей программой, удаляем их, так как они нам больше не нужны

    glDeleteShader(vertexShader);
    glDeleteShader(geometryShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(programID);
}

// Использовать шейдерную программу
void Shader::UseProgram()
{
    glUseProgram(programID);
}
// Деактивировать шейдерную программу
void Shader::DetachProgram()
{
    glUseProgram(0);
}

// Функции для работы с юниформами
void Shader::Set_Float1_Uniform(const std::string& name, GLfloat v0) const
{
    glUniform1f(glGetUniformLocation(programID, name.c_str()), v0);
}

void Shader::Set_Float2_Uniform(const std::string& name, GLfloat v0, GLfloat v1) const
{
    glUniform2f(glGetUniformLocation(programID, name.c_str()), v0, v1);
}

void Shader::Set_Float3_Uniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2) const
{
    glUniform3f(glGetUniformLocation(programID, name.c_str()), v0, v1, v2);
}

void Shader::Set_Float4_Uniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const
{
    glUniform4f(glGetUniformLocation(programID, name.c_str()), v0, v1, v2, v3);
}

void Shader::Set_Int1_Uniform(const std::string& name, GLint v0) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), v0);
}

void Shader::Set_Int2_Uniform(const std::string& name, GLint v0, GLint v1) const
{
    glUniform2i(glGetUniformLocation(programID, name.c_str()), v0, v1);
}

void Shader::Set_Int3_Uniform(const std::string& name, GLint v0, GLint v1, GLint v2) const
{
    glUniform3i(glGetUniformLocation(programID, name.c_str()), v0, v1, v2);
}

void Shader::Set_Int4_Uniform(const std::string& name, GLint v0, GLint v1, GLint v2, GLint v3) const
{
    glUniform4i(glGetUniformLocation(programID, name.c_str()), v0, v1, v2, v3);
}

void Shader::Set_Uint1_Uniform(const std::string& name, GLuint v0) const
{
    glUniform1ui(glGetUniformLocation(programID, name.c_str()), v0);
}

void Shader::Set_Uint2_Uniform(const std::string& name, GLuint v0, GLuint v1) const
{
    glUniform2ui(glGetUniformLocation(programID, name.c_str()), v0, v1);
}

void Shader::Set_Uint3_Uniform(const std::string& name, GLuint v0, GLuint v1, GLuint v2) const
{
    glUniform3ui(glGetUniformLocation(programID, name.c_str()), v0, v1, v2);
}

void Shader::Set_UInt4_Uniform(const std::string& name, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const
{
    glUniform4ui(glGetUniformLocation(programID, name.c_str()), v0, v1, v2, v3);
}

void Shader::Set_Float1v_Uniform(const std::string& name, GLsizei count, const GLfloat* value) const
{
    glUniform1fv(glGetUniformLocation(programID, name.c_str()), count, value);
}

void Shader::Set_Float2v_Uniform(const std::string& name, GLsizei count, const GLfloat* value) const
{
    glUniform2fv(glGetUniformLocation(programID, name.c_str()), count, value);
}

void Shader::Set_Float3v_Uniform(const std::string& name, GLsizei count, const GLfloat* value) const
{
    glUniform3fv(glGetUniformLocation(programID, name.c_str()), count, value);
}

void Shader::Set_Float4v_Uniform(const std::string& name, GLsizei count, const GLfloat* value) const
{
    glUniform4fv(glGetUniformLocation(programID, name.c_str()), count, value);
}

void Shader::Set_Int1v_Uniform(const std::string& name, GLsizei count, const GLint* value) const
{
    glUniform1iv(glGetUniformLocation(programID, name.c_str()), count, value);
}

void Shader::Set_Int2v_Uniform(const std::string& name, GLsizei count, const GLint* value) const
{
    glUniform2iv(glGetUniformLocation(programID, name.c_str()), count, value);
}

void Shader::Set_Int3v_Uniform(const std::string& name, GLsizei count, const GLint* value) const
{
    glUniform3iv(glGetUniformLocation(programID, name.c_str()), count, value);
}

void Shader::Set_Int4v_Uniform(const std::string& name, GLsizei count, const GLint* value) const
{
    glUniform4iv(glGetUniformLocation(programID, name.c_str()), count, value);
}

void Shader::Set_Uint1v_Uniform(const std::string& name, GLsizei count, const GLuint* value) const
{
    glUniform1uiv(glGetUniformLocation(programID, name.c_str()), count, value);
}

void Shader::Set_Uint2v_Uniform(const std::string& name, GLsizei count, const GLuint* value) const
{
    glUniform2uiv(glGetUniformLocation(programID, name.c_str()), count, value);
}

void Shader::Set_Uint3v_Uniform(const std::string& name, GLsizei count, const GLuint* value) const
{
    glUniform3uiv(glGetUniformLocation(programID, name.c_str()), count, value);
}

void Shader::Set_UInt4v_Uniform(const std::string& name, GLsizei count, const GLuint* value) const
{
    glUniform4uiv(glGetUniformLocation(programID, name.c_str()), count, value);
}

void Shader::Set_Matrix2fv_Uniform(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) const
{
    glUniformMatrix2fv(glGetUniformLocation(programID, name.c_str()), count, transpose, value);
}

void Shader::Set_Matrix3fv_Uniform(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) const
{
    glUniformMatrix3fv(glGetUniformLocation(programID, name.c_str()), count, transpose, value);
}

void Shader::Set_Matrix4fv_Uniform(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) const
{
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), count, transpose, value);
}

void Shader::Set_Matrix2x3fv_Uniform(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) const
{
    glUniformMatrix2x3fv(glGetUniformLocation(programID, name.c_str()), count, transpose, value);
}

void Shader::Set_Matrix3x2fv_Uniform(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) const
{
    glUniformMatrix3x2fv(glGetUniformLocation(programID, name.c_str()), count, transpose, value);
}

void Shader::Set_Matrix2x4fv_Uniform(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) const
{
    glUniformMatrix2x4fv(glGetUniformLocation(programID, name.c_str()), count, transpose, value);
}

void Shader::Set_Matrix4x2fv_Uniform(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) const
{
    glUniformMatrix4x2fv(glGetUniformLocation(programID, name.c_str()), count, transpose, value);
}

void Shader::Set_Matrix3x4fv_Uniform(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) const
{
    glUniformMatrix3x4fv(glGetUniformLocation(programID, name.c_str()), count, transpose, value);
}

void Shader::Set_Matrix4x3fv_Uniform(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value) const
{
    glUniformMatrix4x3fv(glGetUniformLocation(programID, name.c_str()), count, transpose, value);
}