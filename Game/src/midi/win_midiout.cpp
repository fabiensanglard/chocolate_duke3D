/*
Copyright (C) 2000, 2001, 2002  Ryan Nunn

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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#if (__GNUG__ >= 2) && (!defined WIN32)
#  pragma interface
#endif

//Windows-specific code
#ifdef WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// These will prevent inclusion of mmsystem sections
#define MMNODRV         // Installable driver support
#define MMNOSOUND       // Sound support
#define MMNOWAVE        // Waveform support
#define MMNOAUX         // Auxiliary audio support
#define MMNOMIXER       // Mixer support
#define MMNOTIMER       // Timer support
#define MMNOJOY         // Joystick support
#define MMNOMCI         // MCI support
#define MMNOMMIO        // Multimedia file I/O support

#include <windows.h>
#include <mmsystem.h>
#include <winbase.h>

#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cstring>
#include <cassert>

#include "win_midiout.h"
#include "SDL_mixer.h"

#define W32MO_THREAD_COM_READY			0
#define W32MO_THREAD_COM_PLAY			1
#define W32MO_THREAD_COM_STOP			2
#define W32MO_THREAD_COM_INIT			3
#define W32MO_THREAD_COM_INIT_FAILED	4
#define W32MO_THREAD_COM_EXIT			-1

const unsigned short Windows_MidiOut::centre_value = 0x2000;
const unsigned char Windows_MidiOut::fine_value = centre_value & 127;
const unsigned char Windows_MidiOut::coarse_value = centre_value >> 7;
const unsigned short Windows_MidiOut::combined_value = (coarse_value << 8) | fine_value;

#define MUSIC_STATUS_IDLE    0
#define MUSIC_STATUS_PLAYING 1

unsigned char nMusicState = MUSIC_STATUS_IDLE;

Mix_Music *music;

//#define DO_SMP_TEST

#ifdef DO_SMP_TEST
#define giveinfo() std::cerr << __FILE__ << ":" << __LINE__ << std::endl; std::cerr.flush();
#else
#define giveinfo()
#endif

using std::string;
using std::cout;
using std::cerr;
using std::endl;


Windows_MidiOut::Windows_MidiOut() : 
dev_num(-1), 
new_volume(-1)
{
	giveinfo();
	InterlockedExchange (&playing, false);
	InterlockedExchange (&s_playing, false);
	InterlockedExchange (&is_available, false);
	giveinfo();
	init_device();
	giveinfo();
}

Windows_MidiOut::~Windows_MidiOut()
{
	giveinfo();
	if (!is_available) return;

	giveinfo();
	while (thread_com != W32MO_THREAD_COM_READY) Sleep (1);
	
	giveinfo();
	InterlockedExchange (&thread_com, W32MO_THREAD_COM_EXIT);

	giveinfo();
	int count = 0;
	
	giveinfo();
	while (count < 100)
	{
		giveinfo();
		DWORD code;
		GetExitCodeThread (thread_handle, &code);
		
		giveinfo();
		// Wait 1 MS before trying again
		if (code == STILL_ACTIVE) Sleep (10);
		else break;
		giveinfo();
		
		count++;
	}

	// We waited a second and it still didn't terminate
	giveinfo();
	if (count == 100 && is_available)
		TerminateThread (thread_handle, 1);

	giveinfo();
	InterlockedExchange (&is_available, false);
	giveinfo();
}

void Windows_MidiOut::init_device()
{
	string s;
		
	// Opened, lets open the thread
	giveinfo();
	InterlockedExchange (&thread_com, W32MO_THREAD_COM_INIT);
	
	// Get Win32 Midi Device num
	dev_num = get_MusicDevice();//0;//MidiDevice;//0;//-1;

	giveinfo();
	thread_handle = (HANDLE*) CreateThread (NULL, 0, thread_start, this, 0, &thread_id);
	
	giveinfo();
	while (thread_com == W32MO_THREAD_COM_INIT) Sleep (1);

	giveinfo();
	if (thread_com == W32MO_THREAD_COM_INIT_FAILED) cerr << "Failure to initialize midi playing thread" << endl;
	giveinfo();
}

DWORD __stdcall Windows_MidiOut::thread_start(void *data)
{
	giveinfo();
	Windows_MidiOut *ptr=static_cast<Windows_MidiOut *>(data);
	giveinfo();
	return ptr->thread_main();
}

DWORD Windows_MidiOut::thread_main()
{
	int i;
	thread_data = NULL;
	giveinfo();
	InterlockedExchange (&playing, false);
	InterlockedExchange (&s_playing, false);

	giveinfo();

	// List all the midi devices.
	MIDIOUTCAPS caps;
	signed long dev_count = (signed long) midiOutGetNumDevs(); 
	std::cout << dev_count << " Midi Devices Detected" << endl;
	std::cout << "Listing midi devices:" << endl;

	for (i = -1; i < dev_count; i++)
	{
		midiOutGetDevCaps ((UINT) i, &caps, sizeof(caps));
		std::cout << i << ": " << caps.szPname << endl;
	}

	if (dev_num < -1 || dev_num >= dev_count)
	{
		std::cerr << "Warning Midi device in config is out of range." << endl;
		dev_num = -1;
	}
	midiOutGetDevCaps ((UINT) dev_num, &caps, sizeof(caps));
	std::cout << "Using device " << dev_num << ": "<< caps.szPname << endl;

	UINT mmsys_err = midiOutOpen (&midi_port, dev_num, 0, 0, 0);

	giveinfo();
	if (mmsys_err != MMSYSERR_NOERROR)
	{
		char buf[512];

		giveinfo();
		midiOutGetErrorText(mmsys_err, buf, 512);
		cerr << "Unable to open device: " << buf << endl;
		giveinfo();
		InterlockedExchange (&thread_com, W32MO_THREAD_COM_INIT_FAILED);
		giveinfo();
		return 1;
	}
	giveinfo();
	InterlockedExchange (&is_available, true);
	
//	SetThreadPriority (thread_handle, THREAD_PRIORITY_HIGHEST);
	giveinfo();
	SetThreadPriority (thread_handle, THREAD_PRIORITY_TIME_CRITICAL);
	
	giveinfo();
	InterlockedExchange (&thread_com, W32MO_THREAD_COM_READY);
	InterlockedExchange (&sfx_com, W32MO_THREAD_COM_READY);

	giveinfo();
	thread_play();
	giveinfo();

	giveinfo();
	Sleep(100);
	midiOutClose (midi_port);
	Sleep(100);
	giveinfo();
	giveinfo();
	return 0;
}

void Windows_MidiOut::thread_play ()
{
	int				repeat = false;
	uint32			aim = 0;
	sint32			diff = 0;
	uint32			last_tick = 0;
	XMIDIEventList	*evntlist = NULL;
	midi_event		*event = NULL;
	NoteStack		notes_on;
	midi_event		*note = NULL;

	//
	// Xmidi Looping
	//

	// The for loop event
	midi_event	*loop_event[XMIDI_MAX_FOR_LOOP_COUNT];

	// The amount of times we have left that we can loop
	int		loop_count[XMIDI_MAX_FOR_LOOP_COUNT];

	// The level of the loop we are currently in
	int		loop_num = -1;		

	giveinfo();

	int				s_track = 0;
	uint32			s_aim = 0;
	sint32			s_diff = 0;
	uint32			s_last_tick = 0;
	NoteStack		s_notes_on;
	XMIDIEventList	*s_evntlist = NULL;
	midi_event		*s_event = NULL;

	giveinfo();

	vol_multi = 0xFF;

	// Play while there isn't a message waiting
	while (1)
	{
		if (thread_com == W32MO_THREAD_COM_EXIT && !playing && !s_playing) break;
		
		// Volume settings
		if (new_volume != -1) {
			vol_multi = new_volume;
			new_volume = -1;

			for (int i = 0; i < 16; i++) {
				uint32 message = i;
				message |= MIDI_STATUS_CONTROLLER << 4;
				message |= 7 << 8;
				message |= ((volumes[i] * vol_multi)/0xFF)<<16;
				midiOutShortMsg (midi_port,  message);
			}
		}

		if (thread_com == W32MO_THREAD_COM_STOP)
		{
			giveinfo();
			InterlockedExchange (&playing, FALSE);
			InterlockedExchange (&thread_com, W32MO_THREAD_COM_READY);

			// Handle note off's here
			while (note = notes_on.Pop())
				midiOutShortMsg (midi_port, note->status + (note->data[0] << 8));

			giveinfo();
		 	// Clean up
			for (int i = 0; i < 16; i++) reset_channel (i); 

			midiOutReset (midi_port);
			giveinfo();
			if (evntlist) evntlist->DecerementCounter();
			giveinfo();
			evntlist = NULL;
			event = NULL;
			giveinfo();

			// If stop was requested, we are ready to receive another song

			loop_num = -1;

			wmoInitClock ();
			last_tick = 0;
		}

		// Handle note off's here
		while (note = notes_on.PopTime(wmoGetRealTime()))
			midiOutShortMsg (midi_port, note->status + (note->data[0] << 8));

		while (note = s_notes_on.PopTime(wmoGetRealTime()))
			midiOutShortMsg (midi_port, note->status + (note->data[0] << 8));

		while (event && thread_com != W32MO_THREAD_COM_STOP)
		{
	 		aim = (event->time-last_tick)*50;
			diff = aim - wmoGetTime ();

			if (diff > 0) break;

			last_tick = event->time;
			wmoAddOffset(aim);
		
				// XMIDI For Loop
			if ((event->status >> 4) == MIDI_STATUS_CONTROLLER && event->data[0] == XMIDI_CONTROLLER_FOR_LOOP)
			{
				if (loop_num < XMIDI_MAX_FOR_LOOP_COUNT) loop_num++;

				loop_count[loop_num] = event->data[1];
				loop_event[loop_num] = event;

			}	// XMIDI Next/Break
			else if ((event->status >> 4) == MIDI_STATUS_CONTROLLER && event->data[0] == XMIDI_CONTROLLER_NEXT_BREAK)
			{
				if (loop_num != -1)
				{
					if (event->data[1] < 64)
					{
						loop_num--;
					}
				}
				event = NULL;

			}	// XMIDI Callback Trigger
			else if ((event->status >> 4) == MIDI_STATUS_CONTROLLER && event->data[0] == XMIDI_CONTROLLER_CALLBACK_TRIG)
			{
				// TODO
			}	// Not SysEx
			else if (event->status < 0xF0)
			{
				unsigned int type = event->status >> 4;
				uint32 data = event->data[0] | (event->data[1] << 8);

				// Channel volume
				if (type == MIDI_STATUS_CONTROLLER && event->data[0] == 0x7) {
					volumes[event->status &0xF] = event->data[1];
					data = event->data[0] | (((event->data[1] * vol_multi)/0xFF)<<8);
				}

				if ((type != MIDI_STATUS_NOTE_ON || event->data[1]) && type != MIDI_STATUS_NOTE_OFF) {
					if (type == MIDI_STATUS_NOTE_ON) {
						notes_on.Remove(event);
						notes_on.Push (event, event->duration * 50 + wmoGetStart());
					}

					midiOutShortMsg (midi_port, event->status | (data<<8));
				}
			}
		
		 	if (event) event = event->next;
	
	 		if (!event || thread_com != W32MO_THREAD_COM_READY)
		 	{
				bool clean = !repeat || (thread_com != W32MO_THREAD_COM_READY) || last_tick == 0;

		 		if (clean)
		 		{
					InterlockedExchange (&playing, FALSE);
					if (thread_com == W32MO_THREAD_COM_STOP)
						InterlockedExchange (&thread_com, W32MO_THREAD_COM_READY);

					// Handle note off's here
					while (note = notes_on.Pop())
						midiOutShortMsg (midi_port, note->status + (note->data[0] << 8));

		 			// Clean up
					for (int i = 0; i < 16; i++) reset_channel (i); 
					midiOutReset (midi_port);
					if (evntlist) evntlist->DecerementCounter();
					evntlist = NULL;
					event = NULL;

					loop_num = -1;
					wmoInitClock ();
		 		}

				last_tick = 0;

				if (evntlist)
				{
	 				if (loop_num == -1) event = evntlist->events;
					else
					{
						event = loop_event[loop_num]->next;
						last_tick = loop_event[loop_num]->time;

						if (loop_count[loop_num])
							if (!--loop_count[loop_num])
								loop_num--;
					}
				}
		 	}
		}


		// Got issued a music play command
		// set up the music playing routine
		if (thread_com == W32MO_THREAD_COM_PLAY)
		{
			// Handle note off's here
			while (note = notes_on.Pop())
				midiOutShortMsg (midi_port, note->status + (note->data[0] << 8));

			// Manual Reset since I don't trust midiOutReset()
			giveinfo();
			for (int i = 0; i < 16; i++) reset_channel (i);
			midiOutReset (midi_port);

			if (evntlist) evntlist->DecerementCounter();
			evntlist = NULL;
			event = NULL;
			InterlockedExchange (&playing, FALSE);

			// Make sure that the data exists
			giveinfo();
			while (!thread_data) Sleep(1);
			
			giveinfo();
			evntlist = thread_data->list;
			repeat = thread_data->repeat;

			giveinfo();
			InterlockedExchange ((LONG*) &thread_data, (LONG) NULL);
			giveinfo();
			InterlockedExchange (&thread_com, W32MO_THREAD_COM_READY);
			
			giveinfo();
			if (evntlist) event = evntlist->events;
			else event = 0;

			giveinfo();
			last_tick = 0;
			
			giveinfo();
			wmoInitClock ();
	
			// Reset XMIDI Looping
			loop_num = -1;

			giveinfo();
			InterlockedExchange (&playing, true);
		}

	 	if (s_event)
	 	{
	 		s_aim = (s_event->time-s_last_tick)*50;
			s_diff = s_aim - wmoGetSFXTime ();
	 	}
	 	else 
	 		s_diff = 1;
	
		if (s_diff <= 0)
		{
			s_last_tick = s_event->time;
			wmoAddSFXOffset(s_aim);
		
			// Not SysEx
			if ((s_event->status >> 4) != MIDI_STATUS_SYSEX)
			{
				int type = s_event->status >> 4;

				if ((type != MIDI_STATUS_NOTE_ON || s_event->data[1]) && type != MIDI_STATUS_NOTE_OFF) {
					if (type == MIDI_STATUS_NOTE_ON) {
						s_notes_on.Remove(s_event);
						s_notes_on.Push (s_event, s_event->duration * 50 + wmoGetSFXStart());
					}

					midiOutShortMsg (midi_port, s_event->status + (s_event->data[0] << 8) + (s_event->data[1] << 16));
				}
				s_track |= 1 << (s_event->status & 0xF);
			}

		 	s_event = s_event->next;
		}
	 	if (s_evntlist && (!s_event || thread_com == W32MO_THREAD_COM_EXIT || sfx_com != W32MO_THREAD_COM_READY))
		{
		 	// Play all the remaining note offs 
			while (note = s_notes_on.Pop())
				midiOutShortMsg (midi_port, note->status + (note->data[0] << 8));
		 	
		 	// Also reset the played tracks
			for (int i = 0; i < 16; i++) if ((s_track >> i)&1) reset_channel (i);

			s_evntlist->DecerementCounter();
			s_evntlist = NULL;
			s_event = NULL;
			InterlockedExchange (&s_playing, false);
			if (sfx_com != W32MO_THREAD_COM_PLAY) InterlockedExchange (&sfx_com, W32MO_THREAD_COM_READY);
		}

		// Got issued a sound effect play command
		// set up the sound effect playing routine
		if (!s_evntlist && sfx_com == W32MO_THREAD_COM_PLAY)
		{
			giveinfo();
			cout << "Play sfx command" << endl;

		 	// Play all the remaining note offs 
			while (note = s_notes_on.Pop())
				midiOutShortMsg (midi_port, note->status + (note->data[0] << 8));

			// Make sure that the data exists
			while (!sfx_data) Sleep(1);
			
			giveinfo();
			s_evntlist = sfx_data->list;

			giveinfo();
			InterlockedExchange ((LONG*) &sfx_data, (LONG) NULL);
			InterlockedExchange (&sfx_com, W32MO_THREAD_COM_READY);
			giveinfo();
			
			if (s_evntlist) s_event = s_evntlist->events;
			else s_event = 0;

			giveinfo();
	
			s_last_tick = 0;
			
			giveinfo();
			wmoInitSFXClock ();

			giveinfo();
			InterlockedExchange (&s_playing, true);
			
			giveinfo();
			// Reset thet track counter
			s_track = 0;
		}

	 	if (event)
	 	{
	 		aim = (event->time-last_tick)*50;
			diff = aim - wmoGetTime ();
	 	}
	 	else 
	 		diff = 6;

	 	if (s_event)
	 	{
	 		s_aim = (s_event->time-s_last_tick)*50;
			s_diff = s_aim - wmoGetSFXTime ();
	 	}
	 	else 
	 		s_diff = 6;

		//std::cout << sfx_com << endl;

		if (diff > 5 && s_diff > 5) Sleep (1);
	}
	// Handle note off's here
	while (note = notes_on.Pop())
		midiOutShortMsg (midi_port, note->status + (note->data[0] << 8));

	// Play all the remaining note offs 
	while (note = s_notes_on.PopTime(wmoGetRealTime()))
		midiOutShortMsg (midi_port, note->status + (note->data[0] << 8));

	if (evntlist) evntlist->DecerementCounter();
	evntlist = NULL;
	if (s_evntlist) s_evntlist->DecerementCounter();
	s_evntlist = NULL;
	for (int i = 0; i < 16; i++) reset_channel (i); 
	midiOutReset (midi_port);
	InterlockedExchange (&new_volume, -1);
}

void Windows_MidiOut::reset_channel (int i)
{
	// Pitch Wheel
	midiOutShortMsg (midi_port, i | (MIDI_STATUS_PITCH_WHEEL << 4) | (combined_value << 8));
	
	// All controllers off
	midiOutShortMsg (midi_port, i | (MIDI_STATUS_CONTROLLER << 4) | (121 << 8));

	// All notes off
	midiOutShortMsg (midi_port, i | (MIDI_STATUS_CONTROLLER << 4) | (123 << 8));

	// Bank Select
	midiOutShortMsg (midi_port, i | (MIDI_STATUS_PROG_CHANGE << 4) | (0 << 8));
	midiOutShortMsg (midi_port, i | (MIDI_STATUS_CONTROLLER << 4) | (0 << 8));
	midiOutShortMsg (midi_port, i | (MIDI_STATUS_CONTROLLER << 4) | (32 << 8));

	// Modulation Wheel
	midiOutShortMsg (midi_port, i | (MIDI_STATUS_CONTROLLER << 4) | (1 << 8) | (coarse_value << 16));
	midiOutShortMsg (midi_port, i | (MIDI_STATUS_CONTROLLER << 4) | (33 << 8) | (fine_value << 16));
	
	// Volume
	volumes[i] = coarse_value;
	midiOutShortMsg (midi_port, i | (MIDI_STATUS_CONTROLLER << 4) | (7 << 8) | (((coarse_value*vol_multi)/0xFF) << 16));
	midiOutShortMsg (midi_port, i | (MIDI_STATUS_CONTROLLER << 4) | (39 << 8) | (fine_value << 16));

	// Pan
	midiOutShortMsg (midi_port, i | (MIDI_STATUS_CONTROLLER << 4) | (8 << 8) | (coarse_value << 16));
	midiOutShortMsg (midi_port, i | (MIDI_STATUS_CONTROLLER << 4) | (40 << 8) | (fine_value << 16));

	// Balance
	midiOutShortMsg (midi_port, i | (MIDI_STATUS_CONTROLLER << 4) | (10 << 8) | (coarse_value << 16));
	midiOutShortMsg (midi_port, i | (MIDI_STATUS_CONTROLLER << 4) | (42 << 8) | (fine_value << 16));

	// Effects (Reverb)
	midiOutShortMsg (midi_port, i | (MIDI_STATUS_CONTROLLER << 4) | (91 << 8));

	// Chorus
	midiOutShortMsg (midi_port, i | (MIDI_STATUS_CONTROLLER << 4) | (93 << 8));
}

void Windows_MidiOut::start_track (XMIDIEventList *xmidi, bool repeat)
{
	giveinfo();
	if (!is_available)
		init_device();

	giveinfo();
	if (!is_available)
		return;

	giveinfo();
	while (thread_com != W32MO_THREAD_COM_READY) Sleep (1);
	
	giveinfo();
	xmidi->IncerementCounter();
	data.list = xmidi;
	data.repeat = repeat;
//	xmidi->Write("winmidi_out.mid");
	
	giveinfo();
	InterlockedExchange ((LONG*) &thread_data, (LONG) &data);
	giveinfo();
	InterlockedExchange (&thread_com, W32MO_THREAD_COM_PLAY);
	giveinfo();
}

void Windows_MidiOut::start_sfx(XMIDIEventList *xmidi)
{
	giveinfo();
	if (!is_available)
		init_device();

	giveinfo();
	if (!is_available)
		return;
	
	giveinfo();
	while (sfx_com != W32MO_THREAD_COM_READY) Sleep (1);

	giveinfo();
	xmidi->IncerementCounter();
	sdata.list = xmidi;
	sdata.repeat;
	
	giveinfo();
	InterlockedExchange ((LONG*) &sfx_data, (LONG) &sdata);
	giveinfo();
	InterlockedExchange (&sfx_com, W32MO_THREAD_COM_PLAY);
	giveinfo();
}


void Windows_MidiOut::stop_track(void)
{
	giveinfo();
	if (!is_available)
		return;

	giveinfo();
	if (!playing) return;

	giveinfo();
	while (thread_com != W32MO_THREAD_COM_READY) Sleep (1);
	giveinfo();
	InterlockedExchange (&thread_com, W32MO_THREAD_COM_STOP);
	giveinfo();
	while (thread_com != W32MO_THREAD_COM_READY) Sleep (1);
	giveinfo();
}

void Windows_MidiOut::stop_sfx(void)
{
	giveinfo();
	if (!is_available)
		return;

	giveinfo();
	if (!s_playing) return;

	giveinfo();
	while (sfx_com != W32MO_THREAD_COM_READY) Sleep (1);
	giveinfo();
	InterlockedExchange (&sfx_com, W32MO_THREAD_COM_STOP);
	giveinfo();
}

bool Windows_MidiOut::is_playing(void)
{
	giveinfo();
	return playing!=0;
}

const char *Windows_MidiOut::copyright(void)
{
	giveinfo();
	return "Internal Win32 Midiout Midi Player for Pentagram. Version 1.2a";
}

//
// PSMDEX - Pentagram Streaming Midi Driver Extensions
//

int Windows_MidiOut::max_streams()
{
	return 1;
}

void Windows_MidiOut::start_stream(int str_num, XMIDIEventList *eventlist, bool repeat, bool activate, int vol)
{
	stop_track();
	set_volume(0, vol);
	start_track(eventlist, repeat);
}

void Windows_MidiOut::activate_stream(int str_num)
{

}

void Windows_MidiOut::stop_stream(int str_num)
{
	stop_track();
}

void Windows_MidiOut::set_volume(int str_num, int level)
{
	if (!is_available) return;

	while (new_volume != -1) Sleep (1);
	InterlockedExchange (&new_volume, level);
}

bool Windows_MidiOut::is_playing(int str_num)
{
	return is_playing();
}

int Windows_MidiOut::get_active()
{ 
	return 0;
}

extern "C"
{
    #include "../duke3d.h"

    int get_MusicDevice()
    {
        return MusicDevice;
    }
}

extern "C"
{

// The music functions...

#include "../duke3d.h"
#include "cache1d.h"

static char warningMessage[80];
static char errorMessage[80];

char *MUSIC_ErrorString(int ErrorNumber)
{
    switch (ErrorNumber)
    {
        case MUSIC_Warning:
            return(warningMessage);

        case MUSIC_Error:
            return(errorMessage);

        case MUSIC_Ok:
            return("OK; no error.");

        case MUSIC_ASSVersion:
            return("Incorrect sound library version.");

        case MUSIC_SoundCardError:
            return("General sound card error.");

        case MUSIC_InvalidCard:
            return("Invalid sound card.");

        case MUSIC_MidiError:
            return("MIDI error.");

        case MUSIC_MPU401Error:
            return("MPU401 error.");

        case MUSIC_TaskManError:
            return("Task Manager error.");

        case MUSIC_FMNotDetected:
            return("FM not detected error.");

        case MUSIC_DPMI_Error:
            return("DPMI error.");

        default:
            return("Unknown error.");
    } // switch

    assert(0);    // shouldn't hit this point.
    return(NULL);
} // MUSIC_ErrorString


static int music_initialized = 0, ext_music_initialized = 1;
static int music_context = 0;
static int music_loopflag = MUSIC_PlayOnce;
static Windows_MidiOut *midi_device = NULL;

extern void musdebug(const char *fmt, ...);
extern void init_debugging(void);
extern void setWarningMessage(const char *msg);
extern void setErrorMessage(const char *msg);
extern int MUSIC_ErrorCode;
#define __FX_TRUE  (1 == 1)
#define __FX_FALSE (!__FX_TRUE)

#pragma message (" The win_midi code is temp until the SDL midi code functions properly ")

#pragma message (" STUBBED musdebug ")
void musdebug(const char *fmt, ...)
{
#if 0
    va_list ap;

    if (false)
    {
        fprintf(debug_file, "DUKEMUS: ");
        va_start(ap, fmt);
        vfprintf(debug_file, fmt, ap);
        va_end(ap);
        fprintf(debug_file, "\n");
        fflush(debug_file);
    } // if
#endif
} // snddebug

#pragma message (" STUBBED setErrorMessage ")
static void setErrorMessage(const char *msg)
{
#if 0
    strncpy(errorMessage, msg, sizeof (errorMessage));
    // strncpy() doesn't add the null char if there isn't room...
    errorMessage[sizeof (errorMessage) - 1] = '\0';
    snddebug("Error message set to [%s].", errorMessage);
#endif
} // setErrorMessage

#pragma message (" STUBBED init_debugging ")
static void init_debugging(void)
{

}


int MUSIC_Init(int SoundCard, int Address)
{
    init_debugging();

    musdebug("INIT! card=>%d, address=>%d...", SoundCard, Address);

    if (music_initialized)
    {
        setErrorMessage("Music system is already initialized.");
        return(MUSIC_Error);
    } // if
    
    music_initialized = 1;
	
	midi_device = new Windows_MidiOut();

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
	    printf("Mix_OpenAudio: %s\n", Mix_GetError());
	}
	else {
	    ext_music_initialized = 1;
	}

    
    return(MUSIC_Ok);
} // MUSIC_Init


int MUSIC_Shutdown(void)
{
    musdebug("shutting down sound subsystem.");

    if ((!music_initialized) && (!ext_music_initialized))
    {
        setErrorMessage("Music system is not currently initialized.");
        return(MUSIC_Error);
    } // if

    if(midi_device)
	delete midi_device;
	midi_device = 0;
    music_context = 0;
    music_initialized = 0;
    music_loopflag = MUSIC_PlayOnce;

    nMusicState = MUSIC_STATUS_IDLE;
    
	return(MUSIC_Ok);
} // MUSIC_Shutdown


void MUSIC_SetMaxFMMidiChannel(int channel)
{
    musdebug("STUB ... MUSIC_SetMaxFMMidiChannel(%d).\n", channel);
} // MUSIC_SetMaxFMMidiChannel


void MUSIC_SetVolume(int volume)
{
	if(midi_device)
	midi_device->set_volume(0,volume);

	if (ext_music_initialized == 1)
	Mix_VolumeMusic((int)(volume / 2));

}

void MUSIC_SetMidiChannelVolume(int channel, int volume)
{
    musdebug("STUB ... MUSIC_SetMidiChannelVolume(%d, %d).\n", channel, volume);
} // MUSIC_SetMidiChannelVolume


void MUSIC_ResetMidiChannelVolumes(void)
{
    musdebug("STUB ... MUSIC_ResetMidiChannelVolumes().\n");
} // MUSIC_ResetMidiChannelVolumes


int MUSIC_GetVolume(void)
{
	if(midi_device)
	return midi_device->vol_multi;
	else
	return 0;
} // MUSIC_GetVolume


void MUSIC_SetLoopFlag(int loopflag)
{
    music_loopflag = loopflag;
} // MUSIC_SetLoopFlag


int MUSIC_SongPlaying(void)
{
    if (ext_music_initialized)
	{
	 return((Mix_PlayingMusic()) ? __FX_TRUE : __FX_FALSE);
	}
	else
	{
		if(midi_device)
			return midi_device->is_playing()?__FX_TRUE : __FX_FALSE;
		else
			return __FX_FALSE;
	}

} // MUSIC_SongPlaying


void MUSIC_Continue(void)
{
    if (Mix_PausedMusic())
        Mix_ResumeMusic();
    //else if (music_songdata)
      //  MUSIC_PlaySong(music_songdata, MUSIC_PlayOnce);
} // MUSIC_Continue


void MUSIC_Pause(void)
{
    Mix_PauseMusic();
} // MUSIC_Pause


int MUSIC_StopSong(void)
{
    if ( (Mix_PlayingMusic()) || (Mix_PausedMusic()) )
	{
        Mix_HaltMusic();

		if (music) Mix_FreeMusic(music);
		
		nMusicState = MUSIC_STATUS_IDLE;
	}
    
	if(midi_device) midi_device->stop_stream(0);

    return(MUSIC_Ok);
} // MUSIC_StopSong


int MUSIC_PlaySong(unsigned char *song, int loopflag)
{
    //SDL_RWops *rw;

    MUSIC_StopSong();

    //music_songdata = song;

    // !!! FIXME: This could be a problem...SDL/SDL_mixer wants a RWops, which
    // !!! FIXME:  is an i/o abstraction. Since we already have the MIDI data
    // !!! FIXME:  in memory, we fake it with a memory-based RWops. None of
    // !!! FIXME:  this is a problem, except the RWops wants to know how big
    // !!! FIXME:  its memory block is (so it can do things like seek on an
    // !!! FIXME:  offset from the end of the block), and since we don't have
    // !!! FIXME:  this information, we have to give it SOMETHING.

    /* !!! ARGH! There's no LoadMUS_RW  ?!
    rw = SDL_RWFromMem((void *) song, (10 * 1024) * 1024);  // yikes.
    music_musicchunk = Mix_LoadMUS_RW(rw);
    Mix_PlayMusic(music_musicchunk, (loopflag == MUSIC_PlayOnce) ? 0 : -1);
    */

	if(midi_device)
	midi_device->stop_stream(0);

	BufferDataSource mid_data((char*)song, 1024 * 1024);
	XMIDI		midfile(&mid_data, XMIDI_CONVERT_EMIDI_GM);
	XMIDIEventList *eventlist = midfile.GetEventList(0);
	if (eventlist) 
	{
		if(midi_device)
		midi_device->start_track(eventlist, loopflag?true:false);
	}

