#include <stdlib.h>
#include <math.h>

#include "atm.h"

ATM *atm_create() {
    ATM *atm = (ATM *) malloc(sizeof(ATM));
    memset(atm, 0, sizeof(ATM));
    atm->value[0] = 20;
    atm->value[1] = 50;
    atm->value[2] = 100;
    atm->value[3] = 200;
    atm->value[4] = 500;
    return atm;
}

void atm_deposit(ATM *obj, int *banknotesCount, int banknotesCountSize) {
    for (int i = 0; i < 5; ++i) {
        obj->count[i] += banknotesCount[i];
    }
}

int *atm_withdraw(ATM *obj, int amount, int *returnSize) {
    int *res = (int *) malloc(sizeof(int) * 5);
    *returnSize = 5;
    for (int i = 4; i >= 0; --i) {
        res[i] = fmin(obj->count[i], amount / obj->value[i]);
        amount -= res[i] * obj->value[i];
    }

    if (amount) {
        res = (int *) malloc(sizeof(int));
        *returnSize = 1;
        res[0] = -1;
        return res;
    } else {
        for (int i = 0; i < 5; ++i) {
            obj->count[i] -= res[i];
        }
        return res;
    }
}

void atm_free(ATM *obj) {
    free(obj);
}
