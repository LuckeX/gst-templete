# Note: plugindir is set in configure

##############################################################################
# TODO: change libgstplugin.la to something else, e.g. libmysomething.la     #
##############################################################################
# plugin_LTLIBRARIES = libgstplugin.la libgstaudiofilterexample.la

# ##############################################################################
# # TODO: for the next set of variables, name the prefix if you named the .la, #
# #  e.g. libmysomething.la => libmysomething_la_SOURCES                       #
# #                            libmysomething_la_CFLAGS                        #
# #                            libmysomething_la_LIBADD                        #
# #                            libmysomething_la_LDFLAGS                       #
# ##############################################################################





INCLUDES= -I./case/include
plugin_LTLIBRARIES = libgstwebrtc.la

libgstwebrtc_la_SOURCES = gstwebrtc.c \
                                 case/wrapper.cpp \
                                 case/wrapper.h \
                                 case/p2psocketsignalingchannel.h \
                                 case/p2psocketsignalingchannel.cc \
                                 case/Yuv.h \
                                 case/Yuv.cpp

libgstwebrtc_la_CFLAGS = $(GST_CFLAGS)

libgstwebrtc_la_LIBADD = $(GST_LIBS) 
libgstwebrtc_la_LIBADD += -lboost_date_time \
        -lboost_random \
        -lboost_system \
        -lssl \
        -lsioclient \
        ./case/libs/libowt.a \
        -lcrypto \
        -lz \
        -lasound \
        -lbz2 \
        -lrt \
        -lm \
        -ldl \
        -lX11 \
        -lXext \
        -lXcomposite \
        -lXrender \
        -lpthread \
        -lva \
        -lva-drm \
        -lva-x11 \
        -lyami 

libgstwebrtc_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgstwebrtc_la_LDFLAGS += -L./case/libs

libgstwebrtc_la_LIBTOOLFLAGS = --tag=disable-static

noinst_HEADERS = gstwebrtc.h 






