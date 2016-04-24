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
	${OBJECTDIR}/ConsoleGLogger.o \
	${OBJECTDIR}/FileGLogger.o \
	${OBJECTDIR}/GClientContainer.o \
	${OBJECTDIR}/GCommandExecution.o \
	${OBJECTDIR}/GConfig.o \
	${OBJECTDIR}/GLogger.o \
	${OBJECTDIR}/GObject.o \
	${OBJECTDIR}/GSocket.o \
	${OBJECTDIR}/GTagGenerator.o \
	${OBJECTDIR}/GTunnelContainer.o \
	${OBJECTDIR}/LocalGLogger.o \
	${OBJECTDIR}/SCTPClientGSocket.o \
	${OBJECTDIR}/SCTPGSocket.o \
	${OBJECTDIR}/SCTPServerGSocket.o \
	${OBJECTDIR}/TCPClientGSocket.o \
	${OBJECTDIR}/TCPGSocket.o \
	${OBJECTDIR}/TCPServerGSocket.o \
	${OBJECTDIR}/UDPGSocket.o \
	${OBJECTDIR}/UDPGSocketClient.o \
	${OBJECTDIR}/UDPServerGSocket.o \
	${OBJECTDIR}/lib/socket.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++11
CXXFLAGS=-std=c++11

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

${OBJECTDIR}/ConsoleGLogger.o: nbproject/Makefile-${CND_CONF}.mk ConsoleGLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ConsoleGLogger.o ConsoleGLogger.cpp

${OBJECTDIR}/FileGLogger.o: nbproject/Makefile-${CND_CONF}.mk FileGLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FileGLogger.o FileGLogger.cpp

${OBJECTDIR}/GClientContainer.o: nbproject/Makefile-${CND_CONF}.mk GClientContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GClientContainer.o GClientContainer.cpp

${OBJECTDIR}/GCommandExecution.o: nbproject/Makefile-${CND_CONF}.mk GCommandExecution.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GCommandExecution.o GCommandExecution.cpp

${OBJECTDIR}/GConfig.o: nbproject/Makefile-${CND_CONF}.mk GConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GConfig.o GConfig.cpp

${OBJECTDIR}/GLogger.o: nbproject/Makefile-${CND_CONF}.mk GLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GLogger.o GLogger.cpp

${OBJECTDIR}/GObject.o: nbproject/Makefile-${CND_CONF}.mk GObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GObject.o GObject.cpp

${OBJECTDIR}/GSocket.o: nbproject/Makefile-${CND_CONF}.mk GSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GSocket.o GSocket.cpp

${OBJECTDIR}/GTagGenerator.o: nbproject/Makefile-${CND_CONF}.mk GTagGenerator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GTagGenerator.o GTagGenerator.cpp

${OBJECTDIR}/GTunnelContainer.o: nbproject/Makefile-${CND_CONF}.mk GTunnelContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GTunnelContainer.o GTunnelContainer.cpp

${OBJECTDIR}/LocalGLogger.o: nbproject/Makefile-${CND_CONF}.mk LocalGLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LocalGLogger.o LocalGLogger.cpp

${OBJECTDIR}/SCTPClientGSocket.o: nbproject/Makefile-${CND_CONF}.mk SCTPClientGSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SCTPClientGSocket.o SCTPClientGSocket.cpp

${OBJECTDIR}/SCTPGSocket.o: nbproject/Makefile-${CND_CONF}.mk SCTPGSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SCTPGSocket.o SCTPGSocket.cpp

${OBJECTDIR}/SCTPServerGSocket.o: nbproject/Makefile-${CND_CONF}.mk SCTPServerGSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SCTPServerGSocket.o SCTPServerGSocket.cpp

${OBJECTDIR}/TCPClientGSocket.o: nbproject/Makefile-${CND_CONF}.mk TCPClientGSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TCPClientGSocket.o TCPClientGSocket.cpp

${OBJECTDIR}/TCPGSocket.o: nbproject/Makefile-${CND_CONF}.mk TCPGSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TCPGSocket.o TCPGSocket.cpp

${OBJECTDIR}/TCPServerGSocket.o: nbproject/Makefile-${CND_CONF}.mk TCPServerGSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TCPServerGSocket.o TCPServerGSocket.cpp

${OBJECTDIR}/UDPGSocket.o: nbproject/Makefile-${CND_CONF}.mk UDPGSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/UDPGSocket.o UDPGSocket.cpp

${OBJECTDIR}/UDPGSocketClient.o: nbproject/Makefile-${CND_CONF}.mk UDPGSocketClient.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/UDPGSocketClient.o UDPGSocketClient.cpp

${OBJECTDIR}/UDPServerGSocket.o: nbproject/Makefile-${CND_CONF}.mk UDPServerGSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/UDPServerGSocket.o UDPServerGSocket.cpp

${OBJECTDIR}/lib/socket.o: nbproject/Makefile-${CND_CONF}.mk lib/socket.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/socket.o lib/socket.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include -Isockets -Isockets/serversocket -Ilogger -include /usr/include/libconfig.h++ -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
