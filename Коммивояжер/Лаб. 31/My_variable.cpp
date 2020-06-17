#include "Graph.h"
#define window_width 1000
#define window_height 700
using namespace std;
int MovVert;//перемещаемая вершина
int CursorX;//позиция курсора 
int CursorY;
bool* ThisVert = new bool[MaxV]; //курсор в зоне круга
bool MovMode = false; //перемещены ли вершины
bool IsMove = false; //отвечает за перемещение вершин 
coordinates vertC[MaxV + 1];//координаты вершин
vector<pair<int, int>> PathVert;
vector<int> WayVert;
int R;
int but;
Graph graph;
//Состояние кнопок
bool state_buttom_1 = false;
bool state_buttom_2 = false;
bool state_buttom_3 = false;
bool state_buttom_4 = false;
bool state_buttom_5 = false;
bool state_buttom_6 = false;

//Конструктор
Graph::Graph()
{
	for (int i = 0; i < MaxV; i++)
	{
		ThisVert[i] = false;
		for (int j = 0; j < MaxV; j++)
			AdjMatr[i][j] = 0;
	}
}

int Graph::GetVertPos(const int& vertex)
{
	for (size_t i = 0; i < VList.size(); i++)
	{
		if (VList[i] == vertex)
			return i;
	}
	return -1;
}

bool Graph::IsEmpty()
{
	if (VList.size() != 0)
		return false;
	else
		return true;
}

bool Graph::IsFull()
{
	return (VList.size() == MaxV);
}

void Graph::AddVertex(const int& vertex)
{
	if (!IsFull())
		VList.push_back(vertex);
	else
	{
		cout << "Граф уже заполнен. Невозможно добавить новую вершину " << endl;
		return;
	}
}

void Graph::AddEdge(const int& vertex1, const int& vertex2, int weight)
{
	if (weight < 1)
	{
		cout << "\nДанная величина веса некорректна\n";
		return;
	}
	if (GetVertPos(vertex1) != (-1) && GetVertPos(vertex2) != (-1))
	{
		int vertPos1 = GetVertPos(vertex1);
		int vertPos2 = GetVertPos(vertex2);
		if (AdjMatr[vertPos1][vertPos2] != 0 && AdjMatr[vertPos2][vertPos1] != 0)
		{
			cout << "Ребро между вершинами уже есть" << endl;
			return;
		}
		else
		{
			AdjMatr[vertPos1][vertPos2] = weight;
		}
	}
	else
	{
		cout << "Обеих вершин (или одной из них) нет в графе " << endl;
		return;
	}
}

void Graph::PrintGraph()
{
	if (!IsEmpty())
	{
		cout << "Матрица смежности графа: " << endl;
		for (int i = 0; i < VList.size(); i++)
		{
			cout << VList[i] << " ";
			for (int j = 0; j < VList.size(); j++)
				cout << setw(4) << AdjMatr[i][j];
			cout << endl;
		}
	}
	else
		cout << "Граф пуст " << endl;
}

void Graph::DelVertex()
{
	if (IsEmpty())
	{
		cout << "\nГраф пуст\n";
		return;
	}
	int n = VList.size();
	for (int j = 0; j < n; j++)
	{
		AdjMatr[n - 1][j] = 0;
		AdjMatr[j][n - 1] = 0;
	}

	VList.pop_back();
}

void Graph::DelEdge(const int& vertex1, const int& vertex2)
{
	if (GetVertPos(vertex1) != (-1) && GetVertPos(vertex2) != (-1))	//если вершины есть в графе
	{
		int vertPos1 = GetVertPos(vertex1);							//находим позиции вершин
		int vertPos2 = GetVertPos(vertex2);
		if (AdjMatr[vertPos1][vertPos2] == 0 && AdjMatr[vertPos2][vertPos1] == 0)//если между ними уже есть ребро
		{
			cout << "Здесь ребра нет" << endl;
			return;
		}
		else														//иначе добавляем ребро
			AdjMatr[vertPos1][vertPos2] = 0;
	}
	else
	{
		cout << "Обеих вершин (или одной из них) нет в графе " << endl;
		return;
	}
}

