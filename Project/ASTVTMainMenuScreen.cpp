#include "ASTVTMainMenuScreen.h"

Engine::ASTVTMainMenuScreen::ASTVTMainMenuScreen()
{
	text = NULL;
}

void Engine::ASTVTMainMenuScreen::Init()
{
	// Create a Texture
	Texture* bg_texture = new Texture("Cover.png");
	Texture* play_texture = new Texture("Start_Game.png");
	Texture* exit_texture = new Texture("Exit.png");
	backgroundSprite = (new Sprite(bg_texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetSize((float)game->GetSettings()->screenWidth, (float)game->GetSettings()->screenHeight);

	// Create Sprites
	Sprite* playSprite = (new Sprite(play_texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(3)->SetNumYFrames(1)->AddAnimation("normal", 2, 2)->AddAnimation("hover", 0, 1)
		->AddAnimation("press", 0, 1)->SetAnimationDuration(400)->SetScale(0.4f);

	Sprite* exitSprite = (new Sprite(exit_texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(3)->SetNumYFrames(1)->AddAnimation("normal", 2, 2)->AddAnimation("hover", 0, 1)
		->AddAnimation("press", 0, 1)->SetAnimationDuration(400)->SetScale(0.4f);

	//Create Buttons
	Button* playButton = new Button(playSprite, "play");
	playButton->SetPosition((game->GetSettings()->screenWidth / 2 + 270) - (playSprite->GetScaleWidth() / 2),
		400);
	buttons.push_back(playButton);

	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition((game->GetSettings()->screenWidth / 2 + 270) - (exitSprite->GetScaleWidth() / 2),
		250);
	buttons.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Create Text
	text = (new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))
		->SetText("Veiled Truth")->SetPosition(game->GetSettings()->screenWidth * 0.5f - 10, game->GetSettings()->screenHeight - 100.0f)->SetColor(255, 209, 122);

}

void Engine::ASTVTMainMenuScreen::Update()
{
	// Set background
	game->SetBackgroundColor(52, 155, 235);

	if (game->GetInputManager()->IsKeyReleased("next")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Next Button
		currentButtonIndex = (currentButtonIndex < (int)buttons.size() - 1) ? currentButtonIndex + 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (game->GetInputManager()->IsKeyReleased("prev")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Prev Button
		currentButtonIndex = currentButtonIndex > 0 ? currentButtonIndex - 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (game->GetInputManager()->IsKeyReleased("press")) {
		// Set current button to press state
		Button* b = buttons[currentButtonIndex];
		b->SetButtonState(Engine::ButtonState::PRESS);
		// If play button then go to InGame, exit button then exit
		if ("play" == b->GetButtonName()) {
			ScreenManager::GetInstance(game)->SetCurrentScreen("astvtgamescreen");
		}
		else if ("exit" == b->GetButtonName()) {
			game->SetState(Engine::State::EXIT);
		}
	}

	// Update All buttons
	for (Button* b : buttons) {
		b->Update(game->GetGameTime());
	}
}

void Engine::ASTVTMainMenuScreen::Draw()
{
	backgroundSprite->Draw();
	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
	// Render title 
	text->Draw();
}