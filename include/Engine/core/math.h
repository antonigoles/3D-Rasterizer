#pragma once

#include <Engine/core/core.h>
#include <cmath>
#include <SDL2/SDL.h>

namespace Engine::Math
{
    float sqrt(float n);

    float v3_dot(Engine::Core::Vector3 a, Engine::Core::Vector3 b);

    float v3_mag( Engine::Core::Vector3 vec );

    float v2_mag( Engine::Core::Vector2 vec );

    float v3_angle( Engine::Core::Vector3 vec_a, Engine::Core::Vector3 vec_b );

    //  Modified from http://www.fullonsoftware.co.uk/snippets/content/Math_-_Calculating_Face_Normals.pdf
    Engine::Core::Vector3 polygon_normal( Engine::Core::Polygon polygon );

    void normalize_SDL_Point(int width, int height, SDL_Point &pt);

    void v3_rot(Engine::Core::Vector3 * point, float rx, float ry, float rz, Engine::Core::Vector3 axis);

}