// Oliver Kullmann, 22.4.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/GreenTaoProblems/plans/GreenTao_4-3-3-3-3.hpp
  \brief Investigations on greentao_4(3,3,3,3)


  \todo Best local search algorithm
  <ul>
   <li> ubcsat-okl -runs 10 -cutoff 10000 -i GreenTao_4-3-3-3-3_400.cnf yields
   the following means for the different algorithms:
   \verbatim
gsat 36
gsat -v simple 37.2
gwsat 31.1
gsat-tabu 21.7
hsat 36.1
hwsat 35.4
walksat 84.3
walksat-tabu 48.6
walksat-tabu -v nonull 49.7
novelty 51
novelty+ 50.7
adaptnovelty+ 22.2
rnovelty 53.6
rnovelty+ 49.7
saps 41.6
rsaps 37.8
sapsnr 42.3
rots 21.2
irots 38.6
samd 20.9
   \endverbatim
   The best algorithms here are samd, rots, gsat-tabu and adaptnovelty+
   (in this order). </li>
   <li> With runs=100:
   \verbatim
samd 20.950000 FlipsPerSecond = 100301
gsat-tabu 21.1 FlipsPerSecond = 68634
rots 21.17 FlipsPerSecond = 77399
adaptnovelty+ 22.66 FlipsPerSecond = 473934
   \endverbatim
   So adaptnovelty+ is the weakest w.r.t. what is reached, but it is
   fastest by far. </li>
   <li> Now with cutoff=100*10^3:
   \verbatim
adaptnovelty+ 13.24 min = 8 FlipsPerSecond = 457666
samd 13.67 min = 10 FlipsPerSecond = 95157
gsat-tabu 13.75 min = 10 FlipsPerSecond = 94661
rots 18.34 min = 15 FlipsPerSecond = 79853
   \endverbatim
   So actually adaptnovelty+ seems best by far! </li>
   <li> With cutoff=10^6:
   \verbatim
adaptnovelty+ 9.41 min = 7
samd 11.37 min = 7
gsat-tabu 11.35 min = 8
rots 17.97 min = 15
   \endverbatim
   So adaptnovelty+ should be clearly the best. </li>
   <li> One needs to investigate preprocessing (together with symmetry
   breaking), whether this changes the picture. Using n=400 as above.
    <ol>
     <li> Just the minisat2-preprocessing alone makes things far worse:
     \verbatim
> ubcsat-okl -runs 10 -cutoff 1000000 -alg adaptnovelty+ -i GreenTao_4-3-3-3-3_400-m2pp.cnf
Clauses = 30761
Variables = 1600
TotalLiterals = 135432
FlipsPerSecond = 256674
BestStep_Mean = 368355.300000
Steps_Mean = 1000000.000000
Steps_Max = 1000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 15.200000
BestSolution_Median = 14.500000
BestSolution_Min = 14.000000
BestSolution_Max = 18.000000
> ubcsat-okl -runs 10 -cutoff 1000000 -alg adaptnovelty+ -i GreenTao_4-3-3-3-3_400.cnf
Clauses = 32364
Variables = 1600
TotalLiterals = 95092
FlipsPerSecond = 542299
BestStep_Mean = 481813.900000
Steps_Mean = 1000000.000000
Steps_Max = 1000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 9.800000
BestSolution_Median = 10.000000
BestSolution_Min = 6.000000
BestSolution_Max = 11.000000

adaptnovelty+ 15.2 min = 14
samd 80.4 min = 74
gsat-tabu 80.5 min = 71
rots 76.0 min = 72

walksat 116.5 min = 110
     \endverbatim
     Once we have the tools available, we need actually to reconsider all
     algorithms.
     </li>
     <li> Just symmetry-breaking alone:
     \verbatim
