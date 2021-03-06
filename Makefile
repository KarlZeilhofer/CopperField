#############################################################################
# Makefile for building: CopperField
# Generated by qmake (3.0) (Qt 5.5.1)
# Project:  CopperField.pro
# Template: app
# Command: /usr/lib/x86_64-linux-gnu/qt5/bin/qmake -o Makefile CopperField.pro
#############################################################################

MAKEFILE      = Makefile

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT -fPIC $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT -fPIC $(DEFINES)
INCPATH       = -I. -I. -isystem /usr/include/x86_64-linux-gnu/qt5 -isystem /usr/include/x86_64-linux-gnu/qt5/QtGui -isystem /usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64
QMAKE         = /usr/lib/x86_64-linux-gnu/qt5/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = CopperField1.0.0
DISTDIR = /home/karl/Qt4-projects/CopperField/.tmp/CopperField1.0.0
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS) -L/usr/X11R6/lib64 -lQt5Gui -lQt5Core -lGL -lpthread 
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = copperfield.cpp \
		crosshair.cpp \
		cutout.cpp \
		dialoglayers.cpp \
		gcodesettings.cpp \
		gerberaperture.cpp \
		gerberelement.cpp \
		gerberreader.cpp \
		griditem.cpp \
		layerwidget.cpp \
		main.cpp \
		matrix.cpp \
		myrectangle.cpp \
		netlistwidget.cpp \
		netsviewer.cpp \
		progresssplashscreen.cpp \
		scene.cpp \
		view.cpp qrc_copperfield.cpp \
		moc_copperfield.cpp \
		moc_dialoglayers.cpp \
		moc_gcodesettings.cpp \
		moc_gerberreader.cpp \
		moc_layerwidget.cpp \
		moc_netlistwidget.cpp \
		moc_netsviewer.cpp \
		moc_progresssplashscreen.cpp \
		moc_view.cpp
OBJECTS       = copperfield.o \
		crosshair.o \
		cutout.o \
		dialoglayers.o \
		gcodesettings.o \
		gerberaperture.o \
		gerberelement.o \
		gerberreader.o \
		griditem.o \
		layerwidget.o \
		main.o \
		matrix.o \
		myrectangle.o \
		netlistwidget.o \
		netsviewer.o \
		progresssplashscreen.o \
		scene.o \
		view.o \
		qrc_copperfield.o \
		moc_copperfield.o \
		moc_dialoglayers.o \
		moc_gcodesettings.o \
		moc_gerberreader.o \
		moc_layerwidget.o \
		moc_netlistwidget.o \
		moc_netsviewer.o \
		moc_progresssplashscreen.o \
		moc_view.o
DIST          = /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_device_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64/qmake.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf \
		CopperField.pro copperfield.h \
		crosshair.h \
		cutout.h \
		dialoglayers.h \
		DrawingItem.h \
		gcodesettings.h \
		gerberaperture.h \
		gerberelement.h \
		gerberreader.h \
		griditem.h \
		layerwidget.h \
		matrix.h \
		netlistwidget.h \
		netsviewer.h \
		progresssplashscreen.h \
		scene.h \
		ui_dialoglayers.h \
		ui_gcodesettings.h \
		ui_layerwidget.h \
		ui_progresssplashscreen.h \
		view.h copperfield.cpp \
		crosshair.cpp \
		cutout.cpp \
		dialoglayers.cpp \
		gcodesettings.cpp \
		gerberaperture.cpp \
		gerberelement.cpp \
		gerberreader.cpp \
		griditem.cpp \
		layerwidget.cpp \
		main.cpp \
		matrix.cpp \
		myrectangle.cpp \
		netlistwidget.cpp \
		netsviewer.cpp \
		progresssplashscreen.cpp \
		scene.cpp \
		view.cpp
QMAKE_TARGET  = CopperField
DESTDIR       = #avoid trailing-slash linebreak
TARGET        = CopperField


