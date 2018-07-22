#include "Scene0.h"
#include "Scene1.h"
USING_NS_CC;

using namespace CocosDenshion;

Scene* Scene0::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Scene0::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Scene0::init() {
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	preloadMusic(); 
	
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/scene_1.mp3", true);
	
	photo = Sprite::create("Scene1_CG/scene0_1.jpg");
	photo->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	photo->setScale(visibleSize.width / photo->getContentSize().width);
	this->addChild(photo, 0);
	num = 1;
	addTouchListener();
}

void Scene0::preloadMusic() {
	auto audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("music/scene_1.mp3");
}

void Scene0::addTouchListener() {
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(Scene0::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Scene0::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool Scene0::onTouchBegan(Touch *touch, Event *event) {
	return true;
}

void Scene0::onTouchEnded(Touch *touch, Event *event) {
	num++;
	if (num <= 8) {
		char str[30];
		auto visibleSize = Director::getInstance()->getVisibleSize();
		sprintf(str, "Scene1_CG/scene0_%d.jpg", num);
		auto temp = photo;
		temp->removeFromParentAndCleanup(true);
		photo = Sprite::create(str);
		photo->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		photo->setScale(visibleSize.width / photo->getContentSize().width);
		this->addChild(photo, 0);
	}
	else {
		auto scene = Scene1::createScene();
		// run
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
	}
}