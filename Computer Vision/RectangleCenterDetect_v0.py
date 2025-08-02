import sensor
# import math
# import display


def detect_x_edges(img):
    blobs = img.find_blobs([(0, 10)], area_threshold=100, merge=True)

    if not blobs:
        return False, 0, 0, 0, 0

    graph = max(blobs, key=lambda b: b.area())
    left_x = graph.x()
    right_x = graph.x() + graph.w() - 1

    # 更精确地获取左右边缘的Y坐标
    # 在左边缘列上扫描Y值
    left_y_sum, left_count = 0, 0
    for y in range(graph.y(), graph.y() + graph.h()):
        if img.get_pixel(left_x, y) < 4:
            left_y_sum += y
            left_count += 1
    left_y = left_y_sum // left_count if left_count > 0 else graph.cy()

    # 在右边缘列上扫描Y值
    right_y_sum, right_count = 0, 0
    for y in range(graph.y(), graph.y() + graph.h()):
        if img.get_pixel(right_x, y) < 4:
            right_y_sum += y
            right_count += 1
    right_y = right_y_sum // right_count if right_count > 0 else graph.cy()

    # 绘制轮廓和边缘点
    img.draw_rectangle(graph.rect(), color=(0, 255, 0))
    img.draw_circle(left_x, left_y, 4, color=(0, 255, 255))
    img.draw_circle(right_x, right_y, 4, color=(0, 255, 255))

    return left_x, left_y, right_x, right_y


def detect_y_edges(img):
    blobs = img.find_blobs([(0, 10)], area_threshold=100, merge=True)

    if not blobs:
        return False, 0, 0, 0, 0

    graph = max(blobs, key=lambda b: b.area())
    top_y = graph.y()
    bottom_y = graph.y() + graph.h() - 1

    # 扫描顶部边缘行（Y最小）获取X坐标
    top_x_sum, top_count = 0, 0
    for x in range(graph.x(), graph.x() + graph.w()):
        if img.get_pixel(x, top_y) < 4:
            top_x_sum += x
            top_count += 1
    top_x = top_x_sum // top_count if top_count > 0 else graph.cx()

    # 扫描底部边缘行（Y最大）获取X坐标
    bottom_x_sum, bottom_count = 0, 0
    for x in range(graph.x(), graph.x() + graph.w()):
        if img.get_pixel(x, bottom_y) < 4:
            bottom_x_sum += x
            bottom_count += 1
    bottom_x = bottom_x_sum // bottom_count if bottom_count > 0 else graph.cx()

    # 绘制轮廓和边缘点
    img.draw_circle(top_x, top_y, 4, color=(0, 255, 255))
    img.draw_circle(bottom_x, bottom_y, 4, color=(0, 255, 255))

    return top_x, top_y, bottom_x, bottom_y

sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
sensor.set_auto_exposure(True)
sensor.set_brightness(-1)
sensor.set_framesize(sensor.VGA)
sensor.skip_frames(time=1000)

while True:
    img = sensor.snapshot()

    # Exclude outer edges
    y = 0
    for y in range(40):
        img.draw_line((0, y, 640, y))
        y += 1
    y = 440
    for y in range(440, 480):
        img.draw_line((0, y, 640, y))
        y += 1
    del(y)

    x_left, y_left, x_right, y_right = detect_x_edges(img)
    x_top, y_top, x_bottom, y_bottom = detect_y_edges(img)

    x_center = (x_left + x_right) / 2
    y_center = (y_top + y_bottom) / 2

    img.draw_circle(int(x_center), int(y_center), 10, color=(255, 255, 255))
    img.draw_cross(int(x_center), int(y_center), color=(255, 255, 255))

    img.draw_line(int(x_left), int(y_left), int(x_right), int(y_right), color=(255, 255, 255))
    img.draw_line(int(x_top), int(y_top), int(x_bottom), int(y_bottom), color=(255, 255, 255))
