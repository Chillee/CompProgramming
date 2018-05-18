from fractions import Fraction

def answer(pegs):
    is_even = (len(pegs) % 2 == 0)
    sm = -pegs[0]
    if is_even:
        sm += pegs[-1]
    else:
        sm -= pegs[-1]

    if len(pegs) > 2:
        for index in range(1, len(pegs) - 1):
            sm += 2 * (-1)**(index + 1) * pegs[index]

    init_radius = Fraction(2 * (float(sm) / 3 if is_even else sm)).limit_denominator()

    cur = init_radius
    for index in range(len(pegs) - 2):
        center = pegs[index + 1] - pegs[index]
        nxt = center - cur
        if cur < 1 or nxt < 1:
            return [-1, -1]
        cur = nxt

    return [init_radius.numerator, init_radius.denominator]