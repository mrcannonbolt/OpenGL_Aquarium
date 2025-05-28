#pragma once

#include <vector>         // Dla std::vector
#include <GL/glew.h>      // Dla GLuint, itp.
#include <glm/glm.hpp>    // Dla typów GLM takich jak glm::mat4, glm::vec3
#include "shaderprogram.h" // Za³o¿enie, ¿e ShaderProgram jest zdefiniowany w tym pliku nag³ówkowym

// --- STA£E I DANE WIERZCHO£KÓW DLA GLONÓW ---
// Zak³adamy, ¿e te definicje s¹ w myAlgae.cpp i s¹ tu deklarowane jako extern,
// lub s¹ zdefiniowane bezpoœrednio tutaj, jeœli s¹ proste.
// Dla spójnoœci z poprzednimi krokami, zak³adam extern.

extern const int ALGAE_BLADE_VERTEX_COUNT;
extern const float algaeBladeVertices[];
extern const float algaeBladeTexCoords[];
extern const float algaeBladeNormals[];

// --- STRUKTURY DANYCH DLA GLONÓW ---

// Struktura przechowuj¹ca indywidualne, pre-generowane atrybuty dla jednego "ostrza" glonu
struct AlgaeBladeInstanceData {
    glm::vec3 basePositionOffset; // Przesuniêcie (offsetX, 0, offsetZ) wzglêdem œrodka grupy na dnie
    float rotationY;              // Obrót wokó³ osi Y
    glm::vec3 tiltAxis;           // Oœ pochylenia (znormalizowana)
    float tiltAngle;              // K¹t pochylenia
    float heightScale;            // Mno¿nik wysokoœci
};

// Struktura przechowuj¹ca wszystkie dane potrzebne do wyrenderowania jednej kêpy glonów
struct AlgaeGroupData {
    glm::vec3 groupCenterOnAquariumFloor; // Wspó³rzêdne (X,Z) œrodka kêpy na dnie akwarium
    float waterBottomLevelY;              // Wspó³rzêdna Y dna, na którym rosn¹ glony
    std::vector<AlgaeBladeInstanceData> blades; // Dane dla poszczególnych "ostrzy" w tej grupie
};


// --- DEKLARACJE FUNKCJI DLA GLONÓW ---

/**
 * @brief Inicjalizuje (generuje) dane dla pojedynczej kêpy glonów.
 * Ta funkcja powinna byæ wywo³ana raz podczas konfiguracji sceny, aby stworzyæ dane dla kêpy.
 * * @param groupCenterPosXZ Wspó³rzêdne (X, Z) œrodka kêpy glonów w lokalnej przestrzeni akwarium.
 * @param algaeWaterBottomY Wspó³rzêdna Y okreœlaj¹ca poziom dna, na którym maj¹ rosn¹æ glony.
 * @param numAlgaeInGroup Liczba pojedynczych "ostrzy" glonów do wygenerowania w tej kêpie.
 * @param maxSpreadRadius Maksymalny promieñ rozrzucenia glonów wokó³ groupCenterPosXZ.
 * @param minHeightFactor Minimalny mno¿nik dla bazowej wysokoœci glonu.
 * @param maxHeightFactor Maksymalny mno¿nik dla bazowej wysokoœci glonu.
 * @return AlgaeGroupData Obiekt zawieraj¹cy wszystkie wygenerowane dane dla kêpy glonów.
 */
AlgaeGroupData initializeAlgaeGroup(
    const glm::vec3& groupCenterPosXZ,
    float algaeWaterBottomY,
    int numAlgaeInGroup,
    float maxSpreadRadius,
    float minHeightFactor,
    float maxHeightFactor);

/**
 * @brief Rysuje wczeœniej zainicjalizowan¹ kêpê glonów.
 * Ta funkcja u¿ywa pre-generowanych danych i powinna byæ wywo³ywana w ka¿dej klatce.
 *
 * @param spAlgae WskaŸnik do obiektu ShaderProgram u¿ywanego do renderowania glonów.
 * @param texAlgae ID tekstury OpenGL, która ma byæ u¿yta dla glonów.
 * @param M_aquariumTransform Macierz transformacji modelu dla ca³ego akwarium.
 * @param groupData Dane kêpy glonów (wygenerowane przez initializeAlgaeGroup).
 */
void renderAlgaeGroup(
    ShaderProgram* spAlgae,
    GLuint texAlgae,
    const glm::mat4& M_aquariumTransform,
    const AlgaeGroupData& groupData);

// Funkcja randomFloat, jeœli nie jest zdefiniowana globalnie,
// powinna byæ dostêpna w .cpp (np. jako statyczna funkcja pomocnicza).