#ifndef OCTREE_MODELING_MODEL_SPHERE_HPP_
#define OCTREE_MODELING_MODEL_SPHERE_HPP_

#include "model/Primitive.hpp"

namespace octree_modeling {
    namespace model {

        class Sphere : public Primitive {

            private:

                glm::vec3 center;
                float radius;

            public:

                Sphere (glm::vec3 _center = glm::vec3(0.0f), float _radius = 1.0f);

                glm::vec3 get_center () const;
                void set_center (glm::vec3 _center);

                float get_radius () const;
                void set_radius (float _radius);

                OctreeNodeColor classify (glm::vec3 max, glm::vec3 min) const override;

        };

    }
}

#endif