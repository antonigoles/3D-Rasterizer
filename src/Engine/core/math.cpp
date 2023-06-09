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

    void mat3x3_v3_multi(Engine::Core::Vector3 * vec, float mat[3][3])
    {
        // Engine::Debug::logrich(std::to_string(mat.values[2][1]));
        vec->x = vec->x * mat[0][0] + vec->y * mat[0][1] + vec->z * mat[0][2];
        vec->y = vec->x * mat[1][0] + vec->y * mat[1][1] + vec->z * mat[1][2];
        vec->z = vec->x * mat[2][0] + vec->y * mat[2][1] + vec->z * mat[2][2];
    }

    void mat3x3_mat3x3_multi(float mat1[3][3], float mat2[3][3])
    {

        int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r; mat1[0][0];
    }

    void v3_rot(Engine::Core::Vector3 * point, float rx, float ry, float rz, Engine::Core::Vector3 axis)
    {
        typedef Engine::Core::Vector3 v3;
        typedef Engine::Core::Vector2 v2;
        // typedef Engine::Core::Mat3x3 mat3x3;
        
        float y = (PI * rx)/180;
        float b = (PI * ry)/180;
        float a = (PI * rz)/180;

        // Rz(rz)

        float rmat[3][3] =
        {
            {cosf(a)*cosf(b), cosf(a)*sinf(b)*sinf(y)-sinf(a)*cosf(y), cosf(a)*sinf(b)*cosf(y) + sinf(a)*sinf(y)},
            {sinf(a)*cosf(b), sinf(a)*sinf(b)*sinf(y)+cosf(a)*cosf(y), sinf(a)*sinf(b)*cosf(y) - cosf(a)*sinf(y)},
            {-sinf(b), cosf(b)*sinf(y), cosf(b)*cosf(y) },
        };


        v3 rz_temp_point = *point - axis;
        mat3x3_v3_multi(&rz_temp_point, rmat);

        point->x = rz_temp_point.x + axis.x;
        point->y = rz_temp_point.y + axis.y;
        point->z = rz_temp_point.z + axis.z;

    

    }

}