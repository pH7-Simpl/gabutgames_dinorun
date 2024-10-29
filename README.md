# Game Dino

Game Dino sederhana yang dibuat menggunakan C++ dan SDL.

## Deskripsi

Ini adalah implementasi sederhana dari game Dino klasik yang biasa ditemukan di browser Chrome saat offline.  Game ini menampilkan Dino yang berlari dan harus melompati kaktus untuk menghindari tabrakan.  Latar belakang menggunakan parallax scrolling untuk memberikan efek seolah-olah background ikut bergerak bersama karakter.  Game ini juga dilengkapi dengan menu utama, layar game over, dan layar pause.

## Fitur

* **Parallax Scrolling:** Latar belakang bergerak dengan kecepatan berbeda untuk menciptakan ilusi kedalaman.
* **Object Pooling:**  Object pooling digunakan untuk kaktus agar lebih efisien.
* **Deteksi Tabrakan:**  Mendeteksi tabrakan antara Dino dan kaktus.
* **Sistem Skor:**  Menghitung dan menampilkan skor.
* **Menu Utama:**  Memungkinkan pemain untuk memulai permainan atau keluar.
* **Layar Game Over:**  Menampilkan skor dan pilihan untuk memulai ulang atau kembali ke menu utama.
* **Layar Pause:**  Memungkinkan pemain untuk menjeda dan melanjutkan permainan, atau kembali ke menu utama.
* **Suara dan Musik:** Termasuk efek suara lompatan dan musik latar.

## Cara Bermain

* **Tombol Panah Atas/Bawah:** Navigasi menu.
* **Enter:** Memilih opsi di menu.
* **Spasi:** Melompat.
* **Esc:** Pause/Unpause game.

## Struktur Proyek

* **`Dino.h/cpp`:**  Kelas utama game.
* **`DinoGameScreen.h/cpp`:**  Layar permainan utama.
* **`DinoMainMenuScreen.h/cpp`:**  Layar menu utama.
* **`DinoGameOverScreen.h/cpp`:**  Layar game over.
* **`DinoPauseScreen.h/cpp`:** Layar pause game.
* **`Cactus.h/cpp`:** Kelas untuk objek kaktus.
* **`Game.h/cpp`:** Kelas dasar game engine.
* **`Input.h/cpp`:**  Mengelola input pemain.
* **`Sprite.h/cpp`:**  Kelas untuk sprite.
* **`Texture.h/cpp`:**  Mengelola tekstur.
* **`Sound.h/cpp`:** Mengelola efek suara.
* **`Music.h/cpp`:** Mengelola musik latar.
* **`SATCollision.h/cpp`:** Deteksi tabrakan (Separating Axis Theorem).


## Screenshot

(Tambahkan screenshot game di sini)


## Dependensi

* SDL2
* OpenGL
* SOIL
* SDL_mixer
* glm

## Cara Menjalankan

1. Pastikan semua dependensi terinstal.
2. Clone repositori ini.
3. Compile kode menggunakan compiler C++.
4. Jalankan executable yang dihasilkan.


## Kontributor

1. Eleazar Tadeo Eman / 225150201111053
2. Aliya Rizki Fatiha / 225150201111038
3. Emilia Syah Putri / 225150200111020
4. Senopati Fadhillah Langit / 225150207111028

# Langkah-Langkah Pembuatan Game Dino
<details>
  <summary>1. Setup Proyek</summary>
  
  * Buat proyek baru di IDE Microsoft Visual Studio 2022
  * Atur library yang diperlukan (SDL, OpenGL, SOIL, SDL_mixer, glm).
  * Pastikan file game engine (Game.h, Sprite.h, Input.h, dll.) sudah ada dalam folder proyek dan terkonfigurasi dengan benar.
    
