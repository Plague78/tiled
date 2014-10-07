/*
 * changemapproperty.cpp
 * Copyright 2012, Emmanuel Barroga emmanuelbarroga@gmail.com
 *
 * This file is part of Tiled.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "changemapproperty.h"

#include "map.h"
#include "mapdocument.h"
#include "objectgroup.h"

#include <QCoreApplication>

using namespace Tiled;
using namespace Tiled::Internal;

ChangeMapProperty::ChangeMapProperty(MapDocument *mapDocument,
                                     const QColor &backgroundColor)
    : QUndoCommand(QCoreApplication::translate("Undo Commands",
                                               "Change Background Color"))
    , mMapDocument(mapDocument)
    , mProperty(BackgroundColor)
    , mBackgroundColor(backgroundColor)
{
}

ChangeMapProperty::ChangeMapProperty(MapDocument *mapDocument,
                                     Map::Orientation orientation)
    : QUndoCommand(QCoreApplication::translate("Undo Commands",
                                               "Change Orientation"))
    , mMapDocument(mapDocument)
    , mProperty(Orientation)
    , mOrientation(orientation)
{
}

ChangeMapProperty::ChangeMapProperty(MapDocument *mapDocument,
                                     Map::RenderOrder renderOrder)
    : QUndoCommand(QCoreApplication::translate("Undo Commands",
                                               "Change Render Order"))
    , mMapDocument(mapDocument)
    , mProperty(RenderOrder)
    , mRenderOrder(renderOrder)
{
}

ChangeMapProperty::ChangeMapProperty(MapDocument *mapDocument,
                                     Map::LayerDataFormat layerDataFormat)
    : QUndoCommand(QCoreApplication::translate("Undo Commands",
                                               "Change Layer Data Format"))
    , mMapDocument(mapDocument)
    , mProperty(LayerDataFormat)
    , mLayerDataFormat(layerDataFormat)
{
}

void ChangeMapProperty::redo()
{
    swap();
}

void ChangeMapProperty::undo()
{
    swap();
}

void ChangeMapProperty::swap()
{
    Map *map = mMapDocument->map();

    switch (mProperty) {
    case Orientation: {
        const Map::Orientation orientation = map->orientation();
        map->setOrientation(mOrientation);
        mOrientation = orientation;
        mMapDocument->createRenderer();
        break;
    }
    case RenderOrder: {
        const Map::RenderOrder renderOrder = map->renderOrder();
        map->setRenderOrder(mRenderOrder);
        mRenderOrder = renderOrder;
        break;
    }
    case BackgroundColor: {
        const QColor backgroundColor = map->backgroundColor();
        map->setBackgroundColor(mBackgroundColor);
        mBackgroundColor = backgroundColor;
        break;
    }
    case LayerDataFormat: {
        const Map::LayerDataFormat layerDataFormat = map->layerDataFormat();
        map->setLayerDataFormat(mLayerDataFormat);
        mLayerDataFormat = layerDataFormat;
        break;
    }
    }

    mMapDocument->emitMapChanged();
}