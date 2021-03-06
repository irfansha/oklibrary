// Oliver Kullmann, 8.11.2007 (Swansea)
/* Copyright 2007, 2009, 2010 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Interfaces/InputOutput/ExtendedToStrictDimacs.cpp
  \brief Application to transfer extended Dimacs format to strict Dimacs format

  <ul>
   <li> Reads from standard input, and writes to standard output (and standard
   error). </li>
   <li> Extended Dimacs format allows identifiers as variable names. </li>
   <li> Currently the old parameter line is just copied (and checked). </li>
   <li> The new variable numbers are gapless, so that the new variable numbers
   are exactly the numbers from 1 to n, where n is true number of (occurring)
   variables. </li>
  </ul>

*/


#include <iostream>

#include <OKlib/Satisfiability/Interfaces/InputOutput/Dimacs.hpp>
#include <OKlib/Satisfiability/Interfaces/InputOutput/ClauseSetAdaptors.hpp>

int main() {
  typedef OKlib::InputOutput::CLSAdaptorDIMACSOutput<> CLSAdaptor;
  CLSAdaptor output(std::cout);
  OKlib::InputOutput::StandardDIMACSInput<CLSAdaptor, OKlib::InputOutput::LiteralReadingExtended>(std::cin, output);
}

