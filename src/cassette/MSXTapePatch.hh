// $Id$

#ifndef __MSXTapePatch_HH__
#define __MSXTapePatch_HH__

#include "MSXRomPatchInterface.hh"
#include "Command.hh"
#include "CommandLineParser.hh"

class File;
class FileContext;


class MSXCasCLI : public CLIOption, public CLIFileType
{
	public:
		MSXCasCLI();
		virtual void parseOption(const string &option,
				list<string> &cmdLine);
		virtual const string& optionHelp() const;
		virtual void parseFileType(const string &filename);
		virtual const string& fileTypeHelp() const;
};


class MSXTapePatch : public MSXRomPatchInterface, private Command
{
	public:
		MSXTapePatch();
		virtual ~MSXTapePatch();

		virtual void patch(CPU::CPURegs& regs);

	private:
		File* file;

		void insertTape(FileContext *context,
		                const string &filename);
		void ejectTape();

		// 0x00E1 Tape input ON
		void TAPION(CPU::CPURegs& R);

		// 0x00E4 Tape input
		void TAPIN (CPU::CPURegs& R);

		// 0x00E7 Tape input OFF
		void TAPIOF(CPU::CPURegs& R);

		// 0x00EA Tape output ON
		void TAPOON(CPU::CPURegs& R);

		// 0x00ED Tape output
		void TAPOUT(CPU::CPURegs& R);

		// 0x00F0 Tape output OFF
		void TAPOOF(CPU::CPURegs& R);

		// 0x00F3 Turn motor ON/OFF
		void STMOTR(CPU::CPURegs& R);

		// Tape Command
		virtual void execute(const vector<string> &tokens);
		virtual void help   (const vector<string> &tokens) const;
		virtual void tabCompletion(vector<string> &tokens) const;
};

#endif // __MSXTapePatch_HH__
