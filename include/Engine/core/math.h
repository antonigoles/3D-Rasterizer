#pragma once

#include <Engine/core/core.h>
#include <cmath>


namespace Engine::Math
{
    float sqrt(float n)
    {
        return std::sqrt(n);
    }

    float v3_dot(Engine::Core::Vector3 a, Engine::Core::Vector3 b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    float v3_mag( Engine::Core::Vector3 vec ) 
    {
        return std::sqrt( vec.x * vec.x + vec.y * vec.y + vec.z * vec.z );
    }

    float v3_angle( Engine::Core::Vector3 vec_a, Engine::Core::Vector3 vec_b ) 
    {
        return std::acos( v3_dot(vec_a, vec_b) / ( v3_mag(vec_a) * v3_mag(vec_b) ) );
    }

    //  Modified from http://www.fullonsoftware.co.uk/snippets/content/Math_-_Calculating_Face_Normals.pdf
    Engine::Core::Vector3 polygon_normal( Engine::Core::Polygon polygon )
    {

        Engine::Core::Vector3 p1 = polygon.vertices[0];
        Engine::Core::Vector3 p2 = polygon.vertices[1];
        Engine::Core::Vector3 p3 = polygon.vertices[2];

        Engine::Core::Vector3 V1= (p2 - p1);
        Engine::Core::Vector3 V2 = (p3 - p1);
        Engine::Core::Vector3 surfaceNormal;
        surfaceNormal.x = (V1.y*V2.z) - (V1.z-V2.y);
        surfaceNormal.y = - ( (V2.z * V1.x) - (V2.x * V1.z) );
        surfaceNormal.z = (V1.x*V2.y) - (V1.y*V2.x);

        // Dont forget to normalize if needed
        return surfaceNormal;
    }

}