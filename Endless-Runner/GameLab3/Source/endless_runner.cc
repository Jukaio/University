// endless_runner.cc

// Due to a lack of time, I was not able to clean up the code, structure it, make it prettier, yadda yadda
// Usually I would use polymorphism for most of the objects, but well, it works like that for this scope

#include "endless_runner.h"
#include "input_context.h"
#include "easing.h"

int window_width = 1280;
int window_height = 720;
float music_volume = 50.0f;
float sound_volume = 50.0f;
float screen_shake_strength = 1.0f;

void get_Settings(const char* file_path)
{
	FILE* stream;
	int width;
	int height;
	float volume;
	float sfx_volume;
	float shake_strength;

	if (fopen_s(&stream, file_path, "r") != 0)
		return;

	if (fscanf_s(stream, "%ld", &width) == 0)
		return;
	if (fscanf_s(stream, "%ld", &height) == 0)
		return;
	if (fscanf_s(stream, "%f", &volume) == 0)
		return;
	if (fscanf_s(stream, "%f", &sfx_volume) == 0)
		return;
	if (fscanf_s(stream, "%f", &shake_strength) == 0)
		return;
	fclose(stream);

	window_width = width;
	window_height = height;
	music_volume = volume;
	sound_volume = sfx_volume;
	screen_shake_strength = shake_strength;
}

constexpr uint32_t EXIT_CODE  = 0xFFFF;
constexpr uint32_t JUMP_CODE = 0xFFF1;
constexpr uint32_t PAUSE_CODE = 0xFFF3;

template <typename T> T min(T a, T b) { return a < b ? a : b; }

static float get_deltatime(sf::Clock &clock)
{
   sf::Time diff = clock.restart();
   float dt = min(diff.asSeconds(), 1.0f / 60.0f);
   return dt;
}

endless_runner::endless_runner()
   : current_state_(GAME_STATE_LOAD)
   , input_manager_(window_)
{
	
}

