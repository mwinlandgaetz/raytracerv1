#include "ray.hpp"

Ray::Ray(glm::vec3 o, glm::vec3 d)
{
    this->origin=o;
    this->dir=d;
}

glm::vec4 Ray::rayCast(std::vector<Sphere> sphere){
    for(int i=0;i<sphere.size();i++)
        {
            //float distToObj = sphere[i].getIntersection(origin,dir);
            float distToObj = sphere[i].getMarch(origin,dir);
            if(!isnan(distToObj)){
                //glm::vec3 nVector = glm::abs(-glm::normalize(sphere[i].spherePos - (dir*distToObj + origin)));
                glm::vec3 nVector = glm::abs(-glm::normalize(sphere[i].spherePos - (dir*distToObj + origin)));

                return glm::vec4(nVector.x,nVector.y,nVector.z,1);
            }
        }
    
    return glm::vec4(1,1,1,1);
}