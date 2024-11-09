#pragma once
#include "Scene.hpp"
#include "Components.hpp"
#include "Object.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>


class Win : public Scene
{
	void Create()
	{
		Text* t = (Text*)AddObject(new Text("\nThank You for playing!!! \n Programming and saved cats done by Shadow Kitsune \n Level desing and graphics: Ignof \n Music by Imie!", sf::Vector2f(100, 50)));
		Text* t1 = (Text*)AddObject(new Text("Click R - like Ready, when You are ready to go back to menu, or try again", sf::Vector2f(100, 550)));
		AddObject(new ChangeToMenu());
		Flags::LevelCount = 0;


		Object* cat = CreateObject(CreateTexture("GPX/Kass.png"));
		Object* cat1 = CreateObject(CreateTexture("GPX/Liya.png"));
		Object* cat2 = CreateObject(CreateTexture("GPX/Odoru..png"));
		Object* cat3 = CreateObject(CreateTexture("GPX/Carmen.png"));
		Object* cat4 = CreateObject(CreateTexture("GPX/bee.png"));

		cat->me.setScale(4, 4);
		cat1->me.setScale(4, 4);
		cat2->me.setScale(4, 4);
		cat3->me.setScale(4, 4);
		cat4->me.setScale(4, 4);

		cat->me.setPosition(100, 300);
		cat1->me.setPosition(250, 300);
		cat2->me.setPosition(400, 300);
		cat3->me.setPosition(550, 300);
		cat4->me.setPosition(700, 300);
	}
};

class Menu : public Scene
{
	void Create()
	{
		Flags::LoadStats("config.txt");

		sf::Texture* no = CreateTexture("GPX/noClick.png");
		sf::Texture* yes = CreateTexture("GPX/Click.png");

		Object* o = CreateObject("GPX/Title.png");
		o->me.setPosition(430, 80);
		o->me.setScale(3, 3);

		Text* t = (Text*)AddObject(new Text("Play", sf::Vector2f(560, 323)));
		t->Layer = UI;
		t->m_text.setCharacterSize(80);

		Text* t1 = (Text*)AddObject(new Text("Quit", sf::Vector2f(568, 485)));
		t1->Layer = UI;
		t1->m_text.setCharacterSize(80);

		PlayButton* pb = new PlayButton(no, yes);
		pb->me.setPosition(520, 320);
		pb->me.setScale(6, 6);

		QuitButton* qb = new QuitButton(no, yes);
		qb->me.setPosition(520, 480);
		qb->me.setScale(6, 6);

		AddObject(pb);
		AddObject(qb);

		Object* background = CreateObject("GPX/back.png");
		background->me.setScale(3, 3);
		background->me.setPosition(-50, -10);
		background->Layer = Background;


		Text* t2 = (Text*)AddObject(new Text("Up Arror for louder music", sf::Vector2f(800, 600)));
		Text* t3 = (Text*)AddObject(new Text("Down Arror for quiter music", sf::Vector2f(800, 660)));

		AddObject(new MusicHandler());

		
	}
};

class MainScene : public Scene
{
public:
	void Create() override
	{

		sf::Texture* t_cat = CreateTexture("GPX/cat_alt-Sheet.png");

		Object* Cat = CreateObject(t_cat);
		Cat->me.setPosition(200, 24 * 64*2);
		Cat->me.setScale(2, 2);

		Animator* anim_cat = (Animator*)Cat->AddComponent(new Animator());
		CatMove* cmove_cat = (CatMove*)Cat->AddComponent(new CatMove());
		cmove_cat->anim = anim_cat;
		cmove_cat->InitAnimations();
		cmove_cat->catState = CatMove::CatState::Falling;

		MapLoader* ml = (MapLoader*)AddObject(new MapLoader());

		//Flags::LevelCount = 3;

		switch (Flags::LevelCount)
		{
		case 0:
			cmove_cat->obstacles = ml->GenerateMap("GPX/Levels/level0.png","GPX/Levels/level0-rays.png");
			break;
		case 1:
			cmove_cat->obstacles = ml->GenerateMap("GPX/Levels/level1.png", "GPX/Levels/level1-rays.png");
			break;
		case 2:
			cmove_cat->obstacles = ml->GenerateMap("GPX/Levels/level2.png", "GPX/Levels/level2-rays.png");
			break;
		case 3:
			cmove_cat->obstacles = ml->GenerateMap("GPX/Levels/level3.png", "GPX/Levels/level3-rays.png");
			break;
		case 4:
			GetGame()->ChangeScene(new Win());
			//cmove_cat->obstacles = ml->GenerateMap("GPX/level4.png");
			break;
		default:
			GetGame()->ChangeScene(new Win());
			break;
		}
		




	}
};