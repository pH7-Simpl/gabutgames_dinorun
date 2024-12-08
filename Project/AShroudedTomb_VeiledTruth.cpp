#include "AShroudedTomb_VeiledTruth.h"
#include "ScreenManager.h"

Engine::AShroudedTomb_VeiledTruth::AShroudedTomb_VeiledTruth(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "A Shrouded Tomb: Veiled Truth";
}

Engine::AShroudedTomb_VeiledTruth::~AShroudedTomb_VeiledTruth()
{
}

void Engine::AShroudedTomb_VeiledTruth::Init()
{
    mc_texture1 = new Texture("mc1.png");
    mc_texture2 = new Texture("mc2.png");
    mc_sprite1 = new Sprite(mc_texture1, defaultSpriteShader, defaultQuad);
    mc_sprite2 = new Sprite(mc_texture2, defaultSpriteShader, defaultQuad);
    Texture* bg1 = new Texture("bg_1.png");
    Texture* bg2 = new Texture("bg_2.png");
    game_bg = (new Sprite(bg1, defaultSpriteShader, defaultQuad))->SetSize((float) GetSettings()->screenWidth, (float) GetSettings()->screenHeight);
    end_bg = (new Sprite(bg2, defaultSpriteShader, defaultQuad))->SetSize((float)GetSettings()->screenWidth, (float)GetSettings()->screenHeight);
    current_bg = game_bg;
    for (int i = 0; i < 3; i++) {
        Texture* texture = new Texture("Item" + std::to_string(i + 1) + ".png");
        Item* item = new Item("puzzle_item" + std::to_string(i + 1), new Sprite(texture, defaultSpriteShader, defaultQuad), this);
        items_to_collect.push_back(item);
    }
    for (int i = 0; i < items_to_collect.size(); i++) {
        items_to_collect[i]->Init();
    }
    mc_sprite1->SetPosition(200, 100)->SetNumXFrames(13)->SetNumYFrames(46)->SetAnimationDuration(70)->SetScale(1.0f)->AddAnimation("idle", 131, 131)->AddAnimation("walk_up", 104, 112)->AddAnimation("walk_left", 117, 125)->AddAnimation("walk_down", 130, 138)->AddAnimation("walk_right", 143, 151)->AddAnimation("die", 259, 264);
    mc_sprite1->SetBoundingBoxSize(mc_sprite1->GetScaleWidth() - (30 * mc_sprite1->GetScale()),
        mc_sprite1->GetScaleHeight() - (14 * mc_sprite1->GetScale()));
    mc_sprite2->SetPosition(200, 0)->SetNumXFrames(8)->SetNumYFrames(12)->SetAnimationDuration(70)->SetScale(1.0f)->AddAnimation("attack_up", 0, 5)->AddAnimation("attack_left", 8, 13)->AddAnimation("attack_down", 16, 21)->AddAnimation("attack_right", 24, 29);
    SaveSettings();
    LoadSettings();
    ResetGame();
	Engine::ScreenManager::GetInstance(this)
        ->AddScreen("astvtmainmenuscreen", new ASTVTMainMenuScreen())
        ->AddScreen("astvtgamescreen", new ASTVTGameScreen(this))
        ->AddScreen("astvtpausescreen", new ASTVTPauseScreen(this))
        ->AddScreen("astvtgameoverscreen", new ASTVTGameOverScreen(this))
        ->SetCurrentScreen("astvtmainmenuscreen");
}

void Engine::AShroudedTomb_VeiledTruth::Update()
{
	Engine::ScreenManager::GetInstance(this)->Update();
}

void Engine::AShroudedTomb_VeiledTruth::Render()
{
	Engine::ScreenManager::GetInstance(this)->Draw();
}


