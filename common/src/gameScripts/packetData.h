#pragma once
#include "commandData.h"
#include "gameObject/player.h"
#include <cstring>
#include <enet/enet.h>
#include <iostream>

enum class PacketDataType : uint8_t {
    Message,
    MatchingInit,
    PlayerInfo,
    StartBattle,
    BattleCommand,
    CurrentFrame,
    PlayerCurrentData,
    INVALID,
    GameEnd,
    PacketDataTypeNum
};

struct PacketData {
    PacketDataType mPacketDataType;

    PacketData(PacketDataType packetDataType);
    // 構造体をデータ化
    virtual ENetPacket* CreatePacket();
    // データを構造体化
    virtual void LoadPacket(ENetPacket* packet);
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
struct PlayerInfoData : public PacketData {
    PlayerInfo playerInfo;

    PlayerInfoData();
    ENetPacket* CreatePacket() override;
    void LoadPacket(ENetPacket* packet) override;
};
struct BattleCommandData : public PacketData {
    int id;
    CommandData commandData;

    BattleCommandData();
    ENetPacket* CreatePacket() override;
    void LoadPacket(ENetPacket* packet) override;
};
struct CurrentFrameData : public PacketData {
    int currentFrame;

    CurrentFrameData();
    ENetPacket* CreatePacket() override;
    void LoadPacket(ENetPacket* packet) override;
};

struct PlayerCurrentData : public PacketData {
    int id;
    HeroCurrentStatus heroCurrentStatus;
    Matrix4 heroTransform;
    PlayerCurrentData();
    ENetPacket* CreatePacket() override;
    void LoadPacket(ENetPacket* packet) override;
};

struct StartBattleData : public PacketData {
    int coutDownFrame;

    StartBattleData();
    ENetPacket* CreatePacket() override;
    void LoadPacket(ENetPacket* packet) override;
};