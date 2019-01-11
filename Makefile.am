sbin_PROGRAMS = sfp-manager

sfp_manager_SOURCES = \
	main.cpp  
BUILT_SOURCES = org/inspur/sfp/server.hpp \
		org/inspur/sfp/server.cpp

sfp_manager_LDFLAGS = \
		      $(SDBUSPLUS_LIBS) 

sfp_manager_CFLAGS =  \
		      $(SDBUSPLUS_CFLAGS)

org/inspur/sfp/server.hpp: ${top_srcdir}/org/inspur/sfp.interface.yaml
	@mkdir -p `dirname $@`
	$(SDBUSPLUSPLUS)  -r ${top_srcdir} interface server-header org.inspur.sfp > $@
org/inspur/sfp/server.cpp: ${top_srcdir}/org/inspur/sfp.interface.yaml
	@mkdir -p `dirname $@`
	$(SDBUSPLUSPLUS)  -r ${top_srcdir} interface server-cpp org.inspur.sfp > $@
