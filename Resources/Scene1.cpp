#include "Scene1.h"
#include <algorithm>

USING_NS_CC;

using namespace CocosDenshion;

Scene* Scene1::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Scene1::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Scene1::init() {
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	bg = Sprite::create("Cave.jpg");
	bg->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
	this->addChild(bg, 1);

	Sprite* sp0 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* sp = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));

	HP = ProgressTimer::create(sp);
	HP->setScaleX(90);
	HP->setAnchorPoint(Vec2(0, 0));
	HP->setType(ProgressTimerType::BAR);
	HP->setBarChangeRate(Point(1, 0));
	HP->setMidpoint(Point(0, 1));
	HP->setPercentage(100);
	HP->setPosition(Vec2(origin.x + 14 * HP->getContentSize().width, origin.y + visibleSize.height - 2 * HP->getContentSize().height - 50));
	addChild(HP, 2);
	sp0->setAnchorPoint(Vec2(0, 0));
	sp0->setPosition(Vec2(origin.x + HP->getContentSize().width, origin.y + visibleSize.height - sp0->getContentSize().height - 50));
	addChild(sp0, 1);


	Sprite* sp1 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	SP = ProgressTimer::create(sp);
	SP->setScaleX(90);
	SP->setAnchorPoint(Vec2(0, 0));
	SP->setType(ProgressTimerType::BAR);
	SP->setBarChangeRate(Point(1, 0));
	SP->setMidpoint(Point(0, 1));
	SP->setPercentage(100);
	SP->setPosition(Vec2(origin.x + 14 * HP->getContentSize().width, origin.y + visibleSize.height - 2 * HP->getContentSize().height - 120));
	addChild(SP, 2);
	sp1->setAnchorPoint(Vec2(0, 0));
	sp1->setPosition(Vec2(origin.x + SP->getContentSize().width, origin.y + visibleSize.height - sp1->getContentSize().height - 120));
	addChild(sp1, 1);

	Sprite* sp2 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	HP1 = ProgressTimer::create(sp);
	HP1->setScaleX(90);
	HP1->setAnchorPoint(Vec2(0, 0));
	HP1->setType(ProgressTimerType::BAR);
	HP1->setBarChangeRate(Point(1, 0));
	HP1->setMidpoint(Point(0, 1));
	HP1->setPercentage(100);
	HP1->setPosition(Vec2(origin.x + 14 * HP1->getContentSize().width, origin.y + visibleSize.height - 2 * HP1->getContentSize().height - 520));
	addChild(HP1, 2);
	sp2->setAnchorPoint(Vec2(0, 0));
	sp2->setPosition(Vec2(origin.x + SP->getContentSize().width, origin.y + visibleSize.height - sp1->getContentSize().height - 520));
	addChild(sp2, 1);

	auto texture = Director::getInstance()->getTextureCache()->addImage("zhangwujistand.png");
	//从贴图中以像素单位切割，创建关键帧
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(875, 175, 175, 175)));
	//使用第一帧创建精灵
	player = Sprite::createWithSpriteFrame(frame0);
	player->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	player->setScale(visibleSize.height*0.25/player->getContentSize().height);
	schedule(schedule_selector(Scene1::update), 0.01f, kRepeatForever, 0);

	this->addChild(player,3);
	//添加郭靖
	texture = Director::getInstance()->getTextureCache()->addImage("guojingstand.png");
	//从贴图中以像素单位切割，创建关键帧
	frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(320, 160, 160, 160)));
	//使用第一帧创建精灵
	guojing = Sprite::createWithSpriteFrame(frame0);
	guojing->setScale(visibleSize.height*0.25 / guojing->getContentSize().height);
	guojing->setPosition(Vec2(visibleSize.width / 2 + origin.x + 200, visibleSize.height / 2 + origin.y));
	this->addChild(guojing,2);
	schedule(schedule_selector(Scene1::updateGuojing), 0.4f, kRepeatForever, 0);
	//变量初始化
	isMove = false;
	//监听器
	addKeyboardListener();
	addCustomListener();
	return true;
}

