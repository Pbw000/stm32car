QT       += core gui bluetooth


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bluetooth_conn.cpp \
    bluetooth_serial.cpp \
    config_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    route.cpp

HEADERS += \
    bluetooth_conn.h \
    bluetooth_serial.h \
    config_dialog.h \
    joystick.h \
    mainwindow.h \
    route.h

FORMS += \
    bluetooth_conn.ui \
    bluetooth_serial.ui \
    config_dialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

RC_FILE +=logo.rc

DISTFILES += \
    ../Remote_Controller.pro/AndroidManifest.xml \
    ../Remote_Controller.pro/AndroidManifest.xml \
    ../Remote_Controller.pro/build.gradle \
    ../Remote_Controller.pro/build.gradle \
    ../Remote_Controller.pro/gradle.properties \
    ../Remote_Controller.pro/gradle/wrapper/gradle-wrapper.jar \
    ../Remote_Controller.pro/gradle/wrapper/gradle-wrapper.properties \
    ../Remote_Controller.pro/gradlew \
    ../Remote_Controller.pro/gradlew.bat \
    ../Remote_Controller.pro/res/values/libs.xml \
    ../Remote_Controller.pro/res/values/libs.xml \
    ../Remote_Controller.pro/res/xml/qtprovider_paths.xml \
    ../Remote_Controller.pro/res/xml/qtprovider_paths.xml \
    android/AndroidManifest.xml \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/res/xml/qtprovider_paths.xml \
    logo.ico \
    logo.rc

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/../Remote_Controller.pro
}

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/../Remote_Controller.pro
}
