#ifndef OCTREE_MODELING_MODEL_OCTREE_HPP_
#define OCTREE_MODELING_MODEL_OCTREE_HPP_

#include "model/OctreeNode.hpp"
#include "model/Sphere.hpp"
#include <string>
#include <memory>
#include <glm/vec3.hpp>

namespace octree_modeling {
    namespace model {

        class Octree {

            private:

                glm::vec3 center;
                std::shared_ptr<OctreeNode> root;
                std::size_t depth;
                float radius;

            public:

                Octree (glm::vec3 _center = glm::vec3(0.0f), float _radius = 1.0f);
                Octree (Sphere const& _sphere);
                Octree (Sphere const& _sphere, glm::vec3 _center, float _radius);

                // Returns a string representation of the octree.
                std::string string_octree () const;

                // If the octree is empty, build the octree from a primitive.
                void build_from_primitive (Sphere const& sphere);

        };

    }
}

#endif