// C++ code for Tic-Tac-Toe using OpenGL

#include <GL/glut.h>
#include <bits/stdc++.h>
#include <GL/freeglut.h>

using namespace std;

int window_width = 1350, window_height = 690;
int boxes[9][4] = {{450,600,420,570}, {600,750,420,570}, {750,900,420,570},
                    {450,600,270,420}, {600,750,270,420}, {750,900,270,420},
                    {450,600,120,270}, {600,750,120,270}, {750,900,120,270}};
float color_box[9][3] = {{0.2f, 0.4f, 0.7f}, {0.2f, 0.4f, 0.7f}, {0.2f, 0.4f, 0.7f},
                        {0.2f, 0.4f, 0.7f}, {0.2f, 0.4f, 0.7f}, {0.2f, 0.4f, 0.7f},
                        {0.2f, 0.4f, 0.7f}, {0.2f, 0.4f, 0.7f}, {0.2f, 0.4f, 0.7f}};
float restart_red = 0.7f, restart_green = 0.3f, restart_blue = 0.5f;
bool player_A_wins = false, player_B_wins = false, game_finished = false, draw = false;
char moves[3][3] = {{' ', ' ', ' '},
                    {' ', ' ', ' '},
                    { ' ', ' ', ' '}};
int filled_boxes = 0;
char players[2] = {'X', 'O'};
int turn = 0;
int restart_x1 = 1050, restart_x2 = 1200, restart_y1 = 320, restart_y2 = 380;
void initGL()
{
    glClearColor(0.2f, 0.4f, 0.1f, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, window_width, 0, window_height);
}

void drawString(float x, float y, float z, char * str, float r, float g, float b)
{
    glColor3f(r, g, b);
    glRasterPos3f(x, y, z);
    for (char* c = str; *c != '\0';c++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}

void drawStrokeText(float x, float y, float z, char* str, float r, float g, float b, float scalex, float scaley, float scalez)
{
      glColor3f(r, g, b);
      glPushMatrix();
      glTranslatef(x, y, z);
      glScalef(scalex, scaley, scaley);
      for (char *c= str; *c != '\0'; c++)
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN  , *c);
      glPopMatrix();
}

