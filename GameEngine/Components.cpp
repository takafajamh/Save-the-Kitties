#include "Components.hpp"
#include "Scenes.hpp"



void PlayButton::onClick()
{
	GetScene()->GetGame()->ChangeScene(new MainScene());

}
void QuitButton::onClick()
{
	window.close();
}

template <class T>
void LevelButton<T>::onClick()
{
	GetScene()->GetGame()->ChamgeScene(new T());
}


void LaserObstacle::Do() 
{
	Flags::DeathCounter[Flags::LevelCount]++;
	Holder->GetScene()->GetGame()->ChangeScene(new MainScene());
}
#ifdef MapLoaderOn
void MapLoader::Do()
{
	GetScene()->GetGame()->ChangeScene(new MainScene());
}
#endif // MapLoaderOn


void DeadObstacle::Do()
{
	Flags::DeathCounter[Flags::LevelCount]++;
	Holder->GetScene()->GetGame()->ChangeScene(new MainScene());
}
void MenuButton::onClick()
{
	Flags::LevelTime[Flags::LevelCount] = 0;
	GetScene()->GetGame()->ChangeScene(new Menu());
}
void SettingsButton::onClick()
{
	GetScene()->GetGame()->ChangeScene(new Settings());
}


void winObstacle::Do()
{
	Holder->GetScene()->GetGame()->ChangeScene(new MainScene());
}

void ChangeToMenu::Go()
{
	GetScene()->GetGame()->ChangeScene(new Menu());
}