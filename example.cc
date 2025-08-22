#include <Arduino.h>

#include "tlv.h"

uint8_t buffer[255];

int main()
{
    TLVS tlvs;
    TLVNode *tlvNode, *childNode;
    size_t data_size;
    uint8_t abc[] = { 0x65, 0x66, 0x67 };
    uint8_t def[] = { 0x68, 0x69, 0x6a };

    // Build a set of TLVs
    tlvNode = tlvs.addTLV(0xbf10);
    tlvs.addTLV(tlvNode, 0x8a, abc, sizeof(abc));
    tlvs.addTLV(tlvNode, 0x8b, def, sizeof(def));
    data_size = tlvs.encodeTLVs(buffer, sizeof(buffer));

    // Decode TLVs
    tlvs.reset();
    tlvs.decodeTLVs(buffer, sizeof(buffer));
    tlvNode = tlvs.firstTLV();
    Serial.print("TLV Node ");
    Serial.println(tlvNode->getTag(), HEX);
    for (childNode = tlvNode->firstChild(); childNode; childNode = tlvNode->nextChild(childNode)) {
        Serial.print("Child Node ");
        Serial.println(childNode->getTag(), HEX);
    }
    TLVS::printTLV(tlvNode);
}

