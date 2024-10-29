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
  <summary>2. Buat Main Class Dino</summary>

  isi
  
</details>
<details>
  <summary>3. Buat Layar Main Menu</summary>

  isi
  
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

  isi
  
</details>
<details>
  <summary>6. Buat Layar Game Over</summary>

  isi
  
</details>
<details>
  <summary>7. Buat Layar Pause</summary>

  isi
  
</details>
<details>
  <summary>8. Implementasi class yang telah dibuat ke dalam main class Dino</summary>

  isi
  
</details>
<details>
  <summary>9. Testing dan Debugging</summary>

  isi
  
</details>
