#include "MenuScene.h"
#include "Scene0.h"


USING_NS_CC;
using namespace CocosDenshion;
Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
	//背景
    auto sprite = Sprite::create("MenuBackground.jpg");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	auto title = Sprite::create("title.png");
	title->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 200);
	this->addChild(title, 1);

	auto label1 = Label::createWithTTF("初入江湖", "fonts/simkai.ttf", 32);	
	label1->setColor(Color3B::BLACK);
	auto startItem = MenuItemLabel::create(label1, CC_CALLBACK_1(MenuScene::menuStartCallback, this));
	startItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 50));

	auto label3 = Label::createWithTTF("归隐山林", "fonts/simkai.ttf", 32);
	label3->setColor(Color3B::BLACK);
	auto closeItem = MenuItemLabel::create(label3, CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
	closeItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 50));

	auto menu = Menu::create(startItem, closeItem, NULL);
	menu->setPosition(Vec2(origin.x,origin.y));
	this->addChild(menu, 1);

	auto texture = Director::getInstance()->getTextureCache()->addImage("menu_fight.png");
	//从贴图中以像素单位切割，创建关键帧
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0,192,0,192)));
	//使用第一帧创建精灵
	auto fight = Sprite::createWithSpriteFrame(frame0);
	fight->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 150));
	fight->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("menu_fight"))));
	this->addChild(fight);

	prelodeMusic();
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/menu.mp3", true);
    return true;
}

void MenuScene::menuStartCallback(Ref* pSender)
{
	auto scene = Scene0::createScene();
	// run
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 0, 0)));
}


void MenuScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void MenuScene::prelodeMusic() {
	auto audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("music/menu.mp3");

}
