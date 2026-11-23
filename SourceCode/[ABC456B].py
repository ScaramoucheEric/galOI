import itertools

def probability_exactly_4_5_6(dice_faces):
    counts = []
    for die in dice_faces:
        c4 = sum(1 for face in die if face == 4)
        c5 = sum(1 for face in die if face == 5)
        c6 = sum(1 for face in die if face == 6)
        counts.append([c4, c5, c6])
    
    perm_sum = 0
    for p0, p1, p2 in itertools.permutations([0, 1, 2]):
        perm_sum += counts[0][p0] * counts[1][p1] * counts[2][p2]
    
    probability = perm_sum / 216.0
    return probability

if __name__ == "__main__":
    dice_faces = []
    for _ in range(3):
        die = list(map(int, input().split()))
        dice_faces.append(die)
    
    result = probability_exactly_4_5_6(dice_faces)
    print(f"{result:.10f}")