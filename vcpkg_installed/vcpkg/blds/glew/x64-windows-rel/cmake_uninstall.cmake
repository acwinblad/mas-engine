if(NOT EXISTS "C:/Users/Aidan/source/repos/mas-engine/vcpkg_installed/vcpkg/blds/glew/x64-windows-rel/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: C:/Users/Aidan/source/repos/mas-engine/vcpkg_installed/vcpkg/blds/glew/x64-windows-rel/install_manifest.txt")
endif(NOT EXISTS "C:/Users/Aidan/source/repos/mas-engine/vcpkg_installed/vcpkg/blds/glew/x64-windows-rel/install_manifest.txt")

if (NOT DEFINED CMAKE_INSTALL_PREFIX)
  set (CMAKE_INSTALL_PREFIX "C:/Users/Aidan/source/repos/mas-engine/vcpkg_installed/vcpkg/pkgs/glew_x64-windows")
endif ()
 message(${CMAKE_INSTALL_PREFIX})

file(READ "C:/Users/Aidan/source/repos/mas-engine/vcpkg_installed/vcpkg/blds/glew/x64-windows-rel/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach(file ${files})
  message(STATUS "Uninstalling $ENV{DESTDIR}${file}")
  if(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    exec_program(
      "C:/Users/Aidan/AppData/Local/vcpkg/downloads/tools/cmake-3.29.2-windows/cmake-3.29.2-windows-i386/bin/cmake.exe" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
      )
    if(NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing $ENV{DESTDIR}${file}")
    endif(NOT "${rm_retval}" STREQUAL 0)
  else(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    message(STATUS "File $ENV{DESTDIR}${file} does not exist.")
  endif(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
endforeach(file)
