#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <utility>
#include "shaderprogram.h"

// --- DEKLARACJE zmiennych ---
extern const int myAquariumVertexCount; // Liczba wierzcho�k�w mo�e by� const
extern float myAquariumVertices[];      // Tablica wierzcho�k�w
extern float myAquariumTexCoords[];   // Tablica wsp�rz�dnych tekstur
extern float myAquariumColors[];      // Tablica kolor�w
extern float myAquariumNormals[];

// --- DEKLARACJE funkcji ---
void initMyAquariumData();

// Funkcja rysuj�ca
void drawAquarium(ShaderProgram *sp, GLuint tex, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float localRotationAngleY = 0.0f);
void drawWater(ShaderProgram* sp, GLuint tex, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float localRotationAngleY = 0.0f);