#include <stdlib.h>
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

	Paddle leftPaddle(50, GetScreenHeight() / 2, 750, 10, 100);
	Paddle rightPaddle(GetScreenWidth() - 50, GetScreenHeight() / 2, 750, 10, 100);


	const char* WinnerText = nullptr;

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

		if (IsKeyDown(KEY_W) && leftPaddle.y > leftPaddle.height / 2) {
			leftPaddle.y -= leftPaddle.speed * GetFrameTime();

		}

		if (IsKeyDown(KEY_S) && leftPaddle.y + leftPaddle.height / 2 < GetScreenHeight()) {
			leftPaddle.y += leftPaddle.speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_UP) && rightPaddle.y > rightPaddle.height / 2) {
			rightPaddle.y -= rightPaddle.speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_DOWN) && rightPaddle.y + rightPaddle.height / 2 < GetScreenHeight()) {
			rightPaddle.y += rightPaddle.speed * GetFrameTime();
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.GetRec())) {
			if (ball.speedX < 0) {
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX; //scaling ballspeedY with ballspeedX instead of a constant
			}
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.GetRec())) {
			if (ball.speedX > 0) {
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * - ball.speedX;
			}
		}

		if (ball.x < 0) {
			WinnerText = "Player B wins";
		}
		if (ball.x > GetScreenWidth()) {
			WinnerText = "Player A wins";
		}
		if (WinnerText && IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_R)) {
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;
			int rand1 = (rand() % 2) == 0 ? -1 : 1;
			int rand2 = (rand() % 2) == 0 ? -1 : 1;
			
			ball.speedX = 300 * rand1;
			ball.speedY = 300 * rand2;
			WinnerText = nullptr;
			leftPaddle.y = GetScreenHeight() / 2;
			rightPaddle.y = GetScreenHeight() / 2;
		}

		

		BeginDrawing();
			ClearBackground(BLACK);

			ball.Draw();
			leftPaddle.Draw();
			rightPaddle.Draw();

			if (WinnerText) {
				int textWidth = MeasureText(WinnerText, 60);
				DrawText(WinnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
			}

			DrawFPS(10, 10);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}