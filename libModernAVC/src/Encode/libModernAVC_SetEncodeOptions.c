#include "../../include/Private/Common/libModernAVC_Types.h"
#include "../../include/Private/Common/libModernAVC_Common.h"
#include "../../include/Private/Decode/libModernAVC_Decode.h"
#include "../../include/Private/Decode/libModernAVC_ParseMacroBlock.h"
#include "../../include/Private/Decode/libModernAVC_ParseSlice.h"
#include "../../include/Private/Decode/libModernAVC_ParseNAL.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    void SetAVCEncodeProfile(EncodeAVC *Enc, const uint8_t ProfileMajor, const uint8_t ProfileMinor) {
        if (Enc == NULL) {
            Log(LOG_ERR, "libModernAVC", "SetAVCEncodeProfile", "Pointer to DecodeAVC is NULL");
        } else {
            Enc->ProfileMajor = ProfileMajor;
            Enc->ProfileMinor = ProfileMinor;
        }
    }
    
#ifdef __cplusplus
}
#endif
