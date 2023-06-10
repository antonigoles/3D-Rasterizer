#include <Engine/core/core.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <Engine/Debug.h>
#include <filesystem>

namespace Engine::Loader
{
    class MeshFileLoader
    {
        private:
            std::string filepath;
            int current_line_index = 0;
            std::vector<Engine::Core::Vector3> vertices;
            Engine::Core::Mesh * loaded_mesh;

            void read_triangle(std::string &line) 
            {
                Engine::Core::Polygon p = Engine::Core::Polygon();
                std::string parsed_number = "";
                std::vector<int> indexes;
                for ( auto c : line ) {
                    if ( std::isdigit(c) ) 
                        parsed_number += c;
                    else {
                        if ( parsed_number.size() > 0 ) {
                            indexes.push_back( stoi(parsed_number) );
                        }
                        parsed_number = "";
                    }
                    if ( indexes.size() >= 3 ) break;
                }

                if ( parsed_number.size() > 0 ) {
                    indexes.push_back( stoi(parsed_number) );
                }

                if ( indexes.size() < 3 ) 
                    throw std::runtime_error("Error while loading a mesh file: Not enough arguments on line " + current_line_index);
                
                p.vertices[0] = vertices[indexes[0]];
                p.vertices[1] = vertices[indexes[1]];
                p.vertices[2] = vertices[indexes[2]];
                loaded_mesh->polygons.push_back(p);
            }

            void read_vertex(std::string &line) 
            {
                std::string parsed_number = "";
                std::vector<float> floats;
                for ( auto c : line ) {
                    if ( std::isdigit(c) || c == '.' ) 
                        parsed_number += c; 
                    else {
                        if ( parsed_number.size() > 0 ) {
                            floats.push_back( stof(parsed_number) );
                        }
                        parsed_number = "";
                    }
                    if ( floats.size() >= 3 ) break;
                }

                if ( parsed_number.size() > 0 ) {
                    floats.push_back( stof(parsed_number) );
                }

                if ( floats.size() < 3 ) 
                    throw std::runtime_error("Error while loading a mesh file: Not enough arguments on line " + current_line_index);
                
                Engine::Core::Vector3 v3 = Engine::Core::Vector3( floats[0], floats[1], floats[2] );
                vertices.push_back( v3 );
            }

            void parse_next_line(std::string &line) 
            {   
                if (line.size() <= 0) {
                    current_line_index++;
                    return;
                }
                switch ( line[0] ) 
                {
                    case 't':
                        read_triangle(line);
                        break;
                    case 'v':
                        read_vertex(line);
                        break;
                    default: 
                        break;
                }
                current_line_index++;
            }


        public:
            MeshFileLoader(std::string &path) {
                filepath = path;
                current_line_index = 0;
                loaded_mesh = new Engine::Core::Mesh();
            }

            Engine::Core::Mesh *load_mesh() 
            {   
                Engine::Debug::logrich("Loading a 3D file " + filepath);
                std::ifstream mesh_file(filepath);

                bool exist = std::filesystem::exists(filepath);

                if (!exist) {
                    Engine::Debug::errorrich("Could not find " + filepath);
                }

                if (mesh_file.fail()) {
                    Engine::Debug::errorrich("Failed loading a 3D file: " + filepath);
                }
                std::string current_line; 
                while ( std::getline(mesh_file, current_line) ) 
                {
                    try {
                        parse_next_line(current_line);
                    } catch( std::runtime_error error ) {
                        Engine::Debug::logrich("[Loader] [ERROR] " + *(error.what()) );
                    }
                }

                mesh_file.close();
                return loaded_mesh;
            };
    };

    Engine::Core::Mesh * load_mesh_from_native_engine_file(std::string path)
    {
        MeshFileLoader *loader = new MeshFileLoader( path );
        Engine::Core::Mesh *loaded_mesh = loader->load_mesh();

        return loaded_mesh;
    }

    Engine::Core::Mesh * load_mesh_from_obj_file(std::string path)
    {
        // TODO: Implement
    }

}