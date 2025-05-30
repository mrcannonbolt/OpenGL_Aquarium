#pragma once

#include "ShaderProgram.h" 
#include <glm/glm.hpp>
#include <GL/glew.h>

void drawMyFish(ShaderProgram* sp, GLuint tex, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float rotationY);
