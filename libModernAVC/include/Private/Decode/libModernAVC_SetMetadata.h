#include "../../include/Private/Common/libModernAVC_Types.h"
#include "../../include/Private/Common/libModernAVC_Common.h"
#include "../../include/Private/Decode/libModernAVC_Decode.h"
#include "../../include/Private/Decode/libModernAVC_DecodeMacroBlock.h"
#include "../../include/Private/Decode/libModernAVC_DecodeSlice.h"
#include "../../include/Private/Decode/libModernAVC_ParseNAL.h"

#pragma once

#ifndef libModernAVC_SetMetadata_h
#define libModernAVC_SetMetadata_h

#ifdef __cplusplus
extern "C" {
#endif

	void SetAVCProfile(DecodeAVC *Dec, const uint8_t ProfileMajor, const uint8_t ProfileMinor);

#ifdef __cplusplus
}
#endif
    
#endif /* libModernAVC_SetMetadata_h */
