#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Sphere
{
private:
    /* data */
public:
float radius = 1;
glm::vec3 spherePos = glm::vec3(0,0,0);
glm::vec3 sphereSca = glm::vec3(1,1,1);
glm::vec4 sphereRot = glm::vec4(0,0,0,0);
    Sphere(glm::vec3 p, glm::vec3 s = glm::vec3(1,1,1));
    float getIntersection(glm::vec3 pos, glm::vec3 dir);
    float getMarch(glm::vec3 pos,glm::vec3 dir);
};