int Graph::GetAmountEdges()
{
	int edges = 0;
	for (int i = 0; i < VList.size(); i++)
		for (int j = 0; j < VList.size(); j++)
			if (AdjMatr[i][j] > 0)
				edges++;
	return edges;
}

void Graph::DrawGraph()
{
	int n = graph.GetAmountVerts();
	for (int i = 0; i < n; i++)
	{
		if (!MovMode)
			SetCoords(i, n);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int a = AdjMatr[i][j];
			if (a != 0)
				DrawLine(a, vertC[i].x, vertC[i].y, vertC[j].x, vertC[j].y);
			if (a == AdjMatr[j][i] && a != 0)
				DrawLine(a, vertC[j].x, vertC[j].y, vertC[i].x, vertC[i].y);
		}
	}
	DrawVert(n);
	glutPostRedisplay();
}

void Button1()
{
	if (state_buttom_1) glColor3f(0.5f, 0.5f, 0.5f);
	else glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_QUADS);
	glVertex2i(13, window_height - 13);
	glVertex2i(13, window_height - window_height / 8);
	glVertex2i(window_width / 7, window_height - window_height / 8);
	glVertex2i(window_width / 7, window_height - 13);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(13, window_height - 13);
	glVertex2i(13, window_height - window_height / 8);
	glVertex2i(window_width / 7, window_height - window_height / 8);
	glVertex2i(window_width / 7, window_height - 13);
	glEnd();
	string name = "new graph";
	glRasterPos2i(45, window_height - 0.5 * window_height / 7);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, name[i]);
}

void Button2()
{
	if (state_buttom_5) glColor3f(0.5f, 0.5f, 0.5f);
	else glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_QUADS);
	glVertex2i(13, (window_height - 4 * window_height / 7) + 39);
	glVertex2i(13, window_height - 5 * window_height / 8);
	glVertex2i(window_width / 7, window_height - 5 * window_height / 8);
	glVertex2i(window_width / 7, (window_height - 4 * window_height / 7) + 39);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(13, (window_height - 4 * window_height / 7) + 39);
	glVertex2i(13, window_height - 5 * window_height / 8);
	glVertex2i(window_width / 7, window_height - 5 * window_height / 8);
	glVertex2i(window_width / 7, (window_height - 4 * window_height / 7) + 39);
	glEnd();
	string name = "delete edge";
	glRasterPos2i(45, (window_height - 4.5 * window_height / 7) + 50);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, name[i]);
}

void Button3()
{
	if (state_buttom_3) glColor3f(0.5f, 0.5f, 0.5f);
	else glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_QUADS);
	glVertex2i(13, (window_height - 2 * window_height / 7) + 13);
	glVertex2i(13, window_height - 3 * window_height / 8);
	glVertex2i(window_width / 7, window_height - 3 * window_height / 8);
	glVertex2i(window_width / 7, (window_height - 2 * window_height / 7) + 13);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(13, (window_height - 2 * window_height / 7) + 13);
	glVertex2i(13, window_height - 3 * window_height / 8);
	glVertex2i(window_width / 7, window_height - 3 * window_height / 8);
	glVertex2i(window_width / 7, (window_height - 2 * window_height / 7) + 13);
	glEnd();
	string name = "delete vertex";
	glRasterPos2i(40, (window_height - 2.5 * window_height / 7) + 20);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, name[i]);
}

