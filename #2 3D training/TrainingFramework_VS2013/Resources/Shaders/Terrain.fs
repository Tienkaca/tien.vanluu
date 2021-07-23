precision mediump float;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
varying vec2 v_uv;
void main()
{
    vec4 tx0,tx1,tx2,tx3,result;
    tx0 = texture2D(u_texture0,v_uv);
    tx1 = texture2D(u_texture1,v_uv);
    tx2 = texture2D(u_texture2,v_uv);
    tx3 = texture2D(u_texture3,v_uv);
	result = (tx0.r*tx1 + tx0.g*tx2 + tx0.b*tx3)/(tx0.r + tx0.g +tx0.b);
    
    gl_FragColor = result;//vec4(1,0,0,1); 
}
