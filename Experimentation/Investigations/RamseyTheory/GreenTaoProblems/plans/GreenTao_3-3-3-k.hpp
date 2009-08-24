// Oliver Kullmann, 26.4.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/GreenTaoProblems/plans/GreenTao_3-3-3-k.hpp
  \brief On investigations into Green-Tao numbers greentao_3(3,3,k)

  SAT problems generated by output_greentao_stdname([3,3,k],n) and
  output_greentao_sb_stdname([3,3,k],n).


  \todo greentao_3(3,3,4) >= 434
  <ul>
   <li> Created by output_greentao_stdname([3,3,4],n) and
   output_greentao_sb_stdname([3,3,4],n). </li>
   <li> n=150 trivially satisfiable by adaptnovelty+. </li>
   <li> n=200 trivially satisfiable by adaptnovelty+. </li>
   <li> n=300 trivially satisfiable by adaptnovelty+. </li>
   <li> n=400 easily satisfiable by adaptnovelty+ (cutoff=100*10^3). </li>
   <li> n=412 found satisfiable by adaptnovelty+ with cutoff=10*10^6
   (e.g., seed=573073979). </li>
   <li> n=419 found satisfiable by adaptnovelty+ with cutoff=10*10^6
   (seed=1429074341). </li>
   <li> n=425 found satisfiable by adaptnovelty+ with cutoff=10*10^6 (40 runs
   needed; seed=610774669). </li>
   <li> n=428: cutoff=50*10^6 found a solution after 17 runs (seed=621103542).
   </li>
   <li> n=429: cutoff=50*10^6 yields 13 solutions in 358 runs (e.g.,
   seed=2019144865). </li>
   <li> n=430: cutoff=50*10^6 yields 1 solution in 276 runs (seed=3076580871).
   </li>
   <li> n=431: cutoff=200*10^6 yields in 4 runs constantly min=1, and so
   does cutoff=50*10^6 in 10 runs, but using 730 runs (cutoff=50*10^6)
   one solution was found (seed=731527187). </li>
   <li> n=432: found satisfiable by adaptnovelty+ with cutoff=50*10^6
   (seed=769951307, osteps=40681058); 1 solution in 1000 runs:
   \verbatim
Clauses = 20506
Variables = 1296
TotalLiterals = 61906
FlipsPerSecond = 753471
BestStep_Mean = 15526608.088000
Steps_Mean = 49990681.058000
Steps_Max = 50000000.000000
PercentSuccess = 0.10
BestSolution_Mean = 1.320000
BestSolution_Median = 1.000000
BestSolution_Min = 0.000000
BestSolution_Max = 2.000000
   \endverbatim
   </li>
   <li> n=433: cutoff=60*10^6 found in 175 runs one solution
   (seed=3663211116). </li>
   <li> n=434:
    <ol>
     <li> cutoff=60*10^6:
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 1000 -cutoff 60000000 -i GreenTao_3-3-3-4_434.cnf
Clauses = 20673
Variables = 1302
TotalLiterals = 62410
FlipsPerSecond = 754097
BestStep_Mean = 15831901.495000
Steps_Mean = 60000000.000000
Steps_Max = 60000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.467000
BestSolution_Median = 1.000000
BestSolution_Min = 1.000000
BestSolution_Max = 2.000000
     \endverbatim
     </li>
     <li> cutoff=200*10^6:
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 1000 -cutoff 200000000 -i GreenTao/GreenTao_3-3-3-4_434.cnf
Clauses = 20673
Variables = 1302
TotalLiterals = 62410
FlipsPerSecond = 758972
BestStep_Mean = 58144942.258000
Steps_Mean = 200000000.000000
Steps_Max = 200000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.070000
BestSolution_Median = 1.000000
BestSolution_Min = 1.000000
BestSolution_Max = 2.000000
     \endverbatim
     </li>
     <li> Let's finally consider a higher number of runs, 20000, but with just
     cutoff=50*10^6:
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 20000 -cutoff 50000000 -i GreenTao/GreenTao_3-3-3-4_434.cnf -solve | tee GreenTao_3-3-3-4.out
> E2 = read_ubcsat("GreenTao_3-3-3-4.out")
    1     2
 9253 10747
