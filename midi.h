#ifndef MIDI_H
#define MIDI_H

#include <iostream>

class Midi
{
public:
    Midi(std::string address);
    void parse();
};

#endif // MIDI_H
