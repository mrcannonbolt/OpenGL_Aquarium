#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "shaderprogram.h"

/**
  * @brief Rysuje prosty, "kanciasty" kamieñ w stylu low-poly.
 *
 * Geometria kamienia jest zdefiniowana na sta³e w pliku .cpp w tablicach
 * `myStoneVertices` i `myStoneTexCoords`.
 *
 * @param spStone WskaŸnik na ShaderProgram do rysowania.
 * @param texStone Uchwyt do tekstury kamienia.
 * @param parentModelMatrix Macierz modelu rodzica.
 * @param position Pozycja kamienia.
 * @param scale Wspó³czynnik skalowania.
 * @param localRotationAngleY K¹t obrotu wokó³ lokalnej osi Y.
 * @param stoneLength D³ugoœæ kamienia (skalowanie X).
 * @param stoneWidth Szerokoœæ kamienia (skalowanie Z).
 * @param stoneHeight Wysokoœæ kamienia (skalowanie Y).
 */
void drawStone(ShaderProgram* spStone, GLuint texStone,
    const glm::mat4& parentModelMatrix,
    const glm::vec3& position,
    float scale,
    float localRotationAngleY,
    float stoneLength, float stoneWidth, float stoneHeight);