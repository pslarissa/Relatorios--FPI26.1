RELATÓRIO da LISTA 4

QUESTÃO 1 A fuga de Rebeka

Esse código deixa a entender, à primeira vista, que pode até parecer simples, mas na realidade me exigiu um raciocínio a mais.
A minha principal dificuldade foi pensar na melhor forma de encontrar o menor caminho, porque a questão obriga a pensar de uma forma mais elaborada, no caso a busca em largura.
Outro ponto que deu trabalho foi organizar bem as estruturas auxiliares, como a matriz de distâncias e o controle de posições já visitadas. É fácil se perder ou esquecer alguma verificação, principalmente nos limites da matriz ou nas condições de parada, por isso exigiu mais atenção.
No geral, foi um código de dificuldade média, e pedi ajuda a IAs como ChatGPT e Gemini para entender melhor os tópicos onde tive mais dificuldade.

QUESTÃO 2 MARQUINHOS E A GOTEIRA

Esse código já trouxe uma proposta bem diferente da primeira questão, já que aqui não é mais sobre achar caminho, mas sim simular um comportamento físico.
Onde mais tive dificuldade foi em traduzir o movimento da água. Esse tipo de código exige várias verificações, onde eu acabava me perdendo.
Outro ponto que complica um pouco é o controle do fluxo ao longo das linhas. Como a água vai se espalhando e influenciando posições futuras, é importante percorrer a matriz na ordem correta, de cima para baixo, e tomar cuidado para não sobrescrever informações de forma errada.
Foi uma questão considerada difícil, mas principalmente trabalhosa por conta da quantidade de verificações.

QUESTÃO 3 INVESTIMENTOS N3

Esse código foi mais tranquilo em comparação com os anteriores, pois a lógica é mais direta e envolve basicamente acompanhar os movimentos dentro de uma matriz.
A principal dificuldade foi ter atenção com as coordenadas, principalmente na relação entre linha e coluna com X e Y na saída. Isso pode confundir um pouco no início e gerar erros simples. Também foi importante cuidar dos limites da matriz, garantindo que os movimentos não saíssem do espaço 4x4. Além disso, a parte de contar quantas vezes cada posição foi visitada exigiu atenção na hora de percorrer a matriz para encontrar o maior valor.
Foi uma questão em que eu entendi o que precisava ser feito, mas acredito que não consegui aplicar isso no código tão bem quanto deveria. Tentei procurar ajuda no Gemini para entender o que estava errando, já que a questão não passou em todos os test cases para ser enviada com sucesso. Porém, nenhuma IA conseguiu me ajudar a encontrar exatamente o que precisava ser corrigido. Como passou em vários testes, acabei não me aprofundando tanto. Foi aquele tipo de questão em que você entende a ideia, mas tem dificuldade na implementação.

QUESTÃO 4 ENFEITE NA PRAÇA

Esse código foi um pouco mais tranquilo de entender no começo, mas ainda assim exigiu bastante atenção na implementação.
A principal dificuldade foi garantir que cada poste influenciasse corretamente as posições ao seu redor, principalmente separando bem o que era diagonal x e o que era lateral +. Além disso, tive que tomar cuidado com a regra de prioridade, onde o + deve sobrescrever o x, o que poderia causar confusão se não fosse bem organizado, nessa parte contei com ajuda de IA.
Resumindo, foi uma questão de dificuldade média, mais focada em organização da lógica e atenção às regras do enunciado. Não é um código muito complexo e conseguiu passar em todos os test cases na primeira tentativa.
