#pragma once
#include <string>
#include "Person.h"

using namespace std;

class Player : public Person
{
public:
    int gameId = 0;
    string gameName = "游戏昵称";
    vector<string> games;

    using Person::Person;
    Player(string name, int age, bool gender,int gameId,string gameName);
    ~Player();
    string getType();

private:
    int mmr = 0;
};


Player::Player(string name, int age, bool gender,int gameId,string gameName):gameId(gameId),gameName(gameName),Person(name,age,gender)
{
    curNum++;
}
Player::~Player()
{
    cout << "Player Clear\t";
}


string Player::getType()
{
    return "Player";
}