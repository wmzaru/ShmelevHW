#include <windows.h>
#include <vector>
#include <map>
#include <time.h>
#include <tchar.h>
#include <cstdlib>
#include "resource.h"

using namespace std;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
bool fillField(HWND hWin);
BOOL CALLBACK clearField(HWND hExWnd, LPARAM lParam);

HWND hStatic1, hStatic2, hStartButton;
TCHAR szCoordinates[20];
HINSTANCE hInst;
const int LEFT = 15, TOP = 15, WIDTH = 30, HEIGHT = 30; 

class Model {
public:
	const size_t height, width, nmines;
	vector<vector<bool>> mines;
	vector<vector<bool>> isopen;
	vector<vector<int>> neighbours;
	int opened;
	bool gameover;
	bool win;
public:
	Model(size_t height_, size_t width_, size_t nmines_)
		:
		height(height_), width(width_), nmines(nmines_),
		mines(height, vector<bool>(width, false)),
		isopen(height, vector<bool>(width, false)),
		neighbours(height, vector<int>(width, 0)),
		win(false), gameover(false), opened(0)

	{
		//Раскидываер рандомно бомбы
		for (size_t i = 0; i < nmines; i++) {
			mines[rand() % height][rand() % width] = true;
		}
		//Проходимся по клеткам
		for (size_t row = 0; row < height; row++)
		{
			for (size_t col = 0; col < width; col++) {
				//Соседями являются клетки от -1 до +1 по координатам (квадрат 3x3)
				//Проходимся по соседям
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						if ((row + i >= 0) && (row + i < height) &&
							(col + j >= 0) && (col + j < width))
							neighbours[row][col] += (int)mines[row + i][col + j];
					}
				}

			}
		}
	}
	bool check(size_t row, size_t col) {

		if ((!gameover)
			&& (row >= 0) && (row < height) &&
			(col >= 0) && (col  < height) && (!isopen[row][col])){

			if (mines[row][col]) {
				gameover = true;
				MessageBox(0, TEXT("Вы проиграли"), TEXT("Игра окончена"), MB_OK);
			}
			else {
				//Если не попали на мину - пишем что эта клетка открыта
				isopen[row][col] = true;
				opened++;
				if (opened + nmines == height*width) {
					win = true;
					MessageBox(0, TEXT("Вы ВЫЙГРАЛИ"), TEXT("Игра окончена"), MB_OK);
				}
				if (neighbours[row][col] == 0) {
				//??? Что тут происходит? Почему не открывается всё поле?
					check(row + 1, col + 1);
					check(row + 0, col + 1);
					check(row - 1, col + 1);
					check(row + 1, col + 0);
					check(row - 1, col + 0);
					check(row + 1, col - 1);
					check(row + 0, col - 1);
					check(row - 1, col - 1);
				}
			}
		}
		return gameover;
	}
};

Model* currentGame;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	srand(time(NULL));
	hInst = hInstance;
	// создаём главное окно приложения на основе модального диалога
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc); 
}

struct coo {
	size_t leftPoint, topPoint;
};

