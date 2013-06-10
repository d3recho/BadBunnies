#ifndef BUNNY_H_
#define BUNNY_H_

#include "cocos2d.h"

/**
 * Main character class. 
 */
class Bunny : public cocos2d::CCSprite {

public:
	Bunny(int col, int row, cocos2d::CCPoint position);
	int col, row;
	bool isBunnyHit;
	void init(cocos2d::CCLayer& layer);
	void wasHit();
	void setMove(float x, float y);
	void removeBunny(cocos2d::CCNode* pSender);

private:
	cocos2d::CCSprite* pSpriteBunny, pSpriteBunnyHit;
	cocos2d::CCPoint* pPoint;
};

#endif /* BALLOON_H_ */
