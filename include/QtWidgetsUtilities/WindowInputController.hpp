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

# ifndef QT_WIDGETS_UTILITIES_WINDOW_INPUT_CONTROLLER_HPP
# define QT_WIDGETS_UTILITIES_WINDOW_INPUT_CONTROLLER_HPP

# include "InputController.hpp"

# include <QWidget>


namespace QtUtilities
{
namespace Widgets
{
class WindowInputController : public InputController
{
public:
    /// @param window Window to be automatically shown when blocking and to be
    /// used as message box parent. Must be a valid pointer.
    explicit WindowInputController(QWidget * window);

    bool blocked() const { return blocked_; }

    /// @brief Calls showWindow(window_) if block == true.
    /// Sets blocked_ to block.
    void blockInput(bool block) override;

private:
    int showMessageImplementation(
        const QString & title, const QString & text,
        QMessageBox::StandardButtons buttons,
        QMessageBox::StandardButton defaultButton,
        QMessageBox::Icon icon) override;

    QStringList getFileOrDirNames(const QString & title,
                                  QFileDialog::AcceptMode acceptMode,
                                  QFileDialog::FileMode fileMode) override;


    QWidget * const window_;
    /// Blocked input flag.
    bool blocked_ = false;
};

}

}

# endif // QT_WIDGETS_UTILITIES_WINDOW_INPUT_CONTROLLER_HPP
