#include <GL/glew.h>

#include <time.h>

#include "demo.h"

namespace {

uint64_t
get_cur_ms()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec*1000ull + ts.tv_nsec/1000000;
}

}

demo::demo(int width, int height)
    : width_ { width }
    , height_ { height }
    , vbo_ { GL_ARRAY_BUFFER }
    , ssbo_ { GL_SHADER_STORAGE_BUFFER }
{
    init();
}

void
demo::start_audio(const std::string& path)
{
    player_.open(path);
    player_.start();

    start_ms_ = get_cur_ms();
}

void
demo::redraw()
{
    player_.update();

    glViewport(0, 0, width_, height_);
    glClear(GL_COLOR_BUFFER_BIT);

    // compute

    update_sample_window();
    ssbo_.set_data(sizeof(sample_window_), sample_window_);

    ssbo_.bind_base(1);
    compute_prog_.use();
    GL_CHECK(glDispatchCompute(1, 1, 1));

    // render

    render_prog_.use();
    vbo_.bind();
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
}

void
demo::update_sample_window()
{
    uint64_t cur_ms = get_cur_ms() - start_ms_;

    const int buffer_samples = player_.get_num_buffer_samples();
    const int total_buffer_samples = buffer_samples*ogg_player::NUM_BUFFERS;

    // ogg_player::rate samples --> 1 second
    // y samples --> cur_ms msecs

    // 1 tic --> ogg_player::rate/30 samples

    int sample_index = (cur_ms*player_.rate/1000)%total_buffer_samples;

    for (int i = 0; i < WINDOW_SIZE; i++) {
        const ogg_player::buffer& buf = player_.buffers[sample_index/buffer_samples];
        const int16_t *buffer_data = reinterpret_cast<const int16_t *>(buf.data);

        int j = sample_index%buffer_samples;

        switch (player_.format) {
            case AL_FORMAT_MONO16:
                sample_window_[i] = static_cast<float>(buffer_data[j])/(1 << 15);
                break;

            case AL_FORMAT_STEREO16:
                {
                int16_t l = buffer_data[j*2];
                int16_t r = buffer_data[j*2 + 1];
                sample_window_[i] = (.5*(static_cast<float>(l) + static_cast<float>(r)))/(1 << 15);
                }
                break;
        }

        if (++sample_index == total_buffer_samples)
            sample_index = 0;
    }
}

void
demo::init()
{
    // vert/frag shaders

    gl::shader vert_shader(GL_VERTEX_SHADER);
    vert_shader.load_source("vert.glsl");

    gl::shader frag_shader(GL_FRAGMENT_SHADER);
    frag_shader.load_source("frag.glsl");

    render_prog_.attach(vert_shader);
    render_prog_.attach(frag_shader);
    render_prog_.link();

    // vbo

    static const GLfloat verts[] { -1, -1, -1, 1, 1, -1, 1,  1 };
    vbo_.set_data(sizeof(verts), verts);

    vbo_.bind();
    GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));
    GL_CHECK(glEnableVertexAttribArray(0));

    // compute shader

    gl::shader compute_shader(GL_COMPUTE_SHADER);
    compute_shader.load_source("fft.glsl");

    compute_prog_.attach(compute_shader);
    compute_prog_.link();

    // texture

    // XXX need a wrapper for this

    GL_CHECK(glGenTextures(1, &texture_id_));
    GL_CHECK(glActiveTexture(GL_TEXTURE0));
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture_id_));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, WINDOW_SIZE, 1, 0, GL_RED, GL_FLOAT, nullptr));
    GL_CHECK(glBindImageTexture(0, texture_id_, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F));
}
