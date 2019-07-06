#include<GL/glut.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

static int window;
static int menu_id;
static int value = 0;
char city_name[10] = {'A', 'B', 'C', 'D', 'E', 'F'};
int ary[10][10],completed[10],n,cost=0, top=-1, path[10], min_pos=0, pos=0, city=0, city_prev=0, i=0, j=0, k, disp_x=100, disp_y=800, show_x=100, show_y=800, mat_x=-300, mat_y=1400, source;
char str[100];
char minicost[5], first;

float vector3[][2] = {{0, 0}, {820, 0}, {410, 820}};
float vector4[][2] = {{0, 0}, {820, 0}, {0, 820}, {820, 820}};
float vector5[][2] = {{0, 0}, {820, 0}, {0, 480}, {820, 480}, {410, 820}};
float vector6[][2] = {{410, 820}, {410, 0}, {0, 220}, {820, 220}, {0, 580}, {820, 580}};

int doneInput = 0;
int keypa=0;

//char str[20];

char line1[] = {"JSS Academy of Technical Education, Bangalore"};
char line2[] = {"Computer Science Department"};
char line3[] = {"Computer Graphics project"};
char line8[] = {"Topic: Traveling Salesperson Problem"};
char line4[] = {"Submitted By : "};
char line5[] = {"Cauvery A : 1JS16CS031"};
char line6[] = {"Akshitha Y V : 1JS16CS010"};
char line7[] = {"Press 1 to enter the main page"};
char line9[] = {"Under The Guidance Of : "};
char line10[] = {"Mrs. Rashmi B N"};
char line11[] = {"Assisant Professor."};
char line12[] = {"Mr. Sharana Basavana Gowda"};

//Function to display text at given position in given color
void displayText( float x, float y, int r, int g, int b, char *string )
{
    int j = strlen (string);
    glColor3f( r, g, b );
    glRasterPos2f( x, y );
    for( int i = 0; i < j; i++ )
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
    glFlush();
}

void displayTextSmall(float x, float y, int r, int g, int b, char *string)
{
	int j = strlen (string);
    glColor3f( r, g, b );
    glRasterPos2f( x, y );
    for( int i = 0; i < j; i++ )
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, string[i] );
    glFlush();
}

//First page
void displayfirst(void)
{
    displayText(-10, 850, 0, 0, 1,line1);
    displayText(150, 800, 0, 0, 0,line2);
    displayText(200, 750, 0, 0, 0,line3);
    displayText(100, 700, 1, 0, 0,line8);
    displayText(-350, 150, 1, 0, 0,line4);
    displayText(-350, 100,0, 0, 0,line5);
    displayText(-350, 50, 0, 0, 0,line6);
    displayText(150,500,0,1,0,line7);
    displayText(750,150,1,0,0,line9);
    displayText(750,100,0,0,0,line10);
    displayTextSmall(750,50,0,0,0,line11);
    displayText(750,0,0,0,0,line12);
    displayTextSmall(750,-50,0,0,0,line11);
    
    glFlush();
}

void displaysec(void)
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    displayText(-100,900,0,0,0,"ENTER THE NUMBER OF CITIES: ");
    constr();
    glFlush();
}

void constr()
{
    displayText(-100,300,0,0,0,"PLEASE NOTE : ");
    displayText(-100,275,0,0,0,"____________");
    displayText(-100,150,0,0,1,"-> The number of cities is limited to 6.");
    displayText(-100,100,0,0,1,"-> The input to the cost matrix is limited to single digit.");
    displayText(-100,50,0,0,1,"-> This algorithm  is for directed graph and all nodes must be reachable"); 
    displayTextSmall(-100,-50,0,0,0,"Made by Cauvery & Akshitha.");
}


void displaythird(void)
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    displayText(-100,900,0,0,0,"ENTER THE COST MATRIX : ");
    constr();
    glFlush();
}

int least(int c)
{
    int i,nc=999;
    int min=999,kmin;
 
    for(i=0;i < n;i++)
    {
        if((ary[c][i]!=0)&&(completed[i]==0))
            if(ary[c][i]+ary[i][c] < min)
            {
                min=ary[i][0]+ary[c][i];
                kmin=ary[c][i];
                nc=i;
            }
    }
 
    if(min!=999)
        cost+=kmin;
 
    return nc;
}

//calculates the minimum cost
void mincost(int city)
{
    int i,ncity;
 
    completed[city]=1;
    //printf("%d--->",city+1);
    path[pos++] = city;
  
    ncity=least(city);
 
    if(ncity==999)
    {
        ncity=0;
        //printf("%d\n",ncity+1);
        path[pos++] = ncity;
      
        cost+=ary[city][ncity];
 
        return;
    }
 
    mincost(ncity);
}

//Green land
void land(float x, float y)
{
    glColor3f(0.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + 90, y - 30);
        glVertex2f(x + 180, y);
        glVertex2f(x + 210, y + 90);
        glVertex2f(x + 180, y + 180);
        glVertex2f(x + 90, y + 210);
        glVertex2f(x, y + 180);
        glVertex2f(x - 30, y + 90);
    glEnd();
}