20000
     \endverbatim
     So let's consider this case as "unsatisfiable".
     </li>
     <li> OKsolver_2002
      <ol>
       <li> Without preprocessing and without symmetry-breaking:
       \verbatim
> OKsolver_2002-O3-DNDEBUG -M -D30 -F GreenTao_3-3-3-4_434.cnf
s UNKNOWN
c sat_status                            2
c initial_maximal_clause_length         4
c initial_number_of_variables           1302
c initial_number_of_clauses             20673
c initial_number_of_literal_occurrences 62410
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   1302
c running_time(sec)                     6689.7
c number_of_nodes                       478637
c number_of_single_nodes                0
c number_of_quasi_single_nodes          0
c number_of_2-reductions                5829494
c number_of_pure_literals               0
c number_of_autarkies                   4810
c number_of_missed_single_nodes         19
c max_tree_depth                        113
c number_of_table_enlargements          0
c number_of_1-autarkies                 210768130
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             GreenTao_3-3-3-4_434.cnf
       \endverbatim
       average 2-reductions ~ 12.2, where 1302/12.2 ~ 107, while speed
       is 72 nodes per second.
       </li>
       <li> With preprocessing and without symmetry-breaking:
       \verbatim
> OKsolver_2002-m2pp -M -D30 -F GreenTao_3-3-3-4_434.cnf
s UNKNOWN
c sat_status                            2
c initial_maximal_clause_length         8
c initial_number_of_variables           864
c initial_number_of_clauses             19175
c initial_number_of_literal_occurrences 65558
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   432
c running_time(sec)                     87501.4
c number_of_nodes                       7410032
c number_of_single_nodes                8
c number_of_quasi_single_nodes          0
c number_of_2-reductions                89745142
c number_of_pure_literals               10442
c number_of_autarkies                   0
c number_of_missed_single_nodes         309
c max_tree_depth                        80
c number_of_table_enlargements          0
c number_of_1-autarkies                 1045400
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             GreenTao_3-3-3-4_434.cnf_m2pp_19403
       \endverbatim
       (without reaching a monitoring node); 2red/nds ~ 12.11, where
       864 / 12.11 ~ 71, 84.7 nds/sec. This looks like an improvement. </li>
       <li> Without preprocessing and with symmetry-breaking:
       \verbatim
