find_package(OpenCV REQUIRED)
if (RPI_COMPILE)
   set(CMAKE_MODULE_PATH "/usr/lib/cmake")
   find_package(raspicam REQUIRED)
   set(ADDITIONAL_ROBOSUB_RPI_SOURCES RPIVideoDevice.cpp)
else (RPI_COMPILE)
   set(ADDITIONAL_ROBOSUB_RPI_SOURCES "")
endif (RPI_COMPILE)
add_executable(robosub_rpi BaseVideoDevice.cpp Circle.cpp CliOptions.cpp Contour.cpp ContourDetector.cpp HSVImage.cpp Logger.cpp Mission.cpp Rectangle.cpp robosub_rpi.cpp Robot.cpp RXPacket.cpp Serial.cpp StartingGateMission.cpp TXPacket.cpp USBVideoDevice.cpp ${ADDITIONAL_ROBOSUB_RPI_SOURCES})
if (RPI_COMPILE)
   target_link_libraries(robosub_rpi ${OpenCV_LIBS} ${raspicam_CV_LIBS} wiringPi)
else (RPI_COMPILE)
   target_link_libraries(robosub_rpi ${OpenCV_LIBS})
endif (RPI_COMPILE)
if (NOT RPI_COMPILE)
   add_subdirectory(experiments)
endif (NOT RPI_COMPILE)
