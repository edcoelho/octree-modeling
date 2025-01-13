#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "render/Window.hpp"
#include "render/Shader.hpp"
#include "render/Program.hpp"
#include "render/utils.hpp"
#include "scene/Camera.hpp"

#include "model/Octree.hpp"
#include "model/Sphere.hpp"

using namespace octree_modeling;

const std::string path_to_project = "src";

scene::Camera camera(
    glm::vec3(0.0f, 0.0f, 5.0f), // position
    glm::vec3(0.0f, 0.0f, -1.0f), // look_at
    glm::vec3(0.0f, 1.0f, 0.0f), // view_up (in view/camera space)
    scene::PERSPECTIVE, // projection type
    // near and far distances (positive numbers)
    0.01f, 500.0f,
    // bottom, top, left, right
    -0.01f, 0.01f, -0.01f, 0.01f
);

render::Program program;
render::Shader vertex_shader(GL_VERTEX_SHADER);
render::Shader fragment_shader(GL_FRAGMENT_SHADER);

glm::mat4
    model_mat(1.0f), // Model transformation
    view_mat = camera.get_view_matrix(), // View transformation
    projection_mat = camera.get_projection_matrix(); // Projection transformation

std::vector<float> vertices_pos;
std::vector<unsigned int> indexes_vertices_pos;
std::size_t quantity_of_indexes;

int main(int argc, char * argv[]) {

    // Initialize GLUT.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitContextFlags(GLUT_DEBUG);

    render::Window window(800, 800, glm::vec4(0.0, 0.0, 0.0, 1.0), "Octree Modeling");

    // Set GLUT callbacks.
    glutDisplayFunc(render::display);
    glutKeyboardFunc(render::keyboard);
    glutSpecialFunc(render::special_func_keyboard);
    glutMouseFunc(render::mouse);
    glutMotionFunc(render::mouse_drag);
    glutPassiveMotionFunc(render::mouse_passive_motion);
    glutReshapeFunc(render::window_reshape);
    glutIdleFunc(render::idle);

    // Initialize GLEW to load OpenGL API.
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {

        std::cout << "GLEW: Failed to initialize!" << std::endl;
        std::cout << "GLEW: " << glewGetErrorString(glew_status) << std::endl;
        return EXIT_FAILURE;

    }

    // Configure OpenGL resources.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    render::enable_openGL_debug_messages(false);

    program.create();

    vertex_shader.compile(path_to_project + "/shaders/main.vert");
    program.attach(vertex_shader);

    fragment_shader.compile(path_to_project + "/shaders/main.frag");
    program.attach(fragment_shader);

    program.link();
    program.use();

    glUniformMatrix4fv(glGetUniformLocation(program.get_id(), "model_mat"), 1, GL_FALSE, glm::value_ptr(model_mat));
    glUniformMatrix4fv(glGetUniformLocation(program.get_id(), "view_mat"), 1, GL_FALSE, glm::value_ptr(view_mat));
    glUniformMatrix4fv(glGetUniformLocation(program.get_id(), "projection_mat"), 1, GL_FALSE, glm::value_ptr(projection_mat));

    // Create a Vertex Array Object (VAO)
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a Vertex Buffer Object (VBO) for vertex position.

    // model::Octree octree(glm::vec3(0.0f), 4.4f, 4);
    // octree.build_from_primitive(model::Sphere(glm::vec3(0.0f), 2.2f));
    // vertices_pos = octree.leaves_vertices();
    // std::size_t quantity_of_cubes = vertices_pos.size()/3/8;

    model::Octree octree1(glm::vec3(0.0f), 4.4f, 4);
    octree1.build_from_primitive(model::Sphere(glm::vec3(-2.5f, 0.0f, 0.0), 2.2f));
    model::Octree octree2(glm::vec3(0.0f), 4.4f, 4);
    octree2.build_from_primitive(model::Sphere(glm::vec3(2.5f, 0.0f, 0.0), 2.2f));

    model::Octree octree = octree1.union_octree(octree2);
    vertices_pos = octree.leaves_vertices();
    std::size_t quantity_of_cubes = vertices_pos.size()/3/8;

    GLuint vbo_pos;
    glGenBuffers(1, &vbo_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices_pos.size(), vertices_pos.data(), GL_DYNAMIC_DRAW);

    GLuint position_attrib = glGetAttribLocation(program.get_id(), "pos");
    glEnableVertexAttribArray(position_attrib);
    glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    vertices_pos.clear();
    vertices_pos.shrink_to_fit();

    // Create a Element Buffer Object (EBO) for vertex position.

    indexes_vertices_pos.reserve(12 * 2 * quantity_of_cubes);

    for (std::size_t i = 0; i < quantity_of_cubes; i++) {

        indexes_vertices_pos.push_back(0 + i*8);
        indexes_vertices_pos.push_back(1 + i*8);

        indexes_vertices_pos.push_back(1 + i*8);
        indexes_vertices_pos.push_back(2 + i*8);

        indexes_vertices_pos.push_back(2 + i*8);
        indexes_vertices_pos.push_back(3 + i*8);

        indexes_vertices_pos.push_back(3 + i*8);
        indexes_vertices_pos.push_back(0 + i*8);

        indexes_vertices_pos.push_back(4 + i*8);
        indexes_vertices_pos.push_back(5 + i*8);

        indexes_vertices_pos.push_back(5 + i*8);
        indexes_vertices_pos.push_back(6 + i*8);

        indexes_vertices_pos.push_back(6 + i*8);
        indexes_vertices_pos.push_back(7 + i*8);

        indexes_vertices_pos.push_back(7 + i*8);
        indexes_vertices_pos.push_back(4 + i*8);

        indexes_vertices_pos.push_back(1 + i*8);
        indexes_vertices_pos.push_back(4 + i*8);

        indexes_vertices_pos.push_back(2 + i*8);
        indexes_vertices_pos.push_back(7 + i*8);

        indexes_vertices_pos.push_back(0 + i*8);
        indexes_vertices_pos.push_back(5 + i*8);

        indexes_vertices_pos.push_back(3 + i*8);
        indexes_vertices_pos.push_back(6 + i*8);

    }

    GLuint ebo_pos;
    glGenBuffers(1, &ebo_pos);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_pos);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indexes_vertices_pos.size(), indexes_vertices_pos.data(), GL_DYNAMIC_DRAW);

    quantity_of_indexes = indexes_vertices_pos.size();
    indexes_vertices_pos.clear();
    indexes_vertices_pos.shrink_to_fit();

    std::cout << "Volume da octree: " << octree.volume() << std::endl;

    glutMainLoop();

    return EXIT_SUCCESS;

}

