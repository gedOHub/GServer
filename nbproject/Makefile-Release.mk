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
	${OBJECTDIR}/GObject.o \
	${OBJECTDIR}/TagGenerator.o \
	${OBJECTDIR}/TunnelContainer.o \
	${OBJECTDIR}/lib/socket.o \
	${OBJECTDIR}/logger/GLogger.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/sockets/GSocket.o \
	${OBJECTDIR}/sockets/serversocket/STCPServerSocket.o \
	${OBJECTDIR}/sockets/serversocket/ServerSocket.o \
	${OBJECTDIR}/sockets/serversocket/TCPServerSocket.o \
	${OBJECTDIR}/sockets/serversocket/UDPServerSocket.o


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

${OBJECTDIR}/GObject.o: GObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GObject.o GObject.cpp

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

${OBJECTDIR}/logger/GLogger.o: logger/GLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}/logger
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/logger/GLogger.o logger/GLogger.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/sockets/GSocket.o: sockets/GSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/sockets
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sockets/GSocket.o sockets/GSocket.cpp

${OBJECTDIR}/sockets/serversocket/STCPServerSocket.o: sockets/serversocket/STCPServerSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/sockets/serversocket
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sockets/serversocket/STCPServerSocket.o sockets/serversocket/STCPServerSocket.cpp

${OBJECTDIR}/sockets/serversocket/ServerSocket.o: sockets/serversocket/ServerSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/sockets/serversocket
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sockets/serversocket/ServerSocket.o sockets/serversocket/ServerSocket.cpp

${OBJECTDIR}/sockets/serversocket/TCPServerSocket.o: sockets/serversocket/TCPServerSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/sockets/serversocket
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sockets/serversocket/TCPServerSocket.o sockets/serversocket/TCPServerSocket.cpp

${OBJECTDIR}/sockets/serversocket/UDPServerSocket.o: sockets/serversocket/UDPServerSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/sockets/serversocket
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sockets/serversocket/UDPServerSocket.o sockets/serversocket/UDPServerSocket.cpp

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