void endless_runner::create_Game() // "Re-init" - Basically restarts the game
{
	//--------------------//
	const sf::Texture* resource_Deep_Layer = new sf::Texture;
	texture_cache_.get("assets/sunny-land-files/environment/back.png", &resource_Deep_Layer);
	sf::Vector2i temp_deep_pos(0, 0);
	sf::Vector2i temp_deep_size(resource_Deep_Layer->getSize());
	sf::IntRect rect_deep(temp_deep_pos, temp_deep_size);
	parallax_Deep_Layer_ = new Parallax(resource_Deep_Layer, 3, 50, 0, 0, rect_deep, window_width);
	//--------------------//

	const sf::Texture* resource_Middle_Layer;
	texture_cache_.get("assets/sunny-land-files/environment/middle.png", &resource_Middle_Layer);
	sf::Vector2i temp_middle_pos(0, 0);
	sf::Vector2i temp_middle_size(resource_Middle_Layer->getSize());
	sf::IntRect rect_middle(temp_middle_pos, temp_middle_size);
	parallax_Middle_Layer_ = new Parallax(resource_Middle_Layer, 1.0f, 125, 0, resource_Middle_Layer->getSize().y * 1.0f, rect_middle, window_width);
	//--------------------//

	const sf::Texture* resource_Front_Layer;
	texture_cache_.get("assets/sunny-land-files/environment/tileset.png", &resource_Front_Layer);
	sf::Vector2i temp_front_pos(48, 16);
	sf::Vector2i temp_front_size(16, 16);
	sf::IntRect rect_front(temp_front_pos, temp_front_size);
	parallax_Front_Layer_ = new Parallax(resource_Front_Layer, 8.0f, 250, 0, 720 - 100, rect_front, window_width);
	//-------------------//

	const sf::Texture* resource_obstacles;
	texture_cache_.get("assets/sunny-land-files/environment/props.png", &resource_obstacles);
	sf::Vector2i temp_obst_pos(16, 176);
	sf::Vector2i temp_obst_size(32, 32);
	sf::IntRect rect_obst(temp_obst_pos, temp_obst_size);


	const sf::Texture* resource_Pretty_Stuff;
	texture_cache_.get("assets/sunny-land-files/environment/props.png", &resource_Pretty_Stuff);
	sf::Vector2i temp_pretty_pos(120, 34);
	sf::Vector2i temp_pretty_size(106, 94);
	sf::IntRect rect_pretty(temp_pretty_pos, temp_pretty_size);
	parallax_Pretty_Stuff_ = new Parallax(resource_Pretty_Stuff, 4.0f, 200, 250, 720 - 476, rect_pretty, window_width);


	for (int i = 0; i < 3; i++)
	{
		obstacles_[i].setTexture(*resource_obstacles);
		obstacles_[i].setTextureRect(rect_obst);
		obstacles_[i].setScale(2.0f, 2.0f);
		obstacles_[i].setPosition((float)((i + 1) * rect_obst.width) + ((i + 2) * 720), 720 - 100 - (32 * 2));
	}

	//-------------------//
	player_ = new Player();
	player_->load("assets/animation/player_run.txt", texture_cache_);
	player_->load("assets/animation/player_jump.txt", texture_cache_);
	player_->load("assets/animation/player_hurt.txt", texture_cache_);
	player_->set_Animation(0);


	gem_ = new Object();
	gem_->load("assets/animation/diamond.txt", texture_cache_);
	gem_->position_ = sf::Vector2f(1280.0f, 400.0f);

	const sf::SoundBuffer* buffer_Jump;
	const sf::SoundBuffer* buffer_Death;
	const sf::SoundBuffer* buffer_Boing;
	sound_buffer_cache_.get("assets/DEATH.wav", &buffer_Death);
	sound_buffer_cache_.get("assets/JUMP.wav", &buffer_Jump);
	sound_buffer_cache_.get("assets/BOING.wav", &buffer_Boing);

	sound_Death_.setBuffer(*buffer_Death);
	sound_Death_.setVolume(sound_volume);
	sound_Jump_.setBuffer(*buffer_Jump);
	sound_Jump_.setVolume(sound_volume);
	sound_Boing_.setBuffer(*buffer_Boing);
	sound_Boing_.setVolume(sound_volume);

	background_Music_.openFromFile("assets/specialsong.wav");
	background_Music_.setLoop(true);
	background_Music_.setVolume(music_volume);
	background_Music_.play();

	const sf::Font* font;
	font_cache_.get("assets/Arial.ttf", &font);

	highscore_.setFont(*font);
	highscore_.setCharacterSize(24);
	highscore_.setString("HIGHSCORE:");
	highscore_.setPosition(15.0f, 15.0f);
	highscore_.setFillColor(sf::Color::Black);
	highscore_.setStyle(sf::Text::Bold);

	menu_Text_.setFont(*font);
	explosion_frame_ = 0;
	screenshake_duration = 1.0f;
	current_state_ = GAME_STATE_MENU;
	score_ = 0.0f;
}

//Collision function
bool intersect(const sf::Sprite lhs, const sf::Sprite& rhs, float x_offset, float y_offset) //ANCHOR IS TOP LEFT
{
	if (lhs.getPosition().x + (lhs.getTextureRect().width * lhs.getScale().x) >= rhs.getPosition().x  + x_offset && //i do not consider right and bottom cause I do not have to consider them
		lhs.getPosition().x <= rhs.getPosition().x + (rhs.getTextureRect().width * rhs.getScale().x) - x_offset &&
		lhs.getPosition().y + (lhs.getTextureRect().height * lhs.getScale().y) >= rhs.getPosition().y + y_offset &&
		lhs.getPosition().y <= rhs.getPosition().y + (rhs.getTextureRect().height * rhs.getScale().y - y_offset))
		return true;

	return false;
}

