
# Configuração do projeto

cmake_minimum_required(VERSION 3.16)

project(DicomViewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Caminho da biblioteca dcmtk instalada

set(DCMTK_PATH "C:/DCMTK_FINAL")
include_directories("${DCMTK_PATH}/include")
link_directories("${DCMTK_PATH}/lib")
set(SYSTEM_LIBS ws2_32 iphlpapi netapi32)

# Lista de Módulos do DCMTK
set(DCMTK_LIBS
    dcmjpeg
    dcmimage
    dcmimgle
    dcmnet
    dcmdata
    oflog
    ofstd
    oficonv
    ijg8
    ijg12
    ijg16
)

#Arquivos fonte do projeto
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

#Cria o executável final
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DicomViewer MANUAL_FINALIZATION ${PROJECT_SOURCES})
else()
    if(ANDROID)
        add_library(DicomViewer SHARED ${PROJECT_SOURCES})
    else()
        add_executable(DicomViewer ${PROJECT_SOURCES})
    endif()
endif()


#Conecta as bibliotecas externas ao nosso executável DicomViewer
target_link_libraries(DicomViewer PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${DCMTK_LIBS}
    ${SYSTEM_LIBS}
)

set_target_properties(DicomViewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DicomViewer
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DicomViewer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DicomViewer)
endif()
