#pragma once

//#define DEBUG
#define GLFW_INCLUDE_NONE
#define SOKOL_IMPL
#define SOKOL_GLCORE33
#define STB_IMAGE_IMPLEMENTATION

#include <unordered_map>
#include <complex>
#include <functional>

#include "GLFW/glfw3.h"
#include "sokol_gfx.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image.h"

#include "GraphicsManager.h"
#include "ECS.h"
#include "GuiManager.h"

using namespace RenEngine;
using namespace glm;

namespace
{
    // Transformation matrices.
    struct Uniforms
    {
        glm::mat4 projection;
        glm::mat4 transform;
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
        int width;
        int height;

        // Actual pipeline
        sg_pipeline pipeline;

        // Binds vertex buffer data to pipeline for each draw call.
        sg_bindings bindings{};

        // Tells the system what to do with the frame buffer when drawing a new frame.
        sg_pass_action pass_action{};

        // Stores image data.
        std::unordered_map<std::string, Image> imageMap;

};

// Constructor creates a new Private Implemenation automatically.
GraphicsManager::GraphicsManager()
: pImpl(new PrivateImpl())
{}

// Creates the window to be displayed with the specific
// configuration parameters.
void GraphicsManager::startup(Configuration windowParam)
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

    pImpl->width = windowParam.window.width;
    pImpl->height = windowParam.window.height;

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

    // A vertex buffer containing a textured square.
    const float vertices[] = {
        // positions      // texcoords
        -1.0f,  -1.0f,    0.0f,  0.0f,
        1.0f,  -1.0f,    1.0f,  0.0f,
        -1.0f,   1.0f,    0.0f,  1.0f,
        1.0f,   1.0f,    1.0f,  1.0f,
    };

    sg_buffer_desc buffer_desc{};
    sg_buffer vertex_buffer;

    // Pipeline description to describe GPU state for drawing.
    sg_pipeline_desc pipeline_desc{};

    // Shader
    sg_shader_desc shader_desc{};

    buffer_desc.data = SG_RANGE(vertices);
    vertex_buffer = sg_make_buffer(buffer_desc);    

    // Triangle strip for data primitives.
    pipeline_desc.primitive_type = SG_PRIMITIVETYPE_TRIANGLE_STRIP;

    // Alpha blending.
    pipeline_desc.colors[0].blend.enabled = true;
    pipeline_desc.colors[0].blend.src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA;
    pipeline_desc.colors[0].blend.dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA;

    // Depth buffer.
    pipeline_desc.depth.compare = SG_COMPAREFUNC_LESS_EQUAL;
    pipeline_desc.depth.write_enabled = true;

    // Layout of points.
    pipeline_desc.layout.attrs[0].format = SG_VERTEXFORMAT_FLOAT2;
    pipeline_desc.layout.attrs[1].format = SG_VERTEXFORMAT_FLOAT2;

    // Vertex shader.
    shader_desc.vs.source = R"(
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

    // Sets the uniform matrices used in the vertex shader.
    shader_desc.vs.uniform_blocks[0].size = sizeof(Uniforms);
    
    // The order of `.uniforms[0]` and `.uniforms[1]` must match the order in `Uniforms`
    shader_desc.vs.uniform_blocks[0].uniforms[0].name = "projection";
    shader_desc.vs.uniform_blocks[0].uniforms[0].type = SG_UNIFORMTYPE_MAT4;
    shader_desc.vs.uniform_blocks[0].uniforms[1].name = "transform";
    shader_desc.vs.uniform_blocks[0].uniforms[1].type = SG_UNIFORMTYPE_MAT4;
    
    // Fragment shader.
    shader_desc.fs.source = R"(
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
    shader_desc.fs.images[0].name = "tex"; // The name should match the shader source code.
    shader_desc.fs.images[0].image_type = SG_IMAGETYPE_2D;

    // Pass shader to the GPU and initialize the pipeline.
    pipeline_desc.shader = sg_make_shader( shader_desc );
    pImpl->pipeline = sg_make_pipeline( pipeline_desc );

    // Tells system what to do when drawing a new frame.
    pImpl->pass_action.colors[0].action = SG_ACTION_CLEAR;
    /* red, green, blue, alpha floating point values for a color to fill the frame buffer with */
    pImpl->pass_action.colors[0].value = {/*0.5, 0.5, 0.5, 1.0*/};
    
    pImpl->bindings.vertex_buffers[0] = vertex_buffer;
}

void GraphicsManager::shutdown()
{
    delete pImpl;
    glfwTerminate();
    sg_shutdown();
}