</details>
<details>
  <summary>2. Buat Main Class Dino sebagai Class Manager</summary>

  **Buat File Header Dino.h**
  
  Berisi variabel-variabel berikut:
  * Music* music = NULL;: Pointer ke objek Music. Digunakan untuk mengelola musik latar. NULL menunjukkan bahwa pointer belum menunjuk ke objek apa pun saat inisialisasi.
  * Sound* sound = NULL;: Pointer ke objek Sound. Digunakan untuk mengelola efek suara. NULL menunjukkan bahwa pointer belum menunjuk ke objek apa pun saat inisialisasi.
  * int score = 0;: Variabel integer untuk menyimpan skor saat ini. Diinisialisasi dengan nilai 0.
  * int bestScore = 0;: Variabel integer untuk menyimpan skor terbaik. Diinisialisasi dengan nilai 0.
    
  Deklarasikan fungsi yang ada pada Dino.cpp:
  * Dino(Setting* setting): Konstruktor. Menerima pointer ke objek Setting yang berisi konfigurasi game.
  * ~Dino(): Destruktor. Bertugas membersihkan resource yang dialokasikan oleh objek Dino.
  * Init(): Fungsi untuk inisialisasi game, seperti memuat aset, membuat objek game, dan mengatur layar awal.
  * Update(): Fungsi yang dipanggil setiap frame untuk memperbarui logika game.
  * Render(): Fungsi yang dipanggil setiap frame untuk menggambar game di layar.
  * GetScore() const: Fungsi getter untuk mendapatkan nilai skor saat ini. const menandakan bahwa fungsi ini tidak akan mengubah state dari objek Dino.
  * SetScore(int x): Fungsi setter untuk mengatur nilai skor saat ini.
  * GetBestScore() const: Fungsi getter untuk mendapatkan nilai skor terbaik. const menandakan bahwa fungsi ini tidak akan mengubah state dari objek Dino. Terdapat deklarasi ganda dalam kode yang Anda berikan, dan ini harus dihapus.
  * SetBestScore(int x): Fungsi setter untuk mengatur nilai skor terbaik.
    
  **Buat File Dino.cpp**
  
  Berisi implementasi dari fungsi-fungsi yang dideklarasikan pada Dino.h:
  * Konstruktor (Engine::Dino::Dino(Setting* setting)):
    * Menerima pointer ke objek Setting yang berisi konfigurasi game (resolusi layar, target frame rate, dll.).
    * Memanggil konstruktor base class Engine::Game(setting) untuk menginisialisasi engine dengan pengaturan yang diberikan.
    * Mengatur judul jendela game dengan setting->windowTitle = "Dino Game";. Tidak ada perhitungan khusus di sini, hanya pengaturan nilai string.
  * Destruktor (Engine::Dino::~Dino()): Kosong karena tidak ada alokasi memori dinamis yang perlu di-dealokasikan secara manual dalam kelas Dino. Engine akan menangani dealokasi resource yang dibuat oleh base class Game.
  * Init():
    * Inisialisasi ScreenManager:
      * Engine::ScreenManager::GetInstance(this): Mendapatkan instance singleton dari ScreenManager. this pointer diteruskan agar ScreenManager tahu game mana yang sedang dijalankan.
      * AddScreen(...): Menambahkan layar-layar game ke ScreenManager. Setiap layar diidentifikasi dengan nama string (misalnya, "dino", "mainmenu"). Sebuah objek layar baru dibuat dan pointer-nya disimpan di ScreenManager.
      * SetCurrentScreen("mainmenu"): Mengatur layar awal game ke layar menu utama ("mainmenu").
  * Inisialisasi Skor:
    * score = 0;: Mengatur skor awal menjadi 0. Tidak ada perhitungan, hanya inisialisasi nilai integer.
  * Inisialisasi Musik dan Suara:
    * music = (new Music(...))->SetVolume(40)->Play(true);: Membuat objek Music, mengatur volumenya, dan memainkannya secara berulang (looping).
    * sound = (new Sound(...))->SetVolume(100);: Membuat objek Sound untuk efek suara lompat dan mengatur volumenya.
  * Update():
    * Engine::ScreenManager::GetInstance(this)->Update();: Memanggil fungsi Update() pada ScreenManager. Ini akan meneruskan pemanggilan Update() ke layar yang sedang aktif. Tidak ada perhitungan langsung di fungsi ini, hanya delegasi ke ScreenManager.
  * Render():
    * Engine::ScreenManager::GetInstance(this)->Draw();: Memanggil fungsi Draw() pada ScreenManager. Ini akan meneruskan pemanggilan Draw() ke layar yang sedang aktif. Sama seperti Update(), tidak ada perhitungan langsung di fungsi ini, hanya delegasi ke ScreenManager.
  * GetScore(), SetScore(), GetBestScore(), SetBestScore(): Fungsi-fungsi getter dan setter sederhana untuk mengakses dan memodifikasi nilai score dan bestScore. Tidak ada perhitungan khusus, hanya pengaksesan dan pengaturan nilai integer.
  
