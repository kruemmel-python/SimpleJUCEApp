cmake_minimum_required(VERSION 3.15)

# Setze den Projektnamen und die Version
project(SimpleJUCEApp VERSION 1.0.0)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    # Setzt das Toolchain-File von Vcpkg, das f�r die Verwaltung von Abh�ngigkeiten erforderlich ist.
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()





# JUCE verwenden
find_package(JUCE CONFIG REQUIRED)

# F�ge die Hauptanwendung hinzu
add_executable(SimpleJUCEApp Main.cpp)

# Binde JUCE-Bibliotheken ein
target_link_libraries(SimpleJUCEApp PRIVATE juce::juce_gui_basics juce::juce_core)
