#include "rockalone.h"
#include <glm/gtc/matrix_transform.hpp> // Dla glm::translate, glm::rotate, glm::scale
#include <glm/gtc/type_ptr.hpp>       // Dla glm::value_ptr
#include <vector>                     // Dla dynamicznego tworzenia list wierzcho³ków
#include <cmath>                      // Dla sin, cos, M_PI (jeœli zdefiniowane)
#include "constants.h"


// Prawdopodobnie bêdziesz potrzebowaæ równie¿:
// #include "shaderprogram.h" // Jeœli ShaderProgram jest tam zdefiniowany
// #include <GL/glew.h>     // Dla funkcji OpenGL

// --- Sta³e i dane dla obiektu kamienia ---

const int stoneLatitudeSegments = 16;  // Liczba segmentów wzd³u¿ szerokoœci geograficznej (wp³ywa na g³adkoœæ góra-dó³)
const int stoneLongitudeSegments = 24; // Liczba segmentów wzd³u¿ d³ugoœci geograficznej (wp³ywa na g³adkoœæ wokó³ osi Y)

// Ca³kowita liczba wierzcho³ków do narysowania kamienia (ka¿dy prostok¹t siatki to 2 trójk¹ty, ka¿dy trójk¹t to 3 wierzcho³ki)
const int myStoneVertexCount = stoneLatitudeSegments * stoneLongitudeSegments * 6;

// Globalne tablice dla wierzcho³ków i wspó³rzêdnych tekstury kamienia
// UWAGA: To s¹ du¿e tablice globalne. W bardziej z³o¿onych aplikacjach
// lepiej zarz¹dzaæ tymi danymi w klasach lub u¿ywaæ dynamicznej alokacji
// i VBO/VAO per obiekt, tak jak robiliœmy to dla Aquarium.
// Dla spójnoœci z Twoim podejœciem "myAquarium", zostawiam je jako globalne.
float myStoneVertices[myStoneVertexCount * 4];   // X, Y, Z, W
float myStoneTexCoords[myStoneVertexCount * 2]; // U, V

// Flaga informuj¹ca, czy dane kamienia zosta³y ju¿ zainicjalizowane
// aby unikn¹æ niepotrzebnego przeliczania wierzcho³ków w ka¿dej klatce.
bool stoneDataInitialized = false;
float lastStoneLength = -1.0f, lastStoneWidth = -1.0f, lastStoneHeight = -1.0f;


