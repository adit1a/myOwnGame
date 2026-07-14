#include "raylib.h"

// ========================================================
// 1. CLASS PLAYER (CETAKAN KARAKTER)
// ========================================================
class player {
    private:
        Rectangle kotak;
        float kecepatanX;
        float kecepatanY;
        float gravitasi;
        float powerLompat;
        bool apakahDiTanah; 
    public:
        player(float awalX, float awalY){
            kotak = {awalX, awalY, 40, 40};
            kecepatanX = 5.0f;
            kecepatanY = 0.0f;
            gravitasi = 0.5f;
            powerLompat = -12.0f;
            apakahDiTanah = false;
        }   
        void update(Rectangle tanah, int lebarSekarang, int tinggiSekarang){
         // 1. Logika gerak horizontal
    if(IsKeyDown(KEY_D)) kotak.x += kecepatanX;
    if(IsKeyDown(KEY_A)) kotak.x -= kecepatanX; 
    
    // 2. LOGIKA FIX BUG: Memaksa Mario kembali masuk jika terlempar keluar layar akibat ganti resolusi
    if(kotak.x < 0) kotak.x = 0;
    if(kotak.x > lebarSekarang - kotak.width) kotak.x = lebarSekarang - kotak.width;
    
    if(kotak.y < 0) kotak.y = 0;
    if(kotak.y > tinggiSekarang - kotak.height) kotak.y = tinggiSekarang - kotak.height;

    // 3. Logika gravitasi
    kecepatanY += gravitasi;
    kotak.y += kecepatanY;
    
    // 4. Logika deteksi tabrakan tanah
    if(CheckCollisionRecs(kotak, tanah)){
        kotak.y = tanah.y - kotak.height;
        kecepatanY = 0;
        apakahDiTanah = true; 
    } else {
        apakahDiTanah = false;
    }
    
    // 5. Logika lompat
    if(IsKeyPressed(KEY_SPACE) && apakahDiTanah){
        kecepatanY = powerLompat;
        apakahDiTanah = false;
    }
}
        void Draw(){
            DrawRectangleRec(kotak, BLUE);
        }
        
        bool GetsdgLompat(){
            return apakahDiTanah;
        }
};

// ========================================================
// 2. FUNGSI UTAMA GAME (MAIN FUNCTION)
// ========================================================
int main () {
    // Ukuran Jendela Awal (Windowed Mode)
    const int lebarL = 800;
    const int tinggiL = 400;
    InitWindow(lebarL, tinggiL, "Belajar Platformer OOP - Screen Mode");
    SetTargetFPS(60);
    
    player mario(100, 200);

    // Warna interaktif untuk tombol
    Color warnaTombol = LIGHTGRAY;

    while (!WindowShouldClose()){
        // Mendapatkan lebar dan tinggi layar secara aktual/real-time (Penting saat mode berubah!)
        int lebarSekarang = GetScreenWidth();
        int tinggiSekarang = GetScreenHeight();

        // Membuat tanah dinamis agar melebar otomatis saat fullscreen
        // Posisi Y disesuaikan dengan tinggi layar saat itu dikurangi 40
        Rectangle tanah = {0, (float)tinggiSekarang - 40, (float)lebarSekarang, 40};

        // Mengupdate posisi player menggunakan ukuran lebar layar aktual
        mario.update(tanah, lebarSekarang, tinggiSekarang);

        // ========================================================
        // --- LOGIKA TOMBOL FULLSCREEN WINDOWED (DIPERBAIKI DINAMIS) ---
        // ========================================================
        // Koordinat X ditaruh di (Lebar Layar Aktual - 140) agar selalu di pojok kanan atas
        Rectangle tombolScreen = { (float)lebarSekarang - 140, 20, 120, 30 };
        Vector2 posisiMouse = GetMousePosition();

        // Cek interaksi mouse dengan tombol
        if (CheckCollisionPointRec(posisiMouse, tombolScreen)) {
            warnaTombol = GRAY; // Efek hover
            
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                // FUNGSI SAKTI: Mengubah ke Borderless Windowed secara bolak-balik
                ToggleBorderlessWindowed(); 
            }
        } else {
            warnaTombol = LIGHTGRAY;
        }
        // ========================================================

        // --- PROSES GAMBAR VISUAL ---
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            // Gambar tanah dinamis
            DrawRectangleRec(tanah, GREEN);
            
            // Gambar Player
            mario.Draw();
            
            // --- GAMBAR UTAS TOMBOL SCREEN ---
            DrawRectangleRec(tombolScreen, warnaTombol);
            DrawRectangleLinesEx(tombolScreen, 1, DARKGRAY);
            DrawText("FULLSCREEN", tombolScreen.x + 12, tombolScreen.y + 8, 14, BLACK);

            // HUD INFO
            DrawText("Kontrol: A/D, SPACE (Lompat)", 20, 20, 20, DARKGRAY);
            DrawText(mario.GetsdgLompat() ? "Status: Di Tanah" : "Status: Melayang", 20, 50, 18, ORANGE);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}