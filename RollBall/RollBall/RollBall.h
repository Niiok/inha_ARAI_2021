#pragma once

#include "oun.h"
#include "SDL_State.h"
#include "SDL_cTexture.h"

#include "iRollBall.h"
#include "RB_Manager.h"
#include "RB_Player.h"
#include "RB_Object.h"


class RB_Player;
class RB_Object;
class RB_UI;
class oun::World;



class RollBall 
	: public SDL_State, public iRollBall
{

public:
	RollBall();
	~RollBall();

	// SDL_State
	inline void Input() override;
	inline void Process() override;
	inline void Output() override;

	//iRollBall
	RB_Player* getPlayer() override { return player_; }
	int getLonger() override { return longer_screen_; }
	const oun::World& getWorld() override { return world_; }
	std::set<RB_Object*>& getObjects() override { return objects_; }

private:	
	SDL_cTexture* background_;
	oun::World world_;
	//RB_UI ui_;
	RB_Player* player_;
	std::set<RB_Object*> objects_;
	int longer_screen_;

	uint64_t initial_time_;
	uint64_t time_limit_ = 2000;
	bool game_end_ = false;

};