bool endless_runner::init()
{
	get_Settings("assets/settings.txt");
   // note: create a non-resizable window 
   window_.create(sf::VideoMode(window_width, window_height), 
                  "endless-runner", 
                  sf::Style::Titlebar|sf::Style::Close);

   // note: disable key repeats
   window_.setKeyRepeatEnabled(false);

   // note: enable vertical sync
   window_.setVerticalSyncEnabled(true);

   // note: base input context for global game
   auto context = input_manager_.create_context("base");

   // note: bind an action to the newly created input context
   //       when we press escape we will set the current 
   //       state to be GAME_STATE_QUIT which makes the 
   //       game exit
   context->bind_action(sf::Keyboard::Escape, EXIT_CODE);
   context->bind_action(sf::Keyboard::Space, JUMP_CODE);
   context->bind_action(sf::Keyboard::P, PAUSE_CODE);

   // note: push base context to input stack
   input_manager_.push_context("base");

   // note: register 'this' to receive input
   input_manager_.attach_listener(this);

   // note: preload textures
   texture_cache_.load("assets/sunny-land-files/environment/back.png");
   texture_cache_.load("assets/sunny-land-files/environment/middle.png");
   texture_cache_.load("assets/sunny-land-files/environment/tileset.png");
   texture_cache_.load("assets/sunny-land-files/environment/props.png");
   texture_cache_.load("assets/sunny-land-files/spritesheets/gem.png");
   texture_cache_.load("assets/sunny-land-files/spritesheets/enemy-deadth.png");
   texture_cache_.get("assets/sunny-land-files/spritesheets/enemy-deadth.png", &explosion_);

   // note: preload sound buffers
   sound_buffer_cache_.load("assets/DEATH.wav");
   sound_buffer_cache_.load("assets/JUMP.wav");
   sound_buffer_cache_.load("assets/BOING.wav");

   // note: preload fonts
   font_cache_.load("assets/Arial.ttf");

   create_Game();

   return true;
}

