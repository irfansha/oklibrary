// Matthew Gwynne, 12.3.2011 (Swansea)
/* Copyright 2011 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Interfaces/InputOutput/MinOnes2WeightedMaxSAT.cpp
  \brief Application to translate a CNF into a weighted MaxSAT encoding of the "minimum ones" problem for that CNF.

  <ul>
   <li> Reads from standard input, and writes to standard output (and standard
   error). </li>
   <li> Weighted partial MaxSAT CNF Dimacs files are Dimacs files where each
   clause is prefixed with an integer weight. The solver must find an
   assignment which maximises the sum of the weights of the satisfied clauses.
   See http://maxsat.ia.udl.cat/requirements/. </li>
   <li> The old parameter line is updated from:
   \verbatim
p cnf n c
   \endverbatim
   to
   \verbatim
p wcnf n c+n
   \endverbatim
   </li>
   <li> All clauses in the input are output directly, prefixed with the
   integer n+1 (as the weight of that clause). </li>
   <li> After all clauses have been read from the input, a unit-clause
   containing the negated literal for each variable from 1 to n is output,
   prefixed with weight 1. </li>
  </ul>

  \todo Improve specification
  <ul>
   <li> A full specification of what the "minimum ones" problem is,
   should be given. </li>
   <li> A full specification of the optimum solutions to the output
   weighted MaxSAT formula should be given. </li>
   <li> A specification of the weighted MaxSAT file format should be
   given. </li>
  </ul>

  \todo Move to correct place
  <ul>
   <li> Satisfiability/Interfaces/InputOutput/ is likely not
   the right place for this application. </li>
  </ul>

*/

#include <string>
#include <iostream>
#include <cstdlib>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

#include <OKlib/Satisfiability/Interfaces/InputOutput/Dimacs.hpp>
#include <OKlib/Satisfiability/Interfaces/InputOutput/ClauseSetAdaptors.hpp>


namespace {

  const std::string program = "MinOnes2WeightedMaxSAT";
  const std::string err = "ERROR[" + program + "]: ";

  const std::string version = "0.0.11";

  /*!
    \class CLSAdaptorMinOnes2WeightedMaxSATOutput
    \brief Adaptor for translating a CNF into a weighted MaxSAT encoding of the "minimum ones" problem for that CNF.

    The role of the template parameters are as follows:
    <ol>
     <li> Int is the integral type for the Dimacs literals. </li>
     <li> String is the string type for comments. </li>
     <li> AdaptorStatistics is a CLSAdaptor which handles statistics. </li>
    </ol>

  */

  template <typename Int = int, class String = std::string, class AdaptorStatistics = OKlib::InputOutput::CLSAdaptorStatistics<Int, String> >
  class CLSAdaptorMinOnes2WeightedMaxSATOutput {
    typedef AdaptorStatistics adaptor_statistics_type;
    std::ostream& out;
    adaptor_statistics_type adaptor_statistics;

  public :
    typedef Int int_type;
    typedef String string_type;
    typedef typename adaptor_statistics_type::statistics_type statistics_type;

    CLSAdaptorMinOnes2WeightedMaxSATOutput(std::ostream& out) : out(out) {
      if (not out)
        throw OKlib::InputOutput::OStreamError("OKlib::InputOutput::CLSAdaptorMinOnes2WeightedMaxSATOutput::CLSAdaptorMinOnes2WeightedMaxSATOutput(std::ostream&):\n  cannot open the output stream");
    }

    void comment(const string_type& s) {
      adaptor_statistics.comment(s);
      if (s.empty()) out << "c";
      else
        if (boost::algorithm::is_space()(s[0])) out << "c" << s;
        else out << "c " << s;
      out << "\n";
    }
    void n(const int_type pn) {
      adaptor_statistics.n(pn);
      if (pn < 0)
        throw OKlib::InputOutput::ParameterOutputError("OKlib::InputOutput::CLSAdaptorMinOnes2WeightedMaxSATOutput::n:\n  maximal variable index is a negative quantity = " + boost::lexical_cast<std::string>(pn));
    }
    void c(const int_type pc) {
      adaptor_statistics.c(pc);
      if (pc < 0)
        throw OKlib::InputOutput::ParameterOutputError("OKlib::InputOutput::CLSAdaptorMinOnes2WeightedMaxSATOutput::n:\n  number of clauses is a negative quantity = " + boost::lexical_cast<std::string>(pc));
      out << "p wcnf " << adaptor_statistics.stat.pn() << " " << adaptor_statistics.stat.pc() + adaptor_statistics.stat.pn() << "\n";
    }
    void finish() {
      const int_type n = adaptor_statistics.stat.pn();
      for (int_type i = 1; i <= n; ++i) out << "1 " << -i << " 0\n";
      adaptor_statistics.finish();
    }
    void tautological_clause(const int_type t) {
      adaptor_statistics.tautological_clause(t);
    }
    template <class ForwardRange>
    void clause(const ForwardRange& r, const int_type t) {
      adaptor_statistics.clause(r, t);
      out << adaptor_statistics.stat.pn() + 1 << " ";
      if (adaptor_statistics.stat.c() > adaptor_statistics.stat.pc())
        throw OKlib::InputOutput::ClauseOutputError("OKlib::InputOutput::CLSAdaptorMinOnes2WeightedMaxSATOutput::clause:\n  number of non-tautological clauses exceeds specified total number of clauses = " + boost::lexical_cast<std::string>(adaptor_statistics.stat.pc()));
      typedef typename boost::range_const_iterator<ForwardRange>::type const_iterator;
      const const_iterator& end(boost::end(r));
      for (const_iterator i = boost::begin(r); i != end; ++i) {
        typedef typename boost::range_value<ForwardRange>::type value_type;
        const value_type& literal = *i;
        if (std::abs(literal) > adaptor_statistics.stat.pn())
          throw OKlib::InputOutput::ClauseOutputError("OKlib::InputOutput::CLSAdaptorMinOnes2WeightedMaxSATOutput::clause:\n  variable index of literal = " + boost::lexical_cast<std::string>(literal) + " exceeds specified maximal index = " + boost::lexical_cast<std::string>(adaptor_statistics.stat.pn()));
        out << literal << " ";
      }
      out << 0 << "\n";
    }

  };

}

int main() {
  typedef CLSAdaptorMinOnes2WeightedMaxSATOutput<> CLSAdaptor;
  CLSAdaptor output(std::cout);
  OKlib::InputOutput::StandardDIMACSInput<CLSAdaptor >(std::cin, output);
}

