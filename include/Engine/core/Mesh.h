#pragma once

#include <vector>
#include <Engine/core/Polygon.h>
#include <iostream>

namespace Engine
{
    struct Mesh
    {
        std::vector<Polygon> polygons;
        void print_mesh() 
        {
            for ( auto pol : polygons ) {
                pol.print_polygon();
                std::cout<<"\n";
            }
        }
    };
}
