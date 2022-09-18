#pragma once

#define GLFW_INCLUDE_NONE
#define SOKOL_IMPL
#define SOKOL_GLCORE33
#define STB_IMAGE_IMPLEMENTATION

#include <unordered_map>

#include "GLFW/glfw3.h"
#include "sokol_gfx.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image.h"
#include "GraphicsManager.h"

using namespace RenEngine;
using namespace glm;

namespace
{
    // Transformation matrices.
    struct Uniforms {
        mat4 projection;
        mat4 transform;
    };

    // Image struct to hold sprite image info.
    typedef struct image_info
    {
        sg_image image;
        int width, height;
    } Image;
}

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

        // Tells the system what to do with the frame buffer when drawing a new frame.
        sg_pass_action pass_action{};

        // Binds vertex buffer data to pipeline for each draw call.
        sg_bindings bindings{};

        // Stores image data.
        std::unordered_map<std::string, Image> imageMap;

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

    // Vertex shader.
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
    })";
    pImpl->shader_desc.vs.uniform_blocks[0].size = sizeof(Uniforms);
    // The order of `.uniforms[0]` and `.uniforms[1]` must match the order in `Uniforms`
    pImpl->shader_desc.vs.uniform_blocks[0].uniforms[0].name = "projection";
    pImpl->shader_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_MAT4;
    pImpl->shader_desc.vs.uniform_blocks[0].uniforms[1].name = "transform";
    pImpl->shader_desc.vs.uniform_blocks[0].uniforms[1].type = SG_UNIFORMTYPE_MAT4;

    // Fragment shader.
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
    })";
    pImpl->shader_desc.fs.images[0].name = "tex"; // The name should match the shader source code.
    pImpl->shader_desc.fs.images[0].image_type = SG_IMAGETYPE_2D;

    // Pass shader to the GPU and initialize the pipeline.
    pImpl->pipeline_desc.shader = sg_make_shader( pImpl->shader_desc );
    pImpl->pipeline = sg_make_pipeline( pImpl->pipeline_desc );

    // Tells system what to do when drawing a new frame.
    pImpl->pass_action.colors[0].action = SG_ACTION_CLEAR;
    /* red, green, blue, alpha floating point values for a color to fill the frame buffer with */
    pImpl->pass_action.colors[0].value = {0.5, 0.5, 0.0, 1.0};

    
    pImpl->bindings.vertex_buffers[0] = pImpl->vertex_buffer;
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

// Loads sprite images to attach to fragment shader.
bool GraphicsManager::loadImage(const std::string& name, const std::string& path)
{
    // Loads the image.
    Image newImage = {};
    int channels;
    unsigned char* data = stbi_load( path.c_str(), &newImage.width, &newImage.height, &channels, 4 );

    // Uploads image data to the GPU
    sg_image_desc image_desc{};
    image_desc.width = newImage.width;
    image_desc.height = newImage.height;
    image_desc.pixel_format = SG_PIXELFORMAT_RGBA8;
    image_desc.min_filter = SG_FILTER_LINEAR;
    image_desc.mag_filter = SG_FILTER_LINEAR;
    image_desc.wrap_u = SG_WRAP_CLAMP_TO_EDGE;
    image_desc.wrap_v = SG_WRAP_CLAMP_TO_EDGE;
    image_desc.data.subimage[0][0].ptr = data;
    image_desc.data.subimage[0][0].size = (size_t)(newImage.width * newImage.height * 4);

    sg_image image = sg_make_image( image_desc );
    newImage.image = image;

    // Adds the image data to the map
    pImpl->imageMap[name] = newImage;

    // Free image memory now that data's in the GPU.
    stbi_image_free( data );

    return true;
}

// Destroys a specific image in the image map.
void GraphicsManager::destroyImage(const std::string& name)
{
    pImpl->imageMap.erase(name);
}

// Clears the entire list of images.
void GraphicsManager::clearAllImages()
{
    pImpl->imageMap.clear();
}