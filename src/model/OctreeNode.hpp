#ifndef OCTREE_MODELING_MODEL_OCTREENODE_HPP_
#define OCTREE_MODELING_MODEL_OCTREENODE_HPP_

#include <memory>
#include <array>
#include <glm/vec3.hpp> 
#include "model/Sphere.hpp"
#include "model/utils.hpp"

namespace octree_modeling {
    namespace model {

        class OctreeNode {

            private:

                OctreeNodeColor color;
                glm::vec3 max, min;
                std::array<std::shared_ptr<OctreeNode>, 8> octants;

            public:

                OctreeNode (glm::vec3 center = glm::vec3(0.0f), float radius = 1.0f);

                OctreeNodeColor get_color () const;
                void set_color (OctreeNodeColor _color);

                void subdivide ();
                void make_tree (Sphere const& sphere, std::size_t depth);

        };

    }
}

#endif