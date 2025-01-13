#ifndef OCTREE_MODELING_MODEL_BLOCK_HPP_
#define OCTREE_MODELING_MODEL_BLOCK_HPP_

#include "model/Primitive.hpp"

namespace octree_modeling {
    namespace model {

        class Block : public Primitive {

            private:

                glm::vec3 max, min;

            public:

                Block (glm::vec3 _max = glm::vec3(1.0f), glm::vec3 _min = glm::vec3(-1.0f));

                glm::vec3 get_max () const;
                void set_max (glm::vec3 _max);

                glm::vec3 get_min () const;
                void set_min (glm::vec3 _min);

                OctreeNodeColor classify (glm::vec3 max, glm::vec3 min) const override;

        };

    }
}

#endif