first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: CopperField.pro /usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64/qmake.conf /usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_device_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64/qmake.conf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf \
		/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf \
		CopperField.pro \
		copperfield.qrc \
		/usr/lib/x86_64-linux-gnu/libQt5Gui.prl \
		/usr/lib/x86_64-linux-gnu/libQt5Core.prl
	$(QMAKE) -o Makefile CopperField.pro
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_pre.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/linux.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/sanitize.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-base.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/common/g++-unix.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/qconfig.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_eglfs_device_lib_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_platformsupport_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_functions.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_config.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64/qmake.conf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/spec_post.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_pre.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resolve_config.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/default_post.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/warn_on.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/resources.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/moc.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/opengl.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/unix/thread.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/testcase_targets.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/exceptions.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/yacc.prf:
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/lex.prf:
CopperField.pro:
copperfield.qrc:
/usr/lib/x86_64-linux-gnu/libQt5Gui.prl:
/usr/lib/x86_64-linux-gnu/libQt5Core.prl:
qmake: FORCE
	@$(QMAKE) -o Makefile CopperField.pro

qmake_all: FORCE


all: Makefile $(TARGET)

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/
	$(COPY_FILE) --parents copperfield.qrc $(DISTDIR)/
	$(COPY_FILE) --parents copperfield.h crosshair.h cutout.h dialoglayers.h DrawingItem.h gcodesettings.h gerberaperture.h gerberelement.h gerberreader.h griditem.h layerwidget.h matrix.h netlistwidget.h netsviewer.h progresssplashscreen.h scene.h ui_dialoglayers.h ui_gcodesettings.h ui_layerwidget.h ui_progresssplashscreen.h view.h $(DISTDIR)/
	$(COPY_FILE) --parents copperfield.cpp crosshair.cpp cutout.cpp dialoglayers.cpp gcodesettings.cpp gerberaperture.cpp gerberelement.cpp gerberreader.cpp griditem.cpp layerwidget.cpp main.cpp matrix.cpp myrectangle.cpp netlistwidget.cpp netsviewer.cpp progresssplashscreen.cpp scene.cpp view.cpp $(DISTDIR)/


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


####### Sub-libraries

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

check: first

compiler_rcc_make_all: qrc_copperfield.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_copperfield.cpp
qrc_copperfield.cpp: copperfield.qrc \
		images/save.png \
		images/open.png \
		images/cut.png \
		images/copy.png \
		images/new.png \
		images/paste.png
	/usr/lib/x86_64-linux-gnu/qt5/bin/rcc -name copperfield copperfield.qrc -o qrc_copperfield.cpp

compiler_moc_header_make_all: moc_copperfield.cpp moc_dialoglayers.cpp moc_gcodesettings.cpp moc_gerberreader.cpp moc_layerwidget.cpp moc_netlistwidget.cpp moc_netsviewer.cpp moc_progresssplashscreen.cpp moc_view.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_copperfield.cpp moc_dialoglayers.cpp moc_gcodesettings.cpp moc_gerberreader.cpp moc_layerwidget.cpp moc_netlistwidget.cpp moc_netsviewer.cpp moc_progresssplashscreen.cpp moc_view.cpp
moc_copperfield.cpp: gcodesettings.h \
		dialoglayers.h \
		layerwidget.h \
		gerberreader.h \
		gerberaperture.h \
		gerberelement.h \
		matrix.h \
		progresssplashscreen.h \
		copperfield.h
	/usr/lib/x86_64-linux-gnu/qt5/bin/moc $(DEFINES) -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I/home/karl/Qt4-projects/CopperField -I/home/karl/Qt4-projects/CopperField -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/5 -I/usr/include/x86_64-linux-gnu/c++/5 -I/usr/include/c++/5/backward -I/usr/lib/gcc/x86_64-linux-gnu/5/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/5/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include copperfield.h -o moc_copperfield.cpp

moc_dialoglayers.cpp: layerwidget.h \
		gerberreader.h \
		gerberaperture.h \
		gerberelement.h \
		gcodesettings.h \
		matrix.h \
		dialoglayers.h
	/usr/lib/x86_64-linux-gnu/qt5/bin/moc $(DEFINES) -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I/home/karl/Qt4-projects/CopperField -I/home/karl/Qt4-projects/CopperField -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/5 -I/usr/include/x86_64-linux-gnu/c++/5 -I/usr/include/c++/5/backward -I/usr/lib/gcc/x86_64-linux-gnu/5/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/5/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include dialoglayers.h -o moc_dialoglayers.cpp

moc_gcodesettings.cpp: gcodesettings.h
	/usr/lib/x86_64-linux-gnu/qt5/bin/moc $(DEFINES) -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I/home/karl/Qt4-projects/CopperField -I/home/karl/Qt4-projects/CopperField -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/5 -I/usr/include/x86_64-linux-gnu/c++/5 -I/usr/include/c++/5/backward -I/usr/lib/gcc/x86_64-linux-gnu/5/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/5/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include gcodesettings.h -o moc_gcodesettings.cpp

