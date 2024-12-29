#include "pong_primitives.h"

void draw_field(SDL_Renderer *renderer) {
	const int sep_height = WINDOW_HEIGHT / SIDES_SEP_CNT - SIDES_SEP_GAP_H;
	for (int i = 0; i < SIDES_SEP_CNT; i++) {
		SDL_Rect sep_rect = { WINDOW_WIDTH / 2, i * (sep_height + SIDES_SEP_GAP_H), SIDES_SEP_W, sep_height };
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &sep_rect);
	}
}

void draw_ball(SDL_Renderer *renderer, struct Ball *ball) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (int w = 0; w < ball->radius * 2; w++) {
		for (int h = 0; h < ball->radius * 2; h++) {
			int dx = ball->radius - w; // horizontal offset
			int dy = ball->radius - h; // vertical offset
			if ((dx*dx + dy*dy) < (ball->radius * ball->radius)) {
				SDL_RenderDrawPoint(renderer, ball->x + dx, ball->y + dy);
			}
		}
	}
}

void draw_paddles(SDL_Renderer *renderer, struct Paddle *p_l, struct Paddle *p_r) {
	SDL_Rect p_l_rect = { p_l->x, p_l->y, PADDLE_WIDTH, PADDLE_HEIGHT };
	SDL_Rect p_r_rect = { p_r->x, p_r->y, PADDLE_WIDTH, PADDLE_HEIGHT };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &p_l_rect);
	SDL_RenderFillRect(renderer, &p_r_rect);
}

void draw_score(SDL_Renderer *ren, TTF_Font *font, struct Players *player_scores) {
	char ltext[3];
	char rtext[3];
	snprintf(ltext, 3, "%d", player_scores->left_score);
	snprintf(rtext, 3, "%d", player_scores->right_score);
	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Surface *lsurf = TTF_RenderText_Solid(font, ltext, white);
	SDL_Surface *rsurf = TTF_RenderText_Solid(font, rtext, white);

	SDL_Texture *ltexture = SDL_CreateTextureFromSurface(ren, lsurf);
	SDL_Texture *rtexture = SDL_CreateTextureFromSurface(ren, rsurf);

	SDL_Rect dst = { PADDLE_PADDING, 0, SCORE_FONT_WIDTH, SCORE_FONT_HEIGHT };
	SDL_RenderCopy(ren, ltexture, NULL, &dst);
	dst.x = WINDOW_WIDTH - PADDLE_PADDING - SCORE_FONT_WIDTH;
	SDL_RenderCopy(ren, rtexture, NULL, &dst);
}

void draw_game_over_screen(SDL_Renderer *ren, TTF_Font *font, struct Players *player_scores) {
	char text[100];
	SDL_Rect dst = { 0, 0, 200, 50 };
	if (player_scores->left_score == SCORE_MAX) {
		dst.x = 6 * PADDLE_PADDING;
		dst.y = WINDOW_HEIGHT / 2 - 25;
		snprintf(text, 100, "Left won");
	}
	else {
		dst.x = WINDOW_WIDTH / 2 + 6 * PADDLE_PADDING;
		dst.y = WINDOW_HEIGHT / 2 - 25;
		snprintf(text, 100, "Right won");
	}

	SDL_Color white = { 255, 255, 255, 255 };
	SDL_Surface *surf = TTF_RenderText_Solid(font, text, white);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surf);
	SDL_RenderCopy(ren, texture, NULL, &dst);
}

