#include "myAlgae.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <random>

// --- DEFINICJE STA�YCH I DANYCH WIERZCHO�K�W ---
const float ALGAE_BLADE_WIDTH = 0.08f;
const float ALGAE_BLADE_BASE_HEIGHT = 0.7f;
const int ALGAE_BLADE_VERTEX_COUNT = 6;

float algaeBladeVertices[ALGAE_BLADE_VERTEX_COUNT * 4] = {
    -ALGAE_BLADE_WIDTH / 2.0f, 0.0f,                    0.0f, 1.0f,
     ALGAE_BLADE_WIDTH / 2.0f, 0.0f,                    0.0f, 1.0f,
     ALGAE_BLADE_WIDTH / 2.0f, ALGAE_BLADE_BASE_HEIGHT, 0.0f, 1.0f,
    -ALGAE_BLADE_WIDTH / 2.0f, 0.0f,                    0.0f, 1.0f,
     ALGAE_BLADE_WIDTH / 2.0f, ALGAE_BLADE_BASE_HEIGHT, 0.0f, 1.0f,
    -ALGAE_BLADE_WIDTH / 2.0f, ALGAE_BLADE_BASE_HEIGHT, 0.0f, 1.0f
};

float algaeBladeTexCoords[ALGAE_BLADE_VERTEX_COUNT * 2] = {
    0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

float algaeBladeNormals[ALGAE_BLADE_VERTEX_COUNT * 3] = {
    0.0f, 0.0f, 1.0f,   // Wierzcho�ek 1
    0.0f, 0.0f, 1.0f,   // Wierzcho�ek 2
    0.0f, 0.0f, 1.0f,   // Wierzcho�ek 3 (pierwszy tr�jk�t)
    0.0f, 0.0f, 1.0f,   // Wierzcho�ek 4
    0.0f, 0.0f, 1.0f,   // Wierzcho�ek 5
    0.0f, 0.0f, 1.0f    // Wierzcho�ek 6 (drugi tr�jk�t)
};

// Funkcja pomocnicza do generowania liczb losowych
static float randomFloat(float min, float max) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

// --- IMPLEMENTACJE FUNKCJI ---

AlgaeGroupData initializeAlgaeGroup(
    const glm::vec3& groupCenterPosXZ,
    float algaeWaterBottomY,
    int numAlgaeInGroup,
    float maxSpreadRadius,
    float minHeightFactor,
    float maxHeightFactor)
{
    AlgaeGroupData group;
    group.groupCenterOnAquariumFloor = groupCenterPosXZ;
    group.waterBottomLevelY = algaeWaterBottomY;
    group.blades.reserve(numAlgaeInGroup);

    for (int i = 0; i < numAlgaeInGroup; ++i) {
        AlgaeBladeInstanceData blade;

        blade.basePositionOffset.x = randomFloat(-maxSpreadRadius, maxSpreadRadius);
        blade.basePositionOffset.y = 0.0f;
        blade.basePositionOffset.z = randomFloat(-maxSpreadRadius, maxSpreadRadius);

        blade.rotationY = randomFloat(0.0f, 2.0f * glm::pi<float>());

        blade.tiltAngle = randomFloat(-glm::pi<float>() / 18.0f, glm::pi<float>() / 18.0f); // +/- 10 stopni
        blade.tiltAxis = glm::vec3(randomFloat(-1.0f, 1.0f), 0.0f, randomFloat(-1.0f, 1.0f));
        if (glm::length(blade.tiltAxis) > 0.001f) {
            blade.tiltAxis = glm::normalize(blade.tiltAxis);
        }
        else {
            blade.tiltAxis = glm::vec3(1.0f, 0.0f, 0.0f); // Domy�lna o�
        }

        blade.heightScale = randomFloat(minHeightFactor, maxHeightFactor);

        group.blades.push_back(blade);
    }
    return group;
}

void renderAlgaeGroup(
    ShaderProgram* spAlgae,
    GLuint texAlgae,
    const glm::mat4& M_aquariumTransform,
    const AlgaeGroupData& groupData)
{
    glEnableVertexAttribArray(spAlgae->a("vertex"));
    glVertexAttribPointer(spAlgae->a("vertex"), 4, GL_FLOAT, false, 0, algaeBladeVertices);

    glEnableVertexAttribArray(spAlgae->a("texCoord0"));
    glVertexAttribPointer(spAlgae->a("texCoord0"), 2, GL_FLOAT, false, 0, algaeBladeTexCoords);

    glEnableVertexAttribArray(spAlgae->a("normal"));
    glVertexAttribPointer(spAlgae->a("normal"), 3, GL_FLOAT, false, 0, algaeBladeNormals);

    glBindTexture(GL_TEXTURE_2D, texAlgae);


    for (const auto& blade : groupData.blades) {
        glm::mat4 M_singleAlgaeLocal = glm::mat4(1.0f);

        // 1. Pozycja: U�ywamy pre-generowanych offset�w i parametr�w grupy
        glm::vec3 bladeAbsoluteBasePosition = glm::vec3(
            groupData.groupCenterOnAquariumFloor.x + blade.basePositionOffset.x,
            groupData.waterBottomLevelY, // Poziom dna
            groupData.groupCenterOnAquariumFloor.z + blade.basePositionOffset.z
        );
        M_singleAlgaeLocal = glm::translate(M_singleAlgaeLocal, bladeAbsoluteBasePosition);

        // 2. Orientacja: U�ywamy pre-generowanych warto�ci
        M_singleAlgaeLocal = glm::rotate(M_singleAlgaeLocal, blade.rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
        if (blade.tiltAngle != 0.0f) {
            M_singleAlgaeLocal = glm::rotate(M_singleAlgaeLocal, blade.tiltAngle, blade.tiltAxis);
        }

        // 3. Skala: U�ywamy pre-generowanej warto�ci
        M_singleAlgaeLocal = glm::scale(M_singleAlgaeLocal, glm::vec3(1.0f, blade.heightScale, 1.0f));

        // Macierz modelu dla tego konkretnego glonu
        glm::mat4 M_final_singleAlgae = M_aquariumTransform * M_singleAlgaeLocal;
        glUniformMatrix4fv(spAlgae->u("M"), 1, false, glm::value_ptr(M_final_singleAlgae));

        glDrawArrays(GL_TRIANGLES, 0, ALGAE_BLADE_VERTEX_COUNT);
    }

    glDisableVertexAttribArray(spAlgae->a("vertex"));
    glDisableVertexAttribArray(spAlgae->a("texCoord0"));
    glDisableVertexAttribArray(spAlgae->a("normal"));

}