import xlsxwriter

# The writing directory; this is where the .xlsx file will be written to.
wb = xlsxwriter.Workbook('E:\GT_Courses\Semester_1\ME-6124\Project\Online_Data\XLSX_Data\Running\Running_Data.xlsx')

# The reading directory; this is where the .txt file is located (make sure to include the .txt file in the address).
f = open('E:\GT_Courses\Semester_1\ME-6124\Project\Online_Data\Orthoload_Data\Running\h4l_080116_2_186.akf.txt')

# Initializes xlsxwriter
data_sheet = wb.add_worksheet()
r = f.readlines()

body_weight = float(str(r[10]).split("\t")[1].replace(",", '.'))  # Reads body weight of patient (data specific)
test_weight = 882.9  # Test subject weight

# Writes labels for excel document.
data_sheet.write(0, 0, "Stumbling")  # This will have to be modified based on what activity is occurring.
data_sheet.write(0, 1, "Patient Weight: " + str(body_weight) + " [N]")
data_sheet.write(0, 2, "Test Subject Weight: " + str(test_weight) + " [N]")
data_sheet.write(0, 3, "Angle of Rotation [deg]:")
data_sheet.write(0, 4, (str(r[16]).split("\t")[1].replace(",", '.')))
data_sheet.write(0, 5, (str(r[16]).split("\t")[2].replace(",", '.')))
data_sheet.write(0, 6, (str(r[16]).split("\t")[3].replace(",", '.')))
data_sheet.write(1, 0, (str(r[32]).split("\t")[0].replace(",", '.')))
data_sheet.write(1, 1, (str(r[32]).split("\t")[1].replace(",", '.')))
data_sheet.write(1, 2, (str(r[32]).split("\t")[2].replace(",", '.')))
data_sheet.write(1, 3, (str(r[32]).split("\t")[3].replace(",", '.')))
data_sheet.write(1, 4, (str(r[32]).split("\t")[4].replace(",", '.')))

# print((str(r[32]).split("\t")[1].replace(",", '.')))

z = 2  # Keeps track of rows.
count = 0  # Keeps track of loop count.
skip = 10  # Determines how often data points are "skipped." If skip == 1, all data is written.
# If skip == 10, every 10th data point is written. The first and last time points will always be written.
time_floor = 2.13  # The start of the desired time window
time_ceiling = 2.90  # The end of the desired time window

# Walking: 2.620 - 3.506
# Running: 2.13 - 2.90
# Jumping: 4.091 - 4.612
# Stairs: 1.471 - 2.569
# Cycling: 2.224 - 3.098
# Stumbling: 0.652 - 1.172

# Reads/writes data.
for i in range(len(r)):

    if i > 34 and time_floor <= float(str(r[i]).split("\t")[0]) <= time_ceiling:

        count = count + 1

        # print(float(str(r[i]).split("\t")[0]))  # Prints time

        if float(str(r[i]).split("\t")[0]) == time_floor or float(str(r[i]).split("\t")[0]) == time_ceiling or count == skip:

            # print(float(str(r[i]).split("\t")[0]))  # Prints time
            data_sheet.write(z, 0, float(str(r[i]).split("\t")[0]))
            data_sheet.write(z, 1, (float(str(r[i]).split("\t")[1])) / body_weight * test_weight)
            data_sheet.write(z, 2, (float(str(r[i]).split("\t")[2])) / body_weight * test_weight)
            data_sheet.write(z, 3, (float(str(r[i]).split("\t")[3])) / body_weight * test_weight)
            data_sheet.write(z, 4, (float(str(r[i]).split("\t")[4])) / body_weight * test_weight)

            z = z + 1

        if count == skip:

            count = 0

wb.close()