</details>
<details>
  <summary>3. Buat Layar Main Menu</summary>

  **Buat File Header DinoMainMenuScreen.h**
  
  Berisi variabel-variabel berikut:
  * std::vector<Button*> buttons;: Vektor yang berisi pointer ke objek-objek Button. Ini digunakan untuk menyimpan dan mengelola tombol-tombol di menu utama (misalnya, "Play", "Exit"). Vektor memungkinkan penambahan dan penghapusan tombol secara dinamis.
  * Text* text;: Pointer ke objek Text. Digunakan untuk menampilkan teks judul di menu utama (misalnya, "Dino Game").
  * int currentButtonIndex = 0;: Variabel integer yang menyimpan indeks tombol yang sedang dipilih dalam vektor buttons. Nilai 0 menunjukkan tombol pertama dalam vektor.
  
  Deklarasikan fungsi yang ada pada DinoMainMenuScreen.cpp:
  * DinoMainMenuScreen();: Konstruktor default. Tidak menerima argumen.
  * Init() override;: Fungsi untuk inisialisasi layar menu utama. override keyword menandakan bahwa fungsi ini meng-override fungsi virtual di base class (Screen). Inisialisasi biasanya meliputi pembuatan tombol, teks, dan pengaturan input mapping.
  * Update() override;: Fungsi yang dipanggil setiap frame untuk memperbarui logika layar menu utama. Ini biasanya memproses input pemain (navigasi menu, memilih tombol) dan memperbarui status tombol.
  * Draw() override;: Fungsi yang dipanggil setiap frame untuk menggambar layar menu utama. Ini menggambar tombol dan teks di layar.
  
  **Buat File DinoMainMenuScreen.cpp**
  
  Berisi implementasi dari fungsi-fungsi yang dideklarasikan pada DinoMainMenuScreen.h:
  * Konstruktor (Engine::DinoMainMenuScreen::DinoMainMenuScreen()): Menginisialisasi pointer text ke NULL. Ini penting untuk menghindari perilaku yang tidak terdefinisi saat mencoba mengakses pointer yang belum diinisialisasi.
  * Init():
    * Membuat Tekstur: Membuat objek Texture dari file gambar "buttons2.png". Tekstur ini akan digunakan untuk sprite tombol.
    * Membuat Sprite: Membuat objek Sprite untuk tombol "Play" dan "Exit", menggunakan tekstur yang telah dimuat. SetNumXFrames, SetNumYFrames, AddAnimation, SetAnimationDuration digunakan untuk mengkonfigurasi animasi tombol.
    * Membuat Tombol:
      * Membuat objek Button untuk "Play" dan "Exit", menggunakan sprite yang sesuai.
      * SetPosition digunakan untuk menempatkan tombol di layar. Perhitungan posisi biasanya relatif terhadap ukuran layar.
      * Tombol-tombol ditambahkan ke vektor buttons.
    * Membuat Teks Judul: Membuat objek Text untuk judul "Dino Game" menggunakan font dan shader yang ditentukan. SetPosition dan SetColor digunakan untuk mengatur posisi dan warna teks.
    * Input Mapping: Mendaftarkan tombol panah atas/bawah (SDLK_UP, SDLK_DOWN) untuk navigasi menu, dan tombol Enter (SDLK_RETURN) untuk memilih tombol.
    * Mengatur Tombol Aktif: currentButtonIndex = 0; Mengatur tombol "Play" (indeks 0) sebagai tombol yang aktif/dipilih saat menu pertama kali ditampilkan. buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER); Mengatur status tombol yang dipilih ke HOVER.
  * Update():
    * Mengatur Warna Latar Belakang: game->SetBackgroundColor(52, 155, 235); Mengatur warna latar belakang layar. Nilai RGB (Red, Green, Blue) digunakan.
    * Memproses Input:
      * Navigasi Menu:
        * if (game->GetInputManager()->IsKeyReleased("next")): Jika tombol "next" (panah bawah) dilepas:
          * Ubah status tombol yang sebelumnya dipilih menjadi NORMAL.
          * Pindahkan currentButtonIndex ke tombol berikutnya dalam vektor buttons. Logika modulo (%) digunakan untuk memastikan indeks tetap dalam batas vektor.
          * Ubah status tombol yang baru dipilih menjadi HOVER.
        * if (game->GetInputManager()->IsKeyReleased("prev")): Logika yang sama untuk tombol "prev" (panah atas), tetapi currentButtonIndex dikurangi.
      * Memilih Tombol:
        * if (game->GetInputManager()->IsKeyReleased("press")): Jika tombol "press" (Enter) dilepas:
          * Ubah status tombol yang dipilih menjadi PRESS.
          * Periksa nama tombol (GetButtonName()):
            * Jika "play", ganti layar ke "dino" (layar permainan).
            * Jika "exit", keluar dari game.
    * Update Tombol: b->Update(game->GetGameTime()); Memanggil fungsi Update() pada setiap tombol dalam vektor buttons. Ini memungkinkan tombol untuk memperbarui animasinya (misalnya, efek hover).
  * Draw():
    * Menggambar Tombol: Loop melalui vektor buttons dan panggil b->Draw() pada setiap tombol untuk menggambarnya di layar.
    * Menggambar Teks Judul: text->Draw(); Menggambar teks judul di layar.
  
