#######################################
# The list of executables we are building seperated by spaces
# the 'bin_' indicates that these build products will be installed
# in the $(bindir) directory. For example /usr/bin
#bin_PROGRAMS=unittest

# Because a.out is only a sample program we don't want it to be installed.
# The 'noinst_' prefix indicates that the following targets are not to be
# installed.
noinst_PROGRAMS=unittest

#######################################
# Build information for each executable. The variable name is derived
# by use the name of the executable with each non alpha-numeric character is
# replaced by '_'. So a.out becomes a_out and the appropriate suffex added.
# '_SOURCES' for example.

ACLOCAL_AMFLAGS=-I ../m4

# Sources for the a.out 
unittest_SOURCES= unittest.cxx

# Libraries for a.out
unittest_LDADD = \
	$(top_srcdir)/libmleventtest/libmleventtest.la \
	$(top_srcdir)/libmlevent/libmlevent.la \
	$(MLE_ROOT)/lib/libmlutil.la \
	$(GTEST_DIR)/libgtest.a

# Linker options for a.out
unittest_LDFLAGS = \
    -Wl, -rpath `cd $(top_srcdir);pwd`/libmlevent/.libs \
    -Wl, -rpath `cd $(top_srcdir);pwd`/libmleventtest/.libs \
    -pthread

# Compiler options for a.out
unittest_CPPFLAGS = \
	-DMLE_NOT_DLL \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/../../include \
	-I$(MLE_HOME)/Core/util/common/include \
	-I$(MLE_HOME)/Core/util/linux/include \
	-I$(GTEST_DIR)/include
