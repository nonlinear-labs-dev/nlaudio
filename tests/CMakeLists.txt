##################
#### Tests ####
##################

cmake_minimum_required(VERSION 3.2)
project(nlaudio_tests)

### libnlaudio
set(NLAUDIO_LIBRARY_PATH /usr/local/lib64)
set(NLAUDIO_LIBRARY ${NLAUDIO_LIBRARY_PATH}/libnlaudio.so)
set(NLAUDIO_INCLUDE_DIR /usr/local/include/nlaudio)

add_compile_options(-Wall)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-std=gnu++17>)

if (NOT EXISTS "${NLAUDIO_LIBRARY}" OR NOT EXISTS "${NLAUDIO_INCLUDE_DIR}")
	set(NLAUDIO_LIBRARY_PATH ${CMAKE_CURRENT_BINARY_DIR}/../lib)
	set(NLAUDIO_LIBRARY ${NLAUDIO_LIBRARY_PATH}/libnlaudio.so)
	set(NLAUDIO_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include/nlaudio)
endif()

message("Found nlaudio:  ${NLAUDIO_LIBRARY_PATH}")
message("                ${NLAUDIO_LIBRARY}")
message("                ${NLAUDIO_INCLUDE_DIR}")

set(RENDERER_PERFORMANCE renderer_performance.cpp
    ../examples/c15_audio_engine/ae_cabinet.cpp
    ../examples/c15_audio_engine/ae_combfilter.cpp
    ../examples/c15_audio_engine/ae_echo.cpp
    ../examples/c15_audio_engine/ae_feedbackmixer.cpp
    ../examples/c15_audio_engine/ae_flanger.cpp
    ../examples/c15_audio_engine/ae_gapfilter.cpp
    ../examples/c15_audio_engine/ae_outputmixer.cpp
    ../examples/c15_audio_engine/ae_reverb.cpp
    ../examples/c15_audio_engine/ae_soundgenerator.cpp
    ../examples/c15_audio_engine/ae_svfilter.cpp
    ../examples/c15_audio_engine/ae_svfilter_fir.cpp
    ../examples/c15_audio_engine/ae_svfilter_proto.cpp
    ../examples/c15_audio_engine/ae_test_tone.cpp
    ../examples/c15_audio_engine/dsp_host.cpp
    ../examples/c15_audio_engine/dsp_host_examine.cpp
    ../examples/c15_audio_engine/dsp_host_handle.cpp
    ../examples/c15_audio_engine/paramengine.cpp
    ../examples/c15_audio_engine/pe_env_engine2.cpp
    ../examples/c15_audio_engine/pe_env_engine.cpp
    ../examples/c15_audio_engine/pe_exponentiator.cpp
    ../examples/c15_audio_engine/pe_key_event.cpp
    ../examples/c15_audio_engine/pe_lfo_engine.cpp
    ../examples/c15_audio_engine/pe_utilities.cpp
    ../examples/c15_audio_engine/tcd_decoder.cpp)
add_executable(renderer_performance ${RENDERER_PERFORMANCE})
target_link_libraries(renderer_performance nlaudio)
