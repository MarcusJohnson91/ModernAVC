#include <string.h>
#include <math.h>

#include "../Dependencies/BitIO/libBitIO/include/BitIO.h"
#include "../libModernAVC/include/libModernAVC.h"

#define ModernAVCVersion "0.1.0"

#ifdef __cplusplus
extern "C" {
#endif
    
    void ExtractAVCProfileFromCMD(CommandLineOptions *CMD) {
        // Profile option = 7
        const char *ProfileString = GetCMDSwitchResult(CMD, 7);
        // Now use strsplit to get the 2 halves on either side of the decimal.
        // then use atoi to get the digit into a number
        
        float Profile        = atof(ProfileString);
        uint8_t ProfileMajor = (uint8_t)Profile;
        uint8_t ProfileMinor = Profile - ProfileMajor;
        /*
        char *ProfileMajorString  = strsep(ProfileString, ".");
        char *ProfileMinorString  = strsep(ProfileString, ".");
         */
    }
    
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
        
        /* Start Encode options */
        SetCMDSwitchFlag(CMD, 2, "Encode", 6);
        SetCMDSwitchDescription(CMD, 2, "Encode input to AVC");
        SetCMDSwitchResultStatus(CMD, 2, false);
        
        SetCMDSwitchFlag(CMD, 3, "Bitrate", 7);
        SetCMDSwitchDescription(CMD, 3, "Target bitrate for the produced AVC file, supported postfixes: MBps, KBps (mega bits, kilo bits (1024))");
        SetCMDSwitchResultStatus(CMD, 3, true);
        SetCMDSwitchDependency(CMD, 3, 2);
        
        SetCMDSwitchFlag(CMD, 4, "Subsample", 9);
        SetCMDSwitchDescription(CMD, 4, "Should the produced AVC file use chroma subsampling? if so, what type");
        SetCMDSwitchResultStatus(CMD, 4, true);
        SetCMDSwitchDependency(CMD, 4, 2);
        
        SetCMDSwitchFlag(CMD, 5, "Framerate", 9);
        SetCMDSwitchDescription(CMD, 5, "the framerate of the movie, for decimal fpses, use fractional notation IE: 24000/1001");
        SetCMDSwitchResultStatus(CMD, 5, true);
        SetCMDSwitchDependency(CMD, 5, 2);
        
        SetCMDSwitchFlag(CMD, 6, "Profile", 9);
        SetCMDSwitchDescription(CMD, 6, "the level to encode the movie with, E.G.: 5.2");
        SetCMDSwitchResultStatus(CMD, 6, true);
        SetCMDSwitchDependency(CMD, 6, 2);
        
        SetCMDSwitchFlag(CMD, 7, "Interlace", 9);
        SetCMDSwitchDescription(CMD, 7, "Should the movie be interlaced?");
        SetCMDSwitchResultStatus(CMD, 7, false);
        SetCMDSwitchDependency(CMD, 7, 2);
        
        SetCMDSwitchFlag(CMD, 8, "Lossless", 8);
        SetCMDSwitchDescription(CMD, 8, "Encode the AVC file losslessly and only uses lossless color transforms like YCgCo");
        SetCMDSwitchResultStatus(CMD, 8, false);
        SetCMDSwitchDependency(CMD, 8, 2);
        /* End encode options */
        
        /* Start Decode options */
        SetCMDSwitchFlag(CMD, 9, "Decode", 6);
        SetCMDSwitchDescription(CMD, 9, "Decode AVC to output");
        SetCMDSwitchResultStatus(CMD, 9, false);
        
        SetCMDSwitchFlag(CMD, 10, "ExtractFrame", 6);
        SetCMDSwitchDescription(CMD, 10, "Extracts frame (frame number, or timestamp in HH:MM:SS:Frame format)");
        SetCMDSwitchResultStatus(CMD, 10, false);
        SetCMDSwitchDependency(CMD, 10, 9);
        
        SetCMDSwitchFlag(CMD, 11, "TrimFrames", 6);
        SetCMDSwitchDescription(CMD, 11, "Removes frames in format FirstFrame..LastFrame (Where Frame is either the frame numbers, or a timestamp in HH:MM:SS:Frame format)");
        SetCMDSwitchResultStatus(CMD, 11, false);
        SetCMDSwitchDependency(CMD, 11, 9);
        /* End Decode options */
        
        SetCMDSwitchFlag(CMD, 12, "Help", 4);
        SetCMDSwitchDescription(CMD, 12, "Prints all the command line options");
        SetCMDSwitchResultStatus(CMD, 12, false);
        
        return CMD;
    }
    
    int main(int argc, const char * argv[]) {
        CommandLineOptions *CMD  = SetModernAVCOptions();
        BitInput           *BitI = InitBitInput();
        BitOutput          *BitO = InitBitOutput();
        
        BitBuffer          *InputBitB = InitBitBuffer();
        BitBuffer          *OutputBitB = InitBitBuffer();
        
        ParseCommandLineArguments(CMD, argc, argv);
        
        if (GetCMDSwitchPresence(CMD, 2)) { // Encode
            
        } else if (GetCMDSwitchPresence(CMD, 3)) { // Decode
            
        } else if (GetCMDSwitchPresence(CMD, 4)) { // Bitrate
            
        } else if (GetCMDSwitchPresence(CMD, 5)) { // Subsampling
            
        } else if (GetCMDSwitchPresence(CMD, 6)) { // Framerate
            
        } else if (GetCMDSwitchPresence(CMD, 7)) { // Profile
            
        } else if (GetCMDSwitchPresence(CMD, 8)) { // Interlacing
            
        } else if (GetCMDSwitchPresence(CMD, 9)) { // Lossless
            
        } else if (GetCMDSwitchPresence(CMD, 10)) { // Help
            
        }
        
        if (GetCMDSwitchPresence(CMD, 0)) { // Input
            
        } else if (GetCMDSwitchPresence(CMD, 1)) { // Output
            
        }
        
        CloseCommandLineOptions(CMD);
        CloseBitInput(BitI);
        CloseBitOutput(BitO);
        CloseBitBuffer(InputBitB);
        CloseBitBuffer(OutputBitB);
        
        return EXIT_SUCCESS;
    }
    
#ifdef __cplusplus
}
#endif
