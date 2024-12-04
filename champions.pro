
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = champions
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
#    qrc_resources.cpp

HEADERS += \
    Champions.h \
    mainwindow.h

# nlohmann/json 라이브러리 설정
#INCLUDEPATH += /nix/store/gcy3qbgyx1hfpaz2jjk6zzz5zpys4sqy-nlohmann_json-3.11.3/include  # json 헤더 파일 위치 (시스템에 맞게 수정 필요)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# 프로그램 실행 시 필요한 리소스 파일들
RESOURCES += \
    resources.qrc

# 디버그/릴리즈 모드 설정
CONFIG(release, debug|release): DEFINES += QT_NO_DEBUG_OUTPUT
