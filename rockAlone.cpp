#include "rockalone.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const int myStoneVertexCount = 60; // 20 tr�jk�t�w * 3 wierzcho�ki

// Tablica wierzcho�k�w
const float myStoneVertices[myStoneVertexCount * 4] = {
    // --- SP�D ---
    // tr�jk�t (p0, p1, p2)
    -0.2f, -0.5f, -0.3f, 1.0f,   0.3f, -0.5f, -0.2f, 1.0f,   0.2f, -0.5f,  0.3f, 1.0f,
    // tr�jk�t (p0, p2, p3)
    -0.2f, -0.5f, -0.3f, 1.0f,   0.2f, -0.5f,  0.3f, 1.0f,  -0.3f, -0.5f,  0.2f, 1.0f,

    // --- �CIANY BOCZNE (dolna cz��) ---
    // tr�jk�t (p0, p4, p5)
    -0.2f, -0.5f, -0.3f, 1.0f,  -0.5f, -0.1f, -0.4f, 1.0f,   0.5f, -0.2f, -0.3f, 1.0f,
    // tr�jk�t (p0, p5, p1)
    -0.2f, -0.5f, -0.3f, 1.0f,   0.5f, -0.2f, -0.3f, 1.0f,   0.3f, -0.5f, -0.2f, 1.0f,
    // tr�jk�t (p1, p5, p6)
     0.3f, -0.5f, -0.2f, 1.0f,   0.5f, -0.2f, -0.3f, 1.0f,   0.4f,  0.1f,  0.5f, 1.0f,
     // tr�jk�t (p1, p6, p2)
      0.3f, -0.5f, -0.2f, 1.0f,   0.4f,  0.1f,  0.5f, 1.0f,   0.2f, -0.5f,  0.3f, 1.0f,
      // tr�jk�t (p2, p6, p7)
       0.2f, -0.5f,  0.3f, 1.0f,   0.4f,  0.1f,  0.5f, 1.0f,  -0.4f,  0.2f,  0.5f, 1.0f,
       // tr�jk�t (p2, p7, p3)
        0.2f, -0.5f,  0.3f, 1.0f,  -0.4f,  0.2f,  0.5f, 1.0f,  -0.3f, -0.5f,  0.2f, 1.0f,
        // tr�jk�t (p3, p7, p4)
        -0.3f, -0.5f,  0.2f, 1.0f,  -0.4f,  0.2f,  0.5f, 1.0f,  -0.5f, -0.1f, -0.4f, 1.0f,
        // tr�jk�t (p3, p4, p0)
        -0.3f, -0.5f,  0.2f, 1.0f,  -0.5f, -0.1f, -0.4f, 1.0f,  -0.2f, -0.5f, -0.3f, 1.0f,

        // --- �CIANY BOCZNE (g�rna cz��) ---
        // tr�jk�t (p4, p8, p9)
        -0.5f, -0.1f, -0.4f, 1.0f,  -0.2f,  0.5f, -0.1f, 1.0f,   0.2f,  0.5f,  0.0f, 1.0f,
        // tr�jk�t (p4, p9, p5)
        -0.5f, -0.1f, -0.4f, 1.0f,   0.2f,  0.5f,  0.0f, 1.0f,   0.5f, -0.2f, -0.3f, 1.0f,
        // tr�jk�t (p5, p9, p10)
         0.5f, -0.2f, -0.3f, 1.0f,   0.2f,  0.5f,  0.0f, 1.0f,   0.1f,  0.5f,  0.3f, 1.0f,
         // tr�jk�t (p5, p10, p6)
          0.5f, -0.2f, -0.3f, 1.0f,   0.1f,  0.5f,  0.3f, 1.0f,   0.4f,  0.1f,  0.5f, 1.0f,
          // tr�jk�t (p6, p10, p11)
           0.4f,  0.1f,  0.5f, 1.0f,   0.1f,  0.5f,  0.3f, 1.0f,  -0.1f,  0.4f,  0.2f, 1.0f,
           // tr�jk�t (p6, p11, p7)
            0.4f,  0.1f,  0.5f, 1.0f,  -0.1f,  0.4f,  0.2f, 1.0f,  -0.4f,  0.2f,  0.5f, 1.0f,
            // tr�jk�t (p7, p11, p8)
            -0.4f,  0.2f,  0.5f, 1.0f,  -0.1f,  0.4f,  0.2f, 1.0f,  -0.2f,  0.5f, -0.1f, 1.0f,
            // tr�jk�t (p7, p8, p4)
            -0.4f,  0.2f,  0.5f, 1.0f,  -0.2f,  0.5f, -0.1f, 1.0f,  -0.5f, -0.1f, -0.4f, 1.0f,

            // --- G�RA ---
            // tr�jk�t (p8, p11, p10)
            -0.2f, 0.5f, -0.1f, 1.0f, -0.1f, 0.4f, 0.2f, 1.0f, 0.1f, 0.5f, 0.3f, 1.0f,
            // tr�jk�t (p8, p10, p9)
            -0.2f, 0.5f, -0.1f, 1.0f, 0.1f, 0.5f, 0.3f, 1.0f, 0.2f, 0.5f, 0.0f, 1.0f
};

