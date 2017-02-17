#ifndef __ROUTE_H__
#define __ROUTE_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>   
#include <map>  
#include <iostream>  
#include <string.h>  
#include <set>  
#include <stack>  
#include <queue>  
#include <vector>  

#define MAX_VERTEX_NUMS  500    //��󶥵���
#define MAX_WEIGHT  -1              //���Ȩֵ
#define MAX_MUST_PASS    50     //���ؾ�����

using namespace std;
void search_route(char *graph[5000], int edge_num, char *condition);

namespace code{
	class CodeCraft
		{
		  public:
		  	//���캯��������ߵ�����
		  	CodeCraft(int edge_nums)       
				{
				    gEdgeNums = edge_nums;
				    gStartVex = 0;
				    gEndVex = 0;
				    gPathSize = 0;
				    gMinCost = 10000;
				    gMinPath = new int[MAX_VERTEX_NUMS];
				    for(int i = 0; i < MAX_VERTEX_NUMS; i++)
						gMinPath[i] = 0;
				    gMustPass = new int[MAX_MUST_PASS];
				    for(int i = 0; i < MAX_MUST_PASS; i++)
						gMustPass[i] = 0;
				};
			~CodeCraft()
				{
				   delete[] gMinPath;
				   gMinPath = NULL;
				   delete[] gMustPass;
				   gMustPass = NULL;
				};
			void build_graph(char **const topo , int const edge_nums);  //��������ͼ
			void edge_to_num(char *one_edge, int *num);     //��topoͼ��Ϣת����int����
                        void demand_to_num(char * const demand);     //�������ļ�����
                        void dfs_best_paths(int pre_cost, int start,  int *visited);  //�������
	                void dfs_solution();
			int   next_adj_vertex(int curVex, int nextVex, bool flagfirst);
			void get_new_path(int *pResultPath, int path_size, int curCost);  
					
		  public:
		  	int gStartVex;           //���
		  	int gEndVex;            //�յ�
		  	int gVertTexNums; //�������
			int gEdgeNums;     //����ߵ�����
			int gMustNums;     //�ؾ���ĸ���
			int gPathSize;       //���·���ĳ���
			int gMinCost;        //����·����Ȩֵ
			int *gMinPath;     //����洢����·��
			int *gMustPass;  //����洢�ؾ���
		};
}

#endif
