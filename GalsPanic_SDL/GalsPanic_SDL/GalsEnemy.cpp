#include "GalsEnemy.h"


GalsEnemy::GalsEnemy(GalsMap& map) : map_{ &map }
{
	location_.x = 0.5f;
	location_.y = 0.5f;
	size_rate_ = 0.1f;
	size_ = 0.1f;

	rect_.x = (location_.x-size_rate_/2) * SDL_Game::window_rect.w;
	rect_.y = (location_.y-size_rate_/2) * SDL_Game::window_rect.h;
	rect_.w = size_ * SDL_Game::window_rect.w;
	rect_.h = size_ * SDL_Game::window_rect.h;

	srand(time(NULL));
}

void GalsEnemy::Update()
{
	static int move_count = 0;
	constexpr float max_char = 256.0f;
	static float hypotenuse = 0;


	if (map_->get_polygon_size() > map_->goal_size_)
	{
		if (move_count == 0)
		{
			move_count = SDL_GetTicks() % (SDL_Game::FPS) + 10;

			int ran_val = rand();

			old_direction.x = (float)(ran_val % (int)max_char) / max_char - 0.5f;
			old_direction.y = (float)((ran_val / (int)max_char) << 1) / max_char - 0.5f;

			old_direction.x += (map_->player_->location_.x - location_.x);
			old_direction.y += (map_->player_->location_.y - location_.y);

			hypotenuse = hypotf(old_direction.x, old_direction.y);
		}


		floatXY new_location;
		new_location.x = location_.x + old_direction.x*speed_;
		new_location.y = location_.y + old_direction.y*speed_;


		floatXY radian_location;
		radian_location.x = location_.x + old_direction.x*speed_ + old_direction.x / hypotenuse * size_rate_;
		radian_location.y = location_.x + old_direction.y*speed_ + old_direction.y / hypotenuse * size_rate_;

		if (map_->CollWithPolygon(location_, new_location).x != -1
			/*|| map_->CollWithFootprint(location_, new_location).x != -1*/)
		{
			move_count = 0;
		}
		else
		{
			if (map_->CollWithFootprint(location_, new_location).x != -1)
				map_->player_->MoveModeChange(1);

			location_ = new_location;
			--move_count;
		}
	}
	else
	{
		static int dead_count = SDL_Game::FPS * 5;

		if (dead_count < 0)
		{
			died_ = 1;
		}
		else
		{
			location_.x += (dead_count % 4 > 1 ? -1 : 1)* 0.005;

			--dead_count;
		}
	}
}

void GalsEnemy::Draw()
{
	rect_.x = (location_.x-size_/2) * SDL_Game::window_rect.w;
	rect_.y = (location_.y-size_/2) * SDL_Game::window_rect.h;
	rect_.w = size_ * SDL_Game::window_rect.w;
	rect_.h = size_ * SDL_Game::window_rect.h;


	SDL_SetRenderDrawColor(SDL_Game::renderer, 200, 0, 0, 255);
	SDL_RenderFillRect(SDL_Game::renderer, &rect_);
}