</details>
<details>
  <summary>4. Buat Layar Permainan</summary>

  **Buat File Header DinoGameScreen.h**
  
  Berisi variabel-variabel berikut:
  * Dino* dino: Pointer ke objek Dino. Digunakan untuk mengakses data dan fungsi di kelas Dino.
  * Texture* texture, Sprite* sprite: Tekstur dan sprite untuk Dino.
  * yVelocity, gravity, jump: Variabel untuk mengontrol lompatan Dino. yVelocity adalah kecepatan vertikal, gravity adalah percepatan gravitasi, dan jump adalah flag untuk menandakan apakah Dino sedang melompat.
  * Texture* cactus_texture: Tekstur untuk kaktus.
  * std::vector<Cactus*> cacti: Vektor yang berisi pointer ke objek-objek Cactus.
  * spawnCactusDuration, maxCactusSpawnTime, numCactusInPool, numCactusPerSpawn: Variabel untuk mengontrol kemunculan kaktus.
  * scoreText: Objek teks untuk menampilkan skor.
  * ScoreDuration, seconds: Variabel untuk menghitung skor berdasarkan waktu. Perhitungannya ada di ScorePerDuration(float seconds), dijelaskan di DinoGameScreen.cpp.
  * speed,speedIncrease, lastSpeedIncreaseScore: Variabel untuk kecepatan game, kenaikan kecepatan dan score terakhir ketika kecepatan bertambah.

  Deklarasikan fungsi yang ada pada DinoGameScreen.cpp:
  * DinoGameScreen(Dino* dinoInstance): Konstruktor.
  * Init(), Update(), Draw(), GameOver(): Fungsi-fungsi utama untuk inisialisasi, update, menggambar, dan game over. Implementasinya ada di DinoGameScreen.cpp.
  * CreateCactusSprite(): Fungsi untuk membuat sprite kaktus. Implementasinya di DinoGameScreen.cpp.
  * SpawnCacti(): Fungsi untuk memunculkan kaktus. Implementasinya di DinoGameScreen.cpp.
  * MoveLayer(), DrawLayer(), AddToLayer(): Fungsi-fungsi untuk parallax scrolling. Implementasinya di DinoGameScreen.cpp.
  
  **Buat File DinoGameScreen.cpp**

  Berisi implementasi dari fungsi-fungsi yang dideklarasikan pada DinoGameScreen.h:
  * Konstruktor (DinoGameScreen::DinoGameScreen(Dino* dinoInstance)): Menerima pointer ke objek Dino sebagai argumen. Ini memungkinkan DinoGameScreen untuk mengakses data dan fungsi di kelas Dino, seperti skor dan fungsi pengaturan skor.
  * Init():
    * Memuat tekstur dan membuat sprite untuk Dino.
    * Mengatur animasi Dino (idle, run, jump).
    * Menginisialisasi parallax scrolling dengan memuat tekstur latar belakang dan membuat sprite untuk setiap layer.
    * Mengatur input mapping untuk lompat ("Jump") dan pause ("pause").
    * Menginisialisasi object pool untuk kaktus dengan membuat sejumlah objek Cactus dan menyimpannya di vektor cacti.
    * Membuat teks untuk menampilkan skor.
  * Update():
    * Parallax Scrolling: MoveLayer(backgrounds, speed * 0.025f), MoveLayer(middlegrounds, speed * 0.15f), MoveLayer(foregrounds, speed * 1.0f) Menggerakkan setiap layer parallax dengan kecepatan yang berbeda, menciptakan ilusi kedalaman. Perhitungan pergerakannya linear: posisi_x -= kecepatan * deltaTime.
    * Input Pause: if (game->GetInputManager()->IsKeyReleased("pause")) Memeriksa apakah tombol pause ditekan. Jika ya, ganti layar ke DinoPauseScreen.
    * sprite->PlayAnim("run"): Memainkan animasi lari Dino.
    * sprite->SetPosition(x, y): Mengatur posisi Dino.
    * Logika Lompatan:
      * if (game->GetInputManager()->IsKeyPressed("Jump") && !jump): Memeriksa input lompat dan apakah Dino sedang tidak melompat.
      * gravity = 0.08f * ratio: Mengatur gravitasi. ratio digunakan untuk menyesuaikan gravitasi dengan frame rate.
      * yVelocity = 1.4f: Mengatur kecepatan vertikal awal saat lompat.
      * jump = true: Menandai Dino sedang melompat.
      * dino->sound->Play(false): Memainkan efek suara lompat. 
    * Fisika Lompatan:
      * if (y > 0) { yVelocity -= gravity; }: Mengurangi kecepatan vertikal dengan gravitasi jika Dino di atas tanah.
      * else if (y < 0) { jump = false; yVelocity = 0; y = 0; }: Mendaratkan Dino jika posisinya di bawah tanah.
      * y += yVelocity * game->GetGameTime(): Memperbarui posisi vertikal Dino.
    * Memunculkan Kaktus (SpawnCacti()):
      * if (spawnCactusDuration >= maxCactusSpawnTime): Memeriksa apakah sudah waktunya memunculkan kaktus baru.
      * maxCactusSpawnTime = (float)(rand() % (max - min + 1) + min);: Menghitung waktu spawn kaktus berikutnya secara acak, dengan batas minimum dan maksimum yang dipengaruhi oleh kecepatan game.
    * Update Score (ScorePerDuration):
      * if (scoreDuration >= seconds): score bertambah setiap durasi waktu tertentu
      * if (dino->GetScore() % 10 == 0 && dino->GetScore() > lastSpeedIncreaseScore): kecepatan game dan kaktus bertambah setiap kelipatan 10 score.
    * Update Kaktus dengan looping melalui setiap kaktus di cacti dan memanggil c->Update(game->GetGameTime()).
    * Deteksi Tabrakan:
      * Loop melalui setiap kaktus di cacti dan memeriksa tabrakan dengan Dino menggunakan c->GetSprite()->GetBoundingBox()->CollideWith(sprite->GetBoundingBox()).
      * Jika terjadi tabrakan, panggil GameOver().
  * Draw():
    * Menggambar layer parallax: DrawLayer(backgrounds), DrawLayer(middlegrounds), DrawLayer(foregrounds).
    * Menggambar sprite Dino: sprite->Draw().
    * Menggambar kaktus: Loop melalui cacti dan panggil c->Draw().
    * Menggambar teks skor: scoreText->Draw().
  * GameOver():
    * mereset kecepatan game
    * mengatur ulang posisi kaktus di luar layar
    * mengatur ulang variabel yang berhubungan dengan kaktus dan score
    * mengecek dan mengupdate best score
    * mengganti layar ke GameOverScreen
  * CreateCactusSprite(): Membuat dan mengembalikan objek Sprite baru untuk kaktus.
  * SpawnCacti():
    * Mencari kaktus yang tidak aktif (status DIE) di object pool.
    * Mengatur status kaktus menjadi SPAWN.
    * Mengatur posisi kaktus di sisi kanan layar, di luar batas layar.
  * MoveLayer(std::vector<Sprite*>& bg, float speed): Menggerakkan layer parallax. Penjelasan detail ada di atas, pada bagian Update().
  * DrawLayer(std::vector<Sprite*>& bg): Menggambar layer parallax.
  * AddToLayer(std::vector<Sprite*>& bg, std::string name): Menambahkan sprite ke layer parallax.
  
