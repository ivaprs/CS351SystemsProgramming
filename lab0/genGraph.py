import matplotlib.pyplot as plt

times, length = [],[]
for lines in open('timesGen.txt', 'r'):
	data = [float(i) for i in lines.split(" ")]
	times.append(data[0])
	length.append(data[1])
plt.plot(length, times, label = "Time to Generate")

times, length = [],[]
for lines in open('timesSort.txt', 'r'):
	data = [float(i) for i in lines.split(" ")]
	times.append(data[0])
	length.append(data[1])

plt.plot(length, times, label = "Time to Sort")
plt.xlabel("Length of File (lines)")
plt.ylabel("Time (seconds)")
plt.title("Length of File vs. Time to Generate/Sort")
plt.legend()
plt.show()
