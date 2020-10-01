;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Solution to Exercise 39a

(class Number Number
    ()
    (method + (aNumber) (subclassResponsibility (coerce: aNumber self)))
    (method * (aNumber) (subclassResponsibility (coerce: aNumber self)))
    )

(check-expect (+ (asFraction 1) (/ 1 2)) (/ 3 2))
(check-expect (- (asFraction 1) (/ 1 2)) (/ 1 2))
(check-expect (* (asFraction 1) (/ 1 2)) (/ 1 2))
