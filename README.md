# Eletronic Lock System ✨

### Funcionalidades  🦾
O sistema de gerenciamento de catraca utiliza dois canais para realizar a liberação do usuário, via interface computacional e PIC (teclado e LCD). Nesses canais é possivel o usuario realizar o login como administrador com opções de gerenciamento dos alunos (CRUD) e login como usuario padrão para liberação da catraca. 

### PIC
- Todos os cadastros são gravados na memória interna.
- Um usuario contém: 2 digitos para senha, 4 digitos para ID, 1 digito para status, totalizando 7 posições na memoria.
- O status é condigurado da seguinte maneira: 0 - usuário não pagante, 1 - usuário pagante e 3 - administrador. 

### Interface computacional 🖥️
- Os dados são gravados no banco de dados SQLite.
- O banco de dados é formado por três colunas: senha, id e status.

![image](https://user-images.githubusercontent.com/53872016/143886627-31956f61-e6c4-4b39-80b2-b31c6c31dcc0.png)


### Comunicação 📤
- A comunicação entre a interface e o PIC é realizada via comunicação serial
- Em ambos os canais, possuem opção para realizar envio e recebido de dados (entre os canais).
- Comunicação não finalizada 🚧

### Tecnologias aplicadas 🛠
- PIC16F877A
- CCS Compiler
- SQLite
- Qt Desginer
- PyQt5

#### Equipe 📚
- André Geraldo
- Danubia Macedo
