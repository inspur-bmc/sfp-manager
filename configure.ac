# Initialization
AC_PREREQ([2.69])
AC_INIT([optical-module], [1.0], [https://github.com/inspur-bmc/optical-module/issues])
AC_LANG([C++])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror foreign dist-xz])
AM_SILENT_RULES([yes])

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_MAKE_SET

# Checks for libraries.
PKG_CHECK_MODULES([SYSTEMD], [libsystemd >= 221])

# Checks for typedefs, structures, and compiler characteristics.
AX_CXX_COMPILE_STDCXX_17([noext])
AX_APPEND_COMPILE_FLAGS([-Wall -Werror], [CXXFLAGS])

# For libtools
LT_INIT

# Checks for header files.
PKG_CHECK_MODULES([SDBUSPLUS], [sdbusplus],, [AC_MSG_ERROR([Could not find sdbusplus...openbmc/sdbusplus package required])])

AC_PATH_PROG([SDBUSPLUSPLUS], [sdbus++])
AS_IF([test "x$SDBUSPLUSPLUS" == "x"], AC_MSG_ERROR([Cannot find sdbus++]))

# Create configured output
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
