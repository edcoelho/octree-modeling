#ifndef OCTREE_MODELING_SCENE_SCENE_HPP
#define OCTREE_MODELING_SCENE_SCENE_HPP

#include "scene/Camera.hpp"

namespace octree_modeling {
namespace scene {

class Scene {

    private:

        Camera camera;
        
    public:

        // --- CONSTRUCTORS ---

        Scene(Camera& camera);

        // --- GETTERS AND SETTERS ---

        Camera& get_camera();
        void set_camera(Camera c);

};

}
}

#endif