#version 400 core

layout (vertices = 3) out;

uniform float uOuter0, uOuter1, uOuter2, uInner;
uniform float uRadius;

void main() {
    gl_out[gl_InvocationID].gl_Position =
        gl_in[gl_InvocationID].gl_Position;
    gl_TessLevelOuter[0] = uRadius * uOuter0;
    gl_TessLevelOuter[1] = uRadius * uOuter1;
    gl_TessLevelOuter[2] = uRadius * uOuter2;
    gl_TessLevelInner[0] = uRadius * uInner;
}