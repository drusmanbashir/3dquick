#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif
varying vec2 TexCoord0;

uniform sampler2D gSampler;
uniform sampler2D gPickingSampler;
uniform sampler2D gDepthSampler;

vec4 genDepthTexture(){
        float Depth = texture2D(gDepthSampler, TexCoord0).x;
//        Depth = 1.0 - (1.0-Depth)* 25.0;
        vec4 fin;
        fin = vec4(Depth);
        return fin;

}

void main()
{
//    vec2 mult=(TexCoord0.x/2.0, TexCoord0.y/2.0);

    gl_FragColor = texture2D(gSampler, TexCoord0.xy);
//        gl_FragColor = texture2D(gPickingSampler, TexCoord0.xy);
//    gl_FragColor = genDepthTexture();
//    gl_FragColor =  vec4(0,1,0,1);
}

