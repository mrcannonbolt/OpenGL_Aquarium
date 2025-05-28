#include "myCoral.h" // Lub "myAquarium.h" jeœli tam doda³eœ deklaracje
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp> // Dla glm::pi<float>()
#include <vector>                // U¿yjemy do przechowania tymczasowych punktów
#include "myCoral.h"

// Definicje globalnych tablic
float myCoralSegmentVertices[myCoralSegmentVertexCount * 4];
float myCoralSegmentTexCoords[myCoralSegmentVertexCount * 2];

void initMyCoralSegmentData() {
    int vertexArrayIndex = 0;    // Indeks dla tablicy wierzcho³ków
    int texCoordArrayIndex = 0;  // Indeks dla tablicy wspó³rzêdnych tekstur
    const float W_COORD = 1.0f;  // Wspó³rzêdna W dla pozycji

    // Punkty oœmiok¹ta na dolnej i górnej podstawie
    std::vector<glm::vec3> bottomBasePoints(coralSegmentSides);
    std::vector<glm::vec3> topBasePoints(coralSegmentSides);
    std::vector<glm::vec2> capTexturePoints(coralSegmentSides); // Wspó³rzêdne tekstur dla wierzcho³ków na obwodzie podstaw

    // Centralne punkty podstaw dla geometrii i tekstur
    glm::vec3 bottomCenter(0.0f, 0.0f, 0.0f);
    glm::vec3 topCenter(0.0f, coralSegmentHeight, 0.0f);
    glm::vec2 capCenterTexCoord(0.5f, 0.5f);

    // Obliczanie wierzcho³ków oœmiok¹ta i ich wspó³rzêdnych tekstur (mapowanie na okr¹g)
    for (int i = 0; i < coralSegmentSides; ++i) {
        float angle = (float)i * (2.0f * glm::pi<float>() / (float)coralSegmentSides);
        float x = coralSegmentRadius * glm::cos(angle);
        float z = coralSegmentRadius * glm::sin(angle);

        bottomBasePoints[i] = glm::vec3(x, 0.0f, z);
        topBasePoints[i] = glm::vec3(x, coralSegmentHeight, z);

        // Mapowanie wierzcho³ków podstawy na okr¹g w przestrzeni UV
        capTexturePoints[i] = glm::vec2(0.5f + 0.5f * glm::cos(angle),
            0.5f + 0.5f * glm::sin(angle));
    }

    // 1. Generowanie dolnej podstawy (oœmiok¹t)
    // Normalna (0, -1, 0) - trójk¹ty w kolejnoœci CW patrz¹c z góry
    for (int i = 0; i < coralSegmentSides; ++i) {
        int next_i = (i + 1) % coralSegmentSides;

        // Wierzcho³ki trójk¹ta
        glm::vec3 p0 = bottomCenter;
        glm::vec3 p1 = bottomBasePoints[next_i]; // CW
        glm::vec3 p2 = bottomBasePoints[i];

        myCoralSegmentVertices[vertexArrayIndex++] = p0.x; myCoralSegmentVertices[vertexArrayIndex++] = p0.y; myCoralSegmentVertices[vertexArrayIndex++] = p0.z; myCoralSegmentVertices[vertexArrayIndex++] = W_COORD;
        myCoralSegmentVertices[vertexArrayIndex++] = p1.x; myCoralSegmentVertices[vertexArrayIndex++] = p1.y; myCoralSegmentVertices[vertexArrayIndex++] = p1.z; myCoralSegmentVertices[vertexArrayIndex++] = W_COORD;
        myCoralSegmentVertices[vertexArrayIndex++] = p2.x; myCoralSegmentVertices[vertexArrayIndex++] = p2.y; myCoralSegmentVertices[vertexArrayIndex++] = p2.z; myCoralSegmentVertices[vertexArrayIndex++] = W_COORD;

        myCoralSegmentTexCoords[texCoordArrayIndex++] = capCenterTexCoord.x; myCoralSegmentTexCoords[texCoordArrayIndex++] = capCenterTexCoord.y;
        myCoralSegmentTexCoords[texCoordArrayIndex++] = capTexturePoints[next_i].x; myCoralSegmentTexCoords[texCoordArrayIndex++] = capTexturePoints[next_i].y;
        myCoralSegmentTexCoords[texCoordArrayIndex++] = capTexturePoints[i].x; myCoralSegmentTexCoords[texCoordArrayIndex++] = capTexturePoints[i].y;
    }

    // 2. Generowanie górnej podstawy (oœmiok¹t)
    // Normalna (0, 1, 0) - trójk¹ty w kolejnoœci CCW patrz¹c z góry
    for (int i = 0; i < coralSegmentSides; ++i) {
        int next_i = (i + 1) % coralSegmentSides;

        // Wierzcho³ki trójk¹ta
        glm::vec3 p0 = topCenter;
        glm::vec3 p1 = topBasePoints[i]; // CCW
        glm::vec3 p2 = topBasePoints[next_i];

        myCoralSegmentVertices[vertexArrayIndex++] = p0.x; myCoralSegmentVertices[vertexArrayIndex++] = p0.y; myCoralSegmentVertices[vertexArrayIndex++] = p0.z; myCoralSegmentVertices[vertexArrayIndex++] = W_COORD;
        myCoralSegmentVertices[vertexArrayIndex++] = p1.x; myCoralSegmentVertices[vertexArrayIndex++] = p1.y; myCoralSegmentVertices[vertexArrayIndex++] = p1.z; myCoralSegmentVertices[vertexArrayIndex++] = W_COORD;
        myCoralSegmentVertices[vertexArrayIndex++] = p2.x; myCoralSegmentVertices[vertexArrayIndex++] = p2.y; myCoralSegmentVertices[vertexArrayIndex++] = p2.z; myCoralSegmentVertices[vertexArrayIndex++] = W_COORD;

        myCoralSegmentTexCoords[texCoordArrayIndex++] = capCenterTexCoord.x; myCoralSegmentTexCoords[texCoordArrayIndex++] = capCenterTexCoord.y;
        myCoralSegmentTexCoords[texCoordArrayIndex++] = capTexturePoints[i].x; myCoralSegmentTexCoords[texCoordArrayIndex++] = capTexturePoints[i].y;
        myCoralSegmentTexCoords[texCoordArrayIndex++] = capTexturePoints[next_i].x; myCoralSegmentTexCoords[texCoordArrayIndex++] = capTexturePoints[next_i].y;
    }

    // 3. Generowanie œcian bocznych (8 prostok¹tów = 16 trójk¹tów)
    for (int i = 0; i < coralSegmentSides; ++i) {
        int next_i = (i + 1) % coralSegmentSides;

        glm::vec3 v0_bottom = bottomBasePoints[i];
        glm::vec3 v1_bottom = bottomBasePoints[next_i];
        glm::vec3 v0_top = topBasePoints[i];
        glm::vec3 v1_top = topBasePoints[next_i];

        // Wspó³rzêdne tekstur dla œcian bocznych (rozwiniêcie na p³asko)
        // U idzie od 0 do 1 wokó³ segmentu, V od 0 (dó³) do 1 (góra)
        float u_start = (float)i / coralSegmentSides;
        float u_end = (float)(i + 1) / coralSegmentSides;
        float v_bottom = 0.0f;
        float v_top = 1.0f;

        // Pierwszy trójk¹t prostok¹ta bocznego
        // (v0_bottom, v1_bottom, v0_top)
        myCoralSegmentVertices[vertexArrayIndex++] = v0_bottom.x; myCoralSegmentVertices[vertexArrayIndex++] = v0_bottom.y; myCoralSegmentVertices[vertexArrayIndex++] = v0_bottom.z; myCoralSegmentVertices[vertexArrayIndex++] = W_COORD;
        myCoralSegmentVertices[vertexArrayIndex++] = v1_bottom.x; myCoralSegmentVertices[vertexArrayIndex++] = v1_bottom.y; myCoralSegmentVertices[vertexArrayIndex++] = v1_bottom.z; myCoralSegmentVertices[vertexArrayIndex++] = W_COORD;
        myCoralSegmentVertices[vertexArrayIndex++] = v0_top.x;    myCoralSegmentVertices[vertexArrayIndex++] = v0_top.y;    myCoralSegmentVertices[vertexArrayIndex++] = v0_top.z;    myCoralSegmentVertices[vertexArrayIndex++] = W_COORD;

        myCoralSegmentTexCoords[texCoordArrayIndex++] = u_start;  myCoralSegmentTexCoords[texCoordArrayIndex++] = v_bottom;
        myCoralSegmentTexCoords[texCoordArrayIndex++] = u_end;    myCoralSegmentTexCoords[texCoordArrayIndex++] = v_bottom;
        myCoralSegmentTexCoords[texCoordArrayIndex++] = u_start;  myCoralSegmentTexCoords[texCoordArrayIndex++] = v_top;

        // Drugi trójk¹t prostok¹ta bocznego
        // (v1_bottom, v1_top, v0_top)
        myCoralSegmentVertices[vertexArrayIndex++] = v1_bottom.x; myCoralSegmentVertices[vertexArrayIndex++] = v1_bottom.y; myCoralSegmentVertices[vertexArrayIndex++] = v1_bottom.z; myCoralSegmentVertices[vertexArrayIndex++] = W_COORD;
        myCoralSegmentVertices[vertexArrayIndex++] = v1_top.x;    myCoralSegmentVertices[vertexArrayIndex++] = v1_top.y;    myCoralSegmentVertices[vertexArrayIndex++] = v1_top.z;    myCoralSegmentVertices[vertexArrayIndex++] = W_COORD;
        myCoralSegmentVertices[vertexArrayIndex++] = v0_top.x;    myCoralSegmentVertices[vertexArrayIndex++] = v0_top.y;    myCoralSegmentVertices[vertexArrayIndex++] = v0_top.z;    myCoralSegmentVertices[vertexArrayIndex++] = W_COORD;

        myCoralSegmentTexCoords[texCoordArrayIndex++] = u_end;    myCoralSegmentTexCoords[texCoordArrayIndex++] = v_bottom;
        myCoralSegmentTexCoords[texCoordArrayIndex++] = u_end;    myCoralSegmentTexCoords[texCoordArrayIndex++] = v_top;
        myCoralSegmentTexCoords[texCoordArrayIndex++] = u_start;  myCoralSegmentTexCoords[texCoordArrayIndex++] = v_top;
    }
}

