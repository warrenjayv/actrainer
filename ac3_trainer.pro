QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    err.cpp \
    main.cpp \
    ac3.cpp \
    piper.cpp \
    process_handler.cpp \
    sonar.cpp

HEADERS += \
    ../../../../../Program Files (x86)/msys64/home/six/projects/luna.systems.external/six/dinput/utilities/util-writer.h \
    ../../../../../Program Files (x86)/msys64/home/six/projects/luna.systems.external/six/dinput/utilities/util-writer.h \
    ac3.h \
    err.h \
    piper.h \
    process_handler.h \
    sonar.h \
    vstructs.h

FORMS += \
    ac3.ui \
    err.ui \
    process_handler.ui \
    sonar.ui

TRANSLATIONS += \
    ac3_trainer_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
