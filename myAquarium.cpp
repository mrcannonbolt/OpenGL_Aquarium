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

const float waterFillPercentage = 0.90f;
const float waterBottomY = -iH; // Dno wody na poziomie dna wewnêtrznego akwarium
const float waterTopY = -iH + (2.0f * iH * waterFillPercentage); // Górna powierzchnia wody

const int myWaterVertexCount = 36; // 6 œcian * 2 trójk¹ty/œciana * 3 wierzcho³ki/trójk¹t

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

// Wspó³rzêdne tekstury (U, V)
float myAquariumTexCoords[myAquariumVertexCount * 2] = {
    // Œcianka 1: Przód
    // Zewnêtrzny
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    // Wewnêtrzny
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    // Paski ³¹cz¹ce (mapowanie 0-1 dla ka¿dego paska)
    // Górny
    0.0f, 1.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    0.0f, 1.0f,   1.0f, 0.0f,   0.0f, 0.0f,
    // Dolny
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    // Lewy
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    // Prawy
    1.0f, 0.0f,   0.0f, 0.0f,   0.0f, 1.0f,
    1.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f,

    // Œcianka 2: Ty³ (analogicznie do przodu)
    // Zewnêtrzny
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    // Wewnêtrzny
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    // Paski
    0.0f, 1.0f,   0.0f, 0.0f,   1.0f, 0.0f, // Górny
    0.0f, 1.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f, // Dolny
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f, // Lewy
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    1.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f, // Prawy
    1.0f, 0.0f,   0.0f, 1.0f,   0.0f, 0.0f,

    // Œcianka 3: Dó³
    // Zewnêtrzny
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    // Wewnêtrzny
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    // Paski
    0.0f, 1.0f,   1.0f, 1.0f,   1.0f, 0.0f, // Przedni
    0.0f, 1.0f,   1.0f, 0.0f,   0.0f, 0.0f,
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f, // Tylny
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f, // Lewy
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    1.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f, // Prawy
    1.0f, 0.0f,   0.0f, 1.0f,   0.0f, 0.0f,

    // Œcianka 4: Lewo
    // Zewnêtrzny
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    // Wewnêtrzny
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    // Paski
    0.0f, 1.0f,   0.0f, 0.0f,   1.0f, 0.0f, // Górny
    0.0f, 1.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f, // Dolny
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f, // Przedni
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    1.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f, // Tylny
    1.0f, 0.0f,   0.0f, 1.0f,   0.0f, 0.0f,

    // Œcianka 5: Prawo
    // Zewnêtrzny
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f, // Zgodnie z kolejnoœci¹ wierzcho³ków
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f,
    // Wewnêtrzny
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    // Paski
    0.0f, 1.0f,   1.0f, 1.0f,   1.0f, 0.0f, // Górny
    0.0f, 1.0f,   1.0f, 0.0f,   0.0f, 0.0f,
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f, // Dolny
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f, // Przedni
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    1.0f, 0.0f,   0.0f, 0.0f,   0.0f, 1.0f, // Tylny
    1.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f,
};

