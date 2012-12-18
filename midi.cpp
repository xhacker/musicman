#include "midi.h"
#include "note.h"
#include "jdksmidi/world.h"
#include "jdksmidi/midi.h"
#include "jdksmidi/msg.h"
#include "jdksmidi/sysex.h"
#include "jdksmidi/parser.h"

using namespace jdksmidi;

Midi::Midi(std::string address) : address(address)
{
}

Note **Midi::parse()
{
    Note notes[6][200] =
    {
        {
            {0, 0, 0}
        },
        {
            {1, 0, 45},
            {1, 144, 237},
            {1, 336, 429},
            {1, 528, 621},
            {1, 720, 765}
        },
        {
            {2, 48, 93},
            {2, 240, 285},
            {2, 432, 477},
            {2, 624, 669},
            {2, 768, 813}
        },
        {
            {3, 96, 141},
            {3, 288, 333},
            {3, 480, 525},
            {3, 672, 717},
            {3, 816, 861}
        },
        {
            {4, 864, 909},
            {4, 1056, 1101},
            {4, 1248, 1293},
            {4, 1440, 1485},
            {4, 2016, 2061},
        },
        {
        }
    };
    return (Note **)notes;
}
//    FILE *out = fopen("parse.out", "w");
//    MIDIParser p(32 * 1024);
//    MIDITimedBigMessage m;
//    FILE *f = fopen(address.c_str(), "r");

//    while (!feof(f))
//    {
//        int c = fgetc(f);

//        if (c == EOF)
//            break;

//        if (p.Parse((uchar)c, &m))
//        {
//            // 84-88
////            if (m.IsNote() && m.GetNote() <= 88)
//            {
//                fprintf(out, "%d\t%s\t%d\n", m.GetTime(), m.IsNoteOn() ? "On" : "Off", m.GetNote() - 83);
//            }
//        }
//    }
