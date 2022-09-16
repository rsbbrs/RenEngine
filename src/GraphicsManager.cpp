#pragma once

#define GLFW_INCLUDE_NONE
#define SOKOL_IMPL
#define SOKOL_GLCORE33

#include <vector>

#include "GLFW/glfw3.h"
#include "sokol_gfx.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GraphicsManager.h"

using namespace RenEngine;
using namespace glm;

// Private implemenation class.
class PrivateImpl
{
    public:
        // Pointer to main window.
        GLFWwindow* window;

        // A vertex buffer containing a textured square.
        std::vector<float> vertices;
        
        // Vertex buffer for 2D objects.
        sg_buffer_desc buffer_desc{};
        sg_buffer vertex_buffer;

        // Pipeline description to describe GPU state for drawing.
        sg_pipeline_desc pipeline_desc{};

        // Actual pipeline
        sg_pipeline pipeline;

        // Shader
        sg_shader_desc shader_desc{};
};

// Constructor creates a new Private Implemenation automatically.
GraphicsManager::GraphicsManager()
: pImpl(new PrivateImpl())
{}

// Creates the window to be displayed with the specific
// configuration parameters.
void GraphicsManager::gmStartup(Configuration windowParam)
{
    // Window creation magic by GLFW.
    glfwInit();

    // We'll use sokol_gfx's OpenGL backend
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    pImpl->window = glfwCreateWindow( windowParam.window.width, 
                                           windowParam.window.height, 
                                           windowParam.window.name, 
                                           windowParam.window.fullscreen ? glfwGetPrimaryMonitor() : 0, 0);

    glfwSetWindowAspectRatio( pImpl->window, windowParam.window.width, windowParam.window.height );

    if( !pImpl->window )
    {
        std::cerr << "Failed to create a window." << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent( pImpl->window );
    
    glfwSwapInterval(1);

    // Sokol startup
    sg_setup(sg_desc{});

    pImpl->vertices = {
        // positions      // texcoords
        -1.0f,  -1.0f,    0.0f,  0.0f,
        1.0f,  -1.0f,    1.0f,  0.0f,
        -1.0f,   1.0f,    0.0f,  1.0f,
        1.0f,   1.0f,    1.0f,  1.0f,
    };

    pImpl->buffer_desc.data = SG_RANGE(pImpl->vertices);
    pImpl->vertex_buffer = sg_make_buffer(pImpl->buffer_desc);

    // Triangle strip for data primitives.
    pImpl->pipeline_desc.primitive_type = SG_PRIMITIVETYPE_TRIANGLE_STRIP;

    // Alpha blending.
    pImpl->pipeline_desc.colors[0].blend.enabled = true;
    pImpl->pipeline_desc.colors[0].blend.src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA;
    pImpl->pipeline_desc.colors[0].blend.dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;

    // Depth buffer.
    pImpl->pipeline_desc.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;
    pImpl->pipeline_desc.depth.write_enabled = true;

    // Layout of points.
    pImpl->pipeline_desc.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT2;
    pImpl->pipeline_desc.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT2;

    // Transformation matrices.
    struct Uniforms {
        mat4 projection;
        mat4 transform;
    };

    pImpl->shader_desc.vs.source = R"(
        #version 330
        uniform mat4 projection;
        uniform mat4 transform;
        layout(location=0) in vec2 position;
        layout(location=1) in vec2 texcoords0;
        out vec2 texcoords;
        void main() {
            gl_Position = projection*transform*vec4( position, 0.0, 1.0 );
            texcoords = texcoords0;

            // Sets up the projection and transformation matrices and informs the GPU about them.
            // The order of `.uniforms[0]` and `.uniforms[1]` must match the order in `Uniforms`
            pImpl->shader_desc.vs.uniform_blocks[0].size = sizeof(Uniforms);
            pImpl->shader_desc.vs.uniform_blocks[0].uniforms[0].name = "projection";
            pImpl->shader_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_MAT4;
            pImpl->shader_desc.vs.uniform_blocks[0].uniforms[1].name = "transform";
            pImpl->shader_desc.vs.uniform_blocks[0].uniforms[1].type = SG_UNIFORMTYPE_MAT4;

            // Start with an identity matrix.
            uniforms.projection = mat4{1};
            // Scale x and y by 1/100.
            uniforms.projection[0][0] = uniforms.projection[1][1] = 1./100.;
            // Scale the long edge by an additional 1/(long/short) = short/long.
            if( width < height ) {
                uniforms.projection[1][1] *= width;
                uniforms.projection[1][1] /= height;
            } else {
                uniforms.projection[0][0] *= height;
                uniforms.projection[0][0] /= width;
            }

            uniforms.transform = translate( mat4{1}, vec3( position, z ) ) * scale( mat4{1}, glm::vec3( scale ) );

            if( image_width < image_height ) {
                uniforms.transform = uniforms.transform * scale( mat4{1}, vec3( real(image_width)/image_height, 1.0, 1.0 ) );
            } else {
                uniforms.transform = uniforms.transform * scale( mat4{1}, vec3( 1.0, real(image_height)/image_width, 1.0 ) );
            }   
        })";

    pImpl->shader_desc.fs.source = R"(
        #version 330
        uniform sampler2D tex;
        in vec2 texcoords;
        out vec4 frag_color;
        void main() {
            frag_color = texture( tex, texcoords );
            // If we're not drawing back to front, discard very transparent pixels so we
            // don't write to the depth buffer and prevent farther sprites from drawing.
            if( frag_color.a < 0.1 ) discard;
        }
    )";
    pImpl->shader_desc.fs.images[0].name = "tex"; // The name should match the shader source code.
    pImpl->shader_desc.fs.images[0].image_type = SG_IMAGETYPE_2D;

    // Sets up the pipeline using the shaders.
    pImpl->pipeline_desc.shader = sg_make_shader( pImpl->shader_desc );
    pImpl->pipeline = sg_make_pipeline( pImpl->pipeline_desc );
}

void GraphicsManager::gmShutdown()
{
    delete pImpl;
    glfwTerminate();
    sg_shutdown();
}

// Returns the value of the close flag, which
// is set to 1 whenever the close button is 
// pressed, otherwise returns 0.
bool GraphicsManager::closeWindow()
{
    return !glfwWindowShouldClose(pImpl->window);
}

// Used to access the window by the input manager.
void* GraphicsManager::getWindow()
{
    return pImpl->window;
}