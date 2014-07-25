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
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/bignum.o \
	${OBJECTDIR}/src/bn_except.o \
	${OBJECTDIR}/src/bn_int_type.o \
	${OBJECTDIR}/src/bn_limits.o \
	${OBJECTDIR}/src/bn_setup.o \
	${OBJECTDIR}/src/bn_type.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	tests/arithmetic_test \
	tests/compress_test \
	tests/integer_test

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Wall -Werror -Wextra -pedantic -pedantic-errors -flto
CXXFLAGS=-Wall -Werror -Wextra -pedantic -pedantic-errors -flto

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk bin/libbignum.a

bin/libbignum.a: ${OBJECTFILES}
	${MKDIR} -p bin
	${RM} bin/libbignum.a
	${AR} -rv bin/libbignum.a ${OBJECTFILES} 
	$(RANLIB) bin/libbignum.a

${OBJECTDIR}/src/bignum.o: src/bignum.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/bignum.o src/bignum.cpp

${OBJECTDIR}/src/bn_except.o: src/bn_except.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/bn_except.o src/bn_except.cpp

${OBJECTDIR}/src/bn_int_type.o: src/bn_int_type.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/bn_int_type.o src/bn_int_type.cpp

${OBJECTDIR}/src/bn_limits.o: src/bn_limits.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/bn_limits.o src/bn_limits.cpp

${OBJECTDIR}/src/bn_setup.o: src/bn_setup.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/bn_setup.o src/bn_setup.cpp

${OBJECTDIR}/src/bn_type.o: src/bn_type.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/bn_type.o src/bn_type.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
tests/arithmetic_test: ${TESTDIR}/tests/arithmetic_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p tests
	${LINK.cc}   -o tests/arithmetic_test -s $^ ${LDLIBSOPTIONS} 

tests/compress_test: ${TESTDIR}/tests/compress_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p tests
	${LINK.cc}   -o tests/compress_test -s $^ ${LDLIBSOPTIONS} 

tests/integer_test: ${TESTDIR}/tests/integer_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p tests
	${LINK.cc}   -o tests/integer_test -s $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/arithmetic_test.o: tests/arithmetic_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -Iinclude -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/arithmetic_test.o tests/arithmetic_test.cpp


${TESTDIR}/tests/compress_test.o: tests/compress_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -Iinclude -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/compress_test.o tests/compress_test.cpp


${TESTDIR}/tests/integer_test.o: tests/integer_test.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -Iinclude -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/integer_test.o tests/integer_test.cpp


${OBJECTDIR}/src/bignum_nomain.o: ${OBJECTDIR}/src/bignum.o src/bignum.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/bignum.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/bignum_nomain.o src/bignum.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/bignum.o ${OBJECTDIR}/src/bignum_nomain.o;\
	fi

${OBJECTDIR}/src/bn_except_nomain.o: ${OBJECTDIR}/src/bn_except.o src/bn_except.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/bn_except.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/bn_except_nomain.o src/bn_except.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/bn_except.o ${OBJECTDIR}/src/bn_except_nomain.o;\
	fi

${OBJECTDIR}/src/bn_int_type_nomain.o: ${OBJECTDIR}/src/bn_int_type.o src/bn_int_type.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/bn_int_type.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/bn_int_type_nomain.o src/bn_int_type.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/bn_int_type.o ${OBJECTDIR}/src/bn_int_type_nomain.o;\
	fi

${OBJECTDIR}/src/bn_limits_nomain.o: ${OBJECTDIR}/src/bn_limits.o src/bn_limits.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/bn_limits.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/bn_limits_nomain.o src/bn_limits.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/bn_limits.o ${OBJECTDIR}/src/bn_limits_nomain.o;\
	fi

${OBJECTDIR}/src/bn_setup_nomain.o: ${OBJECTDIR}/src/bn_setup.o src/bn_setup.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/bn_setup.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/bn_setup_nomain.o src/bn_setup.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/bn_setup.o ${OBJECTDIR}/src/bn_setup_nomain.o;\
	fi

${OBJECTDIR}/src/bn_type_nomain.o: ${OBJECTDIR}/src/bn_type.o src/bn_type.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	@NMOUTPUT=`${NM} ${OBJECTDIR}/src/bn_type.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -s -Iinclude -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/bn_type_nomain.o src/bn_type.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/src/bn_type.o ${OBJECTDIR}/src/bn_type_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    tests/arithmetic_test || true; \
	    tests/compress_test || true; \
	    tests/integer_test || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} bin/libbignum.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