// Creates the projection matrix for drawing.
void GraphicsManager::createProjectionMatrix(glm::mat4& projection, int width, int height)
{
    // Set up the projection matrix.
    // Start with an identity matrix.
    projection = mat4{1};
    // Scale x and y by 1/100.
    projection[0][0] = projection[1][1] = 1./100.;
    // Scale the long edge by an additional 1/(long/short) = short/long.
    if( width < height ) {
        projection[1][1] *= width;
        projection[1][1] /= height;
    } else {
        projection[0][0] *= height;
        projection[0][0] /= width;
    }
}

// Creates the transformation matrix for each sprite.
void GraphicsManager::createTransformMatrix(const std::string name,
                                            const Position& pos, 
                                            const Rotation& rot, 
                                            const Scale& scaleVal, 
                                            glm::mat4& transform)
{
    // Set the transformation matrix.
    // Allows translation, rotation and scaling.
    transform = translate( mat4{1}, pos ) 
                * rotate(mat4{1}, radians(rot.angle), normalize(vec3{0.0, 0.0, pos.z}))
                * scale( mat4{1}, vec3( scaleVal.scale ) );

    // Scales down quad so that image draws within the appropriate aspect ratio.
    int image_width = pImpl->imageMap[name].width;
    int image_height = pImpl->imageMap[name].height;

    if( image_width < image_height ) {
    transform = transform * scale( mat4{1}, vec3( std::real(image_width)/image_height, 1.0, 1.0 ) );
    } else {
        transform = transform * scale( mat4{1}, vec3( 1.0, std::real(image_height)/image_width, 1.0 ) );
    }
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
    Image newImage{};
    int channels;
    unsigned char* data = stbi_load( path.c_str(), &newImage.width, &newImage.height, &channels, 4 );

    // Load failed.
    if(data == NULL)
        return false;

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

// Computes the box collider of a sprite.
// Doesn't handle rotations.
void GraphicsManager::getBoxCollider(const std::string& name, const vec3 pos, const int scale, vec2& min, vec2& max)
{
    vec2 dimensions(pImpl->imageMap[name].width, pImpl->imageMap[name].height);
    vec2 truScale;

    // First, compute the true scale values.
    if(dimensions.x < dimensions.y)
        truScale = vec2(scale, scale) * vec2(std::real(dimensions.x)/dimensions.y, 1.0);
    else if(dimensions.x > dimensions.y)
        truScale = vec2(scale, scale) * vec2(1.0, std::real(dimensions.y)/dimensions.x);
    else
        truScale = vec2(scale, scale);

    // Compute the min/max corners of bounding box as world
    // coordinates based on offsets from the center position.
    min = vec2(pos.x - truScale.x, pos.y - truScale.y);
    max = vec2(pos.x + truScale.x, pos.y + truScale.y);
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

void GraphicsManager::draw(ECS& ecs, GuiManager& gm)
{
    int width, height;

    // 1. Gets current frame buffer size corresponding to the window.
    glfwGetFramebufferSize(pImpl->window, &width, &height);

    // 2. Clears default frame buffer.
    sg_begin_default_pass(pImpl->pass_action, width, height);

    // 3. Apply the pipeline.
    sg_apply_pipeline(pImpl->pipeline);

    // Sprite transformation matrices.
    Uniforms uniforms;

    // 4. Creates the projection matrix
    createProjectionMatrix(uniforms.projection, width, height);

    // 5. Draw each sprite with a position, rotation and scale components.
    ecs.ForEach<Sprite>([&](EntityID e)
    {
        std::string name = ecs.Get<Sprite>(e).name;
        Position pos = ecs.Get<Position>(e);
        Rotation rot = ecs.Get<Rotation>(e);
        Scale scale = ecs.Get<Scale>(e);

        // NOTE: Here's a good place to test if images aren't being drawn.

        createTransformMatrix(name, pos, rot, scale, uniforms.transform);
        sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, SG_RANGE(uniforms));
        pImpl->bindings.fs_images[0] = pImpl->imageMap[name].image;
        sg_apply_bindings(pImpl->bindings);
        sg_draw(0, 4, 1);
    });

    #ifdef DEBUG
    gm.draw(ecs, this);
    #endif

    // 6. End drawing.
    sg_end_pass();
    sg_commit();
    glfwSwapBuffers(pImpl->window);
}

int GraphicsManager::width()
{
    return pImpl->width;
}

int GraphicsManager::height()
{
    return pImpl->height;
}