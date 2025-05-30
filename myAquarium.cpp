#include "myAquarium.h"
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>       

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

const int myWaterVertexCount = 36;

// Definicja i inicjalizacja tablicy wierzcho³ków
float myAquariumVertices[myAquariumVertexCount * 4] = {
    // Œcianka 1: Przód (Front Wall) Z = -oD / -iD
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
        -iW, -iH, -iD, 1.0f,  -iW, -iH,  iD, 1.0f,  -iW,  iH,  iD, 1.0f, 
        -iW, -iH, -iD, 1.0f,  -iW,  iH,  iD, 1.0f,  -iW,  iH, -iD, 1.0f, 
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
         oW, -oH, -oD, 1.0f,   oW,  oH,  oD, 1.0f,   oW,  oH, -oD, 1.0f,
         oW, -oH, -oD, 1.0f,   oW, -oH,  oD, 1.0f,   oW,  oH,  oD, 1.0f,
         // Wewnêtrzny prostok¹t (normalna +X, odwrotna kolejnoœæ)
          iW, -iH, -iD, 1.0f,   iW,  iH, -iD, 1.0f,   iW,  iH,  iD, 1.0f,
          iW, -iH, -iD, 1.0f,   iW,  iH,  iD, 1.0f,   iW, -iH,  iD, 1.0f,
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
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
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
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
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

float myAquariumNormals[180 * 3] = {
    // Œcianka 1: Przód (Front Wall) Z = -oD / -iD (36 wierzcho³ków)
    // Zewnêtrzny prostok¹t (normalna (0,0,1) - skierowana DO OBSERATORA) - 6 wierzcho³ków
    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
    // Wewnêtrzny prostok¹t (normalna (0,0,-1) - skierowana DO WNÊTRZA AKWARIUM) - 6 wierzcho³ków
    0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,
    // Paski ³¹cz¹ce:
    // Górny pasek (normalna (0,1,0)) - 6 wierzcho³ków
    0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
    // Dolny pasek (normalna (0,-1,0)) - 6 wierzcho³ków
    0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
    // Lewy pasek (normalna (-1,0,0)) - 6 wierzcho³ków
    -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
    // Prawy pasek (normalna (1,0,0)) - 6 wierzcho³ków
    1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,

    // Œcianka 2: Ty³ (Back Wall) Z = +oD / +iD (kolejne 36 wierzcho³ków)
    // Zewnêtrzny prostok¹t (normalna (0,0,-1) - skierowana OD OBSERWATORA) - 6 wierzcho³ków
    0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,
    // Wewnêtrzny prostok¹t (normalna (0,0,1) - skierowana DO WNÊTRZA AKWARIUM) - 6 wierzcho³ków
    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
    // Paski: Górny (0,1,0), Dolny (0,-1,0), Lewy (-1,0,0), Prawy (1,0,0)
    0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f, // Górny
    0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f, // Dolny
    0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f, // Lewy
    -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,  // Prawy
    1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,

    // Œcianka 3: Dó³ (Bottom Wall) Y = -oH / -iH (kolejne 36 wierzcho³ków)
    // Zewnêtrzny prostok¹t (normalna (0,-1,0) - skierowana W DÓ£)
    0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
    // Wewnêtrzny prostok¹t (dno akwarium, normalna (0,1,0) - skierowana W GÓRÊ)
    0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
    // Paski: Przedni (0,0,-1), Tylny (0,0,1), Lewy (-1,0,0), Prawy (1,0,0)
    0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f, // Przedni
    0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,  // Tylny
    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
    -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f, // Lewy
    -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,  // Prawy
    1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,

    // Œcianka 4: Lewo (Left Wall) X = -oW / -iW (kolejne 36 wierzcho³ków)
    // Zewnêtrzny prostok¹t (normalna (-1,0,0) - skierowana W LEWO)
    -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
    // Wewnêtrzny prostok¹t (normalna (1,0,0) - skierowana W PRAWO, DO WNÊTRZA)
    1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
    // Paski: Górny (0,1,0), Dolny (0,-1,0), Przedni (0,0,-1), Tylny (0,0,1)
    0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,  // Górny
    0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f, // Dolny
    0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
    0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f, // Przedni
    0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,  // Tylny
    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,

    // Œcianka 5: Prawo (Right Wall) X = +oW / +iW (kolejne 36 wierzcho³ków)
    // Zewnêtrzny prostok¹t (normalna (1,0,0) - skierowana W PRAWO)
    1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
    // Wewnêtrzny prostok¹t (normalna (-1,0,0) - skierowana W LEWO, DO WNÊTRZA)
    -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
    // Paski: Górny (0,1,0), Dolny (0,-1,0), Przedni (0,0,-1), Tylny (0,0,1)
    0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,  // Górny
    0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f, // Dolny
    0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
    0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f, // Przedni
    0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,  // Tylny
    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
};

float myWaterNormals[36 * 3] = {
    // Œciana: Dó³ (Y = waterBottomY), normalna skierowana W DÓ£ (na zewn¹trz objêtoœci wody)
    0.0f, -1.0f, 0.0f,   0.0f, -1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,   0.0f, -1.0f, 0.0f,   0.0f, -1.0f, 0.0f,

    // Œciana: Góra (Y = waterTopY, powierzchnia wody), normalna skierowana W GÓRÊ
    0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 0.0f,

    // Œciana: Przód (Z = iD, z perspektywy wody), normalna skierowana DO PRZODU (+Z)
    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,

    // Œciana: Ty³ (Z = -iD, z perspektywy wody), normalna skierowana DO TY£U (-Z)
    0.0f, 0.0f, -1.0f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f, -1.0f,

    // Œciana: Lewo (X = -iW, z perspektywy wody), normalna skierowana W LEWO (-X)
    -1.0f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,

    // Œciana: Prawo (X = iW, z perspektywy wody), normalna skierowana W PRAWO (+X)
    1.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,
};

void drawAquarium(ShaderProgram* spTextured, GLuint tex, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float localRotationAngleY) {
    // Tworzenie lokalnej macierzy transformacji dla tej instancji akwarium
    glm::mat4 M_local = glm::mat4(1.0f);

    M_local = glm::translate(M_local, position);
    M_local = glm::rotate(M_local, localRotationAngleY, glm::vec3(0.0f, 1.0f, 0.0f)); // Obróæ wokó³ osi Y
    M_local = glm::scale(M_local, glm::vec3(scale, scale, scale)); // Skaluj jednolicie
    // Po³¹czenie lokaln¹ macierz z macierz¹ "rodzica"
    glm::mat4 M_final = parentModelMatrix * M_local;

    // Przesy³anie wynikow¹ macierz Modelu (M_final) do shadera
    glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M_final));

    // Logika rysowania akwarium
    glEnableVertexAttribArray(spTextured->a("vertex"));
    glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, myAquariumVertices);

    glEnableVertexAttribArray(spTextured->a("texCoord0"));
    glVertexAttribPointer(spTextured->a("texCoord0"), 2, GL_FLOAT, false, 0, myAquariumTexCoords);
    glEnableVertexAttribArray(spTextured->a("normal")); 
    glVertexAttribPointer(spTextured->a("normal"), 3, GL_FLOAT, false, 0, myAquariumNormals);

    glBindTexture(GL_TEXTURE_2D, tex);

    glDrawArrays(GL_TRIANGLES, 0, myAquariumVertexCount);

    glDisableVertexAttribArray(spTextured->a("vertex"));
    glDisableVertexAttribArray(spTextured->a("texCoord0"));
    glDisableVertexAttribArray(spTextured->a("normal"));

}

