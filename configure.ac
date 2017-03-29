AC_PREREQ(2.59)
AC_INIT([libvmod-time], [0.1], [https://github.com/joshmarshall/libvmod-time/issues])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR(src/vmod_time.c)
AM_CONFIG_HEADER(config.h)

AC_CANONICAL_SYSTEM
AC_LANG(C)

AM_INIT_AUTOMAKE([foreign])

AC_GNU_SOURCE
AC_PROG_CC
AC_PROG_CC_STDC

if test "x$ac_cv_prog_cc_c99" = xno; then
        AC_MSG_ERROR([Cound not find a C99 compatible compiler])
fi

AC_PROG_CPP

AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_PROG_MAKE_SET

# ignoring RST stuff for now

PKG_PROG_PKG_CONFIG

AC_HEADER_STDC
AC_CHECK_HEADERS([sys.stdlib.h])
AC_CHECK_FUNCS([mempcpy])
AC_CHECK_PROGS(PYTHON, [python3, python] [AC_MSG_ERROR([Python is missing.])])

AC_ARG_VAR([VARNISHSRC], [path to Varnish source required])
if test "x$VARNISHSRC" = x; then
        AC_MSG_ERROR([No varnish source specified or found])
fi

VARNISHSRC=`cd $VARNISHSRC && pwd`

# Is it a Varnish 3 or 4 source tree ?
AC_CHECK_FILE([$VARNISHSRC/lib/libvmod_std/vmod.py], [Varnish_Version_MAJOR=3])
AC_CHECK_FILE([$VARNISHSRC/lib/libvcc/vmodtool.py],  [Varnish_Version_MAJOR=4])

AC_SUBST([VARNISH_MAJOR], [$Varnish_Version_MAJOR])
AC_SUBST([DEFINE_MAJOR], [-DVARNISH_MAJOR=$Varnish_Version_MAJOR])

AC_SUBST([VMODTOOL], ['$(VARNISHSRC)/lib/libvmod_std/vmod.py'])
AC_CHECK_FILE([$VARNISHSRC/bin/varnishtest/varnishtest],
	[], [AC_MSG_FAILURE([Could not find $VARNISHSRC/bin/varnishtest/varnishtest.])])

AC_CHECK_FILE([$VARNISHSRC/include/vmod_abi.h], [], [AC_MSG_ERROR([Could not find $VARNISHSRC/include/vmod_abi.h])])
AC_ARG_VAR([VMODDIR], [vmod installation directory])
if test "x$VMODDIR" = x; then
	VMODDIR=`pkg-config --variable=vmoddir varnishapi`
	if test "x$VMODDIR" = x; then
		AC_MSG_FAILURE([Could not find vmod dir])
	fi
fi

AC_CONFIG_FILES([
	Makefile
	src/Makefile
])

AC_OUTPUT
