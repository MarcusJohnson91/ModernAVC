#include <string.h>
#include <stdlib.h>

#include "../Dependencies/ModernPNG/Dependencies/libPCM/Dependencies/BitIO/libBitIO/include/CommandLineIO.h"

#include "../libModernAVC/include/libModernAVC.h"

#define ModernAVCVersion "0.1.0"

#ifdef __cplusplus
extern "C" {
#endif
    
    enum ModerAVCCommandLineSwitches {
        Input        = 0,
        Output       = 1,
        LeftEye      = 2,
        RightEye     = 3,
        Encode       = 4,
        Lossless     = 5,
        BitRate      = 6,
        SubSample    = 7,
        FrameRate    = 8,
        Profile      = 9,
        Interlace    = 10,
        Decode       = 11,
        ExtractFrame = 12,
        TrimFrames   = 13,
        Help         = 14,
        LogFile      = 15,
    };
    
    void ExtractAVCProfileFromCLI(CommandLineIO *CLI) {
        // Profile option = 7
        const char *ProfileString = GetCLIArgumentResult(CLI, Profile);
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
    
    
    
    CommandLineIO *SetModernAVCOptions(void) {
        CommandLineIO *CLI = InitCommandLineIO(16);
        
        SetCLIName(CLI, "ModernAVC");
        SetCLIVersion(CLI, ModernAVCVersion);
        SetCLIAuthor(CLI, "BumbleBritches57");
        SetCLICopyright(CLI, "2017 - 2017");
        SetCLIDescription(CLI, "AVC encoder/decoder written from scratch in modern C");
        SetCLILicense(CLI, "Revised BSD", "Open source license", false);
        SetCLILicenseURL(CLI, "https://opensource.org/licenses/BSD-3-Clause");
        SetCLIMinSwitches(CLI, 3);
        
        SetCLISwitchFlag(CLI, Input, "Input", 5);
        SetCLISwitchDescription(CLI, Input, "Input file or stdin with: -");
        SetCLISwitchResultStatus(CLI, Input, true);
        SetCLISwitchAsMain(CLI, Input, true);
        
        SetCLISwitchFlag(CLI, Output, "Output", 6);
        SetCLISwitchDescription(CLI, Output, "Output file or stdout with: -");
        SetCLISwitchResultStatus(CLI, Output, true);
        SetCLISwitchAsMain(CLI, Output, true);
        
        SetCLISwitchFlag(CLI, LeftEye, "LeftEye", 7);
        SetCLISwitchDescription(CLI, LeftEye, "The left view for encoding or decoding");
        SetCLISwitchAsChild(CLI, Input, LeftEye);
        SetCLISwitchAsChild(CLI, Output, LeftEye);
        
        SetCLISwitchFlag(CLI, RightEye, "RightEye", 8);
        SetCLISwitchDescription(CLI, RightEye, "The right view for encoding or decoding");
        SetCLISwitchAsChild(CLI, Input, RightEye);
        SetCLISwitchAsChild(CLI, Output, RightEye);
        
        
        /* Start Encode options */
        SetCLISwitchFlag(CLI, Encode, "Encode", 6);
        SetCLISwitchDescription(CLI, Encode, "Encode input to AVC");
        SetCLISwitchResultStatus(CLI, Encode, false);
        SetCLISwitchAsMain(CLI, Encode, true);
        
        SetCLISwitchFlag(CLI, Lossless, "Lossless", 8);
        SetCLISwitchDescription(CLI, Lossless, "Encode the AVC file losslessly and only uses lossless color transforms like YCgCo");
        SetCLISwitchResultStatus(CLI, Lossless, false);
        SetCLISwitchAsChild(CLI, Encode, Lossless);
        
        SetCLISwitchFlag(CLI, BitRate, "BitRate", 7);
        SetCLISwitchDescription(CLI, BitRate, "Target bitrate for the produced AVC file, supported postfixes: MBps, KBps (mega bits, kilo bits (1024))");
        SetCLISwitchResultStatus(CLI, BitRate, true);
        SetCLISwitchMetaFlag(CLI, BitRate, 2);
        SetCLISwitchAsChild(CLI, Encode, BitRate);
        
        SetCLISwitchFlag(CLI, SubSample, "SubSample", 9);
        SetCLISwitchDescription(CLI, SubSample, "Should the produced AVC file use chroma subsampling? if so, what type");
        SetCLISwitchResultStatus(CLI, SubSample, true);
        SetCLISwitchAsChild(CLI, Encode, SubSample);
        
        SetCLISwitchFlag(CLI, FrameRate, "FrameRate", 9);
        SetCLISwitchDescription(CLI, FrameRate, "the framerate of the movie, for decimal fpses, use fractional notation IE: 24000/1001");
        SetCLISwitchResultStatus(CLI, FrameRate, true);
        SetCLISwitchAsChild(CLI, Encode, FrameRate);
        
        SetCLISwitchFlag(CLI, Profile, "Profile", 9);
        SetCLISwitchDescription(CLI, Profile, "the level to encode the movie with, E.G.: 5.2");
        SetCLISwitchResultStatus(CLI, Profile, true);
        SetCLISwitchAsChild(CLI, Encode, Profile);
        
        SetCLISwitchFlag(CLI, Interlace, "Interlace", 9);
        SetCLISwitchDescription(CLI, Interlace, "Should the movie be interlaced?");
        SetCLISwitchResultStatus(CLI, Interlace, false);
        SetCLISwitchAsChild(CLI, Encode, Interlace);
        /* End encode options */
        
        /* Start Decode options */
        SetCLISwitchFlag(CLI, Decode, "Decode", 6);
        SetCLISwitchDescription(CLI, Decode, "Decode AVC to output");
        SetCLISwitchResultStatus(CLI, Decode, false);
        SetCLISwitchAsMain(CLI, Decode, true);
        
        SetCLISwitchFlag(CLI, ExtractFrame, "ExtractFrame", 6);
        SetCLISwitchDescription(CLI, ExtractFrame, "Extracts frame (frame number, or timestamp in HH:MM:SS:Frame format)");
        SetCLISwitchResultStatus(CLI, ExtractFrame, false);
        SetCLISwitchAsChild(CLI, Decode, ExtractFrame);
        
        SetCLISwitchFlag(CLI, TrimFrames, "TrimFrames", 6);
        SetCLISwitchDescription(CLI, TrimFrames, "Removes frames in format FirstFrame..LastFrame (Where Frame is either the frame numbers, or a timestamp in HH:MM:SS:Frame format)");
        SetCLISwitchResultStatus(CLI, TrimFrames, false);
        SetCLISwitchAsChild(CLI, Decode, TrimFrames);
        /* End Decode options */
        
        SetCLISwitchFlag(CLI, Help, "Help", 4);
        SetCLISwitchDescription(CLI, Help, "Prints all the command line options");
        SetCLISwitchResultStatus(CLI, Help, false);
        SetCLISwitchAsMain(CLI, Help, true);
        
        SetCLISwitchFlag(CLI, LogFile, "LogFile", 4);
        SetCLISwitchDescription(CLI, LogFile, "Prints all the command line options");
        SetCLISwitchResultStatus(CLI, LogFile, true);
        SetCLISwitchAsMain(CLI, LogFile, true);
        
        return CLI;
    }
    
    int main(int argc, const char *argv[]) {
        CommandLineIO *CLI  = SetModernAVCOptions();
        BitInput           *BitI = InitBitInput();
        BitOutput          *BitO = InitBitOutput();
        
        BitBuffer          *InputBitB = InitBitBuffer(64); // 64 is pure guess work.
        BitBuffer          *OutputBitB = InitBitBuffer(64);
        
        ParseCommandLineArguments(CLI, argc, argv);
        
        if (GetCLISwitchPresence(CLI, Encode)) { // Encode
            
        } else if (GetCLISwitchPresence(CLI, Decode)) { // Decode
            
        } else if (GetCLISwitchPresence(CLI, BitRate)) { // Bitrate
            
        } else if (GetCLISwitchPresence(CLI, SubSample)) { // Subsampling
            
        } else if (GetCLISwitchPresence(CLI, FrameRate)) { // Framerate
            
        } else if (GetCLISwitchPresence(CLI, Profile)) { // Profile
            
        } else if (GetCLISwitchPresence(CLI, Interlace)) { // Interlacing
            
        } else if (GetCLISwitchPresence(CLI, Lossless)) { // Lossless
            
        } else if (GetCLISwitchPresence(CLI, Help)) { // Help
            
        } else if (GetCLISwitchPresence(CLI, LogFile)) {
            
        }
        
        if (GetCLISwitchPresence(CLI, Input)) { // Input
            
        } else if (GetCLISwitchPresence(CLI, Output)) { // Output
            
        }
        
        DeinitCommandLineIO(CLI);
        DeinitBitInput(BitI);
        DeinitBitOutput(BitO);
        DeinitBitBuffer(InputBitB);
        DeinitBitBuffer(OutputBitB);
        
        return EXIT_SUCCESS;
    }
    
#ifdef __cplusplus
}
#endif
