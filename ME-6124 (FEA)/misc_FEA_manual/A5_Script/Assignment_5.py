import numpy as np
import sympy as sym
import math

# Problem 1

z_r2 = np.array([-(1 / math.sqrt(3)), (1 / math.sqrt(3))])
w_r2 = 1

z_r3 = np.array([0, -(3 / math.sqrt(5)), (3 / math.sqrt(5))])
w_r3 = np.array([8/9, 5/9, 5/9])

sum_storage_A = np.array([0.0, 0.0])
sum_storage_B = np.array([0.0, 0.0, 0.0])


def x_exact(t):

    return (t ** 2 / 2) - ((16 * math.cos(2 * t) * math.exp(-0.5 * t)) / 17) -\
           ((4 * math.sin(2 * t) * math.exp(-0.5 * t)) / 17)


def x_function(t):

    return t + math.sin(2 * t) * math.exp(-0.5 * t)


i = 0

while i < 2:

    sum_storage_A[i] = w_r2 * x_function(2 * z_r2[i] + 2)

    i = i + 1

print("Gauss Quadrature integration for r = 2:", 2 * sum(sum_storage_A))

while i < 3:

    sum_storage_B[i] = w_r3[i] * x_function(2 * z_r3[i] + 2)

    i = i + 1

print("Gauss Quadrature integration for r = 3:", 2 * sum(sum_storage_B))

print("Exact solution:", x_exact(4) - x_exact(0))

# Problem 2

Z = sym.Symbol('Z')
x = sym.Symbol('x')
h = sym.Symbol('h')
I0 = sym.Symbol('I0')
K12_store = np.array([0.0, 0.0])

dZ_dx = h / 2
psi_1 = 1 - (3 / 4) * (1 + Z) ** 2 + (1 / 4) * (1 + Z) ** 3
psi_2 = (-h / 4) * (1 + Z) ** 3
# I_x = math.cos(0.5 * ((h / 2) * (1 + Z)))


def first_derivative(dy, dx):

    return sym.diff(dy, dx)


def second_derivative(dy, dx):

    return sym.diff(sym.diff(dy, dx), dx)


d2_psi_1_dx_2 = second_derivative(psi_1, Z) * dZ_dx ** 2

d2_psi_2_dx_2 = second_derivative(psi_2, Z) * dZ_dx ** 2

print(d2_psi_1_dx_2 * d2_psi_2_dx_2)

i = 0

while i < 2:

    print(-0.0703125 * z_r2[i] * h ** 5 * (2 * z_r2[i] + 2))

    print((1 + z_r2[i])/4)

    i = i + 1

