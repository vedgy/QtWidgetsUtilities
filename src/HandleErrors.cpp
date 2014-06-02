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

# include "HandleErrors.hpp"

# include "InputController.hpp"

# include <QtCoreUtilities/String.hpp>

# include <QString>
# include <QMessageBox>

# include <iostream>


namespace QtUtilities
{
namespace Widgets
{
bool HandleErrors::blocking(InputController & inputController,
                            const QString & errorMessageTitle,
                            bool * const cancelled)
{
    while (true) {
        const QString errorMessage = f_();
        if (errorMessage.isEmpty()) {
            if (cancelled != nullptr)
                * cancelled = false;
            return true;
        }

        QMessageBox::StandardButtons buttons =
            QMessageBox::Retry | QMessageBox::Ignore;
        if (cancelled != nullptr)
            buttons |= QMessageBox::Cancel;
        const auto selectedButton =
            inputController.showMessage(errorMessageTitle, errorMessage,
                                        buttons, QMessageBox::Retry);

        if (selectedButton != QMessageBox::Retry) {
            if (cancelled != nullptr)
                * cancelled = selectedButton == QMessageBox::Cancel;
            return false;
        }
    }
}

bool HandleErrors::nonBlocking()
{
    const QString errorMessage = f_();
    if (errorMessage.isEmpty())
        return true;
    std::cerr << QT_WIDGETS_UTILITIES_ERROR_PREFIX
              << QtUtilities::qStringToString(errorMessage) << std::endl;
    return false;
}

}

}
