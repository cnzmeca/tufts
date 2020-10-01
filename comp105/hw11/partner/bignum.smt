;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Solution to Exercise 42

(class Natural Magnitude
    [m d b]
    ; A (self) = [(self div b) (self mod b) b] 
    ; I (self) = (& (<= 0 d) (> b d))
    (method first:rest: (m d) (cons: d m)) 
    )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Solution to Exercise 43
(class LargeInteger Integer
    [magnitude]
    (class-method withMagnitude: (aNatural)
        (magnitude: (new self) aNatural))
    (method magnitude () magnitude)
    (method magnitude: (aNatural)
        (set magnitude aNatural)
        self)
    (class-method new: (anInteger)
        (if (negative anInteger)
            {(magnitude: (new LargeNegativeInteger)
            (new: Natural (negated anInteger)))}
            {(magnitude: (new LargePositiveInteger) (new: Natural anInteger))}))
    (method asLargeInteger () self)
    (method isZero () (isZero magnitude))
    (method = (anInteger) (isZero   (- self anInteger)))
    (method < (anInteger) (negative (- self anInteger)))
    (method div: (n) (sdiv: self n))
    (method decimal () (locals decimals)
        (set decimals (decimal magnitude))
        (ifTrue: (negative self)
            {(addFirst: decimals ’-)})
        decimals)
    )

(class LargePositiveInteger LargeInteger
    [magnitude]
    ; A (self) = [(self magnitude)]
    ; I (self) = magnitude > 0
    (method negative () false)
    (method strictlyPositive () (not (isZero self)))
    (method + (anInteger) (addLargePositiveIntegerTo: anInteger self))
    (method addLargePositiveIntegerTo: (anInteger) (withMagnitude:
        LargePositiveInteger (+ magnitude (magnitude anInteger))))
    (method multiplyByLargePositiveInteger: (anInteger) (withMagnitude:
        LargePositiveInteger (* magnitude (magnitude anInteger))))
    (method multiplyByLargeNegativeInteger: (anInteger) (withMagnitude:
        LargeNegativeInteger (* magnitude (magnitude anInteger))))
    (method sdiv: (anInteger)
       (ifTrue:ifFalse: (strictlyPositive anInteger)
           {(withMagnitude: LargePositiveInteger (sdiv: magnitude anInteger))}
           {(negated (sdiv: (- (- self (new: LargeInteger anInteger))
               (new: LargeInteger 1)) (negated anInteger)))}))
    )

(class LargeNegativeInteger LargeInteger
    [magnitude]
    ; A (self) = [(self magnitude)]
    ; I (self) = magnitude < 0
    (method negative () true)
    (method strictlyNegative () (not (isZero self)))
    (method + (anInteger) (addLargeNegativeIntegerTo: anInteger self))
    (method addLargeNegativeIntegerTo: (anInteger) (withMagnitude:
        LargeNegativeInteger (- (magnitude anInteger) magnitude)))
    (method multiplyByLargePositiveInteger: (anInteger) (withMagnitude:
        LargeNegativeInteger (* magnitude (magnitude anInteger))))
    (method multiplyByLargeNegativeInteger: (anInteger) (withMagnitude:
        LargePositiveInteger (* magnitude (magnitude anInteger))))
    (method sdiv: (anInteger)
        (ifTrue:ifFalse: (strictlyPositive anInteger)
            {(negated (sdiv: (- (+ (negated self) (new: LargeInteger anInteger))
                (new: LargeInteger 1)) anInteger))}
            {(sdiv: (negated self) (negated anInteger))}))
    )
