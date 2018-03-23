#include <string.h>
#include <stdlib.h>

#include "../Dependencies/ModernPNG/Dependencies/libPCM/Dependencies/FoundationIO/libFoundationIO/include/CommandLineIO.h"

#include "../libModernAVC/include/libModernAVC.h"
#include "../libModernAVC/include/Private/Encode/libModernAVC_SetEncodeOptions.h"

#define ModernAVCVersion "0.1.0"

#ifdef __cplusplus
extern "C" {
#endif
    
    enum ModerAVCCommandLineSwitches {
        /* General Options */
        Input        = 0,
        Output       = 1,
        LogFile      = 2,
        LeftEye      = 3,
        RightEye     = 4,
        /* Encode Options */
        Encode       = 5,
        Lossless     = 6,
        BitRate      = 7,
        SubSample    = 8,
        FrameRate    = 9,
        Profile      = 10,
        Interlace    = 11,
        /* Decode Options */
        Decode       = 12,
        ExtractFrame = 13,
        TrimFrames   = 14,
        /* Help Option */
        Help         = 15,
    };
    
    void ExtractAVCProfileFromCLI(CommandLineIO *CLI, EncodeAVC *Enc) { // Ok, well the seperator will be the decimal, and we'll just use the period as a seperator
        // Profile option = 7
        uint64_t ProfileArg = GetCLIArgumentNumFromSwitchNum(CLI, Profile);
     	char *ProfileString = GetCLIArgumentResult(CLI, ProfileArg);
        // Now use strsplit to get the 2 halves on either side of the decimal.
        // then use atoi to get the digit into a number
        
        char *ProfileMajorString = strtok(ProfileString, ".");
        char *ProfileMinorString = strtok(NULL, ".");
        
        SetAVCEncodeProfile(Enc, atoll(ProfileMajorString), atoll(ProfileMinorString));
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
        SetCLILicense(CLI, "Revised BSD", "Permissive, open source", "https://opensource.org/licenses/BSD-3-Clause", false);
        SetCLIMinSwitches(CLI, 3);
        
        SetCLISwitchFlag(CLI, Input, "Input");
        SetCLISwitchDescription(CLI, Input, "Input file or stdin with: -");
        SetCLISwitchResultStatus(CLI, Input, true);
        SetCLISwitchAsMaster(CLI, Input);
        
        SetCLISwitchFlag(CLI, Output, "Output");
        SetCLISwitchDescription(CLI, Output, "Output file or stdout with: -");
        SetCLISwitchResultStatus(CLI, Output, true);
        SetCLISwitchAsMaster(CLI, Output);
        
        SetCLISwitchFlag(CLI, LogFile, "LogFile");
        SetCLISwitchDescription(CLI, LogFile, "Prints all the command line options");
        SetCLISwitchResultStatus(CLI, LogFile, true);
        SetCLISwitchAsMaster(CLI, LogFile);
        
        SetCLISwitchFlag(CLI, LeftEye, "LeftEye");
        SetCLISwitchDescription(CLI, LeftEye, "The left view for encoding or decoding");
        SetCLISwitchAsChild(CLI, Input, LeftEye);
        SetCLISwitchAsChild(CLI, Output, LeftEye);
        
        SetCLISwitchFlag(CLI, RightEye, "RightEye");
        SetCLISwitchDescription(CLI, RightEye, "The right view for encoding or decoding");
        SetCLISwitchAsChild(CLI, Input, RightEye);
        SetCLISwitchAsChild(CLI, Output, RightEye);
        
        /* Start Encode options */
        SetCLISwitchFlag(CLI, Encode, "Encode");
        SetCLISwitchDescription(CLI, Encode, "Encode input to AVC");
        SetCLISwitchResultStatus(CLI, Encode, false);
        SetCLISwitchAsMaster(CLI, Encode);
        
        SetCLISwitchFlag(CLI, Lossless, "Lossless");
        SetCLISwitchDescription(CLI, Lossless, "Encode the AVC file losslessly and only uses lossless color transforms like YCgCo");
        SetCLISwitchResultStatus(CLI, Lossless, false);
        SetCLISwitchAsChild(CLI, Encode, Lossless);
        
        SetCLISwitchFlag(CLI, BitRate, "BitRate");
        SetCLISwitchDescription(CLI, BitRate, "Target bitrate for the produced AVC file, supported postfixes: MBps, KBps (mega bits, kilo bits (1024))");
        SetCLISwitchResultStatus(CLI, BitRate, true);
        SetCLISwitchAsChild(CLI, Encode, BitRate);
        
        SetCLISwitchFlag(CLI, SubSample, "SubSample");
        SetCLISwitchDescription(CLI, SubSample, "Should the produced AVC file use chroma subsampling? if so, what type");
        SetCLISwitchResultStatus(CLI, SubSample, true);
        SetCLISwitchAsChild(CLI, Encode, SubSample);
        
        SetCLISwitchFlag(CLI, FrameRate, "FrameRate");
        SetCLISwitchDescription(CLI, FrameRate, "the framerate of the movie, for decimal fpses, use fractional notation IE: 24000/1001");
        SetCLISwitchResultStatus(CLI, FrameRate, true);
        SetCLISwitchAsChild(CLI, Encode, FrameRate);
        
        SetCLISwitchFlag(CLI, Profile, "Profile");
        SetCLISwitchDescription(CLI, Profile, "the level to encode the movie with, E.G.: 5.2");
        SetCLISwitchResultStatus(CLI, Profile, true);
        SetCLISwitchAsChild(CLI, Encode, Profile);
        
        SetCLISwitchFlag(CLI, Interlace, "Interlace");
        SetCLISwitchDescription(CLI, Interlace, "Should the movie be interlaced?");
        SetCLISwitchResultStatus(CLI, Interlace, false);
        SetCLISwitchAsChild(CLI, Encode, Interlace);
        /* End encode options */
        
        /* Start Decode options */
        SetCLISwitchFlag(CLI, Decode, "Decode");
        SetCLISwitchDescription(CLI, Decode, "Decode AVC to output");
        SetCLISwitchResultStatus(CLI, Decode, false);
        SetCLISwitchAsMaster(CLI, Decode);
        
        SetCLISwitchFlag(CLI, ExtractFrame, "ExtractFrame");
        SetCLISwitchDescription(CLI, ExtractFrame, "Extracts frame (frame number, or timestamp in HH:MM:SS:Frame format)");
        SetCLISwitchResultStatus(CLI, ExtractFrame, false);
        SetCLISwitchAsChild(CLI, Decode, ExtractFrame);
        
        SetCLISwitchFlag(CLI, TrimFrames, "TrimFrames");
        SetCLISwitchDescription(CLI, TrimFrames, "Removes frames in format FirstFrame..LastFrame (Where Frame is either the frame numbers, or a timestamp in HH:MM:SS:Frame format)");
        SetCLISwitchResultStatus(CLI, TrimFrames, false);
        SetCLISwitchAsChild(CLI, Decode, TrimFrames);
        /* End Decode options */
        
        SetCLISwitchFlag(CLI, Help, "Help");
        SetCLISwitchDescription(CLI, Help, "Prints all the command line options");
        SetCLISwitchResultStatus(CLI, Help, false);
        SetCLISwitchAsMaster(CLI, Help);
        
        return CLI;
    }
    
    int main(int argc, const char *argv[]) {
        CommandLineIO *CLI  = SetModernAVCOptions();
        BitInput           *BitI = InitBitInput();
        BitOutput          *BitO = InitBitOutput();
        
        BitBuffer          *InputBitB = InitBitBuffer(64); // 64 is pure guess work.
        BitBuffer          *OutputBitB = InitBitBuffer(64);
        
        ParseCommandLineArguments(CLI, argc, argv);
        
        
        
        /*
         Ok, so let's say we want to -Encode -Lossless -Subsampling 444 -Framerate 24000/1001 -Profile 5.1 -Input -LeftEye LeftEye.PNGs -Input -RightEye RightEye.PNGs -Output Final.avc
         */
        
        
        if (GetCLIArgumentNumFromSwitchNum(CLI, Encode) != 0xFFFFFFFFFFFFFFFF) { // Encode
            
        } else if (GetCLIArgumentNumFromSwitchNum(CLI, Decode) != 0xFFFFFFFFFFFFFFFF) { // Decode
            
        } else if (GetCLIArgumentNumFromSwitchNum(CLI, BitRate) != 0xFFFFFFFFFFFFFFFF) { // Bitrate
            
        } else if (GetCLIArgumentNumFromSwitchNum(CLI, SubSample) != 0xFFFFFFFFFFFFFFFF) { // Subsampling
            
        } else if (GetCLIArgumentNumFromSwitchNum(CLI, FrameRate) != 0xFFFFFFFFFFFFFFFF) { // Framerate
            
        } else if (GetCLIArgumentNumFromSwitchNum(CLI, Profile) != 0xFFFFFFFFFFFFFFFF) { // Profile
            
        } else if (GetCLIArgumentNumFromSwitchNum(CLI, Interlace) != 0xFFFFFFFFFFFFFFFF) { // Interlacing
            
        } else if (GetCLIArgumentNumFromSwitchNum(CLI, Lossless) != 0xFFFFFFFFFFFFFFFF) { // Lossless
            
        } else if (GetCLIArgumentNumFromSwitchNum(CLI, LogFile) != 0xFFFFFFFFFFFFFFFF) { // LogFile
            
        }
        
        if (GetCLIArgumentNumFromSwitchNum(CLI, Input) != 0xFFFFFFFFFFFFFFFF) { // Input
            
        } else if (GetCLIArgumentNumFromSwitchNum(CLI, Output) != 0xFFFFFFFFFFFFFFFF) { // Output
            
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
