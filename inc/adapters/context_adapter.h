//
// Created by Daniel on 29/5/2018.
//

#ifndef LIBUI_LIBSCCC_CONTEXT_ADAPTER_H
#define LIBUI_LIBSCCC_CONTEXT_ADAPTER_H


#include <ui/adapters/context_adapters/context_adapter_interface.h>

#include <ui/context.h>
#include <ui/color_schemes/color_scheme.h>
#include <ui/ui_base.h>
#include <ui/e.h>
#include <ui/font.h>
#include <map>
#include <functional>
#include "screen_adapter.h"
#include "battery_meter_adapter.h"
#include "joystick_adapter.h"
#include <wincon.h>
#include <thread>
#include <chrono>

namespace adapters {
    class ContextAdapter: public virtual ui::adapters::ContextAdapterInterface {
    public:
        ui::adapters::ScreenAdapterInterface* getScreen() override;
        ui::adapters::JoystickAdapterInterface* getJoystick() override;
        ui::adapters::BatteryMeterAdapterInterface* getBatteryMeter() override;
        void setGUIRotation(RotationalChange rotational_change) override;

        static adapters::ScreenAdapter* screen_adapter_ptr;
        static adapters::BatteryMeterAdapter* battery_meter_adapter_ptr;
        static adapters::JoystickAdapter* joystick_adapter_ptr;

        /**
         * Prepares listener relays.
         *
         * Caution! This will delete and re-instantiate various peripheral pointers.
         */
        void prepareListenerEvents() override;

        uint32_t getSystemTime() override;

        void remapJoystickDirections(ui::JoystickState up, ui::JoystickState down, ui::JoystickState left,
                                     ui::JoystickState right, ui::JoystickState select,
                                     ui::JoystickState idle) override;

        static std::function<void(KEY_EVENT_RECORD)> joystick_listeners_dispatcher;

        static bool running_menu;
    };
}


#endif //LIBUI_LIBSCCC_CONTEXT_ADAPTER_H
