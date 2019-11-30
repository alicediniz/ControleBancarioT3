//
//  Poupanca.hpp
//  Sistema de Controle Bancario
//
//  Created by Alice Diniz Ferreira and Paula Resende Teixeira on 11/30/2019.
//  Copyright © 2019 trabalhoPOO. All rights reserved.
//

#include <string>
#include <vector>
#include "Conta.hpp"
#include "Poupanca.hpp"
#include "Cliente.h"

using namespace std;

Poupanca::Poupanca(string name , string document, string address, string phone, double limit):Conta(name, document, address, phone) {
    saldoPoupanca = {};
    setAccount(cliente);
};

void Poupanca::setAccount(Cliente client){
    numConta = proximoNumConta;
    saldo = 0;
    cliente = client;
    movimentacoes = {};
    proximoNumConta++;
};

double Poupanca::getBalance (){
    double savings = 0;
    for (auto balance : saldoPoupanca) {
        savings = savings + balance.getValue();
    }
    return savings;
}

int Poupanca::findBaseDateSaving(int baseDate) {
    for (int j= 0; j< saldoPoupanca.size(); j++ ) {
        if (saldoPoupanca[j].getDate() == baseDate) {
            return saldoPoupanca[j].getValue();
        }
    }
    return -1;
}

int Poupanca::checkBaseDate(int baseDate) {
    for (int j= 0; j< saldoPoupanca.size(); j++ ) {
        if (saldoPoupanca[j].getDate() == baseDate) {
            return j;
        }
    }
    return -1;
}

void Poupanca::debit(string description, double value, int baseDate) {
    int valorInicial = value;
    int novoSaldo = 0;
    int datePosition = 0;

    if (baseDate == 29 || baseDate == 30 || baseDate == 31){
        baseDate = 28;
    }

        while (value > 0) {
            datePosition = checkBaseDate(baseDate);
            if (datePosition != -1) {
                novoSaldo = findBaseDateSaving(baseDate) - value;
                if (novoSaldo < 0){
                    saldoPoupanca[datePosition].setValue(0);
                    value = novoSaldo*(-1);
                    baseDate = baseDate - 1;
                }
                else {
                    saldoPoupanca[datePosition].setValue(novoSaldo);
                }
            }
            else {
                baseDate = baseDate - 1;
            }

            if(baseDate <= 0){
                throw ExceptionClass(1);
            }
        }

        Movimentacao newMov = Movimentacao(description, 'D', valorInicial);
        movimentacoes.push_back(newMov);
    }
    catch {
        throw ExceptionClass(1);
    }
    
};

void Poupanca::credit (string description, double value, int baseDate) {
    int novoSaldo = 0;

    if (baseDate == 29 || baseDate == 30 || baseDate == 31){
        baseDate = 28;
    }

    int datePosition = checkBaseDate(baseDate);

    if (datePosition != -1) {
        novoSaldo = findBaseDateSaving(baseDate) + value;
        saldoPoupanca[datePosition].setValue(novoSaldo);
    }
    else {
        SaldoDiaBase newSaving = SaldoDiaBase(baseDate, value);
        saldoPoupanca.push_back(newSaving);
    }

    Movimentacao newMov = Movimentacao(description, 'C', value);
    movimentacoes.push_back(newMov);
};

