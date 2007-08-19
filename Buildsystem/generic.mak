# Oliver Kullmann, 6.3.2002 (Swansea)

# See Buildsystem/docus/generic.hpp for the general documentation.

#
# ===============================================================================
# General make variable for customisation of compilation
# ===============================================================================
#
# CXXFLAGS		For specifying options for the C++ compiler.
# CPPFLAGS              For specifying options for the preprocessor. 
# CFLAGS                For specifying options for the C compiler.
#
# These three variables are not used by the build system, but are free for the user.
#
# ===============================================================================
# Enviroment/Make build system variables
# ===============================================================================
#
# The most important build system parameters come as environment/Make variable
# pairs. 
# 
# (OKPLATFORM,OKplatform)
# (OKSYSTEM,OKsystem)
# (SYSTEMDIRECTORIES,SystemDirectories)
# (BOOST,Boost)
# (EXTERNALSOURCES,ExternalSources)
#
# In each case the default behaviour is for the build system to use the 
# environment variable unless the Make variable is defined, in which case
# the Make variable is used.
#
# OKPLATFORM/OKplatform
#
# This variable pair specifies the top level directory of the OKplatform.
# The subdirectories $(ExternalSources) and $(SystemDirectories) are created by 
# the build system in the directory specified by the value of this variable.
#
# If both the environment variable OKPLATFORM and the Make variable OKplatform 
# are undefined then the build system gives an error message.
#
# OKSYSTEM/OKsystem
#
# This variable pair specifies the top level directory of the OKsystem
# source tree. The build system assumes that the directory specified by the value
# of this variable is the directory containing the subdiretories "Annotations",
# "Transitional" and "OKlibrary".
#
# SYSTEMDIRECTORIES/SystemDirectories
#
# This variable pair specifies the location of the top level directory of 
# the OKlibrary build tree. The build system creates the subdirectories "aux", "bin", 
# "doc" and "lib" in the directory specified by the value of this variable.
#
# BOOST/Boost
#
# This variable pair specifies the location of the installation directory 
# of the Boost distribution to be used by the build system for compiling the 
# library.
#
# EXTERNALSOURCES/ExternalSources
#
# This variable pair specifies the location of the directory used by the 
# build system to build local versions of the main software required for
# the OKlibrary.
#
# ===============================================================================
# (SV) System variables (can be optionally redefined) : 
# ===============================================================================
# 
# System variable are for internal use of the build system, but can be 
# redefined by the user with suitable precaution. It is expected in most
# cases that there is no need to redefine any of the values of these variables
# and any redefinition needs to be thoroughly thought through.
#
# ##################################################################################

SHELL = /bin/sh
.SUFFIXES :

# ################################################################
# FUNCTIONS (F)
# ################################################################

# ----------------------------------------------------------
# last-element (F)
#
# Returns last element of its argument.
# ----------------------------------------------------------
define last-element
$(word $(words $1),$1)
endef
# ----------------------------------------------------------

# ######################################################################

# ################################################################
# LOCAL MODULE DEFINITIONS
# ################################################################

# ----------------------------------------------------------
# srcdir (LV)
#
# The full path of the current directory of source code to 
# be compiled.
# ----------------------------------------------------------
ifndef srcdir
this-makefile := $(call last-element,$(MAKEFILE_LIST))
srcdir := $(shell cd $(dir $(this-makefile)); pwd)
endif
# ----------------------------------------------------------

# ----------------------------------------------------------
# module-name (LV)
# The name of the current module.
# ----------------------------------------------------------
module-name := $(notdir $(srcdir))
# ----------------------------------------------------------


# Every module which needs to be built contains a symbolic link, called "makefile"
# to the generic makefile Transitional/Buildsystem/generic.mak.

# The following definitions are temporary: The oklib-masterscript will define OKplatform and OKconfiguration.
ifndef OKplatform
  ifdef OKPLATFORM
    OKplatform = $(OKPLATFORM)
  else
    $(error Either OKplatform (a make-variable) or OKPLATFORM (an environment-variable) must be defined when calling this makefile (as the full directory path containing the OKplatform)!)
  endif
endif
ifndef OKconfiguration
  OKconfiguration = $(OKplatform)/.oklib/Configuration
endif

include $(OKconfiguration)/configuration_data.mak
export

# ######################################################################

# ----------------------------------------------------------
#  Definitions required from standardgoals.mak
#    special_goals
#    cleaning_goals
#    forced_goals
# ----------------------------------------------------------
include $(OKbuildsystem)/standardgoals.mak
export
# ----------------------------------------------------------

# ----------------------------------------------------------
#  Definitions required from makefile.definitions:
#   General_options
#   Optimisation_options
#   test_program (for the old test-system)
#   programs
#   source_libraries
#   link_libraries
# ----------------------------------------------------------
include $(srcdir)/definitions.mak
# ----------------------------------------------------------

