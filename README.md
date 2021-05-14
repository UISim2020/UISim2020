# UISim2020
Source code of the paper 'Unified and Incremental SimRank: Index-free Approximation with Scheduled Principle'



## Tested Environment

Ubuntu 18.04.4 LTS

C++ 11

Make 4.1

## How to Use

Modify the Config in `UISim_C++/src/Config.cpp` and compile with `make`.

#### Select Hubs

```shell
./SelectHubs [hubType]
```

#### Single Pair

```shell
./Online_sp [hubType] [numHubs] [depth] [stopRea] [eta]
```

#### Single Source

```shell
./Online [hubType] [numHubs] [depth] [stopRea] [eta]
```

#### All Pair

```shell
./Online_ap [hubType] [numHubs] [depth] [stopRea] [eta] [topK]
```



## Baselines

#### Single Source:

- ProbeSim https://github.com/dokirabbithole/ProbeSim_vldb_pub
- PRSim https://github.com/wzskytop/PRSim-Code
- SimPush https://github.com/jmshi123/SimPush

#### Single Pair

- BLPMC https://github.com/RapidsAtHKUST/SimRank

#### All Pair

- LocalPush https://github.com/KeithYue/SimRankRelease
- TreeWand https://github.com/fastsim2016/TreeWand



## Data links

#### Small Graph

1. WikiVode (Wiki in `data` folder)
2. 4Area (DBLP in `data` folder)
3. CondMat (CA in `data` folder)

#### Big Graph

1. enwiki2013  http://law.di.unimi.it/webdata/enwiki-2013/
2. it2014 http://law.di.unimi.it/webdata/it-2004/
3. Friendster http://snap.stanford.edu/data/com-Friendster.html 

#### Dynamic Graph

1. Gnutella http://snap.stanford.edu/data/index.html 
2. DBLP http://forward.cs.illinois.edu/datasets/RoundTripRank/RoundTripRank-BibQueryGraphs-Apr2013-BibNet.zip



## Bugs or questions?

If you have any questions related to the code, feel free to email Kai (`drogozhang@gmail.com`). 

If you encounter any problems when using the code, or want to report a bug, you can open an issue. Please try to specify the problem with details so we can help you better and quicker!



