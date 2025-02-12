/***************************************************************************
 *   Copyright (C) 2025 by Santiago González                               *
 *                                                                         *
 ***( see copyright.txt file at root folder )*******************************/

#pragma once

#include "e-element.h"

class AnalogClock : public eElement
{
    public:
        AnalogClock();
        ~AnalogClock();

        void stamp() override;
        void runEvent() override;

        void addClkElement( eElement* e );
        void remClkElement( eElement* e );

        void setPeriod( uint64_t p );
        uint64_t getPeriod() { return m_period; }

        void setDivider( uint64_t d );
        uint64_t getDivider() { return m_divider; }

        uint64_t getStep(){ return m_step; }

 static AnalogClock* self() { return m_pSelf; }

    private:
        uint64_t m_period; // in ps
        uint64_t m_step;
        uint64_t m_divider;

        eElement* m_clkElement;

 static AnalogClock* m_pSelf;
};
