#include <string.h>
#include <stdlib.h>

#include "../Dependencies/BitIO/libBitIO/include/CommandLineInterface.h"
#include "../Dependencies/BitIO/libBitIO/include/BitIO.h"
#include "../libModernAVC/include/libModernAVC.h"

#define ModernAVCVersion "0.1.0"

#ifdef __cplusplus
extern "C" {
#endif
    
    void ExtractAVCProfileFromCLI(CommandLineInterface *CLI) {
        // Profile option = 7
        const char *ProfileString = GetCLIArgumentResult(CLI, 7);
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
    
    CommandLineInterface *SetModernAVCOptions(void) {
        CommandLineInterface *CLI = InitCommandLineInterface(7);
        
        SetCLIName(CLI, "ModernAVC");
        SetCLIVersion(CLI, ModernAVCVersion);
        SetCLIAuthor(CLI, "BumbleBritches57");
        SetCLICopyright(CLI, "2017-2017");
        SetCLIDescription(CLI, "AVC encoder/decoder written from scratch in modern C");
        SetCLILicense(CLI, "Revised BSD (3 clause)", false);
        SetCLILicenseURL(CLI, "https://opensource.org/licenses/BSD-3-Clause", false);
        SetCLIMinSwitches(CLI, 3);
        
        SetCLISwitchFlag(CLI, 0, "Input", 5);
        SetCLISwitchDescription(CLI, 0, "Input file or stdin with: -");
        SetCLISwitchResultStatus(CLI, 0, true);
        
        SetCLISwitchFlag(CLI, 1, "Output", 6);
        SetCLISwitchDescription(CLI, 1, "Output file or stdout with: -");
        SetCLISwitchResultStatus(CLI, 1, true);
        
        /* Start Encode options */
        SetCLISwitchFlag(CLI, 2, "Encode", 6);
        SetCLISwitchDescription(CLI, 2, "Encode input to AVC");
        SetCLISwitchResultStatus(CLI, 2, false);
        
        SetCLISwitchFlag(CLI, 3, "Bitrate", 7);
        SetCLISwitchDescription(CLI, 3, "Target bitrate for the produced AVC file, supported postfixes: MBps, KBps (mega bits, kilo bits (1024))");
        SetCLISwitchResultStatus(CLI, 3, true);
        SetCLISwitchMetaFlag(CLI, 3, 2);
        
        SetCLISwitchFlag(CLI, 4, "Subsample", 9);
        SetCLISwitchDescription(CLI, 4, "Should the produced AVC file use chroma subsampling? if so, what type");
        SetCLISwitchResultStatus(CLI, 4, true);
        SetCLISwitchMetaFlag(CLI, 4, 2);
        
        SetCLISwitchFlag(CLI, 5, "Framerate", 9);
        SetCLISwitchDescription(CLI, 5, "the framerate of the movie, for decimal fpses, use fractional notation IE: 24000/1001");
        SetCLISwitchResultStatus(CLI, 5, true);
        SetCLISwitchMetaFlag(CLI, 5, 2);
        
        SetCLISwitchFlag(CLI, 6, "Profile", 9);
        SetCLISwitchDescription(CLI, 6, "the level to encode the movie with, E.G.: 5.2");
        SetCLISwitchResultStatus(CLI, 6, true);
        SetCLISwitchMetaFlag(CLI, 6, 2);
        
        SetCLISwitchFlag(CLI, 7, "Interlace", 9);
        SetCLISwitchDescription(CLI, 7, "Should the movie be interlaced?");
        SetCLISwitchResultStatus(CLI, 7, false);
        SetCLISwitchMetaFlag(CLI, 7, 2);
        
        SetCLISwitchFlag(CLI, 8, "Lossless", 8);
        SetCLISwitchDescription(CLI, 8, "Encode the AVC file losslessly and only uses lossless color transforms like YCgCo");
        SetCLISwitchResultStatus(CLI, 8, false);
        SetCLISwitchMetaFlag(CLI, 8, 2);
        /* End encode options */
        
        /* Start Decode options */
        SetCLISwitchFlag(CLI, 9, "Decode", 6);
        SetCLISwitchDescription(CLI, 9, "Decode AVC to output");
        SetCLISwitchResultStatus(CLI, 9, false);
        
        SetCLISwitchFlag(CLI, 10, "ExtractFrame", 6);
        SetCLISwitchDescription(CLI, 10, "Extracts frame (frame number, or timestamp in HH:MM:SS:Frame format)");
        SetCLISwitchResultStatus(CLI, 10, false);
        SetCLISwitchMetaFlag(CLI, 10, 9);
        
        SetCLISwitchFlag(CLI, 11, "TrimFrames", 6);
        SetCLISwitchDescription(CLI, 11, "Removes frames in format FirstFrame..LastFrame (Where Frame is either the frame numbers, or a timestamp in HH:MM:SS:Frame format)");
        SetCLISwitchResultStatus(CLI, 11, false);
        SetCLISwitchMetaFlag(CLI, 11, 9);
        /* End Decode options */
        
        SetCLISwitchFlag(CLI, 12, "Help", 4);
        SetCLISwitchDescription(CLI, 12, "Prints all the command line options");
        SetCLISwitchResultStatus(CLI, 12, false);
        
        return CLI;
    }
    
    int main(int argc, const char * argv[]) {
        CommandLineInterface *CLI  = SetModernAVCOptions();
        BitInput           *BitI = InitBitInput();
        BitOutput          *BitO = InitBitOutput();
        
        BitBuffer          *InputBitB = InitBitBuffer();
        BitBuffer          *OutputBitB = InitBitBuffer();
        
        ParseCommandLineArguments(CLI, argc, argv);
        
        if (GetCLISwitchPresence(CLI, 2)) { // Encode
            
        } else if (GetCLISwitchPresence(CLI, 3)) { // Decode
            
        } else if (GetCLISwitchPresence(CLI, 4)) { // Bitrate
            
        } else if (GetCLISwitchPresence(CLI, 5)) { // Subsampling
            
        } else if (GetCLISwitchPresence(CLI, 6)) { // Framerate
            
        } else if (GetCLISwitchPresence(CLI, 7)) { // Profile
            
        } else if (GetCLISwitchPresence(CLI, 8)) { // Interlacing
            
        } else if (GetCLISwitchPresence(CLI, 9)) { // Lossless
            
        } else if (GetCLISwitchPresence(CLI, 10)) { // Help
            
        }
        
        if (GetCLISwitchPresence(CLI, 0)) { // Input
            
        } else if (GetCLISwitchPresence(CLI, 1)) { // Output
            
        }
        
        CloseCommandLineInterface(CLI);
        CloseBitInput(BitI);
        CloseBitOutput(BitO);
        CloseBitBuffer(InputBitB);
        CloseBitBuffer(OutputBitB);
        
        return EXIT_SUCCESS;
    }
    
#ifdef __cplusplus
}
#endif
