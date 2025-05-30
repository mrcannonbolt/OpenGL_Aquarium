#pragma once

#include <vector>         // Dla std::vector
#include <GL/glew.h>      // Dla GLuint, itp.
#include <glm/glm.hpp>    // Dla typ�w GLM takich jak glm::mat4, glm::vec3
#include "shaderprogram.h" // Za�o�enie, �e ShaderProgram jest zdefiniowany w tym pliku nag��wkowym

// --- STA�E I DANE WIERZCHO�K�W DLA GLON�W ---

extern const int ALGAE_BLADE_VERTEX_COUNT;
extern const float algaeBladeVertices[];
extern const float algaeBladeTexCoords[];
extern const float algaeBladeNormals[];

// --- STRUKTURY DANYCH DLA GLON�W ---

// Struktura przechowuj�ca indywidualne, pre-generowane atrybuty dla jednego glonu
struct AlgaeBladeInstanceData {
    glm::vec3 basePositionOffset; // Przesuni�cie (offsetX, 0, offsetZ) wzgl�dem �rodka grupy na dnie
    float rotationY;              // Obr�t wok� osi Y
    glm::vec3 tiltAxis;           // O� pochylenia (znormalizowana)
    float tiltAngle;              // K�t pochylenia
    float heightScale;            // Mno�nik wysoko�ci
};

// Struktura przechowuj�ca wszystkie dane potrzebne do wyrenderowania jednej k�py glon�w
struct AlgaeGroupData {
    glm::vec3 groupCenterOnAquariumFloor; // Wsp�rz�dne (X,Z) �rodka k�py na dnie akwarium
    float waterBottomLevelY;              // Wsp�rz�dna Y dna, na kt�rym rosn� glony
    std::vector<AlgaeBladeInstanceData> blades; // Dane dla poszczeg�lnych "ostrzy" w tej grupie
};


// --- DEKLARACJE FUNKCJI DLA GLON�W ---

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