map<HWND, coo> buttons;

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	/// nmines m(10,10,10);

	switch(message)
	{
		case WM_CLOSE:
			EndDialog(hWnd, 0); // закрываем модальный диалог
			return TRUE;
		// WM_INITDIALOG - данное сообщение приходит после создания диалогового окна, но перед его отображением на экран
		case WM_INITDIALOG:{
			currentGame = new Model(10, 10, 10);
			hStatic1 = GetDlgItem(hWnd, IDC_STATIC1); // получаем дескриптор статика, размещенного на форме диалога
			hStartButton = GetDlgItem(hWnd, IDC_BUTTON1);
			//создаём статик с помощью CreateWindowEx
			fillField(hWnd);
		}
			return TRUE;
		case WM_COMMAND:
		{
			if ((HWND)lParam == hStartButton){
				delete currentGame;
				currentGame = new Model(10, 10, 10);
				EnumChildWindows(hWnd, clearField, 0);
			}
			else{
				auto itr = buttons.find((HWND)lParam);
				coo needleCoo = itr->second;
				//Открываем клетку и её соседей
				currentGame->check(needleCoo.leftPoint, needleCoo.topPoint);
				for (auto itr_button : buttons){
					//Перебираем все кнопки, получаем hwnd и если по текущим координатам кнопки isopen = true, то меняем внешний вид				
					HWND hButton = itr_button.first;
					coo tempCoo = itr_button.second;
					if (currentGame->isopen[tempCoo.leftPoint][tempCoo.topPoint]){
						//SetWindow(hButton, GWL_STYLE, )
						int nearBombs = 0;
						//int nearestNumber = currentGame->height;
						//for (int row = 0; row < currentGame->mines.size(); ++row){
						//	for (int col = 0; col < currentGame->mines[row].size(); ++col){
						//		if (currentGame->mines[row][col] == true){
						//			coo currentMine = { row, col };
						//			int firstCoo = tempCoo.leftPoint - currentMine.leftPoint;
						//			int secondCoo = tempCoo.topPoint - currentMine.topPoint;
						//			//Преобразуем в значения по модулю
						//			firstCoo = firstCoo < 0 ? -firstCoo : firstCoo;
						//			secondCoo = secondCoo < 0 ? -secondCoo : secondCoo;

						//			int needlePoint = firstCoo > secondCoo ? firstCoo : secondCoo;
						//			if (needlePoint < nearestNumber){
						//				nearestNumber = needlePoint;
						//			}
						//		}
						//	}
						//}
						for (int i = -1; i <= 1; i++) {
							for (int j = -1; j <= 1; j++) {
								if ((tempCoo.leftPoint + i >= 0) && (tempCoo.leftPoint + i < currentGame->height) &&
									(tempCoo.topPoint + j >= 0) && (tempCoo.topPoint + j < currentGame->width)){
										if (currentGame->mines[tempCoo.leftPoint + i][tempCoo.topPoint + j]){
											++nearBombs;
										}
									}
								}
							}
						if (nearBombs != 0){
							TCHAR numberOnButton[10];
							wsprintf(numberOnButton, TEXT("%d"), nearBombs);
							SetWindowText(hButton, numberOnButton);
						}
						else{
							SetWindowText(hButton, TEXT("."));
						}
					}
					//Выставляем Х если нарываемся на первую бомбу
					if (currentGame->mines[tempCoo.leftPoint][tempCoo.topPoint]
						&& tempCoo.leftPoint == needleCoo.leftPoint 
						&& tempCoo.topPoint == needleCoo.topPoint){
						SetWindowText(hButton, TEXT("X"));
					}
					//Если нарвались на бомбу - показываем все оставшиеся бомбы
					if (currentGame->gameover && currentGame->mines[tempCoo.leftPoint][tempCoo.topPoint]){
						SetWindowText(hButton, TEXT("X"));
					}
				}
			}
			
		}
			return TRUE;
		case WM_MOUSEMOVE:
			wsprintf(szCoordinates, TEXT("X=%d  Y=%d"), LOWORD(lParam), HIWORD(lParam)); // текущие координаты курсора мыши
			SetWindowText(hStatic1, szCoordinates);	// строка выводится на статик
			return TRUE;
		case WM_LBUTTONDOWN:
			SetWindowText(hStatic2, TEXT("Нажата левая кнопка мыши"));
			return TRUE;
		case WM_RBUTTONDOWN:
			SetWindowText(hStatic2, TEXT("Нажата правая кнопка мыши"));
			return TRUE;
	}
	return FALSE;
}

bool fillField(HWND hWin){
	for (int i = 0; i < currentGame->height; ++i){
		for (int j = 0; j < currentGame->width; ++j){
			int leftPoint = LEFT + (WIDTH*j);
			int topPoint = TOP + (HEIGHT*i);
			buttons[CreateWindowEx(0, TEXT("BUTTON"), 0,
				WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER,
				leftPoint, topPoint, WIDTH, HEIGHT, hWin, 0, hInst, 0)]
				= coo{ i, j };
		}
	}
	return true;
}

BOOL CALLBACK clearField(HWND hExWnd, LPARAM lParam){
	//Очистка поля
	TCHAR classname[100];
	int ctrlID = GetDlgCtrlID(hExWnd);
	if (ctrlID != IDC_BUTTON1){
		SetWindowText(hExWnd, TEXT(""));
	}
	return TRUE;
}