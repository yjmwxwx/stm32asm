#include <cassert>
#include <cstring>

#include "panic.h"
#include "ogg_player.h"

ogg_player::ogg_player()
: playing(false)
{
    alGenSources(1, &source);
    alSourcef(source, AL_GAIN, 1.f);
}

ogg_player::~ogg_player()
{
    close();
    alDeleteSources(1, &source);
}

void
ogg_player::open(const std::string& path)
{
    if (!(ogg_file = fopen(path.c_str(), "rb")))
        panic("failed to open `%s'", path.c_str());

    if (ov_open(ogg_file, &ogg_stream, NULL, 0) < 0)
        panic("failed to open ogg stream");

    const vorbis_info *info = ov_info(&ogg_stream, -1);

    switch (info->channels) {
        case 1:
            format = AL_FORMAT_MONO16;
            break;

        case 2:
            format = AL_FORMAT_STEREO16;
            break;

        default:
            panic("invalid # of channels");
    }

    rate = info->rate;

    num_samples = ov_pcm_total(&ogg_stream, -1);
}

void
ogg_player::close()
{
    stop();
    ov_clear(&ogg_stream);
}

void
ogg_player::start()
{
    if (playing)
        return;

    for (int i = 0; i < NUM_BUFFERS; i++) {
        buffer& b = buffers[i];

        if (b.load(&ogg_stream) > 0)
            b.queue(source, format, rate);
    }

    alSourcePlay(source);

    playing = true;
}

void
ogg_player::stop()
{
    if (!playing)
        return;

    alSourceStop(source);

    ALint num_processed;
    while (alGetSourcei(source, AL_BUFFERS_PROCESSED, &num_processed), num_processed > 0) {
        ALuint id;
        alSourceUnqueueBuffers(source, 1, &id);
    }

    ov_raw_seek(&ogg_stream, 0);

    playing = false;
}

void
ogg_player::update()
{
    if (!playing)
        return;

    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);

    ALint num_processed;
    while (alGetSourcei(source, AL_BUFFERS_PROCESSED, &num_processed), num_processed > 0) {
        ALuint id;

        alSourceUnqueueBuffers(source, 1, &id);

        buffer *p = get_buffer(id);
        if (p->load(&ogg_stream) > 0)
            p->queue(source, format, rate);
    }

    if (state != AL_PLAYING) {
        ALint queued;

        alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);

        if (queued == 0) {
            // we're done
            playing = false;
        } else {
            // restart
            alSourcePlay(source);
        }
    }
}

int
ogg_player::get_num_buffer_samples() const
{
    switch (format) {
        case AL_FORMAT_MONO16:
            return buffer::BUFFER_SIZE/sizeof(int16_t);

        case AL_FORMAT_STEREO16:
            return buffer::BUFFER_SIZE/(2*sizeof(int16_t));

        default:
            assert(0);
            return 0;
    }
}

ogg_player::buffer *
ogg_player::get_buffer(ALuint id)
{
    for (int i = 0; i < NUM_BUFFERS; i++) {
        buffer *p = &buffers[i];
        if (p->id == id)
            return p;
    }

    panic("eh? invalid buffer %d?", id);
    return 0;
}

ogg_player::buffer::buffer()
{
    alGenBuffers(1, &id);
}

ogg_player::buffer::~buffer()
{
    alDeleteBuffers(1, &id);
}

long
ogg_player::buffer::load(OggVorbis_File *stream)
{
    size = 0;

    while (size < BUFFER_SIZE) {
        int section;
        long r = ov_read(stream, data + size, BUFFER_SIZE - size, 0, 2, 1, &section);

        if (r < 0)
            panic("ov_read failed");
        else if (r == 0)
            break;

        size += r;
    }

    return size;
}

void
ogg_player::buffer::queue(ALuint source, ALenum format, int rate)
{
    if (size > 0) {
        alBufferData(id, format, data, size, rate);
        alSourceQueueBuffers(source, 1, &id);
    }
}
