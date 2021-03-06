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

# ifndef QT_WIDGETS_UTILITIES_TOOLTIP_SHOWER_HPP
# define QT_WIDGETS_UTILITIES_TOOLTIP_SHOWER_HPP

# include <QtGlobal>
# include <QPoint>
# include <QString>
# include <QObject>


QT_FORWARD_DECLARE_CLASS(QWidget)

namespace QtUtilities
{
namespace Widgets
{
class TooltipShower : public QObject
{
public:
    /// @param widget Is used to determine the appropriate screen on
    /// multi-head systems.
    explicit TooltipShower(QWidget * widget = nullptr) : widget_(widget)
    {}

    /// @brief Shows tooltip with passed text at the specified position after
    /// a short delay.
    void show(QPoint position, QString text);

private:
    void timerEvent(QTimerEvent *) override;

    QPoint position_;
    QString text_;
    QWidget * const widget_;
    int timerId_ = 0;
};

}

}

# endif // QT_WIDGETS_UTILITIES_TOOLTIP_SHOWER_HPP
