#ifndef OCTREE_MODELING_MODEL_OCTREE_HPP_
#define OCTREE_MODELING_MODEL_OCTREE_HPP_

#include "model/OctreeNode.hpp"
#include "model/Primitive.hpp"
#include <string>
#include <memory>
#include <vector>
#include <glm/vec3.hpp>

namespace octree_modeling {
    namespace model {

        class Octree {

            private:

                glm::vec3 center;
                float width;
                std::size_t depth;
                std::shared_ptr<OctreeNode> root;

            public:

                Octree (glm::vec3 _center = glm::vec3(0.0f), float _width = 1.0f, std::size_t _depth = 6);
                Octree (Primitive const& primitive, glm::vec3 _center, float _width, std::size_t _depth = 6);
                Octree (std::shared_ptr<OctreeNode> _root, glm::vec3 _center, float _width, std::size_t _depth = 6);

                glm::vec3 get_center () const;
                void set_center (glm::vec3 _center);

                std::size_t get_depth () const;

                float get_width () const;
                void set_width (float _width);

                std::shared_ptr<OctreeNode> const& get_root () const;

                // Returns a string representation of the octree.
                std::string string_octree () const;

                // If the octree is empty, build the octree from a primitive.
                void build_from_primitive (Primitive const& primitive);

                // Compute vertices of the octree leaves for rendering.
                std::vector<float> leaves_vertices () const;

                // Returns the volume of the octree.
                float volume () const;

                // Returns the union between this octree and another one.
                Octree union_octree (Octree const& octree) const;

        };

    }
}

#endif