# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/FaceDetector_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/FaceDetector_autogen.dir/ParseCache.txt"
  "FaceDetector_autogen"
  )
endif()
