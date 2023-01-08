#include "Header1.h"
#include "Header.h"
using namespace sf;
int main()
{
	srand(time(nullptr));
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	window.setFramerateLimit(FPS);
	RectangleShape Bat;
	initBat(Bat, BatColor, BatStartPos);
	float BatSpeedX = 0.f;
	CircleShape ball;
	initBall(ball, BALL_COLOR, ballStartPos);

	float arr_speed[]{ -5.f,-4.f,-3.f,-2.f,-1.f,1.f,2.f,3.f,4.f,5.f };
	int index = rand() % 10;
	float ball_speedx = arr_speed[index];
	index = rand() % 10;
	float ball_speedy = arr_speed[index];
	int PlayerScore = 0;

	Font font;
	font.loadFromFile("arial.ttf");
	Text PlayerScoreText;
	initText(PlayerScoreText, PlayerScore, font, charSize, TextStartPos);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		ball.move(ball_speedx, ball_speedy);
		if (ball.getPosition().y <= 0)
		{
			ball_speedy = -ball_speedy;
		}
		if (ball.getPosition().y >= (WINDOW_HEIGHT - 2 * BALL_RADIUS))
		{
			window.close();
		}
		if (ball.getPosition().x <= 0 || ball.getPosition().x >=
			(WINDOW_WIDTH - 2 * BALL_RADIUS))
		{
			ball_speedx = -ball_speedx;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) { Bat.move(-5, 0); }
		if (Keyboard::isKeyPressed(Keyboard::Right)) { Bat.move(5, 0); }
		if (Bat.getPosition().x <= 0) {
			Bat.setPosition(0.f, WINDOW_HEIGHT - 2 * batHeight);
		}
		if (Bat.getPosition().x + batWidth >= WINDOW_WIDTH) {
			Bat.setPosition(WINDOW_WIDTH - batWidth, WINDOW_HEIGHT - 2 * batHeight);
		}
		Bat.move(0, BatSpeedX);
		BatSpeedX = 0;
		float ballX = ball.getPosition().x;
		float ballY = ball.getPosition().y;
		Vector2f midTop{ ballX + BALL_RADIUS,  ballY };
		Vector2f  mid{ ballX, ballY + BALL_RADIUS };
		Vector2f midBottom{ ballX + BALL_RADIUS,  ballY + 2 * BALL_RADIUS };
		if (pointInRect(Bat, mid)) {
			ball_speedx = -ball_speedx;
			PlayerScore++;
			PlayerScoreText.setString(std::to_string(PlayerScore));
		}
		if (pointInRect(Bat, midBottom)) {
			ball_speedy = -ball_speedy;
			PlayerScore++;
			PlayerScoreText.setString(std::to_string(PlayerScore));
		}
		if (pointInRect(Bat, midTop)) {
			ball_speedy = -ball_speedy;
			PlayerScore++;
			PlayerScoreText.setString(std::to_string(PlayerScore));
		}
		window.clear(sf::Color::Black);
		window.draw(Bat);
		window.draw(ball);
		window.draw(PlayerScoreText);
		window.display();
	}

	return 0;
}