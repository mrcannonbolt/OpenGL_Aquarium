#include "myAquarium.h"
#include <glm/gtc/matrix_transform.hpp> // Dla glm::translate, glm::rotate, glm::scale
#include <glm/gtc/type_ptr.hpp>        // Dla glm::value_ptr

// aby nie zaœmiecaæ globalnej przestrzeni nazw, jeœli s¹ u¿ywane tylko tutaj.
const float width = 4.0f;
const float height = 2.0f;
const float depth = 3.0f;
const float glassThickness = 0.1f;

const float oW = width / 2.0f;
const float oH = height / 2.0f;
const float oD = depth / 2.0f;

const float iW = oW - glassThickness;
const float iH = oH - glassThickness;
const float iD = oD - glassThickness;

const int myAquariumVertexCount = 180; 

// Definicja i inicjalizacja tablicy wierzcho³ków
float myAquariumVertices[myAquariumVertexCount * 4] = {
    // Œcianka 1: Przód (Front Wall) Z = -oD / -iD
    // ... (Twoje pe³ne dane wierzcho³ków, tak jak by³y w .h)
    // Pamiêtaj o poprawkach dla œcian Lewej/Prawej, o których rozmawialiœmy!
    // Zewnêtrzny prostok¹t (normalna +Z)
    -oW, -oH, -oD, 1.0f,   oW, -oH, -oD, 1.0f,    oW,  oH, -oD, 1.0f,
    -oW, -oH, -oD, 1.0f,   oW,  oH, -oD, 1.0f,   -oW,  oH, -oD, 1.0f,
    // Wewnêtrzny prostok¹t (normalna -Z, odwrotna kolejnoœæ)
    -iW, -iH, -iD, 1.0f,  -iW,  iH, -iD, 1.0f,   iW,  iH, -iD, 1.0f,
    -iW, -iH, -iD, 1.0f,   iW,  iH, -iD, 1.0f,   iW, -iH, -iD, 1.0f,
    // £¹czenia krawêdzi (4 paski po 2 trójk¹ty)
    // Górny pasek
    -oW,  oH, -oD, 1.0f,   oW,  oH, -oD, 1.0f,   iW,  iH, -iD, 1.0f,
    -oW,  oH, -oD, 1.0f,   iW,  iH, -iD, 1.0f,  -iW,  iH, -iD, 1.0f,
    // Dolny pasek
    -oW, -oH, -oD, 1.0f,  -iW, -iH, -iD, 1.0f,   iW, -iH, -iD, 1.0f,
    -oW, -oH, -oD, 1.0f,   iW, -iH, -iD, 1.0f,   oW, -oH, -oD, 1.0f,
    // Lewy pasek
    -oW, -oH, -oD, 1.0f,  -oW,  oH, -oD, 1.0f,  -iW,  oH, -iD, 1.0f,
    -oW, -oH, -oD, 1.0f,  -iW,  oH, -iD, 1.0f,  -iW, -iH, -iD, 1.0f,
    // Prawy pasek
     oW, -oH, -oD, 1.0f,   iW, -iH, -iD, 1.0f,   iW,  oH, -iD, 1.0f,
     oW, -oH, -oD, 1.0f,   iW,  oH, -iD, 1.0f,   oW,  oH, -oD, 1.0f,

     // Œcianka 2: Ty³ (Back Wall) Z = +oD / +iD
     // ... i tak dalej dla wszystkich 6 œcianek ...
     // Zewnêtrzny prostok¹t (normalna -Z)
     -oW, -oH,  oD, 1.0f,  -oW,  oH,  oD, 1.0f,   oW,  oH,  oD, 1.0f,
     -oW, -oH,  oD, 1.0f,   oW,  oH,  oD, 1.0f,   oW, -oH,  oD, 1.0f,
     // Wewnêtrzny prostok¹t (normalna +Z, odwrotna kolejnoœæ)
     -iW, -iH,  iD, 1.0f,   iW, -iH,  iD, 1.0f,   iW,  iH,  iD, 1.0f,
     -iW, -iH,  iD, 1.0f,   iW,  iH,  iD, 1.0f,  -iW,  iH,  iD, 1.0f,
     // £¹czenia krawêdzi
     // Górny pasek
     -oW,  oH,  oD, 1.0f,  -iW,  iH,  iD, 1.0f,   iW,  iH,  iD, 1.0f,
     -oW,  oH,  oD, 1.0f,   iW,  iH,  iD, 1.0f,   oW,  oH,  oD, 1.0f,
     // Dolny pasek
     -oW, -oH,  oD, 1.0f,   oW, -oH,  oD, 1.0f,   iW, -iH,  iD, 1.0f,
     -oW, -oH,  oD, 1.0f,   iW, -iH,  iD, 1.0f,  -iW, -iH,  iD, 1.0f,
     // Lewy pasek
     -oW, -oH,  oD, 1.0f,  -iW, -iH,  iD, 1.0f,  -iW,  oH,  iD, 1.0f,
     -oW, -oH,  oD, 1.0f,  -iW,  oH,  iD, 1.0f,  -oW,  oH,  oD, 1.0f,
     // Prawy pasek
      oW, -oH,  oD, 1.0f,   oW,  oH,  oD, 1.0f,   iW,  oH,  iD, 1.0f,
      oW, -oH,  oD, 1.0f,   iW,  oH,  iD, 1.0f,   iW, -iH,  iD, 1.0f,

      // Œcianka 3: Dó³ (Bottom Wall) Y = -oH / -iH
      // Zewnêtrzny prostok¹t (normalna +Y)
      -oW, -oH, -oD, 1.0f,  -oW, -oH,  oD, 1.0f,   oW, -oH,  oD, 1.0f,
      -oW, -oH, -oD, 1.0f,   oW, -oH,  oD, 1.0f,   oW, -oH, -oD, 1.0f,
      // Wewnêtrzny prostok¹t (normalna -Y, odwrotna kolejnoœæ)
      -iW, -iH, -iD, 1.0f,   iW, -iH, -iD, 1.0f,   iW, -iH,  iD, 1.0f,
      -iW, -iH, -iD, 1.0f,   iW, -iH,  iD, 1.0f,  -iW, -iH,  iD, 1.0f,
      // £¹czenia krawêdzi
      // Przedni pasek (Z=-oD/-iD)
      -oW, -oH, -oD, 1.0f,   oW, -oH, -oD, 1.0f,   iW, -iH, -iD, 1.0f,
      -oW, -oH, -oD, 1.0f,   iW, -iH, -iD, 1.0f,  -iW, -iH, -iD, 1.0f,
      // Tylny pasek (Z=+oD/+iD)
      -oW, -oH,  oD, 1.0f,  -iW, -iH,  iD, 1.0f,   iW, -iH,  iD, 1.0f,
      -oW, -oH,  oD, 1.0f,   iW, -iH,  iD, 1.0f,   oW, -oH,  oD, 1.0f,
      // Lewy pasek (X=-oW/-iW)
      -oW, -oH, -oD, 1.0f,  -iW, -iH, -iD, 1.0f,  -iW, -iH,  iD, 1.0f,
      -oW, -oH, -oD, 1.0f,  -iW, -iH,  iD, 1.0f,  -oW, -oH,  oD, 1.0f,
      // Prawy pasek (X=+oW/+iW)
       oW, -oH, -oD, 1.0f,   oW, -oH,  oD, 1.0f,   iW, -iH,  iD, 1.0f,
       oW, -oH, -oD, 1.0f,   iW, -iH,  iD, 1.0f,   iW, -iH, -iD, 1.0f,



        // Œcianka 4: Lewo (Left Wall) X = -oW / -iW (z poprawkami na iH dla wewn.)
        // Zewnêtrzny prostok¹t (normalna +X)
        -oW, -oH, -oD, 1.0f,  -oW,  oH, -oD, 1.0f,  -oW,  oH,  oD, 1.0f,
        -oW, -oH, -oD, 1.0f,  -oW,  oH,  oD, 1.0f,  -oW, -oH,  oD, 1.0f,
        // Wewnêtrzny prostok¹t (normalna -X, odwrotna kolejnoœæ)
        -iW, -iH, -iD, 1.0f,  -iW, -iH,  iD, 1.0f,  -iW,  iH,  iD, 1.0f, // Poprawione z oH na iH
        -iW, -iH, -iD, 1.0f,  -iW,  iH,  iD, 1.0f,  -iW,  iH, -iD, 1.0f, // Poprawione z oH na iH
        // £¹czenia krawêdzi
        // Górny pasek (Y=+oH/+iH)
        -oW,  oH, -oD, 1.0f,  -iW,  iH, -iD, 1.0f,  -iW,  iH,  iD, 1.0f,
        -oW,  oH, -oD, 1.0f,  -iW,  iH,  iD, 1.0f,  -oW,  oH,  oD, 1.0f,
        // Dolny pasek (Y=-oH/-iH)
        -oW, -oH, -oD, 1.0f,  -oW, -oH,  oD, 1.0f,  -iW, -iH,  iD, 1.0f,
        -oW, -oH, -oD, 1.0f,  -iW, -iH,  iD, 1.0f,  -iW, -iH, -iD, 1.0f,
        // Przedni pasek (Z=-oD/-iD)
        -oW, -oH, -oD, 1.0f,  -iW, -iH, -iD, 1.0f,  -iW,  oH, -iD, 1.0f,
        -oW, -oH, -oD, 1.0f,  -iW,  oH, -iD, 1.0f,  -oW,  oH, -oD, 1.0f,
        // Tylny pasek (Z=+oD/+iD)
        -oW, -oH,  oD, 1.0f,  -oW,  oH,  oD, 1.0f,  -iW,  oH,  iD, 1.0f,
        -oW, -oH,  oD, 1.0f,  -iW,  oH,  iD, 1.0f,  -iW, -oH,  iD, 1.0f,

        // Œcianka 5: Prawo (Right Wall) X = +oW / +iW (z poprawkami na iH dla wewn.)
        // Zewnêtrzny prostok¹t (normalna -X)
         oW, -oH, -oD, 1.0f,   oW,  oH,  oD, 1.0f,   oW,  oH, -oD, 1.0f, // Poprawiona kolejnoœæ dla -X (CW)
         oW, -oH, -oD, 1.0f,   oW, -oH,  oD, 1.0f,   oW,  oH,  oD, 1.0f,
         // Wewnêtrzny prostok¹t (normalna +X, odwrotna kolejnoœæ)
          iW, -iH, -iD, 1.0f,   iW,  iH, -iD, 1.0f,   iW,  iH,  iD, 1.0f, // Poprawione z oH na iH
          iW, -iH, -iD, 1.0f,   iW,  iH,  iD, 1.0f,   iW, -iH,  iD, 1.0f, // Poprawione z oH na iH
          // £¹czenia krawêdzi
          // Górny pasek (Y=+oH/+iH)
           oW,  oH, -oD, 1.0f,   oW,  oH,  oD, 1.0f,   iW,  iH,  iD, 1.0f,
           oW,  oH, -oD, 1.0f,   iW,  iH,  iD, 1.0f,   iW,  iH, -iD, 1.0f,
           // Dolny pasek (Y=-oH/-iH)
            oW, -oH, -oD, 1.0f,   iW, -iH, -iD, 1.0f,   iW, -iH,  iD, 1.0f,
            oW, -oH, -oD, 1.0f,   iW, -iH,  iD, 1.0f,   oW, -oH,  oD, 1.0f,
            // Przedni pasek (Z=-oD/-iD)
             oW, -oH, -oD, 1.0f,   oW,  oH, -oD, 1.0f,   iW,  oH, -iD, 1.0f,
             oW, -oH, -oD, 1.0f,   iW,  oH, -iD, 1.0f,   iW, -iH, -iD, 1.0f,
             // Tylny pasek (Z=+oD/+iD)
              oW, -oH,  oD, 1.0f,   iW, -iH,  iD, 1.0f,   iW,  oH,  iD, 1.0f,
              oW, -oH,  oD, 1.0f,   iW,  oH,  iD, 1.0f,   oW,  oH,  oD, 1.0f,
};

