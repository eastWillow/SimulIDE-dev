/***************************************************************************
 *   Copyright (C) 2021 by Santiago González                               *
 *                                                                         *
 ***( see copyright.txt file at root folder )*******************************/

#include "boolval.h"
#include "component.h"
#include "propdialog.h"
#include "comproperty.h"

BoolVal::BoolVal( PropDialog* parent, CompBase* comp, ComProperty* prop )
       : PropVal( parent, comp, prop )
{
    setupUi(this);
}
BoolVal::~BoolVal() {;}

void BoolVal::setup( bool )
{
    trueVal->setText( m_property->capt() );
    m_blocked = true;

    bool checked = (m_property->getValStr() == "true");
    trueVal->setChecked( checked );
    m_blocked = false;

    this->adjustSize();
}

void BoolVal::on_trueVal_toggled( bool checked )
{
    if( m_blocked ) return;

    prepareChange();
    m_property->setValStr( checked ? "true" : "false" );
    saveChanges();
}

void BoolVal::updtValues()
{
    bool checked = (m_property->getValStr() == "true");
    trueVal->setChecked( checked );
}
