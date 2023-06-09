#include <vector>
#include <iostream>
#include <Engine/core/core.h>
#include <cmath>

namespace Engine::Core
{

    Color::Color() {
        this->r=0;
        this->g=0;
        this->b=0;
    };

    Color::Color(uint8_t r, uint8_t g, uint8_t b) {
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

    // Mat3x3::Mat3x3() 
    // {
    //     for ( int i = 0; i<3; i++ )
    //         for ( int j = 0; j<3; j++ )
    //             values[i][j] = 0;
    // }

    // Mat3x3::Mat3x3( float values[3][3] ) 
    // {
    //     for ( int i = 0; i<3; i++ )
    //         for ( int j = 0; j<3; j++ )
    //             this->values[i][j] = values[i][j];       
    // }

    std::string Vector3::to_string() {
        return "(" + std::to_string(x) + ',' + std::to_string(y) + ',' + std::to_string(z) + ')';
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

    EngineObject::EngineObject() 
    {
        this->rotation = Vector3(); 
        this->position = Vector3(); 
        this->scale = Vector3();
    }

    void EngineObject::set_mesh(Mesh mesh) {
        this->mesh = mesh;
    };

    void EngineObject::rotateBy(float x, float y, float z)
    {
        rotation.x = fmod( rotation.x + x, 360 );
        rotation.y = fmod( rotation.y + y, 360 );
        rotation.z = fmod( rotation.z + z, 360 );
    }

    Camera::Camera() {
        this->rotation = Vector3(); 
        this->position = Vector3(); 
    };




    Scene::Scene() {};
       
}
