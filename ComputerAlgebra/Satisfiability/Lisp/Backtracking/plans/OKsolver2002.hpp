// Oliver Kullmann, 19.1.2008 (Swansea)
/* Copyright 2008 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ComputerAlgebra/Satisfiability/Lisp/Backtracking/plans/OKsolver2002.hpp
  \brief Plans for the Maxima/Lisp specification of the original OKsolver


  \todo Differences to the original OKsolver2002
  <ul>
   <li> On weak_php(5,4) the C-OKsolver needs 17 nodes and depth 6,
   while the Maxima-OKsolver needs 15 nodes and depth 5. </li>
   <li> The Maxima-tree is (labelled):
   \verbatim
okt_php_54 : OKsolver_2002_st(weak_php(5,4));
[- php(1, 1), [- php(2, 2), [false], [false]],
 [- php(1, 2), [- php(2, 1), [false], [false]],
  [- php(2, 3), [false], 
   [- php(2, 4), [false],
    [- php(3, 1), [false], [false]]
   ]
  ]
 ]
];
   \endverbatim
   This tree seems correct.
   </li>
   <li> It seems that at the deep right end the C-OKsolver added
   a further branching. </li>
   <li> Could be chance (due to the quasi-single-nodes). </li>
   <li> But we must check; we need the C-OKsolver to output the
   branching literals. See "OUTPUTTREEDATAXML" in
   Solvers/OKsolver/SAT2002/plans/general.hpp. </li>
   <li> And we need to develop methods for analysing trees like
   the above; adorning it with further data like
    <ol>
     <li> the number of 2-reductions (obtained by amending
     the tree as r_2-splitting tree and adding the sizes of partial
     assignments). </li>
     <li> the number of quasi-single-nodes  </li>
    </ol>
    etc. </li>
   <li> For weak_php(6,5) the problem gets further pronounced:
   Here we have 79 nodes versus 89 nodes, and a depth of 9 versus 10. </li>
   <li> So there seems to be a systematic problem. </li>
  </ul>

  \todo Tree pruning
  <ul>
   <li> We need to get the variables used in a refutation. </li>
   <li> Then tree-pruning follows straight. </li>
  </ul>


  \todo Counting satisfiable assignments
  <ul>
   <li> At this level it should be easy to add counting of satisfying
   assignments. </li>
  </ul>

*/
