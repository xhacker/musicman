#include "midi.h"
#include "note.h"
#include "jdksmidi/world.h"
#include "jdksmidi/midi.h"
#include "jdksmidi/msg.h"
#include "jdksmidi/sysex.h"
#include "jdksmidi/parser.h"

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
            parse();
        }
    }
    return 0;
}

Midi::parse()
{
      int l = ex->GetLength();

        if ( normal_sysex )
        {
            fprintf ( f, "Normal System-Exclusive message Len=%d", l );
        }
        else
        {
            fprintf ( f, "Authorization System-Exclusive message Len=%d", l );
        }

        for ( int i = 0; i < l; ++i )
        {
            if ( ( ( i ) % 20 ) == 0 )
            {
                fprintf ( f, "\n" );
            }

            fprintf ( f, "%02x ", ( int ) ex->GetData ( i ) );
        }

        fprintf ( f, "\n" );
        fflush ( f );
}
