QT += widgets
RC_ICONS = images\OrangeCode.ico

requires(qtConfig(filedialog))

HEADERS         = highlighter.h \
                  codeeditor.h \
                  mainwindow.h \
                  oc_start.h
SOURCES         = highlighter.cpp \
                  codeeditor.cpp \
                  mainwindow.cpp \
                  main.cpp \
                  oc_start.cpp

INSTALLS += target

RESOURCES += \
    images.qrc
