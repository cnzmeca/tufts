;; Tests taken from homework examples

(check-type cons (forall ('a) ('a (list 'a) -> (list 'a))))
(check-type (@ car int) ((list int) -> int))
(check-type
     (type-lambda ['a] (lambda ([x : 'a]) x))
     (forall ('a) ('a -> 'a)))
