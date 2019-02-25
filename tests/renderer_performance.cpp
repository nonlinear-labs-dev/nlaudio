#include "../examples/c15_audio_engine/dsp_host.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char **argv)
{
    dsp_host m_host;
    if(argc > 1)
    {
        m_host.init(48000, 20);

        unsigned int count = static_cast<unsigned int>(atoi(argv[1]));
        std::cout << "rendering " << count << " samples" << std::endl;

        for(unsigned int i = 0; i < count; i++)
        {
            m_host.tickMain();
        }

    }
    return 0;
}
