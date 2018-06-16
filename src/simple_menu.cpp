//
// Created by Daniel on 15/3/2018.
//

#include "simple_menu.h"

void SimpleMenu::start() {
    //
    // Initialize Menu Group
    //

    ui::MenuGroup menu_group("LibUI Win");
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
    } run_action(&menu_group);

    ui::MenuNumber<int> menu_number;
    menu_number.setName("Select number");
    menu_number.setValue(0);
    menu_number.setStep(1);

    class ImagePreviewAction: public ui::MenuAction {
    public:
        ImagePreviewAction() {
            this->setName("Image Preview");

            //Generate image
            uint16_t i = 0;
            for (uint16_t y = 0; y < h; y++) {
                for (uint16_t x = 0; x < w; x++) {
                    ui::ColorUtil::HSV hsv((double) x/w, (double) y/h, 1);
                    image[i] = hsv.toRGB565();
                    i++;
                }
            }
        }

        int run() override {
            auto* screen_ptr = ui::Context::getScreen();

            //Change screen
            screen_ptr->setRegion(0, 0, screen_ptr->getWidth(), screen_ptr->getHeight());
            screen_ptr->fill(ui::Context::color_scheme.GRAY_DARKER);

            ui::Toolbar toolbar;
            toolbar.setHasBackArrow(false);
            toolbar.setName("Image Preview");
            toolbar.setRegion(0, 0, 128, 16); //actual viewport 128x*120y
            toolbar.render();

            //Render loop
            uint32_t time = ui::Context::getSystemTime();

            bool is_exit = false;
            uint16_t offset_x = 0;

            std::function<ui::ColorUtil::RGB565(uint16_t x, uint16_t y)> getXY = [&](uint16_t x, uint16_t y){
                return image[(x) + (y) * 189];
            };

            std::function<void()> redraw = [&](){
                for (uint16_t y = 0; y < 120; y++) {
                    for (uint16_t x = 0; x < 128; x++) {
                        screen_ptr->setRegion({(uint32_t) (x), (uint32_t) (18 + y), 1, 1});
                        screen_ptr->fill(getXY(x + offset_x, y));
                    }
                }
            };

            std::function<void(ui::E&)> joystick_handler = [&](ui::E& e){
                if (e.JOYSTICK_STATE == ui::JoystickState::SELECT) {
                    is_exit = true;
                } else if (e.JOYSTICK_STATE == ui::JoystickState::LEFT) {
                    offset_x = (uint16_t) std::max(0, offset_x - 10);
                    redraw();
                } else if (e.JOYSTICK_STATE == ui::JoystickState::RIGHT) {
                    offset_x = (uint16_t) std::min(189 - 128, offset_x + 10);
                    redraw();
                }
                e.consume();
            };

            ui::Context::addEventListener(ui::Event::JOYSTICK_DOWN, &joystick_handler);

            redraw();

            while (!is_exit) {}

            ui::Context::removeEventListener(ui::Event::JOYSTICK_DOWN, &joystick_handler);

            return SUCCESS;
        }

    private:
        ui::ColorUtil::RGB565 image[189*120];
        uint16_t w = 189;
        uint16_t h = 120;

    } image_preview_action;

    //
    // Add items to menu_group
    //

    menu_group.addMenuActions({&run_action, &image_preview_action, &menu_number});


    //
    // Enter menu and its render loop.
    // The code will continue when the user hits the "Run" option, which exits the menu.
    //

    menu_group.run();
}
