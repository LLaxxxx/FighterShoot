TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += /usr/lib64/liballegro.so \
        /usr/lib64/liballegro_acodec.so \
        /usr/lib64/liballegro_audio.so \
        /usr/lib64/liballegro_color.so \
        /usr/lib64/liballegro_dialog.so \
        /usr/lib64/liballegro_font.so \
        /usr/lib64/liballegro_image.so \
        /usr/lib64/liballegro_main.so \
        /usr/lib64/liballegro_memfile.so \
        /usr/lib64/liballegro_physfs.so \
        /usr/lib64/liballegro_primitives.so \
        /usr/lib64/liballegro_ttf.so \
        /usr/lib64/liballegro_video.so \


SOURCES += \
        main.c \
    play.c \
    fighter.c \
    bullet.c \
    combat.c \
    audio.c \
    map_move_shoot.c

HEADERS += \
    play.h \
    fighter.h \
    bullet.h \
    combat.h \
    audio.h \
    map_move_shoot.h
