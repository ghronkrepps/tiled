/*
 * tilesetview.h
 * Copyright 2008-2010, Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
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

#ifndef TILESETVIEW_H
#define TILESETVIEW_H

#include "tilesetmodel.h"

#include <QTableView>

namespace Tiled {
namespace Internal {

class MapDocument;
class Zoomable;

/**
 * The tileset view. May only be used with the TilesetModel.
 */
class TilesetView : public QTableView
{
    Q_OBJECT

public:
    TilesetView(QWidget *parent = 0);

    /**
     * Sets the map document associated with the tileset to be displayed, which
     * is needed for the undo support.
     */
    void setMapDocument(MapDocument *mapDocument);

    QSize sizeHint() const;

    int sizeHintForColumn(int column) const;
    int sizeHintForRow(int row) const;

    void setZoomable(Zoomable *zoomable);
    Zoomable *zoomable() const { return mZoomable; }

    /**
     * Returns the scale at which the tileset is displayed.
     */
    qreal scale() const;

    bool drawGrid() const { return mDrawGrid; }

    /**
     * Convenience method that returns the model as a TilesetModel.
     */
    TilesetModel *tilesetModel() const
    { return static_cast<TilesetModel *>(model()); }

    /**
     * Returns whether terrain editing is enabled.
     * \sa terrainId
     */
    bool isEditTerrain() const { return mEditTerrain; }

    /**
     * Sets whether terrain editing is enabled.
     * \sa setTerrainId
     */
    void setEditTerrain(bool enabled);

    /**
     * Sets whether terrain editing is in "erase" mode.
     * \sa setEditTerrain
     */
    void setEraseTerrain(bool erase) { mEraseTerrain = erase; }
    bool isEraseTerrain() const { return mEraseTerrain; }

    /**
     * The id of the terrain currently being specified. Set to -1 for erasing
     * terrain info.
     */
    int terrainId() const { return mTerrainId; }

    /**
     * Sets the id of the terrain to specify on the tiles. An id of -1 allows
     * for erasing terrain information.
     */
    void setTerrainId(int terrainId);

    QModelIndex hoveredIndex() const { return mHoveredIndex; }
    int hoveredCorner() const { return mHoveredCorner; }

signals:
    void createNewTerrain(Tile *tile);
    void terrainImageSelected(Tile *tile);

protected:
    bool event(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void leaveEvent(QEvent *);
    void wheelEvent(QWheelEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void createNewTerrain();
    void selectTerrainImage();
    void setDrawGrid(bool drawGrid);

    void adjustScale();

private:
    void applyTerrain();
    void finishTerrainChange();
    Tile *currentTile() const;

    Zoomable *mZoomable;
    MapDocument *mMapDocument;
    bool mDrawGrid;

    bool mEditTerrain;
    bool mEraseTerrain;
    int mTerrainId;
    QModelIndex mHoveredIndex;
    int mHoveredCorner;
    bool mTerrainChanged;
};

} // namespace Internal
} // namespace Tiled

Q_DECLARE_METATYPE(Tiled::Internal::TilesetView *)

#endif // TILESETVIEW_H
