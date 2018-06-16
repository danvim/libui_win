//
// Created by Daniel on 15/3/2018.
//

#ifndef INNO14_D_2017_INNO_MENU_H
#define INNO14_D_2017_INNO_MENU_H

#include <ui/menus/menu_group.h>
#include <ui/menus/menu_number.h>
#include <ui/fonts/humanist.h>
#include <ui/fonts/blocky.h>
#include <adapters/context_adapter.h>
#include <adapters/application.h>

class SimpleMenu: public virtual Application {
public:
    void start() override;

    static void show() {
        SimpleMenu menu;
        menu.run();
    };
};


#endif //INNO14_D_2017_INNO_MENU_H
