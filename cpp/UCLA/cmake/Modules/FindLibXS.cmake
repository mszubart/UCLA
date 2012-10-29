# Module for finding LibXS

find_package(PkgConfig)
pkg_check_modules(LIBXS QUIET libxs-1.2.0)
set(LIBXS_DEFINITIONS ${LIBXS_CFLAGS_OTHER})

find_path(LIBXS_INCLUDE_DIR xs/xs.h
          HINTS ${PC_LIBXML_INCLUDEDIR} ${PC_LIBXML_INCLUDE_DIRS}
          PATH_SUFFIXES libxs )

      find_library(LIBXS_LIBRARY NAMES xs libxs
          HINTS ${LIBXS_LIBDIR} ${LIBXS_LIBRARY_DIRS} )

      set(LIBXS_LIBRARIES ${LIBXS_LIBRARY} )
      set(LIBXS_INCLUDE_DIRS ${LIBXS_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(LibXS  DEFAULT_MSG
    LIBXS_LIBRARY LIBXS_INCLUDE_DIR)

mark_as_advanced(LIBXS_INCLUDE_DIR LIBXS_LIBRARY )

