import math

# Số bước của encoder (16,384 vị trí)
LUT_SIZE = 16384

# File lưu bảng sin và cos
sin_file = open("sin_lt_values.inc", "w")
cos_file = open("cos_lt_values.inc", "w")

# Hệ số để chuyển giá trị sin/cos thành số nguyên fixed-point
FIXED_POINT_SCALE = 32767  # 16-bit signed integer max value

# Tạo bảng sin và cos
for i in range(LUT_SIZE):
    # Tính góc hiện tại (tính từ 0 đến 2π)
    angle = 2 * math.pi * i / LUT_SIZE
    
    # Tính giá trị sin và cos
    sin_value = math.sin(angle)  # Tính sin(x) trong khoảng [-1.0, 1.0]
    cos_value = math.cos(angle)  # Tính cos(x) trong khoảng [-1.0, 1.0]
    
    # Chuyển sang fixed-point (tính giá trị int16_t)
    sin_fixed = int(sin_value * FIXED_POINT_SCALE)  # Nhân với 32767 để chuyển thành fixed-point
    cos_fixed = int(cos_value * FIXED_POINT_SCALE)  # Nhân với 32767 để chuyển thành fixed-point
    
    # Lưu giá trị vào file
    sin_file.write(f"{sin_fixed},\n")
    cos_file.write(f"{cos_fixed},\n")

# Đóng file
sin_file.close()
cos_file.close()

print("Bảng LUT sin/cos đã được tạo và lưu vào sin_lut_values.inc và cos_lut_values.inc.")
