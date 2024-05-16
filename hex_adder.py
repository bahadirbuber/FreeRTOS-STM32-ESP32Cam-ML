base_address = 0xd0000000
mb_64 = 16 * 1024 * 1024  # 64 MB in bytes

new_address = base_address + mb_64

print("Base Address:", hex(base_address))
print("64 MB Added:", hex(mb_64))
print("New Address:", hex(new_address))

