#include <vector>
#include "raylib.h"

using namespace std;

struct Peluru{
    Rectangle kotak;
    float arah; // 1=kanan, -1=kiri
};

int main (){
    const int lebarL=800;
    const int tinggiL=400;
    InitWindow(lebarL,tinggiL, "Belajar Logika facing");
    SetTargetFPS(60);

    // pemain/player
    Rectangle pemain ={400,300, 40, 40};
    float kecepatanP=4.0f;
    // kunci arah pemain
    float arahHadap=1.0f;
    // khas c++ wadahnya yang dinamis
    vector<Peluru> daftarPeluru;
    float speedPeluru =8.0f;
    while(!WindowShouldClose()){
        // logika gerak
        if(IsKeyDown(KEY_D)){
            pemain.x += kecepatanP;
            arahHadap=1.0f;
        }
        if(IsKeyDown(KEY_A)){
            pemain.x -=kecepatanP;
            arahHadap =-1.0f;
        }
        if(IsKeyDown(KEY_W)) pemain.y -= kecepatanP;
        if(IsKeyDown(KEY_S)) pemain.y += kecepatanP;

        // logika mentok kanan dan kiri
        if(pemain.x <0) pemain.x = 0;
        if(pemain.x>lebarL -pemain.width) pemain.x =lebarL- pemain.width;

        // logika mentok atas dan bawah
        if(pemain.y < 0) pemain.y =0;
        if(pemain.y > tinggiL -pemain.height){
            pemain.y =tinggiL-pemain.height;
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)|| IsKeyPressed(KEY_SPACE)){
            // racik peluru baru tepat ditengah posisi pemain saat ini
            Peluru peluruBaru;
            peluruBaru.kotak = {pemain.x +15, pemain.y +15, 10, 10};
            peluruBaru.arah =arahHadap;

            daftarPeluru.push_back(peluruBaru);
        }

        auto it =daftarPeluru.begin();
        while(it != daftarPeluru.end()){
           it->kotak.x += speedPeluru * it->arah;
        // jika peluru keluar dari layar, akan dihapus dari RAM
            if(it->kotak.x>lebarL || it->kotak.x <0){
                it=daftarPeluru.erase(it);
            }else{
                it++;
                }
            }
         
        BeginDrawing();
            ClearBackground(RAYWHITE);
                 DrawRectangleRec(pemain, BLUE);
                // gambar indikator arah hadap kecil didepan layar
                if(arahHadap == 1.0f) DrawRectangle(pemain.x + 35, pemain.y + 15, 5, 10, BLACK);
                else DrawRectangle(pemain.x, pemain.y + 15, 5, 10, BLACK);
                // gambar semua peluru yang sedang aktif (kuning)
                for(const auto& p:daftarPeluru){
                    DrawRectangleRec(p.kotak, GOLD);
                }
                // HUD INFO
                DrawText("'TEKAN SPACE / KLIK KIRI UNTUK MENEMBAK'", 20,20,20, DARKGRAY);
                DrawText(TextFormat("peluru aktif di memori: %d", daftarPeluru.size()), 20, 50, 18, RED);
            EndDrawing();
    }
        CloseWindow();
        return 0;
}