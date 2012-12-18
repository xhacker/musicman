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

//Note **Midi::parse()
//{
//    return (Note **)notes;
//}
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
