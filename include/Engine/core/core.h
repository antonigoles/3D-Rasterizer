#pragma once

#include <vector>
#include <iostream>

namespace Engine::Core
{

    class Color
    {
        public:
            Color();
            Color(int r, int g, int b);   
            int r,g,b;
    };

    class Vector3
    {
        public:
            Vector3();
            Vector3(float x, float y, float z);   

            friend std::ostream& operator<<(std::ostream& os, const Vector3& v3);
            float x,y,z;
    };

    class Polygon
    {
        public:
            Vector3 vertices[3]; 
            Polygon();
            Polygon(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2); 
            void print_polygon();
              
    };

    struct Mesh
    {
        std::vector<Polygon> polygons;
        void print_mesh();
    };

    class EngineObject
    {
        public: 
            Mesh mesh;
            Vector3 position;
            Vector3 scale;
            void set_mesh(Mesh mesh);
    };

    class Camera
    {
        public:
            Vector3 position;
            Vector3 rotation;
            Camera();
    };

    class Scene
    {
        public:
            Scene();
            std::vector<EngineObject*> engine_objects;   
    };
       
}
