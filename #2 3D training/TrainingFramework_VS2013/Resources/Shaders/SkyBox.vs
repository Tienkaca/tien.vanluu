uniform mat4 u_WVP;
attribute vec3 a_posL;
varying vec4 v_pos;
void main()
{
vec4 posL =  u_WVP*vec4(a_posL, 1.0);
gl_Position = posL;
v_pos = vec4(a_posL,1.0);
}
   