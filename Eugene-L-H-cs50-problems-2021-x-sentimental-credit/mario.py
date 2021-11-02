# pyramid height
while True:
    try:
        hi = int(input("Height: "))
        if hi < 1 or hi > 8:
            continue
        else:
            break
    except ValueError:
        continue

# build pyramid
for i in range(1, hi + 1):
    print((" " * (hi - i)) + ("#" * i) + ("  " + "#" * i))