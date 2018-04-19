/******************************************************************************/
/** @file           paramengine.cpp
    @date           2018-03-20
    @version        0.1
    @author         Matthias Seeber & Anton Schmied[2018-01-23]
    @brief          Paramengine Class member and method definitions
*******************************************************************************/

#include <math.h>
#include "paramengine.h"

/* proper init */
void paramengine::init(uint32_t _sampleRate, uint32_t _voices)
{
    /* determine crucial variables */
    m_millisecond = dsp_samples_to_ms * static_cast<float>(_sampleRate);        // one millisecond in samples
    m_nyquist_frequency = static_cast<float>(_sampleRate >> 1);                 // nyquist frequency (50% sampleRate)
    m_routePolyphony[1] = _voices;                                              // overwrite polyphony
    m_timeFactors[0] = 0.f;                                                     // time convertsion factor (sync types)
    m_timeFactors[1] = 1.f;                                                     // time convertsion factor (audio types)
    m_timeFactors[2] = static_cast<float>(_sampleRate / dsp_clock_rates[0]);    // time convertsion factor (fast types)
    m_timeFactors[3] = static_cast<float>(_sampleRate / dsp_clock_rates[1]);    // time convertsion factor (slow types)
    /* initialize components */
    m_clockIds.reset();
    m_postIds.reset();
    m_convert.init();
    /* provide indices for further definitions */
    uint32_t i, p;
    /* initialize envelope events */
    for(i = 0; i < sig_number_of_env_events; i++)
    {
        m_event.m_env[i].init();
    }
    /* initialize parameters by definition (see pe_defines_params.h) */
    i = 0;
    for(p = 0; p < sig_number_of_params; p++)
    {
        /* provide parameter reference */
        param_head* obj = &m_head[p];
        /* declarations according to parameter definition */
        obj->m_index = i;                                                       // index points to first voice/item in (rendering) array
        obj->m_id = static_cast<uint32_t>(param_definition[p][0]);              // TCD id
        obj->m_clockType = static_cast<uint32_t>(param_definition[p][1]);       // clock type (sync/audio/fast/slow)
        obj->m_polyType = static_cast<uint32_t>(param_definition[p][2]);        // poly type (mono/poly)
        obj->m_size = m_routePolyphony[obj->m_polyType];                        // determine (rendering) size
        obj->m_normalize = 1.f / param_definition[p][3];                        // TCD range
        obj->m_scaleId = static_cast<uint32_t>(param_definition[p][4]);         // TCD scale id
        obj->m_scaleArg = param_definition[p][5];                               // TCD scale argument
        obj->m_postId = static_cast<int32_t>(param_definition[p][6]);           // post processing id
        /* declare parameter according to clock type - crucial for rendering */
        m_clockIds.add(obj->m_clockType, obj->m_polyType, p);
        if(obj->m_postId > -1)
        {
            /* determine automatic post processing (copy, distribution) */
            m_postIds.add(static_cast<uint32_t>(param_definition[p][7]), obj->m_clockType, obj->m_polyType, p);
        }
        /* update item pointer */
        i += obj->m_size;
    }
    /* initialize global utility parameters */
    for(i = 0; i < sig_number_of_utilities; i++)
    {
        m_utilities[i].m_normalize = 1.f / utility_definition[i][0];
        m_utilities[i].m_scaleId = static_cast<uint32_t>(utility_definition[i][1]);
        m_utilities[i].m_scaleArg = utility_definition[i][2];
    }
    /* initialize envelopes */
    m_envelopes.init(_voices, 1 / ((env_init_gateRelease * m_millisecond) + 1));
}

