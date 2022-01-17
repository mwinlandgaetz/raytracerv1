#include "camera.hpp"


Camera::Camera(/* args */)
{
    position = glm::vec3(-5,0,0);
    fwd = glm::vec3(1,0,0);
    up = glm::vec3(0,1,0);
    fov = 90;
    aspect = 1;
    width = 512;
    height = 512;
    lensDist = 1;
}

std::vector<std::vector<glm::vec4>> Camera::render(std::vector<Sphere> sphere)
{
    std::vector<std::vector<glm::vec4>> img_data = std::vector<std::vector<glm::vec4>>(height);
    glm::vec3 right = glm::normalize(glm::cross(fwd,up));

    glm::vec3 lensLeft = (-right*glm::tan(fov*glm::pi<float>()/360));
    glm::vec3 lensRight = (right*glm::tan(fov*glm::pi<float>()/360));
    glm::vec3 lensTop = (up*glm::tan(fov*glm::pi<float>()/360)*aspect);
    glm::vec3 lensBottom = (-up*glm::tan(fov*glm::pi<float>()/360)*aspect);
    
    
    for(int y = 0; y<height;y++){
        img_data[y] = std::vector<glm::vec4>(width);
        float v = ((float)y)/height;
        for(int x = 0; x<width;x++){
            float u = ((float)x)/width;
            glm::vec3 dir = (fwd + lensLeft*(1-u) + lensRight*u + lensTop*(1-v) + lensBottom*v)*lensDist;
            Ray ray = Ray(position,dir);
            img_data[y][x] = ray.rayCast(sphere);
        }
        
    }
    return img_data;
}