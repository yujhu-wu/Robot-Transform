#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define TORSO_HEIGHT 5
#define TORSO_RADIUS 2
#define UPPER_ARM_HEIGHT 2.5
#define LOWER_ARM_HEIGHT 2
#define UPPER_ARM_RADIUS  1
#define LOWER_ARM_RADIUS  1
#define UPPER_LEG_RADIUS  1
#define LOWER_LEG_RADIUS  1
#define LOWER_LEG_HEIGHT 2.5
#define UPPER_LEG_HEIGHT 2.5
#define HEAD_HEIGHT 2
#define HEAD_RADIUS 2

typedef float point[3];
static GLfloat theta[11] = {30.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 180.0, 0.0, 180.0, 0.0};
static GLfloat atheta[8] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
static GLint angle = 2;
GLUquadricObj *t, *h, *lua, *lla, *rua, *rla, *lll, *rll, *rul, *lul;
int time3 = 0;
int time4 = 0;
int time5 = 0;
int time6 = 0;
GLboolean isWalk=false;
GLboolean playGun = false;
GLboolean isPunch = false;
GLboolean isJumpDance = false;
GLboolean isWaveHello = false;

void torso()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(t,TORSO_RADIUS, TORSO_RADIUS, TORSO_HEIGHT,10,10);
   glPopMatrix();
}

void head()
{
   glPushMatrix();
   glTranslatef(0.0, 0.5 * HEAD_HEIGHT, 0.0);
   glScalef(HEAD_RADIUS, HEAD_HEIGHT, HEAD_RADIUS);
   gluSphere(h, 1.0, 10, 10);
   glPushMatrix();
   glTranslatef(0.4, 0.4, 1.0);
   gluSphere(h, 0.1, 10, 3);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(-0.4, 0.4, 1.0);
   gluSphere(h, 0.1, 10, 3);
   glPopMatrix();

   // Add nose
   glPushMatrix();
   glColor3f(1.0, 0.5, 0.5);
   glTranslatef(0.0, 0.2, 1.0);
   gluCylinder(h, 0.1, 0.0, 0.5, 10, 10);
   glPopMatrix();

   // Add mouth
   glPushMatrix();
   glColor3f(1.0, 0.0, 0.0);
   glTranslatef(0.0, -0.2, 1.0);
   glScalef(0.5, 0.1, 0.1);
   glutSolidCube(1.0);
   glPopMatrix();

   glPopMatrix();
}

void left_upper_arm()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(lua,UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
   glPopMatrix();
}

void left_lower_arm()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(lla,LOWER_ARM_RADIUS, LOWER_ARM_RADIUS*0.4, LOWER_ARM_HEIGHT,10,10);
   glPopMatrix();
}

void right_upper_arm()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(rua,UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
   glPopMatrix();
}

void right_lower_arm()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(rla,LOWER_ARM_RADIUS, LOWER_ARM_RADIUS*0.4, LOWER_ARM_HEIGHT,10,10);
   glPopMatrix();
}

void left_upper_leg()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(lul,UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT,10,10);
   glPopMatrix();
}

void left_lower_leg()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(lll,LOWER_LEG_RADIUS, LOWER_LEG_RADIUS*0.4, LOWER_LEG_HEIGHT,10,10);
   glPopMatrix();
}

void right_upper_leg()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(rul,UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT,10,10);
   glPopMatrix();
}

void right_lower_leg()
{
   glPushMatrix();
   glRotatef(-90.0, 1.0, 0.0, 0.0);
   gluCylinder(rll,LOWER_LEG_RADIUS, LOWER_LEG_RADIUS*0.4, LOWER_LEG_HEIGHT,10,10);
   glPopMatrix();
}

void left_hand()
{
   glPushMatrix();
   glScalef(0.1, 0.1, 0.1);
   gluSphere(h,1.5,10,10);
   glPopMatrix();
}

void right_hand()
{
   glPushMatrix();
   glScalef(0.1, 0.1, 0.1);
   gluSphere(h,1.5,10,10);
   glPopMatrix();
}

void left_foot()
{
   glPushMatrix();
   glScalef(1, 0.1, 0.5);
   gluSphere(h,1.5,10,10);
   glPopMatrix();
}

