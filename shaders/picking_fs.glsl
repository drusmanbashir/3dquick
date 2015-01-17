#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;

#endif

uniform int gDrawIndex;

//vec4 CalcColor(){
//    float finalIndex = gDrawIndex+gObjectIndex+1;
//    return vec4(220/(finalIndex),(finalIndex)*10,(220/(finalIndex))+(finalIndex*10),1);
//}


vec4 simpleCalc(){

    vec3 yolo;
    if (gDrawIndex == 0 ){
        yolo = vec3(0,1,0);
    }
    else if (gDrawIndex == 1){
        yolo = vec3(1,0,0);
        }

    else if (gDrawIndex == 2){
        yolo= vec3(1,0,0.4);
        }
   else if (gDrawIndex == 3){
        yolo = vec3(1,0,1);
        }

    else if (gDrawIndex == 4){
        yolo = vec3(1,1,1);
        }
    else if (gDrawIndex == 5){
        yolo= vec3(0,0.3,0.7);
        }
    else if (gDrawIndex == 6 ){
        yolo = vec3(0.7,0,0.3);
        }

   else if (gDrawIndex == 7 ){
        yolo = vec3(0.3,.8,0.3);
        }
    else if (gDrawIndex == 8 ){
        yolo = vec3(.1,.45,0.6);
        }
    else if (gDrawIndex == 9 ){
        yolo = vec3(0.3,.55,0.3);
        }
    else if (gDrawIndex == 10){
        yolo = vec3(0.2,0,0.5);
        }
    else if (gDrawIndex == 11 ){
        yolo = vec3(0,0.5,0.2);
        }
     else if (gDrawIndex == 12 ){
        yolo = vec3(0.7,0,0.3);
        }
    else if (gDrawIndex == 13 ){
        yolo = vec3(0.7,0.5,0.3);
        }
    else if (gDrawIndex == 14 ){
        yolo = vec3(0.17,0.34,0.73);
        }
    else if (gDrawIndex == 15 ){
        yolo = vec3(0.07,.90,0.93);
        }
    else if (gDrawIndex == 16 ){
        yolo = vec3(0.27,.50,0.03);
        }
    else if (gDrawIndex == 17 ){
        yolo = vec3(0.97,0,0.33);
        }
   else if (gDrawIndex == 18 ){
        yolo = vec3(0.97,0.4,0.0);
        }
    else if (gDrawIndex == 19 ){
        yolo = vec3(0.57,0.9,0.23);
        }


    return vec4(yolo,1);
}

void main()                                                                         
{

////   gl_FragColor =vec4(float(gObjectIndex), float(gDrawIndex),float(1),0);
    vec4 gogo = vec4(simpleCalc());
//    if (gObjectIndex == 0 )
        gl_FragColor = gogo;



}
