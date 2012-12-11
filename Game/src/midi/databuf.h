/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef DATA_H
#define DATA_H

#ifndef ALPHA_LINUX_CXX
#  include <cstdio>
#  include <cstring>
#endif
#ifdef MACOS
#  include <cassert>
#endif
#include <fstream>
#include <iomanip>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;

typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;

class DataSource
{
protected:
	union uint_float {
		uint32	i;
		float	f;
	};

public:
	DataSource() {};
	virtual ~DataSource() {};
	
	virtual unsigned int read1() =0;
	virtual uint16 read2() =0;
	virtual uint16 read2high() =0;
	virtual uint32 read4() =0;
	virtual uint32 read4high() =0;
	virtual float readf() =0;
	virtual void read(char *, int) =0;
	
	virtual void write1(unsigned int) =0;
	virtual void write2(uint16) =0;
	virtual void write2high(uint16) =0;
	virtual void write4(uint32) =0;
	virtual void write4high(uint32) =0;
	virtual void writef(float) =0;
	virtual void write(char *, int) =0;
	
	virtual void seek(unsigned int) =0;
	virtual void skip(int) =0;
	virtual unsigned int getSize() =0;
	virtual unsigned int getPos() =0;
};

class BufferDataSource: public DataSource
{
protected:
	/* const solely so that no-one accidentally modifies it.
		data is being passed 'non-const' anyway */
	const unsigned char *buf;
	unsigned char *buf_ptr;
	sint32 size;
public:
	BufferDataSource(char *data, unsigned int len)
	{
		// data can be NULL if len is also 0
//		assert(data!=0 || len==0);
		buf = buf_ptr = reinterpret_cast<unsigned char*>(data);
		size = len;
	};
	
	void load(char *data, unsigned int len)
	{
		// data can be NULL if len is also 0
		//assert(data!=0 || len==0);
		buf = buf_ptr = reinterpret_cast<unsigned char*>(data);
		size = len;
	};
	
	virtual ~BufferDataSource() {};
	
	virtual unsigned int read1() 
	{ 
		unsigned char b0;
		b0 = static_cast<unsigned char>(*buf_ptr++);
		return (b0);
	};
	
	virtual uint16 read2()
	{
		unsigned char b0, b1;
		b0 = static_cast<unsigned char>(*buf_ptr++);
		b1 = static_cast<unsigned char>(*buf_ptr++);
		return (b0 | (b1 << 8));
	};
	
	virtual uint16 read2high()
	{
		unsigned char b0, b1;
		b1 = static_cast<unsigned char>(*buf_ptr++);
		b0 = static_cast<unsigned char>(*buf_ptr++);
		return (b0 | (b1 << 8));
	};
	
	virtual uint32 read4()
	{
		unsigned char b0, b1, b2, b3;
		b0 = static_cast<unsigned char>(*buf_ptr++);
		b1 = static_cast<unsigned char>(*buf_ptr++);
		b2 = static_cast<unsigned char>(*buf_ptr++);
		b3 = static_cast<unsigned char>(*buf_ptr++);
		return (b0 | (b1<<8) | (b2<<16) | (b3<<24));
	};
	
	virtual uint32 read4high()
	{
		unsigned char b0, b1, b2, b3;
		b3 = static_cast<unsigned char>(*buf_ptr++);
		b2 = static_cast<unsigned char>(*buf_ptr++);
		b1 = static_cast<unsigned char>(*buf_ptr++);
		b0 = static_cast<unsigned char>(*buf_ptr++);
		return (b0 | (b1<<8) | (b2<<16) | (b3<<24));
	};
	
	virtual float readf()
	{
		unsigned char b0, b1, b2, b3;
		b0 = static_cast<unsigned char>(*buf_ptr++);
		b1 = static_cast<unsigned char>(*buf_ptr++);
		b2 = static_cast<unsigned char>(*buf_ptr++);
		b3 = static_cast<unsigned char>(*buf_ptr++);
		uint_float	uif;
		uif.i = (b0 | (b1<<8) | (b2<<16) | (b3<<24));
		return uif.f;
	};
	
	void read(char *b, int len) {
		memcpy(b, buf_ptr, len);
		buf_ptr += len;
	};
	
	virtual void write1(unsigned int val)
	{
		*buf_ptr++ = val & 0xff;
	};
	
	virtual void write2(uint16 val)
	{
		*buf_ptr++ = val & 0xff;
		*buf_ptr++ = (val>>8) & 0xff;
	};

	virtual void write2high(uint16 val)
	{
		*buf_ptr++ = (val>>8) & 0xff;
		*buf_ptr++ = val & 0xff;
	};

	
	virtual void write4(uint32 val)
	{
		*buf_ptr++ = val & 0xff;
		*buf_ptr++ = (val>>8) & 0xff;
		*buf_ptr++ = (val>>16)&0xff;
		*buf_ptr++ = (val>>24)&0xff;
	};
	
	virtual void write4high(uint32 val)
	{
		*buf_ptr++ = (val>>24)&0xff;
		*buf_ptr++ = (val>>16)&0xff;
		*buf_ptr++ = (val>>8) & 0xff;
		*buf_ptr++ = val & 0xff;
	};

	virtual void writef(float val)
	{
		uint_float	uif;
		uif.f = val;
		*buf_ptr++ = uif.i & 0xff;
		*buf_ptr++ = (uif.i>>8) & 0xff;
		*buf_ptr++ = (uif.i>>16)&0xff;
		*buf_ptr++ = (uif.i>>24)&0xff;
	};
	
	virtual void write(char *b, int len)
	{
		memcpy(buf_ptr, b, len);
		buf_ptr += len;
	};
	
	virtual void seek(unsigned int pos) { buf_ptr = const_cast<unsigned char *>(buf)+pos; };
	
	virtual void skip(int pos) { buf_ptr += pos; };
	
	virtual unsigned int getSize() { return size; };
	
	virtual unsigned int getPos() { return (buf_ptr-buf); };
	
	unsigned char *getPtr() { return buf_ptr; };
};


#endif
