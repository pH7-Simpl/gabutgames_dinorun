#include "ASTVTGameScreen.h"

Engine::ASTVTGameScreen::ASTVTGameScreen(AShroudedTomb_VeiledTruth* instance) : astvt(instance)
{

}

void Engine::ASTVTGameScreen::Init()
{
	sword_texture = new Texture("sword.png");
	Texture* bgTexture = new Texture("bg_1.png");
	zombie_texture = new Texture("zombiee.png");
	sword_sprite = new Sprite(sword_texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	sword_sprite->SetPosition(200, 50)->SetScale(1.0f)->SetNumXFrames(1)->SetNumYFrames(1)->SetBoundingBoxSize(sword_sprite->GetScaleWidth(),sword_sprite->GetScaleHeight());
	item_drop = (new Sound("item_drop.wav"))->SetVolume(100);
	mc_damage = (new Sound("mc_damage.wav"))->SetVolume(100);
	death = (new Sound("death.wav"))->SetVolume(100);
	mc_walk = (new Sound("mc_walk.wav"))->SetVolume(100);
	sword_swing_hit = (new Sound("sword_swing_hit.wav"))->SetVolume(100);
	sword_swing_miss = (new Sound("sword_swing_miss.wav"))->SetVolume(100);
	narration_text = new Text("lucon.ttf", 12, game->GetDefaultTextShader());
	debugText = new Text("lucon.ttf", 24, game->GetDefaultTextShader());
	narration_text->SetScale(2.2f)->SetColor(64, 64, 64)->SetPosition(150, game->GetSettings()->screenHeight - 150);
	debugText->SetScale(2.2f)->SetColor(64, 64, 64)->SetPosition((game->GetSettings()->screenWidth) / 2, game->GetSettings()->screenHeight - (debugText->GetFontSize() * debugText->GetScale()) - 100);
	Texture* broken_heart_texture = new Texture("broken_heart.png");
	Texture* heart_texture = new Texture("heart.png");
	Texture* skull_texture = new Texture("skeleton.png");
	heart_sprite = (new Sprite(heart_texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetScale(0.1f);
	skull_sprite = (new Sprite(skull_texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetScale(0.07f);
	float topUIX = 20;
	float topImageUIY = game->GetSettings()->screenHeight - heart_sprite->GetScaleHeight();
	float topTextUIY = game->GetSettings()->screenHeight - heart_sprite->GetScaleHeight() / 1.5;
	heart_sprite->SetPosition(topUIX, topImageUIY);
	topUIX += heart_sprite->GetScaleWidth() - 10;
	player_hp_text = (new Text("lucon.ttf", 24, game->GetDefaultTextShader()))->SetPosition(topUIX, topTextUIY);
	topUIX += 60;
	skull_sprite->SetPosition(topUIX, topImageUIY + 10);
	topUIX += skull_sprite->GetScaleWidth();
	zombie_count = (new Text("lucon.ttf", 24, game->GetDefaultTextShader()))->SetPosition(topUIX, topTextUIY);
	Sprite* zombie_broken_heart_sprite = (new Sprite(broken_heart_texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetScale(0.06f);
	player_broken_heart = new BrokenHeart(zombie_broken_heart_sprite);



	// Spawn cactus setting
	maxZombieSpawnTime = 500;
	numZombieInPool = 100;

	for (int i = 0; i < numZombieInPool; i++) {
		Sprite* zombie_hand_sprite = (new Sprite(sword_texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetBoundingBoxSize(72, 72);
		Sprite* zombie_broken_heart_sprite = (new Sprite(broken_heart_texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetScale(0.06f)->SetPosition(-300, -300);
		BrokenHeart* zombie_broken_heart = new BrokenHeart(zombie_broken_heart_sprite);
		Zombie* zombie =  new Zombie(CreateZombieSprite(), zombie_hand_sprite, zombie_broken_heart);
		astvt->zombies.push_back(zombie);
	}

	dotTexture = new Texture("dot.png");
	for (int i = 0; i < 8; i++) {
		Sprite* dotsprite = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
		dotSprites.push_back(dotsprite);
	}
	for (int i = 0; i < astvt->zombies.size(); i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 2; k++) {
				Sprite* dotSprite = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
				dotSprites.push_back(dotSprite);
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			Sprite* dotSprite = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
			dotSprites.push_back(dotSprite);
		}
	}
}

void Engine::ASTVTGameScreen::Update()
{
	//debugText->SetText(to_string(astvt->mc_sprite1->GetColor()[0]));
	if (game->GetInputManager()->IsKeyReleased("pause")) {
		ScreenManager::GetInstance(game)->SetCurrentScreen("astvtpausescreen");
	}
	astvt->mc_sprite1->Update(game->GetGameTime());
	astvt->mc_sprite2->Update(game->GetGameTime());
	player_hp_text->SetText(to_string(astvt->GetPlayerHealth()));
	zombie_count->SetText(to_string(astvt->GetZombieCount()));
	player_broken_heart->Update(game->GetGameTime(), astvt->mc_sprite1->GetPosition().x + 13.0f, astvt->mc_sprite1->GetPosition().y + astvt->mc_sprite1->GetScaleHeight() - 5.0f);
	CharacterMovement();
	// Debugging codes
	if (debug) {
		vector<BoundingBox*> bbZombies;
		vector<BoundingBox*> bbZombiesHands;
		vector<BoundingBox*> bbItems;
		int dotIndex = 0;
		// Process main character bounding box
		BoundingBox* bb = astvt->mc_sprite1->GetBoundingBox();
		for (int j = 0; j < 4; j++) {
			dotSprites[dotIndex]->SetPosition(
				bb->GetVertices()[j].x - (0.5f * dotSprites[dotIndex]->GetScaleWidth()),
				bb->GetVertices()[j].y - (0.5f * dotSprites[dotIndex]->GetScaleHeight())
			);
			dotIndex++; // Increment the counter
		}
		BoundingBox* bb2 = sword_sprite->GetBoundingBox();
		for (int j = 0; j < 4; j++) {
			dotSprites[dotIndex]->SetPosition(
				bb2->GetVertices()[j].x - (0.5f * dotSprites[dotIndex]->GetScaleWidth()),
				bb2->GetVertices()[j].y - (0.5f * dotSprites[dotIndex]->GetScaleHeight())
			);
			dotIndex++; // Increment the counter
		}
		// Process zombies' bounding boxes
		for (int i = 0; i < astvt->zombies.size(); i++) {
			// Get the bounding box for the current zombie
			bbZombies.push_back(astvt->zombies[i]->GetSprite()->GetBoundingBox()); // Store each zombie's bounding box

			// Now loop through the 4 vertices of the bounding box for the current zombie
			for (int j = 0; j < 4; j++) {
				// Ensure the dot sprite exists and is within bounds
				if (dotIndex < dotSprites.size()) {
					// Set the position of the dot sprite based on the corresponding bounding box vertex
					dotSprites[dotIndex]->SetPosition(
						bbZombies[i]->GetVertices()[j].x - (0.5f * dotSprites[dotIndex]->GetScaleWidth()),
						bbZombies[i]->GetVertices()[j].y - (0.5f * dotSprites[dotIndex]->GetScaleHeight())
					);
				}
				dotIndex++;
			}
		}
		for (int i = 0; i < astvt->zombies.size(); i++) {
			bbZombiesHands.push_back(astvt->zombies[i]->GetHandSprite()->GetBoundingBox()); // Store each zombie's hands bounding box

			// Now loop through the 4 vertices of the bounding box for the zombie hands
			for (int j = 0; j < 4; j++) {
				// Ensure the dot sprite exists and is within bounds
				if (dotIndex < dotSprites.size()) {
					// Set the position of the dot sprite based on the corresponding bounding box vertex
					dotSprites[dotIndex]->SetPosition(
						bbZombiesHands[i]->GetVertices()[j].x - (0.5f * dotSprites[dotIndex]->GetScaleWidth()),
						bbZombiesHands[i]->GetVertices()[j].y - (0.5f * dotSprites[dotIndex]->GetScaleHeight())
					);
				}
				dotIndex++;
			}
		}

		for (int i = 0; i < astvt->items_to_collect.size(); i++) {
			bbItems.push_back(astvt->items_to_collect[i]->GetSprite()->GetBoundingBox()); // Store each zombie's hands bounding box

			// Now loop through the 4 vertices of the bounding box for the zombie hands
			for (int j = 0; j < 4; j++) {
				// Ensure the dot sprite exists and is within bounds
				if (dotIndex < dotSprites.size()) {
					// Set the position of the dot sprite based on the corresponding bounding box vertex
					dotSprites[dotIndex]->SetPosition(
						bbItems[i]->GetVertices()[j].x - (0.5f * dotSprites[dotIndex]->GetScaleWidth()),
						bbItems[i]->GetVertices()[j].y - (0.5f * dotSprites[dotIndex]->GetScaleHeight())
					);
				}
				dotIndex++;
			}
		}
	}
	NarrationRegulator();
	if (!astvt->end_scene) {
		ZombieRegulator();
	}
	else {
		EndSceneRegulator();
	}
	if (!astvt->narrating) {
		for (int i = 0; i < astvt->items_to_collect.size(); i++) {
			astvt->items_to_collect[i]->Update(game->GetGameTime());
		}
		if (astvt->GetPlayerDyingDuration() < 0) {
			astvt->SetStoryPhase(10);
		}
		else if (astvt->GetPlayerDyingDuration() > 0) {
			astvt->SetPlayerDyingDuration(astvt->GetPlayerDyingDuration() - game->GetGameTime());
		}
	}
}

void Engine::ASTVTGameScreen::Draw()
{
	astvt->current_bg->Draw();
	for (Zombie* zombie : astvt->zombies) {
		zombie->Draw();
	}
	if (astvt->zombified_time > 0) {
		if (!attacking && !game->GetInputManager()->IsKeyPressed("attack")) {
			astvt->mc_sprite1->Draw();
		}
		else {
			astvt->mc_sprite2->Draw();
		}
	} else  {
		astvt->mc_zombie_sprite->Draw();
	}
	for (int i = 0; i < astvt->items_to_collect.size(); i++) {
		astvt->items_to_collect[i]->Draw();
	}
	heart_sprite->Draw();
	player_hp_text->Draw();
	skull_sprite->Draw();
	zombie_count->Draw();
	player_broken_heart->Draw();
	
	//Debugging Draws
	if (debug) {
		//sword_sprite->Draw();
		debugText->Draw();
		for (int i = 0; i < dotSprites.size(); i++)
		{
			dotSprites[i]->Draw();
		}
	}
	if (astvt->narrating) {
		astvt->narration_bg->Draw();
		narration_text->Draw();
	}
}

void Engine::ASTVTGameScreen::CharacterMovement() {
	if (astvt->narrating) return;
	if (astvt->GetPlayerDyingDuration() != 0) return;
		vec2 oldPlayerPos = astvt->mc_sprite1->GetPosition();
		x = oldPlayerPos.x, y = oldPlayerPos.y;
		if (game->GetInputManager()->IsKeyPressed("attack") && !attacking) {
			attacking = true;
			attack_cooldown = 500.0f;
		}
		if (attack_cooldown > 0.0f) {
			attack_cooldown -= game->GetGameTime();
		}
		if (attack_cooldown <= 0.0f && attacking) {
			attacking = false;
		}
		if (attacking) {
			sword_swing_miss->Play(false);
			if (game->GetInputManager()->IsKeyPressed("move_up")) {
				astvt->mc_sprite2->PlayAnim("attack_up");
				SwordMovement(1);
			}
			else if (game->GetInputManager()->IsKeyPressed("move_down")) {
				astvt->mc_sprite2->PlayAnim("attack_down");
				SwordMovement(2);
			}
			else if (game->GetInputManager()->IsKeyPressed("move_right")) {
				astvt->mc_sprite2->PlayAnim("attack_right");
				SwordMovement(3);
			}
			else if (game->GetInputManager()->IsKeyPressed("move_left")) {
				SwordMovement(4);
				astvt->mc_sprite2->PlayAnim("attack_left");
			}
			else {
				astvt->mc_sprite2->PlayAnim("attack_down");
				SwordMovement(2);
			}
		}
		else {
			astvt->mc_sprite1->PlayAnim("idle");
			astvt->mc_sprite2->PlayAnim("");
			SwordMovement(0);
			if (game->GetInputManager()->IsKeyPressed("move_up")) {
				y += astvt->GetPlayerSpeed();
				astvt->mc_sprite1->PlayAnim("walk_up");
				mc_walk->Play(false);
			}
			else if (game->GetInputManager()->IsKeyPressed("move_down")) {
				y -= astvt->GetPlayerSpeed();
				astvt->mc_sprite1->PlayAnim("walk_down");
				mc_walk->Play(false);
			}
			else if (game->GetInputManager()->IsKeyPressed("move_right")) {
				x += astvt->GetPlayerSpeed();
				astvt->mc_sprite1->PlayAnim("walk_right");
				mc_walk->Play(false);
			}
			else if (game->GetInputManager()->IsKeyPressed("move_left")) {
				x -= astvt->GetPlayerSpeed();
				astvt->mc_sprite1->PlayAnim("walk_left");
				mc_walk->Play(false);
			}
		}
	astvt->mc_sprite1->SetPosition(x, y);
	astvt->mc_zombie_sprite->SetPosition(x, y);
	astvt->mc_sprite2->SetPosition(x - 64, y - 64);
	PlayerHitMechanism();
}

void Engine::ASTVTGameScreen::PlayerHitMechanism() {
	for (Zombie* zombie : astvt->zombies) {
		if (hitCooldown <= 0.0f &&
			zombie->GetHandSprite()->GetBoundingBox()->CollideWith(astvt->mc_sprite1->GetBoundingBox())) {
			// Player takes damage
			astvt->SetPlayerHealth(astvt->GetPlayerHealth() - astvt->GetZombieDamage());
			player_broken_heart->ShowBrokenHeart();
			mc_damage->Play(false);
			astvt->mc_sprite1->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
			astvt->mc_sprite2->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
			if (astvt->GetPlayerHealth() <= 0) {
				attacking = false;
				zombie->SetHandPosition(-300, -300);
				astvt->mc_sprite1->PlayAnim("die", true);
				astvt->SetPlayerDyingDuration(2000.0f);
				death->Play(false);
			}
			hitCooldown = 500.0f;
			break;
		}
	}
	if (hitCooldown >= 0) {
		//zombie->MoveTo(x, y, 100.0f, true);
		hitCooldown -= game->GetGameTime();
		SetHit(true);
	}
	else {
		SetHit(false);
	}

	// Set zombie color back to normal if damaged
	if (astvt->mc_sprite1->GetColor()[1] <= 1.0f) {
		if (colorLerpDuration >= 50.0f) {
			astvt->mc_sprite1->SetColor(1.0f, astvt->mc_sprite1->GetColor()[1] + 0.1f, astvt->mc_sprite1->GetColor()[2] + 0.1f, 1.0f);
			astvt->mc_sprite2->SetColor(1.0f, astvt->mc_sprite2->GetColor()[1] + 0.1f, astvt->mc_sprite2->GetColor()[2] + 0.1f, 1.0f);
			colorLerpDuration = 0;
		}
		colorLerpDuration += game->GetGameTime();
	}
}

void Engine::ASTVTGameScreen::SwordMovement(int direction) {
	switch (direction)
	{
	case 1: // up
		sword_sprite->SetPosition(x, y + 24)->SetBoundingBoxSize(sword_sprite->GetScaleWidth() * 1.5,
			sword_sprite->GetScaleHeight() - 24);
		break;
	case 2: // down
		sword_sprite->SetPosition(x, y - 14)->SetBoundingBoxSize(sword_sprite->GetScaleWidth() * 1.5,
			sword_sprite->GetScaleHeight() - 24);
		break;
	case 3: // right
		sword_sprite->SetPosition(x + 46, y+10)->SetBoundingBoxSize(sword_sprite->GetScaleWidth(),
			sword_sprite->GetScaleHeight()/2 + 2);
		break;
	case 4: // left
		sword_sprite->SetPosition(x - 46, y + 10)->SetBoundingBoxSize(sword_sprite->GetScaleWidth(),
			sword_sprite->GetScaleHeight() / 2 + 2);
		break;
	default:
		sword_sprite->SetPosition(-100, -100);
		break;
	}
}

int Engine::ASTVTGameScreen::Lerp(float a, float b, float f)
{
	return (int)((1 - f) * a + f * b);
}

void Engine::ASTVTGameScreen::NarrationFadeIn(float lerp_speed) {
	astvt->narration_bg_f += lerp_speed;
	astvt->narration_bg->SetColor(1.0f, 1.0f, 1.0f, astvt->narration_bg_f);
	lerp_duration = 0;
	lerp_duration += game->GetGameTime();
}

void Engine::ASTVTGameScreen::NarrationFadeOut(float lerp_speed) {
	astvt->narration_bg_f -= lerp_speed;
	astvt->narration_bg->SetColor(1.0f, 1.0f, 1.0f, astvt->narration_bg_f);
	lerp_duration = 0;
	lerp_duration += game->GetGameTime();
}

void Engine::ASTVTGameScreen::Narrate(string input) {
	narration_pages.clear(); // Clear previous narration pages
	string narration;
	ifstream file(input);
	if (file.is_open()) {
		// Read the entire contents of the file into a string
		std::string line;
		while (std::getline(file, line)) {
			narration += line + " ";
		}
		file.close();
	}
	else {
		// If not a file, use the input string as literal narration
		narration = input;
	}

	string current_page;
	string current_line;
	int char_count = 0;
	int line_count = 0;

	for (char c : narration) {
		// Check for manual page break marker
		if (c == '\t') {
			if (!current_line.empty()) {
				current_page += current_line + '\n'; // Add the remaining line to the current page
				current_line.clear();
				char_count = 0;
			}
			narration_pages.push_back(current_page); // Add the current page to the pages
			current_page.clear();                   // Start a new page
			line_count = 0;                         // Reset the line count
			continue;                               // Skip the marker
		}

		current_line += c; // Add character to the current line
		char_count++;

		// Break the line after 62 characters
		if (char_count >= 62) {
			current_page += current_line + '\n'; // Add the current line to the current page
			current_line.clear();               // Clear the line
			char_count = 0;                     // Reset the character count
			line_count++;
		}

		// Break the page after 15 lines
		if (line_count >= 15) {
			narration_pages.push_back(current_page); // Add the current page to the pages
			current_page.clear();                    // Clear the page
			line_count = 0;                          // Reset the line count
		}
	}

	// Add any remaining text to the current page
	if (!current_line.empty()) {
		current_page += current_line + '\n';
	}
	if (!current_page.empty()) {
		narration_pages.push_back(current_page);
	}

	// Initialize narration variables
	current_page_index = 0;
	full_narration = narration_pages.empty() ? "" : narration_pages[0]; // Set the first page
	displayed_naration = "";
	current_character_index = 0;
	time_since_last_character = 0;
	astvt->narrating = true;
}




void Engine::ASTVTGameScreen::ShowNaration() {
	// Increment the master_time each frame to keep track of the timeline
	master_time += game->GetGameTime();

	// Phase 1: Fade-in
	if (astvt->narration_phase == 0) {
		NarrationFadeIn(0.1f); // Fade in
		if (astvt->narration_bg_f >= 1.0f) { // If fade-in is complete
			astvt->narration_phase = 1;    // Move to narration phase
			if (astvt->end_scene && astvt->end_scene_phase == -1) {
				attacking = false;
				astvt->current_bg = astvt->end_bg;
				KillAllZombies();
				float x_pos = game->GetSettings()->screenWidth / 2 - astvt->mc_sprite1->GetScaleWidth() / 2;
				float y_pos = 50;
				astvt->mc_sprite1->SetPosition(x_pos, y_pos);
				astvt->mc_sprite2->SetPosition(x_pos - 64, y_pos - 64);
				astvt->mc_zombie_sprite->SetPosition(x_pos, y_pos);
				astvt->mc_sprite1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
				astvt->end_scene_phase = 0;
			}
			master_time = 0;        // Reset master_time for the next phase
		}
	}
	// Phase 2: Narration (Character by Character)
	else if (astvt->narration_phase == 1) {
		// Handle text display logic
		time_since_last_character += game->GetGameTime();
		if (time_since_last_character >= text_display_speed && current_character_index < (int)full_narration.length()) {
			displayed_naration += full_narration[current_character_index]; // Add next character to display
			narration_text->SetText(displayed_naration);                   // Update the displayed text
			current_character_index++;                                     // Move to the next character
			time_since_last_character = 0;                                // Reset timer
		}

		// If narration is finished for the current page
		if (current_character_index >= (int)full_narration.length()) {
			astvt->narration_phase = 3; // Move to read-time phase
			master_time = 0;     // Reset master_time for the next phase
		}
	}
	// Phase 3: Wait to give time for the reader to read
	else if (astvt->narration_phase == 3) {
		if (master_time >= read_time) { // If enough time has passed for reading
			if (current_page_index < (int)narration_pages.size() - 1) {
				// Move to the next page
				current_page_index++;
				full_narration = narration_pages[current_page_index];
				displayed_naration = "";
				current_character_index = 0;
				astvt->narration_phase = 1; // Back to narration phase
			}
			else {
				// If no more pages, move to fade-out phase
				astvt->narration_phase = 2;
				master_time = 0;
				narration_text->SetText("");
			}
		}
	}
	// Phase 4: Fade-out
	else if (astvt->narration_phase == 2) {
		if (!astvt->slow_down) {
			NarrationFadeOut(0.1f); // Fade out
		}
		else {
			NarrationFadeOut(0.002f); // Fade out
		}
		if (astvt->narration_bg_f <= 0.0f) { // If fade-out is complete
			master_time = 0;         // Reset master_time
			if (astvt->GetStoryPhase() == -1) {
				astvt->current_bg = astvt->game_bg;
				astvt->post_narration_delay = 0.0f;
				astvt->GameOver();
			}
			else if (astvt->GetStoryPhase() == 7) {
				astvt->GameOver();
			}
			astvt->narration_phase = 4;
			astvt->slow_down = false;
		}
	}
	else if (astvt->narration_phase == 4) {
		if (master_time >= astvt->post_narration_delay) {
			// If the delay is over, reset and start the next narration
			astvt->narration_phase = 0;
			master_time = 0;
			astvt->narrating = false;       // Stop narrating once all phases are complete
			// Trigger your scene or other actions here
		}
	}
}

void Engine::ASTVTGameScreen::NarrationRegulator() {
	struct StoryPhase {
		int phase;
		function<bool()> condition;
		string narration;
		int nextPhase;
		function<void()> postNarrationFunction;
	};

	// Define the story phases
	static const std::vector<StoryPhase> storyPhases = {
		{0, [this]() { return !astvt->narrating; }, "How many days have passed?\tWhere are my friends and family?\tI miss you all...", 1, nullptr},
		{1, [this]() { return !astvt->narrating && astvt->HaveItem("puzzle_item1"); }, "item1.txt", 2, nullptr},
		{2, [this]() { return !astvt->narrating && astvt->HaveItem("puzzle_item2"); }, "item2.txt", 3, nullptr},
		{3, [this]() { return !astvt->narrating && astvt->HaveItem("puzzle_item3"); }, "item3.txt", 4, [this]() {astvt->end_scene = true; astvt->slow_down = true; astvt->mc_sprite1->PlayAnim("idle"); }},
		{4, [this]() { return !astvt->narrating; }, "An altar...?", 5, [this]() {astvt->post_narration_delay = 2000.0f; }},
		{5, [this]() { return !astvt->narrating; }, "A voice erupts from within...\tYou who have passed through the trials...\tShall be granted a reward.\tStep into the altar, what you seek you shall obtain.", 6, [this]() {astvt->end_scene_phase = 1; astvt->post_narration_delay = 8000.0f; }},
		{6, [this]() { return !astvt->narrating; }, "How many days have passed?\tWhere are my friends and family?\tI miss you all...", 7, nullptr},
		{10, [this]() { return !astvt->narrating; }, " It’s not over yet...", -1,nullptr}
	};

	// Find and execute the appropriate phase
	for (const auto& phase : storyPhases) {
		if (astvt->GetStoryPhase() == phase.phase && phase.condition()) {
			Narrate(phase.narration);
			astvt->SetStoryPhase(phase.nextPhase);
			if (phase.postNarrationFunction) {
				phase.postNarrationFunction();
			}
			break;
		}
	}

	// Handle narration display
	if (astvt->narrating) {
		ShowNaration();
	}
}

void Engine::ASTVTGameScreen::EndSceneRegulator() {
	if (astvt->zombified) {
		if (astvt->zombified_time > 0) {
			astvt->zombified_time -= game->GetGameTime();
			death->Play(false);
		}
		else {
			astvt->mc_zombie_sprite->Update(game->GetGameTime());
			astvt->mc_zombie_sprite->PlayAnim("wakey_wakey", true);
		}
	}
	if (astvt->end_scene_phase == 0 && astvt->narration_bg_f <= 0.0f) {
		if (astvt->mc_sprite1->GetPosition().y <= astvt->GetSettings()->screenHeight * 0.25f) {
			vec2 oldPlayerPos = astvt->mc_sprite1->GetPosition();
			x = oldPlayerPos.x, y = oldPlayerPos.y;
			y += astvt->GetPlayerSpeed();
			astvt->mc_sprite1->PlayAnim("walk_up");
			mc_walk->Play(false);
			astvt->mc_sprite1->SetPosition(x, y);
			astvt->mc_zombie_sprite->SetPosition(x, y);
			astvt->mc_sprite2->SetPosition(x - 64, y - 64);
		}
		else {
			astvt->mc_sprite1->PlayAnim("idle");
		}
	}
	else if (astvt->end_scene_phase == 1 && astvt->narration_bg_f <= 0.0f) {
		if (astvt->mc_sprite1->GetPosition().y <= astvt->GetSettings()->screenHeight * 0.5f) {
			vec2 oldPlayerPos = astvt->mc_sprite1->GetPosition();
			x = oldPlayerPos.x, y = oldPlayerPos.y;
			y += astvt->GetPlayerSpeed();
			astvt->mc_sprite1->PlayAnim("walk_up");
			mc_walk->Play(false);
			astvt->mc_sprite1->SetPosition(x, y);
			astvt->mc_zombie_sprite->SetPosition(x, y);
			astvt->mc_sprite2->SetPosition(x - 64, y - 64);
		}
		else {
			astvt->mc_sprite1->PlayAnim("die", true);
			astvt->zombified = true;
		}
	}
}

Engine::Sprite* Engine::ASTVTGameScreen::CreateZombieSprite()
{
	return (new Sprite(zombie_texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetBoundingBoxSize(64, 64)->SetNumXFrames(13)->SetNumYFrames(3)->SetAnimationDuration(70)->SetScale(0.2f)->AddAnimation("attack", 0, 6)->AddAnimation("run", 13, 20)->AddAnimation("die", 26, 38);
}

int Engine::ASTVTGameScreen::Clamp(int value, int min, int max) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

void Engine::ASTVTGameScreen::ZombieRegulator() {
	if (astvt->narrating) return;
	if (astvt->GetPlayerDyingDuration() != 0) return;
	spawnZombieDuration += game->GetGameTime();
	if (spawnZombieDuration >= maxZombieSpawnTime) {
		SpawnZombies();
		spawnZombieDuration = 0;
		int min = 1000;
		int max = 5000;
		maxZombieSpawnTime = (float)(rand() % (max - min + 1) + min);
	}
	for (Zombie* zombie : astvt->zombies) {
		zombie->Update(game->GetGameTime());
		if (!zombie->IsDie()) {  // Only move and update alive zombiesd
			//Zombie movement
			if (zombie->GetHealth() > 0) {
				if (sqrt(pow(x - zombie->GetX(), 2) + pow(y - zombie->GetY(), 2)) > astvt->mc_sprite1->GetScaleWidth()) {
					zombie->MoveTo(x, y, zombie->GetSpeed());
					zombie->PlayAnim("run");
					zombie->SetHandPosition(-300, -300);
				}
				else {
					zombie->PlayAnim("attack");
					zombie->SetHandPosition(zombie->GetX(), zombie->GetY());
				}
			}
			zombie->SetPosition(zombie->GetX(), zombie->GetY());
			if (zombie->GetX() < x) {
				zombie->GetSprite()->SetFlipHorizontal(false);
			}
			else {
				zombie->GetSprite()->SetFlipHorizontal(true);
			}

			//Zombie hit by sword
			// Check if zombie is in cooldown
			if (zombie->GetHitCooldown() <= 0.0f &&
				zombie->GetSprite()->GetBoundingBox()->CollideWith(sword_sprite->GetBoundingBox())) {
				zombie->ShowBrokenHeart();
				// Zombie takes damage
				sword_swing_hit->Play(false);
				zombie->SetHealth(zombie->GetHealth() - astvt->GetSwordDamage());
				zombie->GetSprite()->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
				if (zombie->GetHealth() <= 0) {
					death->Play(false);
					astvt->SetZombieCount(astvt->GetZombieCount() + 1);

					// Check if the kill count meets the drop threshold
					if ((astvt->GetZombieCount() % astvt->GetZombieToDefeatPerWave() == 0) && (astvt->GetZombieCount() <= astvt->GetZombieToDefeatPerWave() * astvt->items_to_collect.size())) {
						// Calculate which item to drop
						int item_index = (astvt->GetZombieCount() / astvt->GetZombieToDefeatPerWave() - 1) % astvt->items_to_collect.size();
						Item* item_to_drop = astvt->items_to_collect[item_index];
						int clampedX = Clamp(zombie->GetX(), 0, game->GetSettings()->screenWidth - item_to_drop->GetWidth());
						int clampedY = Clamp(zombie->GetY(), 0, game->GetSettings()->screenHeight - item_to_drop->GetHeight());
						item_to_drop->SetPosition(clampedX, clampedY);
						item_drop->Play(false);
					}
				}
				zombie->SetHitCooldown(attack_cooldown);
			}
			else {
				//zombie->MoveTo(x, y, 100.0f, true);
				zombie->SetHitCooldown(zombie->GetHitCooldown() - game->GetGameTime());
			}

			if (zombie->GetHitCooldown() >= 0) {
				zombie->MoveTo(x, y, zombie->GetSpeed() * 2, true);
			}

			// Set zombie color back to normal if damaged
			if (zombie->GetSprite()->GetColor()[1] <= 1.0f) {
				if (zombie->colorLerpDuration >= 50.0f) {
					zombie->GetSprite()->SetColor(1.0f, zombie->GetSprite()->GetColor()[1] + 0.1f, zombie->GetSprite()->GetColor()[2] + 0.1f, 1.0f);
					zombie->colorLerpDuration = 0;
				}
				zombie->colorLerpDuration += game->GetGameTime();
			}
		}
		else {
			if (zombie->GetHealth() <= 0) {
				zombie->SetHealth(100);
			}
			if (zombie->GetX() != -300 && zombie->GetY() != -300) {
				zombie->SetPosition(-300, -300);
				zombie->SetHandPosition(-300, -300);
			}
		}
	}
}

void Engine::ASTVTGameScreen::SpawnZombies()
{
	// Find Die object to reuse for spawning
	int spawnCount = 0;
	for (Zombie* zombie : astvt->zombies) {
		if (spawnCount == astvt->GetZombiePerSpawn()) {
			break;
		}
		if (zombie->IsDie()) {
			// Set state to spawn
			zombie->SetSpawn();

			// Randomize spawn side: 0 for left, 1 for right
			bool spawnOnRight = rand() % 2 == 0;

			float x;
			if (spawnOnRight) {
				// Spawn on the right side of the screen
				zombie->GetSprite()->SetFlipHorizontal(true);
				x = game->GetSettings()->screenWidth + zombie->GetWidth();
			}
			else {
				// Spawn on the left side of the screen
				x = -zombie->GetWidth();
			}

			// Randomize Y position within the screen's height
			float y = rand() % (int)(game->GetSettings()->screenHeight - zombie->GetHeight());

			// Set the zombie's position
			zombie->SetPosition(x, y);
			spawnCount++;
		}
	}
}

void Engine::ASTVTGameScreen::KillAllZombies()
{
	for (Zombie* zombie : astvt->zombies) {
		zombie->SetHealth(100);
		if (!zombie->IsDie()) {
			zombie->SetZombieState(ZombieState::DIE);
		}
	}
}
