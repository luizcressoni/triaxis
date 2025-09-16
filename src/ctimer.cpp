/*! \file ctimer.cpp */
#include "ctimer.h"

/*! Construtor */
cTimer::cTimer(void) {
    m_u32TimeNow = 0;
    m_u32TimeOut = 0;
    m_enabled = false;
}

cTimer::~cTimer(void) = default;

/*! \brief Defines how long the timer will take to generate a TimeOut (in ms)
    \param _MSeg : Desired timeout period in ms.
*/
void cTimer::SetTimeOut(uint32_t _MSeg) {
    m_enabled = true;
    m_u32TimeNow = millis();
    m_u32TimeOut = m_u32TimeNow + _MSeg;
}

/*! \brief Detects if a TimeOut occurred
    \return true if it did. Quite obvious, right?
*/
bool cTimer::IsTimeOut(void) {
    bool ret;
    if (!m_enabled)
        return false;
    uint32_t m_u32Time = millis();
    if (m_u32TimeOut >= m_u32TimeNow)
        ret = (m_u32Time >= m_u32TimeOut) || (m_u32Time < m_u32TimeNow);
    else
        ret = (m_u32Time >= m_u32TimeOut) && (m_u32Time < m_u32TimeNow);
    return ret;
}

/*! \brief Get how much time is remaining until timeout
    \return time remeining in ms.
    \sa SetTimeOut(uint32_t _MSeg)
*/
uint32_t cTimer::ReadTimeOut(void) {
    if (IsTimeOut())
        return 0;
    return m_u32TimeOut - millis();
}

void cTimer::Enable(bool _enable) {
    m_enabled = _enable;
}

bool cTimer::IsEnabled(void) {
    return m_enabled;
}

//eof ctimer.cpp