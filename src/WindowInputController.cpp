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

# ifdef DEBUG_QT_WIDGETS_UTILITIES
# include <iostream>
# endif


# include "WindowInputController.hpp"

# include "Miscellaneous.hpp"

# include <QStringList>
# include <QPointer>
# include <QDialog>
# include <QMessageBox>
# include <QFileDialog>

# include <cassert>
# include <iostream>


namespace QtUtilities
{
namespace Widgets
{
WindowInputController::WindowInputController(QWidget * const window)
    : window_(window)
{
    assert(window_ != nullptr);
}

void WindowInputController::blockInput(const bool block)
{
    assert(blocked_ != block &&
           "Recursive blocking and redundant unblocking are forbidden.");
    blocked_ = block;
    if (block)
        showWindow(window_);
}


int WindowInputController::showMessageImplementation(
    const QString & title, const QString & text,
    const QMessageBox::StandardButtons buttons,
    const QMessageBox::StandardButton defaultButton,
    const QMessageBox::Icon icon)
{
    blockInput(true);

    QPointer<QMessageBox> messageBox = new QMessageBox(
        icon, title, text, buttons, window_);
    if (defaultButton != QMessageBox::NoButton) {
        messageBox->setDefaultButton(defaultButton);
        messageBox->setEscapeButton(defaultButton);
    }

    const auto selectedButton = messageBox->exec();
    if (messageBox == nullptr) {
        std::cerr << QT_WIDGETS_UTILITIES_ERROR_PREFIX
                  "Message box was destroyed unexpectedly!" << std::endl;
        return QMessageBox::NoButton; // window_ is already destroyed!!!
    }
# ifdef DEBUG_QT_WIDGETS_UTILITIES
    std::cout << "Message box was closed." << std::endl;
# endif
    messageBox->deleteLater();
    blockInput(false);
    return selectedButton;
}

QStringList WindowInputController::getFileOrDirNames(
    const QString & title, const QFileDialog::AcceptMode acceptMode,
    const QFileDialog::FileMode fileMode)
{
    blockInput(true);

    QPointer<QFileDialog> fileDialog = new QFileDialog(window_, title);
    fileDialog->setAcceptMode(acceptMode);
    if (acceptMode == QFileDialog::AcceptOpen)
        fileDialog->setOption(QFileDialog::ReadOnly, true);
    fileDialog->setFileMode(fileMode);
    fileDialog->setOption(QFileDialog::DontUseNativeDialog, true);

    const auto dialogCode = fileDialog->exec();
    if (fileDialog == nullptr) {
        std::cerr << QT_WIDGETS_UTILITIES_ERROR_PREFIX
                  "File dialog was destroyed unexpectedly!" << std::endl;
        return QStringList(); // window_ is already destroyed!!!
    }
# ifdef DEBUG_QT_WIDGETS_UTILITIES
    std::cout << "File dialog was closed." << std::endl;
# endif
    fileDialog->deleteLater();
    blockInput(false);
    return dialogCode == QDialog::Accepted ?
           fileDialog->selectedFiles() : QStringList();
}

}

}
