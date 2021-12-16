#additional Qt modules
QT += quick qml xml
#QT += network

#Include modules here
include($$modules_dir/Feed/Feed.pri)
include($$modules_dir/NetworkMgr/NetworkMgr.pri)

#Include project files
INCLUDEPATH += $$PWD


SOURCES += main.cpp  \


HEADERS += \
    main.h


RESOURCES += qml/qml.qrc

#LIBS += -L"3rdparty/rapidxml-1.13" -lrapidxml
# Guess not needed, read here: http://rapidxml.sourceforge.net/manual.html


OTHER_FILES +=

#use c++17 compiler flags
CONFIG += c++17

#additional libraries (configured with the feature files in the qmake folder) - libs has to be at the end of the config var
#CONFIG += opencv libs

#Android specific variables - will be ignored in other configuration
ANDROID_PACKAGE_SOURCE_DIR =
ANDROID_EXTRA_LIBS =
OTHER_FILES += $$files($$PWD/android/*)

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH += $$qml_dir
QML_IMPORT_PATH += $$plugin_dir

#copy the executable to the source folder
DLLDESTDIR = $$_PRO_FILE_PWD_

DISTFILES += \
    mydocument.xml
