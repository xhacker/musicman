#include <cstdio>
#include "midi.h"
#include "note.h"
//#include "jdksmidi/world.h"
//#include "jdksmidi/midi.h"
//#include "jdksmidi/msg.h"
//#include "jdksmidi/sysex.h"
//#include "jdksmidi/parser.h"

//#include "jdksmidi/fileread.h"
//#include "jdksmidi/fileshow.h"

//using namespace jdksmidi;

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
//        printf("%d: %d %d\n", notes[count].key, notes[count].start, notes[count].end);
        ++count;
    }
}
