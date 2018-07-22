#include "BossScene.h"
#include "Scene4.h"
#include "MenuScene.h"
#include <algorithm>

USING_NS_CC;

using namespace CocosDenshion;

Scene* BossScene::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = BossScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool BossScene::init() {
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

	Sprite* sp2 = Sprite::create("bar1.png");
	HP1 = ProgressTimer::create(red);
	HP1->setAnchorPoint(Vec2(0, 0));
	HP1->setType(ProgressTimerType::BAR);
	HP1->setBarChangeRate(Point(1, 0));
	HP1->setMidpoint(Point(0, 1));
	HP1->setPercentage(100);
	HP1->setScaleY(1.5);
	HP1->setScaleX(1.74);
	HP1->setPosition(visibleSize.width / 2 - 230, 104);
	addChild(HP1, 2);
	sp2->setAnchorPoint(Vec2(0, 0));
	sp2->setPosition(visibleSize.width / 2 - 300, 50);
	addChild(sp2, 1);
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/scene_3.mp3");
	auto texture = Director::getInstance()->getTextureCache()->addImage("zhangwujistand.png");
	//从贴图中以像素单位切割，创建关键帧
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(875, 175, 175, 175)));
	//使用第一帧创建精灵
	player = Sprite::createWithSpriteFrame(frame0);
	player->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	player->setScale(visibleSize.height*0.25 / player->getContentSize().height);
	schedule(schedule_selector(BossScene::update), 0.01f, kRepeatForever, 0);

	this->addChild(player, 3);
	//添加萧峰
	texture = Director::getInstance()->getTextureCache()->addImage("bossattack.png");
	//从贴图中以像素单位切割，创建关键帧
	frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(900, 180, 180, 180)));
	//使用第一帧创建精灵
	dfbb = Sprite::createWithSpriteFrame(frame0);
	dfbb->setScale(visibleSize.height*0.25 / dfbb->getContentSize().height);
	dfbb->setPosition(Vec2(visibleSize.width / 2 + origin.x + 200, visibleSize.height / 2 + origin.y));
	this->addChild(dfbb, 3);
	schedule(schedule_selector(BossScene::updatedfbb), 0.4f, kRepeatForever, 0);
	//变量初始化
	num = 0;
	isMove = false;
	//监听器
	addKeyboardListener();
	addCustomListener();
	return true;
}

