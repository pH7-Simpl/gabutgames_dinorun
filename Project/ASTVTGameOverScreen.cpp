#include "ASTVTGameOverScreen.h"

Engine::ASTVTGameOverScreen::ASTVTGameOverScreen(AShroudedTomb_VeiledTruth* instance) : astvt(instance)
{

}

void Engine::ASTVTGameOverScreen::Init()
{
	// Create a Texture
	Texture* retry_texture = new Texture("Retry.png");
	Texture* mm_texture = new Texture("Main_Menu.png");
	Texture* exit_texture = new Texture("Exit.png");

	// Create Sprites
	Sprite* retrySprite = (new Sprite(retry_texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(3)->SetNumYFrames(1)->AddAnimation("normal", 2, 2)->AddAnimation("hover", 0, 1)
		->AddAnimation("press", 0, 1)->SetAnimationDuration(400)->SetScale(0.4f);

	Sprite* mainMenuSprite = (new Sprite(mm_texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(3)->SetNumYFrames(1)->AddAnimation("normal", 2, 2)->AddAnimation("hover", 0, 1)
		->AddAnimation("press", 0, 1)->SetAnimationDuration(400)->SetScale(0.4f);

	Sprite* exitSprite = (new Sprite(exit_texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(3)->SetNumYFrames(1)->AddAnimation("normal", 2, 2)->AddAnimation("hover", 0, 1)
		->AddAnimation("press", 0, 1)->SetAnimationDuration(400)->SetScale(0.4f);

	//Create Buttons
	Button* retryButton = new Button(retrySprite, "retry");
	retryButton->SetPosition((game->GetSettings()->screenWidth / 2) - (retrySprite->GetScaleWidth() / 2),
		400);
	buttons.push_back(retryButton);

	Button* mainMenuButton = new Button(mainMenuSprite, "mainmenu");
	mainMenuButton->SetPosition((game->GetSettings()->screenWidth / 2) - (mainMenuSprite->GetScaleWidth() / 2),
		300);
	buttons.push_back(mainMenuButton);

	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition((game->GetSettings()->screenWidth / 2) - (exitSprite->GetScaleWidth() / 2),
		200);
	buttons.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Create Game Over Text
	gameOverText = (new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))
		->SetText("Game Over")->SetPosition(game->GetSettings()->screenWidth * 0.5f - 200, game->GetSettings()->screenHeight - 100.0f)->SetColor(255, 209, 122);

	// Create Game Over Text
	bestScoreText = (new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))
		->SetText("Try Again")->SetPosition(game->GetSettings()->screenWidth * 0.5f - 190, game->GetSettings()->screenHeight - 150.0f)->SetColor(255, 209, 122);

}


void Engine::ASTVTGameOverScreen::Update()
{
	// Set background
	game->SetBackgroundColor(0, 0, 0);

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
		if ("retry" == b->GetButtonName()) {
			astvt->ResetGame();
			ScreenManager::GetInstance(game)->SetCurrentScreen("astvtgamescreen");
		}
		else if ("mainmenu" == b->GetButtonName()) {
			astvt->ResetGame();
			ScreenManager::GetInstance(game)->SetCurrentScreen("astvtmainmenuscreen");
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

void Engine::ASTVTGameOverScreen::Draw()
{
	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
	// Render title 
	gameOverText->Draw();
	bestScoreText->Draw();
}