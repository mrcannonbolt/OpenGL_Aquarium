#include "myFish.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Nasz model 3D b�dzie si� sk�ada� z 9 tr�jk�t�w
const int myFishVertexCount = 27;

// Tablica wierzcho�k�w dla kanciastej rybki 3D ("low-poly") - BEZ ZMIAN
const float myFishVertices[myFishVertexCount * 4] = {
    // --- PRZ�D KORPUSU (4 tr�jk�ty tworz�ce ostros�up) ---
    // Prawy-g�rny-prz�d
     0.6f,  0.0f,  0.0f, 1.0f, // nose
     0.0f,  0.3f,  0.0f, 1.0f, // top
     0.0f,  0.0f,  0.2f, 1.0f, // right
     // Prawy-dolny-prz�d
      0.6f,  0.0f,  0.0f, 1.0f, // nose
      0.0f,  0.0f,  0.2f, 1.0f, // right
      0.0f, -0.3f,  0.0f, 1.0f, // bottom
      // Lewy-dolny-prz�d
       0.6f,  0.0f,  0.0f, 1.0f, // nose
       0.0f, -0.3f,  0.0f, 1.0f, // bottom
       0.0f,  0.0f, -0.2f, 1.0f, // left
       // Lewy-g�rny-prz�d
        0.6f,  0.0f,  0.0f, 1.0f, // nose
        0.0f,  0.0f, -0.2f, 1.0f, // left
        0.0f,  0.3f,  0.0f, 1.0f, // top

        // --- TY� KORPUSU (4 tr�jk�ty tworz�ce drugi ostros�up) ---
        // Prawy-g�rny-ty�
        -0.6f,  0.0f,  0.0f, 1.0f, // tail_base
         0.0f,  0.0f,  0.2f, 1.0f, // right
         0.0f,  0.3f,  0.0f, 1.0f, // top
         // Prawy-dolny-ty�
         -0.6f,  0.0f,  0.0f, 1.0f, // tail_base
          0.0f, -0.3f,  0.0f, 1.0f, // bottom
          0.0f,  0.0f,  0.2f, 1.0f, // right
          // Lewy-dolny-ty�
          -0.6f,  0.0f,  0.0f, 1.0f, // tail_base
           0.0f,  0.0f, -0.2f, 1.0f, // left
           0.0f, -0.3f,  0.0f, 1.0f, // bottom
           // Lewy-g�rny-ty�
           -0.6f,  0.0f,  0.0f, 1.0f, // tail_base
            0.0f,  0.3f,  0.0f, 1.0f, // top
            0.0f,  0.0f, -0.2f, 1.0f, // left

            // --- P�ETWA OGONOWA (1 p�aski tr�jk�t na ko�cu) ---
            -0.6f,  0.0f,  0.0f, 1.0f, // tail_base
            -0.9f,  0.25f, 0.0f, 1.0f, // tip 1
            -0.9f, -0.25f, 0.0f, 1.0f  // tip 2
};

// Wsp�rz�dne tekstury (proste mapowanie) - BEZ ZMIAN
const float myFishTexCoords[myFishVertexCount * 2] = {
    // Prz�d
    1.0f, 0.5f,   0.5f, 1.0f,   0.5f, 0.5f,
    1.0f, 0.5f,   0.5f, 0.5f,   0.5f, 0.0f,
    1.0f, 0.5f,   0.5f, 0.0f,   0.5f, 0.5f,
    1.0f, 0.5f,   0.5f, 0.5f,   0.5f, 1.0f,
    // Ty�
    0.0f, 0.5f,   0.5f, 0.5f,   0.5f, 1.0f,
    0.0f, 0.5f,   0.5f, 0.0f,   0.5f, 0.5f,
    0.0f, 0.5f,   0.5f, 0.5f,   0.5f, 0.0f,
    0.0f, 0.5f,   0.5f, 1.0f,   0.5f, 0.5f,
    // Ogon
    0.1f, 0.5f,   0.0f, 1.0f,   0.0f, 0.0f
};

// *** NOWA TABLICA ***
// Wektory normalne dla ka�dego wierzcho�ka (do cieniowania)
// Dla cieniowania p�askiego, wszystkie 3 wierzcho�ki tr�jk�ta maj� ten sam wektor normalny.
const float myFishNormals[myFishVertexCount * 3] = {
    // --- PRZ�D KORPUSU ---
    // Prawy-g�rny-prz�d (3 takie same wektory normalne)
    0.267f,  0.534f,  0.802f,
    0.267f,  0.534f,  0.802f,
    0.267f,  0.534f,  0.802f,
    // Prawy-dolny-prz�d
    0.267f, -0.534f,  0.802f,
    0.267f, -0.534f,  0.802f,
    0.267f, -0.534f,  0.802f,
    // Lewy-dolny-prz�d
    0.267f, -0.534f, -0.802f,
    0.267f, -0.534f, -0.802f,
    0.267f, -0.534f, -0.802f,
    // Lewy-g�rny-prz�d
    0.267f,  0.534f, -0.802f,
    0.267f,  0.534f, -0.802f,
    0.267f,  0.534f, -0.802f,

    // --- TY� KORPUSU ---
    // Prawy-g�rny-ty�
   -0.267f,  0.534f,  0.802f,
   -0.267f,  0.534f,  0.802f,
   -0.267f,  0.534f,  0.802f,
   // Prawy-dolny-ty�
  -0.267f, -0.534f,  0.802f,
  -0.267f, -0.534f,  0.802f,
  -0.267f, -0.534f,  0.802f,
  // Lewy-dolny-ty�
 -0.267f, -0.534f, -0.802f,
 -0.267f, -0.534f, -0.802f,
 -0.267f, -0.534f, -0.802f,
 // Lewy-g�rny-ty�
-0.267f,  0.534f, -0.802f,
-0.267f,  0.534f, -0.802f,
-0.267f,  0.534f, -0.802f,

// --- P�ETWA OGONOWA --- (normalna skierowana w stron� osi +Z)
0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f
};


// *** ZAKTUALIZOWANA FUNKCJA ***
// Funkcja rysuj�ca z obs�ug� wektor�w normalnych
void drawMyFish(ShaderProgram* sp, GLuint tex, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float rotationY) {
    // Obliczenie macierzy modelu i przes�anie jej do shadera
    glm::mat4 M_local = glm::mat4(1.0f);
    M_local = glm::translate(M_local, position);
    M_local = glm::rotate(M_local, rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
    M_local = glm::scale(M_local, glm::vec3(scale, scale, scale));
    glm::mat4 M_final = parentModelMatrix * M_local;
    glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M_final));
    
    // Obliczenie i przes�anie macierzy normalnych (kluczowe dla o�wietlenia przy skalowaniu!)
    //glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(M_final)));
    //glUniformMatrix3fv(sp->u("normalMatrix"), 1, false, glm::value_ptr(normalMatrix));
    // Przes�anie atrybut�w wierzcho�k�w
    glEnableVertexAttribArray(sp->a("vertex"));
    glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, myFishVertices);

    glEnableVertexAttribArray(sp->a("texCoord0"));
    glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, myFishTexCoords);

    // Przes�anie wektor�w normalnych
    glEnableVertexAttribArray(sp->a("normal"));
    glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, myFishNormals);

    // Teksturowanie
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

    // Rysowanie
    glDrawArrays(GL_TRIANGLES, 0, myFishVertexCount);

    // Wy��czenie atrybut�w
    glDisableVertexAttribArray(sp->a("vertex"));
    glDisableVertexAttribArray(sp->a("texCoord0"));
    glDisableVertexAttribArray(sp->a("normal"));
}