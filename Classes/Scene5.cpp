#include "Scene5.h"
#include "MenuScene.h"
#include "BossScene.h"
#include"Monster.h"
#include <algorithm>

USING_NS_CC;

using namespace CocosDenshion;

Scene* Scene5::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Scene5::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Scene5::init() {
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	bg = Sprite::create("Building.jpg");
	bg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(bg, 0);

	Sprite* sp0 = Sprite::create("hp.png");
	Sprite* red = Sprite::create("red.png");

	HP = ProgressTimer::create(red);
	HP->setAnchorPoint(Vec2(0, 0));
	HP->setType(ProgressTimerType::BAR);
	HP->setBarChangeRate(Point(1, 0));
	HP->setMidpoint(Point(0, 1));
	HP->setPercentage(100);
	HP->setPosition(108, 653);
	addChild(HP, 2);
	sp0->setScale(0.62);
	sp0->setAnchorPoint(Vec2(0, 0));
	sp0->setPosition(70, 650);
	addChild(sp0, 1);


	Sprite* sp1 = Sprite::create("sp.png");
	Sprite* blue = Sprite::create("blue.png");
	SP = ProgressTimer::create(blue);
	SP->setAnchorPoint(Vec2(0, 0));
	SP->setType(ProgressTimerType::BAR);
	SP->setBarChangeRate(Point(1, 0));
	SP->setMidpoint(Point(0, 1));
	SP->setPercentage(100);
	SP->setPosition(visibleSize.width - 370, 653);
	addChild(SP, 2);
	sp1->setScale(0.62);
	sp1->setAnchorPoint(Vec2(0, 0));
	sp1->setPosition(visibleSize.width - 408, 650);
	addChild(sp1, 1);

	auto texture = Director::getInstance()->getTextureCache()->addImage("zhangwujistand.png");
	//´ÓÌùÍ¼ÖÐÒÔÏñËØµ¥Î»ÇÐ¸î£¬´´½¨¹Ø¼üÖ¡
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(875, 175, 175, 175)));
	//Ê¹ÓÃµÚÒ»Ö¡´´½¨¾«Áé
	player = Sprite::createWithSpriteFrame(frame0);
	player->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	player->setScale(visibleSize.height*0.25 / player->getContentSize().height);
	schedule(schedule_selector(Scene5::update), 0.01f, kRepeatForever, 0);

	this->addChild(player, 3);
	//±äÁ¿³õÊ¼»¯
	num = 0;
	isMove = false;
	//¼àÌýÆ÷
	addKeyboardListener();
	addCustomListener();

	schedule(schedule_selector(Scene5::createMonster), 2, 10, 0);


	schedule(schedule_selector(Scene5::moveMonster), 2);



	return true;
}
void Scene5::createMonster(float delta) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto factory = Factory::getInstance();
	auto monster = factory->createMonster();
	float x = random(origin.x, origin.x + visibleSize.width);
	float y = random(origin.y, origin.y + visibleSize.height);
	if (x < player->getPositionX())
	{
		auto monster = factory->createMonster();
	}
	monster->setPosition(x, y);
	this->addChild(monster, 3);

	score++;
}

void Scene5::moveMonster(float delta)
{

	auto factory = Factory::getInstance();
	factory->moveMonster(player->getPosition(), 0.8);
}


