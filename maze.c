#include "maze.h"
#include "types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 128

struct _Point{
    int x, y;
    char symbol;

    bool visited;
};

struct _Maze {
 int ncols, nrows;
 Point *in, *out;
 Point **map;
};

Point *point_new(int x, int y, char symbol) {
    if (x<0 || y<0) {
        return NULL;
    }

    Point *p = (Point*)malloc(sizeof(Point));
    if (p == NULL) {
        return NULL;
    }

    if (symbol == 'E') {
        p->symbol = ERRORCHAR;
    } else if (symbol == '+') {
        p->symbol = WALL;
    } else if (symbol == 'i') {
        p->symbol = IN;
    } else if (symbol == 'o') {
        p->symbol = OUT;
    } else if (symbol == '.') {
        p->symbol = SPACE;
    } else {
        free(p);
        return NULL;
    }

    p->x = x;
    p->y = y;

    return p;
}

void point_free(Point *p){ free(p); }

int point_getX(const Point *p){ 
    if (p == NULL) {
        return MAX;
    }
    return p->x;
}

int point_getY(const Point *p){
    if (p == NULL) {
        return MAX;
    }
    return p->y;
}

char point_getSymbol(const Point *p){ 
    if (p == NULL) {
        return ERROR;
    }

    return p->symbol;
}

Status point_setX(Point *p, int x){

    if(p==NULL || x<0)
        return ERROR;

    p->x=x;

    return OK;   
}

Status point_setY(Point *p, int y){

    if(p == NULL || y<0)
        return ERROR;

    p->y=y;
    return OK;
}

Status point_setSymbol(Point *p, char c) {
    if (p == NULL || c == '\0') {
        return ERROR;
    }
    if (c == '+') {
        p->symbol = WALL;
    } else if (c == 'i') {
        p->symbol = IN;
    } else if (c == 'o') {
        p->symbol = OUT;
    } else if (c == '.') {
        p->symbol = SPACE;
    } else {
        p->symbol = ERRORCHAR;
        return ERROR;
    }
    return OK;
}

bool point_getVisited(const Point *p){ 
    if (p == NULL) {
        return NULL;
    }
    return p->visited;
}

Status point_setVisited(Point *p, bool value){ 
    if (p == NULL) {
        return ERROR;
    }

    p->visited = value;
    
    return OK;
}



Point *point_hardcpy(const Point *p){

    Point *q;

    q= point_new(0, 0, '+');

    q->x=p->x;
    q->y=p->y;
    q->symbol=p->symbol;

    if(q->x==p->x && q->y==p->y && q->y==p->y)
        return q;
    
    else    
        return NULL;
}

bool point_equal(const void *p1, const void *p2){

    if (p1 == NULL || p2 == NULL) {
        return false;
    }
    const Point *q1= (const Point*) p1;
    const Point *q2= (const Point*) p2;

    if(q1->x==q2->x && q1->y==q2->y && q1->symbol==q2->symbol)
        return true;

    else    
        return false;
}

int point_print(FILE *pf, const void *p){

    const Point *point = (const Point *) p; 
    

    if (point == NULL || pf == NULL) {
        return -1; 
    }
    
    int result = fprintf(pf, "[(%d, %d): %c]", point->x, point->y, point->symbol);
    
    if (result < 0) {
        return -1;
    }
    
    return result;
}

int point_cmp(const void *p1, const void *p2){
    if(p1 == NULL || p2 == NULL){
        return 0;
    }
    int distp1;
    int distp2;

    const Point *point1 = (const Point *)p1;
    const Point *point2 = (const Point *)p2;

    distp1 = (point1->x * point1->x) + (point1->y * point1->y);
    distp2 = (point2->x * point2->x) + (point2->y * point2->y);

    if(distp1 == distp2){
        return (int*)point1->symbol - (int*)point2->symbol;
    }
    
    return (distp1 - distp2);

}



Maze *maze_new(int nrows, int ncols){

    if (nrows<1 || ncols<1) {
        return NULL;
    }

    Maze *maze;
    if ((maze = (Maze*)malloc(sizeof(Maze))) == NULL) {
        return NULL;
    }

    maze->nrows = nrows;
    maze->ncols = ncols;

    if ((maze->map = (Point**)malloc(nrows*sizeof(Point*))) == NULL) {
        return NULL;
    }
    for (int i=0; i<nrows; i++) {
        if ((maze->map[i] = (Point*)malloc(ncols*sizeof(Point))) == NULL) {
            return NULL;
        }
    }

    for (int i=0; i<nrows; i++) {
        for (int j=0; j<ncols; j++) {
            maze->map[i][j].x = i;
            maze->map[i][j].y = j;
            maze->map[i][j].symbol = SPACE;
            maze->map[i][j].visited = false;
        }
    }

    return maze;
}

void maze_free(Maze *maze){

    int i;

    if(maze == NULL)
        return;

    for(i=0; i<maze->nrows; i++){
        free(maze->map[i]);
    }

    free(maze->map);
    free(maze);
}

Status maze_setIn(Maze *maze, int x, int y){

    if(maze == NULL){
        return ERROR;
    }

    maze->in = point_new(x, y, IN);
    if(maze->in == NULL){
        return ERROR;
    }

    maze_setSymbol(maze, x, y, IN);

    return OK;
}
Status maze_setOut(Maze *maze, int x, int y){

    if(maze == NULL){
        return ERROR;
    }

    maze->out = point_new(x, y, OUT);
    if(maze->out == NULL){
        return ERROR;
    }

    maze_setSymbol(maze, x, y, OUT);

    return OK;
}