void endless_runner::run()
{
   sf::Clock clock;
   while (window_.isOpen())
   {
	   // note: calculate delta time
	   float deltatime = get_deltatime(clock);
	   // note: currently we have a simple 
	   if (current_state_ == GAME_STATE_QUIT)
		   break;

	   // note: the input manager handles the polling of 
	   //       all sf::Events and dispatching the changes
	   //       in input actions and states to all listeners

	   if (!input_manager_.process())
		   break;

	   view.setCenter(window_width / 2.0f, window_height / 2.0f);
	   view.setSize((float) window_width, (float) window_height);

	   if (current_state_ == GAME_STATE_MENU)
	   {
		   auto text_Ease_Function = getEasingFunction(EaseInSine);
		   double ease = text_Ease_Function(menu_easing_t_);

		   view.setRotation(-(view.getRotation()) * (float)ease);
		   menu_Text_.setFillColor(sf::Color::Black);
		   menu_Text_.setStyle(sf::Text::Bold);
		   menu_Text_.setString("WELCOME! PRESS SPACE TO BEGIN!");
		   menu_Text_.setCharacterSize((int)(64 * ease));
		   sf::FloatRect textRect = menu_Text_.getLocalBounds();

		   menu_Text_.setOrigin(textRect.left + textRect.width / 2.0f,
								textRect.top + textRect.height / 2.0f);
		   menu_Text_.setPosition(sf::Vector2f(window_width / 2.0f, window_height / 4.0f));
		   menu_Text_.setOutlineThickness(1.0f);
		   menu_easing_t_ += deltatime * 2.0f;

		   if (menu_easing_t_ > 1.0f)
			   menu_easing_t_ = 1.0f;

		   parallax_Deep_Layer_->Update(deltatime);
		   parallax_Middle_Layer_->Update(deltatime);
		   parallax_Front_Layer_->Update(deltatime);
		   parallax_Pretty_Stuff_->Update(deltatime);

		   window_.setView(view);
		   window_.clear();

		   parallax_Deep_Layer_->Draw(window_);
		   parallax_Middle_Layer_->Draw(window_);
		   parallax_Pretty_Stuff_->Draw(window_);
		   parallax_Front_Layer_->Draw(window_);
		   window_.draw(menu_Text_);

		   window_.display();
	   }

	   if (current_state_ == GAME_STATE_PAUSE)
	   {
		   score_ += deltatime * 10;
		   std::string temp = "Score: " + std::to_string((int)score_);
		   highscore_.setString(temp);

		   auto text_Ease_Function = getEasingFunction(EaseInBounce);
		   double ease = text_Ease_Function(pause_easing_t_);

		   view.setRotation(-(view.getRotation()) * (float)ease);

		   menu_Text_.setCharacterSize((int)(64 * ease));
		   menu_Text_.setFillColor(sf::Color::Black);
		   menu_Text_.setOutlineThickness(1.0f);
		   menu_Text_.setString("PAUSE!");
		   sf::FloatRect textRect = menu_Text_.getLocalBounds();
		   menu_Text_.setOrigin(textRect.left + textRect.width / 2.0f,
								textRect.top + textRect.height / 2.0f);
		   menu_Text_.setPosition(sf::Vector2f(window_width / 2.0f, window_height / 2.0f));

		   window_.draw(menu_Text_);
		   pause_easing_t_ += deltatime * 2.5f;
		   if (pause_easing_t_ > 1.0f)
			   pause_easing_t_ = 1.0f;

		   window_.setView(view);
		   window_.clear();

		   parallax_Deep_Layer_->Draw(window_);
		   parallax_Middle_Layer_->Draw(window_);
		   parallax_Front_Layer_->Draw(window_);
		   parallax_Pretty_Stuff_->Draw(window_);

		   for (int i = 0; i < 2; i++)
		   {
			   window_.draw(obstacles_[i]);
		   }

		   player_->draw(window_);
		   window_.draw(highscore_);
		   window_.draw(menu_Text_);

		   window_.display();
	   }

	   if (current_state_ == GAME_STATE_DEAD)
	   {
		   player_->update(deltatime);
		   if (hold_explosion_frame_ < 0)
		   {
			   explosion_frame_++;
			   explosion_Object_->setTextureRect({ 40 * explosion_frame_, 0, 40, 41 });
			   hold_explosion_frame_ = 0.2f;
		   }
		   hold_explosion_frame_ -= deltatime;

		   //Shake - nothing random - I could have done it better, but I got a headache while making it :( 
		   if (screenshake_duration > 0)
		   {
			   easing_t_ += deltatime * variable * 20.0f * screen_shake_strength;
			   auto test_Function = getEasingFunction(EaseInOutBounce);
			   double t = test_Function(easing_t_);

			   view.setRotation((float)t * (5 * screen_shake_strength * -shake_direction_));
			   view.zoom(1.0f - ((float) t / 10.0f * screen_shake_strength));
			   view.setCenter( view.getCenter().x + (float)t * shake_direction_ * 30.0f * screen_shake_strength, view.getCenter().y + (float) t * variable * 20.0f * screen_shake_strength);

			   if (easing_t_ > 1.0f || easing_t_ < 0.0f)
				   variable = -variable;

			   if (easing_t_ <= 0)
				   shake_direction_ = -shake_direction_;
		   }
		   screenshake_duration -= deltatime;

		   window_.setView(view);
		   window_.clear();

		   parallax_Deep_Layer_->Draw(window_);
		   parallax_Middle_Layer_->Draw(window_);
		   parallax_Front_Layer_->Draw(window_);
		   parallax_Pretty_Stuff_->Draw(window_);
		   for (int i = 0; i < 2; i++)
		   {
			   window_.draw(obstacles_[i]);
		   }
		   player_->draw(window_);
		   if (screenshake_duration < 0)
		   {
			   auto text_Ease_Function = getEasingFunction(EaseInSine);
			   double ease = text_Ease_Function(text_easing_t_);

			   view.setRotation(-(view.getRotation()) * (float)ease);

			   menu_Text_.setCharacterSize((int)(54 * ease));
			   menu_Text_.setFillColor(sf::Color::Red);
			   menu_Text_.setOutlineThickness(1.0f);
			   menu_Text_.setString("Game Over - Hit Space for the Menu!");
			   sf::FloatRect textRect = menu_Text_.getLocalBounds();
			   menu_Text_.setOrigin(textRect.left + textRect.width / 2.0f,
									textRect.top + textRect.height / 2.0f);
			   menu_Text_.setPosition(sf::Vector2f(window_width / 2.0f, window_height / 2.0f));
			
			   window_.draw(menu_Text_);
			   text_easing_t_ += deltatime;
			   if (text_easing_t_ > 1.0f)
				   text_easing_t_ = 1.0f;
		   }
		   window_.draw(highscore_);
		   window_.display();
	   }

	   if (current_state_ == GAME_STATE_PLAY)
	   {
		   score_ += deltatime * 10;
		   std::string temp = "Score: " + std::to_string((int)score_);

		   highscore_.setString(temp);

		   player_->update(deltatime);

		   float speed = 250 * deltatime;
		   for (int i = 0; i < 2; i++)
		   {
			   obstacles_[i].setPosition(obstacles_[i].getPosition().x - speed, obstacles_[i].getPosition().y);
			   if (obstacles_[i].getPosition().x < 0 - obstacles_[i].getTextureRect().width)
				   obstacles_[i].setPosition((float)(i * obstacles_[i].getTextureRect().width) + window_width, 720 - 100 - (32 * 2));
		   }

		   gem_->update(deltatime, 250.0f);
		   if (intersect(player_->sprite_, gem_->sprite_, 13, 12))
		   {
			   score_ += 1000.0f; 
			   sound_Boing_.play();
			   gem_->position_.x = 1380.0f;
		   }
		   parallax_Deep_Layer_->Update(deltatime);
		   parallax_Middle_Layer_->Update(deltatime);
		   parallax_Front_Layer_->Update(deltatime);
		   parallax_Pretty_Stuff_->Update(deltatime);

		  
		   if (player_->current_state != Player::RUN)
		   {
			   for (int i = 0; i < parallax_Front_Layer_->sprites_.size(); i++)
			   {
				   if (intersect(player_->sprite_, parallax_Front_Layer_->sprites_[i], 0, 0))
				   {
					   jumped_ = false;
					   player_->set_Animation(0);
					   player_->velocity_.y = 0;
					   player_->current_state = Player::RUN;
					   break;
				   }
			   }
		   }

		   for (int i = 0; i < 2; i++)
		   {
			   if (intersect(player_->sprite_, obstacles_[i], 30, 17))
			   {
				   text_easing_t_ = 0;
				   current_state_ = GAME_STATE_DEAD;
				   player_->current_state = Player::DEATH;
				   player_->set_Animation(2);
				   obstacles_[i].setTexture(*explosion_);
				   obstacles_[i].setScale(8.0f, 8.0f);
				   obstacles_[i].setPosition(obstacles_[i].getPosition().x - explosion_->getSize().x/2.0f, obstacles_[i].getPosition().y - explosion_->getSize().y * 4.0f);
				   obstacles_[i].setTextureRect({ 0, 0, 40, 41 });
				   explosion_Object_ = &obstacles_[i];
				   hold_explosion_frame_ = 0.2f;
				   sound_Death_.play();
				   break;
			   }
		   }

		   window_.setView(view);
		   window_.clear();

		   parallax_Deep_Layer_->Draw(window_);
		   parallax_Middle_Layer_->Draw(window_);
		   parallax_Front_Layer_->Draw(window_);
		   parallax_Pretty_Stuff_->Draw(window_);

		   for (int i = 0; i < 2; i++)
		   {
			   window_.draw(obstacles_[i]);
		   }

		   player_->draw(window_);

		   gem_->draw(window_);

		   window_.draw(highscore_);

		   window_.display();
	   }
   }
   exit();
}

