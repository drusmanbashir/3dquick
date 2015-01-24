#-------------------------------------------------
#
# Project created by QtCreator 2015-01-14T01:57:06
#
#-------------------------------------------------

QT       += qml quick opengl

QT       -= gui

TARGET = 3dqtquick
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += \
            include \
            /home/ubashir/programs/assimp/assimp-3.1.1/include \
            source\

HEADERS += \
    include/ubMesh.h \
    include/lightingtechnique.h \
    include/technique.h \
    include/ogldev_util.h \
    include/ogldev_types.h \
    include/ogldev_texture.h \
    include/ogldev_math_3d.h \
    include/camera.h \
    include/pipeline.h \
    include/utils.h \
#    include/picking_technique.h \
#    include/picking_texture.h \
    include/simple_color_technique.h \
    include/render_callbacks.h \
    meshquick.h \


SOURCES += \
        main.cpp \
        source/camera.cpp \
        source/pipeline.cpp \
        source/ubMesh.cpp \
        source/lightingtechnique.cpp \
        source/technique.cpp \
        source/ogldev_util.cpp\
        source/math_3d.cpp \
        source/ogldev_texture.cpp \
#        source/picking_technique.cpp \
#        source/picking_texture.cpp \
        source/simple_color_technique.cpp \
        meshquick.cpp \


RESOURCES += \
            3dqtquick.qrc \
            shaders.qrc \
            textures.qrc \
    models.qrc

#target.path = $$[QT_INSTALL_EXAMPLES]/quick/scenegraph/textureinsgnode
INSTALLS += target

linux|win32: LIBS += -lassimp

QT += androidextras
#ASSIMP_PATH = /home/ubashir/programs/assimp/assimp-3.1.1
#android {
#INCLUDEPATH += /home/ubashir/programs/android-toolchain/user/include
#LIBS +=\
#        -L/home/ubashir/programs/assimp/assimp-3.1.1/libs/armeabi-v7a/
#        -lassimp
#}

macx {
    ASSIMP_PATH = /usr/local/Cellar/assimp/3.1.1
     INCLUDEPATH+= $${ASSIMP_PATH}/include \
            /usr/local/include/glm/\
            PKGCONFIG +=/usr/local/Cellar/assimp/3.1.1/lib/pkgconfig/assimp.pc
    LIBS += -L$${ASSIMP_PATH}/lib \
            -lassimp

}

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/../../programs/assimp/assimp-3.1.1/libs/armeabi-v7a/libassimp.so
     $$PWD/../../programs/assimp/assimp-3.1.1/libs/armeabi-v7a/libassimp.so.3
}

DISTFILES += \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/AndroidManifest.xml \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
