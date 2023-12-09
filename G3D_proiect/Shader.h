#pragma once
#include "libs.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

class Shader
{
public:
    // constructor generates the shaderStencilTesting on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
   
    // activate the shaderStencilTesting
    // ------------------------------------------------------------------------
    void Use() const;


private:
    void Init(const char* vertexPath, const char* fragmentPath);
    void CheckCompileErrors(unsigned int shaderStencilTesting, std::string type);
private:
    unsigned int ID;
};

