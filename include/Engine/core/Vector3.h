#pragma once

#include <iostream>

namespace Engine
{
    namespace Core 
    {
        class Vector3
        {
            public:
                Vector3() { x = 0.0f, y = 0.0f, z = 0.0f;}
                Vector3(float x, float y, float z) {
                    this->x=x; 
                    this->y=y; 
                    this->z=z;
                };   

                friend std::ostream& operator<<(std::ostream& os, const Vector3& v3)
                {
                    os << "(" << v3.x << ',' << v3.y << ',' << v3.z << ')';
                    return os;
                };

                float x,y,z;
        };
    }
    
}
