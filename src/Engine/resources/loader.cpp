#include "../core/core.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

namespace Engine 
{

    class MeshFileLoader
    {
        private:
            std::string filepath;
            int current_line_index = 0;
            std::vector<Vector3> vertices;
            Mesh * loaded_mesh;

            void read_triangle(std::string &line) 
            {
                Polygon p = Polygon();
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
                
                std::cout << "[Loader] Loaded polygon ";
                p.print_polygon();
                std::cout << "\n";
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
                            std::cout << "[Loader] parsed number: " << 
                                parsed_number << " to " << stof(parsed_number) << "\n";

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
                
                Vector3 v3 = Vector3( floats[0], floats[1], floats[2] );
                std::cout << "[Loader] Loaded vertex: " << v3 << "\n";
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
                loaded_mesh = new Mesh();
            }

            Mesh *load_mesh() 
            {   
                std::cout << "[Loader] Loading a file \n";
                std::ifstream mesh_file(filepath);
                std::string current_line; 
                while ( std::getline(mesh_file, current_line) ) 
                {
                    try {
                        std::cout << "[Loader] Parsing line " << current_line_index << "\n";
                        parse_next_line(current_line);
                    } catch( std::runtime_error error ) {
                        std::cout << "[Loader] [ERROR] " << error.what() << "\n";
                    }
                }

                return loaded_mesh;
            };
    };

    Mesh * load_mesh_from_native_engine_file(std::string path)
    {
        std::cout << "[Loader] Loading mesh from a file... " << path << "\n";
        MeshFileLoader *loader = new MeshFileLoader( path );
        Mesh *loaded_mesh = loader->load_mesh();

        return loaded_mesh;
    }

}