void right_foot()
{
   glPushMatrix();
   glScalef(1, 0.1, 0.5);
   gluSphere(h,1.5,10,10);
   glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0, 1, 2);

    glRotatef(theta[0], 0.0, 1.0, 0.0);
    torso();
    glPushMatrix();

    glTranslatef(0.0, TORSO_HEIGHT+0.5*HEAD_HEIGHT, 0.0);
    glRotatef(theta[1], 1.0, 0.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.5*HEAD_HEIGHT, 0.0);
    head();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(TORSO_RADIUS+UPPER_ARM_RADIUS), 0.9*TORSO_HEIGHT, 0.0);
    glRotatef(theta[3], 1.0, 0.0, 0.0);
    glRotatef(atheta[0], 0.0, 0.0, 1.0);
    left_upper_arm();

    glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
    glRotatef(theta[4], 1.0, 0.0, 0.0);
    glRotatef(atheta[1], 0.0, 0.0, 1.0);
    left_lower_arm();

    glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);
    left_hand();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(TORSO_RADIUS+UPPER_ARM_RADIUS, 0.9*TORSO_HEIGHT, 0.0);
    glRotatef(theta[5], 1.0, 0.0, 0.0);
    glRotatef(atheta[2], 0.0, 0.0, 1.0);
    right_upper_arm();

    glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
    glRotatef(theta[6], 1.0, 0.0, 0.0);
    glRotatef(atheta[3], 0.0, 0.0, 1.0);
    right_lower_arm();

    glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);
    right_hand();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(TORSO_RADIUS+UPPER_LEG_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[7], 1.0, 0.0, 0.0);
    glRotatef(atheta[4], 0.0, 0.0, 1.0);
    left_upper_leg();

    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[8], 1.0, 0.0, 0.0);
    glRotatef(atheta[5], 0.0, 0.0, 1.0);
    left_lower_leg();

    glTranslatef(0.0, LOWER_LEG_HEIGHT, 0.0);
    left_foot();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(TORSO_RADIUS+UPPER_LEG_RADIUS, 0.1*UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[9], 1.0, 0.0, 0.0);
    glRotatef(atheta[6], 0.0, 0.0, 1.0);
    right_upper_leg();

    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[10], 1.0, 0.0, 0.0);
    glRotatef(atheta[7], 0.0, 0.0, 1.0);
    right_lower_leg();

    glTranslatef(0.0, LOWER_LEG_HEIGHT, 0.0);
    right_foot();

    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void recover(void)
{
   theta[0] = 30.0;
   theta[1] = 0.0;
   theta[2] = 0.0;
   theta[3] = 0.0;
   theta[4] = 0.0;
   theta[5] = 0.0;
   theta[6] = 0.0;
   theta[7] = 180.0;
   theta[8] = 0.0;
   theta[9] = 180.0;
   theta[10] = 0.0;
   for(int i=0;i<8;i++){
   atheta[i]=0.0;
   }
 }

void midPunch(void)
{
   theta[0] = -40.0;
   theta[1] = 0.0;
   theta[2] = 0.0;
   theta[3] = 0.0;
   theta[4] = 0.0;
   theta[5] = 0.0;
   theta[6] = 0.0;
   theta[7] = 180.0;
   theta[8] = 0.0;
   theta[9] = 180.0;
   theta[10] = 0.0;
   atheta[0] = 90.0;
   atheta[1] = 0.0;
   atheta[2] = 0.0;
   atheta[3] = 90.0;
   atheta[4] = 10.0;
   atheta[5] = 100.0;
   atheta[6] = -90.0;
   atheta[7] = 0.0;
}

void leftPunch(void)
{
   theta[0] = -40.0;
   theta[1] = 0.0;
   theta[2] = 0.0;
   theta[3] = 0.0;
   theta[4] = 0.0;
   theta[5] = 0.0;
   theta[6] = 0.0;
   theta[7] = 180.0;
   theta[8] = 0.0;
   theta[9] = 180.0;
   theta[10] = 0.0;
   atheta[0] = 90.0;
   atheta[1] = 0.0;
   atheta[2] = 0.0;
   atheta[3] = 10.0;
   atheta[4] = 90.0;
   atheta[5] = -90.0;
   atheta[6] = 10.0;
   atheta[7] = 0.0;
}

