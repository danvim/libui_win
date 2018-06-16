//
// Created by Daniel on 11/6/2018.
//

#ifndef LIBUI_WIN_APPLICATION_H
#define LIBUI_WIN_APPLICATION_H

#include <ui/application_interface.h>
#include <ui/fonts/humanist.h>
#include <ui/fonts/blocky.h>
#include <ui/context.h>
#include <adapters/context_adapter.h>

class Application: public virtual ui::ApplicationInterface {
public:
    void init() override;

    void done() override;

    void run() override;

protected:
    ui::fonts::Humanist humanist;
    ui::fonts::Blocky blocky;
    adapters::ContextAdapter* context_adapter_ptr = nullptr;
    adapters::ScreenAdapter* screen_adapter_ptr = nullptr;
    adapters::BatteryMeterAdapter* battery_meter_adapter_ptr = nullptr;
    adapters::JoystickAdapter* joystick_adapter_ptr = nullptr;
};


#endif //LIBUI_WIN_APPLICATION_H
