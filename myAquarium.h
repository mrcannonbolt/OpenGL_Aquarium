#pragma once
#include <GL/glew.h> // Przyk�ad dla GLEW, dla GLuint
#include <glm/glm.hpp>
#include <utility>
#include "shaderprogram.h" // Je�li ShaderProgram jest u�ywany w deklaracjach funkcji poni�ej

// --- DEKLARACJE zmiennych ---
// Informujemy, �e te zmienne istniej� gdzie� indziej (w .cpp)

// Wymiary mo�na zdefiniowa� jako const je�li si� nie zmieniaj�,
// albo przekazywa� jako parametry do funkcji/konstruktora klasy.
// Je�li s� globalne i modyfikowalne, to tak:
// extern float aquarium_width; 
// extern float aquarium_height;
// ... itd.
// Ale cz�sto lepiej przekszta�ci� je w sta�e lub parametry.

// Dla danych wierzcho�k�w:
extern const int myAquariumVertexCount; // Liczba wierzcho�k�w mo�e by� const
extern float myAquariumVertices[];      // Tablica wierzcho�k�w (bez rozmiaru tutaj)
extern float myAquariumTexCoords[];   // Tablica wsp�rz�dnych tekstur
extern float myAquariumColors[];      // Tablica kolor�w (je�li u�ywasz)


// --- DEKLARACJE funkcji ---
// Funkcja inicjalizuj�ca dane (np. texCoords, colors), je�li potrzeba
void initMyAquariumData(); // Pami�taj o zdefiniowaniu jej w .cpp!

// Funkcja rysuj�ca
void drawAquarium(ShaderProgram *sp, GLuint tex, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float localRotationAngleY = 0.0f);
void drawWater(ShaderProgram* sp, GLuint tex, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float localRotationAngleY = 0.0f);