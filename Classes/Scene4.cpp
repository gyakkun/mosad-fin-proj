#include "Scene4.h"
#include "Scene5.h"
USING_NS_CC;

using namespace CocosDenshion;

Scene* Scene4::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Scene4::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Scene4::init() {
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	preloadMusic();

	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/scene_3.mp3", true);

	photo = Sprite::create("Scene3_CG/Scene4_1.jpg");
	photo->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	photo->setScale(visibleSize.width / photo->getContentSize().width);
	this->addChild(photo, 0);
	num = 1;
	addTouchListener();
}

void Scene4::preloadMusic() {
	auto audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("music/scene_3.mp3");
}

void Scene4::addTouchListener() {
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(Scene4::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Scene4::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool Scene4::onTouchBegan(Touch *touch, Event *event) {
	return true;
}

void Scene4::onTouchEnded(Touch *touch, Event *event) {
	num++;
	if (num <= 9) {
		char str[30];
		auto visibleSize = Director::getInstance()->getVisibleSize();
		sprintf(str, "Scene3_CG/Scene4_%d.jpg", num);
		auto temp = photo;
		temp->removeFromParentAndCleanup(true);
		photo = Sprite::create(str);
		photo->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		photo->setScale(visibleSize.width / photo->getContentSize().width);
		this->addChild(photo, 0);
	}
	else {
		auto scene = Scene5::createScene();
		// run
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
	}
}