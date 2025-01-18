#include "packetData.h"
#include <cstring>
#include <enet/enet.h>
PacketData::PacketData(PacketDataType packetDataType)
    : mPacketDataType(packetDataType)
{
}
ENetPacket* PacketData::CreatePacket()
{
    size_t dataSize = sizeof(mPacketDataType);
    uint8_t* buffer = new uint8_t[dataSize];
    uint8_t* p      = buffer;
    memcpy(p, &mPacketDataType, sizeof(mPacketDataType));
    ENetPacket* packet = enet_packet_create(buffer, dataSize, ENET_PACKET_FLAG_RELIABLE);
    delete[] buffer;

    return packet;
}
void PacketData::LoadPacket(ENetPacket* packet)
{
    uint8_t* data = packet->data;

    // mPacketDataType を読み取る
    memcpy(&mPacketDataType, data, sizeof(mPacketDataType));
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
    : PacketData(PacketDataType::MatchingInit)
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
PlayerInfoData::PlayerInfoData()
    : PacketData(PacketDataType::PlayerInfo)
{
}

ENetPacket* PlayerInfoData::CreatePacket()
{
    size_t dataSize = sizeof(mPacketDataType) + sizeof(playerInfo);
    uint8_t* buffer = new uint8_t[dataSize];
    uint8_t* p      = buffer;
    memcpy(p, &mPacketDataType, sizeof(mPacketDataType));
    p += sizeof(mPacketDataType);
    memcpy(p, &playerInfo, sizeof(playerInfo));

    ENetPacket* packet = enet_packet_create(buffer, dataSize, ENET_PACKET_FLAG_RELIABLE);
    delete[] buffer;

    return packet;
}
void PlayerInfoData::LoadPacket(ENetPacket* packet)
{
    // パケットのデータ長を取得
    uint8_t* data = packet->data;

    // mPacketDataType を読み取る
    memcpy(&mPacketDataType, data, sizeof(mPacketDataType));
    data += sizeof(mPacketDataType);

    // playerInfo を読み取る
    memcpy(&playerInfo, data, sizeof(playerInfo));
}

BattleCommandData::BattleCommandData()
    : PacketData(PacketDataType::BattleCommand)
{
}

ENetPacket* BattleCommandData::CreatePacket()
{
    size_t dataSize = sizeof(mPacketDataType) + sizeof(id) + sizeof(commandData);
    uint8_t* buffer = new uint8_t[dataSize];
    uint8_t* p      = buffer;
    memcpy(p, &mPacketDataType, sizeof(mPacketDataType));
    p += sizeof(mPacketDataType);
    memcpy(p, &id, sizeof(id));
    p += sizeof(id);
    memcpy(p, &commandData, sizeof(commandData));

    ENetPacket* packet = enet_packet_create(buffer, dataSize, ENET_PACKET_FLAG_RELIABLE);
    delete[] buffer;

    return packet;
}
void BattleCommandData::LoadPacket(ENetPacket* packet)
{
    // パケットのデータ長を取得
    uint8_t* data = packet->data;

    // mPacketDataType を読み取る
    memcpy(&mPacketDataType, data, sizeof(mPacketDataType));
    data += sizeof(mPacketDataType);
    // idを読み取る
    memcpy(&id, data, sizeof(id));
    data += sizeof(id);
    // commandData を読み取る
    memcpy(&commandData, data, sizeof(commandData));
}

CurrentFrameData::CurrentFrameData()
    : PacketData(PacketDataType::CurrentFrame)
    , currentFrame(0)
{
}
ENetPacket* CurrentFrameData::CreatePacket()
{
    size_t dataSize = sizeof(mPacketDataType) + sizeof(currentFrame);
    uint8_t* buffer = new uint8_t[dataSize];
    uint8_t* p      = buffer;
    memcpy(p, &mPacketDataType, sizeof(mPacketDataType));
    p += sizeof(mPacketDataType);
    memcpy(p, &currentFrame, sizeof(currentFrame));
    ENetPacket* packet = enet_packet_create(buffer, dataSize, ENET_PACKET_FLAG_RELIABLE);
    delete[] buffer;

    return packet;
}
void CurrentFrameData::LoadPacket(ENetPacket* packet)
{
    uint8_t* data = packet->data;

    memcpy(&mPacketDataType, data, sizeof(mPacketDataType));
    data += sizeof(mPacketDataType);
    memcpy(&currentFrame, data, sizeof(currentFrame));
}

PlayerCurrentData::PlayerCurrentData()
    : PacketData(PacketDataType::PlayerCurrentData)
    , id(-1)
{
}
ENetPacket* PlayerCurrentData::CreatePacket()
{
    size_t dataSize = sizeof(mPacketDataType) + sizeof(id) + sizeof(playerState);
    uint8_t* buffer = new uint8_t[dataSize];
    uint8_t* p      = buffer;
    memcpy(p, &mPacketDataType, sizeof(mPacketDataType));
    p += sizeof(mPacketDataType);
    memcpy(p, &id, sizeof(id));
    p += sizeof(id);
    memcpy(p, &playerState, sizeof(playerState));

    ENetPacket* packet = enet_packet_create(buffer, dataSize, ENET_PACKET_FLAG_RELIABLE);
    delete[] buffer;

    return packet;
}
void PlayerCurrentData::LoadPacket(ENetPacket* packet)
{
    uint8_t* data = packet->data;

    memcpy(&mPacketDataType, data, sizeof(mPacketDataType));
    data += sizeof(mPacketDataType);
    memcpy(&id, data, sizeof(id));
    data += sizeof(id);
    memcpy(&playerState, data, sizeof(playerState));
}

StartBattleData::StartBattleData()
    : PacketData(PacketDataType::StartBattle)
    , coutDownFrame(0)
{
}

ENetPacket* StartBattleData::CreatePacket()
{
    size_t dataSize = sizeof(mPacketDataType) + sizeof(coutDownFrame);
    uint8_t* buffer = new uint8_t[dataSize];
    uint8_t* p      = buffer;
    memcpy(p, &mPacketDataType, sizeof(mPacketDataType));
    p += sizeof(mPacketDataType);
    memcpy(p, &coutDownFrame, sizeof(coutDownFrame));
    ENetPacket* packet = enet_packet_create(buffer, dataSize, ENET_PACKET_FLAG_RELIABLE);
    delete[] buffer;

    return packet;
}

void StartBattleData::LoadPacket(ENetPacket* packet)
{
    uint8_t* data = packet->data;

    // mPacketDataType を読み取る
    memcpy(&mPacketDataType, data, sizeof(mPacketDataType));
    data += sizeof(mPacketDataType);
    memcpy(&coutDownFrame, data, sizeof(coutDownFrame));
}