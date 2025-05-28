#pragma once // Dobry zwyczaj, zapobiega wielokrotnemu do³¹czaniu nag³ówka

#ifndef MY_CORAL_H
#define MY_CORAL_H

#include <vector>
#include <GL/glew.h> // Dla GLuint
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp> // Dla glm::quat
#include "shaderprogram.h" // Odkomentuj, jeœli ShaderProgram jest klas¹ i jest potrzebny w deklaracjach poni¿ej

// --- Definicje dla PROTOTYPOWEGO Segmentu Koralowca (Oœmiok¹tny) ---
const float coralSegmentRadius = 0.2f;
const float coralSegmentHeight = 1.0f;
const int coralSegmentSides = 8;
// Obliczenie liczby wierzcho³ków
const int myCoralSegmentVertexCount = (coralSegmentSides * 3) + (coralSegmentSides * 3) + (coralSegmentSides * 2 * 3); // 96

// Deklaracje 'extern' dla tablic wierzcho³ków i wspó³rzêdnych tekstur prototypu.
// Definicje tych tablic musz¹ znajdowaæ siê w jednym pliku .cpp.
extern float myCoralSegmentVertices[myCoralSegmentVertexCount * 4];
extern float myCoralSegmentTexCoords[myCoralSegmentVertexCount * 2];

// Prototyp funkcji inicjalizuj¹cej dane geometryczne prototypowego segmentu.
void initMyCoralSegmentData();


// --- Definicje dla DETERMINISTYCZNEGO Tworzenia Koralowca ---

// Struktura opisuj¹ca pojedynczy segment w zdefiniowanym wzorcu koralowca.
struct DeterministicSegmentData {
    glm::vec3 translation_from_parent_top;    // Przesuniêcie podstawy tego segmentu wzglêdem szczytu segmentu-rodzica.
    glm::quat orientation_relative_to_parent; // Dodatkowy obrót tego segmentu wzglêdem orientacji szczytu rodzica.
    float radius_scale_factor;                // Wspó³czynnik skali dla promienia tego segmentu.
};

// Jeœli chcesz, aby `myFirstCoralPattern` by³ dostêpny globalnie:
// Deklaracja 'extern' w pliku .h:
// extern std::vector<DeterministicSegmentData> myFirstCoralPattern;
// Definicja i inicjalizacja MUSI byæ w JEDNYM pliku .cpp, np.:
// std::vector<DeterministicSegmentData> myFirstCoralPattern = { /* ... dane ... */ };
// ZALECENIE: Zamiast globalnej, definiuj wzorce w .cpp i przekazuj je do funkcji.


// Prototyp funkcji buduj¹cej koralowca wed³ug zadanego wzorca.
std::vector<glm::mat4> buildDeterministicCoral(
    glm::mat4 initialTransformForFirstSegmentBase
);


// --- Funkcje Rysuj¹ce ---

// Forward declaration dla ShaderProgram, jeœli jest to klasa/struktura zdefiniowana gdzie indziej
// i jest u¿ywana jako typ wskaŸnika w funkcjach poni¿ej.
class ShaderProgram;

// Funkcja rysuj¹ca pojedynczy segment (jeœli nadal jej potrzebujesz, by³a w Twoim pliku)
// Jeœli nie jest u¿ywana, mo¿na j¹ usun¹æ.
void drawCoralSegment(ShaderProgram* sp, GLuint textureId, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float rotationY);

// Funkcja rysuj¹ca ca³y koralowiec (z³o¿ony z wielu segmentów)
void drawEntireCoral(
    ShaderProgram* sp,
    unsigned int coralTextureId,
    const std::vector<glm::mat4>& coralSegmentMatricesToDraw // Zmieniono na const&, jeœli funkcja nie modyfikuje tego wektora
);

#endif // MY_CORAL_H