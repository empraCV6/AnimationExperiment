#include"PlayerClass.hpp"


Player::Player(Gamesystem* Gsystem) : PlayerAnim(4,4),sys(Gsystem){
	WalkACCELLATE = 2;
	WalkMAXSPEED = 4;
	WalkFRICTION = 6;
	JumpMAXSPEED = 2;
	FallACCELLATE = 4;
	PlayerDirection = 0;

	movestate = stay;
	airstate = ground;
	JumpStart = false;
	JumpNow = false;
	PlayerPosition = { 0.f,200.f };
	PlayerSPEED = { 0.f,0.f };
	Playersp.setOrigin(16,0);

	Context.Rects.push_back({ 0, 0, 32, 32 });
	Context.Rects.push_back({ 32, 0, 32, 32 });
	Context.Rects.push_back({ 0, 32, 32, 32 });
	Context.Rects.push_back({ 32, 32, 32, 32 });

	Tex[0].loadFromFile("Playerwalk.png");
	Tex[1].loadFromFile("Playerstay.png");
	Tex[2].loadFromFile("Playerjump.png");
	Tex[3].loadFromFile("Playerfall.png");
}
void Player::stateupdate(float dt) {
	//State1で横移動の状態、
	switch (movestate) {
	case stay:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            movestate = walk;
			PlayerDirection = -1;
			break;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			movestate = walk;
			PlayerDirection = 1;
			break;
		}
			break;
	case walk:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		break;
			movestate= stay;
			break;
	}
	//State2で縦移動の状態
	switch (airstate) {
	case ground:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && !JumpNow)
		{
			airstate = jump;
			JumpNow = true;
			JumpStart = true;
		}
		break;
	case jump:
		if (PlayerSPEED.y > 0)
			airstate = fall;
		break;
	case fall:
		if (!JumpNow) {
			airstate = ground;
		}
		break;
	}
}

void Player::Positionupdate(float dt) {
	//横座標更新
	if (movestate == walk) {
		//歩き処理
		if (PlayerSPEED.x + WalkACCELLATE * dt < WalkMAXSPEED) {
			PlayerSPEED.x += WalkACCELLATE * dt * PlayerDirection;
		}
		else {
			PlayerSPEED.x = WalkMAXSPEED * PlayerDirection;
		}

	}
	//速度減少
	else {
		float SPEED = PlayerSPEED.x - WalkFRICTION * dt * PlayerDirection;
		if (SPEED < -1.0f || SPEED > 1.0f ) {
			PlayerSPEED.x -= WalkFRICTION * dt * PlayerDirection;
		}
		else {
			PlayerSPEED.x = 0;
		}
	}
	//縦座標更新
	switch (airstate) {
	case ground:
		break;
	case jump:
		if (JumpStart) {
			PlayerSPEED.y = -JumpMAXSPEED;
			JumpStart = false;
		}
		PlayerSPEED.y += FallACCELLATE * dt;
		break;
	case fall:
		if (PlayerPosition.y >= 200) {
			PlayerSPEED.y = 0;
			JumpStart = true;
			JumpNow = false;
			//床の判定を考慮せず、ひとまず床座標を５００へ
		}
		else {
			PlayerSPEED.y += FallACCELLATE * dt;
		}
    }
	PlayerPosition += PlayerSPEED;
	Playersp.setPosition(PlayerPosition);

}

void Player::draw(sf::RenderWindow* window) {
	Playersp.setTextureRect(Context.Rects[PlayerAnim.FrameNumber]);
	switch (PlayerDirection) {
	case 1:
		Playersp.setScale(1, 1);
		break;
	case -1:
		Playersp.setScale(-1, 1);
		break;
	}
	switch (movestate) {
	case walk:
		Playersp.setTexture(Tex[0]);
		break;
	case stay:
		Playersp.setTexture(Tex[1]);
	}
	switch (airstate) {
	case jump:
		Playersp.setTexture(Tex[2]);
		break;
	case fall:
		Playersp.setTexture(Tex[3]);
		break;
	}
	sys->canvas.clear(sf::Color::Green);
	sys->canvas.draw(Playersp);
	sys->canvas.display();
	sf::Sprite canvassp(sys->canvas.getTexture());
	canvassp.setPosition(0.f, 0.f);
	window->draw(canvassp);
	window->display();
}