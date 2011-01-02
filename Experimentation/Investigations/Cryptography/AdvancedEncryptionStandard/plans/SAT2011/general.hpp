// Oliver Kullmann, 1.1.2011 (Swansea)
/* Copyright 2011 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Investigations/Cryptography/AdvancedEncryptionStandard/plans/SAT2011/general.hpp
  \brief Investigations into AES related to the SAT 2011 paper


  \todo Create submodule "Representations"
  <ul>
   <li> All files "Box*", "Field*", "Sbox*" shall go there. </li>
   <li> Of course, with general plans there in "general.hpp". </li>
   <li> The general structure of the investigations (from arbitrary boolean
   functions to permutations and linear maps) needs to be expressed. </li>
  </ul>


  \todo Connection with the plans one level above
  <ul>
   <li> A full integration of plans SAT2011 with those one level above needs
   to be achieved. </li>
  </ul>


  \todo Prepare benchmarks for SAT 2011
  <ul>
   <li> See "Benchmarks for SAT 2011" in
   Experimentation/Investigations/plans/SATCompetition.hpp. </li>
   <li> Other than the standard AES and small scale translations, the 
   minimisation problems for the AES boxes (Sbox and field multiplications) 
   should yield good benchmarks for weighted MaxSAT solvers. </li>
  </ul>


  \todo Explain how to replace various AES boxes with identity or random
  boxes
  <ul>
   <li> As part of our investigations, we wish to make various parts of
   the AES sbox the identity, and then introduce the various boxes (Sbox,
   field multiplications etc), to determine which combinations of boxes
   "make AES difficult". </li>
   <li> To do this, we need to be able to generate AES translations which
   "make sense" (i.e. are permutations, given the key). </li>
   <li> These translations are possible with the current translation system
   without writing additional rewrite functions, however instructions
   and/or additional helper functions are necessary to make sure things
   easy to experiment with. </li>
  </ul>


  \todo Combining linear components
  <ul>
   <li> A full description of all of the possibilities for recombining
   AES and small scale linear components (from the Sbox and MixColumns)
   needs to be provided. </li>
   <li> The idea here is that, due to the linearity of the Sbox's affine
   transformation, and the MixColumns operations, as well as the
   fact the Shiftrows simply permutes bytes, the linear aspects of the Sbox
   can be moved out, and seperated (in the case of the affine addition),
   or merged into the boxes for the MixColumn. </li>
   <li> For the Sbox, we have 3 possibilities:
    <ul>
     <li> Full Sbox (M . s^(-1) + A) . </li>
     <li> Sbox minus addition of the affine constant (M . s^(-1)). </li>
     <li> Sbox minus affine transform entirely (s^(-1)). </li>
    </ul>
   </li>
   <li> For the MixColumn multiplications, we have 2 possibilities:
   <ul>
    <li> Standard byte-field multiplications. </li>
    <li> Sbox linear component (M) and Standard byte-field multiplications
    together. </li>
   </ul>
   </li>
   <li> A description of how to generate such translation is needed. </li>
   <li> See also "Rearranging linear components of Sbox and MixColumns" in
   ComputerAlgebra/Cryptology/Lisp/Cryptanalysis/Rijndael/plans/Translations.hpp. 
   </li>
  </ul>


  \todo Investigating conditions and their representations
  <ul>
   <li> A first central research question is how to choose appropriate
   representations of the conditions which altogether specify AES. </li>
   <li> More specifically, clause-sets representing the S-box and the
   various multiplications (with constants) are to be investigated upon
   their influence on SAT solving. </li>
   <li> See ComputerAlgebra/Satisfiability/Lisp/Preprocessing/plans/general.hpp
   for the general perspective, where one starts from a CNF and derives
   DNFs from it by partitioning, while we have already given the DNFs (but
   not some original CNF). </li>
   <li> Studying the representations of the Sbox
    <ol>
     <li> See
     ComputerAlgebra/Cryptology/Lisp/Cryptanalysis/Rijndael/plans/SboxAnalysis.hpp.
     </li>
     <li> That module is not properly maintained: Actions for MG. </li>
     <li> See "r-based representations" in 
     Experimentation/Investigations/BooleanFunctions/plans/ReductionBasedRepresentations.hpp.
     </li>
     <li> A 0-based CNF-representation without additional variables is likely
     infeasible to use. </li>
     <li> Via dualts_fcl in
     ComputerAlgebra/Satisfiability/Lisp/FiniteFunctions/TseitinTranslation.mac
     we obtain a (totally) properly r_1-based representation of every box
     (see "Understanding dualts_fcl" in
     Lisp/FiniteFunctions/plans/TseitinTranslation.hpp). </li>
     <li> It seems most promising (for now) to consider here r=r_1 and r=r_2,
     applied to the sets of prime implicates of the various "boxes" involved.
     </li>
     <li> Perhaps actually the hitting-CNFs representing the Sbox might have
     values, since we have special algorithms. So other reductions than just
     the r_k-reductions are useful to consider in general. </li>
    </ol>
   </li>
  </ul>


  \todo Summary of previous experimental results
  <ul>
   <li> Before various improvements were made to the AES translation,
   experiments were run for 1-4 rounds translations of the AES
   and on the various boxes. </li>
   <li> A basic summary (even if not reproducible due to the new state of the
   system), should be made available here. </li>
  </ul>


  \todo DONE More experiments
  <ul>
   <li> DONE What is the meaning of
   "Experiments on AES with the first 32 key bits not set" ? And what does
   the "summary" show? Apparently only trivial results, which are likely of
   no interest. 
   <ul>
    <li> This was regarding initial investigations where all plaintext and 
    ciphertext variables were set to relevant values and the last 96 key 
    variables were set. </li>
    <li> 32 bits were chosen as the AES translation to CNF, using the small CNF
    representations, presented a challenge to solvers for even very small 
    numbers of key bits left "unknown"/"unset" in the SAT problem. </li>
    <li> The experiments were over rounds 2,4,6,8, and 10. </li>
    <li> Experimental data and results has now been moved. See "Experiments". 
    </li>
   </ul>
   </li>
   <li> DONE For the trivial instances (message and key set) more solvers need
   to be considered. In its own file. </li>
   <li> DONE Also ciphertext and key set are to be investigated. </li>
   <li> (MOVED to Experiments) 
   Important is that we systematically study variations of AES:
    <ol>
     <li> the different sizes as belonging to Rijndael </li>
     <li> small-scale variations </li>
     <li> replacing the Sbox by other permutations (random ones, or
     very simple ones) </li>
     <li> replacing the multiplications with certain constants by other
     permutations </li>
     <li> replacing the row- and column-permutations by other permutations.
     </li>
    </ol>
   </li>
   <li> DONE Plan for more experiments! </li>
  </ul>


  \todo DONE Cleanup of todos in this file
  <ul>
   <li> "Solvers to be used for experimentation" needs update. </li>
   <li> DONE (Removed, summarising previous results is already (better)
   handled by "Summary of previous experimental results")
   "More experiments" shall be removed (possible after entering it
   into the summary). </li>
   <li> DONE (moved into Experimentation.hpp and moved some description
   to todos on documenting the translation)
   "Prepare experiments for the SAT 2011 paper", "Open problems" and
   "Experiments" all belong together. </li>
   <li> DONE Likely this should go all into a new file "Experimentation.hpp".
   </li>
  </ul>

*/
