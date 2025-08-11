#ifndef ACTIONS_H
#define ACTIONS_H
#include "cmd.h"
#include "player.h"

#include <iostream>

class FireCmd : public Command
{
public:
	virtual void execute() { std::cout << "Fire" << std::endl; }
};

class WCmd : public Command
{
public:
	WCmd(Player* a, float* deltaTime) : player(a), delta(deltaTime){}
	virtual void execute() override{ 
		player->ProcessKeyboard(FORWARD, *delta);
	}
private:
	Player* player;
	float* delta;
};

class ACmd : public Command
{
public:
	ACmd(Player* a, float* deltaTime) : player(a), delta(deltaTime) {}
	virtual void execute() override{
		player->ProcessKeyboard(LEFT, *delta);
	}
private:
	Player* player;
	float* delta;
};

class SCmd : public Command
{
public:
	SCmd(Player* a, float* deltaTime) : player(a), delta(deltaTime) {}
	virtual void execute() override{
		player->ProcessKeyboard(BACKWARD, *delta);
	}
private:
	Player* player;
	float* delta;
};

class DCmd : public Command
{
public:
	DCmd(Player* a, float* deltaTime) : player(a), delta(deltaTime) {}
	virtual void execute() {
		player->ProcessKeyboard(RIGHT, *delta);
	}
private:
	Player* player;
	float* delta;
};
class JumpUp : public Command  
{  
public:  
   JumpUp(Player* a, float* deltaTime) : player(a), delta(deltaTime) {}  
   virtual void execute() override {  
       if (player->onGround)  
       {  
		   player->ProcessKeyboard(JUMP, *delta);
       }  
   }  
private:  
   Player* player;  
   float* delta;  
};





#endif