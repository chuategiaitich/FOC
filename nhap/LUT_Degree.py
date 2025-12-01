# Python script tạo file .h siêu gọn (chỉ 1 bảng sin)
import math

SIZE = 3600
print("#ifndef FAST_TRIG_H")
print("#define FAST_TRIG_H\n")
print("#define TRIG_TABLE_SIZE {}U".format(SIZE))
print("const int16_t sin_cos_table_q15[{}] = {{".format(SIZE))

for i in range(SIZE):
    deg = i / 10.0
    rad = math.radians(deg)
    val = int(round(math.sin(rad) * 32767.0))
    val = max(-32768, min(32767, val))
    comma = "," if i < SIZE-1 else ""
    if i % 12 == 0: print("   ", end="")
    print("{:6d}{}".format(val, comma), end=" " if i % 12 != 11 and i != SIZE-1 else "\n")

print("};\n#endif")