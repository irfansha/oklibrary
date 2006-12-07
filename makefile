SHELL = /bin/sh
.SUFFIXES :

# ##########################################################
# Original definitions of OKplatform and OKBuildsystem, are 
# in Transtional/Buildsystem/generic.mak and cut-and-pasted
# to :
#  Transitional/Buildsystem/ExternalSources.mak
#  Transitional/Buildsystem/makefile
#  Transitional/Buildsystem/OKsystem.mak
#  Transitional/Buildsystem/recursive.mak
#  Transitional/makefile
#  Annotations/makefile
# ##########################################################

ifndef OKplatform
  ifdef OKPLATFORM
    OKplatform := $(OKPLATFORM)
  else
    $(error Either OKplatform (a make-variable) or OKPLATFORM (an environment-variable) must be defined when calling this makefile!)
  endif
endif

ifndef OKBuildsystem
 ifdef OKBUILDSYSTEM
   OKBuildsystem := $(OKBUILDSYSTEM)
 else
   ifdef OKsystem
     OKBuildsystem := $(OKsystem)/Transitional/Buildsystem
   else
     ifdef OKSYSTEM
       OKBuildsystem := $(OKSYSTEM)/Transitional/Buildsystem
     else
       OKBuildsystem := $(OKplatform)/OKsystem/Transitional/Buildsystem
     endif
   endif
 endif
endif

# ##########################################################

define last-element
$(word $(words $1),$1)
endef
srcdir := $(shell cd $(dir $(call last-element, $(MAKEFILE_LIST))); pwd)

export

include $(OKBuildsystem)/recursive.mak

