dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(libmlevent, 1.0)
AC_PROG_CC
AC_PROG_CXX

AC_PREFIX_DEFAULT(/opt/MagicLantern)

AC_CANONICAL_SYSTEM

AC_CONFIG_MACRO_DIR([m4])

dnl Initialize automake
AM_INIT_AUTOMAKE
AUTOMAKE_OPTIONS = subdir-objects
dnl AM_INIT_AUTOMAKE([subdir-objects])

dnl this allows us specify individual liking flags for each target
AM_PROG_CC_C_O 

dnl Initialize Libtool
LT_INIT

AC_CONFIG_FILES(Makefile
                exampleProgram/Makefile
                libmlevent/Makefile
                libmleventtest/Makefile
                include/Makefile)
AC_OUTPUT