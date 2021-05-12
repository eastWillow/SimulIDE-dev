/***************************************************************************
 *   Copyright (C) 2020 by santiago González                               *
 *   santigoro@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/

#include "plotbase.h"
#include "plotdisplay.h"
#include "simulator.h"
#include "circuit.h"
#include "circuitwidget.h"


PlotBase::PlotBase( QObject* parent, QString type, QString id )
        : Component( parent, type, id )
        , eElement( id )
{
    m_color[0] = QColor( 240, 240, 100 );
    m_color[1] = QColor( 220, 220, 255 );
    m_color[2] = QColor( 255, 210, 90  );
    m_color[3] = QColor( 000, 245, 160 );
    m_color[4] = QColor( 255, 255, 255 );

    m_baSizeX = 135;
    m_baSizeY = 135;

    m_conditions.resize(8);
    m_condTarget.resize(8);

    m_oneShot = false;

    Simulator::self()->addToUpdateList( this );
}
PlotBase::~PlotBase()
{
    Simulator::self()->remFromUpdateList( this );
}

void PlotBase::setBaSizeX( int size )
{
    if( size < 135 ) size = 135;
    m_baSizeX = size;
    expand( m_expand );
}

void PlotBase::setBaSizeY( int size )
{
    if( size < 135 ) size = 135;
    m_baSizeY = size;
    expand( m_expand );
}

void PlotBase::setTimeDiv( uint64_t td )
{
    m_timeDiv = td;
    m_display->setTimeDiv( td );
}

void PlotBase::toggleExpand()
{
    expand( !m_expand );
}

void PlotBase::setOneShot( bool shot )
{
    m_risEdge = 0;
    m_oneShot = shot;
}

QVector<int> PlotBase::conds()
{
    QVector<int> conds;
    for( int i=0; i<m_condTarget.size(); ++i )
        conds.append( (int)m_condTarget[i] );

    return conds;
}

void PlotBase::setConds( QVector<int> conds )
{
    for( int i=0; i<m_condTarget.size(); ++i )
    {
        if( i >= conds.size() ) break;
        m_condTarget[i] = (cond_t)conds[i];
    }
}

void PlotBase::setCond( int ch, int cond )
{
    m_condTarget[ch] = (cond_t)cond;
}

void PlotBase::conditonMet( int ch, cond_t cond )
{
    m_conditions[ch] = cond;

    if( m_conditions == m_condTarget ) // All conditions met
    {                                  // Trigger Pause Simulation
        m_risEdge = Simulator::self()->circTime();
    }
    /*else  // Rising will be High and Falling Low in next cycles
    {
        if     ( cond == C_RISING )  m_conditions[ch] = C_HIGH;
        else if( cond == C_FALLING ) m_conditions[ch] = C_LOW;
    }*/
}

void PlotBase::paint( QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget )
{
    Component::paint( p, option, widget );
    
    //p->setBrush( Qt::darkGray );
    p->setBrush(QColor( 230, 230, 230 ));
    p->drawRoundedRect( m_area, 4, 4 );
    
    p->setBrush( Qt::white );
    QPen pen = p->pen();
    pen.setWidth( 0 );
    pen.setColor( Qt::white );
    p->setPen(pen);
    
    //p->drawRoundedRect( QRectF( -80-4, -(m_screenSizeY+20)/2-4, m_screenSizeX+m_extraSize+4, m_screenSizeY+20+4 ), 3, 3 );
}

#include "moc_plotbase.cpp"


