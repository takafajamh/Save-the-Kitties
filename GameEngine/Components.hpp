#pragma once
#include "Component.hpp"
#include "Globals.hpp"
#include "Object.hpp"
#include "Game.hpp"
#include "Scene.hpp"

#include <iostream>
#include <math.h>
#include <fstream>	
#include <string>
#include <sstream>

#include <unordered_map>
#include <string>





///todo
/*
Credits


Jump indicator
Cheatmode!

Better cat release
Fix colliders

Add lore
Add secret parts of the rooms?
	invisible blocks
	When touched it shows
	color based?
	so 2 files...

Wall jumps on soft stuff

*/


class Flags
{
public:
	static inline float LevelTime[20] = { 0 };
	static inline int DeathCounter[20] = { 0 };

	static inline int LevelCount = 0;

	static inline int MusicVolume = 50;
	static inline int SoundsVolume = 50;

	static inline bool Stop = false;

	static inline bool EasyMode = false;


	// Cat parameters
	static inline float catSpeed = 0.0f;
	static inline float catMaxSpeed = 0.0f;
	static inline float catAccTime = 0.0f;
	static inline float catDeccTime = 0.0f;
	static inline float catMaxJumpForce = 0.0f;
	static inline float catJumpForceSpeed = 0.0f;
	static inline float catGravity = 0.0f;

	// Map parameters
	static inline std::vector<sf::Vector2i> WinBlockPositions;
	static inline std::vector<sf::Vector2i> DeadBlockPositionsD;
	static inline std::vector<sf::Vector2i> DeadBlockPositionsU;
	static inline std::vector<sf::Vector2i> DeadBlockPositionsL;
	static inline std::vector<sf::Vector2i> DeadBlockPositionsR;



	static inline std::vector<sf::Vector2i> NoCollideBlockPositions;
	static inline std::vector<sf::Vector2i> ButtonBlockPositions;
	static inline std::vector<sf::Vector2i> LaserBlockPositions;
	static inline std::vector<sf::Vector2i> LaserRayBlockPositions;
	static inline float BlockScale = 0;
	static inline int BlockSizePixels = 0;
	static inline std::string LegendPath;
	static inline std::string SheetPath;
	static inline sf::Vector2i BaseBackgroundBlock;

	static inline void LoadIntoVector(std::string value, std::vector<sf::Vector2i>& into)
	{
		// Parse position in the format "x;y"
		float x, y;
		std::replace(value.begin(), value.end(), ';', ' ');
		std::istringstream posStream(value);
		if (posStream >> x >> y) 
		{
			into.emplace_back(x, y);
		}
	}

	static inline void LoadIntoVec2(std::string value, sf::Vector2i& into)
	{
		float x, y;
		std::replace(value.begin(), value.end(), ';', ' ');
		std::istringstream posStream(value);
		if (posStream >> x >> y)
		{
			into = sf::Vector2i(x, y);
		}
	}

	static inline void LoadStats(std::string path)
	{
		std::ifstream file(path);
		if (!file.is_open()) 
		{
			std::cerr << "Failed to open file: " << path << std::endl;
			return;
		}

		std::string line;
		while (std::getline(file, line)) 
		{
			// Ignore comments
			if (line.find("//") == 0) continue;

			std::istringstream stream(line);
			std::string key;

			if (std::getline(stream, key, ':')) 
			{
				std::string value;
				std::getline(stream, value);

				// Trim whitespace
				key.erase(0, key.find_first_not_of(" \t"));
				key.erase(key.find_last_not_of(" \t") + 1);

				value.erase(0, value.find_first_not_of(" \t"));
				value.erase(value.find_last_not_of(" \t") + 1);

				// Parse key-value pairs
				if (key == "CatSpeed") 
				{
					catSpeed = std::stof(value);
				}
				else if (key == "CatMaxSpeed") 
				{
					catMaxSpeed = std::stof(value);
				}
				else if (key == "BlockScale")
				{
					BlockScale = std::stof(value) + 0.00f;
				}
				else if (key == "BlockSizePixels")
				{
					BlockSizePixels = std::stof(value);
				}
				else if (key == "CatAccTime") 
				{
					catAccTime = std::stof(value);
				}
				else if (key == "CatDeccTime") 
				{
					catDeccTime = std::stof(value);
				}
				else if (key == "CatMaxJumpForce") 
				{
					catMaxJumpForce = std::stof(value);
				}
				else if (key == "CatJumpForceSpeed") 
				{
					catJumpForceSpeed = std::stof(value);
				}
				else if (key == "CatGravity") 
				{
					catGravity = std::stof(value);
				}
				else if (key == "WinBlockPosition") 
				{
					LoadIntoVector(value, WinBlockPositions);
				}
				else if (key == "DeadBlockPositionsD")
				{
					LoadIntoVector(value, DeadBlockPositionsD);
				}
				else if (key == "DeadBlockPositionsU")
				{
					LoadIntoVector(value, DeadBlockPositionsU);
				}
				else if (key == "DeadBlockPositionsR")
				{
					LoadIntoVector(value, DeadBlockPositionsR);
				}
				else if (key == "DeadBlockPositionsL")
				{
					LoadIntoVector(value, DeadBlockPositionsL);
				}
				else if (key == "NoCollideBlockPositions")
				{
					LoadIntoVector(value, NoCollideBlockPositions);
				}
				else if (key == "ButtonBlockPositions")
				{
					LoadIntoVector(value, ButtonBlockPositions);
				}
				else if (key == "BaseBackgroundBlock")
				{
					LoadIntoVec2(value, BaseBackgroundBlock);
				}
				else if (key == "LaserBlockPositions")
				{
					LoadIntoVector(value, LaserBlockPositions);
				}
				else if (key == "LaserRayBlockPositions")
				{
					LoadIntoVector(value, LaserRayBlockPositions);
				}
				else if (key == "LegendPath") 
				{
					LegendPath = value;
				}
				else if (key == "SheetPath")
				{
					SheetPath = value;
				}
			}
		}
		file.close();

	}

};

class MusicHandler : public Object
{
public:
	bool u = false;
	bool d = false;

	void Update()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			u = true;
		}
		else
		{
			if (u)
			{
				u = false;
				Flags::MusicVolume += 10;

				if (Flags::MusicVolume > 100)
					Flags::MusicVolume = 100;

			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			d = true;
		}
		else
		{
			if (d)
			{
				d = false;
				Flags::MusicVolume -= 10;

				if (Flags::MusicVolume < 00)
					Flags::MusicVolume = 00;

			}
		}

		GetScene()->GetGame()->music.setVolume(Flags::MusicVolume);
	}
};

