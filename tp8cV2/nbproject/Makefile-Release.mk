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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/7aa426f7/graphic.o \
	${OBJECTDIR}/_ext/7aa426f7/input.o \
	${OBJECTDIR}/_ext/7aa426f7/main2.o \
	${OBJECTDIR}/_ext/7aa426f7/nonblock.o \
	${OBJECTDIR}/_ext/7aa426f7/output.o \
	${OBJECTDIR}/_ext/7aa426f7/port_utils.o \
	${OBJECTDIR}/led_api.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tp8cv2

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tp8cv2: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tp8cv2 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/7aa426f7/graphic.o: ../TP8_24-05/TP8b/graphic.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7aa426f7
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7aa426f7/graphic.o ../TP8_24-05/TP8b/graphic.c

${OBJECTDIR}/_ext/7aa426f7/input.o: ../TP8_24-05/TP8b/input.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7aa426f7
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7aa426f7/input.o ../TP8_24-05/TP8b/input.c

${OBJECTDIR}/_ext/7aa426f7/main2.o: ../TP8_24-05/TP8b/main2.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7aa426f7
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7aa426f7/main2.o ../TP8_24-05/TP8b/main2.c

${OBJECTDIR}/_ext/7aa426f7/nonblock.o: ../TP8_24-05/TP8b/nonblock.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7aa426f7
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7aa426f7/nonblock.o ../TP8_24-05/TP8b/nonblock.c

${OBJECTDIR}/_ext/7aa426f7/output.o: ../TP8_24-05/TP8b/output.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7aa426f7
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7aa426f7/output.o ../TP8_24-05/TP8b/output.c

${OBJECTDIR}/_ext/7aa426f7/port_utils.o: ../TP8_24-05/TP8b/port_utils.c
	${MKDIR} -p ${OBJECTDIR}/_ext/7aa426f7
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7aa426f7/port_utils.o ../TP8_24-05/TP8b/port_utils.c

${OBJECTDIR}/led_api.o: led_api.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/led_api.o led_api.c

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