void rightPunch(void)
{
   theta[0] = 40.0;
   theta[1] = 0.0;
   theta[2] = 0.0;
   theta[3] = 0.0;
   theta[4] = 0.0;
   theta[5] = 0.0;
   theta[6] = 0.0;
   theta[7] = 180.0;
   theta[8] = 0.0;
   theta[9] = 180.0;
   theta[10] = 0.0;
   atheta[0] = 90.0;
   atheta[1] = -90.0;
   atheta[2] = -90.0;
   atheta[3] = 0.0;
   atheta[4] = 90.0;
   atheta[5] = 0.0;
   atheta[6] = -90.0;
   atheta[7] = 90.0;
}

void sayHello(void)
{
    time4 = 0;
    isWalk = false;
    isPunch = false;
    isJumpDance = false;
    for (int i = 0; i < 11; i++)
        theta[i] = 0.0;
    for (int i = 0; i < 8; i++)
        atheta[i] = 0.0;

    isWaveHello = true;
}

void waveHello(void)
{
    theta[7] = 180.0;
    theta[8] = 0.0;
    theta[9] = 180.0;
    theta[10] = 0.0;

    if (time4 < 10)
    {
        atheta[0] = 20.0;
        atheta[1] = -20.0;
    }
    else if (time4 >= 10 && time4 < 20)
    {
        atheta[0] = -20.0;
        atheta[1] = 20.0;
    }

    time4++;
    if (time4 == 20)
        time4 = 0;
}

void TimerFunction(int value)
{
     if (isJumpDance)
    {
        time3 += 1;
        if (time3 < 20)
        {
             theta[0] = 0.0;
            theta[1] = -45.0;
            theta[2] = 0.0;
            theta[3] = -45.0;
            theta[4] = 90.0;
            theta[5] = 140.0;
            theta[6] = -30.0;
            theta[7] = 180.0;
            theta[8] = 0.0;
            theta[9] = 180.0;
            theta[10] = 0.0;
            for (int i = 0; i < 8; i++)
                atheta[i] = 0.0;
        }

        if (time3 >= 20 && time3 < 40)
        {
            theta[0] = 0.0;
            theta[1] = 20.0;
            theta[2] = 0.0;
            theta[3] = -45.0;
            theta[4] = -90.0;
            theta[5] = 230.0;
            theta[6] = -30.0;
            theta[7] = 180.0;
            theta[8] = 90.0;
            theta[9] = 180.0;
            theta[10] = 0.0;

            for (int i = 0; i < 8; i++)
                atheta[i] = 0.0;
        }

        if (time3 == 40)
        {
            time3 = 0;
        }
    }

   if(isWalk)
   {
       time3 += 1;
       if(time3 < 20)
       {
           theta[0] = 30.0;
           theta[1] = 0.0;
           theta[2] = -10.0;
           theta[3] = 230.0;
           theta[4] = -30.0;
           theta[5] = 140.0;
           theta[6] = -30.0;
           theta[7] = 100.0;
           theta[8] =  70.0;
           theta[9] = 180.0;
           theta[10]= 0.0;
           for(int i = 0 ; i < 8 ; i++)
                 atheta[i]=0.0;
       }

       if(time3 >= 20 && time3 < 40)
       {
           theta[0] = 30.0;
           theta[1] = 0.0;
           theta[2] = 10.0;
           theta[3] = 140.0;
           theta[4] = -30.0;
           theta[5] = 230.0;
           theta[6] = -30.0;
           theta[7] = 180.0;
           theta[8] =   0.0;
           theta[9] = 120.0;
           theta[10] = 70.0;
           for(int i = 0 ; i < 8 ; i++)
                 atheta[i]=0.0;
       }
       if(time3 == 40)
       {
                time3 = 0;
       }
   }

   if(isPunch)
   {
              if(time6 < 10)
                       rightPunch();
              else if(time6 >= 10 && time6 < 20)
                   leftPunch();
                   else if(time6 >= 20 && time6 < 30)midPunch();
              time6++;
              if(time6 == 30)
                       time6 = 0;
   }

   if (isWaveHello)
        waveHello();

   glutPostRedisplay();
   glutTimerFunc(33,TimerFunction, 1);
 }

void jump(void)
{
    theta[0] = 0.0;
    theta[1] = -45.0;
    theta[2] = 0.0;
    theta[3] = -45.0;
    theta[4] = 90.0;
    theta[5] = -90.0;
    theta[6] = 90.0;
    theta[7] = 180.0;
    theta[8] = -90.0;
    theta[9] = 180.0;
    theta[10] = 0.0;

    for (int i = 0; i < 8; i++)
        atheta[i] = 0.0;
}

