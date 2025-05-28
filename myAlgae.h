#pragma once

#include <vector>         // Dla std::vector
#include <GL/glew.h>      // Dla GLuint, itp.
#include <glm/glm.hpp>    // Dla typ�w GLM takich jak glm::mat4, glm::vec3
#include "shaderprogram.h" // Za�o�enie, �e ShaderProgram jest zdefiniowany w tym pliku nag��wkowym

// --- STA�E I DANE WIERZCHO�K�W DLA GLON�W ---
// Zak�adamy, �e te definicje s� w myAlgae.cpp i s� tu deklarowane jako extern,
// lub s� zdefiniowane bezpo�rednio tutaj, je�li s� proste.
// Dla sp�jno�ci z poprzednimi krokami, zak�adam extern.

extern const int ALGAE_BLADE_VERTEX_COUNT;
extern const float algaeBladeVertices[];
extern const float algaeBladeTexCoords[];
extern const float algaeBladeNormals[];

// --- STRUKTURY DANYCH DLA GLON�W ---

// Struktura przechowuj�ca indywidualne, pre-generowane atrybuty dla jednego "ostrza" glonu
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

/**
 * @brief Inicjalizuje (generuje) dane dla pojedynczej k�py glon�w.
 * Ta funkcja powinna by� wywo�ana raz podczas konfiguracji sceny, aby stworzy� dane dla k�py.
 * * @param groupCenterPosXZ Wsp�rz�dne (X, Z) �rodka k�py glon�w w lokalnej przestrzeni akwarium.
 * @param algaeWaterBottomY Wsp�rz�dna Y okre�laj�ca poziom dna, na kt�rym maj� rosn�� glony.
 * @param numAlgaeInGroup Liczba pojedynczych "ostrzy" glon�w do wygenerowania w tej k�pie.
 * @param maxSpreadRadius Maksymalny promie� rozrzucenia glon�w wok� groupCenterPosXZ.
 * @param minHeightFactor Minimalny mno�nik dla bazowej wysoko�ci glonu.
 * @param maxHeightFactor Maksymalny mno�nik dla bazowej wysoko�ci glonu.
 * @return AlgaeGroupData Obiekt zawieraj�cy wszystkie wygenerowane dane dla k�py glon�w.
 */
AlgaeGroupData initializeAlgaeGroup(
    const glm::vec3& groupCenterPosXZ,
    float algaeWaterBottomY,
    int numAlgaeInGroup,
    float maxSpreadRadius,
    float minHeightFactor,
    float maxHeightFactor);

/**
 * @brief Rysuje wcze�niej zainicjalizowan� k�p� glon�w.
 * Ta funkcja u�ywa pre-generowanych danych i powinna by� wywo�ywana w ka�dej klatce.
 *
 * @param spAlgae Wska�nik do obiektu ShaderProgram u�ywanego do renderowania glon�w.
 * @param texAlgae ID tekstury OpenGL, kt�ra ma by� u�yta dla glon�w.
 * @param M_aquariumTransform Macierz transformacji modelu dla ca�ego akwarium.
 * @param groupData Dane k�py glon�w (wygenerowane przez initializeAlgaeGroup).
 */
void renderAlgaeGroup(
    ShaderProgram* spAlgae,
    GLuint texAlgae,
    const glm::mat4& M_aquariumTransform,
    const AlgaeGroupData& groupData);

// Funkcja randomFloat, je�li nie jest zdefiniowana globalnie,
// powinna by� dost�pna w .cpp (np. jako statyczna funkcja pomocnicza).