void drawWater(ShaderProgram* spWater, GLuint texWater, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float localRotationAngleY) {
   
    glm::mat4 M_local_water = glm::mat4(1.0f);

    // Po³¹czenie z macierz¹ rodzica (ca³ego akwarium)
    glm::mat4 M_aquarium_transform = glm::mat4(1.0f);
    M_aquarium_transform = glm::translate(M_aquarium_transform, position);
    M_aquarium_transform = glm::rotate(M_aquarium_transform, localRotationAngleY, glm::vec3(0.0f, 1.0f, 0.0f));
    M_aquarium_transform = glm::scale(M_aquarium_transform, glm::vec3(scale, scale, scale));

    glm::mat4 M_final = parentModelMatrix * M_aquarium_transform * M_local_water;


    // Przesy³anie wynikow¹ macierz Modelu (M_final) do shadera wody
    glUniformMatrix4fv(spWater->u("M"), 1, false, glm::value_ptr(M_final));
    // Logika rysowania wody
    glEnableVertexAttribArray(spWater->a("vertex")); 
    glVertexAttribPointer(spWater->a("vertex"), 4, GL_FLOAT, false, 0, myWaterVertices);

    glEnableVertexAttribArray(spWater->a("texCoord0")); 
    glVertexAttribPointer(spWater->a("texCoord0"), 2, GL_FLOAT, false, 0, myWaterTexCoords);
    glEnableVertexAttribArray(spWater->a("normal")); 
    glVertexAttribPointer(spWater->a("normal"), 3, GL_FLOAT, false, 0, myWaterNormals); 

    glBindTexture(GL_TEXTURE_2D, texWater);

    glDrawArrays(GL_TRIANGLES, 0, myWaterVertexCount);


    glDisableVertexAttribArray(spWater->a("vertex"));
    glDisableVertexAttribArray(spWater->a("texCoord0"));
    glDisableVertexAttribArray(spWater->a("normal"));
}