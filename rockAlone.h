#pragma once
#include <GL/glew.h> // Przyk�ad dla GLEW, dla GLuint
#include <glm/glm.hpp>
#include <utility>
#include "shaderprogram.h" // Je�li ShaderProgram jest u�ywany w deklaracjach funkcji poni�ej


// --- Sta�e zwi�zane z generowaniem geometrii kamienia ---
// Mo�na je przenie�� tutaj z pliku .cpp, je�li maj� by� dost�pne globalnie
// lub je�li funkcje init/draw maj� by� bardziej generyczne i przyjmowa� je jako parametry.
// Na razie zostawiam je jako zewn�trzne, zak�adaj�c, �e s� zdefiniowane w pliku .cpp.
// Je�li chcesz je tutaj, odkomentuj i przenie�:
// extern const int stoneLatitudeSegments;
// extern const int stoneLongitudeSegments;
// extern const int myStoneVertexCount;

// --- Deklaracje globalnych tablic danych kamienia ---
// Te tablice s� zdefiniowane i wype�niane w pliku .cpp.
// U�ycie 'extern' informuje kompilator, �e definicje znajduj� si� gdzie indziej.
extern float myStoneVertices[];   // X, Y, Z, W
extern float myStoneTexCoords[]; // U, V

// --- Deklaracje funkcji ---

/**
 * @brief Inicjalizuje lub aktualizuje dane wierzcho�k�w i wsp�rz�dnych tekstury dla owalnego kamienia.
 *
 * Funkcja generuje geometri� elipsoidy na podstawie podanych wymiar�w.
 * Wierzcho�ki s� przechowywane w globalnej tablicy myStoneVertices,
 * a wsp�rz�dne tekstury w myStoneTexCoords.
 *
 * @param stoneLength Ca�kowita d�ugo�� kamienia (wzd�u� osi X).
 * @param stoneWidth Ca�kowita szeroko�� kamienia (wzd�u� osi Z).
 * @param stoneHeight Ca�kowita wysoko�� kamienia (wzd�u� osi Y).
 */
void initMyStoneData(float stoneLength, float stoneWidth, float stoneHeight);

/**
 * @brief Rysuje owalny kamie�.
 *
 * Funkcja zak�ada, �e odpowiedni shader jest aktywny, tekstura jest zbindowana,
 * oraz macierze Projekcji (P) i Widoku (V) s� ju� ustawione w shaderze.
 * Wywo�uje initMyStoneData, je�li dane kamienia nie zosta�y jeszcze zainicjalizowane
 * lub je�li wymiary kamienia uleg�y zmianie.
 *
 * @param spStone Wska�nik na obiekt ShaderProgram u�ywany do rysowania kamienia.
 * @param texStone Identyfikator (uchwyt) tekstury OpenGL dla kamienia.
 * @param parentModelMatrix Macierz modelu rodzica (np. transformacja sceny).
 * @param position Pozycja kamienia w przestrzeni rodzica.
 * @param scale Wsp�czynnik skalowania dla kamienia (jednolity).
 * @param localRotationAngleY K�t obrotu kamienia wok� jego lokalnej osi Y (w radianach).
 * @param stoneLength Ca�kowita d�ugo�� kamienia.
 * @param stoneWidth Ca�kowita szeroko�� kamienia.
 * @param stoneHeight Ca�kowita wysoko�� kamienia.
 */
void drawStone(ShaderProgram* spStone, GLuint texStone,
    const glm::mat4& parentModelMatrix,
    const glm::vec3& position,
    float scale,
    float localRotationAngleY,
    float stoneLength, float stoneWidth, float stoneHeight);
