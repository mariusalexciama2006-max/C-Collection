#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 21
#define HEIGHT 21

///Stack

typedef struct s
{
    int capacity;
    int size;
    int *arr_x;
    int *arr_y;

} stack;

stack* init_stack(int capacity)
{
    stack *s = malloc(sizeof(stack));
    if(s==NULL)
        return NULL;
    s->capacity = capacity;
    s->size = 0;
    s->arr_x = calloc(capacity, sizeof(int));
    if(s->arr_x==NULL)
        return NULL;
    s->arr_y = calloc(capacity, sizeof(int));
    if(s->arr_y==NULL)
        return NULL;
    return s;
}

void push(stack *s, int pushed_x, int pushed_y)
{
    if(s==NULL || s->size==s->capacity)
        return;
    s->arr_x[s->size] = pushed_x;
    s->arr_y[s->size] = pushed_y;
    s->size++;
}

void pop(stack *s, int *popped_x, int *popped_y)
{
    if(s==NULL || s->size==0)
        return;
    s->size--;
    *popped_x = s->arr_x[s->size];
    *popped_y = s->arr_y[s->size];
}

///Queue

typedef struct
{
    int capacity;
    int size;
    int *array_x;
    int *array_y;
    int head;
    int tail;
} queue;

queue* init_queue(int capacity)
{
    queue *q = malloc(sizeof(queue));
    if(q == NULL)
        return NULL;
    q->capacity = capacity;
    q->size = 0;
    q->head = 0;
    q->tail = 0;
    q->array_x = calloc(capacity, sizeof(int));
    if(q->array_x==NULL)
    {
        return NULL;
    }

    q->array_y = calloc(capacity, sizeof(int));
    if(q->array_y==NULL)
    {
        free(q->array_x);
        return NULL;
    }
    return q;
}

void enqueue(queue *q, int en_x, int en_y)
{
    if(q==NULL || q->size==q->capacity)
        return;
    q->array_x[q->tail] = en_x;
    q->array_y[q->tail] = en_y;
    q->tail++;
    if(q->tail == q->capacity)
        q->tail = 0;
    q->size++;
}

void dequeue(queue *q, int *deq_x, int *deq_y)
{
    if(q==NULL || q->size==0)
        return;
    *deq_x = q->array_x[q->head];
    *deq_y = q->array_y[q->head];
    q->head++;
    if(q->head == q->capacity)
        q->head=0;
    q->size--;
}

///Randomize our 4 directions

void shuffle(int* array, int n)
{
    int i, j;
    for(i=0; i<n-1; i++)
    {
        j=i+rand()/(RAND_MAX/(n-i)+1);
        int temp = array[j];
        array[j] = array[i];
        array[i] = temp;
    }
}

///Generating the maze

void generate_maze(int maze[HEIGHT][WIDTH])
{
    int i, j;
    for(i=0; i<HEIGHT; i++)
    {
        for(j=0; j<WIDTH; j++)
            maze[i][j] = 1;
    }

    stack *s = init_stack(HEIGHT*WIDTH);

    int v_x[] = {-2, 2, 0, 0};
    int v_y[] = {0, 0, -2, 2};

    ///Starting the maze at (1, 1)
    int start_x = 1;
    int start_y = 1;
    maze[start_x][start_y] = 0;
    push(s, start_x, start_y);

    int curent_x, curent_y;
    int next_x, next_y;
    while(s->size!=0)
    {
        pop(s, &curent_x, &curent_y);

        int directions[] = {0, 1, 2, 3};
        shuffle(directions, 4);

        int i, dir;
        for(i=0; i<4; i++)
        {
            dir = directions[i];
            next_x = curent_x + v_x[dir];
            next_y = curent_y + v_y[dir];

            ///Checking the limits
            if(next_x>0 && next_x<HEIGHT-1 && next_y>0 && next_y<WIDTH-1)
            {
                ///If it wasn't visited
                if(maze[next_x][next_y]==1)
                {
                    ///Checking the coordinates between
                    int wall_x = curent_x + (v_x[dir]/2);
                    int wall_y = curent_y + (v_y[dir]/2);

                    ///Change the flag to '0'(visited)
                    maze[next_x][next_y] = 0;
                    maze[wall_x][wall_y] = 0;

                    push(s, curent_x, curent_y);///Backtrack

                    push(s, next_x, next_y);

                    break;
                }
            }
        }
    }

    free(s->arr_x);
    free(s->arr_y);
    free(s);

}


