// $Id$

// This code implements the functionality of my older msxtar program
// that could manipulate files and directories on dsk and ide-hd images
// Integrating it is seen as temporary bypassing of the need for a
// DirAsDisk2 that supports subdirs, partitions etc. since this class will
// of those functionalities although not on a dynamic base

#ifndef MSXTAR_HH
#define MSXTAR_HH

#include "openmsx.hh"
#include <string>

namespace openmsx {

class SectorBasedDisk;

class MSXtar
{
public: 
	MSXtar(SectorBasedDisk& sectordisk);
	void format();

private:
	struct MSXBootSector {
		byte jumpcode[3];	// 0xE5 to bootprogram
		byte name[8];
		byte bpsector[2];	// bytes per sector (always 512)
		byte spcluster[1];	// sectors per cluster (always 2)
		byte reservedsectors[2];// amount of non-data sectors (ex bootsector)
		byte nrfats[1];		// number of fats
		byte direntries[2];	// max number of files in root directory
		byte nrsectors[2];	// number of sectors on this disk
		byte descriptor[1];	// media descriptor
		byte sectorsfat[2];	// sectors per FAT
		byte sectorstrack[2];	// sectors per track
		byte nrsides[2];	// number of sides
		byte hiddensectors[2];	// not used
		byte bootprogram[512-30];// actual bootprogram
	};

	struct MSXDirEntry {
		byte filename[8];
		byte ext[3];
		byte attrib;
		byte reserved[10];	// unused
		byte time[2];
		byte date[2];
		byte startcluster[2];
		byte size[4];
	};

	//Modified struct taken over from Linux' fdisk.h
	struct partition {
		byte boot_ind;         // 0x80 - active
		byte head;             // starting head
		byte sector;           // starting sector
		byte cyl;              // starting cylinder
		byte sys_ind;          // What partition type
		byte end_head;         // end head
		byte end_sector;       // end sector
		byte end_cyl;          // end cylinder
		byte start4[4];        // starting sector counting from 0
		byte size4[4];         // nr of sectors in partition
	};


	static const word EOF_FAT = 0x0FFF; // signals EOF in FAT12
	static const int SECTOR_SIZE = 512;

	static const byte T_MSX_REG  = 0x00; // Normal file
	static const byte T_MSX_READ = 0x01; // Read-Only file
	static const byte T_MSX_HID  = 0x02; // Hidden file
	static const byte T_MSX_SYS  = 0x04; // System file
	static const byte T_MSX_VOL  = 0x08; // filename is Volume Label
	static const byte T_MSX_DIR  = 0x10; // entry is a subdir
	static const byte T_MSX_ARC  = 0x20; // Archive bit

	struct physDirEntry {
		int sector;
		byte index;
	};

	std::string MSXrootdir;
	std::string MSXhostdir;
	std::string inputFile;
	std::string outputFile;
	int nbSectors;
	int maxCluster;
	int sectorsPerCluster;
	int sectorsPerTrack;
	int sectorsPerFat;
	int nbFats;
	int nbSides;
	byte nbSectorsPerCluster;
	int nbRootDirSectors ;
	int rootDirStart; // first sector from the root directory
	int rootDirEnd;   // last sector from the root directory
	int MSXchrootSector;
	int MSXchrootStartIndex;
	int MSXpartition;
	bool do_extract;
	bool do_subdirs;
	bool do_singlesided;
	bool touch_option;
	bool keep_option;
	bool msxdir_option;
	bool msxpart_option;
	bool msx_allpart;
	bool do_fat16;
	const byte* defaultBootBlock;
	SectorBasedDisk& disk;

	int clusterToSector(int cluster);
	void setBootSector(byte* buf,word nbsectors);
	word sectorToCluster(int sector);
	void readBootSector(byte* buf);
};

} // namespace openmsx

#endif
