// $Id$

#include "DACSound8U.hh"


DACSound8U::DACSound8U(const string &name, short maxVolume,
                       const EmuTime &time)
	: DACSound16S(name, maxVolume, time)
{
}

DACSound8U::~DACSound8U()
{
}

void DACSound8U::writeDAC(byte value, const EmuTime &time)
{
	DACSound16S::writeDAC(((short)value - 0x80) << 8, time);
}
