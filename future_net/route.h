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

#define MAX_VERTEX_NUMS  500    //最大顶点数
#define MAX_WEIGHT  -1              //最大权值
#define MAX_MUST_PASS    50     //最大必经点数

using namespace std;
void search_route(char *graph[5000], int edge_num, char *condition);

namespace code{
	class CodeCraft
		{
		  public:
		  	//构造函数，有向边的条数
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
			void build_graph(char **const topo , int const edge_nums);  //生成有向图
			void edge_to_num(char *one_edge, int *num);     //把topo图信息转换成int类型
                        void demand_to_num(char * const demand);     //把需求文件读出
                        void dfs_best_paths(int pre_cost, int start,  int *visited);  //暴力穷举
	                void dfs_solution();
			int   next_adj_vertex(int curVex, int nextVex, bool flagfirst);
			void get_new_path(int *pResultPath, int path_size, int curCost);  
					
		  public:
		  	int gStartVex;           //起点
		  	int gEndVex;            //终点
		  	int gVertTexNums; //顶点个数
			int gEdgeNums;     //有向边的条数
			int gMustNums;     //必经点的个数
			int gPathSize;       //结果路径的长度
			int gMinCost;        //最优路径的权值
			int *gMinPath;     //数组存储最优路径
			int *gMustPass;  //数组存储必经点
		};
}

#endif