using json = nlohmann::json;
void Engine::AShroudedTomb_VeiledTruth::SaveGame() {
    json gameData;
    vec2 playerPos = mc_sprite1->GetPosition();
    gameData["player"] = {
        {"name", "Adaline"},
        {"health", playerHealth},
        {"speed", playerSpeed},
        {"x", playerPos.x},
        {"y", playerPos.y},
        {"zombie_count", zombie_count},
        {"sword_damage", swordDamage}
    };
    gameData["zombie"] = {
        {"damage", zombieDamage},
        {"zombie_per_spawn", zombie_per_spawn},
        {"zombie_to_defeat_per_wave", zombie_to_defeat_per_wave},
    };
    for (int i = 0; i < items.size(); i++) {
        gameData["items"].push_back(items[i]->GetName());
    }
    gameData["story_phase"] = story_phase;
    gameData["end_scene"] = end_scene;
    gameData["end_scene_phase"] = end_scene_phase;
    gameData["post_narration_delay"] = post_narration_delay;

    ofstream file("ASTVT_gameData.json");
    if (file.is_open()) {
        file << gameData.dump(4); // Indented with 4 spaces for readability
        file.close();
    }
}

void Engine::AShroudedTomb_VeiledTruth::LoadGame() {
    ifstream file("ASTVT_gameData.json");
    if (!file.is_open()) {
        cerr << "Failed to open save file!" << endl;
        return;
    }

    json gameData;
    file >> gameData;
    playerName = gameData["player"]["name"];
    playerHealth = gameData["player"]["health"];
    playerSpeed = gameData["player"]["speed"];
    items.clear();
    if (gameData.contains("items") && gameData["items"].is_array()) {
        for (int i = 0; i < gameData["items"].size(); i++) {
            string itemName = gameData["items"][i];
            for (Item* item : items_to_collect) {
                if (item->GetName() == itemName) {
                    items.push_back(item);
                    break;
                }
            }
        }
    }
    story_phase = gameData["story_phase"];
    end_scene = gameData["end_scene"];
    end_scene_phase = gameData["end_scene_phase"];
    post_narration_delay = gameData["post_narration_delay"];
    mc_sprite1->SetPosition(gameData["player"]["x"], gameData["player"]["y"]);
    mc_sprite2->SetPosition(gameData["player"]["x"] - 64, gameData["player"]["y"] - 64);
    zombie_count = gameData["player"]["zombie_count"];
    swordDamage = gameData["player"]["sword_damage"];
    zombieDamage = gameData["zombie"]["damage"];
    zombie_per_spawn = gameData["zombie"]["zombie_per_spawn"];
    zombie_to_defeat_per_wave = gameData["zombie"]["zombie_to_defeat_per_wave"];
    file.close();
}

void Engine::AShroudedTomb_VeiledTruth::ResetGame() {
    json gameData;
    gameData["player"] = {
        {"name", "Adaline"},
        {"health", 100},
        {"speed", 2.0},
        {"x", 200.0},
        {"y", 100.0},
        {"zombie_count", 0},
        {"sword_damage", 100},
    };
    gameData["items"] = {};
    gameData["story_phase"] = 0;
    gameData["end_scene"] = false;
    gameData["end_scene_phase"] = -1;
    gameData["post_narration_delay"] = 0.0f;
    gameData["zombie"] = {
        {"damage", 10},
        {"zombie_per_spawn", 2},
        {"zombie_to_defeat_per_wave", 1},
    };
    gameData["items"] = NULL;

    ofstream file("ASTVT_gameData.json");
    if (file.is_open()) {
        file << gameData.dump(4); // Indented with 4 spaces for readability
        file.close();
    }
    player_dying_duration = 0;
    mc_sprite1 = new Sprite(mc_texture1, defaultSpriteShader, defaultQuad);
    mc_sprite2 = new Sprite(mc_texture2, defaultSpriteShader, defaultQuad);
    current_bg = game_bg;
    narration_bg_f = 0.0f;
    narration_phase = 0;
    slow_down = false;
    narrating = false;
    for (int i = 0; i < items_to_collect.size(); i++) {
        items_to_collect[i]->Init();
    }

    mc_sprite1->SetPosition(200, 100)->SetNumXFrames(13)->SetNumYFrames(46)->SetAnimationDuration(70)->SetScale(1.0f)->AddAnimation("idle", 131, 131)->AddAnimation("walk_up", 104, 112)->AddAnimation("walk_left", 117, 125)->AddAnimation("walk_down", 130, 138)->AddAnimation("walk_right", 143, 151)->AddAnimation("die", 259, 264);
    mc_sprite1->SetBoundingBoxSize(mc_sprite1->GetScaleWidth() - (30 * mc_sprite1->GetScale()),
        mc_sprite1->GetScaleHeight() - (14 * mc_sprite1->GetScale()));
    mc_sprite2->SetPosition(200, 0)->SetNumXFrames(8)->SetNumYFrames(12)->SetAnimationDuration(70)->SetScale(1.0f)->AddAnimation("attack_up", 0, 5)->AddAnimation("attack_left", 8, 13)->AddAnimation("attack_down", 16, 21)->AddAnimation("attack_right", 24, 29);
    mc_sprite1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    for (Zombie* zombie : zombies) {
        zombie->SetHealth(100);
        if (!zombie->IsDie()) {
            zombie->SetZombieState(ZombieState::DIE);
        }
    }
    LoadGame();
}

