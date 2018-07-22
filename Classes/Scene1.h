#ifndef __SCENE1_H__
#define __SCENE1_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
class Scene1 : public cocos2d::Layer {
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	void update(float f);

	void updateGuojing(float f);

	void stand(char k);

	void addKeyboardListener();

	void move(char k);

	void onKeyPressed(EventKeyboard::KeyCode code, Event * event);

	void attack(char k);

	void onKeyReleased(EventKeyboard::KeyCode code, Event * event);

	void guojingAttack();

	void Gameover();

	bool onTouchBegan(Touch *touch, Event *event);

	void onTouchEnded(Touch *touch, Event *event);

	void addTouchListener();

	void skillCollision(EventCustom* event);

	void addCustomListener();

	void preloadMusic();
	// implement the "static create()" method manually
	CREATE_FUNC(Scene1);
private:
	cocos2d::Sprite* player;
	cocos2d::Sprite* bg;
	char movekey='D';
	char attackKey = 'J';
	int num;
	bool isMove;
	bool isAttack;
	bool standComplete = true;
	bool moveComplete = true;
	bool attackComplete = true;
	bool guojingAction = false;
	bool win = false;
	cocos2d::Sprite* guojing;
	list<Sprite*> gj_skills;
	list<Sprite*> zwj_skills1;
	list<Sprite*> zwj_skills2;
	list<Sprite*> zwj_skills3;
	cocos2d::ProgressTimer* HP;
	cocos2d::ProgressTimer* SP;
	cocos2d::ProgressTimer* HP1;
};

#endif // __SCENE1_H__
