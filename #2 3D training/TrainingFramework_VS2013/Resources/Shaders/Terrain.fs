precision mediump float;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
varying vec2 v_uv;
varying float v_distance;
void main()
{
    float lerpValue = clamp((v_distance - 0.2)/10.0,0.0,1.0);
    vec4 FogColor = vec4(1.0,1.0,1.0,1.0);

    vec4 tx0,tx1,tx2,tx3,result;
    tx0 = texture2D(u_texture0,v_uv);
    tx1 = texture2D(u_texture1,v_uv*100.0);
    tx2 = texture2D(u_texture2,v_uv*100.0);
    tx3 = texture2D(u_texture3,v_uv*100.0);

	result = (tx0.r*tx3 + tx0.g*tx2 + tx0.b*tx1)/(tx0.r + tx0.g +tx0.b);
    
    gl_FragColor = lerpValue*FogColor +(1.0- lerpValue)*result;//vec4(1,0,0,1); 
}
