{-# LANGUAGE CPP, ExistentialQuantification #-}

#if defined(__GLASGOW_HASKELL__) && !defined(__HADDOCK__)
#include "MachDeps.h"
#endif

module Main (main) where

#if ! MIN_VERSION_base(4,8,0)
import Data.Monoid (Monoid(mappend, mempty))
#endif

import Control.DeepSeq
import Control.Exception (evaluate)
import Criterion.Main
import qualified Data.ByteString as S
import qualified Data.ByteString.Char8 as C
import qualified Data.ByteString.Lazy as L
import Data.Char (ord)
