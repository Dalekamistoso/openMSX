// $Id$

#ifndef __MSXTapePatch_HH__
#define __MSXTapePatch_HH__

#include "openmsx.hh"
#include "MSXRomPatchInterface.hh"
#include "msxconfig.hh"
#include "config.h"

#include <string>
#include "CPU.hh"
#include <iostream>
#include <fstream>


#ifdef HAVE_FSTREAM_TEMPL
#define FILETYPE std::fstream<byte>
#else
#define FILETYPE std::fstream
#endif

class MSXTapePatch: public MSXRomPatchInterface
{
	public:
		MSXTapePatch();
		virtual ~MSXTapePatch();

		virtual void patch() const;
	
	private:
		// TApeHeader used to be fMSX compatible
		static const byte TapeHeader[] = { 0x1F,0xA6,0xDE,0xBA,0xCC,0x13,0x7D,0x74 };
		FILETYPE* file;

		void insertTape(std::string filename);

		// 0x00E1 Tape input ON
		void TAPION() const;

		// 0x00E4 Tape input
		void TAPIN() const;

		// 0x00E7 Tape input OFF
		void TAPIOF() const;

		// 0x00EA Tape output ON
		void TAPOON() const;

		// 0x00ED Tape output
		void TAPOUT() const;

		// 0x00F0 Tape output OFF
		void TAPOOF() const;

		// 0x00F3 Turn motor ON/OFF
		void STMOTR() const;

};

#endif // __MSXTapePatch_HH__
/*
 TODO: Decided what to do with following variables
 
 FCA4H LOWLIM: DEFB 31H

 This variable is used to hold the minimum allowable start bit
 duration as determined by the TAPION standard routine.

 FCA5H WINWID: DEFB 22H

 This variable is used to hold the LO/HI cycle discrimination
 duration as determined by the TAPION standard routine.
*/
