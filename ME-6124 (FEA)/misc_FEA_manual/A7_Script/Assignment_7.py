import numpy as np
import sympy as sp
import math

x_nodes = np.array([0, 2, 2, 1])
y_nodes = np.array([0, 0, 1, 1])
node_array = np.array([[1, 1, 1, 1], [1, 1, 1, 1], [0, 2, 2, 1], [0, 0, 1, 1]])

zeta_OG = 0.333
mu_OG = 0

coordinate_array = np.array([[1], [1], [1.5], [0.5]])

zeta = sp.Symbol('zeta')
mu = sp.Symbol('mu')


# Derivative function
def first_derivative(dy, dx):

    return sp.diff(dy, dx)


# Integral function
def integrate(dy, dx, lim_0, lim_1):

    return sp.integrate(dy, (dx, lim_0, lim_1))


def psi_1(z, m):

    psi = (1 / 4) * (1 - z) * (1 - m)

    return psi


def psi_2(z, m):
    psi = (1 / 4) * (1 + z) * (1 - m)

    return psi


def psi_3(z, m):
    psi = (1 / 4) * (1 + z) * (1 + m)

    return psi


def psi_4(z, m):
    psi = (1 / 4) * (1 - z) * (1 + m)

    return psi


x_coordinate = x_nodes[0] * psi_1(zeta_OG, mu_OG) + x_nodes[1] * psi_2(zeta_OG, mu_OG)\
               + x_nodes[2] * psi_3(zeta_OG, mu_OG) + x_nodes[3] * psi_4(zeta_OG, mu_OG)

y_coordinate = y_nodes[0] * psi_1(zeta_OG, mu_OG) + y_nodes[1] * psi_2(zeta_OG, mu_OG)\
               + y_nodes[2] * psi_3(zeta_OG, mu_OG) + y_nodes[3] * psi_4(zeta_OG, mu_OG)

temp = 100 * psi_1(0, 0) + 130 * psi_2(0, 0) + 170 * psi_3(0, 0) + 140 * psi_4(0, 0)

print('temp:', temp)

dx_dz = x_nodes[0] * first_derivative(psi_1(zeta, mu), zeta) + x_nodes[1] * first_derivative(psi_2(zeta, mu), zeta)\
        + x_nodes[2] * first_derivative(psi_3(zeta, mu), zeta) + x_nodes[3] * first_derivative(psi_4(zeta, mu), zeta)

dx_dm = x_nodes[0] * first_derivative(psi_1(zeta, mu), mu) + x_nodes[1] * first_derivative(psi_2(zeta, mu), mu)\
        + x_nodes[2] * first_derivative(psi_3(zeta, mu), mu) + x_nodes[3] * first_derivative(psi_4(zeta, mu), mu)

dy_dz = y_nodes[0] * first_derivative(psi_1(zeta, mu), zeta) + y_nodes[1] * first_derivative(psi_2(zeta, mu), zeta)\
        + y_nodes[2] * first_derivative(psi_3(zeta, mu), zeta) + y_nodes[3] * first_derivative(psi_4(zeta, mu), zeta)

dy_dm = y_nodes[0] * first_derivative(psi_1(zeta, mu), mu) + y_nodes[1] * first_derivative(psi_2(zeta, mu), mu)\
        + y_nodes[2] * first_derivative(psi_3(zeta, mu), mu) + y_nodes[3] * first_derivative(psi_4(zeta, mu), mu)

print(dx_dz)
print(dx_dm)
print(dy_dz)
print(dy_dm)

det = 1 / (0.375 - 0.125 * mu)

print(det * dx_dz)
print(det * dx_dm)
print(det * dy_dz)
print(det * dy_dm)

print(first_derivative(psi_1(zeta, mu), zeta))
print(first_derivative(psi_1(zeta, mu), mu))
print(first_derivative(psi_4(zeta, mu), zeta))
print(first_derivative(psi_4(zeta, mu), mu))


def gauss(zi, mj):

    gauss_solved = ((1 + (0.5 * ((zi * 3 - zi * mj + mj + 5) / 4))) * ((-4 / (mj - 3)) * ((-1 / 4) * (1 - mj)))
                    * ((-4 / (mj - 3)) * ((1 / 4) * (-1 - mj))) * (0.375 - 0.125 * mj) * 1 * 1)

    return gauss_solved


gauss_sum = gauss(-1/math.sqrt(3), -1/math.sqrt(3)) + gauss(1/math.sqrt(3), -1/math.sqrt(3))\
            + gauss(1/math.sqrt(3), 1/math.sqrt(3)) + gauss(-1/math.sqrt(3), 1/math.sqrt(3))

print(gauss_sum)

