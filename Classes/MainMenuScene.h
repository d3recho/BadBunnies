#include "cocos2d.h"
#include "HelloWorldScene.h"

class MainMenu : public cocos2d::CCLayer
{
public:
	MainMenu(void);
	bool init();
	static cocos2d::CCScene* scene();
	void mainMenuStartCallback(cocos2d::CCObject* pSender);
	CREATE_FUNC(MainMenu);
	~MainMenu(void);
};

