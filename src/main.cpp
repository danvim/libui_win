
#include "simple_menu.h"
#include <ui/reactive/reactive.h>
#include <iostream>
#include <ui/fonts/noto.h>

int main() {
    SimpleMenu::show();

    auto* screen_ptr = ui::Context::getScreen();

    ui::fonts::Noto noto;

    ui::Context::addFontToRepo("noto", &noto);

    ui::TextBlock a;

    a.setFont(&noto);
    a.setRegion(ui::graphics::Rectangle{0, 0, 1000, 0});
    a.setTextWrap(ui::text::NO_WRAP);
    a.setOverflow(ui::text::VISIBLE);
    a.setText("Hello World!");

    a.render();

    while (true) {

    }

    return 0;
}
