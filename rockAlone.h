#pragma once
#include <GL/glew.h> // Przyk³ad dla GLEW, dla GLuint
#include <glm/glm.hpp>
#include <utility>
#include "shaderprogram.h" // Jeœli ShaderProgram jest u¿ywany w deklaracjach funkcji poni¿ej


// --- Sta³e zwi¹zane z generowaniem geometrii kamienia ---
// Mo¿na je przenieœæ tutaj z pliku .cpp, jeœli maj¹ byæ dostêpne globalnie
// lub jeœli funkcje init/draw maj¹ byæ bardziej generyczne i przyjmowaæ je jako parametry.
// Na razie zostawiam je jako zewnêtrzne, zak³adaj¹c, ¿e s¹ zdefiniowane w pliku .cpp.
// Jeœli chcesz je tutaj, odkomentuj i przenieœ:
// extern const int stoneLatitudeSegments;
// extern const int stoneLongitudeSegments;
// extern const int myStoneVertexCount;

// --- Deklaracje globalnych tablic danych kamienia ---
// Te tablice s¹ zdefiniowane i wype³niane w pliku .cpp.
// U¿ycie 'extern' informuje kompilator, ¿e definicje znajduj¹ siê gdzie indziej.
extern float myStoneVertices[];   // X, Y, Z, W
extern float myStoneTexCoords[]; // U, V

// --- Deklaracje funkcji ---

/**
 * @brief Inicjalizuje lub aktualizuje dane wierzcho³ków i wspó³rzêdnych tekstury dla owalnego kamienia.
 *
 * Funkcja generuje geometriê elipsoidy na podstawie podanych wymiarów.
 * Wierzcho³ki s¹ przechowywane w globalnej tablicy myStoneVertices,
 * a wspó³rzêdne tekstury w myStoneTexCoords.
 *
 * @param stoneLength Ca³kowita d³ugoœæ kamienia (wzd³u¿ osi X).
 * @param stoneWidth Ca³kowita szerokoœæ kamienia (wzd³u¿ osi Z).
 * @param stoneHeight Ca³kowita wysokoœæ kamienia (wzd³u¿ osi Y).
 */
void initMyStoneData(float stoneLength, float stoneWidth, float stoneHeight);

/**
 * @brief Rysuje owalny kamieñ.
 *
 * Funkcja zak³ada, ¿e odpowiedni shader jest aktywny, tekstura jest zbindowana,
 * oraz macierze Projekcji (P) i Widoku (V) s¹ ju¿ ustawione w shaderze.
 * Wywo³uje initMyStoneData, jeœli dane kamienia nie zosta³y jeszcze zainicjalizowane
 * lub jeœli wymiary kamienia uleg³y zmianie.
 *
 * @param spStone WskaŸnik na obiekt ShaderProgram u¿ywany do rysowania kamienia.
 * @param texStone Identyfikator (uchwyt) tekstury OpenGL dla kamienia.
 * @param parentModelMatrix Macierz modelu rodzica (np. transformacja sceny).
 * @param position Pozycja kamienia w przestrzeni rodzica.
 * @param scale Wspó³czynnik skalowania dla kamienia (jednolity).
 * @param localRotationAngleY K¹t obrotu kamienia wokó³ jego lokalnej osi Y (w radianach).
 * @param stoneLength Ca³kowita d³ugoœæ kamienia.
 * @param stoneWidth Ca³kowita szerokoœæ kamienia.
 * @param stoneHeight Ca³kowita wysokoœæ kamienia.
 */
void drawStone(ShaderProgram* spStone, GLuint texStone,
    const glm::mat4& parentModelMatrix,
    const glm::vec3& position,
    float scale,
    float localRotationAngleY,
    float stoneLength, float stoneWidth, float stoneHeight);
