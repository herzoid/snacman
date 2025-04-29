#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#define SAMPLE_RATE 44100
#define FREQUENCY 440 // Частота в герцах (например, 440 Гц для ноты A4)
#define BUFFER_SIZE 4096


class sound
{
private:
    bool SDLSoundSuccess;
    SDL_AudioDeviceID sndDevID;
    SDL_AudioSpec wavSpec;

    void generateSineWave(Uint32 *buffer, int length, double frequency);
    void audioCallback(void *userdata, Uint8 *stream, int len);

public:
    sound(/* args */);
    ~sound();
    Uint32 open_snd_device();
    void play_sound(int freq);
    bool pause_sound();
};
