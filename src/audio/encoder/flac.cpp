#include "audio/encoder/flac.h"
#include "audio/samplespecs.h"

namespace Nl {

FlacEncoder::FlacEncoder(const SampleSpecs &sampleSpecs) :
    FLAC::Encoder::File()
{

    bool ok = true;
    ok &= set_verify(true);
    ok &= set_compression_level(5);
    ok &= set_channels(sampleSpecs.channels);
    ok &= set_bits_per_sample(sampleSpecs.bytesPerSample * 8);
    ok &= set_sample_rate(sampleSpecs.samplerate);
    ok &= set_total_samples_estimate(0);

    // Process call:
    // process_interleaved()

}

} // namespace Nl



