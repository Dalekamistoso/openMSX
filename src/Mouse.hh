// $Id$

#ifndef __MOUSE_HH__
#define __MOUSE_HH__

#include "JoystickDevice.hh"
#include "EventDistributor.hh"
#include <SDL/SDL.h>


class Mouse : public JoystickDevice, EventListener
{
	public:
		Mouse();
		virtual ~Mouse();
		
		//Pluggable
		const std::string &getName();
		
		//JoystickDevice
		byte read(const EmuTime &time);
		void write(byte value, const EmuTime &time);
	
		//EventListener
		void signalEvent(SDL_Event &event);

	private:
		static const int SCALE = 2;
		static const int JOY_BUTTONA = 0x10;
		static const int JOY_BUTTONB = 0x20;
		static const int FAZE_XHIGH = 0;
		static const int FAZE_XLOW  = 1;
		static const int FAZE_YHIGH = 2;
		static const int FAZE_YLOW  = 3;
		static const int STROBE = 0x04;

		static const std::string name;

		byte status;
		int faze;
		int xrel, yrel;
		int curxrel, curyrel;
};
#endif