float myWaterVertices[myWaterVertexCount * 4] = {
    // Wspó³rzêdne s¹ wzglêdem œrodka akwarium (0,0,0)

    // Œciana: Dó³ (Y = waterBottomY), normalna -Y
    -iW, waterBottomY, -iD, 1.0f,   // Lewy-tylny-dolny
     iW, waterBottomY, -iD, 1.0f,   // Prawy-tylny-dolny
     iW, waterBottomY,  iD, 1.0f,   // Prawy-przedni-dolny
    -iW, waterBottomY, -iD, 1.0f,   // Lewy-tylny-dolny
     iW, waterBottomY,  iD, 1.0f,   // Prawy-przedni-dolny
    -iW, waterBottomY,  iD, 1.0f,   // Lewy-przedni-dolny

    // Œciana: Góra (Y = waterTopY), normalna +Y (powierzchnia wody)
    -iW, waterTopY,  iD, 1.0f,   // Lewy-przedni-górny
     iW, waterTopY,  iD, 1.0f,   // Prawy-przedni-górny
     iW, waterTopY, -iD, 1.0f,   // Prawy-tylny-górny
    -iW, waterTopY,  iD, 1.0f,   // Lewy-przedni-górny
     iW, waterTopY, -iD, 1.0f,   // Prawy-tylny-górny
    -iW, waterTopY, -iD, 1.0f,   // Lewy-tylny-górny

    // Œciana: Przód (Z = iD), normalna +Z
    -iW, waterBottomY,  iD, 1.0f,   // Lewy-dolny-przedni
     iW, waterBottomY,  iD, 1.0f,   // Prawy-dolny-przedni
     iW, waterTopY,     iD, 1.0f,   // Prawy-górny-przedni
    -iW, waterBottomY,  iD, 1.0f,   // Lewy-dolny-przedni
     iW, waterTopY,     iD, 1.0f,   // Prawy-górny-przedni
    -iW, waterTopY,     iD, 1.0f,   // Lewy-górny-przedni

    // Œciana: Ty³ (Z = -iD), normalna -Z
     iW, waterBottomY, -iD, 1.0f,   // Prawy-dolny-tylny
    -iW, waterBottomY, -iD, 1.0f,   // Lewy-dolny-tylny
    -iW, waterTopY,    -iD, 1.0f,   // Lewy-górny-tylny
     iW, waterBottomY, -iD, 1.0f,   // Prawy-dolny-tylny
    -iW, waterTopY,    -iD, 1.0f,   // Lewy-górny-tylny
     iW, waterTopY,    -iD, 1.0f,   // Prawy-górny-tylny

     // Œciana: Lewo (X = -iW), normalna -X
     -iW, waterBottomY, -iD, 1.0f,   // Tylny-dolny-lewy
     -iW, waterBottomY,  iD, 1.0f,   // Przedni-dolny-lewy
     -iW, waterTopY,     iD, 1.0f,   // Przedni-górny-lewy
     -iW, waterBottomY, -iD, 1.0f,   // Tylny-dolny-lewy
     -iW, waterTopY,     iD, 1.0f,   // Przedni-górny-lewy
     -iW, waterTopY,    -iD, 1.0f,   // Tylny-górny-lewy

     // Œciana: Prawo (X = iW), normalna +X
      iW, waterBottomY,  iD, 1.0f,   // Przedni-dolny-prawy
      iW, waterBottomY, -iD, 1.0f,   // Tylny-dolny-prawy
      iW, waterTopY,    -iD, 1.0f,   // Tylny-górny-prawy
      iW, waterBottomY,  iD, 1.0f,   // Przedni-dolny-prawy
      iW, waterTopY,    -iD, 1.0f,   // Tylny-górny-prawy
      iW, waterTopY,     iD, 1.0f,   // Przedni-górny-prawy
};

// Wspó³rzêdne tekstury dla wody (U, V)
float myWaterTexCoords[myWaterVertexCount * 2] = {
    // Dó³
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    // Góra (powierzchnia wody)
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f, // Mo¿esz chcieæ inaczej mapowaæ powierzchniê
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    // Przód
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f, // 1.0f na górze odpowiada waterTopY
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    // Ty³
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    // Lewo
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    // Prawo
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
};


// Definicja tablic (pamiêtaj o ich wype³nieniu!)
float myAquariumColors[myAquariumVertexCount * 4];

// Implementacja funkcji inicjalizuj¹cej
void initMyAquariumData() {
    for (int i = 0; i < myAquariumVertexCount; ++i) {
        myAquariumColors[i * 4 + 0] = 0.2f; // R
        myAquariumColors[i * 4 + 1] = 0.5f; // G
        myAquariumColors[i * 4 + 2] = 1.0f; // B
        myAquariumColors[i * 4 + 3] = 0.3f; // A (alpha dla przezroczystoœci)
    }
}

void drawAquarium(ShaderProgram* spTextured, GLuint tex, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float localRotationAngleY) {
    initMyAquariumData();
    // 1. Stwórz lokaln¹ macierz transformacji dla tej instancji akwarium
    glm::mat4 M_local = glm::mat4(1.0f); // Macierz jednostkowa

    M_local = glm::translate(M_local, position);
    M_local = glm::rotate(M_local, localRotationAngleY, glm::vec3(0.0f, 1.0f, 0.0f)); // Obróæ wokó³ osi Y
    M_local = glm::scale(M_local, glm::vec3(scale, scale, scale)); // Skaluj jednolicie

    // 2. Po³¹cz lokaln¹ macierz z macierz¹ "rodzica"
    glm::mat4 M_final = parentModelMatrix * M_local;

    // 3. Przeœlij wynikow¹ macierz Modelu (M_final) do shadera
    glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M_final));

    // 4. Logika rysowania akwarium
    glEnableVertexAttribArray(spTextured->a("vertex"));
    glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, myAquariumVertices);

    glEnableVertexAttribArray(spTextured->a("texCoord"));
    glVertexAttribPointer(spTextured->a("texCoord"), 2, GL_FLOAT, false, 0, myAquariumTexCoords);

    //glEnableVertexAttribArray(sp->a("color"));
    //glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, myAquariumColors);

    glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, tex);
    glUniform1i(spTextured->u("tex"), 0); // Ustawienie samplera tekstury

    // glDepthMask jest specyficzne dla tego obiektu
    glDepthMask(GL_FALSE);
    glDrawArrays(GL_TRIANGLES, 0, myAquariumVertexCount);
    glDepthMask(GL_TRUE);

    glDisableVertexAttribArray(spTextured->a("vertex"));
    glDisableVertexAttribArray(spTextured->a("texCoord"));
    //glDisableVertexAttribArray(sp->a("color"));
}

