/***************************************************************************
 **  @file   vexceptionobjecterror.cpp
 **  @author Douglas S Caskey
 **  @date   17 Sep, 2023
 **
 **  @copyright
 **  Copyright (C) 2017 - 2023 Seamly, LLC
 **  https://github.com/fashionfreedom/seamly2d
 **
 **  @brief
 **  Seamly2D is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Seamly2D is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Seamly2D. If not, see <http://www.gnu.org/licenses/>.
 **************************************************************************/

/************************************************************************
 **  @file   vexceptionobjecterror.cpp
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   November 15, 2013
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentina project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2013 Valentina project
 **  <https://bitbucket.org/dismine/valentina> All Rights Reserved.
 **
 **  Valentina is free software: you can redistribute it and/or modify
 **  it under the terms of the GNU General Public License as published by
 **  the Free Software Foundation, either version 3 of the License, or
 **  (at your option) any later version.
 **
 **  Valentina is distributed in the hope that it will be useful,
 **  but WITHOUT ANY WARRANTY; without even the implied warranty of
 **  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **  GNU General Public License for more details.
 **
 **  You should have received a copy of the GNU General Public License
 **  along with Seamly2D.  If not, see <http://www.gnu.org/licenses/>.
 **
 *************************************************************************/

#include "vexceptionobjecterror.h"

#include <QDomElement>
#include <QTextStream>

#include "vexception.h"

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief VExceptionObjectError exception object error
 * @param what string with error
 * @param domElement dom element
 */
VExceptionObjectError::VExceptionObjectError(const QString &what, const QDomElement &domElement)
    : VException(what)
    , tagText(QString())
    , tagName(QString())
    , lineNumber(-1)
{
    Q_ASSERT_X(not domElement.isNull(), Q_FUNC_INFO, "domElement is null");
    QTextStream stream(&tagText);
    domElement.save(stream, 4);
    tagName = domElement.tagName();
    lineNumber = domElement.lineNumber();
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief VExceptionObjectError copy constructor
 * @param e exception
 */
VExceptionObjectError::VExceptionObjectError(const VExceptionObjectError &error)
    : VException(error)
    , tagText(error.TagText())
    , tagName(error.TagName())
    , lineNumber(error.LineNumber())
{}

//---------------------------------------------------------------------------------------------------------------------
VExceptionObjectError &VExceptionObjectError::operator=(const VExceptionObjectError &error)
{
    if (&error == this)
    {
        return *this;
    }
    VException::operator=(error);
    tagText = error.TagText();
    tagName = error.TagName();
    lineNumber = error.LineNumber();
    return *this;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief ErrorMessage return main error message
 * @return main error message
 */
QString VExceptionObjectError::ErrorMessage() const
{
    return QString("ExceptionObjectError: %1").arg(error);
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief DetailedInformation return detailed information about error
 * @return detailed information
 */
QString VExceptionObjectError::DetailedInformation() const
{
    return MoreInfo(QString("tag: %1 in line %2\n%3").arg(tagName).arg(lineNumber).arg(tagText));
}
