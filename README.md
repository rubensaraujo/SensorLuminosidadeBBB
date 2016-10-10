Sensor de Luminosidade com uso da BeagleBone Black
=============

Projeto para a disciplina de Sistemas Operacionais, do curso de Bacharelado em Tecnologia da Informação da UFRN.
Ele consiste em receber dados a partir de um FotoResistor LDR e modificar o brilho da tela do PC.

Requisitos
-------

0. Sistema Linux em sua máquina (Ubuntu de preferencia).
0. BeagleBone Black conectada com o seu computador
0. O programa 'sshpass' instalado em seu linux. Caso nao tenha, basta no terminal digitar `sudo apt-get install sshpass`

Configuração
-----------
* -- Copie o executavel `ledFoto` presente nesse repositório para a BeagleBone usando o comando: `scp ledFoto debian@192.168.7.2:~/Dev`

* -- Conecte sua BeagleBone no PC, usando o comando ssh: `ssh debian@192.168.7.2`
* -- Execute o `ledFoto` na BBB como root ou com `sudo ./ledFoto`
* -- Na sua maquina, execute em outro terminal o `brightness`


Compilação
-----
Caso queria realizar alguma modificação e compiliar basta seguir alguns passos:

0. Instale os seguintes programas no seu Linux: 
` sudo apt-get install libc6-armel-cross libc6-dev-armel-cross `
` sudo apt-get install binutils-arm-linux-gnueabi `
` sudo apt-get install libncurses5-dev `
` sudo apt-get install gcc-arm-linux-gnueabihf `
` sudo apt-get install g++-arm-linux-gnueabihf `

0. Compile usando o comando:
`arm-linux-gnueabihf-g++ -std=c++11 -o &nomedoexecutavel -static main.cpp BlackCore.cpp BlackGPIO/BlackGPIO.cpp`