> OKsolver_2002-O3-DNDEBUG -M -D30 -F GreenTao_sb_3-3-3-4_434.cnf
s UNKNOWN
c sat_status                            2
c initial_maximal_clause_length         4
c initial_number_of_variables           1302
c initial_number_of_clauses             20674
c initial_number_of_literal_occurrences 62412
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   1303
c running_time(sec)                     146231.2
c number_of_nodes                       12297953
c number_of_single_nodes                0
c number_of_quasi_single_nodes          0
c number_of_2-reductions                151996719
c number_of_pure_literals               0
c number_of_autarkies                   116929
c number_of_missed_single_nodes         445
c max_tree_depth                        120
c number_of_table_enlargements          0
c number_of_1-autarkies                 5390584354
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             GreenTao_sb_3-3-3-4_434.cnf
       \endverbatim
       (without reaching a monitoring node); 2red/nds ~ 12.36, where
       1302 / 12.36 ~ 105, 84.1 nds/sec. Looks worth than with preprocesssing,
       while slightly better than without anything. </li>
       <li> With preprocessing and with symmetry-breaking:
       \verbatim

       \endverbatim
       </li>
      </ol>
     </li>
     <li> minisat2 </li>
    </ol>
   </li>
   <li> n=437
    <ol>
     <li> cutoff=10*10^6 with 65 runs only achieved 5 times min=1. </li>
     <li> cutoff=100*10^6 with 10 runs achieved 6 times min=1 and 4 times
     min=2. More runs:
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 100 -cutoff 100000000 -i GreenTao_3-3-3-4_437.cnf
Clauses = 20918
Variables = 1311
TotalLiterals = 63157
FlipsPerSecond = 748371
BestStep_Mean = 29088565.360000
Steps_Mean = 100000000.000000
Steps_Max = 100000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.330000
BestSolution_Median = 1.000000
BestSolution_Min = 1.000000
BestSolution_Max = 2.000000
     \endverbatim
     </li>
     <li> cutoff=10^9 doesn't seem effective:
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 10 -cutoff 1000000000 -i GreenTao_3-3-3-4_437.cnf
Clauses = 20918
Variables = 1311
TotalLiterals = 63157
FlipsPerSecond = 724933
BestStep_Mean = 91967835.900000
Steps_Mean = 1000000000.000000
Steps_Max = 1000000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.000000
BestSolution_Median = 1.000000
BestSolution_Min = 1.000000
BestSolution_Max = 1.000000
     \endverbatim
     where the maximum of osteps is 170234040. </li>
     <li> So if this n is to be considered further, then with 1000 runs and
     a cutoff of 200*10^6: Aborted after 440 runs, with most of them yielding
     min=1 and some min=2. </li>
    </ol>
   </li>
   <li> n=450
    <ol>
     <li>
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 10 -cutoff 10000000 -i GreenTao_3-3-3-4_450.cnf
Clauses = 22012
Variables = 1350
TotalLiterals = 66488
FlipsPerSecond = 799233
BestStep_Mean = 4388254.200000
Steps_Mean = 10000000.000000
Steps_Max = 10000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 3.300000
BestSolution_Median = 3.000000
BestSolution_Min = 3.000000
BestSolution_Max = 4.000000
> ubcsat-okl -alg adaptnovelty+ -runs 10 -cutoff 100000000 -i GreenTao_3-3-3-4_450.cnf
Clauses = 22012
Variables = 1350
TotalLiterals = 66488
FlipsPerSecond = 761899
BestStep_Mean = 23395422.200000
Steps_Mean = 100000000.000000
Steps_Max = 100000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 2.100000
BestSolution_Median = 2.000000
BestSolution_Min = 2.000000
BestSolution_Max = 3.000000
> ubcsat-okl -alg adaptnovelty+ -runs 10 -cutoff 1000000000 -i GreenTao_3-3-3-4_450.cnf
Clauses = 22012
Variables = 1350
TotalLiterals = 66488
FlipsPerSecond = 718685
BestStep_Mean = 436206673.400000
Steps_Mean = 1000000000.000000
Steps_Max = 1000000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 1.500000
BestSolution_Median = 1.500000
BestSolution_Min = 1.000000
BestSolution_Max = 2.000000
     \endverbatim
     </li>
     <li> This needs to be investigated further, but first we look at smaller
     n. </li>
     <li> Since osteps for cutoff=10^9 comes close to the cutoff value, let's
     try 10 runs with cutoff=4*10^9. </li>
    </ol>
   </li>
   <li> n=500 looks unsatisfiable: cutoff=100*10^3 and 10 runs yields a
   minimum=14, cutoff=10^6 yields minimum=8, cutoff=10*10^6 yields
   minimum=7. </li>
  </ul>


  \todo greentao_3(3,3,5) > 1925
  <ul>
   <li> n=1000 easy for adaptnovelty+ with cutoff=100000. </li>
   <li> n=1200 easy for adaptnovelty+ with cutoff=100000. </li>
   <li> n=1400 easy for adaptnovelty+ with cutoff=10^6. </li>
   <li> n=1600 easy for adaptnovelty+ with cutoff=10^6. </li>
   <li> n=1800
    <ul>
     <li> cutoff=10^6 yields in 10 runs min=3. </li>
     <li> cutoff=5*10^6 found in 10 runs one solution (seed=992240675). </li>
    </ul>
   </li>
   <li> n=1850
    <ol>
     <li> cutoff=5*10^6 yields in 10 runs min=2. </li>
     <li> cutoff=25*10^6 found in 10 runs one solution (seed=2209127524).
     </li>
    </ol>
   </li>
   <li> n=1875: cutoff=10^8 found in run 6 a solution (seed=195078017). </li>
   <li> n=1887: cutoff=2*10^8 produced 5 solutions in 100 runs (e.g.,
   seed=2857056001, osteps=22392426 </li>
   <li> n=1900
    <ol>
     <li> cutoff=25*10^6 yields in 10 runs only min=2. </li>
     <li> cutoff=10^8 yields in 10 runs min=1 twice; so could be
     investigated using more runs. </li>
     <li> cutoff=2*10^8: 100 runs min=1, max=3, mean=1.77. </li>
     <li> cutoff=4*10^8 found in 54 runs one solution (seed=1090357734,
     osteps=5547490). </li>
    </ol>
   </li>
   <li> n=1910: cutoff=4*10^8 found in 59 runs one solution (seed=3723062408,
   osteps=187616262). </li>
   <li> n=1920: cutoff=4*10^8 found in 49 runs one solution (seed=1165735423,
   osteps=232394841). </li>
   <li> n=1921:
    <ol>
     <li> cutoff=10^9:
     \verbatim
> E2 = read_ubcsat("GreenTao_3-3-3-5_1921.cnf_OUT")
 1  2  3
19 78  3
100
> E2 = read_ubcsat("GreenTao_3-3-3-5_1921.cnf_OUT2")
  1   2   3
167 612  27
806
     \endverbatim
     </li>
     <li> cutoff=2*10^9: In 27 runs one solution was found (seed=4076787552,
     osteps=1932855399). </li>
     <li> So apparently a higher cutoff is needed. </li>
    </ol>
   </li>
   <li> n=1925
    <ol>
     <li> cutoff=10^9 yields
     \verbatim
> E2 = read_ubcsat("GreenTao_3-3-3-5_1925.cnf_OUT")
 1  2  3
 8 59  9
76
> E2 = read_ubcsat("~/GreenTao_3-3-3-5_1925.cnf_OUT2")
 1  2  3
11 79 10
100
     \endverbatim
     </li>
     <li> cutoff=2*10^9: 76 runs yield
     \verbatim
 1  2  3
13 62  1
     \endverbatim
     Another 57 runs yield
     \verbatim
 0  1  2
 1 11 45
57
     \endverbatim
     (the solution has osteps=857758539 and seed=4288803153)
     </li>
    </ol>
   </li>
   <li> n=1930
    <ol>
     <li> cutoff=4*10^8 yields (length, table)
     \verbatim
[1] 100
 1  2  3  4
 2 40 57  1
     \endverbatim
     </li>
     <li> cutoff=10^9 yields
     \verbatim
E = read_ubcsat("GreenTao_3-3-3-5_1930.cnf_OUT2")
 1  2  3
 4 69 27
100
     \endverbatim
     </li>
     <li> cutoff=2*10^9
     \verbatim
E = read_ubcsat("GreenTao_3-3-3-5_1930.cnf_OUT3")
1 2 3
3 5 1
9
> E = read_ubcsat("GreenTao_3-3-3-5_1930.cnf_OUT4")
 1  2  3
10 84  6
100
> E2 = read_ubcsat("GreenTao_3-3-3-5_1930.cnf_OUT5")
 1  2  3
 1 14  2
17
     \endverbatim
     </li>
     <li> Now with cutoff=4*10^9: 43 runs yield 7 times min=1 (rest min=2).
     </li>
    </ol>
   </li>
  </ul>


  \todo Upper bounds
  <ul>
   <li> Running minisat2 on GreenTao_3-3-3-4_431.cnf for a day (33 restarts)
   doesn't seem to make progress. </li>
   <li> We now need to investigate GreenTao_3-3-3-4_434.cnf further. </li>
   <li> Apparently the symmetry-breaking clause doesn't make things easier
   for minisat2. </li>
   <li> Running OKsolver_2002-O3-DNDEBUG / -m2pp with "-M -D20" for a while
   doesn't show any progress (max_tree_depth=104 resp. 68 reached, and the bit
   symmetry-breaking shouldn't make a big difference; the only positive thing
   here is that some autarkies are found (in the non-preprocessed case; but
   we can't see how efficient they are). </li>
  </ul>

*/

