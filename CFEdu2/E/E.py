import math
from decimal import *

getcontext().prec = 40
def areaOfIntersection(x0, y0, r0, x1, y1, r1):
    rr0 = r0 * r0
    rr1 = r1 * r1
    c = Decimal((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)).sqrt()
    phi = Decimal((math.acos((rr0 + (c * c) - rr1) / (2 * r0 * c))) * 2)
    theta = Decimal((math.acos((rr1 + (c * c) - rr0) / (2 * r1 * c))) * 2)
    area1 = Decimal(0.5) * theta * rr1 - Decimal(0.5) * rr1 * Decimal(math.sin(theta))
    area2 = Decimal(0.5) * phi * rr0 - Decimal(0.5) * rr0 * Decimal(math.sin(phi))
    return area1 + area2

x0, y0, r0 = input().split(' ')
x1, y1, r1 = input().split(' ')
x0 = Decimal(x0)
x1 = Decimal(x1)
y0 = Decimal(y0)
y1 = Decimal(y1)
r0 = Decimal(r0)
r1 = Decimal(r1)

try:
    print(areaOfIntersection(x0, y0, r0, x1, y1, r1))
except:
    print(0)
