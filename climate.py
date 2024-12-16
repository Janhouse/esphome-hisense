import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate, uart
from esphome.components.logger import HARDWARE_UART_TO_SERIAL
from esphome.const import (
    CONF_ID,
    CONF_HARDWARE_UART,
    CONF_BAUD_RATE,
    CONF_UPDATE_INTERVAL,
    CONF_MODE,
    CONF_FAN_MODE,
    CONF_SWING_MODE,
    CONF_PERIOD,
    CONF_TIMEOUT
)
from esphome.core import CORE, coroutine

DEPENDENCIES = ['uart', 'climate']
AUTO_LOAD = ['uart', 'sensor', 'climate']

hisense_ns = cg.esphome_ns.namespace('hisense')
HisenseClimate = hisense_ns.class_(
    "HisenseClimate", climate.Climate, cg.PollingComponent, uart.UARTDevice
)

CONFIG_SCHEMA = climate.CLIMATE_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(HisenseClimate),
                    cv.Optional(CONF_PERIOD, default="1s"): cv.time_period,
            cv.Optional(CONF_TIMEOUT, default="2s"): cv.time_period,
    }
).extend(cv.polling_component_schema("2s")).extend(uart.UART_DEVICE_SCHEMA)

@coroutine
def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    
    yield cg.register_component(var, config)
    yield climate.register_climate(var, config)
    yield uart.register_uart_device(var, config)
