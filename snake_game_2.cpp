// Block of variables:
bool GameOver_snk = false; 
const int Wight_field = 13;
const int Height_field = 9;
int SnakeX, SnakeY, FruitX, FruitY, Score_snk; 
enum Move_snk {STOP, UP, DOWN, RIGHT, LEFT};
Move_snk Head_snk;
bool Getch_flg = false; // флаг ловли одного срабатывания
int tailX[100], tailY[100];
int nTail;

// Block of functions:
void snk_Setup() {
	Head_snk = STOP;
	SnakeX = Wight_field / 2;
	SnakeY = Height_field / 2;
	cout << "SnakeX =" << SnakeX << endl;
	cout << "SnakeY =" << SnakeY << endl;
	FruitX = get_rand_num(0, 2000) % Wight_field; // rand() % Weight_field; 
	FruitY = get_rand_num(0, 2000) % Height_field; // rand() % Height_field; 
}

void snk_Draw() {

	Getch_flg = false;
	clean_screen(); 
	
	for (int i = 0; i <= (Wight_field + 1); i++) {
		cout << "#";
	}
	cout << endl;

	for (int j = 0; j < Height_field; j++) {
		for (int i = 0; i <= (Wight_field + 1); i++) {
			if ((i == 0) || (i == Wight_field)) {
				cout << "#";
			}
			// Добавим координаты змеи и фруктов:
			if (j == SnakeY && i == SnakeX) {
				cout << "S";
			}
			else if (j == FruitY && i == FruitX) {
				cout << "F";
			}
			else { // отрисовка хвоста:
				bool tail_flg = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == i && tailY[k] == j) {
						tail_flg = true;
						cout << "s";
					}
				}
				if (!tail_flg) {
					cout << " ";
				}
			}
		}
		cout << endl;
	}

	for (int i = 0; i <= (Wight_field+1); i++) {
		cout << "#";
	}
	cout << endl << "Вы набрали " << Score_snk << " очков" << endl;
}

void snk_Input() {
	if (_kbhit()) {
		Getch_flg = true;

		switch (_getch()) {
		case 'a':
			Head_snk = LEFT;
			break;
		case 'w':
			Head_snk = UP;
			break;
		case 'd':
			Head_snk = RIGHT;
			break;
		case 's':
			Head_snk = DOWN;
			break;
		case 'q':
			GameOver_snk = true;
			break;
		default:
			Head_snk = STOP;
			break;
		}
	}
}

void snk_Logic() {
	// обработка хвоста:
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = SnakeX;
	tailY[0] = SnakeY;

	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	// навигация:
	if (Getch_flg && (SnakeX >= 0 && (SnakeX <= (Wight_field - 1))) && (SnakeY >= 0 && (SnakeY <= (Height_field - 1))) ) {
		switch (Head_snk) {
		case RIGHT:
			SnakeX++;
			break;

		case LEFT:
			SnakeX--;
			break;

		case UP:
			SnakeY--;
			break;

		case DOWN:
			SnakeY++;
			break;

		case STOP:
			Getch_flg = false;
			break;
		}
	}
	else if (SnakeX < 0 || SnakeY < 0 || SnakeX >= (Wight_field ) || SnakeY >= (Height_field)){
		cout << "Вы врезались в стенку!" << endl;
		GameOver_snk = true;
	}

	

	
	/*for (int k = 0; k < nTail; k++) {
			if (tailX[k] == SnakeX && tailY[k] == SnakeY) {
				cout << "Вы укусили хвост!" << endl;
				GameOver_snk = true;
			}
	}*/
	
	if ((SnakeX == FruitX) && (SnakeY == FruitY)) {
		Score_snk += 10;
		FruitX = get_rand_num(0, 2000) % Wight_field; // rand() % Weight_field; 
		FruitY = get_rand_num(0, 2000) % Height_field; // rand() % Height_field; 
		nTail++;
	}
	
}

// Game itself:
void snake() {
	// на базе IT Progger: https://youtu.be/6qaAZTwemXY 
	snk_Setup();
	while (!GameOver_snk) {
		snk_Draw();

		snk_Input(); 

		snk_Logic(); 

		Sleep(250); // задержка для плавности игры - подбирается экспериментально
	};

	cout << "SnakeX =" << SnakeX << endl;
	cout << "SnakeY =" << SnakeY << endl;

}
