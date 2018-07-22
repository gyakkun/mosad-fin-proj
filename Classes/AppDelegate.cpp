#include "AppDelegate.h"
#include "MenuScene.h"
#include "network\HttpClient.h"

using namespace cocos2d::network;

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1280, 700);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {
#if USE_AUDIO_ENGINE
	AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs() {
	// set OpenGL context attributes: red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,
// don't modify or remove this function
static int register_all_packages() {
	return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("NetworkAccess", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
		glview = GLViewImpl::create("NetworkAccess");
#endif
		director->setOpenGLView(glview);
	}

	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0f / 60);

	// Set the design resolution
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
	auto frameSize = glview->getFrameSize();
	// if the frame's height is larger than the height of medium size.
	if (frameSize.height > mediumResolutionSize.height) {
		director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width));
	}
	// if the frame's height is larger than the height of small size.
	else if (frameSize.height > smallResolutionSize.height) {
		director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width));
	}
	// if the frame's height is smaller than the height of medium size.
	else {
		director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width));
	}

	register_all_packages();



	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("zhangwujistand.plist");

	char frameName[30];
	Animation* downstandAnimation1 = Animation::create();

	for (int i = 1; i <= 8; i++)
	{
		sprintf(frameName, "zhangwujistand_%02d.png", i);
		downstandAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	downstandAnimation1->setDelayPerUnit(0.05);
	AnimationCache::getInstance()->addAnimation(downstandAnimation1, "downstandAnimation1");

	Animation* leftstandAnimation1 = Animation::create();
	for (int i = 9; i <= 16; i++)
	{
		sprintf(frameName, "zhangwujistand_%02d.png", i);
		leftstandAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	leftstandAnimation1->setDelayPerUnit(0.05);
	AnimationCache::getInstance()->addAnimation(leftstandAnimation1, "leftstandAnimation1");

	Animation* rightstandAnimation1 = Animation::create();
	for (int i = 17; i <= 24; i++)
	{
		sprintf(frameName, "zhangwujistand_%02d.png", i);
		rightstandAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	rightstandAnimation1->setDelayPerUnit(0.05);
	AnimationCache::getInstance()->addAnimation(rightstandAnimation1, "rightstandAnimation1");


	Animation* upstandAnimation1 = Animation::create();
	for (int i = 25; i <= 32; i++)
	{
		sprintf(frameName, "zhangwujistand_%02d.png", i);
		upstandAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	upstandAnimation1->setDelayPerUnit(0.05);
	AnimationCache::getInstance()->addAnimation(upstandAnimation1, "upstandAnimation1");


	// load game resource
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("zhangwujirun.plist");

	Animation* downrunAnimation1 = Animation::create();

	for (int i = 1; i < 9; i++)
	{
		sprintf(frameName, "zhangwujirun_%02d.png", i);
		downrunAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	downrunAnimation1->setDelayPerUnit(0.05);
	AnimationCache::getInstance()->addAnimation(downrunAnimation1, "downrunAnimation1");


	Animation* leftrunAnimation1 = Animation::create();

	for (int i = 9; i < 17; i++)
	{
		sprintf(frameName, "zhangwujirun_%02d.png", i);
		leftrunAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	leftrunAnimation1->setDelayPerUnit(0.05);
	AnimationCache::getInstance()->addAnimation(leftrunAnimation1, "leftrunAnimation1");



	Animation* rightrunAnimation1 = Animation::create();

	for (int i = 17; i < 25; i++)
	{
		sprintf(frameName, "zhangwujirun_%d.png", i);
		rightrunAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	rightrunAnimation1->setDelayPerUnit(0.05);
	AnimationCache::getInstance()->addAnimation(rightrunAnimation1, "rightrunAnimation1");


	Animation* uprunAnimation1 = Animation::create();

	for (int i = 25; i < 33; i++)
	{
		sprintf(frameName, "zhangwujirun_%d.png", i);
		uprunAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	uprunAnimation1->setDelayPerUnit(0.05);
	AnimationCache::getInstance()->addAnimation(uprunAnimation1, "uprunAnimation1");


	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("zhangwujiattack.plist");

	Animation* downattackAnimation1 = Animation::create();

	for (int i = 1; i < 9; i++)
	{
		sprintf(frameName, "zhangwujiattack_%02d.png", i);
		downattackAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	downattackAnimation1->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(downattackAnimation1, "downattackAnimation1");


	Animation* leftattackAnimation1 = Animation::create();

	for (int i = 9; i < 17; i++)
	{
		sprintf(frameName, "zhangwujiattack_%02d.png", i);
		leftattackAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	leftattackAnimation1->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(leftattackAnimation1, "leftattackAnimation1");



	Animation* rightattackAnimation1 = Animation::create();

	for (int i = 17; i < 25; i++)
	{
		sprintf(frameName, "zhangwujiattack_%d.png", i);
		rightattackAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	rightattackAnimation1->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(rightattackAnimation1, "rightattackAnimation1");


	Animation* upattackAnimation1 = Animation::create();

	for (int i = 25; i < 33; i++)
	{
		sprintf(frameName, "zhangwujiattack_%d.png", i);
		upattackAnimation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	upattackAnimation1->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(upattackAnimation1, "upattackAnimation1");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("zwj_skill_1.plist");
	Animation* zwj_skill_1 = Animation::create();

	for (int i = 1; i <= 18; i++)
	{
		sprintf(frameName, "zwj1_%02d.png", i);
		zwj_skill_1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	zwj_skill_1->setDelayPerUnit(0.15);
	AnimationCache::getInstance()->addAnimation(zwj_skill_1, "zwj_skill_1");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("zwj_attack_taichi_1.plist");
	Animation* zwj_skill_2 = Animation::create();

	for (int i = 1; i <= 12; i++)
	{
		sprintf(frameName, "tx46_%02d.png", i);
		zwj_skill_2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	zwj_skill_2->setDelayPerUnit(0.15);
	AnimationCache::getInstance()->addAnimation(zwj_skill_2, "zwj_skill_2");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("zwj_attack_taichi_2.plist");
	Animation* zwj_skill_3 = Animation::create();

	for (int i = 1; i <= 15; i++)
	{
		sprintf(frameName, "taichi_%02d.png", i);
		zwj_skill_3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	zwj_skill_3->setDelayPerUnit(0.15);
	AnimationCache::getInstance()->addAnimation(zwj_skill_3, "zwj_skill_3");


	//郭靖
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("guojingstand.plist");


	Animation* downstandAnimation2 = Animation::create();

	for (int i = 1; i <= 8; i++)
	{
		sprintf(frameName, "guojingstand_%02d.png", i);
		downstandAnimation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	downstandAnimation2->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(downstandAnimation2, "downstandAnimation2");

	Animation* leftstandAnimation2 = Animation::create();
	for (int i = 9; i <= 16; i++)
	{
		sprintf(frameName, "guojingstand_%02d.png", i);
		leftstandAnimation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	leftstandAnimation2->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(leftstandAnimation2, "leftstandAnimation2");

	Animation* rightstandAnimation2 = Animation::create();
	for (int i = 17; i <= 24; i++)
	{
		sprintf(frameName, "guojingstand_%02d.png", i);
		rightstandAnimation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	rightstandAnimation2->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(rightstandAnimation2, "rightstandAnimation2");


	Animation* upstandAnimation2 = Animation::create();
	for (int i = 25; i <= 32; i++)
	{
		sprintf(frameName, "guojingstand_%02d.png", i);
		upstandAnimation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	upstandAnimation2->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(upstandAnimation2, "upstandAnimation2");


	// load game resource
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("guojingrun.plist");

	Animation* downrunAnimation2 = Animation::create();

	for (int i = 1; i < 9; i++)
	{
		sprintf(frameName, "guojingrun_%02d.png", i);
		downrunAnimation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	downrunAnimation2->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(downrunAnimation2, "downrunAnimation2");


	Animation* leftrunAnimation2 = Animation::create();

	for (int i = 9; i < 17; i++)
	{
		sprintf(frameName, "guojingrun_%02d.png", i);
		leftrunAnimation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	leftrunAnimation2->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(leftrunAnimation2, "leftrunAnimation2");



	Animation* rightrunAnimation2 = Animation::create();

	for (int i = 17; i < 25; i++)
	{
		sprintf(frameName, "guojingrun_%d.png", i);
		rightrunAnimation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	rightrunAnimation2->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(rightrunAnimation2, "rightrunAnimation2");


	Animation* uprunAnimation2 = Animation::create();

	for (int i = 25; i < 33; i++)
	{
		sprintf(frameName, "guojingrun_%d.png", i);
		uprunAnimation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	uprunAnimation2->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(uprunAnimation2, "uprunAnimation2");


	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("guojingattack.plist");

	Animation* downattackAnimation2 = Animation::create();

	for (int i = 1; i < 9; i++)
	{
		sprintf(frameName, "guojingattack_%02d.png", i);
		downattackAnimation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	downattackAnimation2->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(downattackAnimation2, "downattackAnimation2");


	Animation* leftattackAnimation2 = Animation::create();

	for (int i = 9; i < 17; i++)
	{
		sprintf(frameName, "guojingattack_%02d.png", i);
		leftattackAnimation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	leftattackAnimation2->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(leftattackAnimation2, "leftattackAnimation2");



	Animation* rightattackAnimation2 = Animation::create();

	for (int i = 17; i < 25; i++)
	{
		sprintf(frameName, "guojingattack_%d.png", i);
		rightattackAnimation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	rightattackAnimation2->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(rightattackAnimation2, "rightattackAnimation2");


	Animation* upattackAnimation2 = Animation::create();

	for (int i = 25; i < 33; i++)
	{
		sprintf(frameName, "guojingattack_%d.png", i);
		upattackAnimation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	upattackAnimation2->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(upattackAnimation2, "upattackAnimation2");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gj_attack_1.plist");
	Animation* gj_attack_1 = Animation::create();

	for (int i = 1; i <= 20; i++)
	{
		sprintf(frameName, "gj_attack_1_%02d.png", i);
		gj_attack_1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	gj_attack_1->setDelayPerUnit(0.15);
	AnimationCache::getInstance()->addAnimation(gj_attack_1, "gj_attack_1");

	//被打中动画
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hurt_1.plist");
	Animation* hurt_1 = Animation::create();

	for (int i = 1; i <= 9; i++)
	{
		sprintf(frameName, "Ice4_%02d.png", i);
		hurt_1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	hurt_1->setDelayPerUnit(0.05);
	AnimationCache::getInstance()->addAnimation(hurt_1, "hurt_1");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hurt_2.plist");
	Animation* hurt_2 = Animation::create();

	for (int i = 1; i <= 13; i++)
	{
		sprintf(frameName, "light1_%02d.png", i);
		hurt_2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	hurt_2->setDelayPerUnit(0.05);
	AnimationCache::getInstance()->addAnimation(hurt_2, "hurt_2");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hurt_3.plist");
	Animation* hurt_3 = Animation::create();

	for (int i = 1; i <= 15; i++)
	{
		sprintf(frameName, "Light00_%02d.png", i);
		hurt_3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	hurt_3->setDelayPerUnit(0.05);
	AnimationCache::getInstance()->addAnimation(hurt_3, "hurt_3");

	//萧峰
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("xiaofengstand.plist");


	Animation* downstandAnimation3 = Animation::create();

	for (int i = 1; i <= 8; i++)
	{
		sprintf(frameName, "xiaofengstand_%02d.png", i);
		downstandAnimation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	downstandAnimation3->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(downstandAnimation3, "downstandAnimation3");

	Animation* leftstandAnimation3 = Animation::create();
	for (int i = 9; i <= 16; i++)
	{
		sprintf(frameName, "xiaofengstand_%02d.png", i);
		leftstandAnimation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	leftstandAnimation3->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(leftstandAnimation3, "leftstandAnimation3");

	Animation* rightstandAnimation3 = Animation::create();
	for (int i = 17; i <= 24; i++)
	{
		sprintf(frameName, "xiaofengstand_%02d.png", i);
		rightstandAnimation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	rightstandAnimation3->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(rightstandAnimation3, "rightstandAnimation3");


	Animation* upstandAnimation3 = Animation::create();
	for (int i = 25; i <= 32; i++)
	{
		sprintf(frameName, "xiaofengstand_%02d.png", i);
		upstandAnimation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	upstandAnimation3->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(upstandAnimation3, "upstandAnimation3");


	// load game resource
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("xiaofengrun.plist");

	Animation* downrunAnimation3 = Animation::create();

	for (int i = 1; i < 9; i++)
	{
		sprintf(frameName, "xiaofeng_%02d.png", i);
		downrunAnimation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	downrunAnimation3->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(downrunAnimation3, "downrunAnimation3");


	Animation* leftrunAnimation3 = Animation::create();

	for (int i = 9; i < 17; i++)
	{
		sprintf(frameName, "xiaofeng_%02d.png", i);
		leftrunAnimation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	leftrunAnimation3->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(leftrunAnimation3, "leftrunAnimation3");



	Animation* rightrunAnimation3 = Animation::create();

	for (int i = 17; i < 25; i++)
	{
		sprintf(frameName, "xiaofeng_%d.png", i);
		rightrunAnimation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	rightrunAnimation3->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(rightrunAnimation3, "rightrunAnimation3");


	Animation* uprunAnimation3 = Animation::create();

	for (int i = 25; i < 33; i++)
	{
		sprintf(frameName, "xiaofeng_%d.png", i);
		uprunAnimation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	uprunAnimation3->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(uprunAnimation3, "uprunAnimation3");


	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("xiaofengattack.plist");

	Animation* downattackAnimation3 = Animation::create();

	for (int i = 1; i < 9; i++)
	{
		sprintf(frameName, "xiaofengattack_%02d.png", i);
		downattackAnimation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	downattackAnimation3->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(downattackAnimation3, "downattackAnimation3");


	Animation* leftattackAnimation3 = Animation::create();

	for (int i = 9; i < 17; i++)
	{
		sprintf(frameName, "xiaofengattack_%02d.png", i);
		leftattackAnimation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	leftattackAnimation3->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(leftattackAnimation3, "leftattackAnimation3");



	Animation* rightattackAnimation3 = Animation::create();

	for (int i = 17; i < 25; i++)
	{
		sprintf(frameName, "xiaofengattack_%d.png", i);
		rightattackAnimation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	rightattackAnimation3->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(rightattackAnimation3, "rightattackAnimation3");


	Animation* upattackAnimation3 = Animation::create();

	for (int i = 25; i < 33; i++)
	{
		sprintf(frameName, "xiaofengattack_%d.png", i);
		upattackAnimation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	upattackAnimation3->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(upattackAnimation3, "upattackAnimation3");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("qf_attack_1.plist");
	Animation* qf_attack_1 = Animation::create();

	for (int i = 1; i <= 25; i++)
	{
		sprintf(frameName, "flydragon_%02d.png", i);
		qf_attack_1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	qf_attack_1->setDelayPerUnit(0.15);
	AnimationCache::getInstance()->addAnimation(qf_attack_1, "qf_attack_1");


	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("qf_attack_2.plist");
	Animation* qf_attack_2 = Animation::create();

	for (int i = 1; i <= 14; i++)
	{
		sprintf(frameName, "fireblade_%02d.png", i);
		qf_attack_2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	qf_attack_2->setDelayPerUnit(0.15);
	AnimationCache::getInstance()->addAnimation(qf_attack_2, "qf_attack_2");


	//东方不败

	// load game resource
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bossrun.plist");

	Animation* downrunAnimation4 = Animation::create();

	for (int i = 1; i < 9; i++)
	{
		sprintf(frameName, "bossrun_%02d.png", i);
		downrunAnimation4->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	downrunAnimation4->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(downrunAnimation4, "downrunAnimation4");


	Animation* leftrunAnimation4 = Animation::create();

	for (int i = 9; i < 17; i++)
	{
		sprintf(frameName, "bossrun_%02d.png", i);
		leftrunAnimation4->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	leftrunAnimation4->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(leftrunAnimation4, "leftrunAnimation4");



	Animation* rightrunAnimation4 = Animation::create();

	for (int i = 17; i < 25; i++)
	{
		sprintf(frameName, "bossrun_%d.png", i);
		rightrunAnimation4->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	rightrunAnimation4->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(rightrunAnimation4, "rightrunAnimation4");


	Animation* uprunAnimation4 = Animation::create();

	for (int i = 25; i < 33; i++)
	{
		sprintf(frameName, "bossrun_%d.png", i);
		uprunAnimation4->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	uprunAnimation4->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(uprunAnimation4, "uprunAnimation4");


	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bossattack.plist");

	Animation* downattackAnimation4 = Animation::create();

	for (int i = 1; i < 9; i++)
	{
		sprintf(frameName, "bossattack_%02d.png", i);
		downattackAnimation4->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	downattackAnimation4->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(downattackAnimation4, "downattackAnimation4");


	Animation* leftattackAnimation4 = Animation::create();

	for (int i = 9; i < 17; i++)
	{
		sprintf(frameName, "bossattack_%02d.png", i);
		leftattackAnimation4->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	leftattackAnimation4->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(leftattackAnimation4, "leftattackAnimation4");



	Animation* rightattackAnimation4 = Animation::create();

	for (int i = 17; i < 25; i++)
	{
		sprintf(frameName, "bossattack_%d.png", i);
		rightattackAnimation4->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	rightattackAnimation4->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(rightattackAnimation4, "rightattackAnimation4");


	Animation* upattackAnimation4 = Animation::create();

	for (int i = 25; i < 33; i++)
	{
		sprintf(frameName, "bossattack_%d.png", i);
		upattackAnimation4->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	upattackAnimation4->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(upattackAnimation4, "upattackAnimation4");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("dfbb_attack_1.plist");
	Animation* dfbb_attack_1 = Animation::create();

	for (int i = 1; i <= 15; i++)
	{
		sprintf(frameName, "dfbb_attack_1_%02d.png", i);
		dfbb_attack_1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	dfbb_attack_1->setDelayPerUnit(0.15);
	AnimationCache::getInstance()->addAnimation(dfbb_attack_1, "dfbb_attack_1");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("dfbb_attack_2.plist");
	Animation* dfbb_attack_2 = Animation::create();

	for (int i = 1; i <= 6; i++)
	{
		sprintf(frameName, "jianchi_%02d.png", i);
		dfbb_attack_2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	dfbb_attack_2->setDelayPerUnit(0.15);
	AnimationCache::getInstance()->addAnimation(dfbb_attack_2, "dfbb_attack_2");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("dfbb_attack.plist");
	Animation* dfbb_attack_3 = Animation::create();

	for (int i = 1; i <= 13; i++)
	{
		sprintf(frameName, "dfbb_attack_%02d.png", i);
		dfbb_attack_3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	dfbb_attack_3->setDelayPerUnit(0.15);
	AnimationCache::getInstance()->addAnimation(dfbb_attack_3, "dfbb_attack_3");

	//主菜单动画
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("menu_fight.plist");
	Animation* menu_fight = Animation::create();

	for (int i = 1; i <= 16; i++)
	{
		sprintf(frameName, "anim001_%02d.png", i);
		menu_fight->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	menu_fight->setDelayPerUnit(0.2);
	AnimationCache::getInstance()->addAnimation(menu_fight, "menu_fight");

	// create a scene. it's an autorelease object
	auto scene = MenuScene::createScene();

	// run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
	AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
	AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}