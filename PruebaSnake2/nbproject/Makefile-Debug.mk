#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/d4ba4a00/main.o \
	${OBJECTDIR}/_ext/d4ba4a00/snake_graphic_base.o \
	${OBJECTDIR}/_ext/d4ba4a00/snake_logic.o \
	${OBJECTDIR}/_ext/d4ba4a00/snake_pc.o \
	${OBJECTDIR}/_ext/d4ba4a00/ui.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs allegro-5.0` `pkg-config --libs allegro_acodec-5.0` `pkg-config --libs allegro_audio-5.0` `pkg-config --libs allegro_color-5.0` `pkg-config --libs allegro_dialog-5.0` `pkg-config --libs allegro_font-5.0` `pkg-config --libs allegro_image-5.0` `pkg-config --libs allegro_main-5.0` `pkg-config --libs allegro_memfile-5.0` `pkg-config --libs allegro_physfs-5.0` `pkg-config --libs allegro_primitives-5.0` `pkg-config --libs allegro_ttf-5.0`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pruebasnake2

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pruebasnake2: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pruebasnake2 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/d4ba4a00/main.o: ../PruebaSnake/main.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d4ba4a00
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d4ba4a00/main.o ../PruebaSnake/main.c

${OBJECTDIR}/_ext/d4ba4a00/snake_graphic_base.o: ../PruebaSnake/snake_graphic_base.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d4ba4a00
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d4ba4a00/snake_graphic_base.o ../PruebaSnake/snake_graphic_base.c

${OBJECTDIR}/_ext/d4ba4a00/snake_logic.o: ../PruebaSnake/snake_logic.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d4ba4a00
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d4ba4a00/snake_logic.o ../PruebaSnake/snake_logic.c

${OBJECTDIR}/_ext/d4ba4a00/snake_pc.o: ../PruebaSnake/snake_pc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d4ba4a00
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d4ba4a00/snake_pc.o ../PruebaSnake/snake_pc.c

${OBJECTDIR}/_ext/d4ba4a00/ui.o: ../PruebaSnake/ui.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d4ba4a00
	${RM} "$@.d"
	$(COMPILE.c) -g `pkg-config --cflags allegro-5.0` `pkg-config --cflags allegro_acodec-5.0` `pkg-config --cflags allegro_audio-5.0` `pkg-config --cflags allegro_color-5.0` `pkg-config --cflags allegro_dialog-5.0` `pkg-config --cflags allegro_font-5.0` `pkg-config --cflags allegro_image-5.0` `pkg-config --cflags allegro_main-5.0` `pkg-config --cflags allegro_memfile-5.0` `pkg-config --cflags allegro_physfs-5.0` `pkg-config --cflags allegro_primitives-5.0` `pkg-config --cflags allegro_ttf-5.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d4ba4a00/ui.o ../PruebaSnake/ui.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
