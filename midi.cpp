#include <cstdio>
#include "midi.h"
#include "note.h"

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
            break;
        //printf("%d: %d %d\n", notes[count].key, notes[count].start, notes[count].end);
        ++count;
    }
}
