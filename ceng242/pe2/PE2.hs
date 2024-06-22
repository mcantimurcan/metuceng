module PE2 where

data Tree k v = EmptyTree | Node k v [Tree k v] deriving (Show, Eq)

-- Question 1
selectiveMap :: (a -> Bool) -> (a -> a) -> [a] -> [a]
selectiveMap _ _ [] = []
selectiveMap fun1 fun2 (x:rest) = 
    if fun1 x 
        then fun2 x : selectiveMap fun1 fun2 rest
        else x : selectiveMap fun1 fun2 rest

-- Question 2
tSelectiveMap :: (k -> Bool) -> (v -> v) -> Tree k v -> Tree k v
tSelectiveMap _ _ EmptyTree = EmptyTree
tSelectiveMap fun1 fun2 (Node k v children) =
    if fun1 k 
        then Node k (fun2 v) (map (tSelectiveMap fun1 fun2) children)
        else Node k v (map (tSelectiveMap fun1 fun2) children)

-- Question 3
tSelectiveMappingFold :: (k -> Bool) -> (k -> v -> r) -> (r -> r -> r) -> r -> Tree k v -> r
tSelectiveMappingFold _ _ _ idt EmptyTree = idt
tSelectiveMappingFold fun1 fun2 comb val (Node k v children) = 
    if fun1 k 
        then comb (fun2 k v) (foldr (\child acc -> tSelectiveMappingFold fun1 fun2 comb acc child) val children)
        else foldr (\child acc -> tSelectiveMappingFold fun1 fun2 comb acc child) val children
    
-- Question 4
-- This question commented out so that your file compiles even before you complete it
-- It shouldn't effect the grades of other questions when commented out
-- When ready, just remove the lines with {- and -} to uncomment the function
searchTree :: (Eq k, Eq v) => v -> Tree k v -> (k -> v)
searchTree def = tSelectiveMappingFold a b c d
    where a = bypassTrue
          b = filterHelper
          c = combineHelper
          d = const def
          
          -- Helper Functions
          bypassTrue _ = True
           
          filterHelper x y key = case lookup key [(x, y)] of
                                   Just v -> v
                                   Nothing -> def
           
          combineHelper f g k =
              let fValue = f k
                  gValue = g k
              in if fValue == def then gValue else fValue
          
            





