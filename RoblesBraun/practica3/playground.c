#include <stdio.h>

int letra[][2] =    {{200, 200}, {200, 50}, {220, 50}, {220, 200}, //rectangulo izquierdo
                    {220, 200}, {220, 220}, {280, 220}, {280, 200}, // rectangulo superior
                    {280, 200}, {280, 50}, {300, 50}, {300, 200}, // rectangulo izquierdo
                    {220, 50}, {220, 30}, {280, 30}, {280, 50} // rectangulo inferior
                };

int main(int argc, char const *argv[])
{
    printf("%d", letra[5][1] + 10);
    return 0;
}
