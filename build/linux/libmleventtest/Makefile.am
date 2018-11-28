#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = libmleventtest.la

#######################################
# Build information for each library

# Sources for libmleventtest
libmleventtest_la_SOURCES = libmleventtest.cxx \
	testMlePq.cxx testMlePqThread.cxx

# Linker options libTestProgram
libmleventtest_la_LDFLAGS = 

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libmleventtest_la_CPPFLAGS = \
	-DMLE_NOT_DLL \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/../../include \
	-I$(MLE_HOME)/Core/util/common/include \
	-I$(MLE_HOME)/Core/util/linux/include \
	-I$(GTEST_DIR)/include
