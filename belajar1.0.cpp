#include <vector>
#include <iostream>
#include "raylib.h"

using namespace std;

int main() {
    InitWindow(800, 600, "Let Him Cook - Arena Pertarungan C++");
    SetTargetFPS(60);

    // Fitur C++ murni: std::vector untuk menampung data objek secara dinamis
    vector<Rectangle> targetMusuh;
    targetMusuh.push_back({ 400, 300, 50, 50 });

    while (!WindowShouldClose()) {
        
        // Logika C++ modern untuk mengecek data di dalam vector
        if (!targetMusuh.empty()) {
            // Siap memasak bos/musuh di sini
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("MODE COOKING AKTIF: 100% C++", 20, 20, 20, DARKGRAY);
            
            for (const auto& musuh : targetMusuh) {
                DrawRectangleRec(musuh, RED);
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}