void Scene1::updateGuojing(float f) {
	if (guojingAction)return;
	guojingAction = true;
	Vec2 pp = player->getPosition();
	Vec2 gp = guojing->getPosition();
	auto callFunc1 = CallFunc::create([&] {guojingAttack(); });
	//判断移动方向
	if (abs(pp.x-gp.x) > abs(pp.y-gp.y)) {
		if (pp.x > gp.x) {
			Repeat* animate = Repeat::create(Animate::create(AnimationCache::getInstance()->getAnimation("rightrunAnimation2")), (pp.x - gp.x) / 100 + 1);
			auto spa = Spawn::createWithTwoActions(MoveTo::create((pp.x-gp.x)/100,Vec2(pp.x,gp.y)),
				animate);
			auto seq = Sequence::create(spa,
				callFunc1, nullptr);
				guojing->runAction(seq);
		}
		else {
			Repeat* animate = Repeat::create(Animate::create(AnimationCache::getInstance()->getAnimation("leftrunAnimation2")), (gp.x - pp.x) / 100 + 1);
			auto spa = Spawn::createWithTwoActions(MoveTo::create((gp.x - pp.x)/100, Vec2(pp.x, gp.y)),
				animate);
			auto seq = Sequence::create(spa,
				callFunc1, nullptr);
			guojing->runAction(seq);
		}
	}
	else {
		if (pp.y > gp.y) {
			Repeat* animate = Repeat::create(Animate::create(AnimationCache::getInstance()->getAnimation("uprunAnimation2")), (pp.y - gp.y) / 100 + 1);
			auto spa = Spawn::createWithTwoActions(MoveTo::create((pp.y - gp.y)/100, Vec2(gp.x, pp.y)),
				animate);
			auto seq = Sequence::create(spa,
				callFunc1, nullptr);
			guojing->runAction(seq);
		}
		else {
			Repeat* animate = Repeat::create(Animate::create(AnimationCache::getInstance()->getAnimation("downrunAnimation2")), (gp.y - pp.y) / 100 + 1);
			auto spa = Spawn::createWithTwoActions(MoveTo::create((gp.y - pp.y) /100, Vec2(gp.x, pp.y)),
				animate);
			auto seq = Sequence::create(spa,
				callFunc1, nullptr);
			guojing->runAction(seq);
		}
	}

}
//郭靖攻击，包括攻击方向，技能特效及飞出方向
void Scene1::guojingAttack() {
	//一次动作包括移动和攻击，攻击完毕后设为false
	auto callFunc = CallFunc::create([&] {guojingAction = false; });
	Vec2 pp = player->getPosition();
	Vec2 gp = guojing->getPosition();
	//添加技能
	auto texture = Director::getInstance()->getTextureCache()->addImage("gj_attack_1.png");
	//从贴图中以像素单位切割，创建关键帧
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));

	int r = 1 + rand() % 3;
	SimpleAudioEngine::getInstance()->playEffect("music/dragon.wav");
	if (abs(pp.x - gp.x) > abs(pp.y - gp.y)) {
		if (pp.x > gp.x) {
			Sequence* seq = Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("rightattackAnimation2")),
				callFunc,nullptr);
			guojing->runAction(seq);
			for (int i = 1; i <= r; i++) {
				Animate* skill1_animate = Animate::create(AnimationCache::getInstance()->getAnimation("gj_attack_1"));
				//使用第一帧创建精灵
				auto skill1 = Sprite::createWithSpriteFrame(frame0);
				skill1->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill1->getContentSize().height);
				skill1->setPosition(gp);
				this->addChild(skill1,4);
				gj_skills.push_back(skill1);
				if ((r == 2 && i == 2) || r == 1) i++;
				auto temp = skill1;
				skill1->runAction(Sequence::create(
					Spawn::create(skill1_animate, MoveTo::create(3, Vec2(gp.x + 500, gp.y+ 200 * (i - 2))), nullptr),
					CallFunc::create([skill1, temp, this] {
					gj_skills.remove(skill1);
					temp->removeFromParentAndCleanup(true);
				}), nullptr));
			}
		}
		else {
			Sequence* seq = Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("leftattackAnimation2")),
				callFunc, nullptr);
			guojing->runAction(seq);

			for (int i = 1; i <= r; i++) {
				Animate* skill1_animate = Animate::create(AnimationCache::getInstance()->getAnimation("gj_attack_1"));
				//使用第一帧创建精灵
				auto skill1 = Sprite::createWithSpriteFrame(frame0);
				skill1->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill1->getContentSize().height);
				skill1->setPosition(gp);
				this->addChild(skill1,4);
				gj_skills.push_back(skill1);
				auto temp = skill1;
				if ((r == 2&& i == 2 )|| r == 1) i++;
				skill1->runAction(Sequence::create(
					Spawn::create(skill1_animate, MoveTo::create(3, Vec2(gp.x - 500, gp.y + 200 *(i - 2))), nullptr),
					CallFunc::create([skill1, temp, this] {
					gj_skills.remove(skill1);
					temp->removeFromParentAndCleanup(true);
				}), nullptr));
			}
		}
	}
	else {
		if (pp.y > gp.y) {
			Sequence* seq = Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("upattackAnimation2")),
				callFunc, nullptr);
			guojing->runAction(seq);

			for (int i = 1; i <= r; i++) {
				Animate* skill1_animate = Animate::create(AnimationCache::getInstance()->getAnimation("gj_attack_1"));
				//使用第一帧创建精灵
				auto skill1 = Sprite::createWithSpriteFrame(frame0);
				skill1->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill1->getContentSize().height);
				skill1->setPosition(gp);
				this->addChild(skill1,4);
				gj_skills.push_back(skill1);
				auto temp = skill1;
				if ((r == 2 && i == 2) || r == 1) i++;
				skill1->runAction(Sequence::create(
					Spawn::create(skill1_animate, MoveTo::create(3, Vec2(gp.x + 200 * (i - 2), gp.y + 500)), nullptr),
					CallFunc::create([skill1, temp, this] {
					gj_skills.remove(skill1);
					temp->removeFromParentAndCleanup(true);
				}), nullptr));
			}
		}
		else {
			Sequence* seq = Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("downattackAnimation2")),
				callFunc, nullptr);
			guojing->runAction(seq);

			for (int i = 1; i <= r; i++) {
				Animate* skill1_animate = Animate::create(AnimationCache::getInstance()->getAnimation("gj_attack_1"));
				auto skill1 = Sprite::createWithSpriteFrame(frame0);
				skill1->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill1->getContentSize().height);
				skill1->setPosition(gp);
				this->addChild(skill1,4);
				gj_skills.push_back(skill1);
				auto temp = skill1;
				if ((r == 2 && i == 2) || r == 1) i++;
				skill1->runAction(Sequence::create(
					Spawn::create(skill1_animate, MoveTo::create(3, Vec2(gp.x + 200 * (i - 2), gp.y - 500)), nullptr),
					CallFunc::create([skill1, temp, this] {
					gj_skills.remove(skill1);
					temp->removeFromParentAndCleanup(true);
				}), nullptr));
			}
		}
	}
}
void Scene1::Gameover()
{
	stopAllActions();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	bg = Sprite::create("shibai.jpg");
	bg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(bg, 1);
}

