#pragma once

#include "FLAC++/encoder.h"
#include "FLAC++/metadata.h"
#include "audio/samplespecs.h"

namespace Nl {

class FlacEncoder : public FLAC::Encoder::File {
public:
    FlacEncoder(const SampleSpecs &sampleSpecs);

private:


};

} // namepsace Nl
