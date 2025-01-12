#pragma once

typedef struct {
    long long count[5];
    long long value[5];
} ATM;

ATM *atm_create();
void atm_deposit(ATM *obj, int *banknotesCount, int banknotesCountSize);
int *atm_withdraw(ATM *obj, int amount, int *returnSize);
void atm_free(ATM *obj);
