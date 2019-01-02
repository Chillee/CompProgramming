normal = ['great', "don't think so", "don't touch me",
          "not bad", "cool"]
grumpy = ["don't even", "are you serious", "go die in a hole",
          "worse", "terrible", "noway"]
for i in range(10):
    print(i, flush=True)
    v = input().lower()
    done = False
    for w in normal:
        if w in v:
            print("normal")
            done = True
            break
    for w in grumpy:
        if w in v:
            print("grumpy")
            done = True
            break
    if done:
        break