class Button : public Object
{
protected:
	sf::Texture* defaultTexture = nullptr;
	sf::Texture* hoverTexture = nullptr;
	bool isHovered = false;
	bool wasClicked = false;
	bool firstClick = true;
public:

	bool Active = true;

	Button(sf::Texture* defaultTex, sf::Texture* hoverTex)
	{
		defaultTexture = defaultTex;
		hoverTexture = hoverTex;
		me.setTexture(*defaultTexture);
	}


	virtual void Update() override
	{
		if (firstClick)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				return;
			}
			else
			{
				firstClick = false;
			}
		}
		
		if (!Active)
			return;

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

		if (me.getGlobalBounds().contains(worldPos))
		{
			if (!isHovered)
			{
				isHovered = true;
				me.setTexture(*hoverTexture);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (!wasClicked)
				{
					wasClicked = true;
					onClick();
				}


			}
			else
			{
				wasClicked = false;
			}
		}
		else
		{
			if (isHovered)
			{
				isHovered = false;
				me.setTexture(*defaultTexture);
			}
		}
	}



	void Draw() override
	{
		if (!Active)
			return;

		window.draw(me);
	}

	virtual void onClick() = 0; // Pure virtual function to be implemented by derived classes
};

class PlayButton : public Button
{
public:
	PlayButton(sf::Texture* defaultTex, sf::Texture* hoverTex)
		: Button(defaultTex, hoverTex) {}

	virtual void onClick();

};

class SettingsButton : public Button
{
public:
	SettingsButton(sf::Texture* defaultTex, sf::Texture* hoverTex)
		: Button(defaultTex, hoverTex) {}

	virtual void onClick();

};

class RestartButton : public PlayButton
{
public:
	RestartButton(sf::Texture* defaultTex, sf::Texture* hoverTex)
		: PlayButton(defaultTex, hoverTex) {}

	virtual void onClick()
	{
		Flags::LevelTime[Flags::LevelCount] = 0;
		PlayButton::onClick();
	}
};

class QuitButton : public Button
{
public:
	QuitButton(sf::Texture* defaultTex, sf::Texture* hoverTex)
		: Button(defaultTex, hoverTex) {}


	void onClick();

};

class FlagClickerButton : public Button
{
public:
	bool* set;
	bool once = false;
	sf::Texture* d;
	sf::Texture* h;

	FlagClickerButton(sf::Texture* defaultTex, sf::Texture* hoverTex, bool* setter)
		: Button(defaultTex, hoverTex)
	{
		set = setter;
		d = defaultTex;
		h = hoverTex;

		if (!(*set))
		{
			defaultTex = h;
			hoverTex = d;
			me.setTexture(*defaultTex);

		}
	}

	void Update()
	{
		if (!(*set) && !once)
		{
			once = true;
			defaultTexture = h;
			hoverTexture = d;
			me.setTexture(*defaultTexture);
		}

		Button::Update();

		

	}

	virtual void onClick()
	{
		(*set) = !(*set);
		if (!(*set))
		{
			defaultTexture = h;
			hoverTexture = d;
		}
		else
		{
			defaultTexture = d;
			hoverTexture = h;
		}

		me.setTexture(*hoverTexture);

	}
};


class MusicVolumeButton : public Button
{
public:
	bool Up;

	MusicVolumeButton(sf::Texture* defaultTex, sf::Texture* hoverTex, bool up)
		: Button(defaultTex, hoverTex) 
	{
		Up = up;
	}

	void onClick() 
	{
		if (Up)
		{
			Flags::MusicVolume += 5;

			if (Flags::MusicVolume > 100)
				Flags::MusicVolume = 100;
		}
		else
		{
			Flags::MusicVolume -= 5;

			if (Flags::MusicVolume < 0)
				Flags::MusicVolume = 0;
		}
		GetScene()->GetGame()->music.setVolume(Flags::MusicVolume);
			
	}
};

class SoundsVolumeButton : public Button
{
public:
	bool Up;

	SoundsVolumeButton(sf::Texture* defaultTex, sf::Texture* hoverTex, bool up)
		: Button(defaultTex, hoverTex) 
	{
		Up = up;
	}

	void onClick()
	{
		if (Up)
		{
			Flags::SoundsVolume += 5;

			if (Flags::SoundsVolume > 100)
				Flags::SoundsVolume = 100;
		}
		else
		{
			Flags::SoundsVolume -= 5;

			if (Flags::SoundsVolume < 0)
				Flags::SoundsVolume = 0;
		}

		//GetScene()->GetGame()->music.setVolume(Flags::SoundsVolume);

	}
};

class ContinueButton : public Button
{
public:
	bool Continue = false;
	ContinueButton(sf::Texture* defaultTex, sf::Texture* hoverTex)
		: Button(defaultTex, hoverTex) {}

	void onClick()
	{
		Continue = true;


	}
};

class MenuButton : public Button
{
public:
	MenuButton(sf::Texture* defaultTex, sf::Texture* hoverTex)
		: Button(defaultTex, hoverTex) {}

	void onClick();
};





class Text : public Object
{
public:
	sf::Text m_text;
	sf::Font font;

	bool Active = true;

	Text(std::string text, sf::Vector2f pos)
	{
		font.loadFromFile("Font/munro.ttf");
		me.setPosition(pos);
		m_text.setString(text);
		m_text.setScale(0.8f, 0.8f);
		m_text.setCharacterSize(36);
		m_text.setFillColor(sf::Color::White);
		m_text.setPosition(pos);
		m_text.setFont(font);
	}
	virtual void Update()
	{
		if(Active)
			Object::Update();
	}
	void Draw()
	{
		if (!Active)
			return;

		m_text.setPosition(me.getPosition());
		window.draw(m_text);

	}
};


class SoundText : public Text
{
public:
	SoundText(std::string text, sf::Vector2f pos) : Text(text, pos)
	{

	}


	void Update()
	{
		Text::Update();

		if (!Active)
			return;

		m_text.setString(std::to_string(Flags::SoundsVolume));
	}

};

class MusicText : public Text
{
public:
	MusicText(std::string text, sf::Vector2f pos) : Text(text, pos)
	{

	}