/* TCD mechanism - scaling */
float paramengine::scale(const uint32_t _scaleId, const float _scaleArg, float _value)
{
    /* tcd scale methods (currently 13 established scalings), provide result variable */
    float result;
    switch(_scaleId)
    {
    case 0:
        /* bipolar, linear scaling (argument is offset) */
        result = _value + _scaleArg;
        break;
    case 1:
        /* bipolar, linear scaling (argument is factor) */
        result = _value * _scaleArg;
        break;
    case 2:
        /* inverted, linear scaling (argument is offset) */
        result = _scaleArg - _value;
        break;
    case 3:
        /* bipolar, parabolic scaling (argument is offet) */
        result = (fabs(_value) * _value) + _scaleArg;
        break;
    case 4:
        /* bipolar, parabolic scaling (argument is factor) */
        result = fabs(_value) * _value * _scaleArg;
        break;
    case 5:
        /* bipolar, cubic scaling (argument is offset) */
        result = (_value * _value * _value) + _scaleArg;
        break;
    case 6:
        /* inverted, s-curve scaling (argument is offset) */
        _value = (2 * (_scaleArg - _value)) - 1;
        result = ((_value * _value * _value) - 0.25) + (0.75 * _value) + 0.5;
        break;
    case 7:
        /* exponential, gain scaling (argument is offset) */
        result = m_convert.eval_level(_value + _scaleArg);
        break;
    case 8:
        /* exponential, osc-pitch scaling (argument is offset) */
        result = m_convert.eval_osc_pitch(_value + _scaleArg);              // includes hyperbolic floor, oscillators only
        break;
    case 9:
        /* exponential, lin-pitch scaling (argument is offset) */
        result = m_convert.eval_lin_pitch(_value + _scaleArg);              // other (linear) pitches
        break;
    case 10:
        /* exponential, drive scaling (argument is factor) */
        result = (m_convert.eval_level(_value) * _scaleArg) - _scaleArg;    // shaper a/b drives only
        break;
    case 11:
        /* exponential, mix-drive scaling (argument is factor) */
        result = m_convert.eval_level(_value) * _scaleArg;                  // mixer shaper drives
        break;
    case 12:
        /* exponential, envelope-time scaling (argument is offset) */
        result = m_convert.eval_time((_value * dsp_expon_time_factor) + _scaleArg);
        break;
    }
    /* return scaled value */
    return result;
}

/* TCD mechanism - time updates */
void paramengine::setDx(const uint32_t _voiceId, const uint32_t _paramId, float _value)
{
    /* provide object reference */
    param_head* obj = &m_head[_paramId];
    const uint32_t index = obj->m_index + _voiceId;
    /* handle by clock type and clip to fit [0 ... 1] range */
    _value = fmin(_value * m_timeFactors[obj->m_clockType], 1);
    /* pass value to (rendering) item */
    m_body[index].m_dx[0] = _value;
}

/* TCD mechanism - destination updates */
void paramengine::setDest(const uint32_t _voiceId, const uint32_t _paramId, float _value)
{
    /* provide object and (rendering) item references */
    param_head* obj = &m_head[_paramId];
    const uint32_t index = obj->m_index + _voiceId;
    param_body* item = &m_body[index];
    /* normalize and scale destination argument, pass result to (rendering) item */
    _value *= obj->m_normalize;
    item->m_dest = scale(obj->m_scaleId, obj->m_scaleArg, _value);
    /* apply according to preload and clock type */
    if(m_preload == 0)
    {
        /* sync type parameters apply directly, non-sync type parameters apply destinations */
        if(obj->m_clockType > 0)
        {
            applyDest(index);
        }
        else
        {
            applySync(index);
        }
    }
    else
    {
        item->m_preload++;
    }
}

/* TCD mechanism - preload functionality */
void paramengine::applyPreloaded(const uint32_t _voiceId, const uint32_t _paramId)
{
    /* provide object and (rendering) item references */
    param_head* obj = &m_head[_paramId];
    const uint32_t index = obj->m_index + _voiceId;
    param_body* item = &m_body[index];
    /* apply according to preload status */
    if(item->m_preload > 0)
    {
        item->m_preload = 0;
        /* sync type parameters apply directly, non-sync type parameters apply destinations */
        if(obj->m_clockType == 0)
        {
            applySync(index);
        }
        else
        {
            applyDest(index);
        }
    }
}

/* TCD mechanism - application (non-sync types performing transitions) */
void paramengine::applyDest(const uint32_t _index)
{
    /* provide (rendering) item reference */
    param_body* item = &m_body[_index];
    /* construct segment and set rendering state */
    item->m_start = item->m_signal;
    item->m_diff = item->m_dest - item->m_start;
    item->m_x = item->m_dx[1] = item->m_dx[0];
    item->m_state = 1;
}

/* TCD mechanism - application (sync types performing steps) */
void paramengine::applySync(const uint32_t _index)
{
    /* just update signal, no reference for one-liner */
    m_body[_index].m_signal = m_body[_index].m_dest;
}

