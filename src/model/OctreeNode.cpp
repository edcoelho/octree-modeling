#include "model/OctreeNode.hpp"

namespace octree_modeling {
    namespace model {

        OctreeNode::OctreeNode (glm::vec3 center, float radius) : color(WHITE) {

            this->max = center + glm::vec3(radius);
            this->min = center - glm::vec3(radius);

        }

        OctreeNodeColor OctreeNode::get_color () const {

            return this->color;

        }

        void OctreeNode::set_color (OctreeNodeColor _color) {

            this->color = color;

        }

        void OctreeNode::subdivide () {

            glm::vec3 center = this->max - glm::vec3((this->max.x - this->min.x)/2.0f);
            float radius = (this->max.x - this->min.x)/4.0f;

            this->octants[0] = std::make_shared<OctreeNode>(center + glm::vec3(-radius, -radius, radius), radius);
            this->octants[1] = std::make_shared<OctreeNode>(center + glm::vec3(radius, -radius, radius), radius);
            this->octants[2] = std::make_shared<OctreeNode>(center + glm::vec3(-radius, radius, radius), radius);
            this->octants[3] = std::make_shared<OctreeNode>(center + glm::vec3(radius, radius, radius), radius);
            this->octants[4] = std::make_shared<OctreeNode>(center + glm::vec3(-radius, -radius, radius), -radius);
            this->octants[5] = std::make_shared<OctreeNode>(center + glm::vec3(radius, -radius, radius), -radius);
            this->octants[6] = std::make_shared<OctreeNode>(center + glm::vec3(-radius, radius, radius), -radius);
            this->octants[7] = std::make_shared<OctreeNode>(center + glm::vec3(radius, radius, radius), -radius);

        }

        void OctreeNode::make_tree (Sphere const& sphere, std::size_t depth) {

            switch (sphere.classify(this->max, this->min)) {

                case WHITE:
                    this->color = WHITE;
                    break;

                case BLACK:
                    this->color = BLACK;
                    break;

                case GRAY:
                    if (depth == 0){

                        this->color = BLACK;

                    } else {

                        this->subdivide();
                        for (std::size_t i = 0; i < 8; i++) {

                            this->octants[i]->make_tree(sphere, depth-1);

                        }

                    }
                    break;

            }

        }

    }
}