#include"Animation.hpp"

Animation::Animation(int FPS,int MAXFrame) {
	FrameNumber = 0;
	AnimationFPS = 1.0f / FPS;
	AnimationTimer = 0.f;
	MaxFramenumber = MAXFrame;
}
void Animation::updateAnimation(float dt, Playercontext* Rects) {
	//初めにテクスチャ指定
	AnimationTimer += dt;
	if (AnimationTimer >= AnimationFPS) {
		if (FrameNumber + 1 < MaxFramenumber) {
			FrameNumber += 1;
		}
		else {
			FrameNumber = 0;
		}

	}
}