void print_maze(int maze[HEIGHT][WIDTH])
{
    for(int i=0; i<HEIGHT; i++)
    {
        for(int j=0; j<WIDTH; j++)
        {
            if(maze[i][j] == 1)
            {
                /// Use two block characters for better square proportions in the terminal
                printf("11");
            }
            else if(maze[i][j] == 2)
            {
                ///Use two block characters for the shortest path
                printf("\033[42m  \033[0m");
            }
            else
            {
                /// Use two spaces for the open paths
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("\n");
}


int shortest_path(int maze[HEIGHT][WIDTH], int final_x, int final_y)
{
    queue *q = init_queue(HEIGHT*WIDTH);

    int i;
    int **visited = calloc(HEIGHT, sizeof(int*));
    for(i=0; i<HEIGHT; i++)
        visited[i] = calloc(WIDTH, sizeof(int));

    int v_x[4] = {0, 0, -1, 1};
    int v_y[4] = {1, -1, 0, 0};

    int start_x = 1;
    int start_y = 1;
    enqueue(q, start_x, start_y);

    visited[start_x][start_y] = 1;

    int parent_x[HEIGHT][WIDTH];
    int parent_y[HEIGHT][WIDTH];
    parent_x[start_x][start_y] = -1;
    parent_y[start_x][start_y] = -1;


    int curent_x, curent_y;
    int next_x, next_y;
    int found = 0;
    while(q->size!=0)
    {
        dequeue(q, &curent_x, &curent_y);

        if(curent_x == final_x && curent_y == final_y)
        {
            found = 1;
            break;
        }

        for(int i=0; i<4; i++)
        {
            next_x = curent_x + v_x[i];
            next_y = curent_y + v_y[i];

            if(next_x>0 && next_x<HEIGHT && next_y>0 && next_y<WIDTH)
            {
                if(maze[next_x][next_y]==0 && visited[next_x][next_y]==0)
                {
                    visited[next_x][next_y]= 1;

                    parent_x[next_x][next_y] = curent_x;
                    parent_y[next_x][next_y] = curent_y;

                    enqueue(q, next_x, next_y);
                }
            }
        }
    }
    int counter;
    if(found==1)
    {
        counter = 0;

        while(parent_x[curent_x][curent_y] != -1 && parent_y[curent_x][curent_y] != -1)
        {
            counter++;
            int temp_x = parent_x[curent_x][curent_y];
            int temp_y = parent_y[curent_x][curent_y];

            maze[curent_x][curent_y] = 2;

            curent_x = temp_x;
            curent_y = temp_y;
        }
        maze[curent_x][curent_y] = 2;
    }

    for(i=0; i<HEIGHT; i++)
        free(visited[i]);
    free(visited);
    free(q->array_x);
    free(q->array_y);
    free(q);

    if(found!=1)
        return -1;

    return counter;
}

int main()
{
    srand(time(NULL));
    int maze[HEIGHT][WIDTH];
    generate_maze(maze);

    print_maze(maze);

    int final_x, final_y;

    printf("What coordinates you want to check if are valid for the shortest path of the maze? (x, y):");
    scanf("%d %d", &final_x, &final_y);
    printf("\n");
    if(maze[final_x][final_y] == 1)
        printf("The coordinate (%d, %d) is a wall!", final_x, final_y);
    else if(final_x<=0 || final_x>=HEIGHT-1 || final_y <=0 || final_y>=WIDTH-1)
    {
        printf("Wrong Input!");
    }
    else
    {
        int short_path = shortest_path(maze, final_x, final_y);
        if(short_path==-1)
            printf("There is no path to the (%d, %d) coordinates", final_x, final_y);
        else
        {
            printf("The shortest path to the (%d, %d) coordinates is %d\n", final_x, final_y, short_path);
            print_maze(maze);
        }
    }
    return 0;
}
