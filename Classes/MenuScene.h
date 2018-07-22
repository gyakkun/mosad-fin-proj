#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuStartCallback(cocos2d::Ref* pSender);
	void prelodeMusic();
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
};

#endif // __MENU_SCENE_H__
