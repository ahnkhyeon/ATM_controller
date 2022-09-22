# ATM_controller
This is for ATM_controller sample code.

* MINIMUM CMAKE VERSION: CMAKE 3.10

* HOW TO BUILD
(1) run ./build.sh

* HOW TO EXECUTE
(1) ./ATM

* EXPLANATION
** If ATM is executed, you need to insert the account number. This is simulated process for insert card. 
** The account number and pin number are managed by using the database.txt
** If account number is not belong to database.txt or inserted pin number is different with the that stored in database.txt, you need to inser the account number again.
** If account number and pin number are matched, you can deposit, withdraw the money and show the account information. 
** When all of processes that you want to do by using the ATM, you can close the ATM by using the "exit" menu. If the ATM goes to exit, the database will be updated.