</details>
<details>
  <summary>5. Buat Class Cactus sebagai rintangan</summary>

  **Buat File Header Cactus.h**
  
  Berisi variabel-variabel berikut:
  * Sprite* sprite = NULL;: Pointer ke objek Sprite yang digunakan untuk menggambar kaktus. Diinisialisasi dengan NULL.
  * CactusState state;: Variabel bertipe CactusState (sebuah enum class) yang merepresentasikan status kaktus (SPAWN, GROUND, atau DIE).
  * float groundDur = 0;: Durasi (dalam milidetik) kaktus berada di status GROUND. Diinisialisasi dengan 0.
  * float groundTime = 0;: Waktu total (dalam milidetik) kaktus akan berada di status GROUND sebelum berubah ke status DIE. Diinisialisasi dengan 0. Nilai ini kemungkinan diinisialisasi di konstruktor pada file .cpp.
  * float x = 0, y = 0;: Posisi awal kaktus (x dan y). Diinisialisasi dengan 0. Nilai-nilai ini tidak digunakan langsung untuk menggambar kaktus, tetapi lebih sebagai variabel bantu. Posisi sebenarnya dikelola oleh objek Sprite.
  * float xVelocity = 0.2f;: Kecepatan horizontal kaktus.
  
  Deklarasikan fungsi yang ada pada Cactus.cpp:
  * Cactus(Sprite* sprite);: Konstruktor. Menerima pointer ke objek Sprite.
  * ~Cactus();: Destruktor.
  * Update(float deltaTime);: Memperbarui status dan posisi kaktus berdasarkan waktu yang berlalu (deltaTime).
  * Draw();: Menggambar kaktus di layar.
  * SetPosition(float x, float y);: Mengatur posisi kaktus. Mengembalikan pointer ke objek Cactus itu sendiri (memungkinkan method chaining).
  * SetSpawn();: Mengatur status kaktus ke SPAWN. Mengembalikan pointer ke objek Cactus.
  * GetWidth();: Mendapatkan lebar kaktus.
  * GetHeight();: Mendapatkan tinggi kaktus.
  * IsDie();: Memeriksa apakah kaktus dalam status DIE.
  * GetX();: Mendapatkan posisi x kaktus.
  * GetY();: Mendapatkan posisi y kaktus.
  * Sprite* GetSprite();: Mengembalikan pointer ke objek Sprite kaktus.
  * Cactus* SetCactusState(CactusState state);: Mengatur status kaktus. Mengembalikan pointer ke objek Cactus.
  * float GetXVelocity() const;: Mengembalikan kecepatan horizontal kaktus. const menandakan fungsi ini tidak mengubah state objek.
  * void SetXVelocity(float x);: Mengatur kecepatan horizontal kaktus.
  
  **Buat File Cactus.cpp**
  
  Berisi implementasi dari fungsi-fungsi yang dideklarasikan pada Cactus.h:
  * Konstruktor (Engine::Cactus::Cactus(Sprite* sprite)):
    * Menerima pointer ke objek Sprite yang akan digunakan untuk menggambar kaktus.
    * Menginisialisasi anggota sprite dengan pointer yang diterima.
    * Mengatur status awal kaktus ke DIE.
    * Mengatur groundDur ke 0.
    * Mengatur groundTime ke 1000 (1 detik).
  * Destruktor (Engine::Cactus::~Cactus()): Kosong. Tidak ada alokasi memori dinamis yang perlu dibersihkan secara manual dalam kelas ini. Objek Sprite kemungkinan dikelola di tempat lain (misalnya, dengan object pooling).
  * Update(float deltaTime):
    * Jika status kaktus adalah DIE, fungsi langsung keluar (return).
    * Mendapatkan posisi x dan y kaktus menggunakan GetX() dan GetY().
    * State Spawn: Jika state adalah SPAWN dan posisi x kaktus kurang dari atau sama dengan -70 (kaktus telah melewati batas tertentu di sebelah kiri layar), state diubah ke GROUND.
    * State Ground: Jika state adalah GROUND:
      * groundDur ditambah dengan deltaTime.
      * Jika groundDur lebih dari atau sama dengan groundTime (kaktus telah berada di tanah selama groundTime), state kaktus diubah ke DIE dan groundDur di-reset ke 0.
    * Pergerakan Kaktus:
      * x -= xVelocity * deltaTime;: Mengurangi posisi x kaktus berdasarkan kecepatan horizontal (xVelocity) dan waktu yang berlalu (deltaTime). Ini menciptakan pergerakan kaktus ke kiri. Ini adalah perhitungan inti untuk pergerakan kaktus.
    * Memperbarui posisi sprite kaktus dengan sprite->SetPosition(x, y);.
    * Memperbarui animasi sprite (jika ada) dengan sprite->Update(deltaTime);.
  * Draw():
    * Jika status kaktus adalah DIE, fungsi langsung keluar (return).
    * Menggambar sprite kaktus dengan sprite->Draw();.
  * SetPosition(float x, float y):
    * Mengatur posisi sprite kaktus menggunakan sprite->SetPosition(x, y);.
    * Mengembalikan this (pointer ke objek Cactus itu sendiri). Ini memungkinkan method chaining.
  * SetSpawn(): Mengatur status kaktus ke SPAWN dan mengembalikan this.
  * GetWidth(): Mengembalikan lebar sprite kaktus menggunakan sprite->GetScaleWidth();.
  * GetHeight(): Mengembalikan tinggi sprite kaktus menggunakan sprite->GetScaleHeight();.
  * IsDie(): Mengembalikan true jika status kaktus adalah DIE, false jika sebaliknya.
  * GetX(): Mengembalikan posisi x sprite kaktus menggunakan sprite->GetPosition().x;.
  * GetY(): Mengembalikan posisi y sprite kaktus menggunakan sprite->GetPosition().y;.
  * GetSprite(): Mengembalikan pointer ke objek Sprite kaktus.
  * SetCactusState(CactusState state): Mengatur state kaktus dan mengembalikan this.
  * GetXVelocity() const: Mengembalikan kecepatan horizontal kaktus (xVelocity).
  * SetXVelocity(float x): Mengatur kecepatan horizontal kaktus (xVelocity).
  
