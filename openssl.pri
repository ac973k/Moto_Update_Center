versionAtLeast(QT_VERSION, "5.14.0") {
    ANDROID_EXTRA_LIBS += \
        $$PWD/lib/libcrypto_1_1.so \
        $$PWD/lib/libssl_1_1.so
} else {
    equals(ANDROID_TARGET_ARCH,armeabi-v7a) {
        ANDROID_EXTRA_LIBS += \
            $$PWD/lib/libcrypto_1_1.so \
            $$PWD/lib/libssl_1_1.so
    }
}
