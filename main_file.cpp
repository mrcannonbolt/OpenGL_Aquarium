/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "myAquarium.h"
#include "rockAlone.h"
#include "myAlgae.h"
#include "myFish.h"

float speed_x=0;
float speed_y=0;
float aspectRatio=1;
float zoom = -8.0;

ShaderProgram *spTextured;

//Uchwyty dla tekstur
GLuint Glasstex;
GLuint Watertex;
GLuint Rocktex;
GLuint Algaetex;
GLuint Fishtex;

std::vector<AlgaeGroupData> allMyAlgaeGroups; // Kontener na wszystkie kępy glonów


GLuint readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pamięci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);

	//Import do pamięci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods) {
    if (action==GLFW_PRESS) {
        if (key==GLFW_KEY_LEFT) speed_x=-PI/2;
        if (key==GLFW_KEY_RIGHT) speed_x=PI/2;
        if (key==GLFW_KEY_UP) speed_y=PI/2;
        if (key==GLFW_KEY_DOWN) speed_y=-PI/2;
    }
    if (action==GLFW_RELEASE) {
        if (key==GLFW_KEY_LEFT) speed_x=0;
        if (key==GLFW_KEY_RIGHT) speed_x=0;
        if (key==GLFW_KEY_UP) speed_y=0;
        if (key==GLFW_KEY_DOWN) speed_y=0;
    }
}

// Funkcja zwrotna (callback) dla zdarzeń scrolla myszy
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	if (yoffset > 0) {
		if (zoom<-3.0)zoom += 0.2;
	}
	else if (yoffset < 0) {
		zoom += -0.2;
	}
}

void windowResizeCallback(GLFWwindow* window,int width,int height) {
    if (height==0) return;
    aspectRatio=(float)width/(float)height;
    glViewport(0,0,width,height);
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	//************Ładowanie tekstur do obiektów na scenie************
	Glasstex=readTexture("glass.png");
	Watertex = readTexture("water.png");
	Rocktex = readTexture("rock.png");
	Algaetex = readTexture("alga.png");
	Fishtex = readTexture("fish.png"); 
	glfwSetWindowSizeCallback(window,windowResizeCallback);
	glfwSetKeyCallback(window,keyCallback);
	glfwSetScrollCallback(window, scrollCallback);
	spTextured =new ShaderProgram("v_simplest.glsl",NULL,"f_simplest.glsl");
	AlgaeGroupData group1 = initializeAlgaeGroup(
		glm::vec3(0.0f, 0.0f, -0.5f), // Środek kępy na dnie (XZ)
		-0.9,          // Poziom Y dna
		40,                          // Liczba liści w kępie
		0.85f,                       // Promień rozrzucenia
		0.8f, 1.3f                   // Min/max mnożnik wysokości
	);
	AlgaeGroupData group3 = initializeAlgaeGroup(
		glm::vec3(-0.3f, 1.3f, 1.0f), 
		-0.9,         
		20,                     
		0.25f,               
		0.8f, 1.3f        
	);
	AlgaeGroupData group4 = initializeAlgaeGroup(
		glm::vec3(1.4f, 1.2f, -0.6f),
		-0.9,          
		100,                 
		0.25f,                      
		0.8f, 1.3f               
	);
	allMyAlgaeGroups.push_back(group1);
	allMyAlgaeGroups.push_back(group3);
	allMyAlgaeGroups.push_back(group4);
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
	//************Usuwanie tekstur obiektów ze sceny************
	glDeleteTextures(1,&Glasstex);
	glDeleteTextures(1, &Watertex);
	glDeleteTextures(1, &Rocktex);
	glDeleteTextures(1, &Algaetex);
	glDeleteTextures(1, &Fishtex);
    delete spTextured;
}