/* parameter rendering */
void paramengine::tickItem(const uint32_t _index)
{
    /* provide (rendering) item reference */
    param_body* item = &m_body[_index];
    /* render when state is true */
    if(item->m_state == 1)
    {
        /* stop on final sample */
        if(item->m_x >= 1)
        {
            item->m_x = 1;
            item->m_state = 0;
        }
        /* update signal (and x) */
        item->m_signal = item->m_start + (item->m_diff * item->m_x);
        item->m_x += item->m_dx[1];
    }
}

/* TCD Key Events - keyDown */
void paramengine::keyDown(const uint32_t _voiceId, float _velocity)
{
    /* velocity scaling */
    _velocity = scale(m_utilities[0].m_scaleId, m_utilities[0].m_scaleArg, _velocity * m_utilities[0].m_normalize);
    /* update event, preload handling by parent (dsp_host) */
    m_event.m_mono.m_velocity = _velocity;              // set mono velocity (always last velocity)
    m_event.m_mono.m_type = 1;                          // set mono event type (1: DOWN)
    m_event.m_poly[_voiceId].m_velocity = _velocity;    // set poly velocity (according to voiceId)
    m_event.m_poly[_voiceId].m_type = 1;                // set poly event type (1: DOWN)
}

/* TCD Key Events - keyUp */
void paramengine::keyUp(const uint32_t _voiceId, float _velocity)
{
    /* velocity scaling */
    _velocity = scale(m_utilities[0].m_scaleId, m_utilities[0].m_scaleArg, _velocity * m_utilities[0].m_normalize);
    /* update event, preload handling by parent (dsp_host) */
    m_event.m_mono.m_velocity = _velocity;              // set mono velocity (always last velocity)
    m_event.m_mono.m_type = 0;                          // set mono event type (0: UP)
    m_event.m_poly[_voiceId].m_velocity = _velocity;    // set poly velocity (according to voiceId)
    m_event.m_poly[_voiceId].m_type = 0;                // set poly event type (0: UP)
}

/* TCD Key Events - preload functionality */
void paramengine::keyApply(const uint32_t _voiceId)
{
    /* apply key event (update envelopes according to event type) */
    const float pitch = m_body[m_head[par_notePitch].m_index + _voiceId].m_signal;
    const float velocity = m_event.m_poly[_voiceId].m_velocity;
    if(m_event.m_poly[_voiceId].m_type == 0)
    {
        /* key up */
        envUpdateStop(_voiceId, 0, pitch, velocity);    // Envelope A
        // Envelopes B, C currently missing
        m_envelopes.stopEnvelope(_voiceId, 3);          // Gate
    }
    else
    {
        /* key down */
        envUpdateStart(_voiceId, 0, pitch, velocity);   // Envelope A
        // Envelopes B, C currently missing
        m_envelopes.startEnvelope(_voiceId, 3, 0);      // Gate
    }
}

/* TCD Key Events - mono key mechanism */
void paramengine::keyApplyMono()
{
    /* Flanger Envelope (peak) update by mono velocity (only on key down) */
    if(m_event.m_mono.m_type == 1)
    {
        m_envelopes.setSegmentDest(0, 4, 1, m_event.m_mono.m_velocity);
        m_envelopes.startEnvelope(0, 4, 0);
    }
}

