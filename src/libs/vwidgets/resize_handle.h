/******************************************************************************
 **  @file   resize_handle.h
 **  @author DS Caskey
 **  @date   Jul 2, 2022
 **
 **  @brief
 **  @copyright
 **  This source code is part of the Seamly2D project, a pattern making
 **  program, whose allow create and modeling patterns of clothing.
 **  Copyright (C) 2013-2022 Seamly2D project
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
 *****************************************************************************/

#ifndef RESIZE_HANDLE_H
#define RESIZE_HANDLE_H

#include "../vmisc/def.h"

#include <QColor>
#include <QGraphicsItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QMetaObject>
#include <QRectF>
#include <QVector>

class ResizeHandlesItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
private:
    class HandleItem : public QGraphicsRectItem
    {
        public:
                                HandleItem(Position position, ResizeHandlesItem *parent);
            Position            position() const;

        protected:
            void                paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

            virtual QVariant    itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
            virtual void        hoverEnterEvent (QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
            virtual void        hoverLeaveEvent (QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
            virtual void        mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
            virtual void        mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
            virtual void        mouseReleaseEvent (QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
            virtual void        keyReleaseEvent (QKeyEvent *event) Q_DECL_OVERRIDE;

        private:
            QPointF            limitPosition(const QPointF &newPos);

            ResizeHandlesItem *m_parent;
            Position           m_handlePosition;
            Qt::CursorShape    m_handleCursors[9];
            bool               m_isHovered;
            qreal              m_scalingFactor;
    };

public:
    explicit           ResizeHandlesItem(QGraphicsItem *parent = nullptr);
    virtual           ~ResizeHandlesItem() = default;

    virtual int        type() const Q_DECL_OVERRIDE {return Type;}
    enum               {Type = UserType + static_cast<int>(Vis::ResizeHandlesItem)};

    QRectF             boundingRect() const override;
    void               paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void               setTopLeft(const QPointF &pos);
    void               setTop(qreal y);
    void               setTopRight(const QPointF &pos);
    void               setRight(qreal x);
    void               setBottomRight(const QPointF &pos);
    void               setBottom(qreal y);
    void               setBottomLeft(const QPointF &pos);
    void               setLeft(qreal x);
    void               setParentRect(const QRectF &rect);

signals:
    void               sizeChanged(QRectF rect);

private:
    void               updateHandlePositions();

    QList<HandleItem*> m_handleItems;
    QRectF             m_parentRect;
};

#endif //RESIZE_HANDLE_H