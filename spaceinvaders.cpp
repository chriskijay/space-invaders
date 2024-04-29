#include "raylib.h"
#include <vector>
#include <iostream>

struct ship {
  Vector2 pos;
  int speed;
  Vector2 size;
  bool alive;
};

struct invader {
  Vector2 pos;
  int speed;
  Vector2 size;
  float alive;
};

struct projectile {
  Vector2 pos;
  int speed;
  float live;
  Vector2 size;
};

int x = 12;
int y = 5;
int n = 0;
int tick = 0;
int tick_counter = 0;
int tickmove;
int tickshoot = 0;

std::vector<Vector3> projvector;

int main(void) {
  
  SetTargetFPS(60);  
  
  const int screenWidth = 640;
  const int screenHeight = 480;
  InitWindow(screenWidth, screenHeight, "demo");

  ship player;
  player.speed = 4;
  player.pos = (Vector2){ 0, screenHeight - 32};
  player.size = (Vector2){ 16, 16};
  player.alive = true;
  
  invader alien;
  alien.pos = (Vector2){ 64, 50};
  alien.size = (Vector2){ 16, 16};
  alien.alive = 1;
  alien.speed = 16;

  projectile proj;
  proj.live = 1;
  proj.size = (Vector2){6,8};
  proj.speed = 4;
  proj.pos = (Vector2){0,0};

  Vector3 projvarname;

  int p = 0;
  //Vector3 alienvarname;
  Vector3 alienvarname = {alien.pos.x, alien.pos.y, alien.alive};
  Vector3 alienarray[64] = { alienvarname };

  int i;
  int pi;

  for (i = 0; i < x * y; i += 1) {
    alienarray[i] = alienvarname;
  };

  int c;
  int r;
  i = 1;
  while ( i < x * y ){
    c = i;
    r = 0;
    while (c - x * y / y >= 0) {
      c -= x * y / y;
      r += 1;
    }
      alienarray[i].x = alienarray[0].x + 2 * c * alien.size.x;
      alienarray[i].y = alienarray[0].y + 2 * r * alien.size.y;
    std::cout<<i<<'\n';
    i += 1;
  }

  bool moveright = true;
  //bool moveleft = false;
  
      //for (i = 1; i < x * y; i += 1) {
        //if (i < x * y / y) {
          //alienarray[i].x = alienarray[0].x + 2 * i * alien.size.x;
    //} else {  
      //    alienarray[i].x = alienarray[0].x + 2 * (i - x * y / y) * alien.size.x;
        //  alienarray[i].y = alienarray[0].y + 2 * alien.size.y;
    //}
          //}
  
  
  while (!WindowShouldClose())
  {

    if(IsKeyDown(KEY_A)) {
      player.pos.x -= player.speed;
    }

    if(IsKeyDown(KEY_D)) {
      player.pos.x += player.speed;
    }        

    if(IsKeyPressed(KEY_SPACE)) {
      projvarname = (Vector3){player.pos.x, player.pos.y, proj.live};
      projvector.emplace(projvector.begin(),projvarname);
      p += 1;
        std::cout <<projvector.size()<<'\n';
    }
   
    //pi = 0;
    //i = 0;
    for(pi = 0; pi < p; pi += 1){
      if (projvector[pi].z == 1) {
        if (projvector[pi].y < alienarray[x * y - 1].y + alien.size.y && projvector[pi].x + proj.size.x > alienarray[0].x && projvector[pi].x < alienarray[x * y - 1].x + alien.size.x) {
          for(i = 0; i < x * y; i += 1){
           // for (i = 0; i < y; i += 1) {
              if (alienarray[i].z == 1) {
                if (projvector[pi].y < alienarray[i].y + alien.size.y && projvector[pi].x + proj.size.x > alienarray[i].x && projvector[pi].x < alienarray[i].x + alien.size.x) {
                  alienarray[i].z = 0;
                  projvector[pi].z = 0;
                }
              }
              
            //}
          }   
        }
       }   //projvector[pi].z = 0;
      }

    tick += 1;
    if (tick > 50) {
      tick_counter += 1;
      tick = 0;
    }

    tickmove = 40;

    if (moveright == true && tick == tickmove) {
      for (i = 0; i < x * y; i += 1) {
        alienarray[i].x += alien.speed;
        if (alienarray[x * y -1].x >= screenWidth - 2 * alien.size.x){
      //    alienarray[i].x -= alien.speed;
          for (i = 0; i < x * y; i += 1) {
            alienarray[i].x -= alien.speed;
            moveright = false;
          }
          //moveright = false;
        }
      }
        std::cout<<tick_counter<<'\n';
    }

    //if (alienarray[x * y - 1].x >= screenWidth ) {
      //moveright = false;
    //}

    //if (alienarray[0].x > screenWidth - 300) {
    //  moveright = false;
    //}

    if (moveright == false && tick == tickmove) {
      for (i = 0; i < x * y; i += 1) {
        alienarray[i].x -= alien.speed;
        if (alienarray[0].x <= 2 * alien.size.x) {
          moveright = true;
        }
      }
        std::cout<<tick_counter<<'\n';
    }

    tickshoot += 1;

    if (tickshoot > 50) {
      //insert array for alien shooting
      tickshoot = 0;        
    }
    //if (alienarray[0].x <= 2 * alien.size.x) {
      //moveright = true;
    //}

      ClearBackground(DARKBLUE);
      DrawFPS(10,10);
      DrawRectangle(player.pos.x, player.pos.y, player.size.x, player.size.y, LIGHTGRAY); //Player render
      //DrawRectangle(alien.pos.x, alien.pos.y, alien.size.x, alien.size.y, PINK); //Alien render

      //for (y = 0; y < 3; y+=1) {
        //for (x = 0; x < 4; x+=1) {
      //DrawRectangle(alien.pos.x + alien.size.x * x, alien.pos.y + alien.size.y * y, alien.size.x, alien.size.y, PURPLE);
        //}  
      //}

      //i=0;//rows
      //n = 0;//columns
    //for (n = 0; n < 2; n += 1) {
    for(i = 0; i < x * y; i += 1) {
        if (alienarray[i].z == 1) {
          DrawRectangle(alienarray[i].x,
                        alienarray[i].y, alien.size.x,
                        alien.size.y, PURPLE);
        }
    }

    
    //pi = 0;
    for(pi = 0; pi < p; pi += 1){
        if (projvector[pi].z == 1) {
          DrawRectangle(projvector[pi].x,projvector[pi].y,proj.size.x,proj.size.y,RED);
        }  
        projvector[pi].y -= proj.speed;
        if(projvector[pi].y < 0) {
          projvector.pop_back();
          p -= 1;
          std::cout <<projvector.size()<<'\n';
        }
    }

        EndDrawing();

  }

  CloseWindow();
  return 0;
};

