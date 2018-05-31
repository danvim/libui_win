![libui_logo_trim](libui_logo_trim.png)

# LibUI for Windows

This is an example implementation of LibUI on Windows, following requirements in LibUI, to implement required adapters to connect  with`windows.h` API in creating a GDI application.

The example project has a `SimpleMenu` class to run a simple menu. And the implemented adapters are as follow:

- `adapters::ContextAdapter`
  Completes the logic for `ui::Context`.

- `adapters::JoystickAdapter`
  Keyboard inputs will substitute the 5-way switch inputs:

  - Arrow Up: Up
  - Arrow Down: Down
  - Arrow Left: Left
  - Arrow Right: Right
  - Enter: Select
  - Any other key: Idle (Dummy input. No practical usages)

- `adapters::ScreenAdapter`
  Draws in the application screen. Two parameters are added: `offset_x`, `scaling`

- `adapters::BatteryMeterAdapter`

  A dummy adapter that always return `9.9f` as voltage.

## Compiling

You are required to obtain a `libui.a` statically linked library from the LibUI repo, and put that within `./lib/libui.a`. You are also required to change the library include path to that in your cloned LibUI directory.