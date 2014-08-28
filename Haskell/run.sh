#!/bin/bash

echo -e "1 core"

ghc -O2 main.hs -threaded
./main ../shuffled/xaa +RTS -N1

ghc -O2 main.hs -threaded
./main ../shuffled/xab +RTS -N1

ghc -O2 main.hs -threaded
./main ../shuffled/xac +RTS -N1

ghc -O2 main.hs -threaded
./main ../shuffled/xad +RTS -N1

ghc -O2 main.hs -threaded
./main ../shuffled/xae +RTS -N1

ghc -O2 main.hs -threaded
./main ../shuffled/xaf +RTS -N1

ghc -O2 main.hs -threaded
./main ../shuffled/xag +RTS -N1

ghc -O2 main.hs -threaded
./main ../shuffled/xah +RTS -N1

ghc -O2 main.hs -threaded
./main ../shuffled/xai +RTS -N1

ghc -O2 main.hs -threaded
./main ../shuffled/xaj +RTS -N1


echo -e "\n2 cores"

ghc -O2 main.hs -threaded
./main ../shuffled/xaa +RTS -N2

ghc -O2 main.hs -threaded
./main ../shuffled/xab +RTS -N2

ghc -O2 main.hs -threaded
./main ../shuffled/xac +RTS -N2

ghc -O2 main.hs -threaded
./main ../shuffled/xad +RTS -N2

ghc -O2 main.hs -threaded
./main ../shuffled/xae +RTS -N2

ghc -O2 main.hs -threaded
./main ../shuffled/xaf +RTS -N2

ghc -O2 main.hs -threaded
./main ../shuffled/xag +RTS -N2

ghc -O2 main.hs -threaded
./main ../shuffled/xah +RTS -N2

ghc -O2 main.hs -threaded
./main ../shuffled/xai +RTS -N2

ghc -O2 main.hs -threaded
./main ../shuffled/xaj +RTS -N2



echo -e "\n3 cores"

ghc -O2 main.hs -threaded
./main ../shuffled/xaa +RTS -N3

ghc -O2 main.hs -threaded
./main ../shuffled/xab +RTS -N3

ghc -O2 main.hs -threaded
./main ../shuffled/xac +RTS -N3

ghc -O2 main.hs -threaded
./main ../shuffled/xad +RTS -N3

ghc -O2 main.hs -threaded
./main ../shuffled/xae +RTS -N3

ghc -O2 main.hs -threaded
./main ../shuffled/xaf +RTS -N3

ghc -O2 main.hs -threaded
./main ../shuffled/xag +RTS -N3

ghc -O2 main.hs -threaded
./main ../shuffled/xah +RTS -N3

ghc -O2 main.hs -threaded
./main ../shuffled/xai +RTS -N3

ghc -O2 main.hs -threaded
./main ../shuffled/xaj +RTS -N3



echo -e "\n4 cores"

ghc -O2 main.hs -threaded
./main ../shuffled/xaa +RTS -N4

ghc -O2 main.hs -threaded
./main ../shuffled/xab +RTS -N4

ghc -O2 main.hs -threaded
./main ../shuffled/xac +RTS -N4

ghc -O2 main.hs -threaded
./main ../shuffled/xad +RTS -N4

ghc -O2 main.hs -threaded
./main ../shuffled/xae +RTS -N4

ghc -O2 main.hs -threaded
./main ../shuffled/xaf +RTS -N4

ghc -O2 main.hs -threaded
./main ../shuffled/xag +RTS -N4

ghc -O2 main.hs -threaded
./main ../shuffled/xah +RTS -N4

ghc -O2 main.hs -threaded
./main ../shuffled/xai +RTS -N4

ghc -O2 main.hs -threaded
./main ../shuffled/xaj +RTS -N4
