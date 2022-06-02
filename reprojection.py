import numpy as np
import cv2

src = cv2.imread("data/1.jpg", cv2.IMREAD_GRAYSCALE)
cv2.imshow('source', src)
cv2.waitKey(0)

width = src.shape[1]
height = src.shape[0]

fx1 = 10.0
fy1 = 10.0
cx1 = width / 2.0
cy1 = height / 2.0
lamb1 = 0.0

fx2 = 5.0
fy2 = 5.0
cx2 = 100
cy2 = 100
lamb2 = 0.1

img_convert = np.zeros_like(src)
XY = np.indices(src.shape, dtype=float)

XY[0] = (XY[0] - cx1) / fx1
XY[1] = (XY[1] - cy1) / fy1
Z = 1 + lamb1 * (((XY[0] - cx1) / fx1) ** 2 + ((XY[1] - cy1) / fy1) ** 2)

max_x = np.max(XY[0])
max_y = np.max(XY[1])

u = XY[0] / Z * fx2 * (1 + lamb2 * ((XY[0] / max_x) ** 2 + (XY[1] / max_y) ** 2)) + cx2
v = XY[1] / Z * fy2 * (1 + lamb2 * ((XY[0] / max_x) ** 2 + (XY[1] / max_y) ** 2)) + cy2

u[(u < 0)] = 0
u[u > width] = 0
v[(v < 0)] = 0
v[v > height] = 0

img_convert[u.astype(int), v.astype(int)] = src

cv2.imshow('dst', img_convert)
cv2.waitKey(0)
cv2.destroyAllWindows()
