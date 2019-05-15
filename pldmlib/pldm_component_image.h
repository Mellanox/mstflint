/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) 2019, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 * pldm_utils.h
 *
 *  Created on: Feb 27, 2019
 *      Author: Samer Deeb
 */

#ifndef _PLDM_COMPONENET_IMAGE_
#define _PLDM_COMPONENET_IMAGE_

class PldmComponenetImage {
public:
    PldmComponenetImage();
    virtual ~PldmComponenetImage();

    bool unpack(PldmBuffer & buff);
    void print(FILE * fp);

    u_int16_t getComponentClassification() const {
        return componentClassification;
    }
    u_int16_t getComponentIdentifier() const { return componentIdentifier; }
    u_int32_t getComponentComparisonStamp() const {
        return componentComparisonStamp;
    }
    u_int16_t getComponentOptions() const { return componentOptions; }
    u_int16_t getRequestedComponentActivationMethod() const {
        return requestedComponentActivationMethod;
    }
    u_int32_t getComponentLocationOffset() const{
        return componentLocationOffset;
    }
    u_int32_t getComponentSize() const { return componentSize; }
    u_int8_t getComponentVersionStringType() const {
        return componentVersionStringType;
    }
    u_int8_t getComponentVersionStringLength() const {
        return componentVersionStringLength;
    }
    std::string getComponentVersionString() const {
        return componentVersionString;
    }

    const u_int8_t * getComponentData() const { return componentData; }

private:
    bool readComponentData(PldmBuffer & buff);

    u_int16_t componentClassification;
    u_int16_t componentIdentifier;
    u_int32_t componentComparisonStamp;
    u_int16_t componentOptions;
    u_int16_t requestedComponentActivationMethod;
    u_int32_t componentLocationOffset;
    u_int32_t componentSize;
    u_int8_t componentVersionStringType;
    u_int8_t componentVersionStringLength;
    std::string componentVersionString;

    u_int8_t * componentData;
};

#endif /* _PLDM_COMPONENET_IMAGE_ */