/* envelope updates - start procedure */
void paramengine::envUpdateStart(const uint32_t _voiceId, const uint32_t _envId, const float _pitch, const float _velocity)
{
    /* provide envelope index (for parameter access) and segment parameters (time, dest) */
    const uint32_t envIndex = m_envIds[_envId];
    float time, dest;
    /* determine envelope event parameters */
    float timeKT = -m_body[m_head[envIndex + 11].m_index].m_signal * _pitch;
    float levelVel = -m_body[m_head[envIndex + 7].m_index].m_signal;
    float attackVel = -m_body[m_head[envIndex + 8].m_index].m_signal * _velocity;
    float levelKT = m_body[m_head[envIndex + 10].m_index].m_signal * _pitch;
    // float peak = fmin(m_convert.eval_level(((1 - _velocity) * levelVel * env_norm_peak) + levelKT), env_clip_peak);
    float peak = fmin(m_convert.eval_level(((1 - _velocity) * levelVel) + levelKT), env_clip_peak);
    /* envelope event updates */
    m_event.m_env[_envId].m_levelFactor[_voiceId] = peak;
    m_event.m_env[_envId].m_timeFactor[_voiceId][0] = m_convert.eval_level(timeKT + attackVel) * m_millisecond;
    m_event.m_env[_envId].m_timeFactor[_voiceId][1] = m_convert.eval_level(timeKT) * m_millisecond;
    m_event.m_env[_envId].m_timeFactor[_voiceId][2] = m_event.m_env[_envId].m_timeFactor[_voiceId][1];
    /* envelope segment updates (Attack - Time, Peak) */
    time = m_body[m_head[envIndex].m_index].m_signal * m_event.m_env[_envId].m_timeFactor[_voiceId][0];
    m_envelopes.setSegmentDx(_voiceId, _envId, 1, 1 / (time + 1));
    m_envelopes.setSegmentDest(_voiceId, _envId, 1, peak);
    /* envelope segment updates (Decay1 - Time, Breakpoint Level) */
    time = m_body[m_head[envIndex + 1].m_index].m_signal * m_event.m_env[_envId].m_timeFactor[_voiceId][1];
    m_envelopes.setSegmentDx(_voiceId, _envId, 2, 1 / (time + 1));
    dest = peak * m_body[m_head[envIndex + 2].m_index].m_signal;
    m_envelopes.setSegmentDest(_voiceId, _envId, 2, dest);
    /* envelope segment updates (Decay2 - Time, Sustain Level) */
    time = m_body[m_head[envIndex + 3].m_index].m_signal * m_event.m_env[_envId].m_timeFactor[_voiceId][2];
    m_envelopes.setSegmentDx(_voiceId, _envId, 3, 1 / (time + 1));
    dest = peak * m_body[m_head[envIndex + 4].m_index].m_signal;
    m_envelopes.setSegmentDest(_voiceId, _envId, 3, dest);
    /* trigger envelope start (passing envelope curvature) */
    m_envelopes.startEnvelope(_voiceId, _envId, m_body[m_head[envIndex + 12].m_index].m_signal);
}

/* envelope updates - stop procedure */
void paramengine::envUpdateStop(const uint32_t _voiceId, const uint32_t _envId, const float _pitch, const float _velocity)
{
    /* provide envelope index (for parameter access) and segment parameter (time) */
    const uint32_t envIndex = m_envIds[_envId];
    float time;
    /* determine envelope event parameters */
    float timeKT = -m_body[m_head[envIndex + 11].m_index].m_signal * _pitch;
    float releaseVel = -m_body[m_head[envIndex + 9].m_index].m_signal * _velocity;
    /* envelope event updates */
    m_event.m_env[_envId].m_timeFactor[_voiceId][3] = m_convert.eval_level(timeKT + releaseVel) * m_millisecond;
    /* envelope segment updates (Release - Time) - distinguish finite and infinite times */
    if(m_body[m_head[envIndex + 5].m_index].m_signal <= env_highest_finite_time)
    {
        /* finite release time */
        time = m_body[m_head[envIndex + 5].m_index].m_signal * m_event.m_env[_envId].m_timeFactor[_voiceId][3];
        m_envelopes.setSegmentDx(_voiceId, _envId, 4, 1 / (time + 1));
    }
    else
    {
        /* infinite release time */
        m_envelopes.setSegmentDx(_voiceId, _envId, 4, 0);
    }
    /* trigger envelope stop */
    m_envelopes.stopEnvelope(_voiceId, _envId);
}

