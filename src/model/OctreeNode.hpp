#ifndef OCTREE_MODELING_MODEL_OCTREENODE_HPP_
#define OCTREE_MODELING_MODEL_OCTREENODE_HPP_

#include <memory>
#include <array>
#include <string>
#include <glm/vec3.hpp> 
#include <vector>
#include "model/Primitive.hpp"
#include "model/utils.hpp"

namespace octree_modeling {
    namespace model {

        class OctreeNode {

            private:

                OctreeNodeColor color;
                std::array<std::shared_ptr<OctreeNode>, 8> octants;

            public:

                OctreeNode ();
                OctreeNode (OctreeNode const& node);

                OctreeNodeColor get_color () const;
                void set_color (OctreeNodeColor _color);

                std::array<std::shared_ptr<OctreeNode>, 8>& get_octants ();
                std::array<std::shared_ptr<OctreeNode>, 8> const& get_octants () const;

                void subdivide ();
                void unify_children ();
                void make_subtree (Primitive const& primitive, std::size_t const& depth, float const& width, glm::vec3 const& center);
                void make_subtree_from_string (std::string& df_string, const std::size_t depth, std::size_t& global_depth);
                void append_df_representation (std::string& df_string) const;
                void append_vertices (std::vector<float>& vertices, float const& width, glm::vec3 const& center) const;
                float compute_volume (float const& width) const;
                std::shared_ptr<OctreeNode> union_node (OctreeNode const& node) const;

        };

    }
}

#endif