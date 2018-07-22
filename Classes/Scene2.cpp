#include "Scene2.h"
#include "Scene3.h"
USING_NS_CC;

using namespace CocosDenshion;

Scene* Scene2::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Scene2::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Scene2::init() {
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	preloadMusic();

	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/scene_2.mp3", true);

	photo = Sprite::create("Scene2_CG/Scene2_1.jpg");
	photo->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	photo->setScale(visibleSize.width / photo->getContentSize().width);
	this->addChild(photo, 0);
	num = 1;
	addTouchListener();
}

void Scene2::preloadMusic() {
	auto audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("music/scene_2.mp3");
}

void Scene2::addTouchListener() {
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(Scene2::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Scene2::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool Scene2::onTouchBegan(Touch *touch, Event *event) {
	return true;
}

void Scene2::onTouchEnded(Touch *touch, Event *event) {
	num++;
	if (num <= 5) {
		char str[30];
		auto visibleSize = Director::getInstance()->getVisibleSize();
		sprintf(str, "Scene2_CG/Scene2_%d.jpg", num);
		auto temp = photo;
		temp->removeFromParentAndCleanup(true);
		photo = Sprite::create(str);
		photo->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		photo->setScale(visibleSize.width / photo->getContentSize().width);
		this->addChild(photo, 0);
	}
	else {
		auto scene = Scene3::createScene();
		// run
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
	}
}