	void Update()
	{
		Text::Update();

		if (!Active)
			return;

		m_text.setString(std::to_string(Flags::MusicVolume));

	}

};

class Timer : public Text
{
public:
	float time = 0;
	sf::Vector2i pos = sf::Vector2i(10,10);
	Timer() : Text("text", sf::Vector2f(2,2))
	{

	}


	void Update()
	{
		Text::Update();

		if (!Active)
			return;

		sf::Vector2f newPos = window.mapPixelToCoords(pos);
		me.setPosition(newPos);

		Flags::LevelTime[Flags::LevelCount] += dt;
	
		std::string sText = std::to_string(std::round(Flags::LevelTime[Flags::LevelCount] * 100.0f) / 100.0f);

		sText.erase(sText.find('.') + 3);
		m_text.setString(sText);

	}
};


template <class T>
class LevelButton : public Button
{
public:
	LevelButton(sf::Texture* defaultTex, sf::Texture* hoverTex)
		: Button(defaultTex, hoverTex) {}

	void onClick();//Create a class, change scene

};

class ChangeToMenu : public Object
{
public:
	void Update()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			Go();
	}
	void Draw()
	{

	}
	void Go();
};


class Animation
{
public:
	struct Frame
	{
		sf::IntRect InTexture;
		float FrameTime;
		Frame(sf::IntRect fr, float time)
		{
			FrameTime = time;
			InTexture = fr;
		}
	};

	std::string Name;
	std::vector<Frame> frames;

	Animation(std::string name, std::vector<Frame> fr)
	{
		Name = name;
		frames = fr;
	}
};

class Animator : public Component
{
public:
	bool Inited = false;

	bool EndFrame = false; //if true, end anim in last frame
	int XSize = 24;
	int YSize = 48;

	std::vector<Animation> anims;
	int RunningId = 0;
	std::string RunningName = "";

	bool running = false;

	float FrameTime = 0;
	int Frame = -1;
	bool looping = true;

	float RunningSpeed = 1;

	bool onEnd = false;
	std::string onEndName = "";


	Animator() {}

	bool Play(std::string AnimationName)
	{
		if (AnimationName == anims.at(RunningId).Name && Inited)
		{
			return false;
		}
		for (int i = 0; i < anims.size(); i++)
		{
			if (anims.at(i).Name == AnimationName)
			{
				Inited = true;
				running = true;
				RunningName = AnimationName;
				RunningId = i;
				FrameTime = 0;
				Frame = -1;
				return true;
			}
		}
		return false;
	}

	void Update()
	{
		if (running)
		{
			if (FrameTime <= 0)
			{

				Frame++;

				if (Frame >= anims.at(RunningId).frames.size())
				{
					Frame = 0;
					if (onEnd)
					{
						Play(onEndName);
						onEnd = false;
						onEndName = "";
						return;
					}
					if (!looping)
					{
						Stop();
						return;
					}
				}

				Holder->me.setTextureRect(anims.at(RunningId).frames.at(Frame).InTexture);
				FrameTime = anims.at(RunningId).frames.at(Frame).FrameTime;
			}
			else
			{
				FrameTime -= RunningSpeed * dt;
			}

		}
	}


	bool PlayOnEnd(std::string AnimationName)
	{
		if (AnimationName == anims.at(RunningId).Name && Inited || onEndName == AnimationName)
		{
			return false;
		}
		if (!running)
		{
			Play(AnimationName);
			return true;
		}

		onEnd = true;
		onEndName = AnimationName;
		return true;

	}
	void Stop()
	{
		if (!running) return;

		if (!EndFrame) Holder->me.setTextureRect(anims.at(RunningId).frames.at(0).InTexture);

		RunningId = 0;
		running = false;
		FrameTime = 0;
		Frame = -1;
		RunningName = "";


	}
	void Pause()
	{
		running = false;
	}
	virtual ~Animator() {}
};


class Obstacle : public Component
{
public:
	sf::FloatRect collider;
	enum Mode 
	{
		fullblock,
		L,
		R,
		D,
		U
	};

	int width = (2 *  Flags::BlockSizePixels / 3) * Flags::BlockScale;

	Mode colliderMode = fullblock;

	virtual void Update()
	{
		collider = Holder->me.getGlobalBounds();
		switch (colliderMode)
		{
		case Obstacle::L:
			collider.width -= width;
			collider.height -= width;

			collider.top += width / 4;

			break;
		case Obstacle::R:
			collider.width -= width;
			collider.height -= width;

			collider.top += width / 4;
			collider.left += width / 2;
			break;
		case Obstacle::D:
			collider.width -= width;
			collider.height -= width;

			collider.top += width / 2;
			collider.left += width / 4;
			break;
		case Obstacle::U:
			collider.width -= width;
			collider.height -= width;

			collider.left += width / 4;
			break;
		default:
			break;
		}

#ifdef ShowColliders
		ColliderRects.push_back(collider);
#endif // ShowColliders


	}
	virtual void Collide()
	{

	}
};

class DeadObstacle : public Obstacle
{
public:

	virtual void Collide() override
	{
		Do();
	}

	void Do();
};


class LaserObstacle : public Obstacle
{
public:

	bool done = false;

	void Update()
	{
		Obstacle::Update();
	}

	virtual void Collide() override
	{
		Do();
	}

	void Do();
};

class Laser1Obstacle : public Obstacle
{
public:

	bool done = false;

	void Update()
	{
		Obstacle::Update();
	}
	virtual void Collide() override
	{
		//dead
	}
};

class DoObstacle : public Obstacle
{
public:

	std::vector <LaserObstacle*> Rays;
	std::vector <Laser1Obstacle*> Shooters;


	bool done = false;
	virtual void Collide() override
	{
		if (done)
			return;

		Obstacle::Update();

		done = true;
		sf::IntRect a = Holder->me.getTextureRect();
		a.left += Flags::BlockSizePixels;
		Holder->me.setTextureRect(a);

		for (LaserObstacle* lo : Rays)
		{
			lo->Holder->me.setPosition(20000, 20000);
		}

		for (Laser1Obstacle* l1o : Shooters)
		{
			((Animator*)(l1o->Holder->GetComponents()[1]))->Stop();
			sf::IntRect a = l1o->Holder->me.getTextureRect();
			l1o->Holder->me.setTextureRect(sf::IntRect(a.left + (Flags::BlockSizePixels * 2), a.top, Flags::BlockSizePixels, Flags::BlockSizePixels));
		}

	}
};


