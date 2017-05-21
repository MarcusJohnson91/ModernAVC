#include "../../../Dependencies/BitIO/libBitIO/include/BitIO.h"

#include "../../include/ModernAVCTypes.h"
#include "../../include/Decode/DecodeAVCCommon.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    int64_t Min(int64_t X, int64_t Y) {
        return X <= Y ? X : Y;
    }
    
    int64_t Max(int64_t X, int64_t Y) {
        return X >= Y ? X : Y;
    }
    
    int64_t InverseRasterScan(int64_t A, int64_t B, int64_t C, int64_t D, int64_t E) {
        int64_t Result = 0;
        if (E == 0) {
            Result = (A % (D / B)) * B;
        } else if (E == 1) {
            Result = (A / (D / B)) * C;
        }
        return Result;
    }
    
    int64_t Clip3(int16_t X, int16_t Y, int16_t Z) {
        int64_t Result = 0;
        if (Z < X) {
            Result = X;
        } else if (Y < Z) {
            Result = Y;
        } else {
            Result = Z;
        }
        return Result;
    }
    
    int64_t Clip1Luma(int16_t X, uint8_t BitDepth) { // Clip1y
        return Clip3(0, (1 << BitDepth) -1, X);
    }
    
    int64_t Clip1Chroma(int16_t X, uint8_t BitDepth) { // Clip1c
        return Clip3(0, (1 << BitDepth) -1, X);
    }
    
    int64_t Median(double X, double Y, double Z) {
        return X + Y + Z - Min(X, Min(Y, Z)) - Max(X, Max(Y, Z));
    }
    
    int8_t Sign(double X) {
        return X >= 0 ? 1 : -1;
    }
    
    bool     AreAllViewsPaired(DecodeAVC *Dec) {
        bool AllViewsPairedFlag = false;
        for (uint8_t View = 0; View < Dec->SPS->ViewCount; View++) {
            AllViewsPairedFlag = (1 && Dec->SPS->DepthViewPresent[View] && Dec->SPS->TextureViewPresent[View]);
        }
        return AllViewsPairedFlag;
    }
    
    void ParseTransformCoeffs(DecodeAVC *Dec, uint8_t i16x16DC, uint8_t i16x16AC, uint8_t Level4x4, uint8_t Level8x8, uint8_t StartIndex, uint8_t EndIndex) { // residual_block
        uint8_t Intra16x16DCLevel = i16x16DC, Intra16x16ACLevel = i16x16AC, LumaLevel4x4 = Level4x4, LumaLevel8x8 = Level8x8;
        // Return the first 4 variables
        if (Dec->PPS->EntropyCodingMode == ExpGolomb) {
            // Read ExpGolomb
        } else {
            // Read Arithmetic
        }
        
        if (Dec->SPS->ChromaArrayType == Chroma420 || Dec->SPS->ChromaArrayType == Chroma422) {
            for (uint8_t iCbCr = 0; iCbCr < 1; iCbCr++) {
                ChromaDCLevel[iCbCr] = 4 * NumC8x8;
                for (uint8_t ChromaBlock = 0; ChromaBlock < i4x4; ChromaBlock++) {
                    ChromaACLevel[iCbCr][(i8x8 * 4) + i4x4] = 0;
                }
            }
        } else if (Dec->SPS->ChromaArrayType == Chroma444) {
            
        }
    }
    
    void ResidualLuma(DecodeAVC *Dec, BitBuffer *BitB, int i16x16DClevel, int i16x16AClevel, int level4x4,
                      int level8x8, int startIdx, int endIdx) { // residual_luma
        if (startIdx == 0 && MacroBlockPartitionPredictionMode(Dec, Dec->MacroBlock->Type, 0) == Intra_16x16) {
            residual_block(i16x16DClevel, 0, 15, 16);
        }
        for (uint8_t i8x8 = 0; i8x8 < 4; i8x8++) {
            if (Dec->MacroBlock->TransformSizeIs8x8 == false || Dec->PPS->EntropyCodingMode == ExpGolomb) {
                for (uint8_t i4x4 = 0; i4x4 < 4; i4x4++) {
                    if (Dec->MacroBlock->BlockPatternLuma & (1 << i8x8)) {
                        if (MacroBlockPartitionPredictionMode(Dec, Dec->MacroBlock->Type, 0) == Intra_16x16) {
                            residual_block(i16x16AClevel[i8x8 * 4 + i4x4], Max(0, startIdx - 1), endIdx - 1, 15);
                        } else {
                            residual_block(level4x4[i8x8 * 4 + i4x4], startIdx, endIdx, 16);
                        }
                    } else if (MacroBlockPartitionPredictionMode(Dec, Dec->MacroBlock->Type, 0) == Intra_16x16) {
                        for (uint8_t i = 0; i < 15; i++) {
                            i16x16AClevel[i8x8 * 4 + i4x4][i] = 0;
                        }
                    } else {
                        for (uint8_t i = 0; i < 16; i++) {
                            level4x4[i8x8 * 4 + i4x4][i] = 0;
                        }
                    }
                }
            }
            if (Dec->PPS->EntropyCodingMode == ExpGolomb && Dec->MacroBlock->TransformSizeIs8x8) {
                for (uint8_t i = 0; i < 16; i++) {
                    level8x8[i8x8][4 * i + i4x4] = level4x4[i8x8 * 4 + i4x4][i];
                }
            }
            else if (Dec->MacroBlock->BlockPatternLuma & (1 << i8x8)) {
                residual_block(level8x8[i8x8], 4 * startIdx, 4 * endIdx + 3, 64);
            } else {
                for (uint8_t i = 0; i < 64; i++) {
                    level8x8[i8x8][i] = 0;
                }
            }
        }
    }
    
    int8_t MacroBlock2SliceGroupMap(DecodeAVC *Dec, uint8_t CurrentMacroBlock) { // MbToSliceGroupMap
        if (Dec->PPS->SliceGroups == 1 && (Dec->PPS->SliceGroupMapType == 3 || Dec->PPS->SliceGroupMapType == 4 || Dec->PPS->SliceGroupMapType == 5)) {
            if (Dec->PPS->SliceGroupMapType == 3) {
                if (Dec->PPS->SliceGroupChangeDirection == false) {
                    return BoxOutClockwise;
                } else if (Dec->PPS->SliceGroupChangeDirection == true) {
                    return BoxOutCounterClockwise;
                }
            } else if (Dec->PPS->SliceGroupMapType == 4) {
                if (Dec->PPS->SliceGroupChangeDirection == false) {
                    return RasterScan;
                } else if (Dec->PPS->SliceGroupChangeDirection == true) {
                    return ReverseRasterScan;
                }
            } else if (Dec->PPS->SliceGroupMapType == 5) {
                if (Dec->PPS->SliceGroupChangeDirection == false) {
                    return WipeRight;
                } else if (Dec->PPS->SliceGroupChangeDirection == true) {
                    return WipeLeft;
                }
            }
        }
        Log(LOG_ERR, "libModernAVC", "MacroBlock2SliceGroupMap", "SliceGroups: %hhu, SliceGroupMapType: %d", Dec->PPS->SliceGroups, Dec->PPS->SliceGroupMapType);
        return -1; // failure
    }
    
    typedef struct Arthimetic {
        uint16_t *ProbabilityTable;
        size_t    TableSize;
    } Arthimetic;
    
    typedef struct Probability {
        double Low;
        double High;
    } Probability;
    
    uint64_t ReadArithmetic(BitInput *Input, uint64_t *MaximumTable, uint64_t *MinimumTable, size_t TableSize, uint64_t Bits2Decode) {
        // Read a bit at a time.
        double High = 1.0, Low = 0.0; // Decimal point is implied before the highest bit.
        return 0;
    }
    
    void WriteArithmetic(BitBuffer *BitB, double *ProbabilityTable[], size_t TableSize, uint64_t Bits2Encode) { // Use the least precision you can get away with to be as efficent as possible.
        uint64_t High = 0xFFFFFFFFFFFFFFFFULL, Low = 0ULL, Range = 0ULL, Probability = 0ULL;
        while ((Bits2Encode >= High) && (Bits2Encode <= Low)) {
            Range = (High - Low) + 1;
            Probability = ProbabilityTable[Range]; // Probability should be an int table ordered on how often a symbol shows up, not it's quantized probability.
            
        }
    }
    
    void rbsp_slice_trailing_bits(DecodeAVC *Dec, BitBuffer *BitB) {
        AlignBitBuffer(BitB, 1); // rbsp_trailing_bits();
        if (Dec->PPS->EntropyCodingMode == Arithmetic) {
            while (more_rbsp_trailing_data()) {
                Dec->PPS->CABACZeroWord = ReadBits(BitB, 16, true); /* equal to 0x0000 */
            }
        }
    }
    
    uint8_t NumberOfMacroBlockPartitions(uint8_t MacroBlockType) { // NumMbPart
        
    }
    
    uint8_t MacroBlockPartitionPredictionMode(DecodeAVC *Dec, uint8_t MacroBlockType, uint8_t PartitionNumber) {  // MbPartPredMode
        uint8_t ReturnValue = 0;
        if (MacroBlockType == 0) {
            if (Dec->MacroBlock->TransformSizeIs8x8 == true) {
                ReturnValue = Intra_8x8;
            } else {
                ReturnValue = Intra_4x4;
            }
        } else if (MacroBlockType == 1) {
            ReturnValue = I_16x16_0_0_0;
        } else if (MacroBlockType == 2) {
            ReturnValue  = I_16x16_1_0_0;
        } else if (MacroBlockType == 3) {
            ReturnValue  = I_16x16_2_0_0;
        } else if (MacroBlockType == 4) {
            ReturnValue  = I_16x16_3_0_0;
        } else if (MacroBlockType == 5) {
            ReturnValue  = I_16x16_0_1_0;
        } else if (MacroBlockType == 6) {
            ReturnValue  = I_16x16_1_1_0;
        } else if (MacroBlockType == 7) {
            ReturnValue  = I_16x16_2_1_0;
        } else if (MacroBlockType == 8) {
            ReturnValue  = I_16x16_3_1_0;
        } else if (MacroBlockType == 9) {
            ReturnValue  = I_16x16_0_2_0;
        } else if (MacroBlockType == 10) {
            ReturnValue  = I_16x16_1_2_0;
        } else if (MacroBlockType == 11) {
            ReturnValue  = I_16x16_2_2_0;
        } else if (MacroBlockType == 12) {
            ReturnValue  = I_16x16_3_2_0;
        } else if (MacroBlockType == 13) {
            ReturnValue  = I_16x16_0_0_1;
        } else if (MacroBlockType == 14) {
            ReturnValue  = I_16x16_1_0_1;
        } else if (MacroBlockType == 15) {
            ReturnValue  = I_16x16_2_0_1;
        } else if (MacroBlockType == 16) {
            ReturnValue  = I_16x16_3_0_1;
        } else if (MacroBlockType == 17) {
            ReturnValue  = I_16x16_0_1_1;
        } else if (MacroBlockType == 18) {
            ReturnValue  = I_16x16_1_1_1;
        } else if (MacroBlockType == 19) {
            ReturnValue  = I_16x16_2_1_1;
        } else if (MacroBlockType == 20) {
            ReturnValue  = I_16x16_3_1_1;
        } else if (MacroBlockType == 21) {
            ReturnValue  = I_16x16_0_2_1;
        } else if (MacroBlockType == 22) {
            ReturnValue  = I_16x16_1_2_1;
        } else if (MacroBlockType == 23) {
            ReturnValue  = I_16x16_2_2_1;
        } else if (MacroBlockType == 24) {
            ReturnValue  = I_16x16_3_2_1;
        } else if (MacroBlockType == 25) {
            ReturnValue  = I_PCM;
        }
        /*
         if (NotPartitioned == true) {
         return BlockPredictionMode;
         } else if (PartitionNumber >= 0) {
         PartitionMode;
         }
         }
         */
        return ReturnValue;
    }
    
    uint64_t NextMacroBlockAddress(DecodeAVC *Dec, uint64_t CurrentMacroBlockAddress) { // NextMbAddress
        while (CurrentMacroBlockAddress + 1 < Dec->Slice->PicSizeInMacroBlocks && MacroBlock2SliceGroupMap(Dec, CurrentMacroBlockAddress + 1) != MacroBlock2SliceGroupMap(Dec, CurrentMacroBlockAddress)) {
            i++; nextMbAddress = I
        }
        
        // aka
        for (uint64_t I = CurrentMacroBlockAddress + 1; I < Dec->Slice->PicSizeInMacroBlocks && MbToSliceGroups[I]) {
            MacroBlock2SliceGroupMap(Dec, CurrentMacroBlockAddress);
        }
    }
    
    uint8_t NumberOfSubMacroBlockPartitions() { // NumSubMbPart
        bool IsDirectFlag = 0;
        
        if (mbType[CurrMbAddr] == B_Skip || mbType[CurrMbAddr] == B_Direct_16x16) {
            IsDirectFlag = true;
        } else if (mbType[CurrMbAddr] == B_8x8 && subMbType[CurrMbAddr][mbPartIdx] == B_Direct_8x8) {
            IsDirectFlag = true;
        }
        
        if (IsDirectFlag == true && DQID == 0 && nal_unit_type != NAL_AuxiliarySliceExtension) {
            return 4;
        } else if (IsDirectFlag == true && DQID > 0 && nal_unit_type == NAL_AuxiliarySliceExtension) {
            return 1;
        } else if (IsDirectFlag == 0) {
            return NumSubMbPart(subMbType[CurrMbAddr][mbPartIdx]);
        }
    }
    
    size_t GetSizeOfNALUnit(DecodeAVC *Dec, BitBuffer *BitB) {
        
    }
    
    bool IsThereMoreDataInThisNAL() { // more_rbsp_data
        if (there is no more data) {
            return false;
        } else {
            // find the rightmost 1 bit, Given the position of this bit, which is the first bit (rbsp_stop_one_bit) of the rbsp_trailing_bits( ) syntax structure
        }
    }
    
    uint8_t CalculateNumberOfTimeStamps(DecodeAVC *Dec) { // PicOrderCount
        uint8_t NumTimeStamps = 0;
        if ((Dec->Slice->SliceIsInterlaced == false) && (Dec->Slice->TopFieldOrderCount == Dec->Slice->BottomFieldOrderCount)) {
            NumTimeStamps = 1;
        } else if (0 == 1) {
            
        }
        return 0;
    }
    
    bool InCropWindow(DecodeAVC *Dec, uint64_t MacroBlockAddress) { // mbAddr
        uint64_t mbX     = ((MacroBlockAddress / (1 + Dec->Slice->MbaffFrameFlag)) % Dec->Slice->PicWidthInMacroBlocks);
        uint64_t mbY0    = 0;
        uint64_t mbY1    = 0;
        uint8_t  scalMbH  = 0; // Max = 32
        bool     Status   = 0;
        
        Dec->Slice->ScaledRefLayerPicHeightInSamplesL = Dec->Slice->PicHeightInMacroBlocks * 16 - (Dec->Slice->ScaledRefLayerTopOffset + Dec->Slice->ScaledRefLayerBottomOffset) / (1 + Dec->Slice->SliceIsInterlaced);
        
        if (Dec->Slice->MbaffFrameFlag == false) {
            mbY0 = (MacroBlockAddress / Dec->Slice->PicWidthInMacroBlocks);
            mbY1 = (MacroBlockAddress / Dec->Slice->PicWidthInMacroBlocks);
        } else if (Dec->Slice->MbaffFrameFlag == true) {
            mbY0 = (2 * ((MacroBlockAddress / Dec->Slice->PicWidthInMacroBlocks) / 2));
            mbY1 = mbY0 + 1;
        }
        scalMbH = (16 * (1 + Dec->Slice->SliceIsInterlaced));
        
        if (Dec->NAL->NoInterLayerPredictionFlag == true && (mbX >= ((Dec->Slice->ScaledRefLayerLeftOffset + 15) / 16) && mbX < ((Dec->Slice->ScaledRefLayerLeftOffset + ScaledRefLayerPicWidthInSamplesL) / 16)) && mbY0 >= ((Dec->Slice->ScaledRefLayerTopOffset + scalMbH - 1) / scalMbH) && mbY1 < ((Dec->Slice->ScaledRefLayerTopOffset + Dec->Slice->ScaledRefLayerPicHeightInSamplesL) / scalMbH)) {
            Status = true;
        } else {
            Status = false;
        }
        
        return Status;
    }
    
    DecodeAVC *InitAVCDecoder(void) {
        errno = 0;
        DecodeAVC *Dec                = (DecodeAVC*) calloc(1, sizeof(DecodeAVC));
        if (errno != 0) {
            const char ErrnoError[128];
            strerror_r(errno, ErrnoError, 128);
            Log(LOG_ERR, "libModernAVC", "InitAVCDecoder", "Errno error: %s", ErrnoError);
        } else {
            Dec->NAL                  = (NALHeader*)                    calloc(1, sizeof(NALHeader));
            Dec->SPS                  = (SequenceParameterSet*)         calloc(1, sizeof(SequenceParameterSet));
            Dec->PPS                  = (PictureParameterSet*)          calloc(1, sizeof(PictureParameterSet));
            Dec->VUI                  = (VideoUsabilityInformation*)    calloc(1, sizeof(VideoUsabilityInformation));
            Dec->HRD                  = (HypotheticalReferenceDecoder*) calloc(1, sizeof(HypotheticalReferenceDecoder));
            Dec->SEI                  = (SupplementalEnhancementInfo*)  calloc(1, sizeof(SupplementalEnhancementInfo));
            Dec->Slice                = (Slice*)                        calloc(1, sizeof(Slice));
            Dec->SVC                  = (ScalableVideoCoding*)          calloc(1, sizeof(ScalableVideoCoding));
            Dec->DPS                  = (DepthParameterSet*)            calloc(1, sizeof(DepthParameterSet));
            Dec->MacroBlock           = (MacroBlock*)                   calloc(1, sizeof(MacroBlock));
        }
        return Dec;
    }
    
#ifdef __cplusplus
}
#endif
