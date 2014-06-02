/*
 This file is part of vedgTools/QtWidgetsUtilities.
 Copyright (C) 2014 Igor Kushnir <igorkuo AT Google mail>

 vedgTools/QtWidgetsUtilities is free software: you can redistribute it and/or
 modify it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 vedgTools/QtWidgetsUtilities is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with
 vedgTools/QtWidgetsUtilities.  If not, see <http://www.gnu.org/licenses/>.
*/

# include "TooltipShower.hpp"

# include <QPoint>
# include <QString>
# include <QToolTip>

# include <utility>


namespace QtUtilities
{
namespace Widgets
{
void TooltipShower::show(QPoint position, QString text)
{
    position_ = std::move(position);
    text_ = std::move(text);
    killTimer(timerId_);
    timerId_ = startTimer(300);
}

void TooltipShower::timerEvent(QTimerEvent *)
{
    QToolTip::showText(position_, text_, widget_);
    killTimer(timerId_);
    timerId_ = 0;
}

}

}
