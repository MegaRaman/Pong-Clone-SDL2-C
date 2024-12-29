#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "pong_primitives.h"
#include "pong_logic.h"

static const char* window_name = "Pong Game";

int main() {
	srand(time(NULL));
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	SDL_Window *window = \
		SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
	SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	bool simulation_running = true;
	bool ball_out = true;
	bool game_over = false;
	int side = 1;

	struct Paddle p_l;
	struct Paddle p_r;
	struct Ball ball;
	struct Players player_scores = { 0 };

	TTF_Font *font = TTF_OpenFont("Nasa21.ttf", 40);

	while (simulation_running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					simulation_running = false;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_UP:
							p_r.vy = -PADDLE_STEP;
							break;
						case SDLK_DOWN:
							p_r.vy = PADDLE_STEP;
							break;
						case SDLK_w:
							p_l.vy = -PADDLE_STEP;
							break;
						case SDLK_s:
							p_l.vy = PADDLE_STEP;
							break;
						case SDLK_SPACE:
							if (game_over) {
								ball_out = true;
								game_over = false;
								side = 1;
								player_scores.left_score = player_scores.right_score = 0;
							}
							break;
					}
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym) {
						case SDLK_UP:
						case SDLK_DOWN:
							p_r.vy = 0;
							break;
						case SDLK_w:
						case SDLK_s:
							p_l.vy = 0;
							break;
					}
					break;
			}
		}
		if (game_over)
			continue;
		/* Set background to black */
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);

		/* Draw separating lines */
		if (ball_out) {
			start_ball(&ball, side);
			start_paddles(&p_l, &p_r);
			ball_out = false;
			side = -side;
			if (player_scores.left_score == SCORE_MAX || player_scores.right_score == SCORE_MAX) {
				game_over = true;
				draw_game_over_screen(ren, font, &player_scores);
			}
			SDL_Delay(200);
		}
		step(ren, &ball, &ball_out, &p_l, &p_r, &player_scores);
		draw_field(ren);
		draw_ball(ren, &ball);
		draw_paddles(ren, &p_l, &p_r);
		draw_score(ren, font, &player_scores);

		SDL_RenderPresent(ren);

		SDL_Delay(6); /* For little less than 60 Hz refresh rate */
	}
	return 0;
}

