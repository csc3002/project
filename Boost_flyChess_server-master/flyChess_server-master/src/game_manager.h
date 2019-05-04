#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <map>
#include <vector>
#include <memory>
#include "tcp_connection.h"
#include "player.h"
#include "game_room.h"
namespace flyChess {

class GameManager : public std::enable_shared_from_this<GameManager>
{
public:
    GameManager();
    // 这个智能指针不要改, 就是不要改make_shared, 我改了就错也不知道为什么
    void addPlayer(TcpConnection::Pointer);             //将shared_ptr保存在map中
    void removePlayer(TcpConnection::Pointer);
    void processClientMsg(TcpConnection::Pointer, const std::string& msg); //分发，处理客户端发来的信息

private:
    void removePlayerFromHisRoom(Player::Pointer);
    void selectRoom(Player::Pointer , const std::string &msg);
    bool changeRoom(Player::Pointer , int roomNum);
    
    void ping(Player::Pointer);
    void login(Player::Pointer , const std::string &msg);
    // 到时候register函数可以选择删掉, 那么在TCP_conn和server里面都要对应删掉
    void registerAccount(Player::Pointer,  const std::string &msg);

private:
    std::map<TcpConnection::Pointer, Player::Pointer> players_;
    std::vector<GameRoom> rooms_;
};
// 1
}//namespace

#endif // GAMEMANAGER_H


//selectroom 1   选择房间
//login username password
//game ready  准备
//game showcards  看手牌
//game quitroom 从房间退出
//game rob 1抢地主
//game norob 不抢
//game play 1,2,3,4,5,6 出牌
//ping 心跳
