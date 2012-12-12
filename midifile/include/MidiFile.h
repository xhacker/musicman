//
// Copyright 1999-2000 by Craig Stuart Sapp, All Rights Reserved.
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Fri Nov 26 14:12:01 PST 1999
// Last Modified: Fri Dec  2 13:26:44 PST 1999
// Last Modified: Fri Nov 10 12:13:15 PST 2000 (added some more editing cap.)
// Last Modified: Thu Jan 10 10:03:39 PST 2002 (added allocateEvents())
// Last Modified: Mon Jun 10 22:43:10 PDT 2002 (added clear())
// Last Modified: Sat Dec 17 23:11:57 PST 2005 (added millisecond ticks)
// Last Modified: Tue Feb  5 11:51:43 PST 2008 (read() set to const char*)
// Last Modified: Tue Apr  7 09:23:48 PDT 2009 (added addMetaEvent)
// Last Modified: Fri Jun 12 22:58:34 PDT 2009 (renamed SigCollection class)
// Filename:      ...sig/include/sigInfo/MidiFile.h
// Web Address:   http://sig.sapp.org/include/sigInfo/MidiFile.h
// Syntax:        C++ 
//
// Description:   A class which can read/write Standard MIDI files.
//                MIDI data is stored by track in an array.  This
//                class is used for example in the MidiPerform class.
//

#ifndef _MIDIfILE_H_INCLUDED
#define _MIDIfILE_H_INCLUDED

#include "FileIO.h"
#include "Array.h"
#include "SigCollection.h"

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned long  ulong;

#define TIME_STATE_DELTA       0
#define TIME_STATE_ABSOLUTE    1

#define TRACK_STATE_SPLIT      0
#define TRACK_STATE_JOINED     1


class _MFEvent {
   public:
      _MFEvent (void);
      _MFEvent (int command);
      _MFEvent (int command, int param1);
      _MFEvent (int command, int param1, int param2);
      _MFEvent (int track, int command, int param1, int param2);
      _MFEvent (int aTime, int aTrack, int command, int param1, int param2);
     ~_MFEvent ();
      int time;
      int track;
      Array<uchar> data;
};



class MidiFile {
   public:
                MidiFile                  (void);
                MidiFile                  (const char* aFile);
               ~MidiFile                  ();

      void      absoluteTime              (void);
      int       addEvent                  (int aTrack, int aTime, 
                                             Array<uchar>& midiData);
      int       addMetaEvent              (int aTrack, int aTime, int aType,
                                             Array<uchar>& metaData);
      int       addMetaEvent              (int aTrack, int aTime, int aType,
                                             const char* metaData);
      int       addPitchBend              (int aTrack, int aTime,
		                             int aChannel, double amount);
      int       addTrack                  (void);
      int       addTrack                  (int count);
      void      allocateEvents            (int track, int aSize);
      void      deltaTime                 (void);
      void      deleteTrack               (int aTrack);
      void      erase                     (void);
      void      clear                     (void);
      _MFEvent& getEvent                  (int aTrack, int anIndex);
      int       getTimeState              (void);
      int       getTrackState             (void);
      int       getTicksPerQuarterNote    (void);
      int       getTrackCount             (void);
      int       getNumTracks              (void);
      int       getNumEvents              (int aTrack);
      void      joinTracks                (void);
      void      mergeTracks               (int aTrack1, int aTrack2);
      int       read                      (const char* aFile);

      void      setTicksPerQuarterNote    (int ticks);
      void      setMillisecondDelta       (void);

      void      sortTrack                 (SigCollection<_MFEvent>& trackData);
      void      sortTracks                (void);
      void      splitTracks               (void);
      int       write                     (const char* aFile);

   protected:
      SigCollection<SigCollection<_MFEvent>*> events;  // midi file events
      int                   ticksPerQuarterNote; // time base of file
      int                   trackCount;          // # of tracks in file
      int                   theTrackState;       // joined or split
      int                   theTimeState;        // absolute or delta
      char*                 readFileName;        // read file name

   private:
      void      extractMidiData  (FileIO& inputfile, Array<uchar>& array, 
                                       uchar& runningCommand);
      ulong     extractVlvTime   (FileIO& inputfile);
      ulong     unpackVLV        (uchar a, uchar b, uchar c, uchar d, uchar e);
      void      writeVLValue     (long aValue, Array<uchar>& data);
      int       makeVLV          (uchar *buffer, int number);
};


int eventcompare(const void* a, const void* b);
ostream& operator<<(ostream& out, MidiFile& aMidiFile);

#endif /* _MIDIfILE_H_INCLUDED */



// md5sum: ff46e64698e2d9e88ebeef3efa9927d0 MidiFile.h [20030102]
