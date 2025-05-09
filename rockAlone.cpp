#include "rockalone.h"
#include <glm/gtc/matrix_transform.hpp> // Dla glm::translate, glm::rotate, glm::scale
#include <glm/gtc/type_ptr.hpp>       // Dla glm::value_ptr
#include <vector>                     // Dla dynamicznego tworzenia list wierzcho�k�w
#include <cmath>                      // Dla sin, cos, M_PI (je�li zdefiniowane)
#include "constants.h"


// Prawdopodobnie b�dziesz potrzebowa� r�wnie�:
// #include "shaderprogram.h" // Je�li ShaderProgram jest tam zdefiniowany
// #include <GL/glew.h>     // Dla funkcji OpenGL

// --- Sta�e i dane dla obiektu kamienia ---

const int stoneLatitudeSegments = 16;  // Liczba segment�w wzd�u� szeroko�ci geograficznej (wp�ywa na g�adko�� g�ra-d�)
const int stoneLongitudeSegments = 24; // Liczba segment�w wzd�u� d�ugo�ci geograficznej (wp�ywa na g�adko�� wok� osi Y)

// Ca�kowita liczba wierzcho�k�w do narysowania kamienia (ka�dy prostok�t siatki to 2 tr�jk�ty, ka�dy tr�jk�t to 3 wierzcho�ki)
const int myStoneVertexCount = stoneLatitudeSegments * stoneLongitudeSegments * 6;

// Globalne tablice dla wierzcho�k�w i wsp�rz�dnych tekstury kamienia
// UWAGA: To s� du�e tablice globalne. W bardziej z�o�onych aplikacjach
// lepiej zarz�dza� tymi danymi w klasach lub u�ywa� dynamicznej alokacji
// i VBO/VAO per obiekt, tak jak robili�my to dla Aquarium.
// Dla sp�jno�ci z Twoim podej�ciem "myAquarium", zostawiam je jako globalne.
float myStoneVertices[myStoneVertexCount * 4];   // X, Y, Z, W
float myStoneTexCoords[myStoneVertexCount * 2]; // U, V

// Flaga informuj�ca, czy dane kamienia zosta�y ju� zainicjalizowane
// aby unikn�� niepotrzebnego przeliczania wierzcho�k�w w ka�dej klatce.
bool stoneDataInitialized = false;
float lastStoneLength = -1.0f, lastStoneWidth = -1.0f, lastStoneHeight = -1.0f;


