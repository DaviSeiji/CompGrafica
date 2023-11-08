// Davi Seiji Kawai Santos - 156373

#include <glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Variáveis globais, um para guardar as coordenadas dos vértices(linha) e outro pra ver se é linha(0) ou triângulo(1)
int linha[6];


// Valores da janela de recorte
int xwmin = 100;
int xwmax = 300;
int ywmin = 100;
int ywmax = 300;


// Funções para normalizar as coordenadas
float coordx(int x)
{
    float a;

    a = (x - 200) / 200.0;

    return a;
}

float coordy(int y)
{
    float b;

    b = (y - 200) * -1 / 200.0;

    return b;
}

// Função para desenhar uma linha, recebendo seus vértices
void desenhar_linha(int x1, int y1, int x2, int y2)
{
    float a1, b1, a2, b2;

    a1 = coordx(x1);
    a2 = coordx(x2);
    b1 = coordy(y1);
    b2 = coordy(y2);

    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(a1, b1);
    glVertex2f(a2, b2);
    glEnd();
}


void displayFunc()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    desenhar_linha(xwmin, ywmin, xwmax, ywmin);
    desenhar_linha(xwmax, ywmin, xwmax, ywmax);
    desenhar_linha(xwmax, ywmax, xwmin, ywmax);
    desenhar_linha(xwmin, ywmax, xwmin, ywmin);
    glColor3f(0.0, 0.0, 1.0);
    glFlush();
}

void cohen_sutherland(int x1, int y1, int x2, int y2){

    int b1[4], b2[4], b[4];

    int aux = 0;

    for(aux == 0; aux < 4; aux++){
        b1[aux] = 0;
        b2[aux] = 0;
        b[aux] = 0;
    }

    if(x1 - xwmin < 0){
        b1[0] = 1;
    }

    if(x2 - xwmin < 0){
        b2[0] = 1;
    }

    if(xwmax - x1 < 0){
        b1[1] = 1;
    }

    if(xwmax - x2 < 0){
        b2[1] = 1;
    }

    if(y1 - ywmin < 0){
        b1[2] = 1;
    }

    if(y2 - ywmin < 0){
        b2[2] = 1;
    }

    if(ywmax - y1 < 0){
        b1[3] = 1;
    }

    if(ywmax - y2 < 0){
        b2[3] = 1;
    }

    for (aux = 0; aux < 4; aux++) {

        if(b1[aux] == 1 && b2[aux] == 1){

            return;
        }

        b[aux] = b1[aux] + b2[aux];
    }

    if (b[0] == 0 && b[1] == 0 && b[2] == 0 && b[3] == 0) {

        // Totalmente dentro da janela, desenha
        desenhar_linha(x1, y1, x2, y2);
        return;
    }

    int x, y;

    if(b1[0] == 1){
        x1 = xwmin;
        y1 = y1 + (y2 - y1) * (xwmin - x1) / (x2 - x1);
    }

    else if(b1[1] == 1){
        x1 = xwmax;
        y1 = y1 + (y2 - y1) * (xwmax - x1) / (x2 - x1);
    }

    else if(b1[2] == 1){
        y1 = ywmin;
        x1 = x1 + (x2 - x1) * (ywmin - y1) / (y2 - y1);
    }

    else if(b1[3] == 1){
        y1 = ywmax;
        x1 = x1 + (x2 - x1) * (ywmax - y1) / (y2 - y1);
    }

    else if(b2[0] == 1){
        x2 = xwmin;
        y2 = y1 + (y2 - y1) * (xwmin - x1) / (x2 - x1);
    }

    else if(b2[1] == 1){
        x2 = xwmax;
        y2 = y1 + (y2 - y1) * (xwmax - x1) / (x2 - x1);
    }

    else if(b2[2] == 1){
        y2 = ywmin;
        x2 = x1 + (x2 - x1) * (ywmin - y1) / (y2 - y1);
    }

    else if(b2[3] == 1){
        y2 = ywmax;
        x2 = x1 + (x2 - x1) * (ywmax - y1) / (y2 - y1);
    }

    // Vamos verificar novamente
    cohen_sutherland(x1, y1, x2, y2);
}

// Ao detectar um clique vem aqui
void MouseInt(int botao, int estado, int x, int y)
{

    switch (botao)
    {
    case GLUT_LEFT_BUTTON:
        if (estado == GLUT_DOWN)
        {

            if (linha[1] == 1000)
            {
                linha[0] = x;
                linha[1] = y;
            }
            else if (linha[3] == 1000)
            {
                linha[2] = x;
                linha[3] = y;
            }
            else
            {
                linha[4] = x;
                linha[5] = y;

                cohen_sutherland(linha[0], linha[1], linha[2], linha[3]);
                cohen_sutherland(linha[2], linha[3], linha[4], linha[5]);
                cohen_sutherland(linha[4], linha[5], linha[0], linha[1]);

                linha[1] = 1000;
                linha[3] = 1000;
                linha[5] = 1000;
                glFlush();
            }
        }
        break;
    }
}

// Aqui é para detectar o teclado, mudando de cor
void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        printf("\nCOR MUDADA PARA AZUL\n");
        glColor3f(0.0, 0.0, 1.0);
        break;
    case '2':
        printf("\nCOR MUDADA PARA VERDE\n");
        glColor3f(0.0, 1.0, 0.0);
        break;
    case '3':
        printf("\nCOR MUDADA PARA VERMELHO\n");
        glColor3f(1.0, 0.0, 0.0);
        break;
    case '4':
        printf("\nCOR MUDADA PARA AMARELO\n");
        glColor3f(1.0, 1.0, 0.0);
        break;
    case '5':
        printf("\nCOR MUDADA PARA TURQUESA\n");
        glColor3f(0.0, 1.0, 1.0);
        break;
    case '6':
        printf("\nCOR MUDADA PARA ROSA\n");
        glColor3f(1.0, 0.0, 1.0);
        break;
    case '7':
        printf("\nCOR MUDADA PARA ROXO\n");
        glColor3f(0.5, 0.1, 0.9);
        break;
    case '8':
        printf("\nCOR MUDADA PARA ROXO ESCURO\n");
        glColor3f(0.3, 0.3, 0.5);
        break;
    case '9':
        printf("\nCOR MUDADA PARA MARROM\n");
        glColor3f(0.8, 0.4, 0.2);
        break;
    }
}
// Função main para organizar a lógica
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Ex03");
    printf("CORES: 1 = AZUL, 2 = VERDE, 3 = VERMELHO, 4 = AMARELO, 5 = TURQUESA, "
           "6 = ROSA, 7 = ROXO, 8 = ROXO ESCURO, 9 = MARROM\n");

    linha[5] = 1000;
    linha[3] = 1000;
    linha[1] = 1000;

    glColor3f(1.0, 1.0, 0.0);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(MouseInt);
    glutDisplayFunc(displayFunc);
    glutMainLoop();

    return 0;
}