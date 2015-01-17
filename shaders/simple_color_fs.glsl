#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif


//uniform sampler2D gSampler;
uniform sampler2D gPickingSampler;
uniform sampler2D gDepthSampler;
uniform sampler2D gSampler;

varying vec2 TexCoord0;

varying vec3 Normal0;

void main()                                                                         
{
    float Depth = texture2D(gDepthSampler, TexCoord0).x;
    Depth = 1.0 - (1.0 - Depth) * 25.0;
//    gl_FragColor = vec4(Depth);
//        gl_FragColor = vec4(1,1,0,1).rgba;
        gl_FragColor = texture2D(gDepthSampler, TexCoord0.xy) ;
    }
