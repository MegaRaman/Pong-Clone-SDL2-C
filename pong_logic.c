#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdbool.h>
#include "pong_logic.h"
#include "pong_primitives.h"

static inline int get_random_int(int min, int max) {
	return rand() % (max + 1 - min) + min;
}

void start_ball(struct Ball *ball, int side) {
	int ball_y = get_random_int(WINDOW_HEIGHT / 2 - BALL_INITIAL_DISTRIB, WINDOW_HEIGHT / 2 + BALL_INITIAL_DISTRIB);
	int ball_vx = get_random_int(BALL_MIN_VX, BALL_MIN_VX + BALL_VX_DISTRIB);
	int ball_vy = get_random_int(-BALL_MAX_INIT_VY, BALL_MAX_INIT_VY);

	ball->x = WINDOW_WIDTH / 2.0;
	ball->y = ball_y;
	ball->radius = BALL_RADIUS;
	ball->vx = ball_vx * side;
	ball->vy = ball_vy;
}

void start_paddles(struct Paddle *p_l, struct Paddle *p_r) {
	p_l->x = PADDLE_PADDING;
	p_l->y = WINDOW_HEIGHT / 2.0 - PADDLE_HEIGHT / 2.0;

	p_r->x = WINDOW_WIDTH - PADDLE_WIDTH - PADDLE_PADDING;
	p_r->y = WINDOW_HEIGHT / 2.0 - PADDLE_HEIGHT / 2.0;

	p_l->vy = 0;
	p_r->vy = 0;
}

void handle_rpaddle(SDL_Renderer *renderer, struct Ball *ball, struct Paddle *p_r) {
	if (ball->x + ball->radius >= p_r->x && ball->x - ball->radius < WINDOW_WIDTH - PADDLE_PADDING) {
		if (ball->y + ball->radius >= p_r->y && ball->y + ball->radius < p_r->y + PADDLE_HEIGHT / 2.0) {
			// vy should be negative
			ball->vx = fabs(ball->vx) * -1;
			ball->vy = fabs(ball->vy) > 1 ? fabs(ball->vy) * -1: -1;
		}
		else if (ball->y - ball->radius < p_r->y + PADDLE_HEIGHT && ball->y - ball->radius > p_r->y + PADDLE_HEIGHT / 2.0) {
			// vy should be pos, if now too small get it to 1
			ball->vx = fabs(ball->vx) * -1;
			ball->vy = fabs(ball->vy) > 1 ? fabs(ball->vy): 1;
		}
		else if (ball->y + ball->radius > p_r->y && ball->y - ball->radius < p_r->y + PADDLE_HEIGHT) {
			// small random vy
			ball->vx = fabs(ball->vx) * -1;
			ball->vy = 0.3 * get_random_int(-1, 1);
		}
		else if (ball->y + ball->radius >= p_r->y && ball->y < p_r->y) {
			ball->vx = fabs(ball->vx) * -1;
			ball->vy = fabs(ball->vy) > 1 ? fabs(ball->vy) * -2: -2;
		}
		else if (ball->y - ball->radius <= p_r->y && ball->y > p_r->y) {
			ball->vx = fabs(ball->vx) * -1;
			ball->vy = fabs(ball->vy) > 2 ? fabs(ball->vy): 2;
		}
	}
}

void handle_lpaddle(SDL_Renderer *renderer, struct Ball *ball, struct Paddle *p_l) {
	if (ball->x - ball->radius <= p_l->x + PADDLE_WIDTH && ball->x + ball->radius > PADDLE_PADDING) {
		if (ball->y + ball->radius >= p_l->y && ball->y + ball->radius < p_l->y + PADDLE_HEIGHT / 2.0) {
			// vy should be negative
			ball->vx = fabs(ball->vx);
			ball->vy = fabs(ball->vy) > 1 ? fabs(ball->vy) * -1: -1;
		}
		else if (ball->y - ball->radius < p_l->y + PADDLE_HEIGHT && ball->y - ball->radius > p_l->y + PADDLE_HEIGHT / 2.0) {
			// vy should be pos, if now too small get it to 1
			ball->vx = fabs(ball->vx);
			ball->vy = fabs(ball->vy) > 1 ? fabs(ball->vy): 1;
		}
		else if (ball->y + ball->radius > p_l->y && ball->y - ball->radius < p_l->y + PADDLE_HEIGHT) {
			// small random vy
			ball->vx = fabs(ball->vx);
			ball->vy = 0.3 * get_random_int(-1, 1);
		}
		else if (ball->y + ball->radius >= p_l->y && ball->y < p_l->y) {
			ball->vx = fabs(ball->vx);
			ball->vy = fabs(ball->vy) > 1 ? fabs(ball->vy) * -2: -2;
		}
		else if (ball->y - ball->radius <= p_l->y && ball->y > p_l->y) {
			ball->vx = fabs(ball->vx);
			ball->vy = fabs(ball->vy) > 2 ? fabs(ball->vy): 2;
		}
	}
}

void step(SDL_Renderer *renderer, struct Ball *ball, bool *ball_out,
		struct Paddle *p_l, struct Paddle *p_r, struct Players *player_scores) {
	ball->x += ball->vx;
	ball->y += ball->vy;

	p_l->y += p_l->vy;
	p_r->y += p_r->vy;

	// collision with the right paddle
	// for right paddle you substract width, for left you add it
	handle_rpaddle(renderer, ball, p_r);
	handle_lpaddle(renderer, ball, p_l);

	// ball collision with the sides of the table
	if (ball->y + ball->radius >= WINDOW_HEIGHT || ball->y - ball->radius <= 0) {
		ball->vy = -ball->vy;
	}

	if (ball->x - ball->radius >= WINDOW_WIDTH ) {
		*ball_out = true;
		player_scores->left_score++;
	}
	else if (ball->x <= 0) {
		*ball_out = true;
		player_scores->right_score++;
	}

	if (p_r->y <= 0 || p_r->y + PADDLE_HEIGHT >= WINDOW_HEIGHT) {
		p_r->y -= p_r->vy;
		p_r->vy = 0;
	}

	if (p_l->y <= 0 || p_l->y + PADDLE_HEIGHT >= WINDOW_HEIGHT) {
		p_l->y -= p_l->vy;
		p_l->vy = 0;
	}

}


