#version 400 core

layout (triangles, equal_spacing, ccw) in;

uniform float uRadius;
uniform mat4 uModel;
uniform mat4 uView;

void main() {
    vec3 p0 = gl_in[0].gl_Position.xyz;
    vec3 p1 = gl_in[1].gl_Position.xyz;
    vec3 p2 = gl_in[2].gl_Position.xyz;
    vec3 p3 = gl_in[3].gl_Position.xyz;

    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;
    float w = gl_TessCoord.z;

    gl_Position = uView * uModel *
        vec4(uRadius * normalize(u*p0 + v*p1 + w*p2), 1.f);
}