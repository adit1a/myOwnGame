#include <vector>
#include "raylib.h"
#include <cstdlib>
#include <ctime>

using namespace std;

struct Peluru{
    Rectangle kotak;
    float arah; // 1=kanan, -1=kiri
};

int main (){
    const int lebarL=800;
    const int tinggiL=400;
    InitWindow(lebarL,tinggiL, "OwnGame");
    SetTargetFPS(60);

    srand(time(0));

    // pemain/player
    Rectangle pemain ={400,300, 40, 40};
    float kecepatanP=4.0f;
    // kunci arah pemain
    float arahHadap=1.0f;
    int skorBantai = 0; // skor membunuh musuh
    // khas c++ wadahnya yang dinamis
    vector<Peluru> daftarPeluru;
    float speedPeluru =8.0f;
    // menambahkan musuh
    Rectangle musuh={800, 200, 40, 40};
    float kecepatanM=3.0f;

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
        //logika ketika peluru bertabrakan
            if(CheckCollisionRecs(it->kotak, musuh)){
                skorBantai += 1;
                musuh.x =lebarL;
                musuh.y = rand() %(tinggiL-60)+20;
                it = daftarPeluru.erase(it);
            }else if (it->kotak.x>lebarL || it->kotak.x <0){
                it = daftarPeluru.erase(it);
            }else{
                it++;
            }
        }
            // logika jika peluru peluru menabrak musuh
            if(CheckCollisionRecs(musuh, pemain)){
                //untuk mereset player jika kalah
                pemain.x = 100;
                pemain.y = 200;
                // reset musuh juga
                musuh.x =lebarL;
                musuh.y = rand() % (tinggiL -60 )+ 20;
            }
            musuh.x-=kecepatanM;
            if(musuh.x < -musuh.width){
                musuh.x =lebarL;

                musuh.y = rand() % (tinggiL-60)+20;
            }
         
        BeginDrawing();
            ClearBackground(RAYWHITE);
                 DrawRectangleRec(pemain, BLUE);
                // gambar indikator arah hadap kecil didepan layar
                DrawRectangleRec(musuh, RED);
                if(arahHadap == 1.0f) DrawRectangle(pemain.x + 35, pemain.y + 15, 5, 10, BLACK);
                else DrawRectangle(pemain.x, pemain.y + 15, 5, 10, BLACK);
                // gambar semua peluru yang sedang aktif (kuning)
                for(const auto& p:daftarPeluru){
                    DrawRectangleRec(p.kotak, GOLD);
                }
                // HUD INFO
                DrawText(TextFormat("MUSUH DI BANTAI : %d", skorBantai), 20, 20, 22, RED );
                DrawText("Tembak Kotak Merah sebelum di menabrakmu", 20, 360, 18, GRAY);
            EndDrawing();
    }
        CloseWindow();
        return 0;
        
}
        
