#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <math.h>
#include "sphere.hpp"

class Ray
{
private:
    /* data */
public:
    glm::vec3 origin;
    glm::vec3 dir;
    Ray(glm::vec3 o,glm::vec3 d);
    glm::vec4 rayCast(std::vector<Sphere> sphere);
    //glm::vec4 rayMarch(std::vector<Sphere> sphere);
};

