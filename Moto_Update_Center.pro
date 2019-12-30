QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

include(android_openssl/openssl.pri)

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    motoupdater.cpp

HEADERS += \
    QZip/qzipreader_p.h \
    QZip/qzipwriter_p.h \
    motoupdater.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android_openssl/LICENSE \
    android_openssl/README.md \
    android_openssl/arm/libcrypto_1_1.so \
    android_openssl/arm/libssl_1_1.so \
    android_openssl/arm64/libcrypto_1_1.so \
    android_openssl/arm64/libssl_1_1.so \
    android_openssl/build_ssl.sh \
    android_openssl/x86/libcrypto_1_1.so \
    android_openssl/x86/libssl_1_1.so \
    android_openssl/x86_64/libcrypto_1_1.so \
    android_openssl/x86_64/libssl_1_1.so

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android

}