// Funkcja inicjalizuj�ca/aktualizuj�ca dane wierzcho�k�w i tekstur dla kamienia
void initMyStoneData(float stoneLength, float stoneWidth, float stoneHeight) {
    // Je�li wymiary si� nie zmieni�y i dane by�y ju� inicjalizowane, nie r�b nic
    if (stoneDataInitialized &&
        lastStoneLength == stoneLength &&
        lastStoneWidth == stoneWidth &&
        lastStoneHeight == stoneHeight) {
        return;
    }

    printf("Initializing stone data (L:%.2f, W:%.2f, H:%.2f)...\n", stoneLength, stoneWidth, stoneHeight);

    float radiusX = stoneLength / 2.0f;
    float radiusY = stoneHeight / 2.0f; // Wysoko�� kamienia
    float radiusZ = stoneWidth / 2.0f;

    int vertexIndex = 0;
    int texCoordIndex = 0;

    for (int i = 0; i < stoneLatitudeSegments; ++i) { // P�tle po segmentach szeroko�ci geograficznej (theta)
        float theta1 = (float)i / stoneLatitudeSegments * PI;
        float theta2 = (float)(i + 1) / stoneLatitudeSegments * PI;

        for (int j = 0; j < stoneLongitudeSegments; ++j) { // P�tle po segmentach d�ugo�ci geograficznej (phi)
            float phi1 = (float)j / stoneLongitudeSegments * 2.0f * PI;
            float phi2 = (float)(j + 1) / stoneLongitudeSegments * 2.0f * PI;

            // Wierzcho�ki czworok�ta na sferze/elipsoidzie
            glm::vec3 v1 = glm::vec3(radiusX * sin(theta1) * cos(phi1), radiusY * cos(theta1), radiusZ * sin(theta1) * sin(phi1));
            glm::vec3 v2 = glm::vec3(radiusX * sin(theta1) * cos(phi2), radiusY * cos(theta1), radiusZ * sin(theta1) * sin(phi2));
            glm::vec3 v3 = glm::vec3(radiusX * sin(theta2) * cos(phi2), radiusY * cos(theta2), radiusZ * sin(theta2) * sin(phi2));
            glm::vec3 v4 = glm::vec3(radiusX * sin(theta2) * cos(phi1), radiusY * cos(theta2), radiusZ * sin(theta2) * sin(phi1));

            // Wsp�rz�dne tekstury dla wierzcho�k�w
            glm::vec2 uv1 = glm::vec2((float)j / stoneLongitudeSegments, (float)i / stoneLatitudeSegments);
            glm::vec2 uv2 = glm::vec2((float)(j + 1) / stoneLongitudeSegments, (float)i / stoneLatitudeSegments);
            glm::vec2 uv3 = glm::vec2((float)(j + 1) / stoneLongitudeSegments, (float)(i + 1) / stoneLatitudeSegments);
            glm::vec2 uv4 = glm::vec2((float)j / stoneLongitudeSegments, (float)(i + 1) / stoneLatitudeSegments);

            // Pierwszy tr�jk�t (v1, v4, v3)
            // Wierzcho�ek 1
            myStoneVertices[vertexIndex++] = v1.x; myStoneVertices[vertexIndex++] = v1.y; myStoneVertices[vertexIndex++] = v1.z; myStoneVertices[vertexIndex++] = 1.0f;
            myStoneTexCoords[texCoordIndex++] = uv1.x; myStoneTexCoords[texCoordIndex++] = uv1.y;
            // Wierzcho�ek 4
            myStoneVertices[vertexIndex++] = v4.x; myStoneVertices[vertexIndex++] = v4.y; myStoneVertices[vertexIndex++] = v4.z; myStoneVertices[vertexIndex++] = 1.0f;
            myStoneTexCoords[texCoordIndex++] = uv4.x; myStoneTexCoords[texCoordIndex++] = uv4.y;
            // Wierzcho�ek 3
            myStoneVertices[vertexIndex++] = v3.x; myStoneVertices[vertexIndex++] = v3.y; myStoneVertices[vertexIndex++] = v3.z; myStoneVertices[vertexIndex++] = 1.0f;
            myStoneTexCoords[texCoordIndex++] = uv3.x; myStoneTexCoords[texCoordIndex++] = uv3.y;

            // Drugi tr�jk�t (v1, v3, v2)
            // Wierzcho�ek 1
            myStoneVertices[vertexIndex++] = v1.x; myStoneVertices[vertexIndex++] = v1.y; myStoneVertices[vertexIndex++] = v1.z; myStoneVertices[vertexIndex++] = 1.0f;
            myStoneTexCoords[texCoordIndex++] = uv1.x; myStoneTexCoords[texCoordIndex++] = uv1.y;
            // Wierzcho�ek 3
            myStoneVertices[vertexIndex++] = v3.x; myStoneVertices[vertexIndex++] = v3.y; myStoneVertices[vertexIndex++] = v3.z; myStoneVertices[vertexIndex++] = 1.0f;
            myStoneTexCoords[texCoordIndex++] = uv3.x; myStoneTexCoords[texCoordIndex++] = uv3.y;
            // Wierzcho�ek 2
            myStoneVertices[vertexIndex++] = v2.x; myStoneVertices[vertexIndex++] = v2.y; myStoneVertices[vertexIndex++] = v2.z; myStoneVertices[vertexIndex++] = 1.0f;
            myStoneTexCoords[texCoordIndex++] = uv2.x; myStoneTexCoords[texCoordIndex++] = uv2.y;
        }
    }
    // Zaktualizuj zapami�tane wymiary i flag�
    lastStoneLength = stoneLength;
    lastStoneWidth = stoneWidth;
    lastStoneHeight = stoneHeight;
    stoneDataInitialized = true;
    printf("Stone data initialized. Vertex count: %d. Vertex array size: %d floats. TexCoord array size: %d floats.\n",
        myStoneVertexCount, myStoneVertexCount * 4, myStoneVertexCount * 2);
}


