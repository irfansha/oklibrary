// Oliver Kullmann, 9.6.2019 (Swansea)
/* Copyright 2019 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/* Random dependency-quantified CNF

DESIGN:

The three models:

1. No clause contains universal variables not in the dependency of some
   existential variable in the clause. Clauses do not contain clashes,
   and no literal is repeated.
2. Given the constraints, all possible clauses are considered equally likely,
   based on the variables. The number c of clauses is given.
3. Signs are distributed with probability 1/2.
4. Known models to be supported CI (Chen-Interian), CCI (controlled-CI).
   In general the numbers of variables are na (universal), ne (existential).
   For CI one specifies a tuple, the length of each quantifier-block.
5. CI additionally also with just only one or two parameters on clause-length:
    - k: total length of clause
    - (ka,ke): number of universal/existential literals.
   Otherwise for each quantifier-block b a length k_b.
   Innermost q-block always existential (always at least one block).
6. Several clause-blocks possible in CI, always with c-parameter (number of
   clauses in this clause-block):
    - As with clause-sets.
    - There we allow a sign-probability per block (default 1/2), which we can
      also do here.
    - For clause-sets we allow each block to have its own variables; here we
      need to use the given dependencies, and thus using arbitrary universal/
      existential variables for each block seems impossible.
    - However via the k-values for each block of variables, for different
      clause-blocks one can use different variable-blocks.
7. CCI just all-exists, and ke (number of existential literals), while ka=1
   and c = 2*na, each clause contain exactly one universal literal, so that
   every universal literal occurs exactly once.
   GCI has one more parameter ka, and now the universal part of the clauses
   runs through all possible clauses of length ka over the universal variables.
   SGCI has a parameter m, which means that only m of the binomial(na,ka)*2^ka
   many clauses are chosen, and na is chosen as the minimal value so that
   m choices are possible.
8. The dependency specification of CI allows to add/subtract dependencies for
   the existential variables: adding with later univerals, subtracting with
   earlier universals. Writing this +d/-d.
9. CCI and variations also allow that, subtracting dependencies for the
   single existential block.
10. The DQCNF-model has one additional parameter K, for the number of
    randomly chosen dependencies. One could see that as addition of
    dependencies, as above, when starting with no dependencies.
    Or this could be covered by all-exists, now removing dependencies.
11. The following generalisation seems interesting (generalising also CI),
    and likely should be implemented:

    Consider M >= 1 blocks of variables, alternating between a and e, innermost
    always e, numbered from 1 to M, from left to right.
    Now a dependency-specification-triple is (i,j,K), where i is an e-index,
    j an a-index or "<i" (all left) or ">i" (all right), and where K >= 0
    means the number of dependencies between these blocks, while in case of
    j < i also K < 0 is allowed, which means the positive K' is K' = total
    number of dependencies + K, and where especially "-0" means to take
    all dependencies (using the a-blocks are marked by j).

    Perhaps for j one can code "<i" with j=0, while ">i" can be coded by
    j=M+1.

    Perhaps here always "+" or "-" is required, with "+" meaning the total
    number of dependencies, while with "-" missing dependencies are stated.
    Or perhaps not requiring this, but always interpreting "0" as "-0" in that
    sense (note that 0 is never needed, since one can just leave out the
    triple, and that means no dependencies). But that wouldn't look nice?
    "(i,0,0)" would mean normal quantifier-block rules, using all dependencies.
    So well, why not. Here for all existential position i such a triple
    would be needed, if one wanted QCNF. Perhaps a single triple "(0,0,0)"
    would signal that?
11. Clause-lengths then just k resp. (ka,ke) resp. by q-blocks as in CI.
12. Each clause-block, which for clause-sets is characterised by
    (n,k,c,p), now is (k,c,p), where k is just the total clause-length,
    or the (ka,ke) pair, or the choice per q-block, which has the same meaning
    as the (ka,ke) pair in case of just two q-blocks.
13. It is natural to allow non-alternating variable-blocks; so the only
    conditions on the variable-blocks are that they have non-zero length,
    and the last block (index M) is existential.
     - For the clause-blocks one just refers to variable-blocks by index, and
       thus we allow arbitrary sets of pairs [v-block-index, natural number
       >= 1] to describe the partitioned clause-length.
     - Internally the indices are translated into variable-intervals, as in
       RandGen::VarInterval.
14. Variable-numbering consecutively, starting with the first (outer) q-block.
15. File-suffixes ".dimacs", ".qdimacs", or ".dqdimacs".
16. Should we really allow for ordinary CNF, and thus having *two* generators?
    Perhaps better not; or perhaps in the case of ordinary CNF we just get
    the exact behaviour as in ClauseSets.hpp?!
     - It is natural to allow just one variable-block, which necessarily then
       is existential, and this is a CNF. So we allow CNF generation.
     - The type-seed is different, and thus the formulas generated here are
       independent of the pure CNF-generator.
     - Via having differennt e-blocks one has a different (in principle
       equivalent) handling of the variable-intervals (as in ClauseSets.hpp).


Seed handling: basically as for clause-sets.

*/

#ifndef DQCNF_Z7vpC0rD5U
#define DQCNF_Z7vpC0rD5U

#include "Distributions.hpp"
#include "ClauseSets.hpp"

namespace RandGen {

}

#endif