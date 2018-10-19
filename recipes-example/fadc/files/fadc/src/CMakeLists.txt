set (daemon_src daemon.c adc.c)

# Make build flags compiler specific
if (CMAKE_COMPILER_IS_GNUCC)
	if (CMAKE_BUILD_TYPE STREQUAL "Debug")
		set (CMAKE_C_FLAGS "-D_REETRANT -ggdb -fPIC -Wall -Wextra -pedantic -O0")
	elseif( CMAKE_BUILD_TYPE STREQUAL "Release" )
		set (CMAKE_C_FLAGS "-D_REETRANT -DNDEBUG -fPIC -Wall -Wextra -pedantic -O3")
	endif ()
endif (CMAKE_COMPILER_IS_GNUCC)

include_directories($ENV{SINC})

#include_directories($ENV{SINC}/glib-2.0)
#include_directories($ENV{SLIB}/glib-2.0/include)

#find_library(GIO gio-2.0)
#find_library(GLIB glib-2.0)

add_executable (${PROJECT_NAME} ${daemon_src})

#target_link_libraries(daemon
#  ${GIO}
#  ${GLIB}
#)

message("ENV SINC :" $ENV{SINC})
message("ENV SLIB :" $ENV{SLIB})
#message("GIO :" ${GIO})
#message("GLIB :" ${GLIB})

# The rule to install daemon binary
install (TARGETS ${PROJECT_NAME}
	RUNTIME
	DESTINATION bin)
