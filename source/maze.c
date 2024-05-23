#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "../header/pos.h"
#include "../header/stack.h"

#define MAX 100
#define PATH 0
#define WALL 1
#define VISITED 2
#define BACKTRACKED 3

int maze[MAX][MAX];
int n;
Position cur;

void read_maze();
bool movable(Position pos1, int dir);
void print_maze();

int main() {
	read_maze();
	Stack s = create(); /* 이번에는 Position대신 정수들을 저장하는 스택을 사용한다. */
	cur.x = 0;
	cur.y = 0;
	FILE *out = fopen("./text/out.txt", "w");
	fprintf(out,"<%d,%d>\n",cur.x, cur.y);
	while (1) {
		maze[cur.x][cur.y] = VISITED; /* visited */
		if (cur.x == n - 1 && cur.y == n - 1) {
			printf("Found the path.\n");
			break;
		}
		bool forwarded = false;
		int dir = 0;
		while(1) /* 0:N, 1:E, 2:S, 3:W */
		{
			print_maze();
			printf("> ");
			scanf("%d", &dir);
			fprintf(out, "입력 : %d -> ",dir);
			if (dir == (peek(&s) + 2) % 4) {
				for(int i = 1 ; i < 4 ; i++)
				{
					if (movable(cur, (dir + i) % 4))
						forwarded = true;
				}
				if (!forwarded)
					break;
			}
			if (movable(cur, dir)) {
				push(&s, dir); /* 스택에는 현재 위치 대신 이동하는 방향을 push */
				cur = move_to(cur, dir);
				fprintf(out,"<%d,%d>\n",cur.x, cur.y);
				forwarded = true;
				break;
			}
		}
		if (!forwarded) { /* nowhere to go forward */
			maze[cur.x][cur.y] = BACKTRACKED; /* backtracked */
			if (is_empty(&s)) {
				printf("No path exists.\n");
				break;
			}
			int d = pop(&s);
			cur = move_to(cur, (d + 2) % 4);
			fprintf(out,"되돌아감 : (%d,%d)\n",cur.x, cur.y);
		}
	}
	print_maze();
	fclose(out);
}

void read_maze() {
	FILE *file;
	char line[MAX + 1];
	int row = 0;

	file = fopen("./text/maze.txt", "r");
	if (file == NULL) {
		fprintf(stderr, "파일을 열 수 없습니다.\n");
		exit(EXIT_FAILURE);  // 파일을 열 수 없으면 프로그램을 종료
	}

	while (fgets(line, sizeof(line), file) != NULL && row < MAX) {
		int len = strlen(line);

		if (line[len - 1] == '\n') {
			line[len - 1] = '\0';
			len--;
		}

		for (int col = 0; col < len && col < MAX; col++) {
			if (line[col] >= '0' && line[col] <= '9') {
				maze[row][col] = line[col] - '0';
			} else {
				fprintf(stderr, "숫자 오류\n");
				fclose(file);
				exit(EXIT_FAILURE);  // 오류 발생 시 프로그램을 종료
			}
		}
		row++;
	}

	n = row;  // 미로의 크기를 설정

	fclose(file);  // 파일 닫기
}


bool movable(Position pos1, int dir) {
	Position check = move_to(pos1, dir);
	if (check.x < 0 || check.x >= n || check.y < 0 || check.y >= n)
		return 0;
	if (maze[check.x][check.y] == WALL || maze[check.x][check.y] == BACKTRACKED)
		return 0;
	else
		return 1;
}

void print_maze() {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) {
			if(i == cur.x && j == cur.y) {
				printf("☉");
				continue;
			}
			if(maze[i][j] == PATH || maze[i][j] == BACKTRACKED)
				printf("□");
			if(maze[i][j] == WALL)
				printf("■");
			if(maze[i][j] == VISITED)
				printf("\033[0;32m★\033[0m");
		}
		printf("\n");
	}
}



