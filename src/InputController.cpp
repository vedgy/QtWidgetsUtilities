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

# include "InputController.hpp"

# include <QString>
# include <QStringList>
# include <QFileDialog>

# include <cassert>
# include <utility>


namespace QtUtilities
{
namespace Widgets
{
InputController::~InputController() noexcept = default;

int InputController::showMessage(
    const QString & title, const QString & text,
    const QMessageBox::StandardButtons buttons,
    const QMessageBox::StandardButton defaultButton,
    const QMessageBox::Icon icon)
{
    return showMessageImplementation(title, text, buttons, defaultButton, icon);
}

QString InputController::getFileOrDirName(
    const QString & title, const QFileDialog::AcceptMode acceptMode,
    const QFileDialog::FileMode fileMode)
{
    assert(fileMode != QFileDialog::ExistingFiles);
    QStringList names = getFileOrDirNames(title, acceptMode, fileMode);
    assert(names.size() <= 1 &&
           "More than one name must never appear here!");
    return names.empty() ? QString() : std::move(names.back());
}

QStringList InputController::getOpenFileNames(const QString & title)
{
    return getFileOrDirNames(title, QFileDialog::AcceptOpen,
                             QFileDialog::ExistingFiles);
}

}

}