// Funkcja do rysowania kamienia
// Zak�ada, �e masz za�adowany odpowiedni shader (spStone) i tekstur� (texStone)
// oraz �e macierze P (Projekcji) i V (Widoku) s� ju� ustawione w shaderze.
void drawStone(ShaderProgram* spStone, GLuint texStone,
    const glm::mat4& parentModelMatrix,
    const glm::vec3& position,
    float scale,
    float localRotationAngleY,
    float stoneLength, float stoneWidth, float stoneHeight) {

    // Inicjalizuj/aktualizuj dane wierzcho�k�w kamienia, je�li to konieczne
    // UWAGA: Wywo�ywanie tej funkcji w ka�dej klatce jest nieefektywne, je�li wymiary kamienia
    // si� nie zmieniaj�. Lepiej wywo�a� j� raz podczas inicjalizacji sceny
    // lub tylko wtedy, gdy wymiary faktycznie ulegn� zmianie.
    // Mechanizm z flag� `stoneDataInitialized` i `lastStone...` cz�ciowo to rozwi�zuje.
    initMyStoneData(stoneLength, stoneWidth, stoneHeight);

    if (!stoneDataInitialized) {
        fprintf(stderr, "Error: Stone data not initialized, cannot draw stone.\n");
        return;
    }

    // 1. Stw�rz lokaln� macierz transformacji dla tej instancji kamienia
    glm::mat4 M_local = glm::mat4(1.0f); // Macierz jednostkowa
    M_local = glm::translate(M_local, position);
    M_local = glm::rotate(M_local, localRotationAngleY, glm::vec3(0.0f, 1.0f, 0.0f)); // Obr�� wok� osi Y
    M_local = glm::scale(M_local, glm::vec3(scale, scale, scale)); // Skaluj jednolicie

    // 2. Po��cz lokaln� macierz z macierz� "rodzica"
    glm::mat4 M_final = parentModelMatrix * M_local;

    // 3. Prze�lij wynikow� macierz Modelu (M_final) do shadera
    glUniformMatrix4fv(spStone->u("M"), 1, false, glm::value_ptr(M_final));

    // 4. Logika rysowania kamienia
    glEnableVertexAttribArray(spStone->a("vertex")); // U�yj nazw atrybut�w ze swojego shadera kamienia
    glVertexAttribPointer(spStone->a("vertex"), 4, GL_FLOAT, false, 0, myStoneVertices);

    glEnableVertexAttribArray(spStone->a("texCoord")); // U�yj nazw atrybut�w ze swojego shadera kamienia
    glVertexAttribPointer(spStone->a("texCoord"), 2, GL_FLOAT, false, 0, myStoneTexCoords);

    glActiveTexture(GL_TEXTURE0); // Aktywuj jednostk� teksturuj�c�
    glBindTexture(GL_TEXTURE_2D, texStone); // Zbinduj tekstur� kamienia
    glUniform1i(spStone->u("tex"), 0); // Ustaw sampler tekstury dla shadera kamienia (zak�adaj�c nazw� "tex")

    // Kamie� jest domy�lnie nieprzezroczysty.
    // Je�li potrzebujesz przezroczysto�ci, musisz w��czy� blendowanie:
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glDepthMask(GL_FALSE); // Je�li rysujesz inne przezroczyste obiekty

    // Rysuj kamie�
    glDrawArrays(GL_TRIANGLES, 0, myStoneVertexCount);

    // Je�li w��cza�e� blendowanie/zmienia�e� glDepthMask:
    // glDisable(GL_BLEND);
    // glDepthMask(GL_TRUE);

    glDisableVertexAttribArray(spStone->a("vertex"));
    glDisableVertexAttribArray(spStone->a("texCoord"));
}
