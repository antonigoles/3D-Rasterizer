#include <Engine/core/core.h>
#include <cmath>
#include <Engine/Debug.h>
#include <SDL2/SDL.h>

#define PI 3.142

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

    float v2_mag( Engine::Core::Vector2 vec ) 
    {
        return std::sqrt( vec.x * vec.x + vec.y * vec.y );
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

    void normalize_SDL_Point(int width, int height, SDL_Point &pt) 
    {
        pt.x = std::min( width, std::max( 0, pt.x ));
        pt.y = std::min( height, std::max( 0, pt.y ));
    }

    void mat3x3_v3_multi(Engine::Core::Vector3 * vec, Engine::Core::Mat3x3 mat)
    {
        // Engine::Debug::logrich(std::to_string(mat.values[2][1]));
        vec->x = vec->x * mat.values[0][0] + vec->y * mat.values[0][1] + vec->z * mat.values[0][2];
        vec->y = vec->x * mat.values[1][0] + vec->y * mat.values[1][1] + vec->z * mat.values[1][2];
        vec->z = vec->x * mat.values[2][0] + vec->y * mat.values[2][1] + vec->z * mat.values[2][2];
    }

    void v3_rot(Engine::Core::Vector3 * point, float rx, float ry, float rz, Engine::Core::Vector3 axis)
    {
        typedef Engine::Core::Vector3 v3;
        typedef Engine::Core::Vector2 v2;
        typedef Engine::Core::Mat3x3 mat3x3;
        
        float radX = (PI * rx)/180;
        float radY = (PI * ry)/180;
        float radZ = (PI * rz)/180;

        // Rx(rx)

        float rxmat_values[3][3] =
        {
            {1, 0, 0},
            {0, (float)cosf(radX), (float)sinf(radX)},
            {0, -(float)sinf(radX), (float)cosf(radX) },
        };

        mat3x3 rxmat = mat3x3(
            rxmat_values
        );

        v3 rx_temp_point = *point - axis;
        mat3x3_v3_multi(&rx_temp_point,rxmat);

        point->x = rx_temp_point.x + axis.x;
        point->y = rx_temp_point.y + axis.y;
        point->z = rx_temp_point.z + axis.z;
        
        


        // Ry(ry)

        float rymat_values[3][3] =
        {
            {cosf(radY), 0, sinf(radY)},
            {0, 1, 0},
            {-sinf(radY), 0, cosf(radY) },
        };

        mat3x3 rymat = mat3x3(
            rymat_values
        );

        v3 ry_temp_point = *point - axis;
        mat3x3_v3_multi(&ry_temp_point,rymat);

        point->x = ry_temp_point.x + axis.x;
        point->y = ry_temp_point.y + axis.y;
        point->z = ry_temp_point.z + axis.z;



        // Rz(rz)

        float rzmat_values[3][3] =
        {
            {cosf(radZ), -sinf(radZ), 0},
            {sinf(radZ), cosf(radZ), 0},
            {0, 0, 1 },
        };

        mat3x3 rzmat = mat3x3(
            rzmat_values
        );

        v3 rz_temp_point = *point - axis;
        mat3x3_v3_multi(&rz_temp_point,rzmat);

        point->x = rz_temp_point.x + axis.x;
        point->y = rz_temp_point.y + axis.y;
        point->z = rz_temp_point.z + axis.z;


    }

}