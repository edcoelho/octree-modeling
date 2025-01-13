#include <iostream>
#include <stdexcept>
#include <string>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "render/Window.hpp"
#include "render/Shader.hpp"
#include "render/Program.hpp"
#include "render/utils.hpp"
#include "scene/Camera.hpp"

using namespace octree_modeling;

const std::string path_to_project = "src";

scene::Camera camera(
    glm::vec3(0.0f, 0.0f, 0.0f), // position
    glm::vec3(0.0f, 0.0f, -1.0f), // look_at
    glm::vec3(0.0f, 1.0f, 0.0f), // view_up (in view/camera space)
    scene::ORTHOGRAPHIC, // projection type
    // near and far distances (positive numbers)
    1.0f, 5.0f,
    // bottom, top, left, right
    -5.0f, 5.0f, -5.0f, 5.0f
);

render::Program program;
render::Shader vertex_shader(GL_VERTEX_SHADER);
render::Shader fragment_shader(GL_FRAGMENT_SHADER);

glm::mat4
    model_mat(1.0f), // Model transformation
    view_mat = camera.get_view_matrix(), // View transformation
    projection_mat = camera.get_projection_matrix(); // Projection transformation

int main(int argc, char * argv[]) {

    // Initialize GLUT.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitContextFlags(GLUT_DEBUG);

    render::Window window(500, 500, glm::vec4(0.0, 0.0, 0.0, 1.0), "Octree");

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

    float z_v = -2.0;
    float vertices_pos[] = {
        -3.0f, 2.5f, z_v,
        4.5f, 0.5f, z_v,
        -10.0f, -4.0f, z_v,
        4.7f, -3.0, z_v,
        4.0f, -4.5, z_v,
        4.9f, -4.0f, z_v
    };

    GLuint vbo_pos;
    glGenBuffers(1, &vbo_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_pos), vertices_pos, GL_STATIC_DRAW);

    GLuint position_attrib = glGetAttribLocation(program.get_id(), "pos");
    glEnableVertexAttribArray(position_attrib);
    glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    glutMainLoop();

    return EXIT_SUCCESS;

}

void render::display () {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glutSwapBuffers();

}

void render::keyboard (unsigned char key, int x, int y) {

    switch (key) {

        case 27: // ESC

            // Terminates the main FreeGLUT loop.
            glutLeaveMainLoop();

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

    // Asks GLUT to call the display function.
    glutPostRedisplay();

}