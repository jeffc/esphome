#pragma once

#include "esphome/core/defines.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"

#ifdef USE_SNAPCAST

#include "AudioTools/AudioStreams.h"
#include "AudioTools/AudioTypes.h"

#ifdef USE_SPEAKER
#include "esphome/components/speaker/speaker.h"
#endif

using esphome::esp_log_printf_;

namespace esphome {
namespace snapcast {

class EsphomeSpeakerStream : public audio_tools::AudioStream {
 public:
  EsphomeSpeakerStream() = default;
  void set_speaker(speaker::Speaker *spkr) { this->speaker_ = spkr; };

  bool begin() {
    return true;
  };

  size_t write(const uint8_t *data, size_t len) override {
    if (this->speaker_ == nullptr) {
      ESP_LOGW("snapcast-stream", "Tried to write %d bytes, but speaker not set", len);
      return len;
    }
    size_t written = this->speaker_->play(data, len);
    return written;
  }

  //void writeSilence(size_t len) override {
  //  // do nothing
  //}

 protected:
  speaker::Speaker *speaker_ = nullptr;
};


}  // namespace snapcast
}  // namespace esphome

#endif // USE_SNAPCAST

