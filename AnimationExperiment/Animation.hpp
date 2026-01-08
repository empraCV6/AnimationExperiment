#pragma once
#include"Gamecontext.hpp"
#include<vector>

class Animation {
public:
	Animation(int FPS,int MAXFrame);
	void updateAnimation(float dt,Playercontext* Rects);

	int MaxFramenumber;
	int FrameNumber;
private:
	float AnimationFPS;
	float AnimationTimer;
};
