#ifndef OCTREE_MODELING_MODEL_PRIMITIVE_HPP_
#define OCTREE_MODELING_MODEL_PRIMITIVE_HPP_

#include <glm/vec3.hpp>
#include "model/utils.hpp"

namespace octree_modeling {
    namespace model {

        class Primitive {

            public:

                // Classifies the node color relative to the primitive.
                virtual OctreeNodeColor classify (glm::vec3 max, glm::vec3 min) const = 0;

        };

    }
}

#endif