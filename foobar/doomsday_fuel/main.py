from __future__ import division
from itertools import compress
from itertools import starmap
from operator import mul
import fractions


def convertMatrix(transMatrix):
    """Converts transition matrix values to floats representing probabilities."""
    probMatrix = []

    for i in range(len(transMatrix)):
        row = transMatrix[i]
        newRow = []
        rowSum = sum(transMatrix[i])

        if all([v == 0 for v in transMatrix[i]]):
            for j in transMatrix[i]:
                newRow.append(0)
            newRow[i] = 1
            probMatrix.append(newRow)
        else:
            for j in transMatrix[i]:
                if j == 0:
                    newRow.append(0)
                else:
                    newRow.append(j / rowSum)
            probMatrix.append(newRow)
    return probMatrix


def terminalStateFilter(matrix):
    terminalStates = []

    for row in range(len(matrix)):

        if all(x == 0 for x in matrix[row]):
            terminalStates.append(True)

        else:
            terminalStates.append(False)

    return terminalStates


def probDistributionVector(matrix, row, timesteps):
    vector = matrix[row]

    for i in range(timesteps):
        newVector = [sum(starmap(mul, zip(vector, col)))
                     for col in zip(*matrix)]
        vector = newVector

    return vector


def answer(m):
    if len(m) == 1:
        return [1, 1]
    probMatrix = convertMatrix(m)
    terminalStates = terminalStateFilter(m)
    probVector = probDistributionVector(probMatrix, 0, 100)

    numerators = []
    for i in probVector:
        numerator = fractions.Fraction(i).limit_denominator().numerator
        numerators.append(numerator)

    denominators = []
    for i in probVector:
        denominator = fractions.Fraction(i).limit_denominator().denominator
        denominators.append(denominator)

    factors = [max(denominators) / x for x in denominators]
    numeratorsTimesFactors = [a * b for a, b in zip(numerators, factors)]
    terminalStateNumerators = list(
        compress(numeratorsTimesFactors, terminalStates))

    # append numerators and denominator to answerList
    answerlist = []
    for i in terminalStateNumerators:
        answerlist.append(i)
    answerlist.append(max(denominators))

    return list(map(int, answerlist))
