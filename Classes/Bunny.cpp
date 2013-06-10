#include "Bunny.h"

using namespace cocos2d;

Bunny::Bunny(int col, int row, CCPoint position) {
	isBunnyHit = false;
	CCSprite::initWithFile("bunny_carrot2.png");
	setAnchorPoint(ccp(0.5f, 1.0f));
	setPosition(position);
	this->col = col;
	this->row = row;
}

void Bunny::removeBunny(CCNode* pSender) {
	
}

void Bunny::wasHit() {
	isBunnyHit = true;
	setTexture(CCTextureCache::sharedTextureCache()->addImage("bunny_hit2.png"));
}

void Bunny::init(cocos2d::CCLayer& layer) {
	//If you don't add this object to the layer,
	//scheduler callback won't be able to access the object properties directly.
//	layer.addChild(this);
}

