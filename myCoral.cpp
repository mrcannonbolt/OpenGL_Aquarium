#include "myCoral.h" // Lub "myAquarium.h" je�li tam doda�e� deklaracje
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp> // Dla glm::pi<float>()
#include <vector>                // U�yjemy do przechowania tymczasowych punkt�w
#include "myCoral.h"

// Definicje globalnych tablic
float myCoralSegmentVertices[myCoralSegmentVertexCount * 4];
float myCoralSegmentTexCoords[myCoralSegmentVertexCount * 2];

void initMyCoralSegmentData() {
    int vertexArrayIndex = 0;    // Indeks dla tablicy wierzcho�k�w
    int texCoordArrayIndex = 0;  // Indeks dla tablicy wsp�rz�dnych tekstur
    const float W_COORD = 1.0f;  // Wsp�rz�dna W dla pozycji

    // Punkty o�miok�ta na dolnej i g�rnej podstawie
    std::vector<glm::vec3> bottomBasePoints(coralSegmentSides);
    std::vector<glm::vec3> topBasePoints(coralSegmentSides);
    std::vector<glm::vec2> capTexturePoints(coralSegmentSides); // Wsp�rz�dne tekstur dla wierzcho�k�w na obwodzie podstaw

    // Centralne punkty podstaw dla geometrii i tekstur
    glm::vec3 bottomCenter(0.0f, 0.0f, 0.0f);
    glm::vec3 topCenter(0.0f, coralSegmentHeight, 0.0f);
    glm::vec2 capCenterTexCoord(0.5f, 0.5f);

    // Obliczanie wierzcho�k�w o�miok�ta i ich wsp�rz�dnych tekstur (mapowanie na okr�g)
    for (int i = 0; i < coralSegmentSides; ++i) {
        float angle = (float)i * (2.0f * glm::pi<float>() / (float)coralSegmentSides);
        float x = coralSegmentRadius * glm::cos(angle);
        float z = coralSegmentRadius * glm::sin(angle);

        bottomBasePoints[i] = glm::vec3(x, 0.0f, z);
        topBasePoints[i] = glm::vec3(x, coralSegmentHeight, z);

        // Mapowanie wierzcho�k�w podstawy na okr�g w przestrzeni UV
        capTexturePoints[i] = glm::vec2(0.5f + 0.5f * glm::cos(angle),
            0.5f + 0.5f * glm::sin(angle));
    }

    // 1. Generowanie dolnej podstawy (o�miok�t)
    // Normalna (0, -1, 0) - tr�jk�ty w kolejno�ci CW patrz�c z g�ry
    for (int i = 0; i < coralSegmentSides; ++i) {
        int next_i = (i + 1) % coralSegmentSides;

        // Wierzcho�ki tr�jk�ta
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

    // 2. Generowanie g�rnej podstawy (o�miok�t)
    // Normalna (0, 1, 0) - tr�jk�ty w kolejno�ci CCW patrz�c z g�ry
    for (int i = 0; i < coralSegmentSides; ++i) {
        int next_i = (i + 1) % coralSegmentSides;

        // Wierzcho�ki tr�jk�ta
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

    // 3. Generowanie �cian bocznych (8 prostok�t�w = 16 tr�jk�t�w)
    for (int i = 0; i < coralSegmentSides; ++i) {
        int next_i = (i + 1) % coralSegmentSides;

        glm::vec3 v0_bottom = bottomBasePoints[i];
        glm::vec3 v1_bottom = bottomBasePoints[next_i];
        glm::vec3 v0_top = topBasePoints[i];
        glm::vec3 v1_top = topBasePoints[next_i];

        // Wsp�rz�dne tekstur dla �cian bocznych (rozwini�cie na p�asko)
        // U idzie od 0 do 1 wok� segmentu, V od 0 (d�) do 1 (g�ra)
        float u_start = (float)i / coralSegmentSides;
        float u_end = (float)(i + 1) / coralSegmentSides;
        float v_bottom = 0.0f;
        float v_top = 1.0f;

        // Pierwszy tr�jk�t prostok�ta bocznego
        // (v0_bottom, v1_bottom, v0_top)
        myCoralSegmentVertices[vertexArrayIndex++] = v0_bottom.x; myCoralSegmentVertices[vertexArrayIndex++] = v0_bottom.y; myCoralSegmentVertices[vertexArrayIndex++] = v0_bottom.z; myCoralSegmentVertices[vertexArrayIndex++] = W_COORD;
        myCoralSegmentVertices[vertexArrayIndex++] = v1_bottom.x; myCoralSegmentVertices[vertexArrayIndex++] = v1_bottom.y; myCoralSegmentVertices[vertexArrayIndex++] = v1_bottom.z; myCoralSegmentVertices[vertexArrayIndex++] = W_COORD;
        myCoralSegmentVertices[vertexArrayIndex++] = v0_top.x;    myCoralSegmentVertices[vertexArrayIndex++] = v0_top.y;    myCoralSegmentVertices[vertexArrayIndex++] = v0_top.z;    myCoralSegmentVertices[vertexArrayIndex++] = W_COORD;

        myCoralSegmentTexCoords[texCoordArrayIndex++] = u_start;  myCoralSegmentTexCoords[texCoordArrayIndex++] = v_bottom;
        myCoralSegmentTexCoords[texCoordArrayIndex++] = u_end;    myCoralSegmentTexCoords[texCoordArrayIndex++] = v_bottom;
        myCoralSegmentTexCoords[texCoordArrayIndex++] = u_start;  myCoralSegmentTexCoords[texCoordArrayIndex++] = v_top;

        // Drugi tr�jk�t prostok�ta bocznego
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
    // 1. Stw�rz lokaln� macierz transformacji
    glm::mat4 M_local = glm::mat4(1.0f);
    M_local = glm::translate(M_local, position);
    M_local = glm::rotate(M_local, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f)); // GLM oczekuje radian�w
    M_local = glm::scale(M_local, glm::vec3(scale));

    // 2. Po��cz z macierz� rodzica
    glm::mat4 M_final = parentModelMatrix * M_local;

    // 3. Prze�lij macierz do shadera
    glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M_final));

    // 4. Ustaw atrybuty wierzcho�k�w
    glEnableVertexAttribArray(sp->a("vertex"));
    glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, myCoralSegmentVertices);

    glEnableVertexAttribArray(sp->a("texCoord"));
    glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, myCoralSegmentTexCoords);

    // 5. Ustaw tekstur�
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texCoral);
    glUniform1i(sp->u("tex"), 0);

    // 6. Rysuj
    glDrawArrays(GL_TRIANGLES, 0, myCoralSegmentVertexCount);

    // 7. Wy��cz atrybuty
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
    // ... ewentualnie wi�cej segment�w ...
};

