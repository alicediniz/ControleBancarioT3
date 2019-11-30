//
//  Conta.cpp
//  Sistema de Controle Bancario
//
//  Created by Alice Diniz Ferreira and Paula Resende Teixeira on 10/1/19.
//  Copyright © 2019 trabalhoPOO. All rights reserved.
//
#include <string>
#include <vector>
#include "Conta.hpp"
#include "Cliente.h"

using namespace std;

// Conta::Conta(string name , string document, string address, string phone):cliente(name, document,address,phone){
//     setAccount(cliente);
// };

// void Conta::setAccount(Cliente client){
//     numConta = proximoNumConta;
//     saldo = 0;
//     cliente = client;
//     movimentacoes = {};
//     proximoNumConta++;
// };

// int Conta::getAccountNumber () {
//     return numConta;
// };

// double Conta::getBalance () {
//     return saldo;
// };
// Cliente Conta::getClient () {
//     return cliente;
// };

// vector <Movimentacao> Conta::getFinancialMovements() {
//     return movimentacoes;
// };

// void Conta::debit(string description, double value) {
//     double novoSaldo = saldo - value;
//     if (novoSaldo >= 0 || description == "Cobrança de tarifa" || description == "Cobrança de CPMF") {
//         saldo = novoSaldo;
//         Movimentacao newMov = Movimentacao(description, 'D', value);
//         movimentacoes.push_back(newMov);
//     }
//     else {
//         cout << "Saldo insuficiente para debito" << endl;
//     }
// };

// void Conta::credit (string description, double value) {
//     double novoSaldo = saldo + value;
//     saldo = novoSaldo;
//     Movimentacao newMov = Movimentacao(description, 'C', value);
//     movimentacoes.push_back(newMov);
// };

// vector <Movimentacao> Conta::getAccountBalance(){
//     return getFinancialMovements();
// };

// vector <Movimentacao> Conta::getAccountBalance(struct tm startTime){
//     vector <Movimentacao> movs = {};
//     vector <Movimentacao> accountMovs = getFinancialMovements();
//     if (accountMovs.empty()) {
//         return {};
//     }
//     else {
//         time_t timeNow = time(0);
//         for (auto v : accountMovs) {
//             struct tm movDate = v.getDate();
//             if ((mktime(&movDate) >= mktime(&startTime)) and (mktime(&movDate) <= timeNow)){
//                 movs.push_back(v);
//             }
//         }
//     }
//     return movs;
// };

// vector <Movimentacao> Conta::getAccountBalance(struct tm startTime, struct tm endTime){
//     vector <Movimentacao> movs = {};
//     vector <Movimentacao> accountMovs = getFinancialMovements();
//     if (accountMovs.empty()) {
//         return {};
//     }
//     else {
//         for (auto v : accountMovs) {
//             struct tm movDate = v.getDate();
//             if ((mktime(&movDate) >= mktime(&startTime)) and (mktime(&movDate) <= mktime(&endTime))){
//                 movs.push_back(v);
//             }
//         }
//     }
//     return movs;
// };



// int Conta::proximoNumConta = 0;



// void Conta::newMovTest (struct tm dataMov, string description, double value){
//     Movimentacao newMov = Movimentacao(description, 'T', value);
//     newMov.setMovimentation(dataMov, description, 'T', value);
//     movimentacoes.push_back(newMov);
//     cout << "Ola" << endl;
// };
