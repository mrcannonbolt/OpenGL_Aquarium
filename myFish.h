#pragma once

#include "ShaderProgram.h" // Upewnij si�, �e �cie�ka jest poprawna
#include <glm/glm.hpp>
#include <GL/glew.h>

/**
 * @brief Rysuje prosty, statyczny model ryby.
 *
 * @param sp Wska�nik do u�ywanego programu shadera.
 * @param tex Identyfikator tekstury OpenGL do na�o�enia na ryb�.
 * @param parentModelMatrix Macierz modelu "rodzica" (np. ca�ego �wiata).
 * @param position Pozycja ryby w przestrzeni rodzica.
 * @param scale Skala ryby.
 * @param rotationY K�t obrotu ryby wok� jej osi Y.
 */
void drawMyFish(ShaderProgram* sp, GLuint tex, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float rotationY);