void render::display () {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    glDrawElements(GL_LINES, quantity_of_indexes, GL_UNSIGNED_INT, 0);

    glutSwapBuffers();

}

void render::keyboard (unsigned char key, int x, int y) {

    switch (key) {

        case 27: // ESC

            // Terminates the main FreeGLUT loop.
            glutLeaveMainLoop();

            break;

        case 97: // A

            camera.set_position(camera.get_position() - glm::vec3(0.1f, 0.0f, 0.0f));
            camera.set_look_at(camera.get_look_at() - glm::vec3(0.1f, 0.0f, 0.0f));
            break;

        case 100: // D

            camera.set_position(camera.get_position() + glm::vec3(0.1f, 0.0f, 0.0f));
            camera.set_look_at(camera.get_look_at() + glm::vec3(0.1f, 0.0f, 0.0f));
            break;

        case 106: // J

            camera.set_position(camera.get_position() + glm::vec3(0.0f, 0.1f, 0.0f));
            camera.set_look_at(camera.get_look_at() + glm::vec3(0.0f, 0.1f, 0.0f));
            break;

        case 107: // K

            camera.set_position(camera.get_position() - glm::vec3(0.0f, 0.1f, 0.0f));
            camera.set_look_at(camera.get_look_at() - glm::vec3(0.0f, 0.1f, 0.0f));
            break;

        case 115: // S

            camera.set_position(camera.get_position() + glm::vec3(0.0f, 0.0f, 0.05f));
            camera.set_look_at(camera.get_look_at() + glm::vec3(0.0f, 0.0f, 0.05f));
            break;

        case 119: // W

            camera.set_position(camera.get_position() - glm::vec3(0.0f, 0.0f, 0.05f));
            camera.set_look_at(camera.get_look_at() - glm::vec3(0.0f, 0.0f, 0.05f));
            break;
        
        default:
            break;

    }

    // Asks GLUT to call the display function.
    glutPostRedisplay();

}

void render::special_func_keyboard (int key, int x, int y) {}

void render::mouse (int button, int state, int x, int y) {}

void render::mouse_drag (int x, int y) {}

void render::mouse_passive_motion (int x, int y) {}

void render::window_reshape (int x, int y) {}

void render::idle () {

    view_mat = camera.get_view_matrix();
    projection_mat = camera.get_projection_matrix();

    glUniformMatrix4fv(glGetUniformLocation(program.get_id(), "view_mat"), 1, GL_FALSE, glm::value_ptr(view_mat));
    glUniformMatrix4fv(glGetUniformLocation(program.get_id(), "projection_mat"), 1, GL_FALSE, glm::value_ptr(projection_mat));

    // Asks GLUT to call the display function.
    glutPostRedisplay();

}