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

#ifndef WIN_MIDIOUT_H
#define WIN_MIDIOUT_H

#if (__GNUG__ >= 2) && (!defined WIN32)
#  pragma interface
#endif

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
#include "xmidi.h"

class	Windows_MidiOut
{
public:
	virtual void		start_track(XMIDIEventList *, bool repeat);
	virtual void		start_sfx(XMIDIEventList *);
	virtual void		stop_track(void);
	virtual void		stop_sfx(void);
	virtual bool		is_playing(void);
	virtual const char	*copyright(void);

	// PSMDEX - Pentagram Streaming Midi Driver Extensions
	virtual int			max_streams();
	virtual void		start_stream(int str_num, XMIDIEventList *, bool repeat, bool activate, int vol);
	virtual void		activate_stream(int str_num);
	virtual void		stop_stream(int str_num);
	virtual void		set_volume(int str_num, int level);
	virtual bool		is_playing(int str_num);
	virtual int			get_active();

	Windows_MidiOut();
	virtual ~Windows_MidiOut();

//private:

	struct mid_data {
		XMIDIEventList	*list;
		bool			repeat;
	};

	static const unsigned short	centre_value;
	static const unsigned char	fine_value;
	static const unsigned char	coarse_value;
	static const unsigned short	combined_value;

	signed int	dev_num;
	HMIDIOUT	midi_port;
	
	HANDLE	 	*thread_handle;
	DWORD		thread_id;

	// Thread communicatoins
	LONG		is_available;
	LONG		playing;
	LONG		s_playing;
	LONG		thread_com;
	LONG		sfx_com;

	LONG		new_volume;
	LONG		volumes[16];
	LONG		vol_multi;

	mid_data *thread_data;
	mid_data *sfx_data;

	mid_data data;
	mid_data sdata;

	// Methods
	static DWORD __stdcall thread_start(void *data);
	void init_device();
	DWORD thread_main();
	void thread_play ();
	void reset_channel (int i);

	// Microsecond Clock
	unsigned long start;
	unsigned long sfx_start;

	inline void wmoInitClock ()
	{ start = GetTickCount()*6; }

	inline void wmoAddOffset (unsigned long offset)
	{ start += offset; }

	inline unsigned long wmoGetTime ()
	{ return GetTickCount()*6 - start; }

	inline unsigned long wmoGetStart ()
	{ return start; }

	inline unsigned long wmoGetRealTime ()
	{ return GetTickCount()*6; }

	inline void wmoInitSFXClock ()
	{ sfx_start = GetTickCount()*6; }

	inline void wmoAddSFXOffset (unsigned long offset)
	{ sfx_start += offset; }

	inline unsigned long wmoGetSFXTime ()
	{ return GetTickCount()*6 - sfx_start; }

	inline unsigned long wmoGetSFXStart ()
	{ return sfx_start; }
};

#endif //WIN32

extern "C"
{
    int get_MusicDevice();
}

#endif //WIN_MIDIOUT_H
