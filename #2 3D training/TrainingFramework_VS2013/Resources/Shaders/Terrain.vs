uniform mat4 u_WVP;
attribute vec3 a_posL;
attribute vec4 a_color;
attribute vec2 a_uv;
varying vec4 v_color;
varying vec2 v_uv;
void main()
{
vec4 posL =  u_WVP*vec4(a_posL, 1.0);
gl_Position = posL;
v_uv = a_uv;
}
   