</details>
<details>
  <summary>6. Buat Layar Game Over</summary>

  **Buat File Header DinoGameOverScreen.h**
  
  Berisi variabel-variabel berikut:
  * std::vector<Button*> buttons;: Vektor yang menyimpan pointer ke objek-objek Button. Digunakan untuk mengelola tombol di layar Game Over (misalnya, "Retry", "Main Menu", "Exit").
  * Text* gameOverText;: Pointer ke objek Text yang digunakan untuk menampilkan teks "Game Over".
  * Text* bestScoreText;: Pointer ke objek Text yang digunakan untuk menampilkan skor terbaik.
  * int currentButtonIndex = 0;: Variabel integer yang menyimpan indeks tombol yang sedang dipilih dalam vektor buttons. Nilai 0 menunjukkan tombol pertama.
  * Dino* dino;: Pointer ke objek Dino. Digunakan untuk mengakses informasi seperti skor terbaik dari objek Dino.

  Deklarasikan fungsi yang ada pada DinoGameOverScreen.cpp:
  * DinoGameOverScreen(Dino* dinoInstance);: Konstruktor. Menerima pointer ke objek Dino sebagai argumen.
  * Init() override;: Inisialisasi layar Game Over. Biasanya meliputi pembuatan tombol, teks, dan pengaturan input mapping.
  * Update() override;: Memperbarui logika layar Game Over. Memproses input pemain dan memperbarui status tombol.
  * Draw() override;: Menggambar layar Game Over, termasuk tombol, teks "Game Over", dan skor terbaik.
  * SetBestScoreText();: Fungsi untuk memperbarui teks skor terbaik yang ditampilkan di layar.
  
  **Buat File DinoGameOverScreen.cpp**
  
  Berisi implementasi dari fungsi-fungsi yang dideklarasikan pada DinoGameOverScreen.h:
  * Konstruktor (Engine::DinoGameOverScreen::DinoGameOverScreen(Dino* dinoInstance)):
    * Menerima pointer ke objek Dino sebagai argumen.
    * Menginisialisasi anggota dino dengan pointer yang diterima, memungkinkan akses ke data dan fungsi di kelas Dino (misalnya, skor terbaik).
  * Init():
    * Membuat Tekstur: Membuat objek Texture dari file "buttons2.png".
    * Membuat Sprite untuk Tombol: Membuat objek Sprite untuk setiap tombol ("Retry", "Main Menu", "Exit"), menggunakan tekstur yang telah dimuat. Animasi tombol dikonfigurasi menggunakan SetNumXFrames, SetNumYFrames, AddAnimation, dan SetAnimationDuration.
    * Membuat Tombol:
      * Membuat objek Button untuk setiap tombol, menggunakan sprite yang sesuai.
      * SetPosition digunakan untuk menempatkan tombol di layar. Perhitungan posisi biasanya relatif terhadap ukuran layar.
      * Tombol-tombol ditambahkan ke vektor buttons.
    * Membuat Teks "Game Over": Membuat objek Text untuk menampilkan "Game Over". Font, ukuran font, shader, posisi, dan warna teks diatur.
    * Membuat Teks Skor Terbaik: Membuat objek Text untuk menampilkan skor terbaik. Teks awal diatur menggunakan dino->GetBestScore(). Font, ukuran font, shader, posisi, dan warna teks diatur.
    * Input Mapping: Mendaftarkan tombol panah atas/bawah (SDLK_UP, SDLK_DOWN) untuk navigasi, dan Enter (SDLK_RETURN) untuk memilih tombol.
    * Mengatur Tombol Aktif: currentButtonIndex = 0; Mengatur tombol "Retry" (indeks 0) sebagai tombol aktif awal. Status tombol diubah ke HOVER.
  * Update():
    * Warna Latar Belakang: game->SetBackgroundColor(52, 155, 235); Mengatur warna latar belakang.
    * Memproses Input:
      * Navigasi:
        * if (game->GetInputManager()->IsKeyReleased("next")): Jika tombol "next" (panah bawah) dilepas:
          * Status tombol sebelumnya diubah ke NORMAL.
          * currentButtonIndex diinkrementasi (dengan logika modulo untuk loop melingkar).
          * Status tombol baru diubah ke HOVER.
        * if (game->GetInputManager()->IsKeyReleased("prev")): Logika yang sama untuk tombol "prev" (panah atas), tetapi currentButtonIndex didekrementasi.
      * Memilih Tombol:
        * if (game->GetInputManager()->IsKeyReleased("press")): Jika tombol "press" (Enter) dilepas:
          * Status tombol diubah ke PRESS.
          * Periksa nama tombol:
            * Jika "retry", ganti layar ke "dino" (layar permainan).
            * Jika "mainmenu", ganti layar ke "mainmenu".
            * Jika "exit", keluar dari game.
      * Update Tombol: Memanggil Update() pada setiap tombol untuk memperbarui animasi.
  * Draw():
    * Menggambar Tombol: Loop melalui vektor buttons dan panggil Draw() pada setiap tombol.
    * Menggambar Teks: Menggambar teks "Game Over" dan skor terbaik.
    * SetBestScoreText(): Memperbarui teks skor terbaik dengan memanggil bestScoreText->SetText(...). Fungsi ini menggunakan dino->GetBestScore() untuk mendapatkan skor terbaik terbaru dan menggabungkannya ke dalam string yang akan ditampilkan.
  