> ubcsat-okl -runs 10 -cutoff 1000000 -alg adaptnovelty+ -i GreenTao_sb_4-3_400.cnf
Clauses = 32367
Variables = 1600
TotalLiterals = 95095
FlipsPerSecond = 477555
BestStep_Mean = 525055.500000
Steps_Mean = 1000000.000000
Steps_Max = 1000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 9.700000
BestSolution_Median = 10.000000
BestSolution_Min = 9.000000
BestSolution_Max = 11.000000

adaptnovelty+ 9.7 min = 9
samd 11.5 min = 9
gsat-tabu 11.1 min = 9
rots 17.8 min = 16
     \endverbatim
     So it doesn't seem to help (and perhaps it actually harms). Though one
     should definitely apply unit-clause propagation, and see whether this
     improves something. And again all algorithms need to be reexamined. </li>
     <li> Both together:
     \verbatim
> ubcsat-okl -runs 10 -cutoff 1000000 -alg adaptnovelty+ -i GreenTao_sb_4-3_400-m2pp.cnf
Clauses = 30488
Variables = 1600
TotalLiterals = 133986
FlipsPerSecond = 281532
BestStep_Mean = 463622.700000
Steps_Mean = 1000000.000000
Steps_Max = 1000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 15.300000
BestSolution_Median = 15.500000
BestSolution_Min = 12.000000
BestSolution_Max = 17.000000

adaptnovelty+ 15.3 min = 12
samd 83.9  min = 73
gsat-tabu  min = 
rots 79.2 min = 64
     \endverbatim
     </li>
     <li> The first impression is that nothing can be achieved in this way.
     Perhaps there is a fundamental difference between DPLL-like SAT solvers
     and local-search SAT solvers: The former are strongest when some
     "structure" exists (in the form of "attackable points"), while the latter
     are strongest when the problems have a kind of "random" or "uniform"
     "(non-)structure". </li>
    </ol>
   </li>
  </ul>


  \todo Lower bounds: greentao_4(3,3,3,3) > 375
  <ul>
   <li> Best we see first where adaptnovelty+ finds easily solutions. </li>
   <li> n=300 very easily satisfiable. </li>
   <li> n=338 easily satisfiable. </li>
   <li> n=348 found satisfiable (cutoff=10^6, seed=1463613527). </li>
   <li> n=352 found satisfiable (cutoff=10^6, seed=3476207011). </li>
   <li> n=355 found satisfiable (cutoff=10^6, seed=3865650519). </li>
   <li> n=356 found satisfiable (cutoff=10^6, seed=1266825813). </li>
   <li> n=357
    <ol>
     <li>
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 100 -cutoff 1000000 -i GreenTao_4-3-3-3-3_357.cnf
clauses = 26471
Variables = 1428
TotalLiterals = 77628
FlipsPerSecond = 659761
BestStep_Mean = 447147.770000
Steps_Mean = 1000000.000000
Steps_Max = 1000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 2.330000
BestSolution_Median = 2.000000
BestSolution_Min = 1.000000
BestSolution_Max = 4.000000
     \endverbatim
     seems unsatisfiable.
     </li>
     <li>
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 1000 -cutoff 10000000 -i GreenTao_4-3-3-3-3_357.cnf
Clauses = 26471
Variables = 1428
TotalLiterals = 77628
FlipsPerSecond = 628361
BestStep_Mean = 3492205.863000
Steps_Mean = 9675267.971000
Steps_Max = 10000000.000000
PercentSuccess = 5.90
BestSolution_Mean = 1.236000
BestSolution_Median = 1.000000
BestSolution_Min = 0.000000
BestSolution_Max = 2.000000
     \endverbatim
     A solution was found e.g. with seed=876327096. </li>
    </ol>
   </li>
   <li> n=358 found satisfiable with cutoff=10*10^6 and seed=1641133745. </li>
   <li> n=359 found satisfiable with cutoff=10*10^6 and seed=2108885839. </li>
   <li> n=360 found satisfiable with cutoff=10*10^6 and seed=1802549929. </li>
   <li> n=361 found satisfiable with cutoff=10*10^6 and seed=1427782088
   (140 runs needed). </li>
   <li> n=362 found satisfiable with cutoff=10*10^6 and seed=2256326590. </li>
   <li> n=363 found satisfiable with cutoff=10*10^6 and seed=342405381. </li>
   <li> n=364 found satisfiable (seed=373433483)
   \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 1000 -cutoff 10000000 -i GreenTao_4-3-3-3-3_364.cnf
