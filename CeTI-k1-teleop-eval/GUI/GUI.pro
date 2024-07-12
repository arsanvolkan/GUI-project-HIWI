QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    background.cpp \
    config.cpp \
    endpaint.cpp \
    endstiffness.cpp \
    endtask.cpp \
    main.cpp \
    mainwindow.cpp \
    questionletter.cpp \
    questionletter_trial.cpp \
    questionstiffness.cpp \
    questionstiffness_trial.cpp \
    selecttask.cpp \
    usabilityquestionnaire.cpp \
    usabilityquestionnaire2.cpp \
    usabilityquestionnaire3.cpp

HEADERS += \
    background.h \
    config.h \
    endpaint.h \
    endstiffness.h \
    endtask.h \
    mainwindow.h \
    questionletter.h \
    questionletter_trial.h \
    questionstiffness.h \
    questionstiffness_trial.h \
    selecttask.h \
    usabilityquestionnaire.h \
    usabilityquestionnaire2.h \
    usabilityquestionnaire3.h

FORMS += \
    background.ui \
    endpaint.ui \
    endstiffness.ui \
    endtask.ui \
    mainwindow.ui \
    questionletter.ui \
    questionletter_trial.ui \
    questionstiffness.ui \
    questionstiffness_trial.ui \
    selecttask.ui \
    usabilityquestionnaire.ui \
    usabilityquestionnaire2.ui \
    usabilityquestionnaire3.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