# ----------------------------------------------------------
# source_libraries (LV)
#
# The recursive variable source_libraries is defined in the local 
# definitions.mak file. Here we add to the back
# of the include list the OKsystem include option 
# -I$(OKsystem).
# (By adding to the back it it possible, by using compiler
# option "-I-" at the beginning of the source-libraries list, 
# to prevent the "current" directory to be
# used (for all directories *before* "-I-" the system-header-files,
# specified by "<>", are ignored!)).
# ----------------------------------------------------------
source_libraries += $(OKsystem_include)
# ----------------------------------------------------------

# ################################################################
# BUILD DIRECTORY STRUCTURE
# ################################################################


# ################################################################
# COMPILATION
# ################################################################

# ----------------------------------------------------------
# programs (LV)
#
# This variable is not defined here, but rather it's
# definition is in the local definitions.mak.
#
# If there are program names specified in the local
# definitions.mak then we prefix those program
# names with the full path to the executable directory, so
# that Make knows where to build those executables.
#
# Contains also the test program for the old test-system (but not
# for the new one).
# ----------------------------------------------------------
ifneq ($(programs),)
  programs := $(addprefix $(bin_dir)/, $(programs))
endif
# ----------------------------------------------------------

# ----------------------------------------------------------
# test_program (LV) (old test system)
#
# This variable is not defined here, but rather it's
# definition is in the local definitions.mak.
#
# If test programs (from the old test system) are specified
# in the local definitions.mak then
# those program names are prefixed here by the full path
# to the directory where test executables are built, so that
# Make knows where to build those executables. Also, those
# full program path names are appended to the variable
# "programs".
#
# ----------------------------------------------------------
ifneq ($(test_program),) # old test-system needed
  test_program := $(addprefix $(bin_dir)/, $(test_program))
  programs += $(test_program)
endif
# ----------------------------------------------------------


# ----------------------------------------------------------
# new_test_program (LV)
#
# The full path name for the test executable for the
# current module.
# ----------------------------------------------------------
new_test_program := $(test-bin_dir)/$(module-name)
# ----------------------------------------------------------

# ----------------------------------------------------------
# standard_test_program_object_file (SV)
#
# The full path name for the object file which is
# linked to by every test program.
# ----------------------------------------------------------
standard_test_program_object_file := $(lib_dir)/TestProgram_DesignStudy.o
# ----------------------------------------------------------

# ----------------------------------------------------------
# testobjects-dir (LV)
# 
# The subdirectory of the module source code
# directory which contains the test object-files.
# ----------------------------------------------------------
testobjects-dir := $(srcdir)/testobjects
# ----------------------------------------------------------

# ----------------------------------------------------------
# name_addition (LV)
#
# A string which is appended to the name of every executable.
# By default the value is just the optimisation options.
# ----------------------------------------------------------
name_addition := $(shell echo $(Optimisation_options) | tr --delete " ")
# ----------------------------------------------------------

# ----------------------------------------------------------
# programs_optimised (LV)
#
# The names of the optimised executables.
# ----------------------------------------------------------
programs_optimised := $(programs:=$(name_addition))
# ----------------------------------------------------------

# ----------------------------------------------------------
# new_test_program_optimised (LV)
#
# The names of the optimised test programs. (New test
# system).
# ----------------------------------------------------------
new_test_program_optimised := $(new_test_program)$(name_addition)
# ----------------------------------------------------------

# ----------------------------------------------------------
# standard_test_program_object_file_optimised (LV)
#
# The full path name of the optimised object-file to which
# every test program is linked.
# ----------------------------------------------------------
standard_test_program_object_file_optimised := $(lib_dir)/TestProgram_DesignStudy$(name_addition).o
# ----------------------------------------------------------

# ######################################################################

# ################################################################
# COMPILATION UNITS
# ################################################################

