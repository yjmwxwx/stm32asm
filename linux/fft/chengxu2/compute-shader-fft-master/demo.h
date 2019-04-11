#pragma once

#include <cstdint>

#include "glutil.h"
#include "ogg_player.h"

class demo
{
public:
    demo(int width, int height);

    void start_audio(const std::string& path);
    void redraw();

private:
    static const int WINDOW_SIZE = 512;

    void init();
    void update_sample_window();

    int width_, height_;

    gl::program render_prog_;
    gl::buffer vbo_;

    gl::program compute_prog_;
    gl::buffer ssbo_;

    GLuint texture_id_;

    ogg_player player_;
    uint64_t start_ms_;

    float sample_window_[WINDOW_SIZE];
};
