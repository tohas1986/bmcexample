

set (rikor-fru_src main.c dictionary.c iniparser.c)
set (rikor-fru_libsrc rikor-fru.c crc16.c)

# Make build flags compiler specific
if (CMAKE_COMPILER_IS_GNUCC)
	if (CMAKE_BUILD_TYPE STREQUAL "Debug")
		set (CMAKE_C_FLAGS "-D_REETRANT -ggdb -fPIC -Wall -Wextra -pedantic -O0")
	elseif( CMAKE_BUILD_TYPE STREQUAL "Release" )
		set (CMAKE_C_FLAGS "-D_REETRANT -DNDEBUG -fPIC -Wall -Wextra -pedantic -O3")
	endif ()
endif (CMAKE_COMPILER_IS_GNUCC)


include_directories($ENV{SINC})
include_directories($ENV{SINC}/glib-2.0)
include_directories($ENV{SLIB}/glib-2.0/include)

find_library(GIO gio-2.0)
find_library(GLIB glib-2.0)

add_executable (rikor-fru-util ${rikor-fru_src})

target_link_libraries(rikor-fru-util
  ${GIO}
  ${GLIB}
  rikor-fru
)


add_library (rikor-fru ${rikor-fru_libsrc})

target_link_libraries(rikor-fru
  ${GIO}
  ${GLIB}
)

# The rule to install binary
install (TARGETS rikor-fru-util
	RUNTIME	DESTINATION bin)
