TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Camera.cpp \
    Shader.cpp \
    Texture.cpp \
    Window.cpp \
    Sphere.cpp \
    Mesh.cpp


LIBS += -L/usr/lib/x86_64-linux-gnu/ -lGLEW -lglfw -lGL

INCLUDEPATH += /usr/lib/x86_64-linux-gnu
DEPENDPATH += /usr/lib/x86_64-linux-gnu

DISTFILES += \
    Shaders/shader.fsh \
    Shaders/shader.vsh \
    data/Shaders/shader.fsh \
    data/Shaders/shader.vsh


HEADERS += \
    Camera.h \
    Shader.h \
    stb_image.h \
    Texture.h \
    Window.h \
    Sphere.h \
    Mesh.h \


copydata.commands = $(COPY_DIR) $$PWD/data $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