/* envelope updates - times */
void paramengine::envUpdateTimes(const uint32_t _voiceId, const uint32_t _envId)
{
    /* provide envelope index (for parameter access) and segment parameter (time) */
    const uint32_t envIndex = m_envIds[_envId];
    float time;
    /* envelope segment updates (Attack - Time) */
    time = m_body[m_head[envIndex].m_index].m_signal * m_event.m_env[_envId].m_timeFactor[_voiceId][0];
    m_envelopes.setSegmentDx(_voiceId, _envId, 1, 1 / (time + 1));
    /* envelope segment updates (Decay1 - Time) */
    time = m_body[m_head[envIndex + 1].m_index].m_signal * m_event.m_env[_envId].m_timeFactor[_voiceId][1];
    m_envelopes.setSegmentDx(_voiceId, _envId, 2, 1 / (time + 1));
    /* envelope segment updates (Decay2 - Time) */
    time = m_body[m_head[envIndex + 3].m_index].m_signal * m_event.m_env[_envId].m_timeFactor[_voiceId][2];
    m_envelopes.setSegmentDx(_voiceId, _envId, 3, 1 / (time + 1));
    /* envelope segment updates (Release  Time) - distinguish finite and infinite times */
    if(m_body[m_head[envIndex + 5].m_index].m_signal <= env_highest_finite_time)
    {
        /* finite release time */
        time = m_body[m_head[envIndex + 5].m_index].m_signal * m_event.m_env[_envId].m_timeFactor[_voiceId][3];
        m_envelopes.setSegmentDx(_voiceId, _envId, 4, 1 / (time + 1));
    }
    else
    {
        /* infinite release time */
        m_envelopes.setSegmentDx(_voiceId, _envId, 4, 0);
    }
}

/* envelope updates - levels */
void paramengine::envUpdateLevels(const uint32_t _voiceId, const uint32_t _envId)
{
    /* provide envelope index (for parameter access) and segment parameter (peak) */
    const uint32_t envIndex = m_envIds[_envId];
    float peak = m_event.m_env[_envId].m_levelFactor[_voiceId];
    /* envelope segment updates (Decay1 - Breakpoint Level) */
    m_envelopes.setSegmentDest(_voiceId, _envId, 2, peak * m_body[m_head[envIndex + 2].m_index].m_signal);
    /* envelope segment updates (Decay2 - Sustain Level) */
    m_envelopes.setSegmentDest(_voiceId, _envId, 3, peak * m_body[m_head[envIndex + 4].m_index].m_signal);
}

/* Post Processing - slow parameters */
void paramengine::postProcess_slow(float *_signal, const uint32_t _voiceId)
{
    /* provide indices for distributions */
    uint32_t i, p;
    /* automatic mono to poly distribution */
    for(i = 0; i < m_postIds.m_data[1].m_data[3].m_data[0].m_length; i++)
    {
        /* spread values of mono parameters to all voices of shared signal array */
        p = m_head[m_postIds.m_data[1].m_data[3].m_data[0].m_data[i]].m_postId;
        _signal[p] = m_body[m_head[m_postIds.m_data[1].m_data[3].m_data[0].m_data[i]].m_index].m_signal;
    }
    /* automatic poly to poly copy - each voice */
    for(i = 0; i < m_postIds.m_data[0].m_data[3].m_data[1].m_length; i++)
    {
        p = m_head[m_postIds.m_data[0].m_data[3].m_data[1].m_data[i]].m_postId;
        _signal[p] = m_body[m_head[m_postIds.m_data[0].m_data[3].m_data[1].m_data[i]].m_index + _voiceId].m_signal;
    };
    /* automatic mono to mono copy (effect parameters) - only for voice 0 */
    if(_voiceId == 0)
    {
        for(i = 0; i < m_postIds.m_data[0].m_data[3].m_data[0].m_length; i++)
        {
            p = m_head[m_postIds.m_data[0].m_data[3].m_data[0].m_data[i]].m_postId;
            _signal[p] = m_body[m_head[m_postIds.m_data[0].m_data[3].m_data[0].m_data[i]].m_index].m_signal;
        }
    }
    /* update envelope times */
    envUpdateTimes(_voiceId, 0);    // Envelope A
    /* later: Envelope C trigger at slow clock? */
    /* Pitch Updates */
    float basePitch = m_body[m_head[par_notePitch].m_index + _voiceId].m_signal + m_body[m_head[20].m_index].m_signal;
    float keyTracking, oscPitch;
    /* determine Oscillator A Frequency in Hz (Base Pitch, Master Tune, Key Tracking, Osc Pitch - EnvC missing) */
    keyTracking = m_body[m_head[14].m_index].m_signal;
    oscPitch = m_body[m_head[13].m_index].m_signal;
    _signal[OSC_A_FRQ] = m_pitch_reference * oscPitch * m_convert.eval_lin_pitch(69 + (basePitch * keyTracking));   // nyquist clip?
    /* determine Oscillator A Chirp Frequency in Hz */
    _signal[OSC_A_CHI] = m_body[m_head[18].m_index].m_signal * 440.f;                                               // nyquist clip?
}

