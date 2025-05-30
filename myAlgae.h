#pragma once

#include <vector>         // Dla std::vector
#include <GL/glew.h>      // Dla GLuint, itp.
#include <glm/glm.hpp>    // Dla typów GLM takich jak glm::mat4, glm::vec3
#include "shaderprogram.h" // Za³o¿enie, ¿e ShaderProgram jest zdefiniowany w tym pliku nag³ówkowym

// --- STA£E I DANE WIERZCHO£KÓW DLA GLONÓW ---

extern const int ALGAE_BLADE_VERTEX_COUNT;
extern const float algaeBladeVertices[];
extern const float algaeBladeTexCoords[];
extern const float algaeBladeNormals[];

// --- STRUKTURY DANYCH DLA GLONÓW ---

// Struktura przechowuj¹ca indywidualne, pre-generowane atrybuty dla jednego glonu
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

AlgaeGroupData initializeAlgaeGroup(
    const glm::vec3& groupCenterPosXZ,
    float algaeWaterBottomY,
    int numAlgaeInGroup,
    float maxSpreadRadius,
    float minHeightFactor,
    float maxHeightFactor);

void renderAlgaeGroup(
    ShaderProgram* spAlgae,
    GLuint texAlgae,
    const glm::mat4& M_aquariumTransform,
    const AlgaeGroupData& groupData);