#include <iostream>
#include <glm/glm.hpp>
#include <stdio.h>
#include <vector>
#include "pngwrite.hpp"
#include "camera.hpp"

int main(int, char**) {
    std::cout << "Hello, world!\n";
    Camera cam = Camera();
    std::vector<Sphere> mainSphere = std::vector<Sphere>();
    mainSphere.push_back(Sphere(glm::vec3(0,0,-2)));
    mainSphere.push_back(Sphere(glm::vec3(0,0,2), glm::vec3(1, 2, 1)));
    std::vector<std::vector<glm::vec4>> img_data = cam.render(mainSphere);

    
    write_png(img_data,cam.width,cam.height);
    
}
 