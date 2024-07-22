import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.components import speaker

empty_component_ns = cg.esphome_ns.namespace("snapcast")
Snapcast = empty_component_ns.class_("Snapcast", cg.Component)

DEPENDENCIES = [ "wifi" ]

CONF_SPEAKER = "speaker"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(Snapcast),
        cv.Optional(CONF_SPEAKER) : cv.use_id(speaker.Speaker),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])

    cg.add_define("USE_SNAPCAST")

    # when the author cuts a new release, these should probably use a stable
    # version tag instead of None (HEAD)
    cg.add_library(
        name = "arduino-snapclient",
        repository = "https://github.com/pschatzmann/arduino-snapclient",
        version = None)

    cg.add_library(
        name = "arduino-audio-tools",
        repository = "https://github.com/pschatzmann/arduino-audio-tools.git",
        version = None)

    cg.add_library(
        name = "arduino-libopus",
        repository = "https://github.com/pschatzmann/arduino-libopus.git",
        version = None)

    # The arduino audio tools library depends on these, even if you aren't
    # actually using WiFi. The LDF can't find them automagically, so add them
    # here.
    cg.add_library("WiFi", None)
    cg.add_library("WiFiClientSecure", None)


    if CONF_SPEAKER in config:
      spkr = await cg.get_variable(config[CONF_SPEAKER])
      cg.add(var.set_speaker(spkr))


    await cg.register_component(var, config)
