project (sparkan_cli)

include_directories(include)
include_directories(../coreservice/include/api)
link_directories(../coreservice/)

file(GLOB sparkan_HEADER "include/*.h" "*.h" "../coreservice/include/api/*.h")
file(GLOB sparkan_SRCS "*cpp" "*.c" "src/*.cpp" "src/*.c")
file(GLOB sparkan_RES "res/*qrc")


cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
cmake_policy(SET CMP0063 NEW)
set(QT_MIN_VERSION "5.3.0")
set(KF5_MIN_VERSION "5.2.0")

include_directories ("${PROJECT_SOURCE_DIR}/include")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS 
    Core    # QCommandLineParser, QStringLiteral
    Widgets # QApplication
    Quick
    Qml
)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    CoreAddons      # KAboutData
    I18n            # KLocalizedString
    XmlGui          # KXmlGuiWindow
    TextWidgets     # KTextEdit
)

qt5_add_resources(RESOURCES ${sparkan_RES})

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1y -pedantic")
add_executable(sparkan ${sparkan_SRCS} ${sparkan_HEADER} ${RESOURCES} authview.ui)

target_link_libraries(sparkan coreservice)
target_link_libraries(sparkan
    Qt5Network
    Qt5::Qml
    Qt5::Quick
    Qt5::Widgets
    Qt5WebKit
    Qt5WebKitWidgets
    KF5::CoreAddons
    KF5::I18n
    KF5::XmlGui
    KF5::TextWidgets
)

install(TARGETS sparkan  ${INSTALL_TARGETS_DEFAULT_ARGS}) 