// Funkcja inicjalizuj¹ca/aktualizuj¹ca dane wierzcho³ków i tekstur dla kamienia
void initMyStoneData(float stoneLength, float stoneWidth, float stoneHeight) {
    // Jeœli wymiary siê nie zmieni³y i dane by³y ju¿ inicjalizowane, nie rób nic
    if (stoneDataInitialized &&
        lastStoneLength == stoneLength &&
        lastStoneWidth == stoneWidth &&
        lastStoneHeight == stoneHeight) {
        return;
    }

    printf("Initializing stone data (L:%.2f, W:%.2f, H:%.2f)...\n", stoneLength, stoneWidth, stoneHeight);

    float radiusX = stoneLength / 2.0f;
    float radiusY = stoneHeight / 2.0f; // Wysokoœæ kamienia
    float radiusZ = stoneWidth / 2.0f;

    int vertexIndex = 0;
    int texCoordIndex = 0;

    for (int i = 0; i < stoneLatitudeSegments; ++i) { // Pêtle po segmentach szerokoœci geograficznej (theta)
        float theta1 = (float)i / stoneLatitudeSegments * PI;
        float theta2 = (float)(i + 1) / stoneLatitudeSegments * PI;

        for (int j = 0; j < stoneLongitudeSegments; ++j) { // Pêtle po segmentach d³ugoœci geograficznej (phi)
            float phi1 = (float)j / stoneLongitudeSegments * 2.0f * PI;
            float phi2 = (float)(j + 1) / stoneLongitudeSegments * 2.0f * PI;

            // Wierzcho³ki czworok¹ta na sferze/elipsoidzie
            glm::vec3 v1 = glm::vec3(radiusX * sin(theta1) * cos(phi1), radiusY * cos(theta1), radiusZ * sin(theta1) * sin(phi1));
            glm::vec3 v2 = glm::vec3(radiusX * sin(theta1) * cos(phi2), radiusY * cos(theta1), radiusZ * sin(theta1) * sin(phi2));
            glm::vec3 v3 = glm::vec3(radiusX * sin(theta2) * cos(phi2), radiusY * cos(theta2), radiusZ * sin(theta2) * sin(phi2));
            glm::vec3 v4 = glm::vec3(radiusX * sin(theta2) * cos(phi1), radiusY * cos(theta2), radiusZ * sin(theta2) * sin(phi1));

            // Wspó³rzêdne tekstury dla wierzcho³ków
            glm::vec2 uv1 = glm::vec2((float)j / stoneLongitudeSegments, (float)i / stoneLatitudeSegments);
            glm::vec2 uv2 = glm::vec2((float)(j + 1) / stoneLongitudeSegments, (float)i / stoneLatitudeSegments);
            glm::vec2 uv3 = glm::vec2((float)(j + 1) / stoneLongitudeSegments, (float)(i + 1) / stoneLatitudeSegments);
            glm::vec2 uv4 = glm::vec2((float)j / stoneLongitudeSegments, (float)(i + 1) / stoneLatitudeSegments);

            // Pierwszy trójk¹t (v1, v4, v3)
            // Wierzcho³ek 1
            myStoneVertices[vertexIndex++] = v1.x; myStoneVertices[vertexIndex++] = v1.y; myStoneVertices[vertexIndex++] = v1.z; myStoneVertices[vertexIndex++] = 1.0f;
            myStoneTexCoords[texCoordIndex++] = uv1.x; myStoneTexCoords[texCoordIndex++] = uv1.y;
            // Wierzcho³ek 4
            myStoneVertices[vertexIndex++] = v4.x; myStoneVertices[vertexIndex++] = v4.y; myStoneVertices[vertexIndex++] = v4.z; myStoneVertices[vertexIndex++] = 1.0f;
            myStoneTexCoords[texCoordIndex++] = uv4.x; myStoneTexCoords[texCoordIndex++] = uv4.y;
            // Wierzcho³ek 3
            myStoneVertices[vertexIndex++] = v3.x; myStoneVertices[vertexIndex++] = v3.y; myStoneVertices[vertexIndex++] = v3.z; myStoneVertices[vertexIndex++] = 1.0f;
            myStoneTexCoords[texCoordIndex++] = uv3.x; myStoneTexCoords[texCoordIndex++] = uv3.y;

            // Drugi trójk¹t (v1, v3, v2)
            // Wierzcho³ek 1
            myStoneVertices[vertexIndex++] = v1.x; myStoneVertices[vertexIndex++] = v1.y; myStoneVertices[vertexIndex++] = v1.z; myStoneVertices[vertexIndex++] = 1.0f;
            myStoneTexCoords[texCoordIndex++] = uv1.x; myStoneTexCoords[texCoordIndex++] = uv1.y;
            // Wierzcho³ek 3
            myStoneVertices[vertexIndex++] = v3.x; myStoneVertices[vertexIndex++] = v3.y; myStoneVertices[vertexIndex++] = v3.z; myStoneVertices[vertexIndex++] = 1.0f;
            myStoneTexCoords[texCoordIndex++] = uv3.x; myStoneTexCoords[texCoordIndex++] = uv3.y;
            // Wierzcho³ek 2
            myStoneVertices[vertexIndex++] = v2.x; myStoneVertices[vertexIndex++] = v2.y; myStoneVertices[vertexIndex++] = v2.z; myStoneVertices[vertexIndex++] = 1.0f;
            myStoneTexCoords[texCoordIndex++] = uv2.x; myStoneTexCoords[texCoordIndex++] = uv2.y;
        }
    }
    // Zaktualizuj zapamiêtane wymiary i flagê
    lastStoneLength = stoneLength;
    lastStoneWidth = stoneWidth;
    lastStoneHeight = stoneHeight;
    stoneDataInitialized = true;
    printf("Stone data initialized. Vertex count: %d. Vertex array size: %d floats. TexCoord array size: %d floats.\n",
        myStoneVertexCount, myStoneVertexCount * 4, myStoneVertexCount * 2);
}