//Road with block and white stripped line
void road(float start_x, float start_y, float end_x, float end_y)
{
    float width = end_x - start_x;
    float height = end_y - start_y;
 
    float thickness = 50;
    float length = sqrt(width * width + height * height);
 
    float xs = (thickness * height / length) / 2;
    float ys = (thickness * width / length) / 2;
 
    glColor3f(0.4, 0.4, 0.4);
    glBegin(GL_POLYGON);
        glVertex2f(start_x - xs, start_y + ys);
        glVertex2f(start_x + xs, start_y - ys);
        glVertex2f(end_x + xs, end_y - ys);
        glVertex2f(end_x - xs, end_y + ys);
    glEnd();
    
      glEnable(GL_LINE_STIPPLE);
      glLineWidth(3);
    glLineStipple(1, 0x00FF);
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
        glVertex2f(start_x, start_y);
        glVertex2f(end_x, end_y);
    glEnd();
}

//Salesman Representation
void object(float x, float y)
{
    glColor3f(0.7, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(x - 30, y);
        glVertex2f(x, y + 30);
        glVertex2f(x + 30, y);
        glVertex2f(x, y - 30);
    glEnd();
}

void lines(float x, float y, float x1,float y1)
{
    glDisable(GL_LINE_STIPPLE);
    glColor3f(0.7, 0.0, 0.0);
    glLineWidth(10);
    glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x1, y1);
    glEnd();
}

void displayMatrix()
{
    int p, r;
    char q;
    mat_x=-350;
    mat_y=1300;
    displayText(-400,1400,0,0,0,"INPUT MATRIX :");
    for(p=0;p<value;p++)
    {
        q = city_name[p];
        displayText(mat_x,mat_y,0,0,0,&q);
        mat_x += 50;
    }
    mat_x = -400;
    mat_y = 1250;
    for(p=0;p<value;p++)
    {
        q = city_name[p];
        displayText(mat_x,mat_y,0,0,0,&q);
        mat_y -= 50;
    }
    mat_x = -350;
    mat_y = 1250;
  
    for(r=0;r<value;r++)
    {
        for(p=0;p<value;p++)
        {
            q = ary[r][p] + '0';
            displayText(mat_x,mat_y,0,0,1,&q);
            mat_x += 50;
        }
        mat_x = -350;
        mat_y -= 50;
    }
}

//To show min path on window
void showMinPathCost()
{
    char p;
    show_x=100;
    /*glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);*/
    displayText(100,-200,0,0,0,"THE BEST PATH IS :");
    for(k=0;k<n;k++)
    {
        //str[k] = path[k]+'1';
        p = city_name[path[k]];
        displayText(show_x,-300,0,0,1,&p);
        displayText(show_x+50,-300,0,0,0,"--->");
        show_x = show_x + 180;
        //printf("%c\t",str[k]);
    }
    first = city_name[path[0]];
    displayText(show_x,-300,0,0,1,&first);
    
    sprintf(minicost, "%d", cost);
    displayText(100,-400,0,0,0,"THE MINIMUM COST IS :");
    displayText(700,-400,0,0,1,&minicost);
    glFlush();
}

void menu(int num)
{
    if(num == 1)
    {
        glutDestroyWindow(window);
        exit(0);
    }
    else if(num == 2)
    {
        showMinPathCost();
    }
    glutPostRedisplay();
}

