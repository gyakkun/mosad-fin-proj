#pragma once
#ifndef __SCENE2_H__
#define __SCENE2_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
class Scene2 : public cocos2d::Layer {
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);
	void addTouchListener();
	void preloadMusic();
	// implement the "static create()" method manually
	CREATE_FUNC(Scene2);
private:
	cocos2d::Sprite* photo;
	int num;
};

#endif // __SCENE2_H__