// Wsp�rz�dne tekstury
const float myStoneTexCoords[myStoneVertexCount * 2] = {
    // SP�D
    0.30f, 0.20f,  0.80f, 0.30f,  0.70f, 0.80f,
    0.30f, 0.20f,  0.70f, 0.80f,  0.20f, 0.70f,
    // �CIANY DOLNE
    0.30f, 0.20f,  0.00f, 0.10f,  1.00f, 0.20f,
    0.30f, 0.20f,  1.00f, 0.20f,  0.80f, 0.30f,
    0.80f, 0.30f,  1.00f, 0.20f,  0.90f, 1.00f,
    0.80f, 0.30f,  0.90f, 1.00f,  0.70f, 0.80f,
    0.70f, 0.80f,  0.90f, 1.00f,  0.10f, 1.00f,
    0.70f, 0.80f,  0.10f, 1.00f,  0.20f, 0.70f,
    0.20f, 0.70f,  0.10f, 1.00f,  0.00f, 0.10f,
    0.20f, 0.70f,  0.00f, 0.10f,  0.30f, 0.20f,
    // �CIANY G�RNE
    0.00f, 0.10f,  0.30f, 0.40f,  0.70f, 0.50f,
    0.00f, 0.10f,  0.70f, 0.50f,  1.00f, 0.20f,
    1.00f, 0.20f,  0.70f, 0.50f,  0.60f, 0.80f,
    1.00f, 0.20f,  0.60f, 0.80f,  0.90f, 1.00f,
    0.90f, 1.00f,  0.60f, 0.80f,  0.40f, 0.70f,
    0.90f, 1.00f,  0.40f, 0.70f,  0.10f, 1.00f,
    0.10f, 1.00f,  0.40f, 0.70f,  0.30f, 0.40f,
    0.10f, 1.00f,  0.30f, 0.40f,  0.00f, 0.10f,
    // G�RA
    0.30f, 0.40f,  0.40f, 0.70f,  0.60f, 0.80f,
    0.30f, 0.40f,  0.60f, 0.80f,  0.70f, 0.50f
};