class winObstacle : public Obstacle
{
public:
	bool done = false;

	Object* s = nullptr;
	Object* to = nullptr;
	float time = 0;
	
	void Update()
	{
		Obstacle::Update();


		if (s == nullptr)
			return;

		Flags::LevelTime[Flags::LevelCount] -= dt;

		if (time > 2.3f)
		{
			tell( "Poziom " << Flags::LevelCount << " t = " << Flags::LevelTime[Flags::LevelCount] << " Dead: " << Flags::DeathCounter[Flags::LevelCount]);
			Do();
			Flags::LevelCount++;
		}
			

		time += dt;

		s->me.setScale(2 * (1 + 2*time), 2 * (1 + 2*time));
		s->me.move(-220 * dt, -220 * dt);
		
	}
	virtual void Collide() override
	{
		if (s != nullptr)
			return;
		
		s = to;
		s->Layer = Foreground;
		Holder->GetScene()->sorted = false;
	}
	void Do();
};

class ToDrawObject : public Object
{
public:
	bool ToDraw = false;
	void Update()
	{

	}

	void Draw()
	{
		if (ToDraw) window.draw(me);
	}

};


struct ColorHash
{
	std::size_t operator()(const sf::Color& color) const
	{
		return ((std::hash<int>()(color.r) ^ (std::hash<int>()(color.g) << 1)) >> 1)
			^ (std::hash<int>()(color.b) << 1)
			^ (std::hash<int>()(color.a) << 1);
	}
};


#ifdef MapLoaderOn
inline sf::Vector2f posix;
#endif 




class PauseScreen : public Object
{
public:
	sf::Vector2i pos;

	bool Run = false;

	SoundsVolumeButton* svb_up;
	Text* t_sup;
	SoundsVolumeButton* svb_down;
	Text* t_sdo;

	MusicVolumeButton* mvb_up;
	Text* t_mup;
	MusicVolumeButton* mvb_down;
	Text* t_mdo;

	RestartButton* restart;
	Text* t_re;
	ContinueButton* continueBtn;
	Text* t_co;

	MenuButton* menuBtn;
	Text* t_me;

	SoundText* sot;
	MusicText* mut;


	bool clicked = false;

	void Draw()
	{
		if(Run)
			window.draw(me);
	}

	void Clean()
	{
		sot->Active = false;
		mut->Active = false;

		svb_up->Active = false;
		svb_down->Active = false;
		mvb_up->Active = false;
		mvb_down->Active = false;
		restart->Active = false;
		continueBtn->Active = false;

		t_mup->Active = false;
		t_sup->Active = false;
		t_mdo->Active = false;
		t_sdo->Active = false;
		t_re->Active = false;
		t_co->Active = false;

		menuBtn->Active = false;
		mut->Active = false;
		t_me->Active = false;
		
	}

	void UnClean()
	{
		me.setPosition(window.mapPixelToCoords(pos));
		sf::Vector2f Base = me.getPosition();

		sot->Active = true;
		mut->Active = true;


		menuBtn->Active = true;
		t_me->Active = true;

		svb_up->Active = true;
		svb_down->Active = true;
		mvb_up->Active = true;
		mvb_down->Active = true;
		restart->Active = true;
		continueBtn->Active = true;
		continueBtn->Continue = false;

		t_mup->Active = true;
		t_sup->Active = true;
		t_mdo->Active = true;
		t_sdo->Active = true;
		t_re->Active = true;
		t_co->Active = true;

		svb_up->me.setPosition(Base.x + 188 + 8, Base.y + 112);
		t_sup->me.setPosition(Base.x + 188 + 42, Base.y + 116);
		t_sup->m_text.setCharacterSize(36);

		svb_down->me.setPosition(Base.x + 8, Base.y + 112);
		t_sdo->me.setPosition(Base.x + 4 + 24, Base.y + 117);
		t_sdo->m_text.setCharacterSize(36);


		sot->me.setPosition(Base.x + 82 + 50, Base.y + 116);
		sot->m_text.setCharacterSize(36);


		mvb_up->me.setPosition(Base.x + 188 + 8, Base.y + 212);
		t_mup->me.setPosition(Base.x + 188 + 42, Base.y + 216);
		t_mup->m_text.setCharacterSize(36);

		mvb_down->me.setPosition(Base.x +  8, Base.y + 212);
		t_mdo->me.setPosition(Base.x +  4 + 24, Base.y + 217);
		t_mdo->m_text.setCharacterSize(36);

		mut->me.setPosition(Base.x + 82 + 50, Base.y + 216);
		mut->m_text.setCharacterSize(36);



		continueBtn->me.setPosition(Base.x + 82 , Base.y + 272);
		continueBtn->me.setScale(4, 4);
		t_co->me.setPosition(Base.x + 82 + 15, Base.y + 283);
		t_co->m_text.setCharacterSize(36);


		restart->me.setPosition(Base.x + 82, Base.y + 352);
		restart->me.setScale(4, 4);
		t_re->me.setPosition(Base.x + 82 + 21, Base.y + 363);
		t_re->m_text.setCharacterSize(36);

		menuBtn->me.setPosition(Base.x + 82, Base.y + 432);
		menuBtn->me.setScale(4, 4);
		t_me->me.setPosition(Base.x + 82 + 31, Base.y + 443);
		t_me->m_text.setCharacterSize(36);


	}

	void Update()
	{
		if (Run)
		{
			if (continueBtn->Continue)
			{
				Clean();
				Run = false;
				clicked = false;
				Flags::Stop = false;
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				clicked = true;
			}
			else
			{
				if (clicked)
				{
					clicked = false;
					Clean();
					Flags::Stop = false;
					Run = false;
				}
			}
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				clicked = true;
			}
			else
			{
				if (clicked)
				{
					clicked = false;
					UnClean();
					Flags::Stop = true;
					Run = true;
				}
			}
		}
	}
};

class MapLoader : public Object
{
public:
	float speed = 800;
	sf::Vector2f catPosition;

#ifdef MapLoaderOn
	MapLoader()
	{
		if (posix.x != 0)
		{
			sf::View v = window.getDefaultView();
			sf::View v1 = window.getDefaultView();

			v.setSize(v1.getSize() * 3.0f);
			v.setCenter(posix);
			window.setView(v);
		}
		
		


	}
#endif // MapLoaderOn


