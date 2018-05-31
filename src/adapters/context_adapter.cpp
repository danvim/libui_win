//
// Created by Daniel on 29/5/2018.
//

#include <iostream>
#include <chrono>
#include <future>
#include <thread>
#include "adapters/context_adapter.h"

namespace adapters {
    adapters::ScreenAdapter* ContextAdapter::screen_adapter_ptr = nullptr;
    adapters::JoystickAdapter* ContextAdapter::joystick_adapter_ptr = nullptr;
    adapters::BatteryMeterAdapter* ContextAdapter::battery_meter_adapter_ptr = nullptr;

    void ContextAdapter::prepareListenerEvents() {
        SetConsoleTitle("LibUI for Windows");

        HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
        HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

        DWORD prevMode;
        GetConsoleMode(input, &prevMode);

        SetConsoleMode(input, prevMode & ~ENABLE_QUICK_EDIT_MODE);

        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(output, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(output, &cursorInfo);

        std::thread listener_thread([input](){
            INPUT_RECORD irInBuf[128];
            DWORD cNumRead, fdwMode, fdwSaveOldMode, i;
            fdwMode = ENABLE_WINDOW_INPUT;
            GetConsoleMode(input, &fdwSaveOldMode);
            SetConsoleMode(input, fdwMode);

            while (ContextAdapter::running_menu) {
                if (WaitForSingleObject(input, 50) == WAIT_OBJECT_0) {
                    if (!ReadConsoleInput(input, irInBuf, 128, &cNumRead))
                        continue;

                    for (i = 0; i < cNumRead; i++) {
                        auto input_record = irInBuf[i];
                        if (input_record.EventType == KEY_EVENT && input_record.Event.KeyEvent.wRepeatCount == 1) {
                            ContextAdapter::joystick_listeners_dispatcher(input_record.Event.KeyEvent);
                        }
                    }
                }
            }


            SetConsoleMode(input, fdwSaveOldMode);
        });

        listener_thread.detach();
    }

    std::function<void(KEY_EVENT_RECORD)> ContextAdapter::joystick_listeners_dispatcher = [](KEY_EVENT_RECORD record) {
        ui::E::Config e;
        e.JOYSTICK_ID = 0;
        e.IS_JOYSTICK_DOWN = (bool) record.bKeyDown;
        switch (record.wVirtualKeyCode) {
            case VK_UP:
                e.JOYSTICK_STATE = ui::JoystickState::UP;
                break;
            case VK_DOWN:
                e.JOYSTICK_STATE = ui::JoystickState::DOWN;
                break;
            case VK_LEFT:
                e.JOYSTICK_STATE = ui::JoystickState::LEFT;
                break;
            case VK_RIGHT:
                e.JOYSTICK_STATE = ui::JoystickState::RIGHT;
                break;
            case VK_RETURN:
                e.JOYSTICK_STATE = ui::JoystickState::SELECT;
                break;
            default:
                e.JOYSTICK_STATE = ui::JoystickState::IDLE;
                break;
        }

        ui::Context::triggerListeners(record.bKeyDown ? ui::Event::JOYSTICK_DOWN : ui::Event::JOYSTICK_UP, ui::E(e));
    };

    ui::adapters::ScreenAdapterInterface* ContextAdapter::getScreen() {
        return screen_adapter_ptr;
    }

    ui::adapters::JoystickAdapterInterface* ContextAdapter::getJoystick() {
        return joystick_adapter_ptr;
    }

    ui::adapters::BatteryMeterAdapterInterface *ContextAdapter::getBatteryMeter() {
        return battery_meter_adapter_ptr;
    }

    void ContextAdapter::setGUIRotation(ui::adapters::ContextAdapterInterface::RotationalChange rotational_change) {

    }

    uint32_t ContextAdapter::getSystemTime() {
        return (uint32_t) time(nullptr);
    }

    bool ContextAdapter::running_menu = true;
}