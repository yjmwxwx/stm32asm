#pragma once

#include <string>
#include <cstdio>

#include <AL/alc.h>
#include <AL/al.h>
#include <vorbis/vorbisfile.h>

struct ogg_player
{
    ogg_player();
    ~ogg_player();

    void open(const std::string& path);
    void close();

    void start();
    void stop();

    void update();

    float get_track_duration() const
    { return static_cast<float>(num_samples)/rate; }

    int get_num_buffer_samples() const;

    struct buffer;
    buffer *get_buffer(ALuint id);

    struct buffer {
        buffer();
        ~buffer();

        long load(OggVorbis_File *stream);
        void queue(ALuint source, ALenum format, int rate);

        enum { BUFFER_SIZE = 2*8192 };
        char data[BUFFER_SIZE];

        long size;

        ALuint id;
    };

    enum { NUM_BUFFERS = 4, };
    buffer buffers[NUM_BUFFERS];

    FILE *ogg_file;
    OggVorbis_File ogg_stream;

    ALuint source;

    ALenum format;
    int rate;
    int num_samples;

    bool playing;
};
