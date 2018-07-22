#ifndef __BossScene_H__
#define __BossScene_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;
class BossScene : public cocos2d::Layer {
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	void update(float f);

	void updatedfbb(float f);

	void stand(char k);

	void addKeyboardListener();

	void move(char k);

	void onKeyPressed(EventKeyboard::KeyCode code, Event * event);

	void attack(char k);

	void onKeyReleased(EventKeyboard::KeyCode code, Event * event);

	void dfbbAttack();

	void Gameover();

	bool onTouchBegan(Touch *touch, Event *event);

	void onTouchEnded(Touch *touch, Event *event);

	void addTouchListener();

	void skillCollision(EventCustom* event);

	void addCustomListener();

	void preloadMusic();
	// implement the "static create()" method manually
	CREATE_FUNC(BossScene);
private:
	cocos2d::Sprite* player;
	cocos2d::Sprite* bg;
	char movekey = 'D';
	char attackKey = 'J';
	int num;
	bool isMove;
	bool isAttack;
	bool standComplete = true;
	bool moveComplete = true;
	bool attackComplete = true;
	bool dfbbAction = false;
	bool win = false;
	cocos2d::Sprite* dfbb;
	list<Sprite*> dfbb_skills1;
	list<Sprite*> dfbb_skills2;
	list<Sprite*> dfbb_skills3;
	list<Sprite*> zwj_skills1;
	list<Sprite*> zwj_skills2;
	list<Sprite*> zwj_skills3;
	cocos2d::ProgressTimer* HP;
	cocos2d::ProgressTimer* SP;
	cocos2d::ProgressTimer* HP1;
};

#endif // __BossScene_H__