void Scene5::skillCollision(EventCustom* event) {
	auto factory = Factory::getInstance();
	Sprite* collision = factory->collider(player->getBoundingBox());
	if (collision != NULL) {

		//collision->setVisible(false);
		// Åöµ½ÈËÎïºó¹ÖÎïÏûÊ§
		CCActionInterval* fadeout = CCFadeOut::create(2);
		collision->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("hurt_3")));
		factory->removeMonster(collision);

		if (HP->getPercentage() - 20 > 0) {
			HP->setPercentage(HP->getPercentage() - 20);
		}
		else {
			HP->setPercentage(0);
			Gameover();
		}
	}
	Sprite* temp;
	for (auto it = zwj_skills1.begin(); it != zwj_skills1.end(); it++) {
		temp = (*it);
		Rect playerRect = temp->getBoundingBox();
		Rect attackRect = Rect(playerRect.getMinX() + 20, playerRect.getMinY() + 10,
			playerRect.getMaxX() - playerRect.getMinX() - 10,
			playerRect.getMaxY() - playerRect.getMinY() - 10);
		auto factory = Factory::getInstance();
		Sprite* collision = factory->collider(attackRect);
		if (collision != NULL) {


			CCActionInterval* fadeout = CCFadeOut::create(2);
			collision->runAction(fadeout);
			factory->removeMonster(collision);

		}
	}
	for (auto it = zwj_skills2.begin(); it != zwj_skills2.end(); it++) {
		temp = (*it);
		temp = (*it);
		Rect playerRect = temp->getBoundingBox();
		Rect attackRect = Rect(playerRect.getMinX() + 20, playerRect.getMinY() + 10,
			playerRect.getMaxX() - playerRect.getMinX() - 10,
			playerRect.getMaxY() - playerRect.getMinY() - 10);
		auto factory = Factory::getInstance();
		Sprite* collision = factory->collider(attackRect);
		if (collision != NULL) {


			CCActionInterval* fadeout = CCFadeOut::create(2);
			collision->runAction(fadeout);
			factory->removeMonster(collision);



		}

	}
	for (auto it = zwj_skills3.begin(); it != zwj_skills3.end(); it++) {
		temp = (*it);
		temp = (*it);
		Rect playerRect = temp->getBoundingBox();
		Rect attackRect = Rect(playerRect.getMinX() + 20, playerRect.getMinY() + 10,
			playerRect.getMaxX() - playerRect.getMinX() - 10,
			playerRect.getMaxY() - playerRect.getMinY() - 10);
		auto factory = Factory::getInstance();
		Sprite* collision = factory->collider(attackRect);
		if (collision != NULL) {


			CCActionInterval* fadeout = CCFadeOut::create(2);
			collision->runAction(fadeout);
			factory->removeMonster(collision);





		}
	}
}

void Scene5::addCustomListener() {
	auto customListener1 = EventListenerCustom::create("skillCollision", CC_CALLBACK_1(Scene5::skillCollision, this));
	_eventDispatcher->addEventListenerWithFixedPriority(customListener1, 1);



}

