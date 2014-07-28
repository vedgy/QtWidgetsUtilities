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

# ifndef QT_WIDGETS_UTILITIES_INPUT_CONTROLLER_HPP
# define QT_WIDGETS_UTILITIES_INPUT_CONTROLLER_HPP

# include <QString>
# include <QStringList>
# include <QMessageBox>
# include <QFileDialog>

# include <cassert>


namespace QtUtilities
{
namespace Widgets
{
/// @brief Can be used to prevent unforeseen execution order when non-GUI
/// user input is received while GUI is blocked by modal dialog.
/// Passing reference or pointer to InputController provides classes/functions
/// with interface for blocking non-GUI user input.
class InputController
{
public:
    /// @brief Blocks/unblocks some non-GUI user input.
    /// @param block If true, input will be blocked; if false - unblocked.
    /// WARNING: recursive blocking and redundant unblocking are forbidden.
    virtual void blockInput(bool block) = 0;

    /// @brief Shows message box and handles input blocking/unblocking.
    /// @param title Title of the message box.
    /// @param text Text of the message box.
    /// @param buttons Buttons to be displayed in the message box.
    /// @param defaultButton Button that will be set as default and escape
    /// button of the message box unless it is equal to QMessageBox::NoButton.
    /// @param icon Message box's icon.
    /// @return Button that was selected by user.
    int showMessage(
        const QString & title, const QString & text,
        QMessageBox::StandardButtons buttons = QMessageBox::Ok,
        QMessageBox::StandardButton defaultButton = QMessageBox::NoButton,
        QMessageBox::Icon icon = QMessageBox::Critical) {
        return showMessageImplementation(
                   title, text, buttons, defaultButton, icon);
    }

    /// @brief Asks user for file or directory.
    /// @param title Title of the file dialog.
    /// @return File or directory selected by user. If no item was
    /// selected, that is, operation was cancelled, empty string.
    /// WARNING: never pass fileMode equal to QFileDialog::ExistingFiles.
    QString getFileOrDirName(const QString & title,
                             QFileDialog::AcceptMode acceptMode,
                             QFileDialog::FileMode fileMode) {
        assert(fileMode != QFileDialog::ExistingFiles);
        QStringList names = getFileOrDirNames(title, acceptMode, fileMode);
        assert(names.size() <= 1 &&
               "More than one name must never appear here!");
        return names.empty() ? QString() : names.back();
    }

    /// @brief Asks user for one or more files to be opened for reading.
    /// @param title Title of the file dialog.
    /// @return List of files selected by user. If no item was
    /// selected, that is, operation was cancelled, empty list.
    QStringList getOpenFileNames(const QString & title) {
        return getFileOrDirNames(title, QFileDialog::AcceptOpen,
                                 QFileDialog::ExistingFiles);
    }

protected:
    InputController() = default;
    ~InputController() = default;

    virtual int showMessageImplementation(
        const QString & title, const QString & text,
        QMessageBox::StandardButtons buttons,
        QMessageBox::StandardButton defaultButton, QMessageBox::Icon icon) = 0;

    virtual QStringList getFileOrDirNames(const QString & title,
                                          QFileDialog::AcceptMode acceptMode,
                                          QFileDialog::FileMode fileMode) = 0;

private:
    Q_DISABLE_COPY(InputController)
};

}

}

# endif // QT_WIDGETS_UTILITIES_INPUT_CONTROLLER_HPP
