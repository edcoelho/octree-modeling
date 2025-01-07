#include "model/Sphere.hpp"
#include <glm/glm.hpp>

namespace octree_modeling {
    namespace model {

        Sphere::Sphere (glm::vec3 _center, float _radius) : center(_center), radius(_radius) {}

        glm::vec3 Sphere::get_center () const {

            return this->center;

        }
        void Sphere::set_center (glm::vec3 _center) {

            this->center = _center;

        }

        float Sphere::get_radius () const {

            return this->radius;

        }
        void Sphere::set_radius (float _radius) {

            this->radius = _radius;

        }

        OctreeNodeColor Sphere::classify (glm::vec3 max, glm::vec3 min) const {

            if (
                (((this->center.x - this->radius)) < max.x) && (((this->center.x + this->radius)) > min.x)
                &&
                (((this->center.y - this->radius)) < max.y) && (((this->center.y + this->radius)) > min.y)
                &&
                (((this->center.z - this->radius)) < max.z) && (((this->center.z + this->radius)) > min.z)
            ) {

                float cube_width = max.x - min.x;

                if (
                    (glm::distance(this->center, min) <= this->radius)
                    &&
                    (glm::distance(this->center, (min + glm::vec3(cube_width, 0.0f, 0.0f))) <= this->radius)
                    &&
                    (glm::distance(this->center, (min + glm::vec3(0.0f, cube_width, 0.0f))) <= this->radius)
                    &&
                    (glm::distance(this->center, (min + glm::vec3(cube_width, cube_width, 0.0f))) <= this->radius)

                    &&
                    (glm::distance(this->center, (min + glm::vec3(0.0f, 0.0f, cube_width))) <= this->radius)
                    &&
                    (glm::distance(this->center, (min + glm::vec3(cube_width, 0.0f, cube_width))) <= this->radius)
                    &&
                    (glm::distance(this->center, (min + glm::vec3(0.0f, cube_width, cube_width))) <= this->radius)
                    &&
                    (glm::distance(this->center, max) <= this->radius)
                ) {

                    return BLACK;

                } else {

                    return GRAY;

                }

            } else {

                return WHITE;

            }

        }

    }
}