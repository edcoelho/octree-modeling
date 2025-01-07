#include "model/Octree.hpp"
#include <stdexcept>

namespace octree_modeling {
    namespace model {

        Octree::Octree (glm::vec3 _center, float _radius) : center(_center), radius(_radius) {

            this->root = std::make_shared<OctreeNode>(OctreeNode(this->center, this->radius));
            this->root->set_color(WHITE);

        }

        Octree::Octree (Sphere const& _sphere) {

            this->center = _sphere.get_center();
            this->radius = _sphere.get_radius();
            this->root = std::make_shared<OctreeNode>(OctreeNode(this->center, this->radius));
            this->root->set_color(WHITE);
            this->build_from_primitive(_sphere);

        }

        Octree::Octree (Sphere const& _sphere, glm::vec3 _center, float _radius) : center(_center), radius(_radius) {

            this->root = std::make_shared<OctreeNode>(OctreeNode(this->center, this->radius));
            this->root->set_color(WHITE);
            this->build_from_primitive(_sphere);

        }

        std::string Octree::string_octree () const {

            return "Octree DF representation";
            
        }

        void Octree::build_from_primitive (Sphere const& sphere) {

            if (this->root->get_color() == WHITE) {

                this->root->make_tree(sphere, this->depth);

            } else {

                throw std::runtime_error("Error: It is not possible to build an octree which is already builded.");

            }

        }

    }
}