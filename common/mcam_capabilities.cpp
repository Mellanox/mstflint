#include "mcam_capabilities.h"
#include "tools_layouts/reg_access_hca_layouts.h"

bool is_valid_mcam_capability(mcam_capability_t cap)
{
    return (cap >= 0 && cap < MCAM_CAP_MAX);
}

reg_access_status_t isCapabilitySupportedAccordingToMcamReg(mfile* mf,
                                                            mcam_capability_t capability_number,
                                                            bool is_hca,
                                                            bool* is_capability_supported)
{
    if (!mf || !is_capability_supported || !is_valid_mcam_capability(capability_number))
    {
        return ME_BAD_PARAMS;
    }

    *is_capability_supported = false;

    struct reg_access_hca_mcam_reg_ext mcam;
    memset(&mcam, 0, sizeof(mcam));
    reg_access_status_t rc = reg_access_mcam(mf, REG_ACCESS_METHOD_GET, &mcam);

    if (rc == ME_OK)
    {
        int dword_length = 32;
        if (is_hca)
        {
            // due to FW bug, MCAM mng_feature_cap_mask dwords are set in reversed order for NICs
            u_int32_t temp = mcam.mng_feature_cap_mask[0];
            mcam.mng_feature_cap_mask[0] = mcam.mng_feature_cap_mask[3];
            mcam.mng_feature_cap_mask[3] = temp;

            temp = mcam.mng_feature_cap_mask[1];
            mcam.mng_feature_cap_mask[1] = mcam.mng_feature_cap_mask[2];
            mcam.mng_feature_cap_mask[2] = temp;
        }
        int dword_index = capability_number / dword_length;
        int offset = capability_number % dword_length;
        *is_capability_supported = EXTRACT(mcam.mng_feature_cap_mask[dword_index], offset, 1);
    }
    return rc;
}

reg_access_status_t getIndexOfRegGroup(unsigned int reg_id, int* idx)
{
    reg_access_status_t rc = ME_BAD_PARAMS;
    if (idx && (reg_id >= REG_ACCESS_BASE_GROUP_0_ID && reg_id <= MAX_REG_ACCESS_ID))
    {
        *idx = (reg_id - REG_ACCESS_BASE_GROUP_0_ID) / REG_GROUP_LEN;
        rc = ME_OK;
    }

    return rc;
}

reg_access_status_t isRegisterValidAccordingToMcamReg(mfile* mf, unsigned int reg_id, bool* is_reg_valid)
{
    reg_access_status_t rc = ME_BAD_PARAMS;

    if (mf && is_reg_valid)
    {
        *is_reg_valid = false;

        int reg_group_index = 0;
        rc = getIndexOfRegGroup(reg_id, &reg_group_index);
        if (rc == ME_OK)
        {
            struct reg_access_hca_mcam_reg_ext mcam;
            memset(&mcam, 0, sizeof(mcam));
            mcam.access_reg_group = reg_group_index;
            rc = reg_access_mcam(mf, REG_ACCESS_METHOD_GET, &mcam);

            if (rc == ME_OK)
            {
                unsigned int reg_group_to_base_address[MCAM_REG_GROUPS_AMOUNT] = {
                  REG_ACCESS_BASE_GROUP_0_ID, REG_ACCESS_BASE_GROUP_1_ID, REG_ACCESS_BASE_GROUP_2_ID,
                  REG_ACCESS_BASE_GROUP_3_ID};
                unsigned int base_address = reg_group_to_base_address[reg_group_index];
                unsigned int relative_loc = reg_id - base_address;
                int dword_length = 32;
                int dword_index = 3 - (relative_loc / dword_length);
                unsigned int offset = relative_loc % dword_length;
                int bits_amount = 1;
                *is_reg_valid = EXTRACT(mcam.mng_access_reg_cap_mask[dword_index], offset, bits_amount);
            }
        }
    }

    return rc;
}