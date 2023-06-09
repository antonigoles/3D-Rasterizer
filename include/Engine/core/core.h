#pragma once

#include <vector>
#include <iostream>

namespace Engine::Core
{

    class Color
    {
        public:
            Color();
            Color(uint8_t r, uint8_t g, uint8_t b);   
            uint8_t r,g,b;
    };

    class Vector2
    {
        public:
            Vector2();
            Vector2(float x, float y);   

            friend std::ostream& operator<<(std::ostream& os, const Vector2& v2);
            float x,y;

            Vector2 operator+(Vector2 const& obj)
            {
                Vector2 res;
                res.x = this->x + obj.x;
                res.y = this->y + obj.y;
                return res;
            }

            Vector2 operator-(Vector2 const& obj)
            {
                Vector2 res;
                res.x = this->x - obj.x;
                res.y = this->y - obj.y;

                return res;
            }

            Vector2 operator*(Vector2 const& obj)
            {
                Vector2 res;
                res.x = this->x * obj.x;
                res.y = this->y * obj.y;
                return res;
            }

            Vector2 operator*(float const& n)
            {
                Vector2 res;
                res.x = this->x * n;
                res.y = this->y * n;
                return res;
            }

            Vector2 operator/(Vector2 const& obj)
            {
                Vector2 res;
                res.x = this->x / obj.x;
                res.y = this->y / obj.y;
                return res;
            }

            Vector2 operator/(float const& n)
            {
                Vector2 res;
                res.x = this->x / n;
                res.y = this->y / n;
                return res;
            }
    };

    class Vector3
    {
        public:
            Vector3();
            Vector3(float x, float y, float z);   

            friend std::ostream& operator<<(std::ostream& os, const Vector3& v3);
            float x,y,z;

            std::string to_string();

            Vector3 operator+(Vector3 const& obj)
            {
                Vector3 res;
                res.x = this->x + obj.x;
                res.y = this->y + obj.y;
                res.z = this->z + obj.z;
                return res;
            }

            Vector3 operator-(Vector3 const& obj)
            {
                Vector3 res;
                res.x = this->x - obj.x;
                res.y = this->y - obj.y;
                res.z = this->z - obj.z;
                return res;
            }

            Vector3 operator*(Vector3 const& obj)
            {
                Vector3 res;
                res.x = this->x * obj.x;
                res.y = this->y * obj.y;
                res.z = this->z * obj.z;
                return res;
            }

            Vector3 operator*(float const& n)
            {
                Vector3 res;
                res.x = this->x * n;
                res.y = this->y * n;
                res.z = this->z * n;
                return res;
            }

            Vector3 operator/(Vector3 const& obj)
            {
                Vector3 res;
                res.x = this->x / obj.x;
                res.y = this->y / obj.y;
                res.z = this->z / obj.z;
                return res;
            }

            Vector3 operator/(float const& n)
            {
                Vector3 res;
                res.x = this->x / n;
                res.y = this->y / n;
                res.z = this->z / n;
                return res;
            }

    };

    // class Mat3x3
    // {
    //     public:
    //         Mat3x3();
    //         Mat3x3( float values[3][3] );   
    //         float values[3][3];    
    //         float * operator[] (int i) const { return values[i]; };
    // };

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
            Vector3 rotation;
            Vector3 scale;
            EngineObject();
            void set_mesh(Mesh mesh);
            void rotateBy(float x, float y, float z);
    };

    class Camera: public EngineObject
    {
        public:
            Camera();
    };

    class Scene
    {
        public:
            Scene();
            Camera *camera;
            std::vector<EngineObject*> engine_objects;   
    };
}
