import numpy as np
import sympy as sp

# Question 2

# Defining symbols for derivatives and integrals
x = sp.Symbol('x')
y = sp.Symbol('y')
a = sp.Symbol('a')
b = sp.Symbol('b')
xa = sp.Symbol('xa')
yb = sp.Symbol('yb')
A0 = sp.Symbol('A0')
k = sp.Symbol('k')
x_bar = sp.Symbol('x_bar')
y_bar = sp.Symbol('y_bar')

# a11 w/out K0 * k (since they are constant and can be pulled out)
a11 = 1 - ((xa + x_bar) / (6 * a))

# Psi values
psi_1 = (1 - ((x - xa) / a) * (1 - ((y - yb) / b)))
psi_2 = ((x - xa) / a) * (1 - (yb / b))
psi_3 = ((x - xa) * (y - yb)) / (a * b)
psi_4 = (1 - ((x - xa) / a)) * ((y - yb) / b)

psi_array = np.array([psi_1, psi_2, psi_3, psi_4])


# Derivative function
def first_derivative(dy, dx):

    return sp.diff(dy, dx)


# Integral function
def integrate(dy, dx, lim_0, lim_1):

    return sp.integrate(dy, (dx, lim_0, lim_1))


# Loops through all locations in S11 (4X4, 16 in total) and prints the S11 value
for i in range(4):
    for j in range(4):

        integrand = a11 * first_derivative(psi_array[i], x) * first_derivative(psi_array[j], x)

        first_integral = integrate(integrand, x_bar, 0, xa)

        second_integral = integrate(first_integral, y_bar, 0, yb)

        print("S{}{}".format(i + 1, j + 1), "=", "(A0 * k) *", second_integral)


# Question 3

coordinate_matrix = np.array([[1, 1, 1], [2, 20, 17], [2, 1, 13]])
area_coors = np.array([1/6, 1/6, 2/3])
point = np.array([1, 10, 3])

global_coors = np.dot(coordinate_matrix, area_coors)
natural_coors = np.dot(np.linalg.inv(coordinate_matrix), point)

print("------------------------------------------------------")
print(global_coors)
print(natural_coors)

