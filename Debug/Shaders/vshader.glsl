#version 330 core
layout(location=0) in vec3 pos;
uniform vec3 uMove;
uniform mat3 uMtx;
void main(){
	gl_Position=vec4((uMtx*pos)+uMove,1.0);
}