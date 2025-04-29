#include "sound.hpp"

Uint32 sound::open_snd_device()
{
    wavSpec.freq = SAMPLE_RATE;
    wavSpec.format = AUDIO_U16; // 16-bit little-endian samples
    wavSpec.channels = 2;      // Mono
    wavSpec.samples = BUFFER_SIZE;
    wavSpec.callback = nullptr;
    // wavSpec.userdata = nullptr;
    sndDevID = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(1, 0), 0, &wavSpec, nullptr, 0);
    // sndDevID = SDL_OpenAudio(&wavSpec, nullptr);
    std::cout << SDL_GetNumAudioDevices(0) << "opened dev: " << SDL_GetAudioDeviceName(1, 0) << '\n';

    if (sndDevID < 0)
    {
        std::cerr << "SDL could not open audio device! SDL_Error: " << SDL_GetError() << std::endl;
    }

    return sndDevID;
}

void sound::generateSineWave(Uint32 *buffer, int length, double frequency)
{
    double phaseIncrement = 2.0 * M_PI * frequency / SAMPLE_RATE;
    double phase = 0.0;

    for (int i = 0; i < length / 2; ++i)
    {
        Sint32 sample = static_cast<Sint32>(32767.0 * sin(phase));
        buffer[i] = sample;
        phase += phaseIncrement;
        if (phase >= 2.0 * M_PI)
        {
            phase -= 2.0 * M_PI;
        }
    }
}

void sound::audioCallback(void *userdata, Uint8 *stream, int len)
{
    Sint16 *buffer = static_cast<Sint16 *>(userdata);
    int samples = len / sizeof(Sint16);
    // generateSineWave(buffer, samples, FREQUENCY);
    SDL_memcpy(stream, buffer, len);
}

sound::sound()
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        SDLSoundSuccess = false;
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }
}

sound::~sound()
{
    SDL_CloseAudioDevice(sndDevID);
}

void sound::play_sound(int freq)
{
    // if (open_snd_device())
    // {
    //     /* code */
    // }

    // open_snd_device();
    // SDL_PauseAudio(0);
    
    SDL_PauseAudioDevice(sndDevID, 0); // Start playing audio
    Uint32 buffer[BUFFER_SIZE];
    generateSineWave(buffer, BUFFER_SIZE, freq);
    SDL_QueueAudio(sndDevID, buffer, BUFFER_SIZE);
}

bool sound::pause_sound()
{
    SDL_PauseAudioDevice(sndDevID, 0); // Start playing audio
    return false;
}
