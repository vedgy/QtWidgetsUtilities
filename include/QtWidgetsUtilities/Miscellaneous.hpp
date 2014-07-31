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

# ifndef QT_WIDGETS_UTILITIES_MISCELLANEOUS_HPP
# define QT_WIDGETS_UTILITIES_MISCELLANEOUS_HPP

# include <QtGlobal>
# include <QSizePolicy>
# include <QSpacerItem>
# include <QLayout>
# include <QWidget>

# include <cassert>


QT_FORWARD_DECLARE_CLASS(QString)
QT_FORWARD_DECLARE_CLASS(QFormLayout)
QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QTabWidget)

namespace QtUtilities
{
namespace Widgets
{
/// @brief Ensures that window is visible (not hidden and not minimized),
/// preserves maximized state.
/// @param window Must be a valid pointer.
void showWindow(QWidget * window);
/// @brief Calls showWindow(window) and activates window (gives focus).
void showAndActivateWindow(QWidget * window);

inline void setFixedSizePolicy(QWidget * widget)
{
    assert(widget != nullptr);
    widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

inline void addSpacing(QLayout * layout, int width = 1, int height = 10)
{
    assert(layout != nullptr);
    layout->addItem(new QSpacerItem(width, height));
}

/// @return Label with given text and parent that can be used as a caption.
/// @param boldText If true, label's text is bold.
/// @param fontPointSizeIncrement pt-size to be added to default QLabel font
/// size. Allows to increase (or decrease) label's text size.
QLabel * getCaption(const QString & text, QWidget * parent = nullptr,
                    bool boldText = true, int fontPointSizeIncrement = 2);

/// @brief Adds tab wrapped in scroll area with label=tabLabel to widget.
/// NOTE: widget and tab must be valid pointers.
void addScrollableTab(QTabWidget * widget,
                      QWidget * tab, const QString & tabLabel);

constexpr int subWidgetIndent() noexcept { return 30; }
/// @brief Adds (labelText, field) row indented by subWidgetIndent() to layout.
/// NOTE: layout and field must be valid pointers.
void addSubWidget(QFormLayout * layout, const QString & labelText,
                  QWidget * field);

}

}

# endif // QT_WIDGETS_UTILITIES_MISCELLANEOUS_HPP
