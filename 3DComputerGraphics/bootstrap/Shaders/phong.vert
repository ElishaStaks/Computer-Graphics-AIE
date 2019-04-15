// classic Phong Vertex Shader
#version 410

layout( location = 0 ) in vec4 Position;
layout( location = 1 ) in vec4 Normal;
layout( location = 2 ) in vec2 TexCoord;

out vec3 vNormal;
out vec4 vPosition;
out vec2 vTexCoord;

uniform mat4 ProjectionViewModel;

// we need this matirx to transform the normal
uniform mat3 NormalMatrix;

uniform mat4 ModelMatrix;

void main() {
    vPosition = ModelMatrix * Position;
    vNormal = NormalMatrix * Normal.xyz;
	vTexCoord = TexCoord;
	gl_Position = ProjectionViewModel * Position;
}