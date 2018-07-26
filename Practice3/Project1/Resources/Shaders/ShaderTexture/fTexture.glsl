#version 330 core

in vec2 vTexCoords;

out vec4 fColor;

uniform sampler2D texture1;
/*float near = 0.1;
float far = 100;*/

/*float LinearizeDepth(float depth){
  float z = (depth * 2) - 1;
  return (2.f * near * far) / (far + near - z * (far - near));
}*/

void main() {    
  fColor = texture(texture1, vTexCoords);
  //float _depth = LinearizeDepth(gl_FragCoord.z) / far;
  //fColor = vec4(vec3(_depth), 1.0f);
}