void drawWater(ShaderProgram* spWater, GLuint texWater, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float localRotationAngleY) {
    // Woda nie potrzebuje w³asnej inicjalizacji danych w tej funkcji,
    // poniewa¿ myWaterVertices i myWaterTexCoords s¹ globalne i sta³e.

    // 1. Stwórz lokaln¹ macierz transformacji dla wody.
    // Zak³adamy, ¿e woda jest czêœci¹ akwarium, wiêc jej transformacje
    // powinny byæ wzglêdem akwarium. Jeœli 'position', 'scale', 'localRotationAngleY'
    // odnosz¹ siê do ca³ego akwarium (jak w drawAquarium), to M_local dla wody
    // powinno byæ macierz¹ jednostkow¹, a M_final bêdzie takie samo jak dla akwarium.
    // Jeœli jednak chcesz wodê pozycjonowaæ/skalowaæ/obracaæ niezale¿nie *wewn¹trz*
    // przestrzeni akwarium, musia³byœ to tutaj uwzglêdniæ.
    // Dla prostoty, zak³adam, ¿e woda dziedziczy transformacje akwarium.
    glm::mat4 M_local_water = glm::mat4(1.0f); // Macierz jednostkowa, bo wierzcho³ki s¹ ju¿ w przestrzeni lokalnej akwarium

    // Po³¹cz z macierz¹ rodzica (ca³ego akwarium)
    // Jeœli 'position', 'scale', 'localRotationAngleY' to globalne transformacje akwarium
    glm::mat4 M_aquarium_transform = glm::mat4(1.0f);
    M_aquarium_transform = glm::translate(M_aquarium_transform, position);
    M_aquarium_transform = glm::rotate(M_aquarium_transform, localRotationAngleY, glm::vec3(0.0f, 1.0f, 0.0f));
    M_aquarium_transform = glm::scale(M_aquarium_transform, glm::vec3(scale, scale, scale));

    glm::mat4 M_final = parentModelMatrix * M_aquarium_transform * M_local_water;


    // 2. Przeœlij wynikow¹ macierz Modelu (M_final) do shadera wody
    glUniformMatrix4fv(spWater->u("M"), 1, false, glm::value_ptr(M_final));

    // 3. Logika rysowania wody
    glEnableVertexAttribArray(spWater->a("vertex")); // U¿yj nazw atrybutów ze swojego shadera wody
    glVertexAttribPointer(spWater->a("vertex"), 4, GL_FLOAT, false, 0, myWaterVertices);

    glEnableVertexAttribArray(spWater->a("texCoord")); // U¿yj nazw atrybutów ze swojego shadera wody
    glVertexAttribPointer(spWater->a("texCoord"), 2, GL_FLOAT, false, 0, myWaterTexCoords);

    glActiveTexture(GL_TEXTURE0); // Aktywuj jednostkê teksturuj¹c¹
    glBindTexture(GL_TEXTURE_2D, texWater); // Zbinduj teksturê wody
    glUniform1i(spWater->u("tex"), 0); // Ustaw sampler tekstury dla shadera wody

    // Woda jest zazwyczaj pó³przezroczysta.
    // Upewnij siê, ¿e blendowanie jest w³¹czone przed rysowaniem wody
    // i potencjalnie wy³¹czone po, jeœli inne obiekty nie s¹ przezroczyste.
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Typowe ustawienie dla przezroczystoœci

    // Dla wody, glDepthMask(GL_FALSE) jest czêsto u¿ywane, aby inne przezroczyste
    // obiekty za wod¹ by³y poprawnie renderowane, ale powierzchnia wody
    // powinna zapisywaæ do bufora g³êbi, jeœli jest nieprzezroczysta lub ostatnia.
    // Jeœli woda jest pó³przezroczysta i chcesz widzieæ przez ni¹ dno akwarium,
    // byæ mo¿e bêdziesz chcia³ rysowaæ akwarium (szk³o) po wodzie,
    // lub u¿yæ glDepthMask(GL_TRUE) dla wody i sortowaæ obiekty.
    // Twoja funkcja drawAquarium u¿ywa glDepthMask(GL_FALSE) -> glDepthMask(GL_TRUE).
    // Dla wody, jeœli jest rysowana przed szk³em i ma byæ widoczna przez szk³o:
    // glDepthMask(GL_TRUE); // Woda powinna normalnie zapisywaæ do bufora g³êbi

    glDrawArrays(GL_TRIANGLES, 0, myWaterVertexCount);

    // glDisable(GL_BLEND); // Jeœli by³o w³¹czone tylko dla wody

    glDisableVertexAttribArray(spWater->a("vertex"));
    glDisableVertexAttribArray(spWater->a("texCoord"));
}