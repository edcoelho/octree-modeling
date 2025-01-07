#include "model/Sphere.hpp"
#include <glm/glm.hpp>
#include <algorithm>

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

            glm::vec3 closest_to_the_center;
            for (std::size_t i = 0; i < 3; i++) {

                closest_to_the_center[i] = std::max(min[i], std::min(this->center[i], max[i]));
    
            }

            if (glm::distance(this->center, closest_to_the_center) > this->radius) {

                return WHITE;

            } else if (

                (glm::distance(this->center, glm::vec3(min.x, min.y, min.z)) <= this->radius) &&
                (glm::distance(this->center, glm::vec3(max.x, min.y, min.z)) <= this->radius) &&
                (glm::distance(this->center, glm::vec3(min.x, max.y, min.z)) <= this->radius) &&
                (glm::distance(this->center, glm::vec3(max.x, max.y, min.z)) <= this->radius) &&

                (glm::distance(this->center, glm::vec3(min.x, min.y, max.z)) <= this->radius) &&
                (glm::distance(this->center, glm::vec3(max.x, min.y, max.z)) <= this->radius) &&
                (glm::distance(this->center, glm::vec3(min.x, max.y, max.z)) <= this->radius) &&
                (glm::distance(this->center, glm::vec3(max.x, max.y, max.z)) <= this->radius)

            ) {

                return BLACK;

            } else {
                
                return GRAY;

            }

        }

    }
}