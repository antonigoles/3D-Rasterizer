#pragma once

#include <Engine/core/Vector3.h>
#include <iostream>

namespace Engine::Core
{
    class Polygon
    {
        public:
            Vector3 vertices[3]; 
            Polygon() {};
            Polygon(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2) {
                this->vertices[0] = vertex0;
                this->vertices[1] = vertex1; 
                this->vertices[2] = vertex2;
            };
            
            void print_polygon() 
            {
                std::cout << vertices[0] << " " << vertices[1] << " " << vertices[2];
            };
              
    };
}