	void Update()
	{
#ifdef MapLoaderOn

		sf::View v = window.getView();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			v.move(0, (int)(speed * -dt));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			v.move(0, (int)(speed * dt));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			v.move((int)(speed * -dt), 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			v.move((int)(speed * dt), 0);
		}

		posix = v.getCenter();

		window.setView(v);

		Do();
		
#endif
	}

#ifdef MapLoaderOn
	void Do();
#endif // MapLoaderOn

	

	void Draw()
	{

	}
	~MapLoader(){}

	std::unordered_map<sf::Color, sf::IntRect, ColorHash> LoadLegend(const std::string& legendPath)
	{
		std::unordered_map<sf::Color, sf::IntRect, ColorHash> colorRectMap;
		sf::Image legend;

		// Load the legend image
		if (!legend.loadFromFile(legendPath))
		{
			std::cerr << "Failed to load legend image from path: " << legendPath << std::endl;
			return colorRectMap;
		}

		// Get the size of the legend image
		sf::Vector2u legendSize = legend.getSize();

		// Iterate over each pixel in the legend image
		for (unsigned int y = 0; y < legendSize.y; ++y)
		{
			for (unsigned int x = 0; x < legendSize.x; ++x)
			{
				sf::Color color = legend.getPixel(x, y);

				// Skip fully transparent pixels
				if (color.a == 0) continue;

				// Map the color to a texture rectangle based on its position
				sf::IntRect textureRect(x * Flags::BlockSizePixels, y * Flags::BlockSizePixels, Flags::BlockSizePixels, Flags::BlockSizePixels);
				colorRectMap[color] = textureRect;
			}
		}

		return colorRectMap;
	}

