#pragma once
#include <GL/glew.h> // Przyk³ad dla GLEW, dla GLuint
#include <glm/glm.hpp>
#include <utility>
#include "shaderprogram.h" // Jeœli ShaderProgram jest u¿ywany w deklaracjach funkcji poni¿ej

// --- DEKLARACJE zmiennych ---
// Informujemy, ¿e te zmienne istniej¹ gdzieœ indziej (w .cpp)

// Wymiary mo¿na zdefiniowaæ jako const jeœli siê nie zmieniaj¹,
// albo przekazywaæ jako parametry do funkcji/konstruktora klasy.
// Jeœli s¹ globalne i modyfikowalne, to tak:
// extern float aquarium_width; 
// extern float aquarium_height;
// ... itd.
// Ale czêsto lepiej przekszta³ciæ je w sta³e lub parametry.

// Dla danych wierzcho³ków:
extern const int myAquariumVertexCount; // Liczba wierzcho³ków mo¿e byæ const
extern float myAquariumVertices[];      // Tablica wierzcho³ków (bez rozmiaru tutaj)
extern float myAquariumTexCoords[];   // Tablica wspó³rzêdnych tekstur
extern float myAquariumColors[];      // Tablica kolorów (jeœli u¿ywasz)


// --- DEKLARACJE funkcji ---
// Funkcja inicjalizuj¹ca dane (np. texCoords, colors), jeœli potrzeba
void initMyAquariumData(); // Pamiêtaj o zdefiniowaniu jej w .cpp!

// Funkcja rysuj¹ca
void drawAquarium(ShaderProgram *sp, GLuint tex, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float localRotationAngleY = 0.0f);
void drawWater(ShaderProgram* sp, GLuint tex, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float localRotationAngleY = 0.0f);