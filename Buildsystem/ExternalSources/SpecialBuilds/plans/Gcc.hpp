// Oliver Kullmann, 27.6.2007 (Swansea)
/* Copyright 2007, 2008 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Buildsystem/ExternalSources/SpecialBuilds/plans/Gcc.hpp
  \brief Plans regarding installation of gcc


  \todo Install GCC 4.2.3
  <ul>
   <li> First only as an alternative (since yet code doesn't compile with
   versions later than 4.2). </li>
  </ul>
  

  \todo Installation in general
  <ul>
   <li> Documentation:
    <ol>
     <li> Linking to the gcc-documentation (main info-page) should be checked
     for completeness. </li>
     <li> We could offer also to show the man-page (just open it into a browser);
     however then it should be said that likely the html-documentation is more complete. </li>
     <li> We should also move the info-pages to the doc-directory. How to view them?
     The least is just to open them into a browser. </li>
    </ol>
   </li>
   <li> Instead of, %e.g., "make gcc-4.1.2", wouldn't it be more consistent with
   building Boost to also have "make gcc gcc-version=4.1.2" ? </li>
   <li> If variable "gcc-version" is set, then it should have one of the
   allowed values (while otherwise we get an error). </li>
   <li> We must understand, how gcc interacts with 32- and 64-bit
   environments, and how to take control of this. </li>
   <li> There should be make-variables, which allow control over
   some settings for the build of gcc. </li>
   <li> texti2pdf is a script, which can be put into ~/bin for example,
   and is needed for building the gcc-documentation --- how to provide it?
   Such small utilities could be put under version control (OKlibrary) ? </li>
   <li> Installation of R requires a Fortran compiler. Therefore the 
    system-installation of Gcc should allow for enabling of Fortran
    language support. </li>
   <li> Enabling Fortran language support in Gcc requires that the MPFR
    and GMP libraries are installed. Should we install these also locally?
    <ol>
     <li> GMP is also of interest to us regarding big-number-types, so we need full
     control about it, and perhaps a local installation is warranted (ignoring the
     system installation). UPDATE NEEDED </li>
    </ol>
   </li>
   <li> Shouldn't file external_sources_versions.mak be placed in
   subdirectory Buildsystem/ExternalSources ? DONE (placed in Buildsystem/Configuration) </li>
   <li> If the filestamp does already exist, then we want nothing to happen ---
   however yet the build-directory will be rebuilt if not existent, since
   it is a prerequisite of the rule for the "tag-paths". So it seems
   necessary to remove the build-directory from the prerequisite-list,
   however then it seems impossible to create the build-directory, if actually
   gcc *is* to be build, via the target-mechanism. DONE (it seems reasonable
   to remove the build-directory from the prerequisite-list and to build it
   "manually") </li>
  </ul>

*/
