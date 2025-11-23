import math
import struct

# ==============================
# Cấu hình
# ==============================
BITS = 14
SIZE = 1 << BITS          # 16384
SCALE = 8192.0             # Q14: nhân với 8192 → -8192 ... +8191

OUTPUT_FILE_H   = "as5048a_lut_14bit.h"
OUTPUT_FILE_BIN = "as5048a_lut_14bit.bin"

# ==============================
# Tạo bảng sin và cos (ép kiểu int rõ ràng)
# ==============================
sin_lut = []
cos_lut = []

print(f"Đang tạo LUT {BITS}-bit ({SIZE} phần tử)...")

for i in range(SIZE):
    angle_deg = i * 360.0 / SIZE
    angle_rad = math.radians(angle_deg)

    sin_val = math.sin(angle_rad)
    cos_val = math.cos(angle_rad)

    # Ép kiểu int ngay lập tức để tránh lỗi format sau này
    sin_q14 = int(round(sin_val * SCALE))
    cos_q14 = int(round(cos_val * SCALE))

    # Clamp chắc chắn trong khoảng signed 14-bit
    sin_q14 = max(-8192, min(8191, sin_q14))
    cos_q14 = max(-8192, min(8191, cos_q14))

    sin_lut.append(sin_q14)
    cos_lut.append(cos_q14)

print("Hoàn tất tính toán LUT.")

# ==============================
# Ghi file header C (.h)
# ==============================
with open(OUTPUT_FILE_H, "w", encoding="utf-8") as f:
    f.write("/**\n")
    f.write(" * AS5048A 14-bit Sin/Cos LUT (Q14 fixed-point)\n")
    f.write(f" * Size: {SIZE} entries\n")
    f.write(" * Format: signed 14-bit (-8192 ... +8191) = value * 8192\n")
    f.write(" * Generated automatically - OK to regenerate\n")
    f.write(" */\n\n")
    f.write("#ifndef AS5048A_LUT_14BIT_H\n")
    f.write("#define AS5048A_LUT_14BIT_H\n\n")
    f.write("#include <stdint.h>\n\n")
    f.write(f"#define LUT_SIZE {SIZE}\n\n")

    # Sin table
    f.write("const int16_t sin_lut[LUT_SIZE] = {\n")
    for i in range(SIZE):
        if i % 12 == 0:
            f.write("   ")
        f.write(f"{sin_lut[i]:6d}")
        if i < SIZE-1:
            f.write(",")
            if (i+1) % 12 == 0:
                f.write("\n")
            else:
                f.write(" ")
        else:
            f.write("\n")
    f.write("};\n\n")

    # Cos table
    f.write("const int16_t cos_lut[LUT_SIZE] = {\n")
    for i in range(SIZE):
        if i % 12 == 0:
            f.write("   ")
        f.write(f"{cos_lut[i]:6d}")
        if i < SIZE-1:
            f.write(",")
            if (i+1) % 12 == 0:
                f.write("\n")
            else:
                f.write(" ")
        else:
            f.write("\n")
    f.write("};\n\n")

    f.write("#endif // AS5048A_LUT_14BIT_H\n")

print(f"Đã ghi file header: {OUTPUT_FILE_H}")

# ==============================
# Ghi file binary (64KB)
# ==============================
with open(OUTPUT_FILE_BIN, "wb") as f:
    for i in range(SIZE):
        f.write(struct.pack("<h", sin_lut[i]))  # little-endian int16
        f.write(struct.pack("<h", cos_lut[i]))

print(f"Đã ghi file binary 64KB: {OUTPUT_FILE_BIN}")
print("Xong! LUT sẵn sàng dùng cho STM32, ESP32, Arduino hoặc FPGA.")