Clauses = 27420
Variables = 1456
TotalLiterals = 80440
FlipsPerSecond = 602655
BestStep_Mean = 3488853.231000
Steps_Mean = 9993570.374000
Steps_Max = 10000000.000000
PercentSuccess = 0.10
BestSolution_Mean = 2.195000
BestSolution_Median = 2.000000
BestSolution_Min = 0.000000
BestSolution_Max = 4.000000
   \endverbatim
   </li>
   <li> n=365 found satisfiable (seed=2430690635)
   \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 1000 -cutoff 10000000 -i GreenTao_4-3-3-3-3_365.cnf
Clauses = 27543
Variables = 1460
TotalLiterals = 80804
FlipsPerSecond = 598431
BestStep_Mean = 3608383.766000
Steps_Mean = 9990625.610000
Steps_Max = 10000000.000000
PercentSuccess = 0.10
BestSolution_Mean = 2.248000
BestSolution_Median = 2.000000
BestSolution_Min = 0.000000
BestSolution_Max = 4.000000
   \endverbatim
     </li>
    </ol>
   </li>
   <li> n=366 found satisfiable (seed=3191925315). </li>
   <li> n=367 found satisfiable (seed=1210488827). </li>
   \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 1000 -cutoff 10000000 -i GreenTao_4-3-3-3-3_367.cnf
Clauses = 27805
Variables = 1468
TotalLiterals = 81580
FlipsPerSecond = 597684
BestStep_Mean = 3695380.296000
Steps_Mean = 9999170.437000
Steps_Max = 10000000.000000
PercentSuccess = 0.10
BestSolution_Mean = 2.468000
BestSolution_Median = 2.000000
BestSolution_Min = 0.000000
BestSolution_Max = 4.000000
   \endverbatim
   </li>
   <li> n=368 found satisfiable:
   \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 1000 -cutoff 10000000 -i GreenTao_4-3-3-3-3_368.cnf
