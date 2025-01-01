#include "packet.h"
#include <cstring>
#include <enet/enet.h>
PacketData::PacketData(PacketDataType packetDataType)
    : mPacketDataType(packetDataType)
{
}

PacketDataType PacketData::RecognizePacketDatatype(ENetPacket* packet)
{
    if (packet == nullptr || packet->data == nullptr || packet->dataLength < 1) {
        return PacketDataType::INVALID; // 無効なパケット
    }
    uint8_t* data = packet->data;
    return static_cast<PacketDataType>(data[0]);
}

IDInitData::IDInitData()
    : PacketData(PacketDataType::Init)
    , id(0)
{
}
ENetPacket* IDInitData::CreatePacket()
{
    size_t dataSize = sizeof(mPacketDataType) + sizeof(id);
    uint8_t* buffer = new uint8_t[dataSize];
    uint8_t* p      = buffer;
    memcpy(p, &mPacketDataType, sizeof(mPacketDataType));
    p += sizeof(mPacketDataType);
    memcpy(p, &id, sizeof(id));
    ENetPacket* packet = enet_packet_create(buffer, dataSize, ENET_PACKET_FLAG_RELIABLE);
    delete[] buffer;

    return packet;
}
void IDInitData::LoadPacket(ENetPacket* packet)
{
    uint8_t* data = packet->data;

    // mPacketDataType を読み取る
    memcpy(&mPacketDataType, data, sizeof(mPacketDataType));
    data += sizeof(mPacketDataType);
    memcpy(&id, data, sizeof(id));
    data += sizeof(id);
}

MessageData::MessageData()
    : PacketData(PacketDataType::Message)
    , message(nullptr)
{
}
MessageData::~MessageData()
{
    if (message != nullptr) {
        delete[] message;
    }
}
ENetPacket* MessageData::CreatePacket()
{
    size_t messageSize = strlen(message) + 1;
    size_t dataSize    = sizeof(mPacketDataType) + messageSize;
    uint8_t* buffer    = new uint8_t[dataSize];
    uint8_t* p         = buffer;
    memcpy(p, &mPacketDataType, sizeof(mPacketDataType));
    p += sizeof(mPacketDataType);
    memcpy(p, &messageSize, sizeof(messageSize));
    p += sizeof(messageSize);
    memcpy(p, message, messageSize);
    ENetPacket* packet = enet_packet_create(buffer, dataSize, ENET_PACKET_FLAG_RELIABLE);
    delete[] buffer;

    return packet;
}
void MessageData::LoadPacket(ENetPacket* packet)
{
    // パケットのデータ長を取得
    uint8_t* data = packet->data;

    // mPacketDataType を読み取る
    memcpy(&mPacketDataType, data, sizeof(mPacketDataType));
    data += sizeof(mPacketDataType);

    // messageSize を読み取る
    size_t messageSize;
    memcpy(&messageSize, data, sizeof(messageSize));
    data += sizeof(messageSize);

    // message のためのメモリ確保
    message = new char[messageSize];

    // message を読み取る
    memcpy(message, data, messageSize);
}
