//==========================================================================
//  MATCHABLEFIELD.CC - part of
//                     OMNeT++/OMNEST
//            Discrete System Simulation in C++
//
//  Author: Andras Varga
//
//==========================================================================

/*--------------------------------------------------------------*
  Copyright (C) 1992-2008 Andras Varga
  Copyright (C) 2006-2008 OpenSim Ltd.

  This file is distributed WITHOUT ANY WARRANTY. See the file
  `license' for details on this and other legal matters.
*--------------------------------------------------------------*/

#include "commonutil.h"
#include "matchablefield.h"
#include "cclassdescriptor.h"

NAMESPACE_BEGIN

MatchableFieldAdapter::MatchableFieldAdapter(cObject *object, int fieldIndex)
{
    setField(object, fieldIndex);
}

void MatchableFieldAdapter::setField(cObject *object, int fieldIndex)
{
    Assert(object);
    this->object = object;
    this->fieldIndex = fieldIndex;
    this->classDescriptor = object->getDescriptor();
}

void MatchableFieldAdapter::setField(cObject *object, const char *fieldName)
{
    Assert(object);
    this->object = object;
    this->fieldIndex = -1;
    this->classDescriptor = object->getDescriptor();

    for (int i = 0; i < classDescriptor->getFieldCount(object); i++)
        if (!strcmp(fieldName, classDescriptor->getFieldName(object, i)))
            this->fieldIndex = i;

    Assert(fieldIndex != -1);
}

const char *MatchableFieldAdapter::getAsString() const
{
    Assert(object && classDescriptor);
    return classDescriptor->getFieldName(object, fieldIndex);
}

const char *MatchableFieldAdapter::getAsString(const char *attribute) const
{
    Assert(object && classDescriptor);

    if (!strcmp("name", attribute))
        return classDescriptor->getFieldName(object, fieldIndex);
    else if (!strcmp("type", attribute))
        return classDescriptor->getFieldTypeString(object, fieldIndex);
    else if (!strcmp("declaredOn", attribute))
        return classDescriptor->getFieldDeclaredOn(object, fieldIndex);
    else
        return NULL;
}

NAMESPACE_END