void mouse(int btn, int state, int x, int y)
{
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
        theta[angle] += 5.0;
        if( theta[angle] > 360.0 ) theta[angle] -= 360.0;
        }
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
        theta[angle] -= 5.0;
        if( theta[angle] < 360.0 ) theta[angle] += 360.0;
        }
        display();
}

void menu(int id)
{
   if(id <11 ) angle=id;
   if(id ==11 ) exit(0);
}

void action_menu(int id)
{
    if (id == 0)
        recover();
    if (id == 1)
        isWalk = true;
    else
        isWalk = false;
    if (id == 2)
        isPunch = true;
    else
        isPunch = false;
    if (id == 3)
    {
        isJumpDance = !isJumpDance;
        if (isJumpDance)
            jump();
    }
    if (id == 4)
        sayHello();
    display();
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-10.0, 10.0, -10.0 * (GLfloat) h / (GLfloat) w,
            10.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-10.0 * (GLfloat) w / (GLfloat) h,
            10.0 * (GLfloat) w / (GLfloat) h, 0.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myinit()
{
        GLfloat mat_specular[]={1.0, 1.0, 1.0, 1.0};
        GLfloat mat_diffuse[]={1.0, 1.0, 1.0, 1.0};
        GLfloat mat_ambient[]={1.0, 1.0, 1.0, 1.0};
        GLfloat mat_shininess={100.0};
        GLfloat light_ambient[]={0.0, 0.0, 0.0, 1.0};
        GLfloat light_diffuse[]={1.0, 1.0, 0.0, 1.0};
        GLfloat light_specular[]={1.0, 1.0, 1.0, 1.0};
        GLfloat light_position[]={10.0, 10.0, 10.0, 0.0};

        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

        glShadeModel(GL_SMOOTH);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_DEPTH_TEST);

        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT);
        glEnable(GL_COLOR_MATERIAL);
        glClearColor(0, 0, 0.5, 1);

/* allocate quadrics with filled drawing style */

        h=gluNewQuadric();
        gluQuadricDrawStyle(h, GLU_FILL);
        t=gluNewQuadric();
        gluQuadricDrawStyle(t, GLU_FILL);
        lua=gluNewQuadric();
        gluQuadricDrawStyle(lua, GLU_FILL);
        lla=gluNewQuadric();
        gluQuadricDrawStyle(lla, GLU_FILL);
        rua=gluNewQuadric();
        gluQuadricDrawStyle(rua, GLU_FILL);
        rla=gluNewQuadric();
        gluQuadricDrawStyle(rla, GLU_FILL);
        lul=gluNewQuadric();
        gluQuadricDrawStyle(lul, GLU_FILL);
        lll=gluNewQuadric();
        gluQuadricDrawStyle(lll, GLU_FILL);
        rul=gluNewQuadric();
        gluQuadricDrawStyle(rul, GLU_FILL);
        rll=gluNewQuadric();
        gluQuadricDrawStyle(rll, GLU_FILL);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Robot Transform");
    myinit();
    glutReshapeFunc(myReshape);
    glutTimerFunc(33, TimerFunction, 1);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutCreateMenu(menu);
    glutAddMenuEntry("torso", 0);
    glutAddMenuEntry("head1", 1);
    glutAddMenuEntry("head2", 2);
    glutAddMenuEntry("right_upper_arm", 3);
    glutAddMenuEntry("right_lower_arm", 4);
    glutAddMenuEntry("left_upper_arm", 5);
    glutAddMenuEntry("left_lower_arm", 6);
    glutAddMenuEntry("right_upper_leg", 7);
    glutAddMenuEntry("right_lower_leg", 8);
    glutAddMenuEntry("left_upper_leg", 9);
    glutAddMenuEntry("left_lower_leg", 10);
    glutAddMenuEntry("quit", 11);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
    glutCreateMenu(action_menu);
    glutAddMenuEntry("Attention",0);
    glutAddMenuEntry("Walk",1);
    glutAddMenuEntry("Crazy Dance",2);
    glutAddMenuEntry("Hurray!", 3);
    glutAddMenuEntry("Say Hello", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}