moc_gerberreader.cpp: gerberaperture.h \
		gerberelement.h \
		gcodesettings.h \
		matrix.h \
		gerberreader.h
	/usr/lib/x86_64-linux-gnu/qt5/bin/moc $(DEFINES) -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I/home/karl/Qt4-projects/CopperField -I/home/karl/Qt4-projects/CopperField -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/5 -I/usr/include/x86_64-linux-gnu/c++/5 -I/usr/include/c++/5/backward -I/usr/lib/gcc/x86_64-linux-gnu/5/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/5/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include gerberreader.h -o moc_gerberreader.cpp

moc_layerwidget.cpp: gerberreader.h \
		gerberaperture.h \
		gerberelement.h \
		gcodesettings.h \
		matrix.h \
		layerwidget.h
	/usr/lib/x86_64-linux-gnu/qt5/bin/moc $(DEFINES) -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I/home/karl/Qt4-projects/CopperField -I/home/karl/Qt4-projects/CopperField -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/5 -I/usr/include/x86_64-linux-gnu/c++/5 -I/usr/include/c++/5/backward -I/usr/lib/gcc/x86_64-linux-gnu/5/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/5/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include layerwidget.h -o moc_layerwidget.cpp

moc_netlistwidget.cpp: netlistwidget.h
	/usr/lib/x86_64-linux-gnu/qt5/bin/moc $(DEFINES) -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I/home/karl/Qt4-projects/CopperField -I/home/karl/Qt4-projects/CopperField -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/5 -I/usr/include/x86_64-linux-gnu/c++/5 -I/usr/include/c++/5/backward -I/usr/lib/gcc/x86_64-linux-gnu/5/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/5/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include netlistwidget.h -o moc_netlistwidget.cpp

moc_netsviewer.cpp: netsviewer.h
	/usr/lib/x86_64-linux-gnu/qt5/bin/moc $(DEFINES) -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I/home/karl/Qt4-projects/CopperField -I/home/karl/Qt4-projects/CopperField -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/5 -I/usr/include/x86_64-linux-gnu/c++/5 -I/usr/include/c++/5/backward -I/usr/lib/gcc/x86_64-linux-gnu/5/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/5/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include netsviewer.h -o moc_netsviewer.cpp

moc_progresssplashscreen.cpp: progresssplashscreen.h
	/usr/lib/x86_64-linux-gnu/qt5/bin/moc $(DEFINES) -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I/home/karl/Qt4-projects/CopperField -I/home/karl/Qt4-projects/CopperField -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/5 -I/usr/include/x86_64-linux-gnu/c++/5 -I/usr/include/c++/5/backward -I/usr/lib/gcc/x86_64-linux-gnu/5/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/5/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include progresssplashscreen.h -o moc_progresssplashscreen.cpp

moc_view.cpp: view.h
	/usr/lib/x86_64-linux-gnu/qt5/bin/moc $(DEFINES) -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I/home/karl/Qt4-projects/CopperField -I/home/karl/Qt4-projects/CopperField -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/c++/5 -I/usr/include/x86_64-linux-gnu/c++/5 -I/usr/include/c++/5/backward -I/usr/lib/gcc/x86_64-linux-gnu/5/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/5/include-fixed -I/usr/include/x86_64-linux-gnu -I/usr/include view.h -o moc_view.cpp

compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_rcc_clean compiler_moc_header_clean 

####### Compile

copperfield.o: copperfield.cpp copperfield.h \
		gcodesettings.h \
		dialoglayers.h \
		layerwidget.h \
		gerberreader.h \
		gerberaperture.h \
		gerberelement.h \
		matrix.h \
		progresssplashscreen.h \
		view.h \
		scene.h \
		netsviewer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o copperfield.o copperfield.cpp

crosshair.o: crosshair.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o crosshair.o crosshair.cpp

cutout.o: cutout.cpp copperfield.h \
		gcodesettings.h \
		dialoglayers.h \
		layerwidget.h \
		gerberreader.h \
		gerberaperture.h \
		gerberelement.h \
		matrix.h \
		progresssplashscreen.h \
		cutout.h \
		DrawingItem.h \
		view.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o cutout.o cutout.cpp

