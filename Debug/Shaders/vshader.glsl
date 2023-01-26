#version 330 core
layout(location=0) in vec3 pos;
layout(location=1) in vec3 ColorVertex;
layout(location=2) in vec2 Texture;
out vec3 color;
out vec2 TextureCord;


//Uniforms
uniform vec3 uMove;
uniform mat3 uMtx;
void main(){
	gl_Position=vec4(uMove+(uMtx*pos),1.0);
	color=ColorVertex;
	TextureCord=Texture;
}