void createMenu(void)
{
    menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("QUIT", 1);
    glutAddMenuEntry("MINIMUM COST AND BEST PATH", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//To display the land,road and the object
void display(void)
{
    int i, j, k;
    char p;
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
   
    if(value == 3)
    {
    
        glClear( GL_COLOR_BUFFER_BIT);
        
        for(j=0;j<value;j++)
        {
            for(k=0;k<value;k++)
            {
                if(j == k)
                    ary[j][k] = 0;
            
                if(ary[j][k] != 0)
                    road(vector3[j][0]+90, vector3[j][1]+90, vector3[k][0]+90, vector3[k][1]+90);
            }
        }
    
        for(i=0;i<value;i++)
        {
            land(vector3[i][0], vector3[i][1]);
            p = city_name[i];
            displayText(vector3[i][0]+70, vector3[i][1]+70,1,1,1,&p);
        }
        
        object(vector3[city][0] + 90, vector3[city][1] + 90);
        lines(vector3[city_prev][0] + 90, vector3[city_prev][1] + 90, vector3[city][0] + 90, vector3[city][1] + 90);
    }
    
    
    else if(value == 4)
    {
    
        glClear( GL_COLOR_BUFFER_BIT);
        for(j=0;j<value;j++)
        {
            for(k=0;k<value;k++)
            {
                if(j == k)
                    ary[j][k] = 0;
            
                if(ary[j][k] != 0)
                    road(vector4[j][0]+90, vector4[j][1]+90, vector4[k][0]+90, vector4[k][1]+90);
            }
        }
    
        for(i=0;i<value;i++)
        {
            land(vector4[i][0], vector4[i][1]);
             p = city_name[i];
            displayText(vector4[i][0]+70, vector4[i][1]+70,1,1,1,&p);
        }
        object(vector4[city][0] + 90, vector4[city][1] + 90);
        lines(vector4[city_prev][0] + 90, vector4[city_prev][1] + 90, vector4[city][0] + 90, vector4[city][1] + 90);
    }
    
    
    else if(value == 5)
    {
    
        glClear( GL_COLOR_BUFFER_BIT);
        
        for(j=0;j<value;j++)
        {
            for(k=0;k<value;k++)
            {
                if(j == k)
                    ary[j][k] = 0;
            
                if(ary[j][k] != 0)
                    road(vector5[j][0]+90, vector5[j][1]+90, vector5[k][0]+90, vector5[k][1]+90);
            }
        }
    
        for(i=0;i<value;i++)
        {
            land(vector5[i][0], vector5[i][1]);
            p = city_name[i];
            displayText(vector5[i][0]+70, vector5[i][1]+70,1,1,1,&p);
        }
        
        object(vector5[city][0] + 90, vector5[city][1] + 90);
        lines(vector5[city_prev][0] + 90, vector5[city_prev][1] + 90, vector5[city][0] + 90, vector5[city][1] + 90);
    }
    
    
    else if(value == 6)
    {
    
        glClear( GL_COLOR_BUFFER_BIT);
    
        for(j=0;j<value;j++)
        {
            for(k=0;k<value;k++)
            {
                if(j == k)
                    ary[j][k] = 0;
            
                if(ary[j][k] != 0)
                    road(vector6[j][0]+90, vector6[j][1]+90, vector6[k][0]+90, vector6[k][1]+90);
            }
        }
    
        for(i=0;i<value;i++)
        {
            land(vector6[i][0], vector6[i][1]);
            p = city_name[i];
            displayText(vector6[i][0]+70, vector6[i][1]+70,1,1,1,&p);
        }
        
        object(vector6[city][0] + 90, vector6[city][1] + 90);
        lines(vector6[city_prev][0] + 90, vector6[city_prev][1] + 90, vector6[city][0] + 90, vector6[city][1] + 90);
    }
    /*sprintf(minicost, "%d", cost);
    displayText(100,-400,0,0,0,"THE MINIMUM COST IS :");
    displayText(700,-400,0,0,1,&minicost);*/
    displayMatrix();
  
    glFlush();
    if(keypa == 3)
        createMenu();
}

//Reshape function
void myReshape(int w,int h)
{
    glClearColor(1,1,1,1);
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h)
            glOrtho(-2,2,-2*(GLfloat)h/(GLfloat)w,2*(GLfloat)h/(GLfloat)w,-10,10);
    else
            glOrtho(-2*(GLfloat)w/(GLfloat)h,2*(GLfloat)w/(GLfloat)h,-2,2,-10,10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 
    gluOrtho2D(0,1000,0,1000);
}

//Keyboard function
void key(unsigned char k,int x,int y)
{
    char a=k;
    int num;
    if(keypa==0 && !doneInput)
    {
        if(a == '1')
        {
            //printf("done\n");
            displaysec();
            keypa = 1;
        }
    }
    else if(keypa==1 && !doneInput)
    {
        if(isdigit(a))
        {
            num = a - '0';
            if(num>=3 && num<=6)
            {
                n = num;
                displayText(800,900,1,0,0,&a);
                keypa=2;
                usleep(500000);
                displaythird();
            }
            else
            {
                displayText(15,500,1,0,0,"ERROR!! SPECIFY NUMBER OF CITIES BETWEEN 3 AND 6");
                usleep(700000);
                displaysec();
            }
        }
    }
    else if(keypa==2 && !doneInput)
    {
        if(isdigit(a))
        {
            num = a - '0';
            ary[i][j] = num;
            displayText(disp_x,disp_y,1,0,0,&a);
            j++;
            disp_x = disp_x + 75;
            if(j>=n)
            {
                j=0;
                i++;
                disp_x = 100;
                disp_y = disp_y - 75;
            }
            if(i>=n)
            {
                usleep(500000);
                doneInput = 1;
                value = n;
                i=0;
                j=0;
                mincost(0);
                keypa=3;
                display();
            }
        }
    }
    else if(keypa==3 && doneInput)
    {
        if(a=='e' || a=='E')
        {
            keypa=0;
            doneInput=0;
            glClearColor(1,1,1,1);
            glClear(GL_COLOR_BUFFER_BIT);
            displayfirst();
        }
    }
}

//Mouse Function
void myMouseFunc(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && keypa==3)
    {
        if(i == pos)
            i = 0;
        //if(min_pos == n) min_pos = 0;
 
        city = path[i];
        city_prev = path[i-1];
        //printf("%d\t", i);
        i++;
        display();
      
    }
}

//First display screen
void disp()
{
    if(keypa < 1)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        displayfirst();
    }
}

//Main function
int main(int argc, char** argv)
{
	char c;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(0,0);
    window = glutCreateWindow("TRAVELLING SALESMAN PROBLEM");
    glutDisplayFunc(disp);
    glutMouseFunc(myMouseFunc);
    glutKeyboardFunc(key);
    glutReshapeFunc(myReshape);
	glutMainLoop();
    return EXIT_SUCCESS;
}
