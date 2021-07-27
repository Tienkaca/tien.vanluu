precision mediump float;
uniform sampler2D u_texture;
varying vec4 v_color;
varying vec2 v_uv;
varying float v_distance;
void main()
{
    float lerpValue = clamp((v_distance - 0.2)/10.0,0.0,1.0);
    vec4 FogColor = vec4(1.0,1.0,1.0,1.0);
    lerpValue = 0.0;
	gl_FragColor = lerpValue*FogColor + (1.0- lerpValue)*texture2D(u_texture, v_uv);
}
