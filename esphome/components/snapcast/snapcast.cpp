#include "esphome/core/log.h"
#include "snapcast.h"

#ifdef USE_SNAPCAST
#include "SnapClient.h"

using esphome::esp_log_printf_;

namespace esphome {
namespace snapcast {

static const char *TAG = "snapcast";

Snapcast::Snapcast() {
  this->client_ = std::unique_ptr<SnapClient>(new SnapClient(this->wific_, this->out_, this->opus_));
  this->client_->snapProcessor().setFastLoop(true);
  //auto config = this->out_i2s_.defaultConfig();
  //config.pin_bck = 15;
  //config.pin_ws = 0;
  //config.pin_data = 2;
  //this->out_i2s_.begin(config);
}

void Snapcast::setup() {
  ESP_LOGD(TAG, "setting up...");
  this->client_->setWiFi(false); // don't have the snapclient library manage the
                                // wifi connection
  this->client_->setServerIP(IPAddress(192,168,1,201));
  ESP_LOGD(TAG, "set server ip");
}


static bool previously_connected = false;
void Snapcast::loop() {
  bool currently_connected = WiFi.status() == WL_CONNECTED;
  if (currently_connected && !previously_connected) {
    ESP_LOGD(TAG, "wifi connected, starting snapclient");
    this->client_->begin();
  } else if (!currently_connected && previously_connected) {
    ESP_LOGD(TAG, "wifi disconnected, ending snapclient");
    this->client_->end();
  }

  if (currently_connected) {
    this->client_->doLoop();
  }

  previously_connected = WiFi.status() == WL_CONNECTED;;
}

void Snapcast::dump_config(){
    ESP_LOGCONFIG(TAG, "snapcast");
}


}  // namespace snapcast
}  // namespace esphome

#endif // USE_SNAPCAST
