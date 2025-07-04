#version 330 core

uniform sampler2D textureMap0; //zmienna reprezentuj�ca jednostk� teksturuj�c�

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec2 iTexCoord0;

in vec4 l;
in vec4 n;
in vec4 v;

void main(void) {
    vec4 textureColor = texture(textureMap0, iTexCoord0);

	vec4 ml = normalize(l);
	vec4 mn = normalize(n);
	vec4 mv = normalize(v);
	vec4 mr=reflect(-ml,mn); //Wektor odbity

	float nl = clamp(dot(mn, ml), 0, 1); //Kosinus k�ta pomi�dzy wektorami n i l.
	float rv = pow(clamp(dot(mr, mv), 0, 1), 25); // Kosinus k�ta pomi�dzy wektorami r i v podniesiony do 25 pot�gi

	pixelColor= vec4(nl * textureColor.rgb, textureColor.a) + vec4(rv, rv, rv, 0); //Wyliczenie modelu o�wietlenia (bez ambient);
}