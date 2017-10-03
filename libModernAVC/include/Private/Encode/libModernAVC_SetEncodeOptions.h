#include "../../Private/Common/libModernAVC_Types.h"

#pragma once

#ifndef libModernAVC_SetEncodeOptions_h
#define libModernAVC_SetEncodeOptions_h

#ifdef __cplusplus
extern "C" {
#endif
    
    void SetAVCEncodeProfile(EncodeAVC *Enc, const uint8_t ProfileMajor, const uint8_t ProfileMinor);
    
#ifdef __cplusplus
}
#endif

#endif /* libModernAVC_SetEncodeOptions_h */
