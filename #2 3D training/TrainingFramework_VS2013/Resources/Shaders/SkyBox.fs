precision mediump float;
uniform sampler2D u_texture;
varying vec4 v_color;
varying vec2 v_uv;
varying vec4 v_pos;
uniform samplerCube u_samplerCubeMap;
void main()
{
	gl_FragColor = textureCube( u_samplerCubeMap, v_pos.xyz);
}
