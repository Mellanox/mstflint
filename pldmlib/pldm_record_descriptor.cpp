#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>

#include "pldm_buff.h"
#include "pldm_record_descriptor.h"

PldmRecordDescriptor::PldmRecordDescriptor() :
    bufferOffset(0),
    descriptorType(0),
    descriptorLength(0),
    descriptorData(NULL),
    vendorDefinedType(VendorDefinedType::NOT_VENDOR_DEFINED),
    vendorDefinedStringValue(""),
    vendorDefinedNumericValue(0)
{
}

PldmRecordDescriptor::~PldmRecordDescriptor()
{
    if (descriptorData)
    {
        delete[] descriptorData;
    }
}

bool PldmRecordDescriptor::unpack(PldmBuffer& buff)
{
    bufferOffset = buff.tell();
    buff.read(descriptorType);
    buff.read(descriptorLength);
    if (descriptorLength)
    {
        descriptorData = new u_int8_t[descriptorLength];
        buff.read(descriptorData, descriptorLength);
        if (!extractVendorDefined())
        {
            printf("unknown vendor defined descriptor\n");
            delete[] descriptorData;
            descriptorData = NULL;
            return false;
        }
    }
    return true;
}

bool PldmRecordDescriptor::extractVendorDefined()
{
    if (descriptorType == Vendor_Defined)
    {
        u_int8_t* vendoreDefinedPtr = descriptorData;
        vendoreDefinedPtr++;
        u_int8_t prefixlen = *vendoreDefinedPtr;
        std::string descriptorName((char*)vendoreDefinedPtr + 1, prefixlen);
        vendoreDefinedPtr++;
        vendoreDefinedPtr += prefixlen;
        if (descriptorName == "PSID")
        {
            vendorDefinedStringValue = std::string(reinterpret_cast<const char*>(vendoreDefinedPtr));
            vendorDefinedType = VendorDefinedType::PSID;
        }
        else if (descriptorName == "recovery")
        {
            vendorDefinedStringValue = std::string(reinterpret_cast<const char*>(vendoreDefinedPtr));
            vendorDefinedType = VendorDefinedType::RECOVERY;
        }
        else if (descriptorName == "APSKU")
        {
            vendorDefinedNumericValue = __cpu_to_le32(*reinterpret_cast<u_int32_t*>(vendoreDefinedPtr));
            vendorDefinedType = VendorDefinedType::APSKU;
        }
        else if (descriptorName == "GLACIERDSD")
        {
            vendorDefinedNumericValue = __cpu_to_le32(*reinterpret_cast<u_int32_t*>(vendoreDefinedPtr));
            vendorDefinedType = VendorDefinedType::GLACIERDSD;
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool PldmRecordDescriptor::IsStringVendorDefinedType(const PldmRecordDescriptor::VendorDefinedType type) const
{
    static const std::vector<VendorDefinedType> stringTypes = {
      VendorDefinedType::PSID,
      VendorDefinedType::RECOVERY,
    };
    return std::find(stringTypes.begin(), stringTypes.end(), type) != stringTypes.end();
}

bool PldmRecordDescriptor::IsNumericVendorDefinedType(const PldmRecordDescriptor::VendorDefinedType type) const
{
    static const std::vector<VendorDefinedType> numericTypes = {
      VendorDefinedType::APSKU,
      VendorDefinedType::GLACIERDSD,
    };
    return std::find(numericTypes.begin(), numericTypes.end(), type) != numericTypes.end();
}

std::string PldmRecordDescriptor::GetVendorDefinedValue(const VendorDefinedType type) const
{
    if (IsStringVendorDefinedType(type))
    {
        return vendorDefinedStringValue;
    }
    else if (IsNumericVendorDefinedType(type))
    {
        return std::to_string(vendorDefinedNumericValue);
    }
    return "";
}

u_int16_t PldmRecordDescriptor::getValueOffset() const
{
    // Vendor-defined descriptors carry an inline metadata prefix before the value:
    //   descriptorData[0]      : title-string-type (1 byte, e.g. 0x01 = ASCII)
    //   descriptorData[1]      : title-string-len  (1 byte, length of the title that follows)
    //   descriptorData[2..2+N-1]: title-string     (N bytes, e.g. "PSID")
    //   descriptorData[2+N..]  : the actual value bytes
    // Non-vendor-defined descriptors have no prefix; the value is the whole descriptorData.
    if (descriptorData == NULL || descriptorType != Vendor_Defined || descriptorLength < 2)
    {
        return 0;
    }
    // +2 accounts for the two fixed header bytes (title-string-type + title-string-len);
    // descriptorData[1] holds the title-string length, so the total prefix to skip is 2 + that.
    size_t valueOffset = (size_t)2 + descriptorData[1];
    if (valueOffset > descriptorLength)
    {
        return 0;
    }
    return (u_int16_t)valueOffset;
}

u_int8_t* PldmRecordDescriptor::getMutableValue()
{
    if (descriptorData == NULL)
    {
        return NULL;
    }
    u_int16_t valueOffset = getValueOffset();
    if (valueOffset == 0)
    {
        return NULL;
    }
    return descriptorData + valueOffset;
}

u_int16_t PldmRecordDescriptor::getValueLength() const
{
    u_int16_t offset = getValueOffset();
    if (offset == 0 || offset > descriptorLength)
    {
        return 0;
    }
    return (u_int16_t)(descriptorLength - offset);
}

bool PldmRecordDescriptor::pack(PldmBuffer& buff) const
{
    if (descriptorData == NULL || bufferOffset < 0)
    {
        return false;
    }
    size_t off = (size_t)bufferOffset;

    u_int16_t typeLE = __cpu_to_le16(descriptorType);
    if (!buff.writeAt(off, (const u_int8_t*)&typeLE, sizeof(typeLE)))
    {
        return false;
    }
    off += sizeof(typeLE);

    u_int16_t lenLE = __cpu_to_le16(descriptorLength);
    if (!buff.writeAt(off, (const u_int8_t*)&lenLE, sizeof(lenLE)))
    {
        return false;
    }
    off += sizeof(lenLE);

    if (descriptorLength == 0)
    {
        return true;
    }
    return buff.writeAt(off, descriptorData, descriptorLength);
}

void PldmRecordDescriptor::printFormatted() const
{
    const int LABEL_WIDTH = 26;
    switch (descriptorType)
    {
        case PCI_Vendor_ID:
            printf("%-*s0x%02x%02x\n", LABEL_WIDTH, "PCI Vendor ID:", descriptorData[1], descriptorData[0]);
            break;
        case IANA_Enterprise_ID:
            printf("%-*s0x%02x%02x\n", LABEL_WIDTH, "IANA Enterprise ID:", descriptorData[1], descriptorData[0]);
            break;
        case FD_UUID:
            printf("%-*s%s\n", LABEL_WIDTH, "FD UUID:", descriptorData);
            break;
        case PnP_Vendor_ID:
            printf("%-*s0x%02x%02x\n", LABEL_WIDTH, "PnP Vendor ID:", descriptorData[1], descriptorData[0]);
            break;
        case ACPI_Vendor_ID:
            printf("%-*s0x%02x%02x\n", LABEL_WIDTH, "ACPI Vendor ID:", descriptorData[1], descriptorData[0]);
            break;
        case PCI_Device_ID:
            printf("%-*s0x%02x%02x\n", LABEL_WIDTH, "PCI Device ID:", descriptorData[1], descriptorData[0]);
            break;
        case PCI_Subsystem_Vendor_ID:
            printf("%-*s0x%02x%02x\n", LABEL_WIDTH, "PCI Subsystem Vendor ID:", descriptorData[1], descriptorData[0]);
            break;
        case PCI_Subsystem_ID:
            printf("%-*s0x%02x%02x\n", LABEL_WIDTH, "PCI Subsystem ID:", descriptorData[1], descriptorData[0]);
            break;
        case PCI_Revision_ID:
            printf("%-*s0x%02x%02x\n", LABEL_WIDTH, "PCI Revision ID:", descriptorData[1], descriptorData[0]);
            break;
        case PnP_Product_ID:
            printf("%-*s0x%02x%02x\n", LABEL_WIDTH, "PnP Product ID:", descriptorData[1], descriptorData[0]);
            break;
        case ACPI_Product_ID:
            printf("%-*s0x%02x%02x\n", LABEL_WIDTH, "ACPI Product ID:", descriptorData[1], descriptorData[0]);
            break;
        case Vendor_Defined:
            if (vendorDefinedType == VendorDefinedType::PSID)
            {
                printf("%-*s%s\n", LABEL_WIDTH, "PSID:", vendorDefinedStringValue.c_str());
            }
            else if (vendorDefinedType == VendorDefinedType::RECOVERY)
            {
                printf("%-*s%s\n", LABEL_WIDTH, "RECOVERY:", vendorDefinedStringValue.c_str());
            }
            else if (vendorDefinedType == VendorDefinedType::APSKU)
            {
                printf("%-*s0x%08X\n", LABEL_WIDTH, "APSKU:", vendorDefinedNumericValue);
            }
            else if (vendorDefinedType == VendorDefinedType::GLACIERDSD)
            {
                printf("%-*s0x%08X\n", LABEL_WIDTH, "GLACIERDSD:", vendorDefinedNumericValue);
            }
            break;
        default:
            printf("%-*s0x%04X\n", LABEL_WIDTH, "Unknown:", descriptorType);
            break;
    }
}
