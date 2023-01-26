#version 330 core
out vec4 fragColor;

in vec3 color;
in vec2 TextureCord;

uniform sampler2D texture_uniform;
void main(){
	fragColor=texture(texture_uniform,TextureCord);
	}