	std::vector<Obstacle*> GenerateMap(const std::string& path, const std::string& specialPath, const std::string& catPath)
	{
		sf::Texture* spriteSheet = GetScene()->CreateTexture(Flags::SheetPath);
		sf::Texture* cattex = GetScene()->CreateTexture(catPath);

		std::unordered_map<sf::Color, sf::IntRect, ColorHash> colorRectMap = LoadLegend(Flags::LegendPath);
		std::unordered_map<sf::Color, DoObstacle*, ColorHash> specialEffectsMap;


		std::vector<Obstacle*> obstacles;
		sf::Image image;
		sf::Image effectorMap;

		if (!image.loadFromFile(path) || !effectorMap.loadFromFile(specialPath)) // load a map file
		{
			std::cerr << "Failed to load map image from path: " << path << "or " << specialPath << std::endl;
			return obstacles;
		}

		if (image.getSize().x != effectorMap.getSize().x || image.getSize().y != effectorMap.getSize().y)
		{
			std::cerr << "Ray map and normal map are of a different size!"<<std::endl;
#ifndef MapLoaderOn
			return obstacles;
#endif // !MapLoaderOn
			exit(-2);
		}

		sf::Vector2u imageSize = image.getSize();

		//load buttons first
		for (unsigned int y = 0; y < imageSize.y; ++y)
		{
			for (unsigned int x = 0; x < imageSize.x; ++x)
			{
				sf::Color color = image.getPixel(x, y);

				if (color.a == 0) continue;

				if (color == sf::Color(0, 0, 0))
				{
					catPosition = sf::Vector2f(x * Flags::BlockScale * Flags::BlockSizePixels, y * Flags::BlockScale * Flags::BlockSizePixels);
					
					Object* obs1 = GetScene()->CreateObject(spriteSheet);
					obs1->Layer = b3;
					obs1->me.setScale(Flags::BlockScale, Flags::BlockScale);
					obs1->me.setPosition(x * Flags::BlockScale * Flags::BlockSizePixels, y * Flags::BlockSizePixels * Flags::BlockScale);

					obs1->me.setTextureRect(sf::IntRect(Flags::BaseBackgroundBlock.x * Flags::BlockSizePixels, Flags::BaseBackgroundBlock.y * Flags::BlockSizePixels, Flags::BlockSizePixels, Flags::BlockSizePixels));

					
					continue;
				}

				if (colorRectMap.find(color) != colorRectMap.end())
				{
					sf::IntRect textureRect = colorRectMap[color];

					

					for (sf::Vector2i& pos : Flags::ButtonBlockPositions)
					{
						if (pos.x == textureRect.left / Flags::BlockSizePixels && pos.y == textureRect.top / Flags::BlockSizePixels)
						{
							Object* obs = GetScene()->CreateObject(spriteSheet);
							obs->Layer = b1;
							obs->me.setScale(Flags::BlockScale, Flags::BlockScale);
							obs->me.setPosition(x * Flags::BlockSizePixels * Flags::BlockScale, y * Flags::BlockSizePixels * Flags::BlockScale);

							obs->me.setTextureRect(textureRect);

							Obstacle* on = nullptr;


							on = static_cast<Obstacle*>(obs->AddComponent(new DoObstacle()));

							specialEffectsMap[effectorMap.getPixel(x, y)] = (DoObstacle*)on;


							obstacles.emplace_back(on);
						}
					}


				}

			}
		}


		for (unsigned int y = 0; y < imageSize.y; ++y)
		{
			for (unsigned int x = 0; x < imageSize.x; ++x)
			{
				sf::Color color = image.getPixel(x, y);

				if (color.a == 0) continue;

				if (colorRectMap.find(color) != colorRectMap.end())
				{
					sf::IntRect textureRect = colorRectMap[color];

					Object* obs = GetScene()->CreateObject(spriteSheet);
					obs->Layer = b1;
					obs->me.setScale(Flags::BlockScale, Flags::BlockScale);
					obs->me.setPosition(x * Flags::BlockSizePixels * Flags::BlockScale, y * Flags::BlockSizePixels * Flags::BlockScale);

					obs->me.setTextureRect(textureRect);

					Obstacle* on = nullptr;

					//napraw level to more dynamic

					bool nocoll = false;


					for (sf::Vector2i& pos : Flags::WinBlockPositions)
					{
						if (pos.x == textureRect.left / Flags::BlockSizePixels && pos.y == textureRect.top / Flags::BlockSizePixels)
						{
							nocoll = true;
							on = static_cast<Obstacle*>(obs->AddComponent(new winObstacle()));
							winObstacle* oo = (winObstacle*)on;

							sf::Texture* t_tex = cattex;

							Object* obs1 = GetScene()->CreateObject(spriteSheet);
							obs1->Layer = b3;
							obs1->me.setScale(Flags::BlockScale, Flags::BlockScale);
							obs1->me.setPosition(x * Flags::BlockScale * Flags::BlockSizePixels, y * Flags::BlockSizePixels * Flags::BlockScale);

							obs1->me.setTextureRect(sf::IntRect(Flags::BaseBackgroundBlock.x* Flags::BlockSizePixels, Flags::BaseBackgroundBlock.y * Flags::BlockSizePixels, Flags::BlockSizePixels, Flags::BlockSizePixels));

							Object* obs2 = GetScene()->CreateObject(t_tex); // cat
							obs2->Layer = b2;
							obs2->me.setScale(3, 3);

							float yPos = obs->me.getGlobalBounds().top + obs->me.getGlobalBounds().height - obs2->me.getGlobalBounds().height;
							float xPos = obs->me.getGlobalBounds().left + (obs->me.getGlobalBounds().width / 2) - (obs2->me.getGlobalBounds().width / 2);

							obs2->me.setPosition(xPos, yPos);

							oo->to = obs2;

							obs->GetScene()->sorted = false;
						}
					}


					float yAdjust = 0;
					if (x % 2 == y % 2)
					{
						yAdjust = Flags::BlockSizePixels;
					}
	

					
					for (sf::Vector2i& pos : Flags::DeadBlockPositionsU)
					{
						if (pos.x == textureRect.left / Flags::BlockSizePixels && pos.y == textureRect.top / Flags::BlockSizePixels)
						{
							nocoll = true;

							on = static_cast<Obstacle*>(obs->AddComponent(new DeadObstacle()));
							Animator* anim = (Animator*)obs->AddComponent(new Animator);

							anim->anims.emplace_back("Idle", std::vector<Animation::Frame>({
							Animation::Frame(sf::IntRect(textureRect.left, textureRect.top + yAdjust, Flags::BlockSizePixels, Flags::BlockSizePixels),0.15f),
							Animation::Frame(sf::IntRect(textureRect.left + Flags::BlockSizePixels, textureRect.top + yAdjust, Flags::BlockSizePixels, Flags::BlockSizePixels),0.15f),
								}));
							anim->Play("Idle");

							on->colliderMode = Obstacle::Mode::U;
						}
					}
					
					for (sf::Vector2i& pos : Flags::DeadBlockPositionsD)
					{
						if (pos.x == textureRect.left / Flags::BlockSizePixels && pos.y == textureRect.top / Flags::BlockSizePixels)
						{
							nocoll = true;

							on = static_cast<Obstacle*>(obs->AddComponent(new DeadObstacle()));
							Animator* anim = (Animator*)obs->AddComponent(new Animator);

							anim->anims.emplace_back("Idle", std::vector<Animation::Frame>({
							Animation::Frame(sf::IntRect(textureRect.left, textureRect.top + yAdjust, Flags::BlockSizePixels, Flags::BlockSizePixels),0.15f),
							Animation::Frame(sf::IntRect(textureRect.left + Flags::BlockSizePixels, textureRect.top + yAdjust, Flags::BlockSizePixels, Flags::BlockSizePixels),0.15f),
								}));
							anim->Play("Idle");

							on->colliderMode = Obstacle::Mode::D;
						}
					}
					
					for (sf::Vector2i& pos : Flags::DeadBlockPositionsL)
					{
						if (pos.x == textureRect.left / Flags::BlockSizePixels && pos.y == textureRect.top / Flags::BlockSizePixels)
						{
							nocoll = true;

							on = static_cast<Obstacle*>(obs->AddComponent(new DeadObstacle()));
							Animator* anim = (Animator*)obs->AddComponent(new Animator);

							anim->anims.emplace_back("Idle", std::vector<Animation::Frame>({
							Animation::Frame(sf::IntRect(textureRect.left, textureRect.top + yAdjust, Flags::BlockSizePixels, Flags::BlockSizePixels),0.15f),
							Animation::Frame(sf::IntRect(textureRect.left + Flags::BlockSizePixels, textureRect.top + yAdjust, Flags::BlockSizePixels, Flags::BlockSizePixels),0.15f),
								}));
							anim->Play("Idle");

							on->colliderMode = Obstacle::Mode::L;
						}
					}

					for (sf::Vector2i& pos : Flags::DeadBlockPositionsR)
					{
						if (pos.x == textureRect.left / Flags::BlockSizePixels && pos.y == textureRect.top / Flags::BlockSizePixels)
						{
							nocoll = true;

							on = static_cast<Obstacle*>(obs->AddComponent(new DeadObstacle()));
							Animator* anim = (Animator*)obs->AddComponent(new Animator);

							anim->anims.emplace_back("Idle", std::vector<Animation::Frame>({
							Animation::Frame(sf::IntRect(textureRect.left, textureRect.top + yAdjust, Flags::BlockSizePixels, Flags::BlockSizePixels),0.15f),
							Animation::Frame(sf::IntRect(textureRect.left + Flags::BlockSizePixels, textureRect.top + yAdjust, Flags::BlockSizePixels, Flags::BlockSizePixels),0.15f),
								}));
							anim->Play("Idle");

							on->colliderMode = Obstacle::Mode::R;
						}
					}

					for (sf::Vector2i& pos : Flags::LaserBlockPositions) // laser do wyłączenia
					{
						if (pos.x == textureRect.left / Flags::BlockSizePixels && pos.y == textureRect.top / Flags::BlockSizePixels)
						{
							nocoll = true;

							on = static_cast<Obstacle*>(obs->AddComponent(new Laser1Obstacle()));
							Animator* anim = (Animator*)obs->AddComponent(new Animator);

							anim->anims.emplace_back("Idle", std::vector<Animation::Frame>({
							Animation::Frame(sf::IntRect(textureRect.left, textureRect.top, Flags::BlockSizePixels, Flags::BlockSizePixels),0.15f),
							Animation::Frame(sf::IntRect(textureRect.left + Flags::BlockSizePixels, textureRect.top, Flags::BlockSizePixels, Flags::BlockSizePixels),0.15f),
								}));
							anim->Play("Idle");

							if (specialEffectsMap.find(effectorMap.getPixel(x, y)) != specialEffectsMap.end())
								specialEffectsMap[effectorMap.getPixel(x, y)]->Shooters.push_back((Laser1Obstacle*)on);


							Object* obs1 = GetScene()->CreateObject(spriteSheet);
							obs1->Layer = b3;
							obs1->me.setScale(Flags::BlockScale, Flags::BlockScale);
							obs1->me.setPosition(x* Flags::BlockScale* Flags::BlockSizePixels, y* Flags::BlockSizePixels* Flags::BlockScale);

							obs1->me.setTextureRect(sf::IntRect(Flags::BaseBackgroundBlock.x* Flags::BlockSizePixels, Flags::BaseBackgroundBlock.y* Flags::BlockSizePixels, Flags::BlockSizePixels, Flags::BlockSizePixels));



						}
					}

					for (sf::Vector2i& pos : Flags::LaserRayBlockPositions) // Laser do zmiany pozycji, ten morduje
					{
						if (pos.x == textureRect.left / Flags::BlockSizePixels && pos.y == textureRect.top / Flags::BlockSizePixels)
						{
							nocoll = true;

							on = static_cast<Obstacle*>(obs->AddComponent(new LaserObstacle()));
							Animator* anim = (Animator*)obs->AddComponent(new Animator);

							anim->anims.emplace_back("Idle", std::vector<Animation::Frame>({
							Animation::Frame(sf::IntRect(textureRect.left, textureRect.top, Flags::BlockSizePixels, Flags::BlockSizePixels),0.15f),
							Animation::Frame(sf::IntRect(textureRect.left + Flags::BlockSizePixels, textureRect.top, Flags::BlockSizePixels, Flags::BlockSizePixels),0.15f),
								}));
							anim->Play("Idle");

							Object* obs1 = GetScene()->CreateObject(spriteSheet);
							obs1->Layer = b3;
							obs1->me.setScale(Flags::BlockScale, Flags::BlockScale);
							obs1->me.setPosition(x* Flags::BlockScale* Flags::BlockSizePixels, y* Flags::BlockSizePixels* Flags::BlockScale);

							obs1->me.setTextureRect(sf::IntRect(Flags::BaseBackgroundBlock.x * Flags::BlockSizePixels, Flags::BaseBackgroundBlock.y* Flags::BlockSizePixels, Flags::BlockSizePixels, Flags::BlockSizePixels));

							if (specialEffectsMap.find(effectorMap.getPixel(x, y)) != specialEffectsMap.end())
								specialEffectsMap[effectorMap.getPixel(x, y)]->Rays.push_back((LaserObstacle*)on);


						}
					}

					for (sf::Vector2i& pos : Flags::NoCollideBlockPositions) 
					{
						if (pos.x == textureRect.left / Flags::BlockSizePixels && pos.y == textureRect.top / Flags::BlockSizePixels)
						{
							nocoll = true;
						}
					}
					
					for (sf::Vector2i& pos : Flags::ButtonBlockPositions)
					{
						if (pos.x == textureRect.left / Flags::BlockSizePixels && pos.y == textureRect.top / Flags::BlockSizePixels)
						{
							if(obs)
								obs->KillMePlease = true;
							
							obs = nullptr;
							nocoll = true;
						}
					}

					
					if (!nocoll)
					{
						on = static_cast<Obstacle*>(obs->AddComponent(new Obstacle()));
					}

					if (on) obstacles.emplace_back(on);
				}
			}
		}

		return obstacles;
	}


};