void Scene1::Win()
{

}
//技能碰撞检测
void Scene1::skillCollision(EventCustom* event) {
	Sprite* temp;
	for (auto it = gj_skills.begin(); it != gj_skills.end(); it++) {
		temp = (*it);
		if (player->getBoundingBox().containsPoint((*it)->getPosition())) {
			if (HP->getPercentage() - 4 <= 0)
			{
				Gameover();
			}
			HP->setPercentage(HP->getPercentage() - 4);

			temp->stopAllActions();
			gj_skills.remove(temp);
			temp->removeFromParentAndCleanup(true);
			//添加技能
			auto texture = Director::getInstance()->getTextureCache()->addImage("hurt_3.png");
			//从贴图中以像素单位切割，创建关键帧
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			//使用第一帧创建精灵
			auto hurt = Sprite::createWithSpriteFrame(frame0);
			hurt->setScale(Director::getInstance()->getVisibleSize().height*0.25 / hurt->getContentSize().height);
			hurt->setPosition(player->getPosition());
			this->addChild(hurt, 4);
			hurt->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("hurt_3")),
				CallFunc::create([hurt, this] {
				hurt->removeFromParentAndCleanup(true);
			})
			,nullptr));
			break;
		}
	}
	for (auto it = zwj_skills1.begin(); it != zwj_skills1.end(); it++) {
		temp = (*it);
		if (guojing->getBoundingBox().containsPoint((*it)->getPosition())) {
			if(HP1->getPercentage()-3<=0)
			{
				HP1->setPercentage(0);
					Win();
			}
			
			HP1->setPercentage(HP1->getPercentage() - 3);

			temp->stopAllActions();
			zwj_skills1.remove(temp);
			temp->removeFromParentAndCleanup(true);
			//添加技能
			auto texture = Director::getInstance()->getTextureCache()->addImage("hurt_3.png");
			//从贴图中以像素单位切割，创建关键帧
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			//使用第一帧创建精灵
			auto hurt = Sprite::createWithSpriteFrame(frame0);
			hurt->setScale(Director::getInstance()->getVisibleSize().height*0.25 / hurt->getContentSize().height);
			hurt->setPosition(guojing->getPosition());
			this->addChild(hurt, 4);
			hurt->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("hurt_3")),
				CallFunc::create([hurt, this] {
				hurt->removeFromParentAndCleanup(true);
			})
				, nullptr));
			break;
		}
	}
	for (auto it = zwj_skills2.begin(); it != zwj_skills2.end(); it++) {
		temp = (*it);
		if (guojing->getBoundingBox().containsPoint((*it)->getPosition())) {
			if (HP1->getPercentage() - 2 <= 0)
			{
				HP1->setPercentage(0);
				Win();
			}
			HP1->setPercentage(HP1->getPercentage() - 2);
			
			temp->stopAllActions();
			zwj_skills2.remove(temp);
			temp->removeFromParentAndCleanup(true);
			//添加技能
			auto texture = Director::getInstance()->getTextureCache()->addImage("hurt_2.png");
			//从贴图中以像素单位切割，创建关键帧
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			//使用第一帧创建精灵
			auto hurt = Sprite::createWithSpriteFrame(frame0);
			hurt->setScale(Director::getInstance()->getVisibleSize().height*0.25 / hurt->getContentSize().height);
			hurt->setPosition(guojing->getPosition());
			this->addChild(hurt, 4);
			hurt->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("hurt_2")),
				CallFunc::create([hurt, this] {
				hurt->removeFromParentAndCleanup(true);
			})
				, nullptr));
			break;
		}
	}
	for (auto it = zwj_skills3.begin(); it != zwj_skills3.end(); it++) {
		temp = (*it);
		if (guojing->getBoundingBox().containsPoint((*it)->getPosition())) {
			if (HP1->getPercentage() - 1 <= 0)
			{
				HP1->setPercentage(0);
				Win();
			}
			HP1->setPercentage(HP1->getPercentage() - 1);
			
			temp->stopAllActions();
			zwj_skills3.remove(temp);
			temp->removeFromParentAndCleanup(true);
			//添加技能
			auto texture = Director::getInstance()->getTextureCache()->addImage("hurt_1.png");
			//从贴图中以像素单位切割，创建关键帧
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			//使用第一帧创建精灵
			auto hurt = Sprite::createWithSpriteFrame(frame0);
			hurt->setScale(Director::getInstance()->getVisibleSize().height*0.25 / hurt->getContentSize().height);
			hurt->setPosition(guojing->getPosition());
			this->addChild(hurt, 4);
			hurt->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("hurt_1")),
				CallFunc::create([hurt, this] {
				hurt->removeFromParentAndCleanup(true);
			})
				, nullptr));
			break;
		}
	}
}

