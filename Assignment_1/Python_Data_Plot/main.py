import matplotlib.pyplot as plt
import numpy as np

body_mass_raw = [4.22*pow(10, -4), 4.50*pow(10, -4), 3.90*pow(10, -4), 0.0138, 5.22*pow(10, -6),
                 6.86*pow(10, -6), 1.30*pow(10, -6), 1.76*pow(10, -7), 7.47*pow(10, -7), 7.89*pow(10, -8),
                 2.05*pow(10, -7), 9.00*pow(10, -5), 1.70*pow(10, -4), 0.0015, 4.73*pow(10, -5), 0.002,
                 0.002, 6.52*pow(10, -5), 1.01*pow(10, -4)]

max_speed_raw = [36, 27, 25.92, 36, 6.48, 4.8, 3.6, 3.24, 6.84, 3.06, 4.32, 36, 36, 25.56, 6, 19.08, 18, 10.8, 23.76]

body_mass = np.log(body_mass_raw)

max_speed = np.log(max_speed_raw)

x = np.arange(-18, 2, 0.0001)
y = 4.809 + 0.227*x

plt.scatter(body_mass, max_speed, color='r')
plt.xlabel("ln(body mass [kg])")
plt.ylabel("ln(max speed [km/hr])")
plt.title("Natural Log of Body Mass vs. Natural Log of Max Speed with Linear Plot Using Calculated k1 & k0")
plt.plot(x, y)
plt.show()
