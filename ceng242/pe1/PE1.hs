module PE1 where

-- Question 1
findInList :: (Eq a) => [a] -> [a] -> [Int]
findInList [] _ = []
findInList xs ys = findIndices 0 xs ys

-- Helper function for question 1 
findIndices :: (Eq a) => Int -> [a] -> [a] -> [Int]
findIndices _ [] _ = []
findIndices idx (x:restX) (y:restY)
  | x == y    = idx : findIndices (idx + 1) restX restY
  | otherwise = findIndices (idx + 1) (x:restX) restY

-- Question 2
findInMatrix :: (Eq a) => [[a]] -> [[a]] -> [[(Int, Int)]]
findInMatrix pattern matrix = 
    let newPattern = traverseDiagonalPattern pattern
        newMatrix = traverseDiagonalMatrix matrix
        coords = findCoordinates newPattern newMatrix
        rows = length pattern
        cols = length (head pattern)
    in map (\i -> take cols (drop (i * cols) coords)) [0..rows-1]

-- Helper functions for question 2
findCoordinates :: (Eq a) => [a] -> [(a, (Int, Int))] -> [(Int, Int)]
findCoordinates _ [] = []
findCoordinates [] _ = []
findCoordinates (x:xs) ((y1, y2):ys)
    | x == y1   = y2 : findCoordinates xs ys
    | otherwise = findCoordinates (x:xs) ys

-- Flattens the pattern matrix
traverseDiagonalPattern :: [[a]] -> [a]
traverseDiagonalPattern pattern = go 0 []
  where
    numRows = length pattern
    numCols = length (head pattern)
    totalDiagonals = numRows + numCols - 1
    
    go diagonal result
      | diagonal >= totalDiagonals = result
      | otherwise =
        let diagonalElements = [pattern !! r !! (diagonal - r) | r <- [max 0 (diagonal - numCols + 1) .. min diagonal (numRows - 1)]]
        in go (diagonal + 1) (result ++ diagonalElements)
        
-- Flattens the image matrix with the coordinates
traverseDiagonalMatrix :: [[a]] -> [(a, (Int, Int))]
traverseDiagonalMatrix matrix
    | length (head matrix) >= length matrix = traverseHorizontalDiagonals matrix
    | otherwise = traverseVerticalDiagonals matrix

traverseHorizontalDiagonals :: [[a]] -> [(a, (Int, Int))]
traverseHorizontalDiagonals matrix = 
    let rows = length matrix
        cols = length (head matrix)
        diagonalStarts = [0..rows + cols - 2]
        getIndices start = 
            let row = max 0 (start - cols + 1)
                col = min start (cols - 1)
            in [(matrix !! i !! j, (i, j)) | i <- [row..min (rows - 1) (start - row)], let j = start - i]
    in concatMap getIndices diagonalStarts

traverseVerticalDiagonals :: [[a]] -> [(a, (Int, Int))]
traverseVerticalDiagonals matrix = 
    let rows = length matrix
        cols = length (head matrix)
        diagonalStarts = [0..rows + cols - 2]
        getIndices start = 
            let col = max 0 (start - rows + 1)
                row = min start (rows - 1)
            in [(matrix !! i !! j, (i, j)) | j <- [col..min (cols - 1) (start - col)], let i = start - j]
    in concatMap getIndices diagonalStarts






    
    
    

        


    



