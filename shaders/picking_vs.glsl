#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

attribute vec3 Position;

                                                                                    
uniform mat4 gWVP;                                                                  
                                                                                    
void main()                                                                         
{                                                                                   
    gl_Position = gWVP * vec4(Position, 1.0);
}