</details>
<details>
  <summary>7. Buat Layar Pause</summary>

  **Buat File Header DinoPauseScreen.h**
  
  Berisi variabel-variabel berikut:
  * std::vector<Button*> buttons;: Vektor yang menyimpan pointer ke objek-objek Button. Digunakan untuk mengelola tombol-tombol di layar Pause (misalnya, "Continue", "Main Menu", "Exit").
  * Text* text;: Pointer ke objek Text. Digunakan untuk menampilkan teks "Paused" di layar.
  * int currentButtonIndex = 0;: Variabel integer yang menyimpan indeks tombol yang sedang dipilih dalam vektor buttons. 0 menunjukkan tombol pertama.
  
  Deklarasikan fungsi yang ada pada DinoPauseScreen.cpp:
  * DinoPauseScreen();: Konstruktor default.
  * Init() override;: Fungsi untuk inisialisasi layar Pause. Biasanya meliputi pembuatan tombol, teks, dan pengaturan input mapping. override keyword menandakan fungsi ini meng-override fungsi virtual di base class (Screen).
  * Update() override;: Fungsi yang dipanggil setiap frame untuk memperbarui logika layar Pause. Ini biasanya memproses input pemain (navigasi menu, memilih tombol) dan memperbarui status tombol.
  * Draw() override;: Fungsi yang dipanggil setiap frame untuk menggambar layar Pause. Ini menggambar tombol dan teks "Paused" di layar.
  
  **Buat File DinoPauseScreen.cpp**
  
  Berisi implementasi dari fungsi-fungsi yang dideklarasikan pada DinoPauseScreen.h:
  * Konstruktor (Engine::DinoPauseScreen::DinoPauseScreen()): Menginisialisasi pointer text ke NULL. Ini penting untuk menghindari perilaku yang tidak terdefinisi saat mencoba mengakses pointer sebelum diinisialisasi.
  * Init():
    * Membuat Tekstur: Membuat objek Texture dari file gambar "buttons2.png".
    * Membuat Sprite untuk Tombol: Membuat objek Sprite untuk setiap tombol ("Continue", "Main Menu", "Exit"), menggunakan tekstur yang dimuat. Animasi tombol dikonfigurasi dengan SetNumXFrames, SetNumYFrames, AddAnimation, dan SetAnimationDuration.
    * Membuat Tombol:
      * Membuat objek Button untuk setiap tombol menggunakan sprite yang sesuai.
      * SetPosition digunakan untuk menempatkan tombol di layar. Perhitungan posisi relatif terhadap ukuran layar.
      * Tombol ditambahkan ke vektor buttons.
    * Membuat Teks "Paused": Membuat objek Text untuk menampilkan "Paused". Font, ukuran, shader, posisi, dan warna teks diatur.
    * Input Mapping: Mendaftarkan tombol panah atas/bawah (SDLK_UP, SDLK_DOWN) untuk navigasi, Enter (SDLK_RETURN) untuk memilih tombol, dan Escape (SDLK_ESCAPE) untuk pause/unpause.
    * Tombol Aktif Awal: currentButtonIndex = 0; Mengatur "Continue" (indeks 0) sebagai tombol aktif awal dan mengubah statusnya ke HOVER.
  * Update():
    * Warna Latar Belakang: game->SetBackgroundColor(52, 155, 235); Mengatur warna latar belakang layar.
    * Memproses Input:
      * Navigasi:
        * if (game->GetInputManager()->IsKeyReleased("next")): Jika tombol "next" (panah bawah) dilepas:
          * Status tombol sebelumnya diubah ke NORMAL.
          * currentButtonIndex diinkrementasi (dengan logika modulo untuk loop melingkar).
          * Status tombol baru diubah ke HOVER.
        * if (game->GetInputManager()->IsKeyReleased("prev")): Logika yang sama untuk tombol "prev" (panah atas), tetapi currentButtonIndex didekrementasi.
      * Memilih Tombol:
        * if (game->GetInputManager()->IsKeyReleased("press")): Jika tombol "press" (Enter) dilepas:
          * Status tombol diubah ke PRESS. Periksa nama tombol:
            * Jika "continue", ganti layar ke "dino" (layar permainan).
            * Jika "mainmenu", jalankan GameOver() di DinoGameScreen untuk mereset game, lalu ganti layar ke "mainmenu".
            * Jika "exit", keluar dari game.
      * Tombol Pause:
      * if (game->GetInputManager()->IsKeyReleased("pause")): Jika tombol "pause" (Escape) dilepas, ganti layar ke "dino" untuk melanjutkan permainan. Ini menyediakan cara alternatif untuk unpause selain tombol "Continue".
  * Update Tombol: Memanggil Update() pada setiap tombol untuk memperbarui animasi (misalnya, efek hover).
  * Draw():
    * Menggambar Tombol: Loop melalui vektor buttons dan panggil Draw() pada setiap tombol.
    * Menggambar Teks: Menggambar teks "Paused".
  
</details>
<details>
  <summary>8. Implementasi class yang telah dibuat ke dalam main class Dino</summary>

  isi
  
</details>
<details>
  <summary>9. Testing dan Debugging</summary>

  isi
  
</details>
