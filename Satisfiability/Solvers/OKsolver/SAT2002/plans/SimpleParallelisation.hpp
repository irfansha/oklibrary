// Oliver Kullmann, 21.4.2011 (Swansea)
/* Copyright 2011 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Solvers/OKsolver/SAT2002/plans/SimpleParallelisation.hpp
  \brief Plans on extending OKsolver-2002 for using it to compute a splitting of a large problem into subproblems


  \todo The basic idea
  </ul>
   <li> Needs to be transferred to the docus. </li>
   <li> As a simple means to achieve parallelisation, for a given depth
   the clause-sets at that level should be output (to files, with
   suitable names indicating the decisions leading to that clause-set). </li>
   <li> DONE (this is not the right way, since monitoring happens after a
   branch was completed, while here we act before branching)
   This should simply employ the monitoring-mode, outputting the (reduced)
   clause-sets at the monitoring nodes, while not going into the branches, but
   immediately backtracking (stipulating result "unsat", using all variables,
   but at the end outputting "unknown" if no solution was found and at least
   one open node was created). </li>
   <li> Then a simple script would allocate these problem-instances to
   the available machines, monitor their execution, record the results,
   and schedule new jobs if possible (and needed). </li>
   <li> For monitoring-depth 0 one would get the OKsolver_2002 to act
   as preprocessor (applying r_2-reduction and autarky-reduction). </li>
  </ul>


  \todo Wrapper script
  <ul>
   <li> Transfers the parameters to the call of OKsolver_2002_NTP-O3-DNDEBUG,
   except that before the final parameter (the file-name) the option
   "-S=dir-name" is inserted. </li>
   <li> So we should provide a public link to this version of the OKsolver.
   </li>
   <li> The directory dir-name contains the splitting instances; "dir-name"
   is formed according to our usual standards for naming
   experiment-directories. </li>
   <li> A file "dir-name/Parameters" is to be created:
    <ol>
     <li> Containing the parameter-line. </li>
     <li> And the output of running the used form of the OKsolver-2002 with
     option "--version". </li>
     <li> And also the statistics output shall go there. </li>
     <li> Or perhaps we should have different files for these different types
     of information? </li>
     <li> Perhaps, via R, also some statistics on the lengths of the partial
     assignments should be computed and stored. </li>
    </ol>
   </li>
  </ul>


  \todo Script for applying partial assignments
  <ul>
   <li> The script ApplyPASS_UCP takes one argument, the file with the partial
   assignment. </li>
   <li> It reads from standard input the CNF F (DIMACS). </li>
   <li> Internally, it then adds the assignments as unit-clauses, and performs
   unit-clause propgatation. </li>
   <li> The result (in DIMACS format) is output to standard output. </li>
   <li> Actually, the partiall assignments computed by the OKsolver-2002
   already contain all derived unit-clause-eliminations, and thus better a
   script ApplyPASS is provided, which just applies the partial assignment.
   </li>
  </ul>


  \todo Computing a splitting tree
  <ul>
   <li> In order to see what really needs to be done, for a given depth
   one actually wants also the list of indices of nodes which still need to be
   processed; if a satisfying assignment was found then the whole process
   can stop (likely we don't do counting in this framework). </li>
   <li> So this task is to compute a complete splitting tree according to
   ExperimentSystem/plans/DistributedSolving.hpp.
    <ol>
     <li> Here one could detect that branches don't need to be processed due
     to resolution tree pruning or autarky reduction. </li>
     <li> This could be achieved by forced backtracking when the given depth D
     is reached, assuming for the intelligent backtracking that all variables
     (respectively available) are used. Here then there are no "missed single
     nodes", but tree resolution pruning is always to be performed. </li>
    </ol>
   </li>
  </ul>

*/
