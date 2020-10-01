(val drop 
    (type-lambda ['a]
        (letrec
            [([drop-mono : (int (list 'a) -> (list 'a))]
                (lambda ([n : int] [xs : (list 'a)])
                    (if ((@ = int) 0 n)
                    xs
                        (if ((@ null? 'a) xs)
                        (@ '() 'a)
                        (drop-mono (- n 1) ((@ cdr 'a) xs))))))]
            drop-mono)))

;; (check-type ((@ drop int) 2 [1 2 3 4 5]) int list)

(val takewhile
    (type-lambda ['a]
        (letrec
            [([takewhile-mono : (('a -> bool) (list 'a) -> (list 'a))]
                (lambda ([p? : ('a -> bool)] [xs : (list 'a)])
                    (if ((@ null? 'a) xs)
                        (@ '() 'a)
                        (if (p? ((@ car 'a) xs))
                            ((@ cons 'a) ((@ car 'a) xs) (takewhile-mono
                                                p? ((@ cdr 'a) xs)))
                            (@ '() 'a)))))]
            takewhile-mono)))

;; (check-type ((@ takewhile int) number? [2 4 6 7 9]) int list)
