#pragma once // Dobry zwyczaj, zapobiega wielokrotnemu do��czaniu nag��wka

#ifndef MY_CORAL_H
#define MY_CORAL_H

#include <vector>
#include <GL/glew.h> // Dla GLuint
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp> // Dla glm::quat
#include "shaderprogram.h" // Odkomentuj, je�li ShaderProgram jest klas� i jest potrzebny w deklaracjach poni�ej

// --- Definicje dla PROTOTYPOWEGO Segmentu Koralowca (O�miok�tny) ---
const float coralSegmentRadius = 0.2f;
const float coralSegmentHeight = 1.0f;
const int coralSegmentSides = 8;
// Obliczenie liczby wierzcho�k�w
const int myCoralSegmentVertexCount = (coralSegmentSides * 3) + (coralSegmentSides * 3) + (coralSegmentSides * 2 * 3); // 96

// Deklaracje 'extern' dla tablic wierzcho�k�w i wsp�rz�dnych tekstur prototypu.
// Definicje tych tablic musz� znajdowa� si� w jednym pliku .cpp.
extern float myCoralSegmentVertices[myCoralSegmentVertexCount * 4];
extern float myCoralSegmentTexCoords[myCoralSegmentVertexCount * 2];

// Prototyp funkcji inicjalizuj�cej dane geometryczne prototypowego segmentu.
void initMyCoralSegmentData();


// --- Definicje dla DETERMINISTYCZNEGO Tworzenia Koralowca ---

// Struktura opisuj�ca pojedynczy segment w zdefiniowanym wzorcu koralowca.
struct DeterministicSegmentData {
    glm::vec3 translation_from_parent_top;    // Przesuni�cie podstawy tego segmentu wzgl�dem szczytu segmentu-rodzica.
    glm::quat orientation_relative_to_parent; // Dodatkowy obr�t tego segmentu wzgl�dem orientacji szczytu rodzica.
    float radius_scale_factor;                // Wsp�czynnik skali dla promienia tego segmentu.
};

// Je�li chcesz, aby `myFirstCoralPattern` by� dost�pny globalnie:
// Deklaracja 'extern' w pliku .h:
// extern std::vector<DeterministicSegmentData> myFirstCoralPattern;
// Definicja i inicjalizacja MUSI by� w JEDNYM pliku .cpp, np.:
// std::vector<DeterministicSegmentData> myFirstCoralPattern = { /* ... dane ... */ };
// ZALECENIE: Zamiast globalnej, definiuj wzorce w .cpp i przekazuj je do funkcji.


// Prototyp funkcji buduj�cej koralowca wed�ug zadanego wzorca.
std::vector<glm::mat4> buildDeterministicCoral(
    glm::mat4 initialTransformForFirstSegmentBase
);


// --- Funkcje Rysuj�ce ---

// Forward declaration dla ShaderProgram, je�li jest to klasa/struktura zdefiniowana gdzie indziej
// i jest u�ywana jako typ wska�nika w funkcjach poni�ej.
class ShaderProgram;

// Funkcja rysuj�ca pojedynczy segment (je�li nadal jej potrzebujesz, by�a w Twoim pliku)
// Je�li nie jest u�ywana, mo�na j� usun��.
void drawCoralSegment(ShaderProgram* sp, GLuint textureId, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float rotationY);

// Funkcja rysuj�ca ca�y koralowiec (z�o�ony z wielu segment�w)
void drawEntireCoral(
    ShaderProgram* sp,
    unsigned int coralTextureId,
    const std::vector<glm::mat4>& coralSegmentMatricesToDraw // Zmieniono na const&, je�li funkcja nie modyfikuje tego wektora
);

#endif // MY_CORAL_H