Point *maze_getIn(const Maze *maze){
    if(maze == NULL){
        return NULL;
    }

    return maze->in;
}
Point *maze_getOut(const Maze *maze){

    if(maze == NULL){
        return NULL;
    }

    return maze->out;
}
int maze_getNrows(const Maze *maze){
    if(maze == NULL){
        return -1;
    }

    return maze->nrows;
}
int maze_getNcols(const Maze *maze){
    if(maze == NULL){
        return -1;
    }

    return maze->ncols;
}

Point *maze_getNeighbor(const Maze *maze, const Point *p, direction dir){
    
    int x, y;
    if (maze==NULL || p==NULL || dir<0 || dir>4) {
        return NULL;
    }

    x = point_getX(p);
    y = point_getY(p);

    if (dir == 0) {
        if (maze_checkCoordinates(maze, x, y+1) == ERROR) {
            return NULL;
        }
        return &maze->map[x][y+1];
    } else if (dir == 1) {
        if (maze_checkCoordinates(maze, x-1, y) == ERROR) {
            return NULL;
        }
        return &maze->map[x-1][y];
    } else if (dir == 2) {
        if (maze_checkCoordinates(maze, x, y-1) == ERROR) {
            return NULL;
        }
        return &maze->map[x][y-1];
    } else if (dir == 3) {
        if (maze_checkCoordinates(maze, x+1, y) == ERROR) {
            return NULL;
        }
        return &maze->map[x+1][y];
    } else {
        return &maze->map[x][y];
    }
}

Status maze_checkCoordinates(const Maze *maze, int x, int y){

    if(maze == NULL){
        return ERROR;
    }

    if(x<0 || x>= maze->nrows || y<0 || y>maze->ncols){
        return ERROR;
    }

    return OK;
    
}

Status maze_setSymbol(const Maze *maze, int x, int y, char sym){

    if (maze == NULL|| x<0 || y<0 || x>maze->ncols || y>maze->nrows){
        return ERROR;
    }
    else if(sym == WALL || sym == SPACE || sym == IN || sym == OUT){
        point_setSymbol(&maze->map[x][y], sym);
        return OK;
    }
    return ERROR;
    
}
Status maze_setVisited(const Maze *maze, int x, int y, bool visited){
    if(maze == NULL|| x<0 || y<0 || x>maze->nrows || y>maze->ncols){
        return ERROR;
    }
    else if(visited == true || visited == false){
        point_setVisited(&maze->map[x][y], visited);

        return OK;
    }
    else{
        return ERROR;
    }

}
Point *maze_getPoint(const Maze *maze, int x, int y){
    if(maze == NULL|| x<0 || y<0 || x>maze->nrows || y>maze->ncols){
        return NULL;
    }

    return &maze->map[x][y];    
}
char maze_getSymbol(const Maze *maze, int x, int y){
    if(maze == NULL|| x<0 || y<0 || x>maze->nrows || y>maze->ncols){
        return '0';
    }

    return maze->map[x][y].symbol;
}
bool maze_isVisited(const Maze *maze, int x, int y){
    if(maze == NULL|| x<0 || y<0 || x>maze->nrows || y>maze->ncols){
        return false;
    }
    else if(maze->map[x][y].visited == true || maze->map[x][y].visited == false){

        return maze->map[x][y].visited;
    }

    return false;
}

int maze_printPoints(FILE *fp, const Maze *maze){

    if(fp == NULL || maze == NULL){
        return -1;
    }

    int i, j;

    fprintf(fp, "Maze points: %d rows %d cols\n", maze->nrows, maze->ncols);

    for(i=0; i< maze->nrows; i++){
        for(j=0; j< maze->ncols; j++){
            maze->map[i][j].x = i;
            maze->map[i][j].y = j;
            maze->map[i][j].visited = false;
            
            point_print(fp, &maze->map[i][j]);

        }
        fprintf(fp, "\n");
    }

    return 0;

}

int maze_print(FILE *fp, const Maze *maze){
    if(fp == NULL || maze == NULL){
        return -1;
    }
    int i, j;
    fprintf(fp, "Maze: %d rows %d cols\n", maze->nrows, maze->ncols);
    point_print(stdout, maze->in);
    point_print(stdout, maze->out);
    fprintf(stdout, "\n");

    for(i=0; i< maze->nrows; i++){
        for(j=0; j< maze->ncols; j++){
            fprintf(fp, "%c", maze->map[i][j].symbol);
        }
        fprintf(fp, "\n");
    }
    return 0;
}

Maze *maze_readFromFile(const char *filename) {
    if (filename == NULL) {
        return NULL;
    }

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        return NULL;
    }

    int nrows, ncols;
    if (fscanf(f, "%d %d\n", &nrows, &ncols) != 2 || nrows <= 0 || ncols <= 0) {
        fclose(f);
        return NULL;
    }

    Maze *maze = maze_new(nrows, ncols);
    if (maze == NULL) {
        fclose(f);
        return NULL;
    }

    char symbol;
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            if (fscanf(f, " %c", &symbol) != 1) {
                fclose(f);
                maze_free(maze);
                return NULL;
            }
            maze_setSymbol(maze, i, j, symbol);
            if (symbol == 'i') {
                maze_setIn(maze, i, j);
            } else if (symbol == 'o') {
                maze_setOut(maze, i, j);
            }
        }
    }

    fclose(f);
    return maze;
}
