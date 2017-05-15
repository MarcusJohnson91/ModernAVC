#include "../Dependencies/BitIO/libBitIO/include/BitIO.h"

#include "../libModernAVC/include/libModernAVC.h"

#define ModernAVCVersion "0.1.0"

#ifdef __cplusplus
extern "C" {
#endif
    
    CommandLineOptions *SetModernAVCOptions(void) {
        CommandLineOptions *CMD = InitCommandLineOptions(7);
        
        SetCMDName(CMD, "ModernAVC");
        SetCMDVersion(CMD, ModernAVCVersion);
        SetCMDAuthor(CMD, "BumbleBritches57");
        SetCMDCopyright(CMD, "2017-2017");
        SetCMDDescription(CMD, "AVC encoder/decoder written from scratch in modern C");
        SetCMDLicense(CMD, "Revised BSD (3 clause)", false);
        SetCMDLicenseURL(CMD, "https://opensource.org/licenses/BSD-3-Clause", false);
        SetCMDMinSwitches(CMD, 3);
        
        SetCMDSwitchFlag(CMD, 0, "Input", 5);
        SetCMDSwitchDescription(CMD, 0, "Input file or stdin with: -");
        SetCMDSwitchResultStatus(CMD, 0, true);
        
        SetCMDSwitchFlag(CMD, 1, "Output", 6);
        SetCMDSwitchDescription(CMD, 1, "Output file or stdout with: -");
        SetCMDSwitchResultStatus(CMD, 1, true);
        
        SetCMDSwitchFlag(CMD, 2, "Encode", 6);
        SetCMDSwitchDescription(CMD, 2, "Encode input to AVC");
        SetCMDSwitchResultStatus(CMD, 2, false);
        
        SetCMDSwitchFlag(CMD, 3, "Decode", 6);
        SetCMDSwitchDescription(CMD, 3, "Decode AVC to output");
        SetCMDSwitchResultStatus(CMD, 3, false);
        
        SetCMDSwitchFlag(CMD, 4, "Resolution", 10);
        SetCMDSwitchDescription(CMD, 4, "Resolution in WidthxHeight format");
        SetCMDSwitchResultStatus(CMD, 4, true);
        
        SetCMDSwitchFlag(CMD, 5, "Bitrate", 7);
        SetCMDSwitchDescription(CMD, 5, "Target bitrate for the produced AVC file, supported postfixes: MBps, KBps (mega bits, kilo bits (1024))");
        SetCMDSwitchResultStatus(CMD, 5, true);
        
        SetCMDSwitchFlag(CMD, 6, "Subsample", 9);
        SetCMDSwitchDescription(CMD, 6, "Should the produced AVC file use chroma subsampling? if so, what type");
        SetCMDSwitchResultStatus(CMD, 6, true);
        
        SetCMDSwitchFlag(CMD, 7, "Framerate", 9);
        SetCMDSwitchDescription(CMD, 7, "the framerate of the movie, for decimal fpses, use fractional notation IE: 24000/1001");
        SetCMDSwitchResultStatus(CMD, 7, true);
        
        SetCMDSwitchFlag(CMD, 8, "Profile", 9);
        SetCMDSwitchDescription(CMD, 8, "the level to encode the movie with, IE: 5.2");
        SetCMDSwitchResultStatus(CMD, 8, true);
        
        SetCMDSwitchFlag(CMD, 9, "Interlace", 9);
        SetCMDSwitchDescription(CMD, 9, "Should the movie be interlaced?");
        SetCMDSwitchResultStatus(CMD, 9, false);
        
        SetCMDSwitchFlag(CMD, 10, "Lossless", 8);
        SetCMDSwitchDescription(CMD, 10, "Encode the AVC file losslessly and only uses lossless color transforms like YCgCo");
        SetCMDSwitchResultStatus(CMD, 10, false);
        
        SetCMDSwitchFlag(CMD, 11, "Help", 4);
        SetCMDSwitchDescription(CMD, 11, "Prints all the command line options");
        SetCMDSwitchResultStatus(CMD, 11, false);
        
        // Switch 6 is NULL, aka the auto Help option. Fuck it, the user will just have to code that themselves.
        
        return CMD;
    }
    
    int main(int argc, const char * argv[]) {
        CommandLineOptions *CMD  = SetModernAVCOptions();
        BitInput           *BitI = InitBitInput();
        BitOutput          *BitO = InitBitOutput();
        
        BitBuffer          *InputBitB = InitBitBuffer();
        BitBuffer          *OutputBitB = InitBitBuffer();
        
        // We should add a function to BitIO that can tell us if an input command is a network address or a file.
        
        ParseCommandLineArguments(CMD, argc, argv);
        if        (GetCMDSwitchPresence(CMD, 2) == true) {
            // Split string into resolution.
        } else if (GetCMDSwitchPresence(CMD, 3) == true) { // Encode
            EncodeAVC     *Enc   = InitEncodeAVC();
            AVCEncodeImage(Enc, BitO);
        } else if (GetCMDSwitchPresence(CMD, 4) == true) { // Decode
            DecodeAVC     *Dec   = InitDecodeAVC();
            AVCDecodeImage(InputBitB, Dec, NULL);
        }
        
        CloseCommandLineOptions(CMD);
        
        return EXIT_SUCCESS;
    }
    
#ifdef __cplusplus
}
#endif
