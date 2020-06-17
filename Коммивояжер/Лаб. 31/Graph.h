#pragma once
#include <vector>
#include <glut.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <queue>
using namespace std;

const int MaxV = 20;//максимальное число вершин
extern int WinW;//ширина и высота окна
extern int WinH;
struct coordinates //структура координат вершин
{
	int x, y;
};

class Graph
{
private:
	vector<int> VList;
	int AdjMatr[MaxV][MaxV];
public:    
	Graph();
	~Graph() {};
	bool IsEmpty();//проверка на пустоту
	bool IsFull(); //проверка на переполнение
	vector<int> GetVList() { return  VList; }      //получить вектор вершин 
	int GetVElem(int i) { return VList[i]; }//получить значение вершины                                                
	int GetAmountEdges();//получить количество ребер                      
	int GetAmountVerts() { return VList.size(); }//получить количество вершин                             
	int GetVertPos(const int& v);//получить координаты вектора	
	int GetAdjMatrElem(int i, int j) { return AdjMatr[i][j]; }//получить элемент матрицы смежности   
	void PrintGraph();//вывод матрицы 
	void AddVertex(const int& v);//вставка вершины               
	void AddEdge(const int& v, const int& v2, int w);//вставка ребра	                                                         
	void DelVertex();//удаление вершины                                           
	void DelEdge(const int& v1, const int& v2);  //удаление ребра                 
	void DrawGraph(); //изображение графа                                              
};
extern Graph graph;
int** TSPMatr(); //создается матрица, заменяя 0 на -1
int* FindMin(int* l, int n);//поиск минимального элемента в строке матрицы
int** ReductMatr(int** m); //редукция матрицы
int** RebuildMatr(int** m);
void DrawCircle(int x, int y, int R);
void DrawVert(int n);//рисование вершины  
void DrawLine(int text, int x0, int y0, int x1, int y1);
void DrawT(int nom, int x1, int y1);
bool CommiCheck(int** matrix);
int Circle_Check(int x, int y);//проверка на вхождение курсорв в вершину                                                
void ButtonsCheck(int x, int y);//проверка на вхождение курсора в кнопки                                                         
void SetCoords(int i, int n); //установление начальных координат                                                                                                                                               
void Movement(int x, int y);   //передвижение вершин                                                 
void Click(int button, int state, int x, int y);  //нажимаение на кнопки 
void MakeGraph();   //создание графа 
void reshape(int w, int h);//обеспечивает масштабирование                                
void display();//обеспечивает вывод изображения         
void Button1();
void Button2();
void Button3();
void Button4();
void Button5();
void Button6();