#include "ASTVTPauseScreen.h"
#include "ASTVTGameScreen.h"

Engine::ASTVTPauseScreen::ASTVTPauseScreen(AShroudedTomb_VeiledTruth* instance) : astvt(instance)
{
	text = NULL;
}

void Engine::ASTVTPauseScreen::Init()
{
	// Create a Texture
	Texture* continue_texture = new Texture("assets/Continue.png");
	Texture* mm_texture = new Texture("assets/Main_Menu.png");
	Texture* exit_texture = new Texture("assets/Exit.png");
	Texture* bg_texture = new Texture("assets/mc_phone.png");
	backgroundSprite = (new Sprite(bg_texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetSize((float)game->GetSettings()->screenWidth/2, (float)game->GetSettings()->screenHeight-150)
		->SetPosition((game->GetSettings()->screenWidth / 2), 0);

	// Create Sprites
	Sprite* continueSprite = (new Sprite(continue_texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(3)->SetNumYFrames(1)->AddAnimation("normal", 2, 2)->AddAnimation("hover", 0, 1)
		->AddAnimation("press", 0, 1)->SetAnimationDuration(400)->SetScale(0.4f);

	Sprite* mainMenuSprite = (new Sprite(mm_texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(3)->SetNumYFrames(1)->AddAnimation("normal", 2, 2)->AddAnimation("hover", 0, 1)
		->AddAnimation("press", 0, 1)->SetAnimationDuration(400)->SetScale(0.4f);

	Sprite* exitSprite = (new Sprite(exit_texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(3)->SetNumYFrames(1)->AddAnimation("normal", 2, 2)->AddAnimation("hover", 0, 1)
		->AddAnimation("press", 0, 1)->SetAnimationDuration(400)->SetScale(0.4f);

	//Create Buttons
	Button* continueButton = new Button(continueSprite, "continue");
	continueButton->SetPosition((game->GetSettings()->screenWidth / 2 - 300) - (continueSprite->GetScaleWidth() / 2),
		400);
	buttons.push_back(continueButton);

	Button* mainMenuButton = new Button(mainMenuSprite, "mainmenu");
	mainMenuButton->SetPosition((game->GetSettings()->screenWidth / 2 - 300) - (mainMenuSprite->GetScaleWidth() / 2),
		300);
	buttons.push_back(mainMenuButton);

	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition((game->GetSettings()->screenWidth / 2 - 300) - (exitSprite->GetScaleWidth() / 2),
		200);
	buttons.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Create Text
	text = (new Text("assets/8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))
		->SetText("Paused")->SetPosition(game->GetSettings()->screenWidth * 0.5f - 260, game->GetSettings()->screenHeight - 100.0f)->SetColor(255, 209, 122);

}


void Engine::ASTVTPauseScreen::Update()
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
		if ("continue" == b->GetButtonName()) {
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

	if (game->GetInputManager()->IsKeyReleased("pause")) {
		ScreenManager::GetInstance(game)->SetCurrentScreen("astvtgamescreen");
	}
}

void Engine::ASTVTPauseScreen::Draw()
{
	backgroundSprite->Draw();
	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
	// Render title 
	text->Draw();
}
