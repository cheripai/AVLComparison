{-# LANGUAGE TemplateHaskell #-}
import Control.DeepSeq.TH
import Control.Concurrent
import Data.Maybe
import Data.Tree.AVL as A
import Data.COrdering
import System.CPUTime
import qualified Data.ByteString.Lazy.Char8 as B
import Control.Monad.Par
import Control.DeepSeq
import Data.List.Split
import Control.Monad.IO.Class
import System.Environment

$(deriveNFData ''AVL)

load :: AVL B.ByteString -> [B.ByteString] -> AVL B.ByteString
load t [] = t
load t (x:xs) = A.push (fstCC x) x (load t xs)


unload :: AVL B.ByteString -> [B.ByteString] -> IO ()
unload t [] = return ()
unload t (x:xs) = do
            let t' = snd $ A.assertPop (fstCC x) t
            unload t' xs


find :: AVL B.ByteString -> [B.ByteString] -> Bool 
find t [] = True
find t (x:xs) = do
        if (A.contains t (compare x)) == False
            then False
            else find t xs


main = do
    args <- getArgs
    contents <- fmap B.lines $ B.readFile $ args !! 0
    let l = splitEvery (length contents `div` 4) contents
    deepseq contents $ deepseq l $ return  ()
    start <- getCPUTime
    runParIO $ do
        t1 <- spawn (return $ load empty $ l !! 0)
        t2 <- spawn (return $ load empty $ l !! 1)
        t3 <- spawn (return $ load empty $ l !! 2)
        t4 <- spawn (return $ load empty $ l !! 3)
        t1' <- get t1
        t2' <- get t2
        t3' <- get t3
        t4' <- get t4
        let b' = union fstCC t1' t2'
        let t' = union fstCC t3' t4'
        let bt = union fstCC b' t'
        return ()
    end <- getCPUTime
    n <- getNumCapabilities
    let diff = ((fromIntegral (end-start)) / (10^12) / fromIntegral n)
    putStrLn $ show diff