#include <glm/gtc/matrix_transform.hpp> // Dla glm::translate, glm::rotate, glm::scale
#include <glm/gtc/type_ptr.hpp>        // Dla glm::value_ptr

void drawCoralSegment(ShaderProgram* sp, GLuint texCoral, const glm::mat4& parentModelMatrix, const glm::vec3& position, float scale, float rotationY) {
    // 1. Stwórz lokaln¹ macierz transformacji
    glm::mat4 M_local = glm::mat4(1.0f);
    M_local = glm::translate(M_local, position);
    M_local = glm::rotate(M_local, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f)); // GLM oczekuje radianów
    M_local = glm::scale(M_local, glm::vec3(scale));

    // 2. Po³¹cz z macierz¹ rodzica
    glm::mat4 M_final = parentModelMatrix * M_local;

    // 3. Przeœlij macierz do shadera
    glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M_final));

    // 4. Ustaw atrybuty wierzcho³ków
    glEnableVertexAttribArray(sp->a("vertex"));
    glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, myCoralSegmentVertices);

    glEnableVertexAttribArray(sp->a("texCoord"));
    glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, myCoralSegmentTexCoords);

    // 5. Ustaw teksturê
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texCoral);
    glUniform1i(sp->u("tex"), 0);

    // 6. Rysuj
    glDrawArrays(GL_TRIANGLES, 0, myCoralSegmentVertexCount);

    // 7. Wy³¹cz atrybuty
    glDisableVertexAttribArray(sp->a("vertex"));
    glDisableVertexAttribArray(sp->a("texCoord"));
}

