#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <AL/alc.h>
#include <AL/al.h>

#include "glutil.h"
#include "demo.h"
#include "panic.h"

namespace {

void
error_callback(int error, const char *description)
{
    panic("GLFW error: %s", description);
}

void
key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

}

#if 0
void
test_fft()
{
    gl::shader shader(GL_COMPUTE_SHADER);
    shader.load_source("fft-test.glsl");

    gl::program prog;
    prog.attach(shader);
    prog.link();

    static float shader_input[16] = { 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    gl::buffer ssbo_input(GL_SHADER_STORAGE_BUFFER);
    ssbo_input.set_data(sizeof(shader_input), shader_input);

    static float shader_output[16] = { 0 };
    gl::buffer ssbo_output(GL_SHADER_STORAGE_BUFFER);
    ssbo_output.set_data(sizeof(shader_output), shader_output);

    ssbo_input.bind_base(0);
    ssbo_output.bind_base(1);

    prog.use();
    GL_CHECK(glDispatchCompute(1, 1, 1));

    static float output[16];
    ssbo_output.get_sub_data(0, sizeof(output), output);

    for (int i = 0; i < 16; i++) {
        printf("%f ", output[i]);
    }
    putchar('\n');

    exit(0);
}
#endif

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "%s <ogg file>\n", *argv);
        return 1;
    }

    // init OpenAL

    ALCdevice *al_device;
    ALCcontext *al_context;

    if (!(al_device = alcOpenDevice(NULL)))
        panic("alcOpenDevice failed");

    if (!(al_context = alcCreateContext(al_device, NULL)))
        panic("alcCreateContext failed");

    alcMakeContextCurrent(al_context);
    alGetError();

    // init GLFW

    if (!glfwInit())
        return 1;

    glfwSetErrorCallback(error_callback);

    GLFWwindow *window = glfwCreateWindow(512, 128, "test", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewInit();

    glfwSetKeyCallback(window, key_callback);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    demo d(width, height);
    d.start_audio(argv[1]);

    while (!glfwWindowShouldClose(window)) {
        d.redraw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    alcMakeContextCurrent(NULL);
    alcDestroyContext(al_context);
    alcCloseDevice(al_device);
}