dialoglayers.o: dialoglayers.cpp dialoglayers.h \
		layerwidget.h \
		gerberreader.h \
		gerberaperture.h \
		gerberelement.h \
		gcodesettings.h \
		matrix.h \
		ui_dialoglayers.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dialoglayers.o dialoglayers.cpp

gcodesettings.o: gcodesettings.cpp gcodesettings.h \
		ui_gcodesettings.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gcodesettings.o gcodesettings.cpp

gerberaperture.o: gerberaperture.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gerberaperture.o gerberaperture.cpp

gerberelement.o: gerberelement.cpp gerberelement.h \
		gerberaperture.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gerberelement.o gerberelement.cpp

gerberreader.o: gerberreader.cpp copperfield.h \
		gcodesettings.h \
		dialoglayers.h \
		layerwidget.h \
		gerberreader.h \
		gerberaperture.h \
		gerberelement.h \
		matrix.h \
		progresssplashscreen.h \
		netsviewer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o gerberreader.o gerberreader.cpp

griditem.o: griditem.cpp view.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o griditem.o griditem.cpp

layerwidget.o: layerwidget.cpp layerwidget.h \
		gerberreader.h \
		gerberaperture.h \
		gerberelement.h \
		gcodesettings.h \
		matrix.h \
		ui_layerwidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o layerwidget.o layerwidget.cpp

main.o: main.cpp copperfield.h \
		gcodesettings.h \
		dialoglayers.h \
		layerwidget.h \
		gerberreader.h \
		gerberaperture.h \
		gerberelement.h \
		matrix.h \
		progresssplashscreen.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

matrix.o: matrix.cpp matrix.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o matrix.o matrix.cpp

myrectangle.o: myrectangle.cpp copperfield.h \
		gcodesettings.h \
		dialoglayers.h \
		layerwidget.h \
		gerberreader.h \
		gerberaperture.h \
		gerberelement.h \
		matrix.h \
		progresssplashscreen.h \
		view.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o myrectangle.o myrectangle.cpp

netlistwidget.o: netlistwidget.cpp netlistwidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o netlistwidget.o netlistwidget.cpp

netsviewer.o: netsviewer.cpp netsviewer.h \
		netlistwidget.h \
		gerberelement.h \
		gerberaperture.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o netsviewer.o netsviewer.cpp

progresssplashscreen.o: progresssplashscreen.cpp progresssplashscreen.h \
		ui_progresssplashscreen.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o progresssplashscreen.o progresssplashscreen.cpp

scene.o: scene.cpp copperfield.h \
		gcodesettings.h \
		dialoglayers.h \
		layerwidget.h \
		gerberreader.h \
		gerberaperture.h \
		gerberelement.h \
		matrix.h \
		progresssplashscreen.h \
		griditem.h \
		scene.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o scene.o scene.cpp

view.o: view.cpp view.h \
		crosshair.h \
		scene.h \
		DrawingItem.h \
		cutout.h \
		copperfield.h \
		gcodesettings.h \
		dialoglayers.h \
		layerwidget.h \
		gerberreader.h \
		gerberaperture.h \
		gerberelement.h \
		matrix.h \
		progresssplashscreen.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o view.o view.cpp

qrc_copperfield.o: qrc_copperfield.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_copperfield.o qrc_copperfield.cpp

moc_copperfield.o: moc_copperfield.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_copperfield.o moc_copperfield.cpp

moc_dialoglayers.o: moc_dialoglayers.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_dialoglayers.o moc_dialoglayers.cpp

moc_gcodesettings.o: moc_gcodesettings.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_gcodesettings.o moc_gcodesettings.cpp

moc_gerberreader.o: moc_gerberreader.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_gerberreader.o moc_gerberreader.cpp

moc_layerwidget.o: moc_layerwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_layerwidget.o moc_layerwidget.cpp

moc_netlistwidget.o: moc_netlistwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_netlistwidget.o moc_netlistwidget.cpp

moc_netsviewer.o: moc_netsviewer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_netsviewer.o moc_netsviewer.cpp

moc_progresssplashscreen.o: moc_progresssplashscreen.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_progresssplashscreen.o moc_progresssplashscreen.cpp

moc_view.o: moc_view.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_view.o moc_view.cpp

####### Install

install:  FORCE

uninstall:  FORCE

FORCE:

