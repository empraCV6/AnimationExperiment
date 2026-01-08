#pragma once
#include<SFML/Graphics.hpp>
#include"Gamecontext.hpp"
#include"Animation.hpp"

class Player {
public:
	Player(Gamesystem* Gsystem);
	Playercontext Context;
	Gamesystem* sys;
	Animation PlayerAnim;
	void stateupdate(float dt);
	void Positionupdate(float dt);
	void draw(sf::RenderWindow* window);
	enum MoveState { stay, walk };
	enum AirState { ground, jump, fall };
	bool JumpStart;
	bool JumpNow;

	sf::Vector2f PlayerPosition;
	sf::Vector2f PlayerSPEED;

	sf::Texture Tex[4];
	sf::Sprite Playersp;
private:
	float WalkACCELLATE;
	float WalkMAXSPEED;
	float WalkFRICTION;
	int PlayerDirection;

	float JumpMAXSPEED;
	float FallACCELLATE;

	MoveState movestate;
	AirState airstate;
};