void Button4()
{
	if (state_buttom_4) glColor3f(0.5f, 0.5f, 0.5f);
	else glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_QUADS);
	glVertex2i(13, (window_height - 3 * window_height / 7) + 26);
	glVertex2i(13, window_height - 4 * window_height / 8);
	glVertex2i(window_width / 7, window_height - 4 * window_height / 8);
	glVertex2i(window_width / 7, (window_height - 3 * window_height / 7) + 26);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(13, (window_height - 3 * window_height / 7) + 26);
	glVertex2i(13, window_height - 4 * window_height / 8);
	glVertex2i(window_width / 7, window_height - 4 * window_height / 8);
	glVertex2i(window_width / 7, (window_height - 3 * window_height / 7) + 26);
	glEnd();
	string name = "add edge";
	glRasterPos2i(50, (window_height - 3.5 * window_height / 7) + 35);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, name[i]);
}

void Button5()
{
	if (state_buttom_2) glColor3f(0.5f, 0.5f, 0.5f);
	else glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_QUADS);
	glVertex2i(13, window_height - window_height / 7);
	glVertex2i(13, window_height - 2 * window_height / 8);
	glVertex2i(window_width / 7, window_height - 2 * window_height / 8);
	glVertex2i(window_width / 7, window_height - window_height / 7);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(13, window_height - window_height / 7);
	glVertex2i(13, window_height - 2 * window_height / 8);
	glVertex2i(window_width / 7, window_height - 2 * window_height / 8);
	glVertex2i(window_width / 7, window_height - window_height / 7);
	glEnd();
	string name = "add vertex";
	glRasterPos2i(45, WinH - 1.5 * WinH / 7.5);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, name[i]);
}

void Button6()
{
	if(state_buttom_6) glColor3f(0.5f, 0.5f, 0.5f);
	else glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_QUADS);
	glVertex2i(13, (window_height - 5 * window_height / 7) + 52);
	glVertex2i(13, window_height - 6 * window_height / 8);
	glVertex2i(window_width / 7, window_height - 6 * window_height / 8);
	glVertex2i(window_width / 7, (window_height - 5 * window_height / 7) + 52);
	glEnd();


	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2i(13, (window_height - 5 * window_height / 7) + 52);
	glVertex2i(13, window_height - 6 * window_height / 8);
	glVertex2i(window_width / 7, window_height - 6 * window_height / 8);
	glVertex2i(window_width / 7, (window_height - 5 * window_height / 7) + 52);
	glEnd();
	string name = "commivoyager";
	glRasterPos2i(40, (window_height - 5.5 * window_height / 7) + 60);
	for (int i = 0; i < name.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, name[i]);
}

void DrawCircle(int x, int y, int R)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	float x1, y1;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y1 = R * cos(theta) + y;
		x1 = R * sin(theta) + x;;
		glVertex2f(x1, y1);
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	float x2, y2;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y2 = R * cos(theta) + y;
		x2 = R * sin(theta) + x;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void DrawT(int text, int x1, int y1)
{
	glColor3f(0.0, 0.0, 0.0);
	GLvoid* font = GLUT_BITMAP_HELVETICA_18;
	string s = to_string(text);
	glRasterPos2i(x1 - 5, y1 - 5);
	for (size_t j = 0; j < s.length(); j++)
		glutBitmapCharacter(font, s[j]);
}

