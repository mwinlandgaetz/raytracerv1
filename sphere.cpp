#include "sphere.hpp"
#include <stdio.h>
#include <iostream>


Sphere::Sphere(glm::vec3 p, glm::vec3 s)
{
    this->spherePos = p;
    this->sphereSca = s;
}

float Sphere::getIntersection(glm::vec3 pos,glm::vec3 dir)
{
    glm::mat4 rotationMat = glm::mat4(1); //Modulate the rays cast by the camera into the sphere's space to make it easier to calculate.
    glm::mat4 translationMat = glm::translate(glm::mat4(1),spherePos);
    glm::mat4 scalingMat = glm::scale(sphereSca);
    glm::mat4 finalMat = translationMat*rotationMat*scalingMat;
    glm::vec4 pos2 = glm::vec4(pos,1);
    glm::vec4 dir2 = glm::vec4(dir,0);
    pos2 = glm::inverse(finalMat)*pos2;
    dir2 = glm::inverse(finalMat)*dir2;
    float a = glm::pow(dir2.x,2) + glm::pow(dir2.y,2) + glm::pow(dir2.z,2);
    float b = 2*(dir2.x*pos2.x + dir2.y*pos2.y + dir2.z*pos2.z);
    float c = glm::pow(pos2.x,2) + glm::pow(pos2.y,2) + glm::pow(pos2.z,2) - glm::pow(radius,2);
    if(glm::pow(b,2) - 4*a*c < 0){
        return nanf("");
    }
    float q = (-b-glm::sqrt(glm::pow(b,2)-4*a*c))/(2*a); //returns a distance
    if(q > 0)
        return q;
    q = (-b+glm::sqrt(glm::pow(b,2)-4*a*c))/(2*a);
    if(q > 0)
        return q;
    
    return nanf("");
}

float Sphere::getMarch(glm::vec3 pos, glm::vec3 dir){
    glm::mat4 rotationMat = glm::mat4(1);
    glm::mat4 translationMat = glm::translate(glm::mat4(1),spherePos);
    glm::mat4 scalingMat = glm::scale(sphereSca);
    glm::mat4 finalMat = translationMat*rotationMat*scalingMat;
    glm::vec4 pos2 = glm::vec4(pos,1);
    glm::vec4 dir2 = glm::vec4(dir,0);
    pos2 = glm::inverse(finalMat)*pos2;
    dir2 = glm::inverse(finalMat)*dir2;
    
    int maxMarch = 500;
    float marchDist = 0.25;
    float res = 0.01;
    float returnDist {nanf("")};
    glm::vec4 cPos = pos2;
    float a = cPos.x*cPos.x + cPos.y*cPos.y + cPos.z*cPos.z;
    for(int i = 0; i<maxMarch; i++){
        cPos = (marchDist*dir2)+cPos;
        if(cPos.x*cPos.x + cPos.y*cPos.y + cPos.z*cPos.z > a && a>(1.5)) //If the test point is travelling away from the sphere and also further than 1.5x march distance, it is never approaching this sphere again and we can just truncate the loop here.
            break;
        a = cPos.x*cPos.x + cPos.y*cPos.y + cPos.z*cPos.z;
        if (a <= (1.25)){ 
            marchDist = marchDist*0.5;
        }
        
        marchDist = glm::sign(a-1)*glm::abs(marchDist); //make sure marchDist is always pointing towards the skin.
        if(a > (1-res) && a < (1+res)){ //Check if it's on the money.
            returnDist = glm::distance(pos2,cPos); 
            break;
        }
    }
    if(returnDist < 0 || returnDist > 10){
        std::cout << "returnDist is :" << returnDist << ". Error thrown.";
    }
    return returnDist;
}