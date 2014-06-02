cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Depends on Qt, QtCoreUtilities.
set(Target_Name QtWidgetsUtilities)
set(CAP_Target_Name QT_WIDGETS_UTILITIES)
message(<${Target_Name}>)

## vedgTools/CMakeModules path boilerplate.
include(vedgTools/CMakeLicense OPTIONAL RESULT_VARIABLE CMakeModulesWasIncluded)
if(CMakeModulesWasIncluded STREQUAL NOTFOUND)
    set(PATH_TO_CMAKE_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PATH_TO_CMAKE_MODULES})
    message("Including CMakeModules.")
    include(vedgTools/CMakeLicense)
endif()

# NOTE: QtCore and QtWidgets/QtGui modules are used by this library.
include(vedgTools/LibraryQtStart)

include(vedgTools/LibraryQtCoreUtilitiesStart)

if(NOT DEFINED Target_Error_Prefix)
    include(vedgTools/AddErrorPrefixDefinition)
endif()
add_definitions(-DQT_WIDGETS_UTILITIES_ERROR_PREFIX=${Target_Error_Prefix})

if(DEBUG_QT_WIDGETS_UTILITIES)
    add_definitions(-DDEBUG_QT_WIDGETS_UTILITIES)
endif()

include(vedgTools/LibraryWithQtInit)


include(vedgTools/LibraryFindQt)
libraryFindQt(Qt5Core Qt5Widgets . QTCORE QTGUI)

include(vedgTools/LibraryGetQtCoreUtilitiesPublicHeaders)


set(Sources_Path src)

include_directories(
    ${QtCoreUtilities_PublicHeaders_Path}
    ${${Target_Name}_PublicHeaders_Path}
    ${${Target_Name}_PublicHeaders_Path}/${Target_Name}
)

set(Sources
    ${Sources_Path}/Miscellaneous.cpp ${Sources_Path}/TooltipShower.cpp
    ${Sources_Path}/WindowInputController.cpp ${Sources_Path}/HandleErrors.cpp
)


include(vedgTools/LibraryAddTarget)

include(vedgTools/LinkQt)
linkQt(${Target_Name} Core Widgets . ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

include(vedgTools/LibraryLinkQtCoreUtilitiesToTarget)


set_target_properties(${Target_Name} PROPERTIES PUBLIC_HEADER
    "Miscellaneous.hpp;TooltipShower.hpp;InputController.hpp;WindowInputController.hpp;HandleErrors.hpp"
)

message(</${Target_Name}>)
