
find_path(Readline_INCLUDE_DIR readline/readline.h)
find_library(Readline_LIBRARY NAMES readline) 

if (Readline_INCLUDE_DIR AND Readline_LIBRARY)
   set(Readline_FOUND TRUE)
endif (Readline_INCLUDE_DIR AND Readline_LIBRARY)

if (Readline_FOUND)
   if (NOT Readline_FIND_QUIETLY)
      message(STATUS "Found GNU readline: ${Readline_LIBRARY}")
   endif (NOT Readline_FIND_QUIETLY)
else (Readline_FOUND)
   if (Readline_FIND_REQUIRED)
      message(FATAL_ERROR "Could not find GNU readline")
   endif (Readline_FIND_REQUIRED)
endif (Readline_FOUND)