void drawScene(GLFWwindow* window, float angle_x, float angle_y) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 1. Oblicz macierz Widoku (V)
	glm::mat4 V = glm::lookAt(
		glm::vec3(0.0f, 0.0f, zoom),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

	// 2. Oblicz macierz Rzutowania (P)
	glm::mat4 P = glm::perspective(50.0f * PI / 180.0f, aspectRatio, 0.01f, 50.0f);

	// 3. Aktywuj program cieniujący i prześlij macierze P i V
	spTextured->use();
	glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spTextured->u("V"), 1, false, glm::value_ptr(V));
	glUniform4f(spTextured->u("lp"), 0, 0, 0, 1.12137);
	glUniform1i(spTextured->u("textureMap0"), 0); //drawScene

	// 4. Oblicz bazową macierz Modelu dla sceny (parentModelMatrix)
	// Ta macierz będzie zawierać globalne transformacje, np. obrót całej sceny.
	glm::mat4 M_sceneBase = glm::mat4(1.0f);
	M_sceneBase = glm::rotate(M_sceneBase, angle_y, glm::vec3(1.0f, 0.0f, 0.0f)); // Globalny obrót góra/dół
	M_sceneBase = glm::rotate(M_sceneBase, angle_x, glm::vec3(0.0f, 1.0f, 0.0f)); // Globalny obrót lewo/prawo

	// --- Rysowanie obiektów NIEPRZEZROCZYSTYCH ---
	drawStone(spTextured, Rocktex, M_sceneBase, glm::vec3(0.0f, -0.74f, 1.0f), 2.0f, 1.0f, 0.5f, 0.3f, 0.15f);

	// --- RYBKA 1 (Oryginalna) ---
	float time1 = glfwGetTime() * 0.4f; // Czas dla pierwszej rybki
	float radiusX1 = 0.9f;
	float radiusZ1 = 1.1f;
	// Pozycja rybki 1
	float fishX1 = radiusX1 * cos(time1);
	float fishZ1 = radiusZ1 * sin(2 * time1) / 2.0f;
	float fishY1 = 0.4f * sin(time1 * 0.7f); // Delikatne unoszenie góra-dół
	// Obrót rybki 1
	float dx1 = -radiusX1 * sin(time1);
	float dz1 = radiusZ1 * cos(2 * time1);
	float fishRotation1 = atan2(dz1, dx1);
	// Rysowanie pierwszej rybki
	drawMyFish(spTextured, Fishtex, M_sceneBase, glm::vec3(fishX1, fishY1, fishZ1), 0.5f, fishRotation1);


	// --- RYBKA 2 (Nowa) ---
	// Modyfikujemy czas, aby druga rybka poruszała się inaczej
	// Mniejszy mnożnik = wolniejsza rybka. Dodanie stałej wartości = przesunięcie w fazie.
	float time2 = glfwGetTime() * 0.3f + 1.5f;
	// Zmieniamy promienie, aby miała nieco inną ścieżkę
	float radiusX2 = 1.1f;
	float radiusZ2 = 0.9f;
	// Pozycja rybki 2
	float fishX2 = radiusX2 * cos(time2);
	float fishZ2 = radiusZ2 * sin(2 * time2) / 2.0f;
	float fishY2 = -0.1f + 0.3f * cos(time2 * 0.8f); // Inny wzór na ruch góra-dół i na innej wysokości
	// Obrót rybki 2
	float dx2 = -radiusX2 * sin(time2);
	float dz2 = radiusZ2 * cos(2 * time2);
	float fishRotation2 = atan2(dz2, dx2);
	// Rysowanie drugiej rybki (np. nieco mniejszej)
	drawMyFish(spTextured, Fishtex, M_sceneBase, glm::vec3(fishX2, fishY2, fishZ2), 0.4f, fishRotation2);

	// --- RYBKA 3 (Nowa, dodana w tym samym stylu) ---
	float time3 = glfwGetTime() * 0.5f + 3.0f; // Inne parametry czasu dla zróżnicowania
	float radiusX3 = 0.8f;
	float radiusZ3 = 0.8f;
	// Pozycja rybki 3
	float fishX3 = radiusX3 * sin(time3); // Użycie sin dla odmiany w osi X
	float fishZ3 = radiusZ3 * cos(time3); // Użycie cos dla odmiany w osi Z
	float fishY3 = 0.1f + 0.4f * sin(time3 * 1.1f); // Inny wzór na ruch góra-dół
	// Obrót rybki 3
	float dx3 = radiusX3 * cos(time3);
	float dz3 = -radiusZ3 * sin(time3);
	float fishRotation3 = atan2(dz3, dx3);
	// Rysowanie trzeciej rybki
	drawMyFish(spTextured, Fishtex, M_sceneBase, glm::vec3(fishX3, fishY3, fishZ3), 0.45f, fishRotation3);

	// 6. Rysowanie obiektów z przezroczystością:
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	drawWater(spTextured, Watertex, M_sceneBase, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f);

	for (const AlgaeGroupData& singleGroupData : allMyAlgaeGroups) {
		renderAlgaeGroup(spTextured, Algaetex, M_sceneBase, singleGroupData);
	}

	drawAquarium(spTextured, Glasstex, M_sceneBase, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f);


	// 7. Koniec rysowania obiektów z przezroczystością
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);

	glfwSwapBuffers(window); // Przerzuć tylny bufor na przedni
}


int main(void) {
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}
	window = glfwCreateWindow(1000, 1000, "Akwarium", NULL, NULL);
	if (!window) {

		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}
	initOpenGLProgram(window);
	float angle_x = 0;
	float angle_y = 0;
	// Zapamiętujemy czas ostatniej klatki, aby obliczyć "delta time"
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		// Obliczanie "delta time" - czasu, jaki upłynął od ostatniej klatki
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);
		lastTime = currentTime;
		// Aktualizuj kąty kamery używając deltaTime dla płynnego ruchu
		angle_x += speed_x * deltaTime;
		angle_y += speed_y * deltaTime;
		// Wywołaj procedurę rysującą (nic się tu nie zmienia)
		// Funkcja drawScene sama pobierze aktualny, globalny czas za pomocą glfwGetTime()
		drawScene(window, angle_x, angle_y);
		glfwPollEvents();

	}
	freeOpenGLProgram(window);
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}