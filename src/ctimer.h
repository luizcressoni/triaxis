/*! \file ctimer.h */ 
#pragma once
#include <Arduino.h>

/*! \class cTimer
	\brief Implements a easy way to delay stuff without delay()
*/
class cTimer
{
    private:
        uint32_t m_u32TimeOut;
        uint32_t m_u32TimeNow;
        bool m_enabled;
   	public:
   	    cTimer(void);
   	    ~cTimer(void);
		void SetTimeOut(uint32_t _MSeg);
		bool IsTimeOut(void);
		uint32_t ReadTimeOut(void);
		void Enable(bool _enable);
		bool IsEnabled(void);
};


//eof ctimer.h