#include "model/Octree.hpp"
#include <stdexcept>
#include <cmath>

namespace octree_modeling {
    namespace model {

        Octree::Octree (glm::vec3 _center, float _width, std::size_t _depth) : center(_center), width(_width), depth(_depth) {

            this->root = std::make_shared<OctreeNode>();
            this->root->set_color(WHITE);

        }

        Octree::Octree (Primitive const& primitive, glm::vec3 _center, float _width, std::size_t _depth) : center(_center), width(_width), depth(_depth) {

            this->root = std::make_shared<OctreeNode>();
            this->root->set_color(WHITE);
            this->build_from_primitive(primitive);

        }

        Octree::Octree (std::shared_ptr<OctreeNode> _root, glm::vec3 _center, float _width, std::size_t _depth) : center(_center), width(_width), depth(_depth) {

            this->root = _root;

        }

        glm::vec3 Octree::get_center () const {

            return this->center;

        }
        void Octree::set_center (glm::vec3 _center) {

            this->center = _center;

        }

        std::size_t Octree::get_depth () const {

            return this->depth;

        }

        float Octree::get_width () const {

            return this->width;

        }
        void Octree::set_width (float _width) {

            this->width = _width;

        }

        std::shared_ptr<OctreeNode> const& Octree::get_root () const {

            return this->root;

        }

        std::string Octree::string_octree () const {

            std::string linear_octree = "";

            this->root->append_df_representation(linear_octree);

            return linear_octree;
            
        }

        void Octree::build_from_primitive (Primitive const& primitive) {

            if (this->root->get_color() == WHITE) {

                this->root->make_subtree(primitive, this->depth, this->width, this->center);

            } else {

                throw std::runtime_error("Error: It is not possible to build an octree which is already builded.");

            }

        }

        std::vector<float> Octree::leaves_vertices () const {

            std::vector<float> vertices;
            if (this->root->get_color() != WHITE) {

                vertices.reserve(8 + std::min(std::pow(8, this->depth), std::pow(10,6)));

                // Adding octree root vertices.
                glm::vec3 vertex;

                vertex = this->center + glm::vec3(-this->width/2.0f, -this->width/2.0f, this->width/2.0f);
                vertices.push_back(vertex.x);
                vertices.push_back(vertex.y);
                vertices.push_back(vertex.z);

                vertex = this->center + glm::vec3(this->width/2.0f, -this->width/2.0f, this->width/2.0f);
                vertices.push_back(vertex.x);
                vertices.push_back(vertex.y);
                vertices.push_back(vertex.z);

                vertex = this->center + glm::vec3(this->width/2.0f, this->width/2.0f, this->width/2.0f);
                vertices.push_back(vertex.x);
                vertices.push_back(vertex.y);
                vertices.push_back(vertex.z);

                vertex = this->center + glm::vec3(-this->width/2.0f, this->width/2.0f, this->width/2.0f);
                vertices.push_back(vertex.x);
                vertices.push_back(vertex.y);
                vertices.push_back(vertex.z);

                vertex = this->center + glm::vec3(this->width/2.0f, -this->width/2.0f, -this->width/2.0f);
                vertices.push_back(vertex.x);
                vertices.push_back(vertex.y);
                vertices.push_back(vertex.z);

                vertex = this->center + glm::vec3(-this->width/2.0f, -this->width/2.0f, -this->width/2.0f);
                vertices.push_back(vertex.x);
                vertices.push_back(vertex.y);
                vertices.push_back(vertex.z);

                vertex = this->center + glm::vec3(-this->width/2.0f, this->width/2.0f, -this->width/2.0f);
                vertices.push_back(vertex.x);
                vertices.push_back(vertex.y);
                vertices.push_back(vertex.z);

                vertex = this->center + glm::vec3(this->width/2.0f, this->width/2.0f, -this->width/2.0f);
                vertices.push_back(vertex.x);
                vertices.push_back(vertex.y);
                vertices.push_back(vertex.z);

                // Adding octree leaves vertices.
                this->root->append_vertices(vertices, this->width, this->center);
                vertices.shrink_to_fit();

            }

            return vertices;

        }

        float Octree::volume () const {

            return this->root->compute_volume(this->width);

        }

        Octree Octree::union_octree (Octree const& octree) const {

            std::shared_ptr<OctreeNode> new_root = this->root->union_node(*(octree.get_root()));
            return Octree(new_root, this->center, this->depth);

        }

    }
}