// $Id$

#ifndef __JOYSTICKPORTS_HH__
#define __JOYSTICKPORTS_HH__

#include "openmsx.hh"
#include "Connector.hh"

// forward declaration
class JoystickDevice;
class Mouse;
class Joystick;


class JoystickPort : public Connector
{
public:
	JoystickPort(const std::string &name, const EmuTime &time);
	virtual ~JoystickPort();

	virtual std::string getName();
	virtual std::string getClass();
	virtual void plug(Pluggable *device, const EmuTime &time);
	virtual void unplug(const EmuTime &time);

	byte read(const EmuTime &time);
	void write(byte value, const EmuTime &time);

private:
	std::string name;
	static std::string className;

	byte lastValue;
};

class JoystickPorts
{
	public:
		JoystickPorts(const EmuTime &time);
		~JoystickPorts();

		byte read(const EmuTime &time);
		void write(byte value, const EmuTime &time);

	private:
		int selectedPort;
		JoystickPort* ports[2];
};
#endif
