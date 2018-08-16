#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 5) out;

in VS_OUT{
    vec3 color;
} gs_in[];

out vec3 gColor;

void build_house(vec4 position) {
    gColor = gs_in[0].color;
    gl_Position = position + vec4(-.2f, -.2f, .0f, .0f);
    EmitVertex();
    gl_Position = position + vec4( .2f, -.2f, .0f, .0f);
    EmitVertex();
    gl_Position = position + vec4(-.2f,  .2f, .0f, .0f);
    EmitVertex();
    gl_Position = position + vec4( .2f,  .2f, .0f, .0f);
    EmitVertex();
    gColor = vec3(1.f, 1.f, 1.f);
    gl_Position = position + vec4( .0f,  .4f, .0f, .0f);
    EmitVertex();
    EndPrimitive();
}

void main() {
    build_house(gl_in[0].gl_Position);
}