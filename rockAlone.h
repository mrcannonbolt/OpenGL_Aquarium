#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "shaderprogram.h"

/**
  * @brief Rysuje prosty, "kanciasty" kamie� w stylu low-poly.
 *
 * Geometria kamienia jest zdefiniowana na sta�e w pliku .cpp w tablicach
 * `myStoneVertices` i `myStoneTexCoords`.
 *
 * @param spStone Wska�nik na ShaderProgram do rysowania.
 * @param texStone Uchwyt do tekstury kamienia.
 * @param parentModelMatrix Macierz modelu rodzica.
 * @param position Pozycja kamienia.
 * @param scale Wsp�czynnik skalowania.
 * @param localRotationAngleY K�t obrotu wok� lokalnej osi Y.
 * @param stoneLength D�ugo�� kamienia (skalowanie X).
 * @param stoneWidth Szeroko�� kamienia (skalowanie Z).
 * @param stoneHeight Wysoko�� kamienia (skalowanie Y).
 */
void drawStone(ShaderProgram* spStone, GLuint texStone,
    const glm::mat4& parentModelMatrix,
    const glm::vec3& position,
    float scale,
    float localRotationAngleY,
    float stoneLength, float stoneWidth, float stoneHeight);