analytical_integral = integrate(integrate(((1 + 0.5 * (x_nodes[0] * psi_1(zeta, mu) + x_nodes[1] * psi_2(zeta, mu)
                                            + x_nodes[2] * psi_3(zeta, mu) + x_nodes[3] * psi_4(zeta, mu)))
                                           * ((-4 / (mu - 3)) * ((mu - 1) / 4)) * ((-4 / (mu - 3)) * ((-mu - 1) / 4))
                                           * (0.375 - 0.125 * mu) * 1 * 1), zeta, -1, 1), mu, -1, 1)

print(analytical_integral)

# Question 3

displacement_array = math.e**-2 * np.array([[0, 0], [-0.162, -0.625], [-0.163, -1.386],
                                            [0, -0.217], [0.303, -0.577], [0.363, -1.326]])


def find_centroid_triangle(n1, n2, n3, x1, x2, x3, y1, y2, y3):

    centroid = np.array([[1, 1, 1], [x1, x2, x3], [y1, y2, y3]]).dot(np.array([[n1], [n2], [n3]]))

    return centroid


def find_area_coordinates(cent, x1, x2, x3, y1, y2, y3):

    area_c = np.linalg.inv(np.array([[1, 1, 1], [x1, x2, x3], [y1, y2, y3]])).dot(cent)

    return area_c


def calculate_b(x1, x2, x3, y1, y2, y3):

    b = 1 / (2 * 0.5) * np.array([[y2 - y3, 0, y3 - y1, 0, y1 - y2, 0],
                                  [0, x3 - x2, 0, x1 - x3, 0, x2 - x1],
                                  [x3 - x2, y2 - y3, x1 - x3, y3 - y1, x2 - x1, y1 - y2]])

    return b


centroid_1 = find_centroid_triangle(1/3, 1/3, 1/3, 0, 1, 1, 0, 0, 1)
centroid_2 = find_centroid_triangle(1/3, 1/3, 1/3, 0, 1, 0, 0, 1, 1)
centroid_3 = find_centroid_triangle(1/3, 1/3, 1/3, 1, 2, 1, 0, 0, 1)
centroid_4 = find_centroid_triangle(1/3, 1/3, 1/3, 2, 2, 1, 0, 1, 1)

print(centroid_1)
print(centroid_2)
print(centroid_3)
print(centroid_4)
print('------------------------------')

area_coordinates_e1 = find_area_coordinates(centroid_1, 0, 1, 1, 0, 0, 1)
area_coordinates_e2 = find_area_coordinates(centroid_2, 0, 1, 0, 0, 1, 1)
area_coordinates_e3 = find_area_coordinates(centroid_3, 1, 2, 1, 0, 0, 1)
area_coordinates_e4 = find_area_coordinates(centroid_4, 2, 2, 1, 0, 1, 1)

print(area_coordinates_e1)
print(area_coordinates_e2)
print(area_coordinates_e3)
print(area_coordinates_e4)
print('------------------------------')

N_matrix = np.array([[1/3, 0, 1/3, 0, 1/3, 0], [0, 1/3, 0, 1/3, 0, 1/3]])

d1 = np.array([[displacement_array[0][0]], [displacement_array[0][1]], [displacement_array[1][0]],
               [displacement_array[1][1]], [displacement_array[4][0]], [displacement_array[4][1]]])

d2 = np.array([[displacement_array[0][0]], [displacement_array[0][1]], [displacement_array[4][0]],
               [displacement_array[4][1]], [displacement_array[3][0]], [displacement_array[3][1]]])

d3 = np.array([[displacement_array[1][0]], [displacement_array[1][1]], [displacement_array[2][0]],
               [displacement_array[2][1]], [displacement_array[4][0]], [displacement_array[4][1]]])

d4 = np.array([[displacement_array[3][0]], [displacement_array[3][1]], [displacement_array[5][0]],
               [displacement_array[5][1]], [displacement_array[4][0]], [displacement_array[4][1]]])

uv1 = N_matrix.dot(d1)
uv2 = N_matrix.dot(d2)
uv3 = N_matrix.dot(d3)
uv4 = N_matrix.dot(d4)

print(uv1)
print(uv2)
print(uv3)
print(uv4)
print('------------------------------')

E1 = calculate_b(0, 1, 1, 0, 0, 1).dot(d1)
E2 = calculate_b(0, 1, 0, 0, 1, 1).dot(d2)
E3 = calculate_b(1, 2, 1, 0, 0, 1).dot(d3)
E4 = calculate_b(2, 2, 1, 0, 1, 1).dot(d4)

print(E1)
print(E2)
print(E3)
print(E4)
print('------------------------------')

print(calculate_b(0, 1, 1, 0, 0, 1))
print(calculate_b(1, 2, 1, 0, 0, 1))