void endless_runner::exit()
{
   window_.close();
}

// input_listener
bool endless_runner::on_input(input_state_delta &input)
{
   if (input.has_action(EXIT_CODE))
   {
      current_state_ = GAME_STATE_QUIT;
      input.eat_action(EXIT_CODE);
   }
   if (input.has_action(JUMP_CODE)) //PlayerObject->On_Input
   {
	   if (player_->current_state != Player::DEATH && current_state_ != GAME_STATE_PAUSE)
	   {
		   if (current_state_ == GAME_STATE_MENU)
			   current_state_ = GAME_STATE_PLAY;
		   else
		   {
			   if (!jumped_)
			   {
				   player_->velocity_.y = 5.0f;
				   player_->current_state = Player::JUMP;
				   player_->set_Animation(1);
				   sound_Jump_.play();
				   jumped_ = true;

			   }
		   }
		   input.eat_action(JUMP_CODE);
	   }
	   if (current_state_ == GAME_STATE_DEAD)
	   {
		   menu_easing_t_ = 0;
		   create_Game();
	   }
   }
   if (input.has_action(PAUSE_CODE))
   {
	   if (current_state_ != GAME_STATE_MENU && current_state_ != GAME_STATE_DEAD)
	   {
		   if (current_state_ != GAME_STATE_PAUSE)
		   {
			   pause_easing_t_ = 0;
			   current_state_ = GAME_STATE_PAUSE;
			   return true;
		   }
		   current_state_ = GAME_STATE_PLAY;
	   }
		   input.eat_action(PAUSE_CODE);
   }
   return true;
}