void Scene5::update(float f) {
	if (score >= 10)
	{
		auto factory = Factory::getInstance();
		if (factory->getMonsetnumber() == 0)
		{
			win = true;
			Gameover();
		}
	}
	if (HP->getPercentage() <= 0) {
		win = false;
		Gameover();
	}
	if (SP->getPercentage()<100)
		SP->setPercentage(SP->getPercentage() + 0.05);
	if (isMove) {
		this->move(movekey);
	}
	else if (isAttack) {
		attack(attackKey);
	}
	else if (!isMove && !isAttack)
	{
		stand(movekey);
	}
	//¼¼ÄÜÅö×²
	EventCustom e("skillCollision");
	_eventDispatcher->dispatchEvent(&e);
}
//Õ¾Á¢·½Ïò
void Scene5::stand(char k)
{
	if (!standComplete || !attackComplete)return;
	if (!moveComplete) {
		player->stopAllActions();
		moveComplete = true;
	}
	standComplete = false;
	if (k == 'A')
	{
		auto callFunc = CallFunc::create([&] {standComplete = true; });
		auto seq = Sequence::createWithTwoActions(Animate::create(AnimationCache::getInstance()->getAnimation("leftstandAnimation1")),
			callFunc);

		player->runAction(seq);

	}
	else if (k == 'D')
	{
		auto callFunc = CallFunc::create([&] {standComplete = true; });
		auto seq = Sequence::createWithTwoActions(Animate::create(AnimationCache::getInstance()->getAnimation("rightstandAnimation1")),
			callFunc);

		player->runAction(seq);
	}

	else if (k == 'W')
	{
		auto callFunc = CallFunc::create([&] {standComplete = true; });
		auto seq = Sequence::createWithTwoActions(Animate::create(AnimationCache::getInstance()->getAnimation("upstandAnimation1")),
			callFunc);

		player->runAction(seq);
	}
	else if (k == 'S')
	{
		auto callFunc = CallFunc::create([&] {standComplete = true; });
		auto seq = Sequence::createWithTwoActions(Animate::create(AnimationCache::getInstance()->getAnimation("downstandAnimation1")),
			callFunc);

		player->runAction(seq);
	}
}
//ÒÆ¶¯·½Ïò
void Scene5::move(char k)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//ÒÆ¶¯Ê±²»ÄÜÔÙ´´½¨ÒÆ¶¯¶¯×÷
	if (!moveComplete)return;
	if (!standComplete || !attackComplete) {
		player->stopAllActions();
		standComplete = true;
		attackComplete = true;
	}
	moveComplete = false;
	if (k == 'A')
	{
		auto callFunc = CallFunc::create([&] {moveComplete = true; });
		auto moveAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("leftrunAnimation1"));
		auto spa = Spawn::createWithTwoActions(MoveBy::create(0.4f, Vec2(-50, 0)),
			moveAnimate);
		auto seq = Sequence::createWithTwoActions(moveAnimate, callFunc);
		if (player->getBoundingBox().getMinX() >= 0) {
			seq = Sequence::createWithTwoActions(spa, callFunc);
		}
		player->runAction(seq);

	}
	else if (k == 'D')
	{
		auto callFunc = CallFunc::create([&] {moveComplete = true; });
		auto moveAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("rightrunAnimation1"));
		auto spa = Spawn::createWithTwoActions(MoveBy::create(0.4f, Vec2(50, 0)),
			moveAnimate);
		auto seq = Sequence::createWithTwoActions(moveAnimate, callFunc);
		if (player->getBoundingBox().getMaxX() <= visibleSize.width) {
			seq = Sequence::createWithTwoActions(spa, callFunc);
		}
		player->runAction(seq);

	}

	else if (k == 'W')
	{
		auto callFunc = CallFunc::create([&] {moveComplete = true; });
		auto moveAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("uprunAnimation1"));
		auto spa = Spawn::createWithTwoActions(MoveBy::create(0.4f, Vec2(0, 50)),
			moveAnimate);
		auto seq = Sequence::createWithTwoActions(moveAnimate, callFunc);
		if (player->getBoundingBox().getMaxY() <= visibleSize.height) {
			seq = Sequence::createWithTwoActions(spa, callFunc);
		}
		player->runAction(seq);

	}
	else if (k == 'S')
	{
		auto callFunc = CallFunc::create([&] {moveComplete = true; });
		auto moveAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("downrunAnimation1"));
		auto spa = Spawn::createWithTwoActions(MoveBy::create(0.4f, Vec2(0, -50)),
			moveAnimate);
		auto seq = Sequence::createWithTwoActions(moveAnimate, callFunc);
		if (player->getBoundingBox().getMinY() >= 0) {
			seq = Sequence::createWithTwoActions(spa, callFunc);
		}
		player->runAction(seq);
	}
}

