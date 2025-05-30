#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <utility>
#include "shaderprogram.h"

// --- DEKLARACJE zmiennych ---
extern const int myAquariumVertexCount; // Liczba wierzcho³ków mo¿e byæ const
extern float myAquariumVertices[];      // Tablica wierzcho³ków
extern float myAquariumTexCoords[];   // Tablica wspó³rzêdnych tekstur
extern float myAquariumColors[];      // Tablica kolorów
extern float myAquariumNormals[];

// --- DEKLARACJE funkcji ---
void initMyAquariumData();

// Funkcja rysuj¹ca
void drawAquarium(ShaderProgram *sp, GLuint tex, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float localRotationAngleY = 0.0f);
void drawWater(ShaderProgram* sp, GLuint tex, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float localRotationAngleY = 0.0f);