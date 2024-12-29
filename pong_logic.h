#ifndef __PONG_LOGIC__
#define __PONG_LOGIC__

#include "pong_primitives.h"
#include <SDL2/SDL_ttf.h>


void start_ball(struct Ball *ball, int side);
void start_paddles(struct Paddle *p_l, struct Paddle *p_r);
void ball_collision(struct Ball *ball, float side_x, float side_y);
void step(SDL_Renderer *renderer, struct Ball *ball, bool *ball_out,
		struct Paddle *p_l, struct Paddle *p_r, struct Players *player_scores);

#endif // __PONG_LOGIC__
