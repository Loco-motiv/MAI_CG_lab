#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& error)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << error.what() << std::endl;
    }

    const GLchar* vertexShaderCode   = vertexCode.c_str();
    const GLchar* fragmentShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    // vertex shader
    GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexID);
    CheckCompileErrors(vertexID, "VERTEX");

    // fragment Shader
    GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentID);
    CheckCompileErrors(fragmentID, "FRAGMENT");

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertexID);
    glAttachShader(ID, fragmentID);
    glLinkProgram(ID);
    CheckCompileErrors(ID, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}

void Shader::Use()
{
    glUseProgram(ID);
}

void Shader::SetBool(const std::string& name, const GLboolean value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, const GLint value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, const GLfloat value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloatMatrix(const std::string& name, const GLfloat* matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, matrix);
}

void Shader::CheckCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLint length;
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
            if (length > 0)
            {
                GLchar* info(new GLchar[length]);
                glGetShaderInfoLog(shader, length, 0, info);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                          << info << " -- --------------------------------------------------- -- " << std::endl;
                delete[] info;
            }
            else
            {
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type
                          << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
            if (length > 0)
            {
                GLchar* info(new GLchar[length]);
                glGetShaderInfoLog(shader, length, 0, info);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                          << info << " -- --------------------------------------------------- -- " << std::endl;
                delete[] info;
            }
            else
            {
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type
                          << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
}