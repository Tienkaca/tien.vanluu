precision mediump float;
uniform float u_time;
uniform sampler2D u_Displacement;
uniform sampler2D u_fireText;
uniform sampler2D u_maskText;
varying vec2 v_uv;
varying float v_distance;
varying vec4 v_color;
void main()
{
    float lerpValue = clamp((v_distance - 0.2)/10.0,0.0,1.0);
    vec4 FogColor = vec4(1.0,1.0,1.0,1.0);

    float dMax = 5.0;
    vec2 disp = texture2D(u_Displacement, vec2(v_uv.x, v_uv.y + u_time)).rg;
    vec2 offset = (2.0 * disp - 1.0) * dMax;
    vec2 Tex_coords_displaced = v_uv + offset;
    vec4 fire_color = texture2D (u_fireText, Tex_coords_displaced);
    //gl_FragColor = fire_color;
    gl_FragColor =  texture2D(u_fireText,v_uv);
}
