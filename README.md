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

  Deklarasikan fungsi yang ada pada DinoMainMenuScreen.cpp:
  
  **Buat File DinoMainMenuScreen.cpp**
  
  Berisi implementasi dari fungsi-fungsi yang dideklarasikan pada DinoMainMenuScreen.h:
  
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

  Deklarasikan fungsi yang ada pada Cactus.cpp:
  
  **Buat File Cactus.cpp**
  
  Berisi implementasi dari fungsi-fungsi yang dideklarasikan pada Cactus.h:
  
</details>
<details>
  <summary>6. Buat Layar Game Over</summary>

  **Buat File Header DinoGameOverScreen.h**
  
  Berisi variabel-variabel berikut:

  Deklarasikan fungsi yang ada pada DinoGameOverScreen.cpp:
  
  **Buat File DinoGameOverScreen.cpp**
  
  Berisi implementasi dari fungsi-fungsi yang dideklarasikan pada DinoGameOverScreen.h:
  
</details>
<details>
  <summary>7. Buat Layar Pause</summary>

  **Buat File Header DinoPauseScreen.h**
  
  Berisi variabel-variabel berikut:

  Deklarasikan fungsi yang ada pada DinoPauseScreen.cpp:
  
  **Buat File DinoPauseScreen.cpp**
  
  Berisi implementasi dari fungsi-fungsi yang dideklarasikan pada DinoPauseScreen.h:
  
</details>
<details>
  <summary>8. Implementasi class yang telah dibuat ke dalam main class Dino</summary>

  isi
  
</details>
<details>
  <summary>9. Testing dan Debugging</summary>

  isi
  
</details>
