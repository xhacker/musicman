#ifndef MIDI_H
#define MIDI_H

#include <iostream>
#include "note.h"

class Midi
{
public:
    Midi(std::string address);
    Note parse();
};

#endif // MIDI_H
