uniform mat4 u_WVP;
attribute vec3 a_posL;
attribute vec2 a_uv;
attribute vec4 a_color;
varying vec2 v_uv;
varying float v_distance;
varying vec4 v_color;
void main()
{
vec4 posL =  u_WVP*vec4(a_posL, 1.0);
gl_Position = posL;
v_uv = a_uv;
v_distance = posL.z;
v_color = a_color;
}
   