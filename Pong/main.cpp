#include "raylib.h"

struct Ball {
	float x, y;
	float speedX, speedY;
	float radius;

	Ball(float x, float y, float radius, float speedX, float speedY)
		:x(x), y(y), speedX(speedX), speedY(speedY), radius(radius){}

	void Draw() {
		DrawCircle((int)x, (int)y, radius, WHITE);
	}
};

struct Paddle {
	float x, y;
	float speed;
	float width, height;

	Paddle(float x, float y, float speed, float width, float height)
		:x(x), y(y), speed(speed), width(width), height(height){}

	Rectangle GetRec() {
		return Rectangle{ x - width / 2, y - height / 2, width, height };
	}

	void Draw(){
		DrawRectangleRec(GetRec(), WHITE);
	}
};

int main() {
	InitWindow(800, 600, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);

	Ball ball(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f, 5, 300, 300);
	//ball.x = GetScreenWidth() / 2.0f;
	//ball.y = GetScreenHeight() / 2.0f;
	//ball.radius = 5;
	//ball.speedX = 100;
	//ball.speedY = 300;

	Paddle leftPaddle(50, GetScreenHeight() / 2, 500, 10, 100);
	Paddle rightPaddle(GetScreenWidth() - 50, GetScreenHeight() / 2, 500, 10, 100);


	while (!WindowShouldClose()) {

		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();

		if (ball.y < 0) {
			ball.y = 0;
			ball.speedY *= -1;
		}

		if (ball.y > GetScreenHeight()) {
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}

		if (IsKeyDown(KEY_W)) {
			leftPaddle.y -= leftPaddle.speed * GetFrameTime();

		}

		if (IsKeyDown(KEY_S)) {
			leftPaddle.y += leftPaddle.speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_UP)) {
			rightPaddle.y -= rightPaddle.speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_DOWN)) {
			rightPaddle.y += rightPaddle.speed * GetFrameTime();
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.GetRec())) {
			if(ball.speedX < 0)
				ball.speedX *= -1.1f;
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.GetRec())) {
			if(ball.speedX > 0)
				ball.speedX *= -1.1f;
		}

		BeginDrawing();
			ClearBackground(BLACK);

			ball.Draw();
			leftPaddle.Draw();
			rightPaddle.Draw();

			DrawFPS(10, 10);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}