// Wektory normalne dla ka�dego wierzcho�ka (do cieniowania p�askiego)
const float myStoneNormals[myStoneVertexCount * 3] = {
    // --- SP�D --- (normalne skierowane w d�)
    // tr�jk�t (p0, p1, p2)
     0.000f, -1.000f,  0.000f,   0.000f, -1.000f,  0.000f,   0.000f, -1.000f,  0.000f,
     // tr�jk�t (p0, p2, p3)
      0.000f, -1.000f,  0.000f,   0.000f, -1.000f,  0.000f,   0.000f, -1.000f,  0.000f,

      // --- �CIANY BOCZNE (dolna cz��) ---
      // tr�jk�t (p0, p4, p5)
       0.080f, -0.184f, -0.980f,   0.080f, -0.184f, -0.980f,   0.080f, -0.184f, -0.980f,
       // tr�jk�t (p0, p5, p1)
        0.174f, -0.406f, -0.898f,   0.174f, -0.406f, -0.898f,   0.174f, -0.406f, -0.898f,
        // tr�jk�t (p1, p5, p6)
         0.787f, -0.612f,  0.088f,   0.787f, -0.612f,  0.088f,   0.787f, -0.612f,  0.088f,
         // tr�jk�t (p1, p6, p2)
          0.912f, -0.365f,  0.182f,   0.912f, -0.365f,  0.182f,   0.912f, -0.365f,  0.182f,
          // tr�jk�t (p2, p6, p7)
          -0.038f, -0.305f,  0.951f,  -0.038f, -0.305f,  0.951f,  -0.038f, -0.305f,  0.951f,
          // tr�jk�t (p2, p7, p3)
          -0.179f, -0.409f,  0.895f,  -0.179f, -0.409f,  0.895f,  -0.179f, -0.409f,  0.895f,
          // tr�jk�t (p3, p7, p4)
          -0.952f, -0.211f,  0.191f,  -0.952f, -0.211f,  0.191f,  -0.952f, -0.211f,  0.191f,
          // tr�jk�t (p3, p4, p0)
          -0.781f, -0.625f, -0.000f,  -0.781f, -0.625f, -0.000f,  -0.781f, -0.625f, -0.000f,

          // --- �CIANY BOCZNE (g�rna cz��) ---
          // tr�jk�t (p4, p8, p9)
           0.229f,  0.343f, -0.914f,   0.229f,  0.343f, -0.914f,   0.229f,  0.343f, -0.914f,
           // tr�jk�t (p4, p9, p5)
            0.032f,  0.526f, -0.849f,   0.032f,  0.526f, -0.849f,   0.032f,  0.526f, -0.849f,
            // tr�jk�t (p5, p9, p10)
             0.901f,  0.257f,  0.343f,   0.901f,  0.257f,  0.343f,   0.901f,  0.257f,  0.343f,
             // tr�jk�t (p5, p10, p6)
              0.793f,  0.543f, -0.271f,   0.793f,  0.543f, -0.271f,   0.793f,  0.543f, -0.271f,
              // tr�jk�t (p6, p10, p11)
              -0.480f,  0.080f,  0.873f,  -0.480f,  0.080f,  0.873f,  -0.480f,  0.080f,  0.873f,
              // tr�jk�t (p6, p11, p7)
               0.098f,  0.783f,  0.614f,   0.098f,  0.783f,  0.614f,   0.098f,  0.783f,  0.614f,
               // tr�jk�t (p7, p11, p8)
               -0.224f,  0.894f,  0.397f,  -0.224f,  0.894f,  0.397f,  -0.224f,  0.894f,  0.397f,
               // tr�jk�t (p7, p8, p4)
               -0.884f,  0.465f, -0.059f,  -0.884f,  0.465f, -0.059f,  -0.884f,  0.465f, -0.059f,

               // --- G�RA --- (normalne skierowane w g�r�)
               // tr�jk�t (p8, p11, p10)
               -0.588f,  0.735f,  0.353f,  -0.588f,  0.735f,  0.353f,  -0.588f,  0.735f,  0.353f,
               // tr�jk�t (p8, p10, p9)
                0.000f,  1.000f,  0.000f,   0.000f,  1.000f,  0.000f,   0.000f,  1.000f,  0.000f
};

void drawStone(ShaderProgram* spStone, GLuint texStone,
    const glm::mat4& parentModelMatrix,
    const glm::vec3& position,
    float scale,
    float localRotationAngleY,
    float stoneLength, float stoneWidth, float stoneHeight) {

    glm::mat4 M_local = glm::mat4(1.0f);
    M_local = glm::translate(M_local, position);
    M_local = glm::rotate(M_local, localRotationAngleY, glm::vec3(0.0f, 1.0f, 0.0f));

    // Skalujemy bazowy model do docelowych wymiar�w.
    M_local = glm::scale(M_local, glm::vec3(stoneLength * scale, stoneHeight * scale, stoneWidth * scale));

    glm::mat4 M_final = parentModelMatrix * M_local;

    glUniformMatrix4fv(spStone->u("M"), 1, false, glm::value_ptr(M_final));

    // Przes�anie atrybut�w wierzcho�k�w
    glEnableVertexAttribArray(spStone->a("vertex"));
    glVertexAttribPointer(spStone->a("vertex"), 4, GL_FLOAT, false, 0, myStoneVertices);

    glEnableVertexAttribArray(spStone->a("texCoord0"));
    glVertexAttribPointer(spStone->a("texCoord0"), 2, GL_FLOAT, false, 0, myStoneTexCoords);

    // Przes�anie wektor�w normalnych
    glEnableVertexAttribArray(spStone->a("normal"));
    glVertexAttribPointer(spStone->a("normal"), 3, GL_FLOAT, false, 0, myStoneNormals);

    // Teksturowanie
    glBindTexture(GL_TEXTURE_2D, texStone);

    // Rysowanie
    glDrawArrays(GL_TRIANGLES, 0, myStoneVertexCount);

    // Wy��czenie atrybut�w
    glDisableVertexAttribArray(spStone->a("vertex"));
    glDisableVertexAttribArray(spStone->a("texCoord0"));
    glDisableVertexAttribArray(spStone->a("normal"));
}