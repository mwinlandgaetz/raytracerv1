#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>
#include "sphere.hpp"
#include "ray.hpp"

class Camera
{
private:
    /* data */
public:
    glm::vec3 position;
    glm::vec3 fwd;
    glm::vec3 up;
    float fov;
    float aspect;
    float lensDist;
    int width;
    int height;
    
    Camera(/* args */);
    std::vector<std::vector<glm::vec4>> render(std::vector<Sphere> sphere);
};