# ----------------------------------------------------------
# compilation_units_cpp (LV)
#
# The names of every C++ source code file in the current
# module source code directory.
# ----------------------------------------------------------
compilation_units_cpp := $(wildcard $(srcdir)/*.cpp)
compilation_units_cpp := $(notdir $(compilation_units_cpp))
# ----------------------------------------------------------

# ----------------------------------------------------------
# compilation_units_c (LV)
#
# The names of every C source code file in the current
# module source code directory.
# ----------------------------------------------------------
compilation_units_c := $(wildcard $(srcdir)/*.c)
compilation_units_c := $(notdir $(compilation_units_c))
# ----------------------------------------------------------

# ----------------------------------------------------------
# test_compilation_units (LV) (new test system)
#
# The full path names of every C++ source code file in
# the testobjects subdirectory of the current module
# ----------------------------------------------------------
test_compilation_units := $(wildcard $(testobjects-dir)/*.cpp)
# ----------------------------------------------------------

# ----------------------------------------------------------
# dependency_files_cpp (LV)
#
# The full path name of the dependency files for every C++
# source code file in the current module.
# ----------------------------------------------------------
dependency_files_cpp := $(compilation_units_cpp:.cpp=.d)
dependency_files_cpp := $(addprefix $(dependencies_dir)/, $(dependency_files_cpp))
# ----------------------------------------------------------

# ----------------------------------------------------------
# dependency_files_c (LV)
#
# The full path name of the dependency files for every C
# source code file in the current module.
# ----------------------------------------------------------
dependency_files_c := $(compilation_units_c:.c=.d) 
dependency_files_c := $(addprefix $(dependencies_dir)/, $(dependency_files_c))
# ----------------------------------------------------------

# ----------------------------------------------------------
# test_dependency_files (LV)
#
# The full path name of the dependency files for every 
# test source code file in the current module.
# ----------------------------------------------------------
test_dependency_files := $(notdir $(test_compilation_units))
test_dependency_files := $(test_dependency_files:.cpp=.d)
test_dependency_files := $(addprefix $(test-aux_dir)/, $(test_dependency_files))
# ----------------------------------------------------------

# ----------------------------------------------------------
# dependency_files (LV)
#
# The full path name of the dependency files for every C
# and C++ source code file in the current module.
# ----------------------------------------------------------
dependency_files := $(dependency_files_cpp) \
                    $(dependency_files_c) \
                    $(dependency_files) \
                    $(test_dependency_files)
# ----------------------------------------------------------

# ----------------------------------------------------------
# object_files_cpp (LV)
#
# The full path name of the object files for every C++
# source code file in the current directory.
# ----------------------------------------------------------
object_files_cpp := $(compilation_units_cpp:.cpp=.o) 
object_files_cpp := $(addprefix $(lib_dir)/, $(object_files_cpp))
# ----------------------------------------------------------

# ----------------------------------------------------------
# object_files_c (LV)
# 
# The full path name of the object files for every C
# source code file in the current directory.
# ----------------------------------------------------------
object_files_c := $(compilation_units_c:.c=.o)
object_files_c := $(addprefix $(lib_dir)/, $(object_files_c))
# ----------------------------------------------------------

# ----------------------------------------------------------
# object_files (LV)
# 
# The full path name of the object files for every C and C++
# source code file in the current directory.
# ----------------------------------------------------------
object_files := $(object_files_cpp) $(object_files_c)
# ----------------------------------------------------------

# ----------------------------------------------------------
# object_files_cpp_optimised (LV)
# 
# The full path name of the optimised object files for every
# C++ source code file in the current directory.
# ----------------------------------------------------------
object_files_cpp_optimised := $(compilation_units_cpp:.cpp=$(name_addition).o)
object_files_cpp_optimised := $(addprefix $(lib_dir)/, $(object_files_cpp_optimised))
# ----------------------------------------------------------

# ----------------------------------------------------------
# object_files_c_optimised (LV)
# 
# The full path name of the optimised object files for every
# C source code file in the current directory.
# ----------------------------------------------------------
object_files_c_optimised := $(compilation_units_c:.c=$(name_addition).o)
object_files_c_optimised := $(addprefix $(lib_dir)/, $(object_files_c_optimised))
# ----------------------------------------------------------

# ----------------------------------------------------------
# object_files_optimised (LV)
# 
# The full path name of the optimised object files for every
# C and C++ source code file in the current directory.
# ----------------------------------------------------------
object_files_optimised := $(object_files_cpp_optimised) $(object_files_c_optimised)
# ----------------------------------------------------------

# ----------------------------------------------------------
# test_object_files (LV)
#
# The full path names of the object files for the tests in the
# current module (new test system).
# ----------------------------------------------------------
test_object_files := $(notdir $(test_compilation_units))
test_object_files := $(test_object_files:.cpp=.o)
test_object_files := $(addprefix $(test-lib_dir)/, $(test_object_files))
# ----------------------------------------------------------

# ----------------------------------------------------------
# test_object_files (LV)
#
# The full path names of the object files for the tests in the
# current module.
# ----------------------------------------------------------
test_object_files_optimised := $(notdir $(test_compilation_units))
test_object_files_optimised := $(test_object_files_optimised:.cpp=$(name_addition).o)
test_object_files_optimised := $(addprefix $(test-lib_dir)/, $(test_object_files_optimised))
# ----------------------------------------------------------

# ----------------------------------------------------------
# test_file (SV)
#
# The old test system timestamp file for the current module
# test program. 
# ----------------------------------------------------------
test_file := $(srcdir)/test
# ----------------------------------------------------------

# ----------------------------------------------------------
# testop_file (SV)
#
# The old test system timestamp file for the current module
# optimised test program. .
# ----------------------------------------------------------
testop_file := $(srcdir)/testop
# ----------------------------------------------------------

# ################################################################
# GENERAL MAKE VARIABLES FOR CUSTOMISATION OF COMPILATION
# ################################################################

# ----------------------------------------------------------
# CXX (SV)
#
# Name of the C++ compiler executable. 
# default value: recommended library version of g++
# OK: perhaps this should go to configuration?
# ----------------------------------------------------------
CXX = $(gpp_system_call)
# ----------------------------------------------------------

# ----------------------------------------------------------
# CC (SV)
#
# Name of the C compiler executable.
# default value: recommended library version of gcc
# OK: perhaps this should go to configuration?
# ----------------------------------------------------------
CC = $(gcc_system_call)
# ----------------------------------------------------------

# ----------------------------------------------------------
# Standard_options (SV)
# Standard_options_c (SV)
#
# Language-standard options for C++ and C compilation.
# Defined in makefile_generic.mak.
# Passed to the compiler for every program.
# Default values : -ansi -pedantic resp. -std=c99 -pedantic.
# ----------------------------------------------------------
Standard_options   := -ansi -pedantic
Standard_options_c := -std=c99 -pedantic 
# ----------------------------------------------------------

# ----------------------------------------------------------
# Warning_options (SV)
#
# Compiler warnings. Defined in makefile_generic.mak. Passed to 
# the compiler for every program.
# Default value : -Wall
# ----------------------------------------------------------
Warning_options := -Wall
# ----------------------------------------------------------

# ----------------------------------------------------------
# Compile_tool (SV)     
#
# A command to prefix each call of the compiler. So, for
# example to use the time program to time the execution
# of the compiler.
# Default value : time -p (measuring the wall clock time, 
# the process time and the system time used in total for 
# the execution)
# ----------------------------------------------------------
Compile_tool := time -p
# ----------------------------------------------------------

# ----------------------------------------------------------
# Link_tool (SV)
#             
# A command to prefix each call of the linker. So, for
# example to use the time program to time the execution
# of the linker.
# Default value : time -p (measuring the wall clock time, 
# the process time and the system time used in total for 
# the execution)
# ----------------------------------------------------------
Link_tool := time -p
# ----------------------------------------------------------

# ----------------------------------------------------------
# Test_tool (SV)
#
# A command to prefix each call of a test program. So, for
# example to use the time program to time the execution
# of the test program. 
# Default value : time -p (measuring the wall clock time, 
# the process time and the system time used in total for 
# the execution)
# Setting Test_tool="valgrind --quiet" runs all tests with 
# memory check.
# ----------------------------------------------------------
Test_tool := time -p
# ----------------------------------------------------------

# ######################################################################

# ################################################################
# VARIABLES FOR CUSTOMISATION OF NEW TEST SYSTEM
# ################################################################

# ----------------------------------------------------------
# test_level (SV)
# By default has the value "basic" but can be
# redefined to either of the values "full" or
# "extensive". Specifies the level of testing
# carried out be (new) test system.
test_level := basic
# ----------------------------------------------------------
# error_file (SV)
# Specifies the location of the error log file
# for the test program of the current module.
error_file := $(test-aux_dir)/Error
# ----------------------------------------------------------
# message_file (SV)
# Specifies the location of the messages log file
# for the test program of the current module.
message_file := $(test-aux_dir)/Message
# ----------------------------------------------------------
# log_file (SV)
# Specifies the location of the log file for the
# test program of the current module.
log_file := $(test-aux_dir)/Log
# ----------------------------------------------------------
# error_stream (SV)   
# Specifies a stream for the streaming of error
# messages.
error_stream := "cerr|ofstream-w=$(error_file)|ofstream-w=$(log_file)"
# ----------------------------------------------------------
# message_stream (SV)
# Specifies a stream for the streaming of non-
# error messages.
message_stream := "cout|ofstream-w=$(message_file)|ofstream-w=$(log_file)"
# ----------------------------------------------------------
# log_stream (SV)
# Specifies a stream for the streaming of log
# messages.
log_stream := "ofstream-w=$(log_file)"
# ----------------------------------------------------------
# error_level (SV)                 
# Specifies verbosity level for error messages,
# by default 0 (lowest verbosity).
error_level := 0
# ----------------------------------------------------------
# message_level (SV)               
# Specifies verbosity level for non-error 
# messages, default 0 (lowest verbosity).
message_level := 0
# ----------------------------------------------------------
# log_level (SV)                   
# Specifies verbosity level for log 
# messages, default 0 (lowest verbosity).
log_level := 0
# ----------------------------------------------------------
# error_lang (SV)                   
# Specifies language for error messages, by
# default equal to en_GB.
error_lang := en_GB
# ----------------------------------------------------------
# message_lang (SV)                
# Specifies language for non-error messages, by
# default equal to en_GB.
message_lang := en_GB
# ----------------------------------------------------------
# log_lang (SV)             
# Specifies language for log messages, by
# default equal to en_GB.
log_lang := en_GB
# ----------------------------------------------------------
# test_parameters (LV)              
# Parameters to be passed to the test program for
# the current module.
test_parameters := $(test_level) \
                   $(error_stream) \
                   $(message_stream) \
                   $(log_stream) \
                   $(error_level) \
                   $(message_level) \
                   $(log_level) \
                   $(error_lang) \
                   $(message_lang) \
                   $(log_lang)
# ----------------------------------------------------------

# ----------------------------------------------------------
# test_timestamp (LV)
#
# Timestamp for the creation of test programs with
# the new test system.
# ----------------------------------------------------------
test_timestamp := $(test-aux_dir)/new_test_$(test_level)
# ----------------------------------------------------------

# ----------------------------------------------------------
# testop_timestamp (LV)
#
# Timestamp for the creation of optimised test
# programs with the new test system.
# ----------------------------------------------------------
testop_timestamp := $(test-aux_dir)/new_testop_$(test_level)
# ----------------------------------------------------------

# ######################################################################

# ################################################################
# VARIABLES FOR GCC AND BOOST VERSIONS, INCLUDES AND LINKING
# ################################################################

# ----------------------------------------------------------
# system_version (LV)
#
# If defined (with any non-empty value) then the build
# system will use the system versions of gcc and boost
# rather than the recommended local versions.
#
# gcc_version_number (SV)           
#
# Can be defined to specify the version number
# of a locally installed GCC to be used by the
# build system instead of the system compiler. By
# default, has the value of the recommended version
# of gcc.
# 
# boost_version_number (SV)
#
# Can be defined to specify the version number
# of a locally installed Boost to be used by the
# build system instead of the system Boost. By
# default, has the value of the recommended version
# of boost.
#
# ----------------------------------------------------------
system_versions :=

ifeq ($(system_versions),)
    gcc_version_number:= $(gcc_recommended_version_number)
    boost_version_number:= $(boost_recommended_version_number)
endif
# ----------------------------------------------------------


# ----------------------------------------------------------
#
# alternative_library_path
#
#  Specifies the full options necessary to pass the full path
#  of the Gcc and Boost link-libraries to the compiler and
#  linker. With "-Wl,-rpath,Path" we tell the compiler to 
#  pass the option "-rpath Path" to the linker, which will 
#  add Path to the places searched for this program for 
#  run-time-libraries.
#
# boost_version_number
#
#  The version number of the Boost library.
#
# Boost
#
#  Include option to be passed to the compiler, specifying
#  the location of the Boost include directory. 
#
# ----------------------------------------------------------
alternative_library_path:=

ifneq ($(gcc_version_number),) # alternative gcc specified
  CXX = $(ExternalSources)/Gcc/$(gcc_version_number)/bin/g++
  CC = $(ExternalSources)/Gcc/$(gcc_version_number)/bin/gcc
  alternative_library_path:= -L$(ExternalSources)/Gcc/$(gcc_version_number)/lib64 -Wl,-rpath,$(ExternalSources)/Gcc/$(gcc_version_number)/lib64 -L$(ExternalSources)/Gcc/$(gcc_version_number)/lib -Wl,-rpath,$(ExternalSources)/Gcc/$(gcc_version_number)/lib
  ifeq ($(boost_version_number),)
    ifndef Boost
      $(error Variable Boost must be defined!)
    endif
    boost_version_number := $(patsubst -I%,%,$(Boost))
    boost_version_number := $(patsubst %/,%,$(boost_version_number))
    boost_version_number := $(notdir $(boost_version_number))
    boost_version_number := $(patsubst boost-%,%,$(boost_version_number))
  endif
  alternative_library_path := $(alternative_library_path) -L$(ExternalSources)/Boost/$(boost_version_number)+$(gcc_version_number)/lib -Wl,-rpath,$(ExternalSources)/Boost/$(boost_version_number)+$(gcc_version_number)/lib
  Boost = -I$(ExternalSources)/Boost/$(boost_version_number)+$(gcc_version_number)/include/boost-$(boost_version_number)
else # no alternative gcc specified
  ifneq ($(boost_version_number),) # alternative boost specified
  alternative_library_path := $(alternative_library_path) -L$(ExternalSources)/Boost/$(boost_version_number)/lib -Wl,-rpath,$(ExternalSources)/Boost/$(boost_version_number)/lib
  Boost = -I$(ExternalSources)/Boost/$(boost_version_number)/include/boost-$(boost_version_number)
  endif
endif

# ######################################################################


# ################################################################
# DOCUMENTATION MAKEFILE INCLUDE STATEMENTS
# ################################################################

include $(OKbuildsystem)/OKlibBuilding/Targets/html/doxygen_documentation.mak
include $(OKbuildsystem)/OKlibBuilding/Targets/html/documentation_index.mak

# ######################################################################

# ################################################################
# MAIN TARGETS
# ################################################################

# ----------------------------------------------------------
# all 
#
# Build all optimised and unoptimised object files and
# programs (including test programs)
# ----------------------------------------------------------
all : unoptimised optimised
# ----------------------------------------------------------

# ----------------------------------------------------------
# $(build_directories)
#
# Make a directory with the target name, creating all
# parent directories if necessary.
# ----------------------------------------------------------
$(build_directories) :
	@mkdir -p $@
# ----------------------------------------------------------

# ----------------------------------------------------------
# unoptimised
#
# Build all unoptimised object files and programs (including
# test programs).
# ----------------------------------------------------------
unoptimised : $(object_files) $(programs)
# ----------------------------------------------------------

# ----------------------------------------------------------
# optimised
#
# Build optimised object files and programs (including test
# programs from old test system).
# ----------------------------------------------------------
optimised : $(object_files_optimised) $(programs_optimised)
# ----------------------------------------------------------

# ----------------------------------------------------------
# check
#
# Perform all tests (unoptimised and optimised) from the old 
# test system.
# ----------------------------------------------------------
check : test testop
# ----------------------------------------------------------

# ----------------------------------------------------------
# new_check
#
# Perform all tests (unoptimised and optimised) from the new 
# test system.
# ----------------------------------------------------------
new_check : new_test new_testop
# ----------------------------------------------------------

# ----------------------------------------------------------
# test, testop
#
# If there are test programs from the old test system in the
# current module then build those tests and perform them. 
# Creating a timestamp file to prevent the next 'make check'
# from running unmodified tests again.
# ----------------------------------------------------------
ifneq ($(test_program),) # old test-system needed
test : $(test_file)
testop : $(testop_file)
else
test :
testop :
endif
# ----------------------------------------------------------

# ----------------------------------------------------------
# new_test, new_testop
#
# If there are test programs from the new test system in the
# current module then build those tests and perform them. 
# Creating a timestamp file to prevent the next 'make check' 
# from running unmodified tests again.
# ----------------------------------------------------------
new_test : $(test_timestamp)
new_testop : $(testop_timestamp)
# ----------------------------------------------------------

# ----------------------------------------------------------
# $(test_file)
# $(testop_file)
#
# Run the test program from the old test system, using the
# $(Test_tool) and touch the corresponding timestamp file.
# ----------------------------------------------------------
$(test_file) : $(test_program)
	$(Test_tool) $(test_program)
	touch $(test_file)
$(testop_file) : $(test_program)$(name_addition)
	$(Test_tool) $(test_program)$(name_addition)
	touch $(testop_file)
# ----------------------------------------------------------

# ----------------------------------------------------------
# $(test_timestamp)
# $(testop_timestamp)
#
# Run the test program from the new test system, using the
# $(Test_tool) and touch the corresponding timestamp file.
# ----------------------------------------------------------
$(test_timestamp) : $(new_test_program) | $(test-aux_dir)
	$(Test_tool) $(new_test_program) $(test_parameters)
	touch $(test_timestamp)
$(testop_timestamp) : $(new_test_program_optimised) | $(test-aux_dir)
	$(Test_tool) $(new_test_program_optimised) $(test_parameters)
	touch $(testop_timestamp)
# ----------------------------------------------------------

# ----------------------------------------------------------
# force
#
# Target to force actions
# ----------------------------------------------------------
force :
# ----------------------------------------------------------

# ----------------------------------------------------------
# Include the list of dependencies from the relevant 
# dependency file.
# ----------------------------------------------------------
ifeq ($(firstword $(filter $(special_goals) $(cleaning_goals) $(forced_goals), $(MAKECMDGOALS))),)
include $(dependency_files)
endif
# ----------------------------------------------------------

# ----------------------------------------------------------
# $(dependency_files_cpp)
# 
# Extract dependency information from the C++ object files
# for the current module and write it to a dependency
# file in $(dependencies_dir)
# ----------------------------------------------------------
$(dependency_files_cpp) : $(dependencies_dir)/%.d : $(srcdir)/%.cpp | $(dependencies_dir)
	$(CXX) -MM -MF $@ -MT $(lib_dir)/$*.o -MT $(lib_dir)/$*$(name_addition).o -MT $@ $(source_libraries) $<
# ----------------------------------------------------------

# ----------------------------------------------------------
# $(dependency_files_c)
# 
# Extract dependency information from the C object files
# for the current module and write it to a dependency
# file in $(dependencies_dir)
# ----------------------------------------------------------
$(dependency_files_c) : $(dependencies_dir)/%.d : $(srcdir)/%.c | $(dependencies_dir)
	$(CC) -MM -MF $@ -MT $(lib_dir)/$*.o -MT $(lib_dir)/$*$(name_addition).o -MT $@ $(source_libraries) $<
# ----------------------------------------------------------

# ----------------------------------------------------------
# $(test_dependency_files)
# 
# Extract dependency information from the test object files
# for the current module and write it to a dependency
# file in $(dependencies_dir)
# ----------------------------------------------------------
$(test_dependency_files) : $(test-aux_dir)/%.d : $(testobjects-dir)/%.cpp | $(test-aux_dir)
	$(CXX) -MM -MF $@ -MT $(test-lib_dir)/$*.o -MT $(test-lib_dir)/$*$(name_addition).o -MT $@ $(source_libraries) $<
# ----------------------------------------------------------

# ----------------------------------------------------------
# $(object_files_cpp_optimised)
#
# Compile optimised C++ object files for the current module.
# ----------------------------------------------------------
$(object_files_cpp_optimised) : $(lib_dir)/%$(name_addition).o : $(srcdir)/%.cpp | $(lib_dir)
	$(Compile_tool) $(CXX) -c -o $@ $(Standard_options) $(Warning_options) $(Optimisation_options) $(CPPFLAGS) $(CXXFLAGS) $(source_libraries) $<
# ----------------------------------------------------------

# ----------------------------------------------------------
# $(object_files_cpp)
#
# Compile unoptimised C++ object files for the current module.
# ----------------------------------------------------------
$(object_files_cpp) : $(lib_dir)/%.o : $(srcdir)/%.cpp | $(lib_dir)
	$(Compile_tool) $(CXX) -c -o $@ $(Standard_options) $(Warning_options) $(General_options) $(CPPFLAGS) $(CXXFLAGS) $(source_libraries) $<
# ----------------------------------------------------------

# ----------------------------------------------------------
# $(object_files_c_optimised)
#
# Compile optimised C object files for the current module.
# ----------------------------------------------------------
$(object_files_c_optimised) : $(lib_dir)/%$(name_addition).o : $(srcdir)/%.c | $(lib_dir)
	$(Compile_tool) $(CC) -c -o $@ $(Standard_options_c) $(Warning_options) $(Optimisation_options) $(CPPFLAGS) $(CFLAGS) $(source_libraries) $<
# ----------------------------------------------------------

# ----------------------------------------------------------
# $(object_files_c)
#
# Compile unoptimised C object files for the current module.
# ----------------------------------------------------------
$(object_files_c) : $(lib_dir)/%.o : $(srcdir)/%.c | $(lib_dir)
	$(Compile_tool) $(CC) -c -o $@ $(Standard_options_c) $(Warning_options) $(General_options) $(CPPFLAGS) $(CFLAGS) $(source_libraries) $<
# ----------------------------------------------------------

# ----------------------------------------------------------
# $(test_object_files)
#
# Compile unoptimised test object files for the current module.
# ----------------------------------------------------------
$(test_object_files) : $(test-lib_dir)/%.o : $(testobjects-dir)/%.cpp | $(test-lib_dir)
	$(Compile_tool) $(CXX) -c -o $@ $(Standard_options) $(Warning_options) $(General_options) $(CPPFLAGS) $(CXXFLAGS) $(source_libraries) $<
# ----------------------------------------------------------

# ----------------------------------------------------------
# $(test_object_files_optimised)
#
# Compile optimised test object files for the current module.
# ----------------------------------------------------------
$(test_object_files_optimised) : $(test-lib_dir)/%$(name_addition).o : $(testobjects-dir)/%.cpp | $(test-lib_dir)
	$(Compile_tool) $(CXX) -c -o $@ $(Standard_options) $(Warning_options) $(Optimisation_options) $(CPPFLAGS) $(CXXFLAGS) $(source_libraries) $<
# ----------------------------------------------------------

# ----------------------------------------------------------
# get-link-libraries      
#
# If the current module contains a file 
# Module.link_libraries then echo the contents
# of this file, otherwise echo the Make variable
# $(link_libraries).
# ----------------------------------------------------------
define get-link_libraries
$$(if [[ -e $(srcdir)/$*.link_libraries ]]; then $(srcdir)/$*.link_libraries; else echo $(link_libraries); fi)
endef
# ----------------------------------------------------------

# ----------------------------------------------------------
# get-link-libraries_optimised
#
# If the current module contains a file 
# Module.link_libraries_optimised then echo the 
# contents of this file, otherwise echo the Make 
# variable $(link_libraries).
# ----------------------------------------------------------
define get-link_libraries_optimised
$$(if [[ -e $(srcdir)/$*.link_libraries_optimised ]]; then $(srcdir)/$*.link_libraries_optimised; else if [[ -e $(srcdir)/$*.link_libraries ]]; then $(srcdir)/$*.link_libraries; else echo $(link_libraries); fi; fi)
endef
# ----------------------------------------------------------

export


# ----------------------------------------------------------
# $(programs)
#
# Link together relevant object files to build programs
# for the current module. Including test programs from the
# old test system.
# ----------------------------------------------------------
$(programs) : $(bin_dir)/% : $(lib_dir)/%.o | $(bin_dir)
	$(Link_tool) $(CXX) -o $@ $(Standard_options) $(Warning_options) $(General_options) $< $(alternative_library_path) $(get-link_libraries)
# ----------------------------------------------------------

# ----------------------------------------------------------
# $(programs_optimised)
#
# Link together relevant object files to build optimised programs
# for the current module. Including test programs from the
# old test system.
# ----------------------------------------------------------
$(programs_optimised) : $(bin_dir)/%$(name_addition) : $(lib_dir)/%$(name_addition).o | $(bin_dir)
	$(Link_tool) $(CXX) -o $@ $(Standard_options) $(Warning_options) $(Optimisation_options) $< $(alternative_library_path) $(get-link_libraries_optimised)
# ----------------------------------------------------------

# ----------------------------------------------------------
# test_link_libraries
# ----------------------------------------------------------
test_link_libraries := -liberty
# because of demangling
# ----------------------------------------------------------

# ----------------------------------------------------------
# $(new_test_program)
#
# Link together relevant object files to build the test program
# for the current module.
# ----------------------------------------------------------
$(new_test_program) : $(test-bin_dir)/% : $(test_object_files) $(standard_test_program_object_file) | $(test-bin_dir) $(test-aux_dir)
	$(Link_tool) $(CXX) -o $@ $(Standard_options) $(Warning_options) $(General_options) $^ $(alternative_library_path) $(get-link_libraries) $(test_link_libraries)
# ----------------------------------------------------------

# ----------------------------------------------------------
# $(new_test_program_optimised)
#
# Link together relevant object files to build the optimised 
# test program for the current module.
# ----------------------------------------------------------
$(new_test_program_optimised) : $(test-bin_dir)/%$(name_addition) : $(test_object_files_optimised) $(standard_test_program_object_file_optimised) | $(test-bin_dir) $(test-aux_dir)
	$(Link_tool) $(CXX) -o $@ $(Standard_options) $(Warning_options) $(Optimisation_options) $^ $(alternative_library_path) $(get-link_libraries_optimised) $(test_link_libraries)
# ----------------------------------------------------------

# ######################################################################

# ################################################################
# CLEANING TARGETS
# ################################################################

# ----------------------------------------------------------
# cleantest (old test system)
#
# Removes the test timestamp file for the current module.
# The next 'make check' will re-run the tests from the old
# test system for the current module.
# ----------------------------------------------------------
cleantest :
	- rm $(test_file)
# ----------------------------------------------------------

# ----------------------------------------------------------
# cleantestop (old test system)
#
# Removes the optimised test timestamp file for
# the current module. The next 'make check' will re-run
# the optimised tests from the old test system for the current 
# module.
# ----------------------------------------------------------
cleantestop :
	- rm $(testop_file)
# ----------------------------------------------------------

# ----------------------------------------------------------
# cleanalltest (old test system)
#
# Removes both the test timestamp file and the optimised test
# timestamp file for the current module.
# The next 'make check' will re-run the tests and the
# optimised tests from the old test system for the
# current module.
# ----------------------------------------------------------
cleanalltest : cleantest cleantestop
# ----------------------------------------------------------

# ----------------------------------------------------------
# new_cleantest (new test system)
#
# Removes the test timestamp file for the current module.
# The next 'make new_check' will re-run the tests for the
# current module.
# ----------------------------------------------------------
new_cleantest :
	- rm $(test_timestamp)
# ----------------------------------------------------------

# ----------------------------------------------------------
# new_cleantestop (new test system)
#
# Removes the optimised test timestamp file for the current 
# module. The next 'make new_check' will re-run the optimised 
# tests for the current module.
# ----------------------------------------------------------
new_cleantestop :
	- rm $(testop_timestamp)
# ----------------------------------------------------------

# ----------------------------------------------------------
# new_cleanalltests (new test system)
#
# Removes both the test timestamp file and the optimised 
# test timestamp file for the current module. 
# The next 'make new_check' will re-run both the tests and the 
# optimised tests for the current module.
# ----------------------------------------------------------
new_cleanalltests : new_cleantest new_cleantestop
# ----------------------------------------------------------

# ----------------------------------------------------------
# cleanobj
#
# Removes all object files and optimised object
# files for the current module.
# This includes the object-files from the old test-system
# (but not for the new one).
# ----------------------------------------------------------
cleanobj :
	- rm $(object_files) $(object_files_optimised)
# ----------------------------------------------------------

# ----------------------------------------------------------
# cleantestobj (new test system)
#
# Removes all test object files and optimised test object
# files for the current module.
# ----------------------------------------------------------
cleantestobj :
	- rm $(test_object_files) $(test_object_files_optimised)
# ----------------------------------------------------------

# ----------------------------------------------------------
# cleandep
#
# Removes all dependency files for the current module.
# ----------------------------------------------------------
cleandep :
	- rm $(dependency_files)
# ----------------------------------------------------------

# ----------------------------------------------------------
# clean
#
# Removes all object files (unoptimised and optimised), along
# with all test programs (unoptimised and optimised) and dependency
# files for the current module (for the old and the new test system).
# ----------------------------------------------------------
clean : cleanobj cleantestobj cleandep cleanalltest new_cleanalltests
# ----------------------------------------------------------

# ----------------------------------------------------------
# cleanprograms
#
# Removes all program executables 
# (optimised and unoptimised) for the current module.
# For the old test system, this includes the test-programs, but
# not for new test system.
# ----------------------------------------------------------
cleanprograms :
	- rm $(programs) $(programs_optimised)
# ----------------------------------------------------------

# ----------------------------------------------------------
# cleantestprograms (new test system)
#
# Removes all test program executables 
# (optimised and unoptimised) for the current module.
# ----------------------------------------------------------
cleantestprograms :
	- rm $(new_test_program) $(new_test_program_optimised) 
# ----------------------------------------------------------

# ----------------------------------------------------------
# cleanmessages (new test system)
#
# Removes error, log and message files for the current module.

cleanmessages :
	- rm $(error_file) $(message_file) $(log_file)

# ----------------------------------------------------------
# cleanall
#
# Removes all object files (unoptimised and optimised), along
# with all tests (unoptimised and optimised) and dependencies
# for the current module, and removes all (test and non-test)
# program executables (optimised and unoptimised) for the current module.
# For the new test system, removes error, log and message files 
# for the current module.
# ----------------------------------------------------------
cleanall : clean cleanprograms cleantestprograms cleanmessages
# ----------------------------------------------------------

# ######################################################################
