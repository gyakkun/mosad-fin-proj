#include"Monster.h"
USING_NS_CC;

Factory* Factory::factory = NULL;
Factory::Factory() {
	initSpriteFrame();
}
Factory* Factory::getInstance() {
	if (factory == NULL) {
		factory = new Factory();
	}
	return factory;
}
int Factory::getMonsetnumber()
{
	return monster.size();
}
void Factory::initSpriteFrame() {
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("soldier.plist");

	char frameName[30];
	Animation* soldierrunright = Animation::create();

	for (int i = 1; i <= 8; i++)
	{
		sprintf(frameName, "soldier_%02d.png", i);
		soldierrunright->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	soldierrunright->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(soldierrunright, "soldierrunright");

	Animation* soldierrunleft = Animation::create();

	for (int i = 9; i <= 16; i++)
	{
		sprintf(frameName, "soldier_%02d.png", i);
		soldierrunleft->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	soldierrunleft->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(soldierrunleft, "soldierrunleft");
}

Sprite* Factory::createMonster() {
	auto texture = Director::getInstance()->getTextureCache()->addImage("soldier.png");
	//从贴图中以像素单位切割，创建关键帧
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(200, 0, 200, 200)));
	//使用第一帧创建精灵
	Sprite* mons = Sprite::createWithSpriteFrame(frame0);

	monster.pushBack(mons);
	return mons;
}

void Factory::removeMonster(Sprite* sp) {


	sp->runAction(CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, sp)));
	monster.eraseObject(sp);
}
void Factory::moveMonster(Vec2 playerPos, float time) {
	for (auto i : monster) {
		Vec2 Pos = i->getPosition();
		Vec2 dir = playerPos - Pos;
		dir.normalize();
		if (dir.x < 0)
		{
			auto spa = Spawn::createWithTwoActions(MoveBy::create(time, dir * 40),
				Animate::create(AnimationCache::getInstance()->getAnimation("soldierrunleft")));
			i->runAction(spa);
		}
		else
		{
			auto spa = Spawn::createWithTwoActions(MoveBy::create(time, dir * 40),
				Animate::create(AnimationCache::getInstance()->getAnimation("soldierrunright")));
			i->runAction(spa);

		}




	}
}

Sprite* Factory::collider(Rect rect) {
	for (auto i : monster) {
		if (rect.containsPoint(i->getPosition())) {
			return i;
		}
	}
	return NULL;
}



