#ifndef MIDI_H
#define MIDI_H

#include <iostream>
#include "note.h"

class Midi
{
public:
    Midi(std::string address);
    void parse();
    Note notes[1000];
    int bpm;
    int division;
private:
    std::string address;
};

#endif // MIDI_H
