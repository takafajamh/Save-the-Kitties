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

	void AddPauzeScreen()
	{
		sf::Texture* no = CreateTexture("GPX/noClick.png");
		sf::Texture* yes = CreateTexture("GPX/Click.png");

		sf::Texture* stuff = CreateTexture("GPX/pauzaScreen.png");

		PauseScreen* ps = (PauseScreen*)AddObject(new PauseScreen());
		ps->me.setTexture(*stuff);
		ps->me.setScale(1, 1);
		ps->Layer = UIBack;
		ps->pos = sf::Vector2i(430, 80);


		Text* t_re = (Text*)AddObject(new Text("Restart", sf::Vector2f(560, 323)));
		t_re->Layer = UIFront;
		t_re->m_text.setCharacterSize(80);

		RestartButton* pb = (RestartButton*)AddObject(new RestartButton(no, yes));
		pb->Layer = UI;
		pb->me.setPosition(520, 320);
		pb->me.setScale(3, 3);

		ps->restart = pb;
		ps->t_re = t_re;



		Text* t_co = (Text*)AddObject(new Text("Continue", sf::Vector2f(560, 323)));
		t_co->Layer = UIFront;
		t_co->m_text.setCharacterSize(80);

		ContinueButton* cb = (ContinueButton*)AddObject(new ContinueButton(no, yes));
		cb->Layer = UI;
		cb->me.setPosition(520, 320);
		cb->me.setScale(3, 3);

		ps->continueBtn = cb;
		ps->t_co = t_co;


		Text* t_mu = (Text*)AddObject(new Text("UP", sf::Vector2f(560, 323)));
		t_mu->Layer = UIFront;
		t_mu->m_text.setCharacterSize(80);

		MusicVolumeButton* mvbu = (MusicVolumeButton*)AddObject(new MusicVolumeButton(no, yes, true));
		mvbu->Layer = UI;
		mvbu->me.setPosition(520, 320);
		mvbu->me.setScale(3, 3);


		ps->mvb_up = mvbu;
		ps->t_mup = t_mu;


		Text* t_md = (Text*)AddObject(new Text("DOWN", sf::Vector2f(560, 323)));
		t_md->Layer = UIFront;
		t_md->m_text.setCharacterSize(80);

		MusicVolumeButton* mvbd = (MusicVolumeButton*)AddObject(new MusicVolumeButton(no, yes, false));
		mvbd->Layer = UI;
		mvbd->me.setPosition(520, 320);
		mvbd->me.setScale(3, 3);


		ps->mvb_down = mvbd;
		ps->t_mdo = t_md;



		Text* t_su = (Text*)AddObject(new Text("UP", sf::Vector2f(560, 323)));
		t_su->Layer = UIFront;
		t_su->m_text.setCharacterSize(80);

		SoundsVolumeButton* svbu = (SoundsVolumeButton*)AddObject(new SoundsVolumeButton(no, yes, true));
		svbu->Layer = UI;
		svbu->me.setPosition(520, 320);
		svbu->me.setScale(3, 3);


		ps->svb_up = svbu;
		ps->t_sup = t_su;


		Text* t_sd = (Text*)AddObject(new Text("DOWN", sf::Vector2f(560, 323)));
		t_sd->Layer = UIFront;
		t_sd->m_text.setCharacterSize(80);

		SoundsVolumeButton* svbd = (SoundsVolumeButton*)AddObject(new SoundsVolumeButton(no, yes, false));
		svbd->Layer = UI;
		svbd->me.setPosition(520, 320);
		svbd->me.setScale(3, 3);

		ps->svb_down = svbd;
		ps->t_sdo = t_sd;


		SoundText* st = (SoundText*)AddObject(new SoundText("ss",sf::Vector2f(0,0)));
		ps->sot = st;
		st->Layer = UIFront;

		MusicText* mt = (MusicText*)AddObject(new MusicText("ss", sf::Vector2f(0, 0)));
		ps->mut = mt;
		mt->Layer = UIFront;



		Text* t_me = (Text*)AddObject(new Text("Menu", sf::Vector2f(560, 323)));
		t_me->Layer = UIFront;
		t_me->m_text.setCharacterSize(80);

		MenuButton* mbtn = (MenuButton*)AddObject(new MenuButton(no, yes));
		mbtn->Layer = UI;
		mbtn->me.setPosition(520, 320);
		mbtn->me.setScale(3, 3);


		ps->menuBtn = mbtn;
		ps->t_me = t_me;


		ps->Clean();
		
	}

	void Create() override
	{
#ifdef StateLevel
		if (!ShowedColliders)
		{
			ShowedColliders = true;
			tell("Which level you want to play?");
			std::cin >> Flags::LevelCount;
		}
#endif // StateLeve



		Flags::Stop = false;
		sf::Texture* t_cat = CreateTexture("GPX/cat_alt-Sheet.png");

		Object* Cat = CreateObject(t_cat);
		Cat->me.setScale(2, 2);

		Animator* anim_cat = (Animator*)Cat->AddComponent(new Animator());
		CatMove* cmove_cat = (CatMove*)Cat->AddComponent(new CatMove());
		cmove_cat->anim = anim_cat;
		cmove_cat->InitAnimations();
		cmove_cat->catState = CatMove::CatState::Falling;

		MapLoader* ml = (MapLoader*)AddObject(new MapLoader());

		//Flags::LevelCount = 5;

		std::string LevelPath = "GPX/Levels/level" + std::to_string(Flags::LevelCount) + ".png";
		std::string LevelRaysPath = "GPX/Levels/level" + std::to_string(Flags::LevelCount) + "-rays.png";

		std::ifstream file(LevelPath);
		if (file.good())
		{
			std::string catPath;
			switch (Flags::LevelCount)
			{
			case 0:
				catPath = "GPX/Kass.png";
				break;
			case 1:
				catPath = "GPX/Odoru..png";
				break;
			case 2:
				catPath = "GPX/Liya.png";
				break;
			case 3:
				catPath = "GPX/Carmen.png";
				break;
			case 4:
				catPath = "GPX/bee.png";
				break;
			case 5:
				catPath = "GPX/Liam.png";
				break;
			case 6:
				catPath = "GPX/Maitake.png";
				break;
			default:
				catPath = "GPX/Kass.png";
				break;
			}


			cmove_cat->obstacles = ml->GenerateMap(LevelPath, LevelRaysPath, catPath);
		}
		else
		{
			GetGame()->ChangeScene(new Win());
		}

		/*
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
			cmove_cat->obstacles = ml->GenerateMap("GPX/Levels/level4.png", "GPX/Levels/level4-rays.png");
			break;
		case 5:
			cmove_cat->obstacles = ml->GenerateMap("GPX/Levels/level5.png", "GPX/Levels/level5-rays.png");
			break;
		case 6:
			cmove_cat->obstacles = ml->GenerateMap("GPX/Levels/level6.png", "GPX/Levels/level6-rays.png");
			break;
		default:
			GetGame()->ChangeScene(new Win());
			break;
		}*/
		
		Cat->me.setPosition(ml->catPosition.x, ml->catPosition.y - 20);



		AddPauzeScreen();


		Timer* t_timer = (Timer*)AddObject(new Timer());
		t_timer->Layer = UIFront;
		t_timer->m_text.setCharacterSize(52);


	}
};