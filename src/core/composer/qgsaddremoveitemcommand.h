/***************************************************************************
                          qgsaddremoveitemcommand.h
                          ------------------------
    begin                : 2010-11-27
    copyright            : (C) 2010 by Marco Hugentobler
    email                : marco dot hugentobler at sourcepole dot ch
***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSADDREMOVEITEMCOMMAND_H
#define QGSADDREMOVEITEMCOMMAND_H

#include <QUndoCommand>
#include "qgis.h"

#include "qgis_core.h"

#define SIP_NO_FILE

class QgsComposerItem;
class QgsComposition;

/**
 * \ingroup core
 * A composer command class for adding / removing composer items. If mState == Removed, the command owns the item
 * \note Not available in Python bindings
 * \deprecated Will be removed in QGIS 3.2
*/
class CORE_EXPORT QgsAddRemoveItemCommand: public QObject, public QUndoCommand
{
    Q_OBJECT

  public:

    enum State
    {
      Added = 0,
      Removed
    };

    //! Constructor for QgsAddRemoveItemCommand
    QgsAddRemoveItemCommand( State s, QgsComposerItem *item, QgsComposition *c, const QString &text, QUndoCommand *parent SIP_TRANSFERTHIS = nullptr );
    ~QgsAddRemoveItemCommand() override;

    void redo() override;
    void undo() override;

  signals:
    void itemAdded( QgsComposerItem *item );
    void itemRemoved( QgsComposerItem *item );

  private:
    QgsComposerItem *mItem = nullptr;
    QgsComposition *mComposition = nullptr;
    State mState;
    bool mFirstRun; //flag to prevent execution when the command is pushed to the QUndoStack

    //changes between added / removed state
    void switchState();
};

#endif // QGSADDREMOVEITEMCOMMAND_H
