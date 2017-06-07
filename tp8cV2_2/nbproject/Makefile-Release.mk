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
	${OBJECTDIR}/_ext/d13e46b2/graphic.o \
	${OBJECTDIR}/_ext/d13e46b2/input.o \
	${OBJECTDIR}/_ext/d13e46b2/nonblock.o \
	${OBJECTDIR}/_ext/d13e46b2/output.o \
	${OBJECTDIR}/_ext/d13e46b2/port_utils.o \
	${OBJECTDIR}/led_api.o \
	${OBJECTDIR}/main2.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tp8cv2_2

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tp8cv2_2: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tp8cv2_2 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/d13e46b2/graphic.o: ../tp8cV2/graphic.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d13e46b2
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d13e46b2/graphic.o ../tp8cV2/graphic.c

${OBJECTDIR}/_ext/d13e46b2/input.o: ../tp8cV2/input.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d13e46b2
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d13e46b2/input.o ../tp8cV2/input.c

${OBJECTDIR}/_ext/d13e46b2/nonblock.o: ../tp8cV2/nonblock.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d13e46b2
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d13e46b2/nonblock.o ../tp8cV2/nonblock.c

${OBJECTDIR}/_ext/d13e46b2/output.o: ../tp8cV2/output.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d13e46b2
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d13e46b2/output.o ../tp8cV2/output.c

${OBJECTDIR}/_ext/d13e46b2/port_utils.o: ../tp8cV2/port_utils.c
	${MKDIR} -p ${OBJECTDIR}/_ext/d13e46b2
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d13e46b2/port_utils.o ../tp8cV2/port_utils.c

${OBJECTDIR}/led_api.o: led_api.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/led_api.o led_api.c

${OBJECTDIR}/main2.o: main2.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main2.o main2.c

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
