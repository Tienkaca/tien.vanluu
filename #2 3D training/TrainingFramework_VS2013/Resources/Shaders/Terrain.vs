uniform mat4 u_WVP;
uniform sampler2D u_height;
attribute vec3 a_posL;
attribute vec4 a_color;
attribute vec2 a_uv;
varying vec4 v_color;
varying vec2 v_uv;
void main()
{
vec4 pos = vec4(a_posL,1.0);
//pos.y = (texture2D(u_height,a_uv).b)*10.0;
vec4 posL =  u_WVP*pos;
gl_Position = posL;
vec2 uv = a_uv;
v_uv =uv;
}
   