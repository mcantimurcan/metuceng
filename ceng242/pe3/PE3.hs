module PE3 where

data Expression = Variable String 
    | Constant Float
    | Sine Expression
    | Cosine Expression
    | Negation Expression
    | Addition Expression Expression
    | Multiplication Expression Expression

class Differential a where
    diff :: a -> a -> a

instance Show Expression where
    show (Variable x) = "Variable '" ++ x ++ "'"
    show (Constant c) = "Constant " ++ show c
    show (Sine expr) = "sin " ++ show expr
    show (Cosine expr) = "cos " ++ show expr
    show (Negation expr) = "-" ++ show expr
    show (Addition expr1 expr2) = "(" ++ show expr1 ++ " + " ++ show expr2 ++ ")"
    show (Multiplication expr1 expr2) = "(" ++ show expr1 ++ " * " ++ show expr2 ++ ")"

instance Eq Expression where
    (Variable x) == (Variable y) = x == y
    (Constant a) == (Constant b) = a == b
    (Sine expr1) == (Sine expr2) = expr1 == expr2
    (Cosine expr1) == (Cosine expr2) = expr1 == expr2
    (Negation expr1) == (Negation expr2) = expr1 == expr2
    (Addition expr1a expr1b) == (Addition expr2a expr2b) = expr1a == expr2a && expr1b == expr2b
    (Multiplication expr1a expr1b) == (Multiplication expr2a expr2b) = expr1a == expr2a && expr1b == expr2b
    _ == _ = False

instance Num Expression where
    fromInteger = Constant . fromInteger
    
    negate (Constant c) = Constant (-c)
    negate expr = Negation expr
    
    (+) (Constant 0) expr = expr
    (+) expr (Constant 0) = expr
    (+) expr1 expr2 = Addition expr1 expr2
    
    (*) (Constant 0) _ = Constant 0
    (*) _ (Constant 0) = Constant 0
    (*) (Constant 1) expr = expr
    (*) expr (Constant 1) = expr
    (*) expr1 expr2 = Multiplication expr1 expr2
    
    abs (Constant n) = Constant (abs n)
    abs (Negation (Constant n)) = Constant (abs n)
    
    signum (Constant n)
        | n > 0 = Constant 1
        | n == 0 = Constant 0
        | otherwise = Constant (-1)
    signum (Negation (Constant n)) = Negation (signum (Constant n))

instance Differential Expression where
    diff (Constant _) _ = Constant 0
    diff (Variable v) (Variable dv)
        | v == dv = Constant 1
        | otherwise = Constant 0
    diff (Sine expr) dv = Multiplication (Cosine expr) (diff expr dv) 
    diff (Cosine expr) dv = Multiplication (Negation (Sine expr)) (diff expr dv)
    diff (Negation expr) dv = Negation (diff expr dv)
    diff (Addition lhs rhs) dv = Addition (diff lhs dv) (diff rhs dv)
    diff (Multiplication lhs rhs) dv = Addition (Multiplication (diff lhs dv) rhs) (Multiplication lhs (diff rhs dv))

shuntingyard :: [String] -> [String] -> [String] -> [String]
shuntingyard [] stack queue = queue ++ reverse stack
shuntingyard (token:expression) stack queue
    | token == "(" =
        shuntingyard expression (token:stack) queue
    | token == ")" =
        let (newStack, newQueue) = processUntilLeftParen stack queue
        in shuntingyard expression newStack newQueue
    | token `elem` ["-", "sin", "cos", "*", "+"] =
        let (newStack, newQueue) = processHigherPrecedence token stack queue
        in shuntingyard expression newStack newQueue
    | otherwise = shuntingyard expression stack (queue ++ [token])

-- Helper functions
processUntilLeftParen :: [String] -> [String] -> ([String], [String])
processUntilLeftParen stack queue
    | null stack = error "Mismatched parentheses"
    | head stack == "(" = (tail stack, queue)
    | otherwise = processUntilLeftParen (tail stack) (queue ++ [head stack])

processHigherPrecedence :: String -> [String] -> [String] -> ([String], [String])
processHigherPrecedence token stack queue
    | null stack || head stack == "(" = (token:stack, queue)
    | precedence token <= precedence (head stack) =
        processHigherPrecedence token (tail stack) (queue ++ [head stack])
    | otherwise = (token:stack, queue)

precedence :: String -> Int
precedence "-" = 4
precedence "sin" = 3
precedence "cos" = 3
precedence "*" = 2
precedence "+" = 1
precedence _ = error "Invalid operator"
