/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2017  Seamly, LLC                                       *
 *                                                                         *
 *   https://github.com/fashionfreedom/seamly2d                             *
 *                                                                         *
 ***************************************************************************
 **
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
 **  along with Seamly2D.  If not, see <http://www.gnu.org/licenses/>.
 **
 **************************************************************************

 ************************************************************************
 **
 **  @file   tst_vposter.cpp
 **  @author Roman Telezhynskyi <dismine(at)gmail.com>
 **  @date   15 4, 2015
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Valentine project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2015 Seamly2D project
 **  <https://github.com/fashionfreedom/seamly2d> All Rights Reserved.
 **
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
 **  along with Seamly2D.  If not, see <http://www.gnu.org/licenses/>.
 **
 *************************************************************************/

#include "tst_vposter.h"
#include "../vlayout/vposter.h"
#include "../vmisc/def.h"

#include <QImage>
#include <QPrinter>
#include <QtTest>

//---------------------------------------------------------------------------------------------------------------------
TST_VPoster::TST_VPoster(QObject *parent) :
    QObject(parent)
{
}

//---------------------------------------------------------------------------------------------------------------------
// cppcheck-suppress unusedFunction
void TST_VPoster::BigPoster()
{
    QPrinter printer;
    printer.setResolution(96);// By default
    printer.setPageSize(printer.pageLayout().pageSize());
    printer.setFullPage(true);
    // We need to set full page because otherwise QPrinter->pageRect returns different values in Windows and Linux

    //sets the margins to 0 to perform the test.
    const qreal left = 0, top = 0, right = 0, bottom = 0;

    printer.setPageMargins(QMarginsF(left, top, right, bottom), QPageLayout::Millimeter);

    const QRect image(0, 0, 2622, 3178); // Little bit bigger than A1
    VPoster posterazor(&printer);
    const QVector<PosterData> poster = posterazor.Calc(image, 0, PageOrientation::Portrait);

    QCOMPARE(poster.size(), 12);

    for (int i=0; i < poster.size(); i++)
    {
        QCOMPARE(poster.at(i).rect.size(), PageRect(printer).size());
    }
}

//---------------------------------------------------------------------------------------------------------------------
// cppcheck-suppress unusedFunction
void TST_VPoster::SmallPoster()
{
    QPrinter printer;
    printer.setResolution(96);// By default
    printer.setPageSize(printer.pageLayout().pageSize());

    const QRect image(0, 0, 700, 1000); // Little bit less than A4
    VPoster posterazor(&printer);
    const QVector<PosterData> poster = posterazor.Calc(image, 0, PageOrientation::Portrait);

    QCOMPARE(poster.size(), 1);

    QCOMPARE(poster.at(0).rect.size(), PageRect(printer).size());
}

//---------------------------------------------------------------------------------------------------------------------
QRect TST_VPoster::PageRect(const QPrinter &printer) const
{
    // Because the Point unit is defined to be 1/72th of an inch
    // we can't use method pageRect(QPrinter::Point). Our dpi different can be different.
    // We convert value yourself to pixels.
    const QRectF rect = printer.pageRect(QPrinter::Millimeter);
    QRect pageRect(qFloor(ToPixel(rect.x())), qFloor(ToPixel(rect.y())),
                   qFloor(ToPixel(rect.width())), qFloor(ToPixel(rect.height())));
    return pageRect;
}

//---------------------------------------------------------------------------------------------------------------------
qreal TST_VPoster::ToPixel(qreal val) const
{
    return val / 25.4 * PrintDPI; // Mm to pixels with current dpi.
}
