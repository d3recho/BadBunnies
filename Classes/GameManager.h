#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "cocos2d.h"

class GameManager {

private:
	GameManager();
	static GameManager* m_mySingleton;
	int gameDifficulty;

public:
	static GameManager* sharedGameManager();
	int getGameDifficulty() {return gameDifficulty;}
	void setGameDifficulty(int val) {gameDifficulty = val;}
};

#endif