void DrawLine(int text, int x0, int y0, int x1, int y1) //ребро неориентированного взвешенного графа
{
	glColor3i(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(x1, y1);
	glEnd();
	DrawT(text, (x0 + x1) / 2 + 10, (y0 + y1) / 2 + 10);

	float vx = x0 - x1;
	float vy = y0 - y1;
	float s = 1.0f / sqrt(vx * vx + vy * vy);
	vx *= s;
	vy *= s;
	x1 = x1 + R * vx;
	y1 = y1 + R * vy;
}

void DrawVert(int n)
{
	for (int i = 0; i < n; i++)
	{
		DrawCircle(vertC[i].x, vertC[i].y, R);
		DrawT(i + 1, vertC[i].x, vertC[i].y);
	}
}

void SetCoords(int i, int n)
{
	int R_;
	int x0 = WinW / 2;
	int y0 = WinH / 2;
	if (WinW > WinH)
	{
		R = 5 * (WinH / 13) / n;
		R_ = WinH / 2 - R - 10;
	}
	else
	{
		R = 5 * (WinW / 13) / n;
		R_ = WinW / 2 - R - 10;
	}
	float theta = 2.0f * 3.1415926f * i / n;
	int y1 = R_ * cos(theta) + y0;
	int x1 = R_ * sin(theta) + x0;
	vertC[i].x = x1;
	vertC[i].y = y1;
}

void MakeGraph()
{
	int amountVerts, amountEdges, sourceVertex, targetVertex, edgeWeight;
	cout << "Введите количество вершин в графе: "; cin >> amountVerts;
	cout << "Введите количество ребер в графе: "; cin >> amountEdges;
	for (int i = 1; i <= amountVerts; i++)
		graph.AddVertex(i);
	for (int i = 0; i < amountEdges; i++)
	{
		cout << "Исходная вершина: "; cin >> sourceVertex;
		cout << "Конечная вершина: "; cin >> targetVertex;
		cout << "Вес ребра: "; cin >> edgeWeight;
		graph.AddEdge(sourceVertex, targetVertex, edgeWeight);
	}
	cout << endl;
	MovMode = false;
	graph.PrintGraph();
}

int** TSPMatr()
{
	int n = graph.GetAmountVerts();
	int** matrix = new int* [n];
	for (int i = 0; i < n; i++)
		matrix[i] = new int[n];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int elem = graph.GetAdjMatrElem(i, j);
			if (elem == 0 or i == j)
				matrix[i][j] = -1;
			else
				matrix[i][j] = elem;
		}
	}
	return matrix;
}

int* FindMin(int* line, int n)
{
	int min = 1000000;
	for (int j = 0; j < n; j++)
		if (line[j] >= 0 && line[j] < min)
			min = line[j];
	for (int j = 0; j < n; j++)
		if (line[j] >= 0)
			line[j] -= min;
	return line;
}

int** ReductMatr(int** oldmatrix)
{
	int** matrix = oldmatrix;
	int n = graph.GetAmountVerts();
	for (int i = 0; i < n; i++)
		matrix[i] = FindMin(matrix[i], n);
	for (int i = 0; i < n; i++)
	{
		int min = 1000000;
		for (int j = 0; j < n; j++)
		{
			if (matrix[j][i] >= 0 && matrix[j][i] < min)
				min = matrix[j][i];
		}
		for (int j = 0; j < n; j++)
		{
			if (matrix[j][i] >= 0)
				matrix[j][i] -= min;
		}
	}
	return matrix;
}

int** RebuildMatr(int** oldmatrix)
{
	int n = graph.GetAmountVerts();
	int** matrix = ReductMatr(oldmatrix);
	int max = -1;
	int line, column;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j] == 0)
			{
				int minLine = 1000000;
				int minColumn = 1000000;
				for (int k = 0; k < n; k++)
				{
					if (matrix[i][k] != -1 && k != j && matrix[i][k] < minLine)
						minLine = matrix[i][k];
				}
				for (int k = 0; k < n; k++)
				{
					if (matrix[k][j] != -1 && k != i && matrix[k][j] < minColumn)
						minColumn = matrix[k][j];
				}
				if (max < minColumn + minLine)
				{
					max = minColumn + minLine;
					line = i;
					column = j;
				}
			}
		}
	}

	pair<int, int> p;
	p.first = line + 1;
	p.second = column + 1;
	PathVert.push_back(p);

	matrix[line][column] = -1;
	matrix[column][line] = -1;

	for (int i = 0; i < n; i++)
	{
		matrix[line][i] = -1;
		matrix[i][column] = -1;
	}
	return matrix;
}

