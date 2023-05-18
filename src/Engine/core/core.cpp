#include <vector>
#include <iostream>
#include <Engine/core/core.h>

namespace Engine::Core
{

    Color::Color() {
        this->r=0;
        this->g=0;
        this->b=0;
    };

    Color::Color(int8_t r, int8_t g, int8_t b) {
        this->r=r;
        this->g=g;
        this->b=b;
    };

    Vector2::Vector2() { 
        this->x = 0.0f; 
        this->y = 0.0f;
    };

    Vector2::Vector2(float x, float y) {
        this->x=x; 
        this->y=y; 
    };  

    std::ostream& operator<<(std::ostream& os, const Vector2& v2)
    {
        os << "(" << v2.x << ',' << v2.y << ')';
        return os;
    };

    Vector3::Vector3() { 
        this->x = 0.0f; 
        this->y = 0.0f; 
        this->z = 0.0f;
    }

    Vector3::Vector3(float x, float y, float z) {
        this->x=x; 
        this->y=y; 
        this->z=z;
    };   

    std::ostream& operator<<(std::ostream& os, const Vector3& v3)
    {
        os << "(" << v3.x << ',' << v3.y << ',' << v3.z << ')';
        return os;
    };

    Polygon::Polygon() {};
    Polygon::Polygon(Vector3 vertex0, Vector3 vertex1, Vector3 vertex2) {
        this->vertices[0] = vertex0;
        this->vertices[1] = vertex1; 
        this->vertices[2] = vertex2;
    };
    
    void Polygon::print_polygon() 
    {
        std::cout << vertices[0] << " " << vertices[1] << " " << vertices[2];
    };


    void Mesh::print_mesh()
    {
        for ( auto pol : polygons ) {
            pol.print_polygon();
            std::cout<<"\n";
        }
    };

    void EngineObject::set_mesh(Mesh mesh) {
        this->mesh = mesh;
    };

    Camera::Camera() {
        this->rotation = Vector3(); 
        this->position = Vector3(); 
    };


    Scene::Scene() {};
       
}
