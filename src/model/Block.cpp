#include "model/Block.hpp"

namespace octree_modeling {
    namespace model {

        Block::Block (glm::vec3 _max, glm::vec3 _min) : max(_max), min(_min) {}

        glm::vec3 Block::get_max () const {

            return this->max;

        }
        void Block::set_max (glm::vec3 _max) {

            this->max = _max;

        }

        glm::vec3 Block::get_min () const {

            return this->min;

        }
        void Block::set_min (glm::vec3 _min) {

            this->min = _min;

        }

        OctreeNodeColor Block::classify (glm::vec3 max, glm::vec3 min) const {

            if (
                this->max.x >= max.x && this->min.x <= min.x
                &&
                this->max.y >= max.y && this->min.y <= min.y
                &&
                this->max.z >= max.z && this->min.z <= min.z
            ) return BLACK;

            else if (
                this->max.x > min.x && this->min.x < max.x
                &&
                this->max.y > min.y && this->min.y < max.y
                &&
                this->max.z > min.z && this->min.z < max.z
            ) return GRAY;

            else return WHITE;

        }

    }
}