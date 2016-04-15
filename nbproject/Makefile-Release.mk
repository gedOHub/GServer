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
	${OBJECTDIR}/ClientContainer.o \
	${OBJECTDIR}/ConsoleGLogger.o \
	${OBJECTDIR}/FileGLogger.o \
	${OBJECTDIR}/GConfig.o \
	${OBJECTDIR}/GLogger.o \
	${OBJECTDIR}/GObject.o \
	${OBJECTDIR}/GSocket.o \
	${OBJECTDIR}/LocalGLogger.o \
	${OBJECTDIR}/SCTPClientGSocket.o \
	${OBJECTDIR}/SCTPGSocket.o \
	${OBJECTDIR}/SCTPServerGSocket.o \
	${OBJECTDIR}/TCPClientGSocket.o \
	${OBJECTDIR}/TCPGSocket.o \
	${OBJECTDIR}/TCPServerGSocket.o \
	${OBJECTDIR}/TagGenerator.o \
	${OBJECTDIR}/TunnelContainer.o \
	${OBJECTDIR}/lib/socket.o \
	${OBJECTDIR}/main.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gserver

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gserver: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gserver ${OBJECTFILES} ${LDLIBSOPTIONS} -lconfig++ -Wall

${OBJECTDIR}/ClientContainer.o: ClientContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ClientContainer.o ClientContainer.cpp

${OBJECTDIR}/ConsoleGLogger.o: ConsoleGLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ConsoleGLogger.o ConsoleGLogger.cpp

${OBJECTDIR}/FileGLogger.o: FileGLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FileGLogger.o FileGLogger.cpp

${OBJECTDIR}/GConfig.o: GConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GConfig.o GConfig.cpp

${OBJECTDIR}/GLogger.o: GLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GLogger.o GLogger.cpp

${OBJECTDIR}/GObject.o: GObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GObject.o GObject.cpp

${OBJECTDIR}/GSocket.o: GSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GSocket.o GSocket.cpp

${OBJECTDIR}/LocalGLogger.o: LocalGLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LocalGLogger.o LocalGLogger.cpp

${OBJECTDIR}/SCTPClientGSocket.o: SCTPClientGSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SCTPClientGSocket.o SCTPClientGSocket.cpp

${OBJECTDIR}/SCTPGSocket.o: SCTPGSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SCTPGSocket.o SCTPGSocket.cpp

${OBJECTDIR}/SCTPServerGSocket.o: SCTPServerGSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SCTPServerGSocket.o SCTPServerGSocket.cpp

${OBJECTDIR}/TCPClientGSocket.o: TCPClientGSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TCPClientGSocket.o TCPClientGSocket.cpp

${OBJECTDIR}/TCPGSocket.o: TCPGSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TCPGSocket.o TCPGSocket.cpp

${OBJECTDIR}/TCPServerGSocket.o: TCPServerGSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TCPServerGSocket.o TCPServerGSocket.cpp

${OBJECTDIR}/TagGenerator.o: TagGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TagGenerator.o TagGenerator.cpp

${OBJECTDIR}/TunnelContainer.o: TunnelContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TunnelContainer.o TunnelContainer.cpp

${OBJECTDIR}/lib/socket.o: lib/socket.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/socket.o lib/socket.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gserver

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
