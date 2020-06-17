#pragma once
#include <vector>
#include <glut.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <queue>
using namespace std;

const int MaxV = 20;//������������ ����� ������
extern int WinW;//������ � ������ ����
extern int WinH;
struct coordinates //��������� ��������� ������
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
	bool IsEmpty();//�������� �� �������
	bool IsFull(); //�������� �� ������������
	vector<int> GetVList() { return  VList; }      //�������� ������ ������ 
	int GetVElem(int i) { return VList[i]; }//�������� �������� �������                                                
	int GetAmountEdges();//�������� ���������� �����                      
	int GetAmountVerts() { return VList.size(); }//�������� ���������� ������                             
	int GetVertPos(const int& v);//�������� ���������� �������	
	int GetAdjMatrElem(int i, int j) { return AdjMatr[i][j]; }//�������� ������� ������� ���������   
	void PrintGraph();//����� ������� 
	void AddVertex(const int& v);//������� �������               
	void AddEdge(const int& v, const int& v2, int w);//������� �����	                                                         
	void DelVertex();//�������� �������                                           
	void DelEdge(const int& v1, const int& v2);  //�������� �����                 
	void DrawGraph(); //����������� �����                                              
};
extern Graph graph;
int** TSPMatr(); //��������� �������, ������� 0 �� -1
int* FindMin(int* l, int n);//����� ������������ �������� � ������ �������
int** ReductMatr(int** m); //�������� �������
int** RebuildMatr(int** m);
void DrawCircle(int x, int y, int R);
void DrawVert(int n);//��������� �������  
void DrawLine(int text, int x0, int y0, int x1, int y1);
void DrawT(int nom, int x1, int y1);
bool CommiCheck(int** matrix);
int Circle_Check(int x, int y);//�������� �� ��������� ������� � �������                                                
void ButtonsCheck(int x, int y);//�������� �� ��������� ������� � ������                                                         
void SetCoords(int i, int n); //������������ ��������� ���������                                                                                                                                               
void Movement(int x, int y);   //������������ ������                                                 
void Click(int button, int state, int x, int y);  //���������� �� ������ 
void MakeGraph();   //�������� ����� 
void reshape(int w, int h);//������������ ���������������                                
void display();//������������ ����� �����������         
void Button1();
void Button2();
void Button3();
void Button4();
void Button5();
void Button6();