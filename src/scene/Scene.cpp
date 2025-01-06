#include "scene/Scene.hpp"

namespace octree_modeling {
namespace scene {

Camera& Scene::get_camera() {

    return this->camera;

}
void Scene::set_camera(Camera c) {

    this->camera = c;

}

}
}