/* Post Processing - fast parameters */
void paramengine::postProcess_fast(float *_signal, const uint32_t _voiceId)
{
    /* provide indices for distributions */
    uint32_t i, p;
    /* automatic mono to poly distribution */
    for(i = 0; i < m_postIds.m_data[1].m_data[2].m_data[0].m_length; i++)
    {
        /* spread values of mono parameters to all voices of shared signal array */
        p = m_head[m_postIds.m_data[1].m_data[2].m_data[0].m_data[i]].m_postId;
        _signal[p] = m_body[m_head[m_postIds.m_data[1].m_data[2].m_data[0].m_data[i]].m_index].m_signal;
    }
    /* automatic poly to poly copy - each voice */
    for(i = 0; i < m_postIds.m_data[0].m_data[2].m_data[1].m_length; i++)
    {
        p = m_head[m_postIds.m_data[0].m_data[2].m_data[1].m_data[i]].m_postId;
        _signal[p] = m_body[m_head[m_postIds.m_data[0].m_data[2].m_data[1].m_data[i]].m_index + _voiceId].m_signal;
    };
    /* automatic mono to mono copy (effect parameters) - only for voice 0 */
    if(_voiceId == 0)
    {
        for(i = 0; i < m_postIds.m_data[0].m_data[2].m_data[0].m_length; i++)
        {
            p = m_head[m_postIds.m_data[0].m_data[2].m_data[0].m_data[i]].m_postId;
            _signal[p] = m_body[m_head[m_postIds.m_data[0].m_data[2].m_data[0].m_data[i]].m_index].m_signal;
        }
    }
    /* update envelope levels */
    envUpdateLevels(_voiceId, 0);   // Envelope A
}

/* Post Processing - audio parameters */
void paramengine::postProcess_audio(float *_signal, const uint32_t _voiceId)
{
    /* provide indices for distributions */
    uint32_t i, p;
    /* automatic mono to poly distribution */
    for(i = 0; i < m_postIds.m_data[1].m_data[1].m_data[0].m_length; i++)
    {
        /* spread values of mono parameters to all voices of shared signal array */
        p = m_head[m_postIds.m_data[1].m_data[1].m_data[0].m_data[i]].m_postId;
        _signal[p] = m_body[m_head[m_postIds.m_data[1].m_data[1].m_data[0].m_data[i]].m_index].m_signal;
    }
    /* automatic poly to poly copy - each voice */
    for(i = 0; i < m_postIds.m_data[0].m_data[1].m_data[1].m_length; i++)
    {
        p = m_head[m_postIds.m_data[0].m_data[1].m_data[1].m_data[i]].m_postId;
        _signal[p] = m_body[m_head[m_postIds.m_data[0].m_data[1].m_data[1].m_data[i]].m_index + _voiceId].m_signal;
    };
    /* automatic mono to mono copy (effect parameters) and mono envelope ticking - only for voice 0 */
    if(_voiceId == 0)
    {
        for(i = 0; i < m_postIds.m_data[0].m_data[1].m_data[0].m_length; i++)
        {
            p = m_head[m_postIds.m_data[0].m_data[1].m_data[0].m_data[i]].m_postId;
            _signal[p] = m_body[m_head[m_postIds.m_data[0].m_data[1].m_data[0].m_data[i]].m_index].m_signal;
        }
        m_envelopes.tickMono();
    }
    /* poly envelope ticking */
    m_envelopes.tickPoly(_voiceId);
    /* poly envelope distribution */
    _signal[ENV_A_SIG] = m_envelopes.m_body[m_envelopes.m_head[0].m_index + _voiceId].m_signal * m_body[m_head[6].m_index].m_signal;     // Envelope A post Gain
    _signal[ENV_G_SIG] = m_envelopes.m_body[m_envelopes.m_head[3].m_index + _voiceId].m_signal;     // Gate
    /* Oscillator parameter post processing */
    float pm_amt, pm_env;
    /* Oscillator A */
    pm_amt = m_body[m_head[16].m_index].m_signal;
    pm_env = m_body[m_head[17].m_index].m_signal;
    _signal[OSC_A_PMSEA] = ((_signal[ENV_A_SIG] * pm_env) + (1 - pm_env)) * pm_amt;                           // Osc A PM Self (Env A)
}
