#include <Joystick.h>

enum class JoystickMove {None, Up, Down, Left, Right, UpLeft, UpRight, DownLeft, DownRight};
JoystickMove move = JoystickMove::None;
Joystick joystick(A0, A1, 5);

void joystick_setup() {
  joystick.initialize();
  joystick.setSensivity(0);
}

void joystick_moveUpd() {
  if (joystick.isUpperLeft() || joystick.isUpperRight() || joystick.isLowerLeft() || joystick.isLowerRight() || joystick.isLeft() || joystick.isRight() || joystick.isUp() || joystick.isDown()) {
    if (joystick.isUpperLeft() || joystick.isUpperRight() || joystick.isLowerLeft() || joystick.isLowerRight()) {
      if (joystick.isUpperLeft()) {move = JoystickMove::UpRight;}
      if (joystick.isUpperRight()) {move = JoystickMove::DownRight;}
      if (joystick.isLowerLeft()) {move = JoystickMove::UpLeft;}
      if (joystick.isLowerRight()) {move = JoystickMove::DownLeft;}
    } else {
      if (joystick.isLeft()) {move = JoystickMove::Up;}
      if (joystick.isRight()) {move = JoystickMove::Down;}
      if (joystick.isUp()) {move = JoystickMove::Right;}
      if (joystick.isDown()) {move = JoystickMove::Left;}
    }
  } else {
    move = JoystickMove::None;
  }
}