class CatMove : public Component
{
public:
	Animator* anim;

	std::vector<Obstacle*> obstacles;

	enum CatState
	{
		Standing,
		Running,
		Slowing,
		PrepJump,
		Jumping,
		Falling
	};

	CatState catState;
	bool inverseDirection=false;

	sf::Vector2f velocity;

	float speed = 300;
	float maxSpeed = 300;
	float accTime = 0.3f;
	float deccTime = 0.3f;
	float jumpForce = 0;
	float maxJumpForce = 800;
	float jumpForceSpeed = 1.1f;
	float gravity = 1000;

	CatMove()
	{
		UpdateVariables();
	}

	void UpdateVariables()
	{
		speed = Flags::catSpeed;
		maxSpeed = Flags::catMaxSpeed;
		accTime = Flags::catAccTime;
		deccTime = Flags::catDeccTime;
		maxJumpForce = Flags::catMaxJumpForce;
		jumpForceSpeed = Flags::catJumpForceSpeed;
		gravity = Flags::catGravity;
	}

	void InitAnimations()
	{
		anim->anims.emplace_back("Empty", std::vector<Animation::Frame>({}));
		anim->anims.emplace_back("IdleR", std::vector<Animation::Frame>({
			Animation::Frame(sf::IntRect(0 * 64,0 * 32, 64, 32),0.15f)
			}));
		anim->anims.emplace_back("IdleL", std::vector<Animation::Frame>({
			Animation::Frame(sf::IntRect(1 * 64,0 * 32, 64, 32),0.15f)
			}));

		anim->anims.emplace_back("RunRight", std::vector<Animation::Frame>({
			Animation::Frame(sf::IntRect(0 * 64,1 * 32, 64, 32),0.15f),
			Animation::Frame(sf::IntRect(0 * 64,2 * 32, 64, 32),0.15f),
			}));

		anim->anims.emplace_back("SlowRight", std::vector<Animation::Frame>({
			Animation::Frame(sf::IntRect(0 * 64,3 * 32, 64, 32),0.15f)
			}));

		anim->anims.emplace_back("PrepRight", std::vector<Animation::Frame>({
			Animation::Frame(sf::IntRect(0 * 64,6 * 32, 64, 32),0.15f),
			Animation::Frame(sf::IntRect(0 * 64,7 * 32, 64, 32),0.15f),
			}));

		anim->anims.emplace_back("JumpRight", std::vector<Animation::Frame>({
			Animation::Frame(sf::IntRect(0 * 64,4 * 32, 64, 32),0.15f)
			}));

		anim->anims.emplace_back("FallRight", std::vector<Animation::Frame>({
			Animation::Frame(sf::IntRect(0 * 64,5 * 32, 64, 32),0.15f)
			}));
	


		anim->anims.emplace_back("RunLeft", std::vector<Animation::Frame>({
			Animation::Frame(sf::IntRect(1 * 64,1 * 32, 64, 32),0.15f),
			Animation::Frame(sf::IntRect(1 * 64,2 * 32, 64, 32),0.15f)

			}));

		anim->anims.emplace_back("SlowLeft", std::vector<Animation::Frame>({
			Animation::Frame(sf::IntRect(1 * 64,3 * 32, 64, 32),0.15f)
			}));

		anim->anims.emplace_back("PrepLeft", std::vector<Animation::Frame>({
			Animation::Frame(sf::IntRect(1 * 64,6 * 32, 64, 32),0.15f),
			Animation::Frame(sf::IntRect(1 * 64,7 * 32, 64, 32),0.15f),
			}));

		anim->anims.emplace_back("JumpLeft", std::vector<Animation::Frame>({
			Animation::Frame(sf::IntRect(1 * 64,4 * 32, 64, 32),0.15f)
			}));

		anim->anims.emplace_back("FallLeft", std::vector<Animation::Frame>({
			Animation::Frame(sf::IntRect(1 * 64,5 * 32, 64, 32),0.15f)
			}));


	
	
	}

