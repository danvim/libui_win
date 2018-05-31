//
// Created by Daniel on 29/5/2018.
//

#include <ui/graphics.h>
#include <ui/color_util.h>
#include "adapters/screen_adapter.h"

int offset_x = 20;
int scaling = 2;

void adapters::ScreenAdapter::setRegion(ui::graphics::Rectangle rectangle) {
    region = rectangle;
}

ui::graphics::Rectangle adapters::ScreenAdapter::getRegion() {
    return region;
}

void adapters::ScreenAdapter::clear() {
    setRegion({0, 0, getWidth(), getHeight()});
    fill(0x0);
}

void adapters::ScreenAdapter::fill(uint16_t rgb565) {
    ui::ColorUtil::RGB24 rgb = ui::ColorUtil::RGB565(rgb565).toRGB24();

    HRGN rgn = CreateRectRgn(offset_x + region.x * scaling, region.y * scaling, offset_x + (region.x + region.w) * scaling, (region.y + region.h) * scaling);
    HBRUSH brush = CreateSolidBrush(RGB(rgb.r, rgb.g, rgb.b));

    FillRgn(context_ptr, rgn, brush);

    DeleteObject(rgn);
    DeleteObject(brush);
}

uint16_t adapters::ScreenAdapter::getWidth() {
    return 128u;
}

uint16_t adapters::ScreenAdapter::getHeight() {
    return 160u;
}
