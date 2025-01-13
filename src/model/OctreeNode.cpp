#include "model/OctreeNode.hpp"
// #include <iostream>
// #define GLM_ENABLE_EXPERIMENTAL
// #include <glm/gtx/string_cast.hpp>

namespace octree_modeling {
    namespace model {

        // OctreeNode::OctreeNode (glm::vec3 center, float radius) : color(WHITE) {

        //     this->max = center + glm::vec3(radius);
        //     this->min = center - glm::vec3(radius);

        // }

        OctreeNodeColor OctreeNode::get_color () const {

            return this->color;

        }

        void OctreeNode::set_color (OctreeNodeColor _color) {

            this->color = _color;

        }

        void OctreeNode::subdivide () {

            for (std::size_t i = 0; i < 8; i++) this->octants[i] = std::make_shared<OctreeNode>();

        }

        void OctreeNode::unify () {

            if (this->octants[0] != nullptr) {

                bool same_color_children = true;
                OctreeNodeColor first_color = this->octants[0]->get_color();

                for (std::size_t i = 1; i < 8; i++) {

                    if (this->octants[i]->get_color() != first_color) {

                        same_color_children = false;
                        break;

                    }

                }

                if (same_color_children && first_color != GRAY) {

                    for (std::size_t i = 0; i < 8; i++) {

                        this->octants[i].reset();

                    }
                    this->color = first_color;

                }

            }

        }

        void OctreeNode::make_subtree (Primitive const& primitive, std::size_t const& depth, float const& width, glm::vec3 const& center) {

            // std::cout << glm::to_string(center + glm::vec3(width/2.0f)) << std::endl;
            // std::cout << glm::to_string(center - glm::vec3(width/2.0f)) << std::endl;
            // std::cout << "DEPTH " << depth << std::endl;

            this->color = primitive.classify(center + glm::vec3(width/2.0f), center - glm::vec3(width/2.0f));

            // std::cout << "COLOR ";

            // if (this->color == WHITE) std::cout << "WHITE";
            // if (this->color == GRAY) std::cout << "GRAY";
            // if (this->color == BLACK) std::cout << "BLACK";

            // std::cout << std::endl;

            if (this->color == GRAY) {

                if (depth == 0){

                    this->color = BLACK;

                } else {

                    this->subdivide();
                    // for (std::size_t i = 0; i < 8; i++) {

                    //     this->octants[i]->make_subtree(primitive, depth, center);

                    // }
                    this->octants[0]->make_subtree(primitive, depth-1, width/2.0f, center + glm::vec3(-width/4.0f, -width/4.0f, width/4.0f));
                    this->octants[1]->make_subtree(primitive, depth-1, width/2.0f, center + glm::vec3(width/4.0f, -width/4.0f, width/4.0f));
                    this->octants[2]->make_subtree(primitive, depth-1, width/2.0f, center + glm::vec3(-width/4.0f, width/4.0f, width/4.0f));
                    this->octants[3]->make_subtree(primitive, depth-1, width/2.0f, center + glm::vec3(width/4.0f, width/4.0f, width/4.0f));

                    this->octants[4]->make_subtree(primitive, depth-1, width/2.0f, center + glm::vec3(-width/4.0f, -width/4.0f, -width/4.0f));
                    this->octants[5]->make_subtree(primitive, depth-1, width/2.0f, center + glm::vec3(width/4.0f, -width/4.0f, -width/4.0f));
                    this->octants[6]->make_subtree(primitive, depth-1, width/2.0f, center + glm::vec3(-width/4.0f, width/4.0f, -width/4.0f));
                    this->octants[7]->make_subtree(primitive, depth-1, width/2.0f, center + glm::vec3(width/4.0f, width/4.0f, -width/4.0f));

                }

            }

            this->unify();

        }

        void OctreeNode::append_df_representation (std::string& df_string) const {

            switch (this->get_color()) {

                case WHITE:
                    df_string += "W";
                    break;

                case BLACK:
                    df_string += "B";
                    break;

                case GRAY:
                    df_string += "(";
                    for (std::size_t i = 0; i < 8; i++) {

                        this->octants[i]->append_df_representation(df_string); 

                    }

            }

        }

        void OctreeNode::append_vertices (std::vector<float>& vertices, float const& width, glm::vec3 const& center) const {

            if (this->color == BLACK) {

                glm::vec3 vertex;

                vertex = center + glm::vec3(-width/2.0f, -width/2.0f, width/2.0f);
                vertices.push_back(vertex.x);
                vertices.push_back(vertex.y);
                vertices.push_back(vertex.z);

                vertex = center + glm::vec3(width/2.0f, -width/2.0f, width/2.0f);
                vertices.push_back(vertex.x);
                vertices.push_back(vertex.y);
                vertices.push_back(vertex.z);

                vertex = center + glm::vec3(width/2.0f, width/2.0f, width/2.0f);
                vertices.push_back(vertex.x);
                vertices.push_back(vertex.y);
                vertices.push_back(vertex.z);

                vertex = center + glm::vec3(-width/2.0f, width/2.0f, width/2.0f);
                vertices.push_back(vertex.x);
                vertices.push_back(vertex.y);
                vertices.push_back(vertex.z);

                vertex = center + glm::vec3(width/2.0f, -width/2.0f, -width/2.0f);
                vertices.push_back(vertex.x);
                vertices.push_back(vertex.y);
                vertices.push_back(vertex.z);

                vertex = center + glm::vec3(-width/2.0f, -width/2.0f, -width/2.0f);
                vertices.push_back(vertex.x);
                vertices.push_back(vertex.y);
                vertices.push_back(vertex.z);

                vertex = center + glm::vec3(-width/2.0f, width/2.0f, -width/2.0f);
                vertices.push_back(vertex.x);
                vertices.push_back(vertex.y);
                vertices.push_back(vertex.z);

                vertex = center + glm::vec3(width/2.0f, width/2.0f, -width/2.0f);
                vertices.push_back(vertex.x);
                vertices.push_back(vertex.y);
                vertices.push_back(vertex.z);

            } else if (this->color == GRAY) {

                this->octants[0]->append_vertices(vertices, width/2.0f, center + glm::vec3(-width/4.0f, -width/4.0f, width/4.0f));
                this->octants[1]->append_vertices(vertices, width/2.0f, center + glm::vec3(width/4.0f, -width/4.0f, width/4.0f));
                this->octants[2]->append_vertices(vertices, width/2.0f, center + glm::vec3(-width/4.0f, width/4.0f, width/4.0f));
                this->octants[3]->append_vertices(vertices, width/2.0f, center + glm::vec3(width/4.0f, width/4.0f, width/4.0f));

                this->octants[4]->append_vertices(vertices, width/2.0f, center + glm::vec3(-width/4.0f, -width/4.0f, -width/4.0f));
                this->octants[5]->append_vertices(vertices, width/2.0f, center + glm::vec3(width/4.0f, -width/4.0f, -width/4.0f));
                this->octants[6]->append_vertices(vertices, width/2.0f, center + glm::vec3(-width/4.0f, width/4.0f, -width/4.0f));
                this->octants[7]->append_vertices(vertices, width/2.0f, center + glm::vec3(width/4.0f, width/4.0f, -width/4.0f));

            }

        }

    }
}