#ifndef OCTREE_MODELING_MODEL_OCTREENODE_HPP_
#define OCTREE_MODELING_MODEL_OCTREENODE_HPP_

#include <memory>
#include <array>
#include <string>
#include <glm/vec3.hpp> 
#include "model/Primitive.hpp"
#include "model/utils.hpp"

namespace octree_modeling {
    namespace model {

        class OctreeNode {

            private:

                OctreeNodeColor color;
                std::array<std::shared_ptr<OctreeNode>, 8> octants;

            public:

                OctreeNodeColor get_color () const;
                void set_color (OctreeNodeColor _color);

                void subdivide ();
                void unify ();
                void make_subtree (Primitive const& primitive, std::size_t const& depth, float const& width, glm::vec3 const& center);
                void append_df_representation (std::string& df_string) const;

        };

    }
}

#endif