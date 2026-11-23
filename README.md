# Gestão de Pets - Clínica Veterinária

**Disciplina:** Linguagem de Programação  
**Professor:** Marcos Roberto de Moraes

### Integrantes
- Mateus Henrique Emilio Santos - RA: 1630482613045
- Vinicius Henrique da Silva Malvezzi - RA: 1630482613032

## Sobre o projeto

Escolhemos o tema de Gestão de Pets e Clínica Veterinária por ser um assunto interessante e que permite trabalhar com diferentes tipos de dados.

Nossa ideia foi desenvolver um programa simples em C para cadastrar animais e consultar suas informações, utilizando os conteúdos estudados durante o semestre, principalmente estruturas, ponteiros e manipulação de arquivos.

## Desenvolvimento

Dividimos o projeto em três arquivos principais para organizar melhor o código.

O `main.c` contém o menu e controla as opções escolhidas pelo usuário. O `pet.h` possui a estrutura dos animais e as declarações das funções, enquanto o `pet.c` contém as funções utilizadas pelo programa.

O sistema permite cadastrar animais informando chip, nome, espécie, raça, idade e peso. Também é possível listar os animais cadastrados, buscar um registro pelo chip e consultar um relatório com algumas informações gerais.

Para armazenar os registros, utilizamos um vetor de 100 ponteiros. As posições começam com `NULL`, e a memória é alocada com `malloc` conforme os animais são cadastrados. Antes de encerrar, utilizamos `free` para liberar a memória.

Os dados ficam armazenados no arquivo `dados.txt`, permitindo que sejam recuperados quando o programa for aberto novamente.

### Divisão das atividades

Vinicius ficou responsável pela estrutura dos dados, leitura e gravação dos arquivos e desenvolvimento do relatório.

Mateus ficou responsável pelo menu principal, cadastro, busca e listagem dos animais.

Os testes e ajustes finais foram realizados em conjunto.

## Funcionalidades

1. Cadastrar um novo animal.
2. Listar todos os animais cadastrados.
3. Buscar um animal pelo número do chip.
4. Gerar um relatório com a quantidade de animais, peso médio e animal mais idoso.
5. Salvar os dados e encerrar o programa.

## Ajustes realizados

Durante o desenvolvimento, fizemos algumas alterações para melhorar o funcionamento do programa.

Organizamos o menu, adicionamos verificações para evitar informações inválidas e modificamos o cadastro de idade para aceitar anos e meses.

A idade é armazenada em meses, mas aparece convertida em anos e meses na consulta. Dessa forma, também conseguimos cadastrar animais com menos de um ano.

Uma das dificuldades foi trabalhar com a leitura dos dados, principalmente ao utilizar `scanf` e `fgets` no mesmo programa. Também tivemos que ajustar a leitura dos registros armazenados no arquivo de texto.

Consultamos materiais de apoio e utilizamos auxílio de IA em algumas dessas correções.

## Compilação e execução

Para executar o projeto, é necessário ter o compilador GCC instalado.

Com o terminal aberto na pasta do projeto, utilize:

**Windows:**
```bash
gcc main.c pet.c -o pets.exe
```

Depois execute:
```bash
pets.exe
```

**Linux:**
```bash
gcc main.c pet.c -o pets
./pets
```

O programa carrega os registros do arquivo `dados.txt` ao iniciar. Caso o arquivo não exista, começa sem nenhum animal cadastrado.

Para salvar as alterações, basta selecionar a opção 5 do menu.

## Arquivos do projeto

- `main.c` - Menu principal.
- `pet.c` - Funções do sistema.
- `pet.h` - Estrutura e declarações.
- `dados.txt` - Registros dos animais.
- `README.md` - Informações sobre o projeto.
