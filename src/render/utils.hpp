#ifndef OCTREE_MODELING_RENDER_UTILS_HPP_
#define OCTREE_MODELING_RENDER_UTILS_HPP_

#include <GL/glew.h>
#include <string>

#ifndef APIENTRY
#define APIENTRY
#endif

namespace octree_modeling {
    namespace render {

        // OpenGL Debug

        std::string get_openGL_version ();
        void APIENTRY openGL_debug_message_callback (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);
        void enable_openGL_debug_messages (bool enable_notifications = true);

        // FreeGLUT callbacks (must be implemented in the same file of main function)

        // Called when FreeGLUT needs to draw something on the screen.
        void display ();
        // Handles keyboard events involving keys that have ASCII representations.
        void keyboard (unsigned char key, int x, int y);
        // Handles keyboard events involving special keys like Shift, Ctrl, Fn, F1 to F12, etc.
        void special_func_keyboard (int key, int x, int y);
        // Handles events involving mouse buttons.
        void mouse (int button, int state, int x, int y);
        // Handles events involving mouse movement while a button is being pressed.
        void mouse_drag (int x, int y);
        // Handles events involving passive mouse movement (when no button is being pressed).
        void mouse_passive_motion (int x, int y);
        // Handles window resizing events.
        void window_reshape (int x, int y);
        // Handles moments when no events are being processed.
        void idle ();

    }
}

#endif