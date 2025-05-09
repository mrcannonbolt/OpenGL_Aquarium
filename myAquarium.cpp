#include "myAquarium.h"
#include <glm/gtc/matrix_transform.hpp> // Dla glm::translate, glm::rotate, glm::scale
#include <glm/gtc/type_ptr.hpp>        // Dla glm::value_ptr

// aby nie za�mieca� globalnej przestrzeni nazw, je�li s� u�ywane tylko tutaj.
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
const float waterBottomY = -iH; // Dno wody na poziomie dna wewn�trznego akwarium
const float waterTopY = -iH + (2.0f * iH * waterFillPercentage); // G�rna powierzchnia wody

const int myWaterVertexCount = 36; // 6 �cian * 2 tr�jk�ty/�ciana * 3 wierzcho�ki/tr�jk�t

// Definicja i inicjalizacja tablicy wierzcho�k�w
float myAquariumVertices[myAquariumVertexCount * 4] = {
    // �cianka 1: Prz�d (Front Wall) Z = -oD / -iD
    // ... (Twoje pe�ne dane wierzcho�k�w, tak jak by�y w .h)
    // Pami�taj o poprawkach dla �cian Lewej/Prawej, o kt�rych rozmawiali�my!
    // Zewn�trzny prostok�t (normalna +Z)
    -oW, -oH, -oD, 1.0f,   oW, -oH, -oD, 1.0f,    oW,  oH, -oD, 1.0f,
    -oW, -oH, -oD, 1.0f,   oW,  oH, -oD, 1.0f,   -oW,  oH, -oD, 1.0f,
    // Wewn�trzny prostok�t (normalna -Z, odwrotna kolejno��)
    -iW, -iH, -iD, 1.0f,  -iW,  iH, -iD, 1.0f,   iW,  iH, -iD, 1.0f,
    -iW, -iH, -iD, 1.0f,   iW,  iH, -iD, 1.0f,   iW, -iH, -iD, 1.0f,
    // ��czenia kraw�dzi (4 paski po 2 tr�jk�ty)
    // G�rny pasek
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

     // �cianka 2: Ty� (Back Wall) Z = +oD / +iD
     // ... i tak dalej dla wszystkich 6 �cianek ...
     // Zewn�trzny prostok�t (normalna -Z)
     -oW, -oH,  oD, 1.0f,  -oW,  oH,  oD, 1.0f,   oW,  oH,  oD, 1.0f,
     -oW, -oH,  oD, 1.0f,   oW,  oH,  oD, 1.0f,   oW, -oH,  oD, 1.0f,
     // Wewn�trzny prostok�t (normalna +Z, odwrotna kolejno��)
     -iW, -iH,  iD, 1.0f,   iW, -iH,  iD, 1.0f,   iW,  iH,  iD, 1.0f,
     -iW, -iH,  iD, 1.0f,   iW,  iH,  iD, 1.0f,  -iW,  iH,  iD, 1.0f,
     // ��czenia kraw�dzi
     // G�rny pasek
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

      // �cianka 3: D� (Bottom Wall) Y = -oH / -iH
      // Zewn�trzny prostok�t (normalna +Y)
      -oW, -oH, -oD, 1.0f,  -oW, -oH,  oD, 1.0f,   oW, -oH,  oD, 1.0f,
      -oW, -oH, -oD, 1.0f,   oW, -oH,  oD, 1.0f,   oW, -oH, -oD, 1.0f,
      // Wewn�trzny prostok�t (normalna -Y, odwrotna kolejno��)
      -iW, -iH, -iD, 1.0f,   iW, -iH, -iD, 1.0f,   iW, -iH,  iD, 1.0f,
      -iW, -iH, -iD, 1.0f,   iW, -iH,  iD, 1.0f,  -iW, -iH,  iD, 1.0f,
      // ��czenia kraw�dzi
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



        // �cianka 4: Lewo (Left Wall) X = -oW / -iW (z poprawkami na iH dla wewn.)
        // Zewn�trzny prostok�t (normalna +X)
        -oW, -oH, -oD, 1.0f,  -oW,  oH, -oD, 1.0f,  -oW,  oH,  oD, 1.0f,
        -oW, -oH, -oD, 1.0f,  -oW,  oH,  oD, 1.0f,  -oW, -oH,  oD, 1.0f,
        // Wewn�trzny prostok�t (normalna -X, odwrotna kolejno��)
        -iW, -iH, -iD, 1.0f,  -iW, -iH,  iD, 1.0f,  -iW,  iH,  iD, 1.0f, // Poprawione z oH na iH
        -iW, -iH, -iD, 1.0f,  -iW,  iH,  iD, 1.0f,  -iW,  iH, -iD, 1.0f, // Poprawione z oH na iH
        // ��czenia kraw�dzi
        // G�rny pasek (Y=+oH/+iH)
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

        // �cianka 5: Prawo (Right Wall) X = +oW / +iW (z poprawkami na iH dla wewn.)
        // Zewn�trzny prostok�t (normalna -X)
         oW, -oH, -oD, 1.0f,   oW,  oH,  oD, 1.0f,   oW,  oH, -oD, 1.0f, // Poprawiona kolejno�� dla -X (CW)
         oW, -oH, -oD, 1.0f,   oW, -oH,  oD, 1.0f,   oW,  oH,  oD, 1.0f,
         // Wewn�trzny prostok�t (normalna +X, odwrotna kolejno��)
          iW, -iH, -iD, 1.0f,   iW,  iH, -iD, 1.0f,   iW,  iH,  iD, 1.0f, // Poprawione z oH na iH
          iW, -iH, -iD, 1.0f,   iW,  iH,  iD, 1.0f,   iW, -iH,  iD, 1.0f, // Poprawione z oH na iH
          // ��czenia kraw�dzi
          // G�rny pasek (Y=+oH/+iH)
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

// Wsp�rz�dne tekstury (U, V)
float myAquariumTexCoords[myAquariumVertexCount * 2] = {
    // �cianka 1: Prz�d
    // Zewn�trzny
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    // Wewn�trzny
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    // Paski ��cz�ce (mapowanie 0-1 dla ka�dego paska)
    // G�rny
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

    // �cianka 2: Ty� (analogicznie do przodu)
    // Zewn�trzny
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    // Wewn�trzny
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    // Paski
    0.0f, 1.0f,   0.0f, 0.0f,   1.0f, 0.0f, // G�rny
    0.0f, 1.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f, // Dolny
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f, // Lewy
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    1.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f, // Prawy
    1.0f, 0.0f,   0.0f, 1.0f,   0.0f, 0.0f,

    // �cianka 3: D�
    // Zewn�trzny
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    // Wewn�trzny
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

    // �cianka 4: Lewo
    // Zewn�trzny
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    // Wewn�trzny
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    // Paski
    0.0f, 1.0f,   0.0f, 0.0f,   1.0f, 0.0f, // G�rny
    0.0f, 1.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f, // Dolny
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f, // Przedni
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    1.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f, // Tylny
    1.0f, 0.0f,   0.0f, 1.0f,   0.0f, 0.0f,

    // �cianka 5: Prawo
    // Zewn�trzny
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f, // Zgodnie z kolejno�ci� wierzcho�k�w
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f,
    // Wewn�trzny
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    // Paski
    0.0f, 1.0f,   1.0f, 1.0f,   1.0f, 0.0f, // G�rny
    0.0f, 1.0f,   1.0f, 0.0f,   0.0f, 0.0f,
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f, // Dolny
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f, // Przedni
    0.0f, 0.0f,   1.0f, 1.0f,   1.0f, 0.0f,
    1.0f, 0.0f,   0.0f, 0.0f,   0.0f, 1.0f, // Tylny
    1.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f,
};

float myWaterVertices[myWaterVertexCount * 4] = {
    // Wsp�rz�dne s� wzgl�dem �rodka akwarium (0,0,0)

    // �ciana: D� (Y = waterBottomY), normalna -Y
    -iW, waterBottomY, -iD, 1.0f,   // Lewy-tylny-dolny
     iW, waterBottomY, -iD, 1.0f,   // Prawy-tylny-dolny
     iW, waterBottomY,  iD, 1.0f,   // Prawy-przedni-dolny
    -iW, waterBottomY, -iD, 1.0f,   // Lewy-tylny-dolny
     iW, waterBottomY,  iD, 1.0f,   // Prawy-przedni-dolny
    -iW, waterBottomY,  iD, 1.0f,   // Lewy-przedni-dolny

    // �ciana: G�ra (Y = waterTopY), normalna +Y (powierzchnia wody)
    -iW, waterTopY,  iD, 1.0f,   // Lewy-przedni-g�rny
     iW, waterTopY,  iD, 1.0f,   // Prawy-przedni-g�rny
     iW, waterTopY, -iD, 1.0f,   // Prawy-tylny-g�rny
    -iW, waterTopY,  iD, 1.0f,   // Lewy-przedni-g�rny
     iW, waterTopY, -iD, 1.0f,   // Prawy-tylny-g�rny
    -iW, waterTopY, -iD, 1.0f,   // Lewy-tylny-g�rny

    // �ciana: Prz�d (Z = iD), normalna +Z
    -iW, waterBottomY,  iD, 1.0f,   // Lewy-dolny-przedni
     iW, waterBottomY,  iD, 1.0f,   // Prawy-dolny-przedni
     iW, waterTopY,     iD, 1.0f,   // Prawy-g�rny-przedni
    -iW, waterBottomY,  iD, 1.0f,   // Lewy-dolny-przedni
     iW, waterTopY,     iD, 1.0f,   // Prawy-g�rny-przedni
    -iW, waterTopY,     iD, 1.0f,   // Lewy-g�rny-przedni

    // �ciana: Ty� (Z = -iD), normalna -Z
     iW, waterBottomY, -iD, 1.0f,   // Prawy-dolny-tylny
    -iW, waterBottomY, -iD, 1.0f,   // Lewy-dolny-tylny
    -iW, waterTopY,    -iD, 1.0f,   // Lewy-g�rny-tylny
     iW, waterBottomY, -iD, 1.0f,   // Prawy-dolny-tylny
    -iW, waterTopY,    -iD, 1.0f,   // Lewy-g�rny-tylny
     iW, waterTopY,    -iD, 1.0f,   // Prawy-g�rny-tylny

     // �ciana: Lewo (X = -iW), normalna -X
     -iW, waterBottomY, -iD, 1.0f,   // Tylny-dolny-lewy
     -iW, waterBottomY,  iD, 1.0f,   // Przedni-dolny-lewy
     -iW, waterTopY,     iD, 1.0f,   // Przedni-g�rny-lewy
     -iW, waterBottomY, -iD, 1.0f,   // Tylny-dolny-lewy
     -iW, waterTopY,     iD, 1.0f,   // Przedni-g�rny-lewy
     -iW, waterTopY,    -iD, 1.0f,   // Tylny-g�rny-lewy

     // �ciana: Prawo (X = iW), normalna +X
      iW, waterBottomY,  iD, 1.0f,   // Przedni-dolny-prawy
      iW, waterBottomY, -iD, 1.0f,   // Tylny-dolny-prawy
      iW, waterTopY,    -iD, 1.0f,   // Tylny-g�rny-prawy
      iW, waterBottomY,  iD, 1.0f,   // Przedni-dolny-prawy
      iW, waterTopY,    -iD, 1.0f,   // Tylny-g�rny-prawy
      iW, waterTopY,     iD, 1.0f,   // Przedni-g�rny-prawy
};

// Wsp�rz�dne tekstury dla wody (U, V)
float myWaterTexCoords[myWaterVertexCount * 2] = {
    // D�
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    // G�ra (powierzchnia wody)
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f, // Mo�esz chcie� inaczej mapowa� powierzchni�
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    // Prz�d
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f, // 1.0f na g�rze odpowiada waterTopY
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    // Ty�
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    // Lewo
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
    // Prawo
    0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
    0.0f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f,
};


// Definicja tablic (pami�taj o ich wype�nieniu!)
float myAquariumColors[myAquariumVertexCount * 4];

// Implementacja funkcji inicjalizuj�cej
void initMyAquariumData() {
    for (int i = 0; i < myAquariumVertexCount; ++i) {
        myAquariumColors[i * 4 + 0] = 0.2f; // R
        myAquariumColors[i * 4 + 1] = 0.5f; // G
        myAquariumColors[i * 4 + 2] = 1.0f; // B
        myAquariumColors[i * 4 + 3] = 0.3f; // A (alpha dla przezroczysto�ci)
    }
}

void drawAquarium(ShaderProgram* spTextured, GLuint tex, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float localRotationAngleY) {
    initMyAquariumData();
    // 1. Stw�rz lokaln� macierz transformacji dla tej instancji akwarium
    glm::mat4 M_local = glm::mat4(1.0f); // Macierz jednostkowa

    M_local = glm::translate(M_local, position);
    M_local = glm::rotate(M_local, localRotationAngleY, glm::vec3(0.0f, 1.0f, 0.0f)); // Obr�� wok� osi Y
    M_local = glm::scale(M_local, glm::vec3(scale, scale, scale)); // Skaluj jednolicie

    // 2. Po��cz lokaln� macierz z macierz� "rodzica"
    glm::mat4 M_final = parentModelMatrix * M_local;

    // 3. Prze�lij wynikow� macierz Modelu (M_final) do shadera
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
    // Woda nie potrzebuje w�asnej inicjalizacji danych w tej funkcji,
    // poniewa� myWaterVertices i myWaterTexCoords s� globalne i sta�e.

    // 1. Stw�rz lokaln� macierz transformacji dla wody.
    // Zak�adamy, �e woda jest cz�ci� akwarium, wi�c jej transformacje
    // powinny by� wzgl�dem akwarium. Je�li 'position', 'scale', 'localRotationAngleY'
    // odnosz� si� do ca�ego akwarium (jak w drawAquarium), to M_local dla wody
    // powinno by� macierz� jednostkow�, a M_final b�dzie takie samo jak dla akwarium.
    // Je�li jednak chcesz wod� pozycjonowa�/skalowa�/obraca� niezale�nie *wewn�trz*
    // przestrzeni akwarium, musia�by� to tutaj uwzgl�dni�.
    // Dla prostoty, zak�adam, �e woda dziedziczy transformacje akwarium.
    glm::mat4 M_local_water = glm::mat4(1.0f); // Macierz jednostkowa, bo wierzcho�ki s� ju� w przestrzeni lokalnej akwarium

    // Po��cz z macierz� rodzica (ca�ego akwarium)
    // Je�li 'position', 'scale', 'localRotationAngleY' to globalne transformacje akwarium
    glm::mat4 M_aquarium_transform = glm::mat4(1.0f);
    M_aquarium_transform = glm::translate(M_aquarium_transform, position);
    M_aquarium_transform = glm::rotate(M_aquarium_transform, localRotationAngleY, glm::vec3(0.0f, 1.0f, 0.0f));
    M_aquarium_transform = glm::scale(M_aquarium_transform, glm::vec3(scale, scale, scale));

    glm::mat4 M_final = parentModelMatrix * M_aquarium_transform * M_local_water;


    // 2. Prze�lij wynikow� macierz Modelu (M_final) do shadera wody
    glUniformMatrix4fv(spWater->u("M"), 1, false, glm::value_ptr(M_final));

    // 3. Logika rysowania wody
    glEnableVertexAttribArray(spWater->a("vertex")); // U�yj nazw atrybut�w ze swojego shadera wody
    glVertexAttribPointer(spWater->a("vertex"), 4, GL_FLOAT, false, 0, myWaterVertices);

    glEnableVertexAttribArray(spWater->a("texCoord")); // U�yj nazw atrybut�w ze swojego shadera wody
    glVertexAttribPointer(spWater->a("texCoord"), 2, GL_FLOAT, false, 0, myWaterTexCoords);

    glActiveTexture(GL_TEXTURE0); // Aktywuj jednostk� teksturuj�c�
    glBindTexture(GL_TEXTURE_2D, texWater); // Zbinduj tekstur� wody
    glUniform1i(spWater->u("tex"), 0); // Ustaw sampler tekstury dla shadera wody

    // Woda jest zazwyczaj p�przezroczysta.
    // Upewnij si�, �e blendowanie jest w��czone przed rysowaniem wody
    // i potencjalnie wy��czone po, je�li inne obiekty nie s� przezroczyste.
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Typowe ustawienie dla przezroczysto�ci

    // Dla wody, glDepthMask(GL_FALSE) jest cz�sto u�ywane, aby inne przezroczyste
    // obiekty za wod� by�y poprawnie renderowane, ale powierzchnia wody
    // powinna zapisywa� do bufora g��bi, je�li jest nieprzezroczysta lub ostatnia.
    // Je�li woda jest p�przezroczysta i chcesz widzie� przez ni� dno akwarium,
    // by� mo�e b�dziesz chcia� rysowa� akwarium (szk�o) po wodzie,
    // lub u�y� glDepthMask(GL_TRUE) dla wody i sortowa� obiekty.
    // Twoja funkcja drawAquarium u�ywa glDepthMask(GL_FALSE) -> glDepthMask(GL_TRUE).
    // Dla wody, je�li jest rysowana przed szk�em i ma by� widoczna przez szk�o:
    // glDepthMask(GL_TRUE); // Woda powinna normalnie zapisywa� do bufora g��bi

    glDrawArrays(GL_TRIANGLES, 0, myWaterVertexCount);

    // glDisable(GL_BLEND); // Je�li by�o w��czone tylko dla wody

    glDisableVertexAttribArray(spWater->a("vertex"));
    glDisableVertexAttribArray(spWater->a("texCoord"));
}