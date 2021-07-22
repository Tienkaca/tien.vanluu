precision mediump float;
uniform samplerCube u_samplerCubeMap;
varying vec4 v_pos;
varying vec2 v_uv;
void main()
{
	gl_FragColor = textureCube(u_samplerCubeMap, v_pos.xyz);
}
