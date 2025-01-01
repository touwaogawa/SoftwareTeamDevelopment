#pragma once
#include <cstring>
#include <enet/enet.h>
#include <iostream>

enum class PacketDataType : uint8_t {
    Init,
    Message,
    INVALID,
    PacketDataTypeNum
};

struct PacketData {
    PacketDataType mPacketDataType;

    PacketData(PacketDataType packetDataType);
    // 構造体をデータ化
    virtual ENetPacket* CreatePacket() = 0;
    // データを構造体化
    virtual void LoadPacket(ENetPacket* packet) = 0;
    // パケットの種類を判別
    static PacketDataType RecognizePacketDatatype(ENetPacket* packet);
};

struct IDInitData : public PacketData {
    int id;
    IDInitData();
    ENetPacket* CreatePacket() override;
    void LoadPacket(ENetPacket* packet) override;
};
struct MessageData : public PacketData {
    char* message;
    MessageData();
    ~MessageData();
    ENetPacket* CreatePacket() override;
    void LoadPacket(ENetPacket* packet) override;
};