std::vector<glm::mat4> buildDeterministicCoral(
    glm::mat4 initialTransformForFirstSegmentBase
) {
    const std::vector<DeterministicSegmentData>& pattern = myFirstCoralPattern;
    std::vector<glm::mat4> generatedModelMatrices; // Tutaj zapiszemy macierze dla tego koralowca

    // Ta macierz �ledzi transformacj� DO PUNKTU ZACZEPIENIA dla nast�pnego segmentu.
    // Pocz�tkowo jest to transformacja podstawy pierwszego segmentu.
    glm::mat4 currentSegmentAttachmentPointTransform = initialTransformForFirstSegmentBase;

    for (const auto& segmentData : pattern) {
        // 1. Oblicz transformacj� podstawy bie��cego segmentu:
        //    Zaczynamy od punktu zaczepienia (kt�ry jest szczytem poprzedniego segmentu lub pozycj� startow�)
        //    i stosujemy zdefiniowane w patternie przesuni�cie podstawy.
        glm::mat4 baseOffsetMatrix = glm::translate(glm::mat4(1.0f), segmentData.translation_from_parent_top);
        glm::mat4 currentSegmentBaseTransform = currentSegmentAttachmentPointTransform * baseOffsetMatrix;

        // 2. Zastosuj wzgl�dn� orientacj� (obr�t) tego segmentu
        currentSegmentBaseTransform = currentSegmentBaseTransform * glm::mat4_cast(segmentData.orientation_relative_to_parent);

        // 3. Stw�rz macierz skali dla tego segmentu
        //    Skalujemy tylko promie� (X, Z), wysoko�� (Y) pozostaje taka jak w prototypie (coralSegmentHeight)
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f),
            glm::vec3(segmentData.radius_scale_factor,
                1.0f, // Skala Y = 1.0 oznacza, �e wysoko�� jest `coralSegmentHeight`
                segmentData.radius_scale_factor));

        // 4. Finalna macierz Modelu (M) dla tego konkretnego segmentu
        glm::mat4 finalModelMatrixForThisSegment = currentSegmentBaseTransform * scaleMatrix;
        generatedModelMatrices.push_back(finalModelMatrixForThisSegment);

        // 5. Przygotuj punkt zaczepienia dla NAST�PNEGO segmentu.
        //    B�dzie to szczyt bie��cego segmentu, z uwzgl�dnieniem jego orientacji.
        //    Szczyt segmentu znajduje si� `coralSegmentHeight` jednostek wzd�u� jego lokalnej osi Y
        //    od jego podstawy (`currentSegmentBaseTransform`).
        currentSegmentAttachmentPointTransform = currentSegmentBaseTransform * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, coralSegmentHeight, 0.0f));
    }

    return generatedModelMatrices;
}
// T� funkcj� umie�� w pliku .cpp (np. myCoral.cpp), tam gdzie masz inne implementacje.
// Upewnij si�, �e masz odpowiednie include'y na g�rze pliku .cpp,
// takie jak dla GLM, Twojego loadera OpenGL (np. <GL/glew.h>), oraz nag��wka,
// w kt�rym zdefiniowa�e� ShaderProgram (je�li to klasa).


