#include "midi.h"
#include “note.h”

Midi::Midi(std::string address)
{
    fprintf ( stdout, "mdparse:\n" );
    MIDIParser p ( 32 * 1024 );
    MIDIMessage m;
    FILE *f = fopen("D:\\jeffsong.mid", "r");

    while ( !feof ( f ) )
    {
        int c = fgetc ( f );

        if ( c == EOF )
            break;

        if ( p.Parse ( ( uchar ) c, &m ) )
        {
            parse（）；
        }
    }
    system("pause");
    return 0;
}

Midi：：parse{

      }
