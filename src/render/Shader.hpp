#ifndef OCTREE_MODELING_RENDER_SHADER_HPP
#define OCTREE_MODELING_RENDER_SHADER_HPP

#include <GL/glew.h>
#include <optional>
#include <string>

namespace octree_modeling {
    namespace render {

        class Shader {

            private:
                std::optional<GLuint> id;
                GLenum type;

            public:

                Shader (GLenum _type = GL_VERTEX_SHADER);
                virtual ~Shader ();

                GLuint get_id () const;
                GLenum get_type () const;

                // Compiles the shader from a file.
                void compile (const std::string source_path);
                // Deletes the shader.
                void destroy ();

        };

    }
}

#endif