void BossScene::updatedfbb(float f) {
	if (dfbbAction)return;
	dfbbAction = true;
	Vec2 pp = player->getPosition();
	Vec2 gp = dfbb->getPosition();
	auto callFunc1 = CallFunc::create([&] {dfbbAttack(); });
	//判断移动方向
	if (abs(pp.x - gp.x) > abs(pp.y - gp.y)) {
		if (pp.x > gp.x) {
			Repeat* animate = Repeat::create(Animate::create(AnimationCache::getInstance()->getAnimation("rightrunAnimation4")), (pp.x - gp.x) / 100 + 1);
			auto spa = Spawn::createWithTwoActions(MoveTo::create((pp.x - gp.x) / 150, Vec2(pp.x, gp.y)),
				animate);
			auto seq = Sequence::create(spa,
				callFunc1, nullptr);
			dfbb->runAction(seq);
		}
		else {
			Repeat* animate = Repeat::create(Animate::create(AnimationCache::getInstance()->getAnimation("leftrunAnimation4")), (gp.x - pp.x) / 100 + 1);
			auto spa = Spawn::createWithTwoActions(MoveTo::create((gp.x - pp.x) / 150, Vec2(pp.x, gp.y)),
				animate);
			auto seq = Sequence::create(spa,
				callFunc1, nullptr);
			dfbb->runAction(seq);
		}
	}
	else {
		if (pp.y > gp.y) {
			Repeat* animate = Repeat::create(Animate::create(AnimationCache::getInstance()->getAnimation("uprunAnimation4")), (pp.y - gp.y) / 100 + 1);
			auto spa = Spawn::createWithTwoActions(MoveTo::create((pp.y - gp.y) / 150, Vec2(gp.x, pp.y)),
				animate);
			auto seq = Sequence::create(spa,
				callFunc1, nullptr);
			dfbb->runAction(seq);
		}
		else {
			Repeat* animate = Repeat::create(Animate::create(AnimationCache::getInstance()->getAnimation("downrunAnimation4")), (gp.y - pp.y) / 100 + 1);
			auto spa = Spawn::createWithTwoActions(MoveTo::create((gp.y - pp.y) / 150, Vec2(gp.x, pp.y)),
				animate);
			auto seq = Sequence::create(spa,
				callFunc1, nullptr);
			dfbb->runAction(seq);
		}
	}

}
//萧峰攻击，包括攻击方向，技能特效及飞出方向
void BossScene::dfbbAttack() {
	//一次动作包括移动和攻击，攻击完毕后设为false
	auto callFunc = CallFunc::create([&] {dfbbAction = false; });
	Vec2 pp = player->getPosition();
	Vec2 gp = dfbb->getPosition();
	int r = 1 + rand() % 3;
	auto texture = Director::getInstance()->getTextureCache()->addImage("dfbb_attack_1.png");
	if (r == 2) {
		//添加技能
		texture = Director::getInstance()->getTextureCache()->addImage("dfbb_attack_2.png");
	}
	else if (r == 3) {
		texture = Director::getInstance()->getTextureCache()->addImage("dfbb_attack.png");
	}
	//从贴图中以像素单位切割，创建关键帧
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 192, 0, 192)));
	SimpleAudioEngine::getInstance()->playEffect("music/dragon.wav");
	if (abs(pp.x - gp.x) > abs(pp.y - gp.y)) {
		if (pp.x > gp.x) {
			Sequence* seq = Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("rightattackAnimation4")),
				callFunc, nullptr);
			dfbb->runAction(seq);
			if (r == 1) {
				for (int i = -2; i <= 2; i++) {
					Animate* skill_animate = Animate::create(AnimationCache::getInstance()->getAnimation("dfbb_attack_1"));
					//使用第一帧创建精灵
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(pp.x + 100 * i, pp.y);
					this->addChild(skill, 4);
					dfbb_skills1.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						skill_animate,
						CallFunc::create([skill, temp, this] {
						dfbb_skills1.remove(skill);
						temp->removeFromParentAndCleanup(true);
					}), nullptr));
				}
				for (int i = -2; i <= 2; i++) {
					if (i == 0)continue;
					//使用第一帧创建精灵
					Animate* skill_animate = Animate::create(AnimationCache::getInstance()->getAnimation("dfbb_attack_1"));
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(pp.x, pp.y + 100 * i);
					this->addChild(skill, 4);
					dfbb_skills1.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						skill_animate,
						CallFunc::create([skill, temp, this] {
						dfbb_skills1.remove(skill);
						temp->removeFromParentAndCleanup(true);
					}), nullptr));
				}
				
			}
			else if (r == 2) {
				for (int i = 1; i <= 3; i++) {
					Animate* skill_animate = Animate::create(AnimationCache::getInstance()->getAnimation("dfbb_attack_2"));
					//使用第一帧创建精灵
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(gp);
					this->addChild(skill, 4);
					dfbb_skills2.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						Spawn::create(skill_animate, MoveTo::create(0.9, Vec2(gp.x + 500, gp.y + 300 * (i - 2))), nullptr),
						CallFunc::create([skill, temp, this] {
						dfbb_skills2.remove(skill);
						temp->removeFromParentAndCleanup(true);
					}), nullptr));
				}
			}

			else{
				for (int i = -4; i <= 4; i++) {
					for (int j = -4; j <= 4; j++) {
						Animate* skill_animate = Animate::create(AnimationCache::getInstance()->getAnimation("dfbb_attack_3"));
						//使用第一帧创建精灵
						auto skill = Sprite::createWithSpriteFrame(frame0);
						skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
						skill->setPosition(gp.x + 50 * i, gp.y + 50 * j);
						this->addChild(skill, 4);
						dfbb_skills3.push_back(skill);
						auto temp = skill;
						skill->runAction(Sequence::create(
							Spawn::create(skill_animate, MoveTo::create(2.4, Vec2(gp.x + 400 * i, gp.y + 400 * j)), nullptr),
							CallFunc::create([skill, temp, this] {
							dfbb_skills3.remove(skill);
							temp->removeFromParentAndCleanup(true);
						}), nullptr));
					}
				}
			}
		}
		else {
			Sequence* seq = Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("leftattackAnimation4")),
				callFunc, nullptr);
			dfbb->runAction(seq);

			if (r == 1) {
				for (int i = -2; i <= 2; i++) {
					Animate* skill_animate = Animate::create(AnimationCache::getInstance()->getAnimation("dfbb_attack_1"));
					//使用第一帧创建精灵
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(pp.x + 100 * i, pp.y);
					this->addChild(skill, 4);
					dfbb_skills1.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						skill_animate,
						CallFunc::create([skill, temp, this] {
						dfbb_skills1.remove(skill);
						temp->removeFromParentAndCleanup(true);
					}), nullptr));
				}
				for (int i = -2; i <= 2; i++) {
					if (i == 0)continue;
					//使用第一帧创建精灵
					Animate* skill_animate = Animate::create(AnimationCache::getInstance()->getAnimation("dfbb_attack_1"));
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(pp.x, pp.y + 100 * i);
					this->addChild(skill, 4);
					dfbb_skills1.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						skill_animate,
						CallFunc::create([skill, temp, this] {
						dfbb_skills1.remove(skill);
						temp->removeFromParentAndCleanup(true);
					}), nullptr));
				}

			}
			else if (r == 2) {
				for (int i = 1; i <= 3; i++) {
					Animate* skill_animate = Animate::create(AnimationCache::getInstance()->getAnimation("dfbb_attack_2"));
					//使用第一帧创建精灵
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(gp);
					this->addChild(skill, 4);
					dfbb_skills2.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						Spawn::create(skill_animate, MoveTo::create(0.9, Vec2(gp.x - 500, gp.y + 300 * (i - 2))), nullptr),
						CallFunc::create([skill, temp, this] {
						dfbb_skills2.remove(skill);
						temp->removeFromParentAndCleanup(true);
					}), nullptr));
				}
			}

			else {
				for (int i = -4; i <= 4; i++) {
					for (int j = -4; j <= 4; j++) {
						Animate* skill_animate = Animate::create(AnimationCache::getInstance()->getAnimation("dfbb_attack_3"));
						//使用第一帧创建精灵
						auto skill = Sprite::createWithSpriteFrame(frame0);
						skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
						skill->setPosition(gp.x + 50 * i, gp.y + 50 * j);
						this->addChild(skill, 4);
						dfbb_skills3.push_back(skill);
						auto temp = skill;
						skill->runAction(Sequence::create(
							Spawn::create(skill_animate, MoveTo::create(2.4, Vec2(gp.x + 400 * i, gp.y + 400 * j)), nullptr),
							CallFunc::create([skill, temp, this] {
							dfbb_skills3.remove(skill);
							temp->removeFromParentAndCleanup(true);
						}), nullptr));
					}
				}
			}
		}
	}
	else {
		if (pp.y > gp.y) {
			Sequence* seq = Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("upattackAnimation4")),
				callFunc, nullptr);
			dfbb->runAction(seq);

			if (r == 1) {
				for (int i = -2; i <= 2; i++) {
					Animate* skill_animate = Animate::create(AnimationCache::getInstance()->getAnimation("dfbb_attack_1"));
					//使用第一帧创建精灵
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(pp.x + 100 * i, pp.y);
					this->addChild(skill, 4);
					dfbb_skills1.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						skill_animate,
						CallFunc::create([skill, temp, this] {
						dfbb_skills1.remove(skill);
						temp->removeFromParentAndCleanup(true);
					}), nullptr));
				}
				for (int i = -2; i <= 2; i++) {
					if (i == 0)continue;
					//使用第一帧创建精灵
					Animate* skill_animate = Animate::create(AnimationCache::getInstance()->getAnimation("dfbb_attack_1"));
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(pp.x, pp.y + 100 * i);
					this->addChild(skill, 4);
					dfbb_skills1.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						skill_animate,
						CallFunc::create([skill, temp, this] {
						dfbb_skills1.remove(skill);
						temp->removeFromParentAndCleanup(true);
					}), nullptr));
				}

			}
			else if (r == 2) {
				for (int i = 1; i <= 3; i++) {
					Animate* skill_animate = Animate::create(AnimationCache::getInstance()->getAnimation("dfbb_attack_2"));
					//使用第一帧创建精灵
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(gp);
					this->addChild(skill, 4);
					dfbb_skills2.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						Spawn::create(skill_animate, MoveTo::create(0.9, Vec2(gp.x + 300 * (i - 2), gp.y + 500 )), nullptr),
						CallFunc::create([skill, temp, this] {
						dfbb_skills2.remove(skill);
						temp->removeFromParentAndCleanup(true);
					}), nullptr));
				}
			}

			else {
				for (int i = -4; i <= 4; i++) {
					for (int j = -4; j <= 4; j++) {
						Animate* skill_animate = Animate::create(AnimationCache::getInstance()->getAnimation("dfbb_attack_3"));
						//使用第一帧创建精灵
						auto skill = Sprite::createWithSpriteFrame(frame0);
						skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
						skill->setPosition(gp.x + 50 * i, gp.y + 50 * j);
						this->addChild(skill, 4);
						dfbb_skills3.push_back(skill);
						auto temp = skill;
						skill->runAction(Sequence::create(
							Spawn::create(skill_animate, MoveTo::create(2.4, Vec2(gp.x + 400 * i, gp.y + 400 * j)), nullptr),
							CallFunc::create([skill, temp, this] {
							dfbb_skills3.remove(skill);
							temp->removeFromParentAndCleanup(true);
						}), nullptr));
					}
				}
			}
		}
		else {
			Sequence* seq = Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("downattackAnimation4")),
				callFunc, nullptr);
			dfbb->runAction(seq);

			if (r == 1) {
				for (int i = -2; i <= 2; i++) {
					Animate* skill_animate = Animate::create(AnimationCache::getInstance()->getAnimation("dfbb_attack_1"));
					//使用第一帧创建精灵
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(pp.x + 100 * i, pp.y);
					this->addChild(skill, 4);
					dfbb_skills1.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						skill_animate,
						CallFunc::create([skill, temp, this] {
						dfbb_skills1.remove(skill);
						temp->removeFromParentAndCleanup(true);
					}), nullptr));
				}
				for (int i = -2; i <= 2; i++) {
					if (i == 0)continue;
					//使用第一帧创建精灵
					Animate* skill_animate = Animate::create(AnimationCache::getInstance()->getAnimation("dfbb_attack_1"));
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(pp.x, pp.y + 100 * i);
					this->addChild(skill, 4);
					dfbb_skills1.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						skill_animate,
						CallFunc::create([skill, temp, this] {
						dfbb_skills1.remove(skill);
						temp->removeFromParentAndCleanup(true);
					}), nullptr));
				}

			}
			else if (r == 2) {
				for (int i = 1; i <= 3; i++) {
					Animate* skill_animate = Animate::create(AnimationCache::getInstance()->getAnimation("dfbb_attack_2"));
					//使用第一帧创建精灵
					auto skill = Sprite::createWithSpriteFrame(frame0);
					skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
					skill->setPosition(gp);
					this->addChild(skill, 4);
					dfbb_skills2.push_back(skill);
					auto temp = skill;
					skill->runAction(Sequence::create(
						Spawn::create(skill_animate, MoveTo::create(0.9, Vec2(gp.x + 300 * (i - 2), gp.y - 500 )), nullptr),
						CallFunc::create([skill, temp, this] {
						dfbb_skills2.remove(skill);
						temp->removeFromParentAndCleanup(true);
					}), nullptr));
				}
			}

			else {
				for (int i = -4; i <= 4; i++) {
					for (int j = -4; j <= 4; j++) {
						Animate* skill_animate = Animate::create(AnimationCache::getInstance()->getAnimation("dfbb_attack_3"));
						//使用第一帧创建精灵
						auto skill = Sprite::createWithSpriteFrame(frame0);
						skill->setScale(Director::getInstance()->getVisibleSize().height*0.25 / skill->getContentSize().height);
						skill->setPosition(gp.x + 50 * i, gp.y + 50 * j);
						this->addChild(skill, 4);
						dfbb_skills3.push_back(skill);
						auto temp = skill;
						skill->runAction(Sequence::create(
							Spawn::create(skill_animate, MoveTo::create(2.4, Vec2(gp.x + 400 * i, gp.y + 400 * j)), nullptr),
							CallFunc::create([skill, temp, this] {
							dfbb_skills3.remove(skill);
							temp->removeFromParentAndCleanup(true);
						}), nullptr));
					}
				}
			}
		}
	}
}
void BossScene::Gameover()
{
	player->stopAllActions();
	dfbb->stopAllActions();
	_eventDispatcher->removeAllEventListeners();
	unschedule(schedule_selector(BossScene::update));
	unschedule(schedule_selector(BossScene::updatedfbb));
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	bg = win ? Sprite::create("Scene3_CG/ge0.jpg") : Sprite::create("Scene3_CG/be0.jpg");
	bg->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	bg->setScale(visibleSize.width / bg->getContentSize().width);
	addTouchListener();
	this->addChild(bg, 6);
}