Clauses = 27936
Variables = 1472
TotalLiterals = 81968
FlipsPerSecond = 601632
BestStep_Mean = 3627492.165000
Steps_Mean = 9984052.649000
Steps_Max = 10000000.000000
PercentSuccess = 0.30
BestSolution_Mean = 2.580000
BestSolution_Median = 3.000000
BestSolution_Min = 0.000000
BestSolution_Max = 4.000000
   \endverbatim
   for example seed=1454356055. </li>
   <li> n=369 found satisfiable (2 solutions in 807 runs with
   cutoff=10000000=10*10^6, for example seed=191448713). </li>
   <li> n=370
    <ol>
     <li>
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 1000 -cutoff 10000000 -i GreenTao_4-3-3-3-3_370.cnf
Clauses = 28202
Variables = 1480
TotalLiterals = 82756
FlipsPerSecond = 612643
BestStep_Mean = 3801288.200000
Steps_Mean = 10000000.000000
Steps_Max = 10000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 2.821000
BestSolution_Median = 3.000000
BestSolution_Min = 1.000000
BestSolution_Max = 4.000000
     \endverbatim
     </li>
     <li>
     \verbatim With cutoff=20000000 in 1295 runs one solution was found
     (seed=406385002). </li>
    </ol>
   </li>
   <li> n=375:
    <ol>
     <li>
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 3000 -cutoff 10000000 -i GreenTao_4-3-3-3-3_375.cnf
Clauses = 28901
Variables = 1500
TotalLiterals = 84828
FlipsPerSecond = 587133
BestStep_Mean = 3945694.062333
Steps_Mean = 10000000.000000
Steps_Max = 10000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 3.491667
BestSolution_Median = 4.000000
BestSolution_Min = 1.000000
BestSolution_Max = 5.000000
ubcsat-okl -alg adaptnovelty+ -runs 1000 -cutoff 20000000 -i GreenTao_4-3-3-3-3_375.cnf
Clauses = 28901
Variables = 1500
TotalLiterals = 84828
FlipsPerSecond = 577930
BestStep_Mean = 7458479.743000
Steps_Mean = 20000000.000000
Steps_Max = 20000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 3.156000
BestSolution_Median = 3.000000
BestSolution_Min = 1.000000
BestSolution_Max = 5.000000
> ubcsat-okl -alg adaptnovelty+ -runs 1000 -cutoff 100000000 -i GreenTao_4-3-3-3-3_375.cnf
Clauses = 28901
Variables = 1500
TotalLiterals = 84828
FlipsPerSecond = 601664
BestStep_Mean = 31289071.326000
Steps_Mean = 100000000.000000
Steps_Max = 100000000.000000
PercentSuccess = 0.00
BestSolution_Mean = 2.463000
BestSolution_Median = 2.000000
BestSolution_Min = 1.000000
BestSolution_Max = 4.000000
     \endverbatim
     </li>
     <li> Finally using cutoff=10^9 in 31 runs a solution (seed=1958151049,
     osteps=765212681) was found. </li>
    </ol>
   </li>
   <li> n=376 to be processed on cs-oksvr with cutoff=10^9. </li>
   <li> n=378
    <ol>
     <li> cutoff=10^9 yields in 15 runs 14 times min=2 and once min=1. </li>
     <li> cutoff=4*10^9:
     \verbatim
> ubcsat-okl -alg adaptnovelty+ -runs 100 -cutoff 4000000000 -i GreenTao_4-3-3-3-3_378.cnf
       sat  min     osteps     msteps       seed
      1 0     1 3247511031 4000000000  969465860
      2 0     2   26424461 4000000000 3292184256
      3 0     2   41342213 4000000000 2086282835
      4 0     1 2670401695 4000000000 3600327435
     \endverbatim
     Possibly this is satisfiable, but according to the general strategy
     outlined in "Finding the n where a problem series changes from SAT to
     UNSAT" in ExperimentSystem/plans/RunUBCSAT.hpp we first investigate
     n=376. </li>
    </ol>
   </li>
   <li> n=381 cutoff=2*10^9 yields in 8 runs constantly min=2 with the maximal
   osteps ~ 500*10^6, so it looks unsatisfiable. </li>
   <li> n=387, cutoff=10^9 yields in 22 runs only min=2,3,4; if this is to be
   re-examined, then cutoff=4*10^9 should be used. </li>
   <li> n=400, cutoff=10^9 yields in 12 runs a minimum=4, and this only
   once, so this looks very tough. </li>
   <li> n=450: using cutoff=10^9, one run reaches a minimum of 14, which
   seems hopeless. </li>
   <li> n=600
    <ol>
     <li> The instance-generation by Maxima takes far too long.
      <ul>
       <li> nbfcsfd2fcs_aloamo is rather slow, but a worse bottleneck
       is standardise_fcs. </li>
       <li> And worst is standard_statistics_fcs! </li>
       <li> Where actually these statistics are not so informative anymore,
       since they mix three different types of clauses. So we better
       should have separate statistics on the hypergraphs, on the alo-
       and alo-clauses, and for everything together. </li>
      </ul>
     </li>
     <li> adaptnovelty+ reaches only values in the sixties. </li>
    </ol>
   </li>
  </ul>


  \todo Upper bounds
  <ul>
   <li> From the experience with "greentao_3(3,3,3) = 137" (see
   Investigations/RamseyTheory/GreenTaoProblems/plans/general.hpp)
   it seems that minisat2 performs best here. </li>
   <li> One one should employ symmetry breaking here. </li>
  </ul>

*/

