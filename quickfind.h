/*
 * Copyright (C) 2010 Nicolas Bonnefon and other contributors
 *
 * This file is part of glogg.
 *
 * glogg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * glogg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with glogg.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QUICKFIND_H
#define QUICKFIND_H

#include <QPoint>

class QuickFindPattern;
class AbstractLogData;
class Portion;

// Represents a search made with Quick Find (without its results)
// it keeps a pointer to a set of data and to a QuickFindPattern which
// are used for the searches. (the caller retains ownership of both).
class QuickFind
{
  public:
    // Construct a search
    QuickFind( const AbstractLogData* const logData, Selection* selection,
            const QuickFindPattern* const quickFindPattern );

    // Set the starting point that will be used by the next search
    void setSearchStartPoint( QPoint startPoint );

    // Used for incremental searches
    // Return the first occurence of the passed pattern from the starting
    // point.  These searches don't use the QFP and don't change the
    // starting point.
    Portion incrementallySearchForward( const QString& incPattern );
    Portion incrementallySearchBackward( const QString& incPattern );

    // Used for 'normal' (n/N) QF searches
    // Return the line of the first occurence of the QFP and
    // update the selection. It returns -1 if nothing is found.
    int searchNext();
    int searchPrevious();

  private:
    // Pointers to external objects
    const AbstractLogData* const logData_;
    Selection* selection_;
    const QuickFindPattern* const quickFindPattern_;
};

#endif