// Funkcja do rysowania kamienia
// Zak³ada, ¿e masz za³adowany odpowiedni shader (spStone) i teksturê (texStone)
// oraz ¿e macierze P (Projekcji) i V (Widoku) s¹ ju¿ ustawione w shaderze.
void drawStone(ShaderProgram* spStone, GLuint texStone,
    const glm::mat4& parentModelMatrix,
    const glm::vec3& position,
    float scale,
    float localRotationAngleY,
    float stoneLength, float stoneWidth, float stoneHeight) {

    // Inicjalizuj/aktualizuj dane wierzcho³ków kamienia, jeœli to konieczne
    // UWAGA: Wywo³ywanie tej funkcji w ka¿dej klatce jest nieefektywne, jeœli wymiary kamienia
    // siê nie zmieniaj¹. Lepiej wywo³aæ j¹ raz podczas inicjalizacji sceny
    // lub tylko wtedy, gdy wymiary faktycznie ulegn¹ zmianie.
    // Mechanizm z flag¹ `stoneDataInitialized` i `lastStone...` czêœciowo to rozwi¹zuje.
    initMyStoneData(stoneLength, stoneWidth, stoneHeight);

    if (!stoneDataInitialized) {
        fprintf(stderr, "Error: Stone data not initialized, cannot draw stone.\n");
        return;
    }

    // 1. Stwórz lokaln¹ macierz transformacji dla tej instancji kamienia
    glm::mat4 M_local = glm::mat4(1.0f); // Macierz jednostkowa
    M_local = glm::translate(M_local, position);
    M_local = glm::rotate(M_local, localRotationAngleY, glm::vec3(0.0f, 1.0f, 0.0f)); // Obróæ wokó³ osi Y
    M_local = glm::scale(M_local, glm::vec3(scale, scale, scale)); // Skaluj jednolicie

    // 2. Po³¹cz lokaln¹ macierz z macierz¹ "rodzica"
    glm::mat4 M_final = parentModelMatrix * M_local;

    // 3. Przeœlij wynikow¹ macierz Modelu (M_final) do shadera
    glUniformMatrix4fv(spStone->u("M"), 1, false, glm::value_ptr(M_final));

    // 4. Logika rysowania kamienia
    glEnableVertexAttribArray(spStone->a("vertex")); // U¿yj nazw atrybutów ze swojego shadera kamienia
    glVertexAttribPointer(spStone->a("vertex"), 4, GL_FLOAT, false, 0, myStoneVertices);

    glEnableVertexAttribArray(spStone->a("texCoord")); // U¿yj nazw atrybutów ze swojego shadera kamienia
    glVertexAttribPointer(spStone->a("texCoord"), 2, GL_FLOAT, false, 0, myStoneTexCoords);

    glActiveTexture(GL_TEXTURE0); // Aktywuj jednostkê teksturuj¹c¹
    glBindTexture(GL_TEXTURE_2D, texStone); // Zbinduj teksturê kamienia
    glUniform1i(spStone->u("tex"), 0); // Ustaw sampler tekstury dla shadera kamienia (zak³adaj¹c nazwê "tex")

    // Kamieñ jest domyœlnie nieprzezroczysty.
    // Jeœli potrzebujesz przezroczystoœci, musisz w³¹czyæ blendowanie:
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glDepthMask(GL_FALSE); // Jeœli rysujesz inne przezroczyste obiekty

    // Rysuj kamieñ
    glDrawArrays(GL_TRIANGLES, 0, myStoneVertexCount);

    // Jeœli w³¹cza³eœ blendowanie/zmienia³eœ glDepthMask:
    // glDisable(GL_BLEND);
    // glDepthMask(GL_TRUE);

    glDisableVertexAttribArray(spStone->a("vertex"));
    glDisableVertexAttribArray(spStone->a("texCoord"));
}
