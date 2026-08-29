#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream> //usada para ler arquivos
#include <ostream> //usada para escrever arquivos
#include <iostream>
#include <SFML/Audio.hpp>
#include <string>

std::string arquiv = "save";

int maxScore = 0;

std::ifstream arquivo(arquiv);

sf::Texture retornaTextura(std::string s) {
    sf::Texture texture;
    if (!texture.loadFromFile(s)) {
        std::cout << "Erro lendo imagem: " << s << "\n";
    }
    return texture;
}

sf::SoundBuffer retornaSom(std::string s) {
    sf::SoundBuffer som;
    if (!som.loadFromFile(s)) {
        std::cout << "Erro lendo som: " << s << "\n";
    }
    return som;
}

const int linhas = 42;
const int colunas = 39;


char mapa[42][40] = {
  "111111111111111111111111111111111111111",
  "155555555555555555515555555555555555551",
  "153000000000000000515000000000000000351",
  "150555555055555550515055555550555555051",
  "150511115051111150515051111150511115051",
  "150511115051111150515051111150511115051",
  "150555555055555550555055555550555555051",
  "150000000000000000000000000000000000051",
  "150555555055505555555555505550555555051",
  "150511115051505111111111505150511115051",
  "150555555051505555515555505150555555051",
  "153000000051500000515000005150000000351",
  "155555555051555550515055555150555555551",
  "111111115051111150515051111150511111111",
  "111111115051555550555055555150511111111",
  "111111115051500000000000005150511111111",
  "111111115051505555555555505150511111111",
  "111111115051505111555111505150511111111",
  "555555555055505155555551505550555555555",
  "888000000000005158888851500000000000888",
  "555555555055505155555551505550555555555",
  "111111115051505111111111505150511111111",
  "111111115051505555555555505150511111111",
  "111111115051500000020000005150511111111",
  "111111115051505555555555505150511111111",
  "111111115051505111111111505150511111111",
  "155555555055505555515555505550555555551",
  "153000000000000000515000000000000000351",
  "150555555055555550515055555550555555051",
  "150511115051111150515051111150511115051",
  "150555515055555550555055555550515555051",
  "150000515000000000000000000000515000051",
  "155550515055505555555555505550515055551",
  "111150515051505111111111505150515051111",
  "155550555051505555515555505150555055551",
  "150000000051500000515000005150000000051",
  "150555555551555550515055555155555555051",
  "150511111111111150515051111111111115051",
  "150555555555555550555055555555555555051",
  "153000000000000000000000000000000000351",
  "155555555555555555555555555555555555551",
  "111111111111111111111111111111111111111"
};

int contadorBolinhasRestantes() {
    int total = 0;
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            if (mapa[i][j] == '0' || mapa[i][j] == '3') {
                total++;
            }
        }
    }
    return total;
}


const float larguraTela = 1920.0f;
const float alturaTela = 1080.0f;
const float SIZE = 22;
const float tamanhoBolinhaPequena = SIZE * 0.15f; 
const float tamanhoBolinhaGrande = SIZE * 0.35f;
const float tamanhoDaFruta = SIZE;
const float tamanhoPac = SIZE * 2.4f;
float velocidade = 0.16f;
float velocidadePacMan = 0.2f;

float sizeQuadBlack = SIZE*3;

bool passouTunel = false;

bool isPoweredUp = false;
sf::Clock relogioPowerUp;
const float TEMPO_POWER_UP = 5.0f;
const float TEMPO_FANTASMINHA_NASCER = 3.0f;

bool baiduEaten = false; sf::Clock relogioBaiduEaten;
bool avastEaten = false; sf::Clock relogioAvastEaten;
bool winEaten = false;   sf::Clock relogioWinEaten;
bool mcEaten = false;    sf::Clock relogioMcEaten;

bool pressionou = false;

int posxghostb =  16;
int posyghostb =  19;

int posxghosta =  18;
int posyghosta =  19;

int posxghostw =  20;
int posyghostw =  19;

int posxghostm =  22;
int posyghostm =  19;

int posxfruit;
int posyfruit;
int berryeat=0;
int orangeeat=0;
int meloneat=0;
bool berryhud=false, melonhud=false, orangehud=false;

bool isOutQuadradoB = false;
int dirBaidu = 0;

int nivel = 1;

bool isOutQuadradoA = false;
int dirAvast = 0;

bool isOutQuadradoW = false;
int dirW = 0;

bool isOutQuadradoM = false;
int dirM = 0;

float posxf = 19.0f; //posicao relativa fluida
float posyf = 23.0f;
float posxf_ghostb = 16.0f;
float posyf_ghostb = 19.0f;
float posxf_ghosta = 18.0f;
float posyf_ghosta = 19.0f;
float posxf_ghostw = 20.0f;
float posyf_ghostw = 19.0f;
float posxf_ghostm = 22.0f;
float posyf_ghostm = 19.0f;
float xdeslocamento = (larguraTela - (colunas*SIZE))/2.0f;
float ydeslocamento = (alturaTela - (linhas*SIZE))/2.0f;

float tamanhoFonteStart = SIZE*1.8f;
float tamanhoFonteGameOver = SIZE*2.72f;

float espessuraParede = SIZE * 0.1f;

bool cima = false;  // direcao de movimento do PacMan
bool baixo = false;
bool esq = false;
bool dir = false;

bool isMoving = false;

