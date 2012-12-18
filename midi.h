#ifndef MIDI_H
#define MIDI_H

#include <iostream>
#include "note.h"

class Midi
{
public:
    Midi(std::string address);
    note[] parse();
private:
    std::string address;
};

#endif // MIDI_H
