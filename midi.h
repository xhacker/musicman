#ifndef MIDI_H
#define MIDI_H

#include <iostream>
#include "note.h"

const int division = 96;

class Midi
{
public:
    Midi(std::string address);
    void parse();
    Note notes[1000];
    int bpm;
private:
    std::string address;
};

#endif // MIDI_H
