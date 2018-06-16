//
// Created by Daniel on 11/6/2018.
//

#include "adapters/application.h"

void Application::init() {
    //
    // Prepare UI
    //

    if (ui::Context::getContext() == nullptr) {
        context_adapter_ptr = new adapters::ContextAdapter;
        ui::Context::attachAdapter(context_adapter_ptr);

        screen_adapter_ptr = adapters::ContextAdapter::screen_adapter_ptr = new adapters::ScreenAdapter;
        battery_meter_adapter_ptr = adapters::ContextAdapter::battery_meter_adapter_ptr = new adapters::BatteryMeterAdapter;

        screen_adapter_ptr->console_ptr = GetConsoleWindow();
        screen_adapter_ptr->context_ptr = GetDC(screen_adapter_ptr->console_ptr);

        ui::Context::prepareListenerEvents();

        ui::Context::setGUIRotation(ui::adapters::ContextAdapterInterface::QUARTER_CCW);
    }

    ui::Context::addFontToRepo("Humanist", &humanist);
    ui::Context::addFontToRepo("Blocky", &blocky);
}

void Application::done() {
    //
    // Clean removal of fonts to save memory
    //

    ui::Context::removeFontFromRepo("Humanist");
    ui::Context::removeFontFromRepo("Blocky");
}

void Application::run() {
    init();
    start();
    done();
}