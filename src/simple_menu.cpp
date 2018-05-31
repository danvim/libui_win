//
// Created by Daniel on 15/3/2018.
//

#include "simple_menu.h"

void SimpleMenu::run() {
    //
    // Prepare UI
    //

    ui::fonts::Humanist humanist;
    ui::fonts::Blocky blocky;

    if (ui::Context::getContext() == nullptr) {
        auto* context_adapter = new adapters::ContextAdapter;
        ui::Context::attachAdapter(context_adapter);

        adapters::ScreenAdapter* screen_adapter = adapters::ContextAdapter::screen_adapter_ptr = new adapters::ScreenAdapter;
        adapters::BatteryMeterAdapter* battery_meter_adapter = adapters::ContextAdapter::battery_meter_adapter_ptr = new adapters::BatteryMeterAdapter;

        screen_adapter->console_ptr = GetConsoleWindow();
        screen_adapter->context_ptr = GetDC(screen_adapter->console_ptr);

        ui::Context::prepareListenerEvents();

        ui::Context::setGUIRotation(ui::adapters::ContextAdapterInterface::QUARTER_CCW);
    }

    ui::Context::addFontToRepo("Humanist", &humanist);
    ui::Context::addFontToRepo("Blocky", &blocky);

    ui::Context::setColorScheme([](){
        ui::color_schemes::Futurism color_scheme;
        return color_scheme;
    }());


    //
    // Initialize Menu Group
    //

    ui::MenuGroup menu_group("Startup Menu");
    menu_group.setHasBackArrow(false);

    class RunAction: public ui::MenuAction {
    public:
        explicit RunAction(ui::MenuGroup* menu_group_ptr): menu_group_ptr(menu_group_ptr) {
            this->setName("Run");
        }
        int run() override {
            menu_group_ptr->exitMenu();
            return SUCCESS;
        }

    private:
        ui::MenuGroup* menu_group_ptr;
    };

    RunAction run_action(&menu_group);
    ui::MenuNumber<int> menu_number;
    menu_number.setName("Select number");
    menu_number.setValue(0);
    menu_number.setStep(1);

    //
    // Add items to menu_group
    //

    menu_group.addMenuAction(&run_action);
    menu_group.addMenuAction(&menu_number);


    //
    // Enter menu and its render loop.
    // The code will continue when the user hits the "Run" option, which exits the menu.
    //

    menu_group.run();


    //
    // Clean removal of fonts to save memory
    //

    ui::Context::removeFontFromRepo("Humanist");
    ui::Context::removeFontFromRepo("Blocky");
}
