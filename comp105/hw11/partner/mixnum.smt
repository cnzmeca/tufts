(use bignum.smt)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Solution to Exercise 44
(class SmallInteger SmallInteger
    ()
    (method asLargeInteger () (new: LargeInteger self))
    (method + (aNumber) (addSmallIntegerTo: aNumber self))
    (method addSmallIntegerTo: (anInteger)
        (value (addSmall:withOverflow: self anInteger
        {(+ (asLargeInteger self) anInteger)})))
    (method addSmall:withOverflow: primitive add:withOverflow:)

    (method * (aNumber) (mulSmallIntegerTo: aNumber self))
    (method mulSmallIntegerTo: (anInteger)
        (value (mulSmall:withOverflow: self anInteger
        {(+ (asLargeInteger self) anInteger)})))
    (method mulSmall:withOverflow: primitive mul:withOverflow:)

    (method - (aNumber) (addSmallIntegerTo: (negated aNumber) self))
    
    (method negated () (- 0 self))
 
    (method addLargePositiveIntegerTo: (aNumber) (+ self aNumber))
    (method addLargeNegativeIntegerTo: (aNumber) (+ (negated self) aNumber))
    (method multiplyByLargePositiveInteger: (aNumber) (* self aNumber))
   (method multiplyByLargeNegativeInteger: (aNumber) (* (negated self) aNumber))
    )

    