void Engine::AShroudedTomb_VeiledTruth::SaveSettings() {
    json gameSetting;
    gameSetting["input"] = {
        {"move_up", SDLK_w},
        {"move_right", SDLK_d},
        {"move_down", SDLK_s},
        {"move_left", SDLK_a},
        {"pause", SDLK_ESCAPE},
        {"attack", SDLK_SPACE},
        {"pick_up", SDLK_f},
        {"next", SDLK_DOWN},
        {"prev", SDLK_UP},
        {"press", SDLK_RETURN},
    };

    ofstream file("ASTVT_gameSettings.json");
    if (file.is_open()) {
        file << gameSetting.dump(4);
        file.close();
    }
}


void Engine::AShroudedTomb_VeiledTruth::LoadSettings() {
    ifstream file("ASTVT_gameSettings.json");
    if (file.is_open()) {
        json gameSetting;
        file >> gameSetting;
        if (gameSetting.contains("input")) {
            for (auto& element : gameSetting["input"].items()) {
                string action = element.key();
                int key = element.value();
                GetInputManager()->AddInputMapping(action, key);
            }
        }
        file.close();
    }
}

void Engine::AShroudedTomb_VeiledTruth::SetPlayerSpeed(float x) {
    playerSpeed = x;
}

float Engine::AShroudedTomb_VeiledTruth::GetPlayerSpeed() const {
    return playerSpeed;
}

void Engine::AShroudedTomb_VeiledTruth::GameOver() {
    mc_sprite1->SetPosition(200, 100);
    items.clear();
    for (int i = 0; i < items_to_collect.size(); i++) {
        items_to_collect[i]->Init();
    }
    mc_sprite1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    for (Zombie* zombie : zombies) {
        zombie->SetHealth(100);
        if (!zombie->IsDie()) {
            zombie->SetZombieState(ZombieState::DIE);
        }
    }
    ScreenManager::GetInstance(this)->SetCurrentScreen("astvtgameoverscreen");
    return;
}

void Engine::AShroudedTomb_VeiledTruth::AddItem(Item* item) {
    items.push_back(item);
    return;
}

bool Engine::AShroudedTomb_VeiledTruth::HaveItem(string itemname) const {
    // Use std::find_if to find an item by its name
    auto it = find_if(items.begin(), items.end(), [&itemname](const Item* item) {
        return item->GetName() == itemname;
        });
    return it != items.end();
}

void Engine::AShroudedTomb_VeiledTruth::SetStoryPhase(float x) {
    story_phase = x;
}

float Engine::AShroudedTomb_VeiledTruth::GetStoryPhase() const {
    return story_phase;
}

void Engine::AShroudedTomb_VeiledTruth::SetZombieCount(float x) {
    zombie_count = x;
}

int Engine::AShroudedTomb_VeiledTruth::GetZombieCount() const {
    return zombie_count;
}

void Engine::AShroudedTomb_VeiledTruth::SetPlayerHealth(float x) {
    playerHealth = x;
}

int Engine::AShroudedTomb_VeiledTruth::GetPlayerHealth() const {
    return playerHealth;
}

int Engine::AShroudedTomb_VeiledTruth::GetSwordDamage() const {
    return swordDamage;
}

int Engine::AShroudedTomb_VeiledTruth::GetZombieDamage() const {
    return zombieDamage;
}