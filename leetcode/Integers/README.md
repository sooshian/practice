How to check overflow of integer ?

change any integer operation to this format

newValue = oldValue * 10 + digit (digit is between 0..9)

if it is a positive number
when (oldValue > MAX_INT / 10 || (oldValue == MAX_INT / 10 && digit > MAX_INT % 10)) equals true, overflow happens

if it is a negative number
when (oldValue < MIN_INT /10 || (oldValue == MIN_INT / 10  && digit < MIN_INT % 10)) equals true, overflow happens