void Scene1::addCustomListener() {
	auto customListener1 = EventListenerCustom::create("skillCollision", CC_CALLBACK_1(Scene1::skillCollision, this));
	_eventDispatcher->addEventListenerWithFixedPriority(customListener1, 1);
}

void Scene1::update(float f) {
	if (SP->getPercentage()<100)
		SP->setPercentage(SP->getPercentage() + 0.05);
	if (isMove) {
		this->move(movekey);
	}
	else if (isAttack) {
		attack(attackKey);
	}
	else if(!isMove&&!isAttack)
	{
		stand(movekey);
	}
	//技能碰撞
	EventCustom e("skillCollision");
	_eventDispatcher->dispatchEvent(&e);
}
//站立方向
void Scene1::stand(char k)
{
	if (!standComplete||!attackComplete)return;
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
//移动方向
void Scene1::move(char k)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//移动时不能再创建移动动作
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

//主角攻击
void Scene1::attack(char attackKey)
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
	Vec2 gp = guojing->getPosition();
	
	if (k == 'A')
	{
		auto callFunc = CallFunc::create([&] {attackComplete = true; });
		auto seq = Sequence::createWithTwoActions(Animate::create(AnimationCache::getInstance()->getAnimation("leftattackAnimation1")),
			callFunc);

		player->runAction(seq);

		
		if (attackKey == 'J') {
			//添加技能
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_skill_1.png");
			//从贴图中以像素单位切割，创建关键帧
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			//使用第一帧创建精灵
			auto skill = Sprite::createWithSpriteFrame(frame0);
			skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
			skill->setPosition(pp);
			this->addChild(skill, 4);
			zwj_skills1.push_back(skill);
			auto temp = skill;
			skill->runAction(Sequence::create(
				Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_1")),
					MoveTo::create(2.7f, Vec2(pp.x - 500,pp.y)), nullptr),
				CallFunc::create([skill, temp, this] {
				zwj_skills1.remove(skill);
				temp->removeFromParentAndCleanup(true);
			}), nullptr));
		}
		else if(attackKey == 'K'){
			//添加技能
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_attack_taichi_1.png");
			//从贴图中以像素单位切割，创建关键帧
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			for (int i = 1; i <= 3; i ++) {
				//使用第一帧创建精灵
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
			//添加技能
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_attack_taichi_2.png");
			//从贴图中以像素单位切割，创建关键帧
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));

			for (int i = -2; i <= 2; i++) {
				for (int j = -2; j <= 2; j ++) {

					//使用第一帧创建精灵
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(gp.x+100*i,gp.y + 100*j);
					this->addChild(skill, 4);
					zwj_skills3.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_3")),
							MoveTo::create(2.25f, gp), nullptr),
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
			//添加技能
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_skill_1.png");
			//从贴图中以像素单位切割，创建关键帧
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			//使用第一帧创建精灵
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
			//添加技能
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_attack_taichi_1.png");
			//从贴图中以像素单位切割，创建关键帧
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			for (int i = 1; i <= 3; i++) {
				//使用第一帧创建精灵
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
			//添加技能
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_attack_taichi_2.png");
			//从贴图中以像素单位切割，创建关键帧
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));

			for (int i = -2; i <= 2; i++) {
				for (int j = -2; j <= 2; j++) {

					//使用第一帧创建精灵
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(gp.x + 100 * i, gp.y + 100 * j);
					this->addChild(skill, 4);
					zwj_skills3.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_3")),
							MoveTo::create(2.25f, gp), nullptr),
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
			//添加技能
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_skill_1.png");
			//从贴图中以像素单位切割，创建关键帧
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			//使用第一帧创建精灵
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
			//添加技能
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_attack_taichi_1.png");
			//从贴图中以像素单位切割，创建关键帧
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			for (int i = 1; i <= 3; i++) {
				//使用第一帧创建精灵
				auto skill = Sprite::createWithSpriteFrame(frame0);
				skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
				skill->setPosition(pp);
				this->addChild(skill, 4);
				zwj_skills2.push_back(skill);
				auto temp = skill;
				skill->runAction(Sequence::create(
					Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_2")),
						MoveTo::create(1.8f, Vec2(pp.x + 200 * (i - 2), pp.y + 500 )), nullptr),
					CallFunc::create([skill, temp, this] {
					zwj_skills2.remove(skill);
					temp->removeFromParentAndCleanup(true);
				}), nullptr));
			}

		
		}
		else if (attackKey == 'L') {
			//添加技能
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_attack_taichi_2.png");
			//从贴图中以像素单位切割，创建关键帧
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));

			for (int i = -2; i <= 2; i++) {
				for (int j = -2; j <= 2; j++) {

					//使用第一帧创建精灵
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(gp.x + 100 * i, gp.y + 100 * j);
					this->addChild(skill, 4);
					zwj_skills3.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_3")),
							MoveTo::create(2.25f, gp), nullptr),
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
			//添加技能
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_skill_1.png");
			//从贴图中以像素单位切割，创建关键帧
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			//使用第一帧创建精灵
			auto skill = Sprite::createWithSpriteFrame(frame0);
			skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
			skill->setPosition(pp);
			this->addChild(skill, 4);
			zwj_skills1.push_back(skill);
			auto temp = skill;
			skill->runAction(Sequence::create(
				Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_1")),
					MoveTo::create(2.7f, Vec2(pp.x , pp.y- 500)), nullptr),
				CallFunc::create([skill, temp, this] {
				zwj_skills1.remove(skill);
				temp->removeFromParentAndCleanup(true);
			}), nullptr));
		}
		else if (attackKey == 'K') {
			//添加技能
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_attack_taichi_1.png");
			//从贴图中以像素单位切割，创建关键帧
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
			for (int i = 1; i <= 3; i++) {
				//使用第一帧创建精灵
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
			//添加技能
			auto texture = Director::getInstance()->getTextureCache()->addImage("zwj_attack_taichi_2.png");
			//从贴图中以像素单位切割，创建关键帧
			auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));

			for (int i = -2; i <= 2; i++) {
				for (int j = -2; j <= 2; j++) {

					//使用第一帧创建精灵
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(gp.x + 100 * i, gp.y + 100 * j);
					this->addChild(skill, 4);
					zwj_skills3.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						Spawn::create(Animate::create(AnimationCache::getInstance()->getAnimation("zwj_skill_3")),
							MoveTo::create(2.25f, gp), nullptr),
						CallFunc::create([skill, temp, this] {
						zwj_skills3.remove(skill);
						temp->removeFromParentAndCleanup(true);
					}), nullptr));
				}


			}

		}
	}
}

void Scene1::addKeyboardListener() {
	// 键盘监听
	auto KeyBoardListener = EventListenerKeyboard::create();
	KeyBoardListener->onKeyPressed = CC_CALLBACK_2(Scene1::onKeyPressed, this);
	KeyBoardListener->onKeyReleased = CC_CALLBACK_2(Scene1::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(KeyBoardListener, player);
}

//按下键盘
void Scene1::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {
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

//松开按键
void Scene1::onKeyReleased(EventKeyboard::KeyCode code, Event* event) {
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
//预载音乐
void Scene1::preloadMusic() {
	auto audio = SimpleAudioEngine::getInstance();
	//->preloadBackgroundMusic("music/bgm.mp3");
	//audio->preloadEffect("music/explore.wav");
	audio->preloadEffect("music/dragon.wav");
}
