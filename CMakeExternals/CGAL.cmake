#-----------------------------------------------------------------------------
# CGAL
#-----------------------------------------------------------------------------

if(MITK_USE_CGAL)

  # Sanity checks
  if(DEFINED CGAL_DIR AND NOT EXISTS ${CGAL_DIR})
    message(FATAL_ERROR "CGAL_DIR variable is defined but corresponds to non-existing directory")
  endif()

  set(proj CGAL)
  set(proj_DEPENDENCIES Boost VTK)
  set(CGAL_DEPENDS ${proj})

  set(preconfigure_cmake_args )

  if(NOT MITK_USE_SYSTEM_Boost)
    list(APPEND preconfigure_cmake_args
      -DBoost_NO_SYSTEM_PATHS:BOOL=ON
      -DBOOST_ROOT:PATH=${BOOST_ROOT}
      -DBOOST_LIBRARYDIR:PATH=${BOOST_LIBRARYDIR}
      -DBoost_ADDITIONAL_VERSIONS:STRING=1.59${sep}1.59.0
    )
  endif()

  if(NOT DEFINED CGAL_DIR)

    set(additional_cmake_args)
    
    list(APPEND additional_cmake_args
      -DGMP_LIBRARIES_DIR:PATH=${GMP_LIBRARIES_DIR}
      -DGMP_LIBRARIES:PATH=${GMP_LIBRARIES}
      -DGMP_INCLUDE_DIR:PATH=${GMP_INCLUDE_DIR}
      -DMPFR_LIBRARIES_DIR:PATH=${MPFR_LIBRARIES_DIR}
      -DMPFR_LIBRARIES:PATH=${MPFR_LIBRARIES}
      -DMPFR_INCLUDE_DIR:PATH=${MPFR_INCLUDE_DIR}
    )

    ExternalProject_Add(${proj}
      LIST_SEPARATOR ${sep}

      URL "https://github.com/CGAL/cgal/releases/download/releases%2FCGAL-4.9/CGAL-4.9.tar.xz"
      URL_MD5 ee31343dbc4bf7b5b7501ec1650e9233

      CMAKE_GENERATOR ${gen}

      CMAKE_ARGS
        ${ep_common_args}
        ${preconfigure_cmake_args}
        ${additional_cmake_args}

      CMAKE_CACHE_ARGS
        ${ep_common_cache_args}

      CMAKE_CACHE_DEFAULT_ARGS
        ${ep_common_cache_default_args}

      DEPENDS ${proj_DEPENDENCIES}
    )

    set(CGAL_DIR ${ep_prefix})
    mitkFunctionInstallExternalCMakeProject(${proj})
  else()
    mitkMacroEmptyExternalProject(${proj} "${proj_DEPENDENCIES}")
  endif()
endif()