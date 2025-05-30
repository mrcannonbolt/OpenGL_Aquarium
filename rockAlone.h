#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "shaderprogram.h"

// --- DEKLARACJE funkcji ---
void drawStone(ShaderProgram* spStone, GLuint texStone,
    const glm::mat4& parentModelMatrix,
    const glm::vec3& position,
    float scale,
    float localRotationAngleY,
    float stoneLength, float stoneWidth, float stoneHeight);