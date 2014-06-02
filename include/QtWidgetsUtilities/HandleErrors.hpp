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

# ifndef QT_WIDGETS_UTILITIES_HANDLE_ERRORS_HPP
# define QT_WIDGETS_UTILITIES_HANDLE_ERRORS_HPP

# include <QString>

# include <utility>
# include <functional>


namespace QtUtilities
{
namespace Widgets
{
class InputController;

/// @brief Handles error returned by f() in specified manner.
class HandleErrors
{
public:
    typedef std::function<QString()> F;
    /// @param f If returned string is empty, it is assumed that no error has
    /// occurred; otherwise, returned string is used as an error message.
    explicit HandleErrors(F f) : f_(std::move(f))
    {}

    /// @brief Calls f_. If it returns an empty string, returns true. Otherwise,
    /// shows inputController's message box with error to user, and then either
    /// calls f_ again or returns false, depending on user's choice.
    /// @param errorMessageTitle Title of the message box.
    /// @param cancelled Makes a difference only in case of error.
    /// If not nullptr, Cancel button is present in error dialog;
    /// *cancelled is set to true if user cancels the operation; is set to false
    /// otherwise (success or if user chose to ignore error).
    /// @return true if the last call to f_ returned empty string.
    bool blocking(InputController & inputController,
                  const QString & errorMessageTitle,
                  bool * cancelled = nullptr);
    /// @brief Calls f_. If it returns an empty string, returns true. Otherwise,
    /// prints QT_WIDGETS_UTILITIES_ERROR_PREFIX, error message to stderr and
    /// returns false.
    bool nonBlocking();

private:
    std::function<QString()> f_;
};

}

}

# endif // QT_WIDGETS_UTILITIES_HANDLE_ERRORS_HPP
