#include <stdio.h>
#include <string.h>
int c[100][10000];
int coins[5] = {1, 5, 10, 25, 50};

int count(int amount, int coin_index) {
    if (c[coins[coin_index]][amount] != -1)
        return c[coins[coin_index]][amount];

    else if (coin_index == 0 || amount == 0)
        return c[coins[coin_index]][amount] = 1;

    else if (amount < 0)
        return 0;

    else if (amount < coins[coin_index])
        return c[coins[coin_index]][amount] = count(amount, coin_index - 1);

    else
        return c[coins[coin_index]][amount] =
                   count(amount, coin_index - 1) + count(amount - coins[coin_index], coin_index);
}

int main() {
    // freopen("input.txt","r",stdin);
    memset(c, -1, sizeof(c));
    int i;
    for (i = 0; i < 5; i++)
        c[coins[i]][0] = 1;

    int amount;
    while (scanf("%d", &amount) != EOF)
        printf("%d\n", count(amount, 4));
}