void CommiResult(int n)
{
	int second = PathVert[0].second;
	int i = 2;
	WayVert.push_back(PathVert[0].first);
	WayVert.push_back(PathVert[0].second);
	while (i != graph.GetAmountVerts() + 1)
		for (int j = 1; j < graph.GetAmountVerts(); j++)
			if (PathVert[j].first == second)
			{
				second = PathVert[j].second;
				WayVert.push_back(second);
				i++;
			}
	WayVert.pop_back();
	cout << "Ответ: ";
	int j = 0;
	for (int i = 0; i < WayVert.size(); i++)
	{
		if (WayVert[i] == n)
			j = i;
	}
	for (int i = 0; i < WayVert.size() + 1; i++)
	{
		cout << WayVert[j % WayVert.size()];
		if (i != WayVert.size())
			cout << " -> ";
		j++;
	}
	int sum = 0;
	for (int i = 0; i < PathVert.size(); i++)
	{
		int line = PathVert[i].first - 1;
		int column = PathVert[i].second - 1;
		sum += graph.GetAdjMatrElem(line, column);
	}
	cout << "\nS = " << sum << endl;;
}

bool CommiCheck(int** matrix)
{
	if (graph.IsEmpty())
		return false;
	for (int i = 0; i < graph.GetAmountVerts(); i++)
	{
		int cnt = 0;
		for (int j = 0; j < graph.GetAmountVerts(); j++)
		{
			if (matrix[i][j] > 0)
				cnt++;
		}
		if (cnt < 1)
			return false;
	}
	return true;
}

int Circle_Check(int x, int y)
{
	for (int i = 0; i < graph.GetAmountVerts(); i++)
		if (pow(x - vertC[i].x, 2) + pow(y - vertC[i].y, 2) <= R * R)
			return i;
	return -1;
}

void Movement(int x, int y)//отслеживание движения мыши
{
	y = WinH - y;
	CursorX = x;
	CursorY = y;
	int i = Circle_Check(x, y);
	if (i != -1)
		ThisVert[i] = true;
	else
		for (int j = 0; j < graph.GetAmountVerts(); j++)
			ThisVert[j] = false;
	if (IsMove)
	{
		vertC[MovVert].x = CursorX;
		vertC[MovVert].y = CursorY;
	}
	ButtonsCheck(x, y);
	glutPostRedisplay();
}

void ButtonsCheck(int x, int y)
{
	if (x > 13 && x < WinW / 7 && y > 13 && y < 88)
		but = 1;
	else if (x > 13 && x < WinW / 7 && y > 98 && y < 173)
		but = 2;
	else if (x > 13 && x < WinW / 7 && y > 183 && y < 258)
		but = 3;
	else if (x > 13 && x < WinW / 7 && y > 268 && y < 343)
		but = 4;
	else if (x > 13 && x < WinW / 7 && y > 353 && y < 428)
		but = 5;
	else if (x > 13 && x < WinW / 7 && y > 438 && y < 513)
		but = 6;
	else
		but = 0;
}

