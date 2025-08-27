noinst_LIBRARIES = libpados.a libpthread.a
libpados_a_SOURCES = 

libpthread_a_SOURCES = pthread.c

# Install library into the multilib dir selected by GCC flags
padoslibdir = $(tooldir)/lib/$(MULTISUBDIR)
padoslib_DATA = libpados.a

pthreadlibdir = $(tooldir)/lib/$(MULTISUBDIR)
pthreadlib_DATA = libpthread.a

# Install a specs file alongside other libgloss specs
toollibdir    = $(tooldir)/lib
toollib_DATA  = pados.specs

#AM_CPPFLAGS += \
#  -I$(top_builddir)/../newlib/targ-include \
#  -I$(top_srcdir)/../newlib/libc/include