//STUBBED("Need to use PlaySongROTT.  :(");

    return(MUSIC_Ok);
} // MUSIC_PlaySong

int MUSIC_PlayExtSong(char *fn)
{
    MUSIC_StopSong();

	if(midi_device)
	midi_device->stop_stream(0);

    music = Mix_LoadMUS(fn);
	if(!music) 
	{
		printf("Mix_LoadMUS(\"%s\"): %s\n", fn, Mix_GetError());
		nMusicState = MUSIC_STATUS_IDLE;
	}
	else
	{
		
		if(Mix_PlayMusic(music, -1)==-1) 
		{
			printf("Mix_PlayMusic: %s\n", Mix_GetError());
    		nMusicState = MUSIC_STATUS_IDLE;
		}
		else 
		{
			nMusicState = MUSIC_STATUS_PLAYING;
		}
	}
return(MUSIC_Ok);

//STUBBED("Need to use PlaySongROTT.  :(");

} // MUSIC_PlaySong


extern char ApogeePath[256];

static void CheckAndPlayMusicType(const char* szName, const char* szType)
{

	char fpath[1024] = {'\0'};

	// Is this a TC?
	if(game_dir[0] != '\0')
	{
		
	   sprintf(fpath, "%s\\%s%s", game_dir, szName, szType);
	}
	else
	{
		// FIX_00010: Hi resolution tunes (*.ogg files) are now first searched in .\tunes\ 
		// and then searched in the main folder. Allows a better separation of files
		// OGG tunes are NOT required. They are only used if found else normal
		// MIDI files are used by default for music		

	   sprintf(fpath, "%s\\%s%s", HIRESMUSICPATH, szName, szType);
	   if (!SafeFileExists(fpath))
			sprintf(fpath, "%s%s", szName, szType);
	}

	// Play MP3 file if available
	if (nMusicState == MUSIC_STATUS_IDLE) 
	{
	    //If it exists let's play it.
	   if (SafeFileExists(fpath)) 
	   {
		   MUSIC_PlayExtSong(fpath);
	   }
	}
}

// Duke3D-specific.  --ryan.
void PlayMusic(char *fn)
{
	//extern int File_Exists(char *fn);
	//extern void GetOnlyNameOfFile(char *fn);

	short      fp;
    long        l;
	char *cfn;
	char *buffer;
	char fpath[19] = {'\0'};

	cfn = fn;

	//GetOnlyNameOfFile(cfn);
	buffer = strtok(cfn, ".");

	CheckAndPlayMusicType(buffer, ".ogg");
	CheckAndPlayMusicType(buffer, ".mp3");
	CheckAndPlayMusicType(buffer, ".mod");
	CheckAndPlayMusicType(buffer, ".s3m");
	CheckAndPlayMusicType(buffer, ".it");
	CheckAndPlayMusicType(buffer, ".xm");
	CheckAndPlayMusicType(buffer, ".wav");

	// else fall back to the midis.
	if (nMusicState == MUSIC_STATUS_IDLE) 
	{
		if(MusicToggle == 0) return;
		if(MusicDevice == NumSoundCards) return;
		if(eightytwofifty && numplayers > 1) return;

		fp = kopen4load(fn,0);

		if(fp == -1) return;

		l = kfilelength( fp );
		if(l >= 72000)
		{
	        kclose(fp);
			return;
		}

		kread( fp, MusicPtr, l);
		kclose( fp );
		MUSIC_PlaySong( (unsigned char*)MusicPtr, MUSIC_LoopSong );
	}
}


void MUSIC_SetContext(int context)
{
    musdebug("STUB ... MUSIC_SetContext().\n");
    music_context = context;
} // MUSIC_SetContext


int MUSIC_GetContext(void)
{
    return(music_context);
} // MUSIC_GetContext


void MUSIC_SetSongTick(unsigned long PositionInTicks)
{
    musdebug("STUB ... MUSIC_SetSongTick().\n");
} // MUSIC_SetSongTick


void MUSIC_SetSongTime(unsigned long milliseconds)
{
    musdebug("STUB ... MUSIC_SetSongTime().\n");
}// MUSIC_SetSongTime


void MUSIC_SetSongPosition(int measure, int beat, int tick)
{
    musdebug("STUB ... MUSIC_SetSongPosition().\n");
} // MUSIC_SetSongPosition


void MUSIC_GetSongPosition(songposition *pos)
{
    musdebug("STUB ... MUSIC_GetSongPosition().\n");
} // MUSIC_GetSongPosition


void MUSIC_GetSongLength(songposition *pos)
{
    musdebug("STUB ... MUSIC_GetSongLength().\n");
} // MUSIC_GetSongLength


int MUSIC_FadeVolume(int tovolume, int milliseconds)
{
 //   Mix_FadeOutMusic(milliseconds);
    return(MUSIC_Ok);
} // MUSIC_FadeVolume


int MUSIC_FadeActive(void)
{
   // return((Mix_FadingMusic() == MIX_FADING_OUT) ? __FX_TRUE : __FX_FALSE);
	return __FX_FALSE;
} // MUSIC_FadeActive


void MUSIC_StopFade(void)
{
    musdebug("STUB ... MUSIC_StopFade().\n");
} // MUSIC_StopFade


void MUSIC_RerouteMidiChannel(int channel, int cdecl ( *function )( int event, int c1, int c2 ))
{
    musdebug("STUB ... MUSIC_RerouteMidiChannel().\n");
} // MUSIC_RerouteMidiChannel


void MUSIC_RegisterTimbreBank(unsigned char *timbres)
{
    musdebug("STUB ... MUSIC_RegisterTimbreBank().\n");
} // MUSIC_RegisterTimbreBank


// end of fx_man.c ...

}



#endif
