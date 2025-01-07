#include "model/Octree.hpp"
#include <stdexcept>

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

    }
}