#version 430

layout(location = 0) out vec4 FragColor;

in vec4 velocity;
uniform vec4 Color;

vec3 pallete(vec4 vel)
{
  vec3 a = vec3(-0.042, -0.042, 0.088);
  vec3 b = vec3(-1.630, 2.718, 0.107);
  vec3 c = vec3(0.154, 0.254, 1.045);
  vec3 d = vec3(0.220, 0.547, 1.508);

  float alpha = dot(vel, vel);

  return a + b * cos(6.28 * (c * alpha * 0.00004 + d));
}

void main() 
{
  vec3 col = pallete(velocity);

	FragColor = vec4(col, 1.0);
}
