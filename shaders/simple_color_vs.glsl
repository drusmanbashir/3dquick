#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

attribute vec3 Position;
attribute vec2 TexCoord;
attribute vec3 Normal;

varying vec2 TexCoord0;

varying vec3 Normal0;

uniform mat4 gWVP;                                                                  
                                                                                    
void main()                                                                         
{                                                                                   
    TexCoord0   = TexCoord;
    gl_Position = gWVP * vec4(Position, 1.0);
}