int score=0; //pontuação
bool intencao_cima = false;
bool intencao_baixo = false;
bool intencao_esq = false;
bool intencao_dir = false;
bool morreu = false;
bool closexavast=false, closexbaidu=false, closexwin=false, closexmc=false;
bool closeyavast=false,closeybaidu=false, closeywin=false, closeymc=false;
int gamestatus=0;
int main() {

    sf::SoundBuffer somComendo = retornaSom("./sounds/pacman_chomp.wav");
    sf::Sound soundComendo(somComendo);
    soundComendo.setVolume(15.0f);

    sf::SoundBuffer songComendoFantasma = retornaSom("./sounds/comendoFantasma.wav");
    sf::Sound comeF(songComendoFantasma);
    soundComendo.setVolume(40.0f);

    sf::SoundBuffer songComendoFruta = retornaSom("./sounds/comendoFruta.wav");
    sf::Sound comeFruta(songComendoFruta);
    soundComendo.setVolume(40.0f);

    sf::SoundBuffer songStart = retornaSom("./sounds/start.wav");
    sf::Sound somStart(songStart);

    sf::SoundBuffer songPersegue = retornaSom("./sounds/somPersegue.wav");
    sf::Sound somPersegue(songPersegue);

    sf::SoundBuffer songPress = retornaSom("./sounds/press.wav");
    sf::Sound somPress(songPress);

    sf::SoundBuffer songMorrendo = retornaSom("./sounds/morrendo.wav");
    sf::Sound somMorrendo(songMorrendo);


    sf::SoundBuffer songSirene = retornaSom("./sounds/somSirene.wav");
    sf::Sound somSirene(songSirene);

    arquivo >> maxScore;
    arquivo.close();
    // cria a janela
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Pac-Man", sf::State::Fullscreen);
    window.setFramerateLimit(60);

    // cria um quadrado de tamanho 50 (a parede)
    sf::RectangleShape quad({SIZE, SIZE});
    quad.setFillColor({57, 255, 20});
    sf::RectangleShape quadBlack({sizeQuadBlack, sizeQuadBlack});
    sf::RectangleShape quadBlack1({sizeQuadBlack, sizeQuadBlack});
    quadBlack.setFillColor({0, 0, 0});
    quadBlack1.setFillColor({0, 0, 0});
    quadBlack.setOrigin({sizeQuadBlack/2, sizeQuadBlack/2});
    quadBlack1.setOrigin({sizeQuadBlack/2, sizeQuadBlack/2});

    // cria bolinhas
    sf::CircleShape bolinha({tamanhoBolinhaPequena});
    bolinha.setFillColor({255, 255, 255});
    //cria bolinha maior
    sf::CircleShape BOLA({tamanhoBolinhaGrande});
    BOLA.setFillColor({255, 255, 255});

    // sprites do PacMan
    sf::Texture texture = retornaTextura("./sprites/virusdireita.png");
    sf::Texture texture1 = retornaTextura("./sprites/virusdireitagiro.png");
    sf::Texture texture2 = retornaTextura("./sprites/virusdireitaapagado.png");
    sf::Texture texturaPacPower = retornaTextura("./sprites/fantasmaPowered.png"); 
    sf::Texture texturaPacPower2 = retornaTextura("./sprites/fantasmaPowered2.png");
    sf::Texture texturaFantasmaAssustado = retornaTextura("./sprites/scared.png");
    sf::Sprite sprite(texture);

    float escalaPacman = tamanhoPac / texture.getSize().x;
    sprite.setScale({escalaPacman, escalaPacman});


     //FANTASMAS SPRITE

    sf::Texture baidutextura = retornaTextura("./sprites/baidu.png");
    sf::Texture baidutextura1 = retornaTextura("./sprites/baidu1.png");
    sf::Texture baidutextura2 = retornaTextura("./sprites/baidu2.png");
    sf::Sprite fantasmabaidu{baidutextura};

    sf::Texture avasttextura = retornaTextura("./sprites/avast.png");
    sf::Texture avasttextura1 = retornaTextura("./sprites/avast1.png");
    sf::Texture avasttextura2 = retornaTextura("./sprites/avast2.png");
    sf::Sprite fantasmaavast{avasttextura};

    sf::Texture wintextura = retornaTextura("./sprites/win.png");
    sf::Texture wintextura1 = retornaTextura("./sprites/win1.png");
    sf::Texture wintextura2 = retornaTextura("./sprites/win2.png");
    sf::Sprite fantasmawin{wintextura};

    sf::Texture mctextura = retornaTextura("./sprites/mc.png");
    sf::Texture mctextura1 = retornaTextura("./sprites/mc1.png");
    sf::Texture mctextura2 = retornaTextura("./sprites/mc2.png");
    sf::Sprite fantasmamc{mctextura};

    //FRUTAS SPRITE

    sf::Texture berrytextura = retornaTextura("./sprites/frutaberry.png");
    sf::Texture orangetextura = retornaTextura("./sprites/frutaorange.png");
    sf::Texture melontextura = retornaTextura("./sprites/frutamelon.png");
    sf::Sprite melon{melontextura};
    sf::Sprite orange{orangetextura};
    sf::Sprite berry{berrytextura};
    sf::Sprite berryh{berrytextura};
    sf::Sprite melonh{melontextura};
    sf::Sprite orangeh{orangetextura};

    // Define o tamanho desejado em pixels
    float tamanhoFantasma = SIZE*1.9f;

    float escalaFantasma1x = tamanhoFantasma / mctextura.getSize().x;
    float escalaFantasma1y = tamanhoFantasma / mctextura.getSize().y;

    float escalaFantasma2x = tamanhoFantasma / avasttextura.getSize().x;
    float escalaFantasma2y = tamanhoFantasma / avasttextura.getSize().y;

    float escalaFantasma3x = tamanhoFantasma / wintextura.getSize().x;
    float escalaFantasma3y = tamanhoFantasma / wintextura.getSize().y;

    float escalaFantasma4x = tamanhoFantasma / baidutextura.getSize().x;
    float escalaFantasma4y = tamanhoFantasma / baidutextura.getSize().y;

    fantasmawin.setScale({escalaFantasma3x, escalaFantasma3y});

    fantasmabaidu.setScale({escalaFantasma4x, escalaFantasma4y});

    fantasmamc.setScale({escalaFantasma1x, escalaFantasma1y});

    fantasmaavast.setScale({escalaFantasma2x, escalaFantasma2y});

    fantasmamc.setOrigin({mctextura.getSize().x / 2.0f, mctextura.getSize().y / 2.0f});

    fantasmabaidu.setOrigin({baidutextura.getSize().x / 2.0f, baidutextura.getSize().y / 2.0f});
    
    fantasmaavast.setOrigin({avasttextura.getSize().x / 2.0f, avasttextura.getSize().y / 2.0f});
    
    fantasmawin.setOrigin({wintextura.getSize().x / 2.0f, wintextura.getSize().y / 2.0f});


    sf::Font font; //fonte
    if(!font.openFromFile("emulogic.ttf")){
        std::cout << "Erro lendo fonte emulogic\n";
        return 0;
    }
    sf::Text text(font);
    sf::Text start(font, "PRESS ENTER TO START!", tamanhoFonteStart);
    sf::Text count1(font);
    sf::Text count2(font);
    sf::Text count3(font);
    auto tamanhoRealStart = start.getLocalBounds();
    start.setOrigin({tamanhoRealStart.size.x/2.0f, tamanhoRealStart.size.y/2});
    start.setPosition({larguraTela/2.0f, alturaTela/2.0f});
    text.setFillColor({255, 255, 255});
    text.setPosition({0, 0});
    start.setFillColor({255, 255, 255});

    // cria um relogio para medir o tempo do PacMan
    sf::Clock relogioMovimento;
    sf::Clock relogioAnimacao;
    sf::Clock relogioAnimacaoPower;
    int framePower = 0;
    sf::Clock relogioSomComendo;
    sf::Clock relogioSomStart;
    bool firstTime = true;
    sf::Clock relogioSomSirene;
    bool firstTimeSirene = true;
    sf::Clock relogioSomPersegue;
    bool firstTimePersegue = true;
    const float TEMPO_TIMEOUT_SOM = 0.09f; // Ajuste este valor (em segundos) conforme o tamanho do seu arquivo de som
    sf::Clock relogioMovimentofantasma;
    sf::Clock relogioAnimacaofantasma;
    sf::Clock relogioTextoPiscando;
    sf::Clock TempoSpawnFrutas;

    srand(time(NULL));


    // executa o programa enquanto a janela está aberta
    while (window.isOpen()) {

        // verifica todos os eventos que foram acionados na janela desde a última iteração do loop
        while (const std::optional event = window.pollEvent()) {
            // evento "fechar" acionado: fecha a janela
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                  if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                      window.close();
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Left) {
                      intencao_esq = true;   // left key: PacMan tem intenção de se mover para esquerda
                      intencao_dir = intencao_cima = intencao_baixo = false;
                  }
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Right) {
                      intencao_dir = true;   // right key: PacMan tem intenção de se mover para direita
                      intencao_esq = intencao_cima = intencao_baixo = false;
                  }
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Up) {
                      intencao_cima = true;   // up key: PacMan tem intenção de se mover para cima
                      intencao_esq = intencao_dir = intencao_baixo = false;
                  }
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Down) {
                      intencao_baixo = true;   // down key: PacMan tem intenção de se mover para baixo
                      intencao_esq = intencao_dir = intencao_cima = false;
                  }
                if (keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
                    pressionou = true;
                                if(pressionou == true) {
                                    somPress.play();
                                    pressionou = false;
                                    somMorrendo.stop();                 
                                }

                        if (gamestatus == 2 || gamestatus == 0) { 
                        score = 0;
                        isOutQuadradoB = isOutQuadradoA = isOutQuadradoW = isOutQuadradoM = false;
                        passouTunel = false;
                        isMoving = false;
                        intencao_cima = intencao_baixo = intencao_esq = intencao_dir = false;
                        cima = baixo = esq = dir = false;

                        posxf = 19.0f; posyf = 23.0f;
                        posxf_ghostb = 16.0f; posyf_ghostb = 19.0f;
                        posxf_ghosta = 18.0f; posyf_ghosta = 19.0f;
                        posxf_ghostw = 20.0f; posyf_ghostw = 19.0f;
                        posxf_ghostm = 22.0f; posyf_ghostm = 19.0f;

                        velocidade = 0.16f;

                        nivel = 1;
                        isPoweredUp = false;
                        baiduEaten = false;
                        avastEaten = false;
                        winEaten = false;
                        mcEaten = false;

                        for(int i = 0; i < linhas; i++) {
                            for(int j = 0; j < colunas; j++) {
                                if (mapa[i][j] == '2') mapa[i][j] = '0';
                                if (mapa[i][j] == '6') mapa[i][j] = '0';
                                if (mapa[i][j] == '7') mapa[i][j] = '0';
                                if (mapa[i][j] == '9') mapa[i][j] = '0';
                            }
                        }

                        berryhud = false;
                        melonhud = false;
                        orangehud = false;

                        berryeat = 0;
                        orangeeat = 0;
                        meloneat = 0;

                        TempoSpawnFrutas.restart();


                        mapa[2][2] = '3';
                        mapa[2][36] = '3';
                        mapa[11][2] = '3';
                        mapa[11][36] = '3';
                        mapa[27][2] = '3';
                        mapa[27][36] = '3';
                        mapa[39][2] = '3';
                        mapa[39][36] = '3';
                        mapa[23][19] = '2';
                        gamestatus = 1;
                    }
                }
            }
        }

        static bool showText = true;
            if (relogioTextoPiscando.getElapsedTime().asSeconds() > 0.5f) {
                showText = !showText;
            relogioTextoPiscando.restart();
            }

        window.clear(sf::Color::Black);

        if (gamestatus == 0) {
            if (showText) {
                window.draw(start);
            }
         if(firstTime == true || relogioSomStart.getElapsedTime().asSeconds() >= 4.2f) {
                        somStart.play();
                        firstTime = false;
                        relogioSomStart.restart();
                        
         }
        } 
        else if (gamestatus == 1) {
            somStart.stop();
            if (!isPoweredUp) {
                if(firstTimeSirene == true || relogioSomSirene.getElapsedTime().asSeconds() >= 3.2f) {
                    somSirene.play();
                    firstTimeSirene = false;
                    relogioSomSirene.restart();       
                }
            }

            if(contadorBolinhasRestantes() == 0) {
                nivel++;
                        for(int i = 0; i < linhas; i++) {
                            for(int j = 0; j < colunas; j++) {
                                if (mapa[i][j] == '2') mapa[i][j] = '0';
                            }
                        }

                        if (nivel >= 3) {
                            velocidade += 0.01f;
                        }

                        mapa[2][2] = '3';
                        mapa[2][36] = '3';
                        mapa[11][2] = '3';
                        mapa[11][36] = '3';
                        mapa[27][2] = '3';
                        mapa[27][36] = '3';
                        mapa[39][2] = '3';
                        mapa[39][36] = '3';
            }
            
            float tolerancia = velocidadePacMan * 0.55f;
            bool noCentroX = std::abs(posxf - std::round(posxf)) < tolerancia;
            bool noCentroY = std::abs(posyf - std::round(posyf)) < tolerancia;

            


            if (noCentroX && noCentroY) {

            posxf = std::round(posxf);
            posyf = std::round(posyf);

            int x = (int)posxf;
            int y = (int)posyf;

            if (intencao_cima && mapa[y-1][x] != '5') {
                cima = true; baixo = esq = dir = false;
                isMoving = true;
            } else if (intencao_baixo && mapa[y+1][x] != '5') {
                baixo = true; cima = esq = dir = false;
                isMoving = true;
            } else if (intencao_esq && mapa[y][x-1] != '5') {
                esq = true; cima = baixo = dir = false;
                isMoving = true;
            } else if (intencao_dir && mapa[y][x+1] != '5') {
                dir = true; cima = baixo = esq = false;
                isMoving = true;
            }

            if(y == 19 && x == 38 && passouTunel == false) {
                posyf = 19;
                posxf = 0;
                x = 0;
                passouTunel = true;
            }

            if(y == 19 && x == 0 && passouTunel == false) {
                posyf = 19;
                posxf = 38;
                passouTunel = true;
            }

            if (y == 19 && x == 37) {
                passouTunel = false;
            }

            if (y == 19 && x == 1) {
                passouTunel = false;
            }

            if(mapa[y][x]=='0'){
                mapa[y][x]='2';
            if (soundComendo.getStatus() != sf::SoundSource::Status::Playing) {
                soundComendo.play();
            }
    
            // Reseta o relógio toda vez que come uma bolinha
            relogioSomComendo.restart();
                score+=10;
            }
            else if(mapa[y][x]=='3'){
                mapa[y][x]='2';
                isPoweredUp = true;
                if (!isPoweredUp) {
                    firstTimePersegue = true;
                    somSirene.stop();
                }
                relogioPowerUp.restart();
                score+=50;
                somSirene.stop();
            }
            else if(mapa[y][x]=='6'){
                mapa[y][x]='2';
                score+=150;
                berryeat++;
                comeFruta.play();
                if(!berryhud)
                    berryhud=true;
            }
            else if(mapa[y][x]=='7'){
                mapa[y][x]='2';
                score+=160;
                meloneat++;
                comeFruta.play();
                if(!melonhud)
                    melonhud=true;
            }
            else if(mapa[y][x]=='9'){
                mapa[y][x]='2';
                score+=170;
                orangeeat++;
                comeFruta.play();
                if(!orangehud)
                    orangehud=true;
            }
            
            if (cima && mapa[y-1][x] == '5') { cima = false; isMoving = false;}
            if (baixo && mapa[y+1][x] == '5') { baixo = false; isMoving = false;}
            if (esq && mapa[y][x-1] == '5') { esq = false; isMoving = false;}
            if (dir && mapa[y][x+1] == '5') { dir = false; isMoving = false;}

            }

            if (isPoweredUp && relogioPowerUp.getElapsedTime().asSeconds() > TEMPO_POWER_UP) {
                isPoweredUp = false;
                somPersegue.stop();
                firstTimePersegue = false;
                firstTimeSirene = true;
                relogioSomSirene.restart();
            }
         
            if (cima) { posyf -= velocidadePacMan; sprite.setRotation(sf::degrees(270));}
            if (baixo) { posyf += velocidadePacMan; sprite.setRotation(sf::degrees(90));}
            if (esq) { posxf -= velocidadePacMan; sprite.setRotation(sf::degrees(180));}
            if (dir) { posxf += velocidadePacMan; sprite.setRotation(sf::degrees(0));}
            
        // limpa a janela com a cor preta
        window.clear(sf::Color::Black);

        // desenhar tudo aqui...
        sf::Time tempoFantasma = relogioAnimacaofantasma.getElapsedTime();

        if (tempoFantasma < sf::seconds(0.50f)) {
            fantasmamc.setTexture(mctextura);
            fantasmabaidu.setTexture(baidutextura);
            fantasmaavast.setTexture(avasttextura);
            fantasmawin.setTexture(wintextura);
        } 
        else if (tempoFantasma >= sf::seconds(0.50f) && tempoFantasma < sf::seconds(1.00f)) {
            fantasmamc.setTexture(mctextura1);
            fantasmabaidu.setTexture(baidutextura1);
            fantasmaavast.setTexture(avasttextura1);
            fantasmawin.setTexture(wintextura1);
        } 
        else if (tempoFantasma >= sf::seconds(1.00f) && tempoFantasma < sf::seconds(1.50f)) {
            fantasmamc.setTexture(mctextura2);
            fantasmabaidu.setTexture(baidutextura2);
            fantasmaavast.setTexture(avasttextura2);
            fantasmawin.setTexture(wintextura2);
        } 
        else if (tempoFantasma >= sf::seconds(1.50)) {
            // Reseta o relógio UMA ÚNICA VEZ para o loop recomeçar
            relogioAnimacaofantasma.restart();
        }

        bool noCentroXB = std::abs(posxf_ghostb - std::round(posxf_ghostb)) < tolerancia;
        bool noCentroYB = std::abs(posyf_ghostb - std::round(posyf_ghostb)) < tolerancia;

        bool noCentroXA = std::abs(posxf_ghosta - std::round(posxf_ghosta)) < tolerancia;
        bool noCentroYA = std::abs(posyf_ghosta - std::round(posyf_ghosta)) < tolerancia;

        bool noCentroXW = std::abs(posxf_ghostw - std::round(posxf_ghostw)) < tolerancia;
        bool noCentroYW = std::abs(posyf_ghostw - std::round(posyf_ghostw)) < tolerancia;

        bool noCentroXM = std::abs(posxf_ghostm - std::round(posxf_ghostm)) < tolerancia;
        bool noCentroYM = std::abs(posyf_ghostm - std::round(posyf_ghostm)) < tolerancia;

        if (baiduEaten && relogioBaiduEaten.getElapsedTime().asSeconds() > TEMPO_FANTASMINHA_NASCER) {
            baiduEaten = false; isOutQuadradoB = false; dirBaidu = 0;
            posxf_ghostb = 16.0f; posyf_ghostb = 19.0f;
        }
        if (avastEaten && relogioAvastEaten.getElapsedTime().asSeconds() > TEMPO_FANTASMINHA_NASCER) {
            avastEaten = false; isOutQuadradoA = false; dirAvast = 0;
            posxf_ghosta = 18.0f; posyf_ghosta = 19.0f;
        }
        if (winEaten && relogioWinEaten.getElapsedTime().asSeconds() > TEMPO_FANTASMINHA_NASCER) {
            winEaten = false; isOutQuadradoW = false; dirW = 0;
            posxf_ghostw = 20.0f; posyf_ghostw = 19.0f;
        }
        if (mcEaten && relogioMcEaten.getElapsedTime().asSeconds() > TEMPO_FANTASMINHA_NASCER) {
            mcEaten = false; isOutQuadradoM = false; dirM = 0;
            posxf_ghostm = 22.0f; posyf_ghostm = 19.0f;
        }

        if(!winEaten) {

        if (!isOutQuadradoW) {
            posyf_ghostw -= velocidade; 
            if (posyf_ghostw <= 15.0f) {
                posyf_ghostw = 15.0f;     
                isOutQuadradoW = true;    
                dirW = 2;             
            }
        } else {
            if (noCentroXW && noCentroYW) {
        
                posxf_ghostw = std::round(posxf_ghostw);
                posyf_ghostw = std::round(posyf_ghostw);
            
                int xw = (int)posxf_ghostw;
                int yw = (int)posyf_ghostw;
                
                if (yw == 19 && xw <= 0 && dirW == 2) {
                    posxf_ghostw = 38.0f;
                    xw = 38;
                } else if (yw == 19 && xw >= 38 && dirW == 3) {
                    posxf_ghostw = 0.0f;
                    xw = 0;
                }

                int direcaoOposta = -1;
                if (dirW == 0) direcaoOposta = 1; 
                if (dirW == 1) direcaoOposta = 0; 
                if (dirW == 2) direcaoOposta = 3; 
                if (dirW == 3) direcaoOposta = 2; 

                int direcoesValidas[4];
                int numDirecoes = 0; 
            
                if (mapa[yw-1][xw] != '5' && direcaoOposta != 0) {
                    direcoesValidas[numDirecoes] = 0; 
                    numDirecoes++;
                }
                if (mapa[yw+1][xw] != '5' && direcaoOposta != 1) {
                    direcoesValidas[numDirecoes] = 1; 
                    numDirecoes++;
                }
                if (mapa[yw][xw-1] != '5' && direcaoOposta != 2) {
                    direcoesValidas[numDirecoes] = 2; 
                    numDirecoes++;
                }
                if (mapa[yw][xw+1] != '5' && direcaoOposta != 3) {
                    direcoesValidas[numDirecoes] = 3; 
                    numDirecoes++;
                }

                if (numDirecoes == 0) {
                    direcoesValidas[0] = direcaoOposta;
                    numDirecoes = 1;
                }

                int indiceSorteado = rand() % numDirecoes;
                dirW = direcoesValidas[indiceSorteado];
            }

            // Aplica o movimento
            if (dirW == 0) posyf_ghostw -= velocidade;
            if (dirW == 1) posyf_ghostw += velocidade;
            if (dirW == 2) posxf_ghostw -= velocidade;
            if (dirW == 3) posxf_ghostw += velocidade;
        }
    }

    if (!mcEaten) {

        if (!isOutQuadradoM) {
            posyf_ghostm -= velocidade; 
            if (posyf_ghostm <= 15.0f) {
                posyf_ghostm = 15.0f;     
                isOutQuadradoM = true;    
                dirM = 2;             
            }
        } else {
        // TODA A VEZ que ele entra no centro de um novo bloco, ele avalia as opções
            if (noCentroXM && noCentroYM) {
        
            // Trava no centro exato para evitar desvios igual a logica q fiz do pacman
            posxf_ghostm = std::round(posxf_ghostm);
            posyf_ghostm = std::round(posyf_ghostm);
        
            int xm = (int)posxf_ghostm;
            int ym = (int)posyf_ghostm;
            
            if (ym == 19 && xm <= 0 && dirM == 2) {
                posxf_ghostm = 38.0f;
                xm = 38;
            } else if (ym == 19 && xm >= 38 && dirM == 3) {
                posxf_ghostm = 0.0f;
                xm = 0;
            }

            // ta memorizando a direcao oposta (de onde ele veio) para NUNCA dar meia-volta
            int direcaoOposta = -1;
            if (dirM == 0) direcaoOposta = 1; // Se vai para cima, não pode voltar para baixo
            if (dirM == 1) direcaoOposta = 0; // Se vai para baixo, não pode voltar para cima
            if (dirM == 2) direcaoOposta = 3; // Se vai para a esq, não pode voltar para a dir
            if (dirM == 3) direcaoOposta = 2; // Se vai para a dir, não pode voltar para a esq

            int direcoesValidas[4];
            int numDirecoes = 0; // Contador de quantas rotas estão livres
        

            if (mapa[ym-1][xm] != '5' && direcaoOposta != 0) {
                direcoesValidas[numDirecoes] = 0; // Cima
                numDirecoes++;
            }
            if (mapa[ym+1][xm] != '5' && direcaoOposta != 1) {
                direcoesValidas[numDirecoes] = 1; // Baixo
                numDirecoes++;
            }
            if (mapa[ym][xm-1] != '5' && direcaoOposta != 2) {
                direcoesValidas[numDirecoes] = 2; // Esquerda
                numDirecoes++;
            }
            if (mapa[ym][xm+1] != '5' && direcaoOposta != 3) {
                direcoesValidas[numDirecoes] = 3; // Direita
                numDirecoes++;
            }

            if (numDirecoes == 0) {
                direcoesValidas[0] = direcaoOposta;
                numDirecoes = 1;
            }


            int indiceSorteado = rand() % numDirecoes;
            dirM = direcoesValidas[indiceSorteado];
            }

            if (dirM == 0) posyf_ghostm -= velocidade;
            if (dirM == 1) posyf_ghostm += velocidade;
            if (dirM == 2) posxf_ghostm -= velocidade;
            if (dirM == 3) posxf_ghostm += velocidade;
        
    }
    }

    if (!baiduEaten) {
        if (!isOutQuadradoB) {
            posyf_ghostb -= velocidade; 
            if (posyf_ghostb <= 15.0f) {
                posyf_ghostb = 15.0f;     
                isOutQuadradoB = true;    
                dirBaidu = 2;             
            }
        } else {
        // TODA A VEZ que ele entra no centro de um novo bloco, ele avalia as opções
            if (noCentroXB && noCentroYB) {
        
            // Trava no centro exato para evitar desvios igual a logica q fiz do pacman
            posxf_ghostb = std::round(posxf_ghostb);
            posyf_ghostb = std::round(posyf_ghostb);
        
            int xb = (int)posxf_ghostb;
            int yb = (int)posyf_ghostb;
            
            if (yb == 19 && xb <= 0 && dirBaidu == 2) {
                posxf_ghostb = 38.0f;
                xb = 38;
            } else if (yb == 19 && xb >= 38 && dirBaidu == 3) {
                posxf_ghostb = 0.0f;
                xb = 0;
            }

            // ta memorizando a direcao oposta (de onde ele veio) para NUNCA dar meia-volta
            int direcaoOposta = -1;
            if (dirBaidu == 0) direcaoOposta = 1; // Se vai para cima, não pode voltar para baixo
            if (dirBaidu == 1) direcaoOposta = 0; // Se vai para baixo, não pode voltar para cima
            if (dirBaidu == 2) direcaoOposta = 3; // Se vai para a esq, não pode voltar para a dir
            if (dirBaidu == 3) direcaoOposta = 2; // Se vai para a dir, não pode voltar para a esq

            int direcoesValidas[4];
            int numDirecoes = 0; // Contador de quantas rotas estão livres
        
                
            if (mapa[yb-1][xb] != '5' && direcaoOposta != 0) {
                direcoesValidas[numDirecoes] = 0; // Cima
                numDirecoes++;
            }
            if (mapa[yb+1][xb] != '5' && direcaoOposta != 1) {
                direcoesValidas[numDirecoes] = 1; // Baixo
                numDirecoes++;
            }
            if (mapa[yb][xb-1] != '5' && direcaoOposta != 2) {
                direcoesValidas[numDirecoes] = 2; // Esquerda
                numDirecoes++;
            }
            if (mapa[yb][xb+1] != '5' && direcaoOposta != 3) {
                direcoesValidas[numDirecoes] = 3; // Direita
                numDirecoes++;
            }

            if (numDirecoes == 0) {
                direcoesValidas[0] = direcaoOposta;
                numDirecoes = 1;
            }


            int indiceSorteado = rand() % numDirecoes;
            dirBaidu = direcoesValidas[indiceSorteado];
            }

            if (dirBaidu == 0) posyf_ghostb -= velocidade;
            if (dirBaidu == 1) posyf_ghostb += velocidade;
            if (dirBaidu == 2) posxf_ghostb -= velocidade;
            if (dirBaidu == 3) posxf_ghostb += velocidade;
        
    }
    }
    if (!avastEaten) {
        
    if (!isOutQuadradoA) {
            posyf_ghosta -= velocidade; 
            if (posyf_ghosta <= 15.0f) {
                posyf_ghosta = 15.0f;     
                isOutQuadradoA = true;    
                dirAvast = 2;             
            }
        } else {
        // TODA A VEZ que ele entra no centro de um novo bloco, ele avalia as opções
            if (noCentroXA && noCentroYA) {
        
            // Trava no centro exato para evitar desvios igual a logica q fiz do pacman
            posxf_ghosta = std::round(posxf_ghosta);
            posyf_ghosta = std::round(posyf_ghosta);
        
            int xa = (int)posxf_ghosta;
            int ya = (int)posyf_ghosta;

            if (ya == 19 && xa <= 0 && dirAvast == 2) {
                posxf_ghosta = 38.0f;
                xa = 38;
            } else if (ya == 19 && xa >= 38 && dirAvast == 3) {
                posxf_ghosta = 0.0f;
                xa = 0;
            }

            // ta memorizando a direcao oposta (de onde ele veio) para NUNCA dar meia-volta
            int direcaoOposta = -1;
            if (dirAvast == 0) direcaoOposta = 1; // Se vai para cima, não pode voltar para baixo
            if (dirAvast == 1) direcaoOposta = 0; // Se vai para baixo, não pode voltar para cima
            if (dirAvast == 2) direcaoOposta = 3; // Se vai para a esq, não pode voltar para a dir
            if (dirAvast == 3) direcaoOposta = 2; // Se vai para a dir, não pode voltar para a esq

            int direcoesValidas[4];
            int numDirecoes = 0; // Contador de quantas rotas estão livres
        

            if (mapa[ya-1][xa] != '5' && direcaoOposta != 0) {
                direcoesValidas[numDirecoes] = 0; // Cima
                numDirecoes++;
            }
            if (mapa[ya+1][xa] != '5' && direcaoOposta != 1) {
                direcoesValidas[numDirecoes] = 1; // Baixo
                numDirecoes++;
            }
            if (mapa[ya][xa-1] != '5' && direcaoOposta != 2) {
                direcoesValidas[numDirecoes] = 2; // Esquerda
                numDirecoes++;
            }
            if (mapa[ya][xa+1] != '5' && direcaoOposta != 3) {
                direcoesValidas[numDirecoes] = 3; // Direita
                numDirecoes++;
            }

            if (numDirecoes == 0) {
                direcoesValidas[0] = direcaoOposta;
                numDirecoes = 1;
            }


            int indiceSorteado = rand() % numDirecoes;
            dirAvast = direcoesValidas[indiceSorteado];
            }

            if (dirAvast== 0) posyf_ghosta -= velocidade;
            if (dirAvast == 1) posyf_ghosta += velocidade;
            if (dirAvast == 2) posxf_ghosta -= velocidade;
            if (dirAvast == 3) posxf_ghosta += velocidade;
    }
} 
        sf::Time tempospawnfruta = TempoSpawnFrutas.getElapsedTime();

        // desenha paredes
        for(int i=0;i<linhas;i++)
            for(int j=0;j<colunas;j++) {
            if(mapa[i][j] == '1') {
                if(mapa[i-1][j] != '1') {
                quad.setPosition({xdeslocamento + j*SIZE, ydeslocamento+ i*SIZE});
                quad.setSize({SIZE, espessuraParede});
                window.draw(quad);
                }
                if(mapa[i+1][j] != '1') {
                quad.setPosition({xdeslocamento + j*SIZE, ydeslocamento+ i*SIZE + SIZE - espessuraParede});
                quad.setSize({SIZE, espessuraParede});
                window.draw(quad);
                } if(mapa[i][j-1] != '1') {
                quad.setPosition({xdeslocamento + j*SIZE, ydeslocamento+ i*SIZE});
                quad.setSize({espessuraParede, SIZE});
                window.draw(quad);
                } if (mapa[i][j+1] != '1') {
                quad.setPosition({xdeslocamento + j*SIZE + SIZE - espessuraParede, ydeslocamento+ i*SIZE});
                quad.setSize({espessuraParede,SIZE});
                window.draw(quad);
                }
            }
            if(mapa[i][j] == '0'){
                bolinha.setOrigin({tamanhoBolinhaPequena, tamanhoBolinhaPequena}); 
                bolinha.setPosition({xdeslocamento + j*SIZE + SIZE/2, ydeslocamento + i*SIZE + SIZE/2});
                window.draw(bolinha);
            }
            else if(mapa[i][j] == '3'){
                BOLA.setOrigin({tamanhoBolinhaGrande, tamanhoBolinhaGrande});
                BOLA.setPosition({xdeslocamento + j*SIZE + SIZE/2, ydeslocamento + i*SIZE + SIZE/2});
                window.draw(BOLA);
            }
            else if(mapa[i][j] == '6'){
                berry.setOrigin({tamanhoDaFruta, tamanhoDaFruta});
                berry.setPosition({xdeslocamento + j*SIZE + SIZE/2, ydeslocamento + i*SIZE + SIZE/2});
                berry.setScale(sf::Vector2f(0.5f, 0.5f));
                window.draw(berry);
            }
            else if(mapa[i][j] == '7'){
                melon.setOrigin({tamanhoDaFruta, tamanhoDaFruta});
                melon.setPosition({xdeslocamento + j*SIZE + SIZE/2, ydeslocamento + i*SIZE + SIZE/2});
                melon.setScale(sf::Vector2f(0.5f, 0.5f));
                window.draw(melon);
            }
            else if(mapa[i][j] == '9'){
                orange.setOrigin({tamanhoDaFruta, tamanhoDaFruta});
                orange.setPosition({xdeslocamento + j*SIZE + SIZE/2, ydeslocamento + i*SIZE + SIZE/2});
                orange.setScale(sf::Vector2f(0.5f, 0.5f));
                window.draw(orange);
            }
        
           sf::Time tempospawnfruta = TempoSpawnFrutas.getElapsedTime();
           char opcoesFrutas[] = {'6', '7', '9'};
           if (tempospawnfruta >= sf::seconds(35.f)) {
           TempoSpawnFrutas.restart(); 
           tempospawnfruta = sf::Time::Zero; 
           bool frutaPosicionada = false;
           int tentativas = 0;
           while (!frutaPosicionada && tentativas < 100) {
           int posxfruit = rand() % 40; 
           int posyfruit = rand() % 40; 
           if (mapa[posyfruit][posxfruit] == '2') {
               int indiceAleatorio = rand() % 3;
               mapa[posyfruit][posxfruit] = opcoesFrutas[indiceAleatorio];
               frutaPosicionada = true;
           }
           tentativas++;
           }
           }
            
           }
        
        if(isMoving == true) {
            
            if(relogioAnimacao.getElapsedTime() < sf::seconds(0.15f)) {
                sprite.setTexture(texture1);
            } 
            
            else if (relogioAnimacao.getElapsedTime() >= sf::seconds(0.30f) && relogioAnimacao.getElapsedTime() < sf::seconds(0.45f)) {
                sprite.setTexture(texture2);
            } 
            
            else if (relogioAnimacao.getElapsedTime() >= sf::seconds(0.45f) && relogioAnimacao.getElapsedTime() < sf::seconds(0.60f)) {
                sprite.setTexture(texture);
            } 
            // Reseta o relógio
            else if (relogioAnimacao.getElapsedTime() >= sf::seconds(0.75f)) {
                relogioAnimacao.restart();
            }
       } else {
         sprite.setTexture(texture2);
       }
       
       if (isPoweredUp) {
            soundComendo.stop();
            // Verifica se passaram 0.15 segundos (pode ajustar este valor para a animação ficar mais rápida ou mais lenta)
            if (relogioAnimacaoPower.getElapsedTime().asSeconds() > 0.15f) {
                // Alterna o frame entre 0 e 1
                if (framePower == 0) {
                    framePower = 1;
                } else {
                    framePower = 0;
                }
                // Reinicia o relógio para contar o próximo frame
                relogioAnimacaoPower.restart();
            }

            // Define a textura correta consoante o frame atual
            if (framePower == 0) {
                sprite.setTexture(texturaPacPower, true);
            } else {
                sprite.setTexture(texturaPacPower2, true);
            }
            if(firstTimePersegue == true || relogioSomPersegue.getElapsedTime().asSeconds() >= 5.2f) {
                    somSirene.stop();
                    somPersegue.play();
                    firstTimePersegue = false;
                    relogioSomPersegue.restart();             
         }
        }
   
        // desenha PacMan
        float texturaAtualX = sprite.getTexture().getSize().x;
        float texturaAtualY = sprite.getTexture().getSize().y;
        float escalaAtualX = tamanhoPac / texturaAtualX;
        float escalaAtualY = tamanhoPac / texturaAtualY;

        sprite.setScale({escalaAtualX, escalaAtualY});
        sprite.setOrigin({texturaAtualX / 2.0f, texturaAtualY / 2.0f});
        sprite.setPosition({xdeslocamento + posxf*SIZE + SIZE/2.0f, ydeslocamento + posyf*SIZE + SIZE/2.0f}); //o que fizer no desenho tem que fazer aqui
        // para renderização dos espaços e a posição dele baterem
        window.draw(sprite);
        //desenha o score
        std::string infoStr = "LEVEL: " + std::to_string(nivel) + 
                      "   SCORE: " + std::to_string(score) + 
                      "   MAX: " + std::to_string(maxScore);

        sf::Text infoText(font, infoStr, tamanhoFonteGameOver / 2);
        infoText.setFillColor({255, 255, 255});
        auto tamanhoRealInfo = infoText.getLocalBounds();
        infoText.setOrigin({tamanhoRealInfo.size.x / 2.0f, tamanhoRealInfo.size.y / 2.0f});
        infoText.setPosition({tamanhoRealInfo.size.x, tamanhoRealInfo.size.y});
        window.draw(infoText);
        if(berryhud){
            berryh.setPosition({xdeslocamento + (SIZE-10), ydeslocamento + 42*SIZE + SIZE / 2.0f});
            window.draw(berryh);
            count1.setPosition({xdeslocamento + SIZE*2, ydeslocamento + 43*SIZE + SIZE / 2.0f});
            count1.setString(std::to_string(berryeat));
            window.draw(count1);
        }
        if(melonhud){
            melonh.setPosition({xdeslocamento + SIZE*4, ydeslocamento + 42*SIZE + SIZE / 2.0f});
            window.draw(melonh);
            count2.setPosition({xdeslocamento + SIZE*5, ydeslocamento + 43*SIZE + SIZE / 2.0f});
            count2.setString(std::to_string(meloneat));
            window.draw(count2);
        }
        if(orangehud){
            orangeh.setPosition({xdeslocamento + SIZE*7, ydeslocamento + 42*SIZE + SIZE / 2.0f});
            window.draw(orangeh);
            count3.setPosition({xdeslocamento + SIZE*8, ydeslocamento + 43*SIZE + SIZE / 2.0f});
            count3.setString(std::to_string(orangeeat));
            window.draw(count3);
        }

        if (!baiduEaten) {
            if (isPoweredUp) fantasmabaidu.setTexture(texturaFantasmaAssustado);
            fantasmabaidu.setPosition({xdeslocamento + posxf_ghostb*SIZE + SIZE/2, ydeslocamento + posyf_ghostb*SIZE + SIZE/2});
            window.draw(fantasmabaidu);
        }

        if (!winEaten) {
            if (isPoweredUp) fantasmawin.setTexture(texturaFantasmaAssustado);
            fantasmawin.setPosition({xdeslocamento + posxf_ghostw*SIZE + SIZE/2, ydeslocamento + posyf_ghostw*SIZE + SIZE/2}); 
            window.draw(fantasmawin);
        }

        if (!avastEaten) {
            if (isPoweredUp) fantasmaavast.setTexture(texturaFantasmaAssustado);
            fantasmaavast.setPosition({xdeslocamento + posxf_ghosta*SIZE + SIZE/2, ydeslocamento + posyf_ghosta*SIZE + SIZE/2});
            window.draw(fantasmaavast);
        }

        if (!mcEaten) {
            if (isPoweredUp) fantasmamc.setTexture(texturaFantasmaAssustado);
            fantasmamc.setPosition({xdeslocamento + posxf_ghostm*SIZE + SIZE/2, ydeslocamento + posyf_ghostm*SIZE + SIZE/2}); 
            window.draw(fantasmamc);
        }

        quadBlack.setPosition({xdeslocamento + 38*SIZE, ydeslocamento + 19*SIZE + SIZE / 2.0f});
        window.draw(quadBlack);
        quadBlack1.setPosition({xdeslocamento + SIZE, ydeslocamento + 19*SIZE + SIZE / 2.0f });
        window.draw(quadBlack1);

        //verifica se o pacman está encostado no baidu
        if (std::abs(posxf - posxf_ghostb) < 0.2f && std::abs(posyf - posyf_ghostb) < 0.2f && !baiduEaten) {
            if (isPoweredUp) {
                baiduEaten = true;
                comeF.play();
                score += 200; // Pontos por comer o fantasma
                relogioBaiduEaten.restart();
            } else {
                closexbaidu = true; closeybaidu = true;
            }
        } else {
            closexbaidu = false; closeybaidu = false;
        }

        // Verifica se o pacman está encostado no mc
        if (std::abs(posxf - posxf_ghostm) < 0.2f && std::abs(posyf - posyf_ghostm) < 0.2f && !mcEaten) {
            if (isPoweredUp) {
                mcEaten = true; score += 200; comeF.play(); relogioMcEaten.restart();
            } else {
                closexmc = true; closeymc = true;
            }
        } else {
            closexmc = false; closeymc = false;
        }

        // Verifica se o pacman está encostado no avast
        if (std::abs(posxf - posxf_ghosta) < 0.2f && std::abs(posyf - posyf_ghosta) < 0.2f && !avastEaten) {
             if (isPoweredUp) {
                avastEaten = true; score += 200; comeF.play(); relogioAvastEaten.restart();
            } else {
                closexavast = true; closeyavast = true;
            }
        } else {
            closexavast = false; closeyavast = false;
        }

        // Verifica se o pacman está encostado no win
        if (std::abs(posxf - posxf_ghostw) < 0.2f && std::abs(posyf - posyf_ghostw) < 0.2f && !winEaten) {
             if (isPoweredUp) {
                winEaten = true; score += 200; comeF.play(); relogioWinEaten.restart();
            } else {
                closexwin = true; closeywin = true;
            }
        } else {
            closexwin = false; closeywin = false;
        }
        if (closexavast && closeyavast || closexbaidu && closeybaidu || 
                closexwin && closeywin || closexmc && closeymc) {
                
                morreu = true;
                gamestatus = 2; // Muda para a tela de Game Over
                if (score > maxScore) {
                    maxScore = score; // Atualiza o histórico
                    std::ofstream arquivoEscrita("save");
                    arquivoEscrita << maxScore;
                    arquivoEscrita.close();
                }
            }


    } else if (gamestatus == 2) {
            somSirene.stop();
        if(morreu == true) {
            somMorrendo.play();
            morreu = false;                  
         }

            sf::Text gameOverText(font, "GAME OVER",  tamanhoFonteGameOver);
            gameOverText.setFillColor({255, 0, 0});
            auto tamanhoRealGameOver = gameOverText.getLocalBounds();
            gameOverText.setOrigin({tamanhoRealGameOver.size.x/2.0f, tamanhoRealGameOver.size.y/2.0f});
            gameOverText.setPosition({(larguraTela / 2.0f), (alturaTela / 2.0f)});
            std::string infoStr = "LEVEL: " + std::to_string(nivel) + 
                      "   SCORE: " + std::to_string(score) + 
                      "   MAX: " + std::to_string(maxScore);

            sf::Text infoText(font, infoStr, tamanhoFonteGameOver / 2);
            infoText.setFillColor({255, 255, 255});
            auto tamanhoRealInfo = infoText.getLocalBounds();
            infoText.setOrigin({tamanhoRealInfo.size.x / 2.0f, tamanhoRealInfo.size.y / 2.0f});
            infoText.setPosition({(larguraTela / 2.0f), (alturaTela / 2.0f + tamanhoRealGameOver.size.y)});
            window.draw(infoText);

            window.draw(gameOverText);
            window.draw(infoText);

            if (showText) {
                start.setPosition({larguraTela/2.0f, alturaTela/2.0f + tamanhoRealGameOver.size.y + tamanhoRealInfo.size.y*2});
                window.draw(start);
            }
        }
        
        // termina e desenha o frame corrente
        window.display();
    
}

    return 0;
}