// Definicja tablic (pamiêtaj o ich wype³nieniu!)
float myAquariumTexCoords[myAquariumVertexCount * 2];
float myAquariumColors[myAquariumVertexCount * 4];

// Implementacja funkcji inicjalizuj¹cej
void initMyAquariumData() {
    for (int i = 0; i < myAquariumVertexCount; ++i) {
        myAquariumTexCoords[i * 2 + 0] = 0.0f; // U
        myAquariumTexCoords[i * 2 + 1] = 0.0f; // V

        myAquariumColors[i * 4 + 0] = 0.2f; // R
        myAquariumColors[i * 4 + 1] = 0.5f; // G
        myAquariumColors[i * 4 + 2] = 1.0f; // B
        myAquariumColors[i * 4 + 3] = 0.3f; // A (alpha dla przezroczystoœci)
    }
}

void drawAquarium(ShaderProgram* sp, GLuint tex, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float localRotationAngleY) {
    initMyAquariumData();
    // 1. Stwórz lokaln¹ macierz transformacji dla tej instancji akwarium
    glm::mat4 M_local = glm::mat4(1.0f); // Macierz jednostkowa

    M_local = glm::translate(M_local, position);
    M_local = glm::rotate(M_local, localRotationAngleY, glm::vec3(0.0f, 1.0f, 0.0f)); // Obróæ wokó³ osi Y
    M_local = glm::scale(M_local, glm::vec3(scale, scale, scale)); // Skaluj jednolicie

    // 2. Po³¹cz lokaln¹ macierz z macierz¹ "rodzica"
    glm::mat4 M_final = parentModelMatrix * M_local;

    // 3. Przeœlij wynikow¹ macierz Modelu (M_final) do shadera
    glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M_final));

    // 4. Logika rysowania akwarium
    glEnableVertexAttribArray(sp->a("vertex"));
    glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, myAquariumVertices);

    glEnableVertexAttribArray(sp->a("texCoord"));
    glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, myAquariumTexCoords);

    glEnableVertexAttribArray(sp->a("color"));
    glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, myAquariumColors);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glUniform1i(sp->u("tex"), 0); // Ustawienie samplera tekstury

    // glDepthMask jest specyficzne dla tego obiektu
    glDepthMask(GL_FALSE);
    glDrawArrays(GL_TRIANGLES, 0, myAquariumVertexCount);
    glDepthMask(GL_TRUE);

    glDisableVertexAttribArray(sp->a("vertex"));
    glDisableVertexAttribArray(sp->a("texCoord"));
    glDisableVertexAttribArray(sp->a("color"));
}