#include "visualization.h"
#include "../Dataset/point.h"
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#define pi 3.142857
#include <stdio.h>
#include <stdlib.h>
#include "../Utils/utils.h"
 
/* Global variables */
char title[] = "3D Shapes";
int * visualization_cluster;
int visualization_n_points;
int visualization_K;
float angle = 00.0f;
int visualize_cube;
 
/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(255.0f, 255.0f, 255.0f, 255.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}
 
/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
    while (1){
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
   glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
 
   // Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();                 // Reset the model-view matrix
   if (visualize_cube == 0){
   glTranslatef(-20.0f, -20.0f, -100.0f);  // Move right and into the screen
   glRotatef(angle, angle, angle, angle);
glPointSize(3.0f);  
   }
   else{
   glTranslatef(0.0f, -0.1f, -0.5f);  // Move right and into the screen
   glRotatef(angle, 0, 1, 0);
   glPointSize(1.0f);

   }

    glBegin(GL_POINTS); 
    for (int i=0; i<visualization_n_points; i++){
        switch (visualization_cluster[i]) {
            case 0: 
                glColor3f(0.0f, 1.0f, 0.0f);     // Green
                break;
            case 1: 
                glColor3f(0.5f, 0.0f, 1.0f); // make this vertex purple;
                break;
            case 2: 
                glColor3f(1.0f, 0.0f, 0.0f); // make this vertex red
                break;
            case 3: 
                glColor3f(1.0f, 1.0f, 0.0f); // make this vertex yellow
                break;
            case 4: 
                glColor3f(1.0f, 0.5f, 0.0f);     // brown
                break;
            default: 
                glColor3f(0.0f, 0.0f, 1.0f);     // Blue
                break;            

        }
      glVertex3f( getValue(points, i,0,3) , getValue(points, i,1,3), getValue(points, i,2,3));
    }
    glEnd();

 
   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
        angle += 0.5f;

    if (angle >= 360.f)
    angle = 0.0f;
    }
}
 
/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
 
/* Main function: GLUT runs as a console application starting at main() */
void showResult(int * cluster, int n_points, int K, int argc, char *argv[], int dataCube){
    visualization_cluster = cluster;
    visualization_n_points = n_points;
    visualization_K = K;
    visualize_cube = dataCube;

   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}