void drawEntireCoral(
    ShaderProgram* sp,                          // Wska�nik do Twojego obiektu programu shadera
    unsigned int coralTextureId,                // ID tekstury koralowca
    const std::vector<glm::mat4>& coralSegmentMatricesToDraw // Wektor macierzy Modelu dla segment�w do narysowania
) {
    // Je�li nie ma nic do narysowania, zako�cz funkcj�.
    if (coralSegmentMatricesToDraw.empty()) {
        return;
    }

    // Aktywacja programu shadera (zak�adam, �e masz metod� use() lub podobn�)
    // sp->use(); // Odkomentuj i dostosuj, je�li jest potrzebne

    // 1. Ustawienie wska�nik�w atrybut�w wierzcho�k�w dla prototypowego segmentu.
    //    U�ywamy danych geometrycznych z `myCoralSegmentVertices` i `myCoralSegmentTexCoords`,
    //    kt�re definiuj� JEDEN o�miok�tny segment (nasz "klocek LEGO").
    glEnableVertexAttribArray(sp->a("vertex")); // U�yj nazwy atrybutu pozycji z Twojego shadera (np. "vertex", "vPosition", "a_position")
    glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, myCoralSegmentVertices);

    glEnableVertexAttribArray(sp->a("texCoord")); // U�yj nazwy atrybutu wsp�rz�dnych UV (np. "texCoord", "vTexCoord", "a_texCoord")
    glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, myCoralSegmentTexCoords);

    // 2. Aktywacja i powi�zanie tekstury
    glActiveTexture(GL_TEXTURE0); // Aktywuj jednostk� teksturuj�c� 0
    glBindTexture(GL_TEXTURE_2D, coralTextureId);
    // Ustaw uniform samplera tekstury w shaderze, aby u�ywa� jednostki teksturuj�cej 0
    glUniform1i(sp->u("tex"), 0); // U�yj nazwy uniformu samplera tekstury z Twojego shadera (np. "tex", "uTextureSampler")

    // 3. Iteracja przez wszystkie macierze Modelu (M) dla segment�w tego koralowca
    for (const glm::mat4& modelMatrix : coralSegmentMatricesToDraw) {
        // Prze�lij bie��c� macierz Modelu (M) segmentu do shadera
        glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(modelMatrix)); // U�yj nazwy uniformu macierzy Modelu (np. "M", "uModelMatrix")

        // Narysuj prototypowy segment z zastosowan� transformacj�
        // `myCoralSegmentVertexCount` to 96 dla o�miok�tnego segmentu
        glDrawArrays(GL_TRIANGLES, 0, myCoralSegmentVertexCount);
    }

    // 4. Wy��czenie tablic atrybut�w wierzcho�k�w po zako�czeniu rysowania
    glDisableVertexAttribArray(sp->a("vertex"));
    glDisableVertexAttribArray(sp->a("texCoord"));

    // Opcjonalnie: odbindowanie tekstury (dla porz�dku, cho� nie zawsze konieczne)
    // glBindTexture(GL_TEXTURE_2D, 0);
}