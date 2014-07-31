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

# include "Miscellaneous.hpp"

# include <QString>
# include <QFont>
# include <QHBoxLayout>
# include <QFormLayout>
# include <QWidget>
# include <QLabel>
# include <QScrollArea>
# include <QTabWidget>

# include <cassert>


namespace QtUtilities
{
namespace Widgets
{
void showWindow(QWidget * const window)
{
    assert(window != nullptr);
    const Qt::WindowStates state = window->windowState();
    if (state & Qt::WindowMinimized) {
        if (state & Qt::WindowMaximized)
            window->showMaximized();
        else
            window->showNormal();
    }
    else
        window->show();
}

void showAndActivateWindow(QWidget * const window)
{
    showWindow(window);
    window->activateWindow();
}


QLabel * getCaption(const QString & text, QWidget * const parent,
                    const bool boldText, const int fontPointSizeIncrement)
{
    QLabel * const captionLabel = new QLabel(
        boldText ? "<b>" + text + "</b>" : text, parent);
    if (fontPointSizeIncrement != 0) {
        QFont font = captionLabel->font();
        font.setPointSize(font.pointSize() + fontPointSizeIncrement);
        captionLabel->setFont(font);
    }
    return captionLabel;
}


void addScrollableTab(QTabWidget * const parent,
                      QWidget * const widget, const QString & name)
{
    assert(parent != nullptr);
    assert(widget != nullptr);
    QScrollArea * const scrollArea = new QScrollArea(parent);
    scrollArea->setWidget(widget);
    scrollArea->setWidgetResizable(true);
    parent->addTab(scrollArea, name);
}


void addSubWidget(QFormLayout * const layout, const QString & labelText,
                  QWidget * const field)
{
    assert(layout != nullptr);
    assert(field != nullptr);
    QHBoxLayout * const rowLayout = new QHBoxLayout;
    rowLayout->addSpacing(subWidgetIndent());
    rowLayout->addWidget(field);
    layout->addRow("       " + labelText, rowLayout);
}

}

}