//Ö÷½Ç¹¥»÷
void Scene5::attack(char attackKey)
{
	if (!attackComplete)return;
	if (!standComplete || !moveComplete) {
		standComplete = true;
		moveComplete = true;
		player->stopAllActions();
	}
	if (attackKey == 'J')
	{
		if (SP->getPercentage() - 20 < 0)return;
		SP->setPercentage(SP->getPercentage() - 20);
	}
	else if (attackKey == 'K')
	{
		if (SP->getPercentage() - 30 < 0)return;
		SP->setPercentage(SP->getPercentage() - 30);
	}
	else if (attackKey == 'L')
	{
		if (SP->getPercentage() - 50 < 0)return;
		SP->setPercentage(SP->getPercentage() - 50);
	}


	attackComplete = false;
	char k = movekey;
	Vec2 pp = player->getPosition();

	if (k == 'A')
	{
		auto callFunc = CallFunc::create([&] {attackComplete = true; });
		auto seq = Sequence::createWithTwoActions(Animate::create(AnimationCache::getInstance()->getAnimation("leftattackAnimation1")),
			callFunc);

		player->runAction(seq);


		if (attackKey == 'J') {
			//Ìí¼Ó¼¼ÄÜ
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_skill_1.png");
			//´ÓÌùÍ¼ÖÐÒÔÏñËØµ¥Î»ÇÐ¸î£¬´´½¨¹Ø¼üÖ¡
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			//Ê¹ÓÃµÚÒ»Ö¡´´½¨¾«Áé
			auto skill = Sprite::createWithSpriteFrame(frame0);
			skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
			skill->setPosition(pp);
			this->addChild(skill, 4);
			zwj_skills1.push_back(skill);
			auto temp = skill;
			skill->runAction(Sequence::create(
				Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_1")),
					MoveTo::create(2.7f, Vec2(pp.x - 500, pp.y)), nullptr),
				CallFunc::create([skill, temp, this] {
				zwj_skills1.remove(skill);
				temp->removeFromParentAndCleanup(true);
			}), nullptr));
		}
		else if (attackKey == 'K') {
			//Ìí¼Ó¼¼ÄÜ
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_attack_taichi_1.png");
			//´ÓÌùÍ¼ÖÐÒÔÏñËØµ¥Î»ÇÐ¸î£¬´´½¨¹Ø¼üÖ¡
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			for (int i = 1; i <= 3; i++) {
				//Ê¹ÓÃµÚÒ»Ö¡´´½¨¾«Áé
				auto skill = Sprite::createWithSpriteFrame(frame0);
				skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
				skill->setPosition(pp);
				this->addChild(skill, 4);
				zwj_skills2.push_back(skill);
				auto temp = skill;
				skill->runAction(Sequence::create(
					Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_2")),
						MoveTo::create(1.8f, Vec2(pp.x - 500, pp.y + 200 * (i - 2))), nullptr),
					CallFunc::create([skill, temp, this] {
					zwj_skills2.remove(skill);
					temp->removeFromParentAndCleanup(true);
				}), nullptr));
			}
		}
		else if (attackKey == 'L') {
			//Ìí¼Ó¼¼ÄÜ
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_attack_taichi_2.png");
			//´ÓÌùÍ¼ÖÐÒÔÏñËØµ¥Î»ÇÐ¸î£¬´´½¨¹Ø¼üÖ¡
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));

			for (int i = -2; i <= 2; i++) {
				for (int j = -2; j <= 2; j++) {

					//Ê¹ÓÃµÚÒ»Ö¡´´½¨¾«Áé
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(pp.x + 100 * i, pp.y + 100 * j);
					this->addChild(skill, 4);
					zwj_skills3.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_3")),
							MoveTo::create(2.25f, Vec2(pp.x + 500 * i, pp.y + 500 * j)), nullptr),
						CallFunc::create([skill, temp, this] {
						zwj_skills3.remove(skill);
						temp->removeFromParentAndCleanup(true);
					}), nullptr));
				}


			}

		}
	}
	else if (k == 'D')
	{
		auto callFunc = CallFunc::create([&] {attackComplete = true; });
		auto seq = Sequence::createWithTwoActions(Animate::create(AnimationCache::getInstance()->getAnimation("rightattackAnimation1")),
			callFunc);

		player->runAction(seq);

		if (attackKey == 'J') {
			//Ìí¼Ó¼¼ÄÜ
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_skill_1.png");
			//´ÓÌùÍ¼ÖÐÒÔÏñËØµ¥Î»ÇÐ¸î£¬´´½¨¹Ø¼üÖ¡
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			//Ê¹ÓÃµÚÒ»Ö¡´´½¨¾«Áé
			auto skill = Sprite::createWithSpriteFrame(frame0);
			skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
			skill->setPosition(pp);
			this->addChild(skill, 4);
			zwj_skills1.push_back(skill);
			auto temp = skill;
			skill->runAction(Sequence::create(
				Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_1")),
					MoveTo::create(2.7f, Vec2(pp.x + 500, pp.y)), nullptr),
				CallFunc::create([skill, temp, this] {
				zwj_skills1.remove(skill);
				temp->removeFromParentAndCleanup(true);
			}), nullptr));
		}
		else if (attackKey == 'K') {
			//Ìí¼Ó¼¼ÄÜ
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_attack_taichi_1.png");
			//´ÓÌùÍ¼ÖÐÒÔÏñËØµ¥Î»ÇÐ¸î£¬´´½¨¹Ø¼üÖ¡
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			for (int i = 1; i <= 3; i++) {
				//Ê¹ÓÃµÚÒ»Ö¡´´½¨¾«Áé
				auto skill = Sprite::createWithSpriteFrame(frame0);
				skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
				skill->setPosition(pp);
				this->addChild(skill, 4);
				zwj_skills2.push_back(skill);
				auto temp = skill;
				skill->runAction(Sequence::create(
					Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_2")),
						MoveTo::create(1.8f, Vec2(pp.x + 500, pp.y + 200 * (i - 2))), nullptr),
					CallFunc::create([skill, temp, this] {
					zwj_skills2.remove(skill);
					temp->removeFromParentAndCleanup(true);
				}), nullptr));
			}
		}
		else if (attackKey == 'L') {
			//Ìí¼Ó¼¼ÄÜ
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_attack_taichi_2.png");
			//´ÓÌùÍ¼ÖÐÒÔÏñËØµ¥Î»ÇÐ¸î£¬´´½¨¹Ø¼üÖ¡
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));

			for (int i = -2; i <= 2; i++) {
				for (int j = -2; j <= 2; j++) {

					//Ê¹ÓÃµÚÒ»Ö¡´´½¨¾«Áé
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(pp.x + 100 * i, pp.y + 100 * j);
					this->addChild(skill, 4);
					zwj_skills3.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_3")),
							MoveTo::create(2.25f, Vec2(pp.x + 500 * i, pp.y + 500 * j)), nullptr),
						CallFunc::create([skill, temp, this] {
						zwj_skills3.remove(skill);
						temp->removeFromParentAndCleanup(true);
					}), nullptr));
				}


			}

		}
	}

	else if (k == 'W')
	{
		auto callFunc = CallFunc::create([&] {attackComplete = true; });
		auto seq = Sequence::createWithTwoActions(Animate::create(AnimationCache::getInstance()->getAnimation("upattackAnimation1")),
			callFunc);

		player->runAction(seq);

		if (attackKey == 'J') {
			//Ìí¼Ó¼¼ÄÜ
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_skill_1.png");
			//´ÓÌùÍ¼ÖÐÒÔÏñËØµ¥Î»ÇÐ¸î£¬´´½¨¹Ø¼üÖ¡
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			//Ê¹ÓÃµÚÒ»Ö¡´´½¨¾«Áé
			auto skill = Sprite::createWithSpriteFrame(frame0);
			skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
			skill->setPosition(pp);
			this->addChild(skill, 4);
			zwj_skills1.push_back(skill);
			auto temp = skill;
			skill->runAction(Sequence::create(
				Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_1")),
					MoveTo::create(2.7f, Vec2(pp.x, pp.y + 500)), nullptr),
				CallFunc::create([skill, temp, this] {
				zwj_skills1.remove(skill);
				temp->removeFromParentAndCleanup(true);
			}), nullptr));


		}
		else if (attackKey == 'K') {
			//Ìí¼Ó¼¼ÄÜ
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_attack_taichi_1.png");
			//´ÓÌùÍ¼ÖÐÒÔÏñËØµ¥Î»ÇÐ¸î£¬´´½¨¹Ø¼üÖ¡
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			for (int i = 1; i <= 3; i++) {
				//Ê¹ÓÃµÚÒ»Ö¡´´½¨¾«Áé
				auto skill = Sprite::createWithSpriteFrame(frame0);
				skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
				skill->setPosition(pp);
				this->addChild(skill, 4);
				zwj_skills2.push_back(skill);
				auto temp = skill;
				skill->runAction(Sequence::create(
					Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_2")),
						MoveTo::create(1.8f, Vec2(pp.x + 200 * (i - 2), pp.y + 500)), nullptr),
					CallFunc::create([skill, temp, this] {
					zwj_skills2.remove(skill);
					temp->removeFromParentAndCleanup(true);
				}), nullptr));
			}


		}
		else if (attackKey == 'L') {
			//Ìí¼Ó¼¼ÄÜ
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_attack_taichi_2.png");
			//´ÓÌùÍ¼ÖÐÒÔÏñËØµ¥Î»ÇÐ¸î£¬´´½¨¹Ø¼üÖ¡
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));

			for (int i = -2; i <= 2; i++) {
				for (int j = -2; j <= 2; j++) {

					//Ê¹ÓÃµÚÒ»Ö¡´´½¨¾«Áé
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(pp.x + 100 * i, pp.y + 100 * j);
					this->addChild(skill, 4);
					zwj_skills3.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_3")),
							MoveTo::create(2.25f, Vec2(pp.x + 500 * i, pp.y + 500 * j)), nullptr),
						CallFunc::create([skill, temp, this] {
						zwj_skills3.remove(skill);
						temp->removeFromParentAndCleanup(true);
					}), nullptr));
				}


			}

		}
	}
	else if (k == 'S')
	{
		auto callFunc = CallFunc::create([&] {attackComplete = true; });
		auto seq = Sequence::createWithTwoActions(Animate::create(AnimationCache::getInstance()->getAnimation("downattackAnimation1")),
			callFunc);

		player->runAction(seq);

		if (attackKey == 'J') {
			//Ìí¼Ó¼¼ÄÜ
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_skill_1.png");
			//´ÓÌùÍ¼ÖÐÒÔÏñËØµ¥Î»ÇÐ¸î£¬´´½¨¹Ø¼üÖ¡
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			//Ê¹ÓÃµÚÒ»Ö¡´´½¨¾«Áé
			auto skill = Sprite::createWithSpriteFrame(frame0);
			skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
			skill->setPosition(pp);
			this->addChild(skill, 4);
			zwj_skills1.push_back(skill);
			auto temp = skill;
			skill->runAction(Sequence::create(
				Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_1")),
					MoveTo::create(2.7f, Vec2(pp.x, pp.y - 500)), nullptr),
				CallFunc::create([skill, temp, this] {
				zwj_skills1.remove(skill);
				temp->removeFromParentAndCleanup(true);
			}), nullptr));
		}
		else if (attackKey == 'K') {
			//Ìí¼Ó¼¼ÄÜ
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_attack_taichi_1.png");
			//´ÓÌùÍ¼ÖÐÒÔÏñËØµ¥Î»ÇÐ¸î£¬´´½¨¹Ø¼üÖ¡
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			for (int i = 1; i <= 3; i++) {
				//Ê¹ÓÃµÚÒ»Ö¡´´½¨¾«Áé
				auto skill = Sprite::createWithSpriteFrame(frame0);
				skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
				skill->setPosition(pp);
				this->addChild(skill, 4);
				zwj_skills2.push_back(skill);
				auto temp = skill;
				skill->runAction(Sequence::create(
					Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_2")),
						MoveTo::create(1.8f, Vec2(pp.x + 200 * (i - 2), pp.y - 500)), nullptr),
					CallFunc::create([skill, temp, this] {
					zwj_skills2.remove(skill);
					temp->removeFromParentAndCleanup(true);
				}), nullptr));
			}
		}
		else if (attackKey == 'L') {
			//Ìí¼Ó¼¼ÄÜ
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_attack_taichi_2.png");
			//´ÓÌùÍ¼ÖÐÒÔÏñËØµ¥Î»ÇÐ¸î£¬´´½¨¹Ø¼üÖ¡
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));

			for (int i = -2; i <= 2; i++) {
				for (int j = -2; j <= 2; j++) {

					//Ê¹ÓÃµÚÒ»Ö¡´´½¨¾«Áé
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(pp.x + 100 * i, pp.y + 100 * j);
					this->addChild(skill, 4);
					zwj_skills3.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_3")),
							MoveTo::create(2.25f, Vec2(pp.x + 500 * i, pp.y + 500 * j)), nullptr),
						CallFunc::create([skill, temp, this] {
						zwj_skills3.remove(skill);
						temp->removeFromParentAndCleanup(true);
					}), nullptr));
				}


			}

		}
	}
}

