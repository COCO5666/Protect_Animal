﻿#pragma execution_character_set("utf-8")

#include "QMenu.h"

MenuItem* QMenu::_item;
Menu* QMenu::_menu;

QE_SINGLETON_CPP(QMenu)

MenuItemSprite* QMenu::createMenuItemSprite(const string& picture, const ccMenuCallback& callback, int x, int y)
{
	return createMenuItemSprite(picture, picture, callback, x, y);
}

MenuItemSprite* QMenu::createMenuItemSprite(const string& normal_picture, const string& pressed_picture, const ccMenuCallback& callback, int x, int y)
{
	Sprite* normal = Sprite::create(normal_picture);
	Sprite* pressed = Sprite::create(pressed_picture);
	pressed->setPositionY(normal->getPositionX() - x);
	pressed->setPositionY(normal->getPositionY() - y);

	MenuItemSprite * item = MenuItemSprite::create(normal, pressed, callback);
	return item;
}

MenuItemLabel* QMenu::createMenuItemLabel(const string& text, const ccMenuCallback& callback)
{
	Label* label = Label::create(text, QE_Font, 25);
	MenuItemLabel* item = MenuItemLabel::create(label, callback);
	item->setAnchorPoint(Vec2(0, 0));
	return item;
}

Menu* QMenu::createMenuLabel(const string& text, const ccMenuCallback& callback)
{
	MenuItemLabel* item = createMenuItemLabel(text, callback);
	item->setColor(Color3B::BLACK);
	Menu* menu = Menu::create(item, NULL);
	menu->setAnchorPoint(Vec2(0, 0));
	return menu;
}
 
Menu* QMenu::createMenuSprite(const string& picture, const ccMenuCallback& callback, MenuItem *&item){ return createMenuSprite(picture, picture, callback, item); }

Menu* QMenu::createMenuSprite(const string& picture, const string& pressedPicture, const ccMenuCallback& callback, MenuItem*& item)
{
	item = createMenuItemSprite(picture, pressedPicture, callback);
	Menu* menu = Menu::create(item, NULL);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(0, 0);
	return menu;
}

Menu* QMenu::createMenuSprite(const string& picture, const string& pressedPicture, const ccMenuCallback& callback){ return createMenuSprite(picture, pressedPicture, callback, _item); }

Menu* QMenu::createMenuSprite(const string& picture, const ccMenuCallback& callback){ return createMenuSprite(picture, picture, callback); }

void QMenu::releaseMenuItemVector(vector<MenuItem*>& menuItems)
{
	for (vector<MenuItem*>::iterator it = menuItems.begin(); it != menuItems.end(); it++)
	{
		(*it)->removeFromParentAndCleanup(true);
	}
	menuItems.clear();
}