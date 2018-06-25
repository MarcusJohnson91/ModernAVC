#include "../../include/Private/Common/libModernAVC_Types.h"
#include "../../include/Private/Common/libModernAVC_Common.h"
#include "../../include/Private/Decode/libModernAVC_Decode.h"
#include "../../include/Private/Decode/libModernAVC_ParseMacroBlock.h"
#include "../../include/Private/Decode/libModernAVC_ParseSlice.h"
#include "../../include/Private/Decode/libModernAVC_ParseNAL.h"

#include "../../../Dependencies/ModernPNG/Dependencies/libPCM/Dependencies/FoundationIO/libFoundationIO/include/Log.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    void SetAVCEncodeProfile(EncodeAVC *Enc, const uint8_t ProfileMajor, const uint8_t ProfileMinor) {
        if (Enc != NULL) {
            Enc->ProfileMajor = ProfileMajor;
            Enc->ProfileMinor = ProfileMinor;
        } else {
            Log(Log_ERROR, __func__, U8("Pointer to EncodeAVC is NULL"));
        }
    }
    
#ifdef __cplusplus
}
#endif