void Scene5::addKeyboardListener() {
	// ¼üÅÌ¼àÌý
	auto KeyBoardListener = EventListenerKeyboard::create();
	KeyBoardListener->onKeyPressed = CC_CALLBACK_2(Scene5::onKeyPressed, this);
	KeyBoardListener->onKeyReleased = CC_CALLBACK_2(Scene5::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(KeyBoardListener, player);
}

//°´ÏÂ¼üÅÌ
void Scene5::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {
	switch (code) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
	case EventKeyboard::KeyCode::KEY_A:
		movekey = 'A';
		isMove = true;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_CAPITAL_W:
	case EventKeyboard::KeyCode::KEY_W:
		movekey = 'W';
		isMove = true;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
	case EventKeyboard::KeyCode::KEY_D:
		movekey = 'D';
		isMove = true;
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_CAPITAL_S:
	case EventKeyboard::KeyCode::KEY_S:
		movekey = 'S';
		isMove = true;
		break;
	case EventKeyboard::KeyCode::KEY_J:
	case EventKeyboard::KeyCode::KEY_CAPITAL_J:
	case EventKeyboard::KeyCode::KEY_1:
		attackKey = 'J';
		isAttack = true;
		break;
	case EventKeyboard::KeyCode::KEY_K:
	case EventKeyboard::KeyCode::KEY_CAPITAL_K:
	case EventKeyboard::KeyCode::KEY_2:
		attackKey = 'K';
		isAttack = true;
		break;
	case EventKeyboard::KeyCode::KEY_L:
	case EventKeyboard::KeyCode::KEY_CAPITAL_L:
	case EventKeyboard::KeyCode::KEY_3:
		attackKey = 'L';
		isAttack = true;
		break;
	}
}

