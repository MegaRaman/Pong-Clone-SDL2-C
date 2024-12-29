#ifndef __PONG_PRIMITIVES__
#define __PONG_PRIMITIVES__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH			(900)
#define WINDOW_HEIGHT			(600)

#define SIDES_SEP_CNT			(12)
#define SIDES_SEP_W				(20)
#define SIDES_SEP_GAP_H			(10)

#define BALL_RADIUS				(10)
#define BALL_INITIAL_DISTRIB	(40)
#define BALL_MIN_VX				(8)
#define BALL_VX_DISTRIB			(4)
#define BALL_MAX_INIT_VY		(2)

#define PADDLE_WIDTH			(20)
#define PADDLE_HEIGHT			(80)
#define PADDLE_PADDING			(20)
#define PADDLE_STEP				(6)

#define SCORE_FONT_WIDTH		(40)
#define SCORE_FONT_HEIGHT		(70)

#define SCORE_MAX				(10)

struct Ball {
	float x;
	float y;
	int radius;
	float vx;
	float vy;
};

struct Paddle {
	float x;
	float y;
	float vy;
};

struct Players {
	int left_score;
	int right_score;
};

void draw_field(SDL_Renderer *renderer);
void draw_ball(SDL_Renderer *renderer, struct Ball *ball);
void draw_paddles(SDL_Renderer *renderer, struct Paddle *p_l, struct Paddle *p_r);
void draw_score(SDL_Renderer *ren, TTF_Font *font, struct Players *player_scores);
void draw_game_over_screen(SDL_Renderer *ren, TTF_Font *font, struct Players *player_scores);

#endif // __PONG_PRIMITIVES__

