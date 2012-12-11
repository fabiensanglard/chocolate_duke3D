/*
Copyright (C) 2000  Ryan Nunn

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

// Tab Size = 4

#ifndef __XMIDI_h_
#define __XMIDI_h_

#include <string>
//#include "common_types.h"
#include "databuf.h"


// Conversion types for Midi files
#define XMIDI_CONVERT_NOCONVERSION		0
#define XMIDI_CONVERT_MT32_TO_GM		1
#define XMIDI_CONVERT_MT32_TO_GS		2
#define XMIDI_CONVERT_MT32_TO_GS127		3
#define XMIDI_CONVERT_OGG               4
#define XMIDI_CONVERT_GS127_TO_GS		5
#define XMIDI_CONVERT_EMIDI_GM			6	// For Duke3D! Selects General Midi tracks

// Midi Status Bytes
#define MIDI_STATUS_NOTE_OFF	0x8
#define MIDI_STATUS_NOTE_ON		0x9
#define MIDI_STATUS_AFTERTOUCH	0xA
#define MIDI_STATUS_CONTROLLER	0xB
#define MIDI_STATUS_PROG_CHANGE	0xC
#define MIDI_STATUS_PRESSURE	0xD
#define MIDI_STATUS_PITCH_WHEEL	0xE
#define MIDI_STATUS_SYSEX		0xF

// XMIDI Controllers
#define XMIDI_CONTROLLER_CHAN_LOCK			0x6e	// Channel Lock
#define XMIDI_CONTROLLER_CHAN_LOCK_PROT		0x6f	// Channel Lock Protect
#define XMIDI_CONTROLLER_VOICE_PROT			0x70	// Voice Protect
#define XMIDI_CONTROLLER_TIMBRE_PROT		0x71	// Timbre Protect
#define XMIDI_CONTROLLER_BANK_CHANGE		0x72	// Bank Change
#define XMIDI_CONTROLLER_IND_CTRL_PREFIX	0x73	// Indirect Controller Prefix
#define XMIDI_CONTROLLER_FOR_LOOP			0x74	// For Loop
#define XMIDI_CONTROLLER_NEXT_BREAK			0x75	// Next/Break
#define XMIDI_CONTROLLER_CLEAR_BB_COUNT		0x76	// Clear Beat/Bar Count
#define XMIDI_CONTROLLER_CALLBACK_TRIG		0x77	// Callback Trigger
#define XMIDI_CONTROLLER_SEQ_BRANCH_INDEX	0x78	// Sequence Branch Index

#define EMIDI_CONTROLLER_TRACK_DESIGNATION	110		// Track Designation
#define EMIDI_CONTROLLER_TRACK_EXCLUSION	111		// Track Exclusion
#define EMIDI_CONTROLLER_PROGRAM_CHANGE		112		// Program Change
#define EMIDI_CONTROLLER_VOLUME				113		// Volume
#define EMIDI_CONTROLLER_LOOP_BEGIN			XMIDI_CONTROLLER_FOR_LOOP
#define EMIDI_CONTROLLER_LOOP_END			XMIDI_CONTROLLER_NEXT_BREAK


// Maximum number of for loops we'll allow (used by win_midiout)
#define XMIDI_MAX_FOR_LOOP_COUNT	128

template <class T> class GammaTable;

struct midi_event
{
	int				time;
	unsigned char	status;

	unsigned char	data[2];

	uint32			len;		// Length of SysEx Data
	unsigned char	*buffer;	// SysEx Data
	int				duration;	// Duration of note (120 Hz)
	midi_event		*next_note;	// The next note on the stack
	uint32			note_time;	// Time note stops playing (6000th of second)
	midi_event	*next;
};

class NoteStack {
	midi_event		*notes;		// Top of the stack
	int				polyphony;
	int				max_polyphony;
public:

	NoteStack() : notes(0), polyphony(0), max_polyphony(0) { }

	// Just clear it. Don't care about what's actually in it
	void clear() {
		notes=0;
		polyphony=0;
		max_polyphony=0;
	}

	// Pops the top of the stack if its off_time is <= time (6000th of second)
	inline midi_event *PopTime(uint32 time) {
		if (notes && notes->note_time <= time)  {
			midi_event *note = notes;
			notes = note->next_note;
			note->next_note = 0;
			polyphony--;
			return note;
		}

		return 0;
	}

	// Pops the top of the stack
	inline midi_event *Pop() {
		if (notes)  {
			midi_event *note = notes;
			notes = note->next_note;
			note->next_note = 0;
			polyphony--;
			return note;
		}

		return 0;
	}

	// Pops the top of the stack
	inline midi_event *Remove(midi_event *event) {
		midi_event *prev = 0;
		midi_event *note = notes;
		while (note) {

			if (note == event) {
				if (prev) prev->next_note = note->next_note;
				else notes = note->next_note;
				note->next_note = 0;
				polyphony--;
				return note;
			}
			prev = note;
			note = note->next_note;
		}
		return 0;
	}

	// Finds the note that has same pitch and channel, and pops it
	inline midi_event *FindAndPop(midi_event *event) {

		midi_event *prev = 0;
		midi_event *note = notes;
		while (note) {

			if ((note->status & 0xF) == (event->status & 0xF) && note->data[0] == event->data[0]) {
				if (prev) prev->next_note = note->next_note;
				else notes = note->next_note;
				note->next_note = 0;
				polyphony--;
				return note;
			}
			prev = note;
			note = note->next_note;
		}
		return 0;
	}

	// Pushes a note onto the top of the stack
	inline void Push(midi_event *event) {
		event->next_note = notes;
		notes = event;
		polyphony++;
		if (max_polyphony < polyphony) max_polyphony = polyphony;
	}


	inline void Push(midi_event *event, uint32 time) {
		event->note_time = time;
		event->next_note = 0;

		polyphony++;
		if (max_polyphony < polyphony) max_polyphony = polyphony;

		if (!notes || time <= notes->note_time) {
			event->next_note = notes;
			notes = event;
		}
		else {
			midi_event *prev = notes;
			while (prev) {
				midi_event *note = prev->next_note;

				if (!note || time <= note->note_time) {
					event->next_note = note;
					prev->next_note = event;
					return;
				}
				prev = note;
			}
		}
	}

	inline int GetPolyphony() {
		return polyphony;
	}

	inline int GetMaxPolyphony() {
		return max_polyphony;
	}
};

class XMIDIEventList 
{
	int				counter;
	
	// Helper funcs for Write
	int				PutVLQ(DataSource *dest, uint32 value);
	uint32			ConvertListToMTrk (DataSource *dest);

	static void		DeleteEventList (midi_event *list);

public:
	midi_event		*events;

	// Write this list to a file/buffer
	int				Write (const char *filename);	
	int				Write (DataSource *dest);	

	// Increments the counter
	void			IncerementCounter () { counter++; }

	// Decrement the counter and delete the event list, if possible
	void			DecerementCounter ();
};

class   XMIDI
{
protected:
	uint16				num_tracks;

private:
	XMIDIEventList		**events;

	midi_event			*list;
	midi_event			*current;
	midi_event			*notes_on;
	
	const static char	mt32asgm[128];
	const static char	mt32asgs[256];
	bool 				bank127[16];
	int					convert_type;

	bool				is_emidi;
	bool				use_emidi_112;
	bool				use_emidi_113;
	
	bool				do_reverb;
	bool				do_chorus;
	int					chorus_value;
	int					reverb_value;

public:
	XMIDI(DataSource *source, int pconvert);
	~XMIDI();

	int number_of_tracks() { return num_tracks; }

	// External Event list functions
	XMIDIEventList *GetEventList (uint32 track);

	// Not yet implimented
	// int apply_patch (int track, DataSource *source);

private:
	XMIDI(); // No default constructor
    
    struct first_state {			// Status,	Data[0]
		midi_event		*patch[16];	// 0xC
		midi_event		*bank[16];	// 0xB,		0
		midi_event		*pan[16];	// 0xB,		7
		midi_event		*vol[16];	// 0xB,		10
	};

	// List manipulation
	void CreateNewEvent (int time);

	// Variable length quantity
	int GetVLQ (DataSource *source, uint32 &quant);
	int GetVLQ2 (DataSource *source, uint32 &quant);

	void AdjustTimings(uint32 ppqn);	// This is used by Midi's ONLY!
	void ApplyFirstState(first_state &fs, int chan_mask);

	int ConvertNote (const int time, const unsigned char status, DataSource *source, const int size);
	int ConvertEvent (const int time, unsigned char status, DataSource *source, const int size, first_state& fs);
	int ConvertSystemMessage (const int time, const unsigned char status, DataSource *source);

	int ConvertFiletoList (DataSource *source, const bool is_xmi, first_state& fs);

	int ExtractTracksFromXmi (DataSource *source);
	int ExtractTracksFromMid (DataSource *source, const uint32 ppqn, const int num_tracks, const bool type1);
	
	int ExtractTracks (DataSource *source);
};
#endif