void Click(int button, int state, int x, int y)//действия с кнопками 
{
	int j = Circle_Check(x, WinH - y);
	if (IsMove)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			IsMove = false;
			return;
		}
	}
	if (j != -1)
	{
		MovMode = true;
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			IsMove = true;
			MovVert = j;
			return;
		}
	}
	if (x <= WinW / 7 and x >= 0 and y >= 5 * WinH / 7 and y <= 6 * WinH / 7) // 6 нкопка
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int num;
			WayVert.clear();
			PathVert.clear();
			cout << "Введите исходную вершину: ";
			cin >> num;
			cout << endl;
			cout << "Решение задачи коммивояжера\n";
			int** matrix = TSPMatr();
			bool tsp = CommiCheck(matrix);
			if (!tsp)
			{
				cout << "\nЗадача Коммивояжера не может быть решена\n\n";
				return;
			}
			int n = graph.GetAmountVerts();
			while (PathVert.size() < n)
				matrix = RebuildMatr(matrix);
			cout << endl;
			CommiResult(num);
			return;
		}
	}
	if (x <= WinW / 7 and x >= 0 and y >= 0 and y <= WinH / 7) // 1 кнопка
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			WayVert.clear();
			PathVert.clear();
			Graph New;
			graph = New;
			MakeGraph();
			return;
		}
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
			MovMode = false;
			return;
		}
	}
	if (x <= WinW / 7 and x >= 0 and y >= 3 * WinH / 7 and y <= 4 * WinH / 7) // 4 кнопка
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int sourceVertex, targetVertex, edgeWeight, vertNum;
			cout << "Количество добавляемых ребер: "; cin >> vertNum;
			for (int i = 0; i < vertNum; i++)
			{
				cout << "Исходная вершина: "; cin >> sourceVertex;
				cout << "Конечная вершина: "; cin >> targetVertex;
				cout << "Вес ребра: "; cin >> edgeWeight;
				graph.AddEdge(sourceVertex, targetVertex, edgeWeight);
			}
			return;
		}
	}
	if (x <= WinW / 7 and x >= 0 and y >= 4 * WinH / 7 and y <= 5 * WinH / 7) // 5 кнопка
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int sourceVertex, targetVertex;
			cout << "Исходная вершина: "; cin >> sourceVertex;
			cout << "Конечная вершина: "; cin >> targetVertex;
			graph.DelEdge(sourceVertex, targetVertex);
			return;
		}
	}
	if (x <= WinW / 7 and x >= 0 and y >= WinH / 7 and y <= 2 * WinH / 7) // 2 кнопка
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			int cur = graph.GetAmountVerts();
			graph.AddVertex(cur + 1);
			vertC[cur].x = WinW / 2;
			vertC[cur].y = WinH / 2;
			cout << "\nДобавлена вершина: " << cur + 1 << endl;
			return;
		}
	}
	if (x <= WinW / 7 and x >= 0 and y >= 2 * WinH / 7 and y <= 3 * WinH / 7) // 3 кнопка
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			graph.DelVertex();
			int cur = graph.GetAmountVerts();
			cout << "\nУдалена вершина: " << cur << endl;
			return;
		}
	}
}

void MouseMove(int x, int y) {
	// 1
	if (x > 13 && x < WinW / 7 && y > 13 && y < 88) {
		state_buttom_1 = true;
		//cout << "buttom_1 ON	";
	}
	else state_buttom_1 = false;

	// 2
	if (x > 13 && x < WinW / 7 && y > 98 && y < 173) {
		state_buttom_2 = true;
		//cout << "buttom_2 ON	";
	}
	else state_buttom_2 = false;

	// 3
	if (x > 13 && x < WinW / 7 && y > 183 && y < 258) {
		state_buttom_3 = true;
		//cout << "buttom_3 ON	";
	}
	else state_buttom_3 = false;

	// 4
	if (x > 13 && x < WinW / 7 && y > 268 && y < 343) {
		state_buttom_4 = true;
		//cout << "buttom_4 ON	";
	}
	else state_buttom_4 = false;

	//5
	if (x > 13 && x < WinW / 7 && y > 353 && y < 428) {
		state_buttom_5 = true;
		//cout << "buttom_5 ON	";
	}
	else state_buttom_5 = false;
	
	// 6
	if (x > 13 && x < WinW / 7 && y > 438 && y < 513) {
		state_buttom_6 = true;
		//cout << "buttom_6 ON	";
	}
	else state_buttom_6 = false;
	cout << x << ":" << y;
	cout << endl;
}

void reshape(int w, int h)//обеспечивает масшатабирование
{
	WinW = w;
	WinH = h;
	glViewport(0, 0, (GLsizei)WinW, (GLsizei)WinH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble)WinW, 0, (GLdouble)WinH);
	glutPostRedisplay();
}

void display()//вывод изображения на экран
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WinW, 0, WinH);
	glViewport(0, 0, WinW, WinH);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glutPassiveMotionFunc(MouseMove);
	graph.DrawGraph();

	Button1();
	Button2();
	Button3();
	Button4();
	Button5();
	Button6();

	glutSwapBuffers();
}