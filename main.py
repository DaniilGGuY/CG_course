import matplotlib.pyplot as plt

fig = plt.subplots(figsize=(10, 8))
plt.title("Сравнение по времени")
plt.xlabel("Размер квадратной карты высот")
plt.ylabel("Время построения изображения, мс")
plt.plot([20, 60, 100, 140, 180, 220, 260, 300],
         [78, 94, 119, 163, 210, 235, 420, 480])
plt.show()