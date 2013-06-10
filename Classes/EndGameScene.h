#include "cocos2d.h"
#include "HelloWorldScene.h"

class EndGame : public cocos2d::CCLayer
{
public:
	EndGame(void);
	bool init();
	static cocos2d::CCScene* scene();
	void endGameStartCallback(cocos2d::CCObject* pSender);
	CREATE_FUNC(EndGame);
	~EndGame(void);
};

