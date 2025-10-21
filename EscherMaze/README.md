MC Escher Maze Design doc:
Basic ideas:
● Monster(<) is chasing you(X) – Gerishom/Blake
● Gain 6 coins(+) to escape
● Choose to go left, right, or straight
● You start with three health/coin
● [] - “This is a empty space gain nothing” -
● * - “Star here gain one star”
● || - disappear/block/hole Very Important - remove permanently
● < - “Monster here lose one health”
● We generate random numbers for the spaces and modulate it by 3, which decides

which of the three options(blank space, star/coin, or monster) is.
● We create a 3x3 board each time we move which recreates the geometry and so we can
go back to the same space without it even being the same.
● There is a chance that every space is all monsters, all blank, or all coins.
Monster ideas:
● Monsters move in random spots
● If you get hit by a monster then you lose health/coin