std::vector<DeterministicSegmentData> myFirstCoralPattern = {
    { glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), 1.0f },
    { glm::vec3(0.0f, 0.0f, 0.0f), glm::angleAxis(glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f)), 0.9f },
    { glm::vec3(0.0f, 0.0f, 0.0f), glm::angleAxis(glm::radians(-10.0f), glm::vec3(0.0f, 0.0f, 1.0f)), 0.8f },
    { glm::vec3(0.05f, -coralSegmentHeight * 0.2f, 0.0f),
      glm::angleAxis(glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::angleAxis(glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
      0.5f
    }
    // ... ewentualnie wiêcej segmentów ...
};

std::vector<glm::mat4> buildDeterministicCoral(
    glm::mat4 initialTransformForFirstSegmentBase
) {
    const std::vector<DeterministicSegmentData>& pattern = myFirstCoralPattern;
    std::vector<glm::mat4> generatedModelMatrices; // Tutaj zapiszemy macierze dla tego koralowca

    // Ta macierz œledzi transformacjê DO PUNKTU ZACZEPIENIA dla nastêpnego segmentu.
    // Pocz¹tkowo jest to transformacja podstawy pierwszego segmentu.
    glm::mat4 currentSegmentAttachmentPointTransform = initialTransformForFirstSegmentBase;

    for (const auto& segmentData : pattern) {
        // 1. Oblicz transformacjê podstawy bie¿¹cego segmentu:
        //    Zaczynamy od punktu zaczepienia (który jest szczytem poprzedniego segmentu lub pozycj¹ startow¹)
        //    i stosujemy zdefiniowane w patternie przesuniêcie podstawy.
        glm::mat4 baseOffsetMatrix = glm::translate(glm::mat4(1.0f), segmentData.translation_from_parent_top);
        glm::mat4 currentSegmentBaseTransform = currentSegmentAttachmentPointTransform * baseOffsetMatrix;

        // 2. Zastosuj wzglêdn¹ orientacjê (obrót) tego segmentu
        currentSegmentBaseTransform = currentSegmentBaseTransform * glm::mat4_cast(segmentData.orientation_relative_to_parent);

        // 3. Stwórz macierz skali dla tego segmentu
        //    Skalujemy tylko promieñ (X, Z), wysokoœæ (Y) pozostaje taka jak w prototypie (coralSegmentHeight)
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f),
            glm::vec3(segmentData.radius_scale_factor,
                1.0f, // Skala Y = 1.0 oznacza, ¿e wysokoœæ jest `coralSegmentHeight`
                segmentData.radius_scale_factor));

        // 4. Finalna macierz Modelu (M) dla tego konkretnego segmentu
        glm::mat4 finalModelMatrixForThisSegment = currentSegmentBaseTransform * scaleMatrix;
        generatedModelMatrices.push_back(finalModelMatrixForThisSegment);

        // 5. Przygotuj punkt zaczepienia dla NASTÊPNEGO segmentu.
        //    Bêdzie to szczyt bie¿¹cego segmentu, z uwzglêdnieniem jego orientacji.
        //    Szczyt segmentu znajduje siê `coralSegmentHeight` jednostek wzd³u¿ jego lokalnej osi Y
        //    od jego podstawy (`currentSegmentBaseTransform`).
        currentSegmentAttachmentPointTransform = currentSegmentBaseTransform * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, coralSegmentHeight, 0.0f));
    }

    return generatedModelMatrices;
}
// Tê funkcjê umieœæ w pliku .cpp (np. myCoral.cpp), tam gdzie masz inne implementacje.
// Upewnij siê, ¿e masz odpowiednie include'y na górze pliku .cpp,
// takie jak dla GLM, Twojego loadera OpenGL (np. <GL/glew.h>), oraz nag³ówka,
// w którym zdefiniowa³eœ ShaderProgram (jeœli to klasa).


