AM_DEFAULT_SOURCE_EXT = .cpp

sbin_PROGRAMS = sfp-manager

sfp_manager_SOURCES = \
	main.cpp  \
	sfp.cpp \
	gpio.cpp \
	xyz/openbmc_project/Sfp/Sfp/server.cpp \
	xyz/openbmc_project/Sfp/Manager/server.cpp \
	generated.cpp 

BUILT_SOURCES = xyz/openbmc_project/Sfp/Sfp/server.hpp \
		xyz/openbmc_project/Sfp/Sfp/server.cpp \
		xyz/openbmc_project/Sfp/Manager/server.hpp \
		xyz/openbmc_project/Sfp/Manager/server.cpp

sfp_manager_LDADD = \
		      $(SDBUSPLUS_LIBS) \
		      $(SDEVENTPLUS_LIBS) \
		      $(LIBEVDEV_LIBS)

sfp_manager_CXXFLAGS =  \
		      $(SDBUSPLUS_CFLAGS) \
		      $(SDEVENTPLUS_CFLAGS) \
		      $(LIBEVDEV_CFLAGS) 

xyz/openbmc_project/Sfp/Sfp/server.hpp: ${top_srcdir}/xyz/openbmc_project/Sfp/Sfp.interface.yaml
	@mkdir -p `dirname $@`
	$(SDBUSPLUSPLUS)  -r ${top_srcdir} interface server-header xyz.openbmc_project.Sfp.Sfp > $@
xyz/openbmc_project/Sfp/Sfp/server.cpp: ${top_srcdir}/xyz/openbmc_project/Sfp/Sfp.interface.yaml
	@mkdir -p `dirname $@`
	$(SDBUSPLUSPLUS)  -r ${top_srcdir} interface server-cpp xyz.openbmc_project.Sfp.Sfp > $@
xyz/openbmc_project/Sfp/Manager/server.hpp: ${top_srcdir}/xyz/openbmc_project/Sfp/Manager.interface.yaml
	@mkdir -p `dirname $@`
	$(SDBUSPLUSPLUS)  -r ${top_srcdir} interface server-header xyz.openbmc_project.Sfp.Manager > $@
xyz/openbmc_project/Sfp/Manager/server.cpp: ${top_srcdir}/xyz/openbmc_project/Sfp/Manager.interface.yaml
	@mkdir -p `dirname $@`
	$(SDBUSPLUSPLUS)  -r ${top_srcdir} interface server-cpp xyz.openbmc_project.Sfp.Manager > $@