//ËÉ¿ª°´¼ü
void Scene5::onKeyReleased(EventKeyboard::KeyCode code, Event* event) {
	switch (code) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_CAPITAL_W:
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_CAPITAL_S:
	case EventKeyboard::KeyCode::KEY_S:
		isMove = false;
		break;
	case EventKeyboard::KeyCode::KEY_J:
	case EventKeyboard::KeyCode::KEY_CAPITAL_J:
	case EventKeyboard::KeyCode::KEY_1:
	case EventKeyboard::KeyCode::KEY_K:
	case EventKeyboard::KeyCode::KEY_CAPITAL_K:
	case EventKeyboard::KeyCode::KEY_2:
	case EventKeyboard::KeyCode::KEY_L:
	case EventKeyboard::KeyCode::KEY_CAPITAL_L:
	case EventKeyboard::KeyCode::KEY_3:
		isAttack = false;
		break;
	}
}
//Ô¤ÔØÒôÀÖ
void Scene5::preloadMusic() {
	auto audio = SimpleAudioEngine::getInstance();
	//->preloadBackgroundMusic("music/bgm.mp3");
	//audio->preloadEffect("music/explore.wav");
	audio->preloadEffect("music/dragon.wav");
}

void Scene5::addTouchListener() {
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(Scene5::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Scene5::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool Scene5::onTouchBegan(Touch *touch, Event *event) {
	return true;
}

void Scene5::onTouchEnded(Touch *touch, Event *event) {

	if (win) {
		auto scene = BossScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
	}
	else {
		auto scene = MenuScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
	}
}

void Scene5::Gameover()
{
	player->stopAllActions();
	_eventDispatcher->removeAllEventListeners();
	unschedule(schedule_selector(Scene5::update));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	bg = win ? Sprite::create("Scene3_CG/Scene4_11.jpg") : Sprite::create("Scene3_CG/be3.jpg");
	bg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	bg->setScale(visibleSize.width / bg->getContentSize().width);
	this->addChild(bg, 6);
	addTouchListener();
}