//技能碰撞检测
void BossScene::skillCollision(EventCustom* event) {
	Sprite* temp;
	for (auto it = dfbb_skills1.begin(); it != dfbb_skills1.end(); it++) {
		temp = (*it);
		if (player->getBoundingBox().containsPoint((*it)->getPosition())) {
			if (HP->getPercentage() - 3 <= 0)
			{
				win = false;
				Gameover();
			}
			HP->setPercentage(HP->getPercentage() - 3);

			temp->stopAllActions();
			dfbb_skills1.remove(temp);
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
				, nullptr));
			break;
		}
	}

	for (auto it = dfbb_skills2.begin(); it != dfbb_skills2.end(); it++) {
		temp = (*it);
		if (player->getBoundingBox().containsPoint((*it)->getPosition())) {
			if (HP->getPercentage() - 4 <= 0)
			{
				win = false;
				Gameover();
			}
			HP->setPercentage(HP->getPercentage() - 4);

			temp->stopAllActions();
			dfbb_skills2.remove(temp);
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
				, nullptr));
			break;
		}
	}

	for (auto it = dfbb_skills3.begin(); it != dfbb_skills3.end(); it++) {
		temp = (*it);
		if (player->getBoundingBox().containsPoint((*it)->getPosition())) {
			if (HP->getPercentage() - 2 <= 0)
			{
				win = false;
				Gameover();
			}
			HP->setPercentage(HP->getPercentage() - 2);

			temp->stopAllActions();
			dfbb_skills3.remove(temp);
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
				, nullptr));
			break;
		}
	}

	for (auto it = zwj_skills1.begin(); it != zwj_skills1.end(); it++) {
		temp = (*it);
		if (dfbb->getBoundingBox().containsPoint((*it)->getPosition())) {
			if (HP1->getPercentage() - 3 <= 0)
			{
				HP1->setPercentage(0);
				win = true;
				Gameover();
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
			hurt->setPosition(dfbb->getPosition());
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
		if (dfbb->getBoundingBox().containsPoint((*it)->getPosition())) {
			if (HP1->getPercentage() - 2 <= 0)
			{
				HP1->setPercentage(0);
				win = true;
				Gameover();
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
			hurt->setPosition(dfbb->getPosition());
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
		if (dfbb->getBoundingBox().containsPoint((*it)->getPosition())) {
			if (HP1->getPercentage() - 1 <= 0)
			{
				HP1->setPercentage(0);
				win = true;
				Gameover();
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
			hurt->setPosition(dfbb->getPosition());
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

void BossScene::addCustomListener() {
	auto customListener1 = EventListenerCustom::create("skillCollision", CC_CALLBACK_1(BossScene::skillCollision, this));
	_eventDispatcher->addEventListenerWithFixedPriority(customListener1, 1);
}

void BossScene::update(float f) {
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
	//技能碰撞
	EventCustom e("skillCollision");
	_eventDispatcher->dispatchEvent(&e);
}
//站立方向
void BossScene::stand(char k)
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
//移动方向
void BossScene::move(char k)
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
void BossScene::attack(char attackKey)
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
	Vec2 gp = dfbb->getPosition();

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
					MoveTo::create(2.7f, Vec2(pp.x - 500, pp.y)), nullptr),
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
						MoveTo::create(1.8f, Vec2(pp.x + 200 * (i - 2), pp.y + 500)), nullptr),
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
					MoveTo::create(2.7f, Vec2(pp.x, pp.y - 500)), nullptr),
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

void BossScene::addKeyboardListener() {
	// 键盘监听
	auto KeyBoardListener = EventListenerKeyboard::create();
	KeyBoardListener->onKeyPressed = CC_CALLBACK_2(BossScene::onKeyPressed, this);
	KeyBoardListener->onKeyReleased = CC_CALLBACK_2(BossScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(KeyBoardListener, player);
}

//按下键盘
void BossScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {
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
void BossScene::onKeyReleased(EventKeyboard::KeyCode code, Event* event) {
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
void BossScene::preloadMusic() {
	auto audio = SimpleAudioEngine::getInstance();
	//->preloadBackgroundMusic("music/bgm.mp3");
	//audio->preloadEffect("music/explore.wav");
	audio->preloadEffect("music/dragon.wav");
}

void BossScene::addTouchListener() {
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(BossScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(BossScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool BossScene::onTouchBegan(Touch *touch, Event *event) {
	return true;
}

void BossScene::onTouchEnded(Touch *touch, Event *event) {
	num++;
	if (win&&num <= 6) {
		char str[30];
		auto visibleSize = Director::getInstance()->getVisibleSize();
		sprintf(str, "Scene3_CG/ge%d.jpg", num);
		auto temp = bg;
		temp->removeFromParentAndCleanup(true);
		bg = Sprite::create(str);
		bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		bg->setScale(visibleSize.width / bg->getContentSize().width);
		this->addChild(bg, 6);
	}
	else if (!win&&num <= 3) {
		char str[30];
		auto visibleSize = Director::getInstance()->getVisibleSize();
		sprintf(str, "Scene3_CG/be%d.jpg", num);
		auto temp = bg;
		temp->removeFromParentAndCleanup(true);
		bg = Sprite::create(str);
		bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		bg->setScale(visibleSize.width / bg->getContentSize().width);
		this->addChild(bg, 6);
	}
	else {
		auto scene = MenuScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
	}
}