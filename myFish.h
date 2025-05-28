#pragma once

#include "ShaderProgram.h" // Upewnij siê, ¿e œcie¿ka jest poprawna
#include <glm/glm.hpp>
#include <GL/glew.h>

/**
 * @brief Rysuje prosty, statyczny model ryby.
 *
 * @param sp WskaŸnik do u¿ywanego programu shadera.
 * @param tex Identyfikator tekstury OpenGL do na³o¿enia na rybê.
 * @param parentModelMatrix Macierz modelu "rodzica" (np. ca³ego œwiata).
 * @param position Pozycja ryby w przestrzeni rodzica.
 * @param scale Skala ryby.
 * @param rotationY K¹t obrotu ryby wokó³ jej osi Y.
 */
void drawMyFish(ShaderProgram* sp, GLuint tex, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float rotationY);