void drawEntireCoral(
    ShaderProgram* sp,                          // WskaŸnik do Twojego obiektu programu shadera
    unsigned int coralTextureId,                // ID tekstury koralowca
    const std::vector<glm::mat4>& coralSegmentMatricesToDraw // Wektor macierzy Modelu dla segmentów do narysowania
) {
    // Jeœli nie ma nic do narysowania, zakoñcz funkcjê.
    if (coralSegmentMatricesToDraw.empty()) {
        return;
    }

    // Aktywacja programu shadera (zak³adam, ¿e masz metodê use() lub podobn¹)
    // sp->use(); // Odkomentuj i dostosuj, jeœli jest potrzebne

    // 1. Ustawienie wskaŸników atrybutów wierzcho³ków dla prototypowego segmentu.
    //    U¿ywamy danych geometrycznych z `myCoralSegmentVertices` i `myCoralSegmentTexCoords`,
    //    które definiuj¹ JEDEN oœmiok¹tny segment (nasz "klocek LEGO").
    glEnableVertexAttribArray(sp->a("vertex")); // U¿yj nazwy atrybutu pozycji z Twojego shadera (np. "vertex", "vPosition", "a_position")
    glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, myCoralSegmentVertices);

    glEnableVertexAttribArray(sp->a("texCoord")); // U¿yj nazwy atrybutu wspó³rzêdnych UV (np. "texCoord", "vTexCoord", "a_texCoord")
    glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, myCoralSegmentTexCoords);

    // 2. Aktywacja i powi¹zanie tekstury
    glActiveTexture(GL_TEXTURE0); // Aktywuj jednostkê teksturuj¹c¹ 0
    glBindTexture(GL_TEXTURE_2D, coralTextureId);
    // Ustaw uniform samplera tekstury w shaderze, aby u¿ywa³ jednostki teksturuj¹cej 0
    glUniform1i(sp->u("tex"), 0); // U¿yj nazwy uniformu samplera tekstury z Twojego shadera (np. "tex", "uTextureSampler")

    // 3. Iteracja przez wszystkie macierze Modelu (M) dla segmentów tego koralowca
    for (const glm::mat4& modelMatrix : coralSegmentMatricesToDraw) {
        // Przeœlij bie¿¹c¹ macierz Modelu (M) segmentu do shadera
        glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(modelMatrix)); // U¿yj nazwy uniformu macierzy Modelu (np. "M", "uModelMatrix")

        // Narysuj prototypowy segment z zastosowan¹ transformacj¹
        // `myCoralSegmentVertexCount` to 96 dla oœmiok¹tnego segmentu
        glDrawArrays(GL_TRIANGLES, 0, myCoralSegmentVertexCount);
    }

    // 4. Wy³¹czenie tablic atrybutów wierzcho³ków po zakoñczeniu rysowania
    glDisableVertexAttribArray(sp->a("vertex"));
    glDisableVertexAttribArray(sp->a("texCoord"));

    // Opcjonalnie: odbindowanie tekstury (dla porz¹dku, choæ nie zawsze konieczne)
    // glBindTexture(GL_TEXTURE_2D, 0);
}