#additional Qt modules
QT += quick qml

#Include modules here
include($$modules_dir/Feed/Feed.pri)

#Include project files
INCLUDEPATH += $$PWD \
                3rdparty/rapidxml-1.13 \
                C:/libs/Qt/6.2.0/mingw81_64/lib


SOURCES += main.cpp  \


HEADERS += \


RESOURCES += qml/qml.qrc

LIBS += -L"3rdparty/rapidxml-1.13" -lrapidxml \
        C:/libs/Qt/6.2.0/mingw81_64/lib/libcurl.a \
        C:/libs/Qt/6.2.0/mingw81_64/lib/libcurl.dll.a


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

DISTFILES +=
