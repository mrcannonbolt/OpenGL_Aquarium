#version 330 core

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 lp;

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec2 texCoord;
in vec4 normal; //wektor normalny wierzcho³ka w przestrzeni modelu

out vec2 TexCoord_FS; // Przekazanie do fragment shadera
out vec4 l;
out vec4 n;
out vec4 v;

void main(void) {
    l = normalize(V * (lp - M * vertex));//znormalizowany wektor do œwiat³a w przestrzeni oka
    n = normalize(V * M * normal);//znormalizowany wektor normalny w przestrzeni oka
    v = normalize(vec4(0, 0, 0, 1) - V * M * vertex); //Wektor do obserwatora w przestrzeni oka
    TexCoord_FS = texCoord;
    gl_Position=P*V*M*vertex;
}