	void PlayAnim(std::string name)
	{
		anim->Play(name);
	}

	void HandleAnimation()
	{
		switch (catState)
		{
		case CatMove::Standing:
			if (inverseDirection) PlayAnim("IdleL");
			else PlayAnim("IdleR");
			break;
		case CatMove::Running:
			if (inverseDirection) PlayAnim("RunLeft");
			else PlayAnim("RunRight");

			break;
		case CatMove::Slowing:
			if (inverseDirection) PlayAnim("SlowLeft");
			else PlayAnim("SlowRight");

			break;
		case CatMove::PrepJump:
			if (inverseDirection) PlayAnim("PrepLeft");
			else PlayAnim("PrepRight");

			break;
		case CatMove::Jumping:
			if (inverseDirection) PlayAnim("JumpLeft");
			else PlayAnim("JumpRight");

			break;
		case CatMove::Falling:
			if (inverseDirection) PlayAnim("FallLeft");
			else PlayAnim("FallRight");

			break;
		default:
			break;
		}
	}

	void Camera()
	{



		sf::View v = window.getDefaultView();

		v.setCenter(Holder->me.getPosition().x + 200, Holder->me.getPosition().y);

		if (v.getCenter().x < window.getDefaultView().getCenter().x)
		{
			v.setCenter(window.getDefaultView().getCenter().x, Holder->me.getPosition().y);

		}
		else
		{
			sf::Vector2f temp = v.getCenter();
			temp.x = (int)temp.x;
			temp.y = (int)temp.y;

			v.setCenter(temp);
		}

		window.setView(v);
	}

	void DoDirections()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			inverseDirection = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			inverseDirection = false;
		}
	}
	void AddMomentum()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			velocity.x -= speed * (dt / accTime);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			velocity.x += speed * (dt / accTime);
		}

		if (velocity.x > maxSpeed)
			velocity.x = maxSpeed;

		if (velocity.x < -maxSpeed)
			velocity.x = -maxSpeed;

	}
	void Deccelarate(bool force = false)
	{
		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || force)
		{
			if (velocity.x > 0)
			{
				velocity.x -= speed * (dt / deccTime);

				if (velocity.x < 1.0f)
					velocity.x = 0;
			}

			if (velocity.x < 0)
			{
				velocity.x += speed * (dt / deccTime);
				if (velocity.x > -1.0f)
					velocity.x = 0;
			}
		}
	}
	void PowerTheJump()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			jumpForce += maxJumpForce * (dt / jumpForceSpeed);

			if (jumpForce > maxJumpForce)
				jumpForce = maxJumpForce;
		}
	}
	void ApplyGravity()
	{
		velocity.y += (dt * gravity);
	}
	bool OnGround()
	{
		return false;
	}
	bool reverseMove()
	{
		sf::FloatRect col = Holder->me.getGlobalBounds();
		col.width -= 32;
		col.left += 16;
		col.height -= 28;
		col.top += 28;

#ifdef ShowColliders
		ColliderRects.push_back(col);
#endif // ShowColliders

		for (Obstacle*& obs : obstacles)
		{
			if (obs->collider.intersects(col))
			{
				obs->Collide();
				return true;
			}
		}

		if (Holder->me.getPosition().x < 0)
			return true;
		return false;
	}
	
	void Update()
	{
#ifdef MapLoaderOn
		return;
#endif

		if (Flags::Stop)
			return;

		switch (catState)
		{
		case CatMove::Standing:
			DoDirections();
			AddMomentum();
			PowerTheJump();
			Deccelarate();
			ApplyGravity();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				catState = PrepJump;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				catState = Running;

			if (velocity.y >= 100)
				catState = Falling;

			break;
		case CatMove::Running:
			DoDirections();
			AddMomentum();
			Deccelarate();
			PowerTheJump();
			ApplyGravity();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				catState = PrepJump;
			}

			if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
				catState = Slowing;

			if (velocity.y >= 100)
				catState = Falling;

			break;
		case CatMove::Slowing:
			DoDirections();
			AddMomentum();
			Deccelarate();
			PowerTheJump();
			ApplyGravity();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				catState = PrepJump;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				catState = Running;

			if (velocity.x == 0)
				catState = Standing;

			if (velocity.y >= 100)
				catState = Falling;


			break;
		case CatMove::PrepJump:
			DoDirections();
			PowerTheJump();
			Deccelarate(true);
			ApplyGravity();


			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				catState = Jumping;
				velocity.y = -jumpForce;
				jumpForce = 0;
			}

			if (velocity.y >= 100)
				catState = Falling;

			break;
		case CatMove::Jumping:
			DoDirections();
			Deccelarate();
			AddMomentum();
			ApplyGravity();


			if (velocity.y >= 0)
				catState = Falling;


			break;
		case CatMove::Falling:
			DoDirections();
			Deccelarate();
			AddMomentum();
			ApplyGravity();

			if (OnGround())
			{
				velocity.y = 0;
				catState = Standing;

			}

			break;
		default:
			break;
		}

		bool dd = false;
		
		Holder->me.move(velocity * dt);

		if (reverseMove())
		{
			Holder->me.move(0, -velocity.y * dt);
			dd = true;
		}
			

		if (reverseMove())
			Holder->me.move(-velocity.x * dt, velocity.y * dt);
		else if (dd)
		{
			if (catState == Falling)
			{
				if (std::abs(velocity.x) < 4)
					catState = Standing;
				else
					catState = Running;

			}
			velocity.y = 0;

		}

		if (reverseMove())
		{
			Holder->me.move(0, -velocity.y * dt);
			if (catState == Falling)
			{
				if (std::abs(velocity.x) < 4)
					catState = Standing;
				else
				{
					catState = Running;
				}
			}
			velocity.y = 0;
			
		}

		HandleAnimation();
		Camera();


		
	}

};