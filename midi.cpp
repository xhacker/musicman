#include <cstdio>
#include "midi.h"
#include "note.h"

const int end_of_the_world = 31415926;

Midi::Midi(std::string address) : address(address)
{}

void Midi::parse()
{
    FILE *fin = fopen(address.c_str(), "r");
    fscanf(fin, "BPM=%d", &bpm);
    printf("BPM: %d\n", bpm);
    int count = 0;
    while (true)
    {
        fscanf(fin, "%d,%d,%d", &(notes[count].key), &(notes[count].start), &(notes[count].end));
        if (notes[count].key == 0)
        {
            notes[count].start = notes[count].end = end_of_the_world;
            break;
        }
        ++count;
    }
}
