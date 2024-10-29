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
</details>
<details>
  <summary>2. Buat Main Class Dino</summary>
</details>
<details>
  <summary>3. Buat Layar Main Menu</summary>
</details>
<details>
  <summary>4. Buat Layar Permainan</summary>
</details>
<details>
  <summary>5. Buat Class Cactus sebagai rintangan</summary>
</details>
<details>
  <summary>6. Buat Layar Game Over</summary>
</details>
<details>
  <summary>7. Buat Layar Pause</summary>
</details>
<details>
  <summary>8. Implementasi class yang telah dibuat ke dalam main class Dino</summary>
</details>
<details>
  <summary>9. Testing dan Debugging</summary>
</details>
