enum GameState {MENU, SIMON, DRAWING, JOKE, FLAPPY, DINO, X2048, PONG, SNAKE};
GameState gameRunning = MENU;
#include "start_setup.h"
#include "graphics.h"
#include "joystick_movement.h"
#include "game_menu.h"
#include "simon_game.h"
#include "drawing_game.h"
#include "joking_app.h"
#include "flappy_game.h"
#include "dino_game.h"
#include "x2048_game.h"
#include "pong_game.h"
#include "snake_game.h"

void setup() {
  randomSeed(analogRead(7));
  joystick_setup();
  screen_setup();
}

void loop() {
  joystick_moveUpd();
  if (gameRunning == MENU) {
    menu_loop();
  } else if (gameRunning == SIMON) {
    simon_loop();
  } else if (gameRunning == DRAWING) {
    draw_loop();
  } else if (gameRunning == JOKE) {
    joke_loop();
  } else if (gameRunning == FLAPPY) {
    flappy_loop();
  } else if (gameRunning == DINO) {
    dino_loop();
  } else if (gameRunning == X2048) {
    x2048_loop();
  } else if (gameRunning == PONG) {
    pong_loop();
  } else if (gameRunning == SNAKE) {
    snake_loop();
  }
}