void passive_motion(int x, int y)
{
    y = window_height - y;
    for(int i = 0; i < 9; i++)
    {
        if(x >= boxes[i][0] && x <= boxes[i][1] && y >= boxes[i][2] && y <= boxes[i][3])
        {
            color_box[i][0] = 0.8f;
            color_box[i][1] = 0.3f;
            color_box[i][2] = 0.2f;
            glutPostRedisplay();
        }
        else
        {
            color_box[i][0] = 0.3f;
            color_box[i][1] = 0.4f;
            color_box[i][2] = 0.7f;
            glutPostRedisplay();
        }
    }
    if(game_finished && x >= restart_x1 && x <= restart_x2 && y >= restart_y1 && y <= restart_y2)
    {
        restart_red = 0.8f;
        restart_green = 0.5f;
        restart_blue = 0.2f;
        restart_x1 = 1045;
        restart_x2 = 1205;
        restart_y1 = 315;
        restart_y2 = 385;
        glutPostRedisplay();
    }
    else
    {
        restart_red = 0.7f;
        restart_green = 0.3f;
        restart_blue = 0.5f;
        restart_x1 = 1050;
        restart_x2 = 1200;
        restart_y1 = 320;
        restart_y2 = 380;
        glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y)
{
    y = window_height - y;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !game_finished)
    {
        for(int i = 0; i < 9; i++)
        {
            if(x >= boxes[i][0] && x <= boxes[i][1] && y >= boxes[i][2] && y <= boxes[i][3])
            {
                if(moves[i/3][i%3] == ' ')
                {
                    moves[i/3][i%3] = players[turn%2];
                    turn++;
                    glutPostRedisplay();
                }
            }
        }
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (game_finished) && x >= restart_x1 && x <= restart_x2 && y >= restart_y1 && y <= restart_y2)
    {
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                moves[i][j] = ' ';
        player_A_wins = false;
        player_B_wins = false;
        game_finished = false;
        turn = 0;
        draw = false;
        glutPostRedisplay();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawStrokeText(435, 600, 0, "Tic-Tac-Toe", 1.0f,1.0f, 1.0f, 0.4f,0.4f, 1.0f);
    int k;
    for(k = 0; k < 9; k++)
    {
        glColor3f(color_box[k][0], color_box[k][1], color_box[k][2]);
        glBegin(GL_POLYGON);
            glVertex2i(boxes[k][0], boxes[k][3]);
            glVertex2i(boxes[k][0], boxes[k][2]);
            glVertex2i(boxes[k][1], boxes[k][2]);
            glVertex2i(boxes[k][1], boxes[k][3]);
        glEnd();
    }
    glLineWidth(2);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
        glVertex2i(boxes[0][0], boxes[0][3]);
        glVertex2i(boxes[0][0], boxes[7][2]);

        glVertex2i(boxes[0][0], boxes[7][2]);
        glVertex2i(boxes[2][1], boxes[7][2]);

        glVertex2i(boxes[2][1], boxes[7][2]);
        glVertex2i(boxes[2][1], boxes[0][3]);

        glVertex2i(boxes[2][1],boxes[0][3]);
        glVertex2i(boxes[0][0], boxes[0][3]);

        glVertex2i(boxes[0][0] + (boxes[2][1]-boxes[0][0])/3, boxes[0][3]);
        glVertex2i(boxes[0][0] + (boxes[2][1]-boxes[0][0])/3, boxes[7][2]);

        glVertex2i(boxes[0][0] + 2*(boxes[2][1]-boxes[0][0])/3, boxes[0][3]);
        glVertex2i(boxes[0][0] + 2*(boxes[2][1]-boxes[0][0])/3, boxes[7][2]);

        glVertex2i(boxes[0][0], boxes[7][2] + (boxes[0][3]-boxes[7][2])/3);
        glVertex2i(boxes[2][1], boxes[7][2] + (boxes[0][3]-boxes[7][2])/3);

        glVertex2i(boxes[0][0], boxes[7][2] + 2*(boxes[0][3]-boxes[7][2])/3);
        glVertex2i(boxes[2][1], boxes[7][2] + 2*(boxes[0][3]-boxes[7][2])/3);
    glEnd();
    drawStrokeText(50, 360, 0, "PLAYER A --> X", 1.0f, 1.0f, 1.0f, 0.25f, 0.25f, 1.0f);
    drawStrokeText(50, 300, 0, "PLAYER B --> O", 1.0f, 1.0f, 1.0f, 0.25f, 0.25f, 1.0f);
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
        {
            string t(1, moves[i][j]);
            char temp[1];
            strcpy(temp, t.c_str());
            drawStrokeText(boxes[0][0]+50 + j*150, (boxes[0][3]-100) - i*150, 0, temp, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 1.0f);
        }
    if(moves[0][0] == 'X' && moves[1][1] == 'X' && moves[2][2] == 'X')
    {
        player_A_wins = true;
        player_B_wins = false;
        game_finished = true;
    }
    if(moves[0][0] == 'O' && moves[1][1] == 'O' && moves[2][2] == 'O')
    {
        player_A_wins = false;
        player_B_wins = true;
        game_finished = true;
    }
    if(moves[0][2] == 'X' && moves[1][1] == 'X' && moves[2][0] == 'X' )
    {
        player_A_wins = true;
        player_B_wins = false;
        game_finished = true;
    }
    if(moves[0][2] == 'O' && moves[1][1] == 'O' && moves[2][0] == 'O' )
    {
        player_A_wins = false;
        player_B_wins = true;
        game_finished = true;
    }
    for(int i = 0; i < 3; i++)
    {
        if(moves[i][0] == 'X' && moves[i][1] == 'X' && moves[i][2] == 'X')
        {
            player_A_wins = true;
            player_B_wins = false;
            game_finished = true;
            break;
        }
        if(moves[i][0] == 'O' && moves[i][1] == 'O' && moves[i][2] == 'O')
        {
            player_A_wins = false;
            player_B_wins = true;
            game_finished = true;
            break;
        }
        if(moves[0][i] == 'X' && moves[1][i] == 'X' && moves[2][i] == 'X')
        {
            player_A_wins = true;
            player_B_wins = false;
            game_finished = true;
            break;
        }
        if(moves[0][i] == 'O' && moves[1][i] == 'O' && moves[2][i] == 'O')
        {
            player_A_wins = false;
            player_B_wins = true;
            game_finished = true;
            break;
        }
    }
    if(turn == 9 && !game_finished)
    {
        draw = true;
        game_finished = true;
        player_A_wins = false;
        player_B_wins = false;
        turn ++;
    }
    if(player_A_wins)
        drawStrokeText(460, 50, 0, "PLAYER A WINS", 1.0f, 1.0f, 0.0f, 0.3f, 0.3f, 0.3f);
    if(player_B_wins)
        drawStrokeText(460, 50, 0, "PLAYER B WINS", 1.0f, 1.0f, 0.0f, 0.3f, 0.3f, 0.3f);
    if(turn%2 == 0 && !game_finished && !draw)
        drawStrokeText(920, 340, 0, "PLAYER A PLAYS!!", 1.0f, 1.0f, 1.0f, 0.25f, 0.25f, 1.0f);
    if(turn % 2 != 0 && !game_finished && !draw)
        drawStrokeText(920, 340, 0, "PLAYER B PLAYS!!", 1.0f, 1.0f, 1.0f, 0.25f, 0.25f, 1.0f);
    if(draw)
        drawStrokeText(500, 50, 0, "GAME DRAW!!", 1.0f, 1.0f, 0.0f, 0.3f, 0.3f, 0.3f);
    if(game_finished)
    {
        glColor3f(restart_red, restart_green, restart_blue);
        glBegin(GL_POLYGON);
            glVertex2i(restart_x1, restart_y2);
            glVertex2i(restart_x1, restart_y1);
            glVertex2i(restart_x2, restart_y1);
            glVertex2i(restart_x2, restart_y2);
        glEnd();
        drawString(1070, 340, 0, "RESTART", 1.0f, 1.0f, 1.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);
            glVertex2i(restart_x1, restart_y2);
            glVertex2i(restart_x1, restart_y1);

            glVertex2i(restart_x1, restart_y1);
            glVertex2i(restart_x2, restart_y1);

            glVertex2i(restart_x2, restart_y1);
            glVertex2i(restart_x2, restart_y2);

            glVertex2i(restart_x2, restart_y2);
            glVertex2i(restart_x1, restart_y2);
        glEnd();
    }
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(0, 5);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("Tic-Tac-Toe");
    initGL();
    glutDisplayFunc(display);
    glutPassiveMotionFunc(passive_motion);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
