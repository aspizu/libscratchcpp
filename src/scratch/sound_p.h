// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>

#include "audio/iaudiooutput.h"
#include "audio/iaudioplayer.h"

namespace libscratchcpp
{

struct SoundPrivate
{
        SoundPrivate();
        SoundPrivate(const SoundPrivate &) = delete;

        int rate = 0;
        int sampleCount = 0;
        static IAudioOutput *audioOutput;
        std::shared_ptr<IAudioPlayer> player = nullptr;
};

} // namespace libscratchcpp
