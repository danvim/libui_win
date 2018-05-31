//
// Created by Daniel on 30/5/2018.
//

#ifndef LIBUI_LIBSCCC_BATTERY_METER_ADAPTER_H
#define LIBUI_LIBSCCC_BATTERY_METER_ADAPTER_H


#include <ui/adapters/module_adapters/battery_meter_interface.h>

namespace adapters {
    class BatteryMeterAdapter: public virtual ui::adapters::BatteryMeterAdapterInterface {
    public:
        float getVoltage() override;
    };
}


#endif //LIBUI_LIBSCCC_BATTERY_METER_ADAPTER_H
