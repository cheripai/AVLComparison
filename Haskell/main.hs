{-# LANGUAGE TemplateHaskell #-}
import Control.DeepSeq.TH
import Control.Concurrent
import Data.Tree.AVL as A
import Data.COrdering
import System.CPUTime
import qualified Data.ByteString.Char8 as B
import Control.DeepSeq
import Data.List.Split
import System.Environment
import Control.Parallel

$(deriveNFData ''AVL)

-- Inserts elements from list into AVL tree
load :: AVL B.ByteString -> [B.ByteString] -> AVL B.ByteString
load t [] = t
load t (x:xs) = A.push (fstCC x) x (load t xs)


main = do
    args <- getArgs
    contents <- fmap B.lines $ B.readFile $ args !! 0
    let l = splitEvery (length contents `div` 4) contents
    deepseq contents $ deepseq l $ return ()
    start <- getCPUTime
    
    -- Loading the tree with the subpartitions
    let t1 = load empty $ l !! 0
    let t2 = load empty $ l !! 1
    let t3 = load empty $ l !! 2
    let t4 = load empty $ l !! 3
    let p = par t1 $ par t2 $ par t3 t4
    
    -- Calling union to combine the trees
    let b = union fstCC t1 t2
    let t = union fstCC t3 t4
    let bt = union fstCC b t
    let bt' = par b $ par t bt
    deepseq p $ deepseq bt' $ return ()
    
    end <- getCPUTime
    n <- getNumCapabilities
    let diff = ((fromIntegral (end-start)) / (10^12) / fromIntegral n)
    putStrLn $ show diff
