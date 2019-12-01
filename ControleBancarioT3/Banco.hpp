//
//  Banco.hpp
//  Sistema de Controle Bancario
//
//  Created by Alice Diniz Ferreira and Paula Resende Teixeira on 10/2/19.
//  Copyright © 2019 trabalhoPOO. All rights reserved.
//

#ifndef Banco_hpp
#define Banco_hpp

#include <string>
#include <vector>
#include "Conta.hpp"
#include "Cliente.h"
#include "ContaCorrente.hpp"
#include "Poupanca.hpp"

using namespace std;


class Banco {
private:
    string nomeBanco;
    vector<Cliente> clientes;
    vector <ContaCorrente> contasCorrente;
    vector <Poupanca> poupancas;
    
    int findAccountIndex(int accountNumber, int tipoConta);
    int checkClientHasAccount(string documentNumber, int tipoConta);
    int findClient(string cpf_cnpj);
    
    
public:
    Banco(string bankName);
    void setBank(string bankName);

    // Metodos get
    vector <Cliente> getClientList ();
    vector <ContaCorrente> getCorrenteList ();
    vector <Poupanca> getPoupancaList ();
    
    // Funcoes
    void newClient (Cliente client);
    void newBankAccount (Cliente client);
    void newBankAccount (Cliente client, double creditLimit);
    void removeClient (string cpf_cnpj);
    void removeBankAccount (int accountNumber, int tipoConta);
    void newDeposit (int accountNumber, double value, string description = "Depósito");
    void newDeposit (int accountNumber, double value, int dataBase, string description = "Depósito");
    void newWithdraw (int accountNumber, double value, string description = "Saque");
    void newWithdraw (int accountNumber, double value, int dataBase, string description = "Saque");
    void newTransaction (int sourceAccountNumber, int destinationAccountNumber, double value, int tipoConta1 , int tipoConta2);
    void newFee (double value);
    void newTaxCPMF();
    void newSavingsIncome();
    double bankBalance (int accountNumber, int tipoConta);
    vector <Movimentacao> bankStatement(int accountNumber);
    vector <Movimentacao> bankStatement (int accountNumber, struct tm startTime);
    vector <Movimentacao> bankStatement (int accountNumber, struct tm startTime, struct tm endTime);
    
    void readFile(string fileName);
    void writeFile(string fileName, string operation, string text);
    
    void testeStatement();
    
};
#endif /* Banco_hpp */
