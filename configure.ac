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
PKG_CHECK_MODULES([SDEVENTPLUS], [sdeventplus],, [AC_MSG_ERROR([The openbmc/sdeventplus package is required])])
PKG_CHECK_MODULES([LIBEVDEV], [libevdev],, [AC_MSG_ERROR([Could not find libevdev...libevdev package required])])

# Download gpio.h from github if necessary.
AC_CHECK_HEADER(linux/gpio.h,[HAVE_LINUX_GPIO_H=""],[HAVE_LINUX_GPIO_H="-I linux/gpio.h"])
AS_IF([test "$HAVE_LINUX_GPIO_H" != ""],
          AC_MSG_WARN([Could not find linux/gpio.h: Attempting to download locally for building from https://raw.githubusercontent.com/torvalds/linux/master/include/uapi/linux/gpio.h])
              AC_SUBST([BT_BMC_DL],[`mkdir -p linux;wget https://raw.githubusercontent.com/torvalds/linux/master/include/uapi/linux/gpio.h -O linux/gpio.h`])
              )

AC_PATH_PROG([SDBUSPLUSPLUS], [sdbus++])
AS_IF([test "x$SDBUSPLUSPLUS" == "x"], AC_MSG_ERROR([Cannot find sdbus++]))

# Create configured output
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
