#include "myFish.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Nasz model 3D bêdzie siê sk³ada³ z 9 trójk¹tów
const int myFishVertexCount = 27;

// Tablica wierzcho³ków dla kanciastej rybki 3D ("low-poly") - BEZ ZMIAN
const float myFishVertices[myFishVertexCount * 4] = {
    // --- PRZÓD KORPUSU (4 trójk¹ty tworz¹ce ostros³up) ---
    // Prawy-górny-przód
     0.6f,  0.0f,  0.0f, 1.0f, // nose
     0.0f,  0.3f,  0.0f, 1.0f, // top
     0.0f,  0.0f,  0.2f, 1.0f, // right
     // Prawy-dolny-przód
      0.6f,  0.0f,  0.0f, 1.0f, // nose
      0.0f,  0.0f,  0.2f, 1.0f, // right
      0.0f, -0.3f,  0.0f, 1.0f, // bottom
      // Lewy-dolny-przód
       0.6f,  0.0f,  0.0f, 1.0f, // nose
       0.0f, -0.3f,  0.0f, 1.0f, // bottom
       0.0f,  0.0f, -0.2f, 1.0f, // left
       // Lewy-górny-przód
        0.6f,  0.0f,  0.0f, 1.0f, // nose
        0.0f,  0.0f, -0.2f, 1.0f, // left
        0.0f,  0.3f,  0.0f, 1.0f, // top

        // --- TY£ KORPUSU (4 trójk¹ty tworz¹ce drugi ostros³up) ---
        // Prawy-górny-ty³
        -0.6f,  0.0f,  0.0f, 1.0f, // tail_base
         0.0f,  0.0f,  0.2f, 1.0f, // right
         0.0f,  0.3f,  0.0f, 1.0f, // top
         // Prawy-dolny-ty³
         -0.6f,  0.0f,  0.0f, 1.0f, // tail_base
          0.0f, -0.3f,  0.0f, 1.0f, // bottom
          0.0f,  0.0f,  0.2f, 1.0f, // right
          // Lewy-dolny-ty³
          -0.6f,  0.0f,  0.0f, 1.0f, // tail_base
           0.0f,  0.0f, -0.2f, 1.0f, // left
           0.0f, -0.3f,  0.0f, 1.0f, // bottom
           // Lewy-górny-ty³
           -0.6f,  0.0f,  0.0f, 1.0f, // tail_base
            0.0f,  0.3f,  0.0f, 1.0f, // top
            0.0f,  0.0f, -0.2f, 1.0f, // left

            // --- P£ETWA OGONOWA (1 p³aski trójk¹t na koñcu) ---
            -0.6f,  0.0f,  0.0f, 1.0f, // tail_base
            -0.9f,  0.25f, 0.0f, 1.0f, // tip 1
            -0.9f, -0.25f, 0.0f, 1.0f  // tip 2
};

// Wspó³rzêdne tekstury (proste mapowanie) - BEZ ZMIAN
const float myFishTexCoords[myFishVertexCount * 2] = {
    // Przód
    1.0f, 0.5f,   0.5f, 1.0f,   0.5f, 0.5f,
    1.0f, 0.5f,   0.5f, 0.5f,   0.5f, 0.0f,
    1.0f, 0.5f,   0.5f, 0.0f,   0.5f, 0.5f,
    1.0f, 0.5f,   0.5f, 0.5f,   0.5f, 1.0f,
    // Ty³
    0.0f, 0.5f,   0.5f, 0.5f,   0.5f, 1.0f,
    0.0f, 0.5f,   0.5f, 0.0f,   0.5f, 0.5f,
    0.0f, 0.5f,   0.5f, 0.5f,   0.5f, 0.0f,
    0.0f, 0.5f,   0.5f, 1.0f,   0.5f, 0.5f,
    // Ogon
    0.1f, 0.5f,   0.0f, 1.0f,   0.0f, 0.0f
};

// *** NOWA TABLICA ***
// Wektory normalne dla ka¿dego wierzcho³ka (do cieniowania)
// Dla cieniowania p³askiego, wszystkie 3 wierzcho³ki trójk¹ta maj¹ ten sam wektor normalny.
const float myFishNormals[myFishVertexCount * 3] = {
    // --- PRZÓD KORPUSU ---
    // Prawy-górny-przód (3 takie same wektory normalne)
    0.267f,  0.534f,  0.802f,
    0.267f,  0.534f,  0.802f,
    0.267f,  0.534f,  0.802f,
    // Prawy-dolny-przód
    0.267f, -0.534f,  0.802f,
    0.267f, -0.534f,  0.802f,
    0.267f, -0.534f,  0.802f,
    // Lewy-dolny-przód
    0.267f, -0.534f, -0.802f,
    0.267f, -0.534f, -0.802f,
    0.267f, -0.534f, -0.802f,
    // Lewy-górny-przód
    0.267f,  0.534f, -0.802f,
    0.267f,  0.534f, -0.802f,
    0.267f,  0.534f, -0.802f,

    // --- TY£ KORPUSU ---
    // Prawy-górny-ty³
   -0.267f,  0.534f,  0.802f,
   -0.267f,  0.534f,  0.802f,
   -0.267f,  0.534f,  0.802f,
   // Prawy-dolny-ty³
  -0.267f, -0.534f,  0.802f,
  -0.267f, -0.534f,  0.802f,
  -0.267f, -0.534f,  0.802f,
  // Lewy-dolny-ty³
 -0.267f, -0.534f, -0.802f,
 -0.267f, -0.534f, -0.802f,
 -0.267f, -0.534f, -0.802f,
 // Lewy-górny-ty³
-0.267f,  0.534f, -0.802f,
-0.267f,  0.534f, -0.802f,
-0.267f,  0.534f, -0.802f,

// --- P£ETWA OGONOWA --- (normalna skierowana w stronê osi +Z)
0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f
};


// *** ZAKTUALIZOWANA FUNKCJA ***
// Funkcja rysuj¹ca z obs³ug¹ wektorów normalnych
void drawMyFish(ShaderProgram* sp, GLuint tex, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float rotationY) {
    // Obliczenie macierzy modelu i przes³anie jej do shadera
    glm::mat4 M_local = glm::mat4(1.0f);
    M_local = glm::translate(M_local, position);
    M_local = glm::rotate(M_local, rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
    M_local = glm::scale(M_local, glm::vec3(scale, scale, scale));
    glm::mat4 M_final = parentModelMatrix * M_local;
    glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M_final));
    
    // Obliczenie i przes³anie macierzy normalnych (kluczowe dla oœwietlenia przy skalowaniu!)
    //glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(M_final)));
    //glUniformMatrix3fv(sp->u("normalMatrix"), 1, false, glm::value_ptr(normalMatrix));
    // Przes³anie atrybutów wierzcho³ków
    glEnableVertexAttribArray(sp->a("vertex"));
    glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, myFishVertices);

    glEnableVertexAttribArray(sp->a("texCoord0"));
    glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, myFishTexCoords);

    // Przes³anie wektorów normalnych
    glEnableVertexAttribArray(sp->a("normal"));
    glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, myFishNormals);

    // Teksturowanie
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

    // Rysowanie
    glDrawArrays(GL_TRIANGLES, 0, myFishVertexCount);

    // Wy³¹czenie atrybutów
    glDisableVertexAttribArray(sp->a("vertex"));
    glDisableVertexAttribArray(sp->a("texCoord0"));
    glDisableVertexAttribArray(sp->a("normal"));
}