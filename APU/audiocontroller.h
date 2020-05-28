#ifndef AUDIOCONTROLLER_H
#define AUDIOCONTROLLER_H

#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>

#define SAMPLES 44100
#define SAMPLE_RATE 44100



class audioController
{

private:

    sf::Int16 raw[SAMPLES];
//    sf::SoundBuffer buffer;
    sf::Sound sound;

    unsigned amplitude;
    double two_pi;
    double increment;
    double x;



public:
    audioController();
    ~audioController();



    void test();

};

#endif // AUDIOCONTROLLER_H
