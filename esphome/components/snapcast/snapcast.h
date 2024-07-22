#pragma once

#include "esphome/core/defines.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"

#ifdef USE_SNAPCAST

#ifdef USE_SPEAKER
#include "esphome/components/speaker/speaker.h"
#endif

#include "WiFiClient.h"
#include "EsphomeSpeakerStream.h"
#include "SnapClient.h"
#include "AudioCodecs/CodecOpus.h"

namespace esphome {
namespace snapcast {

class Snapcast : public Component {
 public:
  Snapcast();
  void setup() override;
  void loop() override;
  void dump_config() override;

  void set_speaker(speaker::Speaker *spkr) {
    this->speaker_ = spkr;
    this->out_.set_speaker(spkr);
  };

 protected:
  WiFiClient wific_; // TODO - figure out how to make this not depend on WiFi
  speaker::Speaker *speaker_ = nullptr;
  EsphomeSpeakerStream out_;
  //I2SStream out_i2s_;
  std::unique_ptr<SnapClient> client_;
  OpusAudioDecoder opus_;
};


}  // namespace snapcast
}  // namespace esphome

#endif // USE_SNAPCAST
